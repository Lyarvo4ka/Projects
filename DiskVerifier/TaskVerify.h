#pragma once

#include "ReadDATA.h"

#define WM_UPDATE_PROGRESS (WM_USER + 1) 
#define WM_FINISH (WM_USER + 2) 
#define WM_EDIT_REPORT (WM_USER + 3)
#define WM_SETNULL_PROGRESS (WM_USER + 4)
#define WM_EDIT_TEXT_CHANGE (WM_USER + 5)



enum MESSAGE_IDENTIFIER {NEW_STRING = 0,START_RANDOM,FINISH_RANDOM,START_STEP_FOLLOW,FINISH_STEP_FOLLOW,START_FULL,FINISH_FULL,};

typedef class CTaskVerify
{
protected:
	void startRandomTest();
	void startFullTest(TEST_TYPE byTestType);
public:
	CTaskVerify(void);
	static DWORD WINAPI ThreadMainFunc(LPVOID lParam);
	void setTestNumbers(TESTNUMBERS & _rTestNumbers);
	void CreateThreads();
	void setDisk(vector<CDiskDrive> &_vec);
	void setRange(VERIFY_RANGE & _rRange);
	void setCountSelection(UINT _iCount);
	void setStopSignal();
	void setFileReportPath(CString str);
	void WirteTimeReport(CStdioFile *pFileWrite, BYTE byStartFinish = 0);

	~CTaskVerify(void);
private:
	UINT iCountSelection;
	HANDLE hThread;
	TESTNUMBERS testNumbers;
	LONGLONG lNotRandom;
	LONGLONG lNotFull;
	vector<CDiskDrive> m_vecDiskDrives;
	vector<CReadDATA*> m_vecReadHDDs;
	VERIFY_RANGE  m_VerifyRange;
	CString strFileReport;
	bool m_bFind;
	bool m_bStop;

} CTASKVERIFY, *PTASKVERIFY;

