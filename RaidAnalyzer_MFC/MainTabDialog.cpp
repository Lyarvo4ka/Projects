#include "stdafx.h"
#include "RaidAnalyzer.h"
#include "MainTabDialog.h"
#include "afxdialogex.h"



IMPLEMENT_DYNAMIC(CMainTabDialog, CDialogEx)

CMainTabDialog::CMainTabDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainTabDialog::IDD, pParent)
	, m_pListSelected(NULL), m_pEditMaxLBA(NULL), m_pEditMinLBA(NULL) 
{

}

CMainTabDialog::~CMainTabDialog()
{
	if (m_pListDrives != NULL)
	{
		delete m_pListDrives;
		m_pListDrives = NULL;
	}
}

void CMainTabDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST_DRIVES, m_ListDrives);
	//DDX_Control(pDX, IDC_EDIT_INDENT, m_EditIndent);
	//DDX_Control(pDX, IDC_EDIT_BLOCK_SIZE, m_pEditBlockSize);
	//DDX_Control(pDX, IDC_SELECTED_LIST, m_pListSelected);
	//DDX_Control(pDX, IDC_MIN_LBA, m_EditMinLBA);
	//DDX_Control(pDX, IDC_MAX_LBA, m_EditMaxLBA);
}


BEGIN_MESSAGE_MAP(CMainTabDialog, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DRIVES, &CMainTabDialog::OnNMDblclkListDrives)
	//ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CMainTabDialog::OnBnClickedClearButton)
END_MESSAGE_MAP()


BOOL CMainTabDialog::OnInitDialog()
{
	//m_Drives.getDiskNames();

	//m_pListDrives = static_cast<CListCtrl*> 
	//				( GetDlgItem ( IDC_LIST_DRIVES ) );
	//setDevices(m_pListDrives,&m_Drives,m_vecDrives);



	//m_pListSelected = static_cast<CListBox*> 
	//				( GetDlgItem ( IDC_SELECTED_LIST ) );

	//m_pEditMinLBA = static_cast<CEdit*> 
	//				( GetDlgItem ( IDC_MIN_LBA ) );
	//m_pEditMinLBA->SetWindowTextW(_T("0"));

	//m_pEditMaxLBA = static_cast<CEdit*> 
	//				( GetDlgItem ( IDC_MAX_LBA ) );
	//m_pEditMaxLBA->SetWindowTextW(_T("10000"));

	return TRUE;
}

bool CMainTabDialog::AddSelectedDrive(int iPos)
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


void CMainTabDialog::OnNMDblclkListDrives(NMHDR *pNMHDR, LRESULT *pResult)
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
			if ((bPresent = AddSelectedDrive(iItem)))
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
			m_MinMaxLBA = m_vecSelDrives.at(0).getSectorCount();
			strEditText.Format(_T("%I64d"),m_MinMaxLBA);
			m_pEditMaxLBA->SetWindowTextW(strEditText);
		}
		else
		for ( size_t i = 0; i < m_vecSelDrives.size(); ++i)
		{
			if ( m_MinMaxLBA > m_vecSelDrives.at(i).getSectorCount() )
			{
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


//void CMainTabDialog::OnBnClickedClearButton()
//{
//	if (m_vecSelDrives.size() > 0)
//	{
//		m_vecSelDrives.clear();
//		m_pListSelected->ResetContent();
//	}
//}

vector<CDiskDrive> & CMainTabDialog::getSelDrives()
{
	return m_vecSelDrives;
}


VerifyRange & CMainTabDialog::getMinMaxLBA() 
{

	m_pEditMinLBA->GetWindowTextW(strEditText);
	rangeMinMaxLBA.lFrom =  _ttoi64(strEditText);

	m_pEditMaxLBA->GetWindowTextW(strEditText);
	rangeMinMaxLBA.lTo = _ttoi64(strEditText);

	return rangeMinMaxLBA;
}

