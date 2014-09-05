#pragma once

#include <string>
using std::string;

#include <assert.h>

bool Open_Read(HANDLE & handle, const string & file_path);
bool Open_Write(HANDLE & handle, const string & file_path);
bool Create_File(HANDLE & handle, const string & file_path);
DWORD File_Size( HANDLE & hangle );

inline bool ReadBlock( HANDLE & handle , BYTE * buffer , DWORD size , DWORD & bytesRead )
{
	assert ( handle != INVALID_HANDLE_VALUE );
	assert( handle != nullptr );
	assert( size != 0 );

	bytesRead = 0;
	return ::ReadFile(handle , buffer , size , &bytesRead , NULL );
}
inline bool WriteBlock( HANDLE & handle , BYTE * buffer , DWORD size , DWORD & bytesWritten )
{
	assert ( handle != INVALID_HANDLE_VALUE );
	assert( handle != nullptr );
	assert( size != 0 );

	bytesWritten = 0;
	return ::WriteFile(handle , buffer , size , &bytesWritten , NULL );
}

class DeviceManager
{
	static DeviceManager * getManager()
	{
		static DeviceManager instance;
		return &instance;
	}


private:
	DeviceManager(void);
	~DeviceManager(void);
};

