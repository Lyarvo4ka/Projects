#include "StdAfx.h"
#include "Buffer.h"


///////////////////////////////////////////////////////////////////////////////
// --------------- CBuffer -------------------
///////////////////////////////////////////////////////////////////////////////
CBuffer::CBuffer()
	:m_pAddess(NULL), m_iDiskNumber(0), m_LBA(0),m_iSize(0)
{

}

CBuffer::CBuffer(const DWORD & _TBufferSize)
	:m_pAddess(NULL), m_iDiskNumber(UCHAR_MAX), m_LBA(0),m_iSize(_TBufferSize)
{
	m_pAddess = new BYTE[_TBufferSize];

}

CBuffer::~CBuffer()
{
	if (m_pAddess != NULL)
		delete m_pAddess;

}

void CBuffer::setLBA(const LONGLONG &_lLBA)
{
	m_LBA = _lLBA;
}
void CBuffer::setDiskNumber(const BYTE &_DiskNumber)
{
	m_iDiskNumber = _DiskNumber;
}

void CBuffer::setSize(const DWORD _iSize)
{
	m_iSize = _iSize;
}

///////////////////////////////////////////////////////////////////////////////
// --------------- CDisksBuffers -------------------
///////////////////////////////////////////////////////////////////////////////
CDisksBuffers::CDisksBuffers(BYTE _iDiskCount)
	:m_iCounter(0)
{
	// new CBuffer[DiskCount];
	m_pArrayPointers.SetSize(_iDiskCount);

}

CDisksBuffers::~CDisksBuffers()
{
	m_pArrayPointers.RemoveAll();

}

///////////////////////////////////////////////////////////////////////////////
// --------------- CAllocator -------------------
///////////////////////////////////////////////////////////////////////////////
//CAllocator::CAllocator()
//	:m_TBlockSize(0),m_iSize(0),m_iSizeFree(0)
//{
//	csFreeAccess = new CRITICAL_SECTION;
//	::InitializeCriticalSection(csFreeAccess);
//	m_hLockSize = CreateEvent(NULL,TRUE,TRUE,_T("Event if More Size"));
//	m_hUsedLock = CreateMutex(NULL,FALSE,_T("MAX used Buffers"));
//}

CAllocator::CAllocator(DWORD _iBufferSize, UINT _iSizeFree)
	:m_TBlockSize(_iBufferSize),m_iSize(0),m_iSizeFree(_iSizeFree)
{
	m_hLockSize = CreateEvent(NULL,TRUE,TRUE,_T("Event if More Size"));
	m_hUsedLock = CreateMutex(NULL,FALSE,_T("MAX used Buffers"));
}

CAllocator::~CAllocator()
{
	while (!m_FreeList.IsEmpty())
	{
		CBuffer *pBufferDelete = m_FreeList.RemoveHead();
		delete pBufferDelete;
	}

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
	if (!m_FreeList.IsEmpty() )
	{
		pBuffer = m_FreeList.RemoveHead();
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
	if (_pBuffer == NULL)
		TRACE(_T("Error Remove Buffer it is NULL"));


	::WaitForSingleObject(m_hUsedLock,INFINITE);
	//::EnterCriticalSection(csFreeAccess);
	if (m_iSize == 0)
		TRACE(_T("Error Buffers Count Don't equal 0"));

	::InterlockedDecrement(&m_iSize);

	if (m_FreeList.GetSize() <= m_iSizeFree)
	{
		m_FreeList.AddTail(_pBuffer);
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

//void CAllocator::setToDefault(CBuffer*  _pBuffer)
//{
//	//_pBuffer->m_iDiskNumber = UCHAR_MAX;
//}


///////////////////////////////////////////////////////////////////////////////
// --------------- !!!!! -------------------
///////////////////////////////////////////////////////////////////////////////
CMapAddress::CMapAddress()
	:m_bResult(FALSE),m_iDiskCount(UCHAR_MAX),m_bFirstMismatch(FALSE)/*,m_Command(NULL)*/,m_bFirstFind(FALSE)/*,pAllocBuffer(NULL)*/
{
	//if (!fileReportTxt.Open(_T("Report.txt"),CFile::modeWrite | CFile::modeCreate))
	//		AfxMessageBox(_T("Unable to open file"),MB_OK);

	//fileReportTxt.SeekToEnd();
	m_CheckedSectors = new NotEqualSectors();
	m_CheckedSectors->lCurrent = 0;
	m_CheckedSectors->lFirst = 0;
	m_CheckedSectors->lInterval = 0;
	m_bQuickFullTest = QUICKTEST;
	m_lCounter = 0;
	m_hWaitThread = INVALID_HANDLE_VALUE;
	m_bStop = FALSE;

	m_hEventFree = CreateEvent(NULL,TRUE,FALSE,_T("Event Check List isFree"));
	hListAccess = CreateMutex(NULL,FALSE,_T("Mutex access Queue List"));
	m_pSendFindData = new FINDSENDDATA();
}

CMapAddress::~CMapAddress()
{
	// Wait for Exit Thread
	//if (hThread != INVALID_HANDLE_VALUE)
		//::WaitForSingleObject(hThread,INFINITE);
	CloseHandle(m_hEventFree);
	CloseHandle(hListAccess);

	if (!m_QueueList.IsEmpty())
	{
		while (m_QueueList.GetCount() > 0)
		{
			CBuffer *pBuffer = NULL;
			pBuffer = m_QueueList.RemoveHead();
			pAllocBuffer->RemoveBuffer(pBuffer);
		}
	}
	deleteBuffer();
	if (m_CheckedSectors != NULL)
	{
		delete m_CheckedSectors;
		m_CheckedSectors = NULL;
	}
	delete m_pSendFindData;
	m_pSendFindData = NULL;
}


/// ???????????
void CMapAddress::addToQueueList(CBuffer* _pBuffer)
{
	::WaitForSingleObject(hListAccess,INFINITE);

	m_QueueList.AddTail(_pBuffer);
	::SetEvent(m_hEventFree);

	::ReleaseMutex(hListAccess);
}

CBuffer * CMapAddress::GetFromQueueList()
{
	// wait when queue list is not free
	// remove from queue list 

	CBuffer *pBuffer = NULL;

	::WaitForSingleObject(hListAccess,INFINITE);

	if (!m_QueueList.IsEmpty())
		pBuffer = m_QueueList.RemoveHead();
	else
		::ResetEvent(m_hEventFree);

	::ReleaseMutex(hListAccess);

	return pBuffer;
}

void CMapAddress::setDiskCount(const BYTE _iDiskCount)
{
	m_iDiskCount = _iDiskCount;
}

void CMapAddress::SetAllocator(CAllocator *_pAllocator)
{
	pAllocBuffer = _pAllocator;
}

void CMapAddress::StartThreads()
{
	hThread = CreateThread(NULL,0,
						   ( LPTHREAD_START_ROUTINE )ThreadReadFunc,
						   this,
						   0,NULL);
}
void CMapAddress::ExitThreads()
{
	ExitThread(0);
}



DWORD WINAPI CMapAddress::ThreadReadFunc(LPVOID lParam)
{
	CMapAddress *pData = (CMapAddress*)lParam;
	UINT iResult = 0;
	if ( pData )
		iResult = pData->run();

	return iResult;
}

void CMapAddress::deleteBuffer()
{
	BOOL bFALSE = FALSE;
	//sendCommand(bFALSE);

	CDisksBuffers *pRemoveBuffers = NULL;
	ULONGLONG RemoveLBA = 0;
	POSITION mapPos;
	for (;mapPos = m_mapBuffer.GetStartPosition(); mapPos != NULL) 
	{
		m_mapBuffer.GetNextAssoc(mapPos,RemoveLBA,(CDisksBuffers*&)pRemoveBuffers);
		for ( int iPos = 0; iPos < m_iDiskCount; ++iPos)
		{
			if (pRemoveBuffers->m_pArrayPointers[iPos] != NULL)
				pAllocBuffer->RemoveBuffer(pRemoveBuffers->m_pArrayPointers[iPos]);
		}
		delete pRemoveBuffers;
		m_mapBuffer.RemoveKey(RemoveLBA);
	}

}

void CMapAddress::setStop()
{
	m_bStop = TRUE;
}

UINT CMapAddress::run()
{
	CDisksBuffers *pDataBuffers = NULL;
	CBuffer *pBuffer = NULL;

	//const CString strDirPath = _T("E:\\RAID\\DiskNumber");
	//
	//DWORD dwError = 0;
	//CString strPath = _T("");
	//HANDLE *hDisk = new HANDLE[m_iDiskCount];
	//for ( BYTE i = 0 ; i < m_iDiskCount ; ++i)
	//{
	//	strPath.Format(_T("%s%i"),strDirPath,i);
	//	hDisk[i] = CreateFile(strPath,GENERIC_WRITE,
	//	  					  FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,
	//						  FILE_ATTRIBUTE_NORMAL,NULL);
	//	if (hDisk[i] == INVALID_HANDLE_VALUE )
	//	{
	//				dwError = GetLastError();
	//				::AfxMessageBox(_T("Error Create File"),MB_OK);
	//		
	//	}
	//}

	//DWORD dwBytesWrite = 0;

	LONGLONG lCounter = 0;
	m_bStop = FALSE;
	BYTE iDiskFinish = 0;
	DWORD dwWaitResult = 0;
	while (true)
	{
		if ( m_bStop == TRUE)
		{
			deleteBuffer();
			break;
		}	
		dwWaitResult = ::WaitForMultipleObjects(2,m_pThreadLock,FALSE,INFINITE);
		if ( dwWaitResult == (WAIT_OBJECT_0  + 1) )		// Abort Thread
			break;


		while (	(pBuffer = GetFromQueueList()) == NULL)
		{
		::WaitForSingleObject(m_hEventFree,INFINITE);
		}


	if (pBuffer->m_iSize == NULL)
		if (++iDiskFinish == m_iDiskCount)
		{
			deleteBuffer();
			break;
		}
		else
			continue;

	pDataBuffers = NULL;
	m_bResult = m_mapBuffer.Lookup(pBuffer->m_LBA,pDataBuffers);
	if (m_bResult)
	{
		pDataBuffers->m_pArrayPointers.SetAt(pBuffer->m_iDiskNumber,pBuffer) ;
		pDataBuffers->m_iCounter++;
		if (pDataBuffers->m_iCounter == m_iDiskCount)
		{
			pDataBuffers->m_pArrayPointers.GetAt(pBuffer->m_iDiskNumber);
			m_mapBuffer.RemoveKey(pBuffer->m_LBA);
			m_bStop = ProcessingBuffer( pDataBuffers );
		}
	}
	else
	{
		pDataBuffers = new CDisksBuffers(m_iDiskCount);
		pDataBuffers->m_pArrayPointers.SetAt(pBuffer->m_iDiskNumber,pBuffer) ;
		pDataBuffers->m_iCounter++;
		m_mapBuffer.SetAt(pBuffer->m_LBA,pDataBuffers);
	}

	//////////////////////////////////////////
		//++lCounter;
	}

	//fileReportTxt.Close();
	//::AfxMessageBox(_T("FINISH CHECK"),MB_OK);

//		???????????????????
	//
	//::SendMessageA(hParityWindow,WM_FINISH_PARITY_CHECK,0,0);
	//::SendMessageA(hMainWindow,WM_FINISH_PARITY_CHECK,0,0);
	//::SendMessageA(hMainWindow,WM_FINISH_GATHER_BY_JPG,0,0);
		//delete hDisk;
	TRACE("Finish MAP ...\r\n");
	return 0;
}

void CMapAddress::setSelectedDrives(vector<CDiskDrive> & _vecDrives)
{
	//m_SelectedDrives = _vecDrives;
}


#define SSIZE 512*256
void CMapAddress::setTest(BOOL _bQuickFullTest)
{
	m_bQuickFullTest = _bQuickFullTest;
}

void CMapAddress::setTestData(LONGLONG _lTestData)
{
	m_lProgress = _lTestData;
	m_lProgress /= PROGRESS_COUNT;
	if (m_bQuickFullTest == FULLTEST)
		m_lProgress /= DEFAULT_SECTORS_SIZE;

	if (m_lProgress == 0 )
		m_lProgress = 1;
	m_lCounter = 0;
}

//const WORD cwJPGSignature = 0xFFD8;

BOOL CMapAddress::ProcessingBuffer(CDisksBuffers* _pDiskBuffers)
{
	CString strFormat = _T("");

	register DWORD *pdwParity = NULL;
	register DWORD *pdwTemp = NULL;

	DWORD *l32BitBuffer = NULL;
	DWORD *l32BitBufferNext = NULL;

// DEBUG
	//DWORD dwChekArr[256*128];
	//LONGLONG curLBA = _pDiskBuffers->m_pArrayPointers[0]->m_LBA;
	//HANDLE hFiles[3];

	//if (curLBA == 8388607)
	//{

	//hFiles[0] = CreateFile(_T("E:\\WORK\\TestXor\\Disk2.par"),
	//						GENERIC_WRITE, FILE_SHARE_WRITE,
	//						NULL,
	//						CREATE_ALWAYS,
	//						NULL,0);
	//if ( hFiles[0] == INVALID_HANDLE_VALUE )
	//{
	//	DWORD dwError = GetLastError();
	//	TRACE(_T("Error Open File Disk3.par"));
	//}

	//hFiles[1] = CreateFile(_T("E:\\WORK\\TestXor\\Disk3.par"),
	//					GENERIC_WRITE,FILE_SHARE_WRITE,
	//					NULL,
	//					CREATE_ALWAYS,
	//					NULL,0);
	//if ( hFiles[1] == INVALID_HANDLE_VALUE )
	//{
	//	DWORD dwError = GetLastError();
	//	TRACE(_T("Error Open File Disk3.par"));
	//}

	//hFiles[2] = CreateFile(_T("E:\\WORK\\TestXor\\Disk4.par"),
	//					GENERIC_WRITE, FILE_SHARE_WRITE,
	//					NULL,
	//					CREATE_ALWAYS,
	//					NULL,0);
	//if ( hFiles[2] == INVALID_HANDLE_VALUE )
	//{
	//	DWORD dwError = GetLastError();
	//	TRACE(_T("Error Open File Disk3.par"));
	//}

	//DWORD dwBytesWrite = 0;


	//WriteFile(hFiles[0],_pDiskBuffers->m_pArrayPointers[0]->m_pAddess,_pDiskBuffers->m_pArrayPointers[0]->m_iSize,&dwBytesWrite,NULL);
	//WriteFile(hFiles[1],_pDiskBuffers->m_pArrayPointers[1]->m_pAddess,_pDiskBuffers->m_pArrayPointers[1]->m_iSize,&dwBytesWrite,NULL);
	//WriteFile(hFiles[2],_pDiskBuffers->m_pArrayPointers[2]->m_pAddess,_pDiskBuffers->m_pArrayPointers[2]->m_iSize,&dwBytesWrite,NULL);

	//for (BYTE b = 0; b < m_iDiskCount; ++b)
	//	CloseHandle(hFiles[b]);

	//	memcpy(dwChekArr,pdwParity,256*128);
	//	int k = 90;
	//}

// END DEBUG

	if (_pDiskBuffers != NULL)
	{
		DWORD iCounts  = _pDiskBuffers->m_pArrayPointers[0]->m_iSize / sizeof (long);
		DWORD loop = 0 ;
		for (BYTE iDisk = 1; iDisk < m_iDiskCount; ++iDisk)
		{
			loop = 0 ;
			pdwParity = (DWORD *) _pDiskBuffers->m_pArrayPointers[0]->m_pAddess;
			pdwTemp = (DWORD *) _pDiskBuffers->m_pArrayPointers[iDisk]->m_pAddess;
			while ( loop  < iCounts)
			{
				*pdwParity ^= *pdwTemp;
				++pdwTemp;
				++pdwParity;
				++loop;
			}
		}

		DWORD dwStep = 512 / sizeof(long);
		DWORD dwLBACount = iCounts / dwStep;

		LONGLONG lLBAPos = 0;
		pdwParity  = (DWORD *) _pDiskBuffers->m_pArrayPointers[0]->m_pAddess;

		DWORD dwWaitResult = 0;

		LONGLONG lFirstPos = 0;
		BOOL bSend = FALSE;

		//m_lStartLBA = 0;
		//m_lCurrentLBA = 0;
		//m_CheckedSectors->lCurrent = 0;
		//m_CheckedSectors->lFirst = 0;
		//m_CheckedSectors->lInterval = 0;

		lFirstPos = _pDiskBuffers->m_pArrayPointers[0]->m_LBA;
		if ( lFirstPos > 0 )
		{
			--lFirstPos ;
			if (lFirstPos != m_CheckedSectors->lCurrent)
				sendCommand(bSend);
		}
		if (dwLBACount > 0 )
		{
			for (int i = 0 ; i < dwLBACount; ++i)
			{
				bSend = FALSE;
				for (int j = 0 ; j < dwStep; ++j)
				{
					lLBAPos = i*dwStep + j;
					if (pdwParity[lLBAPos] != 0 )	// ????????
					{
						bSend = TRUE;
						break;
					}
				} // end sector 512
				m_CheckedSectors->lCurrent =  i + _pDiskBuffers->m_pArrayPointers[0]->m_LBA;
				sendCommand(bSend/*,lFirstPos*/);

				if ( m_bStop == TRUE)
					break;

				if (bSend == TRUE)
				if (m_bFirstMismatch)
				{
					LONGLONG *lLBAposition = new LONGLONG;
					*lLBAposition = m_CheckedSectors->lCurrent;
					SendMessageA(hMainWindow,WM_SET_PAUSE,0,0);
					SendMessageA(hMainWindow,WM_SHOW_MISSHATCH,0,(LPARAM)lLBAposition);

				dwWaitResult = ::WaitForMultipleObjects(2,m_pThreadLock,FALSE,INFINITE);

				if ( dwWaitResult == (WAIT_OBJECT_0  + 1) )		// Abort Thread
				{
					for (BYTE iDisk = 0; iDisk < m_iDiskCount; ++iDisk)
						pAllocBuffer->RemoveBuffer(_pDiskBuffers->m_pArrayPointers[iDisk]);
					delete _pDiskBuffers;
					return TRUE;
				}
				else
					if( dwWaitResult == (WAIT_OBJECT_0 + 0) )	// Resume Thread
					delete lLBAposition;
				}

			}
		}

		// ????????????????????
		for (BYTE iDisk = 0; iDisk < m_iDiskCount; ++iDisk)
		{
			pAllocBuffer->RemoveBuffer(_pDiskBuffers->m_pArrayPointers[iDisk]);
		}

		delete _pDiskBuffers;
		// Finish Check Block

		sendUpdateProgress();
	

	}
	else
	{
		TRACE(_T("(ProcessingBuffer) Error it is NULL"));		
	}
	return FALSE;
}

void CMapAddress::setToFirstMissmatch(BOOL _bMissmatch)
{
	m_bFirstMismatch = _bMissmatch;
}

void CMapAddress::setWaitThread(HANDLE _hWaitThread)
{
	m_hWaitThread = _hWaitThread;
}
//void CMapAddress::setCommand(CCommand * _command)
//{
//	m_Command = _command;
//}

void CMapAddress::sendCommand(BOOL & _XorResult/*, LONGLONG & _lLBA*/)
{
	if ( _XorResult == TRUE )
	{
		if (m_bFirstFind == FALSE)
		{
			m_CheckedSectors->lFirst = m_CheckedSectors->lCurrent;
			m_bFirstFind = TRUE;
			++m_CheckedSectors->lInterval;
			::SendMessageA(hMainWindow,WM_PARITY_CHECK_NOT_EQUAL_FIRST,(WPARAM)0,(LPARAM)m_CheckedSectors);
		}
		else
		{
			++m_CheckedSectors->lInterval;
			m_CheckedSectors->lLast = m_CheckedSectors->lCurrent;
		}
	}
	else
	{
		if ( (m_bFirstFind == TRUE) )
		{
			//if (m_CheckedSectors->lInterval > 1)
				::SendMessageA(hMainWindow,WM_PARITY_CHECK_NOT_EQUAL_LAST,(WPARAM)0,(LPARAM)m_CheckedSectors);
			m_bFirstFind = FALSE;
			m_CheckedSectors->lInterval = 0;
		}
	}
}

void CMapAddress::sendUpdateProgress()
{
	++m_lCounter;
	if (m_lProgress == m_lCounter)
	{
		m_lCounter = 0;
		::SendMessageA(hMainWindow,WM_UPDATE_PARITY_CHECK_PROGRESS,0,0);
	}
}

void CMapAddress::setComunicateHandle(HANDLE *_hHandles)
{
	m_pThreadLock = _hHandles;
}

void CMapAddress::SuspendREADThreads()
{
	::ResetEvent(m_pThreadLock[0]);	
}
void CMapAddress::ResumeREADThreads()
{
	::SetEvent(m_pThreadLock[0]);
}

void CMapAddress::AbortREADThreads()
{
	SuspendREADThreads();
	::SetEvent(m_pThreadLock[1]);
}
void CMapAddress::setSingleton(CSingletonJPGs *_pSingleton)
{
	m_pSingletonJpg = _pSingleton;
}


#define CUT_SECTORS_NUMBER 2000
BOOL CMapForJPG::ProcessingBuffer(CDisksBuffers * _pDiskBuffers)
{
	if (_pDiskBuffers != NULL)
	{
		DWORD dwBufferSize = _pDiskBuffers->m_pArrayPointers[0]->m_iSize;
		DWORD dwSectorsCount = dwBufferSize/512;
		DWORD dwCounter = 0;
		BYTE *pBufferSign = new BYTE[3];
		LONGLONG lPos = 0;
		DWORD dwWaitResult = 0;
		BOOL bFinish = FALSE;
		//::SendMessage()
		for (BYTE iDisk = 0; iDisk < m_iDiskCount; ++iDisk)
		{
			memset(pBufferSign,0,3);
			for (dwCounter = 0; dwCounter < dwSectorsCount; ++dwCounter)
			{
				// Suspend Thread
				dwWaitResult = ::WaitForMultipleObjects(2,m_pThreadLock,FALSE,INFINITE);

				if ( dwWaitResult == (WAIT_OBJECT_0  + 1) )		// Abort Thread
				{
					for (BYTE iDisk = 0; iDisk < m_iDiskCount; ++iDisk)
						pAllocBuffer->RemoveBuffer(_pDiskBuffers->m_pArrayPointers[iDisk]);
					delete _pDiskBuffers;
					delete pBufferSign;
					return TRUE;
				}
				else
					if( dwWaitResult == (WAIT_OBJECT_0 + 0) )	// Resume Thread
				{
				BYTE *pBuffer = _pDiskBuffers->m_pArrayPointers[iDisk]->m_pAddess;
				memcpy(pBufferSign,_pDiskBuffers->m_pArrayPointers[iDisk]->m_pAddess+512*dwCounter,3);
				if (pBufferSign[0] == 0xFF && pBufferSign[1] == 0xD8 && pBufferSign[2] == 0xFF)
				{
					PRESULT_CUTTING_SECTORS pResultCutting = NULL;
					m_pSendFindData->m_iDiskNumber = iDisk;
					lPos = _pDiskBuffers->m_pArrayPointers[iDisk]->m_LBA;
					lPos += dwCounter;
					m_pSingletonJpg->Add(iDisk,lPos);

				}
				}
			}
		}
		delete pBufferSign;

		for (BYTE iDisk = 0; iDisk < m_iDiskCount; ++iDisk)
		{
			pAllocBuffer->RemoveBuffer(_pDiskBuffers->m_pArrayPointers[iDisk]);
		}

		delete _pDiskBuffers;
	}
	else
		TRACE(_T("(ProcessingBuffer) Error it is NULL"));	
	return FALSE;
}










		//DWORD * loop  = (DWORD*)_pDiskBuffers->m_pArrayPointers[0]->m_pAddess;

		//for (BYTE iDisk = 1; iDisk < m_iDiskCount; ++iDisk)
		//{
		//	pBuffer = _pDiskBuffers->m_pArrayPointers.GetAt(0);
		//	pNextBuffer = _pDiskBuffers->m_pArrayPointers.GetAt(0);
		//	pdwParity = (DWORD *) _pDiskBuffers->m_pArrayPointers[0]->m_pAddess;
		//	pdwTemp = (DWORD *) _pDiskBuffers->m_pArrayPointers[iDisk]->m_pAddess;
		//	while ( pdwParity <  (loop + _pDiskBuffers->m_pArrayPointers[0]->m_iSize ) )
		//	{
		//		*pdwParity ^= *pdwTemp;
		//		++pdwTemp;
		//		++pdwParity;

		//	}
		//}
		//pdwParity  = (DWORD *) _pDiskBuffers->m_pArrayPointers[0]->m_pAddess;

		//
		//UINT iPos = 0;

		//for (DWORD i = 0; i < _pDiskBuffers->m_pArrayPointers[0]->m_iSize /*/ sizeof (DWORD)*/ ; ++i)
		//{
		//	if ( pdwParity[i] != 0)
		//	{
		//		//::SendMessageA(hWindow,WM_NOT_EQUAL,0,(LPARAM)_pDiskBuffers->m_pArrayPointers[0]->m_LBA);

		//	}

		//}
		
//


/*

		CBuffer *pBuffer = NULL;
		CBuffer *pNextBuffer = NULL;

			pBuffer = _pDiskBuffers->m_pArrayPointers[1];
			l32BitBuffer = (DWORD *) pBuffer->m_pAddess;
	
			for ( BYTE i = 2 ; i < m_iDiskCount ; ++i)
			{
				pNextBuffer = _pDiskBuffers->m_pArrayPointers[i];
				l32BitBufferNext = (DWORD *) pNextBuffer->m_pAddess;
				for (DWORD iCounts = 0; iCounts < pBuffer->m_iSize / sizeof (DWORD); ++iCounts)
				{
					l32BitBuffer[iCounts] ^= l32BitBufferNext[iCounts];

				}

				// delete
				pAllocBuffer->RemoveBuffer(pNextBuffer);
			}

			pNextBuffer = _pDiskBuffers->m_pArrayPointers[0];
			l32BitBufferNext = ( DWORD * ) pNextBuffer->m_pAddess;


			for (DWORD iCounts = 0; iCounts < pBuffer->m_iSize / sizeof (DWORD); ++iCounts)
			{
				if (l32BitBuffer[iCounts] != l32BitBufferNext[iCounts])
				{
					strFormat.Format(_T("# %I64d "),pBuffer->m_LBA);
					//fileReportTxt.WriteString(strFormat);
					//::SendMessageA(hWindow,WM_NOT_EQUAL,0,(LPARAM)pBuffer->m_LBA);
					//break;
				}

			}

	
		pAllocBuffer->RemoveBuffer(pNextBuffer);
		pAllocBuffer->RemoveBuffer(pBuffer);


*/