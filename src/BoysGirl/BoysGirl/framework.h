#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars


#include <afxsock.h>            // MFC socket extensions


#include <gdiplus.h>
#pragma comment(lib, "gdiplus")

#include <string>
#include <unordered_map>

#define WM_USER_NOTIFYICON WM_USER + WM_NOTIFY + 1

#if !defined(UNICODE) && !defined(_UNICODE)
#define TSTRING std::string
#else
#define TSTRING std::wstring
#endif
template <typename ...Args>
__inline static std::string format_string(const char* format, Args... args) {
    char buffer[BUFSIZ] = { 0 };
    size_t newlen = _snprintf(buffer, BUFSIZ, format, args...);
    if (newlen > BUFSIZ)
    {
        std::vector<char> newbuffer(newlen + 1);
        snprintf(newbuffer.data(), newlen, format, args...);
        return std::string(newbuffer.data());
    }
    return buffer;
}
template <typename ...Args>
__inline static std::wstring format_string(const wchar_t* format, Args... args) {
    wchar_t buffer[BUFSIZ] = { 0 };
    size_t newlen = _snwprintf(buffer, BUFSIZ, format, args...);
    if (newlen > BUFSIZ)
    {
        std::vector<wchar_t> newbuffer(newlen + 1);
        _snwprintf(newbuffer.data(), newlen, format, args...);
        return std::wstring(newbuffer.data());
    }
    return buffer;
}
//通用版将wstring转化为string
__inline std::string WToA(const std::wstring& ws, unsigned int cp = CP_ACP)
{
    if (!ws.empty())
    {
        std::string s(WideCharToMultiByte(cp, 0, ws.data(), -1, NULL, 0, NULL, NULL), ('\0'));
        return s.substr(0, WideCharToMultiByte(cp, 0, ws.c_str(), -1, (LPSTR)s.data(), (int)s.size(), NULL, NULL) - 1);
    }
    return ("");
}
//通用版将string转化为wstring
__inline std::wstring AToW(const std::string& s, unsigned int cp = CP_ACP)
{
    if (!s.empty())
    {
        std::wstring ws(MultiByteToWideChar(cp, 0, s.data(), -1, NULL, 0), (L'\0'));
        return ws.substr(0, MultiByteToWideChar(cp, 0, s.data(), -1, (LPWSTR)ws.data(), (int)ws.size()) - 1);
    }
    return (L"");
}
__inline static
#if !defined(UNICODE) && !defined(_UNICODE)
std::string
#else
std::wstring
#endif
AToT(const std::string& str)
{
#if !defined(UNICODE) && !defined(_UNICODE)
    return str;
#else
    return AToW(str);
#endif
}
__inline static
#if !defined(UNICODE) && !defined(_UNICODE)
std::string
#else
std::wstring
#endif
WToT(const std::wstring& wstr)
{
#if !defined(UNICODE) && !defined(_UNICODE)
    return WToA(wstr);
#else
    return wstr;
#endif
}
__inline static std::string TToA(
    const
#if !defined(UNICODE) && !defined(_UNICODE)
    std::string
#else
    std::wstring
#endif
    & tsT)
{
#if !defined(UNICODE) && !defined(_UNICODE)
    return tsT;
#else
    return WToA(tsT);
#endif
}
__inline static std::wstring TToW(
    const
#if !defined(UNICODE) && !defined(_UNICODE)
    std::string
#else
    std::wstring
#endif
    & tsT)
{
#if !defined(UNICODE) && !defined(_UNICODE)
    return AToW(tsT);
#else
    return tsT;
#endif
}
#define WToUTF8(X) WToA(X, CP_UTF8)
#define UTF8ToW(X) AToW(X, CP_UTF8)
#define AToUTF8(X) WToUTF8(AToW(X))
#define UTF8ToA(X) WToA(UTF8ToW(X))
//将From编码转化为To编码
__inline static std::string CodePage_FromTo(const std::string& str,
    unsigned int from_codepage, unsigned int to_codepage)
{
    return WToA(AToW(str, from_codepage), to_codepage);
}
//将UTF8转化为ANSI
__inline static std::string UTF8ToANSI(const std::string& str)
{
    return CodePage_FromTo(str, CP_UTF8, CP_ACP);
}
//将ANSI转化为UTF8
__inline static std::string ANSIToUTF8(const std::string& str)
{
    return CodePage_FromTo(str, CP_ACP, CP_UTF8);
}

__inline static std::string GetAppExe()
{
    CHAR tFilePath[MAX_PATH] = { 0 };
    GetModuleFileNameA(GetModuleHandleA(NULL), tFilePath, MAX_PATH);
    return tFilePath;
}
__inline static std::string GetAppDir()
{
    auto path = GetAppExe();
    return path.substr(0, path.rfind("\\"));
}

// This macro is the same as IMPLEMENT_OLECREATE, except it passes TRUE
// for the bMultiInstance parameter to the COleObjectFactory constructor.
// We want a separate instance of this application to be launched for
// each automation proxy object requested by automation controllers.
#ifndef IMPLEMENT_OLECREATE2
#define IMPLEMENT_OLECREATE2(class_name, external_name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        AFX_DATADEF COleObjectFactory class_name::factory(class_name::guid, \
                RUNTIME_CLASS(class_name), TRUE, _T(external_name)); \
        const AFX_DATADEF GUID class_name::guid = \
                { l, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };
#endif // IMPLEMENT_OLECREATE2

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


