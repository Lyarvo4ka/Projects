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
//#include "../ZipLib/ZipFile.h"
//#include "../libTinyXML2/tinyxml2.h"

//const std::string core_xml_str = "core.xml";
//
//const std::string open_tag = "<dcterms:modified";
//const std::string close_tag = "</dcterms:modified>";
//
//
//
//
//std::string getDateFromSystemtime(const SYSTEMTIME & system_time)
//{
//	char tmp_buffer[255];
//	::GetDateFormatA(LOCALE_USER_DEFAULT, 0, &system_time, "yyyy-MM-dd", tmp_buffer, 255);
//	std::string tmp_str = tmp_buffer;
//
//	return tmp_str;
//}
//
//std::string getTimeFromSystemtime(const SYSTEMTIME & system_time)
//{
//	char tmp_buffer[255];
//	::GetTimeFormatA(LOCALE_USER_DEFAULT, 0, &system_time, "HH-mm-ss", tmp_buffer, 255);
//	std::string tmp_str = tmp_buffer;
//
//	return tmp_str;
//}
//
//std::string getDateAndTimeFromSystemtime(const SYSTEMTIME & system_time)
//{
//	return getDateFromSystemtime(system_time) + '-' + getTimeFromSystemtime(system_time);
//}
//
//std::string parse_string_date(const std::string & original_date)
//{
//	SYSTEMTIME sys_time = {0};
//	std::string tmp_str;
//	sys_time.wYear = std::stoi(original_date.substr(0, 4));
//	sys_time.wMonth = std::stoi(original_date.substr(5, 2));
//	sys_time.wDay = std::stoi(original_date.substr(8, 2));
//	sys_time.wHour = std::stoi(original_date.substr(11, 2));
//	sys_time.wMinute = std::stoi(original_date.substr(14, 2));
//	sys_time.wSecond = std::stoi(original_date.substr(17, 2));
//
//	//""
//	return getDateAndTimeFromSystemtime(sys_time);
//}

#include "IOLibrary/MLV_raw.h"

int main(int argc, char *argv[])
{
	//save_only_1in10_mlv_clusters("d:\\incoming\\38906\\freespace.bin", "d:\\incoming\\38906\\freespace_new.bin", 32768);
	if (argc == 3)
	{
		std::string source_file = argv[1];
		std::string target_folder = argv[2];
		MLV_raw mlv_raw(source_file, target_folder);
		mlv_raw.execute();
	}
	else
		std::cout << "You entered invalid params." << std::endl;


	printf("finished");
	_getch();


}
