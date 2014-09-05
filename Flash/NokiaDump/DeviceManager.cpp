#include "stdafx.h"
#include "DeviceManager.h"


bool Open_Read(HANDLE & handle, const string & file_path)
{
	handle = CreateFileA( file_path .c_str(),
		GENERIC_READ ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	DWORD dwError = GetLastError();
	return (handle != INVALID_HANDLE_VALUE) ? true : false;		
}
bool Open_Write(HANDLE & handle, const string & file_path)
{
	handle = CreateFileA( file_path .c_str(),
		GENERIC_READ | GENERIC_WRITE ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	return (handle != INVALID_HANDLE_VALUE) ? true : false;	
}
bool Create_File(HANDLE & handle, const string & file_path)
{
	handle = CreateFileA( file_path .c_str(),
		GENERIC_WRITE ,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		0,
		NULL);
	return (handle != INVALID_HANDLE_VALUE) ? true : false;	
}
DWORD File_Size( HANDLE & handle)
{
	return ::GetFileSize(handle, NULL);
}

DeviceManager::DeviceManager(void)
{
}


DeviceManager::~DeviceManager(void)
{
}
