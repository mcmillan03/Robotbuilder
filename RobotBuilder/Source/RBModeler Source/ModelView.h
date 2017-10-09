// ModelView.h : interface of the CModelView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELVIEW_H__183C9BC6_70B2_4D8C_A385_E415766AFCF5__INCLUDED_)
#define AFX_MODELVIEW_H__183C9BC6_70B2_4D8C_A385_E415766AFCF5__INCLUDED_

#include "RBModelerRBMGraphicView.h"	// Added by ClassView
#include "WndWTK.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRBModelerDoc;

class CModelView : public CView
{
protected: // create from serialization only
	CModelView();
	DECLARE_DYNCREATE(CModelView)

// Attributes
public:
	CRBModelerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	CWndWTK* GetWTKWnd ();
	virtual ~CModelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CWndWTK m_wndGraphic;

// Generated message map functions
protected:
	//{{AFX_MSG(CModelView)
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ModelView.cpp
inline CRBModelerDoc* CModelView::GetDocument()
   { return (CRBModelerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELVIEW_H__183C9BC6_70B2_4D8C_A385_E415766AFCF5__INCLUDED_)
