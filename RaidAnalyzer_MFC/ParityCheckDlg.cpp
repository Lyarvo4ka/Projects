// ParityCheckDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RaidAnalyzer.h"
#include "ParityCheckDlg.h"
#include "afxdialogex.h"


// CParityCheckDlg dialog

IMPLEMENT_DYNAMIC(CParityCheckDlg, CDialogEx)

CParityCheckDlg::CParityCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CParityCheckDlg::IDD, pParent)
	, m_pEditParityReport(NULL), m_pEditBlockSize(NULL), m_pEditIndent(NULL)
	, m_pEditStep(NULL)
	, m_pButtonStart(NULL)
	, m_pParityProgress(NULL)
	, m_incProgress(0)
	,m_iProgressPos(0)
	,m_MaxLBA(0)
	,m_pLogReport(NULL)
	, m_pRadioFullTest(NULL)
	, m_pRadioSpeedTest(NULL)
	, m_pButtFirstMissmatch(NULL)
	, m_pTxtOffset(NULL)
	, m_pTxtSelection(NULL)
	, m_pTxtBlockSize(NULL)
	, m_pGroupBox(NULL)

{

}

CParityCheckDlg::~CParityCheckDlg()
{
	/*
	if (m_pEditParityReport != NULL)
	{
		delete m_pEditParityReport;
		m_pEditParityReport = NULL;
	}
	if (m_pEditIndent != NULL)
	{
		delete m_pEditIndent;
		m_pEditIndent = NULL;
	}
	if (m_pEditBlockSize != NULL)
	{
		delete m_pEditBlockSize;
		m_pEditBlockSize = NULL;
	}
	if (m_pEditStep != NULL)
	{
		delete m_pEditStep;
		m_pEditStep = NULL;
	}
	if (m_pButtonStart != NULL)
	{
		delete m_pButtonStart;
		m_pButtonStart = NULL;
	}
	if (m_pParityProgress != NULL)
	{
		delete m_pParityProgress;
		m_pParityProgress = NULL;
	}
	if (m_pRadioFullTest != NULL)
	{
		delete m_pRadioFullTest;
		m_pRadioFullTest = NULL;
	}
	if (m_pRadioSpeedTest != NULL)
	{
		delete m_pRadioSpeedTest;
		m_pRadioSpeedTest = NULL;
	}

	if (m_pButtFirstMissmatch != NULL)
	{
		delete m_pButtFirstMissmatch;
		m_pButtFirstMissmatch = NULL;
	}

	if (m_pTxtOffset != NULL)
	{
		delete m_pTxtOffset;
		m_pTxtOffset = NULL;
	}
	if (m_pTxtSelection != NULL)
	{
		delete m_pTxtSelection;
		m_pTxtSelection = NULL;
	}
	if (m_pTxtBlockSize != NULL)
	{
		delete m_pTxtBlockSize;
		m_pTxtBlockSize = NULL;
	}
	if (m_pGroupBox != NULL)
	{
		delete m_pGroupBox;
		m_pGroupBox = NULL;
	}
*/
}



void CParityCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CParityCheckDlg, CDialogEx)
	ON_BN_CLICKED(IDC_START_BUTTON, &CParityCheckDlg::OnBnClickedStartButton)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CParityCheckDlg::OnBnClickedButtonStop)
	ON_MESSAGE(WM_FINISH_PARITY_CHECK,OnFinishCheck)
	ON_MESSAGE(WM_UPDATE_PROGRESS,OnUpdateProgress)
	ON_MESSAGE(WM_UPDATE_MAX_LBA,OnUpdateMaxLBA)
	ON_BN_CLICKED(IDC_CHECK_FIRST_MISSMATCH, &CParityCheckDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO_SPEED_TEST, &CParityCheckDlg::OnBnClickedRadioSpeedTest)
	ON_BN_CLICKED(IDC_RADIO_FULL_TEST, &CParityCheckDlg::OnBnClickedRadioFullTest)
END_MESSAGE_MAP()

BOOL CParityCheckDlg::OnInitDialog()
{
	m_pButtonStart = static_cast <CButton*>
					( GetDlgItem ( IDC_START_BUTTON ) );

	m_pEditIndent = static_cast<CEdit*> 
					( GetDlgItem ( IDC_EDIT_INDENT ) );
	m_pEditBlockSize = static_cast<CEdit*> 
					( GetDlgItem ( IDC_EDIT_BLOCK_SIZE ) );
	m_pEditStep = static_cast<CEdit*> 
					( GetDlgItem ( IDC_EDIT_STEP ) );

	m_pRadioFullTest = static_cast <CButton*>
					( GetDlgItem ( IDC_RADIO_FULL_TEST ) );	

	m_pRadioSpeedTest = static_cast <CButton*>
					( GetDlgItem ( IDC_RADIO_SPEED_TEST ) );	

	m_pButtFirstMissmatch = static_cast <CButton*>
					( GetDlgItem ( IDC_CHECK_FIRST_MISSMATCH ) );

	m_pTxtOffset = static_cast <CStatic*>
					( GetDlgItem ( IDC_STATIC_OFFSET ) );

	m_pTxtSelection = static_cast <CStatic*>
					( GetDlgItem ( IDC_STATIC_SELECTION ) );

	m_pTxtBlockSize = static_cast <CStatic*>
					( GetDlgItem ( IDC_STATIC_BLOCK_SIZE ) );
	m_pGroupBox = static_cast <CStatic*>
					( GetDlgItem ( IDC_STATIC_GROUP ) );

	m_pEditIndent->SetWindowTextW(_T("0"));
	m_pEditBlockSize->SetWindowTextW(_T("256"));
	m_pEditStep->SetWindowTextW(_T("1000"));

	m_pRadioSpeedTest->SetCheck(TRUE);

	m_pParityProgress = static_cast <CProgressCtrl* >
						( GetDlgItem (IDC_PARITY_PROGRESS ) );
	m_pParityProgress->SetRange(0,100);
	m_pParityProgress->SetPos(0);
	m_pParityProgress->SetStep(1);

	return TRUE;
}

DWORD CParityCheckDlg::getIndentSectors()
{
	m_pEditIndent->GetWindowTextW(strEditText);
	DWORD dwIndent = _wtol(strEditText);
	return dwIndent;
}

DWORD CParityCheckDlg::getStep()
{
	m_pEditStep->GetWindowTextW(strEditText);
	DWORD dwStep = _wtol(strEditText);
	return dwStep;
}

DWORD CParityCheckDlg::getBlockSize()
{
	m_pEditBlockSize->GetWindowTextW(strEditText);
	DWORD dwBlockSize = _wtol(strEditText);
	return dwBlockSize;
}

BOOL CParityCheckDlg::getFirstMissmatch() const
{
	return (BOOL)m_pButtFirstMissmatch->GetCheck();
}

void CParityCheckDlg::setMaxLBA(LONGLONG _lMaxLBA)
{
	m_MaxLBA = _lMaxLBA;
}

void CParityCheckDlg::setLog(CLog * _pLog)
{
	m_pLogReport = _pLog;
}

void CParityCheckDlg::OnBnClickedStartButton()
{
	m_pParityProgress->SetPos(0);
	m_pButtonStart->EnableWindow(FALSE);

	//m_pEditParityReport->ReplaceSel(_T("Starting parity check...\r\n"));

	if (m_pRadioSpeedTest->GetCheck())
	{
		::SendMessageA(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_BUTTON_START,PARAM_START_PARITY_TEST,PARAM_SPEED_TEST);
	}

	if (m_pRadioFullTest->GetCheck())
	{
		::SendMessageA(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_BUTTON_START,PARAM_START_PARITY_TEST,PARAM_FULL_TEST);
	}

	m_iProgressPos = 0;

	if ( ( getStep() == 0) || (m_pRadioFullTest->GetCheck()) )
		m_iCountProgress = m_MaxLBA/100;
	else
	{
		m_iCountProgress = getStep();
		m_iCountProgress /= 100;
		if ( m_iCountProgress == 0)
			m_iCountProgress = 1;
	}
}



void CParityCheckDlg::OnBnClickedButtonStop()
{
	::SendMessageA(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_BUTTON_STOP,0,0);
	m_pParityProgress->SetPos(100);
	m_pButtonStart->EnableWindow(TRUE);
	UpdateData(FALSE);
}

LRESULT CParityCheckDlg::OnFinishCheck(WPARAM wParam, LPARAM lParam)
{
	m_pButtonStart->EnableWindow(TRUE);
	m_pParityProgress->SetPos(100);
	
	return TRUE;
}

LRESULT CParityCheckDlg::OnUpdateProgress(WPARAM wParam, LPARAM lParam)
{
	if (m_pRadioFullTest->GetCheck())
		m_incProgress += DEFAULT_SECTORS_SIZE;
	else
		m_incProgress++;
	if (m_incProgress >= m_iCountProgress)
	{
		m_iProgressPos++;
		m_pParityProgress->SetPos(m_iProgressPos);

		m_incProgress = 0;

	}
	return TRUE;
}


LRESULT CParityCheckDlg::OnUpdateMaxLBA(WPARAM wParam, LPARAM lParam)
{
	m_MaxLBA = (LONGLONG)lParam;
	return TRUE;
}

void CParityCheckDlg::OnBnClickedCheck1()
{

	::SendMessageA(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_FIRST_MISSHATCH,WPARAM(m_pButtFirstMissmatch->GetCheck()),0 );
}

void CParityCheckDlg::setVisibles(int _bVisible)
{
	m_pTxtOffset->ShowWindow(_bVisible);
	m_pTxtSelection->ShowWindow(_bVisible);
	m_pTxtBlockSize->ShowWindow(_bVisible);
	m_pEditStep->ShowWindow(_bVisible);
	m_pEditBlockSize->ShowWindow(_bVisible);
	m_pEditIndent->ShowWindow(_bVisible);
	m_pGroupBox->ShowWindow(_bVisible);
}

void CParityCheckDlg::OnBnClickedRadioSpeedTest()
{
	setVisibles(SW_SHOW);
}


void CParityCheckDlg::OnBnClickedRadioFullTest()
{
	setVisibles(SW_HIDE);
}

void CParityCheckDlg::UpdateChecked( int _iChecked)
{
	m_pButtFirstMissmatch->SetCheck(_iChecked);
	OnBnClickedCheck1();
}
