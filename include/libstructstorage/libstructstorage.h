#ifndef LIBSTRUCTSTORAGE_H
#define LIBSTRUCTSTORAGE_H

#include <Windows.h>
#include <string>
#include "libstructstorage_global.h"

std::string LIBSTRUCTSTORAGE_API getTimeFromFileTime(const FILETIME & file_time);

inline std::string getDateFromFileTime( const FILETIME & file_time )
{
	SYSTEMTIME st = {0};
	std::string date_nane;
	if ( FileTimeToSystemTime( &file_time , &st ) )
	{
		char date_buffer[255];
		GetDateFormatA( LOCALE_USER_DEFAULT  , 0 , &st , "yyyy-MM-dd" , date_buffer , 255);
		date_nane = date_buffer;
	}
	return date_nane;
}
inline std::string getDateTimeFromFileTime( const FILETIME & file_time )
{
	return getDateFromFileTime( file_time ) + "-" + getTimeFromFileTime( file_time );
}




#endif
