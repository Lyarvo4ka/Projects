#include "taskmanager.h"

//#include "copytask.h"

DMTool::DMTaskManager * DMTool::DMTaskManager::instance_ = nullptr;
//DMTool::FileManager * DMTool::FileManager::instance_ = nullptr;
//GlobalLocker * GlobalLocker::inctance_ = nullptr;
//AbstractTask * DMTaskManager::CreateTask( QWidget * baseWidget , const DiskMasterPtr & disk_master )
//{
//	QWriteLocker locker(lock_);
//
//	if ( CopyTabWidget * pCopyTab = dynamic_cast<CopyTabWidget *> ( baseWidget ) )
//	{
//		QuickCopyTask * pCopyTask = new QuickCopyTask(disk_master , pCopyTab);
//		return pCopyTask;
//	}
//}
