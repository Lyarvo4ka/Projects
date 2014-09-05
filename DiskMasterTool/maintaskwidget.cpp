#include "maintaskwidget.h"

#include "dmtreemodel.h"
#include "factories.h"
#include "Functions.h"
#include "settingsdialog.h"
#include "copypropertiesui.h"

#include <algorithm>
 #include <QMessageBox>
 #include <QFileDialog>

#include "taskmanager.h"
#include "DiskMasterMock.h"



MainTaskWidget::MainTaskWidget(QWidget *parent)
	: QWidget(parent)
{
	MainTaskUi_.setupUi(this);

	setButtonEnable(false);

	connect(MainTaskUi_.CopylButton, SIGNAL(clicked()),this,SLOT( CopyButtonClicked() ));
	connect(MainTaskUi_.VerifylButton, SIGNAL(clicked()),this,SLOT(VerifyButtonClicked()));
	connect(MainTaskUi_.EraseButton, SIGNAL(clicked()),this,SLOT(EraseButtonClicked()));
	connect( MainTaskUi_.modifyMBRButton, SIGNAL( clicked( ) ), this, SLOT( ModifySector() ) );
	

	RootIndex_ = new DMItemIdex( );


	/************************************************************************/
	// It's only debug
	//DM::DiskController * pDiskMaster = new DM::DiskMaster(0,nullptr);
	//AddDiskMaster(pDiskMaster);
	//RootIndex_->Add(CreateDiskMasterItem(pDiskMaster));
	//RootIndex_->Add(CreateDiskMasterItem(nullptr));
	/************************************************************************/

	MainTaskUi_.treeView->setItemDelegateForColumn(DMTreeModel::header_progress,new DelegateProgress(this) );

	TreeModel_ = new DMTreeModel(this,RootIndex_);
	MainTaskUi_.treeView->setModel(TreeModel_);

	MainTaskUi_.treeView->resizeColumnToContents(0);
	MainTaskUi_.treeView->setColumnWidth(0,200);

	QItemSelectionModel * pSelectModel = MainTaskUi_.treeView->selectionModel();
	//connect( pSelectModel ,SIGNAL( selectionChanged (const QItemSelection& , const QItemSelection& ) ), 
	//		 this, SLOT( ElementSelected() ) );

	connect( pSelectModel ,SIGNAL( selectionChanged (const QItemSelection& , const QItemSelection& ) ), 
		this, SLOT( ElementSelected( const QItemSelection& , const QItemSelection&  ) ) );

	DetectConnected();
	//DiskMaster * pDiskMaster = new DiskMaster(0,12345,nullptr);
	//this->AddDiskMaster(pDiskMaster);
	device_holder_ = new DeviceHolder(this);
	connect( device_holder_, SIGNAL( AddDevice( DM::DiskController * ) ), this, SLOT( AddDiskMaster( DM::DiskController * ) ) , Qt::QueuedConnection );
	connect( device_holder_, SIGNAL( RemoveDevice( DM::DiskController * ) ), this, SLOT( RemoveDiskMasterItem( DM::DiskController * ) ) , Qt::QueuedConnection );
	device_holder_->start();

#ifdef _DEBUG
	this->AddDiskMaster( new DiskMasterMock( 0xAAAA ) );
#endif
	if ( RootIndex_->hasChildrend() )
	{
		auto child = TreeModel_->index(0,0);
		if ( child.isValid() )
		{
			MainTaskUi_.treeView->setCurrentIndex( child );
		}
	}
}

MainTaskWidget::~MainTaskWidget()
{
	//DM::GetDiskMasterManager()->Detach(this);
	device_holder_->exit();
	qDebug("Destructor [\'MainTaskWidget\']");
}
void MainTaskWidget::DetectConnected()
{
	if (auto count = DM::GetDiskMasterManager()->Rescan())
	{
		for (DWORD iDiskMaster = 0 ; iDiskMaster < count; ++iDiskMaster)
		{
			this->AddDiskMaster( DM::GetDiskMasterManager()->GetDiskMaster(iDiskMaster) );
		}
	}
}

//DMItemIdex * MainTaskWidget::CreateUsbSource(DiskDevicePtr & disk_device)
//{
//	DMItemIdex * usb_source = new DMItemIdex( disk_device );
//	usb_source->setName("USB_1-source");
//	QString iconPath = QString::fromUtf8(":/DiskMasterUI/icons/usb_device_green.png");
//	usb_source->setIcon( QIcon(iconPath) );
//	return usb_source;
//}
//DMItemIdex * MainTaskWidget::CreateUsbTarget( DiskDevicePtr & disk_device)
//{
//	DMItemIdex * usb_target = new DMItemIdex( disk_device );
//	usb_target->setName("USB_2-target");
//	QString iconPath = QString::fromUtf8(":/DiskMasterUI/icons/usb_device_grey.png");
//	usb_target->setIcon( QIcon(iconPath) );
//	return usb_target;
//}
//DMItemIdex * MainTaskWidget::CreateSataTarget( DiskDevicePtr & disk_device)
//{
//	DMItemIdex * sata_target = new DMItemIdex( disk_device );
//	sata_target->setName("SATA-target");
//	QString iconPath = QString::fromUtf8(":/DiskMasterUI/icons/sata_device.png");
//	sata_target->setIcon( QIcon(iconPath) );
//	return sata_target;
//}
DMItemIdex * MainTaskWidget::CreateDiskMasterItem( DiskMasterDevice * disk_master )
{
	//DiskMasterPtr2 newDiskMaster( new DiskMasterDevice( disk_master ) );
	DMItemIdex * dm_Index = new DMItemIdex( DMItemIdex::DiskMasterItem, disk_master->getID() );
	QString iconPath = QString::fromUtf8(":/DiskMasterUI/icons/disk_master.png");
	dm_Index->setIcon( QIcon(iconPath) );


	// now it's impossible

	//auto device_list = newDiskMaster->getSourceList();
	//auto diskIter = device_list.begin();
	//while ( diskIter != device_list.end() )
	//{
	//	DiskDevicePtr disk_ptr = *diskIter;
	//	if ( disk_ptr->isUSB())
	//		dm_Index->Add( CreateUsbSource( disk_ptr ) );
	//	++diskIter;
	//}

	//device_list = newDiskMaster->getTargetList();
	//diskIter = device_list.begin();
	//while ( diskIter != device_list.end() )
	//{
	//	DiskDevicePtr disk_ptr = *diskIter;
	//	if ( disk_ptr->isUSB() )
	//		dm_Index->Add( CreateUsbTarget( disk_ptr ) );
	//	else
	//	if ( disk_ptr->isSATA() )
	//		dm_Index->Add( CreateSataTarget( disk_ptr ) );

	//	++diskIter;
	//}

	return dm_Index;
}
void MainTaskWidget::ShowTask( DMTool::TASK_STATUS task_status )
{
	if (DMItemIdex * dm_index = getIndex( MainTaskUi_.treeView->currentIndex() ) )
	{
		if ( dm_index->getStatus() != DMTool::NOT_READY )
		{
			emit ShowCurrentWidget(dm_index , task_status);
		}
	}
}

void MainTaskWidget::showSettings()
{
	SettingsDialog * pSettingsDlg = new SettingsDialog( this ); 
	pSettingsDlg->exec();
	delete pSettingsDlg;
}

void MainTaskWidget::AddDiskMaster(DM::DiskController * disk_master )
{
	if ( RootIndex_->isRoot() )
	{
		auto pTaskManager = DMTool::DMTaskManager::GetTaskManager();
		if ( pTaskManager->Insert( disk_master ) )
		{
			auto disk_master_ptr = DMTool::getDiskMaster( disk_master->GetID() );
			auto dm_Index = CreateDiskMasterItem( disk_master_ptr );

			RootIndex_->Add( dm_Index );

			int iResult = 0;
			do 
			{
				if ( !RootIndex_->findIndex( dm_Index->getID() ) )
					break;

				if ( disk_master_ptr->Open() )
				{
					dm_Index->update_params();
					break;
				}
				QMessageBox msgNotReady;
				msgNotReady.setWindowTitle(QString::fromLocal8Bit("Ошибка подключения."));
				QString mainText( QString::fromLocal8Bit("<B>Не удалось подключится к DiskMasterUSB (# %1)</B>").arg( disk_master_ptr->getID() ) );
				msgNotReady.setText(mainText);
				msgNotReady.setInformativeText(QString::fromLocal8Bit("Убедитесь что устойство находится в главном меню!"));
				msgNotReady.setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
				msgNotReady.setDefaultButton(QMessageBox::Retry);
				iResult = msgNotReady.exec();
			} while (iResult != QMessageBox::Cancel);

		}
		qDebug("DiskMaster (ADD)");
	}
	TreeModel_->update_view();
}
void MainTaskWidget::RemoveDiskMasterItem( DM::DiskController * disk_master )
{
	if ( DMItemIdex * pIndex = RootIndex_->findIndex( disk_master->GetID() ) )
	{
		emit DeviceDisappered( pIndex );
		RootIndex_->Remove(pIndex);
		DMTool::DMTaskManager::GetTaskManager()->Remove( disk_master->GetID() );
		qDebug("DiskMaster (REMOVED)");
	}
	TreeModel_->update_view();
}
void MainTaskWidget::CopyButtonClicked()
{
	ShowTask( DMTool::COPYING );
}
void MainTaskWidget::VerifyButtonClicked()
{
	ShowTask( DMTool::VERIFYING );
}
void MainTaskWidget::EraseButtonClicked()
{
	ShowTask( DMTool::EARASING );
}

void MainTaskWidget::ModifySector()
{

	DMItemIdex * dm_index = getIndex(MainTaskUi_.treeView->currentIndex());
	{
		if ( dm_index->getStatus() == DMTool::READY )
		{
			SectorModifyDialog modify_sector( this , dm_index->getID() );

			modify_sector.exec();
		}
	}	
//	if ( auto disk_master = DMTool::getDiskMaster( dm_index->getID() ) )
//	{
//
//		if ( auto device = disk_master->getTarget(0) )
//		{
//			if ( !device->isDetected() )
//			{
//				disk_master->Rescan(device);
//			}
////			if ( device->Open() )
//			{
//
//				BYTE read_buffer[512];
//				memset( read_buffer, 0xFF , 512);
//				ULONGLONG offset = 0;
//				DWORD read =  disk_master->ReadBlock( device->getPort()->number , offset , read_buffer , device->getBlockSize() ) ;
//
//				BYTE write_buffer[512];
//				memset( write_buffer, 0xbb , 512);
//				offset = 0;
//				DWORD write =  disk_master->WriteBlock(device->getPort()->number , offset , write_buffer , device->getBlockSize()  ) ;
//
//				int k = 1;
//			}
//		}
//
//	}
}

void MainTaskWidget::ElementClicked(QModelIndex clicked_index)
{
	changeEnable(clicked_index);
}
void MainTaskWidget::setButtonEnable(const bool enable)
{
	MainTaskUi_.CopylButton->setEnabled(enable);
	MainTaskUi_.VerifylButton->setEnabled(enable);
	MainTaskUi_.EraseButton->setEnabled(enable);
}
void MainTaskWidget::Double_Clicked(QModelIndex clicked_index)
{
	//if ( DMItemIdex * index = getIndex(clicked_index) )
	//	if ( DiskMasterPtr2 disk_master = getDiskMaster(index ) )
	//	{
	//		auto itemStatus = index->getStatus();
	//		if ( (itemStatus != DMItemIdex::ready) && (itemStatus != DMItemIdex::not_ready) )
	//			emit ShowCurrentWidget(index, index->getStatus() );
	//	}
}
void MainTaskWidget::changeEnable(QModelIndex model_index)
{
	DMItemIdex * pDeviceIndex = static_cast< DMItemIdex * > (model_index.internalPointer());

	if (pDeviceIndex)
	{
		emit ItemSelected( pDeviceIndex );
		if (pDeviceIndex->isDiskMaster() && ( pDeviceIndex->getStatus() != DMTool::NOT_READY ))
		{
			setButtonEnable();
		}
		else
			setButtonEnable(false);
	}
}
void MainTaskWidget::UpdateTreeView()
{
	if (TreeModel_)
	{
		TreeModel_->update_view();
	}
}
void MainTaskWidget::ElementSelected(const QItemSelection& selected, const QItemSelection& deselected)
{
	QModelIndex selected_index = selected.indexes().first();
	if (selected_index.isValid())
		changeEnable(selected_index);

	/*qDebug("MainTaskWidget::ElementSelected(const QItemSelection& selected, const QItemSelection& deselected)");*/
}

void MainTaskWidget::LoadTask_ckicked()
{
	if (DMItemIdex * dm_index = getIndex(MainTaskUi_.treeView->currentIndex()) )
	{
		if ( dm_index->getStatus() != DMTool::NOT_READY )
		{
			QString fileName = QFileDialog::getOpenFileName(this, tr("Загрузить задачу"),
				"c:\\",
				tr("tasks (*.tsk)"));
			if ( !fileName.isEmpty() )
				emit LoadTask( dm_index , fileName );
		}
	}
}
