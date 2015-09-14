// TestSpeedHDDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RaidAnalyzer.h"
#include "TestSpeedHDDDlg.h"
#include "afxdialogex.h"
#include "InfoData.h"

// CTestSpeedHDDDlg dialog

IMPLEMENT_DYNAMIC(CTestSpeedHDDDlg, CDialogEx)

CTestSpeedHDDDlg::CTestSpeedHDDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestSpeedHDDDlg::IDD, pParent)
	, m_pEditBlockSize(NULL)
{
	if (m_pEditBlockSize != NULL)
	{
		delete m_pEditBlockSize;
		m_pEditBlockSize = NULL;
	}
}

CTestSpeedHDDDlg::~CTestSpeedHDDDlg()
{

}

void CTestSpeedHDDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(CTestSpeedHDDDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_START, &CTestSpeedHDDDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CTestSpeedHDDDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CTestSpeedHDDDlg message handlers
BOOL CTestSpeedHDDDlg::OnInitDialog()
{
	m_pEditBlockSize = static_cast<CEdit *>
					( GetDlgItem ( IDC_EDIT_BLOCK_SIZE) );
	m_pEditBlockSize->SetWindowTextW(_T("256"));
	return TRUE;
}



void CTestSpeedHDDDlg::OnBnClickedButtonStart()
{
	::SendMessageA(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_BUTTON_START,PARAM_START_SPEED_HDD_TEST,0);
}

DWORD CTestSpeedHDDDlg::getBlockSize()
{	
	CString strBlockSize = _T("");
	m_pEditBlockSize->GetWindowTextW(strBlockSize);
	DWORD dwBlockSize = 0;
	dwBlockSize = _wtol(strBlockSize);
	return dwBlockSize;

}

void CTestSpeedHDDDlg::OnBnClickedButtonStop()
{
	::SendMessageA(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_BUTTON_STOP,0,0);
}
