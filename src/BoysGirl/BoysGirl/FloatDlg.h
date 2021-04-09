#pragma once

// CFloatDlg dialog

class CFloatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFloatDlg)

public:
	CFloatDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CFloatDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FLOAT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	POINT m_ptPos = { 0,0 };
	bool m_isDlgInited = false;
public:
	void ShowTopMost();
	void LoadPosition();
	void SavePosition();
};
