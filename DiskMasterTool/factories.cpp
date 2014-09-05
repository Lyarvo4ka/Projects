#include "factories.h"

#include "copytask.h"
#include "verifytask.h"
#include "erasetask.h"


void Factories::ConnectSignal_Slot( AbstractTask * sender , QObject * recivier )
{
	QObject::connect ( sender, SIGNAL(new_device( const DM::PORT * )), recivier, SLOT(DeviceDetected(const DM::PORT *)) );
	QObject::connect ( sender, SIGNAL(disk_removed( const DM::PORT * )), recivier, SLOT( DeviceDisconencted( const DM::PORT * ) ) );
	QObject::connect ( sender, SIGNAL(update_lba( const qlonglong)), recivier, SLOT(current_lba( const qlonglong)) );
	QObject::connect ( sender, SIGNAL( finish_task( const qlonglong ) ), recivier, SLOT( task_finished( const qlonglong )) );
	QObject::connect ( sender, SIGNAL( break_task(const qlonglong) ), recivier, SLOT( task_breaked(const qlonglong) ) );
	QObject::connect ( sender, SIGNAL( finish_detect() ), recivier, SLOT( detect_finished() ) );
	QObject::connect ( sender, SIGNAL( not_detected(const DM::PORT *, int) ), recivier, SLOT( DeviceNotDetected(const DM::PORT *, int) ) );
	QObject::connect ( sender, SIGNAL( error_task( int ) ), recivier, SLOT( task_error( int ) ) );
	QObject::connect ( sender, SIGNAL( bad_sector( const qlonglong ) ), recivier, SLOT( BadSector( const qlonglong ) ) );
	QObject::connect ( sender, SIGNAL( finished () ), recivier, SLOT( thread_finished() ) ) ;
}
void Factories::ConnectForDetect( AbstractTask * sender , QObject * recivier )
{
	QObject::connect ( sender, SIGNAL( finish_detect() ), recivier, SLOT( detect_finished() ) );
}

DMTool::DM_TASK Factories::taskFromItem( int ItemStatus )
{
	switch ( ItemStatus )
	{
	case DMTool::COPYING:
		return DMTool::DM_COPY_TASK;
	case DMTool::VERIFYING:
		return DMTool::DM_VERIFY_TASK;
	case DMTool::EARASING:
		return DMTool::DM_ERASE_TASK;
	}
	return DMTool::UNKNOWN_TASK;
}
DMTool::DM_TASK_TYPE Factories::taskIDFromTask( AbstractTask * abstract_task)
{
	if ( auto smart_copy_task = qobject_cast< SmartCopyTask *> (abstract_task ) )
		return DMTool::DM_SMART_COPY_TASK;
	if ( auto quick_copy_task = qobject_cast< QuickCopyTask *> (abstract_task ) )
		return DMTool::DM_QUICK_COPY_TASK;
	if ( auto verify_task = qobject_cast < QuickVerifyTask * > ( abstract_task ) )
		return DMTool::DM_QUICK_ERASE_TASK;
	if ( auto verify_task = qobject_cast < QuickVerifyTask * > ( abstract_task ) )
		return DMTool::DM_QUICK_VERIFY_TASK;

	return DMTool::UNKNOWN_TASK_TYPE;
}

AbstractTask * Factories::QuickCopyFactory::CreateTask( const DWORD id ,  QObject * parent )
{
	QuickCopyTask * abstract_copy = new QuickCopyTask(id,parent);
	if ( parent )
		ConnectSignal_Slot(abstract_copy,parent);

	return abstract_copy;
}

AbstractTask * Factories::SmartCopyFactory::CreateTask( const DWORD id ,  QObject * parent )
{
	auto * abstract_copy = new SmartCopyTask(id,parent);
	ConnectSignal_Slot(abstract_copy,parent);

	return abstract_copy;
}

AbstractTask * Factories::QuickVerifyFactory::CreateTask( const DWORD id  , QObject * parent ) 
{
	auto * abstract_verify = new QuickVerifyTask(id,parent);
	ConnectSignal_Slot(abstract_verify,parent);

	return abstract_verify;
}

AbstractTask * Factories::QuickEraseFactory::CreateTask( const DWORD id  , QObject * parent ) 
{
	auto * abstract_verify = new QuickEraseTask(id,parent);
	ConnectSignal_Slot(abstract_verify,parent);

	return abstract_verify;
}

Factories::FactoryManager::FactoryManager()
{

}

Factories::FactoryManager::~FactoryManager()
{
	qDebug("Destructor [\'Factories\']");
}

void Factories::FactoryManager::Register( DWORD task_id )
{
	auto Iter = mapFactory_.find( task_id );
	if ( Iter == mapFactory_.end() )
	{
		TaskFactory * task_factory = nullptr;
		switch ( task_id )
		{
		case DMTool::DM_QUICK_COPY_TASK:
			task_factory = new QuickCopyFactory();
			break;
		case DMTool::DM_SMART_COPY_TASK :
			task_factory = new SmartCopyFactory();
			break;
		case DMTool::DM_QUICK_VERIFY_TASK: 
			task_factory = new QuickVerifyFactory();
			break;
		case DMTool::DM_QUICK_ERASE_TASK: 
			task_factory = new QuickEraseFactory();
			break;
		default:
			task_factory = nullptr;
		}

		if ( task_factory )
			mapFactory_.insert( std::make_pair(  task_id, TaskFactoryPtr(task_factory) ) );
	}
}

BaseTabWidget * Factories::CopyWidgetFactory::CreateTaskWidget( DWORD id , QWidget * parent )
{
	return new CopyTabWidget( id , parent );
}

BaseTabWidget * Factories::VerifyWidgetFactory::CreateTaskWidget( DWORD id , QWidget * parent )
{
	return new VerifyTabWidget( id , parent );
}

BaseTabWidget * Factories::EraseWidgetFactory::CreateTaskWidget( DWORD id , QWidget * parent )
{
	return new EraseTabWidget( id , parent );
}

void Factories::WigetFactoryManager::Register( DWORD task_id )
{
	auto Iter = mapFactory_.find( task_id );
	if ( Iter == mapFactory_.end() )
	{
		TaskWidgetFactory * task_factory = nullptr;
		switch ( task_id )
		{
		case DMTool::DM_COPY_TASK :
			task_factory = new CopyWidgetFactory();
			break;
		case DMTool::DM_VERIFY_TASK :
			task_factory = new VerifyWidgetFactory();
			break;
		case DMTool::DM_ERASE_TASK :
			task_factory = new EraseWidgetFactory();
			break;
		default :
			task_factory = nullptr;

		}

		if ( task_factory )
			mapFactory_.insert( std::make_pair( task_id, unique_ptr<TaskWidgetFactory>(task_factory ) ) );
	}

}