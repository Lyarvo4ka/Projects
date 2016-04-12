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


#include "IOLibrary/QuickTime.h"


int _tmain(int argc, TCHAR **argv)
{
	if (argc == 4)
	{
		IO::path_string option = argv[1];
		IO::IODevice *device = nullptr;

		if (option.compare(L"-d") == 0)
		{
			auto drive_list = IO::ReadPhysicalDrives();
			//drive_list.find_by_number()
		}
		else
			if (option.compare(L"-f") == 0)
			{
				//device = new IO::File()
			}
	}
	show_help();

	printf("finished");
	_getch();


}