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

	double IOLIBRARY_EXPORT calcEntropy( BYTE * data, DWORD size );
	bool IOLIBRARY_EXPORT calcEntropyForFile(const std::string & file_name, DWORD block_size);
	void IOLIBRARY_EXPORT removeLRV(const std::string & input_file, const std::string & output_file, DWORD cluster_size);
}



#endif