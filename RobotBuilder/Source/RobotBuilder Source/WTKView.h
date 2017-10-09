// WTKView.h : interface of the CWTKView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WTKVIEW_H__6BC5BDEF_EC4B_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_WTKVIEW_H__6BC5BDEF_EC4B_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "dmvWTKToolkit.h"
#include "WndWTK.h"
//#include "PlayerToolkit.h"	// Added by ClassView
#include "WTKGraphics.h"
#include "DMViewerDoc.h"

class CWTKView : public CView
{
protected: // create from serialization only
	CWTKView();
	DECLARE_DYNCREATE(CWTKView)

// Attributes
public:
	CDMViewerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWTKView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
//	CPlayerToolkit m_PlayerToolkit;
//	CdmvWTKToolkit m_GraphicalViewToolkit;
	CWTKGraphics m_WTKGraphics;
	virtual ~CWTKView();
	CWndWTK m_wndWTK;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CWTKView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WTKView.cpp
inline CDMViewerDoc* CWTKView::GetDocument()
   { return (CDMViewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WTKVIEW_H__6BC5BDEF_EC4B_11D3_A7DF_0000E8978554__INCLUDED_)
