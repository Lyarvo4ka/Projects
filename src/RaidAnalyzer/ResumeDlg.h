#pragma once


// CResumeDlg dialog

class CResumeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResumeDlg)
private:
		CStatic* m_pTextLBA;
		LONGLONG m_lPosLBA;
		int m_iChecked;
public:
	CResumeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CResumeDlg();

// Dialog Data
	enum { IDD = IDD_RESUME_DLG };

	void setLBAPosition(LONGLONG *_pLBApos);
	int CheckResult() const;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CButton* m_pCheckMissmatch;
	afx_msg void OnBnClickedCheckMissmatch();
};
