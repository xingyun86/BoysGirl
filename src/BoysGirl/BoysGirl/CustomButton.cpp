// CustomButton.cpp : implementation file
//

#include "pch.h"
#include "CustomButton.h"


// CCustomButton

IMPLEMENT_DYNAMIC(CCustomButton, CButton)

CCustomButton::CCustomButton()
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CCustomButton::~CCustomButton()
{
}


BEGIN_MESSAGE_MAP(CCustomButton, CButton)
END_MESSAGE_MAP()



// CCustomButton message handlers




void CCustomButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  Add your code to draw the specified item
	int nOldBkMode = SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);

	UINT uStyle = DFCS_BUTTONPUSH;

	// This code only works with buttons.
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

	// If drawing selected, add the pushed style to DrawFrameControl.
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		//鼠标被按下
		uStyle |= DFCS_PUSHED;
	}
	else
	{
		//鼠标不操作或被弹起
	}
	if ((lpDrawItemStruct->itemState & ODS_SELECTED) && (lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{ 
		//选中了本控件,高亮边框

	}
	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) && (lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		//控制的选中状态结束,去掉边框
	}
	// Draw the button frame.
	//::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, DFC_BUTTON, uStyle);
	{
		std::wstring btnokImgFile = AToW(GetAppDir() + "\\res\\btnbg.png");
		Gdiplus::Graphics g(lpDrawItemStruct->hDC);
		Gdiplus::Image* btnokImg = Gdiplus::Image::FromFile(btnokImgFile.c_str());
		if (btnokImg != nullptr)
		{
			if (btnokImg->GetLastStatus() == Gdiplus::Ok)
			{
				//Gdiplus::SolidBrush borderBrush(Gdiplus::Color(100, 20, 20, 20));
				//g.FillRectangle(&borderBrush, lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom);
				g.DrawImage(btnokImg, lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom);
			}
			delete btnokImg;
		}
	}
	// Get the button's text.
	CString strText;
	GetWindowText(strText);
	// Draw the button text using the text color red.
	COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255, 0, 0));
	::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(),	&lpDrawItemStruct->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	::SetTextColor(lpDrawItemStruct->hDC, crOldColor);

	SetBkMode(lpDrawItemStruct->hDC, nOldBkMode);
}

void CCustomButton::PreSubclassWindow()
{
	CButton::PreSubclassWindow();

	ModifyStyle(0, BS_OWNERDRAW); 
	ModifyStyleEx(0, WS_EX_TRANSPARENT);
}
