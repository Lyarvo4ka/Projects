#pragma once
#include "../DiskVerifier/DiskDrive.h"
#include "InfoData.h"
#include "Log.h"
#include "afxwin.h"

// Delete Data ????
class CParityCheckDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParityCheckDlg)

public:
	CParityCheckDlg(CWnd* pParent = NULL);  
	virtual ~CParityCheckDlg();

	enum { IDD = IDD_PARITY_CHECK };
private:

	CString strReport;
	CString strEditText;
	CEdit* m_pEditParityReport;
	CEdit *m_pEditIndent;
	CEdit* m_pEditBlockSize;
	CEdit* m_pEditStep;
	CButton* m_pButtonStart;
	CButton* m_pRadioFullTest;
	CButton* m_pRadioSpeedTest;
	CButton* m_pButtFirstMissmatch;
	CProgressCtrl* m_pParityProgress;
	CStatic* m_pTxtOffset;
	CStatic* m_pTxtSelection;
	CStatic* m_pTxtBlockSize;
	CStatic* m_pGroupBox;

	DWORD m_iCountProgress;
	DWORD m_incProgress;
	USHORT m_iProgressPos;
	LONGLONG m_MaxLBA;
	CLog *m_pLogReport;
public:

	DWORD getIndentSectors() ;
	DWORD getStep();
	DWORD getBlockSize();
	BOOL getFirstMissmatch() const;

	void setMaxLBA(LONGLONG _lMaxLBA);
	void setLog(CLog * _pLog);

	void UpdateChecked( int _iChecked);
	void setVisibles(int _bVisible);
	// event handlers
	afx_msg void OnBnClickedStartButton();
	afx_msg void OnBnClickedButtonStop();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
	afx_msg BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioSpeedTest();
	afx_msg void OnBnClickedRadioFullTest();
	afx_msg void OnBnClickedCheck1();

	LRESULT OnFinishCheck(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateProgress(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateMaxLBA(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
