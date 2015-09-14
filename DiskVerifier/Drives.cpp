#include "StdAfx.h"

#include "Drives.h"
#include <algorithm>
using std::sort;

//////////////////////////////
//#include "TestMakeDll.h"
//////////////////////////////
CDrives::CDrives(void)
{
	//m_DiskDrive = new CDiskDrive();
}


CDrives::~CDrives(void)
{
}


void CDrives::AddDiskDrive(CDiskDrive _diskDrive)
{
	m_vecDrives.push_back(_diskDrive);
}

vector<CDiskDrive>& CDrives::getDiskDrives()
{
	return m_vecDrives;
}

size_t CDrives::getDiskDriveSize() const
{
	return m_vecDrives.size();
}

void CDrives::getDiskNames()
{
	//CDiskInfo InfoDisk;
	//DWORD dwIndex = 0;
	//IDevice *pDevice = NULL;
	//while ((pDevice = InfoDisk.GetDevice(dwIndex)) != NULL)
	//{
	//	CString str(pDevice->GetPath());
	//	m_DiskDrive.setDiskPath(str);
	//	str = pDevice->GetName();
	//	m_DiskDrive.setDiskName(str);
	//	str = pDevice->GetSerialNumber();
	//	m_DiskDrive.setSerialNumber(str);
	//	m_DiskDrive.setBytesPerSector(pDevice->GetBytesPerSector());
	//	m_DiskDrive.setSectorCount(pDevice->GetSectorCount());
	//	m_DiskDrive.setDiskNumber(pDevice->GetNumber());
	//	delete pDevice;
	//	AddDiskDrive(m_DiskDrive);

	//	++dwIndex;
	//}
	//TRACE("\r\nName = %s, \r\n\r\nPath = ",pDevice1->GetName());
	//TRACE(pDevice1->GetPath() );
	//TRACE("\r\n");
	//IDevice *pDevice2 = InfoDisk.GetDevice(1);
	//TRACE("\r\nName = %s, \r\n\r\nPath = ",pDevice2->GetName());
	//TRACE(pDevice2->GetPath() );
	//TRACE("\r\n");	
	//IDevice *pDevice3 = InfoDisk.GetDevice(2);
	HDEVINFO hDriveHandle = INVALID_HANDLE_VALUE;

	SP_DEVINFO_DATA spDeviceInfoData;
	SP_DEVICE_INTERFACE_DATA spDeviceInterfaceData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA spDevInterfaceDataDetail = NULL; 
    DWORD dwDeviceNumber = 0;

	int iErrorCode = 0;
	hDriveHandle = SetupDiGetClassDevs(&DiskClassGuid,
									   NULL,
									   0,
									   DIGCF_PROFILE | DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	if (hDriveHandle == INVALID_HANDLE_VALUE )
	{
		AfxMessageBox(_T("Is not get Disk Class"),MB_OK);
		exit(0);
	}


	BOOL bResult = FALSE;



	while(true) 
	{
		// Clear m_DiskDrive 
		m_DiskDrive.setSerialNumber(_T("!!! NO SERIAL !!!"));
		spDeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
		spDeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

		bResult = SetupDiEnumDeviceInterfaces(hDriveHandle,
											  0,
											  &DiskClassGuid,
											  dwDeviceNumber,
											  &spDeviceInterfaceData);

		iErrorCode = GetLastError();
											  
		if (!bResult)
			break;

		if ( getDiskPathName(hDriveHandle,spDeviceInterfaceData) )
		{
			//m_DiskDrive.setDiskNumber(dwDeviceNumber);
			GetDiskAttribute(m_DiskDrive.getDiskPath());
			AddDiskDrive(m_DiskDrive);
		}
		//bResult = SetupDiEnumDeviceInfo(hDriveHandle,dwDeviceNumber,&spDeviceInfoData);

		//if (!bResult)
		//	break;

		//stDeviceName = getDeviceName(hDriveHandle,spDeviceInfoData);

		//if (stDeviceName != _T(""))
		//	m_ListDevices.InsertString(dwDeviceNumber,stDeviceName);
		//	//OpenPhysicalDisk(stDeviceName);

		++dwDeviceNumber;
	}




	if (hDriveHandle != INVALID_HANDLE_VALUE)
		SetupDiDestroyDeviceInfoList(hDriveHandle);

}


bool CDrives::getDiskPathName(const HDEVINFO & _hDriveHandle, 
							  SP_DEVICE_INTERFACE_DATA &_DeviceInterfaceData)
{
	//SP_DEVICE_INTERFACE_DETAIL_DATA spINDevIntDetailData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA spOUTDevIntDetailData;

	SP_DEVINFO_DATA spDevInfoData;
	spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	int iErrorCode = 0;

	DWORD dwRequiredSize = 1;

	BOOL bStatus = FALSE;

	
	bStatus = SetupDiGetDeviceInterfaceDetail(_hDriveHandle,
						  					  &_DeviceInterfaceData,
											  NULL,
											  0,
											  &dwRequiredSize,
											  NULL);

	iErrorCode = GetLastError();

	//if (!bStatus)
	//	return _T("");

	DWORD dwInterfaceDetailDataSize = dwRequiredSize;

	spOUTDevIntDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(dwInterfaceDetailDataSize);



	if ( spOUTDevIntDetailData != NULL)
	{
		spOUTDevIntDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		bStatus = SetupDiGetDeviceInterfaceDetail(_hDriveHandle,
							  					  &_DeviceInterfaceData,
												  spOUTDevIntDetailData,
												  dwInterfaceDetailDataSize,
												  &dwRequiredSize,
												  &spDevInfoData);
		if ( bStatus )
		{

	//WCHAR *pPath = NULL;
	//pPath = spOUTDevIntDetailData->DevicePath;
	//size_t iSize1 = wcslen(pPath);
	//IDeviceFactory *pDeviceFactory = new CDiskFactory();
	//IDevice *pDevice = NULL;
	//pDevice = pDeviceFactory->CreateDevice();
	//delete pDeviceFactory;
	//CString strPath1 = spOUTDevIntDetailData->DevicePath;
	//int iLength = strPath1.GetLength();

	//pDevice->SetPath( spOUTDevIntDetailData->DevicePath );
	//CString strPath(pDevice->GetPath());

	//TRACE(pDevice->GetPath());
	//delete pDevice;


			//delete pPath;
			
			m_DiskDrive.setDiskPath(spOUTDevIntDetailData->DevicePath); // Path to Device !!!
			m_DiskDrive.setDiskName(getDeviceName(_hDriveHandle,spDevInfoData));
			delete [](char*)spOUTDevIntDetailData; // ???????????????????
		//	spINDevIntDetailData = spOUTDevIntDetailData;
			return true;
		}
		//OpenPhysicalDisk(	str );

	}



	return false;						
}


CString CDrives::getDeviceName(const HDEVINFO & _hDriveHandle, SP_DEVINFO_DATA & _DeviceInfoData)
{
	DWORD dwReturnedBytes = 0;
	DWORD dwRegDataType = 0;
	DWORD dwBufferSize = 0;
	//LPTSTR buffer = NULL;

	BYTE *buffer;
	PBYTE pBuffer = NULL;

	CString stBuffer;

	DWORD dwErrorCode = 0;
	dwErrorCode = GetLastError();

	SetupDiGetDeviceRegistryPropertyA(_hDriveHandle,
									 &_DeviceInfoData,
									 SPDRP_FRIENDLYNAME ,
									 &dwRegDataType,
									 NULL,
									 NULL,
									 &dwReturnedBytes);

	if (dwReturnedBytes == 0 )
		return _T("");

	//dwErrorCode = GetLastError();

	dwBufferSize = dwReturnedBytes;
	buffer = new BYTE[dwBufferSize];

	SetupDiGetDeviceRegistryPropertyA(_hDriveHandle,
									 &_DeviceInfoData,
									 SPDRP_FRIENDLYNAME  ,
									 &dwRegDataType,
									 buffer,
									 dwBufferSize,
									 &dwReturnedBytes);


	//IDevice *pDevice = NULL;
	//IDeviceFactory *pDeviceFactory = new CDiskFactory();
	//pDevice = pDeviceFactory->CreateDevice();
	//delete pDeviceFactory;
	//pDevice->SetName(buffer);
	//TRACE("\r\n%s\r\n",pDevice->GetName());
	//stBuffer = pDevice->GetName()/*buffer*/;
	//delete pDevice;
	stBuffer = buffer;

	delete buffer;

	return stBuffer;
	
}

BOOL CDrives::GetSerialFromSmart(HANDLE _hDevice)
{
	BYTE buff[1024] = {0};

	PSENDCMDINPARAMS sendCommand = (PSENDCMDINPARAMS)&buff;
	sendCommand->irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;

	PSENDCMDOUTPARAMS outCommand = (PSENDCMDOUTPARAMS)&buff;	

	BOOL bResult = FALSE;
	DWORD dwBufferSize = 0;
	bResult = DeviceIoControl(_hDevice,  // device to be queried
								SMART_RCV_DRIVE_DATA ,  // operation to perform
								sendCommand, (sizeof(SENDCMDINPARAMS)), // no input buffer
								outCommand,sizeof(buff),     // output buffer
								&dwBufferSize,                 // # bytes returned
								(LPOVERLAPPED) NULL);  // synchronous I/O


	if (bResult == FALSE)
	{
		DWORD iErrorCode = GetLastError();
		TRACE(_T("Error (Get Serial Number) [Get SERIAL] %d"),iErrorCode);
	}
	else
	{

		BYTE *pBuffer = outCommand->bBuffer;
		BYTE buffer[528] = {0};

		for (int i = 0; i < 528; ++i)
		{
			buffer[i] = pBuffer[i];
		}
	
		m_DiskDrive.setSerialNumber(getSerialNumber(pBuffer));
	}

	return bResult;
}



bool CDrives::GetDiskAttribute(const CString & _csDiskObjectName)
{
	HANDLE hDisk;

	//CString csDiskName(TEXT("\\\\.\\PhysicalDrive0"));
	hDisk = CreateFile(_csDiskObjectName,
					   GENERIC_READ | GENERIC_WRITE,
					   FILE_SHARE_READ | FILE_SHARE_WRITE  ,
					   NULL,
					   OPEN_EXISTING,
					   0,
					   NULL);


//	CM_Get_DevNode_Status

	if ( hDisk == INVALID_HANDLE_VALUE )
	{
		DWORD dwError = GetLastError();
		TRACE("Error Open Device #%d\r\n",dwError);
		AfxMessageBox(_T("This program requires administrative privileges"),MB_OK);
		exit(0);
	}
	

	int iErrorCode = 0;

	DWORD junk = 0;
	BOOL bResult = FALSE;



	//pDeviceDesc.Size = sizeof(STORAGE_DEVICE_DESCRIPTOR);
	CString strSerialNumber;
	CString strBuff;
	BYTE outBuff[512] = {0};
	STORAGE_DEVICE_DESCRIPTOR *pDeviceDesc = (STORAGE_DEVICE_DESCRIPTOR*)outBuff;  // -- Need DELETE

	ZeroMemory(outBuff,sizeof(outBuff));

	STORAGE_PROPERTY_QUERY	pQueryProperty;
	memset(&pQueryProperty,0,sizeof(pQueryProperty));
	pQueryProperty.PropertyId = StorageDeviceProperty;
	pQueryProperty.QueryType = PropertyStandardQuery;


	bResult = DeviceIoControl(hDisk,  // device to be queried
							  IOCTL_STORAGE_QUERY_PROPERTY,  // operation to perform
							  &pQueryProperty, sizeof(STORAGE_PROPERTY_QUERY), // no input buffer
							  outBuff, sizeof(outBuff),     // output buffer
							  &junk,                 // # bytes returned
							  (LPOVERLAPPED) NULL);  // synchronous I/O

	if (bResult == FALSE)
	{
		iErrorCode = GetLastError();
		TRACE(_T("Error (Get Serial Number) [Get SERIAL] %d"),iErrorCode);
		GetSerialFromSmart(hDisk);
	}
	else
	if (pDeviceDesc->SerialNumberOffset)
	{
		strBuff = (LPSTR)outBuff + pDeviceDesc->SerialNumberOffset;

		if (strBuff.GetLength() > 4)
		{
			for (INT i = 0; i < strBuff.GetLength(); i += 4)
			{
				if ( ( i +4 ) < strBuff.GetLength() )
				{
 					strSerialNumber += ASCI2HEX(strBuff.Mid(i+2, 2));
					strSerialNumber += ASCI2HEX(strBuff.Mid(i, 2));
				}
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



/////


	STORAGE_ADAPTER_DESCRIPTOR  pStorageAdapterDescription;
	pStorageAdapterDescription.Size = sizeof(STORAGE_ADAPTER_DESCRIPTOR);

	if (GetStorageDescription(hDisk, pStorageAdapterDescription) )
		m_DiskDrive.setMaxTransferSize(pStorageAdapterDescription.MaximumTransferLength);


	//DISK_GEOMETRY pdg;

	//bResult = DeviceIoControl(hDisk,  // device to be queried
	//						  IOCTL_DISK_GET_DRIVE_GEOMETRY,  // operation to perform
 //                             NULL, 0, // no input buffer
 //                             &pdg, sizeof(pdg),     // output buffer
 //                             &junk,                 // # bytes returned
 //                             (LPOVERLAPPED) NULL);  // synchronous I/O



	DISK_GEOMETRY_EX pdgEx;

	junk = 0;
	bResult = DeviceIoControl(hDisk,  // device to be queried
							  IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,  // operation to perform
                              NULL, 0, // no input buffer
                              &pdgEx, sizeof(pdgEx),     // output buffer
                              &junk,                 // # bytes returned
                              (LPOVERLAPPED) NULL);  // synchronous I/O

	//delete [] (char*)pdgEx.Data;

	m_DiskDrive.setBytesPerSector(pdgEx.Geometry.BytesPerSector);
	//m_DiskDrive.
	m_DiskDrive.setSectorCount(pdgEx.DiskSize.QuadPart);


	  
	STORAGE_DEVICE_NUMBER ioDeviceNumber;
	junk = 0;
	bResult = DeviceIoControl(hDisk,  // device to be queried
							  IOCTL_STORAGE_GET_DEVICE_NUMBER,  // operation to perform
                              NULL, 0, // no input buffer
                              &ioDeviceNumber, sizeof(ioDeviceNumber),     // output buffer
                              &junk,                 // # bytes returned
                              (LPOVERLAPPED) NULL);  // synchronous I/O


	m_DiskDrive.setDiskNumber(ioDeviceNumber.DeviceNumber);

	//GETVERSIONINPARAMS smartVers;
	//bResult = DeviceIoControl(hDisk,  // device to be queried
	//						  SMART_GET_VERSION ,  // operation to perform
 //                             NULL, 0, // no input buffer
 //                             &smartVers, sizeof(GETVERSIONINPARAMS),     // output buffer
 //                             &junk,                 // # bytes returned
 //                             (LPOVERLAPPED) NULL);  // synchronous I/O

	//ERROR_INSUFFICIENT_BUFFER





	return false;
}

BOOL CDrives::GetStorageDescription(HANDLE _hDevice, STORAGE_ADAPTER_DESCRIPTOR &_rStorageAdapterDescription)
{
	STORAGE_PROPERTY_QUERY	pQueryProperty;
	memset(&pQueryProperty,0,sizeof(pQueryProperty));
	pQueryProperty.PropertyId = StorageAdapterProperty;
	pQueryProperty.QueryType = PropertyStandardQuery;

	BOOL bResult = FALSE;
	DWORD dwBufferSize = 0;
	bResult = DeviceIoControl(_hDevice,  // device to be queried
							IOCTL_STORAGE_QUERY_PROPERTY,  // operation to perform
                            &pQueryProperty, sizeof(STORAGE_PROPERTY_QUERY), // no input buffer
                            &_rStorageAdapterDescription, sizeof(STORAGE_ADAPTER_DESCRIPTOR ),     // output buffer
                            &dwBufferSize,                 // # bytes returned
                            (LPOVERLAPPED) NULL);  // synchronous I/O

	return bResult;
}


CString  CDrives::getSerialNumber(BYTE * pPasport)
{
	CString csSerialNumber;

	BYTE buffer[528] = {0};

	for (int i = 0; i < 20; ++i)
	{
		buffer[i] = pPasport[i+20];

	}
	for (int i = 0; i < 20; i+=2)
	{
		csSerialNumber += buffer[i+1];
		csSerialNumber += buffer[i];

	}
	return csSerialNumber;
}
BYTE * CDrives::SerialNumberBYTE(BYTE * pPasport)
{
	BYTE buffer[528] = {0};

	for (int i = 0; i < 20; ++i)
	{
		buffer[i] = pPasport[i+20];

	}
	BYTE *pBuffer = new BYTE[528]; /// DELETE !!!!!!!!!!!!!!!!!
	memset(pBuffer,0,528);
	for (int i = 0; i < 20; i+=2)
	{
		pBuffer[i] = buffer[i+1];
		pBuffer[i+1] += buffer[i];

	}
	return pBuffer;
}



wchar_t CDrives::ASCI2HEX(CString strASCI)
{
return (WCHAR2HEX(strASCI[0]) << 4) + WCHAR2HEX(strASCI[1]);

}

BYTE CDrives::WCHAR2HEX(wchar_t chASCI)
{
	BYTE	nHEX = 0;
	if (chASCI > 0x2F && chASCI < 0x40) nHEX = chASCI - 0x30;
	else if (chASCI > 0x40 && chASCI < 0x47) nHEX = chASCI - 0x37;
	else if (chASCI > 0x60 && chASCI < 0x67) nHEX = chASCI - 0x57;
	return nHEX;
}


void sortDevices(vector<CDiskDrive> & _vecDrives)
{
	if (_vecDrives.size() > 0)
	{
		//vector<CDiskDrive>::reverse_iterator rit;
		//for (rit = _vecDrives.rbegin(); rit != _vecDrives.rend(); ++rit)
		//{
		//	
		//}

		sort(_vecDrives.rbegin(),_vecDrives.rend(),PredFunc);

	}
}

bool PredFunc(CDiskDrive _drive1,CDiskDrive _drive2)
{
	return (_drive1.getDiskNumber() < _drive2.getDiskNumber());
}


void setDevices(CListCtrl* _pListDrives, CDrives * _pDrives,vector<CDiskDrive> &_vecDrives)
{
	_pListDrives->InsertColumn(0,_T("#"),LVCFMT_LEFT,-1);
	_pListDrives->InsertColumn(1,stDisk_NAME,LVCFMT_LEFT,-1);
	_pListDrives->InsertColumn(2,stSector_Count,LVCFMT_LEFT,-1);
	_pListDrives->InsertColumn(3,stDiskSize,LVCFMT_LEFT,-1);
	_pListDrives->InsertColumn(4,stSerial_Number,LVCFMT_LEFT,-1);
	_pListDrives->InsertColumn(5,stBytes_Per_Secors,LVCFMT_LEFT,-1);


	_vecDrives = _pDrives->getDiskDrives();
	
	vector<CDiskDrive>::reverse_iterator rit;
	sort(_vecDrives.begin(),_vecDrives.end(),PredFunc);
	CDiskDrive bufDrive;
	for (rit = _vecDrives.rbegin(); rit != _vecDrives.rend(); ++rit)
	{
	
		bufDrive = *rit;
		int iIndex = 0;
		CString str;
		// NUMBER DISK
		str.Format(_T("%i"),bufDrive.getDiskNumber());
		iIndex = _pListDrives->InsertItem(LVIF_TEXT|LVIF_STATE,0,str,LVIS_SELECTED,LVIS_SELECTED,0,0);

		// Disk Name
		_pListDrives->SetItem(iIndex,1,LVIF_TEXT|LVIF_STATE,bufDrive.getDiskName(),LVIS_SELECTED,LVIS_SELECTED,0,0);
		// Sector Count
		str = _T("");
		str.Format(_T("%I64d"),bufDrive.getSectorCount());
		_pListDrives->SetItem(iIndex,2,LVIF_TEXT|LVIF_STATE,str,LVIS_SELECTED,LVIS_SELECTED,0,0);

		// Disk Size
		str.Format(_T("%i GB"),bufDrive.getDiskSize());
		_pListDrives->SetItem(iIndex,3,LVIF_TEXT|LVIF_STATE,str,LVIS_SELECTED,LVIS_SELECTED,0,0);

		// Serial Number
		_pListDrives->SetItem(iIndex,4,LVIF_TEXT|LVIF_STATE,bufDrive.getSerialNumber(),LVIS_SELECTED,LVIS_SELECTED,0,0);
		// Bytes Per Sector
		str = _T("");
		str.Format(_T("%i"),bufDrive.getBytesPerSector());
		_pListDrives->SetItem(iIndex,5,LVIF_TEXT|LVIF_STATE,str,LVIS_SELECTED,LVIS_SELECTED,0,0);

		//str.Format(_T("%i"),bufDrive.g());
	}

	_pListDrives->SetColumnWidth(0,LVSCW_AUTOSIZE_USEHEADER);
	_pListDrives->SetColumnWidth(1,LVSCW_AUTOSIZE_USEHEADER);
	_pListDrives->SetColumnWidth(2,LVSCW_AUTOSIZE_USEHEADER);
	_pListDrives->SetColumnWidth(3,LVSCW_AUTOSIZE_USEHEADER);
	_pListDrives->SetColumnWidth(4,LVSCW_AUTOSIZE_USEHEADER);
	_pListDrives->SetColumnWidth(5,LVSCW_AUTOSIZE_USEHEADER);
	_pListDrives->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS);
}

bool AddSelectedDrive(int iPos, vector<CDiskDrive> & _vecSource, vector<CDiskDrive> & _vecSelected)
{
	CDiskDrive selDisks;
	if (!_vecSource.empty())
	{
		if (_vecSelected.empty())
			_vecSelected.push_back(_vecSource.at(iPos));
		else
		{
			for (size_t i = 0; i < _vecSelected.size(); ++i)
			{
				if ( _vecSelected.at(i).getDiskNumber() == _vecSource.at(iPos).getDiskNumber() )
					return false;
			}
			_vecSelected.push_back(_vecSource.at(iPos));
		}	
		return true;
	}
	return false;
}
