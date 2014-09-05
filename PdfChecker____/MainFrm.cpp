
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PdfChecker.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


#include "include\acrobat.h"
#include "include\iac.h"

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	CAcroPDDoc * pAcroPdDoc = new CAcroPDDoc();

	CString pdfPath = "c:\\simple.pdf";

	if (!AfxOleInit())	{
		AfxMessageBox("OLE initialization failed in BasicIacVc sample.");
		return FALSE;
	}

	// === Create an Acrobat IAC PDDoc object  
	COleException e;
	pAcroPdDoc = new CAcroPDDoc;
	BOOL bCreate = pAcroPdDoc->CreateDispatch("AcroExch.PDDoc", &e);
	if(!pAcroPdDoc) {
		AfxMessageBox("Creating Acrobat IAC object failed in BasicIacVc sample.");
		return FALSE;
	}
	
	// === Open a pdf file.  

	if(!pAcroPdDoc->Open(pdfPath)) {
		CString message = "Opening the PDF file \"";
		message += pdfPath;
		message += "\" failed in the BasicIacVc sample.";
		AfxMessageBox(message);
		return FALSE;
	}

	// === Get the number of pages, and compose a massage.  
	char str[256];
	sprintf_s(str,"PDF document %s is loaded in Acrobat through IAC program.\n",pdfPath);
	long n = pAcroPdDoc->GetNumPages();

	CString date = pAcroPdDoc->GetInfo("ModDate");

	VARIANT_BOOL saved_ok = pAcroPdDoc->Save( PDSaveFull , "c:\\detected.pdf" );
	if ( !saved_ok )
	{
		sprintf_s(str, "Document is corrupted." );
		
	}

	if(n!=-1) 
		sprintf_s(str, "%sThe PDF file has %d pages.", str, n);
	else
		sprintf_s(str, "Error in getting page number.");
	
	// message
	AfxEnableControlContainer();
	AfxMessageBox(str);

	// === Code to finish program.
	pAcroPdDoc->Close();
	delete pAcroPdDoc;
	pAcroPdDoc = NULL;




	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

