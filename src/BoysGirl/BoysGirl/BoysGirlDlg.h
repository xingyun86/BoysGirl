
// BoysGirlDlg.h : header file
//

#pragma once

#include <CustomButton.h>

class CBoysGirlDlgAutoProxy;

const UINT WMEX_TASKBARCREATED = ::RegisterWindowMessage(TEXT("TaskbarCreated"));
typedef enum RESTYPEID {
	ID_NULLPTR = 1000,
	IDMENU_CONFIG,
}RESTYPEID;
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg LRESULT OnNotifyMsg(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnRestartExplorer(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMenuConfig(void);
	DECLARE_MESSAGE_MAP()
private:
	void Init();
	void Exit();
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
	int BORDER_SIZE = 6;
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
	typedef struct IconBitmapHandle {
		Gdiplus::Bitmap* pBitmapArgb;
		Gdiplus::Bitmap* pBitmapIcon;
	}IconBitmapHandle;
	std::unordered_map<HICON, IconBitmapHandle> m_iconBitmapHandleMap = {};
private:
	IconBitmapHandle& GdiplusBitmapFromHICON(IconBitmapHandle & iconBitmapHandle, HICON hIcon)
	{
		iconBitmapHandle.pBitmapArgb = nullptr;
		iconBitmapHandle.pBitmapIcon = nullptr;
		auto it = m_iconBitmapHandleMap.find(hIcon);
		if (it == m_iconBitmapHandleMap.end())
		{
			ICONINFO iconInfo = { 0 };
			if (GetIconInfo(hIcon, &iconInfo) && iconInfo.fIcon == TRUE)
			{
				iconBitmapHandle.pBitmapIcon = Gdiplus::Bitmap::FromHBITMAP(iconInfo.hbmColor, NULL);
				if (iconBitmapHandle.pBitmapIcon != nullptr)
				{
					Gdiplus::BitmapData bitmapData = {};
					Gdiplus::Rect rcImage(0, 0, iconBitmapHandle.pBitmapIcon->GetWidth(), iconBitmapHandle.pBitmapIcon->GetHeight());
					iconBitmapHandle.pBitmapIcon->LockBits(&rcImage, Gdiplus::ImageLockModeRead, iconBitmapHandle.pBitmapIcon->GetPixelFormat(), &bitmapData);
					iconBitmapHandle.pBitmapArgb = new Gdiplus::Bitmap(bitmapData.Width, bitmapData.Height, bitmapData.Stride, PixelFormat32bppARGB, (BYTE*)bitmapData.Scan0);
					if (iconBitmapHandle.pBitmapArgb != nullptr)
					{
						m_iconBitmapHandleMap.emplace(m_hIcon, iconBitmapHandle);
					}
					iconBitmapHandle.pBitmapIcon->UnlockBits(&bitmapData);
				}
			}
		}
		return iconBitmapHandle;
	}
	void MemoryDoubleBuffer(HDC hDC)
	{
		CRect rc = {};
		GetClientRect(&rc);
		Gdiplus::Bitmap bitmapMem(rc.Width(), rc.Height());
		Gdiplus::Graphics graphicsMem(&bitmapMem);
		
		graphicsMem.Clear(Gdiplus::Color(0, 255, 255, 255)); 
		graphicsMem.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
		
		PaintBackground(graphicsMem, rc);
		PaintTitleBar(graphicsMem, rc);

		Gdiplus::Graphics graphics(hDC);
		Gdiplus::CachedBitmap cachedBmp(&bitmapMem, &graphics);
		graphics.DrawCachedBitmap(&cachedBmp, 0, 0);

		Gdiplus::Image* btnokImg = Gdiplus::Image::FromFile(this->btnokImg.c_str());
		Gdiplus::Graphics g(GetDlgItem(IDOK)->GetWindowDC()->m_hDC);
		g.DrawImage(btnokImg, 0, 0);
		delete btnokImg;
	}
	void PaintBackground(Gdiplus::Graphics& graphicsMem, const CRect& rc)
	{
		Gdiplus::Image* bg = Gdiplus::Image::FromFile(bgImg.c_str());
		if (bg != nullptr)
		{
			if (bg->GetLastStatus() == Gdiplus::Ok)
			{
				graphicsMem.DrawImage(bg, 0, 0, rc.Width(), rc.Height());
			}
			else
			{
				Gdiplus::SolidBrush bgBrush(Gdiplus::Color(60, 90, 20));
				graphicsMem.FillRectangle(&bgBrush, rc.left, rc.top, rc.Width(), rc.Height());
			}
			delete bg;
		}
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

		Gdiplus::SolidBrush maxBoxBrush(Gdiplus::Color(100, 20, 20, 20));
		graphicsMem.FillRectangle(&maxBoxBrush, rc.right - BORDER_SIZE - 10, rc.top + BORDER_SIZE, 10, 10);

		if ((m_iconBitmapHandleMap.find(m_hIcon) != m_iconBitmapHandleMap.end()) 
			&& (m_iconBitmapHandleMap.at(m_hIcon).pBitmapArgb != nullptr))
		{
			graphicsMem.DrawImage(m_iconBitmapHandleMap.at(m_hIcon).pBitmapArgb, 0, 0, m_titleBarHeight, m_titleBarHeight);
		}
		Gdiplus::FontFamily  fontFamily(L"Times New Roman");
		Gdiplus::Font        font(&fontFamily, 28, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
		Gdiplus::PointF      pointF(m_titleBarHeight + 1.0f, 0.0f);
		Gdiplus::SolidBrush  textBrush(Gdiplus::Color(255, 0, 0, 255));
		graphicsMem.DrawString(L"TitleBar", -1, &font, pointF, &textBrush);
	}
	void NotifyUpdate()
	{
		RedrawWindow();
	}
public:
	std::wstring bgImg = AToW(GetAppDir() + "\\res\\bg.png");
	std::wstring btnokImg = AToW(GetAppDir() + "\\res\\btnok.png");
public:
	void ShowOrHideWindow()
	{
		if (IsWindowVisible())
		{
			ShowWindow(SW_HIDE);
		}
		else
		{
			ShowWindow(SW_SHOW);
			BringWindowToTop();
		}
	}
protected:
	CCustomButton m_btnOk;
	CCustomButton m_btnCancel;
};
