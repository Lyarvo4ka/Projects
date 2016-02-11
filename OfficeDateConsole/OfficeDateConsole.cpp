// OfficeDateConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "identify.h"










void show_invalid_params()
{
	printf("Error. You entered invalid params. 1-(source folder) 2-(target_folder)");
}

 
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian"); 

	if (argc == 3)
	{

		const std::string soure_folder(argv[1]);
		const std::string target_folder(argv[2]);


		identify_files(soure_folder, target_folder);
	}

		
	return 0;
}

