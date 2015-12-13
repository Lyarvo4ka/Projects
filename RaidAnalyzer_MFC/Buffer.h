#pragma once
#include "GatherByJPG.h"

class CBuffer
{
public:
	CBuffer();
	CBuffer(const DWORD & _TBufferSize);
	virtual ~CBuffer();

	void setLBA(const LONGLONG &_lLBA);
	void setDiskNumber(const BYTE &_DiskNumber);
	void setSize(const DWORD _iSize);
public:
	DWORD m_iSize;
	LONGLONG m_LBA;
	BYTE m_iDiskNumber;
	BYTE * m_pAddess;
};

class CDisksBuffers
{
public:
	CDisksBuffers(BYTE _iDiskCount);
	virtual ~CDisksBuffers();
	CArray<CBuffer*,CBuffer*> m_pArrayPointers;
public:
	BYTE m_iCounter;
}; 

class CAllocator
{
public:
	//CAllocator();
	CAllocator(DWORD _iBufferSize, UINT _iSizeFree);
	virtual ~CAllocator();

	// S E T
	void setBuffersCount(UINT _iBuffersCount);
	void IncBufferCount();

	CBuffer *GetBuffer();
	void RemoveBuffer(CBuffer*);

protected:

	CList<CBuffer*,CBuffer*> m_FreeList;
	UINT m_iSize;
	const UINT m_iSizeFree;
private:

	DWORD m_TBlockSize;
	HANDLE m_hLockSize;
	HANDLE m_hUsedLock;
};

typedef CMap<ULONGLONG,ULONGLONG,CDisksBuffers*,CDisksBuffers*> MapAddress;

class CMapAddress 
{
public:
	CMapAddress();
	virtual ~CMapAddress();

	void addToQueueList(CBuffer* _pBuffer);
	CBuffer * GetFromQueueList();

	void setDiskCount(const BYTE _iDiskCount);
	void SetAllocator(CAllocator *_pAllocator);



	void setComunicateHandle(HANDLE *_hHandles);
	HWND hParityWindow;
	HWND hMainWindow;

	void StartThreads();
	void ExitThreads();
	void sendCommand(BOOL & _XorResult);
	void deleteBuffer();

	void setTest(BOOL  _bQuickFullTest);
	void setTestData(LONGLONG _lTestData);
	void setStop();
	void setToFirstMissmatch(BOOL _bMissmatch);
	void setWaitThread(HANDLE _hWaitThread);

	// Threads Operations
	void SuspendREADThreads();
	void ResumeREADThreads();
	void AbortREADThreads();
	void setSingleton(CSingletonJPGs *_pSingleton);
	void setBytesPerSector(DWORD bps);
protected:
	virtual BOOL ProcessingBuffer(CDisksBuffers*);
	BYTE m_iDiskCount;
	CAllocator *pAllocBuffer;

	DWORD bps_;

	HANDLE *m_pThreadLock;
	CSingletonJPGs *m_pSingletonJpg;
	FINDSENDDATA *m_pSendFindData;
private:
	CStdioFile fileReportTxt;

	static DWORD WINAPI ThreadReadFunc(LPVOID lParam);
	virtual UINT run();
	void sendUpdateProgress();

	HANDLE hThread;
	HANDLE hListAccess;
	HANDLE m_hWaitThread;
	BOOL m_bResult;
	BOOL m_bEmpty;
	BOOL m_bFirstMismatch;
	LONGLONG m_lProgress;
	LONGLONG m_lCounter;
	NotEqualSectors *m_CheckedSectors;
	BOOL m_bStop;
	BOOL m_bFirstFind;
	BOOL m_bQuickFullTest;
	HANDLE m_hEventFree;
	
	CList<CBuffer*,CBuffer*> m_QueueList;
	MapAddress m_mapBuffer;

};

class CMapForJPG : public CMapAddress
{
	BOOL ProcessingBuffer(CDisksBuffers*);
};

