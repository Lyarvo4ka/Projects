// ResumeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RaidAnalyzer.h"
#include "ResumeDlg.h"
#include "afxdialogex.h"


// CResumeDlg dialog

IMPLEMENT_DYNAMIC(CResumeDlg, CDialogEx)

CResumeDlg::CResumeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CResumeDlg::IDD, pParent)
	, m_pTextLBA(NULL)
	, m_pCheckMissmatch(NULL)
{

}

CResumeDlg::~CResumeDlg()
{
	if (m_pTextLBA != NULL)

		m_pTextLBA = NULL;
}

void CResumeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CResumeDlg::OnInitDialog()
{
	//m_lPosLBA = 0;
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	m_pTextLBA = static_cast<CStatic *>
				( GetDlgItem (IDC_TEXT_LBA) );

	CString strText;
	// Sector at LBA are not XORed
	strText.Format(_T("Sector at %I64d are not XORed"),m_lPosLBA);
	m_pTextLBA->SetWindowTextW(strText);
	m_pCheckMissmatch = static_cast < CButton *>
				( GetDlgItem ( IDC_CHECK_MISSMATCH ) );
	m_pCheckMissmatch->SetCheck(TRUE);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CResumeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_MISSMATCH, &CResumeDlg::OnBnClickedCheckMissmatch)
END_MESSAGE_MAP()

void CResumeDlg::setLBAPosition(LONGLONG *_pLBApos)
{
	m_lPosLBA = *_pLBApos;
}

// CResumeDlg message handlers


void CResumeDlg::OnBnClickedCheckMissmatch()
{
	m_iChecked = m_pCheckMissmatch->GetCheck();
}

int CResumeDlg::CheckResult() const
{
	return m_iChecked;
}