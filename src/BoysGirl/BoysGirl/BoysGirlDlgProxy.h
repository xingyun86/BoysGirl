
// BoysGirlDlgProxy.h: header file
//

#pragma once

class CBoysGirlDlg;


// CBoysGirlDlgAutoProxy command target

class CBoysGirlDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CBoysGirlDlgAutoProxy)

	CBoysGirlDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CBoysGirlDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CBoysGirlDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CBoysGirlDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

