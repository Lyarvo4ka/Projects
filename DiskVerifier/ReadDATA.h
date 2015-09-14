#pragma once

#include "DiskDrive.h"
#include <queue>
using std::queue;


enum TEST_TYPE {FULLTEST = 0, EASY_TEST};
#define HDD_ZONE 10

#define BLOCK_SIZE 512


#pragma pack(1)
typedef struct SECTOR
{
	BYTE buff[512];
} SECTOR, *PSECTOR;

#pragma pack()

typedef class CReadDATA
{
public:
	CReadDATA(void);
	CReadDATA(CDiskDrive * _diskDrive);
	~CReadDATA(void);

	void CreateFullThread();
	void CreateRandomThread();

	void CloseThreads();

	BYTE * getBlock();
	void addBlock(BYTE * _pBytes);
	bool isEmpty();
	void removeBlock();
	void ClearQueue();
	size_t* getSize() const;

	bool *bFlagStartWait;
	bool bFlagFINISH;

	CRITICAL_SECTION *pAllowAccess;
	HANDLE *hWhaitCheck;
	HANDLE *hWaitReaded;
	HANDLE *hFinishThread;

	void setRandomPositions(LONGLONG *_pPos);
	void setSelectionCount(UINT _iCount);

	void setRange(LONGLONG _lFrom, LONGLONG _lTO);
	void setRange(VERIFY_RANGE & _rRange);

	LARGE_INTEGER liDistMove;
	static DWORD WINAPI ThreadFullRead( LPVOID lParam);
	static DWORD WINAPI ThreadRandomRead(LPVOID lPrarm);

	void setTestType(TEST_TYPE _testType);

private:
	HANDLE hThread;
	VERIFY_RANGE verifyRange;
	queue<BYTE*> m_pQueueRead;
	CDiskDrive *m_diskDrive;
	BYTE *pBuffers;
	size_t *m_SizeQueue;
	UINT iSelectionCount;
	TEST_TYPE m_TestType;

	LONGLONG * lRandomLBA;

} READDATA, *PREADDATA;
