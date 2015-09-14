#pragma once


// CTestSpeedHDDDlg dialog

class CTestSpeedHDDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTestSpeedHDDDlg)

public:
	CTestSpeedHDDDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestSpeedHDDDlg();

// Dialog Data
	enum { IDD = IDD_SPEED_HDD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	DWORD getBlockSize();
	CEdit* m_pEditBlockSize;
	afx_msg void OnBnClickedButtonStop();
};
