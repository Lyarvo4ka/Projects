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


int _tmain(int argc, TCHAR **argv)
{
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

	printf("finished");
	_getch();


}
