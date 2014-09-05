
// PdfChecker.h : main header file for the PdfChecker application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPdfCheckerApp:
// See PdfChecker.cpp for the implementation of this class
//

class CPdfCheckerApp : public CWinApp
{
public:
	CPdfCheckerApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPdfCheckerApp theApp;
