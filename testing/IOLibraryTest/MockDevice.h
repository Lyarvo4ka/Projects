#pragma once

#include "IOLibrary/IODevice.h"

using namespace IO;


const uint32_t fake_hadnle = 0x46414B45;

inline void ShowPhysicalDriveInfo(IO::PhysicalDrivePtr physical_drive)
{
	wprintf(L"Drive path = [ %s ].\n", physical_drive->getPath().c_str());
	wprintf(L"Drive name = [ %s ].\n", physical_drive->getDriveName().c_str());
	wprintf(L"Bytes per sector = [ %d ].\n", physical_drive->getBytesPerSector());
	wprintf(L"Number sectors = [ %llu ].\n", physical_drive->getNumberSectors());
	wprintf(L"Drive NUMBER = [ %d ].\n", physical_drive->getDriveNumber());
	printf("Serial number [%s].\n", physical_drive->getSerialNumber().c_str());

	wprintf(L"\r\n");
}

inline PhysicalDrivePtr create_fake_physical_drive(uint32_t drive_number)
{
	auto physical_drive = std::make_shared<PhysicalDrive>();
	physical_drive->setDriveNumber(drive_number);
	physical_drive->setDriveName(L"Physical drive " + std::to_wstring(drive_number));
	physical_drive->setPath(L"drive path " + std::to_wstring(drive_number));
	physical_drive->setTransferLength(1024);
	physical_drive->setNumberSectors(1000);
	physical_drive->setBytesPerSector(512);
	physical_drive->setSerialNumber("serial number " + std::to_string(drive_number));
	return physical_drive;

}
class MockSystemIO :
	public SystemIO
{
public:
	BOOL ReadFile(
		HANDLE       hFile,
		LPVOID       lpBuffer,
		DWORD        nNumberOfBytesToRead,
		LPDWORD      lpNumberOfBytesRead,
		LPOVERLAPPED lpOverlapped) override
	{
		*lpNumberOfBytesRead = nNumberOfBytesToRead;
		return TRUE;
	}
	HANDLE OpenPhysicalDrive(const path_string & drive_path) override
	{
		return (HANDLE)fake_hadnle;
	}
};


struct  F_MockDiskDevice
{
	F_MockDiskDevice()
	{
		disk_device_ = new DiskDevice(create_fake_physical_drive(0) , std::make_unique<MockSystemIO>());

	
	}
	~F_MockDiskDevice()
	{
		delete disk_device_;
	}

	DiskDevice *disk_device_;
};


