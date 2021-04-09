
// BoysGirlDlg.h : header file
//

#pragma once

class CBoysGirlDlgAutoProxy;

const UINT WMEX_TASKBARCREATED = ::RegisterWindowMessage(TEXT("TaskbarCreated"));

// CBoysGirlDlg dialog
class CBoysGirlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBoysGirlDlg);
	friend class CBoysGirlDlgAutoProxy;

// Construction
public:
	CBoysGirlDlg(CWnd* pParent = nullptr);	// standard constructor
	virtual ~CBoysGirlDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BOYSGIRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CBoysGirlDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose(); 
	afx_msg LRESULT OnNotifyMsg(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnRestartExplorer(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	NOTIFYICONDATA m_notifyIconData = { 0 };
	void AddNotifyIcon()
	{
		m_notifyIconData.cbSize = sizeof NOTIFYICONDATA;
		m_notifyIconData.hWnd = this->m_hWnd;
		m_notifyIconData.uID = IDR_MAINFRAME;
		m_notifyIconData.hIcon = m_hIcon;
		lstrcpy(m_notifyIconData.szTip, TEXT("BoysGirl"));
		m_notifyIconData.uCallbackMessage = WM_USER_NOTIFYICON;
		m_notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		Shell_NotifyIcon(NIM_ADD, &m_notifyIconData);
	}
	void ModNotifyIconText(const TSTRING& text)
	{
		lstrcpy(m_notifyIconData.szTip, text.c_str());
	}
	void DelNotifyIcon()
	{
		Shell_NotifyIcon(NIM_DELETE, &m_notifyIconData);
	}
};
