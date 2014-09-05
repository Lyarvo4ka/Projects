#ifndef ENTROPY_H
#define ENTROPY_H

#include <stdio.h>      /* printf */
#include <math.h>   
#include <Windows.h>

#define MAX_BYTE 256

inline double getEntropy(BYTE * data, DWORD size)
{
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

#endif