#pragma once

#include "Devices.h"
#include "Concurrent.h"
#include <ObjBase.h>
class IQueue;
class CBuffer;
class CAllocator;

#include <memory>

#define BAD_SECTOR_SIZE 16

static const BYTE BAD_SECTOR[16] = {0x20,0x3F,0x20,0x42,0x41,0x44,0x20,0x53,0x45,0x43,0x54,0x4F,0x52,0x20,0x3F,0x20}; 
///////////////////// IReader /////////////////////
class DllExport IReader
{
public:
	IReader();
	virtual ~IReader() = 0;
	// Open Device
	virtual BOOL Open() = 0;
	// Testing for Device is opened
	virtual BOOL isOpen() const = 0;
	// Close Device
	virtual void Close() = 0;
	// Read data, to pointer pBuffer bytes of ReadSize from Position
	// return count of read bytes
	virtual DWORD Read(BYTE * pBuffer, DWORD ReadSize, LONGLONG Position ) = 0;
	// Read data, to pointer CBuffer object, number bytes of read has object CBuffer, from file offset Position
	// return count of read bytes
	virtual DWORD Read(CBuffer * pCBuffer, LONGLONG  Position ) = 0;
	//// Read data, to pointer CBuffer object
	//// return count of read bytes
	//virtual DWORD Read(CBuffer *pCBuffer) = 0;
	// Set Position
	virtual BOOL SetPosition(const LONGLONG & Position) = 0;
};

typedef std::tr1::shared_ptr<IReader> AbstractReader;

///////////////////// CReader /////////////////////
class DllExport CReader : 
	public IReader
{
public:
	CReader();
	CReader(IDevice * _pDevice);
	CReader(const DevicePtr &_pDevice);
	virtual ~CReader(void);
	BOOL Open();
	BOOL isOpen() const;
	void Close();
	DWORD Read(BYTE * _pBuffer, DWORD _ReadSize, LONGLONG _Position);
	DWORD Read(CBuffer * _pCBuffer, LONGLONG  _Position );
	DWORD SectorReading(CBuffer * _pCBuffer, LONGLONG &_Position);
	DWORD TailRead(CBuffer * _pCBuffer,LONGLONG &_Position);
	BOOL SetPosition(const LONGLONG &_Position);
	void SetDevice(const DevicePtr &_pDevice);
private:
	DWORD m_iBytesRead;
	LARGE_INTEGER m_iPosition;
	DevicePtr m_pDevice;
	HANDLE m_hDeviceHandle;
	BOOL m_bOpen;
};

///////////////////// CAsyncReader /////////////////////
class DllExport CAsyncReader : 
	public IReader
{
public:
	CAsyncReader(const DevicePtr &_pDevice);
	virtual ~CAsyncReader(void);
	BOOL Open();
	BOOL isOpen() const;
	void Close();
	DWORD Read(BYTE * _pBuffer, DWORD _ReadSize, LONGLONG _Position);
	BOOL SetPosition(const LONGLONG &_Position);
private:
	BOOL ReadAsynchronous(BYTE * _pBuffer, DWORD &_BytesCount, LONGLONG &_Position);

private:
	DWORD m_iBytesRead;
	LARGE_INTEGER m_iPosition;
	DevicePtr m_pDevice;
	HANDLE m_hDeviceHandle;
	OVERLAPPED m_Overlapped;
	HANDLE m_hOverlappedEvent;
	BOOL m_bResultRead;
	BOOL m_bOpen;
};

interface DllExport IStreamReader
{
	virtual void Start() = 0;
	virtual BOOL isReady() = 0;
	virtual string GetErrorString() const = 0;
};

class DllExport CReaderSubject
	: public CSubject
{
protected:
	CReaderSubject();
public:
	virtual ~CReaderSubject();
	void ErrorNotify();
	void SetErrorObserver(Observer * _Observer);
private:
	Observer * m_ErrorObserver;
};
///////////////////// CStreamReader /////////////////////
class DllExport CReaderConsistent : 
	public IStreamReader,
	public CThread,
	public CReaderSubject
{
public:
	//typedef boost::mutex::scoped_lock lock;
	CReaderConsistent();
	CReaderConsistent(IReader * _pReader);
	CReaderConsistent(IReader * _pReader, IQueue * _pQueue, CAllocator *_pAllocator);
	~CReaderConsistent();
	void SetReader(IReader * _Reader);
	void SetQueue(IQueue * _Queue);
	void SetAllocator(CAllocator *_Allocator);
	void SetOffset(LONGLONG _StartOffset);
	void SetSectorsCount(LONGLONG _SectorsCount);
	void SetRange(LONGLONG _StartOffset, LONGLONG _SectorsCount);
	void SetDevice(DevicePtr &_devicePtr);
	void SetBlockSize(DWORD _BlockSize);
	BOOL isReady();
	string GetErrorString() const;
	LONGLONG GetCurrentLBA() const;
	void Start();
protected:
	DWORD StartThread(); 
private:
	// Private Functions
	void SendToFinish();

	// Members
	LONGLONG m_StartOffset;
	LONGLONG m_SectorsCount;
	LONGLONG LBAPositon;
	DevicePtr m_pDevice;
	IReader * m_pReader;
	IQueue * m_pQueue;
	CAllocator * m_pAllocator;
	string m_sError;
	DWORD m_BlockSize;

	//shared_ptr<thread> m_Thread;
	//boost::mutex monitor;
	//condition m_Condition;
};

///////////////////// CReadingCounter /////////////////////
//
//class CReadingCounter
//{
//public: 
//	static CReadingCounter * GetCounter();
//	void SetCounter(DWORD _iCounter);
//	void AddCount();
//	void Remove();
//protected:
//	CReadingCounter();
//	~CReadingCounter();
//private:
//	DWORD m_iCounter;
//	DWORD m_iCurrent;
//	HANDLE m_hSemaphore;
//	HANDLE m_hMutex;
//	static CReadingCounter * m_StreamCounter;
//};