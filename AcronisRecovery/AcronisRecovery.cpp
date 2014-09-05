// AcronisRecovery.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "zlib/zlib.h"

#include "IOLibrary/iofunctions.h"
#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hRead = INVALID_HANDLE_VALUE;
	std::string file = "f:\\7.tmp";
	if ( !IO::open_read( hRead , file ) )
	{
		printf("Error to open file.%s" , file.c_str() );
		return -1;
	}
	std::string target_file = "f:\\target7.bin";
	HANDLE hWrite = INVALID_HANDLE_VALUE;
	if ( !IO::create_file(hWrite , target_file ) )
	{
		printf("error. create target file.");
		return -1;
	}
	DWORD file_size =  ::GetFileSize( hRead , NULL );
	if ( file_size > 0 )
	{
		DWORD bytesRead = 0;
		BYTE * src_buff =  new BYTE[ file_size ];
		IO::read_block( hRead , src_buff , file_size , bytesRead );

		const int max_dst_size = 512*512;

		BYTE * dst_buff = new BYTE[ max_dst_size ];

		uLongf dst_size = max_dst_size;
		int iResult = uncompress( dst_buff , &dst_size , src_buff , file_size );
		if ( iResult == Z_OK )
		{

			DWORD bytesWritten = 0;
			IO::write_block(hWrite , dst_buff , dst_size , bytesWritten );

		}


		delete [] src_buff;
		delete [] dst_buff;
		CloseHandle(hRead);
		CloseHandle(hWrite);

	}



	return 0;
}

