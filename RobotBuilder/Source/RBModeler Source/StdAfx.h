// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__6AB1EB60_3202_44DB_B8C8_66AC8762B663__INCLUDED_)
#define AFX_STDAFX_H__6AB1EB60_3202_44DB_B8C8_66AC8762B663__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxtempl.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <typeinfo.h>		// for RTTI

#define N_MAX_FILENAME_LENGTH	255
#define INITIAL_WTK_BACKGROUND_COLOR RGB(125, 158, 192)
#define WTK_LICENSE_AVAILABLE

#define WTK_MIN .005f  // WTK's smallest number is WTFUZZ = .004, but using that as
	// the absolute minimum can result in roundoff problems that get numbers smaller
	// than .004 - so create a minimum a little bit bigger than that.

#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6AB1EB60_3202_44DB_B8C8_66AC8762B663__INCLUDED_)
