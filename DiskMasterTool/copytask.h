#ifndef COPYTASK_H
#define COPYTASK_H

// warning C4482: nonstandard extension used: enum
#pragma warning(disable : 4482)

 #include <QTime>
 #include <QTimer>

#include "abstract_task.h"
#include "ui_CopyWidgetUi.h"
#include "Functions.h"
#include "tabwidgets.h"
#include "sectormodel.h"
#include "taskmanager.h"
#include "dmtreemodel.h"
#include "factories.h"
#include <QTabWidget>
#include "partitionmodel.h"

class StateManager;

#include "copydetectdialog.h"

const int errSourceMoreTarget = 1000;
static const QString strSourceMoreTarget =  QString::fromLocal8Bit("Source device is more than target device");
const int errDiskMasterNotRespond = 1001;
static const QString strDiskMasterNotRespond =  QString::fromLocal8Bit("DiskMaster isn't responding.");

static QString getErrorFromNumber( int iErrorEode )
{
	switch (iErrorEode)
	{
	case errSourceMoreTarget:
		return strSourceMoreTarget;
	case errDiskMasterNotRespond:
		return strDiskMasterNotRespond;
	}
	return QString();
}


/////////////////////////	QuickCopyTask	///////////////////////////////////
class QuickCopyTask
	: public AbstractTask
	, protected AbstractTaskObserver

{
	Q_OBJECT

protected:
	static const DWORD DefualtJumpSize = 16;	// in sectors

public:

	QuickCopyTask( QObject * parent = 0 );
	QuickCopyTask( const DWORD id, QObject * parent = 0 );
	virtual ~QuickCopyTask();

	void Initialize(const DWORD id);
	void Finalize();

protected:
	virtual void run();

public:
	void Detect( const DM::PORT * source_port, const DM::PORT * target_port );
	void CopyBlock( const DM::PORT * source_port, const DM::PORT * target_port , qlonglong source_offset , qlonglong target_offset , qlonglong sector_count );
	void CopyBlockBack( const DM::PORT * source_port, const DM::PORT * target_port , qlonglong source_offset , qlonglong target_offset , qlonglong sector_count );

	//	implement observers
	 void NewDiskDetected(  void *param ) override;
	 void TaskInProgress( void *param ) override;
	 void BadSector( void *param ) override;
	 void TaskComplete( void * param ) override;
	 void TaskBreak( void * param ) override;
	 void TaskError( void * param ) override;
	 void DetectError( void *param ) override;
	 void DiskRemoved( void *param ) override;

	 virtual void Update(DCNotifier *notifier, DWORD event_code, void *param) override;

	// in this stage this function isn't implemented
	virtual void StartTask(const DM::PORT * source_port, const DM::PORT * target_port , DWORD param) override;
	virtual void StartTaskEx(const DM::PORT * source_port, const DM::PORT * target_port, const DataRange block_range , DWORD param) override;
	virtual void AbortTask() override
	{
		PauseTask();
		//if ( bExecuting_ )
		//	this->BreakTask();
	}
	void PauseTask() 
	{
		task_break_ = true;
		if ( bExecuting_ )
			this->BreakTask();
	}
	void BreakTask() 
	{
		disk_master_->Break();
	}

	bool isTaskBreak() const
	{
		return task_break_;
	}
	LONGLONG getLastSector() const override
	{
		return sectors_count_ + source_offset_;
	}
	void setSectorModel( AbsractSectorModel * sectorModel )
	{
		sectorModel_ = sectorModel;
	}
	AbsractSectorModel * getSectorModel()
	{
		return sectorModel_;
	}
	void setCurrentSector( qlonglong currnetSector )
	{
		currentSector_ = currnetSector;
	}
	void incCurrentSector()
	{
		++currentSector_;
	}
	qlonglong getCurrentSector() const
	{
		return currentSector_;
	}
	qlonglong getSectorCount() const
	{
		return sectors_count_;
	}
	DWORD getID() const
	{
		return id_;
	}
	void setJumpSize( qlonglong jumpSize )
	{
		jumpSize_ = jumpSize;
	}
	ULONGLONG SourceOffset() const
	{
		return source_offset_;
	}
	ULONGLONG TargetOffset() const
	{
		return target_offset_;
	}
	const DM::PORT * SourcePort() const
	{
		return source_port_;
	}
	const DM::PORT * TargetPort() const
	{
		return target_port_;
	}
	qlonglong SectorFromTaskInfo( const DM::DM_TASK_INFO * task_info )
	{
		qlonglong sector = 0;
		memcpy(&sector,&task_info->lba,sizeof(task_info->lba));
		return sector;
	}
	void Update_Sectors( const DM::DM_TASK_INFO * task_info)
	{
		qlonglong updete_sector = 0;
		memcpy(&updete_sector,&task_info->lba,sizeof(task_info->lba));
		if ( sectorModel_ )
		if ( sectorModel_->isLoaded() )
		{
			auto dist = getSectorDistance(updete_sector, currentSector_);
			if ( dist > 0 )
				sectorModel_->updateBlock(currentSector_, dist , SECTOR_STATUS::READ_GOOD );
		}

		currentSector_ = updete_sector;
		//emit update_lba(currentSector_);
	}
	DWORD getBlockSize() const
	{
		return copyBlockSize_;
	}
	void change_direction( TaskDirection task_direction )
	{
		direction_ = task_direction;
	}
	TaskDirection direction()
	{
		return direction_;
	}

private:
	//virtual void CopyBlock(
	void ChangeSector( qlonglong & change_sector , const qlonglong prev_sector , const DWORD blockSize )
	{
		if ( direction_ == BackwardTask)
		{
			change_sector = prev_sector;
			change_sector -= blockSize;
		}
	}
	void JumpSectors( qlonglong & jump_sector , const qlonglong prev_sector , qlonglong sectorsToJump)
	{
		switch ( direction_ )
		{
		case ForwardTask:
			jump_sector += sectorsToJump;
			
			if ( jump_sector > (sectors_count_ + source_offset_) )
				jump_sector = (sectors_count_ + source_offset_);

			break;
		case BackwardTask:
			jump_sector = prev_sector;
			jump_sector -= sectorsToJump;
			if ( jump_sector < source_offset_ )
				jump_sector = source_offset_;
			break;
		}

	}
private:
	DWORD id_;
	DiskMasterDevice * disk_master_;
	DM::PORT * source_port_;
	DM::PORT * target_port_;
	volatile bool task_break_;
	volatile bool bExecuting_;
	bool task_error_;
	bool unknown_bad_;
	//
	ULONGLONG source_offset_;
	ULONGLONG target_offset_;
	ULONGLONG sectors_count_;
	qlonglong currentSector_;
	DWORD copyBlockSize_;
	qlonglong jumpSize_;
	AbsractSectorModel * sectorModel_;
	
	TaskDirection direction_;
};


/////////////////////////	SmartCopyTask	///////////////////////////////////
class SmartCopyTask 
	: public QuickCopyTask
{
	Q_OBJECT
public:
	SmartCopyTask( const DWORD id, QObject * parent = 0 )
		: QuickCopyTask( id , parent )
	{
		setJumpSize( 0 );
	}
	~SmartCopyTask()
	{

	}
	virtual void BadSector( void *param ) override
	{
		if ( auto * pBadSector = static_cast<ULONGLONG*> (param) )
		{
			if ( this->isTaskBreak() || getBlockSize() > MinSectorsCount )
				this->PauseTask();
			qint32 update_size = (qint32) (* pBadSector - this->getCurrentSector() );
			if ( this->getSectorModel() )
			{
				if (update_size > 0 )
					this->getSectorModel()->updateBlock(this->getCurrentSector() , update_size , SECTOR_STATUS::READ_GOOD);

				this->getSectorModel()->updateSector( * pBadSector , SECTOR_STATUS::READ_BAD );
			}
			setCurrentSector(* pBadSector );
			incCurrentSector();
			emit bad_sector( *pBadSector );
			qDebug() << "BadSector." << *pBadSector;
		}

	}
protected: 
	virtual void run() override;
};




class StateManager;

class DevicePresenter;
//class DMItemIdex;

inline void ChangeBackgroundColor( QFrame * frame , QColor color )
{
	QPalette palette = frame->palette();
	palette.setColor( QPalette::Background , color);
	frame->setPalette( palette );
	frame->setAutoFillBackground( true );

}

class MasterBootRecord
{
public:
	static const WORD mbr_size = 512;
	static const byte partition_count = 4;
	static const WORD partition_offset = 446;
	static const WORD boot_signature = 0xAA55;
	static const WORD boot_signature_offset = 510;

	MasterBootRecord(const DWORD offsetMBR = 0)
		: mbr_offset_( offsetMBR )
		, bOpened_( false )
	{

	}
	virtual ~MasterBootRecord()
	{

	}
	void setOffset( const DWORD offsetMBR);
	virtual bool open( DiskMasterDevice * disk_master , DiskDevicePtr & device )
	{
		if ( bOpened_ )
			return true;

		PartitionArray_.clear();
		if ( disk_master->isReady() )
		{
			BYTE sector[ SECTOR_SIZE ];
			ULONGLONG offset = 0;
		//	if ( disk_master->ReadBlock( device->getPort()->number , offset,  sector , 1) )
			{
				WORD * p55AA = ( WORD * ) &sector[ boot_signature_offset ] ;
				if ( *p55AA == boot_signature )
				{
					partition_enty * pEntry = ( partition_enty * ) ( &sector[ partition_offset ] );
					for ( int iPartition = 0 ; iPartition < partition_count ; ++iPartition )
					{ 
						if ( isPartition( pEntry->partition_type ) )
						{
							PartitionArray_.push_back( PartitionEntryPtr( new PartitionEntry( pEntry->start_lba , pEntry->sector_count , pEntry->partition_type ) ) );
							// next check boot sector
						}
						++pEntry;
					}
					bOpened_ = true;
					return bOpened_;
				}
				else
				{
					qDebug() << "Сигнатура 0x55AA не верная.";
				}

			}
		}

		return false;
	}
	bool ReOpen( DiskMasterDevice * disk_master , DiskDevicePtr & device )
	{
		bOpened_ = false;
		return open(disk_master , device );
	}
	DWORD count() const
	{
		return PartitionArray_.size();
	}
	PartitionEntryPtr getPartition(const DWORD number) const
	{
		return ( number < PartitionArray_.size() ) ? PartitionArray_.at( number ) : nullptr;
	}


private:
	DWORD mbr_offset_;
	bool bOpened_;
	vector< PartitionEntryPtr > PartitionArray_;
};



class CopyTabWidget 
	: public BaseTabWidget
	//, public AbstractTaskCreator
{
	Q_OBJECT

public:
	CopyTabWidget( DWORD id , QWidget *parent = 0);
	~CopyTabWidget();

	void Initialize( DWORD id );
	void Finalize();
	AbstractTask * CreateTask( DWORD task_id ) override;
	AbstractTask * OpenTask(const QString & fileName) override;
	void CloseTask( ) override;

	bool isEqual( DWORD id , DMTool::DM_TASK task_id) override;
	QString getTabName() const override;
	void StartTask() override
	{
		start_clicked();
	}
	void AbortTask() override
	{
		cancel_clicked();
	}
	void AbortAndClose( ) 
	{
		CloseTask();
		emit removeMe( this );
	}

	void setProgress( int position);
	void ChangeStartButton( const QString & text , const QIcon & incon )
	{
		UpdateButton( ui_.startButton , text , incon );
	}
	DiskDevicePtr getSourceDevice() const;
	DiskDevicePtr getTargetDevice() const;
	bool isSourceDetected() const;
	bool isTargetDetected() const;

	void setEnableAllView(bool bEnable );
	void InsertLogText(const QString & logText) override
	{
		ui_.logText->insertPlainText(logText);
		//task_log->inserntText(logText);
	}
	void AppendLogText(const QString & logText) override
	{
		ui_.logText->append(logText);
	}
	void UpdateDeviceFromPort( const DM::PORT * port) override
	{
		if ( auto disk_master = DMTool::getDiskMaster( getID()) )
		if ( auto disk_ptr = getDiskFromPort(port) )
		{
			if ( isSource(port) )
				ui_.sourceWidget->change_data( disk_master->getSourceIndex( port ), displayName( disk_ptr ) , identifyIcon( disk_ptr ) );
			else
			if ( isTarget(port) )
				ui_.targetWidget->change_data( disk_master->getTargetIndex( port ), displayName( disk_ptr ) , identifyIcon( disk_ptr ) );
		}
	}
	DiskDevicePtr getDiskFromPort( const DM::PORT * port) override
	{
		return DMTool::getDiskFromPort(port , getID() );
	}
	//void setDefaultPorts( PortNumbers ports)
	//{
	//	source_changed(ports.port_1);
	//	target_changed(ports.port_2);
	//}
	void DetectDevices( DWORD port1 , DWORD port2) 
	{
		if ( auto disk_master = DMTool::getDiskMaster( getID() ) )
		{
			auto source_port = disk_master->getPortByNumber(port1);
			auto target_port = disk_master->getPortByNumber(port2);
			
			StartDetectDevices( source_port , target_port );
		}
	}
	AbsractSectorModel * getModel() const
	{
		return sectorModel_;
	}
	void setCurrentSector( qlonglong current_sector )
	{
		TaskStruct_.current_sector = current_sector;
	}
	qlonglong getCurrentSector( ) const
	{
		return TaskStruct_.current_sector;
	}
	TaskFileStruct & getTaskStruct()
	{
		return TaskStruct_;
	}
	void showSettings();
	void startTimer()
	{
		elapsedTime_.setHMS( 0 , 0 , 0 , 0);
		timeTimer_.start( 1000 );

		timeDuration_.start();
	}
	void stopTimer()
	{
		timeTimer_.stop();
	}
	void setCopyMode( int copy_mode )
	{
		preferences_->setCopyMode( copy_mode ); 
	}
	//////////////////////////////////////////////////////////////////////////
public slots:
		void source_changed(int);
		void target_changed(int);
		void pause_clicked()
		{
			auto task_manager = DMTool::DMTaskManager::GetTaskManager();
			if ( auto copy_task = task_manager->GetTask(getID()) )
			{
				copy_task->PauseTask();
			}
		}
		void StartDetectDevice()
		{
			if ( auto souce_device = getSourceDevice() )
			if ( auto target_device = getTargetDevice() )
			{
				StartDetectDevices(souce_device->getPort() , target_device->getPort() );
			}
		}
		void StartDetectDevices( const DM::PORT * source_port , const DM::PORT * target_port) 
		{
			if ( auto disk_master = DMTool::getDiskMaster( getID() ) )
			{
				if ( source_port != getSourceDevice()->getPort() )
					ui_.sourceWidget->ChangeDevice( disk_master->getSourceIndex(source_port) );
				if ( target_port != getTargetDevice()->getPort() )
					ui_.targetWidget->ChangeDevice( disk_master->getTargetIndex(target_port) );

				auto current_task = DMTool::DMTaskManager::GetTaskManager()->GetTask( getID() );
				if ( ! current_task )
					current_task = this->CreateTask( DMTool::DM_QUICK_COPY_TASK );

				current_task->DetectDevices( source_port , target_port , 0 );
				setEnableAllView(false);

				QString text =  "<B> Performs detection devices.</B>"; //+ "( " + ;

				msgBox_->setText(text);
				msgBox_->setInformativeText("Please wait.");
				msgBox_->setStandardButtons(QMessageBox::NoButton);
				//msgBox_->setStandardButtons(QMessageBox::Cancel);
				msgBox_->setIcon(QMessageBox::Information);
				msgBox_->show();
			}
		}
		void cancelDetection( int result)
		{
			//if ( result == QMessageBox::Cancel )
			//if ( auto task = DMTool::DMTaskManager::GetTaskManager()->GetTask(id_) )
			//{
			//	task->AbortTask();
			//}
		}
		void DeviceNotDetected(const DM::PORT *, int)
		{
			// if program state is "Detection"

		}

		void current_lba(const qlonglong );
		void task_finished(const qlonglong );
		void thread_finished();
		void task_breaked(const qlonglong);
		void detect_finished()
		{
			msgBox_->hide();
			setEnableAllView(true);
			//	1 - check for detection
			if ( isSourceDetected() && isTargetDetected() )
			{
			//	2 - create sector map
				if ( auto file_holder = DMTool::getFileHolder(getID()) )
				{
					TaskStruct_.setSource(this->getSourceDevice());
					TaskStruct_.setTarget(this->getTargetDevice());
					// ????????????????????	15800016
					TaskStruct_.source_offset = 0;
					TaskStruct_.target_offset = 0;
					TaskStruct_.sectors_count = getMinValue( getSourceDevice()->getSize() , getTargetDevice()->getSize() );
					//TaskStruct_.sectors_count -= TaskStruct_.source_offset;
					TaskStruct_.min_lba = 0;
					//if ( DM_Settings::getSettings()->getCopySettings( getID() ).direction_ == ForwardTask )
					//	TaskStruct_.min_lba = TaskStruct_.current_sector;
					TaskStruct_.max_lba = TaskStruct_.sectors_count;

					file_holder->WriteTaskData(TaskStruct_);
					elapsedTime_.restart();
					current_lba( TaskStruct_.current_sector );

					if ( QuickCopyTask * copyTask = qobject_cast< QuickCopyTask * > ( DMTool::DMTaskManager::GetTaskManager()->GetTask(getID()) ) )
					{
						copyTask->setSectorModel(sectorModel_);
						if ( !sectorModel_->isLoaded() )
						{
							QString sectorMapPath( FileSystem::CreateFilePath(file_holder->getFolderName() , file_holder->getTaskName() , ".map"));
							sectorModel_->createMap(getSourceDevice()->getSize() , sectorMapPath );
						}
					}
				}
				//	???
				SectorModel * pSectorModel = qobject_cast< SectorModel * > ( sectorModel_ );
				ui_.badSectorsText->setText( QString::number( pSectorModel->getBadsCount() ) );
				ui_.readSectorsText->setText( QString::number( pSectorModel->getReadCount() ) );
				ui_.unreadText->setText( QString::number( pSectorModel->getUnreadCount() ) );


				ui_.startButton->setEnabled(true);
				
				if ( TaskStruct_.copy_mode == DMTool::PARTITION_COPY )
				if ( auto disk_master = DMTool::getDiskMaster( this->getID() ) )
				{
					partitionModel_->getRootIndex()->RemoveAll();
					MasterBootRecord mbr;
					if ( mbr.open( disk_master , getSourceDevice() ) )
					{
						auto root_Partiton = partitionModel_->getRootIndex() ;
						for ( int iPart = 0 ; iPart < mbr.count() ; ++iPart )
						{
							auto pPartition = mbr.getPartition(iPart);
							PartitionEntry * pEntry = new PartitionEntry( pPartition->getStartSector() , pPartition->getSectorCount(), pPartition->getPartitionType() );
							PartitionItemIndex * pIndex = new PartitionItemIndex( pEntry );
							//pIndex->setNumber( iPart );
							auto partition = mbr.getPartition( iPart );
							pIndex->setName( QString::number( iPart ) + ": " + partition->getPartitionTypeName() ); 
							root_Partiton->Add( pIndex );
						}
						int count = root_Partiton->count();
						if ( count > 0 )
						{
							for ( auto iPart = 0; iPart < count ; ++iPart )
							{
								//PartitionItemIndex * partition = dynamic_cast< PartitionItemIndex *> ( root_Partiton->getChild(iPart) );
								//auto part_entry = partition->getPartitionEntry();
								//pPartitionFile[ iPart ].offset = part_entry->getStartSector();
								//pPartitionFile[ iPart ].count = part_entry->getSectorCount();
								//pPartitionFile[ iPart ].bChecked = partition->getChecked();
							}

							//TaskStruct_.setPartitions(pPartitionFile , count );
						}
					}
					auto root_Partition = partitionModel_->getRootIndex() ;
					if ( root_Partition->hasChildrend() )
					{
						for( int iPartition = 0; iPartition < root_Partition->count() ; ++iPartition )
						{
							if ( root_Partition->getChecked() == Qt::Checked )
							{
								auto partition = dynamic_cast< PartitionItemIndex *> ( root_Partition->getChild( iPartition ) );
								auto part_entry = partition->getPartitionEntry();

								TaskStruct_.source_offset = part_entry->getStartSector();
								TaskStruct_.target_offset = part_entry->getStartSector();
								TaskStruct_.sectors_count = part_entry->getSectorCount();

								TaskStruct_.current_partition_ = iPartition;

							}
							//if ( partition)
						}
					}
				}
			
				ShowTaskInfo( TaskStruct_.copy_mode );
				
			}
			else
			{
				msgBox_->setText("<B> Devices weren't detected.</B>");
				msgBox_->setInformativeText("");
				msgBox_->setStandardButtons(QMessageBox::Ok);
				msgBox_->setIcon(QMessageBox::Information);
				msgBox_->show();

				ui_.startButton->setEnabled(false);
			}
		}
		void task_error( int );
		void BadSector( const qlonglong sector )
		{
			AppendLogText(QString("Sector : ") + QString::number( sector ) + QString(" couldn't read."));
		}

		void onTimeTimer()
		{
			if ( elapsedTime_.isValid() )
			{
				QString text ( elapsedTime_.toString() );
				ui_.timeText->setText( text );
			}
			elapsedTime_ = elapsedTime_.addSecs( 1 );
		}

private:
	void add_sources( );
	void add_targets( );
	bool isSource( const DM::PORT * port );
	bool isTarget( const DM::PORT * port );
	void RemoveTask();
	void ShowTaskText(const QString & outputText );
	void TaskHasFinished();
	void ShowTaskInfo( int task_mode )
	{
		QString outputText;

		switch ( task_mode )
		{
		case DMTool::FULL_COPY:
			outputText = QString::fromLocal8Bit("Full copy ( ") + QString::number(TaskStruct_.source_offset) + " -> " + QString::number( TaskStruct_.sectors_count) + ").";
			break;
		case DMTool::PARTITION_COPY:
			outputText = QString::fromLocal8Bit("Partition copy.");
			break;
		case DMTool::USER_COPY:
			outputText = QString::fromLocal8Bit("User copy ( ") + QString::number(TaskStruct_.source_offset) + " -> " + QString::number( TaskStruct_.sectors_count) + ").";
			break;
		default:
			outputText = "";
		}
		ui_.currentTaskText->setText( outputText );
	}
	void changeTaskRange()
	{
		//if( DM_Settings::getSettings()->getCopySettings(getID()).direction_ == ForwardTask )
		//	TaskStruct_.min_lba = TaskStruct_.current_sector;
		//else
		//	TaskStruct_.max_lba = TaskStruct_.current_sector;
	}

private:
	Ui::CopyWidget ui_;
	AbsractSectorModel * sectorModel_;
	PartitionTreeModel * partitionModel_;
	CopyProperiesUiDialog * preferences_;
	DevicePresenter * DeviceOptions_;

	QMessageBox * msgBox_;
	TaskFileStruct TaskStruct_;
	QTime elapsedTime_;
	QTime timeDuration_;
	QTimer timeTimer_;
	bool bTaskError_;
};






#endif // COPYTASK_H
