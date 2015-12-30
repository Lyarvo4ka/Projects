#pragma once

#include "resource.h"



#include "IOLibrary/iofunctions.h"
#include "IOLibrary/FileFinder.h"
#include <iostream>


const std::string docx_extension = ".docx";
const std::string xlsx_extension = ".xlsx";
const std::string pptx_extension = ".pptx";

//void identify_files(const std::string & source_dir, const std::string & target_dir);

void identify_files(const std::string & source_dir, const std::string & target_dir);
bool identify_office2003(const std::string & file_name, std::string & new_filename, int counter);
bool identify_office2007(const std::string & file_name, std::string & new_filename, int counter);
bool identify_pdf(const std::string & file_name, std::string & new_filename, int counter);

inline bool isOffice2007(const std::string & extension)
{
	if (extension.compare(docx_extension) == 0)
		return true;
	if (extension.compare(xlsx_extension) == 0)
		return true;
	if (extension.compare(pptx_extension) == 0)
		return true;
	return false;
}


inline std::string getDateFromSystemtime(const SYSTEMTIME & system_time)
{
	char tmp_buffer[255];
	::GetDateFormatA(LOCALE_USER_DEFAULT, 0, &system_time, "yyyy-MM-dd", tmp_buffer, 255);
	std::string tmp_str = tmp_buffer;

	return tmp_str;
}

inline std::string getTimeFromSystemtime(const SYSTEMTIME & system_time)
{
	char tmp_buffer[255];
	::GetTimeFormatA(LOCALE_USER_DEFAULT, 0, &system_time, "HH-mm-ss", tmp_buffer, 255);
	std::string tmp_str = tmp_buffer;

	return tmp_str;
}

inline std::string getDateAndTimeFromSystemtime(const SYSTEMTIME & system_time)
{
	return getDateFromSystemtime(system_time) + '-' + getTimeFromSystemtime(system_time);
}

inline std::string parse_string_date(const std::string & original_date)
{
	SYSTEMTIME sys_time = { 0 };
	std::string tmp_str;
	sys_time.wYear = std::stoi(original_date.substr(0, 4));
	sys_time.wMonth = std::stoi(original_date.substr(5, 2));
	sys_time.wDay = std::stoi(original_date.substr(8, 2));
	sys_time.wHour = std::stoi(original_date.substr(11, 2));
	sys_time.wMinute = std::stoi(original_date.substr(14, 2));
	sys_time.wSecond = std::stoi(original_date.substr(17, 2));

	//""
	return getDateAndTimeFromSystemtime(sys_time);
}