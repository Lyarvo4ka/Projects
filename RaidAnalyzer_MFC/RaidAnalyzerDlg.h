
#pragma once
#include "afxcmn.h"

#include "DialogTabCtrl.h"
#include "ReadDisk.h"
#include "afxwin.h"
#include "CuttingSectorsDlg.h"

static CString getTimeCurrent()
{
	CTime cTime =  CTime::GetCurrentTime();
	CString strReport = _T("");

	strReport.Format(_T(" ( %i.%02i.%02i %02i:%02i:%02i  ) \r\n"),
					cTime.GetYear(),
					cTime.GetMonth(),
					cTime.GetDay(),
					cTime.GetHour(),
					cTime.GetMinute(),
					cTime.GetSecond()
					);

	return strReport;
}

class CRaidAnalyzerDlg : public CDialogEx
{

public:
	CRaidAnalyzerDlg(CWnd* pParent = NULL);	
	//virtual void OnDestroy();
	virtual ~CRaidAnalyzerDlg();

	enum { IDD = IDD_RAIDANALYZER_DIALOG };
	// Threads Operations
	void SuspendThreads();
	void ResumeThreads();
	void AbortThreads();

private:
	//CCuttingSectorsDlg *pCuttingDialog;
	CStdioFile pFileWrite;
	CReadDisk *pReadDisk;
	CAllocator *m_Data;
	CMapAddress *pMAP;
	CDialogTabCtrl *m_TabDialogs;
	//CCommand *m_ParityCheckCommand;
	//CReceiver *m_pReciver;
	CSingletonJPGs *m_pSingleton;

	void ClearData();
	CDrives m_Drives;
	vector<CDiskDrive> m_vecDrives;
	vector<CDiskDrive> m_vecSelDrives;
	LONGLONG m_MinMaxLBA;
	VerifyRange verifyMinMax;
	LONGLONG m_lFirstPos;
	LONGLONG m_lLastPos;
	BOOL m_bSequence;
	NotEqualSectors m_notEqaulSectors;
	LONGLONG m_lCountProgress;
	LONGLONG m_incProgress;
	LONGLONG m_lTempProgress;
	DWORD m_dwProgressPos;
	enStateProgram m_enStateProgram;
	CLog *m_ReportLog;
	UINT m_iTestStarted;
	BOOL m_bIsExecuting;
	HANDLE m_hWaitAnswer;
	HANDLE *hComunicateLock;
	RESULT_CUTTING_SECTORS *pResultCutting;
protected: 
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);	
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnNMDblclkListDrives(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeMinLba();
	afx_msg void OnEnChangeMaxLba();
	afx_msg void OnBnClickedClearButton();
	afx_msg void OnBnClickedButtonClearLog();
	afx_msg void OnBnClickedRemoveSelected();
	afx_msg void OnCancel();
	afx_msg void OnOK();
	afx_msg void OnLbnSelchangeSelectedList();
	afx_msg void OnBnClickedButtonJpg();
	afx_msg void OnBnClickedButtonStop();

	LRESULT OnStartButtonPressed(WPARAM wParam, LPARAM lParam);
	LRESULT OnStopButtonPressed(WPARAM wParam, LPARAM lParam);
	LRESULT OnFinishCheck(WPARAM wParam, LPARAM lParam);
	LRESULT OnFinishGatherByJPG(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateReportFirst(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateReportLast(WPARAM wParam, LPARAM lParam);
	LRESULT OnSetFirstMissmatch(WPARAM wParam, LPARAM lParam);
	LRESULT OnParityCheckProgress(WPARAM wParam, LPARAM lParam);
	LRESULT OnShowMissmatchDlg(WPARAM wParam, LPARAM lParam);
	LRESULT OnSetPause(WPARAM wParam, LPARAM lParam);
	LRESULT OnShowCuttingDialog(WPARAM wParam, LPARAM lParam);
	LRESULT OnSuspendThreads(WPARAM wParam, LPARAM lParam);
	LRESULT OnResumeThreads(WPARAM wParam, LPARAM lParam);
	LRESULT OnAbortThreads(WPARAM wParam, LPARAM lParam);
	LRESULT OnExitJpg(WPARAM wParam, LPARAM lParam);

	CListCtrl* m_pListDrives;
	CListBox* m_pListSelected;
	CProgressCtrl m_MainProgress;
	CEdit *m_pEditReport;
	CEdit* m_pEditMinLBA;
	CEdit* m_pEditMaxLBA;
	CButton m_GatherByJPG;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddButtonFile();
	afx_msg void OnBnClickedButton4();
};
