#pragma once

#include "iolibrary_global.h"
#include <windows.h>

#include <vector>
using std::vector;

ULONGLONG NumBytesForBlock( DWORD block_size );
int chuncksPrerBlock( ULONGLONG block_size );

class IOLIBRARY_EXPORT ByteCounts
{
public:
	ByteCounts(void);
	void Add(unsigned char _byte);
	virtual unsigned char GetMax();
	virtual void ShowMaxVal();
	virtual void ShowStatictics();
	virtual ~ByteCounts(void);
private:
	vector<WORD> m_vecBytes;
};




class IOLIBRARY_EXPORT XorAnalyzer
{
public:
	XorAnalyzer(void);
	~XorAnalyzer(void);

	void Analize( const std::string & dump_file , const std::string & result_xor , DWORD xor_size);

};

