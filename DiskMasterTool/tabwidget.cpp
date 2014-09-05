#include "tabwidget.h"

#include "tabwidgets.h"
#include "maintaskwidget.h"
#include "dmtreemodel.h"

#include "copytask.h"
#include "verifytask.h"
#include "erasetask.h"
#include "copydetectdialog.h"
#include "factories.h"
#include "settingsdialog.h"

 #include <QTabBar>

TabWidget::TabWidget(QWidget *parent)
	: QTabWidget(parent)
	, MainWidget_(nullptr)
{
	hideTabBar();
	connect( this , SIGNAL (currentChanged(int)), this, SLOT ( TabChanged(int) ));
	//WigetFactoryManager::getFactoryManager()->Register(DM_QUICK_COPY_TASK);
	//WigetFactoryManager::getFactoryManager()->Register(DM_QUICK_VERIFY_TASK);
	//WigetFactoryManager::getFactoryManager()->Register(DM_QUICK_ERASE_TASK);
}

TabWidget::~TabWidget()
{

}
void TabWidget::addMainTask(MainTaskWidget * mainWidget)
{
	Q_ASSERT( mainWidget != nullptr);
	connect( mainWidget,
			 SIGNAL(ShowCurrentWidget( const DMItemIdex * , int)),
			 this,
			 SLOT( ShowTabWidget( const DMItemIdex * , int) )
			);

	connect( mainWidget,
		SIGNAL ( LoadTask ( const DMItemIdex * , const QString &) ),
		this,
		SLOT ( task_load( const DMItemIdex * , const QString &) )
		);

	connect( mainWidget,
			 SIGNAL (DeviceDisappered ( const DMItemIdex *  )),
			 this,
			 SLOT ( RemoveTabs(const DMItemIdex * ) )
			 );

	this->addTab(mainWidget, QString::fromUtf16(L"Выбор задачи") );
	MainWidget_ = mainWidget;
	widgetHolder_.push_back(MainWidget_);
}
void TabWidget::addToTab(BaseTabWidget * baseTabWidget)
{
	connect(baseTabWidget, SIGNAL(progressUpdated()), MainWidget_, SLOT( UpdateTreeView() ) );
	connect(baseTabWidget, SIGNAL(removeMe( QWidget * ) ), this, SLOT( RemoveTab( QWidget * ) ) );
	connect( baseTabWidget , 
			 SIGNAL ( changeItem( DWORD , DWORD , DWORD  ) ),
			 this ,
			 SLOT ( ChangeItemStatus ( DWORD , DWORD , DWORD ) ) );
	connect( baseTabWidget , 
		SIGNAL ( change_progress( DWORD , int ) ),
		this ,
		SLOT ( ChangeProgress ( DWORD , int ) ) );

	this->addTab( baseTabWidget, baseTabWidget->getTabName() );
	this->setCurrentIndex( this->count() - 1 );
	widgetHolder_.push_back( baseTabWidget );
}
void TabWidget::ShowTabWidget(const DMItemIdex * dm_index, int itemStatus)
{
	assert(dm_index != nullptr);
	if ( BaseTabWidget * baseWidget = findWidget(dm_index,itemStatus) )
	{
		showWidget(dm_index , itemStatus);
	}
	else
	{
		if ( dm_index->getStatus() == DMTool::READY )
		{
		DWORD dm_id = dm_index->getID();
		if ( itemStatus == DMTool::COPYING )
		{
			//dm_index->setState( DMItemIdex::started );
			//dm_index->setStatus( DMItemIdex::copying );
			CopyDetectDialog detect_dialog( this , dm_id );
			if ( detect_dialog.exec() == QDialog::Accepted )
			{
				auto widgetFactory = Factories::WigetFactoryManager::getFactoryManager()->Lookup(DMTool::DM_COPY_TASK);
				if ( CopyTabWidget * copyWidget =  qobject_cast<CopyTabWidget*> ( widgetFactory->CreateTaskWidget( dm_id , this ) ) )
				{
					//copyWidget->setCopyMode( detect_dialog.get)
					auto folder_name( detect_dialog.getFolderName() );
					auto task_name( detect_dialog.getTaskName() );

					if ( auto disk_master = DMTool::getDiskMaster( dm_id ) )
					{
						auto port1 = disk_master->getSource(detect_dialog.getSourceNumber())->getPort()->number;
						auto port2 = disk_master->getTarget(detect_dialog.getTargetNumber())->getPort()->number;

						auto file_manager = DMTool::FileManager::GetFileManager();
						file_manager->CreateFileHolder( dm_id , folder_name , task_name );
						if ( auto task_file = DMTool::getFileHolder( dm_id ) )
						{
							if ( task_file->CreateTaskFile() )
							{
								auto copy_task = copyWidget->CreateTask( DMTool::DM_QUICK_COPY_TASK );
								DMTool::DMTaskManager::GetTaskManager()->AddTask( dm_id , copy_task );
								copyWidget->DetectDevices( port1 , port2 );
								addToTab( copyWidget );
								MainWidget_->changeItemState( dm_id , DMTool::STARTED , DMTool::COPYING );

							}

						}
					}

				}
			}

		}
		if ( itemStatus == DMTool::VERIFYING )	//	??????????????
		{
			VerifyDetectDialog detect_dialog( this , dm_index->getID() );
			if ( detect_dialog.exec() == QDialog::Accepted )
			{
				auto widgetFactory = Factories::WigetFactoryManager::getFactoryManager()->Lookup( DMTool::DM_VERIFY_TASK );
				if( VerifyTabWidget * verifyWidget = qobject_cast< VerifyTabWidget *> ( widgetFactory->CreateTaskWidget( dm_id , this ) ) )
				{
					auto folder_name( detect_dialog.getFolderName() );
					auto task_name( detect_dialog.getTaskName() );

					if ( auto disk_master = DMTool::getDiskMaster( dm_id ) )
					{
						const DM::PORT * port = disk_master->getDevice( detect_dialog.getDeviceIndex() )->getPort();	// ????

						auto * verify_task = verifyWidget->CreateTask( DMTool::DM_QUICK_VERIFY_TASK );
						DMTool::DMTaskManager::GetTaskManager()->AddTask( dm_id , verify_task );
						//verify_task->DetectDevices( port , port , 0 );
						verifyWidget->DetectDevices( port->number , port->number );
						addToTab( verifyWidget );
						MainWidget_->changeItemState( dm_id , DMTool::STARTED , DMTool::VERIFYING );
					}

				}
			}
		}
		if ( itemStatus == DMTool::EARASING)	//	??????????????
		{
			EraseDetectDialog detect_dialog( this , dm_index->getID() );
			if ( detect_dialog.exec() == QDialog::Accepted )
			{
				auto widgetFactory = Factories::WigetFactoryManager::getFactoryManager()->Lookup( DMTool::DM_ERASE_TASK );
				if ( EraseTabWidget * eraseWidget = qobject_cast< EraseTabWidget *> ( widgetFactory->CreateTaskWidget( dm_id , this ) ) )
				{
					if ( auto disk_master = DMTool::getDiskMaster( dm_id ) )
					{
						const DM::PORT * port = disk_master->getTarget( detect_dialog.getDeviceIndex() )->getPort();	// ????
						eraseWidget->setPattern( detect_dialog.erasePattern());
						auto * erase_task = eraseWidget->CreateTask( DMTool::DM_QUICK_ERASE_TASK );
						DMTool::DMTaskManager::GetTaskManager()->AddTask( dm_id , erase_task );
						eraseWidget->DetectDevices( port->number , port->number );
						addToTab( eraseWidget );
						MainWidget_->changeItemState( dm_id , DMTool::STARTED , DMTool::EARASING );

					}
				}
			}
		}
		}
	}
	UpdateTab();
}
void TabWidget::task_load( const DMItemIdex * dm_index, const QString & filename)
{
	assert(dm_index != nullptr);
	QFileInfo file_info( filename ) ;

	TaskFileStruct taskStruct;
	taskStruct.Initialize();
	if ( ReadTaskFile(file_info ,taskStruct) )
	{
		if ( auto * pTaskTabWidget =  Factories::WigetFactoryManager::getFactoryManager()->Lookup(taskStruct.task_id) )
		{
			auto pTabTask = pTaskTabWidget->CreateTaskWidget( dm_index->getID() , this );

			if ( auto task = pTabTask->OpenTask(filename) )
			{
				//DMTool::DMTaskManager::GetTaskManager()->AddTask(dm_index->getID(), task);
				addToTab( pTabTask );
			}
			else
				QMessageBox::critical(this , "Ошибка при открытии задачи","Не удалось открыть задачу - неверный идентификатор задачи.");
		}
	}
	else
	{
		qDebug() << "Error read task-file.";
	}
}
void TabWidget::RemoveTab( QWidget * widget )
{
	for ( int iPos = 0 ; iPos < widgetHolder_.size(); ++iPos)
	{
		if ( widgetHolder_.at(iPos) == widget )
		{
			if ( auto baseWidget = qobject_cast< BaseTabWidget * > ( widget ) )
			{
				QString errStr;
				DWORD id = baseWidget->getID();
				if ( DMTool::DMTaskManager::GetTaskManager()->ResetDiskMaster( baseWidget->getID() , errStr ) )
					this->ChangeItemStatus( id , DMTool::NOT_STARTED , DMTool::READY );
				else
				{
					QMessageBox::critical( this , "Невозможно перезапустить устройсво", errStr );
					this->ChangeItemStatus( id , DMTool::NOT_STARTED , DMTool::NOT_READY );
				}


			}
			CloseTab( widget );
			widgetHolder_.remove( iPos );
			break;
		}
	}
}
void TabWidget::RemoveTabs(const DMItemIdex * dm_index)
{
	removeWidgets(dm_index);
	UpdateTab();
}
void TabWidget::hideTabBar()
{
	QTabBar * pTabBar = this->tabBar();
	pTabBar->hide();
}
void TabWidget::appearTabBar()
{
	QTabBar * pTabBar = this->tabBar();
	pTabBar->show();
}
void TabWidget::UpdateTab()
{
	if ( this->count() > 1 )
	{
		this->appearTabBar();
		this->setTabsClosable(true);
	}
	else
	{
		this->hideTabBar();
		this->setTabsClosable(false);
	}
}
void TabWidget::RemoveTabs()
{
	auto exitIter = widgetHolder_.begin();
	while ( exitIter != widgetHolder_.end() )
	{
		if ( auto widget = qobject_cast< BaseTabWidget * > ( *exitIter) )
		{
			widget->CloseTask();
			//widget->Finalize();
			//this->RemoveTab( widget );
		}
		++exitIter;
	}

}


BaseTabWidget * TabWidget::findWidget(const DMItemIdex * dm_index , int itemStatus )
{
	auto findIter = widgetHolder_.begin();
	while ( findIter != widgetHolder_.end() )
	{
		if ( itemStatus == DMTool::COPYING)
		{
			if ( CopyTabWidget * pCopyTab = qobject_cast< CopyTabWidget * > ( *findIter ) )
				if ( pCopyTab->isEqual(dm_index->getID() , DMTool::DM_COPY_TASK ) )
					return pCopyTab;
		}
		//if ( itemStatus == DMItemIdex::verifying )
		//{
		//	if ( VerifyTabWidget * pVerifyTab = dynamic_cast< VerifyTabWidget * > ( *findIter ) )
		//		if ( pVerifyTab->isEqual(dm_index) )
		//			return pVerifyTab;
		//}
		//if ( itemStatus == DMItemIdex::erasing )
		//{
		//	if ( EraseTabWidget * pEraseTab = dynamic_cast< EraseTabWidget * > ( *findIter ) )
		//		if ( pEraseTab->isEqual(dm_index) )
		//			return pEraseTab;
		//}
		++findIter;
	}
	return nullptr;
}

void TabWidget::UpdateAllView(const DMItemIdex * dm_index)
{
	auto findIter = widgetHolder_.begin();
	while ( findIter != widgetHolder_.end() )
	{
		if ( BaseTabWidget * pBaseWidget = dynamic_cast< BaseTabWidget *> ( * findIter) )
		{
			//if ( pBaseWidget->isEqual(dm_index) )
			//	pBaseWidget->
		}
	}
}
void TabWidget::showWidget(const DMItemIdex * dm_index, int itemStatus)
{
	assert(dm_index != nullptr);
	if ( BaseTabWidget * pWidget = findWidget(dm_index , itemStatus) )
	{
		for (auto iTab = 0; iTab < this->count(); ++iTab)
		{
			if (BaseTabWidget * baseWidget = dynamic_cast<BaseTabWidget*> ( this->widget(iTab) ) )
			{

				if ( baseWidget->isEqual(dm_index->getID() , Factories::taskFromItem(itemStatus) ) )
				{
					setCurrentIndex(iTab);
					UpdateTab();
					return;
				}
			}
		}
		this->addTab( pWidget , pWidget->getTabName() );
		this->setCurrentIndex( this->count() - 1 );
		UpdateTab();
	}
}
void TabWidget::removeWidgets( const DMItemIdex * dm_index )
{
	assert(dm_index != nullptr);
	//	first Close all tabs where disk_master is present
	for (auto iTab = 0; iTab < this->count(); ++iTab)
	{
		if (BaseTabWidget * baseWidget = dynamic_cast<BaseTabWidget*> ( this->widget(iTab) ) )
			if ( baseWidget->isEqual(dm_index->getID() , Factories::taskFromItem( dm_index->getStatus() ) ) )
				this->CloseTabWidget(iTab);
	}
	// then remove all widgets
	auto removeIter = widgetHolder_.begin();
	while ( removeIter != widgetHolder_.end() )
	{
		if (BaseTabWidget * baseWidget = dynamic_cast<BaseTabWidget*> ( *removeIter ) )
		{
			if ( baseWidget->isEqual(dm_index->getID() , Factories::taskFromItem( dm_index->getStatus() )) )
				removeIter = widgetHolder_.erase(removeIter);
		}

		if (removeIter == widgetHolder_.end())
			break;
		++removeIter;
	}
}
void TabWidget::CloseTabWidget(int iTabNumber)
{
	qDebug("Close Tab #(%d) button clicked",iTabNumber);

	// remove 0 tab is impossible
	if (iTabNumber == 0)
		return;
	if (iTabNumber < this->count() )
	{
		this->removeTab(iTabNumber);
		UpdateTab();
	}
}
void TabWidget::CloseTab( QWidget * widget )
{
	for ( int iTab = 0 ; iTab < this->count() ; ++ iTab )
	{
		auto delWidget = this->widget( iTab );
		if ( delWidget == widget )
		{
			if (BaseTabWidget * baseWidget = qobject_cast<BaseTabWidget*> ( delWidget ) )
			{
				QString error_text;
				DMTool::DMTaskManager::GetTaskManager()->ResetDiskMaster( baseWidget->getID() , error_text );		//// ????????????????????
			}
			this->removeTab( iTab );
			break;
		}
	}
}

void TabWidget::TabChanged( int nIndex )
{
	if (nIndex != -1 )
	{
		if ( nIndex < widgetHolder_.size() )
		{
			if (BaseTabWidget * baseWidget = qobject_cast<BaseTabWidget*> ( widgetHolder_.at(nIndex) ) )
			{
				emit setEnabledTasks(false);
				//emit setEnabledStart( baseWidget->getEnabledStart() );
				//emit setEnabledCancel( baseWidget->getEnabledCancel() );
			}
			else
			if (MainTaskWidget * mainWidget = qobject_cast<MainTaskWidget*> ( widgetHolder_.at(nIndex) ))
			{
				emit setEnabledTasks(true);
				emit setEnabledStart( false );
				emit setEnabledCancel( false );
			}


		}
	}
}
void TabWidget::startTask() 
{
	if ( auto baseWidget = dynamic_cast< BaseTabWidget* > ( widgetHolder_.at(this->currentIndex()) ) )
	{
		baseWidget->StartTask();
	}
}
void TabWidget::cancelTask() 
{
	if ( auto baseWidget = dynamic_cast< BaseTabWidget* > ( widgetHolder_.at(this->currentIndex()) ) )
	{
		baseWidget->AbortTask();
	}
}
void TabWidget::Preferences_clicked()
{
	if ( auto mainWidget = qobject_cast< MainTaskWidget *> (this->currentWidget()) )
	{
		mainWidget->showSettings();
	}
	else
	if ( auto copyWidget = qobject_cast< CopyTabWidget *> ( this->currentWidget() ) )
	{
		copyWidget->showSettings();
	}
}
void TabWidget::tabRemoved ( int index ) 
{
	qDebug() << "tab removed.";
	
}

void TabWidget::ChangeItemStatus( DWORD id , DWORD state , DWORD status )
{
	MainWidget_->changeItemState( id , (DMTool::TASK_STATE)state , (DMTool::TASK_STATUS)status );
}
void TabWidget::ChangeProgress( DWORD id , int position )
{
	MainWidget_->changeProgress( id , position );
}
