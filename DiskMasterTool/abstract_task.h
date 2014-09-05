#pragma once

 #include <QThread>
 #include <QWidget>

#include <vector>
using std::vector;

#include "dtm\Abstract.h"


struct DataRange
{
	DataRange()
		: SourceOffset_( 0 )
		, TargetOffset_( 0 )
		, SectorsCount_( 0 )
	{

	}
	DataRange(ULONGLONG sourceOffset,ULONGLONG targetOffset, ULONGLONG sectorsCount)
		: SourceOffset_( sourceOffset )
		, TargetOffset_( targetOffset )
		, SectorsCount_( sectorsCount )
	{

	}
	ULONGLONG SourceOffset_;
	ULONGLONG TargetOffset_;
	ULONGLONG SectorsCount_;

	void setOffset(const ULONGLONG sourceOffset, const ULONGLONG targetOffset, const ULONGLONG sectorsCount)
	{
		SourceOffset_ = sourceOffset;
		TargetOffset_ = targetOffset;
		SectorsCount_ = sectorsCount;
	}
};


static enum enTaskState
{ 
	NotStartedTask = 0 , 
	RunningTask ,
	PausedTask ,
	AbortedTask ,
	FinishTask,
	ExitTask
};


class AbstractTask
		: public QThread
{
	Q_OBJECT
public:

	AbstractTask(QObject * parent = 0)
		: QThread(parent)
	{

	}
	virtual ~AbstractTask() = 0
	{

	}
	virtual void StartTask(const DM::PORT * source_port, const DM::PORT * target_port, DWORD param) = 0;
	virtual void StartTaskEx(const DM::PORT * source_port, const DM::PORT * target_port, const DataRange block_range, DWORD param) = 0;
	virtual void AbortTask() = 0;
	virtual void PauseTask() = 0;
	virtual LONGLONG getLastSector() const = 0;
	virtual void DetectDevices( const DM::PORT * source_port, const DM::PORT * target_port , DWORD param )
	{
		DataRange block_range;
		block_range.setOffset(0 , 0 , 0);
		this->StartTaskEx(source_port , target_port , block_range , 0);

	}

signals:
	void new_device( const DM::PORT * );
	void disk_removed( const DM::PORT * );
	void not_detected( const DM::PORT * , int error_code );
	void update_lba( const qlonglong );
	void finish_task( const qlonglong );
	void break_task( const qlonglong );
	void finish_detect();
	void error_task( int );
	void bad_sector( const qlonglong );
};

class AbstractTaskObserver
	: public DM::DCObserver
{
public:
	virtual ~AbstractTaskObserver() 
	{

	}

	virtual void NewDiskDetected( void *param ) = 0;
	virtual void TaskInProgress( void *param ) = 0;
	virtual void BadSector( void *param ) = 0;
	virtual void TaskComplete( void * param ) = 0;
	virtual void TaskBreak( void *param ) = 0;
	virtual void TaskError( void *param ) = 0;
	virtual void DetectError( void *param ) = 0;
	virtual void DiskRemoved( void *param ) = 0;
};

