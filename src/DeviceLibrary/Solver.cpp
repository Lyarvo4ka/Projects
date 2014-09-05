#include "StdAfx.h"
#include "Solver.h"
#include "Queue.h"
#include "Writer.h"
#include "Buffer.h"
#include "Log.h"
#include "Error.h"

/************************************************************************/
/*                          CTaskSubject						        */
/************************************************************************/
CTaskSubject::CTaskSubject()
{
	m_pErrorObserver = NULL;
	m_pEndObserver = NULL;
}
CTaskSubject::~CTaskSubject()
{
	if (m_pErrorObserver != NULL)
	{
		delete m_pErrorObserver;
		m_pErrorObserver = NULL;
	}
	if (m_pEndObserver != NULL)
	{
		delete m_pEndObserver;
		m_pEndObserver = NULL;
	}
}
void CTaskSubject::ErrorNotify()
{
	if (m_pErrorObserver != NULL)
		m_pErrorObserver->Update(this);
}
void CTaskSubject::EndNotify()
{
	if (m_pEndObserver != NULL)
		m_pEndObserver->Update(this);
}
void CTaskSubject::SetErrorObserver(Observer * _pObserver)
{
	m_pErrorObserver = _pObserver;
}
void CTaskSubject::SetEndObserver(Observer * _pObserver)
{
	m_pEndObserver = _pObserver;
}

/************************************************************************/
/*                          IAbstractTask                               */
/************************************************************************/
IAbstractTask::IAbstractTask()
{
	m_dwResult = 0;
}
IAbstractTask::~IAbstractTask()
{

}
//void IAbstractTask::toFinish()
//{
//
//}
DWORD IAbstractTask::GetResult() const
{
	return m_dwResult;
}
const char * IAbstractTask::GetErrorString() const
{
	return m_sError.c_str();
}
/************************************************************************/
/*                             CTaskManager                             */
/************************************************************************/
CTaskManager::CTaskManager()
	: m_pQueue(NULL)
	, m_pAllocator (0)
	, m_CopiedSectors(0)
	, m_BadSectors(0)
	, m_bForceExit(false)
{
	m_pQueue = NULL;
	m_pAllocator = NULL;
	m_CopiedSectors = 0;
}
CTaskManager::CTaskManager(IQueue * _pQueue, CAllocator *_pAllocator)
	: m_pQueue(_pQueue)
	, m_pAllocator(_pAllocator)
	, m_CopiedSectors(0) 
	, m_BadSectors(0)
	, m_bForceExit(false)
{
}
CTaskManager::~CTaskManager()
{
	RemoveAll();
	if (m_pQueue != NULL)
	{
		delete m_pQueue;
		m_pQueue = NULL;
	}
	if (m_pAllocator != NULL)
	{
		delete m_pAllocator;
		m_pAllocator = NULL;
	}
}
void CTaskManager::SetQueue(IQueue * _pQueue)
{
	m_pQueue = _pQueue;
}
void CTaskManager::SetAllocator(CAllocator *_pAllocator)
{
	m_pAllocator = _pAllocator;
}
DWORD CTaskManager::StartThread()
{
	this->Execute(NULL);
	return this->GetResult();
}
void CTaskManager::Add(IAbstractTask *_pAbstractTast)
{
	if (_pAbstractTast != NULL)
		m_Tasklist.push_back(_pAbstractTast);
}
void CTaskManager::RemoveAll()
{
	CCommunicateLock *pComunicate = CCommunicateLock::GetInstance();
	pComunicate->Abort();

	//HANDLE *hEventQueue = m_pQueue->GetEmptyEvent();
	//while (true)
	//{
	//	CBuffer * pBuffer = m_pQueue->GetFromQueue();
	//	if (pBuffer == NULL)
	//	{
	//		::WaitForSingleObject(*hEventQueue,INFINITE);
	//		if (pBuffer != NULL)
	//		{
	//			if (pBuffer->GetSize() == 0)
	//				break;
	//		}
	//	}
	//	if (pBuffer->GetSize() == 0)
	//		break;
	//	m_pAllocator->RemoveBuffer(pBuffer);
	//}

	ClearQueue();
	list<IAbstractTask*>::iterator it = m_Tasklist.begin();
	IAbstractTask * pAbstractTast;
	while (it != m_Tasklist.end())
	{
		pAbstractTast = (*it);
		pAbstractTast->Join();
		delete pAbstractTast;
		pAbstractTast = NULL;
		it = m_Tasklist.erase(it);
		if (it == m_Tasklist.end())
			break;
	}
}
void CTaskManager::Execute(CBuffer * _pBuffer)
{
	list<IAbstractTask*>::iterator it;
	IAbstractTask * pAbstractTast;
	CBuffer * pBuffer = NULL;
	DWORD dwBufferSize = 0;
	m_CopiedSectors = 0;
	m_BadSectors = 0;
	DWORD WaitResult = 0;
	CCommunicateLock *pComunicate = CCommunicateLock::GetInstance();
	HANDLE *hEventQueue = m_pQueue->GetEmptyEvent();
	while (true)
	{
		WaitResult = pComunicate->LOCK();
		if ( WaitResult == CCommunicateLock::waitResume )
		{
			pBuffer = m_pQueue->GetFromQueue();
			if (pBuffer == NULL)
			{
				::WaitForSingleObject(*hEventQueue,INFINITE);
			}

			if (pBuffer != NULL)
			{
				if ( (dwBufferSize = pBuffer->GetSize()) == 0)
				{
				
					CLog *pLog = CLog::GetInstance();
					string sNewLine = "\r\n";
					pLog->WriteLog(sNewLine);

					for (it = m_Tasklist.begin(); it != m_Tasklist.end(); ++ it)
						(*it)->toFinish();

					m_pAllocator->RemoveBuffer(pBuffer);
					RemoveAll();
					break; 	// Exit...
				}
				
				for (it = m_Tasklist.begin(); it != m_Tasklist.end(); ++ it)
				{
					pAbstractTast = (*it);
					pAbstractTast->Execute(pBuffer);
					m_dwResult = pAbstractTast->GetResult();
					if (m_dwResult != 0)
					{
						// if Error Exit..
						m_sError = "Error";
						if (m_dwResult != ErrorNumber)
						{
							string sError(Errors::GetErrorMessage(m_dwResult));
							m_sError = "\r\n" + sError;
							//m_sError.append(sError);
						}
						else
							m_sError = pAbstractTast->GetErrorString();

						this->ErrorNotify();
						m_pAllocator->RemoveBuffer(pBuffer);
						RemoveAll();
						this->EndNotify();						
						return;		// Exit...
					}
				}

				m_CopiedSectors += dwBufferSize;
				if ( pBuffer->isHasBadSector())
				{
					m_BadSectors += pBuffer->GetBadSectors()->size();
				}
				m_pAllocator->RemoveBuffer(pBuffer);
				this->Notify();
			}
		}
		else
			if (WaitResult == CCommunicateLock::waitAbort)
			{
				//ClearQueue();
				break;
			}
	}
	RemoveAll();
	// Send Finish
	this->EndNotify();

	m_dwResult = 0;

}
IAbstractTask * CTaskManager::GetComposite()
{
	return this;
}
BOOL CTaskManager::isReady()
{
	list<IAbstractTask*>::iterator it;
	IAbstractTask * pAbstractTast;
	//string sErrorString;
	if (m_Tasklist.size() == 0)
	{
		m_sError = "Task is not added";
		return FALSE;
	}
	for (it = m_Tasklist.begin(); it != m_Tasklist.end(); ++it)
	{
		pAbstractTast = (*it);
		if (!pAbstractTast->isReady())
		{
			m_sError = pAbstractTast->GetErrorString();
			return FALSE;
		}
	}
#ifdef _DEBUG
	if (m_pQueue == NULL)
	{
		m_sError = "Parameter is not correct (Queue == NULL)";
		return FALSE;
	}
	if (m_pAllocator == NULL)
	{
		m_sError = "Parameter is not correct (Allocator == NULL)";
		return FALSE;
	}
#endif
	return TRUE;
}
void CTaskManager::toFinish()
{

}
void CTaskManager::SetForceExit(bool bExit)
{
	m_bForceExit = bExit;
}
bool CTaskManager::GetForceExit()
{
	return m_bForceExit;
}

const LONGLONG * CTaskManager::GetCopiedSectors() const
{
	return &m_CopiedSectors;
}
const LONGLONG * CTaskManager::GetBadSectors() const
{
	return &m_BadSectors;
}
void CTaskManager::ClearQueue()
{
	CBuffer *pBuffer = NULL;
	if (m_pQueue != NULL)
	{
		while (true)
		{
			pBuffer = m_pQueue->GetFromQueue();
			if (pBuffer != NULL)
			{
				if (pBuffer->GetSize() == 0)
				{
					m_pAllocator->RemoveBuffer(pBuffer);
					break;
				}
				m_pAllocator->RemoveBuffer(pBuffer);
			}
			else
				break;
		}
	}

}

//ISolver::ISolver(void)
//{
//}
//
//
//ISolver::~ISolver(void)
//{
//}
//
//
////////////////////////////////////////////////
//CSolver::CSolver(void)
//{
//	//m_TaskList.clear();
//}
//
//
//CSolver::~CSolver(void)
//{
//}
//
//void CSolver::Add(ISolver * _pTask)
//{
//	m_TaskList.push_back(_pTask);
//}
//void CSolver::Remove(ISolver *_pTask)
//{
//	list<ISolver*>::iterator it = m_TaskList.begin();
//	ISolver *pRemoveTask = NULL;
//
//	while (it != m_TaskList.end())
//	{
//		pRemoveTask = *it;
//		if (pRemoveTask == _pTask)
//		{
//			delete pRemoveTask;
//			it = m_TaskList.erase(it);
//			break;
//		}
//		++it;
//	}
//}
//ISolver * CSolver::GetComposite()
//{
//	return this;
//}
//void CSolver::Execute()
//{
//
//}
