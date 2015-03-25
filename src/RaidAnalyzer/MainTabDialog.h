#pragma once
#include <vector>
using std::vector;

#include "../DiskVerifier/Drives.h"
#include "afxcmn.h"
#include "afxwin.h"

vector<CDiskDrive> & setDevices(CListCtrl* _m_pListDrives, CDrives * _pDrives);

class CMainTabDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMainTabDialog)

public:
	CMainTabDialog(CWnd* pParent = NULL);   
	virtual ~CMainTabDialog();

	VerifyRange & getMinMaxLBA() ;
	vector<CDiskDrive> & getSelDrives();

	CDrives m_Drives;
	vector<CDiskDrive> m_vecDrives;
	vector<CDiskDrive> m_vecSelDrives;
	CListCtrl *m_pListDrives;
	CListBox* m_pListSelected;

// Dialog Data
	enum { IDD = IDD_MAIN_DIALOG };

private:
	bool AddSelectedDrive(int iPos);

	LONGLONG m_MinMaxLBA;
	CEdit *m_pEditMinLBA;
	CEdit *m_pEditMaxLBA;
	CString strEditText;
	VerifyRange rangeMinMaxLBA;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	virtual BOOL OnInitDialog();
	//afx_msg void OnBnClickedClearButton();
	afx_msg void OnNMDblclkListDrives(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
};
