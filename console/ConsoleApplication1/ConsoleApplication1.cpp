// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <string>


void show_help()
{
	std::cout << "To run this program use : -d|f (path) target folder" << std::endl;
	std::cout << "\t d - to physical drives." << std::endl;
	std::cout << "\t f - to file." << std::endl;

	std::cout << std::endl << std::endl << "Press any key." << std::endl;
	_getch();
}

void show_error_invalid_params()
{
	std::cout <<"You entered invalid params." << std::endl;
	show_help();
}

#include "boost/filesystem.hpp"
#include <boost/lexical_cast.hpp>

#include "IOLibrary/QuickTime.h"
#include "IOLibrary/utility.h"


//////////////////////////////////////////////////////////////////////////
//
//				QuickTime RAW
//
//////////////////////////////////////////////////////////////////////////
/*

show_help();


*/

//#include "libstructstorage/libstructstorage.h"
//#include "IOLibrary/MTS_raw.h"
//#include "IOLibrary/pageaddition.h"
//#include "IOLibrary/cdw_raw.h"
//#include "IOLibrary/IODevice.h"
//#include "IOLibrary/SignatureTest.h"
//#include "IOLibrary/GoPro.h"
/*
std::thread read1(thread_read, &source_1, offset, &buffer1, read_size);
std::thread read2(thread_read, &source_2, offset, &buffer2, read_size);

read1.join();
read2.join();
*/

void thread_read(IO::DiskDevice & disk, uint64_t position ,IO::Buffer & buffer , const uint32_t read_size)
{
	disk.setPosition(position);
	disk.ReadBlock(buffer.data, read_size);
}


/************************************************************************/
/*                              RAID 0                                  */
/************************************************************************/

/*
auto list_drives = IO::ReadPhysicalDrives();

IO::DiskDevice source_1(list_drives.find_by_number(4));
IO::DiskDevice source_2(list_drives.find_by_number(2));
IO::DiskDevice target(list_drives.find_by_number(3));

if (!source_1.Open(IO::OpenMode::OpenRead))
{
printf("Error open source 1\n");
return -1;
}
if (!source_2.Open(IO::OpenMode::OpenRead))
{
printf("Error open source 2\n");
return -1;
}
if (!target.Open(IO::OpenMode::OpenRead))
{
printf("Error open target\n");
return -1;
}
auto target_size = target.Size();

if (target_size == 0)
{
printf("Error target size is 0\n");
return -1;
}

uint32_t bytes_read1 = 0;
uint32_t bytes_read2 = 0;
uint32_t bytes_written = 0;
uint32_t read_size = 0;
uint32_t write_size = 0;

uint64_t offset = 0;
const uint32_t read_block_size = default_block_size;
IO::Buffer buffer1(read_block_size);
IO::Buffer buffer2(read_block_size);
IO::Buffer target_buffer(read_block_size * 2);


uint64_t write_offset = 0;
uint64_t source_size = source_1.Size();
if (source_size == 0)
return -1;
while ( true)
{
read_size = IO::calcBlockSize(offset, source_size, read_block_size);

if ( read_size == 0)
break;

source_1.setPosition(offset);
bytes_read1 = source_1.ReadBlock(buffer1.data, read_size);
if (bytes_read1 == 0)
{
printf("error read disk 1\n");
break;
}

source_2.setPosition(offset);
bytes_read2 = source_2.ReadBlock(buffer2.data, read_size);
if (bytes_read2 == 0)
{
printf("error read disk 2\n");
break;
}


for (auto iSector = 0; iSector < read_size; iSector += default_sector_size)
{
memcpy(target_buffer.data + iSector * 2, buffer1.data + iSector, default_sector_size);
memcpy(target_buffer.data + iSector * 2 + default_sector_size, buffer2.data + iSector, default_sector_size);
}

write_size = read_size*2;
target.setPosition(write_offset);
bytes_written = target.WriteBlock(target_buffer.data, write_size);
if (bytes_written == 0)
{
printf("error write target\n");
break;
}

offset += read_size;
write_offset += write_size;
}


*/

//#include "IOLibrary/func_utils.h"
//#include "IOLibrary/Finder.h"
//#include "IOLibrary/ext2_raw.h"
//#include "IOLibrary/AbstractRaw.h"
//#include "IOLibrary/mxf_raw.h"

/*
Name  : CRC-16 CCITT
Poly  : 0x1021    x^16 + x^12 + x^5 + 1
Init  : 0xFFFF
Revert: false
XorOut: 0x0000
Check : 0x29B1 ("123456789")
MaxLen: 4095 байт (32767 бит) - обнаружение
одинарных, двойных, тройных и всех нечетных ошибок
*/
const unsigned short Crc16Table[256] = {
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
	0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
	0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
	0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
	0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
	0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
	0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
	0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
	0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
	0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
	0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
	0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
	0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
	0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
	0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
	0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
	0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
	0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
	0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
	0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
	0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
	0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
	0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
	0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

unsigned short Crc16(unsigned char * pcBlock, unsigned short len)
{
	unsigned short crc = 0xFFFF;

	while (len--)
		crc = (crc << 8) ^ Crc16Table[(crc >> 8) ^ *pcBlock++];

	return crc;
}

unsigned short Crc16_new(unsigned char *pcBlock, unsigned short len)
{
	unsigned short crc = 0xFFFF;
	unsigned char i;

	while (len--)
	{
		crc ^= *pcBlock++ << 8;

		for (i = 0; i < 8; i++)
			crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
	}
	return crc;
}

//#include "../libTinyXML2/tinyxml2.h"

//
//void show_elements(tinyxml2::XMLNode * xml_node)
//{
//	if ( tinyxml2::XMLNode * pNode = xml_node->FirstChild())
//	{
//		do {
//			if (auto xml_element = pNode->ToElement())
//			if ( auto value_element = pNode->FirstChild())
//			{
//				printf("\t\t%s - %s\r\n", pNode->ToElement()->Value(), value_element->Value());
//			}
//			pNode = pNode->NextSibling();
//		} while (pNode);
//	}
//}


//#include "IOLibrary/MTS_raw.h"

void run_RawMTS(int argc, TCHAR **argv)
{
	//if (argc == 4)
	//{
	//	const int opt = 1;
	//	const int source = 2;
	//	const int target = 3;

	//	std::wstring option = argv[opt];
	//	IO::RawMTS *pMTS_raw = nullptr;

	//	if (option.compare(L"-d") == 0)
	//	{
	//		auto drive_number = boost::lexical_cast<uint32_t>(argv[source]);

	//		auto drive_list = IO::ReadPhysicalDrives();
	//		auto physical_drive = drive_list.find_by_number(drive_number);
	//		pMTS_raw = new IO::RawMTS(new IO::DiskDevice(physical_drive));
	//		//pMTS_raw->setBlockSize(physical_drive->getTransferLength());
	//		pMTS_raw->setSectorSize(physical_drive->getBytesPerSector());
	//	}
	//	else
	//		if (option.compare(L"-f") == 0)
	//		{
	//			auto file_name = argv[source];
	//			pMTS_raw = new IO::RawMTS(new IO::File(file_name));
	//		}

	//	std::wstring target_folder = argv[target];
	//	pMTS_raw->execute(target_folder);
	//	delete pMTS_raw;

	//}
}

//void run_QuickTime(int argc, TCHAR **argv)
//{
//	if (argc == 4)
//	{
//		const int opt = 1;
//		const int source = 2;
//		const int target = 3;
//
//		std::wstring option = argv[opt];
//		IO::QuickTimeRaw *pQt_raw = nullptr;
//
//		if (option.compare(L"-d") == 0)
//		{
//			auto drive_number = boost::lexical_cast<uint32_t>(argv[source]);
//
//			auto drive_list = IO::ReadPhysicalDrives();
//			auto physical_drive = drive_list.find_by_number(drive_number);
//			pQt_raw = new IO::QuickTimeRaw(new IO::DiskDevice(physical_drive));
//			pQt_raw->setBlockSize(physical_drive->getTransferLength());
//			pQt_raw->setSectorSize(physical_drive->getBytesPerSector());
//		}
//		else
//			if (option.compare(L"-f") == 0)
//			{
//				auto file_name = argv[source];
//				pQt_raw = new IO::QuickTimeRaw(new IO::File(file_name));
//			}
//
//		std::wstring target_folder = argv[target];
//
//		pQt_raw->execute(target_folder);
//		delete pQt_raw;
//
//	}
//}

/*	SPLIT ONE BIG FILE TO small
auto src_file = IO::makeFilePtr(L"g:\\mpg\\026657.mpg");
const IO::path_string target_folder(L"f:\\41003\\mpg\\");
uint32_t counter = 0;
IO::SignatureFinder signFinder(src_file);
uint64_t offset = 0;
uint64_t header_pos = 0;

IO::StandartRaw raw(src_file);

while (true)
{
if (signFinder.findHeader(offset, header_pos))
{
uint64_t next_pos = 0;
if (signFinder.findHeader(header_pos+default_sector_size, next_pos))
{
IO::File target_file(IO::toFullPath(target_folder, counter++, L".mpg"));
target_file.Open(IO::OpenMode::Create);
raw.appendToFile(target_file, header_pos, next_pos - header_pos);
}
else
break;

offset = next_pos;
}
}
// write end
IO::File target_file(IO::toFullPath(target_folder, counter++, L".mpg"));
raw.appendToFile(target_file, header_pos, src_file->Size() - header_pos);
*/


#include "IOLibrary/StandartRaw.h"
#include "IOLibrary/QuickTime.h"
//#include "rapidjson/document.h"

const uint8_t keystore_header[] = { 0xFE, 0xED, 0xFE, 0xED };
const uint8_t ext_qt_header[] = { 0x00, 0x00, 0x00, 0x02, 0x09, 0x10, 0x00, 0x00 };
const int param_count = 2;
const int number = 1;

#include "IOLibrary/Entropy.h"
#include "IOLibrary/Finder.h"
//#include "IOLibrary/ext2_raw.h"


int _tmain(int argc, TCHAR **argv)
{
	//auto src_file = L"d:\\incoming\\41914\\41914.img";
	//IO::calcEntropyForFile("d:\\incoming\\42158\\sample\\ZOOM0002\\ZOOM0002_LR.WAV", 32768);
	//IO::calcEntropyForFile("d:\\incoming\\42158\\sample\\ZOOM0002\\ZOOM0002_Tr1.WAV", 32768);
	//IO::ESER_YDXJ_QtRaw entropy_raw(IO::makeFilePtr(src_file));

	//entropy_raw.SaveRawFile


	IO::path_string folder_path(L"d:\\tmp\\1\\");
	IO::path_list ext_list;
	//ext_list.push_back(L".mov");
	//ext_list.push_back(L".mp4");
	ext_list.push_back(L".mov");
	auto finder = IO::Finder();
	finder.FindFiles(folder_path, ext_list);

	//auto drive_number = boost::lexical_cast<uint32_t>(argv[number]);


	//auto drive_list = IO::ReadPhysicalDrives();
	//auto physical_drive = drive_list.find_by_number(drive_number);
	//if (!physical_drive)
	//{
	//	wprintf(L"Wrong drive number.\n");
	//	return -1;
	//}
	//wprintf(L"You selected\n");
	//wprintf(L"Number : %d\n", drive_number);
	//auto drive_name = physical_drive->getDriveName().c_str();
	//wprintf(L"Name : %s\n", drive_name);
	//printf("Serial number : %s\n", physical_drive->getSerialNumber().c_str());
	//wprintf(L"Size : %I64d (bytes)", physical_drive->getSize());

	//IO::path_string target_folder = L"e:\\raw\\";
	//IO::DiskDevice source(physical_drive);
	//IO::ext2_raw ext2(&source);
	//ext2.execute(target_folder);

	//IO::Finder finder;
	//finder.add_extension(L".jpg");
	//finder.FindFiles(L"e:\\Root\\LostFolders\\");

	//finder.FindFiles(L"e:\\Root\\LostFolders\\LostFolder000027\\Зевс-Д\\Зевс Д 057-14\\приход\\");

	//IO::calcEntropyForFile("f:\\41523_example\\100MEDIA\\YDXJ0516.MP4", 131072);
	//IO::calcEntropyForFile("f:\\41523_example\\100MEDIA\\YDXJ0516_thm.MP4", 131072);




	/*
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
	sprintf_s(number_data, 17, "%.16I64d", sector_number);
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
			sprintf_s(number_data, 17, "%.16I64d", ++sector_number);
			memcpy(block_data + iSector*default_sector_size, number_data, 16);
		}

		::SetFilePointerEx(drive_handle, liOffset, NULL, FILE_BEGIN);
		if (!WriteFile(drive_handle, block_data, default_block_size, &bytesWritten, NULL))
		{
			printf("Error write to drive.");
			return -1;
		}
		if (bytesWritten == 0)
		{
			printf("Error write to drive.");
			return -1;
		}
		printf("Write Sector %I64d\r\n", liOffset.QuadPart);

		liOffset.QuadPart += default_block_size;

	}
	*/
	//auto json_filename = L"c:\\Users\\ssavchenko\\Source\\Repos\\Projects\\include\\IOLibrary\\signatures.json";
	//IO::File json_file(json_filename);
	//if (!json_file.Open(IO::OpenMode::OpenRead))
	//{
	//	wprintf(L"Error open file\n");
	//	return -1;
	//}
	//uint32_t file_size = (uint32_t)json_file.Size();
	//auto data = IO::makeDataArray(file_size);
	//json_file.ReadData(data->data(), data->size());

	//rapidjson:: val;
	//Document document;
	//IO::HeaderBase headerBase;
	////////////////////////////MAIN FUNCTION///////////////////////////////
	//IO::path_string target_folder(L"e:\\dbf\\");
	//auto list_drives = IO::ReadPhysicalDrives();
	//auto physical_drive = list_drives.find_by_number(2);
	//if (!physical_drive)
	//	return -1;
/*
	//auto disk_2 = std::make_shared<IO::DiskDevice>(physical_drive);
	const uint32_t source_param = 1;
	const uint32_t size_param = 2;
	const uint32_t folder_param =3;

	//auto drive_number = boost::lexical_cast<uint32_t>(argv[source_param]);
	uint32_t drive_number = 4;
	
	//auto drive_list = IO::ReadPhysicalDrives();
	//auto physical_drive = drive_list.find_by_number(drive_number);
	//auto disk = std::make_shared<IO::DiskDevice>(physical_drive);

	uint64_t max_file_size = 4096;

	IO::path_string soruce_name(L"d:\\PaboTa\\41156\\41156_new.bin");
	IO::path_string folder = L"d:\\PaboTa\\41156\\mp4\\";
	auto src_device = IO::makeFilePtr(soruce_name);
	
	//if (!src_device->Open(IO::OpenMode::OpenRead))
	//	return -1;
	auto header_base = std::make_shared<IO::HeaderBase>();
	auto header_data = IO::makeDataArray((const uint8_t*)ext_qt_header, SIZEOF_ARRAY(ext_qt_header));
	auto footer_data = IO::makeDataArray((const uint8_t*)ext_qt_header, SIZEOF_ARRAY(ext_qt_header));
	auto file_struct = IO::makeFileStruct("split_mp4");
	file_struct->addSignature(header_data, 0);
	file_struct->addFooter(footer_data);

	header_base->addFileFormat(file_struct);

	IO::SignatureFinder signFinder(src_device, header_base);
	////0xDE263D9000 0xDD4BBA9000
	uint64_t offset = 0;
	uint64_t header_pos = 0;
	uint32_t counter = 0;
	while (true)
	{

		if (auto header = signFinder.findHeader(offset, header_pos))
		{
			IO::OnlyHeadersRaw headers_raw(src_device);
			headers_raw.setFooter(header->getFooter(), 0);
			auto new_file_name = IO::toFullPath(folder, ++counter, L".mp4");
			IO::File target_file (new_file_name);
			if ( !target_file.Open(IO::OpenMode::Create))
				break;

			auto saved_size = headers_raw.SaveRawFile(target_file, header_pos);
			if (saved_size == 0)
				break;

			offset = header_pos + saved_size;
			continue;
		}
		else
			break;
		//offset = header_pos;
		offset += default_sector_size;
	}
	//run_RawMTS(argc, argv);

*/
	//auto list_drives = IO::ReadPhysicalDrives();
	//auto physical_drive = list_drives.find_by_number(2);
	//if (!physical_drive)
	//	return -1;




	//auto filePtr = IO::makeFilePtr(L"d:\\incoming\\40873\\40873.img");	
	//IO::path_string folder(L"d:\\incoming\\40873\\result\\");
	//uint32_t counter = 0;
	//const uint32_t Block_Size = 32768;
	//if (filePtr->Open(IO::OpenMode::OpenRead))
	//{
	//	IO::SignatureFinder signFinder(filePtr);
	//	signFinder.setBlockSize(Block_Size);
	//	auto file_size = filePtr->Size();
	//	uint64_t offset = 0;
	//	uint64_t header_offset = 0;
	//	IO::MXF_rawFragment mxf_raw(filePtr);
	//	mxf_raw.setBlockSize(Block_Size);

	//	while (offset < file_size)
	//	{
	//		auto header_ptr = signFinder.findHeader(offset, header_offset);
	//		if (!header_ptr)
	//			break;

	//		auto target_path = IO::toFullPath(folder, counter++, L".mxf");
	//		auto saved_size = mxf_raw.SaveRawFile(header_ptr, header_offset, target_path);

	//		offset = header_offset;
	//		if (saved_size > 0)
	//		{
	//			saved_size /= default_sector_size;
	//			saved_size *= default_sector_size;
	//			offset += saved_size;
	//		}
	//		else
	//			offset += default_sector_size;
	//	}

	//}



/*
	//////////////////////////////////////////////////////////////////////////
	const std::string xml_filename = "c:\\Users\\sergey\\Source\\Repos\\Projects\\include\\IOLibrary\\signatures.xml";
	tinyxml2::XMLDocument xml_signature;
	auto xml_result = xml_signature.LoadFile(xml_filename.c_str());
	if (xml_result != tinyxml2::XML_SUCCESS)
	{
		wprintf_s(L"Error open xml file\n");
		return -1;
	}

	auto root = xml_signature.RootElement();
	if (root)
	{
		printf("Root:%s\r\n", root->Value());

		if (auto xml_node = root->FirstChild())
		{
			printf("\t%s\r\n", xml_node->ToElement()->Value());
			show_elements(xml_node);
			tinyxml2::XMLNode * pNode = xml_node;
			while (auto next_node = pNode->NextSibling())
			{
				printf("\t%s\r\n", next_node->ToElement()->Value());
				show_elements(next_node);
				pNode = next_node;
			}
		}


	}
//////////////////////////////////////////////////////////////////////////
	*/




	//IO::Finder finder;
	//finder.add_extension(L".jpg");
	//finder.add_extension(L".tif");
	//finder.FindFiles(L"f:\\40863\\tif\\");
	//finder.printAll();

	//auto listFiles = finder.getFiles();
	int k = 1;
	k = 2;

	//auto k = { 0 };

	//auto drive_number = 2;
	//IO::path_string target_folder(L"e:\\zbk\\");
	//auto drive_list = IO::ReadPhysicalDrives();
	//auto physical_drive = drive_list.find_by_number(drive_number);
	//auto disk_ptr = std::make_shared<IO::DiskDevice>(physical_drive);
	////auto file_ptr = std::make_shared<IO::File>(L"d:\\PaboTa\\40746\\test\\1.bin");
	//IO::ZBKRaw zbk_raw(disk_ptr);
	//zbk_raw.execute(target_folder);


	//////////////////////////////////////////////////////////////////////////
	//IO::path_string file_path = L"d:\\Temp\\~0003new.rpm";
	//IO::File source_file(file_path);
	//if (!source_file.Open(IO::OpenMode::OpenRead))
	//{
	//	wprintf(L"Error to open.\n");
	//	return -1;
	//}

	//uint32_t file_size = source_file.Size();
	//IO::Buffer buffer(file_size);

	//uint32_t bytes_read = source_file.ReadData(buffer.data, buffer.data_size);

	//for (uint32_t i4byte = 0; i4byte < bytes_read; i4byte += sizeof(uint32_t))
	//{
	//	uint32_t * p4byte = (uint32_t *)(buffer.data + i4byte);
	//	IO::to_big_endian32(*p4byte);
	//}

	//IO::File target_file(file_path+L".converted");
	//if (!target_file.Open(IO::OpenMode::Create))
	//{
	//	wprintf(L"Error to open.\n");
	//	return -1;
	//}
	//target_file.WriteData(buffer.data, buffer.data_size);

	//uint8_t * pData = buffer.data ;
	//uint16_t size = 0x13DA91;
	//short crc_val = Crc16(pData, size);
	//short crc_val_new = Crc16_new(pData, size);

	//int j = 0;
	//j = 1;



	//IO::QuickTimeRaw qt_raw(nullptr);
	//qt_raw.show_header_keywords();


	//IO::QuickTimeRaw qt_raw2(-1);
	//qt_raw2.show_header_keywords();

	//IO::path_string source_file_name(L"d:\\incoming\\40486\\Disk.image");
	//IO::path_string target_folder(L"d:\\incoming\\40486\\mov\\");
	//IO::File *source_file = new IO::File(source_file_name);
	//IO::QuitTimeRawNoSize qt_no_mdat_size(source_file);
	//qt_no_mdat_size.setBlockSize(32768);
	//qt_no_mdat_size.execute(target_folder);

	//IO::addValuesToEachPage(source_file,target_file,0xFF);
	//IO::path_string target_folder(L"e:\\40629\\mov\\");
	//IO::File *source_file = new IO::File(L"e:\\40629\\40629.img");
	//IO::QuickTimeRaw qt_raw(source_file);

	//qt_raw.setSectorSize(default_sector_size);
	//qt_raw.setBlockSize(131072);

	//qt_raw.execute(target_folder);
	//IO::File *s_file = new IO::File(source_file);
	//IO::GoPro go_pro(s_file);
	//go_pro.setClusterSize(32768);
	//go_pro.execute(target_folder);


/*
	IO::File source_file(L"d:\\PaboTa\\40599\\Root\\AGRO_UTP82\\1Cv8.1CD.grihtih");
	if (!source_file.Open(IO::OpenMode::OpenRead))
	{
		wprintf(L"Error open source file.\n");
		return -1;
	}


	IO::File target_file(L"d:\\PaboTa\\40599\\Root\\AGRO_UTP82\\1Cv8.1CD.grihtih.result");
	if (!target_file.Open(IO::OpenMode::Create))
	{
		wprintf(L"Error create target file.\n");
		return -1;
	}


	uint32_t bytes_read = 0;
	uint32_t need_bytes = 0;
	uint32_t pos = 0;

	uint32_t start_enc = 0x78;
	uint32_t end_enc = 0x1FA8A0;

	IO::Buffer buffer(default_block_size);

	const uint8_t xor_1[] = { 0xCC , 0x12 , 0x63 , 0x04 , 0x65 , 0x44 , 0x7D , 0x39 };
	const uint32_t xor_1_size = SIZEOF_ARRAY(xor_1);

	while (pos < source_file.Size())
	{
		need_bytes = IO::calcBlockSize(pos, source_file.Size(), buffer.data_size);
		bytes_read = source_file.ReadData(buffer.data, buffer.data_size);
		if (bytes_read == 0)
			break;


		for (auto i8_bytes = 0; i8_bytes < bytes_read; i8_bytes += 8)
		{
			if ((i8_bytes + pos) > start_enc)
			{
				if ((i8_bytes + pos) < end_enc)
				for (auto iXor = 0; iXor < xor_1_size; ++iXor)
					buffer.data[i8_bytes + iXor] ^= xor_1[iXor];
			}
		}

		target_file.WriteData(buffer.data, buffer.data_size);


	}

	*/




	//const IO::path_string source_file_name = L"d:\\tmp\\044814.psd";
	//const IO::path_string target_foler_name = L"e:\\psd\\";
	//IO::Finder finder;
	//finder.add_extension(L".psd");
	//finder.FindFiles(target_foler_name);
	//finder.printAll();
	//IO::changeSizeIfFindMarker(source_file_name);


	//IO::File *pFile = new IO::File(source_file_name);
	//IO::QuickTimeFragmentRaw qt_raw(pFile);
	//qt_raw.execute(target_foler_name);

	//auto list_drives = IO::ReadPhysicalDrives();
	//auto physical_drive = list_drives.find_by_number(2);
	//if (!physical_drive)
	//	return -1;


	//IO::path_string target_folder = L"d:\\PaboTa\\40282\\cdw\\";
	//IO::DiskDevice source(physical_drive);
	//IO::cdw_raw CDW_raw(&source);
	//CDW_raw.execute(target_folder);


	//IO::path_string target_folder = L"e:\\40152\\";
	//IO::DiskDevice source(physical_drive);
	//IO::ext2_raw ext2(&source);
	//ext2.execute(target_folder);
	

	//if (argc == 6)
	//{
	//	const IO::path_string data_file = argv[1];
	//	const IO::path_string service_file = argv[2];
	//	const IO::path_string target_file = argv[3];
	//	auto data_size = boost::lexical_cast<uint32_t>(argv[4]);
	//	auto service_size = boost::lexical_cast<uint32_t>(argv[5]);


	//////////////////////////////////////////////////////////////////////////
	//if (argc == 3)
	//{
	//	IO::path_string dump_file = argv[1];
	//	IO::path_string image_file = argv[2];
	//	PageAddition pageAddition(dump_file);
	//	pageAddition.execute(image_file);
	//}
	//else
	//	wprintf(L"Invalid params.");
/*
	if (argc == 4)
	{
	const int opt = 1;
	const int source = 2;
	const int target = 3;

	std::wstring option = argv[opt];
	IO::RawMTS *pMTS_raw = nullptr;

	if (option.compare(L"-d") == 0)
	{
		auto drive_number = boost::lexical_cast<uint32_t>(argv[source]);

		auto drive_list = IO::ReadPhysicalDrives();
		auto physical_drive = drive_list.find_by_number(drive_number);
		pMTS_raw = new IO::RawMTS(new IO::DiskDevice(physical_drive));
		//pMTS_raw->setBlockSize(physical_drive->getTransferLength());
		pMTS_raw->setSectorSize(physical_drive->getBytesPerSector());
	}
	else
		if (option.compare(L"-f") == 0)
		{
			auto file_name = argv[source];
			pMTS_raw = new IO::RawMTS(new IO::File(file_name));
		}

	std::wstring target_folder = argv[target];
	pMTS_raw->execute(target_folder);
	delete pMTS_raw;

	}

*/


	//////////////////////////////////////////////////////////////////////////

	//std::wstring root_path = L"d:\\LongPathFolder\\";
	//path_list list_exensions = { L".doc", L".docx" };
	//FileFinder finder;
	//finder.FindFiles(root_path, list_exensions);

	//std::wstring file = L"\\\\?\\d:\\LongPathFolder\\12314124\\143141241214\\1412412412414124124\\141241241241412412414124124124141241241412412412414124124\\14124124124141241241412412412414124124141241241241412412414124124124141241241412412412414124124141241241241412412414124124124141241241412412412414124124\\test1.doc";
	//std::wstring root_folder = L"\\\\?\\d:\\LongPathFolder\\12314124\\143141241214\\200412412412414124124\\300141241241241412412414124124124141241241412412412414124123004\\4001412412412414124124141241241241412412414124124124141241241412412412414124124141241241241412412414124124124141241241412412412414124124141241241241412412404\\";

	//std::wstring file2 = L"test4.doc";
	//std::wstring root_folder = L"\\\\?\\d:\\LongPathFolder\\";
	//BOOL bResult = FALSE;
	//bResult = SetCurrentDirectory(root_folder.c_str());
	//bResult = SetCurrentDirectory(L"12314124");
	//bResult = SetCurrentDirectory(L"143141241214");
	//bResult = SetCurrentDirectory(L"200412412412414124124");
	//bResult = SetCurrentDirectory(L"300141241241241412412414124124124141241241412412412414124123004");
	//bResult = SetCurrentDirectory(L"4001412412412414124124141241241241412412414124124124141241241412412412414124124141241241241412412414124124124141241241412412412414124124141241241241412412404");
	//auto dwError = ::GetLastError();


	//std::wstring root_folder = L"\\\\?\\d:\\LongPathFolder\\aaaaaaaaaaaaa\\bbbbbbbbbbb\\cccccccccccccccccccccccccccccccccc\\dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd\\eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";
	//std::wstring symlink = L"symlink.lnk";
	//auto bSymLink = CreateSymbolicLink(symlink.c_str(), root_folder.c_str(), SYMBOLIC_LINK_FLAG_DIRECTORY);
	//DWORD dwError = ::GetLastError();
	//std::wstring ss_file = symlink + L"\\" + file2;

	//bool bResult = false;
	//SSReader ssReader;
	//auto iStorage = ssReader.open_storage(ss_file);
	//if (iStorage)
	//	bResult = ssReader.read_storage(iStorage);

	

	//path_string source_file = argv[1];
	//path_string target_folder = argv[2];

	//GoPro goProRaw(new File(source_file));
	//goProRaw.setClusterSize(32768);

	//goProRaw.execute(target_folder);



	printf("finished");
	_getch();

	return 0;
}
/* FRAGMENT AVI video
const uint8_t c_00db[] = { 0x30 , 0x30 , 0x64 , 0x62 };
const uint32_t size_00db = SIZEOF_ARRAY(c_00db);
auto file = IO::makeFilePtr(L"d:\\incoming\\41012\\41012.img");
if (!file->Open(IO::OpenMode::OpenRead))
{
printf("Error open source");
return -1;
}

IO::SignatureFinder signFinder(file);

uint64_t offset = 0x4537B200;
uint64_t header_pos = 0;

uint32_t counter = 0;
const IO::path_string folder(L"d:\\PaboTa\\41012\\avi\\");
const uint32_t clst_size = 4096;
uint8_t buff[clst_size];
uint8_t buff2[clst_size];

uint32_t bytes_read = 0;
const uint32_t countToWrite = 320;
uint8_t buffWrite[default_block_size];


while (true)
{
if (auto file_struct = signFinder.findHeader(offset, header_pos))
{
auto target_name = IO::toFullPath(folder, counter++, L".avi");
IO::File write_file(target_name);
if ( !write_file.Open(IO::OpenMode::Create))
{
printf("Error create target file");
break;
}
// Read first cluster
file->setPosition(header_pos);
file->ReadData(buff, clst_size);
write_file.WriteData(buff, clst_size);
uint32_t * pSize = (uint32_t *)&buff[0x804];

uint64_t new_pos = header_pos;
auto dst_pos = *pSize + 4;
new_pos += dst_pos;
while (true)
{
file->setPosition(new_pos);
bytes_read = file->ReadData(buff2, clst_size);
if (bytes_read == 0)
break;
if (memcmp(buff2, c_00db, size_00db) == 0)
{
printf("Found 00db\r\n");
auto start_pos = new_pos / default_sector_size;
start_pos *= default_sector_size;
auto back_clusters = *pSize / clst_size + 1;
start_pos -= back_clusters * clst_size;
for ( uint32_t i = 0; i < countToWrite ; ++i)
{
file->setPosition(start_pos);
bytes_read = file->ReadData(buffWrite, default_block_size);
if (bytes_read == 0)
{
printf("Error read from file.\r\n");
break;
}
write_file.WriteData(buffWrite, default_block_size);
start_pos += default_block_size;
}
}

new_pos += clst_size;
}

}
else
break;
}


*/