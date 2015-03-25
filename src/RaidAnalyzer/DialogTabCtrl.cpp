// DialogTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "RaidAnalyzer.h"
#include "DialogTabCtrl.h"





// CDialogTabCtrl

IMPLEMENT_DYNAMIC(CDialogTabCtrl, CTabCtrl)

CDialogTabCtrl::CDialogTabCtrl()
{
	m_pParityDlg = new CParityCheckDlg;
	//m_pMainTabDlg = new CMainTabDialog;
	//m_pSpeedTestHddDlg = new CTestSpeedHDDDlg;
	//m_tabPages[0] = new CMainTabDialog;

}

CDialogTabCtrl::~CDialogTabCtrl()
{
	m_pParityDlg->DestroyWindow();
	if (m_pParityDlg != NULL)
		delete m_pParityDlg;
	//if (m_pMainTabDlg != NULL)
	//	delete m_pMainTabDlg;
	//if (m_pSpeedTestHddDlg != NULL)
	//	delete m_pSpeedTestHddDlg;
}


BEGIN_MESSAGE_MAP(CDialogTabCtrl, CTabCtrl)
		ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CDialogTabCtrl::Init()
{
	iTabCurrent = 0;
	//m_tabPages[0]->Create(IDD_MAIN_DIALOG,this);
	m_pParityDlg->Create(IDD_PARITY_CHECK,this);
	//m_pMainTabDlg->Create(IDD_MAIN_DIALOG,this);
	//m_pSpeedTestHddDlg->Create(IDD_SPEED_HDD,this);

	SetRectangle();
}

void CDialogTabCtrl::SetRectangle()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX=itemRect.left;
	nY=itemRect.bottom+1;
	nXc=tabRect.right-itemRect.left-1;
	nYc=tabRect.bottom-nY-1;

	m_pParityDlg->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	//m_pMainTabDlg->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	//m_pSpeedTestHddDlg->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
}


// CDialogTabCtrl message handlers

enum TAB_DIALOGS_WINDOWS {PARITY= 0, MAIN,SPEEDTESTHDD};

/*
afx_msg void CDialogTabCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTabCtrl::OnLButtonDown(nFlags,point);
	if (iTabCurrent != GetCurFocus())
	{
		switch (iTabCurrent)
		{
		case PARITY:	// 0
			m_pParityDlg->ShowWindow(SW_HIDE);
			iTabCurrent = GetCurFocus();

			switch (iTabCurrent)
			{
			case MAIN:
				m_pMainTabDlg->ShowWindow(SW_SHOW);
				m_pMainTabDlg->SetFocus();
				break;
			case SPEEDTESTHDD:
				m_pSpeedTestHddDlg->ShowWindow(SW_SHOW);
				m_pSpeedTestHddDlg->SetFocus();
				break;
			}
		break;

		case MAIN:	// 1
			m_pMainTabDlg->ShowWindow(SW_HIDE);
			iTabCurrent = GetCurFocus();

			switch (iTabCurrent)
			{
			case PARITY:
				m_pParityDlg->ShowWindow(SW_SHOW);
				m_pParityDlg->SetFocus();
				break;
			case SPEEDTESTHDD:
				m_pSpeedTestHddDlg->ShowWindow(SW_SHOW);
				m_pSpeedTestHddDlg->SetFocus();
				break;
			};
		break;

		case SPEEDTESTHDD:	//2
			m_pSpeedTestHddDlg->ShowWindow(SW_HIDE);
			iTabCurrent = GetCurFocus();

			switch (iTabCurrent)
			{
			case PARITY:
				m_pParityDlg->ShowWindow(SW_SHOW);
				m_pParityDlg->SetFocus();
				break;
			case MAIN:
				m_pMainTabDlg->ShowWindow(SW_SHOW);
				m_pMainTabDlg->SetFocus();
				break;

			};
		break;

		};
	}
}

*/