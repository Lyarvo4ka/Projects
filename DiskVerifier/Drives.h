#pragma once
#include "diskdrive.h"
#include <vector>
using std::vector;

   #include <windows.h>
   #include <setupapi.h>
   #include <devguid.h>
   #include <regstr.h>
   #include <WinIoCtl.h>  
#pragma comment(lib, "setupapi.lib")
//#include "..\DeviceLibrary\Devices.h"

#define  IDE_ATA_IDENTIFY    0xEC  //  Returns ID sector for ATA.


const CString stDisk_NAME = _T("Disk NAME ");
const CString stSerial_Number = _T("Serial Number ");
const CString stBytes_Per_Secors = _T("BPS ");
const CString stSector_Count = _T("Sector count ");
const CString stDiskSize = _T("Size ");

#ifndef _DRIVES_H
#define _DRIVES_H



class CDrives /*:
	public CDiskDrive*/
{
protected:
	wchar_t ASCI2HEX(CString strASCI);
	BYTE WCHAR2HEX(wchar_t chASCI);
public:
	CDrives(void);
	//CDrives(CDiskDrive _diskDrive);
	void AddDiskDrive(CDiskDrive _diskDrive);
	~CDrives(void);
	CString getDeviceName(const HDEVINFO & _hDriveHandle,  SP_DEVINFO_DATA & _DeviceInfoData);
	bool getDiskPathName( const HDEVINFO &, SP_DEVICE_INTERFACE_DATA & );
	void getDiskNames();
	size_t getDiskDriveSize() const;
	vector<CDiskDrive>& getDiskDrives();
	bool GetDiskAttribute(const CString & _csDiskObjectName = 0);
	CString getSerialNumber(BYTE * pPasport);
	BYTE * SerialNumberBYTE(BYTE * pPasport);
	BOOL GetStorageDescription(HANDLE _hDevice, STORAGE_ADAPTER_DESCRIPTOR &_rStorageAdapterDescription);
	BOOL GetSerialFromSmart(HANDLE _hDevice);

private:

	vector<CDiskDrive> m_vecDrives;
	CDiskDrive m_DiskDrive;
	//CDiviceList m_DeviceList;
};

void setDevices(CListCtrl* _pListDrives, CDrives * _pDrives,vector<CDiskDrive> &_vecDrives);
bool AddSelectedDrive(int iPos, vector<CDiskDrive> & _vecSource, vector<CDiskDrive> & _vecSelected);
void sortDevices(vector<CDiskDrive> & _vecDrives);
bool PredFunc(CDiskDrive _drive1,CDiskDrive _drive2);

#endif