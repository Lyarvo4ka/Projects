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


#include "IOLibrary/FireBird.h"


int main(int argc, char *argv[])
{
	FireBird_Raw firebird_raw("e:\\39462\\free_space.bin", "e:\\gdb\\");
	firebird_raw.execute();

	//if (argc == 3)
	//{
	//}
	//else
	//	std::cout << "You entered invalid params." << std::endl;


	printf("finished");
	_getch();


}
