#pragma once

#include "../DiskVerifier/Drives.h"


#define WM_BUTTON_START (WM_USER + 1)
#define WM_BUTTON_STOP (WM_USER + 2)
#define WM_UPDATE_PARITY_REPORT (WM_USER + 3) 
#define WM_UPDATE_PROGRESS (WM_USER + 4)
#define WM_UPDATE_PARITY_CHECK_PROGRESS (WM_USER + 5)

#define WM_PARITY_CHECK_NOT_EQUAL_FIRST (WM_USER + 20) 
#define WM_PARITY_CHECK_NOT_EQUAL_LAST (WM_USER + 21) 
#define WM_FINISH_PARITY_CHECK (WM_USER + 100)
#define WM_FINISH_GATHER_BY_JPG (WM_USER + 101)
#define WM_UPDATE_MAX_LBA (WM_USER + 199)
#define WM_FIRST_MISSHATCH (WM_USER + 200)
#define WM_SET_PAUSE (WM_USER + 201)

#define PARAM_FULL_TEST 100L
#define PARAM_SPEED_TEST 101L
#define PARAM_SHOW_LAST_MISSMATCH 102L
#define WM_SHOW_MISSHATCH (WM_USER + 103L)

#define PARAM_START_PARITY_TEST 202L
#define PARAM_START_SPEED_HDD_TEST 203L

// Cutting J P G 
#define WM_SHOW_CUTTING_DIGLOG (WM_USER + 11)
// Defaults
#define DEFAULT_SECTORS_SIZE 256

#define QUICKTEST TRUE
#define FULLTEST FALSE
#define PROGRESS_COUNT 100

/////////////////// Threads ////////////////////
#define WM_SUSPEND_THREAD (WM_USER + 1000L)
#define WM_RESUME_THREAD (WM_USER + 1001L)
#define WM_ABORT_THREAD (WM_USER + 1002L)



struct NotEqualSectors
{
	LONGLONG lFirst;
	LONGLONG lCurrent;
	LONGLONG lInterval;
	LONGLONG lLast;
};

typedef struct _Func_Data
{
	LONGLONG lPosFrom;	// position FROM
	LONGLONG lPosTo;	// position TO
	DWORD dwIndent;		// indent
	DWORD dwBlockSize;
	DWORD dwStep;

}FUNKDATA,*PFUNCDATA;

enum IDBUTTONS {iResOK = 0, iResABORT, iResNEXT};
enum enStateProgram {enStart = 0, enPause = 1, enResume = 2, enStop = 3};
typedef struct _ReturnCuttingDlg
{
	UINT m_iSize;
	IDBUTTONS m_ButtonResult;
} RESULT_CUTTING_SECTORS, *PRESULT_CUTTING_SECTORS;

typedef struct _FindDATASend
{
	UINT m_iDiskNumber;
	LONGLONG m_LBAPosition;
	DWORD m_dwStartSector;
} FINDSENDDATA, *PFINDSENDDATA;


static void WirteDiskInfoReport(CStdioFile *pFileWrite, const CDiskDrive & _diskDrive )
{
	CString strReport = _T("");

	strReport = _T("\r\n");
	strReport += _T("*******************************************************************");
	strReport += _T("\r\n");
	pFileWrite->WriteString(strReport);

	// Disk Number		  
	strReport.Format(_T("Disk #%i          : %iGB"),_diskDrive.getDiskNumber(),_diskDrive.getDiskSize());
	strReport += _T("\r\n");
	pFileWrite->WriteString(strReport);

	// Serial Number
	strReport.Format(_T("Serial Number    : %s"),_diskDrive.getSerialNumber());
	strReport += _T("\r\n");
	pFileWrite->WriteString(strReport);

	// Disk Name		
	strReport.Format(_T("Disk NAME        : %s"),_diskDrive.getDiskName());
	strReport += _T("\r\n");
	pFileWrite->WriteString(strReport);

	// MAX LBA			 Serial Number
	strReport.Format(_T("MAX LBA          : %I64d"),_diskDrive.getSectorCount());
	strReport += _T("\r\n");
	pFileWrite->WriteString(strReport);

	// Bytes per Sector
	strReport.Format(_T("Bytes per Sector : %ibytes"),_diskDrive.getBytesPerSector());
	strReport += _T("\r\n");
	pFileWrite->WriteString(strReport);

	strReport = _T("\r\n");
	strReport += _T("*******************************************************************");
	strReport += _T("\r\n");
	pFileWrite->WriteString(strReport);
}


#define ERROR_OPEN_DISK 1001L

///////////////////////////////////////////////////////////////////////////////
// --------------- CReceiver -------------------
///////////////////////////////////////////////////////////////////////////////
class CReceiver
{
public:
	CReceiver();
	void Action();
	void setPosition(LONGLONG & _lLBA);
	void setXorResult(BOOL &_bResultXor);
	void setDataCommand(LONGLONG & _lLBA , BOOL &_bResultXor);
private:
	LONGLONG m_lPosition;
	BOOL m_bXorResult;

};

///////////////////////////////////////////////////////////////////////////////
// --------------- CCommand -------------------
///////////////////////////////////////////////////////////////////////////////
class CCommand 
{
protected:
	CReceiver *m_Recivier;
public:
	void setReceiver(CReceiver *_recivier);
	virtual void Execute() = 0;
	virtual ~CCommand();
};

///////////////////////////////////////////////////////////////////////////////
// --------------- CParityCheckCommand -------------------
///////////////////////////////////////////////////////////////////////////////
class CParityCheckCommand:public CCommand
{
public:
	CParityCheckCommand();
	CParityCheckCommand(CReceiver *_recivier);
	void setPosition(LONGLONG & _lLBA);
	void setXorResult(BOOL &_bResultXor);
	void setDataCommand(LONGLONG & _lLBA , BOOL &_bResultXor);
	virtual ~CParityCheckCommand();
	virtual void Execute();
};

