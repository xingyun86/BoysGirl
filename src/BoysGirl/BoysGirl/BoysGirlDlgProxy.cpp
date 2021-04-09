
// BoysGirlDlgProxy.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BoysGirlApp.h"
#include "BoysGirlDlgProxy.h"
#include "BoysGirlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBoysGirlDlgAutoProxy

IMPLEMENT_DYNCREATE(CBoysGirlDlgAutoProxy, CCmdTarget)

CBoysGirlDlgAutoProxy::CBoysGirlDlgAutoProxy()
{
	EnableAutomation();

	// To keep the application running as long as an automation
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CBoysGirlDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CBoysGirlDlg)))
		{
			m_pDialog = reinterpret_cast<CBoysGirlDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CBoysGirlDlgAutoProxy::~CBoysGirlDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CBoysGirlDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CBoysGirlDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBoysGirlDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_IBoysGirl to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .IDL file.

// {9b0dfc5a-ec68-4a68-8474-703071e47634}
static const IID IID_IBoysGirl =
{0x9b0dfc5a,0xec68,0x4a68,{0x84,0x74,0x70,0x30,0x71,0xe4,0x76,0x34}};

BEGIN_INTERFACE_MAP(CBoysGirlDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CBoysGirlDlgAutoProxy, IID_IBoysGirl, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in pch.h of this project
// {4a56caea-6378-42b0-9031-812b950d715d}
IMPLEMENT_OLECREATE2(CBoysGirlDlgAutoProxy, "BoysGirl.Application", 0x4a56caea,0x6378,0x42b0,0x90,0x31,0x81,0x2b,0x95,0x0d,0x71,0x5d)


// CBoysGirlDlgAutoProxy message handlers
