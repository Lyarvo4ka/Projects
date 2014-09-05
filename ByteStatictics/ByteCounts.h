#pragma once
#include <vector>
using std::vector;

#include <windows.h>
#define BYTE_SIZE 256

class ByteCounts
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

