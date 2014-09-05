#pragma once

#include "Imports.h"
#include <ObjBase.h>


#include <string>
using std::wstring;

class IDevice;
class CDiskDevice;
class CFileDevice;

#include "Devices.h"

/////////////	Device Factory	/////////////
interface DllExport IDeviceFactory
{
	virtual	~IDeviceFactory(void){};
	virtual IDevice * CreateDevice() = 0;
};

struct DllExport CDiskFactory 
			: public IDeviceFactory
{
	~CDiskFactory(){};
	IDevice * CreateDevice();

};

struct DllExport CFileFactory 
			: public IDeviceFactory
{
	~CFileFactory(){};
	IDevice * CreateDevice();

};

/////////////	Reader Factory	/////////////
class IReader;
class CReader;
class CAsyncReader;

interface DllExport IReaderFactory
{
	IReaderFactory(void){};
	virtual ~IReaderFactory(void){};
	virtual IReader * CreateReader() = 0;
	virtual IReader * CreateReader(IDevice * _Device) = 0;
	virtual IReader * CreateReader(const DevicePtr & _DevicePtr) = 0;
};

struct DllExport CReaderFactory
			: public IReaderFactory
{
	CReaderFactory(){};
	~CReaderFactory(){};

	IReader * CreateReader();
	IReader * CreateReader(IDevice * _Device);
	IReader * CreateReader(const DevicePtr & _DevicePtr);

};
class IWriter;
interface DllExport IWriterFactory
{
	IWriterFactory(){};
	virtual ~IWriterFactory(){};
	virtual IWriter * CreateWriter(const DevicePtr & _DevicePtr) = 0;
};

struct DllExport CWriterFactory
{
	CWriterFactory(){};
	virtual ~CWriterFactory(){};
	virtual IWriter * CreateWriter(const DevicePtr & _DevicePtr);
};
/////////////	Stream Reader Factory	/////////////
interface IStreamReader;
class IQueue;
class CAllocator;

interface DllExport IStreamReaderFactory
{
	IStreamReaderFactory(){};
	virtual ~IStreamReaderFactory(){};
	virtual IStreamReader * CreateStreamReader() = 0;
	virtual IStreamReader * CreateStreamReader(IReader * _pReader) = 0;
	virtual IStreamReader * CreateStreamReader(IReader * _pReader, IQueue * _pQueue, CAllocator *_pAllocator) = 0;
};

struct DllExport CConsistentFactory
			: public IStreamReaderFactory
{
	CConsistentFactory(){};
	~CConsistentFactory(){};
	IStreamReader * CreateStreamReader();
	IStreamReader * CreateStreamReader(IReader * _pReader);
	IStreamReader * CreateStreamReader(IReader * _pReader, IQueue * _pQueue, CAllocator *_pAllocator);
};

/////////////	Abstract Task Factory	/////////////
class IAbstractTask;
class CTaskManager;

interface DllExport ITaskFactory
{
	ITaskFactory(){};
	virtual ~ITaskFactory(){};
	virtual IAbstractTask * CreateTask() = 0;
};

struct DllExport CTaskFactory
		: public ITaskFactory
{
	CTaskFactory(){};
	~CTaskFactory(){};
	IAbstractTask * CreateTask();
	void AddHasing(CTaskManager * _pTaskManager, const wstring &_KeyString);
};

struct DllExport CPhysicalFactory
		: public ITaskFactory
{
	CPhysicalFactory(){};
	~CPhysicalFactory(){};
	IAbstractTask * CreateTask();
};

struct DllExport CImageFactory
		: public ITaskFactory
{
	CImageFactory(){};
	~CImageFactory(){};
	IAbstractTask * CreateTask();
};

struct DllExport CRawCreaterFactory
	: public ITaskFactory
{
	CRawCreaterFactory(){};
	~CRawCreaterFactory(){};
	IAbstractTask * CreateTask();
};


/////////////	Hashing Factory	/////////////
struct DllExport CFactoryMD5
		: public ITaskFactory
{
	CFactoryMD5(){};
	virtual ~CFactoryMD5(){};
	IAbstractTask * CreateTask();
};

struct DllExport CFactorySHA1
		: public ITaskFactory
{
	CFactorySHA1(){};
	virtual ~CFactorySHA1(){};
	IAbstractTask * CreateTask();
};

struct DllExport CFactorySHA256
		: public ITaskFactory
{
	CFactorySHA256(){};
	virtual ~CFactorySHA256(){};
	IAbstractTask * CreateTask();
};

class CHashingMap;
struct DllExport CHashMapFactory
{
	CHashMapFactory(){};
	virtual ~CHashMapFactory(){};
	CHashingMap * GetHashinMap();
};

/////////////	Queue Factory	/////////////
class IQueue;
interface DllExport IQueueFactory
{
	IQueueFactory(){};
	virtual ~IQueueFactory(){};
	virtual IQueue * CreateQueue() = 0;
};

struct DllExport CQueueFactory
		: public IQueueFactory
{
	CQueueFactory(){};
	virtual ~CQueueFactory(){};
	IQueue * CreateQueue();
};

///////////	Allocator Factory	/////////////
class CAllocator;

struct DllExport CAllocatorFactory
{
	CAllocatorFactory(){};
	virtual ~CAllocatorFactory(){};
	CAllocator* CreateAllocator(DWORD BufferSize, UINT MaxBuffers);
};
