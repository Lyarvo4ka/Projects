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
#include "IOLibrary/SignatureTest.h"
#include "IOLibrary\MLV_raw.h"



int main(int argc, char *argv[])
{
	//save_only_1in10_mlv_clusters("d:\\incoming\\38906\\Disk.image", "f:\\image.bin", 32768);
	if (argc == 2)
	{

		std::string folder = argv[1];
		//std::string source_file = argv[2];
		//MLV_raw mlv_raw(source_file, folder);
		//mlv_raw.execute();
		Mlv_repair mlv_repair;
		mlv_repair.repair_files(folder);
	}
	else
		std::cout << "You entered invalid params." << std::endl;


	printf("finished");
	_getch();


}
