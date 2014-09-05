#include "State.h"

#include "copytask.h"
#include "verifytask.h"
#include "erasetask.h"

////////////////////////////////////	NewTaskState	//////////////////////////////////////
void NewTaskState::UpdateButton( QWidget * widget )
{
	if ( auto base_widget = qobject_cast< BaseTabWidget *> ( widget ) )
	{
		base_widget->ChangeStartButton("Старт",QIcon("icons\\start_task.png"));
	}
}

bool NewTaskState::PerfomState( QWidget * widget )
{
	// start copy from current sector. 
	if ( auto base_widget = qobject_cast< BaseTabWidget *>( widget ) )
	{
		auto task_id = Factories::taskIDFromTask( DMTool::DMTaskManager::GetTaskManager()->GetTask(base_widget->getID()) );

		if ( auto copy_widget = qobject_cast < CopyTabWidget * > ( base_widget ) )
		{
			auto task_struct = copy_widget->getTaskStruct();
			//if ( task_struct.copy_mode == DMTool::PARTITION_COPY )
			//{
			//	if ( task_struct.partition_count > 0 )
			//	{
			//		auto pPartition = task_struct.partitionArray_;
			//		while ( pPartition < task_struct.partitionArray_ + task_struct.partition_count )
			//		{
			//			if (pPartition->bChecked )
			//			{
			//				task_struct.source_offset = pPartition->offset;
			//				task_struct.target_offset = pPartition->offset;
			//				task_struct.sectors_count = pPartition->count;
			//			}
			//			++pPartition;
			//		}
			//	}
			//}
			return ExecuteCopyTask( widget , task_id , task_struct.source_offset , task_struct.target_offset ,  task_struct.sectors_count );
		}
		else
		if ( auto verify_widget = qobject_cast < VerifyTabWidget * > ( base_widget ) )
		{
			auto task_struct = verify_widget->getTaskStruct();
			return ExecuteVerifyTask( widget , task_id , task_struct->offset , task_struct->sector_count );
		}
		if ( auto erase_widget = qobject_cast < EraseTabWidget * > ( base_widget ) )
		{
			auto task_struct = erase_widget->getTaskStruct();
			return ExecuteEraseTask( widget , task_id , task_struct->offset , task_struct->sector_count, erase_widget->getPattern() );
		}
	}
	return false;
}

enTaskState NewTaskState::getTaskState() const 
{
	return NotStartedTask;
}

////////////////////////////////////	RunningState	//////////////////////////////////////
void RunningState::UpdateButton( QWidget * widget )
{
	if ( auto base_widget = qobject_cast< BaseTabWidget *> ( widget ) )
	{

		base_widget->ChangeStartButton("Continue",QIcon("icons\\start_task.png"));
	}
}

bool RunningState::PerfomState( QWidget * widget )
{
	if ( auto base_widget = qobject_cast< BaseTabWidget *>( widget ) )
	{
		auto task_id = Factories::taskIDFromTask( DMTool::DMTaskManager::GetTaskManager()->GetTask( base_widget->getID()) );

		if ( auto copy_widget = qobject_cast < CopyTabWidget * > ( base_widget ) )
		{
			auto task_struct = copy_widget->getTaskStruct();


			qlonglong source_offset = task_struct.source_offset;
			qlonglong target_offset = task_struct.target_offset;
			qlonglong sector_count = task_struct.sectors_count;

			if ( task_struct.min_lba >= task_struct.max_lba )
				return false;

			//source_offset = 263952;
			//target_offset = 263952;
			//sector_count -= 263952;

			//source_offset = task_struct.min_lba;
			//target_offset = ( qlonglong ) ( task_struct.min_lba + task_struct.target_distance );
			//sector_count = ( qlonglong ) ( task_struct.max_lba - task_struct.min_lba );

			return ExecuteCopyTask( widget , task_id , source_offset , target_offset ,  sector_count );
		}
		else
		if ( auto verify_widget = qobject_cast < VerifyTabWidget *> ( base_widget ) )
		{
			auto task_struct = verify_widget->getTaskStruct();
			auto task_id = Factories::taskIDFromTask( DMTool::DMTaskManager::GetTaskManager()->GetTask(verify_widget->getID()) );
			return ExecuteVerifyTask( widget , task_id , task_struct->offset , task_struct->sector_count );
		}
		else
		if ( auto erase_widget = qobject_cast < EraseTabWidget *> ( base_widget ) )
		{
			auto task_struct = erase_widget->getTaskStruct();
			auto task_id = Factories::taskIDFromTask( DMTool::DMTaskManager::GetTaskManager()->GetTask(erase_widget->getID()) );
			return ExecuteEraseTask( widget , task_id , task_struct->offset , task_struct->sector_count , erase_widget->getPattern() );
		}
	}
	return false;
}

////////////////////////////////////	PauseState	//////////////////////////////////////
void PauseState::UpdateButton( QWidget * widget )
{
	if ( auto base_widget = qobject_cast< BaseTabWidget *> ( widget ) )
	{
		base_widget->ChangeStartButton("Pause",QIcon("icons\\pause.png"));
	}
}

bool PauseState::PerfomState( QWidget * widget )
{
	if ( auto base_widget = qobject_cast< BaseTabWidget *>( widget ) )
	{
		if ( auto copy_widget = qobject_cast< CopyTabWidget * > ( widget ) )
		{
			copy_widget->stopTimer();
		}
		if ( auto task = DMTool::DMTaskManager::GetTaskManager()->GetTask( base_widget->getID() ) )
		{
			task->PauseTask();
			return true;
		}
	}
	return false;
}

////////////////////////////////////	FinishState	//////////////////////////////////////
void FinishState::UpdateButton( QWidget * widget )
{
	if ( auto base_widget = qobject_cast< BaseTabWidget *> ( widget ) )
	{
		base_widget->ChangeStartButton("Start",QIcon("icons\\start_task.png"));
		base_widget->setEnableAllView(false);
	}
}

////////////////////////////////////	ExitState	//////////////////////////////////////
void ExitState::UpdateButton( QWidget * widget )
{
	if ( auto base_widget = qobject_cast< BaseTabWidget *> ( widget ) )
	{
		base_widget->ChangeStartButton("Start",QIcon("icons\\start_task.png"));
		base_widget->setEnableAllView(false);
	}
}

bool ExitState::PerfomState( QWidget * widget )
{
	if ( auto base_widget = qobject_cast< BaseTabWidget *> ( widget ) )
		if ( auto task_manager = DMTool::DMTaskManager::GetTaskManager() )
		{
			if ( auto current_task = task_manager->GetTask( base_widget->getID() ) )
			{
				current_task->AbortTask();
				return true;
			}
		}
		return false;
}


//////////////////////////////////////	Functions	////////////////////////////////////
bool ExecuteCopyTask( QWidget * widget , DWORD task_id , qlonglong source_offset , qlonglong target_offset , qlonglong sector_count )
{
	if ( auto copy_widget = qobject_cast < CopyTabWidget * > ( widget ) )
	{
		copy_widget->startTimer();
		if ( auto abstract_task = PrepereTask( widget , task_id ) )
		{
			auto source_device = copy_widget->getSourceDevice();
			auto target_device = copy_widget->getTargetDevice();
			TaskFileStruct & task_struct = copy_widget->getTaskStruct();
			task_struct.task_id = task_id;


			task_struct.current_task.SrcOffset = source_offset;
			task_struct.current_task.DstOffset = target_offset;
			task_struct.current_task.SectorCount = sector_count;


			DataRange data_range ( source_offset , target_offset , sector_count );


			if ( auto quick_copy_task = qobject_cast< QuickCopyTask *> ( abstract_task ) )
			{
				quick_copy_task->setSectorModel( copy_widget->getModel() );
//				quick_copy_task->change_direction( (TaskDirection)DM_Settings::getSettings()->getCopySettings(copy_widget->getID()).direction_ );
				//quick_copy_task->setJumpSize( DM_Settings::getSettings()->getCopySettings(copy_widget->getID()).jump_size_ );
				//quick_copy_task->setCurrentSector(current_sector);
			}

			abstract_task->StartTaskEx(source_device->getPort() , target_device->getPort(), data_range, 0);
			copy_widget->setEnableAllView(false);
			return true;
		}
	}
	return false;
}

bool ExecuteVerifyTask( QWidget * widget , DWORD task_id , qlonglong offset , qlonglong sector_count )
{
	if ( auto verify_widget = qobject_cast < VerifyTabWidget * > ( widget ) )
	{
		auto abstract_task =  PrepereTask( widget , task_id );
		assert( abstract_task != nullptr );

		auto task_struct = verify_widget->getTaskStruct();
		task_struct->offset = offset;
		task_struct->sector_count = sector_count;
	
		DataRange data_range ( offset , offset , sector_count );
		auto device = verify_widget->getCurrentDevice();
		abstract_task->StartTaskEx( device->getPort() , device->getPort() , data_range, 0);
		verify_widget->setEnableAllView(false);
		return true;
	}
	return false;
}
bool ExecuteEraseTask( QWidget * widget , DWORD task_id , qlonglong offset , qlonglong sector_count , DWORD erase_pattern )
{
	if ( auto erase_widget = qobject_cast < EraseTabWidget * > ( widget ) )
	{
		auto abstract_task =  PrepereTask( widget , task_id );
		assert( abstract_task != nullptr );

		auto task_struct = erase_widget->getTaskStruct();
		task_struct->offset = offset;
		task_struct->sector_count = sector_count;

		DataRange data_range ( offset , offset , sector_count );
		auto device = erase_widget->getCurrentDevice();
		if ( auto erase_task = qobject_cast < QuickEraseTask * > ( abstract_task ) )
			erase_task->setPattern( erase_pattern );
		abstract_task->StartTaskEx( device->getPort() , device->getPort() , data_range, 0);
		erase_widget->setEnableAllView(false);
		return true;
	}
	return false;
}

bool StartQuickCopy( QWidget * widget , qlonglong source_offset , qlonglong target_offset , qlonglong sector_count )
{
	return ExecuteCopyTask( widget , DMTool::DM_QUICK_COPY_TASK , source_offset, target_offset , sector_count );
}

bool StartSmartCopy( QWidget * widget , qlonglong source_offset , qlonglong target_offset , qlonglong sector_count )
{
	return ExecuteCopyTask(widget , DMTool::DM_SMART_COPY_TASK , source_offset  , target_offset , sector_count );
}
//
//bool ShowCopyTaskDialog( QWidget * widget, int DisableButton /*= tError_task */ )
//{
//	StartTaskDialog dialog;
//	if ( DisableButton == tContinue_task)
//		dialog.setEnableContinueButton( false );
//	if ( dialog.exec() == QDialog::Accepted )
//	{
//		auto copy_widget = qobject_cast < CopyTabWidget * > ( widget ) ;
//		auto curr_task = DMTool::DMTaskManager::GetTaskManager()->GetTask( copy_widget->getID() );
//		auto task_id = Factories::taskIDFromTask(curr_task);
//		auto task_struct = copy_widget->getTaskStruct();
//		qlonglong total_sectors = 0;
//
//		//qlonglong source_offset = 0;
//		//qlonglong target_offset = 0;
//		//qlonglong sector_count = 0;
//		//source_offset = task_struct.min_lba;
//		//target_offset = qlonglong( task_struct.min_lba + task_struct.target_distance );
//		//sector_count = qlonglong( task_struct.max_lba - task_struct.min_lba );
//
//		//switch ( dialog.getCommand() )
//		//{
//		//	// 2. If continue.
//		//case tContinue_task:
//		//	if ( task_struct.min_lba >= task_struct.max_lba )
//		//		return false;
//
//		//	return 	StartQuickCopy( widget , source_offset , target_offset , sector_count );
//
//		//	// 3. Read unread sectors.
//		//case tReadUnRead_task:
//		//	if ( DM_Settings::getSettings()->getCopySettings( copy_widget->getID() ).direction_ == ForwardTask )
//		//	{
//		//		if ( task_struct.source_offset < task_struct.min_lba )
//		//		{
//
//		//			return StartSmartCopy( widget , source_offset ,qlonglong( task_struct.min_lba -  task_struct.source_offset ) );
//		//		}
//		//	}
//		//	else 
//		//	{
//		//		if ( task_struct.sectors_count > task_struct.max_lba)
//		//			return StartSmartCopy( widget , task_struct.max_lba , task_struct.sectors_count - task_struct.max_lba );
//		//	}
//
//		//	return false;
//
//		//	// 4. Read bad sectors only;
//		//case tReadBads_task:
//		//	// not implemented
//		//	return true;
//
//		//}
//	}
//	return false;
//}
