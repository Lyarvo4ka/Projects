// PreferenceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RaidAnalyzer.h"
#include "PreferenceDlg.h"
#include "afxdialogex.h"

#include "Settings.h"


// CPreferenceDlg dialog

IMPLEMENT_DYNAMIC(CPreferenceDlg, CDialogEx)

CPreferenceDlg::CPreferenceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPreferenceDlg::IDD, pParent)
{

}

CPreferenceDlg::~CPreferenceDlg()
{
}

void CPreferenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_WORK_FOLDER, m_WorkPathText);
	//DDX_Control(pDX, IDC_FILE_COUNT, m_FileCountText);
	//DDX_Control(pDX, IDC_MIN_BLOCK, m_MinBlockText);
	//DDX_Control(pDX, c, m_MaxBlockText);
}


BEGIN_MESSAGE_MAP(CPreferenceDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CPreferenceDlg::OnInitDialog()
{
	m_WorkPathText = static_cast< CMFCEditBrowseCtrl *> ( GetDlgItem( IDC_WORK_FOLDER ) );
	m_FileCountText = static_cast< CEdit *> ( GetDlgItem( IDC_FILE_COUNT ) );
	m_MinBlockText = static_cast< CEdit *> ( GetDlgItem( IDC_MIN_BLOCK ) );
	m_MaxBlockText = static_cast< CEdit *> ( GetDlgItem( IDC_MAX_BLOCK ) );

	auto pSetting = settings::CSettings::getSetting();
	m_WorkPathText->SetWindowText( pSetting->getWorkFolder().c_str() );
	m_FileCountText->SetWindowText( Utility::IntToString ( pSetting->getFileCount() ).c_str() );
	m_MinBlockText->SetWindowText(Utility::IntToString ( pSetting->getMinBlock() ).c_str() );
	m_MaxBlockText->SetWindowText(Utility::IntToString ( pSetting->getMaxBlock() ).c_str() );
	return TRUE;
}

void CPreferenceDlg::OnOK()
{
	CString controlText;
	auto pSetting = settings::CSettings::getSetting();
	m_WorkPathText->GetWindowText(controlText);
	wstring workFolderStr ( controlText.GetBuffer( ) );
	Utility::PreperePath( workFolderStr );
	if ( ! Utility::isDirectoryExist( workFolderStr.c_str() ) )
	{
		AfxMessageBox(L"Заданая рабочая папка не существует.", MB_ICONERROR );
		return;
	}
	pSetting->setWorkPath( workFolderStr );

	controlText = "";
	m_FileCountText->GetWindowText(controlText);
	auto intValue = _ttoi( controlText.GetBuffer( ) );
	if ( intValue <= 0 )
	{
		AfxMessageBox(L"Количество файлов должно быть больше чем 1.", MB_ICONERROR );
		return;
	}
	pSetting->setFileCount( intValue );

	controlText = "";
	m_MinBlockText->GetWindowText(controlText);
	auto minValue = _ttoi( controlText.GetBuffer( ) );

	m_MaxBlockText->GetWindowText(controlText);
	auto maxValue = _ttoi( controlText.GetBuffer( ) );
	if ( minValue >= maxValue)
	{
		AfxMessageBox(L"Минимальное значение не должно быть больше чем максималное.", MB_ICONERROR );
		return;
	}
	pSetting->setMinBlock( minValue );
	pSetting->setMaxBlock( maxValue );

	CDialogEx::OnOK();
}

void CPreferenceDlg::OnCancel()
{
	CDialogEx::OnCancel();
}

