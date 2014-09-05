#include "StdAfx.h"
#include "Queue.h"
#include "Buffer.h"

#include <windows.h>


IQueue::IQueue(void)
{

}
IQueue::~IQueue(void)
{

}

CQueue::CQueue(void)
{
	m_hMonitor = CreateMutex(NULL,FALSE,L"Mutex access Queue List");
	m_hEventFree = new HANDLE;
	*m_hEventFree = CreateEvent(NULL,TRUE,FALSE,L"Event Check List isFree");
}


CQueue::~CQueue(void)
{
	CloseHandle(m_hMonitor);
	CloseHandle(*m_hEventFree);
	if (m_hEventFree != NULL)
	{
		delete m_hEventFree;
		m_hEventFree = NULL;
	}
	while (!m_Queue.empty())
		m_Queue.pop();
}
void CQueue::AddToQueue(CBuffer * _pBuffer)
{
	::WaitForSingleObject(m_hMonitor,INFINITE);

	m_Queue.push(_pBuffer);

	::SetEvent(*m_hEventFree);

	::ReleaseMutex(m_hMonitor);
}
CBuffer * CQueue::GetFromQueue()
{
	CBuffer *pBuffer = NULL;

	::WaitForSingleObject(m_hMonitor,INFINITE);

	if (!m_Queue.empty())
	{
		pBuffer = m_Queue.front();
		m_Queue.pop();
	}
	else
		::ResetEvent(*m_hEventFree);

	::ReleaseMutex(m_hMonitor);

	return pBuffer;
}

HANDLE * CQueue::GetEmptyEvent()
{
	return m_hEventFree;
}