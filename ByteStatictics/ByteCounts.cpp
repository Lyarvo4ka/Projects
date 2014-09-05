#include "StdAfx.h"
#include "ByteCounts.h"
#include <algorithm>
using std::max_element;
#include <iostream>
using std::cout;
using std::endl;


ByteCounts::ByteCounts(void)
{
	m_vecBytes.resize(BYTE_SIZE,0);
}

ByteCounts::~ByteCounts(void)
{
	m_vecBytes.clear();
}

bool compareMAX(WORD iOne, WORD iSecond)
{
	return iOne < iSecond;
}

void ByteCounts::Add(unsigned char _byte)
{
	m_vecBytes[_byte]++;
}

unsigned char ByteCounts::GetMax()
{
	unsigned char iPos = 0;
	WORD dwMax = m_vecBytes[0]; 
	for (size_t i = 1; i < BYTE_SIZE; ++i)
	{
		if (m_vecBytes[i] > dwMax)
		{
			iPos = (unsigned char)i;
			dwMax = m_vecBytes[i];
		}
	}
	return iPos;
}

void ByteCounts::ShowMaxVal()
{
	cout << GetMax() << " ";
}

void ByteCounts::ShowStatictics()
{
	for (size_t i = 0; i < BYTE_SIZE; ++i)
		printf("%.2X - %d\r\n", i,m_vecBytes[i]);
}