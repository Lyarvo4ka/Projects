#ifndef TASKMANAGER_H
#define TASKMANAGER_H


#include <stddef.h>     /* offsetof */

#include "abstract_task.h"

#include "dtm\Abstract.h"

 #include <QWidget>
 #include <QReadWriteLock>
 
 #include <QWriteLocker>
 #include <QReadLocker>



#include <map>
using std::map;
using std::pair;

#include <vector>
using std::vector;
#include <queue>

#include <memory>
#include <functional>

#include <algorithm>

#include "DiskMasterLib\dm_device.h"
#include "Functions.h"

#include <QMutex>
#include <QWaitCondition>

class GlobalLocker
{
public:
	static GlobalLocker * getInstance()
	{
		static GlobalLocker inctance_;
		return &inctance_;
	}

	void Wait()
	{
		mutex_.lock();
		// waiting 6 seconds..
		wait_.wait(&mutex_,6 * 1000);
		mutex_.unlock();
	}
	void WakeUp()
	{
		wait_.wakeAll();
	}

private:
	QMutex mutex_;
	QWaitCondition wait_;
};



#pragma pack( 1 )
struct CurrentTaskStruct
{
	LONGLONG SrcOffset;
	LONGLONG DstOffset;
	LONGLONG SectorCount;
	LONGLONG CurrentSector;

	CurrentTaskStruct()
		: SrcOffset ( 0 )
		, DstOffset ( 0 )
		, SectorCount ( 0 )
		, CurrentSector ( 0 )
	{

	}
	CurrentTaskStruct( LONGLONG source_offset , LONGLONG target_offset , LONGLONG sector_count , LONGLONG current_sector = 0)
		: SrcOffset ( source_offset )
		, DstOffset ( target_offset )
		, SectorCount ( sector_count )
		, CurrentSector ( current_sector )
	{

	}

	LONGLONG getSectors() const
	{
		return (SrcOffset <= DstOffset ) ? SrcOffset + SectorCount : DstOffset + SectorCount;
	}
};
#pragma pack( )

#include "partitionmodel.h"
class PartitionManager
{
protected:
	PartitionManager()
		: current_ ( nullptr )
	{

	}
	~PartitionManager()
	{

	}
public:
	static PartitionManager * getManager()
	{
		static PartitionManager instance;
		return &instance;
	}
	void add( PartitionEntry * pPartition )
	{
		auto findIter = std::find( partition_.begin() , partition_.end() , pPartition );
		if ( findIter == partition_.end() )
			partition_.push_back( pPartition );
	}
	void setCurrent( int iNumber )
	{
		if ( iNumber < partition_.size() )
			current_ = partition_.at( iNumber );
		else
			current_ = nullptr;
	}
	PartitionEntry * current() 
	{
		return current_;
	}
private:
	vector< PartitionEntry * > partition_;

	PartitionEntry * current_;
};

#pragma pack( 1 )
typedef struct _TaskFileStruct
{
	void setSource( const DiskDevicePtr & source )
	{
		source_port = source->getPort()->number;
		memcpy( source_name , source->getModel().c_str() , source->getModel().size() ); 
		source_size = source->getSize();
	}
	void setTarget( const DiskDevicePtr & target )
	{
		target_port = target->getPort()->number;
		memcpy( target_name , target->getModel().c_str() , target->getModel().size() ); 
		target_size = target->getSize();
	}
	void Initialize( )
	{
		task_id = 0;
		copy_mode = DMTool::FULL_COPY;
		current_sector = 0;
		sectors_count = 0;

		source_port = 0;
		ZeroMemory( & source_name , sizeof( source_name ) );
		source_size = 0;
		source_offset = 0;

		target_port = 0;
		ZeroMemory( & target_name , sizeof( target_name ) );
		target_size = 0;
		target_offset = 0;

		min_lba = 0;
		max_lba = 0;
		target_distance = 0;
		ZeroMemory( & current_task , sizeof( CurrentTaskStruct ) );
		current_partition_ = 0;

	}

	BYTE task_id;	// id task = copy , verify , erase
	int copy_mode;

	LONGLONG current_sector;

	DWORD source_port;
	char source_name[ 64 ];
	LONGLONG source_size;

	DWORD target_port;
	char target_name[ 64 ];
	LONGLONG target_size;

	LONGLONG source_offset;
	LONGLONG target_offset;

	LONGLONG min_lba;
	LONGLONG max_lba;

	LONGLONG target_distance;
	LONGLONG sectors_count;

	CurrentTaskStruct current_task;
	int current_partition_;

} TaskFileStruct , * PTaskFileStrcut;
#pragma pack( )

#pragma pack( 1 )
typedef struct _TestFileStruct
{
	void setDevice( const DiskDevicePtr & device )
	{
		port = device->getPort()->number;
		memcpy( name , device->getModel().c_str() , device->getModel().size() ); 
		size = device->getSize();
	}
	void Initialize( )
	{
		task_id = 0;
		current_sector = 0;
		sector_count = 0;
		port = 0;
		ZeroMemory( name , sizeof( name ) );
		offset = 0;
		size = 0 ;
	}
	BYTE task_id;
	LONGLONG current_sector;
	LONGLONG sector_count;
	DWORD port;
	char name[64];
	DWORD offset;
	LONGLONG size;
} TestFileStruct , * PTestFileStruct;
#pragma pack( )

inline bool ReadTaskFile( const QFileInfo & file_info , TaskFileStruct & taskStruct)
{
	QFile read_file(file_info.absoluteFilePath());
	if ( read_file.open(QIODevice::ReadOnly) )
	{
		auto file_size = read_file.size();
		auto byteArray = read_file.read(file_size);
		read_file.close();
		if ( file_size == byteArray.size() )
		{
			memcpy( &taskStruct , byteArray.data() , sizeof( TaskFileStruct ) );
			return true;
		}
		return false;
	}
	return false;
}

namespace DMTool
{



	typedef std::unique_ptr< DiskMasterDevice > DiskMasterPtr;
	typedef std::unique_ptr< AbstractTask > AbstractTaskPtr;
	typedef std::vector< DiskMasterPtr > DiskMasterArray;
	typedef std::queue< AbstractTaskPtr > TaskQueue;
	typedef std::map < DWORD , TaskQueue > TaskMap;
	//typedef std::pair < DWORD , AbstractTaskPtr > TaskPair;


	class isDiskMasterEqualNumber
		: public std::binary_function< DiskMasterPtr , DWORD , bool >
	{
	public:
		bool operator() ( const DiskMasterPtr & disk_master, DWORD DiskMaster_ID) const
		{
			return ( disk_master->getID() == DiskMaster_ID );
		}
	};



	class DMTaskManager 
	{
	public:
		static DMTaskManager * GetTaskManager()
		{
			//QWriteLocker locker(lock_);
			//static DMTaskManager instance_;
			if ( !instance_ )
				instance_ = new DMTaskManager;
			return instance_;
		}
		bool Insert(DM::DiskController * disk_master )
		{
			if ( ! Find(disk_master->GetID()) )
			{
				QWriteLocker locker( &lock_ );
				dm_array_.push_back( DiskMasterPtr( new DiskMasterDevice( disk_master ) ) );
				return true;
			}
			return false;
		}

		DiskMasterDevice * Find( DWORD DiskMaster_ID )  
		{
			QReadLocker locker( &lock_ );
			auto find_iter = std::find_if ( dm_array_.begin() , dm_array_.end() , std::bind2nd( isDiskMasterEqualNumber() , DiskMaster_ID ) );
			return ( find_iter != dm_array_.end() ) ? (*find_iter).get() : nullptr ;
		}

		void Remove( DWORD DiskMaster_ID )
		{
			QWriteLocker locker( &lock_ );
			auto remove_iter = std::remove_if( dm_array_.begin() , dm_array_.end() , std::bind2nd( isDiskMasterEqualNumber() , DiskMaster_ID ) );
		}
		bool ResetDiskMaster( DWORD DiskMaster_ID, QString & error_text)
		{
			if ( auto disk_master = Find(DiskMaster_ID) )
			{
				disk_master->Close();
				if ( disk_master->Open() )
				{
					return true;
				}
				else
				{
					error_text = QString::fromLocal8Bit("Couldn't open device.");

					return false;
				}
			}

			return false;
		}

		void AddTask( DWORD DiskMaster_ID, AbstractTask * task)
		{
			QWriteLocker locker( &lock_ );
			auto findIter = taskMap_.find( DiskMaster_ID );
			if ( findIter == taskMap_.end() )
			{
				taskMap_.insert(std::make_pair( DiskMaster_ID, TaskQueue() ) ).first->second.push( AbstractTaskPtr( task )) ;
			}
			else
			{
				findIter->second.push( AbstractTaskPtr( task ) );
			}
		}
		void RemoveTask( DWORD DiskMaster_ID )
		{
			//QWriteLocker locker( &lock_ );
			auto findIter = taskMap_.find( DiskMaster_ID );
			if ( findIter != taskMap_.end() )
				if ( ! findIter->second.empty() )
					findIter->second.pop();
		}
		void RemoveTasks( DWORD DiskMaster_ID )
		{
			QWriteLocker locker( &lock_ );
			taskMap_.erase( DiskMaster_ID );
		}
		AbstractTask * GetTask( DWORD DiskMaster_ID )
		{
			QReadLocker locker( &lock_ );
			auto findIter = taskMap_.find( DiskMaster_ID );
			if ( findIter != taskMap_.end() )
				if ( ! findIter->second.empty() )
					return findIter->second.front().get();

			return nullptr;
		}
		void Relese()
		{
			if ( instance_ )
			{
				delete instance_;
				instance_ = nullptr;
			}
		}
	private:
		DMTaskManager()
		{

		}
		~DMTaskManager()
		{
			qDebug() << "dtor TaskManager";
		}
		DMTaskManager(const DMTaskManager &);
		void operator = (const DMTaskManager &);
	private:
		static DMTaskManager * instance_;

		QReadWriteLock lock_;
		DiskMasterArray dm_array_;
		TaskMap taskMap_;
	};

	inline DiskMasterDevice * getDiskMaster( DWORD DiskMaster_ID )
	{
		return DMTaskManager::GetTaskManager()->Find(DiskMaster_ID);
	}

	inline DiskDevicePtr getDiskFromPort( const DM::PORT * port , DWORD device_id )
	{
		if ( auto disk_master = getDiskMaster( device_id ) )
			return disk_master->getDiskDevice(port);
		return DiskDevicePtr(nullptr);
	}

	inline void WaitingForTaskEnd( DWORD dm_id )
	{
		if ( auto task = DMTool::DMTaskManager::GetTaskManager()->GetTask(dm_id) )
		{
			task->AbortTask();	// ?????????????
			task->wait(60 * 1000 );
		}
	}

	class FileHolder
	{
	public:
		FileHolder( const QString & folder_name , const QString & task_name )
			: folder_name_ ( folder_name )
			, task_name_ ( task_name )
		{

		}
		~FileHolder()
		{
			if ( task_file_.isOpen() )
				task_file_.close();
		}
		QString getFolderName() const
		{
			return folder_name_;
		}
		QString getTaskName() const
		{
			return task_name_;
		}
		bool CreateTaskFile()
		{
			return FileSystem::Create_File( task_file_ , FileSystem::CreateFilePath(folder_name_ , task_name_ , ".tsk") );
		}
		bool OpenTaskFile()
		{
			return FileSystem::Open_File( task_file_ , FileSystem::CreateFilePath(folder_name_ , task_name_ , ".tsk") );
		}
		bool WriteTaskData( const TaskFileStruct & file_struct )
		{
			if ( task_file_.write( (const char * ) &file_struct , sizeof( TaskFileStruct ) ) == sizeof (TaskFileStruct) )
				return true;
			return false;
		}
		bool ReadTaskData ( TaskFileStruct * file_struct )
		{
			auto byteArray = task_file_.read( sizeof ( TaskFileStruct));
			if ( byteArray.size() == sizeof ( TaskFileStruct) )
			{
				memcpy( file_struct, byteArray.data() , sizeof( TaskFileStruct ) );
				return true;
			}
			return false;
		}
		void WriteCurrentSector( TaskFileStruct * file_struct )
		{
			DWORD offset = offsetof( TaskFileStruct ,  current_sector );
			task_file_.seek( offset );
			
			if ( task_file_.write( (const char * ) &file_struct->current_sector, sizeof( qlonglong ) ) != sizeof( qlonglong ) )
			{
				qDebug() << "Error to write current sector.";
				throw;
			}

			offset = offsetof( TaskFileStruct , current_task );
			offset += offsetof( CurrentTaskStruct , CurrentSector );
			task_file_.seek( offset );

			if ( task_file_.write( (const char * ) &file_struct->current_task.CurrentSector , sizeof( qlonglong ) ) != sizeof( qlonglong ) )
			{
				qDebug() << "Error to write current sector.";
				throw;
			}
		}
	private:
		QString folder_name_;
		QString task_name_;
		QFile task_file_;
	};

	class FileManager
	{
		typedef std::unique_ptr< FileHolder > FileHolderPtr;
		typedef std::map < DWORD , FileHolderPtr > FileMap;
		typedef std::pair < DWORD , FileHolderPtr> FilePair;

	public:
		static FileManager * GetFileManager()
		{
			static FileManager instance_;
			return &instance_;
		}

		static bool isExist( const QString & folder_name , const QString & taskName ) 
		{
			QDir dirPath(folder_name);
			return dirPath.exists(taskName);

		}	

		static bool MakeFolder ( QString & folder_name , const QString & taskName ) 
		{
			QDir dirPath(folder_name);
			if ( !dirPath.exists() )
			if ( !dirPath.mkpath(folder_name) )
				return false;

			if ( !dirPath.exists(taskName) )
				if ( !dirPath.mkdir(taskName) )
					return false;

			dirPath.cd(taskName);
			folder_name = QDir::toNativeSeparators( dirPath.path() );
			return true;
		}

		void CreateFileHolder( DWORD id , QString & FolderName , const QString & TaskName )
		{
			auto findIter = fileMap_.find(id);
			if ( findIter == fileMap_.end() )
			{
				fileMap_.insert( FilePair( id, FileHolderPtr( new FileHolder( FolderName, TaskName)) ) );
			}
		}
		void RemoveFileHolder( DWORD id)
		{
			fileMap_.erase( id );
		}
		FileHolder * FileHolderLockup( DWORD id )
		{
			auto findIter = fileMap_.find( id );
			if ( findIter != fileMap_.end() )
				return findIter->second.get();

			return nullptr;
		}
	protected:
		FileManager()
		{

		}
		~FileManager()
		{

		}


	private:
		FileMap fileMap_;
	};

	inline FileHolder * getFileHolder( DWORD id )
	{
		return FileManager::GetFileManager()->FileHolderLockup(id) ;
	}


}
#endif // TASKMANAGER_H
