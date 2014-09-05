#pragma once

#include <windows.h>


//		File Size Constants
namespace FileSizeValues
{
	const LONGLONG SIZE_UNLIMITED	= (LONGLONG) 0;									// FULL IMAGE
	const LONGLONG SIZE_4GB			= (LONGLONG) 4*1024*1024*1024 - 10*1024*1024;	// 4 GB - 10 MB
	const LONGLONG SIZE_2GB			= (LONGLONG) 2*1024*1024*1024 - 5*1024*1024;	// 2 GB - 5 MB
	const LONGLONG SIZE_1GB			= (LONGLONG) 1*1024*1024*1024 - 5*1024*1024;	// 1 GB - 2 MB
	const LONGLONG SIZE_700MB		= (LONGLONG) 700*1024*1024 - 1*1024*1024;		// 700 MB - 1MB
}

//	Compression Level Constants
namespace CompressionValues
{
	const int NO_COMPRESSION		= 0;
	const int BEST_SPEED			= 1;
	const int BEST_COMPRESSION		= 9;
	const int DEFAULT_COMPRESSION	= (-1);
}

// Hashing ( MD5 , SHA1 )
namespace HashingValues
{
	const int MD5_SHA1	= 1;	// MD5 + SHA1
	const int MD5		= 2;	
	const int SHA1		= 3;
	const int NONE		= 4;
	const int SHA2		= 5;
}



