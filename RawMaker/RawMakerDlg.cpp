
// RawMakerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RawMaker.h"
#include "RawMakerDlg.h"
#include "afxdialogex.h"
#include "RawMakerSaver.h"
//#include "RawMode.h"
#include "AbstractFactory.h"
#include "Buffer.h"
#include "Queue.h"
#include "Concurrent.h"
#include "Declaration.h"
#include "Converter.h"
#include "Devices.h"
#include "Buffer.h"
#include "Reader.h"
#include "Writer.h"
#include "System.h"
#include "Updater.h"
#include "Declaration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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


// CRawMakerDlg dialog




CRawMakerDlg::CRawMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRawMakerDlg::IDD, pParent)
	, m_TransferSize ( 0 )
	, ReaderConsistent_(NULL)
	, TaskManager_(NULL)
	, nDeviceID ( enNoDevice )
	//, m_pEditHeader(NULL)
	//, m_pEditFooter(NULL)
	//, m_pEditMaxSize(NULL)
	//, m_pEditAddFooter(NULL)
	//, m_pEditHeaderOffset(NULL)
	//, m_pEditMinSize(NULL)
	//, m_pEditExtension(NULL)
	, nRadioFile(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	/*DefaultMsg::FinishMessage = (DWORD) ( WM_USER + 100);*/


}
CRawMakerDlg::~CRawMakerDlg()
{

	Declaration::LanguageDll::GetInstance()->Remove();

}

void CRawMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDIT_INPUT_FILE, m_EditFileName);
	DDX_Control(pDX, IDC_MFCEDIT_OUTPUT_DIR, m_EditOutDir);
	DDX_Control(pDX, IDC_EDIT_START_OFFSET, m_EditHeaderOffset);
	DDX_Control(pDX, IDC_EDIT_HEADER, m_EditHeader);
	DDX_Control(pDX, IDC_EDIT_FOOTER, m_EditFooter);
	DDX_Control(pDX, IDC_EDIT_ADD_FOOTER, m_EditAddFooter);
	DDX_Control(pDX, IDC_EDIT_MIN_SIZE, m_EditMinSize);
	DDX_Control(pDX, IDC_EDIT_MAX_SIZE, m_EditMaxSize);
	DDX_Control(pDX, IDC_EDIT_EXTENSION, m_EditExtension);
	DDX_Control(pDX, IDC_CURRENT_LBA, m_LBAText);
	DDX_Control(pDX, IDC_CURRENT_SPEED, m_SpeedText);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_PROGRESS_NUMBER, m_ProgressNumber);
	DDX_Control(pDX, IDC_BUTTON_START, m_ButtonStart);
	DDX_Control(pDX, IDC_BUTTON_STOP, ButtonStop_);
	DDX_Radio(pDX, IDC_RADIO_FILE, nRadioFile); 
	DDX_Control(pDX, IDC_EDIT_OFFSET, m_Offset);
}

BEGIN_MESSAGE_MAP(CRawMakerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_MESSAGE(WM_UPDATE_LBA , OnUpdateLBA)
	ON_MESSAGE(FoundCounts,OnFoundCounts)
	ON_MESSAGE(DefaultMsg::UpdateSpeed, OnUpdateSpeed)
	ON_MESSAGE(DefaultMsg::UpdateProgress, OnUpdateProgress)
	ON_MESSAGE(DefaultMsg::FinishMessage, OnFinish)
	ON_MESSAGE(DefaultMsg::SendError,OnError)
	ON_BN_CLICKED(IDC_BUTTON_START, &CRawMakerDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CRawMakerDlg::OnBnClickedButtonStop)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_FILE, &CRawMakerDlg::OnBnClickedRadioFile)
	ON_BN_CLICKED(IDC_RADIO_DISK, &CRawMakerDlg::OnBnClickedRadioDisk)
END_MESSAGE_MAP()


// CRawMakerDlg message handlers

void CRawMakerDlg::ClearData()
{
	CCommunicateLock * pCompunicate = CCommunicateLock::GetInstance();
	pCompunicate->Abort();

	if (ReaderConsistent_ != NULL)
	{
		ReaderConsistent_->Join();
		delete ReaderConsistent_;
		ReaderConsistent_ = NULL;
	}
	if (TaskManager_ != NULL)
	{
		TaskManager_->Join();
		delete TaskManager_;
		TaskManager_ = NULL;
	}
	pCompunicate->Release();
	if ( CMFCVisualManager::GetInstance() != NULL )
		delete CMFCVisualManager::GetInstance();
}
BOOL CRawMakerDlg::OnInitDialog()
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

	//Declaration::SetLanguage(Declaration::RussianLanguage);

	//m_pEditHeaderOffset = static_cast<CEdit*>
	//	( GetDlgItem( IDC_EDIT_START_OFFSET ) );

	//m_pEditHeader = static_cast<CEdit*>
	//	( GetDlgItem ( IDC_EDIT_HEADER ) );

	//m_pEditFooter = static_cast<CEdit*>
	//	( GetDlgItem ( IDC_EDIT_FOOTER ) );

	//m_pEditAddFooter = static_cast<CEdit*>
	//	( GetDlgItem ( IDC_EDIT_ADD_FOOTER ) );

	//m_pEditMinSize = static_cast<CEdit*>
	//	( GetDlgItem( IDC_EDIT_MIN_SIZE ) );

	//m_pEditMaxSize = static_cast<CEdit*>
	//	( GetDlgItem ( IDC_EDIT_MAX_SIZE ) );

	//m_pEditExtension = static_cast<CEdit*>
	//	( GetDlgItem ( IDC_EDIT_EXTENSION ) );

	m_EditExtension.SetLimitText(4);
	m_Progress.SetRange(0,1000);

	OnBnClickedRadioFile();
	LoadData();

	m_Offset.SetWindowText(L"0");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRawMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRawMakerDlg::OnPaint()
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
HCURSOR CRawMakerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CRawMakerDlg::LoadData()
{
	CRawMakerSaver serialize_;
	serialize_.Init();
	m_sCurrentFolder = System::GetCurrentDir();
	serialize_.ReadFromFile(DefaultsValues::ProgramINI);

	m_EditFileName.SetWindowTextW(serialize_.GetInputFile());
	m_EditOutDir.SetWindowTextW(serialize_.GetOutputFolder());
	m_EditHeaderOffset.SetWindowTextW(serialize_.GetHeaderOffset());
	m_EditHeader.SetWindowTextW(serialize_.GetHeaderSignature());
	m_EditFooter.SetWindowTextW(serialize_.GetFooterSignature());
	m_EditAddFooter.SetWindowTextW(serialize_.GetFooterOffset());
	m_EditMinSize.SetWindowTextW(serialize_.GetMinSize());
	m_EditMaxSize.SetWindowTextW(serialize_.GetMaxSize());
	m_EditExtension.SetWindowTextW(serialize_.GetExtension());
	m_Offset.SetWindowTextW( serialize_.GetOffset() );

	return FALSE;
}
void CRawMakerDlg::OnOK()
{
	if ( ::AfxMessageBox(L"Are you sure you want to Exit?", MB_YESNO) == IDYES )
	{
		OnBnClickedButtonStop();
		ClearData();
		CRawMakerSaver serialize_;
		serialize_.Init();
		SetSerialization(&serialize_);
		CString FileName = System::PrepereDirectory(m_sCurrentFolder) + DefaultsValues::ProgramINI;
		serialize_.SaveToFile(FileName);
		CDialogEx::OnOK();
	}
}
void CRawMakerDlg::OnCancel()
{
	OnOK();
}
void CRawMakerDlg::OnClose()
{
	/*m_Serialization.Save(_T("RawMaker.ini"));*/

	CDialogEx::OnClose();
}

const char csSignature[4] = {0x06,0x0E,0x2B,0x34};

#define SIZE_OFFSET 48
#define END_SIZE 224

#define AUDIO 1
#define VIDEO 2
DWORD CRawMakerDlg::ToBigEndian( DWORD  _Data)
{
	return ( (_Data&0xff)<<24) + ((_Data&0xff00)<<8) + ((_Data&0xff0000)>>8) + ((_Data>>24)&0xff);
	 //BIG;
}
void CRawMakerDlg::SetCreaterData(CRawCreater * pRawCreater)
{
	if (pRawCreater == NULL)
		return;

	CString sDataString(L"");
	
	m_EditOutDir.GetWindowText(sDataString);
	pRawCreater->SetFolderPath(sDataString.GetBuffer());
	// Header Offset
	m_EditHeaderOffset.GetWindowText(sDataString);
	pRawCreater->SetHeaderOffset(_ttol(sDataString));
	// Header
	m_EditHeader.GetWindowText(sDataString);
	std::string str = System::ToString(sDataString);
	pRawCreater->SetHeader( str );
	// Footer
	m_EditFooter.GetWindowText(sDataString);
	str = System::ToString(sDataString);
	pRawCreater->SetFooter(str);
	// Footer Offset
	m_EditAddFooter.GetWindowText(sDataString);
	pRawCreater->SetFooterOffset(_ttol(sDataString));
	// Footer Offset
	m_EditMinSize.GetWindowText(sDataString);
	pRawCreater->SetMinFileSize(_ttol(sDataString));
	// Footer Offset
	m_EditMaxSize.GetWindowText(sDataString);
	pRawCreater->SetMaxFileSize(_ttoi64(sDataString));
	// Header
	m_EditExtension.GetWindowText(sDataString);
	//wstring sExtension(sDataString.GetBuffer());
	pRawCreater->SetExtension(sDataString.GetBuffer());

}
void CRawMakerDlg::OnBnClickedButtonStart()
{
	//RawMXF();


	// Check
	if (!Parse())
		return;

	ClearData();

	CString sFileName;
	m_EditFileName.GetWindowText(sFileName);

	//CFileFactory FileFactory;
	//DevicePtr pFileDevice(FileFactory.CreateDevice());
	//pFileDevice->SetPath(sFileName.GetBuffer());

	CPhysicalDevice physicalDev;
	CDiviceList DeviceList;
	physicalDev.GetDevices(DeviceList);
	DevicePtr hddDevice(DeviceList.FindDevice(1));

	CReaderFactory ReaderFactory;
	IReader * pReader = ReaderFactory.CreateReader(hddDevice);
	pReader->Open();
	CString str;
	m_Offset.GetWindowText( str );
	LONGLONG offset = 0;//_ttoi64( str );
	//pReader->SetPosition( offset );
	//pReader->set
	CConsistentFactory ConsistentFactory;
	CAllocatorFactory AllocatorFactory;
	CQueueFactory QueueFactory;
	CTaskFactory TaskFactory;
	CRawCreaterFactory RawCreaterFactory;
	CAllocator * pAllocator = AllocatorFactory.CreateAllocator(DefaultBuffer,1000);
	CQueue * pQueue = (CQueue * ) QueueFactory.CreateQueue();

	ReaderConsistent_ = ( CReaderConsistent *) ConsistentFactory.CreateStreamReader(pReader,pQueue,pAllocator);
	ReaderConsistent_->SetDevice(hddDevice);
	ReaderConsistent_->SetSectorsCount( hddDevice->GetSectorCount() - offset );
	ReaderConsistent_->SetBlockSize(DefaultBuffer);
	ReaderConsistent_->SetOffset( offset );
	/*ReaderConsistent_->Attach( new CReaderObserver( this->GetSafeHwnd() ) );*/

	//TaskManager_ = (CTaskManager*)TaskFactory.CreateTask();
	//TaskManager_->SetAllocator(pAllocator);
	//TaskManager_->SetQueue(pQueue);
	TaskManager_ = new CTaskManager(pQueue,pAllocator);
	CRawCreater * pRawCreater = (CRawCreater *) RawCreaterFactory.CreateTask();
	SetCreaterData(pRawCreater);
	pRawCreater->Init();
	pRawCreater->Attach(new CCountFound( this->GetSafeHwnd() ) );

	TaskManager_->Add(pRawCreater);
	TaskManager_->Attach( new CSpeedObserver(this->GetSafeHwnd() , MaxProgress));
	TaskManager_->SetErrorObserver( new CErrorObserver(this->GetSafeHwnd()));
	LONGLONG lUpdateSize = hddDevice->GetSectorCount() / MaxProgress;
	lUpdateSize /= DefaultBuffer / hddDevice->GetBytesPerSector();
	TaskManager_->Attach( new CProgressObserver (this->GetSafeHwnd() , lUpdateSize) );
	m_TransferSize = MaxProgress * DefaultBuffer;
	m_TransferSize /= 1024;
	m_TransferSize *= 60;
	TaskManager_->SetEndObserver( new CFinishObserver(this->GetSafeHwnd() ) );
	
	if ( ReaderConsistent_->isReady() == FALSE )
	{
		CString sErrorString(ReaderConsistent_->GetErrorString().c_str());
		::AfxMessageBox(sErrorString, MB_OK);
		delete ReaderConsistent_;
		ReaderConsistent_ = NULL;
		return;
	}

	if ( TaskManager_->isReady() == FALSE )
	{
		CString sErrorString(TaskManager_->GetErrorString());
		::AfxMessageBox(sErrorString, MB_OK);
		delete ReaderConsistent_;
		ReaderConsistent_ = NULL;
		delete TaskManager_;
		TaskManager_ = NULL;
		return;
	}


	CCommunicateLock *pComunicate = CCommunicateLock::GetInstance();
	pComunicate->Resume();

	ReaderConsistent_->Run();
	TaskManager_->Run();

	m_ButtonStart.EnableWindow(FALSE);
	m_Progress.SetPos(0);
	m_LBAText.SetWindowText(L"0");
	m_ProgressNumber.SetWindowTextW(L"0.0%");

/*

	SetSerialization();

	CFullRaw *pFullRaw = new CFullRaw(&m_Serialization);
	if ( !pFullRaw->OpenRead(*m_Serialization.GetInputFile()) )
	{
		delete pFullRaw;
		AfxMessageBox(_T("Error Open file..."),MB_ICONERROR);
		return ;
	}
	CString strText;
	// Header offset 
	m_EditHeaderOffset.GetWindowText(strText);
	DWORD HeaderOffset = wcstoul(strText,NULL,10);
	pFullRaw->SetHeaderOffset(HeaderOffset);
	// Header
	m_EditHeader.GetWindowText(strText);
	pFullRaw->SetHeader(ToHexString(strText));
	// Footer
	m_EditFooter.GetWindowText(strText);
	pFullRaw->SetFooter(ToHexString(strText));
	// Footer Offset
	m_EditAddFooter.GetWindowText(strText);
	DWORD FooterOffset = wcstoul(strText,NULL,10);
	pFullRaw->SetFooterOffset(FooterOffset);

	// Max File Size
	m_EditMaxSize.GetWindowText(strText);
	LONGLONG MaxFileSize = _ttoi64(strText);
	pFullRaw->SetMaxFileSize(MaxFileSize);
	
	// Extension
	m_EditExtension.GetWindowText(strText);
	pFullRaw->SetExtension(ToString(strText));

	m_EditOutDir.GetWindowText(strText);
	pFullRaw->SetFolderPath(ToString(strText));

	//pFullRaw->
	pFullRaw->Run();

	pFullRaw->Close();
	delete pFullRaw;
	pFullRaw = NULL;

*/
	//::AfxMessageBox(_T("Finished..."),MB_OK);
}
void CRawMakerDlg::OnBnClickedRadioFile()
{
	if ( nDeviceID != enFileDevice )
	{
		HICON hIcon = NULL;
		if ( LoadIcon(hIcon , IDI_FILE_ICON) )
		{
			m_EditFileName.SetBrowseButtonImage(hIcon);
			Invalidate();
		}
		nDeviceID = enFileDevice;
		m_EditFileName.setFileOrDisk(nDeviceID);
	}
}
void CRawMakerDlg::OnBnClickedRadioDisk()
{
	if ( nDeviceID != enDiskDevice )
	{
		HICON hIcon = NULL;
		if ( LoadIcon(hIcon , IDI_HDD_ICON) )
		{
			m_EditFileName.SetBrowseButtonImage(hIcon);
			Invalidate();
		}
		nDeviceID = enDiskDevice;
		m_EditFileName.setFileOrDisk(nDeviceID);
	}
}
void CRawMakerDlg::OnBnClickedButtonStop()
{
	CCommunicateLock::GetInstance()->Abort();
	//ClearData();
	m_ButtonStart.EnableWindow(TRUE);
}
void CRawMakerDlg::SetCurrentFolder()
{
	TCHAR CurrDir[MaxFilePath];
	GetCurrentDirectory(MaxFilePath,CurrDir);
	m_sCurrentFolder = CurrDir;
}
void CRawMakerDlg::SetSerialization(CRawMakerSaver * _Serialize)
{
	CString strValues;
	m_EditFileName.GetWindowText(strValues);
	_Serialize->SetInputFile(strValues);

	m_EditOutDir.GetWindowText(strValues);
	_Serialize->SetOutputFolder(strValues);
	
	m_EditHeaderOffset.GetWindowTextW(strValues);
	_Serialize->SetHeaderOffset(strValues);

	m_EditHeader.GetWindowText(strValues);
	_Serialize->SetHeaderSignature(strValues);

	m_EditFooter.GetWindowTextW(strValues);
	_Serialize->SetFooterSignature(strValues);

	m_EditAddFooter.GetWindowTextW(strValues);
	_Serialize->SetFooterOffset(strValues);

	m_EditMinSize.GetWindowTextW(strValues);
	_Serialize->SetMinSize(strValues);

	m_EditMaxSize.GetWindowTextW(strValues);
	_Serialize->SetMaxSize(strValues);

	m_EditExtension.GetWindowTextW(strValues);
	_Serialize->SetExtension(strValues);

	m_Offset.GetWindowTextW( strValues );
	_Serialize->SetOffset( strValues );
}


BOOL CRawMakerDlg::ParseInteger(const CString &_IntString)
{
	CString integerStr = L"0123456789";
	TCHAR intSymbol = 0;
	for (int iPos = 0; iPos < _IntString.GetLength(); ++iPos)
	{
		intSymbol = _IntString.GetAt(iPos);
		if (integerStr.Find(intSymbol) == -1 )
			return FALSE;
	}
	return TRUE;
}
BOOL CRawMakerDlg::ParseHex(CEdit *_pEdit, const CString &_keyword/*, const CString &_default*/)
{
	CString HexStr = L"0123456789ABCDEF";
	TCHAR hexSymbol = 0;
	CString parseStr;
	_pEdit->GetWindowText(parseStr);
	parseStr.MakeUpper();
	if ( (parseStr.GetLength() ) % 2 != 0)
	{
		AfxMessageBox(_T("Hex values must be consist of two digits."),MB_ICONERROR);
		return FALSE;
	}
	for (int iPos = 0; iPos < parseStr.GetLength(); ++iPos)
	{
		hexSymbol = parseStr.GetAt(iPos);
		if (HexStr.Find(hexSymbol) == -1 )
		{
			CString strFormat;
			strFormat.Format(L"Symbols must be only hex",_keyword);
			AfxMessageBox(strFormat,MB_ICONERROR);
			//_pEdit->SetWindowTextW(_default);
			_pEdit->SetFocus();
			_pEdit->SetSel(0,_pEdit->GetWindowTextLengthW());
			return FALSE;
		}

	}
	return TRUE;
}
BOOL CRawMakerDlg::ParseMaxValue(CEdit *_pEdit,const CString &_keyword/*, const CString &_default*/)
{
	CString parseStr;
	_pEdit->GetWindowText(parseStr);
	DWORD offsetSize = 0;
	DWORD dwError = 0;
	CString strFormat;
	if (!ParseInteger(parseStr))
	{
		strFormat.Format(L"[%s] must be only numbers",_keyword);
		AfxMessageBox(strFormat,MB_ICONERROR);
		//_pEdit->SetWindowTextW(_default);
		_pEdit->SetFocus();
		return FALSE;
	}
	_set_errno(0);
	offsetSize = wcstoul(parseStr,NULL,10);
	if (errno == ERANGE)
	{
		strFormat.Format(L"[%s] value is must be ( 0 - 4294967295 )",_keyword);
		AfxMessageBox(strFormat,MB_ICONERROR);
		//_pEdit->SetWindowTextW(_default);
		_pEdit->SetFocus();
		_pEdit->SetSel(0,_pEdit->GetWindowTextLengthW());
		return FALSE;
	}
	return TRUE;
}
BOOL CRawMakerDlg::ParseLargeMaxValue(CEdit *_pEdit, const CString &_keyword/*, const CString &_default*/)
{
	CString parseStr;
	_pEdit->GetWindowText(parseStr);
	DWORD offsetSize = 0;
	DWORD dwError = 0;
	CString strFormat;
	if (!ParseInteger(parseStr))
	{
		strFormat.Format(L"[%s] must be only numbers",_keyword);
		AfxMessageBox(strFormat,MB_ICONERROR);
		//_pEdit->SetWindowTextW(_default);
		_pEdit->SetFocus();
		return FALSE;
	}
	//_set_errno(0);
	//offsetSize = wcstoul(parseStr,NULL,10);
	//if (errno == ERANGE)
	//{
	//	strFormat.Format(L"[%s] value is must be ( 0 - 4294967295 )",_keyword);
	//	AfxMessageBox(strFormat,MB_ICONERROR);
	//	//_pEdit->SetWindowTextW(_default);
	//	_pEdit->SetFocus();
	//	_pEdit->SetSel(0,_pEdit->GetWindowTextLengthW());
	//	return FALSE;
	//}
	return TRUE;

}

BOOL CRawMakerDlg::ParseMinMax(CEdit *pEditMin, CEdit *pEditMax, const CString &_keyword)
{
	CString parseStr;
	DWORD MinSize = 0;
	LONGLONG MaxSize = 0;
	pEditMin->GetWindowText(parseStr);
	MinSize = _ttol(parseStr);
	pEditMax->GetWindowText(parseStr);
	MaxSize = _ttoi64(parseStr);

	if (MinSize > MaxSize)
	{
		::AfxMessageBox(L"Min size is more the Max size!", MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}

BOOL CRawMakerDlg::Parse()
{
	if (!ParseMaxValue(&m_EditHeaderOffset,Keywords::HeaderOffset))
		return FALSE;
	if (!ParseMaxValue(&m_EditAddFooter,Keywords::FooterOffset))
		return FALSE;
	if (!ParseMaxValue(&m_EditMinSize,Keywords::MinSize))
		return FALSE;
	if (!ParseLargeMaxValue(&m_EditMaxSize,Keywords::MaxSize))
		return FALSE;
	if ( !ParseMinMax(&m_EditMinSize, &m_EditMaxSize, Keywords::MinSize) )
		return FALSE;
	if (!ParseHex(&m_EditHeader,Keywords::HeaderSignature))
		return FALSE;
	if (!ParseHex(&m_EditFooter,Keywords::FooterSignature))
		return FALSE;
	return TRUE;
}
LRESULT CRawMakerDlg::OnUpdateLBA(WPARAM wParam, LPARAM lParam)
{
	const LONGLONG  pCurrentLBA = (const LONGLONG ) lParam;
	CString sFormat;
	sFormat.Format(L"%I64d", pCurrentLBA);
	m_LBAText.SetWindowText(sFormat);
	return S_OK;
}
LRESULT CRawMakerDlg::OnUpdateSpeed(WPARAM wParam, LPARAM lParam)
{
	if (wParam != 0)
	{
		CString sFormat;	// ????????????
		sFormat.Format(_T("%d MB/min"),m_TransferSize/wParam);
		m_SpeedText.SetWindowText(sFormat);
	}
	return S_OK;
}
LRESULT CRawMakerDlg::OnUpdateProgress(WPARAM wParam, LPARAM lParam)
{
	//m_Progress.SetPos(m_Progress.GetPos() + 1 );
	int iPos = m_Progress.GetPos();
	++iPos;
	m_Progress.SetPos(iPos);
	double dPersent = (double) iPos / (double) 1000;
	dPersent *= 100;
	CString sPersent;
	sPersent.Format(L"%.1f%%",dPersent);
	m_ProgressNumber.SetWindowText(sPersent);
	return S_OK;
}
LRESULT CRawMakerDlg::OnFinish(WPARAM wParam, LPARAM lParam)
{
	m_ButtonStart.EnableWindow(TRUE);

	m_Progress.SetPos(MaxProgress);
	CString sPersent;
	sPersent.Format(L"100%%");
	m_ProgressNumber.SetWindowText(sPersent);

	::AfxMessageBox(L"Finished...");
	return S_OK;
}
LRESULT CRawMakerDlg::OnFoundCounts(WPARAM wParam, LPARAM lParam)
{
	DWORD iCounter = (DWORD) lParam;
	CString sText;
	sText.Format(L"%d",iCounter);
	m_LBAText.SetWindowTextW(sText);
	return S_OK;
}
LRESULT CRawMakerDlg::OnError(WPARAM wParam, LPARAM lParam)
{
	const char * pErrorStr = (const char *) lParam;
	CString sShowStr(pErrorStr);
	MessageBox(sShowStr,MB_OK);
	return S_OK;
}
//#include<map>
//using std::map;
//using std::pair;

//typedef pair<wstring,DWORD> TAudioMap;
//
//void CRawMakerDlg::RawMXF()
//{
//	CDiskDevice * pDevice = new CDiskDevice();
//	DevicePtr ptrDevice(pDevice);
//	CDiviceList devList;
//	CPhysicalDevice physicDev;
//	physicDev.GetDevices(devList);
//
//	DWORD iNumber = 2;
//	DevicePtr ptrDev = devList.FindDevice(iNumber);
//	//CFileDevice * pFileDevice = new CFileDevice();
//	//pFileDevice->SetPath(L"e:\\public\\30268\\1\\CONTENTS\\VIDEO\\0005KU.MXF");
//	//	DevicePtr ptrDev(pFileDevice);
//	CReader * pReader = new CReader(ptrDev);
//	if (!pReader->Open() )
//	{
//		TRACE("Error open Device to Read... \r\n");
//		return;
//	}
//	LONGLONG MaxLBA = ptrDev->GetSectorCount();
//	MaxLBA *= ptrDev->GetBytesPerSector();
//	//MaxLBA = 181184992;
//
//	LONGLONG lCurrentPos = (LONGLONG) 60393515 * 512;
//	const DWORD ReadSize = /*256*512*/ptrDev->GetMaxTransferSize();
//	CBuffer * pBuffer = new CBuffer(ReadSize);
//	BYTE * pReadData = NULL;
//	DWORD BytesRead = 0;
//	DWORD nSector = 0;
//	BOOL bFind = FALSE;
//	DWORD iFileNumber = 0;
//	BYTE * pSector = NULL;
//	wstring wsFileName;
//	wstring sVideoName;
//	wstring sAudioName;
//	BYTE RawType = 0;
//	
//	map<wstring,DWORD> AudioMap;
//
//	while (lCurrentPos < MaxLBA)
//	{
//		BytesRead = pReader->Read(pBuffer,lCurrentPos) ;
//		if (BytesRead == 0)
//		{
//			TRACE("Error Read from Device... \r\n");
//			break;
//		}
//
//		pReadData = pBuffer->GetBuffer();
//
//		for (DWORD iSector = 0; iSector < BytesRead; iSector += SECTOR_SIZE)
//		{
//			if (memcmp(pReadData + iSector,csSignature,4) == 0)
//			{
//				nSector = iSector;
//				pSector = (BYTE*)&pReadData[nSector];
//
//				BYTE * pRawType = (BYTE *) & pSector[59];
//				RawType = *pRawType;
//
//				DWORD *pFileSize = (DWORD *) &pSector[SIZE_OFFSET];
//				DWORD FileSize = ToBigEndian(*pFileSize);
//
//				LONGLONG lEndPos = (LONGLONG) (lCurrentPos + nSector);
//				lEndPos += FileSize;
//
//				BYTE Sector[SECTOR_SIZE];
//				if ( pReader->Read(Sector,SECTOR_SIZE,lEndPos) == 0 )
//				{
//					TRACE ("Error Read Sector (FileSize)...");
//					break;
//				}
//				if (memcmp(Sector,csSignature,4) == 0)
//				{
//					LONGLONG lFileNamePos = (LONGLONG) (lCurrentPos + nSector + 4*SECTOR_SIZE);
//					if ( pReader->Read(Sector,SECTOR_SIZE,lFileNamePos) == 0)
//					{
//						TRACE ("Error Read Sector (FileName)...");
//						break;
//
//					}
//					wchar_t wcFileName[8];
//					ZeroMemory(wcFileName,sizeof(wchar_t)*8);
//					wchar_t *pwFileName = (wchar_t *) &Sector[388];
//					wmemcpy(wcFileName,pwFileName,6);
//					for (WORD iNum = 0; iNum < 6; ++iNum)
//					{
//						wcFileName[iNum] = wcFileName[iNum]<< 8 | wcFileName[iNum]>> 8;
//					}
//
//					
//					wsFileName = wcFileName;
//					bFind = TRUE;
//					break;
//				}
//			}
//		}
//
//		if (bFind == TRUE)
//		{
//			// Write to File
//			lCurrentPos += nSector;
//			wchar_t FileName[MAX_PATH];
//			ZeroMemory(FileName,MAX_PATH*sizeof(wchar_t));
//			if (RawType == 0x8C)
//				swprintf_s(FileName,MAX_PATH*sizeof(wchar_t),L"H:\\RAW\\Video\\%s.MXF",wsFileName.c_str());
//			else
//			if (RawType == 0x5a)
//			{
//				map<wstring,DWORD>::iterator it;
//				it = AudioMap.find(wsFileName);
//				if (it == AudioMap.end())
//				{
//					AudioMap.insert(TAudioMap(wsFileName,1));
//					swprintf_s(FileName,MAX_PATH*sizeof(wchar_t),L"H:\\RAW\\Audio\\%s%.2d.MXF",wsFileName.c_str(),0);
//				}
//				else
//				{
//					swprintf_s(FileName,MAX_PATH*sizeof(wchar_t),L"H:\\RAW\\Audio\\%s%.2d.MXF",wsFileName.c_str(),it->second);
//					++it->second;
//				}
//			}
//			else
//				swprintf_s(FileName,MAX_PATH*sizeof(wchar_t),L"H:\\RAW\\Other\\%s-%.2d.MXF",wsFileName.c_str(),iFileNumber);
//
//
//			++iFileNumber;
//			bFind = FALSE;
//
//			CFileDevice *pFileDevice = new CFileDevice();
//			pFileDevice->SetPath(FileName);
//			DevicePtr writeFile(pFileDevice);
//			CWriter * pWriter = new CWriter(writeFile);
//			if ( !pWriter->Open())
//			{
//				TRACE(L"Error Create File %s\r\n",FileName);
//				exit(-1);
//			}
//
//			// Get File size
//			pSector = (BYTE*)&pReadData[nSector];
//			DWORD *pFileSize = (DWORD *) &pSector[SIZE_OFFSET];
//			DWORD FileSize = ToBigEndian(*pFileSize);
//
//			DWORD BytesWrite = 0;
//			LONGLONG lWritePos = 0;
//			while (lCurrentPos < MaxLBA)
//			{
//				if ( (lCurrentPos + ReadSize) > MaxLBA)
//				{
//					DWORD LastReadSize = (DWORD)( MaxLBA - lCurrentPos);
//					pBuffer->SetSize(LastReadSize);
//				}
//				BytesRead = pReader->Read(pBuffer,lCurrentPos);
//				if ( BytesRead == 0)
//				{
//					TRACE("Error Read Device \r\n");
//					break;
//				}
//				
//				 if ( (BytesWrite + BytesRead) > FileSize )
//				 {
//					 BytesRead = FileSize - BytesWrite;
//				 }
//				 BytesWrite += BytesRead;
//
//				if ( pWriter->Write(pBuffer->GetBuffer(),BytesRead,lWritePos) == 0)
//				{
//					TRACE(L"Error write to File %s\r\n",writeFile->GetPath());
//					break;
//				}
//				lWritePos += BytesRead;
//				lCurrentPos += BytesRead;
//				if (BytesWrite > FileSize)
//					break;
//			}
//
//			// Write to End
//			if (BytesRead + END_SIZE <= pBuffer->GetSize())
//			{
//				pReadData = pBuffer->GetBuffer();
//				pSector = &pReadData[BytesRead];
//				if ( pWriter->Write(pSector,END_SIZE,lWritePos) == 0)
//				{
//					TRACE(L"Error write to File %s\r\n",writeFile->GetPath());
//					break;
//				}
//			}
//
//
//			pBuffer->SetSize(ReadSize);
//		}
//		else
//			lCurrentPos += ReadSize;
//
//		
//	}
//
//	delete pBuffer;
//	delete pReader;
//	
//
//
//
//}


