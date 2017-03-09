
#include <boost/lexical_cast.hpp>
#include "IOLibrary/IODevice.h"
#include "IOLibrary/AbstractRaw.h"

const int param_count = 1;
const int number = 1;

int _tmain(int argc, TCHAR **argv)
{

	if (argc != param_count)
	{
		wprintf(L"Wrong params.\n");
		return -1;

	}

	auto drive_number = boost::lexical_cast<uint32_t>(argv[number]);


	auto drive_list = IO::ReadPhysicalDrives();
	auto physical_drive = drive_list.find_by_number(drive_number);
	if (!physical_drive)
	{
		wprintf(L"Wrong drive number.\n");
		return -1;
	}
	wprintf(L"You selected\n");
	wprintf(L"Number : %d\n", drive_number);
	auto drive_name = physical_drive->getDriveName().c_str();
	wprintf(L"Name : %s\n", drive_name);
	printf("Serial number : %s\n", physical_drive->getSerialNumber().c_str());
	wprintf(L"Size : %I64d (bytes)", physical_drive->getSize());

	IO::SystemIO systemIO;
	auto drive_handle = systemIO.OpenPhysicalDrive(physical_drive->getPath());
	if (drive_handle == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Error open drive .\n");
		return -1;
	}

	uint64_t sector_number = 0;

	char number_data[17];

	uint8_t sector_data[default_sector_size];
	uint8_t block_data[default_block_size];

	memset(sector_data, 0x00, default_sector_size);

	const char begin_name[] = "           BEGIN";
	memcpy(sector_data, begin_name, 16);
	sprintf_s(number_data, 17, "%.16ld", sector_number);
	memcpy(sector_data + 16, number_data, 16);

	// write first sector
	DWORD bytesWritten = 0;

	if (!WriteFile(drive_handle, sector_data, default_sector_size, &bytesWritten, NULL))
	{
		printf("Error write to drive.");
		return -1;
	}
	if (bytesWritten == 0)
	{
		printf("Error write to drive.");
		return -1;
	}

	uint64_t offset = default_sector_size;

	LARGE_INTEGER liOffset = { 0 };

	liOffset.QuadPart = offset;

	while (liOffset.QuadPart < physical_drive->getSize())
	{
		ZeroMemory(block_data, default_block_size);

		for (DWORD iSector = 0; iSector < defalut_number_sectors; ++iSector)
		{
			memset(number_data, 0, 17);
			sprintf_s(number_data, 17, "%.16ld", ++sector_number);
			memcpy(block_data + iSector*default_sector_size, number_data, 16);
		}

		::SetFilePointerEx(drive_handle, liOffset, NULL, FILE_BEGIN);
		if (!WriteFile(drive_handle, block_data, default_sector_size, &bytesWritten, NULL))
		{
			printf("Error write to drive.");
			return -1;
		}
		if (bytesWritten == 0)
		{
			printf("Error write to drive.");
			return -1;
		}

		liOffset.QuadPart += default_block_size;

	}


	return 0;
}

