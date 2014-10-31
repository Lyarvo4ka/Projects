#ifndef ENTROPY_H
#define ENTROPY_H

#include "iolibrary_global.h"


#include <stdio.h>      /* printf */
#include <math.h>   
#include <Windows.h>
#include "iofunctions.h"
#include "constants.h"

#define MAX_BYTE 256
#define MAX_BYTE2 UCHAR_MAX + 1

#include <boost/lexical_cast.hpp>

namespace IO
{
	static double Log2 = log(2.0);

	double IOLIBRARY_EXPORT calcEntropy(BYTE * data, DWORD size);
	bool calcEntropyForFile(const std::string & file_name, DWORD block_size);
}



//
//void removeLRV(const std::string & input_file, const std::string & output_file)
//{
//	HANDLE hRead = INVALID_HANDLE_VALUE;
//	if ( !IO::open_read(hRead, input_file) )
//		return;
//
//	HANDLE hWrite = INVALID_HANDLE_VALUE;
//	if ( !IO::create_file( hWrite, output_file) )
//		return;
//
//	const int block_size = 512 * 1024;
//	DWORD bytesRead = 0;
//	DWORD bytesWritten = 0;
//	bool bResult = false;
//	double entropy = 0.0;
//
//
//	BYTE * pBuffer = new BYTE[block_size];
//
//	while (true)
//	{
//		bResult = IO::read_block(hRead, pBuffer, block_size, bytesRead);
//		if ( !bResult || bytesRead == 0)
//			break;
//
//		if (memcmp(pBuffer, Signatures::qt_header4, SIZEOF_ARRAY(Signatures::qt_header4)) == 0)
//		{
//			bResult = IO::write_block(hWrite, pBuffer, bytesRead, bytesWritten);
//			if (!bResult || bytesWritten == 0)
//				break;
//		}
//		else
//		{
//			entropy = getEntropy(pBuffer, bytesRead);
//			if (entropy > 7.9990 && entropy < 7.9999)
//			{
//				bResult = IO::write_block(hWrite, pBuffer, bytesRead, bytesWritten);
//				if ( !bResult || bytesWritten == 0 )
//					break;
//			}
//		}
//	}
//
//	delete pBuffer;
//
//	CloseHandle(hRead);
//	CloseHandle(hWrite);
//}

#endif