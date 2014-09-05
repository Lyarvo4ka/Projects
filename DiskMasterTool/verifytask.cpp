#include "verifytask.h"
#include "Functions.h"
#include "dmtreemodel.h"

#include "DiskMasterLib\dm_constant.h"

QuickVerifyTask::QuickVerifyTask( const DWORD id , QObject * parent )
	: AbstractTask( parent )
	, disk_master_ ( DMTool::getDiskMaster(id) )
	, offset_ ( 0 )
	, sectors_count_ ( 0 )
	, currentSector_ ( 0 )
	, task_break_ ( false )
	, bExecuting_( false )
{
	assert( disk_master_ != nullptr );
	disk_master_->getNotifier()->Attach(this);
}
QuickVerifyTask::~QuickVerifyTask()
{
	disk_master_->getNotifier()->Detach(this);
	disk_master_ = nullptr;
	offset_ = 0;
	sectors_count_ = 0;
	currentSector_ = 0;
	bExecuting_ = false;
}
void QuickVerifyTask::StartTask(const DM::PORT * source_port, const DM::PORT * target_port, DWORD param)
{
	//if (source_port)
	//{

	//	currentSector_ = 0;
	//	param_ = param;

	//	if ( device_ = disk_master_->getDiskDevice(source_port) )
	//		this->start();
	//}
}
void QuickVerifyTask::StartTaskEx(const DM::PORT * source_port, const DM::PORT * target_port, const DataRange block_range, DWORD param)
{
	port_ =  ( DM::PORT * ) source_port;
	offset_ = block_range.SourceOffset_;
	sectors_count_ = block_range.SectorsCount_;
	task_break_ = false;

	this->start();

}

void QuickVerifyTask::AbortTask()
{
	PauseTask();
}
void QuickVerifyTask::Detect( const DM::PORT * port )
{
	assert( port != nullptr );
	ExecuteTask( port->number , 0 , 0 );

	emit finish_detect();
}

void QuickVerifyTask::VerifyBlock( const DM::PORT * port, qlonglong offset , qlonglong sector_count )
{
	assert( port != nullptr );
	auto disk =  disk_master_->getDiskDevice( port );
	assert ( disk != nullptr );
	assert( disk->getSize() <= (qlonglong)( offset + sector_count ) );

	currentSector_ = offset_;
	DWORD block_size = MaxSectorsCount;
	qlonglong prev_sector = currentSector_;

	while( currentSector_ < sector_count )
	{
		if ( task_break_ )
			break;
		if( (qlonglong) (currentSector_ + block_size ) > sector_count )
		{
			block_size = (DWORD) (sector_count - currentSector_);
		}

		qDebug() << "QuickVefifyTask is starting...(" << currentSector_ << ")";
		currentSector_ ;
		bExecuting_ = true;
		if ( ExecuteTask( port->number , currentSector_ , block_size ) )
		{
			/*sectors += block_size;*/
			if ( block_size < MaxSectorsCount )
				block_size *= 2;
		}
		else
		{
			block_size = MinSectorsCount;
			//sectors = currentSector_;
		}
		bExecuting_ = false;

	}
	if ( task_break_ )
		emit break_task( currentSector_ );
	else
		emit finish_task( this->getLastSector() );
}

LONGLONG QuickVerifyTask::getSectorsCount() const
{
	return sectors_count_;
}
void QuickVerifyTask::Update(DCNotifier *notifier, DWORD event_code, void *param)
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
void QuickVerifyTask::run()
{
	if ( sectors_count_  == 0 )
		this->Detect( port_ );
	else
	{
		this->VerifyBlock( port_ , offset_, sectors_count_ );
	}
}

void QuickVerifyTask::NewDiskDetected( void *param )
{
	if (DM::Disk * new_disk = static_cast<DM::Disk *> (param) )
	{
		if ( auto disk_device = disk_master_->getDiskDevice( new_disk->Port() ) )
		{
			disk_device->setDisk(new_disk);
			emit new_device(new_disk->Port());
		}
	}
}

void QuickVerifyTask::TaskInProgress( void *param )
{

}

void QuickVerifyTask::BadSector( void *param )
{
	if ( auto * pBadSector = static_cast<ULONGLONG*> (param) )
	{
		qDebug() << "Bad sector" << *pBadSector;
		disk_master_->Break();
		emit bad_sector( *pBadSector );
	}
}

void QuickVerifyTask::TaskComplete( void * param )
{
	if ( DM::DM_TASK_INFO * task_info = static_cast< DM::DM_TASK_INFO * > (param) )
	{
		memcpy(&currentSector_,&task_info->lba,sizeof(task_info->lba));
		//emit finish_task(currentSector_);
		update_lba( currentSector_ );
	}
}

void QuickVerifyTask::TaskBreak( void * param )
{
	if ( DM::DM_TASK_INFO * task_info = static_cast< DM::DM_TASK_INFO * > (param) )
	{
		memcpy(&currentSector_,&task_info->lba,sizeof(task_info->lba));
		//emit break_task(currentSector_);
		update_lba( currentSector_ );
	}
}

void QuickVerifyTask::TaskError( void * param )
{

}

void QuickVerifyTask::DetectError( void *param )
{
	if (WORD detectErrorNumber = (WORD) param )
	{
		DWORD port_number = portFromNotDetected( detectErrorNumber );
		if ( auto port =  disk_master_->getPortByNumber(port_number) )
			emit not_detected( port, detectErrorNumber );
	}
}

void QuickVerifyTask::DiskRemoved( void *param )
{
	if (DM::Disk * remove_disk = static_cast<DM::Disk *> (param) )
		if ( auto disk_device = disk_master_->getDiskDevice( remove_disk->Port() ) )
		{
			qDebug() << "Disk Removed..." << disk_device->getPort()->name;
			disk_device->setDisk(nullptr);
			emit disk_removed( disk_device->getPort() );
		}

}




/************************************************************************/
/*							 VerifyTabWidget							*/
/************************************************************************/


//VerifyTabWidget::VerifyTabWidget(QWidget *parent , DMItemIdex * dm_index )
//	: BaseTabWidget(parent)
//	, dm_index_(dm_index)
//	, disk_master_(nullptr)
//	, curDevice_ (nullptr)
//	, abstract_test_( nullptr )
//	, taskLog_( nullptr )
//{
//	verifyWidgetUi_.setupUi(this);
//	disk_master_ = toDiskMaster (dm_index->getDevice());
//	if (disk_master_)
//	{
//		verifyWidgetUi_.deviceWidget->setWidgetName( QString::fromLocal8Bit("Устройство для тестирования:") );
//		connect( verifyWidgetUi_.deviceWidget, SIGNAL ( deviceIndexChanged ( int ) ), this, SLOT (device_changed(int) ) );
//		add_devices( );
//
//		verifyWidgetUi_.taskInfoWidget->setDiskMasterName( "DiskMasterUsb Board id = " + QString::number( disk_master_->getID() ) );
//	}
//
//	ShowDetectionInfo(false);
//	connect ( verifyWidgetUi_.rangeWidget, SIGNAL(DetectDevicePressed( PortArray )), this, SLOT( StartDetectDevices( PortArray ) ) );
//
//	taskLog_ = new TaskLog( verifyWidgetUi_.taskInfoWidget->getLogPath() );
//	if ( !taskLog_->isOpen() )
//	{
//		QMessageBox msgBox;
//		msgBox.setText(QString::fromLocal8Bit("Не удалось октрыть файл протокола, проверьте путь к файлу."));
//		msgBox.setIcon(QMessageBox::Critical);
//		msgBox.exec();
//	}
//}
//VerifyTabWidget::~VerifyTabWidget()
//{
//	if (taskLog_)
//	{
//		delete taskLog_;
//		taskLog_ = nullptr;
//	}
//	qDebug("Destructor [\'VerifyTabWidget\']");
//}
//bool VerifyTabWidget::isEqual(const DMItemIdex * dm_index)
//{
//	return compareItemIndexes(dm_index_,dm_index);
//}
//bool VerifyTabWidget::isEqual(const DiskMasterPtr2 & disk_master)
//{
//	return isDM_InIndex(dm_index_,disk_master);
//}
//QString VerifyTabWidget::getTabName() const
//{
//	return VerifyTaskText;
//}
//void VerifyTabWidget::setProgress(const int position)
//{
//	verifyWidgetUi_.progressBar->setValue(position);
//	if (dm_index_)
//		dm_index_->setPorgress(position);
//}
//void VerifyTabWidget::setEnableAllView( bool bEnable )
//{
//	verifyWidgetUi_.taskInfoWidget->setEnabled(bEnable);
//	verifyWidgetUi_.deviceWidget->setEnabled(bEnable);
//	verifyWidgetUi_.rangeWidget->setEnabled(bEnable);
//	verifyWidgetUi_.startButton->setEnabled(bEnable);
//	verifyWidgetUi_.cancelButton->setEnabled(bEnable);
//}
//void VerifyTabWidget::ShowDetectionInfo( bool bShow )
//{
//	EnableDetectionInfo ( verifyWidgetUi_.detectDriveText , verifyWidgetUi_.lcdNumber , bShow );
//}
//void VerifyTabWidget::add_devices( )
//{
//	AddSources(disk_master_ , verifyWidgetUi_.deviceWidget);
//	AddTargets(disk_master_ , verifyWidgetUi_.deviceWidget);
//}
//void VerifyTabWidget::device_changed( int nIndex )
//{
//	if ( nIndex < disk_master_->source_count() )
//		curDevice_ = disk_master_->getSource(nIndex);
//	else
//		curDevice_ = disk_master_->getTarget(nIndex - disk_master_->source_count() );
//
//	verifyWidgetUi_.deviceWidget->set_device(curDevice_);
//	setRangeData();
//}
//void VerifyTabWidget::start_clicked()
//{
//	dm_index_->setState(DMItemIdex::started);
//	dm_index_->setStatus(DMItemIdex::verifying);
//	if ( dm_index_->getStatus() == DMItemIdex::started)
//		setEnableAllView(false);
//	verifyWidgetUi_.cancelButton->setEnabled(true);
//	setProgress(0);
//
//	QString logText(QString::fromLocal8Bit("Задача верификации начата."));
//	AppendLogText(logText);
//
//	abstract_test_ = new QuickVerifyTask(disk_master_,this);
//	connect (abstract_test_, SIGNAL(new_device( const DM::PORT * )), this, SLOT(DeviceDetected(const DM::PORT *)));
//	connect (abstract_test_, SIGNAL(update_lba( const qlonglong)), this, SLOT(current_lba( const qlonglong)));
//	connect (abstract_test_, SIGNAL( finish_task( const qlonglong ) ), this, SLOT( task_finished( const qlonglong )) );
//	connect (abstract_test_, SIGNAL( break_task(const qlonglong) ), this, SLOT( task_breaked(const qlonglong) ));
//	connect (abstract_test_, SIGNAL( not_detected(const DM::PORT *, int) ), this, SLOT( DeviceNotDetected(const DM::PORT *, int) ) );
//
//	if (verifyWidgetUi_.rangeWidget->isChecked())
//	{
//		DataRange data_block;
//		data_block.SourceOffset_ = verifyWidgetUi_.rangeWidget->getOffset();
//		data_block.TargetOffset_ = 0;
//		data_block.SectorsCount_ = verifyWidgetUi_.rangeWidget->getSectorsCount();
//		verifyWidgetUi_.currentSector->setText("0 / " + QString::number(data_block.SectorsCount_));
//
//		abstract_test_->StartTaskEx(curDevice_->getPort(), nullptr, data_block, 0);
//	}
//	else
//	{
//		verifyWidgetUi_.currentSector->setText("0");
//		abstract_test_->StartTask(curDevice_->getPort(), nullptr, 0);
//	}
//
//}
//void VerifyTabWidget::cancel_clicked()
//{
//	if (abstract_test_)
//	{
//		abstract_test_->AbortTask();
//	}
//}
//void VerifyTabWidget::current_lba( const qlonglong currectSector )
//{
//	int progressValue = (int) (currectSector * 100) / ( abstract_test_->getSectorsCount() ) ;
//
//	if ( progressValue >= 0 && progressValue <= 100)
//	{
//		setProgress(progressValue);
//	}
//	QString currSectorStr(QString::number(currectSector) + "/" + QString::number(abstract_test_->getSectorsCount()));
//	verifyWidgetUi_.currentSector->setText(currSectorStr);
//
//}
//void VerifyTabWidget::task_finished( const qlonglong lastSector )
//{
//	current_lba(lastSector);
//	setProgress(100);
//	QString outputText( QString::fromLocal8Bit("Задача \"Верификация\" успешно завершена.\n" ) );
//	AppendLogText(outputText);
//	QMessageBox msgBox;
//	msgBox.setText(outputText);
//	msgBox.exec();
//	dm_index_->setState(DMItemIdex::completed);
//	dm_index_->setStatus(DMItemIdex::ready);
//	setEnableAllView(true);
//
//	if (abstract_test_)
//	{
//		abstract_test_->exit();
//		delete abstract_test_;
//		abstract_test_ = nullptr;
//	}
//}
//void VerifyTabWidget::task_breaked( const qlonglong last_lba )
//{
//	current_lba(last_lba);
//	QString outputText( QString::fromLocal8Bit("Задача \"Верификация\" была прервана.\n" ) );
//	AppendLogText(outputText);
//	QMessageBox msgBox;
//	msgBox.setText(outputText);
//	msgBox.exec();
//	dm_index_->setState(DMItemIdex::completed);
//	dm_index_->setStatus(DMItemIdex::ready);
//	setEnableAllView(true);
//
//	if (abstract_test_)
//	{
//		abstract_test_->exit();
//		delete abstract_test_;
//		abstract_test_ = nullptr;
//	}
//}

//QString VerifyTabWidget::getTabName() const
//{
//	return VerifyTaskText;
//}
