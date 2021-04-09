
// BoysGirl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "BoysGirlDlg.h"
#include "FloatDlg.h"

// CBoysGirlApp:
// See BoysGirl.cpp for the implementation of this class
//

class CBoysGirlApp : public CWinApp
{
public:
	CBoysGirlApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
public:
	std::shared_ptr<CBoysGirlDlg> m_pMainDlg = nullptr;
	std::shared_ptr<CFloatDlg> m_pFloatDlg = nullptr;
	
};

extern CBoysGirlApp theApp;
