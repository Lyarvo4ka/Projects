#include "StdAfx.h"
#include "AbstractFactory.h"
#include "Devices.h"
#include "Reader.h"
#include "Solver.h"
#include "Writer.h"
#include "Hashing.h"
#include "Queue.h"
#include "Buffer.h"

/************************************************************/
/*                       Device Factory			            */
/************************************************************/
IDevice * CDiskFactory::CreateDevice()
{
	return new CDiskDevice();
}

IDevice * CFileFactory::CreateDevice()
{
	return new CFileDevice();
}

/************************************************************/
/*                       Reader Factory			            */
/************************************************************/
IReader * CReaderFactory::CreateReader()
{
	return new CReader();
}
IReader * CReaderFactory::CreateReader(IDevice * _Device)
{
	return new CReader(_Device);
}
IReader * CReaderFactory::CreateReader(const DevicePtr & _DevicePtr)
{
	return new CReader(_DevicePtr);
}
/************************************************************/
/*                       Writer Factory			            */
/************************************************************/
IWriter * CWriterFactory::CreateWriter(const DevicePtr & _DevicePtr)
{
	return new CWriter(_DevicePtr);
}

/************************************************************/
/*                       Stream Reader Factory			    */
/************************************************************/
IStreamReader * CConsistentFactory::CreateStreamReader()
{
	return new CReaderConsistent();
}
IStreamReader * CConsistentFactory::CreateStreamReader(IReader * _pReader)
{
	return new CReaderConsistent(_pReader);
}
IStreamReader * CConsistentFactory::CreateStreamReader(IReader * _pReader, IQueue * _pQueue, CAllocator *_pAllocator)
{
	return new CReaderConsistent(_pReader,_pQueue,_pAllocator);
}

/************************************************************/
/*                       Abstract Task Factory			    */
/************************************************************/

IAbstractTask* CTaskFactory::CreateTask()
{
	return new CTaskManager();
}
void CTaskFactory::AddHasing(CTaskManager * _pTaskManager,const wstring &_KeyString)
{
	if (_pTaskManager == NULL)
		return;
	CHashMapFactory HahMapFactory;
	CHashingMap *pHasingMap = HahMapFactory.GetHashinMap();
	int iHashinMethod = pHasingMap->GetData(_KeyString);
	CFactoryMD5 MD5Factory;
	CFactorySHA1 SHA1Factory;
	CFactorySHA256 SHA2Factory;

	switch (iHashinMethod)
	{
	case HashingValues::MD5_SHA1:
		_pTaskManager->Add(MD5Factory.CreateTask());
		_pTaskManager->Add(SHA1Factory.CreateTask());
		break;
	case HashingValues::MD5:
		_pTaskManager->Add(MD5Factory.CreateTask());
		break;
	case HashingValues::SHA1:
		_pTaskManager->Add(SHA1Factory.CreateTask());
		break;
	case HashingValues::SHA2:
		_pTaskManager->Add(SHA2Factory.CreateTask());
		break;
	}
}

IAbstractTask* CPhysicalFactory::CreateTask()
{
	return new CPhysicalWriter();
}
IAbstractTask* CImageFactory::CreateTask()
{
	return new CFileWriter();
}
IAbstractTask * CRawCreaterFactory::CreateTask()
{
	return new CRawCreater();
}


/************************************************************/
/*                       Hashing Factory				    */
/************************************************************/
IAbstractTask * CFactoryMD5::CreateTask()
{
	return new CMD5Hash();
}

IAbstractTask * CFactorySHA1::CreateTask()
{
	return new CSHA1Hash();
}

IAbstractTask * CFactorySHA256::CreateTask()
{
	return new CSHA256Hash();
}
/************************************************************/
/*                       Singleton Factory				    */
/************************************************************/
CHashingMap * CHashMapFactory::GetHashinMap()
{
	return CHashingMap::GetInstance();
}

/************************************************************/
/*                       Queue Factory						*/
/************************************************************/
IQueue * CQueueFactory::CreateQueue()
{
	return new CQueue();
}

/************************************************************/
/*                    Allocator Factory						*/
/************************************************************/
CAllocator* CAllocatorFactory::CreateAllocator(DWORD BufferSize, UINT MaxBuffers)
{
	return new CAllocator(BufferSize,MaxBuffers);
}