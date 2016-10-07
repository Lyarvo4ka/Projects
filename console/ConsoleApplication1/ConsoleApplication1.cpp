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
#include "IOLibrary/IODevice.h"
//#include "IOLibrary/SignatureTest.h"
#include "IOLibrary/GoPro.h"
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

#include "IOLibrary/func_utils.h"
int _tmain(int argc, TCHAR **argv)
{
	IO::QuickTimeRaw qt_raw(nullptr);
	qt_raw.show_header_keywords();


	IO::QuickTimeRaw qt_raw2(-1);
	qt_raw2.show_header_keywords();

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

	////////////////////////////MAIN FUNCTION///////////////////////////////
//
//if (argc == 4)
//{
//	const int opt = 1;
//	const int source = 2;
//	const int target = 3;
//
//	std::wstring option = argv[opt];
//	IO::QuickTimeRaw *pQt_raw = nullptr;
//
//	if (option.compare(L"-d") == 0)
//	{
//		auto drive_number = boost::lexical_cast<uint32_t>(argv[source]);
//
//		auto drive_list = IO::ReadPhysicalDrives();
//		auto physical_drive = drive_list.find_by_number(drive_number);
//		pQt_raw = new IO::QuickTimeRaw(new IO::DiskDevice(physical_drive));
//		pQt_raw->setBlockSize(physical_drive->getTransferLength());
//		pQt_raw->setSectorSize(physical_drive->getBytesPerSector());
//	}
//	else
//		if (option.compare(L"-f") == 0)
//		{
//			auto file_name = argv[source];
//			pQt_raw = new IO::QuickTimeRaw(new IO::File(file_name));
//		}
//
//	std::wstring target_folder = argv[target];
//
//	pQt_raw->execute(target_folder);
//	delete pQt_raw;
//
//}



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


}
