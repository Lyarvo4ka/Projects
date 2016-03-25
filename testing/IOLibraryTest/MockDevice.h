#pragma once

#include "IOLibrary/IODevice.h"

using namespace IO;

class MockDiskDevice :
	public DiskDevice
{
public:
	MockDiskDevice(PhysicalDrivePtr physical_drive)
		: DiskDevice(physical_drive)
	{}
private:
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
		return (HANDLE)nullptr;
	}
};

struct  F_MockDiskDevice
{
	F_MockDiskDevice()
	{
		mock_diskdevice_ = new MockDiskDevice(create_physical_drive(0));

	
	}
	~F_MockDiskDevice()
	{
		delete mock_diskdevice_;
	}

	MockDiskDevice *mock_diskdevice_;
};

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

inline PhysicalDrivePtr create_physical_drive(uint32_t drive_number)
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
