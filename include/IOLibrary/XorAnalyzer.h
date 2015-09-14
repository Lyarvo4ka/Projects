#pragma once

#include "iolibrary_global.h"
#include <windows.h>

#include <vector>
using std::vector;

ULONGLONG NumBytesForBlock( DWORD block_size );
int chunksPrerBlock( ULONGLONG block_size );

class IOLIBRARY_EXPORT ByteCount
{
public:
	ByteCount(void);
	~ByteCount(void);
	void add(BYTE byte_value);
	BYTE getMax();
private:
	WORD * bytes_;
};




class IOLIBRARY_EXPORT XorAnalyzer
{
private:
	std::string dump_file_;
	HANDLE hDump_;
public:
	XorAnalyzer()
	{}
	XorAnalyzer(const std::string & dump_file);
	~XorAnalyzer(void);
	bool open();
	void close();

	void Analize(const std::string & result_xor, DWORD xor_size);

	DWORD getChunckBufferSize(DWORD chunck_size, int nChunck, DWORD xor_size );

};

