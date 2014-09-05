#ifndef COPYDETECTDIALOG_H
#define COPYDETECTDIALOG_H

#include <QDialog>
#include <QDir>
 #include <QFileInfo>
#include <QDebug>
#include <QMessageBox>

#include "ui_CopyDetectUi.h"
#include "ui_VerifyDetectDialog.h"
#include "copypropertiesui.h"
#include "ui_CopyPropertiesDialog.h"
#include "copyrangewidget.h"

#include <windows.h>
#include "taskmanager.h"

#include "partitionmodel.h"


class CopyProperiesUiDialog
	: public QDialog
{
	Q_OBJECT
public:
	CopyProperiesUiDialog( QWidget *parent , DWORD id , PartitionTreeModel *  model = nullptr ) 
		: QDialog( parent )
		, id_ ( id )
		//, settings_ ( DM_Settings::getSettings() )
	{
		ui_.setupUi( this );
		ui_.propertiesWidget->setProperties( id );

		ui_.partitionWidget->getView()->setModel( model );

		connect( ui_.fullCopyButton , SIGNAL( clicked() ) , this , SLOT( FullCopyClicked() ) );
		connect( ui_.partitionCopyButton , SIGNAL( clicked() ) , this , SLOT( PartitionCopyClicked() ) );
		connect( ui_.userCopyButton , SIGNAL( clicked() ) , this , SLOT( UserCopyClicked() ) );
		//auto copy_mode = settings_->getCopySettings( id_ ).copy_mode_;
		//this->setCopyMode( copy_mode );


	/*	auto options_widget = ui_.widget;*/

		int k = 1;
	}
	~CopyProperiesUiDialog()
	{
		id_= 0;
		//settings_ = nullptr;
	}
	void Initialize( DiskDevicePtr & source , DiskDevicePtr & target )
	{
		if ( source->isDetected() && target->isDetected() )
		{
			showOtherWidgets();
			ui_.rangeWidget->getRange()->setRange( 0 , 0 , getMinValue( source->getSize() , target->getSize() ) );
		}
		else
			showOtherWidgets(false);
		//ui_.stackedWidget->setCurrentIndex( enFullCopy );
		//SectorCopySetting & copy_settings = settings_->getCopySettings( id_ );
		//this->setCopyMode( copy_settings.copy_mode_ );

	}
	void setCopyMode( int nCopyType )
	{
		switch ( nCopyType )
		{
		case DMTool::FULL_COPY:
			//FullCopyClicked( );
			ui_.fullCopyButton->click();
			break;

		case DMTool::PARTITION_COPY:
			ui_.partitionCopyButton->click();
			break;

		case DMTool::USER_COPY:
			ui_.userCopyButton->click();
			break;

		default:
			FullCopyClicked();
		}
	}
	int getCopyMode() const
	{
		return ui_.stackedWidget->currentIndex();
	}
	void showOtherWidgets( bool bShow = true )
	{
		showRangeWidget( bShow );
		showPartitionWidget( bShow );
	}
	void showRangeWidget( bool bShow = true )
	{
		ui_.rangeWidget->setEnabled( bShow );
	}
	void showPartitionWidget( bool bShow = true )
	{
		ui_.partitionWidget->setEnabled( bShow );
	}
	CopyRangeWidget * getRangeWidget()
	{
		return ui_.rangeWidget;
	}
	IOptionsView * getDeviceWidget() const
	{
		return ui_.DeviceOptionsWidget;
	}
private slots:
	void FullCopyClicked()
	{
		//ui_.stackedWidget->setCurrentIndex( DMTool::FULL_COPY );
		//settings_->getCopySettings( id_ ).copy_mode_ = DMTool::FULL_COPY;
		//ui_.stackedWidget->currentWidget()->setSizePolicy(QSizePolicy::Ignored,	QSizePolicy::Ignored);
//		this->adjustSize();
		//this->updateGeometry();
	}
	void PartitionCopyClicked()
	{
		//ui_.stackedWidget->setCurrentIndex( DMTool::PARTITION_COPY );
		//settings_->getCopySettings( id_ ).copy_mode_ = DMTool::PARTITION_COPY;
		int k = 1;
		k = 2;
		//ui_.stackedWidget->currentWidget()->setSizePolicy(QSizePolicy::Expanding,	QSizePolicy::Expanding);
		//this->adjustSize();
	}
	void UserCopyClicked()
	{
		//ui_.stackedWidget->setCurrentIndex( DMTool::USER_COPY );
		//settings_->getCopySettings( id_ ).copy_mode_ =  DMTool::USER_COPY;
		//ui_.stackedWidget->currentWidget()->setSizePolicy(QSizePolicy::Ignored,	QSizePolicy::Ignored);
		//this->adjustSize();
	}

private:
	DWORD id_;
	//DM_Settings * settings_;
	Ui::CopyPropertiesDlg ui_;
};


class AbstractDetectDialog 
	: public QDialog
{
	Q_OBJECT
public:

	AbstractDetectDialog ( QWidget * parent = nullptr )
	: QDialog( parent )
	{

	}

	virtual QString getFolderName() const  = 0;
	virtual void setFolderName( const QString & folder_name ) = 0;
	virtual QString getTaskName() const = 0;

public slots:
	void accept() override
	{
		QDir dirPath( getFolderName() );
		QString folder_name = getFolderName();
		auto file_manager = DMTool::FileManager::GetFileManager();
		if ( DMTool::FileManager::isExist( getFolderName(),getTaskName()) )
		{
			QMessageBox msgBox;
			msgBox.setText("<B>This task already exists.</B>");
			msgBox.setInformativeText("Folder will be removed. Continue?");
			msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Ok);
			msgBox.setIcon(QMessageBox::Question);

			if ( msgBox.exec() == QMessageBox::Ok )
			{
				if ( DMTool::FileManager::MakeFolder( folder_name , getTaskName() ) )
					this->setFolderName( folder_name );
					QDialog::accept();	
			}
		}
		else
		{

			if ( DMTool::FileManager::MakeFolder( folder_name , getTaskName() ) )
			{
				this->setFolderName( folder_name );
				QDialog::accept();	
			}
			else
			{
				QMessageBox msgBox;
				msgBox.setText("<B>It is impossible to create a task.</B>");
				msgBox.setInformativeText("Make sure the path.");
				msgBox.setStandardButtons(QMessageBox::Ok );
				msgBox.setIcon(QMessageBox::Critical);
				msgBox.exec();
				return;
			}
		}
	}
};

class DiskMasterDevice;


#include <QButtonGroup>

class CopyDetectDialog 
	: public AbstractDetectDialog
{
	Q_OBJECT

public:
	CopyDetectDialog(QWidget *parent, DWORD DiskMaster_ID);
	~CopyDetectDialog();
	int getSourceNumber() const
	{
		return ui_.sourceCombo_->currentIndex();
	}
	int getTargetNumber() const 
	{
		return ui_.targetCombo_->currentIndex();
	}
	QString getFolderName() const override
	{
		return ui_.workFolderEdit_->text();
	}
	QString getTaskName() const override
	{
		return ui_.taskNameEdit_->text();
	}
	void setFolderName( const QString & folder_name ) 
	{
		ui_.workFolderEdit_->setText( folder_name );
	}

public slots:
	void copySettingClicked( )
	{
		pCopyProperties_->setCopyMode( buttonGroup_.checkedId() );
		pCopyProperties_->exec();
		
		buttonGroup_.button ( pCopyProperties_->getCopyMode() )->click() ;

	}
private slots:
	void fullCopyClicked()
	{
		pCopyProperties_->setCopyMode( DMTool::FULL_COPY );
	}
	void partitionCopyClicked()
	{
		pCopyProperties_->setCopyMode( DMTool::PARTITION_COPY );
	}
	void userCopyClicked()
	{
		pCopyProperties_->setCopyMode( DMTool::USER_COPY );
	}

private:
	Ui::copyDetectDialog ui_;
	DiskMasterDevice * disk_master_;
	QButtonGroup buttonGroup_;

	CopyProperiesUiDialog * pCopyProperties_;
};

class VerifyDetectDialog
	: public AbstractDetectDialog
{
	Q_OBJECT
public:
	VerifyDetectDialog( QWidget *parent, DWORD DiskMaster_ID );
	~VerifyDetectDialog()
	{

	}
	QString getFolderName() const override
	{
		return ui_.workFolderEdit_->text();
	}
	QString getTaskName() const override
	{
		return ui_.taskNameEdit_->text();
	}
	void setFolderName( const QString & folder_name ) 
	{
		ui_.workFolderEdit_->setText( folder_name );
	}

	int getDeviceIndex()
	{
		return ui_.verifyCombo_->currentIndex();
	}
private:
	Ui::VerifyDetectUi ui_;
	DiskMasterDevice * disk_master_;
	//DWORD id_;
};


#include "ui_EraseDetectUi.h"
class EraseDetectDialog
	: public AbstractDetectDialog
{
	Q_OBJECT
public:
	EraseDetectDialog( QWidget *parent, DWORD DiskMaster_ID );	// ????????????????

	~EraseDetectDialog()
	{

	}
	QString getFolderName() const override
	{
		return ui_.workFolderEdit_->text();
	}
	QString getTaskName() const override
	{
		return ui_.taskNameEdit_->text();
	}
	void setFolderName( const QString & folder_name ) 
	{
		ui_.workFolderEdit_->setText( folder_name );
	}

	int getDeviceIndex()
	{
		return ui_.verifyCombo_->currentIndex();
	}
	DWORD erasePattern() const
	{
		return ui_.patternWidget->getPattern();
	}
private:
	Ui::EraseDetectUi ui_;
	DiskMasterDevice * disk_master_;
	//DWORD id_;
};
//
//#include "ui_StartTaskDialog.h"
//
//enum enTaskCommands
//{
//	tContinue_task = 0,
//	tReadUnRead_task,
//	tReadBads_task,
//	tError_task
//};
//
//class StartTaskDialog
//	: public QDialog
//{
//	Q_OBJECT
//public:
//	StartTaskDialog( QWidget * parent = 0)
//		: QDialog ( parent )
//		, commands_ ( tError_task )
//	{
//		ui_.setupUi(this);
//		setEnableContinueButton();
//	}
//	enTaskCommands getCommand() const
//	{
//		return commands_;
//	}
//	void setEnableContinueButton( bool bEnable = true )
//	{
//		ui_.commandLinkButton->setEnabled( bEnable );
//	}
//private slots:
//	void Continue_clicked()
//	{
//		commands_ = tContinue_task;
//	}
//	//void StarteNew_clicked()
//	//{
//	//	commands_ = tStartNew_task;
//	//}
//	void ReadUnRead_clicked()
//	{
//		commands_ = tReadUnRead_task;
//	}
//	void ReadBads_clicked()
//	{
//		commands_ = tError_task;
//	}
//private:
//	Ui::Dialog ui_;
//	enTaskCommands commands_;
//};



#endif // COPYDETECTDIALOG_H
