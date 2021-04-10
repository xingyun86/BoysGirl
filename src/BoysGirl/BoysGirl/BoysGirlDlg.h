
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
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg LRESULT OnNotifyMsg(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnRestartExplorer(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	typedef struct MsgCursor {
		UINT uMsg;
		LPTSTR pCursor;
	}MsgCursor;
	const std::unordered_map<UINT, MsgCursor> m_mapMsgCursor = {
		{HTTOP, {SC_SIZE | WMSZ_TOP, IDC_SIZENS}},
		{HTBOTTOM, {SC_SIZE | WMSZ_BOTTOM, IDC_SIZENS}},
		{HTLEFT, {SC_SIZE | WMSZ_LEFT, IDC_SIZEWE}},
		{HTRIGHT, {SC_SIZE | WMSZ_RIGHT, IDC_SIZEWE}},
		{HTTOPLEFT, {SC_SIZE | WMSZ_TOPLEFT, IDC_SIZENWSE}},
		{HTTOPRIGHT, {SC_SIZE | WMSZ_TOPRIGHT, IDC_SIZENESW}},
		{HTBOTTOMLEFT, {SC_SIZE | WMSZ_BOTTOMLEFT, IDC_SIZENESW}},
		{HTBOTTOMRIGHT, {SC_SIZE | WMSZ_BOTTOMRIGHT, IDC_SIZENWSE}},
		{HTCAPTION, {SC_MOVE | WMSZ_TOPLEFT, NULL}},
	};
private:
	int BORDER_SIZE = 5;
	int CROSS_BORDER_SIZE = 10;
	int m_titleBarHeight = 30;
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
private:
	void MemoryDoubleBuffer(HDC hDC)
	{
		CRect rc = {};
		GetClientRect(&rc);
		Gdiplus::Bitmap bitmapMem(rc.Width(), rc.Height());
		Gdiplus::Graphics graphicsMem(&bitmapMem);
		
		graphicsMem.Clear(Gdiplus::Color(255, 255, 255));
		graphicsMem.SetSmoothingMode(Gdiplus::SmoothingModeNone);

		PaintTitleBar(graphicsMem, rc);
	
		Gdiplus::Graphics graphics(hDC);
		Gdiplus::CachedBitmap cachedBmp(&bitmapMem, &graphics);
		graphics.DrawCachedBitmap(&cachedBmp, 0, 0);
	}
	void PaintTitleBar(Gdiplus::Graphics& graphicsMem, const CRect & rc)
	{
		Gdiplus::SolidBrush titleBrush(Gdiplus::Color(20, 150, 250));
		Gdiplus::SolidBrush borderBrush(Gdiplus::Color(20, 150, 250));
		//ªÊ÷∆±ÍÃ‚¿∏
		graphicsMem.FillRectangle(&titleBrush, rc.left, rc.top, rc.Width(), m_titleBarHeight);
		//ªÊ÷∆◊Û±ﬂøÚ
		graphicsMem.FillRectangle(&borderBrush, rc.left, rc.top, BORDER_SIZE, rc.Height());
		//ªÊ÷∆…œ±ﬂøÚ
		graphicsMem.FillRectangle(&borderBrush, rc.left, rc.top, rc.Width(), BORDER_SIZE);
		//ªÊ÷∆”“±ﬂøÚ
		graphicsMem.FillRectangle(&borderBrush, rc.right - BORDER_SIZE, rc.top, BORDER_SIZE, rc.Height());
		//ªÊ÷∆œ¬±ﬂøÚ
		graphicsMem.FillRectangle(&borderBrush, rc.left, rc.bottom - BORDER_SIZE, rc.Width(), BORDER_SIZE);

		Gdiplus::FontFamily  fontFamily(L"Times New Roman");
		Gdiplus::Font        font(&fontFamily, 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
		Gdiplus::PointF      pointF(0.0f, 10.0f);
		Gdiplus::SolidBrush  textBrush(Gdiplus::Color(255, 0, 0, 255));
		graphicsMem.DrawString(L"TitleBar", -1, &font, pointF, &textBrush);
	}
	void NotifyUpdate()
	{
		InvalidateRect(NULL);
	}
};
