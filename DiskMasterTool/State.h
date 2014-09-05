#pragma once

#include <QWidget>
#include "abstract_task.h"

class ProgramState
{
public:
	virtual void UpdateButton( QWidget * ) = 0;
	virtual bool PerfomState( QWidget * )  = 0;
	virtual enTaskState getTaskState() const = 0 ;
};

class NewTaskState
	: public ProgramState
{
public:
	static ProgramState * getState()
	{
		static NewTaskState instance_;
		return &instance_;
	}
	void UpdateButton( QWidget * widget);
	bool PerfomState( QWidget * widget ) override;
	enTaskState getTaskState() const override;
private:
	NewTaskState()
	{

	}
	NewTaskState( const NewTaskState & );
	~NewTaskState()
	{

	}
};

class RunningState
	: public ProgramState
{
public:
	static ProgramState * getState()
	{
		static RunningState instance_; 
		return &instance_;
	}
	void UpdateButton( QWidget * widget);
	bool PerfomState( QWidget * widget ) override;
	enTaskState getTaskState() const override
	{
		return RunningTask;
	}
private:
	RunningState()
	{

	}
	RunningState( const RunningState & );
	~RunningState()
	{

	}
};

class PauseState
	: public ProgramState
{
public:
	static ProgramState * getState()
	{
		static PauseState instance_;
		return &instance_;
	}
	void UpdateButton( QWidget * widget);
	bool PerfomState( QWidget * widget ) override;
	enTaskState getTaskState() const override
	{
		return PausedTask;
	}
private:
	PauseState()
	{

	}
	PauseState( const PauseState & );
	~PauseState()
	{

	}
};

class FinishState
	: public ProgramState
{
public:
	static ProgramState * getState()
	{
		static FinishState inctance_;
		return &inctance_;
	}
	void UpdateButton( QWidget * widget ) override;
	bool PerfomState( QWidget * widget) 
	{
		//return ShowCopyTaskDialog( widget , tContinue_task );
		return false;
	}
	enTaskState getTaskState() const 
	{
		return FinishTask;
	}
private:
	FinishState()
	{

	}
	FinishState( const FinishState & );
	~FinishState()
	{

	}

};

class ExitState
	: public ProgramState
{
public:
	static ProgramState * getState()
	{
		static ExitState inctance_;
		return &inctance_;
	}
	void UpdateButton( QWidget * widget ) override;
	bool PerfomState( QWidget * widget);
	enTaskState getTaskState() const 
	{
		return ExitTask;
	}
private:
	ExitState()
	{

	}
	ExitState( const ExitState & );
	~ExitState()
	{

	}

};

class StateManager		/*Contex*/
{
public:
	StateManager()
		: state_ ( nullptr )
	{

	}
	void UpdateButton( QWidget * widget ) 
	{
		state_->UpdateButton( widget );
	}
	ProgramState * getState() const
	{
		return state_;
	}
//protected:
	void ChangeState( ProgramState * next_state )
	{
		if ( state_ != next_state)
			state_ = next_state;
	}
private:
	ProgramState * state_;
	//friend class CopyTabWidget;
};



//////////////////////////////////////////////////////////   Copy Task   ///////////////////////////////////////////////////////////////////////////////
bool ExecuteCopyTask( QWidget * widget , DWORD task_id , qlonglong source_offset , qlonglong target_offset , qlonglong sector_count );
bool ExecuteVerifyTask( QWidget * widget , DWORD task_id , qlonglong offset , qlonglong sector_count );
bool ExecuteEraseTask( QWidget * widget , DWORD task_id , qlonglong offset , qlonglong sector_count , DWORD erase_pattern = 0 );
bool StartQuickCopy( QWidget * widget , qlonglong source_offset  , qlonglong target_offset ,  qlonglong sector_count );
bool StartSmartCopy( QWidget * widget , qlonglong source_offset  , qlonglong target_offset ,  qlonglong sector_count );
//static bool ShowCopyTaskDialog( QWidget * widget,  int DisableButton = 0/*tError_task*/ );
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
