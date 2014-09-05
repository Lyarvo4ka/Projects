#include "StdAfx.h"
//warning C4482: nonstandard extension used: enum used in qualified name
#pragma warning(disable : 4482)
#include "Devices.h"
#include "AbstractFactory.h"
#include <wchar.h>
#include <mbstring.h>
#include <algorithm>
using std::remove_if;

using std::sort;

#include <boost/algorithm/string.hpp>
using boost::trim;


//////////////////////////////////////////
/*			Device Interface			*/
//////////////////////////////////////////
IDevice::IDevice()
{
	m_dwDeviceNumber = 0;
	m_dwBytesPerSector = 0;
	m_dCapacity = 0.0;
	m_lSecorCount = 0;
	m_lSize = 0;
	m_dwMaxTransferSize = 0;
	m_bSystem = false;
}
void IDevice::SetPath(wchar_t *_pDevicePath)
{
	if (m_sDevicePath.size() > 0)
		m_sDevicePath.clear();
	if (_pDevicePath != NULL)
		m_sDevicePath = _pDevicePath;
}
void IDevice::SetName(unsigned char *_pDeviceName)
{
	if (m_sDeviceName.size() > 0)
		m_sDeviceName.clear();
	if (_pDeviceName != NULL)
		m_sDeviceName = (char*)_pDeviceName;
}
void IDevice::SetSerialNumber(unsigned char *_pSerialNumber)
{
	if (m_sSerialNumber.size() > 0)
		m_sSerialNumber.clear();
	if (_pSerialNumber != NULL)
		m_sSerialNumber = (char *)_pSerialNumber;
}
void IDevice::SetNumber(DWORD _dwNuber)
{
	m_dwDeviceNumber = _dwNuber;
}
void IDevice::SetBytesPerSector(DWORD _dwBPS)
{
	m_dwBytesPerSector = _dwBPS;
}
void IDevice::SetSize(LONGLONG _lSize)
{
	m_lSize = _lSize;

	double tmpCapacity = 0.0;
	// 1 Bytes
	tmpCapacity = (double)m_lSize;
	//UINT i
	//// Now is always Capacity in GB (Gigabytes)
	DWORD dwSizeCount = 0;
	while (tmpCapacity > 1024.0)
	{
		tmpCapacity /= 1024.0;
		++dwSizeCount;
	}
	SetSizeData(dwSizeCount);
	m_dCapacity = (double)tmpCapacity;
}
const char * IDevice::GetSizeData() const
{
	return m_sSizeData.c_str();
}
const char * IDevice::GetBusTypeStr() const
{
	char * pBusTypeStr = NULL;
	switch (m_BusType)
	{
	case STORAGE_BUS_TYPE::BusTypeAta:
		return csATA.c_str();
	case STORAGE_BUS_TYPE::BusTypeUsb:
		return csUSB.c_str();
	case WRITE_PROTECTOR:
		return csWriteProtector.c_str();
	case BADDRIVEADAPTER:
		return csBadDriveAdapter.c_str();
	default:
		return NULL;
	}
}
BYTE IDevice::GetBusType() const
{
	return m_BusType;
}
void IDevice::SetSectorCount(LONGLONG _lSectorCount)
{
	//if (m_dwBytesPerSector != 0)
	//{
		m_lSecorCount = _lSectorCount;
		//m_lSecorCount /= m_dwBytesPerSector;
	//}
}
LONGLONG IDevice::GetSize() const
{
	return m_lSize;
}
double IDevice::GetCapacity() const
{
	return m_dCapacity;
}
void IDevice::SetSizeData(DWORD _dwDataCount)
{
	switch (_dwDataCount)
	{
	case BytesSize:
		m_sSizeData = csBytes;
		break;
	case KBytesSize :
		m_sSizeData = csKB;
		break;
	case MBytesSize :
		m_sSizeData = csMB;
		break;
	case GBytesSize :
		m_sSizeData = csGB;
		break;
	case TBytesSize :
		m_sSizeData = csTB;
		break;
	default:
		m_sSizeData = "";
		break;
	}
}
void IDevice::SetMaxTransferSize(DWORD _dwMaxTransferSize)
{
	m_dwMaxTransferSize = _dwMaxTransferSize;
}
void IDevice::SetBusType(BYTE _BusType)
{
	m_BusType = _BusType;
}
bool IDevice::isSystemDisk() const
{
	return m_bSystem;
}
void IDevice::SetSystemDisk(bool _bSystem )
{
	m_bSystem = _bSystem;
}

//////////////////////////////////////////
/*			CDiskDevice					*/
//////////////////////////////////////////
CDiskDevice::CDiskDevice()
{
	m_dwDeviceNumber = 0;
	m_dwBytesPerSector = 0;
	m_lSecorCount = 0;
	m_lSize = 0;
	m_dCapacity = 0.0;
}
CDiskDevice::~CDiskDevice()
{

}
wstring CDiskDevice::GetPath() const 
{
	//return (m_sDevicePath.size() > 0 ) ? (wchar_t*)m_sDevicePath.c_str() : NULL;
	return m_sDevicePath;
}
const char * CDiskDevice::GetName() const 
{
	//return (m_sDeviceName.size() > 0 ) ? (unsigned char *)m_sDeviceName.c_str() : NULL;
	return m_sDeviceName.c_str();
}
const char * CDiskDevice::GetSerialNumber() const
{
	//return (m_sDeviceName.size() > 0 ) ? (unsigned char *)m_sSerialNumber.c_str() : NULL;
	return m_sSerialNumber.c_str();
}
DWORD CDiskDevice::GetNumber() const 
{
	return m_dwDeviceNumber;
}
DWORD CDiskDevice::GetBytesPerSector() const 
{
	return m_dwBytesPerSector;
}
LONGLONG CDiskDevice::GetSectorCount() const 
{
	return m_lSecorCount;
}
BOOL CDiskDevice::OpenRead(HANDLE &_hDeviceHandle, BOOL _bSynchronous)
{
	DWORD dwOpenMode = (_bSynchronous == 0) ? NULL : FILE_FLAG_OVERLAPPED;
	if (m_sDevicePath.size() == 0)
		return FALSE;
	_hDeviceHandle = CreateFile(m_sDevicePath.c_str(),
								GENERIC_READ ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								dwOpenMode,
								NULL);

	if (_hDeviceHandle == INVALID_HANDLE_VALUE)
		return FALSE;
	return TRUE;
}
BOOL CDiskDevice::OpenWrite(HANDLE &_hDeviceHandle, BOOL _bSynchronous)
{
	DWORD dwOpenMode = (_bSynchronous == 0) ? NULL : FILE_FLAG_OVERLAPPED;
	if (m_sDevicePath.size() == 0)
		return FALSE;
	_hDeviceHandle = CreateFile(m_sDevicePath.c_str(),
		GENERIC_WRITE ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		dwOpenMode,
		NULL);

	if (_hDeviceHandle == INVALID_HANDLE_VALUE)
		return FALSE;
	return TRUE;

}
DWORD CDiskDevice::GetMaxTransferSize() const 
{
	return m_dwMaxTransferSize;
}

//////////////////////////////////////////
/*			CFileDevice					*/
//////////////////////////////////////////

CFileDevice::CFileDevice()
{
	m_dwDeviceNumber = 0;
	m_dwBytesPerSector = SECTOR_SIZE;
	m_lSecorCount = 0;
	m_lSize = 0;
	m_dCapacity = 0.0;
}

CFileDevice::~CFileDevice()
{
	
}

wstring CFileDevice::GetPath() const 
{
	return m_sDevicePath;
	//return (m_sDevicePath.size() > 0 ) ? (wchar_t*)m_sDevicePath.c_str() : NULL;
}
const char * CFileDevice::GetName() const 
{
	return m_sDeviceName.c_str();
	//return (m_sDeviceName.size() > 0 ) ? (unsigned char *)m_sDeviceName.c_str() : NULL;
}
const char * CFileDevice::GetSerialNumber() const
{
	return m_sSerialNumber.c_str();
	//return (unsigned char*)m_sSerialNumber.c_str();
}
DWORD CFileDevice::GetNumber() const 
{
	return m_dwDeviceNumber;
}
DWORD CFileDevice::GetBytesPerSector() const 
{
	return m_dwBytesPerSector;
}
LONGLONG CFileDevice::GetSectorCount() const 
{
	return m_lSecorCount;
}
BOOL CFileDevice::OpenRead(HANDLE &_hDeviceHandle, BOOL _bSynchronous)
{
	if (m_sDevicePath.size() == 0)
		return FALSE;
	_hDeviceHandle = CreateFile(m_sDevicePath.c_str(),
		GENERIC_READ ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0, NULL);

	if (_hDeviceHandle == INVALID_HANDLE_VALUE)
		return FALSE;
	LARGE_INTEGER lFileSize = {0};
	if (::GetFileSizeEx(_hDeviceHandle,&lFileSize) )
	{
		SetSize(lFileSize.QuadPart);
		LONGLONG lSectorCount = (LONGLONG) (lFileSize.QuadPart / SECTOR_SIZE);
		SetSectorCount(lSectorCount);
	}
	return TRUE;
}
BOOL CFileDevice::OpenWrite(HANDLE &_hDeviceHandle, BOOL _bSynchronous)
{
	if (m_sDevicePath.size() == 0)
		return FALSE;
	_hDeviceHandle = CreateFile(m_sDevicePath.c_str(),
		GENERIC_WRITE ,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		0, NULL);

	//DWORD dwError = GetLastError();
	if (_hDeviceHandle == INVALID_HANDLE_VALUE)
		return FALSE;
	return TRUE;

}
DWORD CFileDevice::GetMaxTransferSize() const 
{
	return m_dwMaxTransferSize;
}



//////////////////////////////////////////
/*			CDiviceList					*/
//////////////////////////////////////////
CDiviceList::CDiviceList()
{

}

CDiviceList::~CDiviceList()
{
	RemoveAll();
}

void CDiviceList::AddDevice(IDevice * _pIDevice)
{
	DevicePtr ptrDevice(_pIDevice);
	m_SmartDeviceList.push_back(ptrDevice);
	//m_DeviceList.push_back(_pIDevice);
}
void CDiviceList::AddDevice(DevicePtr _ptrDevice)
{
	m_SmartDeviceList.push_back(_ptrDevice);
}

void CDiviceList::RemoveDevice(size_t _iIndex)
{
	if (m_SmartDeviceList.size() > 0)
	{
		vector<DevicePtr>::iterator it;
		for (it = m_SmartDeviceList.begin(); it != m_SmartDeviceList.end(); ++it)
		{
			if ((*it)->GetNumber() == _iIndex)
				it = m_SmartDeviceList.erase(it);
			if (it == m_SmartDeviceList.end())
				break;
		}
	}
}
void CDiviceList::RemoveAll()
{
	vector<DevicePtr>::iterator it;
	if (m_SmartDeviceList.size() > 0)
	{
		m_SmartDeviceList.clear();
	}
}
DevicePtr CDiviceList::GetDevice(size_t _iIndex) const
{
	DevicePtr nullPtr;
	return (_iIndex < m_SmartDeviceList.size()) ? m_SmartDeviceList.at(_iIndex): nullPtr ;
}

// Find Device by Device Number
DevicePtr CDiviceList::FindDevice(DWORD _iDeviceNumber)
{
	DevicePtr returnDevice;
	if (m_SmartDeviceList.size() > 0 )
	{
		vector<DevicePtr>::iterator it;
		for ( it = m_SmartDeviceList.begin(); it != m_SmartDeviceList.end(); ++it)
		{
			if ((*it)->GetNumber() == _iDeviceNumber)
				return (*it);
		}
	}
	return returnDevice;
}
size_t CDiviceList::GetCount() const
{
	return m_SmartDeviceList.size();
}

DevicePtr CDiviceList::operator[] ( size_t _Index )
{
	DevicePtr nullPtr;
	return _Index < m_SmartDeviceList.size() ? m_SmartDeviceList[_Index] : nullPtr;
}
bool CDiviceList::operator()(DevicePtr pDevice1, DevicePtr pDevice2)
{
	return pDevice1->GetNumber() < pDevice2->GetNumber();
}

void CDiviceList::SORT()
{
	if (m_SmartDeviceList.size() > 0)
	{
		sort(m_SmartDeviceList.begin(),m_SmartDeviceList.end(),CDiviceList());
	}
}

//////////////////////////////////////////
/*			CPhysicalDevice				*/
//////////////////////////////////////////
CPhysicalDevice::CPhysicalDevice()
{
	m_hDevInfo = INVALID_HANDLE_VALUE;
	//memset(m_spDeviceInterfaceData,NULL,sizeof(m_spDeviceInterfaceData));
	//memset(m_spDevInfoData, NULL,sizeof(m_spDevInfoData)); 
}
CPhysicalDevice::~CPhysicalDevice()
{
	CloseDevInfo(m_hDevInfo);

}
DWORD CPhysicalDevice::GetDevicesCount()
{
	HDEVINFO hDevInfo = INVALID_HANDLE_VALUE;
	if (!this->GetHDEVINFO(hDevInfo))
		return 0;
	DWORD dwCount = 0;
	DWORD iErrorCode = 0;
	BOOL bNoDevices = FALSE;
	while(true) 
	{
		bNoDevices = this->GetNextDevice(dwCount);
		if (!bNoDevices)
			break;
		++dwCount;
	}

	if (hDevInfo != INVALID_HANDLE_VALUE)
		SetupDiDestroyDeviceInfoList(hDevInfo);
	
	return dwCount;
}

BOOL CPhysicalDevice::GetHDEVINFO(HDEVINFO &_hDevInfo)
{
	if (_hDevInfo == INVALID_HANDLE_VALUE)
		CloseDevInfo(_hDevInfo);

	_hDevInfo = SetupDiGetClassDevs(&DiskClassGuid,
									   NULL,
									   0,
									   DIGCF_PROFILE | DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	if (_hDevInfo == INVALID_HANDLE_VALUE )
		return FALSE;

	return TRUE;
}
BOOL CPhysicalDevice::GetNextDevice(DWORD _DevIndex)
{
	SP_DEVINFO_DATA spDeviceInfoData;

	ZeroMemory(&spDeviceInfoData, sizeof(SP_DEVINFO_DATA));
	spDeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	ZeroMemory(&m_spDeviceInterfaceData, sizeof(SP_DEVICE_INTERFACE_DATA));
	m_spDeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	BOOL bResult = SetupDiEnumDeviceInterfaces(m_hDevInfo,
												0,
												&DiskClassGuid,
												_DevIndex,
												&m_spDeviceInterfaceData);

	int k = 1;
	k = 2;

	return bResult;
}

BOOL CPhysicalDevice::GetDevicePath(IDevice *_pDevice)
{
	PSP_DEVICE_INTERFACE_DETAIL_DATA spOUTDevIntDetailData;
	m_spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	DWORD iErrorCode = 0;
	DWORD dwRequiredSize = 1;
	BOOL bStatus = FALSE;

	bStatus = SetupDiGetDeviceInterfaceDetail(m_hDevInfo,
						  					  &m_spDeviceInterfaceData,
											  NULL,
											  0,
											  &dwRequiredSize,
											  NULL);

	iErrorCode = GetLastError();

	DWORD dwInterfaceDetailDataSize = dwRequiredSize;

	spOUTDevIntDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(dwInterfaceDetailDataSize);

	if ( spOUTDevIntDetailData != NULL)
	{
		spOUTDevIntDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		bStatus = SetupDiGetDeviceInterfaceDetail(m_hDevInfo,
							  					  &m_spDeviceInterfaceData,
												  spOUTDevIntDetailData,
												  dwInterfaceDetailDataSize,
												  &dwRequiredSize,
												  &m_spDevInfoData);
		if ( bStatus )
		{
			_pDevice->SetPath(spOUTDevIntDetailData->DevicePath);
			delete [](char*)spOUTDevIntDetailData; // ???????????????????
		}

	}
	return bStatus;
}

BOOL CPhysicalDevice::GetDeviceName(IDevice *_pDevice)
{
	if (_pDevice == NULL)
		return FALSE;

	DWORD dwReturnedBytes = 0;
	DWORD dwRegDataType = 0;
	DWORD dwBufferSize = 0;
	BYTE *buffer;

	DWORD dwErrorCode = 0;
	dwErrorCode = GetLastError();

	SetupDiGetDeviceRegistryPropertyA(m_hDevInfo,
									 &m_spDevInfoData,
									 SPDRP_FRIENDLYNAME ,
									 &dwRegDataType,
									 NULL,
									 NULL,
									 &dwReturnedBytes);

	if (dwReturnedBytes == 0 )
		return FALSE;

	dwErrorCode = GetLastError();

	dwBufferSize = dwReturnedBytes;
	buffer = new BYTE[dwBufferSize];

	BOOL bResult = FALSE;
	bResult = SetupDiGetDeviceRegistryPropertyA(m_hDevInfo,
											   &m_spDevInfoData,
											   SPDRP_FRIENDLYNAME  ,
											   &dwRegDataType,
											   buffer,
											   dwBufferSize,
											   &dwReturnedBytes);



	_pDevice->SetName(buffer);
	
	delete buffer;

	return bResult;
}

BOOL CPhysicalDevice::GetMaxTransferSize(IDevice *_pDevice)
{
	HANDLE hDevice;
	if (_pDevice->GetPath().size() == 0)
		return FALSE;
	hDevice = CreateFile(_pDevice->GetPath().c_str(),
					   GENERIC_READ | GENERIC_WRITE,
					   FILE_SHARE_READ | FILE_SHARE_WRITE  ,
					   NULL,
					   OPEN_EXISTING,
					   0,
					   NULL);

	if ( hDevice == INVALID_HANDLE_VALUE )
	{
		DWORD dwError = GetLastError();
		return FALSE;
	}

	STORAGE_ADAPTER_DESCRIPTOR  pStorageAdapterDescription;
	pStorageAdapterDescription.Size = sizeof(STORAGE_ADAPTER_DESCRIPTOR);

	STORAGE_PROPERTY_QUERY	pQueryProperty;
	memset(&pQueryProperty,0,sizeof(pQueryProperty));
	pQueryProperty.PropertyId = StorageAdapterProperty;
	pQueryProperty.QueryType = PropertyStandardQuery;

	BOOL bResult = FALSE;
	DWORD dwBufferSize = 0;
	bResult = DeviceIoControl(hDevice,  // device to be queried
							IOCTL_STORAGE_QUERY_PROPERTY,  // operation to perform
                            &pQueryProperty, sizeof(STORAGE_PROPERTY_QUERY), // no input buffer
                            &pStorageAdapterDescription, sizeof(STORAGE_ADAPTER_DESCRIPTOR ),     // output buffer
                            &dwBufferSize,                 // # bytes returned
                            (LPOVERLAPPED) NULL);  // synchronous I/O

	CloseHandle(hDevice);
	if (bResult)
		_pDevice->SetMaxTransferSize(pStorageAdapterDescription.MaximumTransferLength);
		_pDevice->SetBusType(pStorageAdapterDescription.BusType);
	//_pDevice->setMpStorageAdapterDescription.
	return bResult;
	
}

BOOL CPhysicalDevice::GetDiskGeometry(IDevice *_pDevice)
{
	HANDLE hDevice;
	if (_pDevice->GetPath().size() == 0)
		return FALSE;
	hDevice = CreateFile(_pDevice->GetPath().c_str(),
					   GENERIC_READ | GENERIC_WRITE,
					   FILE_SHARE_READ | FILE_SHARE_WRITE  ,
					   NULL,
					   OPEN_EXISTING,
					   0,
					   NULL);

	if ( hDevice == INVALID_HANDLE_VALUE )
	{
		DWORD dwError = GetLastError();
		return FALSE;
	}

	DISK_GEOMETRY_EX pdgEx;

	DWORD dwBufferSize = 0;
	BOOL bResult = FALSE;
	bResult = DeviceIoControl(hDevice,  // device to be queried
							  IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,  // operation to perform
                              NULL, 0, // no input buffer
                              &pdgEx, sizeof(pdgEx),     // output buffer
                              &dwBufferSize,                 // # bytes returned
                              (LPOVERLAPPED) NULL);  // synchronous I/O

	if (bResult)
	{
		_pDevice->SetBytesPerSector(pdgEx.Geometry.BytesPerSector);
		_pDevice->SetSize(pdgEx.DiskSize.QuadPart);
		if (_pDevice->GetBytesPerSector() != 0)
		{
			_pDevice->SetSectorCount(pdgEx.DiskSize.QuadPart / _pDevice->GetBytesPerSector());
		}
		else
			_pDevice->SetSectorCount(0);
		//_pDevice->SetSectorCount(pdgEx.)
	}
	else
		return FALSE;
	  
	STORAGE_DEVICE_NUMBER ioDeviceNumber;
	dwBufferSize = 0;
	bResult = DeviceIoControl(hDevice,  // device to be queried
							  IOCTL_STORAGE_GET_DEVICE_NUMBER,  // operation to perform
                              NULL, 0, // no input buffer
                              &ioDeviceNumber, sizeof(ioDeviceNumber),     // output buffer
                              &dwBufferSize,                 // # bytes returned
                              (LPOVERLAPPED) NULL);  // synchronous I/O

	if (bResult)
		_pDevice->SetNumber(ioDeviceNumber.DeviceNumber);
	CloseHandle(hDevice);
	return bResult;

}
BOOL CPhysicalDevice::GetSerialNumber(IDevice *_pDevice)
{
/*	HANDLE hDevice = INVALID_HANDLE_VALUE;
	if (_pDevice->GetPath() == NULL)
		return FALSE;
	hDevice = CreateFile(_pDevice->GetPath(),
					   GENERIC_READ | GENERIC_WRITE,
					   FILE_SHARE_READ | FILE_SHARE_WRITE  ,
					   NULL,
					   OPEN_EXISTING,
					   0,
					   NULL);

	if ( hDevice == INVALID_HANDLE_VALUE )
	{
		DWORD dwError = GetLastError();
		return FALSE;
	}

	BYTE outBuff[512] = {0};
	STORAGE_DEVICE_DESCRIPTOR *pDeviceDesc = (STORAGE_DEVICE_DESCRIPTOR*)outBuff;  // -- Need DELETE

	ZeroMemory(outBuff,sizeof(outBuff));

	STORAGE_PROPERTY_QUERY	pQueryProperty;
	memset(&pQueryProperty,0,sizeof(pQueryProperty));
	pQueryProperty.PropertyId = StorageDeviceProperty;
	pQueryProperty.QueryType = PropertyStandardQuery;

	BOOL bResult = FALSE;
	DWORD dwOutSize = 0;

	bResult = DeviceIoControl(hDevice,  // device to be queried
							  IOCTL_STORAGE_QUERY_PROPERTY,  // operation to perform
							  &pQueryProperty, sizeof(STORAGE_PROPERTY_QUERY), // no input buffer
							  outBuff, sizeof(outBuff),     // output buffer
							  &dwOutSize,                 // # bytes returned
							  (LPOVERLAPPED) NULL);  // synchronous I/O

	if (bResult == FALSE)
	{
		DWORD iErrorCode = GetLastError();
		//TRACE(_T("Error (Get Serial Number) [Get SERIAL] %d"),iErrorCode);

		return GetSerialFromSmart(_pDevice);
	}
	else
	if (pDeviceDesc->SerialNumberOffset)
	{
		strBuff = (LPSTR)outBuff + pDeviceDesc->SerialNumberOffset;

		if (strBuff.GetLength() > 4)
		{
			for (INT i = 0; i < strBuff.GetLength(); i += 4)
			{
				strSerialNumber += ASCI2HEX(strBuff.Mid(i+2, 2));
				strSerialNumber += ASCI2HEX(strBuff.Mid(i, 2));
			}
			strSerialNumber.Trim();
			strBuff.Empty();
			m_DiskDrive.setSerialNumber(strSerialNumber);

		}
		else
		{
			GetSerialFromSmart(hDisk);
		}

	}	

*/
	return FALSE;
}
BOOL CPhysicalDevice::GetSystemDevice(CDiviceList & _deviceList)
{
	if (_deviceList.GetCount() == 0)
		return FALSE;

	UINT iSysDirSize = 0;
	TCHAR cSystemDirectory[MAX_PATH];
	ZeroMemory(cSystemDirectory,sizeof(TCHAR)*MAX_PATH);


	iSysDirSize = ::GetSystemDirectory(cSystemDirectory,MAX_PATH);
	if ( iSysDirSize == 0 )
		return FALSE;

	wstring sSystemVolName = L"\\\\.\\";
	sSystemVolName += cSystemDirectory[0];
	sSystemVolName += cSystemDirectory[1];

	HANDLE hVolume = CreateFile (sSystemVolName.c_str(),
							FILE_READ_ATTRIBUTES|SYNCHRONIZE|FILE_TRAVERSE,
							FILE_SHARE_READ | FILE_SHARE_WRITE  ,
							NULL,
							OPEN_EXISTING,
							0,
							NULL);

	if ( hVolume == INVALID_HANDLE_VALUE )
	{
		DWORD dwError = GetLastError();
		return FALSE;
	}
	
	STORAGE_DEVICE_NUMBER ioDeviceNumber;
	DWORD dwBufferSize = 0;
	BOOL bResult = DeviceIoControl(hVolume,  // device to be queried
						IOCTL_STORAGE_GET_DEVICE_NUMBER,  // operation to perform
						NULL, 0, // no input buffer
						&ioDeviceNumber, sizeof(ioDeviceNumber),     // output buffer
						&dwBufferSize,                 // # bytes returned
						(LPOVERLAPPED) NULL);  // synchronous I/O
	CloseHandle(hVolume);

	if (bResult)
	{
		DevicePtr ptrDev = _deviceList.FindDevice(ioDeviceNumber.DeviceNumber);
		if (ptrDev != NULL)
			ptrDev->SetSystemDisk(true);

		return TRUE;
	}



	return FALSE;
}

BOOL CPhysicalDevice::GetSerialFromSmart(IDevice *_pDevice)
{
	HANDLE hDevice = INVALID_HANDLE_VALUE;
	if (_pDevice->GetPath().size() == 0)
		return FALSE;
	hDevice = CreateFile(_pDevice->GetPath().c_str(),
					   GENERIC_READ | GENERIC_WRITE,
					   FILE_SHARE_READ | FILE_SHARE_WRITE  ,
					   NULL,
					   OPEN_EXISTING,
					   0,
					   NULL);

	if ( hDevice == INVALID_HANDLE_VALUE )
	{
		DWORD dwError = GetLastError();
		return FALSE;
	}

	BYTE buff[1024] = {0};

	PSENDCMDINPARAMS sendCommand = (PSENDCMDINPARAMS)&buff;
	sendCommand->irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;

	PSENDCMDOUTPARAMS outCommand = (PSENDCMDOUTPARAMS)&buff;	

	BOOL bResult = FALSE;
	DWORD dwBufferSize = 0;
	bResult = DeviceIoControl(hDevice,  // device to be queried
								SMART_RCV_DRIVE_DATA ,  // operation to perform
								sendCommand, (sizeof(SENDCMDINPARAMS)), // no input buffer
								outCommand,sizeof(buff),     // output buffer
								&dwBufferSize,                 // # bytes returned
								(LPOVERLAPPED) NULL);  // synchronous I/O


	if (bResult == FALSE)
	{
		DWORD iErrorCode = GetLastError();
		return FALSE;
	}
	else
	{
		IDENTIFY_DISK_ATA *PASPORT = NULL;
		PASPORT = (PIDENTIFY_DISK_ATA) outCommand->bBuffer;
		LONGLONG SectorCount = PASPORT->TotalNumberLBA48;
		if (SectorCount != 0)
		if (_pDevice->GetSectorCount() < SectorCount)
		{
			_pDevice->SetSectorCount(SectorCount);
		}

		BYTE *pBuffer = outCommand->bBuffer;
		BYTE buffer[528] = {0};
		for (int i = 0; i < 20; ++i)
			buffer[i] = pBuffer[i+20];

		BYTE *pSerial = new BYTE[528]; /// DELETE !!!!!!!!!!!!!!!!!
		memset(pSerial,0,528);
		for (int i = 0; i < 20; i+=2)
		{
			pSerial[i] = buffer[i+1];
			pSerial[i+1] = buffer[i];

		}
		string sSerial((const char *)pSerial);
		//remove_if(sSerial.begin(), sSerial.end(),isspace);
		trim(sSerial);
		
		_pDevice->SetSerialNumber((BYTE *)sSerial.c_str());
		delete pSerial;

		// Model Name
		memset(buffer,0,528);
		size_t ModelSize = sizeof(PASPORT->ModelNumber);
		memcpy(buffer,PASPORT->ModelNumber,ModelSize);
		ExchangeBytes(buffer,sizeof(PASPORT->ModelNumber));
		if (buffer[ModelSize - 2] == 'W' && buffer[ModelSize - 1] == 'P')
		{
			buffer[ModelSize - 2] = ' ';
			buffer[ModelSize - 1] = ' ';
			_pDevice->SetBusType(WRITE_PROTECTOR);
			string sModelName((const char *)buffer,ModelSize-2);
			trim(sModelName);
			_pDevice->SetName((BYTE *)sModelName.c_str());
		}



	}

	return bResult;
	CloseHandle(hDevice);

}
BOOL CPhysicalDevice::GetUsbSerial(IDevice * pDevice)
{
	//HANDLE hDevice = INVALID_HANDLE_VALUE;
	//if (pDevice->GetPath().size() == 0)
	//	return FALSE;
	//hDevice = CreateFile(pDevice->GetPath().c_str(),
	//				   GENERIC_READ | GENERIC_WRITE,
	//				   FILE_SHARE_READ | FILE_SHARE_WRITE  ,
	//				   NULL,
	//				   OPEN_EXISTING,
	//				   0,
	//				   NULL);

	//if ( hDevice == INVALID_HANDLE_VALUE )
	//{
	//	DWORD dwError = GetLastError();
	//	return FALSE;
	//}

	//char buffer[1000];
	//MEDIA_SERIAL_NUMBER_DATA UsbSerialNumber;
	//ZeroMemory(&UsbSerialNumber,sizeof(MEDIA_SERIAL_NUMBER_DATA));

	//DWORD dataSize = 0;
	//BOOL bResult = DeviceIoControl(hDevice,
	//							   IO_GET_MEDIA_SERIAL_NUMBER,
	//							   NULL,
	//							   0,
	//							   /*(LPVOID)*/&buffer,
	//							   sizeof(buffer),
	//							   &dataSize,
	//							   (LPOVERLAPPED)NULL);

	//if (bResult == 0)
	//{
	//	DWORD dwError = GetLastError();

	//	int k = 1;
	//	k = 1;

	//}

	//int k = 1;
	//k = 1;




	return FALSE;
}
BOOL CPhysicalDevice::GetDevices(CDiviceList & _deviceList)
{
    DWORD dwDeviceNumber = 0;
	DWORD iErrorCode = 0;
	BOOL bResult = FALSE;
	BOOL bNoDevices = FALSE;
	CDiskFactory  pDeviceFactory;
	IDevice *pDevice = NULL;

//#ifdef _DEBUG
//	pDevice = pDeviceFactory.CreateDevice();
//	bResult = GetDevice(pDevice,dwDeviceNumber);
//	_deviceList.AddDevice(pDevice);
//#endif



	while(true) 
	//for (int i = 0; i < 2 ; ++i)
	{
		pDevice = pDeviceFactory.CreateDevice();
		bResult = GetDevice(pDevice,dwDeviceNumber);
		if ( !bResult )
		{
			GetSystemDevice(_deviceList);
			//DevicePtr ptrDev = _deviceList.FindDevice(0);
			//ptrDev->SetSystemDisk(true);
			return FALSE;
		}
		_deviceList.AddDevice(pDevice);
		++dwDeviceNumber;
	}

	return bResult;
}
BOOL CPhysicalDevice::GetDevice(IDevice *_pDevice, DWORD _iMemberIndex)
{
	if (_pDevice == NULL)
		return FALSE;

	if (!this->GetHDEVINFO(m_hDevInfo))
		return FALSE;

	BOOL bResult = this->GetNextDevice(_iMemberIndex);

	if ( !bResult )
	{
		CloseDevInfo(m_hDevInfo);
		return FALSE;
	}


	if ( !(bResult = this->GetDevicePath(_pDevice)) )
		return FALSE;

	if ( !(bResult = this->GetDeviceName(_pDevice)) )
		return FALSE;

	if ( !(bResult = this->GetDiskGeometry(_pDevice)) )
		return FALSE;

	if ( !(bResult = this->GetMaxTransferSize(_pDevice)) )
		return FALSE;

	CloseDevInfo(m_hDevInfo);
	return TRUE;
}

BOOL CPhysicalDevice::CloseDevInfo(HDEVINFO &_hDevInfo)
{
	if (_hDevInfo != INVALID_HANDLE_VALUE)
	{
		SetupDiDestroyDeviceInfoList(_hDevInfo);
		_hDevInfo = INVALID_HANDLE_VALUE;
	}
	return TRUE;
}

void CPhysicalDevice::ExchangeBytes(BYTE * _Data, size_t _Size)
{
	BYTE  temp  = 0;
	for (size_t i = 0; i < _Size; i+=2)
	{
		temp = _Data[i];
		_Data[i] = _Data[i+1];
		_Data[i+1] = temp;
	}
}

