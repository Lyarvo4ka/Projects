#pragma once

#include "constants.h"
#include <windows.h>

#include <setupapi.h>
#pragma comment(lib, "setupapi.lib")

#include <memory>

namespace IO
{
	inline HANDLE OpenPhysicalDrive(const path_string & drive_path)
	{
		HANDLE hDevice = CreateFile(drive_path.c_str(),
									GENERIC_READ | GENERIC_WRITE,
									FILE_SHARE_READ | FILE_SHARE_WRITE,
									NULL,
									OPEN_EXISTING,
									0,
									NULL);

		return hDevice;

	}

	class PhysicalDrive
	{
	private:
		uint32_t drive_number_;
		uint32_t bytes_per_sector_;
		uint64_t number_sectors_;
		path_string path_;
		path_string drive_name_;
	public:
		PhysicalDrive()
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
		void setDriveName(const path_string drive_name)
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

	using PhysicalDrivePtr = std::shared_ptr<PhysicalDrive>;

	class PhysicalDriveList
	{
	private:
		std::vector<PhysicalDrivePtr> drive_list_;
	public:
		void add(PhysicalDrivePtr physical_drive)
		{
			if (!this->find_by_number(physical_drive->getDriveNumber()))
				drive_list_.push_back(physical_drive);
		}
		void remove(uint32_t drive_number)
		{
			for (auto it = drive_list_.begin(); it != drive_list_.end(); ++it)
			{
				if ((*it)->getDriveNumber() == drive_number)
					it = drive_list_.erase(it);

				if ( it == drive_list_.end())
					break;

			}
		}
		void remove_all()
		{
			drive_list_.clear();
		}
		PhysicalDrivePtr find_by_number(uint32_t drive_number)
		{
			for (auto find_index : drive_list_)
			{
				if (find_index->getDriveNumber() == drive_number)
					return find_index;
			}
			return nullptr;
		}
		uint32_t getSize() const
		{
			return drive_list_.size();
		}
	};


	class DriveAttributesReader
	{
	private:
		HDEVINFO hDevInfo_;
		SP_DEVICE_INTERFACE_DATA spDeviceInterfaceData_;
	//protected:
	//	virtual HDEVINFO SetupDiGetClassDevs(
	//		const GUID   *ClassGuid,
	//		PCTSTR Enumerator,
	//		HWND   hwndParent,
	//		DWORD  Flags
	//		) 
	//	{
	//		return ::SetupDiGetClassDevs(ClassGuid, Enumerator, hwndParent, Flags);
	//	}
	public:
		DriveAttributesReader()
		{
			InitHDevInfo(hDevInfo_);
		}

		~DriveAttributesReader()
		{
			CloseHDevInfo(hDevInfo_);
		}

		BOOL Initialize(uint32_t member_index)
		{
			InitHDevInfo(this->hDevInfo_);
			SetupDeviceInterfaceData(this->hDevInfo_, this->spDeviceInterfaceData_, member_index);
		}

		BOOL InitHDevInfo(HDEVINFO & hDevInfo)
		{
			if (hDevInfo != INVALID_HANDLE_VALUE)
				CloseHDevInfo(hDevInfo);

			hDevInfo = ::SetupDiGetClassDevs(&DiskClassGuid,
				NULL,
				0,
				DIGCF_PROFILE | DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
			if (hDevInfo == INVALID_HANDLE_VALUE)
				return FALSE;

			return TRUE;
		}

		BOOL isHDevInfoValid() const
		{
			return (hDevInfo_ == INVALID_HANDLE_VALUE);
		}

		BOOL CloseHDevInfo(HDEVINFO &hDevInfo)
		{
			if (hDevInfo != INVALID_HANDLE_VALUE)
			{
				::SetupDiDestroyDeviceInfoList(hDevInfo);
				hDevInfo = INVALID_HANDLE_VALUE;
			}
			return TRUE;
		}

		BOOL SetupDeviceInterfaceData(HDEVINFO &hDevInfo, SP_DEVICE_INTERFACE_DATA & spDeviceInterfaceData, uint32_t member_index)
		{
			::ZeroMemory(&spDeviceInterfaceData, sizeof(SP_DEVICE_INTERFACE_DATA));
			spDeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

			BOOL bResult = ::SetupDiEnumDeviceInterfaces(
				hDevInfo,
				0,
				&DiskClassGuid,
				member_index,
				&spDeviceInterfaceData
			);

			return bResult;
		}
		
		BOOL isValidGUID(GUID guid)
		{
			BOOL bValid = FALSE;
			if (guid.Data1 != 0)
				return TRUE;
			if (guid.Data2 != 0)
				return TRUE;
			if (guid.Data3 != 0)
				return TRUE;
			if (guid.Data4 != 0)
				return TRUE;

			return bValid;
		}

		BOOL readDriveAttributes(uint32_t member_index)
		{
			PhysicalDrive physical_drive;
			path_string drive_path;
			std::wstring drive_name;
			if (!SetupDeviceInterfaceData(hDevInfo_, spDeviceInterfaceData_, member_index))
				return FALSE;

			if (!ReadPathAndName(drive_path, drive_name))
				return FALSE;

			physical_drive.setDriveName(drive_name);
			physical_drive.setPath(drive_path);

			DISK_GEOMETRY_EX disk_geometry_ex = { 0 };
			if (!ReadDeviceGeometryEx(physical_drive.getPath(), disk_geometry_ex) )
				return FALSE;

			physical_drive.setBytesPerSector(disk_geometry_ex.Geometry.BytesPerSector);
			physical_drive.setNumberSectors(disk_geometry_ex.DiskSize.QuadPart);

			STORAGE_ADAPTER_DESCRIPTOR storage_descriptor = { 0 };
			if (!ReadDeviceDescriptor(drive_path, storage_descriptor))
				return FALSE;

			uint32_t drive_number = 0;
			if (!ReadDeviceNumber(drive_path, drive_number))
				return FALSE;

			physical_drive.setDriveNumber(drive_number);

#ifdef _DEBUG
			wprintf(L"Drive path = [ %s ].\r\n", physical_drive.getPath().c_str());
			wprintf(L"Drive name = [ %s ].\r\n", physical_drive.getDriveName().c_str());
			wprintf(L"Bytes per sector = [ %d ]\r\n", physical_drive.getBytesPerSector());
			wprintf(L"Number sectors = [ %llu ]\r\n", physical_drive.getNumberSectors());
			wprintf(L"Drive NUMBER = [ %d ]\r\n", physical_drive.getDriveNumber());
			wprintf(L"\r\n");
#endif
			return TRUE;
		}

		BOOL ReadPathAndName(path_string & drive_path, std::wstring & drive_name)
		{

			DWORD iErrorCode = 0;
			DWORD dwRequiredSize = 0;
			BOOL bStatus = FALSE;

			bStatus = ::SetupDiGetDeviceInterfaceDetail(hDevInfo_,
				&spDeviceInterfaceData_,
				NULL,
				0,
				&dwRequiredSize,
				NULL);

			iErrorCode = ::GetLastError();

			if ( iErrorCode != ERROR_INSUFFICIENT_BUFFER)
				return FALSE;

			DWORD dwInterfaceDetailDataSize = dwRequiredSize;


			char * pTmpBuffer = new char[dwInterfaceDetailDataSize];
			PSP_DEVICE_INTERFACE_DETAIL_DATA pspOUTDevIntDetailData;

			pspOUTDevIntDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA ) pTmpBuffer;
			::ZeroMemory(pspOUTDevIntDetailData, dwInterfaceDetailDataSize);

			SP_DEVINFO_DATA spDeviceInfoData;
			::ZeroMemory(&spDeviceInfoData, sizeof(SP_DEVINFO_DATA));
			spDeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);


			pspOUTDevIntDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			bStatus = ::SetupDiGetDeviceInterfaceDetail(hDevInfo_,
					&spDeviceInterfaceData_,
					pspOUTDevIntDetailData,
					dwInterfaceDetailDataSize,
					&dwRequiredSize,
					&spDeviceInfoData);
				if (bStatus)
				{
					drive_path = pspOUTDevIntDetailData->DevicePath;
					std::wstring tmp_drive_name;
					if (ReadDeviceName(spDeviceInfoData, tmp_drive_name))
						drive_name = tmp_drive_name;
					else
						drive_name = L"NO NAME";
				}

			iErrorCode = ::GetLastError();

			delete[] pTmpBuffer;

			return bStatus;
		}
		uint32_t getNameStringSize(HDEVINFO & hDevInfo, SP_DEVINFO_DATA & spDevInfoData, DWORD & dwRegDataType)
		{
			DWORD ReturnedBytes = 0;
			::SetupDiGetDeviceRegistryProperty(hDevInfo_,
				&spDevInfoData,
				SPDRP_FRIENDLYNAME,
				&dwRegDataType,
				NULL,
				NULL,
				&ReturnedBytes);
			return ReturnedBytes;
		}


		BOOL ReadDeviceName(SP_DEVINFO_DATA & spDevInfoData , std::wstring & drive_name)
		{
			DWORD dwRegDataType = 0;
			DWORD dwReturnedBytes = 0;
			DWORD dwErrorCode = 0;

			uint32_t nameBufferSize = getNameStringSize(hDevInfo_, spDevInfoData, dwRegDataType);


			if (nameBufferSize == 0)
				return FALSE;

			dwErrorCode = ::GetLastError();

			BYTE * buffer = new BYTE[nameBufferSize];

			BOOL bResult = FALSE;
			bResult = ::SetupDiGetDeviceRegistryProperty(hDevInfo_,
				&spDevInfoData,
				SPDRP_FRIENDLYNAME,
				&dwRegDataType,
				buffer,
				nameBufferSize,
				&dwReturnedBytes);

			spDevInfoData.ClassGuid.

			dwErrorCode = ::GetLastError();

			drive_name = (wchar_t*)buffer;
			delete []  buffer;

			return bResult;
		}

		BOOL ReadDeviceGeometryEx(const path_string & drive_path , DISK_GEOMETRY_EX & disk_geometry_ex)
		{
			HANDLE hDevice = OpenPhysicalDrive(drive_path);

			if (hDevice == INVALID_HANDLE_VALUE)
			{
				DWORD dwError = ::GetLastError();
				return FALSE;
			}

			DWORD returned_bytes = 0;
			BOOL bResult = FALSE;
			bResult = ::DeviceIoControl(hDevice,  // device to be queried
				IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,  // operation to perform
				NULL, 0, // no input buffer
				&disk_geometry_ex, sizeof(DISK_GEOMETRY_EX),     // output buffer
				&returned_bytes,                 // # bytes returned
				(LPOVERLAPPED)NULL);  // synchronous I/O

			::CloseHandle(hDevice);
			return bResult;
		}
		BOOL ReadDeviceNumber(const path_string & drive_path, uint32_t & drive_number)
		{
			HANDLE hDevice = OpenPhysicalDrive(drive_path);

			if (hDevice == INVALID_HANDLE_VALUE)
			{
				DWORD dwError = ::GetLastError();
				return FALSE;
			}

			DWORD returned_bytes = 0;
			STORAGE_DEVICE_NUMBER ioDeviceNumber;
			BOOL bResult = FALSE;
			bResult = ::DeviceIoControl(hDevice,  // device to be queried
				IOCTL_STORAGE_GET_DEVICE_NUMBER,  // operation to perform
				NULL, 0, // no input buffer
				&ioDeviceNumber, sizeof(ioDeviceNumber),     // output buffer
				&returned_bytes,                 // # bytes returned
				(LPOVERLAPPED)NULL);  // synchronous I/O

			::CloseHandle(hDevice);
			drive_number = ioDeviceNumber.DeviceNumber;
			return bResult;
		}
		BOOL ReadDeviceDescriptor(const path_string & drive_path, STORAGE_ADAPTER_DESCRIPTOR & storage_descriptor)
		{
			HANDLE hDevice = OpenPhysicalDrive(drive_path);

			if (hDevice == INVALID_HANDLE_VALUE)
			{
				DWORD dwError = ::GetLastError();
				return FALSE;
			}

			storage_descriptor.Size = sizeof(STORAGE_ADAPTER_DESCRIPTOR);

			STORAGE_PROPERTY_QUERY	pQueryProperty;
			memset(&pQueryProperty, 0, sizeof(pQueryProperty));
			pQueryProperty.PropertyId = StorageAdapterProperty;
			pQueryProperty.QueryType = PropertyStandardQuery;

			BOOL bResult = FALSE;
			DWORD dwBufferSize = 0;
			bResult = ::DeviceIoControl(hDevice,  // device to be queried
				IOCTL_STORAGE_QUERY_PROPERTY,  // operation to perform
				&pQueryProperty, sizeof(STORAGE_PROPERTY_QUERY), // no input buffer
				&storage_descriptor, sizeof(STORAGE_ADAPTER_DESCRIPTOR),     // output buffer
				&dwBufferSize,                 // # bytes returned
				(LPOVERLAPPED)NULL);  // synchronous I/O

			::CloseHandle(hDevice);

			return bResult;
		}
		BOOL ReadSerialNumber(const path_string & device_path)
		{
/*			HANDLE hDevice = OpenPhysicalDrive(device_path);

			if (hDevice == INVALID_HANDLE_VALUE)
			{
				DWORD dwError = ::GetLastError();
				return FALSE;
			}

			BYTE outBuff[512] = { 0 };
			STORAGE_DEVICE_DESCRIPTOR *pDeviceDesc = (STORAGE_DEVICE_DESCRIPTOR*)outBuff;

			::ZeroMemory(outBuff, sizeof(outBuff));

			STORAGE_PROPERTY_QUERY	pQueryProperty;
			memset(&pQueryProperty, 0, sizeof(pQueryProperty));
			pQueryProperty.PropertyId = StorageDeviceProperty;
			pQueryProperty.QueryType = PropertyStandardQuery;

			BOOL bResult = FALSE;
			DWORD dwOutSize = 0;

			bResult = ::DeviceIoControl(hDevice,  // device to be queried
				IOCTL_STORAGE_QUERY_PROPERTY,  // operation to perform
				&pQueryProperty, sizeof(STORAGE_PROPERTY_QUERY), // no input buffer
				outBuff, sizeof(outBuff),     // output buffer
				&dwOutSize,                 // # bytes returned
				(LPOVERLAPPED)NULL);  // synchronous I/O

			if (bResult == FALSE)
			{
				DWORD iErrorCode = GetLastError();

				return ReadSerialFromSmart(_pDevice);
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
						return ReadSerialFromSmart(_pDevice);
					}

				}

*/
			return FALSE;
		}
		BOOL ReadSerialFromSmart(const path_string & drive_path )
		{
/*			HANDLE hDevice = INVALID_HANDLE_VALUE;
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
			CloseHandle(hDevice);*/
			return FALSE;
		}



	};

/*
	class CPhysicalDevice
	{
	HDEVINFO m_hDevInfo;
	SP_DEVICE_INTERFACE_DATA m_spDeviceInterfaceData;
	SP_DEVINFO_DATA m_spDevInfoData;
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


	};
	*/
}
