#pragma once
#include <windows.h>
#include <string>
using std::string;

#include <map>
using std::map;
using std::pair;
typedef pair<DWORD,WORD> AddrPair;
typedef map<DWORD,WORD> MAP;
//
//#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
//#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
//
//#define LOWORD(l)           ((WORD)(l))
//#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
//
//#define LOBYTE(w)           ((BYTE)(w))
//#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))
//
//#define SWAPWORD(w) MAKEWORD(HIBYTE(w),LOBYTE(w))
//#define SWAPLONG(l) MAKELONG(SWAPWORD(HIWORD(l)),SWAPWORD(LOWORD(l)))

#define DATA_COUNTS 256
#define DATA_SIZE 4096
#define PAGE_SIZE DATA_COUNTS*DATA_SIZE
#define SERVICE_SIZE 14
#define ECC_SIZE 80
#define PAGE_FULL 4224
#define MARKER_POS DATA_SIZE
#define WRITE_SIZE DATA_COUNTS*DATA_SIZE
#define ECC_POS DATA_SIZE + SERVICE_SIZE
#define DWORD_SIZE 4


#define MAX_SIZE 17397972992 - DATA_SIZE
#define PRED1 1312400947
#define PRED2 2982566348
class CFiles
{
public:
	CFiles(DWORD _Size);
	~CFiles(void);
	BOOL Open(string _fileName);
	void Close();
	BOOL Read(BYTE *_pBuffer);
	DWORD GetSize() const;
	void SetPosition(LARGE_INTEGER &_position);

private:
	BYTE *m_pBuffer;
	HANDLE m_hFile;
	DWORD m_Size;
	DWORD m_dwBytesRead;
	BOOL m_bResult;
};

class DumpWriter
{
public:
	DumpWriter(DWORD _Size);
	~DumpWriter();
	BOOL Open(string _fileName);
	void Close();
	void Run(CFiles *_pFiles);
	void ExchangeLONG(DWORD &_dword);
	BOOL GetMarkers(BYTE *_pByte);
	void WriteNotFound();
private:
	DWORD m_Size;
	HANDLE m_hFileWrite;
	MAP m_Address;

};