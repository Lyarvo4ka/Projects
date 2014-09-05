#pragma once
#include <string>
using std::string;
#include <windows.h>

namespace DMTool 
{
	static const DWORD INVALID_VALUE = 0xFFFFFFFF;
	static const int DefaultJumpSize = 10;

	enum DM_TASK
	{
		DM_COPY_TASK = 0,
		DM_VERIFY_TASK,
		DM_ERASE_TASK,

		UNKNOWN_TASK = INVALID_VALUE
	};

	enum DM_TASK_TYPE 
	{
		DM_QUICK_COPY_TASK = 0 , 
		DM_QUICK_VERIFY_TASK , 
		DM_QUICK_ERASE_TASK , 
		DM_SMART_COPY_TASK ,

		UNKNOWN_TASK_TYPE = INVALID_VALUE
	};

	enum TASK_STATE 
	{
		NOT_STARTED = 0, 
		STARTED, 
		COMPLETED, 
		SUSPENDED, 
		ABORTED
	};

	enum TASK_STATUS 
	{
		NOT_READY = 0, 
		READY , 
		COPYING , 
		VERIFYING, 
		EARASING
	};

	enum COPY_TYPE 
	{ 
		FULL_COPY = 0 , 
		PARTITION_COPY , 
		USER_COPY 
	};

	enum DIRECTION 
	{ 
		FORWARD_TASK = 0 , 
		BACKWARD_TASK 
	};
}	// end namespace

	enum dm_device 
	{ 
		dm_source_device = 0, 
		dm_target_device 
	};

const enum ErasePattern 
{ 
	dm_erase_00 , 
	dm_erase_FF , 
	dm_erase_rand
};
enum TaskDirection
{
	ForwardTask , 
	BackwardTask
};

const DWORD UnknownErasePattern = 0xFFFFFFFF;

//namespace disk_types
//{
const enum dm_disk_type { disk_usb = 0, disk_sata};
const string disk_UsbName = "USB";
const string disk_SataName = "SATA";
const string unknown_PortName = "Unknown port name";

const DWORD Unknown_Port = 0xFFFFFFFF;
const DWORD Unknown_ID = 0xFFFFFFFF;

const WORD SECTOR_SIZE = 512;

static const DWORD MinSectorsCount = 128;
static const DWORD MaxSectorsCount = MinSectorsCount*1024;	// 32 * 1024
static const int DefaultReadSectors = MaxSectorsCount;

static const int DM_BLOCK_SIZE = 256;

//}	// end disk_types

