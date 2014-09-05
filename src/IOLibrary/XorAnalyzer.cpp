#include "XorAnalyzer.h"
#include "iofunctions.h"

#include "constants.h"

#include <iostream>

const int BYTE_SIZE =  256;

ULONGLONG NumBytesForBlock( DWORD block_size )
{
	return sizeof( WORD ) * BYTE_SIZE * block_size;
}

int chuncksPrerBlock( ULONGLONG block_size )
{
	return block_size / BS::GB;
}





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
	std::cout << GetMax() << " ";
}

void ByteCounts::ShowStatictics()
{
	for (size_t i = 0; i < BYTE_SIZE; ++i)
		printf("%.2X - %d\r\n", i,m_vecBytes[i]);
}


XorAnalyzer::XorAnalyzer(void)
{
}


XorAnalyzer::~XorAnalyzer(void)
{
}
void XorAnalyzer::Analize( const std::string & dump_file , const std::string & result_xor , DWORD xor_size)
{
	HANDLE hRead = INVALID_HANDLE_VALUE;
	if ( !IO::open_read(hRead , dump_file ) )
	{
		printf( "Error to open file to read.\r\n");
		return;
	}

	if ( xor_size <= 0 )
	{
		printf("Error block size must be more than 0.\r\n");
		return;
	}

	ULONGLONG needMemory = NumBytesForBlock(xor_size);
	
	int chuncks = chuncksPrerBlock( needMemory );



	int k = 0;
	k = 1;

	//delete pByteCounts;


	CloseHandle( hRead );
}
