#include "StdAfx.h"
#include "Reader.h"
#include "Error.h"
#include "Declaration.h"
//#include <boost/bind.hpp>
//using boost::bind;

#include "Concurrent.h"
#include "Buffer.h"
#include "Queue.h"

#define DEFAULT_SECTOR_COUNT 128
///////////////////// IReader /////////////////////
IReader::IReader()
{

}
IReader::~IReader()
{

}
///////////////////// CReader /////////////////////
CReader::CReader()
{
	m_hDeviceHandle = INVALID_HANDLE_VALUE;
	m_iPosition.QuadPart = 0;
	m_bOpen = FALSE;
	DevicePtr nullPtr;
	m_pDevice = nullPtr;
}
CReader::CReader(IDevice * _pDevice)
{
	m_hDeviceHandle = INVALID_HANDLE_VALUE;
	m_iPosition.QuadPart = 0;
	m_bOpen = FALSE;
	DevicePtr devPtr(_pDevice);
	m_pDevice = devPtr;
}
CReader::CReader(const DevicePtr &_pDevice)
	:m_pDevice(_pDevice),m_iBytesRead(0)
{
	m_hDeviceHandle = INVALID_HANDLE_VALUE;
	m_iPosition.QuadPart = 0;
	m_bOpen = FALSE;
}
CReader::~CReader(void)
{
	Close();
	/*m_pDevice.reset();*/
}
BOOL CReader::Open()
{
	return m_bOpen = m_pDevice->OpenRead(m_hDeviceHandle);
}
BOOL CReader::isOpen() const
{
	return m_bOpen;
}
void CReader::Close()
{
	if (m_hDeviceHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hDeviceHandle);
		m_hDeviceHandle = INVALID_HANDLE_VALUE;
		m_bOpen = FALSE;
	}
}
DWORD CReader::Read(BYTE * _pBuffer, DWORD _ReadSize, LONGLONG _Position)
{
	m_iBytesRead = 0;
	if ((_pBuffer == NULL) || (m_hDeviceHandle == INVALID_HANDLE_VALUE))
		return m_iBytesRead;
	m_iPosition.QuadPart = _Position;
	SetFilePointerEx(m_hDeviceHandle,m_iPosition,NULL,FILE_BEGIN);
	if (!ReadFile(m_hDeviceHandle,_pBuffer,_ReadSize,&m_iBytesRead,NULL))
	{
		DWORD dwError = GetLastError();
		if (dwError == ERROR_IO_DEVICE)	// Testing for End Device
		{
			LONGLONG lMaxLBA = m_pDevice->GetSectorCount();
			lMaxLBA *= m_pDevice->GetBytesPerSector();
			DWORD LastReadSize = (DWORD)(lMaxLBA - _Position);
			if (LastReadSize < _ReadSize)
			{
				SetFilePointerEx(m_hDeviceHandle,m_iPosition,NULL,FILE_BEGIN);
				if (!ReadFile(m_hDeviceHandle,_pBuffer,LastReadSize,&m_iBytesRead,NULL))
				{
					m_iBytesRead = 0;
					return m_iBytesRead;
				}
				else
					return m_iBytesRead;
			}
		}
		else
		if (dwError == ERROR_CRC)
		{
			// Sector-Based Reading
			printf("\r\n");
			m_iBytesRead = 0;
			DWORD dwBytesPerSector = m_pDevice->GetBytesPerSector();
			if (dwBytesPerSector != 0)
			{
				DWORD dwBytesRead = 0;
				BYTE *pSector = new BYTE[dwBytesPerSector];
				DWORD dwSectorsCount = _ReadSize / dwBytesPerSector;
				DWORD iWritePos = 0;
				LONGLONG lBadSector = 0;
				LONGLONG LBAStartBlock = _Position / dwBytesPerSector;
				m_iPosition.QuadPart = _Position;
				for (DWORD iSector = 0; iSector < dwSectorsCount; ++iSector)
				{
					SetFilePointerEx(m_hDeviceHandle,m_iPosition,NULL,FILE_BEGIN);
					if (!ReadFile(m_hDeviceHandle,pSector,dwBytesPerSector,&dwBytesRead,NULL))
					{
						DWORD LinesCount = dwBytesPerSector / BAD_SECTOR_SIZE;
						for (DWORD iLine = 0; iLine < LinesCount; ++iLine)
							memcpy(pSector + iLine * BAD_SECTOR_SIZE, BAD_SECTOR , BAD_SECTOR_SIZE);
						lBadSector =  LBAStartBlock + iSector;
						/*_pCBuffer->AddBadSector(lBadSector);*/
						printf("Error Read Sector %ld\r\n",lBadSector);
					}
					iWritePos = iSector*dwBytesPerSector;
					memcpy(_pBuffer + iWritePos, pSector , dwBytesPerSector);
					m_iPosition.QuadPart += dwBytesPerSector;
					m_iBytesRead += dwBytesPerSector;
				}
				delete pSector;
			}
			return m_iBytesRead;
		}
		m_iBytesRead = 0;
		return m_iBytesRead;
	}
	return m_iBytesRead;
}
DWORD CReader::Read(CBuffer * _pCBuffer, LONGLONG  _Position )
{
	m_iBytesRead = 0;
	if ((_pCBuffer == NULL) || (m_hDeviceHandle == INVALID_HANDLE_VALUE))
		return m_iBytesRead;

	BYTE *pReadBuffer = _pCBuffer->GetBuffer();
	if (pReadBuffer == NULL)
		return m_iBytesRead;

	m_iPosition.QuadPart = _Position;
	SetFilePointerEx(m_hDeviceHandle,m_iPosition,NULL,FILE_BEGIN);
	if (!ReadFile(m_hDeviceHandle,pReadBuffer,_pCBuffer->GetSize(),&m_iBytesRead,NULL))
	{
		DWORD dwError = GetLastError();
		if ( dwError == ERROR_IO_DEVICE || dwError == ERROR_SECTOR_NOT_FOUND )	// Testing for End Device
			return this->TailRead(_pCBuffer,_Position);
		if (dwError == ERROR_CRC)
			return this->SectorReading(_pCBuffer,_Position);
		m_iBytesRead = 0;
	}
	return m_iBytesRead;

}
DWORD CReader::SectorReading(CBuffer * _pCBuffer, LONGLONG &_Position)
{
	if ((_pCBuffer == NULL) || (m_hDeviceHandle == INVALID_HANDLE_VALUE))
		return m_iBytesRead = 0;
	BYTE * pReadBuffer = _pCBuffer->GetBuffer();
	if (pReadBuffer == NULL)
		return m_iBytesRead = 0;
	// Sector-Based Reading
	printf("\r\n");
	m_iBytesRead = 0;
	DWORD dwBytesPerSector = m_pDevice->GetBytesPerSector();
	if (dwBytesPerSector != 0)
	{
		DWORD dwBytesRead = 0;
		BYTE *pSector = new BYTE[dwBytesPerSector];
		DWORD dwSectorsCount = _pCBuffer->GetSize() / dwBytesPerSector;
		DWORD iWritePos = 0;
		LONGLONG lBadSector = 0;
		LONGLONG LBAStartBlock = _Position / dwBytesPerSector;
		m_iPosition.QuadPart = _Position;
		for (DWORD iSector = 0; iSector < dwSectorsCount; ++iSector)
		{
			SetFilePointerEx(m_hDeviceHandle,m_iPosition,NULL,FILE_BEGIN);
			if (!ReadFile(m_hDeviceHandle,pSector,dwBytesPerSector,&dwBytesRead,NULL))
			{
				//DWORD LinesCount = dwBytesPerSector / BAD_SECTOR_SIZE;
				//for (DWORD iLine = 0; iLine < LinesCount; ++iLine)
				//	memcpy(pSector + iLine * BAD_SECTOR_SIZE, BAD_SECTOR , BAD_SECTOR_SIZE);
				ZeroMemory(pSector,dwBytesPerSector);
				lBadSector =  LBAStartBlock + iSector;
				_pCBuffer->AddBadSector(lBadSector);
				printf("Error Read Sector %ld\r\n",lBadSector);
			}

			iWritePos = iSector*dwBytesPerSector;
			memcpy(pReadBuffer + iWritePos, pSector , dwBytesPerSector);
			m_iPosition.QuadPart += dwBytesPerSector;
			m_iBytesRead += dwBytesPerSector;
		}
		delete pSector;
	}
	return m_iBytesRead;
}
DWORD CReader::TailRead(CBuffer * _pCBuffer,LONGLONG &_Position)
{
	m_iBytesRead = 0;
	if (_pCBuffer == NULL || m_hDeviceHandle == INVALID_HANDLE_VALUE)
		return m_iBytesRead;
	BYTE *pReadBuffer = _pCBuffer->GetBuffer();
	if (pReadBuffer == NULL)
		return m_iBytesRead;

	LONGLONG lMaxLBA = m_pDevice->GetSectorCount();
	lMaxLBA *= m_pDevice->GetBytesPerSector();
	DWORD LastReadSize = (DWORD)(lMaxLBA - _Position);
	if (LastReadSize < _pCBuffer->GetSize())
	{
		SetFilePointerEx(m_hDeviceHandle,m_iPosition,NULL,FILE_BEGIN);
		if (!ReadFile(m_hDeviceHandle,pReadBuffer,LastReadSize,&m_iBytesRead,NULL))
		{
			m_iBytesRead = 0;
			return m_iBytesRead;
		}
		else
		{
			_pCBuffer->SetSize(m_iBytesRead);
			return m_iBytesRead;
		}
	}
	return m_iBytesRead;
}
BOOL CReader::SetPosition(const LONGLONG &_Position)
{
	m_iPosition.QuadPart = _Position;
	return SetFilePointerEx(m_hDeviceHandle,m_iPosition,NULL,FILE_BEGIN);
}
void CReader::SetDevice(const DevicePtr &_pDevice)
{
	m_pDevice = _pDevice;
}




///////////////////// CAsyncReader /////////////////////
CAsyncReader::CAsyncReader(const DevicePtr &_pDevice)
	:m_pDevice(_pDevice),m_iBytesRead(0)
{
	m_hDeviceHandle = INVALID_HANDLE_VALUE;
	m_iPosition.QuadPart = 0;
	memset(&m_Overlapped, 0 , sizeof(m_Overlapped));
	m_hOverlappedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_Overlapped.hEvent = m_hOverlappedEvent;
	m_bOpen = FALSE;
}

CAsyncReader::~CAsyncReader(void)
{
	if (m_hOverlappedEvent != INVALID_HANDLE_VALUE)
		CloseHandle(m_hOverlappedEvent);

	m_pDevice.reset();
}

BOOL CAsyncReader::Open()
{
	return m_bOpen = m_pDevice->OpenRead(m_hDeviceHandle,TRUE);
}
BOOL CAsyncReader::isOpen() const
{
	return m_bOpen;
}
void CAsyncReader::Close()
{
	if (m_hDeviceHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hDeviceHandle);
		m_hDeviceHandle = INVALID_HANDLE_VALUE;
	}

}
DWORD CAsyncReader::Read(BYTE * _pBuffer, DWORD _ReadSize, LONGLONG _Position)
{
	if ((_pBuffer == NULL) || (m_hDeviceHandle == INVALID_HANDLE_VALUE))
	{
		m_iBytesRead = 0;
		return m_iBytesRead;
	}
	if ( ReadAsynchronous(_pBuffer,_ReadSize,_Position) )
		return m_iBytesRead;
	else 
	{
		m_iBytesRead = 0;
		return m_iBytesRead;
	}
}
BOOL CAsyncReader::SetPosition(const LONGLONG &_Position)
{
	m_iPosition.QuadPart = _Position;
	m_Overlapped.OffsetHigh = m_iPosition.HighPart;
	m_Overlapped.Offset = m_iPosition.LowPart;
	return TRUE;
}
BOOL CAsyncReader::ReadAsynchronous(BYTE * _pBuffer, DWORD &_BytesCount, LONGLONG &_Position)
{
	m_iPosition.QuadPart = _Position;
	m_Overlapped.OffsetHigh = m_iPosition.HighPart;
	m_Overlapped.Offset = m_iPosition.LowPart;
	m_bResultRead = ReadFile(m_hDeviceHandle,_pBuffer,_BytesCount,&m_iBytesRead,&m_Overlapped);
	if (!m_bResultRead)
	{
		DWORD dwError = GetLastError();
		switch ( dwError )
		{
		case ERROR_HANDLE_EOF:
			return FALSE;
		case ERROR_IO_PENDING:
			m_bResultRead = GetOverlappedResult(m_hDeviceHandle,&m_Overlapped,&m_iBytesRead,TRUE) ;

			if (!m_bResultRead)
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
			//TRACE(_T("Error Read Disk.\r\n The program is will be close !!!"));
			return FALSE;
		}
	}
	return TRUE;
}


CReaderSubject::CReaderSubject()
{
	m_ErrorObserver = NULL;
}
CReaderSubject::~CReaderSubject()
{
	if (m_ErrorObserver != NULL)
	{
		delete m_ErrorObserver;
		m_ErrorObserver = NULL;
	}
}
void CReaderSubject::ErrorNotify()
{
	if (m_ErrorObserver != NULL)
		m_ErrorObserver->Update(this);
}
void CReaderSubject::SetErrorObserver(Observer * _Observer)
{
	m_ErrorObserver = _Observer;
}

///////////////////// CStreamReader /////////////////////
CReaderConsistent::CReaderConsistent()
{
	m_pReader = NULL;
	m_pQueue = NULL;
	m_pAllocator = NULL;
	m_StartOffset = 0;
	m_SectorsCount = 0;
	m_BlockSize = 0;
	m_sError = "";
	LBAPositon = 0;
}
CReaderConsistent::CReaderConsistent(IReader * _pReader)
	: m_pReader(_pReader)
{
	m_pQueue = NULL;
	m_pAllocator = NULL;
	m_StartOffset = 0;
	m_SectorsCount = 0;
	m_BlockSize = 0;
	m_sError = "";
	LBAPositon = 0;
}
CReaderConsistent::CReaderConsistent(IReader *_pReader, IQueue * _pQueue, CAllocator *_pAllocator)
	:m_pReader(_pReader),m_pQueue(_pQueue),m_pAllocator(_pAllocator)
{
	m_StartOffset = 0;
	m_SectorsCount = 0;
	m_BlockSize = 0;
	m_sError = "";
	LBAPositon = 0;
}

CReaderConsistent::~CReaderConsistent()
{
	if (m_pReader != NULL)
	{
		delete m_pReader;
		m_pReader = NULL;
	}
	//m_pQueue = NULL;
	//m_pAllocator = NULL;
}
void CReaderConsistent::SetReader(IReader * _Reader)
{
	m_pReader = _Reader;
}
void CReaderConsistent::SetQueue(IQueue * _Queue)
{
	m_pQueue = _Queue;
}
void CReaderConsistent::SetAllocator(CAllocator *_Allocator)
{
	m_pAllocator = _Allocator;
}
void CReaderConsistent::SetOffset(LONGLONG _StartOffset)
{
	m_StartOffset = _StartOffset;
}
void CReaderConsistent::SetSectorsCount(LONGLONG _SectorsCount)
{
	m_SectorsCount = _SectorsCount;
}
void CReaderConsistent::SetRange(LONGLONG _StartOffset, LONGLONG _SectorsCount)
{
	m_StartOffset = _StartOffset;
	m_SectorsCount = _SectorsCount;
}
void CReaderConsistent::SetDevice(DevicePtr &_devicePtr)
{
	m_pDevice = _devicePtr;
}
void CReaderConsistent::SetBlockSize(DWORD _BlockSize)
{
	m_BlockSize = _BlockSize;
}
BOOL CReaderConsistent::isReady()
{
	m_sError = "no error. Reader";
	if (m_pDevice == NULL)
	{
		m_sError = Declaration::ErrorNoSelectedDevice();
		//m_sError = "Error. Device == NULL";
		return FALSE;
	}
	if (m_pDevice->GetBytesPerSector() == 0)
	{
		m_sError = Declaration::ErrorBPSNull();
		return FALSE;
	}
	LONGLONG lMaxCopyRange = m_StartOffset + m_SectorsCount;
	if (lMaxCopyRange > m_pDevice->GetSectorCount())
	{
		m_sError = Declaration::ErrorOutOffRange();
		return FALSE;
	}
	if (!m_pReader->isOpen())
	{
		m_sError = Declaration::ErrorOpenDevice();
		m_sError += "\r\n" + Declaration::VerifyPath();
		return FALSE;
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
string CReaderConsistent::GetErrorString() const
{
	return m_sError;
}
LONGLONG CReaderConsistent::GetCurrentLBA() const
{
	return LBAPositon;
}
void CReaderConsistent::Start()
{
	Run();
}
DWORD CReaderConsistent::StartThread()
{

	LONGLONG Position = m_StartOffset;
	LBAPositon = m_StartOffset;
	DWORD dwBytesPerSector = m_pDevice->GetBytesPerSector();
	LONGLONG lNumberCopy = m_StartOffset + m_SectorsCount;
	lNumberCopy *= dwBytesPerSector;
	Position *= dwBytesPerSector;
	DWORD dwSize = m_BlockSize;
	if (dwSize == 0)
	{
		dwSize = DEFAULT_SECTOR_COUNT*dwBytesPerSector;
	}

	DWORD dwSectorCount = dwSize / dwBytesPerSector;

	CBuffer *pBuffer = NULL;

	BYTE *pReadBuffer = NULL;
	DWORD dwNumber = m_pDevice->GetNumber();
	DWORD dwBufferRemaining = dwSize;
	DWORD dwBufferSize = 0;
	DWORD WaitResult = 0;
	LONGLONG lLBARemaining = 0;
	CCommunicateLock *pComunicate = CCommunicateLock::GetInstance();
	while (Position < lNumberCopy)
	{
		WaitResult = pComunicate->LOCK();
		if (WaitResult == CCommunicateLock::waitResume)
		{
			pBuffer = m_pAllocator->GetBuffer();
			pReadBuffer = pBuffer->GetBuffer();
			lLBARemaining = lNumberCopy - Position;
			if (lLBARemaining < dwBufferRemaining)
			{
				dwBufferRemaining = (DWORD)lLBARemaining;
				pBuffer->SetSize(dwBufferRemaining);
			}
			if ( (dwBufferSize = m_pReader->Read(pBuffer,Position) ) == 0)
			{
				DWORD dwError = ::GetLastError();
				char Errorbuffer[1000];
				ZeroMemory(Errorbuffer,1000);
				sprintf_s(Errorbuffer,1000,Declaration::ErrorReadSectors().c_str(),LBAPositon,pBuffer->GetSize());
				m_sError = Errorbuffer;
				this->ErrorNotify();
				break;
			}

			if (pBuffer->isHasBadSector())
			{
				char Errorbuffer[100];
				const vector<LONGLONG> *pBadSectors = pBuffer->GetBadSectors();
				vector<LONGLONG>::const_iterator constIter = pBadSectors->begin();
				while (constIter != pBadSectors->end())
				{
					sprintf_s(Errorbuffer,100,Declaration::ErrorReadSector().c_str(),*constIter);
					m_sError  = Errorbuffer;
					this->ErrorNotify();
					++constIter;
				}

			}

			pBuffer->SetDiskNumber(dwNumber);
			pBuffer->SetPosition(Position);
			pBuffer->SetSize(dwBufferSize);
			m_pQueue->AddToQueue(pBuffer);

			Position += dwSize;
			LBAPositon += dwSectorCount;
			this->Notify();
		}
		else
			if (WaitResult == CCommunicateLock::waitAbort)
			{

				break;
			}
	}
	SendToFinish();
	
	/*TRACE("Reader Finished...\r\n");*/
	return 0;
}


void CReaderConsistent::SendToFinish()
{
	if (m_pQueue != NULL)
	{
		CBuffer *pBuffer = new CBuffer(0);
		pBuffer->SetSize(0);
		m_pQueue->AddToQueue(pBuffer);
	}
}
///////////////////// CReadingCounter /////////////////////
//
//CReadingCounter::CReadingCounter()
//{
//	m_iCounter = 0;
//	m_iCurrent = 0;
//	m_hSemaphore = INVALID_HANDLE_VALUE;
////	m_hMutex = CreateMutex(NULL,FALSE,_T("Concurent Mutex"));
//}
//CReadingCounter::~CReadingCounter()
//{
//	CloseHandle(m_hSemaphore);
//	m_hSemaphore = INVALID_HANDLE_VALUE;
//	CloseHandle(m_hMutex);
////	m_hMutex = INVALID_HANDLE_VALUE;
//}
//CReadingCounter * CReadingCounter::GetCounter()
//{
//	if (m_StreamCounter == NULL)
//		m_StreamCounter = new CReadingCounter();
//	return m_StreamCounter;
//}
//void CReadingCounter::Remove()
//{
//	return m_StreamCounter;
//	m_StreamCounter = NULL;
//}
//void CReadingCounter::SetCounter(DWORD _iCounter)
//{
//	m_iCounter = _iCounter;
//	if (m_hSemaphore != INVALID_HANDLE_VALUE)
//	{
//		CloseHandle(m_hSemaphore);
//		m_hSemaphore = INVALID_HANDLE_VALUE;
//	}
//	m_hSemaphore = CreateSemaphore(NULL,0,_iCounter,_T("Semaphore Counter"));
//}
//
//void CReadingCounter::AddCount()
//{
//	::WaitForSingleObject(m_hMutex,INFINITE);
//	if (m_iCounter == m_iCurrent)
//	{
//		
//	}
//	::ReleaseMutex(m_hMutex);
//}