#pragma once
// warning C4251: needs to have dll-interface to be used by clients of class
#pragma warning(disable : 4251)

#include "Imports.h"

#include <queue>
using std::queue;

class CBuffer;

class DllExport IQueue
{
public:
	IQueue(void);
	virtual ~IQueue(void);
	virtual void AddToQueue(CBuffer *) = 0;
	virtual CBuffer * GetFromQueue() = 0;
	virtual HANDLE * GetEmptyEvent() = 0;
};

class DllExport CQueue :
	public IQueue
{
public:
	CQueue(void);
	virtual ~CQueue(void);
	void AddToQueue(CBuffer *);
	CBuffer * GetFromQueue();
	HANDLE * GetEmptyEvent();
private:
	HANDLE m_hMonitor;
	HANDLE *m_hEventFree;
	queue<CBuffer *> m_Queue;
};

