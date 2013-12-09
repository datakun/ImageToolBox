
// ImageToolBox.h : main header file for the ImageToolBox application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CImageToolBoxApp:
// See ImageToolBox.cpp for the implementation of this class
//

class CImageToolBoxApp : public CWinApp
{
public:
	CImageToolBoxApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImageToolBoxApp theApp;
