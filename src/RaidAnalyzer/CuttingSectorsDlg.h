#pragma once

#include "GatherByJPG.h"
// CCuttingSectorsDlg dialog

enum EDIT_STYLE { DIGIT_STYLE = 0, STRING_STYLE = 1};

class CCuttingSectorsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCuttingSectorsDlg)

public:
	CCuttingSectorsDlg(CWnd* pParent = NULL);   // standard constructor
	CCuttingSectorsDlg(CWnd* pParent /*= NULL*/, UINT _iCurrentStep);
	virtual ~CCuttingSectorsDlg();
	CString getStringData() const;
	UINT getNumber() const;
	NUMBER_POS getDiskNumberPos() const;
	enStateProgram getStatProgram() const;
	void setDefaultData(CString _strData);
	void setTextData(CString _strData);
	void setEditStyle(EDIT_STYLE _Edit_Style);
	void setCurrentStep(UINT _icurrStep);
	void setMinMax(UINT _iMin, UINT _iMax);
	void setStateProgram(enStateProgram _enStateProgram);
	void setHeader(CString _strHeader);

// Dialog Data
	enum { IDD = IDD_CUTTING_SECTORS };
private:
	CButton* m_pButtBack;
	CButton* m_pButtonPauseResume;
	CEdit* m_pEditStringDATA;
	CEdit* m_pEditTextOut;
	CStatic* m_pTextOutput;
	CStatic* m_pMainText;
	CStatic* m_pTextDigit;
	CString m_strTextOut;
	CString m_strData;
	CString m_strHeader;
	UINT m_iCurrentSTEP;
	UINT m_iNumber;
	EDIT_STYLE m_EditStyle;
	UINT m_iMin;
	UINT m_iMax;
	NUMBER_POS m_NumberPos;
	enStateProgram m_enStateProgram;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonPauseResume();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditNumberSectors();
	afx_msg void OnCancel();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	DECLARE_MESSAGE_MAP()
};


