#include "copytask.h"

#include "dmtreemodel.h"
#include "State.h"


/************************************************************************/
/*                        QuickCopyTask                                 */
/************************************************************************/

QuickCopyTask::QuickCopyTask( QObject * parent /*= 0 */ ) 
	: AbstractTask(parent)
	, id_ ( -1 )
	, disk_master_( nullptr )
	, source_port_( nullptr )
	, target_port_( nullptr )
	, source_offset_( 0 )
	, target_offset_( 0 )
	, sectors_count_( 0 )
	, currentSector_(0)
	, sectorModel_( nullptr )
	, copyBlockSize_( 0 )
	, jumpSize_( DefualtJumpSize )
	, task_break_( false )
	, task_error_( false )
	, unknown_bad_( false )
	, direction_ ( ForwardTask )
	, bExecuting_ ( false )
{

}

QuickCopyTask::QuickCopyTask( const DWORD id, QObject * parent /*= 0 */ ) : AbstractTask(parent)
	, id_ ( id )
	, disk_master_( DMTool::getDiskMaster(id) )
	, source_port_( nullptr )
	, target_port_( nullptr )
	, source_offset_( 0 )
	, target_offset_( 0 )
	, sectors_count_( 0 )
	, currentSector_( 0 )
	, sectorModel_( nullptr )
	, copyBlockSize_( 0 )
	, jumpSize_( DefualtJumpSize )
	, task_break_( false )
	, task_error_( false )
	, unknown_bad_( false )
	, direction_ ( ForwardTask )
	, bExecuting_ ( false )
{
	if ( auto disk_master = DMTool::getDiskMaster(id_))
		disk_master->getNotifier()->Attach(this);
}

QuickCopyTask::~QuickCopyTask()
{
	Finalize();
	qDebug() << "dtor QuickCopyTask";
}

void QuickCopyTask::Initialize( const DWORD id )
{
	id_ = id;
	disk_master_ = DMTool::getDiskMaster(id_);
	if ( disk_master_)
		disk_master_->getNotifier()->Attach(this);

	source_port_ = nullptr;
	target_port_ = nullptr;
	source_offset_ = 0;
	target_offset_ = 0;
	sectors_count_ = 0;
	sectorModel_ = nullptr;
	copyBlockSize_ = 0;
	jumpSize_ = DefualtJumpSize ;
	task_break_ = false ;
	task_error_ = false;
	unknown_bad_ = false ;
	direction_ = ForwardTask ;
	bExecuting_ = false;
}

void QuickCopyTask::Finalize()
{
	if ( disk_master_ )
		disk_master_->getNotifier()->Detach(this);
	id_ = -1;
	disk_master_ = nullptr;
	source_port_ = nullptr;
	target_port_ = nullptr;
	sectorModel_ = nullptr;
	source_offset_ = 0;
	target_offset_ = 0;
	sectors_count_ = 0;
	copyBlockSize_ = 0;
	jumpSize_ = 0 ;
	task_break_ = false ;
	task_error_ = false;
	unknown_bad_ = false;
	direction_ = ForwardTask ;
	bExecuting_ = false;
}

void QuickCopyTask::run()
{
	// only detection.
	if ( sectors_count_ == 0)
	{
		Detect(source_port_ , target_port_ );
	}
	else
	{
//		if ( DM_Settings::getSettings()->getCopySettings( id_ ).direction_ == ForwardTask)
			CopyBlock(source_port_ , target_port_ , source_offset_ , target_offset_ , sectors_count_ );
		//else
		//	CopyBlockBack(source_port_ , target_port_ , source_offset_ , target_offset_ , sectors_count_ );
	}
}

void QuickCopyTask::Detect( const DM::PORT * source_port, const DM::PORT * target_port )
{
	assert( disk_master_ != nullptr );
	disk_master_->CopyEx(source_port_->number , target_port_->number , 0 , 0 , 0);
	emit finish_detect();
}

void QuickCopyTask::CopyBlock( const DM::PORT * source_port, const DM::PORT * target_port , qlonglong source_offset , qlonglong target_offset , qlonglong sector_count )
{
	assert( disk_master_ != nullptr );

	qlonglong max_blocks = MaxSectorsCount;
	copyBlockSize_ = max_blocks;
	if ( sector_count < copyBlockSize_ )
	{
		if ( sector_count > MinSectorsCount )
		{
			max_blocks = sector_count / MinSectorsCount; 
			if ( max_blocks > sector_count )
				copyBlockSize_ = max_blocks;
			else
				copyBlockSize_ = sector_count;
		}
		else
			copyBlockSize_ = sector_count;
	}
	qlonglong distOffset = (qlonglong) ( SourceOffset() - TargetOffset() );

	qlonglong copied_sectors = 0;
	currentSector_ = SourceOffset();

	qlonglong prev_sector = currentSector_;

	while ( copied_sectors < sectors_count_ )
	{
		if ( task_break_ )
			break;

		if ( ( copied_sectors + copyBlockSize_ ) > sectors_count_ )
			copyBlockSize_ = sectors_count_ - copied_sectors;

		qDebug() << "Forward \'Quick Copy\' is starting..." << currentSector_;
		prev_sector = currentSector_;
		bExecuting_ = true;
		try 
		{
			//throw DM::DMException();
		if ( disk_master_->CopyEx( source_port->number , target_port->number , currentSector_ , currentSector_ - distOffset , copyBlockSize_ ) )
		{
			copied_sectors += copyBlockSize_;

			if ( copyBlockSize_ < max_blocks )
				copyBlockSize_ *= 2;
		}
		else
		{
			if ( task_error_)
			{
				qDebug() << "Task error";
				task_error_ = false;
					disk_master_->Close();
					::Sleep(2000);
					if ( ! disk_master_->Open() )
					{
						qDebug() << disk_master_->getID();
						throw;
					}
			}
			JumpSectors(currentSector_,prev_sector,jumpSize_);
			copied_sectors += (currentSector_ - prev_sector);
			copyBlockSize_ = MinSectorsCount;
		}
		}
		catch ( DM::DMException e)
		{
			qDebug() << "Disk master doesn't respond";
			this->BreakTask() ;
			emit error_task( errDiskMasterNotRespond );
			return;
		}
		catch( ... )
		{
			qDebug() << "unhanded exception";
		}

		bExecuting_ = false;
		qDebug() << "Forward \'Quick Copy\' has finished." << currentSector_;
		emit update_lba(currentSector_);
	}
	if ( task_break_ )
		emit break_task( currentSector_ );
	else
		emit finish_task( currentSector_ );
}
void QuickCopyTask::CopyBlockBack( const DM::PORT * source_port, const DM::PORT * target_port , qlonglong source_offset , qlonglong target_offset , qlonglong sector_count )
{
	assert( disk_master_ != nullptr );

	qlonglong max_blocks = MaxSectorsCount;
	copyBlockSize_ = max_blocks;

	copyBlockSize_ = max_blocks;
	if ( sector_count < copyBlockSize_ )
	{
		if ( sector_count > MinSectorsCount )
		{
			max_blocks = sector_count / MinSectorsCount; 
			if ( max_blocks > sector_count )
				copyBlockSize_ = max_blocks;
			else
				copyBlockSize_ = sector_count;
		}
		else
			copyBlockSize_ = sector_count;
	}

	qlonglong distOffset = SourceOffset() - TargetOffset();

	qlonglong copied_sectors = 0;
	currentSector_ = getLastSector();

	qlonglong prev_sector = currentSector_;
	ChangeSector(currentSector_, prev_sector , copyBlockSize_ );

	while ( currentSector_ >= source_offset )
	{
		if ( task_break_ )
			break;

		//if ( ( copied_sectors + copyBlockSize_ ) > sectors_count_ )
		//	copyBlockSize_ = sectors_count_ - copied_sectors;

		qDebug() << "Backward \'Quick Copy\' is starting..." << currentSector_;
		prev_sector = currentSector_;
		try
		{
		//	throw DM::DMException();
		if ( disk_master_->CopyEx( source_port->number , target_port->number , currentSector_ , currentSector_ - distOffset , copyBlockSize_ ) )
		{
			copied_sectors += copyBlockSize_;

			ChangeSector( currentSector_, prev_sector , copyBlockSize_ );

			if ( copyBlockSize_ < MaxSectorsCount )
				copyBlockSize_ *= 2;
		}
		else
		{
			if ( task_error_)
			{
				task_error_ = false;
				disk_master_->Close();
				::Sleep(2000);
				if ( ! disk_master_->Open() )
				{
					qDebug() << disk_master_->getID();
					throw;
				}
			}
			JumpSectors(currentSector_,prev_sector,jumpSize_);
			copied_sectors += (currentSector_ - prev_sector);
			copyBlockSize_ = MinSectorsCount;
		}
		}
		catch ( DM::DMException e)
		{
			qDebug() << "Disk master doesn't respond.";
		}
		catch ( ... )
		{
			qDebug() << "Unhanded exception.";
		}
		qDebug() << "Backward \'Quick Copy\' has finished." << currentSector_;
		if ( currentSector_ < 0 )
		{
			currentSector_ = 0;
			break;
		}
		emit update_lba(currentSector_);
	}
	if ( task_break_)
		emit break_task( currentSector_ );
	else
		emit finish_task( currentSector_ );
}


void QuickCopyTask::NewDiskDetected( void *param )
{
	if (DM::Disk * new_disk = static_cast<DM::Disk *> (param) )
	{
		if ( auto disk_master = DMTool::getDiskMaster( id_ ) )
		{
			if ( auto disk_device = disk_master->getDiskDevice( new_disk->Port() ) )
			{
				qDebug() << "Device detected " << disk_device->getPort()->name;
				disk_device->setDisk(new_disk);
				emit new_device(new_disk->Port());
			}
		}
	}
}

void QuickCopyTask::TaskInProgress( void *param )
{
	if ( DM::DM_TASK_INFO * task_info = static_cast< DM::DM_TASK_INFO * > (param) )
	{

	}
}

void QuickCopyTask::BadSector( void *param )
{
	if ( auto * pBadSector = static_cast<ULONGLONG*> (param) )
	{
		qDebug() << "Bad sector " << *pBadSector;
		//::Sleep(100);
		//this->BreakTask();
		qint32 update_size = (qint32) (* pBadSector - currentSector_);

		if ( sectorModel_ )
		if ( sectorModel_->isLoaded() )
		{
			if (update_size > 0 )
				sectorModel_->updateBlock(currentSector_ , update_size , SECTOR_STATUS::READ_GOOD);

			if ( copyBlockSize_ > 1 )
			{
				sectorModel_->updateBlock( *pBadSector , DM_BLOCK_SIZE , SECTOR_STATUS::UNKNOWN_BAD);
				currentSector_ = (qlonglong) (*pBadSector + DM_BLOCK_SIZE);
				unknown_bad_ = true;
			}
		}

		//if ( sectorModel_ )
		//if ( sectorModel_->isLoaded() )
		//{
		//	if (update_size > 0 )
		//		sectorModel_->updateBlock(currentSector_ , update_size , SECTOR_STATUS::READ_GOOD);

		//	sectorModel_->updateSector( * pBadSector , SECTOR_STATUS::READ_BAD );
		//}
		//currentSector_ = * pBadSector;
		//++currentSector_;
		//emit bad_sector( *pBadSector );
	}
}

void QuickCopyTask::TaskComplete( void * param )
{
	if ( DM::DM_TASK_INFO * task_info = static_cast< DM::DM_TASK_INFO * > (param) )
	{
		qDebug() << "Task complete";
		Update_Sectors(task_info);
		//emit update_lba(currentSector_);
	}
}

void QuickCopyTask::TaskBreak( void * param )
{
	if ( DM::DM_TASK_INFO * task_info = static_cast< DM::DM_TASK_INFO * > (param) )
	{
		qDebug() << "Task break " << SectorFromTaskInfo( task_info );
		if ( unknown_bad_  )
		{
			unknown_bad_ = false;
		}
		else
		{
			this->Update_Sectors(task_info);
			currentSector_ = SectorFromTaskInfo( task_info );
		}
	}
}

void QuickCopyTask::TaskError( void * param )
{
	if ( DM::DM_TASK_INFO * task_info = static_cast< DM::DM_TASK_INFO * > (param) )
	{
		qDebug() << "TaskError." << currentSector_;
		auto end_code = task_info->end_code;
		task_error_ = true;
	}
}

void QuickCopyTask::DetectError( void *param )
{
	if (WORD detectErrorNumber = (WORD) param )
	{
		DWORD port_number = portFromNotDetected( detectErrorNumber );
		emit not_detected( target_port_ , detectErrorNumber );
		qDebug() << "detect error. Port #" << port_number;
	}
}

void QuickCopyTask::DiskRemoved( void *param )
{
	if (DM::Disk * remove_disk = static_cast<DM::Disk *> (param) )
		if ( auto disk_device = disk_master_->getDiskDevice( remove_disk->Port() ) )
		{
			qDebug() << "Disk Removed..." << disk_device->getPort()->name;
			disk_device->setDisk(nullptr);
		}
}

void QuickCopyTask::Update(DCNotifier *notifier, DWORD event_code, void *param)
{
	switch (event_code)
	{
	case DM::DM_Event::kNewDiskDetected:
		NewDiskDetected( param );
		break;

	case DM::DM_Event::kTaskInProgress:
		TaskInProgress( param );
		break;

	case DM::DM_Event::kBadBlock:
		BadSector( param );
		break;

	case DM::DM_Event::kTaskComplete:
		TaskComplete( param );
		break;

	case DM::DM_Event::kTaskBreak:
		TaskBreak( param );
		break;

	case DM::DM_Event::kTaskError:
		TaskError( param );
		break;

	case DM::DM_Event::kDetectError:
		DetectError( param );
		break;

	case DM::DM_Event::kDiskRemoved:
		DiskRemoved( param );
		break;
	}
}


void QuickCopyTask::StartTask( const DM::PORT * source_port, const DM::PORT * target_port , DWORD param )
{

}

void QuickCopyTask::StartTaskEx( const DM::PORT * source_port, const DM::PORT * target_port, const DataRange block_range , DWORD param )
{
	source_offset_ = block_range.SourceOffset_;
	target_offset_ = block_range.TargetOffset_;
	sectors_count_ = block_range.SectorsCount_;

	//currentSector_ = 0;

	source_port_ = ( DM::PORT * ) source_port;
	target_port_ = ( DM::PORT * ) target_port;

	task_break_ = false;
	task_error_ = false;
	this->start();
}


/************************************************************************/
/*                          SmartCopyTask                               */
/************************************************************************/
void SmartCopyTask::run()
{
	if ( this->getSectorCount() == 0)
		QuickCopyTask::run();
	else
	{

	assert ( getSectorModel() != nullptr );

	if ( auto disk_master = DMTool::getDiskMaster(this->getID() ) )
	{
		setCurrentSector(SourceOffset());
		qlonglong write_sector = getCurrentSector();
		qlonglong disOffset = SourceOffset() - TargetOffset();
		qint32 sectors = 0;
		while ( write_sector < this->getLastSector() )
		{
			if ( isTaskBreak() )
				break;
			if ( getSectorModel()->getUnReadSectors(write_sector , sectors) )
			{
				if ( write_sector >= this->getLastSector() )
					break;
				if ( ( sectors + write_sector ) > this->getLastSector() )
					sectors = this->getLastSector() - write_sector;
				setCurrentSector(write_sector);
				
				if (  disk_master->CopyEx( SourcePort()->number , TargetPort()->number , write_sector , write_sector - disOffset, sectors ) )
				{
					write_sector += sectors;
				}
				else
				{
					write_sector = getCurrentSector();
				}

			}
			else
			{
				write_sector += DefaultReadSectors;
			}
		}
		if ( isTaskBreak() )
			emit break_task( getCurrentSector() );
		else
			emit finish_task( this->getLastSector() );
	}
	}
}

#include "optionsmanager.h"
/************************************************************************/
/*							 CopyTabWidget								*/
/************************************************************************/
CopyTabWidget::CopyTabWidget(DWORD id , QWidget *parent )
	: BaseTabWidget(parent)
	, sectorModel_( new SectorModel )
	, msgBox_( nullptr )
	, elapsedTime_( QTime( 0 , 0 , 0, 0) )
	, timeDuration_( QTime( 0, 0 ) )
	, bTaskError_( false )

{
	ui_.setupUi(this);
	setID( id );
	Initialize(id);
	msgBox_ = new QMessageBox( this );
	connect( msgBox_ , SIGNAL ( finished( int ) ) , this , SLOT( cancelDetection( int ) ) );
	this->getStateManager()->ChangeState( NewTaskState::getState() );

	ui_.sectorViewWidget->getView()->setModel(sectorModel_);
	ChangeBackgroundColor( ui_.redSquare , Qt::red);
	ChangeBackgroundColor( ui_.greenSquare , Qt::green);
	ChangeBackgroundColor( ui_.graySquare , Qt::gray );
	onTimeTimer();

	connect( &timeTimer_ , SIGNAL ( timeout() ) , this , SLOT( onTimeTimer() ) );

	PartitionEntry * root_entry = new PartitionEntry( 0 , 0 , 0 );
	PartitionItemIndex * pRootIndex = new PartitionItemIndex( root_entry );
	partitionModel_ = new PartitionTreeModel( this , pRootIndex ) ;

	preferences_ = new CopyProperiesUiDialog( this , this->getID() , partitionModel_ );
	preferences_->Initialize( this->getSourceDevice() , this->getTargetDevice() ) ;
	


	DeviceOptions_ =  new DevicePresenter( preferences_->getDeviceWidget() , this );
}
CopyTabWidget::~CopyTabWidget()
{
	Finalize();
	qDebug("Destructor [\'CopyTaskWidget\']");

	//???????????????????
	if ( preferences_ ) 
	{
		delete preferences_;
		preferences_ = nullptr;
	}
}
void CopyTabWidget::Initialize( DWORD id ) /* */
{
	setID( id );
	if ( auto disk_master = DMTool::getDiskMaster( getID() ) )
	{
		ui_.sourceWidget->setWidgetName( QString::fromLocal8Bit("Source device:") );
		connect( ui_.sourceWidget, SIGNAL ( deviceIndexChanged(int) ), this, SLOT (source_changed(int) ) );

		ui_.targetWidget->setWidgetName( QString::fromLocal8Bit("Target device:") );
		connect( ui_.targetWidget , SIGNAL ( deviceIndexChanged(int) ), this, SLOT (target_changed(int) ) );

		add_sources();
		add_targets();

		connect( ui_.sourceWidget , SIGNAL ( deviceDetect() ) , this , SLOT( StartDetectDevice() ) );
		connect( ui_.targetWidget , SIGNAL ( deviceDetect() ) , this , SLOT( StartDetectDevice() ) );
		//task_log = new TaskLog(ui_.taskInfoWidget->getLogPath());
		//ui_.taskInfoWidget->setDiskMasterInfo( id_ );

		ZeroMemory( & TaskStruct_ , sizeof( TaskFileStruct ) );
		TaskStruct_.task_id = DMTool::DM_QUICK_COPY_TASK;
		TaskStruct_.current_sector = 0;
		TaskStruct_.setSource(this->getSourceDevice());
		TaskStruct_.setTarget(this->getTargetDevice());

		//preferences_->Initialize( this->getSourceDevice() , this->getTargetDevice() );
		bTaskError_ = false;
	}
}
void CopyTabWidget::Finalize()
{
	if ( sectorModel_ )
	{
		delete sectorModel_;
		sectorModel_ = nullptr;
	}

	bTaskError_ = false; 
	DMTool::FileManager::GetFileManager()->RemoveFileHolder(getID());

}

AbstractTask * CopyTabWidget::CreateTask( DWORD task_id )
{
	return Factories::FactoryManager::getInstance()->Lookup( task_id )->CreateTask(getID() , this) ;
}

AbstractTask * CopyTabWidget::OpenTask( const QString & fileName )
{
	TaskStruct_.Initialize();
	QFileInfo file_info( fileName );
	DMTool::FileManager::GetFileManager()->CreateFileHolder(getID() , file_info.dir().absolutePath() , file_info.baseName() );
	auto fileHolder = DMTool::getFileHolder(getID());
	if (  fileHolder->OpenTaskFile() )
	{
		fileHolder->ReadTaskData( &TaskStruct_ );
		if ( TaskStruct_.task_id == DMTool::DM_QUICK_COPY_TASK || TaskStruct_.task_id == DMTool::DM_SMART_COPY_TASK)
		{
			//qlonglong source_offset = 4931349;
			//qlonglong target_offset = 4931349;
			//qlonglong sector_count = 1948526827;

			//TaskStruct_.min_lba = 4931349;
			//TaskStruct_.max_lba = 1953458176;
			//TaskStruct_.current_sector = 4931349;
		DMTool::DMTaskManager::GetTaskManager()->AddTask(getID(), CreateTask(TaskStruct_.task_id));
		QString sectorMapPath( FileSystem::CreateFilePath(fileHolder->getFolderName() , fileHolder->getTaskName() , ".map"));
		sectorModel_->loadMap(sectorMapPath);
		DetectDevices(TaskStruct_.source_port , TaskStruct_.target_port);
		this->getStateManager()->ChangeState(RunningState::getState());


		return DMTool::DMTaskManager::GetTaskManager()->GetTask(getID());
		}
	}
	return nullptr;
}
void CopyTabWidget::CloseTask( ) 
{
	this->getStateManager()->ChangeState( ExitState::getState() );
	this->getStateManager()->getState()->PerfomState( this );
	DMTool::WaitingForTaskEnd( getID() );
	DMTool::DMTaskManager::GetTaskManager()->RemoveTask( getID() );
	this->Finalize();
}
bool CopyTabWidget::isEqual( DWORD id , DMTool::DM_TASK task_id)
{
	return ( ( id == getID() ) && ( task_id == DMTool::DM_COPY_TASK ) );
}
QString CopyTabWidget::getTabName() const
{
	return CopyTaskText;
}
void CopyTabWidget::setProgress( int position)
{
	ui_.progressBar->setValue(position);
	emit change_progress( this->getID() , position );
}
DiskDevicePtr CopyTabWidget::getSourceDevice() const
{
	if ( auto disk_master = DMTool::getDiskMaster( getID() ) )
	{
		return disk_master->getSource( ui_.sourceWidget->getCurrentIndex() );
	}
	return DiskDevicePtr(nullptr);
}
DiskDevicePtr CopyTabWidget::getTargetDevice() const
{
	if ( auto disk_master = DMTool::getDiskMaster( getID() ) )
	{
		auto nIndex = ui_.targetWidget->getCurrentIndex();
		return disk_master->getTarget( nIndex );
	}	
	return DiskDevicePtr(nullptr);
}
bool CopyTabWidget::isSourceDetected() const
{
	return ( getSourceDevice() ) ? getSourceDevice()->isDetected() : false;
}
bool CopyTabWidget::isTargetDetected() const
{
	return ( getTargetDevice()) ? getTargetDevice()->isDetected() : false;
}
void CopyTabWidget::setEnableAllView(bool bEnable )
{
	ui_.sourceWidget->setEnabled(bEnable);
	ui_.targetWidget->setEnabled(bEnable);
	//ui_.startButton->setEnabled(bEnable);
}

void CopyTabWidget::showSettings()
{
	preferences_->Initialize( getSourceDevice() , getTargetDevice() );
	preferences_->exec();
	TaskStruct_.copy_mode = preferences_->getCopyMode();
	PartitionItemIndex * pRootIndex = partitionModel_->getRootIndex();
	switch ( TaskStruct_.copy_mode )
	{
	case DMTool::PARTITION_COPY:
		
		//for ( int nIndex = 0 ; nIndex < pRootIndex->count() ; ++nIndex )
		//{
		//	//TaskStruct_.partitionArray_[ nIndex ].bChecked = pRootIndex->getChild(nIndex)->getChecked();
		//}
	break;
	case DMTool::USER_COPY:
		auto range_widget = preferences_->getRangeWidget();
		TaskStruct_.source_offset = range_widget->getRange()->getSourceOffset();
		TaskStruct_.target_offset = range_widget->getRange()->getTargetOffset();
		TaskStruct_.sectors_count = range_widget->getRange()->getSectorCount();
		break;
	}

	int k = 1;
	k = 2;
	ShowTaskInfo( TaskStruct_.copy_mode );
}

void CopyTabWidget::source_changed(int current_index)
{
	if ( auto disk_master = DMTool::getDiskMaster( getID() ) )
	{
		if ( auto source_device_ = disk_master->getSource(current_index) )
		{
			ui_.sourceWidget->change_data(current_index , displayName( source_device_ ) , identifyIcon( source_device_ ) );
			TaskStruct_.setSource(source_device_);
		}
	}
}

void CopyTabWidget::target_changed(int current_index)
{
	if ( auto disk_master = DMTool::getDiskMaster( getID() ) )
	{
		if ( auto target_device_ = disk_master->getTarget(current_index) )
		{
			ui_.targetWidget->change_data(current_index , displayName( target_device_ ) , identifyIcon( target_device_ ));
			TaskStruct_.setTarget(target_device_);
		}	
	}
}

void CopyTabWidget::current_lba(const qlonglong currectSector)
{
	if ( auto copy_task = DMTool::DMTaskManager::GetTaskManager()->GetTask( getID() ) )
	{
		int elapsed = timeDuration_.elapsed();

		SectorModel * pSectorModel = qobject_cast< SectorModel * > ( sectorModel_ );

		if ( elapsed > 0)
		{
			timeDuration_.restart();

			qlonglong bytes = ( currectSector - TaskStruct_.current_sector) * SECTOR_SIZE;
			bytes /= 1024;
			//bytes /= 1024;
			bytes *= 60;
			elapsed *= 60;
			double duration = (double) elapsed / (double)1000;
			if ( duration > 0.0 )
			{
				double speed = ( double) bytes / duration;
				ui_.speedText->setText( QString::number(speed) + " Kb/min.");
				if ( speed > 0 )
				{
					qlonglong speed_bytes = (qlonglong) speed;
					speed_bytes *= 1024;
					if ( speed_bytes > 0)
					{
						int remaningTime = (int)( qlonglong(pSectorModel->getUnreadCount()*SECTOR_SIZE) / speed_bytes);
						QTime time(0,0,0,0);
						time = time.addSecs( remaningTime );
						ui_.remainingText->setText( time.toString( ) );
					}

				}
			}
		}


		TaskStruct_.current_sector = currectSector;
		TaskStruct_.current_task.CurrentSector = (qlonglong) ( TaskStruct_.current_sector - TaskStruct_.current_task.SrcOffset );

		auto total_sectors = TaskStruct_.sectors_count + TaskStruct_.source_offset;
		if ( total_sectors > 0 )
		{
		int progressValue = (int) (TaskStruct_.current_sector * 100) / ( total_sectors ) ;

		if ( progressValue >= 0 && progressValue <= 100)
		{
			setProgress(progressValue);
		}
		QString currSectorStr(QString::number(TaskStruct_.current_sector) + "/" + QString::number( total_sectors ));
		ui_.currentSector->setText(currSectorStr);
		if ( auto task_file = DMTool::getFileHolder( getID() ) )
			task_file->WriteCurrentSector(&TaskStruct_);

		ui_.badSectorsText->setText( QString::number( pSectorModel->getBadsCount() ) );
		ui_.readSectorsText->setText( QString::number( pSectorModel->getReadCount() ) );
		ui_.unreadText->setText( QString::number( pSectorModel->getUnreadCount() ) );
		}

	}
}
void CopyTabWidget::task_finished( const qlonglong lastSector)
{
	current_lba(lastSector);
	setProgress(100);
	//if ( DM_Settings::getSettings()->getCopySettings(id_).direction_ == ForwardTask )
	//	TaskStruct_.min_lba = lastSector;
	//else
	//	TaskStruct_.max_lba = 
	changeTaskRange();

}
void CopyTabWidget::thread_finished()
{
	if ( bTaskError_ )
	{
		QString text( QString::fromLocal8Bit("An error has occurred, the application will be closed.") );
		this->ShowTaskText( text );

		this->AbortAndClose( );
		return;
	}
	this->stopTimer();
	auto state_manager = this->getStateManager();
	switch ( state_manager->getState()->getTaskState( ) )
	{
	case PausedTask:
		if ( auto smart_task = qobject_cast< SmartCopyTask * > ( DMTool::DMTaskManager::GetTaskManager()->GetTask( getID() ) ) )
		{
			if ( TaskStruct_.min_lba < TaskStruct_.max_lba )
			{
				auto new_state = RunningState::getState();
				state_manager->ChangeState(new_state);
				if ( new_state->PerfomState( this ) )
					state_manager->ChangeState( PauseState::getState() );
				state_manager->getState()->UpdateButton( this );
			}
			else
				TaskHasFinished();
		}
		else
		if ( auto quick_task = qobject_cast< QuickCopyTask * > ( DMTool::DMTaskManager::GetTaskManager()->GetTask( getID() ) ) )
		{
			if ( TaskStruct_.copy_mode == DMTool::PARTITION_COPY )
			{
				
			}

			//auto settings = DM_Settings::getSettings()->getCopySettings(getID());
			//if ( settings.direction_ == ForwardTask )
			//	TaskStruct_.min_lba = TaskStruct_.current_sector;
			//else
			//	TaskStruct_.max_lba = TaskStruct_.current_sector;

			//if ( !settings.isRead_unread )
			//{
			//	auto new_state = RunningState::getState();
			//	state_manager->ChangeState( new_state );
			//	new_state->UpdateButton(this);
			//}
			//else
			//{
			//	//if ( TaskStruct_.min_lba >= TaskStruct_.max_lba )
			//	{
			//		TaskStruct_.min_lba = TaskStruct_.source_offset;
			//		TaskStruct_.max_lba = TaskStruct_.sectors_count;
			//		ExecuteCopyTask( this , DMTool::DM_SMART_COPY_TASK, TaskStruct_.source_offset  , TaskStruct_.target_offset, TaskStruct_.sectors_count );
			//	}
			//}
		}
		break;
	case ExitTask:
		//msgBox_->hide();
		//RemoveTask();
		//this->close();
		break;
	};

	qDebug() << "Thread finished";
}

void CopyTabWidget::task_breaked(const qlonglong last_lba)
{
	TaskStruct_.current_sector = last_lba;
	//if ( TaskStruct_.sectors_count != TaskStruct_.current_task.getSectors() )
	//	TaskStruct_.current_sector = TaskStruct_.current_task.getSectors();

	changeTaskRange();
	current_lba(TaskStruct_.current_sector);

}
void CopyTabWidget::task_error( int error_code)
{
	if ( error_code == errDiskMasterNotRespond )
		bTaskError_ = true;
	else
	{
		QString outputText( QString::fromLocal8Bit("Task error : " ) + getErrorFromNumber(error_code) );
		ShowTaskText(outputText);
	}
}
void CopyTabWidget::add_sources( )
{
	if ( auto disk_master = DMTool::getDiskMaster( getID() ) )
	for ( int iCount = 0; iCount < disk_master->source_count(); ++ iCount)
	{
		auto device = disk_master->getSource( iCount );
		ui_.sourceWidget->add_data( displayName( device ) , identifyIcon( device ) ) ;
		//ui_.sourceWidget->ChangeDevice( iCount );
	}
}
void CopyTabWidget::add_targets( )
{
	if ( auto disk_master = DMTool::getDiskMaster( getID() ) )
	for ( int iCount = 0; iCount < disk_master->target_count(); ++ iCount)
	{
		auto device = disk_master->getTarget( iCount );
		ui_.targetWidget->add_data( displayName( device ) , identifyIcon( device ) ) ;
	}
}
bool CopyTabWidget::isSource( const DM::PORT * port )
{
	return compareDevicePort(this->getSourceDevice(), *port);
}
bool CopyTabWidget::isTarget( const DM::PORT * port )
{
	return compareDevicePort(this->getTargetDevice(), *port);
}
void CopyTabWidget::RemoveTask()
{
	DMTool::DMTaskManager::GetTaskManager()->RemoveTask( getID() );
}
void CopyTabWidget::ShowTaskText( const QString & outputText )
{
	AppendLogText(outputText);
	QMessageBox msgBox;
	msgBox.setText(outputText);
	msgBox.exec();

	//ui_.sourceWidget->set_device(getSourceDevice());
	//auto diskM
	//change_data(current_index , displayName( target_device_ ) , identifyIcon( target_device_ )
	//ui_.targetWidget->set_device(getTargetDevice());
	setEnableAllView(true);
}

void CopyTabWidget::TaskHasFinished()
{
	auto finish_state = FinishState::getState();
	finish_state->UpdateButton( this );
	this->getStateManager()->ChangeState( finish_state );
	this->ui_.startButton->setEnabled( false );

	QString outputText( QString::fromLocal8Bit("Задача \"Копирование\" успешно завершена.\n" ) );
	ShowTaskText(outputText);
}




