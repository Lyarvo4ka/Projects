#ifndef ERASETASK_H
#define ERASETASK_H

// warning C4482: nonstandard extension used: enum
#pragma warning(disable : 4482)

#include "verifytask.h"
#include "ui_EraseTabWidget.h"

class QuickEraseTask
	: public QuickVerifyTask

{
	Q_OBJECT

public:
	QuickEraseTask( const DWORD id, QObject * parent = 0 )
		: QuickVerifyTask( id , parent )
		, pattern_ ( dm_erase_00 )
	{

	}
	virtual ~QuickEraseTask()
	{

	}
	void setPattern( DWORD erase_pattern = dm_erase_00 )
	{
		pattern_ = erase_pattern;
	}
	bool ExecuteTask( DWORD port , qlonglong offset , qlonglong sector_count ) override
	{
		return this->getDiskMaster()->EraseEx( port , offset , sector_count , pattern_ );
	}
private:
	DWORD pattern_;

};

//
class EraseTabWidget 
	: public BaseTabWidget
{
	Q_OBJECT

public:
	EraseTabWidget( DWORD id , QWidget *parent = 0 )
		: BaseTabWidget ( parent )
		, taskManager_( DMTool::DMTaskManager::GetTaskManager() )
		, disk_master_( DMTool::getDiskMaster( id ) )

	{
		ui_.setupUi( this );
		setID( id );
		msgBox_ = new QMessageBox( this );
		Initialize( id );
		this->getStateManager()->ChangeState( NewTaskState::getState() );
	}
	~EraseTabWidget()
	{
		taskManager_ = nullptr;
		disk_master_ = nullptr;
	}
	void Initialize( DWORD id )
	{
		setID( id );
		ui_.deviceWidget->setWidgetName( QString::fromLocal8Bit("Device to erasing:") );
		connect( ui_.deviceWidget, SIGNAL ( deviceIndexChanged(int) ), this, SLOT ( device_changed(int) ) );

		connect( ui_.deviceWidget , SIGNAL ( deviceDetect() ) , this , SLOT( StartDetectDevice() ) );

		add_devices();
		file_struct_.Initialize();
	}

	AbstractTask * CreateTask( DWORD task_id ) override
	{
		return Factories::FactoryManager::getInstance()->Lookup( task_id )->CreateTask( getID() , this );
	}
	AbstractTask * OpenTask( const QString & fileName ) override
	{
		return nullptr;
	}
	void CloseTask() override
	{
		this->getStateManager()->ChangeState( ExitState::getState() );
		this->getStateManager()->getState()->PerfomState( this );
		DMTool::WaitingForTaskEnd( getID() );
		DMTool::DMTaskManager::GetTaskManager()->RemoveTask( getID() );
	}
	bool isEqual( DWORD id , DMTool::DM_TASK task_id) override
	{
		return ( ( id == getID() ) && ( task_id == DMTool::DM_ERASE_TASK ) );
	}
	void setPattern( const DWORD pattern )
	{
		ui_.patternWidget->setPattern( pattern );
	}
	DWORD getPattern() const
	{
		DWORD pattern = ui_.patternWidget->getPattern();
		return pattern ;
	}
	QString getTabName() const
	{
		return EraseTaskText;
	}
	void StartTask() override
	{
		start_clicked();
	}
	void AbortTask() override
	{
		cancel_clicked();
	}
	void setProgress( int position) override
	{
		ui_.progressBar->setValue( position );
	}
	void setEnableAllView( bool bEnable ) override
	{
		ui_.deviceWidget->setEnabled( bEnable );
		ui_.tabWidget->setEnabled( bEnable );
	}
	void InsertLogText(const QString & logText) override
	{
		ui_.logText->insertPlainText(logText);
	}
	void AppendLogText(const QString & logText) override
	{
		ui_.logText->append(logText);
	}
	void UpdateDeviceFromPort( const DM::PORT * port) override
	{
		if ( auto disk_ptr = getDiskFromPort(port) )
		{
			ui_.deviceWidget->change_data( disk_master_->getDeviceIndex( port) , displayName( disk_ptr ) , identifyIcon( disk_ptr ) );
		}
	}
	DiskDevicePtr getDiskFromPort( const DM::PORT * port) override
	{
		return DMTool::getDiskFromPort(port , getID() );
	}
	void DetectDevices( DWORD port1 , DWORD port2)
	{
		if ( auto port = disk_master_->getPortByNumber(port1) )
			StartDetectDevice( port );
		else
			if ( auto port = disk_master_->getPortByNumber(port2) )
				StartDetectDevice( port );

	}
	void ChangeStartButton( const QString & text , const QIcon & incon )
	{
		UpdateButton( ui_.startButton , text , incon );
	}
	DiskDevicePtr getCurrentDevice() 
	{
		return disk_master_->getTarget( ui_.deviceWidget->getCurrentIndex() ) ;
	}
	//////////////////////////////////////////////////////////////////////////

	TestFileStruct * getTaskStruct () const 
	{
		return (TestFileStruct*)&file_struct_;
	}
	public slots:
		void device_changed( int nIndex ) 
		{
			if ( auto device = disk_master_->getTarget(nIndex) )
			{
				ui_.deviceWidget->change_data( nIndex , displayName( device ) , identifyIcon( device ) );
			}
		}
		void StartDetectDevice( const DM::PORT * port  )
		{
			if ( auto device = getDiskFromPort(port) )
			{
				ui_.deviceWidget->ChangeDevice( disk_master_->getTargetIndex( port ) );

				auto task = taskManager_->GetTask( getID() );
				if ( !task )
				{
					task = this->CreateTask(getID());
					taskManager_->AddTask( getID() , task );
				}
				setEnableAllView(false);
				task->DetectDevices( port , port , 0 );

				QString text =  "<B> Performs detection device.</B>"; 

				msgBox_->setText(text);
				msgBox_->setInformativeText("Please wait.");
				msgBox_->setStandardButtons(QMessageBox::NoButton);
				//msgBox_->setStandardButtons(QMessageBox::Cancel);
				msgBox_->setIcon(QMessageBox::Information);
				msgBox_->show();
			}
		}
		void StartDetectDevice()
		{
			if ( auto device = getCurrentDevice() )
				StartDetectDevice( device->getPort() );
		}
		void current_lba(const qlonglong current_sector )
		{
			file_struct_.current_sector = current_sector;
			QString currSectorStr(QString::number(current_sector) + "/" + QString::number( getCurrentDevice()->getSize() ));
			ui_.currentSector->setText( currSectorStr );
			auto total_sectors = getCurrentDevice()->getSize();
			if ( total_sectors > 0 )
			{
				int progressValue = (int) ( file_struct_.current_sector * 100 ) / ( total_sectors ) ;

				if ( progressValue >= 0 && progressValue <= 100)
				{
					setProgress(progressValue);
				}
			}
			file_struct_.offset = current_sector;
		}
		void task_finished(const qlonglong lastSector )
		{
			current_lba(lastSector);
			setProgress(100);

			msgBox_->setText("<B> Task has been finished.</B>");
			msgBox_->setInformativeText("");
			msgBox_->setStandardButtons(QMessageBox::Ok);
			msgBox_->setIcon(QMessageBox::Information);
			msgBox_->show();
			this->getStateManager()->ChangeState( FinishState::getState() );
			this->getStateManager()->getState()->UpdateButton( this );
			ui_.startButton->setEnabled( false );
		}
		void thread_finished()
		{

		}
		void task_breaked(const qlonglong lastSector)
		{
			current_lba( lastSector );
		}
		void detect_finished()
		{
			msgBox_->hide();
			setEnableAllView(true);
			//	1 - check for detection
			if ( auto device = disk_master_->getTarget( ui_.deviceWidget->getCurrentIndex() ) )
			{
				if ( auto * verifyTask = qobject_cast< QuickVerifyTask * > ( taskManager_->GetTask( getID() ) ) )
				{
					file_struct_.setDevice( device );
					file_struct_.sector_count = device->getSize();
				}


				ui_.startButton->setEnabled(true);
			}
			else
			{
				msgBox_->setText("<B> Device isn't detected.</B>");
				msgBox_->setInformativeText("");
				msgBox_->setStandardButtons(QMessageBox::Ok);
				msgBox_->setIcon(QMessageBox::Information);
				msgBox_->show();

				ui_.startButton->setEnabled(false);
			}
		}
		void task_error( int )
		{

		}
		void BadSector( const qlonglong sector )
		{
			AppendLogText(QString("Sector : ") + QString::number( sector ) + QString(" unable to read."));
		}
private:
	void add_devices()
	{
		for ( auto iDevice = 0 ; iDevice < disk_master_->target_count() ; ++iDevice )
		{
			auto device = disk_master_->getTarget( iDevice );
			ui_.deviceWidget->add_data( displayName( device ) , identifyIcon( device ) );
		}
	}
private:
	Ui::EraseWidget ui_;
	DMTool::DMTaskManager * taskManager_;
	DiskMasterDevice * disk_master_;
	TestFileStruct file_struct_;
	QMessageBox * msgBox_;
};

#endif // ERASETASK_H
