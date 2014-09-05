#pragma once
// warning C4251: needs to have dll-interface to be used by clients of class
#pragma warning(disable : 4251)

#include "Imports.h"
#include "Concurrent.h"
#include <list>
using std::list;
#include <string>
using std::string;
using std::wstring;
class IQueue;
class CAllocator;
class CBuffer;

const DWORD ErrorNumber = (DWORD) (ULONG_MAX - 1);
///////////////////// CTaskSubject /////////////////////
class DllExport CTaskSubject
	: public CSubject
{
protected:
	CTaskSubject();
	virtual ~CTaskSubject();
public:
	virtual void ErrorNotify();
	virtual void EndNotify();
	void SetErrorObserver(Observer * _pObserver);
	void SetEndObserver(Observer * _pObserver);
private:
	Observer * m_pErrorObserver;
	Observer * m_pEndObserver;
};

///////////////////// IAbstractTask /////////////////////
class DllExport IAbstractTask
	: public CThread
{
public:
	IAbstractTask();
	virtual ~IAbstractTask() = 0;
	virtual IAbstractTask * GetComposite() = 0;
	virtual void Execute(CBuffer * _pBuffer) = 0;
	virtual BOOL isReady() = 0;
	virtual void toFinish() = 0;
	const char * GetErrorString() const;
	DWORD GetResult() const;
protected:
	DWORD m_dwResult;
	string m_sError;
};

///////////////////// CTaskManager /////////////////////
class DllExport CTaskManager
	: public IAbstractTask, public CTaskSubject 
{
public:
	CTaskManager();
	CTaskManager(IQueue * _pQueue, CAllocator *_pAllocator);
	~CTaskManager();
	void SetQueue(IQueue * _pQueue);
	void SetAllocator(CAllocator *_pAllocator);
	virtual void Add(IAbstractTask *_pAbstractTast);
	virtual void RemoveAll();
	virtual void Execute(CBuffer * _pBuffer);
	virtual IAbstractTask * GetComposite();
	virtual BOOL isReady();
	virtual void toFinish();
	void SetForceExit(bool bExit = true);
	bool GetForceExit();
	const LONGLONG * GetCopiedSectors() const;
	const LONGLONG * GetBadSectors() const;
protected:
	virtual DWORD StartThread();
private:
	bool m_bForceExit;
	void ClearQueue();
	list<IAbstractTask*> m_Tasklist;
	IQueue *m_pQueue;
	CAllocator * m_pAllocator;
	LONGLONG m_CopiedSectors;
	LONGLONG m_BadSectors;
};

