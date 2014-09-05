#ifndef FACTORIES_H
#define FACTORIES_H

#include "DiskMasterLib\dm_device.h"


#include <QObject>
#include <QWidget>



class AbstractTask;
class BaseTabWidget;



namespace Factories
{
	#include <map>
	#include <utility>
	using std::map;
	using std::pair;

	#include <memory>
	using std::unique_ptr;

	void ConnectSignal_Slot( AbstractTask * sender , QObject * recivier );
	void ConnectForDetect( AbstractTask * sender , QObject * recivier );

	DMTool::DM_TASK taskFromItem( int ItemStatus );
	DMTool::DM_TASK_TYPE taskIDFromTask( AbstractTask * abstract_task );

	class TaskFactory
	{
	public: 
		//TaskFactory();
		virtual ~TaskFactory() = 0
		{

		}

		virtual AbstractTask * CreateTask( const DWORD id ,  QObject * parent ) = 0;
	};

	class QuickCopyFactory
		: public TaskFactory
	{
	public:
		~QuickCopyFactory()
		{
			qDebug("Destructor [\'QuickCopyFactory\']");
		}
		AbstractTask * CreateTask( const DWORD id  , QObject * parent ) override;
	};

	class SmartCopyFactory
		: public TaskFactory
	{
		~SmartCopyFactory()
		{
			qDebug("Destructor [\'SmartCopyFactory\']");
		}
		AbstractTask * CreateTask( const DWORD id  , QObject * parent ) override;
	};

	class QuickVerifyFactory
		: public TaskFactory
	{
	public:
		~QuickVerifyFactory()
		{
			qDebug("dtor [\'QuickVerifyFactory\']");
		}
		AbstractTask * CreateTask( const DWORD id  , QObject * parent ) override;

	};

	class QuickEraseFactory
		: public TaskFactory
	{
	public:
		~QuickEraseFactory()
		{
			qDebug("dtor [\'QuickVerifyFactory\']");
		}
		AbstractTask * CreateTask( const DWORD id  , QObject * parent ) override;

	};

	class FactoryManager  
	{
		typedef map< DWORD , unique_ptr<TaskFactory> > FactoryMap;
		typedef pair< DWORD , unique_ptr<TaskFactory> > FacoryPair;
	public:
		typedef std::unique_ptr< TaskFactory > TaskFactoryPtr;
		static FactoryManager * getInstance()
		{
			static FactoryManager instance_;
			return &instance_;
		}
		void Register( DWORD task_id );
		TaskFactory * Lookup( DWORD task_id )
		{
			Register(task_id);
			auto findIter = mapFactory_.find( task_id );
			if ( findIter != mapFactory_.end() )
				return findIter->second.get();

			return nullptr;
		}
	private:
		FactoryManager();
		FactoryManager( const FactoryManager &);
		void operator = ( const FactoryManager & );
		~FactoryManager();

	private:
		FactoryMap mapFactory_;
	};

	class TaskWidgetFactory
	{
	public:
		TaskWidgetFactory()
		{
			qDebug() << "ctor TaskWidgetFactory.";
		}
		virtual ~TaskWidgetFactory() = 0
		{

		}
		virtual BaseTabWidget * CreateTaskWidget( DWORD id , QWidget * parent ) = 0;
	};

	class CopyWidgetFactory
		: public TaskWidgetFactory
	{
	public:
		~CopyWidgetFactory() /*override*/
		{
			qDebug("Destructor [\'CopyWidgetFactory\']");
		}
		BaseTabWidget * CreateTaskWidget( DWORD id , QWidget * parent ) override;
	};

	class VerifyWidgetFactory
		: public TaskWidgetFactory
	{
	public:
		~VerifyWidgetFactory() /*override*/
		{
			qDebug("Destructor [\'CopyWidgetFactory\']");
		}
		BaseTabWidget * CreateTaskWidget( DWORD id , QWidget * parent ) override;
	};

	class EraseWidgetFactory
		: public TaskWidgetFactory
	{
	public:
		~EraseWidgetFactory() /*override*/
		{
			qDebug("Destructor [\'CopyWidgetFactory\']");
		}
		BaseTabWidget * CreateTaskWidget( DWORD id , QWidget * parent ) override;
	};

	class WigetFactoryManager
	{
		typedef map< DWORD , unique_ptr<TaskWidgetFactory> > WidgetFactoryMap;
		typedef pair< DWORD , unique_ptr<TaskWidgetFactory> > WidgetFacoryPair;
	public:
		static WigetFactoryManager * getFactoryManager()
		{
			static WigetFactoryManager instance_;

			return &instance_;
		}
		TaskWidgetFactory * Lookup( DWORD task_id )
		{
			Register( task_id );
			auto findIter = mapFactory_.find( task_id );
			if ( findIter != mapFactory_.end() )
				return findIter->second.get();

			return nullptr;
		}
		void Register( DWORD task_id );
	protected:
		WigetFactoryManager()
		{

		}
		~WigetFactoryManager()
		{

		}
	private:
		WidgetFactoryMap mapFactory_;
	};


}
#endif // FACTORIES_H
