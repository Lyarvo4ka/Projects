#pragma once

#include "constants.h"
#include <windows.h>
#include <setupapi.h>


#include <memory>

namespace IO
{
	class PhysicalDrive_t
	{
	private:
		uint32_t drive_number_;
		uint32_t bytes_per_sector_;
		uint64_t number_sectors_;
		path_string path_;
		std::wstring drive_name_;
	public:
		PhysicalDrive_t()
			: drive_number_(0)
			, number_sectors_(0)
			, bytes_per_sector_(0)
			, path_(L"")
			, drive_name_(L"")
		{

		}
		void setPath(const path_string & path)
		{
			path_ = path;
		}
		path_string getPath() const
		{
			return path_;
		}
		void setDriveName(const std::wstring drive_name)
		{
			drive_name_ = drive_name;
		}
		std::wstring getDriveName() const
		{
			return drive_name_;
		}
		void setDriveNumber(uint32_t drive_number)
		{
			drive_number_ = drive_number;
		}
		uint32_t getDriveNumber() const
		{
			return drive_number_;
		}
		void setNumberSectors(uint64_t number_sectors)
		{
			number_sectors_ = number_sectors;
		}
		uint64_t getNumberSectors() const
		{
			return number_sectors_;
		}
		void setBytesPerSector(uint32_t bytes_per_sector)
		{
			bytes_per_sector_ = bytes_per_sector;
		}
		uint32_t getBytesPerSector() const
		{
			return bytes_per_sector_;
		}

	};

	using PhysicalDrive = std::shared_ptr<PhysicalDrive_t>;

	class PhysicalDriveList
	{
	private:
		std::vector<PhysicalDrive> drive_list_;
	public:
		void add(PhysicalDrive physical_drive)
		{
			if (!this->find_by_number(physical_drive->getDriveNumber()))
				drive_list_.push_back(physical_drive);
		}
		void remove(uint32_t drive_number)
		{
			//for (auto it = drive_list_.begin(); it != drive_list_.end(); ++it)
			//{
			//	if ((*it)->getDriveNumber() == drive_number)
			//		it = drive_list_.erase(it);

			//		
			//}
		}
		PhysicalDrive find_by_number(uint32_t drive_number)
		{
			for (auto find_index : drive_list_)
			{
				if (find_index->getDriveNumber() == drive_number)
					return find_index;
			}
			return nullptr;
		}
		uint32_t getCount() const
		{
			return drive_list_.size();
		}
	};
/*
	class CPhysicalDevice
	{
	public:
		CPhysicalDevice()
			:m_hDevInfo(INVALID_HANDLE_VALUE)
			, m_spDeviceInterfaceData{ 0 }
			, m_spDevInfoData{ 0 }
		{

		}
		~CPhysicalDevice()
		{
			CloseDevInfo(m_hDevInfo);
		}

	//	bool readDriveInfo(PhysicalDrive * physical_drive)

		DWORD GetDevicesCount()
		{
			HDEVINFO hDevInfo = INVALID_HANDLE_VALUE;
			if (!this->GetHDEVINFO(hDevInfo))
				return 0;
			DWORD dwCount = 0;
			DWORD iErrorCode = 0;
			BOOL bNoDevices = FALSE;
			while (true)
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
		BOOL GetDevices(CDiviceList & _deviceList)
		{
			DWORD dwDeviceNumber = 0;
			DWORD iErrorCode = 0;
			BOOL bResult = FALSE;
			BOOL bNoDevices = FALSE;
			CDiskFactory  pDeviceFactory;
			IDevice *pDevice = NULL;

			while (true)
				//for (int i = 0; i < 2 ; ++i)
			{
				pDevice = pDeviceFactory.CreateDevice();
				bResult = GetDevice(pDevice, dwDeviceNumber);
				if (!bResult)
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
		BOOL GetDevice(IDevice *_pDevice, DWORD _iMemberIndex)
		{
			if (_pDevice == NULL)
				return FALSE;

			if (!this->GetHDEVINFO(m_hDevInfo))
				return FALSE;

			BOOL bResult = this->GetNextDevice(_iMemberIndex);

			if (!bResult)
			{
				CloseDevInfo(m_hDevInfo);
				return FALSE;
			}


			if (!(bResult = this->GetDevicePath(_pDevice)))
				return FALSE;

			if (!(bResult = this->GetDeviceName(_pDevice)))
				return FALSE;

			if (!(bResult = this->GetDiskGeometry(_pDevice)))
				return FALSE;

			if (!(bResult = this->GetMaxTransferSize(_pDevice)))
				return FALSE;

			if (!(bResult = this->GetSerialNumber(_pDevice)))
				return FALSE;

			CloseDevInfo(m_hDevInfo);
			return TRUE;
		}

		BOOL GetSerialFromSmart(IDevice *_pDevice)
		{
			HANDLE hDevice = INVALID_HANDLE_VALUE;
			if (_pDevice->GetPath().size() == 0)
				return FALSE;
			hDevice = CreateFile(_pDevice->GetPath().c_str(),
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

			if (hDevice == INVALID_HANDLE_VALUE)
			{
				DWORD dwError = GetLastError();
				return FALSE;
			}

			BYTE buff[1024] = { 0 };

			PSENDCMDINPARAMS sendCommand = (PSENDCMDINPARAMS)&buff;
			sendCommand->irDriveRegs.bCommandReg = IDE_ATA_IDENTIFY;

			PSENDCMDOUTPARAMS outCommand = (PSENDCMDOUTPARAMS)&buff;

			BOOL bResult = FALSE;
			DWORD dwBufferSize = 0;
			bResult = DeviceIoControl(hDevice,  // device to be queried
				SMART_RCV_DRIVE_DATA,  // operation to perform
				sendCommand, (sizeof(SENDCMDINPARAMS)), // no input buffer
				outCommand, sizeof(buff),     // output buffer
				&dwBufferSize,                 // # bytes returned
				(LPOVERLAPPED)NULL);  // synchronous I/O


			if (bResult == FALSE)
			{
				DWORD iErrorCode = GetLastError();
				return FALSE;
			}
			else
			{
				IDENTIFY_DISK_ATA *PASPORT = NULL;
				PASPORT = (PIDENTIFY_DISK_ATA)outCommand->bBuffer;
				LONGLONG SectorCount = PASPORT->TotalNumberLBA48;
				if (SectorCount != 0)
					if (_pDevice->GetSectorCount() < SectorCount)
					{
						_pDevice->SetSectorCount(SectorCount);
					}

				BYTE *pBuffer = outCommand->bBuffer;
				BYTE buffer[528] = { 0 };
				for (int i = 0; i < 20; ++i)
					buffer[i] = pBuffer[i + 20];

				BYTE *pSerial = new BYTE[528]; /// DELETE !!!!!!!!!!!!!!!!!
				memset(pSerial, 0, 528);
				for (int i = 0; i < 20; i += 2)
				{
					pSerial[i] = buffer[i + 1];
					pSerial[i + 1] = buffer[i];

				}
				string sSerial((const char *)pSerial);
				//remove_if(sSerial.begin(), sSerial.end(),isspace);
				boost::trim(sSerial);

				_pDevice->SetSerialNumber((BYTE *)sSerial.c_str());
				delete pSerial;

				// Model Name
				memset(buffer, 0, 528);
				size_t ModelSize = sizeof(PASPORT->ModelNumber);
				memcpy(buffer, PASPORT->ModelNumber, ModelSize);
				ExchangeBytes(buffer, sizeof(PASPORT->ModelNumber));
				if (buffer[ModelSize - 2] == 'W' && buffer[ModelSize - 1] == 'P')
				{
					buffer[ModelSize - 2] = ' ';
					buffer[ModelSize - 1] = ' ';
					_pDevice->SetBusType(WRITE_PROTECTOR);
					string sModelName((const char *)buffer, ModelSize - 2);
					boost::trim(sModelName);
					_pDevice->SetName((BYTE *)sModelName.c_str());
				}



			}

			return bResult;
			CloseHandle(hDevice);
		}
		BOOL GetUsbSerial(IDevice * pDevice)
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
			//							   &buffer,//(LPVOID)
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


		}
		BOOL CloseDevInfo(HDEVINFO &_hDevInfo)
		{
			if (_hDevInfo != INVALID_HANDLE_VALUE)
			{
				SetupDiDestroyDeviceInfoList(_hDevInfo);
				_hDevInfo = INVALID_HANDLE_VALUE;
			}
			return TRUE;
		}
	private:
		BOOL GetHDEVINFO(HDEVINFO &_hDevInfo)
		{
			if (_hDevInfo != INVALID_HANDLE_VALUE)
				CloseDevInfo(_hDevInfo);

			_hDevInfo = SetupDiGetClassDevs(&DiskClassGuid,
				NULL,
				0,
				DIGCF_PROFILE | DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
			if (_hDevInfo == INVALID_HANDLE_VALUE)
				return FALSE;

			return TRUE;
		}
		BOOL GetNextDevice(DWORD _DevIndex)
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

			return bResult;
		}
		BOOL GetDevicePath(IDevice *_pDevice)
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

			if (spOUTDevIntDetailData != NULL)
			{
				spOUTDevIntDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

				bStatus = SetupDiGetDeviceInterfaceDetail(m_hDevInfo,
					&m_spDeviceInterfaceData,
					spOUTDevIntDetailData,
					dwInterfaceDetailDataSize,
					&dwRequiredSize,
					&m_spDevInfoData);
				if (bStatus)
				{
					_pDevice->SetPath(spOUTDevIntDetailData->DevicePath);
					delete[](char*)spOUTDevIntDetailData; // ???????????????????
				}

			}
			return bStatus;
		}
		BOOL GetDeviceName(IDevice *_pDevice)
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
				SPDRP_FRIENDLYNAME,
				&dwRegDataType,
				NULL,
				NULL,
				&dwReturnedBytes);

			if (dwReturnedBytes == 0)
				return FALSE;

			dwErrorCode = GetLastError();

			dwBufferSize = dwReturnedBytes;
			buffer = new BYTE[dwBufferSize];

			BOOL bResult = FALSE;
			bResult = SetupDiGetDeviceRegistryPropertyA(m_hDevInfo,
				&m_spDevInfoData,
				SPDRP_FRIENDLYNAME,
				&dwRegDataType,
				buffer,
				dwBufferSize,
				&dwReturnedBytes);



			_pDevice->SetName(buffer);

			delete buffer;

			return bResult;
		}
		BOOL GetMaxTransferSize(IDevice *_pDevice)
		{
			HANDLE hDevice;
			if (_pDevice->GetPath().size() == 0)
				return FALSE;
			hDevice = CreateFile(_pDevice->GetPath().c_str(),
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

			if (hDevice == INVALID_HANDLE_VALUE)
			{
				DWORD dwError = GetLastError();
				return FALSE;
			}

			STORAGE_ADAPTER_DESCRIPTOR  pStorageAdapterDescription;
			pStorageAdapterDescription.Size = sizeof(STORAGE_ADAPTER_DESCRIPTOR);

			STORAGE_PROPERTY_QUERY	pQueryProperty;
			memset(&pQueryProperty, 0, sizeof(pQueryProperty));
			pQueryProperty.PropertyId = StorageAdapterProperty;
			pQueryProperty.QueryType = PropertyStandardQuery;

			BOOL bResult = FALSE;
			DWORD dwBufferSize = 0;
			bResult = DeviceIoControl(hDevice,  // device to be queried
				IOCTL_STORAGE_QUERY_PROPERTY,  // operation to perform
				&pQueryProperty, sizeof(STORAGE_PROPERTY_QUERY), // no input buffer
				&pStorageAdapterDescription, sizeof(STORAGE_ADAPTER_DESCRIPTOR),     // output buffer
				&dwBufferSize,                 // # bytes returned
				(LPOVERLAPPED)NULL);  // synchronous I/O

			CloseHandle(hDevice);
			if (bResult)
				_pDevice->SetMaxTransferSize(pStorageAdapterDescription.MaximumTransferLength);
			_pDevice->SetBusType(pStorageAdapterDescription.BusType);
			//_pDevice->setMpStorageAdapterDescription.
			return bResult;
		}
		BOOL GetDiskGeometry(IDevice *_pDevice)
		{
			HANDLE hDevice;
			if (_pDevice->GetPath().size() == 0)
				return FALSE;
			hDevice = CreateFile(_pDevice->GetPath().c_str(),
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

			if (hDevice == INVALID_HANDLE_VALUE)
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
				(LPOVERLAPPED)NULL);  // synchronous I/O

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
				(LPOVERLAPPED)NULL);  // synchronous I/O

			if (bResult)
				_pDevice->SetNumber(ioDeviceNumber.DeviceNumber);
			CloseHandle(hDevice);
			return bResult;
		}
		BOOL GetSerialNumber(IDevice *_pDevice)
		{
			HANDLE hDevice = INVALID_HANDLE_VALUE;
			if (_pDevice->GetPath().empty())
				return FALSE;
			hDevice = CreateFile(_pDevice->GetPath().c_str(),
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

			if (hDevice == INVALID_HANDLE_VALUE)
			{
				DWORD dwError = GetLastError();
				return FALSE;
			}

			BYTE outBuff[512] = { 0 };
			STORAGE_DEVICE_DESCRIPTOR *pDeviceDesc = (STORAGE_DEVICE_DESCRIPTOR*)outBuff;  // -- Need DELETE

			ZeroMemory(outBuff, sizeof(outBuff));

			STORAGE_PROPERTY_QUERY	pQueryProperty;
			memset(&pQueryProperty, 0, sizeof(pQueryProperty));
			pQueryProperty.PropertyId = StorageDeviceProperty;
			pQueryProperty.QueryType = PropertyStandardQuery;

			BOOL bResult = FALSE;
			DWORD dwOutSize = 0;

			bResult = DeviceIoControl(hDevice,  // device to be queried
				IOCTL_STORAGE_QUERY_PROPERTY,  // operation to perform
				&pQueryProperty, sizeof(STORAGE_PROPERTY_QUERY), // no input buffer
				outBuff, sizeof(outBuff),     // output buffer
				&dwOutSize,                 // # bytes returned
				(LPOVERLAPPED)NULL);  // synchronous I/O

			if (bResult == FALSE)
			{
				DWORD iErrorCode = GetLastError();
				//TRACE(_T("Error (Get Serial Number) [Get SERIAL] %d"),iErrorCode);

				return GetSerialFromSmart(_pDevice);
			}
			else
				if (pDeviceDesc->SerialNumberOffset)
				{
					std::string serial_number = (LPSTR)outBuff + pDeviceDesc->SerialNumberOffset;
					if (serial_number.size() > 0)
					{
						boost::trim(serial_number);
						_pDevice->SetSerialNumber((unsigned char*)serial_number.c_str());
						return TRUE;

					}
					else
					{
						return GetSerialFromSmart(_pDevice);
					}

				}


			return FALSE;
		}
		BOOL GetSystemDevice(CDiviceList & _deviceList)
		{
			if (_deviceList.GetCount() == 0)
				return FALSE;

			UINT iSysDirSize = 0;
			TCHAR cSystemDirectory[MAX_PATH];
			ZeroMemory(cSystemDirectory, sizeof(TCHAR)*MAX_PATH);


			iSysDirSize = ::GetSystemDirectory(cSystemDirectory, MAX_PATH);
			if (iSysDirSize == 0)
				return FALSE;

			wstring sSystemVolName = L"\\\\.\\";
			sSystemVolName += cSystemDirectory[0];
			sSystemVolName += cSystemDirectory[1];

			HANDLE hVolume = CreateFile(sSystemVolName.c_str(),
				FILE_READ_ATTRIBUTES | SYNCHRONIZE | FILE_TRAVERSE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

			if (hVolume == INVALID_HANDLE_VALUE)
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
				(LPOVERLAPPED)NULL);  // synchronous I/O
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
		void ExchangeBytes(BYTE * _Data, size_t _Size)
		{
			BYTE  temp = 0;
			for (size_t i = 0; i < _Size; i += 2)
			{
				temp = _Data[i];
				_Data[i] = _Data[i + 1];
				_Data[i + 1] = temp;
			}
		}

		HDEVINFO m_hDevInfo;
		SP_DEVICE_INTERFACE_DATA m_spDeviceInterfaceData;
		SP_DEVINFO_DATA m_spDevInfoData;
	};
	*/
}
