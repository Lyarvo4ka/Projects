
// DiskVerifierDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DiskVerifier.h"
#include "DiskVerifierDlg.h"
#include "afxdialogex.h"
#include <winioctl.h>



#include "CheckDisk.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



#define DISK_COUNT 2


//#define WM_USER 1

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDiskVerifierDlg dialog




CDiskVerifierDlg::CDiskVerifierDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiskVerifierDlg::IDD, pParent)
	, m_StrDevices(_T(""))
	, m_TextCylinders(_T(""))
	, m_TextBytesPerSector(_T(""))
	, m_llReadSize(0)
	, m_pTaskVerify(NULL)
	, strFileReport(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bEasyOrRandomTest = true;
}

void CDiskVerifierDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DRIVES, m_ListDrives);
	DDX_Control(pDX, IDC_SELECTED_LIST, m_ListSelected);
	//	DDX_Text(pDX, IDC_EDIT_REPORT, m_stEditReport);
	DDX_Control(pDX, IDC_PROGRESS_CHECK, m_ProgressCheck);
	DDX_Control(pDX, IDC_EDIT_SIZE, m_EditCheckSize);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_llReadSize);
	DDX_Control(pDX, IDC_EDIT_REPORT, m_EditReport);
	DDX_Control(pDX, IDC_EDIT_START, m_EditStart);
	DDX_Control(pDX, IDC_EDIT_SELECTIONS, m_pEditSelections);
	DDX_Control(pDX, IDC_FULL_CHECK, m_ButtFullCheck);
	DDX_Control(pDX, IDC_RANDOM_CHECK, m_ButtRandomlCheck);
	DDX_Control(pDX, IDC_EASY_CHECK, m_ButtEasylCheck);
	DDX_Control(pDX, IDC_FIRST_MISMATHC_CHECK, m_ButtToFirstMismatch);
	DDX_Control(pDX, IDC_BUTTON_CHECK, m_ButtCheck);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_ButtClear);
}


BEGIN_MESSAGE_MAP(CDiskVerifierDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CDiskVerifierDlg::OnBnClickedCheckButton)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DRIVES, &CDiskVerifierDlg::OnNMRClickListDrives)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DRIVES, &CDiskVerifierDlg::OnNMClickListDrives)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DRIVES, &CDiskVerifierDlg::OnNMDblclkListDrives)
	ON_MESSAGE(WM_UPDATE_PROGRESS,OnFindNotEqual)
	ON_MESSAGE(WM_FINISH,OnFinishCheck)
	ON_MESSAGE(WM_EDIT_REPORT,OnEditReport)
	ON_MESSAGE(WM_SETNULL_PROGRESS,OnSetNullProgress)
	ON_MESSAGE(WM_EDIT_TEXT_CHANGE,OnEditTEXT)
	ON_BN_CLICKED(IDC_STOP_BUTTON, &CDiskVerifierDlg::OnBnClickedStopButton)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDiskVerifierDlg::OnBnClickedButtonClear)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDOK, &CDiskVerifierDlg::OnBnClickedOk)
END_MESSAGE_MAP()



// CDiskVerifierDlg message handlers

BOOL CDiskVerifierDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	m_Drives.getDiskNames();


	m_ListDrives.InsertColumn(0,_T("#"),LVCFMT_LEFT,-1);
	m_ListDrives.InsertColumn(1,stSector_Count,LVCFMT_LEFT,-1);
	m_ListDrives.InsertColumn(2,stSerial_Number,LVCFMT_LEFT,-1);
	m_ListDrives.InsertColumn(3,stDisk_NAME,LVCFMT_LEFT,-1);
	m_ListDrives.InsertColumn(4,stBytes_Per_Secors,LVCFMT_LEFT,-1);



	m_vecDrives = m_Drives.getDiskDrives();

	vector<CDiskDrive>::reverse_iterator rit;

	m_ProgressCheck.SetRange(1,1000);
	m_ProgressCheck.SetPos(0);

	m_EditStart.SetWindowTextW(_T("1"));

	CDiskDrive bufDrive;
	for (rit = m_vecDrives.rbegin(); rit != m_vecDrives.rend(); ++rit)
	{
	
		bufDrive = *rit;
		int iIndex = 0;
		CString str;
		// NUMBER DISK
		str.Format(_T("%i( %i GB )"),bufDrive.getDiskNumber(),bufDrive.getDiskSize());
		iIndex = m_ListDrives.InsertItem(LVIF_TEXT|LVIF_STATE,0,str,LVIS_SELECTED,LVIS_SELECTED,0,0);

		// Sector Count
		str = _T("");
		str.Format(_T("%I64d"),bufDrive.getSectorCount());

		m_ListDrives.SetItem(iIndex,1,LVIF_TEXT|LVIF_STATE,str,LVIS_SELECTED,LVIS_SELECTED,0,0);
		// Serial Number
		m_ListDrives.SetItem(iIndex,2,LVIF_TEXT|LVIF_STATE,bufDrive.getSerialNumber(),LVIS_SELECTED,LVIS_SELECTED,0,0);
		// Disk Name
		m_ListDrives.SetItem(iIndex,3,LVIF_TEXT|LVIF_STATE,bufDrive.getDiskName(),LVIS_SELECTED,LVIS_SELECTED,0,0);
		// Bytes Per Sector
		str = _T("");
		str.Format(_T("%i"),bufDrive.getBytesPerSector());
		m_ListDrives.SetItem(iIndex,4,LVIF_TEXT|LVIF_STATE,str,LVIS_SELECTED,LVIS_SELECTED,0,0);

		//str.Format(_T("%i"),bufDrive.g());
	}

	m_ListDrives.SetColumnWidth(0,LVSCW_AUTOSIZE_USEHEADER);
	m_ListDrives.SetColumnWidth(1,LVSCW_AUTOSIZE_USEHEADER);
	m_ListDrives.SetColumnWidth(2,LVSCW_AUTOSIZE_USEHEADER);
	m_ListDrives.SetColumnWidth(3,LVSCW_AUTOSIZE_USEHEADER);
	m_ListDrives.SetColumnWidth(4,LVSCW_AUTOSIZE_USEHEADER);
	m_ListDrives.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_EditReport.SetLimitText(UINT_MAX);
	m_pEditSelections.SetWindowTextW(_T("100"));
	m_ButtFullCheck.SetCheck(FALSE);
	m_ButtToFirstMismatch.SetCheck(TRUE);
	m_ButtEasylCheck.SetCheck(TRUE);
	m_ButtRandomlCheck.SetCheck(TRUE);




	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDiskVerifierDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDiskVerifierDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDiskVerifierDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CDiskVerifierDlg::setDiskReport(CDiskDrive & _diskDrive)
{
	CString stDiskReport = _T("");
	CString strBuff = _T("");

	strBuff.Format(_T("Selected Disk # %i - Disk Size ( %i GB ) "),_diskDrive.getDiskNumber(),_diskDrive.getDiskSize());
	stDiskReport += strBuff;
	strBuff.Empty();
	strBuff.Format(_T("Serial Number is %s \r\n"),_diskDrive.getSerialNumber());
	stDiskReport += strBuff;
	return stDiskReport;
}





CString CDiskVerifierDlg::getTimeReport()
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

void CDiskVerifierDlg::WirteDiskInfoReport(CStdioFile *pFileWrite, const CDiskDrive & _diskDrive )
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





//LRESULT /*CALLBACK */CDiskVerifierDlg::WindowProc(/*HWND hwnd,*/ UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch(message)
//	{
//	case (WM_USER + 1 ):
//		m_ProgressCheck.SetPos(m_ProgressCheck.GetPos() + 1000);
//	break;
//	case BN_CLICKED(message, &CDiskVerifierDlg::OnBnClickedButton1):
//		break;
//	}
//
//	return DefWindowProc(message,wParam,lParam);
//}



DWORD WINAPI ThreadVerifyDisk(vector<READDATA*> & _vecReadDATA)
{


	return 0;
}

LRESULT CDiskVerifierDlg::OnFindNotEqual(WPARAM wParam, LPARAM lParam)
{
	int iPos = m_ProgressCheck.GetPos() + 1;
	m_ProgressCheck.SetPos(iPos);
		UpdateData(FALSE);
	return 1;
}

LRESULT CDiskVerifierDlg::OnFinishCheck(WPARAM wParam, LPARAM lParam)
{
	CStdioFile fileReportTxt;
	if (!fileReportTxt.Open(strFileReport,CFile::modeWrite))
			AfxMessageBox(_T("Unable to open file"),MB_OK);

	fileReportTxt.SeekToEnd();
	m_pTaskVerify->WirteTimeReport(&fileReportTxt,1);
	CString strReport;

	CString strRandom,strFull,strFollow;

	if (m_testNumbers.bRandomTest)
		if ((LONGLONG)wParam == 0)
			strRandom = _T("Random Test not found unequal sectors\r\n");
		else 
		{
			strReport.Format(_T("\r\n Total found sectors in Random Test %I64d\r\n"),(LONGLONG)wParam);
			fileReportTxt.WriteString(strReport);

			strRandom.Format(_T("Random Test found %I64d unequal sectors\r\n"),(LONGLONG)wParam);
		}
	if (m_testNumbers.bEasyTest)
		if ((LONGLONG)lParam == 0)
			strFollow = _T("FOLLOW STEP Test not found unequal sectors\r\n");
		else 
		{
			strReport.Format(_T("\r\n Total found sectors in FOLLOW STEP Test %I64d"),(LONGLONG)lParam);
			fileReportTxt.WriteString(strReport);

			strFollow.Format(_T("FOLLOW STEP Test found %I64d unequal sectors\r\n"),(LONGLONG)lParam);
		}
	else
		if (m_testNumbers.bFullTest)
		if ((LONGLONG)lParam == 0)
			strFull = _T("Full Test not found unequal sectors\r\n");
		else 
		{
			strReport.Format(_T("\r\n Total found sectors in FULL Test %I64d"),(LONGLONG)lParam);
			fileReportTxt.WriteString(strReport);

			strFull.Format(_T("Full Test found %I64d unequal sectors\r\n"),(LONGLONG)lParam);
		}


	strReport.Format(_T("%s%s%s"),strRandom,strFollow,strFull);
	fileReportTxt.Close();

	AfxMessageBox(strReport,MB_OK);

	delete m_pTaskVerify;
	m_ButtCheck.EnableWindow(TRUE);
	m_ButtClear.EnableWindow(TRUE);

	if (!hVerifyThread)
		CloseHandle(hVerifyThread);

	return 1;
}

LRESULT CDiskVerifierDlg::OnEditReport(WPARAM wParam, LPARAM lParam)
{
	CString strReport;
		strReport.Format(_T("HDD NOT EQUAL\r\n "));
	

	m_EditReport.ReplaceSel(strReport);


	return 1;
}

LRESULT CDiskVerifierDlg::OnSetNullProgress(WPARAM wParam, LPARAM lParam)
{

	m_ProgressCheck.SetPos(0);


	return 1;
}

LRESULT CDiskVerifierDlg::OnEditTEXT(WPARAM wParam, LPARAM lParam)
{

	CString strFormat;
	switch (lParam)
	{
	case NEW_STRING:
		m_EditReport.ReplaceSel(_T("\r\n"));
		break;
	case START_RANDOM:
		m_EditReport.ReplaceSel(_T("Starting Random check "));
		strFormat = getTimeReport();
		m_EditReport.ReplaceSel(strFormat);
		break;
	case FINISH_RANDOM:
		m_EditReport.ReplaceSel(_T("Finish Random check "));
		strFormat = getTimeReport();
		m_EditReport.ReplaceSel(strFormat);

		break;
	case START_STEP_FOLLOW:
		m_EditReport.ReplaceSel(_T("Starting Follow Step check "));
		strFormat = getTimeReport();
		m_EditReport.ReplaceSel(strFormat);
		break;
	case FINISH_STEP_FOLLOW:
		m_EditReport.ReplaceSel(_T("Finish Follow Step check "));
		strFormat = getTimeReport();
		m_EditReport.ReplaceSel(strFormat);
		break;
	case START_FULL:
		m_EditReport.ReplaceSel(_T("Starting FULL check "));
		strFormat = getTimeReport();
		m_EditReport.ReplaceSel(strFormat);
		break;
	case FINISH_FULL:
		m_EditReport.ReplaceSel(_T("Finish FULL check "));
		strFormat = getTimeReport();
		m_EditReport.ReplaceSel(strFormat);
		break;

	};


	return 1;
}


DWORD WINAPI ThreadRandomVerifyDisk(LPVOID lParam)
{
	PVERIFY_RANGE verifyRange = (PVERIFY_RANGE)lParam;

	return 0;
}


void CDiskVerifierDlg::OnBnClickedCheckButton()
{

	CString strReport = _T("");



	m_ProgressCheck.SetPos(0);

	if (!m_vecSelDrives.empty())
	{
		if ( m_vecSelDrives.size() > 1 )
		{
			
		CString strSize = _T("");

		m_EditStart.GetWindowText(strSize);
		verifyRange.lFrom = _ttoi64(strSize);

		m_EditCheckSize.GetWindowText(strSize);
		verifyRange.lTo = _ttoi64(strSize);

		UINT iCount = 0;
		m_pEditSelections.GetWindowTextW(strSize);
		iCount = _ttoi(strSize);
		m_ProgressCheck.SetRange(0,iCount);

		strFileReport.Format(_T("%s-%s.txt"),m_vecSelDrives.at(0).getSerialNumber(),m_vecSelDrives.at(1).getSerialNumber());
			CStdioFile fileReportTxt;
			//if (!fileReportTxt.Open(_T("Reoprt.txt"),CFile::modeWrite))
			if (!fileReportTxt.Open(strFileReport,CFile::modeWrite|CFile::modeCreate))
				AfxMessageBox(_T("Unable to open file"),MB_OK);
			fileReportTxt.SeekToEnd();
			for ( size_t i = 0; i < m_vecSelDrives.size(); ++i)
				WirteDiskInfoReport(&fileReportTxt,m_vecSelDrives.at(i));
			fileReportTxt.Close();




		m_pTaskVerify = new CTaskVerify();



		
		m_testNumbers.bEasyTest = m_ButtEasylCheck.GetCheck();
		m_testNumbers.bRandomTest = m_ButtRandomlCheck.GetCheck();
		m_testNumbers.bFullTest = m_ButtFullCheck.GetCheck();
		m_testNumbers.isFirstMismatch = m_ButtToFirstMismatch.GetCheck();

		m_pTaskVerify->setTestNumbers(m_testNumbers);
		m_pTaskVerify->setDisk(m_vecSelDrives);
		m_pTaskVerify->setRange(verifyRange);
		m_pTaskVerify->setCountSelection(iCount);
		m_pTaskVerify->setFileReportPath(strFileReport);

		m_pTaskVerify->CreateThreads();

		m_ButtCheck.EnableWindow(FALSE);
		m_ButtClear.EnableWindow(FALSE);



			//if (m_ButtFullCheck.GetCheck())
			//{
			//for ( size_t i = 0; i < m_vecSelDrives.size(); ++i)
			//{

			//	READDATA *pReadDATA = new READDATA(m_vecSelDrives.at(i).getDiskDrive());
			//	pReadDATA->verifyRange.lFrom = verifyRange.lFrom;
			//	pReadDATA->verifyRange.lFrom *= 512;

			//	m_EditCheckSize.GetWindowText(strSize);
			//	pReadDATA->verifyRange.lTo = verifyRange.lTo;
			//	pReadDATA->verifyRange.lTo *= 512;


			//	m_vecReadDATA.push_back(pReadDATA);


			//}

			//// ReadDisk



			//hVerifyThread = CreateThread(NULL, 0,
			//							(LPTHREAD_START_ROUTINE)ThreadVerifyDisk,
			//							&m_vecReadDATA,
			//							0,
			//							NULL);

			//} // FULL CHECK


		}
		else
			AfxMessageBox(_T("Selected only One Disk"),MB_OK);



	}
	else
		AfxMessageBox(_T("No Disk Selected to Check"),MB_OK);

	//UpdateData(FALSE);
	

	//fileReportTxt.Close();
	//return 0;

}







bool CDiskVerifierDlg::CheckBytes(BYTE *pByteCheck, const BYTE & _size)
{
	BYTE *pbyCheck = NULL;
	pbyCheck = &pByteCheck[0];
	for (BYTE i = 1; i < _size; ++i)
	{
		if ( *pbyCheck != pByteCheck[i])
			return false;
	}
	return true;
}




//bool CDiskVerifierDlg::isPhysicalEqulToLogical(BYTE * pPasport)
//{
//	WORD *wLogicalSectorSize = (WORD*)&pPasport[106*2];
//	//setWordFrom2Bytes(pPasport,wLogicalSectorSize);
//
//	// check 14 bit to 1
//	if (*wLogicalSectorSize & 0x4000)
//	{
//		// check 15 bit to 0
// 		if (*wLogicalSectorSize ^ 0x8000)
//		{
//			// Infomation is Valid
//			if (*wLogicalSectorSize ^ 0x2000)
//				return true;
//			
//		}
//	}
//
//
//	return false;
//}

//void CDiskVerifierDlg::setWordFrom2Bytes(BYTE * pPasport, WORD * pWord, BYTE _pos)
//{
//		pWord = (WORD*)&pPasport[106*2];
//
//}

bool CDiskVerifierDlg::AddSelectedDrive(int iPos)
{
	CDiskDrive selDisks;
	if (!m_vecDrives.empty())
	{
		if (m_vecSelDrives.empty())
			m_vecSelDrives.push_back(m_vecDrives.at(iPos));
		else
		{
			for (size_t i = 0; i < m_vecSelDrives.size(); ++i)
			{
				if ( m_vecSelDrives.at(i).getDiskNumber() == m_vecDrives.at(iPos).getDiskNumber() )
					return false;
			}
			m_vecSelDrives.push_back(m_vecDrives.at(iPos));
		}	
		return true;
	}

	return false;
}



void CDiskVerifierDlg::OnNMRClickListDrives(NMHDR *pNMHDR, LRESULT *pResult)
{
	//CMenu menu;
	//menu.CreateMenu();


	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int iItemCount = m_ListDrives.GetItemCount();
	UINT uState;

	bool bSelect = false;
	bool bPresent = false;

	CString str;
	if (m_vecSelDrives.size() < 2)
	{
	for (int iItem = 0; iItem < iItemCount; ++iItem)
	{
		uState = m_ListDrives.GetItemState(iItem,LVNI_SELECTED);
		if (uState & LVIS_SELECTED)
		{
			bSelect = true;
			if ((bPresent = AddSelectedDrive(iItem)))
			{
				str.Format(_T("Disk # %i : %s"),m_vecDrives.at(iItem).getDiskNumber(),m_vecDrives.at(iItem).getSerialNumber());
				m_ListSelected.AddString(str);
			}

		}
	}

	if (!m_vecSelDrives.empty())
	{
		if (m_vecSelDrives.size() == 1)
			m_llReadSize = m_vecSelDrives.at(0).getSectorCount();
		else
		for ( size_t i = 0; i < m_vecSelDrives.size(); ++i)
		{
			if ( m_llReadSize > m_vecSelDrives.at(i).getSectorCount() )
			{
				m_llReadSize = m_vecSelDrives.at(i).getSectorCount();
			}
		}

	CString stMaxLBA;
	stMaxLBA.Format(_T("%I64d"), m_llReadSize );
	m_EditCheckSize.SetWindowTextW(stMaxLBA);


	}


	if (!bSelect)
		AfxMessageBox(_T("Is not selected drives"),MB_OK);
	if (!bPresent)
		AfxMessageBox(_T("Drives is already present!!!"),MB_OK);
	}
	else
		AfxMessageBox(_T("Selected only 2 drives !!!"),MB_OK);



//	for (int i =0 ; i < m_ListSelected.getIte
	//m_ListSelected
	//m_ListSelected.AddString(m_vecDrives.at(iItem).getDiskName());
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CDiskVerifierDlg::OnNMClickListDrives(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	int iItem = pNMItemActivate->iItem;

	*pResult = 0;
}



void CDiskVerifierDlg::OnNMDblclkListDrives(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnNMRClickListDrives(pNMHDR,pResult);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CDiskVerifierDlg::OnBnClickedStopButton()
{

	if (m_pTaskVerify != NULL)
		m_pTaskVerify->setStopSignal();

	//AfxMessageBox(_T("STOP!!!!"),MB_OK);
	//if (!hVerifyThread)
	//	CloseHandle(hVerifyThread);
	// TODO: Add your control notification handler code here
}




	void CDiskVerifierDlg::OnBnClickedButtonClear()
{
	m_vecSelDrives.clear();
	m_ListSelected.ResetContent();

}


/*
	//WaitForMultipleObjects(1,&hVerifyThread,TRUE,INFINITE);

	//AfxMessageBox(_T("FINISH!!!"),MB_OK);

///////////////////////////////////////////////////////////////////////
	//		ArrBytes *arBytes = new ArrBytes[iDiskCount];
	//		for ( size_t i = 0; i < m_vecSelDrives.size(); ++i)
	//	
	//			arBytes[i].setBytes(iMaxSectorSize);



	//		LONGLONG llCount = 0;
	//		m_ProgressCheck.SetPos(0);



	//		DWORD *dwBytesRead = new DWORD[1];
	//		*dwBytesRead = 0;


	//		vector<CDiskDrive>::iterator itDisks;
	//		CDiskDrive *pDrive = NULL;

	//		BYTE byDiskCount = 0;

	//		BYTE *byCheckByte = new BYTE[iDiskCount];

	//		LARGE_INTEGER pliDistMove;
	//		pliDistMove.QuadPart = 0;


	//		PLARGE_INTEGER pliNewFilePointer = NULL;
	//		pliNewFilePointer = new LARGE_INTEGER;
	//		pliNewFilePointer->QuadPart = 0;



	//	CString strSize;
	//	m_EditCheckSize.GetWindowText(strSize);
	//	m_llReadSize = _ttoi64(strSize);

	//	m_EditStart.GetWindowText(strSize);
	//	llCount = _ttoi64(strSize);
	//		

	//WirteTimeReport(&fileReportTxt,0);

	//	while (llCount != m_llReadSize)
	//	{
	//		//dwCopyProgress = dwStepProgress * dwProgress;
	//		//if (dwCount < dwCopyProgress)
	//		//{
	//		//	m_ProgressCheck.SetPos(dwProgress);
	//		//	dwProgress++;
	//		//}
	//		byDiskCount = 0;
	//		//for ( itDisks =  m_vecSelDrives.begin() ; itDisks != m_vecSelDrives.end(); ++itDisks)
	//		//{

	//		//	pDrive = itDisks._Ptr;
	//		//	*dwBytesRead = 0;
	//		//	if (!pDrive->ReadBytes(iMaxSectorSize,dwBytesRead,arBytes[byDiskCount].pBytes))
	//		//	{
	//		//		strReport.Format(_T("Can't read bytes from Disk #%i\n"),pDrive->getDiskNumber());
	//		//		fileReportTxt.WriteString(strReport);
	//		//		AfxMessageBox(strReport,MB_OK);
	//		//		exit(0);
	//		//	}
	//		//	++byDiskCount;
	//		//
	//		//}


	//		for ( BYTE i =  0 ; i < m_vecSelDrives.size(); ++i)
	//		{

	//			*dwBytesRead = 0;
	//			if ( !m_vecSelDrives.at(i).ReadBytes(iMaxSectorSize,dwBytesRead,arBytes[i].pBytes,pliDistMove,pliNewFilePointer) )
	//			{
	//				strReport.Format(_T("Can't read bytes from Disk #%i\n"),m_vecSelDrives.at(i).getDiskNumber());
	//				fileReportTxt.WriteString(strReport);
	//				//AfxMessageBox(strReport,MB_OK);
	//				exit(0);
	//			}
	//			else
	//			{
	//				//pliDistMove.QuadPart = pliNewFilePointer->QuadPart;
	//			}
	//		}
	//		
	//		pliDistMove.QuadPart += iMaxSectorSize;

	//
	//		if (!checkDisk(arBytes,byCheckByte,iDiskCount))
	//		{
	//			strReport.Format(_T("HDD NOT EQUAL LBA # %I64d of (%ibytes) "),llCount,iMaxSectorSize);
	//			strReport += _T("\r\n");
	//			////m_stEditReport += 
	//			fileReportTxt.WriteString(strReport);
	//			////m_EditReport.SetWindowTextW(strReport);
	//			//m_EditReport.ReplaceSel(strReport);
	//			////AfxMessageBox(strReport,MB_OK);

	//			//break;
	//		}

	//		++llCount; 

	//	}

	//	delete arBytes;
	//	m_EditReport.ReplaceSel(_T("\r\n"));

	//	for ( size_t i = 0; i < m_vecSelDrives.size(); ++i)
	//		m_vecSelDrives.at(i).ClosePhysicalDisk();

	//	WirteTimeReport(&fileReportTxt,1);
	//	strReport = _T("\r\n Finish testing!!!\r\n");
	//	m_EditReport.ReplaceSel(strReport);
	//	 
	//	fileReportTxt.WriteString(strReport);


	//	AfxMessageBox(_T("FINISH !!!"),MB_OK);




	*/

void CDiskVerifierDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_ESCAPE)
		AfxMessageBox(_T("Escape Pressed"),MB_OK);
	//CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CDiskVerifierDlg::OnCancel()
{
	//CDialogEx::OnCancel();
}

void CDiskVerifierDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}
