
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


class CDib;


class CImageToolBoxApp : public CWinApp
{
public:
	CImageToolBoxApp();
	~CImageToolBoxApp();

public:
	CDib* m_pNewDib;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
};

extern CImageToolBoxApp theApp;

void AfxNewImage(CDib& dib);
