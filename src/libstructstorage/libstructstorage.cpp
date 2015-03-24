// libstructstorage.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "libstructstorage.h"


std::string getTimeFromFileTime(const FILETIME & file_time)
{
	SYSTEMTIME st = { 0 };
	std::string time_nane = "";
	if (::FileTimeToSystemTime(&file_time, &st))
	{
		char time_buffer[255];
		::GetTimeFormatA(LOCALE_USER_DEFAULT, 0, &st, "HH-mm-ss", time_buffer, 255);
		time_nane = time_buffer;
	}
	return time_nane;
}
