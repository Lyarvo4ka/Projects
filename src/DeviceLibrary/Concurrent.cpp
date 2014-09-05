#include "StdAfx.h"
#include "Concurrent.h"


/************************************************************************/
/*                        CThread                                       */
/************************************************************************/
CThread::CThread()
{
	m_hThread = INVALID_HANDLE_VALUE;
}
CThread::~CThread()
{
	if (m_hThread != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hThread);
		m_hThread = INVALID_HANDLE_VALUE;
	}
}
void CThread::Run()
{
	m_hThread = CreateThread(NULL,0,
		( LPTHREAD_START_ROUTINE ) ThreadFunc,
		(LPVOID)this,
		NULL,0);
}
//void CThread::Suspend()
//{
//
//}
//void CThread::Abort()
//{
//
//}
void CThread::Join()
{
	if (m_hThread != INVALID_HANDLE_VALUE)
	{
		WaitForSingleObject(m_hThread,INFINITE);
	}
}
DWORD WINAPI CThread::ThreadFunc(LPVOID lParam)
{
	CThread *pThread = (CThread*)lParam;
	return pThread->StartThread();
}

/************************************************************************/
/*                          Observer                                    */
/************************************************************************/
Observer::Observer()
{

}
Observer::~Observer()
{

}

/************************************************************************/
/*                          CSubject						            */
/************************************************************************/
CSubject::CSubject()
{

}
CSubject::~CSubject()
{
	list<Observer*>::iterator it;
	it = m_ObserversList.begin();
	while (it != m_ObserversList.end())
	{
		Observer *pObserver = *it;
		delete pObserver;
		++it;
	}
	m_ObserversList.clear();


}
void CSubject::Attach(Observer * _pObserver)
{
	m_ObserversList.push_back(_pObserver);
}
void CSubject::Detach(Observer * _pObserver)
{
	list<Observer*>::iterator it = m_ObserversList.begin();
	while (it != m_ObserversList.end())
	{
		if (*it == _pObserver)
		{
			m_ObserversList.erase(it);
			break;
		}
	}
}
void CSubject::Notify()
{
	list<Observer*>::iterator it = m_ObserversList.begin();
	while (it != m_ObserversList.end())
	{
		(*it)->Update(this);
		++it;
	}
}

/************************************************************************/
/*                       CCommunicateLock							    */
/************************************************************************/
#define ToUnLock TRUE
#define ToLock FALSE
//CCommunicateLock * CCommunicateLock::m_pCommunicate = NULL;
CCommunicateLock * CCommunicateLock::m_pInstance = NULL;
#define LOCK_COUNT 2

CCommunicateLock::CCommunicateLock()
{
	m_hComunicateLock = new HANDLE[LOCK_COUNT];
	m_hComunicateLock[waitResume] = CreateEvent(NULL,TRUE,ToUnLock,L"Resume");
	m_hComunicateLock[waitAbort] = CreateEvent(NULL,TRUE,ToLock,L"Break");
}
CCommunicateLock::~CCommunicateLock()
{
	CloseHandle(m_hComunicateLock[waitResume]);
	CloseHandle(m_hComunicateLock[waitAbort]);
	delete m_hComunicateLock;
}

//void CCommunicateLock::Release()
//{
//	delete this;
//}
//CCommunicateLock * CCommunicateLock::GetCommunicate()
//{
//	if (m_pCommunicate == NULL)
//		m_pCommunicate = new CCommunicateLock();
//	return m_pCommunicate;
//}
HANDLE * CCommunicateLock::GetHANDLE()
{
	return m_hComunicateLock;
}
void CCommunicateLock::Suspend()
{
	if (m_hComunicateLock != NULL)
	{
		::ResetEvent(m_hComunicateLock[waitResume]);
	}
}	
void CCommunicateLock::Abort()
{
	Suspend();
	if (m_hComunicateLock != NULL)
	{
		::SetEvent(m_hComunicateLock[waitAbort]);
	}
}
void CCommunicateLock::Resume()
{
	if (m_hComunicateLock != NULL)
	{
		::SetEvent(m_hComunicateLock[waitResume]);
	}
}

DWORD CCommunicateLock::LOCK()
{
	return ::WaitForMultipleObjects(LOCK_COUNT,m_hComunicateLock,FALSE,INFINITE);
}
