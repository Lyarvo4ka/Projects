#ifndef TABWIDGETS_H
#define TABWIDGETS_H

 #include <QWidget>
 #include <QTimer>
 #include <QComboBox>
 #include <QMessageBox>

#include "ui_VerifyWidgetUi.h"
#include "DiskMasterLib\dm_device.h"
#include "abstract_task.h"
#include "factories.h"
#include "Functions.h"
#include "State.h"
#include "taskmanager.h"


class DMItemIdex;


class AbstractTaskCreator
{
public:
	AbstractTaskCreator()
	{

	}
	virtual ~AbstractTaskCreator() 
	{

	}

	virtual AbstractTask * CreateTask( DWORD task_id ) = 0;
	virtual AbstractTask * OpenTask( const QString & fileName ) = 0;
	virtual void CloseTask( ) = 0;	
};

class BaseTabWidget 
	: public QWidget
	, public AbstractTaskCreator
{
	Q_OBJECT
public:
	BaseTabWidget( QWidget *parent )
		: QWidget(parent)
		, stateManager_ ( new StateManager)
		, id_ ( Unknown_ID )
	{

	}

	virtual ~BaseTabWidget()
	{
		if ( !stateManager_ )
		{
			delete stateManager_;
			stateManager_ = nullptr;
		}
	}


	virtual bool isEqual( DWORD id , DMTool::DM_TASK ) = 0;
	virtual QString getTabName() const = 0;
	virtual void StartTask() = 0;
	virtual void AbortTask() = 0;

	virtual void setProgress( int ) = 0;

	virtual void setEnableAllView( bool bEnable ) = 0;
	virtual void InsertLogText(const QString & logText) = 0;
	virtual void AppendLogText(const QString & logText) = 0;
	virtual void UpdateDeviceFromPort( const DM::PORT * port) = 0;
	virtual DiskDevicePtr getDiskFromPort( const DM::PORT * port) = 0;
	StateManager * getStateManager() 
	{
		return stateManager_;
	}
	virtual void ChangeStartButton( const QString & text , const QIcon & incon ) = 0;

	void setID( DWORD id )
	{
		id_ = id;
	}
	DWORD getID() const
	{
		return id_;
	}
protected slots:
	void start_clicked()
	{
		auto prevState = stateManager_->getState();
		assert ( prevState != nullptr );
		if ( prevState->PerfomState(this) )
		{
			ProgramState * program_state = nullptr;
			switch ( prevState->getTaskState() )
			{
			case NotStartedTask : 
				program_state = PauseState::getState();
				break;
			case RunningTask :
				program_state = PauseState::getState();
				break;
			case PausedTask : 
				program_state = RunningState::getState();
				break;
			default:
				program_state = nullptr;
			}

			stateManager_->ChangeState(program_state);
			stateManager_->getState()->UpdateButton(this);
		}
	}
	void cancel_clicked()
	{
		auto prevState = stateManager_->getState();
		if ( prevState->getTaskState() == PausedTask )
		{
			prevState->PerfomState(this);
			stateManager_->ChangeState( RunningState::getState() );
			stateManager_->getState()->UpdateButton(this);
		}
	}
	void exit_clicked()
	{
		this->CloseTask();
		emit removeMe( this );
	}
	void DeviceDetected(const DM::PORT * port)
	{
		UpdateDeviceFromPort(port);
		if ( auto disk_device = getDiskFromPort(port) )
		{
			QString logString( QString(disk_device->getPort()->name ) + QString("- was detected!") );
			AppendLogText(logString);

			logString = getDeviceInfoText( disk_device );
			AppendLogText(logString);
		}
	}
	void DeviceDisconencted( const DM::PORT * port )
	{
		if ( auto disk_device = getDiskFromPort(port) )
		{
			QString logString ( QString(disk_device->getPort()->name ) + QString(" - was deleted.") ) ;
			AppendLogText( logString );
			UpdateDeviceFromPort(port);
		}
	}
	void FinishDetected()
	{
		setEnableAllView(true);
	}
	void DeviceNotDetected(const DM::PORT * port)
	{
		QString logString(QString(port->name) + QString::fromLocal8Bit("- не определен!") );
		AppendLogText(logString);
	}
	void DeviceNotDetected(const DM::PORT * port, int error_number)
	{
		AppendLogText( QString(port->name) + QString::fromLocal8Bit("- не определен!") );
		UpdateDeviceFromPort(port);
		setEnableAllView(true);
	}
signals:
	void progressUpdated();
	void closedTask();
	void removeMe( QWidget * );
	void changeItem( DWORD , DWORD , DWORD );
	void change_progress( DWORD , int );
private:
	StateManager *stateManager_;
	DWORD id_;
};


inline AbstractTask * PrepereTask(QWidget * widget , DWORD task_id )
{
	if ( auto base_widget = qobject_cast < BaseTabWidget * > ( widget ) )
	{
		auto task_manager = DMTool::DMTaskManager::GetTaskManager();
		auto abstract_task =  task_manager->GetTask(base_widget->getID());
		if ( abstract_task )
		{
			DWORD prev_id = Factories::taskIDFromTask(abstract_task);
			if ( prev_id != task_id )
			{
				DMTool::DMTaskManager::GetTaskManager()->RemoveTask(base_widget->getID() );
				abstract_task = nullptr;
			}
		}
		if ( !abstract_task )
		{
			abstract_task = base_widget->CreateTask(task_id);
			DMTool::DMTaskManager::GetTaskManager()->AddTask( base_widget->getID() , abstract_task );
		}
		return abstract_task;
	}
	return nullptr;
};

#include <QFile>
class TaskLog
{
public:
	TaskLog( const QString & fileName)
		: logFile_(fileName)
		, bOpen_( false )
		, file_path_(fileName)
	{
	}
	~TaskLog()
	{
		CloseLog();
	}
	void ChangeLogFile( const QString & logFileName)
	{
		logFile_.setFileName(logFileName);
		file_path_ = logFileName;
	}

	bool OpenLog( const QString & file_name )
	{
		ChangeLogFile(file_name);
		file_path_ = file_name;
		bOpen_ = logFile_.open(QIODevice::ReadWrite | QIODevice::Text);
		return bOpen_;
	}
	bool OpenLog( )
	{

		return bOpen_;
	}
	bool isOpen() const
	{
		return bOpen_;
	}
	void CloseLog()
	{
		logFile_.close();
		bOpen_ = false;
	}
	bool inserntText(const QString & text)
	{
		if ( !OpenLog() )
			return false;

		bool bResult = ( logFile_.write( text.toLocal8Bit() ) != -1 ) ? true : false;

		CloseLog();
		return bResult;
	}
	bool appendText(const QString & text)
	{
		if ( !OpenLog() )
			return false;

		bool bResult = ( logFile_.write(text.toLocal8Bit() + "\r\n") != -1 ) ? true : false;

		CloseLog();
		return bResult;
	}
private:
	QFile logFile_;
	bool bOpen_;
	QString file_path_;
};





#endif // TABWIDGETS_H
