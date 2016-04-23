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

//#include "IOLibrary/QuickTime.h"
#include "IOLibrary/GoPro.h"


//////////////////////////////////////////////////////////////////////////
//
//				QuickTime RAW
//
//////////////////////////////////////////////////////////////////////////
/*
if (argc == 4)
{
const int opt = 1;
const int source = 2;
const int target = 3;

std::wstring option = argv[opt];
IO::QuickTimeRaw *pQt_raw = nullptr;

if (option.compare(L"-d") == 0)
{
auto drive_number = boost::lexical_cast<uint32_t>(argv[source]);

auto drive_list = IO::ReadPhysicalDrives();
auto physical_drive = drive_list.find_by_number(drive_number);
pQt_raw = new IO::QuickTimeRaw(new IO::DiskDevice(physical_drive));
pQt_raw->setBlockSize(physical_drive->getTransferLength());
pQt_raw->setSectorSize(physical_drive->getBytesPerSector());
}
else
if (option.compare(L"-f") == 0)
{
auto file_name = argv[source];
pQt_raw = new IO::QuickTimeRaw(new IO::File(file_name));
}

std::wstring target_folder = argv[target];

pQt_raw->execute(target_folder);
delete pQt_raw;

}
show_help();


*/

#include "libstructstorage/libstructstorage.h"
int _tmain(int argc, TCHAR **argv)
{
	//std::wstring file = L"\\\\?\\d:\\LongPathFolder\\12314124\\143141241214\\1412412412414124124\\141241241241412412414124124124141241241412412412414124124\\14124124124141241241412412412414124124141241241241412412414124124124141241241412412412414124124141241241241412412414124124124141241241412412412414124124\\test1.doc";
	//std::wstring root_folder = L"\\\\?\\d:\\LongPathFolder\\12314124\\143141241214\\200412412412414124124\\300141241241241412412414124124124141241241412412412414124123004\\4001412412412414124124141241241241412412414124124124141241241412412412414124124141241241241412412414124124124141241241412412412414124124141241241241412412404\\";

	std::wstring file2 = L"test1.doc";
	//std::wstring root_folder = L"\\\\?\\d:\\LongPathFolder\\";
	//BOOL bResult = FALSE;
	//bResult = SetCurrentDirectory(root_folder.c_str());
	//bResult = SetCurrentDirectory(L"12314124");
	//bResult = SetCurrentDirectory(L"143141241214");
	//bResult = SetCurrentDirectory(L"200412412412414124124");
	//bResult = SetCurrentDirectory(L"300141241241241412412414124124124141241241412412412414124123004");
	//bResult = SetCurrentDirectory(L"4001412412412414124124141241241241412412414124124124141241241412412412414124124141241241241412412414124124124141241241412412412414124124141241241241412412404");
	//auto dwError = ::GetLastError();


	std::wstring root_folder = L"\\\\?\\d:\\LongPathFolder\\aaaaaaaaaaaaa\\bbbbbbbbbbb\\cccccccccccccccccccccccccccccccccc\\dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd\\eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";
	std::wstring symlink = L"symlink.lnk";
	auto bSymLink = CreateSymbolicLink(symlink.c_str(), root_folder.c_str(), SYMBOLIC_LINK_FLAG_DIRECTORY);
	DWORD dwError = ::GetLastError();
	std::wstring ss_file = symlink + L"\\" + file2;

	SSReader ssReader;
	auto iStorage = ssReader.open_storage(ss_file);
	if (!iStorage)
		return -1;
	IEnumSTATSTG *iEnumStg = nullptr;
	if ( FAILED(iStorage->EnumElements(0, nullptr, 0, &iEnumStg)) )
		return -1;

 	STATSTG statstg = { 0 };
	wprintf(L"\n\nSTART ENUM\n");
	auto hr = iEnumStg->Next(1, &statstg, nullptr);
	while (SUCCEEDED(hr) )
	{
		if (statstg.type == STGTY_STREAM)
		{
			IStream *pStream = nullptr;
			auto stream_hr = iStorage->OpenStream(statstg.pwcsName, nullptr, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pStream);
			if (SUCCEEDED(stream_hr))
			{
				auto buff_size = statstg.cbSize.QuadPart;
				BYTE *pBuffer = new BYTE[buff_size];
				DWORD bytes_read = 0;
				auto read_hr = pStream->Read(pBuffer, buff_size, &bytes_read);

				int k = 1;
				k = 2;
				delete[] pBuffer;
			}
		}

		wprintf(L"%s\n", statstg.pwcsName);
		hr = iEnumStg->Next(1, &statstg, nullptr);
	}

	//path_string source_file = argv[1];
	//path_string target_folder = argv[2];

	//GoPro goProRaw(new File(source_file));
	//goProRaw.setClusterSize(32768);

	//goProRaw.execute(target_folder);



	printf("finished");
	_getch();


}
