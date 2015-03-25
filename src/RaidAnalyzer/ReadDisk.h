#pragma once

#include "Buffer.h"
//---------------------------------------------------------------------------
static CString GetLastErrorMessage(DWORD last_error)
{
	CString			strError;
	static TCHAR	errorBuffer[512];
	if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, last_error, 0, errorBuffer, 511, NULL))
	{
		// if we fail, call ourself to find out why and return that error
		return GetLastErrorMessage(GetLastError());
	}
	return CString(errorBuffer);
}


///////////////////////////////////////////////////////////////////////////////
// ----------------------------- CReadDisk ------------------------------------
///////////////////////////////////////////////////////////////////////////////
typedef class CReadDisk
{
public:
	CReadDisk(void);
	~CReadDisk(void);
	void StartThreads();
	/* IDevice */
	void setDevicePath(CString _str);
	void setDeviceNumber(DWORD _iDiskNumber);
	void setBytesPerSector(const DWORD _iBytesPerSector);

	void setReadRange(LONGLONG _lFrom, LONGLONG _lTo);
	void setIndent(DWORD _iIndent);
	void setBlockSize(DWORD _iBlockSize);

	void setStep(LONGLONG _lSep);
	void setStartEvent( HANDLE _hStartHandle);
	void setComunicateHandle( HANDLE * _hHandles);
	void setMapPointer(CMapAddress *_pMap);
	void setAllocator(CAllocator *_pAllocator);
	void setTestNumber(UINT _iTestNum);

	BOOL ReadData(BYTE * _buffer, DWORD *_dwBytesRead, OVERLAPPED *_oOverlap,DWORD &_dwBlockSize);
	BOOL ReadFileData(BYTE *_buffer, DWORD *_dwBytesRead, DWORD &_dwBlockSize);
	BOOL ReadDataFile(const CString _strPath, LONGLONG &_StartLBA, LONGLONG &_SizeRead,const CString _FileWrite);

private:
	CString m_strDrivePath;
	DWORD m_iDriveNumber;
	HANDLE m_hDevice;

	VerifyRange m_ReadRange;
	DWORD m_iIndent;
	DWORD m_iBlockSize;
	LONGLONG m_lStep;
	DWORD m_dwSectorSize;

	HANDLE m_hEventStart;
	HANDLE hThreads;
	HANDLE *m_hLockThread; // 0 - Pause , 1 - Break
	BOOL m_bResult ;
	UINT m_iTestNumber;

	void OpenPhysicalDisk(HANDLE &);
	static DWORD WINAPI ThreadReadFunc(LPVOID lParam);
	virtual UINT run();
	virtual UINT run2();

	void SendToFinish(CBuffer *_pBuffer);

	CAllocator *pAllocBuffer;
	CMapAddress *m_pMap;
} READDISK, *PREADDISK;




