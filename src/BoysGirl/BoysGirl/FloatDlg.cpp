// FloatDlg.cpp : implementation file
//

#include "pch.h"
#include "BoysGirlApp.h"
#include "FloatDlg.h"
#include "afxdialogex.h"


// CFloatDlg dialog

IMPLEMENT_DYNAMIC(CFloatDlg, CDialogEx)

CFloatDlg::CFloatDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FLOAT_DIALOG, pParent)
{
	m_isDlgInited = false;
}

CFloatDlg::~CFloatDlg()
{
}

void CFloatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFloatDlg, CDialogEx)
	ON_WM_MOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CFloatDlg message handlers
BOOL CFloatDlg::OnInitDialog()
{
	LoadPosition();

	::SetWindowLongPtr(this->GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(this->GetSafeHwnd(), GWL_STYLE) & (~WS_CAPTION));
	::SetWindowLongPtr(this->GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_TOPMOST | WS_EX_TOOLWINDOW & (~WS_EX_APPWINDOW));

	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 64, 64, SWP_NOZORDER | SWP_NOMOVE | SWP_FRAMECHANGED);
	m_isDlgInited = true;

	return FALSE;
}

void CFloatDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: Add your message handler code here
	if (m_isDlgInited == true)
	{
		SavePosition();
	}
}


void CFloatDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CFloatDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (theApp.m_pMainDlg->IsWindowVisible())
	{
		theApp.m_pMainDlg->ShowWindow(SW_HIDE);
	}
	else
	{
		theApp.m_pMainDlg->ShowWindow(SW_SHOW);
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}

void CFloatDlg::ShowTopMost() 
{
	ShowWindow(SW_SHOWNORMAL);
	SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

void CFloatDlg::LoadPosition() 
{
	CString text = theApp.GetProfileString(TEXT("POINT"), TEXT("FLOAT"), TEXT("(0,0)"));
	_stscanf_s(text, TEXT("(%d,%d)"), &m_ptPos.x, &m_ptPos.y);
	SetWindowPos(&CWnd::wndTopMost, m_ptPos.x, m_ptPos.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

void CFloatDlg::SavePosition()
{
	CRect rc = { 0 };
	CString text(TEXT(""));
	this->GetWindowRect(rc);
	m_ptPos.x = rc.left;
	m_ptPos.y = rc.top;
	text.Format(TEXT("(%d,%d)"), m_ptPos.x, m_ptPos.y);
	theApp.WriteProfileString(TEXT("POINT"), TEXT("FLOAT"), text);
}