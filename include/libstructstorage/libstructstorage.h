#ifndef LIBSTRUCTSTORAGE_H
#define LIBSTRUCTSTORAGE_H

#include <Windows.h>

inline std::string getTimeFromFileTime( const FILETIME & file_time )
{
	SYSTEMTIME st = {0};
	std::string time_nane;
	if ( FileTimeToSystemTime( &file_time , &st ) )
	{
		char time_buffer[255];
		GetTimeFormatA( LOCALE_USER_DEFAULT , 0 , &st , "HH-mm-ss" , time_buffer , 255);
		time_nane = time_buffer;
	}
	return time_nane;
}
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
