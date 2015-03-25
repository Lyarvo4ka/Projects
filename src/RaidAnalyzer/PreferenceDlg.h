#pragma once
#include "afxeditbrowsectrl.h"
#include "afxwin.h"

#include "Utility.h"


// CPreferenceDlg dialog

class CPreferenceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPreferenceDlg)

public:
	CPreferenceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPreferenceDlg();

// Dialog Data
	enum { IDD = IDD_PREFERENCE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg BOOL OnInitDialog();
	afx_msg void OnOK();
	afx_msg void OnCancel();

private:
	CMFCEditBrowseCtrl * m_WorkPathText;
	CEdit * m_FileCountText;
	CEdit * m_MinBlockText;
	CEdit * m_MaxBlockText;

	DECLARE_MESSAGE_MAP()

};
