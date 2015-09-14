#include "StdAfx.h"
#include "ReadDisk.h"

CReadDisk::CReadDisk(void)
	:hThreads( NULL ) , m_strDrivePath( _T("") ) , m_iDriveNumber( UINT_MAX )
	,m_iIndent( UINT_MAX ) , m_iBlockSize( UINT_MAX ) , m_lStep ( ULONG_MAX )
	,m_hEventStart(NULL),m_dwSectorSize( ULONG_MAX ), m_bResult(FALSE)
	,m_hDevice(INVALID_HANDLE_VALUE),m_iTestNumber(PARAM_START_PARITY_TEST)
{

	//hMemoryStack = CreateIoCompletionPort()

}

CReadDisk::~CReadDisk(void)
{
	//::WaitForSingleObject(hThreads,INFINITE);
}

void CReadDisk::StartThreads()
{
	UINT iDiskNumber = m_iDriveNumber;
	hThreads = CreateThread(NULL,0,
						  ( LPTHREAD_START_ROUTINE ) ThreadReadFunc,
						  (LPVOID)this,
						  NULL,0);

	if (hThreads == NULL)
		TRACE (_T("class (CReadDisk) Can't CreateThread #%i error %s"),iDiskNumber,GetLastErrorMessage(::GetLastError()));
}

DWORD WINAPI CReadDisk::ThreadReadFunc(LPVOID lParam)
{
	CReadDisk *pData = (CReadDisk*)lParam;
	UINT iResult = 0;
	if ( pData )
	{
		switch (pData->m_iTestNumber)
		{
			case PARAM_START_PARITY_TEST:
				iResult = pData->run();
				break;
			case PARAM_START_SPEED_HDD_TEST:
				iResult = pData->run2();
				break;
			default:
				return 666;
		}
	}

	return iResult;
}

BOOL CReadDisk::ReadData(BYTE * _buffer, DWORD *_dwBytesRead,OVERLAPPED *_oOverlap, DWORD &_dwBlockSize)
{
	//DWORD _dwBytesRead = 0;
	m_bResult = ReadFile(m_hDevice,_buffer,_dwBlockSize,_dwBytesRead,_oOverlap);
	DWORD dwError = GetLastError();
	if (!m_bResult)
	{
		switch ( dwError = GetLastError() )
		{
		case ERROR_HANDLE_EOF:
			return FALSE;
		case ERROR_IO_PENDING:
			m_bResult = GetOverlappedResult(m_hDevice,_oOverlap,_dwBytesRead,TRUE) ;

			if (!m_bResult)
			{
				switch (dwError = GetLastError())
				{
					case ERROR_SECTOR_NOT_FOUND:
					case ERROR_HANDLE_EOF:
						return FALSE;
				}
			}
			return TRUE;
			break;
		default:
			TRACE(_T("Error Read Disk.\r\n The program is will be close !!!"));
			return FALSE;
		}
	}

	return FALSE;
}

BOOL CReadDisk::ReadFileData(BYTE *_buffer, DWORD *_dwBytesRead, DWORD &_dwBlockSize)
{
	m_bResult = ReadFile(m_hDevice,_buffer,_dwBlockSize,_dwBytesRead,NULL);
	return m_bResult;
}

void CReadDisk::setTestNumber(UINT _iTestNum)
{
	m_iTestNumber = _iTestNum;
}

UINT CReadDisk::run2()
{
	CTime cTimeSTART =  CTime::GetCurrentTime();

	OpenPhysicalDisk(m_hDevice);
	if (m_hDevice == INVALID_HANDLE_VALUE)
		TRACE( GetLastErrorMessage( GetLastError() ) );

	DWORD dwBlockSize = m_iBlockSize * m_dwSectorSize;
	DWORD dwBytesRead = 0;

	CBuffer *pBuffer = NULL;
	//OVERLAPPED m_oOverlap = {0};

	HANDLE hEventRead = CreateEvent(NULL, TRUE, FALSE, NULL);
	//m_oOverlap.hEvent = hEventRead;
	//m_oOverlap.Internal = 0;
	//m_oOverlap.InternalHigh = 0;

	DWORD dwError = 0;

	LONGLONG liPosMove;
	liPosMove = m_ReadRange.lFrom;
	BOOL bResult = FALSE;
	BOOL bPending = FALSE;

	m_ReadRange.lTo *= m_dwSectorSize;

	LARGE_INTEGER liPosMOVE;
	liPosMOVE.QuadPart = liPosMove;

	pBuffer = pAllocBuffer->GetBuffer();
	SetFilePointerEx(m_hDevice,liPosMOVE,NULL,FILE_BEGIN);

	while (liPosMOVE.QuadPart < m_ReadRange.lTo)
	{
		DWORD dwError = 0;

		//if (bStopSignal)
		//	break;
		//m_oOverlap.Pointer = (PVOID)liPosMove;
		//m_oOverlap.Offset = liPosMOVE.LowPart;
		//m_oOverlap.OffsetHigh = liPosMOVE.HighPart;

		//if (ReadData(pBuffer->m_pAddess,&dwBytesRead,&m_oOverlap,dwBlockSize) )
		//{
		//	// Read GOOD
		//}
		//else
		//	break;
		SetFilePointerEx(m_hDevice,liPosMOVE,NULL,FILE_BEGIN);

		if (!ReadFile(m_hDevice,pBuffer->m_pAddess,dwBlockSize,&dwBytesRead,NULL) )
		{
			dwError = GetLastError();
			TRACE(_T("Error Read Disk.\r\n The program is will be close !!!"));
			break;
		}

		liPosMOVE.QuadPart += dwBlockSize;


	}
	// send to Finish
	pAllocBuffer->RemoveBuffer(pBuffer);
	CloseHandle(m_hDevice);

	CTime cTimeFINISH =  CTime::GetCurrentTime();
	CTimeSpan cTimeInterval;
	cTimeInterval = cTimeFINISH - cTimeSTART ;//- cTimeSTART;
	CString strTime;
	strTime.Format(_T("Read Time (%i (hours) %i (min), %i (sec)\r\n"),cTimeInterval.GetHours(),cTimeInterval.GetMinutes(),cTimeInterval.GetSeconds());
	TRACE(strTime);

	TRACE(_T("Finish Read Disk..#%i\r\n"),m_iDriveNumber);
	return m_iDriveNumber;
	return 0;
}

#define bWaitAll TRUE

UINT CReadDisk::run()
{
	// wait all functions for START
	WaitForSingleObject(m_hEventStart,INFINITE);
	
	OpenPhysicalDisk(m_hDevice);
	if (m_hDevice == INVALID_HANDLE_VALUE)
		TRACE( GetLastErrorMessage( GetLastError() ) );

	DWORD dwBlockSize = m_iBlockSize * m_dwSectorSize;
	DWORD dwBytesRead = 0;

	CBuffer *pBuffer = NULL;
	OVERLAPPED m_oOverlap = {0};

	HANDLE hEventRead = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_oOverlap.hEvent = hEventRead;
	m_oOverlap.Internal = 0;
	m_oOverlap.InternalHigh = 0;

	DWORD dwError = 0;

	LONGLONG liPosMove;
	liPosMove = m_ReadRange.lFrom + m_iIndent*m_dwSectorSize;

	LONGLONG lNextRead = 0;
	if ( m_lStep > 0 && m_ReadRange.lTo > m_lStep)
	{
		lNextRead = m_ReadRange.lTo / m_lStep;
		lNextRead *= m_dwSectorSize;
	}
	else
		lNextRead = dwBlockSize;

	//BOOL bResult = FALSE;
	//BOOL bPending = FALSE;

	m_ReadRange.lTo *= m_dwSectorSize;
	liPosMove *= m_dwSectorSize;
	LARGE_INTEGER liPosMOVE;
	liPosMOVE.QuadPart = liPosMove;

	DWORD dwResultWait = 0;
	//::SetFilePointerEx(m_hDevice,liPosMOVE,NULL,FILE_BEGIN);
	while (liPosMOVE.QuadPart < m_ReadRange.lTo)
	{
		dwResultWait = ::WaitForMultipleObjects(2,m_hLockThread,FALSE,INFINITE);
		if ( dwResultWait == (WAIT_OBJECT_0  + 1) )
		{
			//STOP
			break;
		}
		else if( dwResultWait == (WAIT_OBJECT_0 + 0) )
			{	
				m_oOverlap.Offset = liPosMOVE.LowPart;
				m_oOverlap.OffsetHigh = liPosMOVE.HighPart;
				pBuffer = pAllocBuffer->GetBuffer();
				if (ReadData(pBuffer->m_pAddess,&dwBytesRead,&m_oOverlap,dwBlockSize) )
				{
					pBuffer->setDiskNumber(m_iDriveNumber);
					pBuffer->setLBA(liPosMOVE.QuadPart / m_dwSectorSize); // ??????????????
					pBuffer->setSize(dwBytesRead);
					m_pMap->addToQueueList(pBuffer);
				}
				else
				{
					// send to Finish
					TRACE(_T("Error Read Disk..#%i\r\n"),m_iDriveNumber);
					break;
				}
				liPosMOVE.QuadPart += dwBytesRead;
		}
		////if (m_bPause == TRUE)
		////	WaitForSingleObject(hPausedHandle,INFINITE);
		//bResult = ReadFile(m_hDevice,pBuffer->m_pAddess,dwBlockSize,&dwBytesRead,&m_oOverlap);
		//if (!bResult)
		//{
		//	dwError = GetLastError();
		//	switch(dwError)
		//	{
		//	case ERROR_IO_PENDING:
		//	{
		//		bPending = GetOverlappedResult(m_hDevice,
  //                                            &m_oOverlap,
  //                                            &dwBytesRead,
  //                                            TRUE) ;

		//		if (bPending)
		//		{
		//			pBuffer->setDiskNumber(m_iDriveNumber);
		//			pBuffer->setLBA(liPosMOVE.QuadPart / 512); // ??????????????
		//			pBuffer->setSize(dwBytesRead);
		//			m_pMap->addToQueueList(pBuffer);
		//			liPosMOVE.QuadPart += lNextRead;
		//			// read successful
		//		}
		//		
		//		else
		//			dwError = GetLastError();


		//		break;
		//	}
		//	default:
		//		TRACE( _T("Error Read Disk.\r\n The program is will be close !!!") );
		//			exit(3);
		//		break;
		//	}
		//}
		
	}


	SendToFinish(pBuffer);
	CloseHandle(m_hDevice);

	TRACE(_T("Finish Read Disk..#%i\r\n"),m_iDriveNumber);
	return m_iDriveNumber;
}

void CReadDisk::SendToFinish(CBuffer *_pBuffer)
{
	_pBuffer = pAllocBuffer->GetBuffer();
	_pBuffer->setSize(NULL);
	m_pMap->addToQueueList(_pBuffer);	
}

void CReadDisk::OpenPhysicalDisk(HANDLE &hDisk)
{
	hDisk = CreateFile(m_strDrivePath,
					   GENERIC_READ,
					   FILE_SHARE_READ,
					   NULL,
					   OPEN_EXISTING,
					   FILE_FLAG_OVERLAPPED /*| FILE_FLAG_NOBUFFERING *//*NULL*/,
					   NULL);
}

void CReadDisk::setDevicePath(CString _strPath)
{
	m_strDrivePath = _strPath;
}

void CReadDisk::setDeviceNumber(DWORD _iDiskNumber)
{
	m_iDriveNumber = _iDiskNumber;
}

void CReadDisk::setReadRange(LONGLONG _lFrom, LONGLONG _lTo)
{
	m_ReadRange.lFrom = _lFrom;
	m_ReadRange.lTo = _lTo;
}

void CReadDisk::setIndent(DWORD _iIndent)
{
	m_iIndent = _iIndent;
}

void CReadDisk::setBlockSize(DWORD _iBlockSize)
{
	m_iBlockSize = _iBlockSize;
}

void CReadDisk::setStep(LONGLONG _lStep)
{
	m_lStep = _lStep;
}

void CReadDisk::setBytesPerSector(const DWORD _iBytesPerSector)
{
	m_dwSectorSize = _iBytesPerSector;
}

void CReadDisk::setStartEvent(HANDLE _hStartHandle)
{
	m_hEventStart = _hStartHandle;
}

void CReadDisk::setComunicateHandle( HANDLE * _hHandle)
{
	m_hLockThread = _hHandle;
}

void CReadDisk::setAllocator(CAllocator *_pAllocator)
{
	pAllocBuffer = _pAllocator;
}

void CReadDisk::setMapPointer(CMapAddress *_pMap)
{
	m_pMap = _pMap;
}

#define SECTOR 512
#define BUFFER_SIZE 256
#define MAX_BUFFERS 5000

BOOL CReadDisk::ReadDataFile(const CString _strPath, LONGLONG &_StartLBA, LONGLONG &_SizeRead,const CString _FileWrite)
{
	HANDLE hDisk = INVALID_HANDLE_VALUE;
	hDisk =	CreateFile(_strPath,
					   GENERIC_READ,
					   FILE_SHARE_READ,
					   NULL,
					   OPEN_EXISTING,
					   0,
					   NULL);

	if (hDisk == INVALID_HANDLE_VALUE)
	{
		DWORD dwError = GetLastError();
		TRACE("Error Open Physical Drive !!!\r\n");
		return FALSE;
	}

	HANDLE hWriteFile = INVALID_HANDLE_VALUE;
	hWriteFile = CreateFile(_FileWrite,
					   GENERIC_WRITE,
					   FILE_SHARE_WRITE,
					   NULL,
					   CREATE_ALWAYS,
					   0,
					   NULL);

	LARGE_INTEGER liPosToMove;
	liPosToMove.QuadPart = _StartLBA;

	LARGE_INTEGER liPosEnd;
	liPosEnd.QuadPart = _StartLBA;
	liPosEnd.QuadPart += _SizeRead;

	LARGE_INTEGER liEndRead;
	liEndRead.QuadPart = _SizeRead;
	pAllocBuffer = new CAllocator(SECTOR*BUFFER_SIZE,MAX_BUFFERS);
	CBuffer *pBuffer;

	DWORD dwReadSize = SECTOR*BUFFER_SIZE;
	liPosEnd.QuadPart -= dwReadSize;
	DWORD dwBytesRead = 0;

	while (liPosToMove.QuadPart < liPosEnd.QuadPart)
	{
		// Get Buffer
		pBuffer = pAllocBuffer->GetBuffer();
		SetFilePointerEx(hDisk,liPosToMove,NULL,FILE_BEGIN);
		if ( !ReadFile(hDisk,pBuffer->m_pAddess,dwReadSize,&dwBytesRead,NULL) )
		{
			TRACE("Error Read\r\n");
			exit(7);
		}
	
		if ( !WriteFile(hWriteFile,pBuffer->m_pAddess,dwReadSize,&dwBytesRead,NULL) )
		{
			TRACE("Error Read\r\n");
			exit(7);
		}

		liPosToMove.QuadPart += dwReadSize;
		// Remove Buffer
		pAllocBuffer->RemoveBuffer(pBuffer);
	}

	LARGE_INTEGER liFileSize;
	GetFileSizeEx(hWriteFile,&liFileSize);
	DWORD dwLastRead = 0;
	dwBytesRead = 0;
	dwLastRead = (DWORD)(_SizeRead - liFileSize.QuadPart);
	dwReadSize = dwLastRead;
	if (dwReadSize > 0)
	{
		dwLastRead /= 512;
		dwLastRead *= 512;
	BYTE *pBuff = new BYTE[dwLastRead];

		SetFilePointerEx(hDisk,liPosToMove,NULL,FILE_BEGIN);
		if ( !ReadFile(hDisk,pBuff,dwLastRead,&dwBytesRead,NULL) )
		{
			DWORD dwError = GetLastError();
			TRACE("Error Read\r\n");
			exit(7);
		}

		if ( !WriteFile(hWriteFile,pBuff,dwReadSize,&dwBytesRead,NULL) )
		{
			TRACE("Error Read\r\n");
			exit(7);
		}
	delete pBuff;
	}
	CloseHandle(hWriteFile);
	CloseHandle(hDisk);

	delete pAllocBuffer;
	return false;
}



//void CParityCheck::startThread()
//{
//	//hDisk = new HANDLE[m_pDrive->size()];
//	//for (size_t i = 0; i < m_pDrive->size(); ++i)
//	HANDLE hDisk = CreateThread(NULL,0,
//								(LPTHREAD_START_ROUTINE )threadParityCheck,
//								this,
//								NULL,0/*(LPDWORD)m_pDrive->getDiskNumber()*/);
//
//}
//
//DWORD WINAPI CParityCheck::threadParityCheck(LPVOID lParam)
//{
//	PARITYCHECK *pData = (PPARITYCHECK)lParam;
//
//	DWORD dwSize;
//	ULONG_PTR  key = 0;
//	LPOVERLAPPED 	lpov;
//
//	CBuffer *pBuffer;
//
//	
//	//if (pData->m_iDiskCount)
//		queue<CBuffer*> checkQueue[3] /*= new queue<CBuffer*>[pData->m_iDiskCount]*/;
//
//
//	for (size_t iHdd = 0; iHdd < pData->m_iDiskCount ; ++iHdd)
//	if ( ::GetQueuedCompletionStatus(pData->hSafeStack,&dwSize,&key,&lpov,INFINITE) )
//	{
//
//		pBuffer = new CBuffer(dwSize);
//		pBuffer = (CBuffer*)lpov->Pointer;
//		//if (pBuffer->ge
//		checkQueue[pBuffer->getDiskNumber()].push(pBuffer);
//	//	pBuffer->freeBuffer();
//	}
//
//	 // check if size of queue > 0
//	bool isFree = true;
//	for (size_t iHdd = 0; iHdd < pData->m_iDiskCount ; ++iHdd)
//		if (checkQueue[iHdd].size() == 0)
//		{
//			isFree = false;
//			break;
//		}
//	if (isFree)
//	{
//	BYTE **pArrBuffers = new BYTE*[pData->m_iDiskCount];
//	*pArrBuffers = new BYTE[dwSize];
//
//	for (size_t iHdd = 0; iHdd < pData->m_iDiskCount; ++iHdd)
//	{
//		pArrBuffers[iHdd] = checkQueue[iHdd].front()->getBuffer();
//	}
//
//	for (size_t iHdd = 1; iHdd < pData->m_iDiskCount - 1; ++iHdd)
//	{
//		for (size_t iBuffs = 0; iBuffs < dwSize; ++iBuffs)
//		{
//			pArrBuffers[0][iBuffs] ^= pArrBuffers[iHdd][iBuffs];
//		}
//	}
//
//	bool bFind = false;
//	for (size_t iBuffs = 0; iBuffs < dwSize; ++iBuffs)
//	{
//		if ( pArrBuffers[0][iBuffs] != pArrBuffers[pData->m_iDiskCount - 1][iBuffs] )
//		{
//			bFind = true;
//			break;
//		}
//	}
//
//	int l = 0;
//	if (bFind)
//	{
//		int k = 0;
//		k = 1;
//	
//	}
//	// after delete 
//		// need to syncornized !!!!!!!!!!
//	for (size_t iHdd = 0; iHdd < pData->m_iDiskCount ; ++iHdd)
//	{
//		checkQueue[iHdd].front()->freeBuffer();
//		checkQueue[iHdd].pop();
//	}
//
//
//	}
//	return 0;
//}
//
//void CParityCheck::setDiskCount(BYTE iDisks)
//{
//	m_iDiskCount = iDisks;
//}
//void CReadDisk::startTread()
//{
//	//hDisk = new HANDLE[m_pDrive->size()];
//	//for (size_t i = 0; i < m_pDrive->size(); ++i)
//	hDisk = CreateThread(NULL,0,
//						(LPTHREAD_START_ROUTINE )threadReadDisk,
//						this,
//						NULL,0/*(LPDWORD)m_pDrive->getDiskNumber()*/);
//
//}
//
//DWORD WINAPI CReadDisk::threadReadDisk(LPVOID lParam)
//{
//
//	READDISK * pData = (PREADDISK)lParam;
//	// set count Read bytes
//	//CBuffer *pBuffer = new CBuffer(128*512/* BYTES */);
//
//
//
//
//	return 0;
/*
	size_t iDiskCount = m_vecDiskDrives.size();
	FUNKDATA funcData;
	funcData.lPosFrom = 1;
	funcData.lPosTo = 10000;
	funcData.dwIndent = 63;
	funcData.dwStep = 100;
	funcData.dwBlockSize = 128;

	if (iDiskCount > 0)
	{
		CBuffer *pBuffers = new CBuffer[iDiskCount];

		for (size_t iDisk = 0; iDisk < iDiskCount; ++iDisk)
		{
			pBuffers[iDisk].setDataSize(funcData.dwBlockSize);
			pBuffers[iDisk].setLength(10);
			pBuffers[iDisk].setDrive(m_vecDiskDrives.at(iDisk).getDiskDrive());
			pBuffers[iDisk].setDATA(funcData);
			pBuffers[iDisk].start();

		}

	bool isNotEqual = false;
	SECTOR *pSectors = new SECTOR[iDiskCount];
	SECTOR tempSector;
	list<SECTOR> * listGetSectors = new list<SECTOR>[iDiskCount];
	list<SECTOR>::iterator *Iterators = new list<SECTOR>::iterator[iDiskCount];

	while (true)
	{
		if (pBuffers[0].isFinish())
			break;
		// getData !!!
		for (size_t iDisk = 0; iDisk < iDiskCount; ++iDisk)
		{
			//memcpy(pBuffer[iDisk],pBuffers[iDisk].getBuffer(),funcData.dwBlockSize);
			listGetSectors[iDisk] = pBuffers[iDisk].getBuffer();
			Iterators[iDisk] = listGetSectors[iDisk].begin();
		}
		
		// check
		while ( Iterators[0] != listGetSectors[0].end() )
		{
			memcpy(tempSector.buff ,Iterators[0]->buff,SECTOR_SIZE);
			for (size_t iDisk = 1; iDisk < iDiskCount-1; ++iDisk)
				for (size_t iBytes = 0; iBytes < SECTOR_SIZE; ++iBytes)
					tempSector.buff[ iBytes ] ^= Iterators[iDisk]->buff[ iBytes ];

			for (size_t iBytes = 0; iBytes < SECTOR_SIZE; ++iBytes)
			if ( tempSector.buff[ iBytes ] != Iterators[iDiskCount - 1]->buff[ iBytes ] )
			{
				isNotEqual = true;
				break;
			}


			for (size_t iDisk = 0; iDisk < iDiskCount; ++iDisk)
				++Iterators[iDisk];
		}


	}

	delete Iterators;
	delete listGetSectors; 
	::AfxMessageBox(_T("Finish !!!"),MB_OK);
	// Get DATA and check PARITY !!!!!!!


	// Don't FORGET !!!!!!!!! DELETE
	//	delete pBuffers;
	}

*/


//}



