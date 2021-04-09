
// BoysGirlDlg.h : header file
//

#pragma once

class CBoysGirlDlgAutoProxy;


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
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
};
