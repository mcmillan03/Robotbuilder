// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6BC5BDE9_EC4B_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_STDAFX_H__6BC5BDE9_EC4B_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxtempl.h>		// added by me -- template support
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <typeinfo.h>		// for RTTI

#endif // _AFX_NO_AFXCMN_SUPPORT

#define WTK_LICENSE_AVAILABLE
#define INITIAL_WTK_BACKGROUND_COLOR RGB(125, 158, 192)

#define WTK_MIN .005f  // WTK's smallest number is WTFUZZ = .004, but using that as
	// the absolute minimum can result in roundoff problems that get numbers smaller
	// than .004 - so create a minimum a little bit bigger than that.

#define X 0
#define Y 1
#define Z 2
#define W 3

#ifndef PI
#define PI 3.1415926535
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6BC5BDE9_EC4B_11D3_A7DF_0000E8978554__INCLUDED_)
