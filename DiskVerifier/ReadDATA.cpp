#include "StdAfx.h"
#include "ReadDATA.h"


CReadDATA::CReadDATA(void)
{

}

CReadDATA::CReadDATA(CDiskDrive * _diskDrive)
{
	m_diskDrive = _diskDrive;
	m_SizeQueue = new size_t();
	bFlagStartWait = new bool(false);
	bFlagFINISH = false;
	iSelectionCount = 100;
//	CreateThreads();

}

void CReadDATA::CreateFullThread()
{
	hThread = CreateThread(NULL,0,
						  (LPTHREAD_START_ROUTINE )ThreadFullRead,
						  this,
						  0,NULL);

	//WaitForMultipleObjects(1,&hThread,TRUE,INFINITE);

}

void CReadDATA::CreateRandomThread()
{
	HANDLE hRandomHANDLE;
	hRandomHANDLE = CreateThread(NULL,0,
								(LPTHREAD_START_ROUTINE )ThreadRandomRead,
								this,
								0,NULL);
	//WaitForSingleObject(hRandomHANDLE,INFINITE);
}

CReadDATA::~CReadDATA(void)
{
//	if (hThread != INVALID_HANDLE_VALUE)
//		CloseHandle(hThread);
}

void CReadDATA::setSelectionCount(UINT _iCount)
{
	iSelectionCount = _iCount;

}

void CReadDATA::ClearQueue()
{
	if (!m_pQueueRead.empty())
	{
		for (size_t i = 0; i < m_pQueueRead.size(); ++i)
		{
			m_pQueueRead.pop();
		}
	}
}

bool CReadDATA::isEmpty()
{
	return 	!m_pQueueRead.empty();
}

void CReadDATA::addBlock(BYTE * _pBytes)
{
	m_pQueueRead.push(_pBytes);
}


void CReadDATA::removeBlock()
{
	m_pQueueRead.pop();
}

#define COUNT_SAMPLE 255*512

void CReadDATA::setRandomPositions(LONGLONG *_pPos)
{
	lRandomLBA = _pPos;
}


DWORD WINAPI CReadDATA::ThreadRandomRead( LPVOID lParam)
{
	READDATA *pData = (PREADDATA)lParam;
	pData->m_diskDrive->OpenPhysicalDisk();
	DWORD dwBytesRead = 0;
		
	pData->pBuffers = new BYTE[COUNT_SAMPLE];
	memset(pData->pBuffers,1,COUNT_SAMPLE);

	SECTOR *pSector = NULL;

	HANDLE hDisks = pData->m_diskDrive->getHandle();

	UINT iRand = 0;
	UINT iMax = (int)(pData->verifyRange.lTo/RAND_MAX) ;

	LARGE_INTEGER lPos ;

	//for (int jCount = 0; jCount < HDD_ZONE; ++jCount)
	for (int iCount = 0; iCount < pData->iSelectionCount*HDD_ZONE; ++iCount)
	{
		// Set position 512 bytes
		lPos.QuadPart = pData->lRandomLBA[iCount];
		lPos.QuadPart *= 512;
	// ---------------------------------------------------
	EnterCriticalSection(pData->pAllowAccess);
		SetFilePointerEx(hDisks,lPos,NULL,FILE_BEGIN);
		
		if ( ReadFile(hDisks,
	 				  pData->pBuffers,
					  COUNT_SAMPLE,
					  &dwBytesRead,
					  NULL))
		{
			for (UINT i = 0; i < COUNT_SAMPLE/BLOCK_SIZE; ++i)
			{
				pSector = (PSECTOR) &pData->pBuffers[i*BLOCK_SIZE];
				pData->m_pQueueRead.push(pSector->buff);
				pSector = NULL;
			}
			
		}
		else
			{
				int i = GetLastError();
				::AfxMessageBox(_T("ERROR ReadFile"),MB_OK);
				exit(7);
				break;
			}

	LeaveCriticalSection(pData->pAllowAccess);	
	// ---------------------------------------------------
	ReleaseSemaphore(*pData->hWhaitCheck,1,NULL);
	if (pData->bFlagFINISH)
		break;
	WaitForSingleObject(*pData->hWaitReaded,INFINITE);
	}


	pData->m_diskDrive->ClosePhysicalDisk();
	ReleaseSemaphore(*pData->hFinishThread,1,NULL);

	
	return 0;
}


DWORD WINAPI CReadDATA::ThreadFullRead( LPVOID lParam)
{
	READDATA *pData;
	pData = (PREADDATA)lParam;


	pData->m_diskDrive->OpenPhysicalDisk();
	DWORD dwBytesRead = 0;

	/*ULONG ulMaxTransferSize = pData->m_diskDrive->getMaxTransferSize();*/
	//DWORD dwBytesPerSector = pData->m_diskDrive->getBytesPerSector();
	//ulMaxTransferSize -= dwBytesPerSector;

	SECTOR * pSector;
	pData->pBuffers = new BYTE[COUNT_SAMPLE];
	memset(pData->pBuffers,1,COUNT_SAMPLE);

	HANDLE hDisks = pData->m_diskDrive->getHandle();

	pData->liDistMove.QuadPart = pData->verifyRange.lFrom;
	pData->liDistMove.QuadPart *= 512;

	LONGLONG lMaxLBA = pData->verifyRange.lTo;
	lMaxLBA *= 512;

	LONGLONG lStep = pData->verifyRange.lTo / pData->iSelectionCount - pData->verifyRange.lFrom;
	if (lStep % 255 != 0)
		lStep = lStep - lStep % 255;

	lStep *= 512;
	LONGLONG lMoveTo = lStep;

	//ReleaseSemaphore(*pData->hWhaitSignal,1,NULL);


		while(pData->liDistMove.QuadPart < lMaxLBA)
		{

		EnterCriticalSection(pData->pAllowAccess);

		{
		SetFilePointerEx(hDisks,pData->liDistMove,NULL,FILE_BEGIN);

 		for (BYTE iNumReads = 0; iNumReads < 1; ++iNumReads)
			if ( ReadFile(hDisks,
						 pData->pBuffers,
						 COUNT_SAMPLE,
						 &dwBytesRead,
						 NULL))
			{
					for (UINT i = 0; i < COUNT_SAMPLE/BLOCK_SIZE; ++i)
					{
						pSector = (PSECTOR) &pData->pBuffers[i*BLOCK_SIZE];
						pData->m_pQueueRead.push(pSector->buff);
						pSector = NULL;

					}


				if (dwBytesRead == 0)
					break;
				//	buff = &pBuffers[iDiskNumber][BLOCK_SIZE];
				pData->liDistMove.QuadPart += COUNT_SAMPLE;

				}
			else
			{
				int i = GetLastError();
				::AfxMessageBox(_T("ERROR ReadFile"),MB_OK);
				exit(7);
				break;
			}

			}

		if (pData->bFlagFINISH)
			break;

		LeaveCriticalSection(pData->pAllowAccess);

		ReleaseSemaphore(*pData->hWhaitCheck,1,NULL);

		WaitForSingleObject(*pData->hWaitReaded,INFINITE);
		
		if (pData->m_TestType == EASY_TEST)
				pData->liDistMove.QuadPart += lStep;
		}

		//delete pBuffers;
		//pBuffers = NULL;

		pSector = NULL;
		pData->m_diskDrive->ClosePhysicalDisk();
	// Send Message Finish	
	ReleaseSemaphore(*pData->hFinishThread,1,NULL);



	return 0;
}


BYTE * CReadDATA::getBlock()
{

	if (!m_pQueueRead.empty())
	{
		return m_pQueueRead.front();
	}
	else
		return NULL;

}

size_t * CReadDATA::getSize() const
{
	*m_SizeQueue = m_pQueueRead.size();
	return m_SizeQueue;
}

void CReadDATA::CloseThreads()
{
	if (hThread)
		CloseHandle(hThread);
}

void CReadDATA::setRange(LONGLONG _lFrom, LONGLONG _lTO)
{
	verifyRange.lFrom = _lFrom;
	verifyRange.lTo = _lTO;
}


void CReadDATA::setRange(VERIFY_RANGE & _rRange)
{
	verifyRange = _rRange;
}


void CReadDATA::setTestType(TEST_TYPE _testType)
{
	m_TestType = _testType;
}
