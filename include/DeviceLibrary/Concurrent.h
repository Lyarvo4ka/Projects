#pragma once
#include "Imports.h"
//warning C4661 : no suitable definition provided for explicit template instantiation request
#pragma warning(disable : 4661)
//warning C4356: static data member cannot be initialized via derived class
#pragma warning(disable : 4356)
// warning C4251: needs to have dll-interface to be used by clients of class
#pragma warning(disable : 4251)
///////////////////// IThread /////////////////////
//interface IThread
//{
//	virtual void Run() = 0;
//	virtual void Suspend() = 0;
//	virtual void Abort() = 0;
//	virtual void Join() = 0;
//};

#include <list>
using std::list;

#include "windows.h"

///////////////////// CThread /////////////////////
class DllExport CThread
	//: public IThread
{
public:
	CThread();
	virtual ~CThread() = 0;
	virtual void Run();
	//virtual void Suspend();
	//virtual void Abort();
	virtual void Join();
protected:
	virtual DWORD StartThread() = 0;
private:
	static DWORD WINAPI ThreadFunc(LPVOID lParam);
	HANDLE m_hThread;
};


///////////////////// Observer /////////////////////
class CSubject;
class DllExport Observer
{
public:
	virtual ~Observer();
	virtual void Update(CSubject *_pSubject) = 0;
protected:
	Observer();
};


///////////////////// CSubject /////////////////////
class DllExport CSubject
{
public:
	virtual ~CSubject();
	virtual void Attach(Observer * _pObserver);
	virtual void Detach(Observer * _pObserver);
	virtual void Notify();
protected:
	CSubject();
private:
	list<Observer*> m_ObserversList;
	DWORD state_;
};


///////////////////// CSingleton /////////////////////
template <class T>
class CSingleton
{
protected:
	CSingleton(){};
	virtual ~CSingleton(){};
	void operator = (const CSingleton &){};
public:
	static T * GetInstance(){
		if (m_pInstance == NULL)
			m_pInstance = new T();
		return m_pInstance;
	};
	void Release(){
		delete m_pInstance;
		m_pInstance = NULL;
	};
private:
	static T * m_pInstance;
};


///////////////////// CCommunicateLock /////////////////////
class CCommunicateLock;
typedef CSingleton<CCommunicateLock> TCommunicateLock;

class DllExport CCommunicateLock
	: public TCommunicateLock
{
public:
	//static CCommunicateLock * GetCommunicate();
	static enum WaitResult{waitResume = (WAIT_OBJECT_0 + 0), waitAbort = (WAIT_OBJECT_0  + 1)};
	HANDLE * GetHANDLE();
	//void Release();
	void Suspend();
	void Abort();
	void Resume();
	DWORD LOCK();
protected:
	CCommunicateLock();
	~CCommunicateLock();
private:
	//static CCommunicateLock * m_pCommunicate;
	friend class CSingleton<CCommunicateLock>;
	HANDLE *m_hComunicateLock;
};
