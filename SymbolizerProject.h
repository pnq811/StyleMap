// SymbolizerProject.h : main header file for the SymbolizerProject application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

// CSymbolizerProjectApp:
// See SymbolizerProject.cpp for the implementation of this class
//

class CSymbolizerProjectApp : public CBCGPWinApp
{
public:
	CSymbolizerProjectApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	virtual BOOL SaveAllModified();

	// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSymbolizerProjectApp theApp;
