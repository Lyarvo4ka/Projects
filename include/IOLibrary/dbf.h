#ifndef DBF_H
#define DBF_H

#include <windows.h>

#pragma pack( 1 )
struct dbf_header
{
	BYTE valid_base;
	BYTE yymmdd[3];
	DWORD numRecords;
	WORD header_size;
	WORD record_size;

}; 
#pragma pack()

int dbf_header_size = sizeof(dbf_header);

#endif
