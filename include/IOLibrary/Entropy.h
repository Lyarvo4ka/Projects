#ifndef ENTROPY_H
#define ENTROPY_H

#include <stdio.h>      /* printf */
#include <math.h>   
#include <Windows.h>
#include "iofunctions.h"
#include "constants.h"

#define MAX_BYTE 256

#include <boost/lexical_cast.hpp>

inline double getEntropy(BYTE * data, DWORD size)
{
	if ( !data || ( size == 0 ) )
		return 0.0;

	DWORD symbols[MAX_BYTE] = { 0 };
	memset(symbols, 0, MAX_BYTE*sizeof(DWORD));
	DWORD dwBytesRead = 0;
	DWORD dwSumm = 0;
	DWORD dwPosition = 0;
	for (DWORD Index = 0; Index < size; ++Index)
	{
		symbols[data[Index]]++;
		++dwSumm;
	}
	double temp = 0.0;
	static double Log2 = log(2.0);
	double entropy = 0.0;
	for (size_t iByte = 0; iByte < MAX_BYTE; ++iByte)
	{
		if (symbols[iByte] > 0)
		{
			temp = ((double)symbols[iByte]) / ((double)dwSumm);
			entropy -= temp * log(temp) / Log2;
		}
	}
	return entropy;
}

bool calcEntropy(const std::string & file_name , DWORD block_size )
{
	HANDLE hRead = INVALID_HANDLE_VALUE;
	if (!IO::open_read(hRead, file_name))
		return false;

	std::string entropy_file = file_name + ".txt";
	HANDLE hWrite = INVALID_HANDLE_VALUE;
	if (!IO::create_file(hWrite, entropy_file))
		return false;

	BYTE * pBuffer = new BYTE[block_size];
	
	DWORD bytesRead = 0;
	DWORD byteWritten = 0;
	double entropy = 0.0;
	bool bResult = false;
	DWORD cluster_number = 0;

	while (true)
	{
		bResult = IO::read_block(hRead, pBuffer, block_size, bytesRead);
		if (!bResult || (bytesRead == 0))
			break;

		entropy = getEntropy(pBuffer, bytesRead);
		std::string write_string( boost::lexical_cast<std::string>(entropy));
		write_string.append("\r\n");

		IO::write_block(hWrite,(BYTE*) write_string.data(), write_string.size(), byteWritten);
		++cluster_number;
	}

	delete pBuffer;

	CloseHandle(hWrite);
	CloseHandle(hRead);
	return true;
}

void removeLRV(const std::string & input_file, const std::string & output_file)
{
	HANDLE hRead = INVALID_HANDLE_VALUE;
	if ( !IO::open_read(hRead, input_file) )
		return;

	HANDLE hWrite = INVALID_HANDLE_VALUE;
	if ( !IO::create_file( hWrite, output_file) )
		return;

	const int block_size = 512 * 1024;
	DWORD bytesRead = 0;
	DWORD bytesWritten = 0;
	bool bResult = false;
	double entropy = 0.0;


	BYTE * pBuffer = new BYTE[block_size];

	while (true)
	{
		bResult = IO::read_block(hRead, pBuffer, block_size, bytesRead);
		if ( !bResult || bytesRead == 0)
			break;

		if (memcmp(pBuffer, Signatures::qt_header4, SIZEOF_ARRAY(Signatures::qt_header4)) == 0)
		{
			bResult = IO::write_block(hWrite, pBuffer, bytesRead, bytesWritten);
			if (!bResult || bytesWritten == 0)
				break;
		}
		else
		{
			entropy = getEntropy(pBuffer, bytesRead);
			if (entropy > 7.9990 && entropy < 7.9999)
			{
				bResult = IO::write_block(hWrite, pBuffer, bytesRead, bytesWritten);
				if ( !bResult || bytesWritten == 0 )
					break;
			}
		}
	}

	delete pBuffer;

	CloseHandle(hRead);
	CloseHandle(hWrite);
}

#endif