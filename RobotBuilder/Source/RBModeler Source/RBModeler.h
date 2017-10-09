// RBModeler.h : main header file for the RBModeler application
//

#if !defined(AFX_RBModeler_H__B0177665_F1C6_490F_8507_64FA95E4FD29__INCLUDED_)
#define AFX_RBModeler_H__B0177665_F1C6_490F_8507_64FA95E4FD29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRBModelerApp:
// See RBModeler.cpp for the implementation of this class
//

class CRBModelerApp : public CWinApp
{
public:
	CRBModelerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRBModelerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRBModelerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RBModeler_H__B0177665_F1C6_490F_8507_64FA95E4FD29__INCLUDED_)
