#include "imagewriter.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

#include "devicetableview.h"
#include "MainSubject.h"

#include "windows.h"

#include "IOLibrary/iofunctions.h"

#include "DeviceLibrary/Writer.h"

ImageWriter::ImageWriter(QWidget *parent)
	: QMainWindow(parent)
	, copy_thread( nullptr )
	, max_file_size( 0 )
	, state_( start )
{
	ui.setupUi(this);

	targetDialog_ = std::shared_ptr< QDialog> ( new QDialog(this) );
	auto dlg = targetDialog_.get();
	uiSelectionDialog.setupUi( dlg );

	
	connect( ui.selectFileButton , SIGNAL( clicked() ) , this , SLOT( FileOpenCliced() ) );
	connect( ui.selectHddButton , SIGNAL( clicked() ) , this , SLOT( HddOpenCliced() ) );
	connect( ui.startButton , SIGNAL( clicked() ) , this , SLOT( StartButtonClicked() ) );

	file_ = QString::fromLocal8Bit("c:\\ukrkardan\\hdd.img");
	ui.fileEdit->setText( file_ );
	ui.hddEdit->setText( DeviceToString(selected_device_) );
	
	copy_thread = new CopyThread (parent);
	connect( copy_thread , SIGNAL( error_name( const QString &  ) ), this , SLOT(OnErrorName( const QString & ) ) );
	connect( copy_thread , SIGNAL( finish_error( const QString &  ) ) , this , SLOT( OnFinishError( const QString & ) ) );
	connect( copy_thread , SIGNAL( finished() )  , this , SLOT( OnFinishOk() ) );
	connect( copy_thread , SIGNAL( update_lba( qlonglong ) ) , this , SLOT( OnUpdateLba( qlonglong ) ) );


}

ImageWriter::~ImageWriter()
{
	if ( copy_thread )
	{
		delete copy_thread;
		copy_thread = nullptr;
	}
}


void ImageWriter::FileOpenCliced()
{
	file_ = QFileDialog::getOpenFileName(this , tr("Open Image") , "c:\\ukrkardan\\" , tr("Image Files (*.img)"));
	ui.fileEdit->setText( file_ );
}


void ImageWriter::HddOpenCliced()
{
	auto * pTableView = uiSelectionDialog.DeviceTable;

	pTableView->RefreshDevices();

	//DeviceTableView * pDeviceView = selectionDialog.DeviceTable;
	//if (pTableView->isEmptyDeviceList())
	//{
	//	uiSelectionDialog.okButton->setDisabled(true);
	//	uiSelectionDialog.DeviceTable->setDisabled(true);
	//}
	int iResult = targetDialog_->exec();
	if (iResult == QDialog::Accepted)	// Pressed 'OK'
	{
		selected_device_ = pTableView->GetSelectedDevice();
		if (selected_device_)
		{
			if ( selected_device_->isSystemDisk() )
			{
				QString error_text = QString::fromLocal8Bit("Вы выбрали системный диск,\r\n");
						error_text +=  QString::fromLocal8Bit("если будет произведени запись на этот диск,\r\n");
						error_text +=  QString::fromLocal8Bit("то операционная система будет уничтожена.\r\n");
						error_text +=  QString::fromLocal8Bit("Выберите другой диск");

				QMessageBox show_box (QMessageBox::Critical , QString::fromLocal8Bit("Ошибка"), error_text );
				show_box.exec();
				selected_device_ = nullptr;
			}
			else
			{
				ui.hddEdit->setText( DeviceToString(selected_device_) );
			}
		}
		ui.hddEdit->setText( DeviceToString(selected_device_) );
	}
	else	// Pressed 'Cancel'
	{
		DevicePtr nullDevice;
		ui.hddEdit->setText( DeviceToString( nullDevice ) );
	}


}
void ImageWriter::OnErrorName( const QString & error_text )
{
	QMessageBox show_box (QMessageBox::Critical , QString::fromLocal8Bit("Ошибка"), error_text );
	show_box.exec();
	state_ = start;
	ui.startButton->setText( QString::fromLocal8Bit( "Старт" ) );
	ui.startButton->setIcon(QIcon("icons\\start.png"));

}
void ImageWriter::OnFinishError( const QString & error_text )
{
	OnErrorName(error_text);
	//	??????????
}
void ImageWriter::OnFinishOk()
{
	ui.progressBar->setValue(100);
	QMessageBox show_box (QMessageBox::Information , QString::fromLocal8Bit("Копирование"), QString::fromLocal8Bit("Запись на диск успешно завершина.") );
	show_box.exec();
}
void ImageWriter::OnUpdateLba( qlonglong offset )
{
	int progressValue =  (int) ( ( offset * 100) / ( max_file_size ) );

	if ( progressValue > 0 && progressValue < 100 )
		ui.progressBar->setValue( progressValue );
}

void ImageWriter::StartButtonClicked()
{
	if ( state_ == start )
	{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	if ( !IO::open_read(hFile , file_.toStdString() ) )
	{
		OnErrorName( QString::fromLocal8Bit("Не возможно открыть файл.") );
		return;
	}

	max_file_size = ::GetFileSize(hFile , NULL );

	if ( max_file_size == 0 )
	{
		OnErrorName( QString::fromLocal8Bit("Файл поврежден.") );
		return;
	}
	CloseHandle(hFile);


	ui.progressBar->setValue( 0 );

	copy_thread->setParams(file_ , selected_device_);
	copy_thread->start();

	state_ = stop;
	ui.startButton->setText( QString::fromLocal8Bit( "Стоп" ) );
	ui.startButton->setIcon(QIcon("icons\\stop.png"));
	}
	else
	{
		state_ = start;
		ui.startButton->setText( QString::fromLocal8Bit( "Старт" ) );
		ui.startButton->setIcon(QIcon("icons\\start.png"));
		copy_thread->terminate();
	}
	

}


CopyThread::CopyThread(QObject * parent )
	: QThread( parent )
{

}
CopyThread::~CopyThread()
{

}


void CopyThread::run()
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	HANDLE hDrive = INVALID_HANDLE_VALUE;

	if ( !IO::open_read(hFile , file_.toStdString()) )
	{
		emit error_name(QString::fromLocal8Bit("Не возможно открыть файл."));
		return;
	}

	if ( !hdd_ )
	{
		emit error_name(QString::fromLocal8Bit("Не выбран диск."));
		return;
	}

	std::shared_ptr < CWriter >  pWriter (new CWriter( hdd_ ) );


	if ( !pWriter->Open() )
	{
		emit error_name(QString::fromLocal8Bit("Не возможно открыть диск."));
		return;
	}

	DWORD file_size = ::GetFileSize(hFile , NULL );
	if ( file_size == 0 )
	{
		emit error_name(QString::fromLocal8Bit("Файл поврежден."));
		return;

	}

	const int BlockSize = 256*512;
	BYTE data_block[ BlockSize ];

	qlonglong cur_pos = 0;
	DWORD bytesRead = 0;
	DWORD byteRemaining = 0;

	bool bResult = false;

	while (cur_pos < file_size )
	{

		if ( file_size - cur_pos > BlockSize )
			byteRemaining = BlockSize;
		else
			byteRemaining = file_size - cur_pos;

		bResult = IO::read_block( hFile , data_block , byteRemaining , bytesRead ) ;
		if ( !bResult || bytesRead == 0 )
		{
			emit finish_error(QString::fromLocal8Bit("Чтения файла не возможно."));
			return;		
		}

		if ( pWriter->Write( data_block , bytesRead , cur_pos ) == 0  )
		{
			emit finish_error(QString::fromLocal8Bit("Записать на диск не возможно."));
			return;		
		}

		cur_pos += bytesRead;
		emit update_lba( cur_pos );
	}

	CloseHandle(hFile);
	CloseHandle(hDrive);


}

void CopyThread::setParams( const QString & file , const DevicePtr & hdd )
{
	file_ = file;
	hdd_ = hdd;
}
