#include "copydetectdialog.h"

#include "DiskMasterLib\dm_device.h"

#include "factories.h"
#include "Functions.h"



CopyDetectDialog::CopyDetectDialog(QWidget *parent, DWORD DiskMaster_ID)
	: AbstractDetectDialog( parent )
	, disk_master_ ( DMTool::getDiskMaster(DiskMaster_ID) )
	, pCopyProperties_( nullptr )
{
	ui_.setupUi(this);

	bool bShow = false;

	if ( disk_master_ )
	{
		for ( auto iCount = 0; iCount < disk_master_->source_count(); ++iCount )
		{
			auto disk_ptr = disk_master_->getSource(iCount);
			ui_.sourceCombo_->addItem( identifyIcon(disk_ptr) , displayName(disk_ptr) );
			//if ( disk_ptr->isDetected() )
			//	bShow = true;
		}
		for ( auto iCount = 0; iCount < disk_master_->target_count(); ++iCount )
		{
			auto disk_ptr = disk_master_->getTarget(iCount);
			ui_.targetCombo_->addItem( identifyIcon(disk_ptr) , displayName(disk_ptr) );
			ui_.targetCombo_->setCurrentIndex( iCount );
			//if ( disk_ptr->isDetected() )
			//	bShow = true;
		}
	}

	pCopyProperties_ = new CopyProperiesUiDialog( this, DiskMaster_ID );
	pCopyProperties_->setWindowFlags(Qt::Dialog);
	pCopyProperties_->setWindowModality(Qt::WindowModal);
	pCopyProperties_->showOtherWidgets(bShow);

	ui_.workFolderEdit_->setText( "c:\\"/*DM_Settings::getSettings()->getFolderName() */);
	ui_.taskNameEdit_->setText("new_task"/* DM_Settings::getSettings()->getTaskName()*/ );

	buttonGroup_.addButton( ui_.fullCopyButton , DMTool::FULL_COPY );
	buttonGroup_.addButton( ui_.partitionCopyButton , DMTool::PARTITION_COPY );
	buttonGroup_.addButton( ui_.userCopyButton , DMTool::USER_COPY );

}

CopyDetectDialog::~CopyDetectDialog()
{

}

VerifyDetectDialog::VerifyDetectDialog( QWidget *parent, DWORD DiskMaster_ID )
	: AbstractDetectDialog( parent )
	, disk_master_ ( DMTool::getDiskMaster(DiskMaster_ID) )

{
	ui_.setupUi(this);

	if ( disk_master_ )
	{
		for ( auto iCount = 0; iCount < disk_master_->source_count(); ++iCount )
		{
			auto disk_ptr = disk_master_->getSource(iCount);
			ui_.verifyCombo_->addItem( identifyIcon(disk_ptr) , displayName(disk_ptr) );
		}
		for ( auto iCount = 0; iCount < disk_master_->target_count(); ++iCount )
		{
			auto disk_ptr = disk_master_->getTarget(iCount);
			ui_.verifyCombo_->addItem( identifyIcon(disk_ptr) , displayName(disk_ptr) );
		}
	}


	ui_.workFolderEdit_->setText( "c:\\"/*DM_Settings::getSettings()->getFolderName() */);
	ui_.taskNameEdit_->setText("new_task"/* DM_Settings::getSettings()->getTaskName()*/ );

}

EraseDetectDialog::EraseDetectDialog( QWidget *parent, DWORD DiskMaster_ID )
	: AbstractDetectDialog( parent )
	, disk_master_ ( DMTool::getDiskMaster(DiskMaster_ID) )

{
	ui_.setupUi(this);

	if ( disk_master_ )
	{
		for ( auto iCount = 0; iCount < disk_master_->target_count(); ++iCount )
		{
			auto disk_ptr = disk_master_->getTarget(iCount);
			ui_.verifyCombo_->addItem( identifyIcon(disk_ptr) , displayName(disk_ptr) );
		}
	}


	ui_.workFolderEdit_->setText( "c:\\"/*DM_Settings::getSettings()->getFolderName() */);
	ui_.taskNameEdit_->setText("new_task"/* DM_Settings::getSettings()->getTaskName()*/ );

}



//void CopyDetectDialog::DetectClicked()
//{
//	if ( auto task_manager = DMTool::DMTaskManager::GetTaskManager() )
//	{
//	if ( auto disk_master = DMTool::getDiskMaster(id_))
//	{
//	auto detect_task = Factories::getInstance()->Lookup(DM_QUICK_COPY_TASK)->CreateTask(id_, this ); 
//	ConnectForDetect(detect_task , this );
//	task_manager->AddTask( id_ , detect_task );
//	
//	auto port1 = disk_master->getSource( ui_.sourceCombo_->currentIndex() )->getPort();
//	auto port2 = disk_master->getTarget( ui_.targetCombo_->currentIndex() )->getPort();
//
//	detect_task->DetectDevices(port1 , port2 , 0);
//	}
//	}
//
//}
//void CopyDetectDialog::detect_finished()
//{
//	if ( auto disk_master = DMTool::getDiskMaster(id_))
//	{
//	auto disk1 = disk_master->getSource( ui_.sourceCombo_->currentIndex() );
//	auto disk2 = disk_master->getTarget( ui_.targetCombo_->currentIndex() );
//	if ( disk1 && disk2)
//		qDebug() << "detected.";
//	}
//
//}
