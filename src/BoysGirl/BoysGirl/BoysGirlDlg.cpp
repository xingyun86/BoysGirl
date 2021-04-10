
// BoysGirlDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "BoysGirlApp.h"
#include "BoysGirlDlg.h"
#include "BoysGirlDlgProxy.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBoysGirlDlg dialog


IMPLEMENT_DYNAMIC(CBoysGirlDlg, CDialogEx);

CBoysGirlDlg::CBoysGirlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BOYSGIRL_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = nullptr;
}

CBoysGirlDlg::~CBoysGirlDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to null, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != nullptr)
		m_pAutoProxy->m_pDialog = nullptr;
}

void CBoysGirlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBoysGirlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_MESSAGE(WM_USER_NOTIFYICON, OnNotifyMsg)
	ON_REGISTERED_MESSAGE(WMEX_TASKBARCREATED, OnRestartExplorer)
END_MESSAGE_MAP()


// CBoysGirlDlg message handlers

BOOL CBoysGirlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	SetWindowLongPtr(this->GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(this->GetSafeHwnd(), GWL_STYLE) & (~WS_CAPTION) & (~WS_SIZEBOX) & (~WS_THICKFRAME));
	SetWindowLongPtr(this->GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(this->GetSafeHwnd(), GWL_EXSTYLE));
	SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);

	theApp.m_pFloatDlg->ShowTopMost();

	AddNotifyIcon();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBoysGirlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		NotifyUpdate();
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBoysGirlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		
		MemoryDoubleBuffer(dc.m_hDC);

		ReleaseDC(&dc);
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBoysGirlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CBoysGirlDlg::OnClose()
{
	if (CanExit())
	{
		CDialogEx::OnClose();
	}
}

void CBoysGirlDlg::OnOK()
{
	if (CanExit())
	{
		CDialogEx::OnOK();
	}
}

void CBoysGirlDlg::OnCancel()
{
	if (CanExit())
	{
		CDialogEx::OnCancel();
	}
}

BOOL CBoysGirlDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != nullptr)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	DelNotifyIcon();

	return TRUE;
}

LRESULT CBoysGirlDlg::OnNotifyMsg(WPARAM wParam, LPARAM lParam)
{
	//wParam接收的是图标的ID，而lParam接收的是鼠标的行为   
	if (wParam != IDR_MAINFRAME)
	{
		return TRUE;
	}
	switch (lParam)
	{
	case WM_RBUTTONUP: 
	{
#define IDMENU_CONFIG 1000
		CMenu menu = {};
		POINT pt = { 0 };
		::GetCursorPos(&pt);
		menu.CreatePopupMenu();
		menu.AppendMenu(MF_STRING, IDMENU_CONFIG, TEXT("配置"));
		menu.AppendMenu(MF_STRING, WM_DESTROY, TEXT("退出"));
		menu.TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this);
		menu.Detach();
		menu.DestroyMenu();
	}
	break;
	case WM_LBUTTONDBLCLK:
	{
		if (IsWindowVisible())
		{
			ShowWindow(SW_HIDE);
		}
		else
		{
			ShowWindow(SW_SHOW);
		}
	}
	break;
	}
	return FALSE;
}

LRESULT CBoysGirlDlg::OnRestartExplorer(WPARAM wParam, LPARAM lParam)
{
	AddNotifyIcon();
	return TRUE;
}

LRESULT CBoysGirlDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect = {};
	GetWindowRect(&rect);
	CRect rectNoBorder = rect;
	rectNoBorder.DeflateRect(CROSS_BORDER_SIZE, CROSS_BORDER_SIZE, -CROSS_BORDER_SIZE, -CROSS_BORDER_SIZE);
	rectNoBorder.NormalizeRect();
	if (point.x <= rect.left + BORDER_SIZE)
	{
		return HTLEFT;
	}
	else if (point.x >= rect.right - BORDER_SIZE)
	{
		return HTRIGHT;
	}
	else if (point.y <= rect.top + BORDER_SIZE)
	{
		return HTTOP;
	}
	else if (point.y >= rect.bottom - BORDER_SIZE)
	{
		return HTBOTTOM;
	}
	else if (point.x <= rect.left + CROSS_BORDER_SIZE && point.y <= rect.top + CROSS_BORDER_SIZE)
	{
		return HTTOPLEFT;
	}
	else if (point.x >= rect.right - CROSS_BORDER_SIZE && point.y <= rect.top + CROSS_BORDER_SIZE)
	{
		return HTTOPRIGHT;
	}
	else if (point.x <= rect.left + CROSS_BORDER_SIZE && point.y >= rect.bottom - CROSS_BORDER_SIZE)
	{
		return HTBOTTOMLEFT;
	}
	else if (point.x >= rect.right - CROSS_BORDER_SIZE && point.y >= rect.bottom - CROSS_BORDER_SIZE)
	{
		return HTBOTTOMRIGHT;
	}
	else if (!rectNoBorder.IsRectEmpty())
	{
		if (point.y > 0 && point.y < (rect.top + m_titleBarHeight))
		{
			return HTCAPTION;
		}
		else
		{
			return CWnd::OnNcHitTest(point);
		}
		//LRESULT lRet = CWnd::OnNcHitTest(point);
		//lRet = (lRet == HTCLIENT) ? HTCAPTION : lRet;
		//return lRet;
	}
	else
	{
		return CWnd::OnNcHitTest(point);
	}
	return FALSE;
	//return CDialogEx::OnNcHitTest(point);
}


void CBoysGirlDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	auto itMsgCursor = m_mapMsgCursor.find(nHitTest);
	if (itMsgCursor != m_mapMsgCursor.end())
	{
		if (itMsgCursor->second.pCursor != NULL)
		{
			SetCursor(LoadCursor(NULL, itMsgCursor->second.pCursor));
		}
		SendMessage(WM_SYSCOMMAND, itMsgCursor->second.uMsg, MAKELPARAM(point.x, point.y));
		NotifyUpdate();
	}
	
	CDialogEx::OnNcLButtonDown(nHitTest, point);
}

