// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <string>


void show_help()
{
	std::cout << "To run this programm use : -d|f (path) target folder" << std::endl;
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

#include "IOLibrary\MovRaw.h"


int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		auto diks_number = std::stoi(argv[1]);
		std::string folder = argv[2];

		QuickTimeRaw qt_raw(diks_number);
		qt_raw.execute(folder);

	}
	else
		std::cout << "You entered invalid params." << std::endl;


	printf("finished");
	_getch();


}
