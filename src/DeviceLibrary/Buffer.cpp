#include "StdAfx.h"
#include "Buffer.h"

CBuffer::CBuffer(const DWORD & _rBufferSize)
	:	m_iSize(_rBufferSize)
	,	m_iLBA(0)
	,	m_iDiskNumber(0)
	,	m_bHasBadSector(FALSE)
{
	m_pBuffer = new BYTE[_rBufferSize];
}
CBuffer::~CBuffer(void)
{
	delete m_pBuffer;
	m_pBuffer = NULL;
}
void CBuffer::SetPosition(const LONGLONG & _rPosition)
{
	m_iLBA = _rPosition;
}
LONGLONG CBuffer::GetPosition() const
{
	return m_iLBA;
}
void CBuffer::SetDiskNumber(const DWORD & _rDiskNumber)
{
	m_iDiskNumber = _rDiskNumber;
}
DWORD CBuffer::GetDiskNumber() const
{
	return m_iDiskNumber;
}
void CBuffer::SetSize(DWORD _Size)
{
	m_iSize = _Size;
}
DWORD CBuffer::GetSize() const
{
	return m_iSize;
}
BYTE * CBuffer::GetBuffer() const
{
	return m_pBuffer;
}
void CBuffer::AddBadSector(const LONGLONG & _rBadSector)
{
	m_BadSectorList.push_back(_rBadSector);
	if (m_bHasBadSector != TRUE)
		m_bHasBadSector = TRUE;
}
BOOL CBuffer::isHasBadSector() const
{
	return m_bHasBadSector;
}
const vector<LONGLONG> * CBuffer::GetBadSectors() const
{
	return &m_BadSectorList;
}

void CBuffer::Clear()
{
	m_bHasBadSector = FALSE;
	if (!m_BadSectorList.empty())
		m_BadSectorList.clear();
}


CAllocator::CAllocator(DWORD _iBufferSize, UINT _iSizeFree)
	:m_TBlockSize(_iBufferSize),m_iSize(0),m_iSizeFree(_iSizeFree)
{
	m_hLockSize = CreateEvent(NULL,TRUE,TRUE,L"Event if More Size");
	m_hUsedLock = CreateMutex(NULL,FALSE,L"MAX used Buffers");
}

CAllocator::~CAllocator()
{
	list<CBuffer*>::iterator it = m_FreeList.begin();
	while (it != m_FreeList.end())
	{
		CBuffer *pBuffer = *it;
		delete pBuffer;
		++it;
	}

	m_FreeList.clear();

	CloseHandle(m_hLockSize);
	CloseHandle(m_hUsedLock);
}

CBuffer *CAllocator::GetBuffer()
{
	CBuffer *pBuffer = NULL;

	// if in ListFree is Present CBuffer then return this pointer 
	// and remove from list

	::WaitForSingleObject(m_hUsedLock,INFINITE);
	if (m_iSize >= m_iSizeFree)
	{	
		::ReleaseMutex(m_hUsedLock);
		::WaitForSingleObject(m_hLockSize,INFINITE);

		::WaitForSingleObject(m_hUsedLock,INFINITE);
	}
	IncBufferCount();
	if (m_iSize >= m_iSizeFree)
		::ResetEvent(m_hLockSize);
	if (!m_FreeList.empty() )
	{
		pBuffer = *m_FreeList.begin();
		m_FreeList.pop_front();

	}
	else
	{
		pBuffer = new CBuffer(m_TBlockSize);
	}
	::ReleaseMutex(m_hUsedLock);

	return pBuffer;

}


void CAllocator::RemoveBuffer(CBuffer *_pBuffer)
{
	//if (_pBuffer == NULL)
	//	TRACE(_T("Error Remove Buffer it is NULL"));


	::WaitForSingleObject(m_hUsedLock,INFINITE);
	//::EnterCriticalSection(csFreeAccess);
	//if (m_iSize == 0)
	//	TRACE(_T("Error Buffers Count Don't equal 0"));

	::InterlockedDecrement(&m_iSize);

	if (m_FreeList.size() <= m_iSizeFree)
	{
		// Clear Buffer Data need.
		_pBuffer->Clear();
		m_FreeList.push_back(_pBuffer);
	}
	else
	{
		delete _pBuffer;

	}
	//::LeaveCriticalSection(csFreeAccess);

	if (m_iSize < m_iSizeFree )
		::SetEvent(m_hLockSize);

	::ReleaseMutex(m_hUsedLock);
}

void CAllocator::setBuffersCount(UINT _iBuffersCount)
{
	m_iSize = _iBuffersCount;
}

void CAllocator::IncBufferCount()
{
	::InterlockedIncrement(&m_iSize);
}