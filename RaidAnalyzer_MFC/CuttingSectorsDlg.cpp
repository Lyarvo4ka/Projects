// CuttingSectorsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RaidAnalyzer.h"
#include "CuttingSectorsDlg.h"
#include "afxdialogex.h"


// CCuttingSectorsDlg dialog

IMPLEMENT_DYNAMIC(CCuttingSectorsDlg, CDialogEx)

CCuttingSectorsDlg::CCuttingSectorsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCuttingSectorsDlg::IDD, pParent)
	, m_pEditStringDATA(NULL)
	, m_strTextOut(_T(""))
	, m_pTextOutput(NULL)
	, m_pMainText(NULL)
	, m_iNumber( 0 )
	, m_iMin(0)
	, m_iMax(0)
	, m_pTextDigit(NULL)
	, m_pEditTextOut(NULL)
	, m_pButtonPauseResume(NULL)
	, m_pButtBack(NULL)
{
	m_EditStyle = DIGIT_STYLE;
	m_strData = _T("");
	m_iCurrentSTEP = 0;
}
CCuttingSectorsDlg::CCuttingSectorsDlg(CWnd* pParent, UINT _iCurrentStep)
	: CDialogEx(CCuttingSectorsDlg::IDD, pParent)
	, m_pEditStringDATA(NULL)
	, m_strTextOut(_T(""))
	, m_pTextOutput(NULL)
	, m_pMainText(NULL)
	, m_iNumber( 0 )
	, m_iMin(0)
	, m_iMax(0)
{
	m_EditStyle = DIGIT_STYLE;
	m_strData = _T("");
	setCurrentStep(_iCurrentStep);
	m_enStateProgram = enStart;
	m_strHeader = _T("");
}


CCuttingSectorsDlg::~CCuttingSectorsDlg()
{
}

void CCuttingSectorsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT_NUMBER_SECTORS, m_pEditNumberSectors);
	//DDX_Control(pDX, IDC_STATIC_DISK_NUMBER, m_pTextDiskNumber);
	//DDX_Control(pDX, IDC_STATIC_SECTOR_NUMBER, m_pTextSectorNumber);
	//DDX_Control(pDX, IDC_STATIC_MAIN, m_pMainText);
	//DDX_Control(pDX, IDC_STATIC_DIGIT_TEXT, m_pTextDigit);
	//DDX_Control(pDX, IDC_EDIT_TEXT_OUT, m_pEditTextOut);
	//DDX_Control(pDX, IDC_BUTTON_PAUSE_RESUME, m_pButtonPauseResume);
	//DDX_Control(pDX, IDC_BUTTON_BACK, m_pButtBack);
}


BEGIN_MESSAGE_MAP(CCuttingSectorsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCuttingSectorsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CCuttingSectorsDlg::OnBnClickedButtonNext)
	ON_EN_CHANGE(IDC_EDIT_NUMBER_SECTORS, &CCuttingSectorsDlg::OnEnChangeEditNumberSectors)
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_BUTTON_PAUSE_RESUME, &CCuttingSectorsDlg::OnBnClickedButtonPauseResume)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CCuttingSectorsDlg::OnBnClickedButtonBack)
END_MESSAGE_MAP()


void CCuttingSectorsDlg::OnCancel()
{
		if (AfxMessageBox(_T("Are you sure you want Exit?"),MB_YESNO) == IDNO)
		return ;
		CDialogEx::OnCancel();
}
BOOL CCuttingSectorsDlg::OnInitDialog()
{
	//ShowWindow(SW_SHOW);
	CRect rect;
	GetClientRect(&rect);
	SIZE screenSize;
	ZeroMemory( &screenSize, sizeof(SIZE) );
	// Get Width/Height
	screenSize.cx = (LONG)::GetSystemMetrics( SM_CXFULLSCREEN );
	screenSize.cy = (LONG)::GetSystemMetrics( SM_CYFULLSCREEN );

	SetWindowPos(&CDialogEx::wndTopMost,screenSize.cx-rect.Width(),screenSize.cy-rect.Height(),0,0,/*SWP_NOMOVE |*/ SWP_NOSIZE | SWP_NOACTIVATE);

	m_pEditStringDATA = static_cast< CEdit *> ( GetDlgItem ( IDC_EDIT_NUMBER_SECTORS ) );
	//m_pEditStringDATA->SetWindowTextW(m_StringData);
	//m_pTextOutput = static_cast< CStatic * > ( GetDlgItem ( IDC_STATIC_TEXT_OUT ) );
	m_pTextDigit = static_cast< CStatic * > ( GetDlgItem ( IDC_STATIC_DIGIT_TEXT ) );

	m_pEditTextOut = static_cast < CEdit * > ( GetDlgItem ( IDC_EDIT_TEXT_OUT ) );
	m_pButtonPauseResume = static_cast < CButton *> ( GetDlgItem ( IDC_BUTTON_PAUSE_RESUME) );
	m_pButtBack = static_cast < CButton * > (GetDlgItem (IDC_BUTTON_BACK ) );

	if (m_iCurrentSTEP <= 1)
		m_pButtBack->EnableWindow(FALSE);
	CString strFormat = _T("");
	strFormat.Format(_T("STEP #%d"),m_iCurrentSTEP);
	m_pEditTextOut->SetWindowTextW(m_strTextOut);
	CString strMainText = strFormat;
	strMainText.Format(_T("%s %s"),strFormat,m_strHeader);
	this->SetWindowTextW(strMainText);
	switch (m_enStateProgram)
	{
	case enStart:
		m_pButtonPauseResume->SetWindowTextW(_T("START"));
		break;
	case enPause:
		m_pButtonPauseResume->SetWindowTextW(_T("PAUSE"));
		break;
	case enResume:
		m_pButtonPauseResume->SetWindowTextW(_T("RESUME"));
		break;
	default:
		m_pButtonPauseResume->SetWindowTextW(_T("Error"));
	};
	if (m_iCurrentSTEP == 0)
	{
		//LONG lOldStyle = ::GetWindowLongW(*m_pEditTextOut,GWL_STYLE);
		//LONG lNewStyle = lOldStyle ^ ES_RIGHT ^ ES_LEFT;
		//lNewStyle |= ES_CENTER;
		//::SetWindowLongW(*m_pEditTextOut,GWL_STYLE,lNewStyle);
		//m_pEditStringDATA->ShowWindow(SW_HIDE);
		//m_pTextDigit->EnableWindow(SW_HIDE);
	}
	else
	{
		strFormat.Format(_T("Enter Number File (%d - %d)"),m_iMin,m_iMax);
		m_pTextDigit->SetWindowTextW(strFormat);
	}


	DWORD dwStyle = ::GetWindowLong(*m_pEditStringDATA,GWL_STYLE);
	if (m_EditStyle == STRING_STYLE)
		dwStyle &= ~ES_NUMBER ;
	else
		dwStyle |= ES_NUMBER ;
	::SetWindowLongW(*m_pEditStringDATA,GWL_STYLE,dwStyle);
	m_pEditStringDATA->SetFocus();
	return TRUE;
}

void CCuttingSectorsDlg::setMinMax(UINT _iMin, UINT _iMax)
{
	m_iMin = _iMin;
	m_iMax = _iMax;
}


void CCuttingSectorsDlg::OnBnClickedOk()
{
	//CString strCheck;
	//m_pEditNumberSectors->GetWindowTextW(strCheck);
	//UINT iNumberSectors = _ttoi(strCheck);
	//if (iNumberSectors < 0 || iNumberSectors > 10000)
	//{
	//	AfxMessageBox(_T("Number of Sectors is must be from (0 - 10000"),MB_OK);
	//	m_pEditNumberSectors->SetWindowTextW(_T("1000"));
	//}
	//else
	//{
		//m_iNumberSectors = iNumberSectors;
		//BYTE m_iDiskNumber = 0;
		//CDetermineBlock determineBlock(m_SelectedDrives.at(m_pFindData->m_iDiskNumber));
		//determineBlock.setLBA(m_pFindData->m_LBAPosition);
		//determineBlock.setStartSector(m_pFindData->m_dwStartSector);
		//determineBlock.toCutFiles(m_iNumberSectors);
		//system("explorer C:\\JPG\\");
	if (m_strData == _T(""))
	{
		AfxMessageBox(_T("Number is not Entered"),MB_OK);
	}
	else
	if (m_iCurrentSTEP == 0)
	{
		CSingletonJPGs *pSigleton = CSingletonJPGs::GetInstance();
		if ( pSigleton->GetNumberPos(m_iNumber,m_NumberPos) )
		{
			CDialogEx::OnOK();			
		}
		else
			AfxMessageBox(_T("File is not present now..."),MB_OK);
	}
	else
	{
	
	
	CString strText = _T("");
	if (m_iMin == m_iMax)
		CDialogEx::OnOK();
	else
	if (m_iNumber >= m_iMin && m_iNumber <= m_iMax)
	{
		CDialogEx::OnOK();
	}
	else
	{
		strText.Format(_T("Entered number must be (%d-%d)"),m_iMin,m_iMax);
		AfxMessageBox(strText,MB_ICONERROR);
		strText.Format(_T("%d"),m_iMin);
		m_pEditStringDATA->SetWindowTextW(_T(""));
	}
	}
}

void CCuttingSectorsDlg::OnBnClickedButtonNext()
{
	EndDialog(0);
}

void CCuttingSectorsDlg::setEditStyle(EDIT_STYLE _Edit_Style)
{
	m_EditStyle = _Edit_Style;
}

CString CCuttingSectorsDlg::getStringData() const
{
	return m_strData;
}

UINT CCuttingSectorsDlg::getNumber() const
{
	return m_iNumber;
}
NUMBER_POS CCuttingSectorsDlg::getDiskNumberPos() const
{
	return m_NumberPos;
}
enStateProgram CCuttingSectorsDlg::getStatProgram() const
{
	return m_enStateProgram;
}
void CCuttingSectorsDlg::setDefaultData(CString _strData)
{
	m_strData = _strData;
}
void CCuttingSectorsDlg::setTextData(CString _strData)
{
	m_strTextOut = _strData;
}

void CCuttingSectorsDlg::setCurrentStep(UINT _icurrStep)
{
	m_iCurrentSTEP = _icurrStep;
}
void CCuttingSectorsDlg::setStateProgram(enStateProgram _enStateProgram)
{
	m_enStateProgram = _enStateProgram;
	//switch (m_enStateProgram)
	//{
	//case enStart:
	//	m_pButtonPauseResume->SetWindowTextW(_T("START"));
	//	break;
	//case enPause:
	//	m_pButtonPauseResume->SetWindowTextW(_T("PAUSE"));
	//	break;
	//case enResume:
	//	m_pButtonPauseResume->SetWindowTextW(_T("RESUME"));
	//	break;
	//default:
	//	m_pButtonPauseResume->SetWindowTextW(_T("Error"));
	//};

}
void CCuttingSectorsDlg::setHeader(CString _strHeader)
{
	m_strHeader = _strHeader;
}
void CCuttingSectorsDlg::OnEnChangeEditNumberSectors()
{
	m_pEditStringDATA->GetWindowTextW(m_strData);
	m_iNumber = _ttoi(m_strData);
}


void CCuttingSectorsDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	if (m_pEditStringDATA != NULL)
		m_pEditStringDATA->SetFocus();
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
}






void CCuttingSectorsDlg::OnBnClickedButtonPauseResume()
{
	if (m_enStateProgram == enPause)
	{
		m_pButtonPauseResume->SetWindowTextW(_T("RESUME"));
		//AfxGetApp()->m_pMainWnd
		//SendMessageW(WM_SUSPEND_THREAD,,0,0)
		::SendMessageW(AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_SUSPEND_THREAD,0,0);
		m_enStateProgram = enResume;
	}
	else
	if (m_enStateProgram == enResume)
	{
		m_pButtonPauseResume->SetWindowTextW(_T("PAUSE"));
		::SendMessageW(AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_RESUME_THREAD,0,0);
		m_enStateProgram = enPause;
	}

}


void CCuttingSectorsDlg::OnBnClickedButtonBack()
{
	EndDialog(10);
}
