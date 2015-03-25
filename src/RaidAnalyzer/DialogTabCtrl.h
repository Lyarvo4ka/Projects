#pragma once


// CDialogTabCtrl
#include "MainTabDialog.h"
#include "ParityCheckDlg.h"
#include "TestSpeedHDDDlg.h"

class CDialogTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CDialogTabCtrl)

public:
	CDialogTabCtrl();
	virtual ~CDialogTabCtrl();
	CParityCheckDlg *m_pParityDlg;
	//CMainTabDialog *m_pMainTabDlg;
	//CTestSpeedHDDDlg *m_pSpeedTestHddDlg;
	void Init();
	void SetRectangle();
	int iTabCurrent;
protected:
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};


