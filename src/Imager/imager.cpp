#include "imager.h"

#include "selectwindow.h"

#include "devicetableview.h"

#include "AbstractFactory.h"
#include "Buffer.h"
#include "Queue.h"
#include "Solver.h"
#include "Declaration.h"

 #include <QMessageBox>

#include "physicaldialog.h"
#include "ui_PhysicalDialog.h"
#include <assert.h>


Imager::Imager(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	
	SelectionDilog_ = CreateSelectionDialog(SelectionUi_);
	PhysicalDialog_ = CreatePhysicalDialog(physicalUi_);
	PhysicalDialog * pPhysicDlg = dynamic_cast<PhysicalDialog *> ( PhysicalDialog_.get() );
	//pPhysicDlg->SetLogFolder(HelpLib::GetCurrentDir());
	
	connect(ui.SourceButton,SIGNAL(clicked()) , this , SLOT(OnSourceSelect()) );
	connect(ui.TargetButton,SIGNAL(clicked()) , this , SLOT(OnTargetSelect()) );
	connect(ui.StartButton, SIGNAL (clicked()), this , SLOT(OnStartClicked()) );

	connect( physicalUi_.SourceStartSector, SIGNAL(textChanged(QString)), pPhysicDlg, SLOT(OnChangeSectorsCount(QString)) );

	connect( physicalUi_.DeviceTable, SIGNAL( clicked(QModelIndex)), pPhysicDlg, SLOT (OnSelectTarget(QModelIndex) ) );


	SourceSubject_.Attach(new TextObserver(ui.SourceText));
	SourceSubject_.Attach(new TargetButtonObserver(ui.TargetButton));
	SourceSubject_.Attach( new PhysicalObserver( pPhysicDlg ) );

	TargetSubject_.Attach(new TextObserver(ui.TargetText));

	Declaration::LanguageDll * pDllLanguage = Declaration::LanguageDll::GetInstance();
	pDllLanguage->SetLanguage(Declaration::EngishLanguage);


	OnSourceSelect();
}
Imager::~Imager()
{

}
void Imager::OnSourceSelect()
{
	SelectionUi_.DeviceTable->RefreshDevices();


	DeviceTableView * pDeviceView = SelectionUi_.DeviceTable;

	int iWidth = pDeviceView->GetTableWidth() + 30;
	QSize moveSize = SelectionDilog_->size();
	moveSize.setWidth(iWidth);
	SelectionDilog_->setMinimumWidth(iWidth);
	SelectionDilog_->setMinimumHeight(moveSize.height());
	SelectionDilog_->resize(moveSize);

	int iResult = SelectionDilog_->exec();
	if (iResult == QDialog::Accepted)	// Pressed 'OK'
	{
		DevicePtr SourceDevice = pDeviceView->GetSelectedDevice();
		if (SourceDevice)
		{
			SourceSubject_.SelectDevice(SourceDevice);
		}
	}
	else	// Pressed 'Cancel'
	{
		DevicePtr nullDevice;
		SourceSubject_.SelectDevice(nullDevice);
	}

}

void Imager::OnTargetSelect()
{
	assert( SourceSubject_.GetDevice() != NULL );
	TargetTableView * pTableView = physicalUi_.DeviceTable;

	pTableView->SetSourceNumber(SourceSubject_.GetDevice()->GetNumber());
	pTableView->RefreshDevices();

	//DeviceTableView * pDeviceView = selectionDialog.DeviceTable;
	if (pTableView->isEmptyDeviceList())
	{
		physicalUi_.okButton->setDisabled(true);
		physicalUi_.DeviceTable->setDisabled(true);
	}
	int iResult = PhysicalDialog_->exec();
	if (iResult == QDialog::Accepted)	// Pressed 'OK'
	{
		DevicePtr SourceDevice = pTableView->GetSelectedDevice();
		if (SourceDevice)
		{
			TargetSubject_.SelectDevice(SourceDevice);

			//qDebug("#%d, Device name %s",SourceDevice->GetNumber(), SourceDevice->GetName());
		}
	}
	else	// Pressed 'Cancel'
	{
		DevicePtr nullDevice;
		TargetSubject_.SelectDevice(nullDevice);
	}

}
Imager::DialogPtr Imager::CreateSelectionDialog(Ui::SelectionDialog & selectionDialog)
{
	DialogPtr SelectDialog( new QDialog(this) );
	selectionDialog.setupUi(SelectDialog.get());

	return SelectDialog;
}
Imager::DialogPtr Imager::CreatePhysicalDialog(Ui::PhysicalDialog & physicalDialog)
{
	DialogPtr PhysicDlg( new PhysicalDialog(this , &physicalDialog ) );
	physicalDialog.setupUi(PhysicDlg.get());

	return PhysicDlg;
}

void Imager::ShowError(string ErrorString)
{
	QMessageBox msgBox;
	msgBox.setText( QString::fromStdString(ErrorString) );
	msgBox.setIcon( QMessageBox::Warning );
	msgBox.exec();
}
void Imager::OnStartClicked()
{
	if (SourceSubject_.isEmpty())
	{
		ShowError("No Selected Source device!");
		return;
	}

	DevicePtr SourceDevice = SourceSubject_.GetDevice();
	DWORD BufferSize = 128*512;


	CAllocatorFactory AllocFactory;
	CAllocator * pAllocator = AllocFactory.CreateAllocator(BufferSize,1000);

	CQueueFactory QueueFactory;
	IQueue *pQueue = QueueFactory.CreateQueue();

	CReaderFactory ReaderFactory;
	IReader * pReader = ReaderFactory.CreateReader(SourceDevice);
	pReader->Open();

	CConsistentFactory ConsistentFactory;

	CReaderConsistent * pConsistentReader = NULL;
	pConsistentReader = dynamic_cast<CReaderConsistent*> ( ConsistentFactory.CreateStreamReader(pReader,pQueue,pAllocator) ) ;

	pConsistentReader->SetBlockSize(BufferSize);
	pConsistentReader->SetDevice(SourceDevice);
	pConsistentReader->SetOffset(0);
	pConsistentReader->SetSectorsCount(999999);
	

	CurrentLBAObserver * pLBAObserver = new CurrentLBAObserver;
	connect( pLBAObserver, SIGNAL(ChangeLbaText(qlonglong)), this, SLOT(OnChangeCurrentLBA(qlonglong)) );

	pConsistentReader->Attach( pLBAObserver );

	CTaskFactory TaskFactory;
	CTaskManager * pTaskManager = (CTaskManager *) TaskFactory.CreateTask();

	pTaskManager->SetQueue(pQueue);
	pTaskManager->SetAllocator(pAllocator);

	TaskHolder_.AddStreamReader(  StreemReaderPtr(pConsistentReader) );
	TaskHolder_.AddTaskManager( AbstractTaskPtr(pTaskManager) );

	if (!TaskHolder_.isReady())
	{
		ShowError(TaskHolder_.GetErrorString());
		return;
	}
	TaskHolder_.StartThreads();


}
void Imager::OnChangeCurrentLBA(LONGLONG CurrentLBA)
{
	ui.EditNumberLBA->setText(QString::number(CurrentLBA));
}




TaskHolder::TaskHolder()
{

}
TaskHolder::~TaskHolder()
{
	CCommunicateLock * pCommunicateLock = CCommunicateLock::GetInstance();
	pCommunicateLock->Abort();
}
void TaskHolder::AddStreamReader(StreemReaderPtr pStreamReader)
{
	PtrStreamReader_ = pStreamReader;
}
void TaskHolder::AddTaskManager(AbstractTaskPtr pTask)
{
	PtrAbstractTask_ = pTask;
}
void TaskHolder::StartThreads()
{
	CCommunicateLock * pCommunicateLock = CCommunicateLock::GetInstance();
	pCommunicateLock->Resume();

	PtrStreamReader_->Start();
	PtrAbstractTask_->Run();
}
bool TaskHolder::isReady()
{
	assert(PtrStreamReader_ != NULL);
	if ( !PtrStreamReader_->isReady() )
	{
		ErrorString_ = PtrStreamReader_->GetErrorString();
		return false;
	}

	assert(PtrAbstractTask_ != NULL);
	if ( !PtrAbstractTask_->isReady() ) 
	{
		ErrorString_ = PtrAbstractTask_->GetErrorString();
		return false;
	}

	return true;
}
string TaskHolder::GetErrorString() const
{
	return ErrorString_;
}