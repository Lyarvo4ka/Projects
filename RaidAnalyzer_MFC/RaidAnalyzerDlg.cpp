
#include "stdafx.h"
#include "afxdialogex.h"

#include "CAboutDlg.h"
#include "RaidAnalyzer.h"
#include "RaidAnalyzerDlg.h"
#include "MainTabDialog.h"
#include "ParityCheckDlg.h"

#include "GatherByJPG.h"
#include "DetermineBlock.h"
#include "Buffer.h"
#include "ResumeDlg.h"
#include "../DiskVerifier/DiskDrive.h"

#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Settings.h"
#include "Utility.h"

#include "PreferenceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DeviceLibrary/AbstractFactory.h"
#include "DeviceLibrary/Devices.h"

CRaidAnalyzerDlg::CRaidAnalyzerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRaidAnalyzerDlg::IDD, pParent)
	, pReadDisk(NULL),m_Data(NULL),pMAP(NULL)
	, m_pListDrives(NULL)
	, m_pListSelected(NULL)
	, m_pEditReport(NULL)
	, m_pEditMinLBA(NULL)
	, m_pEditMaxLBA(NULL)
	, m_bSequence(TRUE),m_lFirstPos(0),m_lLastPos(0),m_bIsExecuting(FALSE)
	, m_lCountProgress(0)
	, m_iTestStarted(0)
	,m_lTempProgress(0)
	,m_enStateProgram(enStart)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_notEqaulSectors.lFirst = 0;
	m_notEqaulSectors.lCurrent = 0;
	m_notEqaulSectors.lInterval = 0;
	m_hWaitAnswer = CreateEvent(NULL,TRUE,FALSE,_T("Event, wait Answer First Mistmatch"));
	hComunicateLock = NULL;
	pResultCutting = new RESULT_CUTTING_SECTORS();
	m_pSingleton = CSingletonJPGs::GetInstance();
	m_TabDialogs = new CDialogTabCtrl();
	//pCuttingDialog = NULL;

}

CRaidAnalyzerDlg::~CRaidAnalyzerDlg()
{
	ClearData();
	m_pSingleton = CSingletonJPGs::GetInstance();
	m_pSingleton->RemoveInstance();
	if (m_TabDialogs != NULL)
	{
		delete m_TabDialogs;
		m_TabDialogs = NULL;
	}
	delete pResultCutting;
}


void CRaidAnalyzerDlg::ClearData()
{
	m_pSingleton = CSingletonJPGs::GetInstance();
	m_pSingleton->RemoveData();
	if (hComunicateLock != NULL)
	{
		AbortThreads();
		CloseHandle(hComunicateLock[0]);
		CloseHandle(hComunicateLock[1]);
		delete hComunicateLock;
		hComunicateLock = NULL;
	}
	if (pMAP != NULL)
	{
		delete pMAP;
		pMAP = NULL;
	}
	if (m_Data != NULL)
	{
		delete m_Data;
		m_Data = NULL;
	}
	if (pReadDisk != NULL)
	{
		delete [] pReadDisk;
		pReadDisk = NULL;
	}
	//if (m_ReportLog != NULL)
	//{
	//	delete m_ReportLog;
	//	m_ReportLog = NULL;
	//}
}


//void CRaidAnalyzerDlg::OnDestroy()
//{
//	//Sleep(1000);
//	ClearData();
//	m_vecDrives.clear();
//	m_vecSelDrives.clear();
//	CloseHandle(m_hWaitAnswer);
//	CDialogEx::OnDestroy();
//
//}

void CRaidAnalyzerDlg::OnCancel()
{
	OnOK();
	
}

void CRaidAnalyzerDlg::OnOK()
{
	if (AfxMessageBox(_T("Are you sure you want to Exit?"),MB_YESNO) == IDNO)
		return ;
	//::SendMessageA(m_TabDialogs.m_pParityDlg->GetSafeHwnd(),WM_FINISH_PARITY_CHECK,0,0);
	if (pMAP != NULL)
	{
		pMAP->setStop();
		//pMAP->ExitThreads();
	}

	//if (pReadDisk != NULL)
	//{
	//	for (size_t i = 0; i < m_vecSelDrives.size(); ++i)
	//		pReadDisk[i].setStopSignal();

	//}
	::ResetEvent(m_hWaitAnswer);
	if (pMAP != NULL)
		pMAP->deleteBuffer();
	//ClearData();


	if (m_ReportLog != NULL)
	{
		delete m_ReportLog;
		m_ReportLog = NULL;
	}
	//if (pCuttingDialog != NULL)
	//{
	//	delete pCuttingDialog;
	//	pCuttingDialog = NULL;
	//}


	CDialogEx::OnOK();
}


void CRaidAnalyzerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_DIALOGS, *m_TabDialogs);
	//DDX_Control(pDX, IDC_LIST_DRIVES, m_pListDrives);
	//DDX_Control(pDX, IDC_SELECTED_LIST, m_pListSelected);
	//DDX_Control(pDX, IDC_EDIT_PARITY_LOG, m_pEditReport);
	//DDX_Control(pDX, IDC_MIN_LBA, m_pEditMinLBA);
	//DDX_Control(pDX, IDC_MAX_LBA, m_pEditMaxLBA);
	DDX_Control(pDX, IDC_PROGRESS_PROG, m_MainProgress);
	DDX_Control(pDX, IDC_BUTTON_JPG, m_GatherByJPG);
}

BEGIN_MESSAGE_MAP(CRaidAnalyzerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DRIVES, &CRaidAnalyzerDlg::OnNMDblclkListDrives)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CRaidAnalyzerDlg::OnBnClickedClearButton)
	ON_EN_CHANGE(IDC_MIN_LBA, &CRaidAnalyzerDlg::OnEnChangeMinLba)
	ON_EN_CHANGE(IDC_MAX_LBA, &CRaidAnalyzerDlg::OnEnChangeMaxLba)
	ON_MESSAGE(WM_BUTTON_START,OnStartButtonPressed)
	ON_MESSAGE(WM_BUTTON_STOP,OnStopButtonPressed)
	ON_MESSAGE(WM_PARITY_CHECK_NOT_EQUAL_FIRST,OnUpdateReportFirst)
	ON_MESSAGE(WM_PARITY_CHECK_NOT_EQUAL_LAST,OnUpdateReportLast)
	ON_MESSAGE(WM_FIRST_MISSHATCH,OnSetFirstMissmatch)
	ON_MESSAGE(WM_UPDATE_PARITY_CHECK_PROGRESS,OnParityCheckProgress)
	ON_MESSAGE(WM_SHOW_MISSHATCH,OnShowMissmatchDlg)
	ON_MESSAGE(WM_SET_PAUSE,OnSetPause)
	ON_MESSAGE(WM_FINISH_PARITY_CHECK,OnFinishCheck)
	ON_MESSAGE(WM_FINISH_GATHER_BY_JPG,OnFinishGatherByJPG)
	ON_MESSAGE(WM_SHOW_CUTTING_DIGLOG,OnShowCuttingDialog)
	// Thread operation
	ON_MESSAGE(WM_SUSPEND_THREAD,OnSuspendThreads)
	ON_MESSAGE(WM_RESUME_THREAD,OnResumeThreads)
	ON_MESSAGE(WM_ABORT_THREAD,OnAbortThreads)
	ON_BN_CLICKED(IDC_REMOVE_SELECTED, &CRaidAnalyzerDlg::OnBnClickedRemoveSelected)
	ON_LBN_SELCHANGE(IDC_SELECTED_LIST, &CRaidAnalyzerDlg::OnLbnSelchangeSelectedList)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_LOG, &CRaidAnalyzerDlg::OnBnClickedButtonClearLog)
	ON_BN_CLICKED(IDC_BUTTON_JPG, &CRaidAnalyzerDlg::OnBnClickedButtonJpg)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CRaidAnalyzerDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_ADD_BUTTON_FILE, &CRaidAnalyzerDlg::OnBnClickedAddButtonFile)
	ON_BN_CLICKED(IDC_BUTTON4, &CRaidAnalyzerDlg::OnBnClickedButton4)
END_MESSAGE_MAP()




BOOL CRaidAnalyzerDlg::OnInitDialog()
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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	m_TabDialogs->InsertItem(0,_T("Parity Check"));
	//m_TabDialogs->InsertItem(1,_T("MAIN DIALOG"));
	//m_TabDialogs->InsertItem(2,_T("Speed Test HDD"));
	m_TabDialogs->Init();

	//CDiskFactory diskfactory;
	//IDevice *pDevice = new CDiskDevice();
	//	//= diskfactory.CreateDevice();
	//CDiviceList devList;
	//devList.AddDevice(pDevice);
	//devList.RemoveAll();
	////delete pDevice;
	//pDevice->SetNumber(10);
	//if (pDevice != NULL)
	//	delete pDevice;

	//m_TabDialogs->InsertItem(0,_T("Parity Check"));
	//m_TabDialogs->Init();

	//IDevice *pDevice = new CDiskDevice();
	//pDevice->SetBytesPerSector(512);
	//delete pDevice;
	m_Drives.getDiskNames();

	m_pListDrives = static_cast<CListCtrl*> 
					( GetDlgItem ( IDC_LIST_DRIVES ) );
	setDevices(m_pListDrives,&m_Drives,m_vecDrives);

	m_pListSelected = static_cast<CListBox*>
					( GetDlgItem ( IDC_SELECTED_LIST ) );

	m_pEditReport = static_cast < CEdit *>
					( GetDlgItem ( IDC_EDIT_PARITY_LOG ) );
	m_pEditReport->SetLimitText(UINT_MAX);

	m_ReportLog = new CLog(_T("Parity Check"),m_pEditReport);
	//m_TabDialogs.m_pParityDlg->setLog(m_ReportLog);

	m_pEditMinLBA = static_cast < CEdit *>
					( GetDlgItem ( IDC_MIN_LBA ) );
	m_pEditMinLBA->SetWindowTextW(_T("0"));
	m_pEditMaxLBA = static_cast < CEdit *>
					( GetDlgItem ( IDC_MAX_LBA ) );					
	m_pEditMaxLBA->SetWindowTextW(_T("1000"));

	m_dwProgressPos = 0;
	m_MainProgress.SetRange(0,PROGRESS_COUNT);
	m_MainProgress.SetStep(1);

	//pCuttingDialog = new CCuttingSectorsDlg(this);
	//pCuttingDialog->Create(CCuttingSectorsDlg::IDD);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRaidAnalyzerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRaidAnalyzerDlg::OnPaint()
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

HCURSOR CRaidAnalyzerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define RANGE_FROM 0
#define RANGE_TO 10000

#define MIN_HDD 2

#define ToUnLock TRUE
#define ToLock FALSE


LRESULT CRaidAnalyzerDlg::OnStartButtonPressed(WPARAM wParam, LPARAM lParam)
{
	//CPhysicalDevice DiskDevices;
	//CDiviceList DeviceList;
	////DiskDevices.GetDevices(DeviceList);
	////DeviceList.RemoveAll();
	//IDeviceFactory *pFactory = new CDiskFactory();
	//CDiskDevice *pDevice = pFactory->CreateDevice();
	////DiskDevices.GetDevice(pDevice,1);
	////DeviceList.AddDevice(pDevice);
	////DeviceList.RemoveAll();
	//delete pFactory;


//	pFileWrite.is
	if ( !pFileWrite.Open(_T("Report.txt"),CFile::modeWrite) )
	{
		if (!pFileWrite.Open(_T("Report.txt"),CFile::modeCreate|CFile::modeWrite) )
		{
			pFileWrite.Close();
			pFileWrite.Open(_T("Report.txt"),CFile::modeCreate|CFile::modeWrite);
		}
	
		
	}
	pFileWrite.SeekToEnd();
	pFileWrite.WriteString(_T("Starting...\r\n"));
	m_ReportLog->AddEvent(cmd_START);
	CString strTimeReport = getTimeCurrent();
	pFileWrite.WriteString(strTimeReport);
	m_ReportLog->AddText(strTimeReport);
	UINT iStartTest = (UINT) wParam;
	m_iTestStarted = (UINT)lParam;
	m_MainProgress.SetPos(0);
	m_dwProgressPos = 0;
	if (iStartTest == PARAM_START_PARITY_TEST)
	{
	m_notEqaulSectors.lFirst = 0;
	m_notEqaulSectors.lInterval = 0;
	m_notEqaulSectors.lCurrent = 0;
	
	// PROGRESS
// ----------------------------------------------------------------------
	m_incProgress = 0;
	if (m_iTestStarted == PARAM_SPEED_TEST)
	{
		m_MainProgress.SetRange(0,PROGRESS_COUNT);
		m_lCountProgress = m_TabDialogs->m_pParityDlg->getStep();
		m_lCountProgress /= PROGRESS_COUNT;
		if (m_lCountProgress == 0 )
			m_lCountProgress = 1;
	}
	else
	{
		m_lTempProgress = verifyMinMax.lTo;
		m_lTempProgress /= DEFAULT_SECTORS_SIZE;
		if ( m_lTempProgress < PROGRESS_COUNT )
			m_MainProgress.SetRange(0,m_lCountProgress);
		else
		{
			m_lCountProgress = m_lTempProgress;
			m_lCountProgress /= PROGRESS_COUNT;
			//++m_lCountProgress;
			m_MainProgress.SetRange(0,PROGRESS_COUNT);
		}
	}
		


// ----------------------------------------------------------------------


	UINT iMaxFreeBuffers = 5000;	

	if ( m_vecSelDrives.size() >= MIN_HDD )
	{

		LONGLONG lminLBA = 0;
		DWORD dwBytesPerSector = 0 ;
		dwBytesPerSector = m_vecSelDrives.at(0).getBytesPerSector();
		lminLBA = m_vecSelDrives.at(0).getSectorCount();
		for (size_t i = 1; i < m_vecSelDrives.size(); ++i)
		{
			if ( dwBytesPerSector < m_vecSelDrives.at(i).getBytesPerSector() )
				dwBytesPerSector = m_vecSelDrives.at(i).getBytesPerSector();
			if (lminLBA > m_vecSelDrives.at(i).getSectorCount())
				lminLBA	= m_vecSelDrives.at(i).getSectorCount();
		}

	// MAX LBA	
	// before need delete
		ClearData();
		hComunicateLock = new HANDLE[2];
		hComunicateLock[0] = CreateEvent(NULL,TRUE,ToUnLock,_T("Run"));
		hComunicateLock[1] = CreateEvent(NULL,TRUE,ToLock,_T("Break"));
		DWORD dwBlockSize = m_TabDialogs->m_pParityDlg->getBlockSize();
		m_Data = new CAllocator(dwBlockSize*dwBytesPerSector,iMaxFreeBuffers);
		pMAP = new CMapAddress();
		pMAP->setBytesPerSector(m_vecSelDrives.at(0).getBytesPerSector());
		//pMAP->setCommand(m_ParityCheckCommand);
		pMAP->SetAllocator(m_Data);
		//pMAP->setWaitThread(m_hWaitAnswer);
		pMAP->setComunicateHandle(hComunicateLock);

		if (lminLBA >= verifyMinMax.lTo)
			verifyMinMax.lTo -= dwBlockSize;
		//pMAP->lMaxLBA = verifyMinMax.lTo;
		pMAP->hParityWindow = m_TabDialogs->m_pParityDlg->GetSafeHwnd();
		pMAP->hMainWindow = ::AfxGetApp()->m_pMainWnd->GetSafeHwnd();

		//m_TabDialogs.m_pParityDlg->setMaxLBA(verifyMinMax.lTo);

		HANDLE hEventStart;
		hEventStart = CreateEvent(NULL,TRUE,FALSE,_T("Event, wait for start"));

		pMAP->setDiskCount(m_vecSelDrives.size());
		pMAP->setToFirstMissmatch(m_TabDialogs->m_pParityDlg->getFirstMissmatch());
		pReadDisk = new CReadDisk[m_vecSelDrives.size()];
		for (size_t i = 0; i < m_vecSelDrives.size(); ++i)
		{
			WirteDiskInfoReport(&pFileWrite,m_vecSelDrives.at(i));
			pReadDisk[i].setDevicePath(m_vecSelDrives.at(i).getDiskPath());
			pReadDisk[i].setDeviceNumber(i);
			pReadDisk[i].setReadRange(verifyMinMax.lFrom,verifyMinMax.lTo);
			if (m_iTestStarted == PARAM_FULL_TEST)
			{
				pMAP->setTest(FULLTEST);
				pMAP->setTestData(verifyMinMax.lTo);
				pReadDisk[i].setStep(0);
				pReadDisk[i].setIndent(0);
				pReadDisk[i].setBlockSize(DEFAULT_SECTORS_SIZE);
			}
			else
			{
				pMAP->setTest(QUICKTEST);
				pMAP->setTestData(m_TabDialogs->m_pParityDlg->getStep());
				pReadDisk[i].setStep(m_TabDialogs->m_pParityDlg->getStep());
				pReadDisk[i].setIndent(m_TabDialogs->m_pParityDlg->getIndentSectors());
				pReadDisk[i].setBlockSize(m_TabDialogs->m_pParityDlg->getBlockSize());
			}
			pReadDisk[i].setBytesPerSector(dwBytesPerSector);
			pReadDisk[i].setStartEvent(hEventStart);
			pReadDisk[i].setComunicateHandle(hComunicateLock);
			pReadDisk[i].setAllocator(m_Data);
			pReadDisk[i].setMapPointer(pMAP);
			pReadDisk[i].StartThreads();
		}
		//::SetEvent(m_hWaitAnswer);
		pMAP->StartThreads();
		Sleep(1000);
		if ( !::SetEvent(hEventStart) )
		{
			TRACE( GetLastErrorMessage( GetLastError() ) );
		}

	}
	else
	{
		AfxMessageBox(_T("HDD must 3 or more"),MB_OK);
		::SendMessageA(m_TabDialogs->m_pParityDlg->GetSafeHwnd(),WM_FINISH_PARITY_CHECK,0,0);
	}
	}



	UpdateData(FALSE);


	return 1;
}

LRESULT CRaidAnalyzerDlg::OnStopButtonPressed(WPARAM wParam, LPARAM lParam)
{
	AbortThreads();
	return 1;
}




void CRaidAnalyzerDlg::SuspendThreads()
{
	if (hComunicateLock != NULL)
	{
	::ResetEvent(hComunicateLock[0]);
	}
}
void CRaidAnalyzerDlg::ResumeThreads()
{
	if (hComunicateLock != NULL)
	{
	::SetEvent(hComunicateLock[0]);
	}
}
void CRaidAnalyzerDlg::AbortThreads()
{
	SuspendThreads();
	if (hComunicateLock != NULL)
	{
	::SetEvent(hComunicateLock[1]);
	}
}

LRESULT CRaidAnalyzerDlg::OnSuspendThreads(WPARAM wParam, LPARAM lParam)
{
	m_enStateProgram = enResume;
	m_GatherByJPG.SetWindowTextW(_T("RESUME"));
	SuspendThreads();
	SuspendThreads();
	return TRUE;

}
LRESULT CRaidAnalyzerDlg::OnResumeThreads(WPARAM wParam, LPARAM lParam)
{
	m_enStateProgram = enPause;
	m_GatherByJPG.SetWindowTextW(_T("PAUSE"));
	ResumeThreads();
	return TRUE;
	
}
LRESULT CRaidAnalyzerDlg::OnAbortThreads(WPARAM wParam, LPARAM lParam)
{
	AbortThreads();
	return TRUE;
}


CSingletonJPGs *CSingletonJPGs::m_Instance = NULL;



void CRaidAnalyzerDlg::OnBnClickedButtonJpg()
{
	IDeviceFactory *pDevFactory = new CDiskFactory();
	IDevice *pDevice = new CDiskDevice();

	delete pDevFactory;
	CDiviceList DevList;
	DevList.AddDevice(pDevice);
	//DevList.RemoveAll();

	size_t iCountHDD = m_vecSelDrives.size();
	if (iCountHDD < 2)
	{
		AfxMessageBox(_T("HDD must 2 or more"),MB_ICONERROR);
		return ;
	}
	HANDLE hEventStart;
	DWORD bytesPerSector = m_vecSelDrives.at(0).getBytesPerSector();
	
	CString strText = _T("");
	CString strPath ( settings::CSettings::getSetting()->getWorkFolder().c_str() );
	switch (m_enStateProgram)
	{
	case enStart:
		ClearData();
		Utility::DeleteDirectory(strPath);
		if (!Utility::CreateStepDirectory(strPath))
		{
			AfxMessageBox(_T("Error Create Directory ()..."),MB_ICONERROR);
			return;
		}
		//system("exlorer.exe C:\\JPG\\");
		strPath = Utility::getDirectoryPath(strPath,0);
		Utility::CreateStepDirectory(strPath);
		m_pSingleton = CSingletonJPGs::GetInstance();
		m_pSingleton->setDirectory(strPath);
		m_pSingleton->setDrives(m_vecSelDrives);
		m_vecSelDrives.at(0).getBytesPerSector();
		m_Data = new CAllocator(DEFAULT_SECTORS_SIZE*bytesPerSector, 2000);

		hEventStart = CreateEvent(NULL,TRUE,FALSE,_T("Event, wait for start"));
		hComunicateLock = new HANDLE[2];
		hComunicateLock[0] = CreateEvent(NULL,TRUE,ToUnLock,_T("Run"));
		hComunicateLock[1] = CreateEvent(NULL,TRUE,ToLock,_T("Break"));
		pMAP = new CMapForJPG();
		pMAP->setBytesPerSector(m_vecSelDrives.at(0).getBytesPerSector());
		pMAP->setSingleton(m_pSingleton);
		pMAP->SetAllocator(m_Data);
		pMAP->setDiskCount(iCountHDD);
		//pMAP->setSelectedDrives(m_vecSelDrives);
		pMAP->setComunicateHandle(hComunicateLock);
		pMAP->hMainWindow = ::AfxGetApp()->m_pMainWnd->GetSafeHwnd();
		pReadDisk = new CReadDisk[iCountHDD];
		for (size_t iDisk = 0; iDisk < iCountHDD; ++iDisk)
		{
			pReadDisk[iDisk].setBlockSize(DEFAULT_SECTORS_SIZE);
			pReadDisk[iDisk].setIndent(0);
			pReadDisk[iDisk].setBytesPerSector(m_vecSelDrives.at(iDisk).getBytesPerSector());
			pReadDisk[iDisk].setDevicePath(m_vecSelDrives.at(iDisk).getDiskPath());
			pReadDisk[iDisk].setDeviceNumber(iDisk);
			pReadDisk[iDisk].setAllocator(m_Data);
			pReadDisk[iDisk].setStartEvent(hEventStart);
			pReadDisk[iDisk].setReadRange(verifyMinMax.lFrom,verifyMinMax.lTo);
			pReadDisk[iDisk].setMapPointer(pMAP);
			pReadDisk[iDisk].setComunicateHandle(hComunicateLock);
			pReadDisk[iDisk].StartThreads();
		}

		pMAP->StartThreads();
		//m_GatherByJPG.EnableWindow(FALSE);
		::SetEvent(hEventStart);

		m_enStateProgram = enPause;
		strText.Format(_T("PAUSE"));
		m_GatherByJPG.SetWindowTextW(strText);
		ShellExecute(this->GetSafeHwnd(),_T("explore"),strPath, NULL, NULL, SW_SHOWNORMAL);
		::PostMessageW(this->GetSafeHwnd(),WM_SHOW_CUTTING_DIGLOG,0,0); // Starting Gather by JPG
		//pCuttingDialog->setStateProgram(m_enStateProgram);
		//pCuttingDialog->ShowWindow(SW_SHOW);
		// End "S T A R T"
		break;
	case enPause:
		m_enStateProgram = enResume;
		strText.Format(_T("RESUME"));
		m_GatherByJPG.SetWindowTextW(strText);
		SuspendThreads();
		// End "P A U S E"
		break;
	case enResume:
		m_enStateProgram = enPause;
		strText.Format(_T("PAUSE"));
		m_GatherByJPG.SetWindowTextW(strText);
		ResumeThreads();
		// End "R E S U M E"
		break;
	}

}
void CRaidAnalyzerDlg::OnBnClickedButtonStop()
{
	// Stop All Threads
	m_enStateProgram = enStart;
	CString strText = _T("");
	strText.Format(_T("START"));
	m_GatherByJPG.SetWindowTextW(strText);
	if (hComunicateLock != NULL)
	{
		::ResetEvent(hComunicateLock[0]);
		::SetEvent(hComunicateLock[1]);
	}
	//pCuttingDialog->ShowWindow(SW_HIDE);
}

#define ID_NO 0
#define ID_ABORD 2
#define ID_YES 1
#define ID_BACK 10

#define ONE_MBYTE 1024*1024







//CString getDiskOrder(vector<UINT> _vecDiskOrder)
//{
//	CString strReport = _T("");
//	CString strDisks;
//	if (_vecDiskOrder.size() > 0 )
//	{
//		strReport = _T("Disk Order : \r\n");
//		for (size_t iDisk = 0; iDisk < _vecDiskOrder.size(); ++iDisk)
//		{
//			if (_vecDiskOrder.at(iDisk) == -1)
//				strDisks = _T("\r\n");
//			else
//			{
//			if ( iDisk == _vecDiskOrder.size() - 1)
//				strDisks.Format(_T("Disk %d "),_vecDiskOrder.at(iDisk));
//			else
//				strDisks.Format(_T("Disk %d + "),_vecDiskOrder.at(iDisk));
//			}
//			strReport += strDisks;
//
//		}
//	}
//	return strReport;
//}


LRESULT CRaidAnalyzerDlg::OnFinishGatherByJPG(WPARAM wParam, LPARAM lParam)
{
	OnBnClickedButtonStop();
	return TRUE;
}




enum enStapName {enContinue = 0, enCuttingFiles = 1, enDetermineNextDisk = 2,enDetermineBlockSize = 3};
LRESULT CRaidAnalyzerDlg::OnShowCuttingDialog(WPARAM wParam, LPARAM lParam)
{
	//UINT iCurrentStep = 0;
	//CCuttingSectorsDlg *pCuttingDialog = new CCuttingSectorsDlg(this,0);
	//pCuttingDialog->Create(CCuttingSectorsDlg::IDD);
	//pCuttingDialog->ShowWindow(SW_SHOW);
	//
	//ShowWindow(SW_HIDE);
	CString defaultString = _T("1000");
	CString strReport = _T("");
	CString strTextOut = _T("");
	CString strStep = _T("");
	CDiskOrder *pDiskOrder = NULL;
	CDiskNumber *pDiskNumber = NULL;
	CNewOrder *pNewOrder = NULL;
	auto setting = settings::CSettings::getSetting();
	CString strWorkingDirectory( setting->getWorkFolder().c_str() );
	INT_PTR iDlgResult = 0;


	CString strCreatePath = _T("");
	// S T E P
	UINT iCurrentStep = 0;
	CDriveReader *pDriveReader = NULL;
	CFileCreater *pFileCreater = NULL;
	CCuttingSectorsDlg *pCuttingDialog = NULL;
	CJGShear *pJpgShear = NULL;
	CMapBlocks *pMapBlock = NULL;
	CDataBlock *pBlockData = NULL;
	CJPGChunk *pJpgChunk = NULL;
	CompositeSTEP *pComposite = NULL;
	BOOL bError = FALSE;
	BOOL bFinishJPG = FALSE;
	CString strError = _T("");
	DWORD dwBlockSize = 0;
	DWORD dwSectorCount = 0;
	LONGLONG lJPGPosition = 0;
	LONGLONG lShearPos = 0;
	LONGLONG lReadPosition = 0;
	BYTE *pDataBuffer = NULL;
	BYTE iDiskNumber = 0;
	NUMBER_POS NumberDiskPosition = {0};
	UINT iFileNumber = 0;
	DWORD dwSize = 0;
	BOOL isNextDisk = FALSE;
	CString strHeader = _T("");

	pDiskOrder = new CDiskOrder();
	pComposite = new CompositeSTEP(0);
	pMapBlock = new CMapBlocks();
	UINT iMinBlockSize = 0;
	DWORD bytesPerSector = SECTOR_SIZE;

	while (true)
	{
		bytesPerSector = SECTOR_SIZE;
		// Creating Directory...
		strCreatePath = Utility::getDirectoryPath(strWorkingDirectory,iCurrentStep);
		bError = Utility::CreateStepDirectory(strCreatePath);
		if (bError == FALSE)
		{
			strError = _T("Error Create Directory..");
			break;
		}

		strStep.Format(_T("\r\nS T E P #%d\r\n"),iCurrentStep);
		m_ReportLog->AddText(strStep);

		switch (iCurrentStep)
		{
		/*------------------******************------------------*/
			//Select File 1Mb to Determine "Continue work" -->>...
		/*------------------******************------------------*/
		case enContinue:
			/*SuspendThreads();*/
			//pMapBlock = new CMapBlocks();
			//pDiskOrder = new CDiskOrder();
			//pComposite = new CompositeSTEP(0);
			pCuttingDialog = new CCuttingSectorsDlg(this,iCurrentStep);
			pCuttingDialog->setHeader(_T("[Определения файла]"));
			strTextOut = _T("Введите номер файла для начала работы.");
			pCuttingDialog->setTextData(strTextOut);
			pCuttingDialog->setStateProgram(m_enStateProgram);
			iDlgResult = pCuttingDialog->DoModal();
			//pCuttingDialog->Create(CCuttingSectorsDlg::IDD);
			//pCuttingDialog->ShowWindow(SW_SHOW);
			if (iDlgResult == ID_YES)
			{
			m_enStateProgram = pCuttingDialog->getStatProgram();
			NumberDiskPosition = pCuttingDialog->getDiskNumberPos();
			lJPGPosition = NumberDiskPosition.m_lLBAPosition;
			iDiskNumber = NumberDiskPosition.m_iDiskNumber;

			pDiskNumber = new CDiskNumber();
			pDiskNumber->setDiskDrive(m_vecSelDrives.at(iDiskNumber));
			pDiskOrder->Add(pDiskNumber);
			//// Log ...
			//m_ReportLog->AddText(_T("Program found start JPG file\r\n"));
			//strReport.Format(_T(" Hard Disk # %d, Sector # %I64d\r\n"),m_vecSelDrives.at(pDiskInfoData->m_iDiskNumber).getDiskNumber(),lJPGPosition);
			//m_ReportLog->AddText(strReport);
			pDiskOrder->MakeDiskOrder();
			strReport = pDiskOrder->GetDiskOrder();
			m_ReportLog->AddText(strReport);
			//// Dialog Text
			//strTextOut = _T("Found the signature JPG-file\r\n");
			//strTextOut += _T("\r\n\CONTINUE WORK ?");
			//// Creating Dialog...
			//pCuttingDialog = new CCuttingSectorsDlg(this,iCurrentStep);
			//pCuttingDialog->setTextData(strTextOut);
			//iDlgResult = pCuttingDialog->DoModal();
			//delete pCuttingDialog;
			//pCuttingDialog = NULL;
			}
			delete pCuttingDialog;
			pCuttingDialog = NULL;

		// End ContinueBlock
			break;

		/*------------------******************------------------*/
			//Creating 1000 files. Determine of Shear -->>...
		/*------------------******************------------------*/
		case enCuttingFiles:
			bytesPerSector = m_vecSelDrives.at(iDiskNumber).getBytesPerSector();
			dwSize = setting->getFileCount() * bytesPerSector;

			m_ReportLog->AddText(_T("Идет создание файлов для определение среза...\r\n"));
			pDriveReader = new CDriveReader(m_vecSelDrives.at(iDiskNumber),lJPGPosition,dwSize);
			bError = pDriveReader->Execute();
			if (bError == FALSE)
			{
				strError = _T("Error Read Drive...");
				break;
			}
			pDataBuffer = pDriveReader->GetData();
			pFileCreater = new CFileCreater(strCreatePath);
			for (UINT i = 1; i <= setting->getFileCount(); ++i)
			{
				pFileCreater->setData(pDataBuffer);
				pFileCreater->setFileNumber(i);
				pFileCreater->setSize(i*bytesPerSector);
				bError = pFileCreater->Execute();
				if (bError == FALSE)
				{
					strError = _T("Error Create Files...");
					break;
				}
			}
			if (bError == FALSE)
				break;
			strTextOut = strCreatePath;
			strTextOut += _T("\\0001.jpg");
			ShellExecute(this->GetSafeHwnd(),_T("open"),strTextOut, NULL, NULL, SW_SHOWNORMAL);

			delete pDriveReader;
			pDriveReader = NULL;
			delete pFileCreater;
			pFileCreater = NULL;
			strTextOut.Format(L"Создано %d файлов\r\n // Введите номер файла для определения \'конца блока\'. \r\n",setting->getFileCount());
			

			pCuttingDialog = new CCuttingSectorsDlg(this,iCurrentStep);
			pCuttingDialog->setHeader(_T("[определения \'конца блока\']"));
			pCuttingDialog->setTextData(strTextOut);
			pCuttingDialog->setMinMax(1,setting->getFileCount());
			pCuttingDialog->setStateProgram(m_enStateProgram);
			iDlgResult = pCuttingDialog->DoModal();
			m_enStateProgram = pCuttingDialog->getStatProgram();
			iFileNumber = pCuttingDialog->getNumber();
			delete pCuttingDialog;
			pCuttingDialog = NULL;
			if (iDlgResult == ID_YES)
			{
				lShearPos = lJPGPosition;
				dwBlockSize = iFileNumber * bytesPerSector;
				iMinBlockSize = iFileNumber;
				lShearPos += iFileNumber;
				strReport.Format(_T("Граница блока по смешению = %I64d (секторов) диск № %d\r\n"), lShearPos , m_vecSelDrives.at(iDiskNumber).getDiskNumber() );
				AfxMessageBox( strReport, MB_OK );	
				m_ReportLog->AddText(strReport);
				pJpgShear = new CJGShear();
				pJpgShear->setDataSize(dwBlockSize); // set Data Buffer size
				pJpgShear->setDiskNumber( (BYTE)m_vecSelDrives.at(iDiskNumber).getDiskNumber() ); // Set Disk Number
				pJpgShear->setJPGStartPostion(lJPGPosition);
				pJpgShear->setDevice(m_vecSelDrives.at(iDiskNumber));
				pJpgShear->Execute();
				pComposite->AddSTEP(pJpgShear);				
			}
			dwBlockSize = 0;
		// End Cutting Files
			break;
		/*------------------******************------------------*/
			//Determine "Block Size", Disk Order -->>...
		/*------------------******************------------------*/
		default:

			pComposite->Execute();
			pFileCreater = new CFileCreater(strCreatePath);
			pFileCreater->setData(pComposite->GetData());
			pFileCreater->setSize(pComposite->GetSize());
			pFileCreater->setFileNumber(0);
			pFileCreater->AddFileName(_T("Original"));
			bError = pFileCreater->Execute();
			if (bError == FALSE)
			{
				strError = _T("Error Create Files...");
				break;
			}
			strTextOut = pFileCreater->GetFilePath();
			delete pFileCreater;
			pFileCreater = NULL;
		//	strTextOut.Insert(0,_T("C:\\WINDOWS\\rundll32.exe "));
			ShellExecute(this->GetSafeHwnd(),_T("open"),strTextOut, NULL, NULL, SW_SHOWNORMAL);
		//	system((char*)strTextOut.GetBuffer());
			pMapBlock->ClearMap();
			bFinishJPG = pComposite->isFinishJPG();
			if (bFinishJPG)
				break;
			pMapBlock->setBlockSize(dwBlockSize);
			pMapBlock->setPosition(lShearPos);
			pMapBlock->setVecDrives(m_vecSelDrives);
			pMapBlock->setDirectory(strCreatePath);
			pMapBlock->setBaseData(pComposite->GetData(),pComposite->GetSize());
			pMapBlock->DeterminateBlock(iMinBlockSize);	//???????

			switch (iCurrentStep)
			{
			case enDetermineBlockSize:
				strTextOut = _T("Размер блока : неизвестно\r\n Определение размера блока\r\n");
				strHeader = _T("[Определение размера блока]");
				break;
			case enDetermineNextDisk:
				strTextOut = _T("Поиск устройств в который есть продолжение jpg \r\n");
				strReport.Format(_T("Граница блока по смешению = %I64d (секторов) диск № %d\r\n"), lShearPos , m_vecSelDrives.at(iDiskNumber).getDiskNumber() );
				//AfxMessageBox( strReport, MB_OK );		
				strTextOut.Append( strReport );
				strHeader = _T("[Поиск следущих устройств]");
				break;
			default:

				strTextOut.Format(_T("Определение следущего устройства\r\nРазмер блока : %d(байт), %d(секторов)\r\n"),dwBlockSize,dwSectorCount);
				LONGLONG lShowShear = lJPGPosition;
				lShowShear += iFileNumber;

				strHeader = _T("[Define the Next Device]");
			}

			//strTextOut += _T("Look in the folder ");
			//strTextOut += strStep;
			//strTextOut += _T("NUMBER FILE");
			pDiskOrder->MakeDiskOrder();
			strTextOut += pDiskOrder->GetDiskOrder();
			pCuttingDialog = new CCuttingSectorsDlg(this,iCurrentStep);
			pCuttingDialog->setHeader(strHeader);
			pCuttingDialog->setTextData(strTextOut);
			pCuttingDialog->setMinMax(1,pMapBlock->getCount());
			pCuttingDialog->setStateProgram(m_enStateProgram);
			iDlgResult = pCuttingDialog->DoModal();
			m_enStateProgram = pCuttingDialog->getStatProgram();
			iFileNumber = pCuttingDialog->getNumber();
			//--iFileNumber; // decrement Number (from (1 - ...))
			delete pCuttingDialog;
			pCuttingDialog = NULL;
			if (iDlgResult == ID_YES)
			{
				pBlockData = pMapBlock->getData(iFileNumber);
				if (pBlockData == NULL)
				{
					bError = FALSE;
					break;
				}

				if (iCurrentStep == enDetermineNextDisk)
				{
					isNextDisk = TRUE;
				for (size_t iDisk = 0; iDisk < m_vecSelDrives.size(); ++iDisk)
				{
					if (m_vecSelDrives.at(iDisk).getDiskNumber() == pBlockData->getDiskNumber())
					{
						pMapBlock->setNextDisk(iDisk);
						break;
					}
				}		
				pJpgChunk = new CJPGChunk();
				pJpgChunk->setBackPos(lShearPos);
				pComposite->AddSTEP(pJpgChunk);
				}
				else
				{
				// check pBlockData for NULL ???????????
				dwBlockSize = pBlockData->getBlockSize();
				dwSectorCount = dwBlockSize / m_vecSelDrives.at(0).getBytesPerSector();
				if (pBlockData->getPosUpDown( ) == PosDown )
				{
					pNewOrder = new CNewOrder();
					pDiskOrder->Add(pNewOrder);				
				}

				pJpgChunk = new CJPGChunk();
				pJpgChunk->setDiskNumber(pBlockData->getDiskNumber());
				for (size_t iDisk = 0; iDisk < m_vecSelDrives.size(); ++iDisk)
				{
					if (m_vecSelDrives.at(iDisk).getDiskNumber() == pBlockData->getDiskNumber())
					{
						pJpgChunk->setDevice(m_vecSelDrives.at(iDisk));
						pDiskNumber = new CDiskNumber();
						pDiskNumber->setDiskDrive(m_vecSelDrives.at(iDisk));
						pDiskOrder->Add(pDiskNumber);
						break;
					}
				}
				lReadPosition = lShearPos;
				pJpgChunk->setBackPos(lShearPos);
				if (pBlockData->getPosUpDown() == PosUP)
					lReadPosition -= dwSectorCount;

				pJpgChunk->setShearPosition(lReadPosition);
				pJpgChunk->setDataSize(dwBlockSize);
				pJpgChunk->Execute();
				pComposite->AddSTEP(pJpgChunk);
				strReport.Format(_T("Размер блока : %d(байт), %d(секторов)\r\n"),dwBlockSize,dwSectorCount);
				m_ReportLog->AddText(strReport);
				pDiskOrder->MakeDiskOrder();
				strReport = pDiskOrder->GetDiskOrder();
				m_ReportLog->AddText(strReport);
				//pDiskOrder->MakeDiskOrder(_T(" # "));
				//m_ReportLog->AddText(pDiskOrder->GetDiskOrder());

				// increment Position
				if (pBlockData->getPosUpDown( ) == PosDown )
					lShearPos += dwSectorCount;
				
			}
			}
			if (iDlgResult == ID_BACK)
			{
				lShearPos = pComposite->GetPositiom();
				pComposite->RemoveSTEP();
				pDiskOrder->Delete();
				--iCurrentStep;
				if (iCurrentStep == enDetermineBlockSize)
					dwBlockSize = 0;
				if (iCurrentStep == enDetermineNextDisk)
					pMapBlock->setNextDisk(-1);
				continue;
			}
			
			// End Default 
		}
		// if error Quit
		if (bError == FALSE)
		{
			AfxMessageBox(strError,MB_ICONERROR);
			break;
		}
		if (bFinishJPG)
		{
			strReport.Format(_T("Найден конец Jpg-файла...\r\n"));
			m_ReportLog->AddText(strReport);
			if (AfxMessageBox(_T("Найден конец Jpg-файла...\r\n Продолжить работу с другими файлами?"),MB_YESNO) == IDNO)
				iDlgResult = ID_ABORD;
			else
				iDlgResult = ID_NO;
			bFinishJPG = FALSE;
		}


	if (iDlgResult == ID_ABORD)
		break;

		// increment STEP;
		++iCurrentStep;
		if ( iDlgResult == ID_NO)
		{
			delete pComposite;
			pComposite = NULL;
			delete pMapBlock;
			pMapBlock = NULL;
			//delete pDiskOrder;
			//pDiskOrder = NULL;
			pDiskOrder->Clear();
			dwBlockSize = 0;
			dwSectorCount = 0;
			iCurrentStep = 0;
		}
	}
	// Clear...
	//OnBnClickedButtonClearLog();
	//if (dwBlockSize > 0)
	//{
	//	strReport.Format(_T("\r\n\Block Size : %d(bytes), %d(sectors)\r\n"),dwBlockSize,dwSectorCount);
	//	m_ReportLog->AddText(strReport);
	//	pDiskOrder->MakeDiskOrder();
	//	strReport = pDiskOrder->GetDiskOrder();
	//	m_ReportLog->AddText(strReport);
	//}

	if (bFinishJPG)
	{

	}

	switch (iDlgResult)
	{
	case ID_ABORD:
		pResultCutting->m_ButtonResult = iResABORT;
		break;
	case ID_NO:
		pResultCutting->m_ButtonResult = iResNEXT;
		break;
	default:
		pResultCutting->m_ButtonResult = iResNEXT;
	}

	if (pComposite != NULL)
	{
		delete pComposite;
		pComposite = NULL;
	}
	if (pMapBlock != NULL)
	{
		//pMapBlock->ClearMap();
		delete pMapBlock;
		pMapBlock = NULL;
	}
	if (pDiskOrder != NULL)
	{
		delete pDiskOrder;
		pDiskOrder = NULL;
	}

	ShowWindow(SW_SHOW);
	OnBnClickedButtonStop();
	
	return TRUE;


}


LRESULT CRaidAnalyzerDlg::OnFinishCheck(WPARAM wParam, LPARAM lParam)
{
	m_ReportLog->AddEvent(cmd_FINISH);
	CString strTimeReport = getTimeCurrent();
	pFileWrite.WriteString(_T("\r\nFinished...\r\n\r\n"));
	pFileWrite.WriteString(strTimeReport);
	m_ReportLog->AddText(strTimeReport);
	::AfxMessageBox(_T("Finish"),MB_OK);
	m_MainProgress.SetPos(0);
	pFileWrite.Close();
	return TRUE;
}

LRESULT CRaidAnalyzerDlg::OnSetFirstMissmatch(WPARAM wParam, LPARAM lParam)
{
	if (pMAP != NULL)
		pMAP->setToFirstMissmatch((BOOL)wParam);
	return TRUE;
}

LRESULT CRaidAnalyzerDlg::OnSetPause(WPARAM wParam, LPARAM lParam)
{
	//AbortThreads();
	return TRUE;
}

LRESULT CRaidAnalyzerDlg::OnParityCheckProgress(WPARAM wParam, LPARAM lParam)
{
	++m_incProgress;
	m_MainProgress.SetPos(m_incProgress);
	//if (m_iTestStarted == PARAM_FULL_TEST)
	//{
	//	if (m_lTempProgress < PROGRESS_COUNT)
	//	{
	//		m_MainProgress.SetPos(m_incProgress);
	//	}
	//	else
	//	{
	//		if (m_incProgress >= m_lCountProgress)
	//		{
	//			++m_dwProgressPos;
	//			m_MainProgress.SetPos(m_dwProgressPos);
	//			m_incProgress = 0;
	//		}
	//	}
	//}
	//else
	//if (m_incProgress >= m_lCountProgress)
	//{
	//	++m_dwProgressPos;
	//	m_MainProgress.SetPos(m_dwProgressPos);
	//	m_incProgress = 0;
	//}

	return TRUE;
}

LRESULT CRaidAnalyzerDlg::OnShowMissmatchDlg(WPARAM wParam, LPARAM lParam)
{
	SuspendThreads();
	CResumeDlg MissmatchDlg;
	INT_PTR iResult = -1;
	LONGLONG *pLBA = NULL;
	pLBA = (LONGLONG * )lParam;
	MissmatchDlg.setLBAPosition(pLBA);
	iResult = MissmatchDlg.DoModal();
	m_TabDialogs->m_pParityDlg->UpdateChecked(MissmatchDlg.CheckResult());

	switch (iResult)
	{
	case IDOK:
		ResumeThreads(); // Continue ...
		break;
	case IDCANCEL:
		AbortThreads();	// Exit ...
		break;
	default:
		TRACE("Show Missmatch Dialog return unknown value");
	}

	return TRUE;
}

void CRaidAnalyzerDlg::OnNMDblclkListDrives(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int iItemCount = m_pListDrives->GetItemCount();
	UINT uState;

	bool bSelect = false;
	bool bPresent = false;

	CString str;
	for (int iItem = 0; iItem < iItemCount; ++iItem)
	{
		uState = m_pListDrives->GetItemState(iItem,LVNI_SELECTED);
		if (uState & LVIS_SELECTED)
		{
			bSelect = true;
			if ((bPresent = AddSelectedDrive(iItem,m_vecDrives,m_vecSelDrives)))
			{
				str.Format(_T("Disk # %i : %s"),m_vecDrives.at(iItem).getDiskNumber(),m_vecDrives.at(iItem).getSerialNumber());
				m_pListSelected->AddString(str);
			}

		}
	}

	if (!m_vecSelDrives.empty())
	{
		if (m_vecSelDrives.size() == 1)
		{
			CString strEditText;
			m_MinMaxLBA = m_vecSelDrives.at(0).getSectorCount();
			strEditText.Format(_T("%I64d"),m_MinMaxLBA);
			m_pEditMaxLBA->SetWindowTextW(strEditText);
		}
		else
		for ( size_t i = 0; i < m_vecSelDrives.size(); ++i)
		{
			if ( m_MinMaxLBA > m_vecSelDrives.at(i).getSectorCount() )
			{
				CString strEditText;
				m_MinMaxLBA = m_vecSelDrives.at(i).getSectorCount();
				strEditText.Format(_T("%I64d"),m_MinMaxLBA);
				m_pEditMaxLBA->SetWindowTextW(strEditText);
			}
		}

	}

	if (!bPresent)
		if (bSelect)
			AfxMessageBox(_T("Drives is already present!!!"),MB_OK);

	*pResult = 0;
}

void CRaidAnalyzerDlg::OnBnClickedClearButton()
{
	if (m_vecSelDrives.size() > 0)
	{
		m_vecSelDrives.clear();
		m_pListSelected->ResetContent();
	}
}

void CRaidAnalyzerDlg::OnEnChangeMinLba()
{
	CString strText;
	m_pEditMinLBA->GetWindowTextW(strText);
	verifyMinMax.lFrom = _ttoi64(strText);
	if (verifyMinMax.lFrom < 0 )
	{
		verifyMinMax.lFrom = 0;
		AfxMessageBox(_T("Value can't accept less 0"),MB_OK);
	}
	else
	{
		if (verifyMinMax.lTo < verifyMinMax.lFrom)
		if (m_vecSelDrives.size() > 0)
		{
			verifyMinMax.lFrom = 0;
			m_pEditMinLBA->SetWindowTextW(_T("0"));
			AfxMessageBox(_T("MaxLBA can't less then MinLBA (MaxLBA > MinLBA)"),MB_ICONHAND);
		
		}
	}

}

void CRaidAnalyzerDlg::OnEnChangeMaxLba()
{

	CString strText;
	m_pEditMaxLBA->GetWindowTextW(strText);
	verifyMinMax.lTo = _ttoi64(strText);
	BOOL bAllGood = TRUE;
	if (verifyMinMax.lTo < 0 )
	{
			verifyMinMax.lTo = 0;
			AfxMessageBox(_T("Value can't accept less 0"),MB_OK);
			bAllGood = FALSE;
	}
	else
		if (verifyMinMax.lTo < verifyMinMax.lFrom)
		{
			verifyMinMax.lFrom = 0;
			m_pEditMinLBA->SetWindowTextW(_T("0"));
			AfxMessageBox(_T("MaxLBA can't less then MinLBA (MaxLBA > MinLBA)"),MB_ICONHAND);
			bAllGood = FALSE;
		}
	//if (bAllGood == TRUE)
	//	::SendMessageA(m_TabDialogs.m_pParityDlg->GetSafeHwnd(),WM_UPDATE_MAX_LBA,0,verifyMinMax.lTo);


}


LRESULT CRaidAnalyzerDlg::OnUpdateReportFirst(WPARAM wParam, LPARAM lParam)
{
	CString strFormat;
	NotEqualSectors *m_notEqaulSectors = (NotEqualSectors*)lParam;

	strFormat.Format(_T("\r\nSectors at %I64d"),m_notEqaulSectors->lFirst);
	m_pEditReport->SetSel(m_pEditReport->GetWindowTextLengthW() - 1,m_pEditReport->GetWindowTextLengthW() - 1);
	m_pEditReport->ReplaceSel(strFormat);
	pFileWrite.WriteString(strFormat);
	//m_notEqaulSectors.lFirst = (LONGLONG)lParam;

	//if (m_notEqaulSectors.lInterval == 0)
	//{
	//	m_lFirstPos = m_notEqaulSectors.lFirst;
	//	m_notEqaulSectors.lInterval++;
	//}
	//else
	//	if ( m_notEqaulSectors.lFirst  == (m_notEqaulSectors.lLast + 1))
	//	{
	//		m_notEqaulSectors.lInterval++;
	//	}
	//	else
	//	{
	//		if (m_notEqaulSectors.lInterval != 1)
	//		{
	//			strFormat.Format(_T("XOR not OK (%I64d-%I64d)"),m_lFirstPos,m_notEqaulSectors.lLast);

	//			m_pEditReport->ReplaceSel(strFormat);
	//			strFormat.Format(_T("(%I64d Sectors)\r\n"),m_notEqaulSectors.lInterval);
	//			m_pEditReport->ReplaceSel(strFormat);
	//			m_notEqaulSectors.lInterval = 1;


	//		}
	//			m_lFirstPos = m_notEqaulSectors.lFirst;
	//	}
	//	m_notEqaulSectors.lLast = m_notEqaulSectors.lFirst;

	//if (PARAM_SHOW_LAST_MISSMATCH == wParam)
	//{
	//	strFormat.Format(_T("XOR not OK %I64d\r\n"),m_notEqaulSectors.lFirst);
	//	m_pEditReport->ReplaceSel(strFormat);
	//}

	return TRUE;
}
LRESULT CRaidAnalyzerDlg::OnUpdateReportLast(WPARAM wParam, LPARAM lParam)
{
	CString strFormat;
	NotEqualSectors *m_notEqaulSectors = (NotEqualSectors*)lParam;
	if (m_notEqaulSectors->lInterval == 1)
		strFormat.Format(_T(" (%I64d sectors) are not XORed"),m_notEqaulSectors->lInterval);
	else
		strFormat.Format(_T("-%I64d (%I64d sectors) are not XORed"),m_notEqaulSectors->lLast,m_notEqaulSectors->lInterval);
	m_pEditReport->SetSel( m_pEditReport->GetWindowTextLengthW() - 1 , m_pEditReport->GetWindowTextLengthW() - 1 );
	pFileWrite.WriteString(strFormat);
	m_pEditReport->ReplaceSel(strFormat);
	return TRUE;
}


void CRaidAnalyzerDlg::OnBnClickedRemoveSelected()
{
	m_pListSelected->SetFocus();
	int iCountSelectedDrives = m_pListSelected->GetCount();
	UINT uState = 0;
	if ( iCountSelectedDrives > 0)
	{
		if (iCountSelectedDrives == 1)
		{
			m_vecSelDrives.clear();
			m_pListSelected->ResetContent();
		}
		else
		{
			for (int iSelPos = 0; iSelPos < iCountSelectedDrives; ++iSelPos)
			{
				uState = m_pListSelected->GetSel(iSelPos);
				if (uState > 0)
				{
					// delete From ListBox and Vector
					vector<CDiskDrive>::iterator it;
					m_vecSelDrives.erase(m_vecSelDrives.begin()+iSelPos,m_vecSelDrives.begin()+iSelPos+1);
					m_pListSelected->DeleteString(iSelPos);
					break;
				}
				
			}
		}
		
	}
}

void CRaidAnalyzerDlg::OnLbnSelchangeSelectedList()
{
	int iSelectedCount = m_pListSelected->GetCount();
	if (iSelectedCount > 0 )
	{
		bool isFind = false;
		int iItemPos = 0;
		for ( iItemPos = 0; iItemPos < iSelectedCount; ++iItemPos)
		{
			if (m_pListSelected->GetSel(iItemPos) > 0)
			{
				isFind = true;
				break;
			}
		}
		if (isFind)
		{
			int iCoutDrives = m_pListDrives->GetItemCount();
			// Clear all selected drives
			for (int i = 0 ; i < iCoutDrives; ++i)
				m_pListDrives->SetItemState(i,LVIS_DROPHILITED,LVIS_SELECTED);


			UINT iDiskNumber = m_vecSelDrives.at(iItemPos).getDiskNumber();
			m_pListDrives->SetFocus();
			m_pListDrives->SetItemState(iDiskNumber,LVIS_SELECTED,LVIS_SELECTED);
			
		}
	}
}

static int iFileNumber = 100;

void CRaidAnalyzerDlg::OnBnClickedAddButtonFile()
{
	CDiskDrive cFileDrive;
	//CDrives FileDevice();
	CFileDialog fileDlg(TRUE);
	fileDlg.DoModal();
	cFileDrive.setDiskPath(fileDlg.GetPathName());
	HANDLE hFile = CreateFile(cFileDrive.getDiskPath(),
							  GENERIC_READ , FILE_SHARE_READ,
							  NULL,
							  OPEN_EXISTING,
							  0,NULL);
	LARGE_INTEGER lFileSize;
	lFileSize.QuadPart = 0;
	if (hFile != INVALID_HANDLE_VALUE)
	{
		::GetFileSizeEx(hFile,&lFileSize);
	}

	lFileSize.QuadPart /= 512;

	CString strMaxLBA = _T("");
	strMaxLBA.Format(_T("%I64d"),lFileSize.QuadPart); 

	this->m_pEditMaxLBA->SetWindowTextW(strMaxLBA);
	CloseHandle(hFile);
	cFileDrive.setBytesPerSector(512);
	cFileDrive.setDiskNumber(iFileNumber);
	m_vecSelDrives.push_back(cFileDrive);
	CString strText;
	strText.Format(_T("%d : %s"),iFileNumber,cFileDrive.getDiskPath());
	m_pListSelected->AddString(strText);
	iFileNumber++;

}


void CRaidAnalyzerDlg::OnBnClickedButtonClearLog()
{
	m_pEditReport->SetReadOnly(FALSE);
	m_pEditReport->SetSel(0,-1);
	m_pEditReport->Clear();
	UpdateData(FALSE);
	m_pEditReport->SetReadOnly(TRUE);
}




/*
	CStdioFile TextFile(_T("E:\\WORK\\Fragments\\Files.txt"),CFile::modeRead);
	CString strRead;
	CString strLBA;
	CString strBytesSize;
	bool bFind = false;
	int iPos = 0;

	if (m_vecSelDrives.size() > 1)
	{
		AfxMessageBox(_T("Only 1 HDD!!!"),MB_OK);
		
	}
	else
	{
		CString strDevPath = m_vecSelDrives.at(0).getDiskPath();
		DWORD dwError = GetLastError();

		const CString csFilePath = _T("E:\\WORK\\Fragments\\File.bin");
		UINT iNumFile = 1;
		while (TextFile.ReadString(strRead) != FALSE)
		{
			TRACE(strRead);
			TRACE("\r\n");
		for (int i = 0; i < strRead.GetLength(); ++i)
			if (strRead.GetAt(i) == _T('-') )
			{
				iPos = i;
				bFind = true;
				break;
			}
			if (bFind == false)
				TRACE("Error not find symbol '-'\r\n");
		strLBA = strRead.Left(iPos);
		strBytesSize= strRead.Right(strRead.GetLength() - iPos - 1);

		LONGLONG lLBAPos = _ttoi64(strLBA);
		LONGLONG lBytesSize = _ttoi64(strBytesSize);

		pReadDisk = new CReadDisk();
		CString strFilePath;
		strFilePath.Format(_T("%s"),csFilePath);
		CString strFormat;
		strFormat.Format(_T("%.5i"),iNumFile);
		strFilePath.Insert(strFilePath.GetLength()-4,strFormat);
		pReadDisk->ReadDataFile(strDevPath,lLBAPos,lBytesSize,strFilePath);
		++iNumFile;
	
	}
	}
	TextFile.Close();
	TRACE("Finish");

	*/











void CRaidAnalyzerDlg::OnBnClickedButton4()
{
	CPreferenceDlg * pDlg = new CPreferenceDlg( this );

	auto nResult = pDlg->DoModal();

	delete pDlg;
}
