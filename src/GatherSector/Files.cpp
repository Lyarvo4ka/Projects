#include "StdAfx.h"
#include "Files.h"
#include <WinSock.h>


CFiles::CFiles(DWORD _Size)
{
	m_Size = _Size;
	m_pBuffer = new BYTE[m_Size];
	m_hFile = INVALID_HANDLE_VALUE;
	m_dwBytesRead = 0;
	m_bResult = FALSE;
}


CFiles::~CFiles(void)
{
	delete m_pBuffer;
}


BOOL CFiles::Open(string _fileName)
{
	m_hFile = CreateFileA(_fileName.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	return (m_hFile != INVALID_HANDLE_VALUE) ? TRUE : FALSE;
}
void CFiles::Close()
{
	CloseHandle(m_hFile);
}
BOOL CFiles::Read(BYTE *_pBuffer)
{
	m_bResult = ReadFile(m_hFile,_pBuffer,m_Size,&m_dwBytesRead,NULL);
	if (!m_bResult)
		return FALSE;
	if (m_dwBytesRead == 0)
		return FALSE;
	return TRUE;
}
DWORD CFiles::GetSize() const
{
	return m_Size;
}

void CFiles::SetPosition(LARGE_INTEGER &_position)
{
	SetFilePointerEx(m_hFile,_position,NULL,FILE_BEGIN);
}


DumpWriter::DumpWriter(DWORD _Size)
{
	m_Size = _Size;
}

DumpWriter::~DumpWriter()
{

}

BOOL DumpWriter::Open(string _fileName)
{
	m_hFileWrite = CreateFileA(_fileName.c_str(),
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	return (m_hFileWrite != INVALID_HANDLE_VALUE) ? TRUE : FALSE;
}
void DumpWriter::Close()
{
	CloseHandle(m_hFileWrite);
}



BOOL DumpWriter::GetMarkers(BYTE *_pByte)
{
	HANDLE hMarkers = INVALID_HANDLE_VALUE;
	hMarkers = CreateFileA("e:\\Work\\Dumps\\markers.dump",
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hMarkers == INVALID_HANDLE_VALUE) 
		return FALSE;
	DWORD dwMarkersSize = GetFileSize(hMarkers,NULL);
	_pByte = new BYTE[dwMarkersSize];
	DWORD dwBytesRead = 0;
	if (!ReadFile(hMarkers,_pByte,dwMarkersSize,&dwBytesRead,NULL))
	{
		printf("Error Read File...");
		return FALSE;
	}
	CloseHandle(hMarkers);
	return TRUE;
}
void DumpWriter::Run(CFiles *_pFiles)
{
	BYTE *pBuffer = new BYTE[PAGE_FULL];
	BYTE *pWriteBuffer = new BYTE[DATA_SIZE];
	DWORD ieccPos = 0;
	DWORD dwBytesWrite = 0;
	DWORD *pMarker = NULL;
	BYTE *pMarkers = NULL;
	bool bSkip = false;
	LARGE_INTEGER liPos;
	liPos.QuadPart = 0;
	MAP::iterator it;
	DWORD dwCounter = 0;
	//_pFiles->SetPosition(liPos);
	DWORD counter = 0;
	Open("d:\\Public\\35179_iPhone\\image.bin");
	string FileName = "d:\\Public\\35179_iPhone\\Result.dump";
	HANDLE hRead = 	CreateFileA(FileName.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hRead == INVALID_HANDLE_VALUE)
	{
		printf("Error Open to Read");
		return; 
	}

	//HANDLE hMarkers = INVALID_HANDLE_VALUE;
	//hMarkers = CreateFileA("d:\\Result\\markers.dump",
	//	GENERIC_READ,
	//	FILE_SHARE_READ,
	//	NULL,
	//	OPEN_EXISTING,
	//	FILE_ATTRIBUTE_NORMAL,
	//	NULL);
	//if (hMarkers == INVALID_HANDLE_VALUE) 
	//	return ;
	//DWORD dwMarkersSize = GetFileSize(hMarkers,NULL);
	//pMarkers = new BYTE[dwMarkersSize];
	//DWORD dwBytesRead = 0;
	//if (!ReadFile(hMarkers,pMarkers,dwMarkersSize,&dwBytesRead,NULL))
	//{
	//	printf("Error Read File...");
	//	return ;
	//}
	//CloseHandle(hMarkers);
	//liPos.QuadPart = 17397972992;
	//SetFilePointerEx(m_hFileWrite,liPos,NULL,FILE_BEGIN);
	//SetEndOfFile(m_hFileWrite);
	DWORD dwPos = 0;
	DWORD dwOffset = 0;
	BOOL bExit = FALSE;
	BOOL bNext = FALSE;
	int iLeftPos = 0;
	int iRightPos = 0;
	DWORD *pMarkerCmp = NULL;
	DWORD *pTempMarker = NULL;
	WORD *pWriteMax = NULL;
	WORD *pWriteMaxTemp = NULL;
	DWORD dwBytesRead = 0;
	DWORD dwBytesRead1 = 0;

	LARGE_INTEGER liReadPosition;
	LARGE_INTEGER liPosTemp;
	liReadPosition.QuadPart = 0;
	BYTE *pTempBuffer = new BYTE[PAGE_FULL];
	BOOL bWrite = FALSE;
	while (true)
	{
		bWrite = FALSE;
		SetFilePointerEx(hRead,liReadPosition,NULL,FILE_BEGIN);
		if (!ReadFile(hRead,pBuffer,PAGE_FULL,&dwBytesRead,NULL))
		{
			printf("Error Read File");
			break;
		}
		if (dwBytesRead == 0)
			break;
		pMarker = (DWORD*)&pBuffer[DATA_SIZE];
		pWriteMax = (WORD *)&pBuffer[DATA_SIZE+4];
		liPos.QuadPart = *pMarker;
		liPos.QuadPart *= DATA_SIZE; 
		if (liPos.QuadPart < 8589934592)
		{
			it = m_Address.find(*pMarker);
			if (it == m_Address.end())
			{
				bWrite = TRUE;
				m_Address.insert(AddrPair(*pMarker,0));
		printf("Marker #%ld - offset %ld bytes\r\n",*pMarker,liReadPosition.QuadPart + DATA_SIZE);
		liPosTemp.QuadPart = 0;
		while (true)
		{
			SetFilePointerEx(hRead,liPosTemp,NULL,FILE_BEGIN);
			if (!ReadFile(hRead,pTempBuffer,PAGE_FULL,&dwBytesRead1,NULL))
			{
				printf("Error Read File");
				break;
			}
			if (dwBytesRead1 == 0)
				break;

			pTempMarker = (DWORD*)&pTempBuffer[DATA_SIZE];
			pWriteMaxTemp = (WORD *)&pTempBuffer[DATA_SIZE + 4];

			if (*pMarker == *pTempMarker)
			{
				printf("Found equal markers on offset %ld ",liPosTemp.QuadPart + DATA_SIZE);
				if (*pWriteMaxTemp >= *pWriteMax)
				{
					printf("MORE \r\n");
					memcpy(pBuffer,pTempBuffer,DATA_SIZE);
					*pWriteMax = *pWriteMaxTemp;
				}
				else
					printf("LESS \r\n");
			}

			liPosTemp.QuadPart += PAGE_FULL;
		}
			}

		// Write to File
		}
		if (bWrite == TRUE)
		{
		liPos.QuadPart = *pMarker;
		liPos.QuadPart *= DATA_SIZE;
		SetFilePointerEx(m_hFileWrite,liPos,NULL,FILE_BEGIN);
		if (!WriteFile(m_hFileWrite,pBuffer,DATA_SIZE,&dwBytesWrite,NULL))
		{
			printf("Error write file");
			break;
		}
		}
		liReadPosition.QuadPart += PAGE_FULL;
	}

	delete pTempBuffer;
	//DWORD dwWriteMarker = 0;
	//while (	_pFiles->Read(pBuffer) != 0)
	//{
	//	++dwPos;
	//	pMarker = (DWORD*)&pBuffer[DATA_SIZE];

	//	liPos.QuadPart = *pMarker;
	//	liPos.QuadPart *= DATA_SIZE; 
	//	if (liPos.QuadPart < 8589934592)
	//	{
	//		it = m_Address.find(*pMarker);
	//		if (it == m_Address.end())
	//		{
	//			pWriteMax = (WORD*)&pBuffer[DATA_SIZE + 4];
	//			SetFilePointerEx(m_hFileWrite,liPos,NULL,FILE_BEGIN);
	//			if (!WriteFile(m_hFileWrite,pBuffer,DATA_SIZE,&dwBytesWrite,NULL))
	//			{
	//				printf("Error write to File");
	//				break;
	//			}
	//			m_Address.insert(AddrPair(*pMarker,*pWriteMax));
	//		}
	//		else
	//		{
	//			pWriteMax = (WORD*)&pBuffer[DATA_SIZE + 4];
	//			if (*pWriteMax > it->second)
	//			{
	//				SetFilePointerEx(m_hFileWrite,liPos,NULL,FILE_BEGIN);
	//				if (!WriteFile(m_hFileWrite,pBuffer,DATA_SIZE,&dwBytesWrite,NULL))
	//				{
	//					printf("Error write to File");
	//					break;
	//				}
	//				it->second = *pWriteMax;
	//			}
	//		}
	//	}

		//if (bExit == TRUE)
		//	break;
		//dwPos += DWORD_SIZE*DWORD_SIZE;

		// Read page .. Testing ECC to 0xFF or 0x00
		//for (size_t iData = 0; iData < DATA_COUNTS; ++iData)
		//{
		//	//++dwCounter;
		//	//liPos.QuadPart = PAGE_FULL * dwCounter;
		//	ieccPos = iData * PAGE_FULL + ECC_POS;
		//	bSkip = true;
		//	for (size_t iECC = 0; iECC < ECC_SIZE; ++iECC)
		//	{
		//		if ( pBuffer[ieccPos+iECC] != 0x00 && pBuffer[ieccPos+iECC] != 0xFF)
		//		{
		//			bSkip = false;
		//			break;
		//		}
		//	}
		//	if (!bSkip)
		//	{

		//		pMarker = (DWORD*)&pBuffer[iData*PAGE_FULL + MARKER_POS];

		//		liPos.QuadPart = *pMarker;
		//		liPos.QuadPart *= 512;
		//		if (liPos.QuadPart < 18196512768)
		//		{
		//			memcpy(pWriteBuffer,pBuffer + iData*PAGE_FULL+SERVICE_SIZE,DATA_SIZE);
		//			SetFilePointerEx(m_hFileWrite,liPos,NULL,FILE_BEGIN);
		//			if (!WriteFile(m_hFileWrite,pWriteBuffer,DATA_SIZE,&dwBytesWrite,NULL))
		//			{
		//				printf("Error write to File");
		//				break;
		//			}
		//		}
		//	}

		//}

	//}
	
	CloseHandle(hRead);
	//Close();
	delete pBuffer;
	delete pWriteBuffer;

}
void DumpWriter::WriteNotFound()
{
	MAP::iterator it;
	LARGE_INTEGER liPos;
	BYTE BLOCK_NOT_FOUND[16] = {0x42,0x4C,0x4F,0x43,0x4B,0x20,0x4E,0x4F,0x54,0x20,0x20,0x46,0x4F,0x55,0x4E,0x44};
	BYTE WriteBuff[DATA_SIZE];
	for (int i = 0; i < DATA_SIZE / 16; ++i)
		memcpy(WriteBuff+i*16, BLOCK_NOT_FOUND,16);
	DWORD dwBytesWrite = 0;

	Open("D:\\Result\\iPhone.bin");
	for (DWORD iNumBlock = 0; iNumBlock < 1991893; ++iNumBlock)
	{
		it = m_Address.find(iNumBlock);
		if (it == m_Address.end() )
		{
			liPos.QuadPart = iNumBlock;
			iNumBlock *= DATA_SIZE;
			SetFilePointerEx(m_hFileWrite,liPos,NULL,FILE_BEGIN);
			if (!WriteFile(m_hFileWrite,WriteBuff,DATA_SIZE,&dwBytesWrite,NULL))
			{
				printf("Error write to File");
				break;
			}
		}
	}
	Close();
}

void DumpWriter::ExchangeLONG(DWORD &_dword)
{
	//_dword = ( ((_dword << 16 ) << 8 ) | ((_dword << 16 ) >> 8) ) | ( ((_dword >> 16 ) << 8 ) | ((_dword >> 16 ) >> 8) ) ;
	DWORD temp1 = _dword << 24 | _dword >> 24;
	DWORD temp2 = _dword & 0x0000FF00;
	temp2 <<= 8;
	DWORD temp3 = _dword & 0x00FF0000;
	temp3 >>= 8;
	//_dword = _dword & 0xFF0000FF;
	_dword = temp1 | temp2 | temp3;

	//_dword = ( (_dword << 16 ) << 8 ) | ((_dword >> 16 ) >> 8) ;
	//_dword = ( _dword >> 24
}


		//for (int iData = 0; iData < DATA_SIZE; iData+=4 )
		//{
		////ExchangeLONG(*pMarker);
		////*pMarker = ntohl(*pMarker);
		////pMarker = (DWORD *)&pBuffer[0];

		////if (*pMarker == 1312400947 || *pMarker == 2982566348)
		////	continue;
		////if (pBuffer[3] <= 1)
		////if (!WriteFile(m_hFileWrite,pBuffer,DATA_SIZE,&dwBytesWrite,NULL))
		////{
		////	printf("Error write to File");
		////	break;
		////}
		//it = Address.find(*pMarker);
		//if (it == Address.end())
		//{
		//	Address.insert(AddrPair(*pMarker,1));
		//}
		//else
		//	it->second++;
		//}
		//++counter;
		//ExchangeLONG(*pMarker);
		//if (*pMarker == 8848)


//string WriteString;
//char buffStr[50];
//int iWriteSize = 0;
//for (it = Address.begin(); it != Address.end(); ++it)
//{
//	iWriteSize = sprintf(buffStr,"%.8lX - %lu\r\n",it->first,it->second);
//	if (!WriteFile(m_hFileWrite,buffStr,iWriteSize,&dwBytesWrite,NULL))
//	{
//		printf("Error write to File");
//		break;
//	}
//}
