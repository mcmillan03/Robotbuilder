#if !defined(AFX_MOVEMENTCONTROLSVIEW_H__A9B04AD4_B17F_4798_8938_8C2FEEC14EA7__INCLUDED_)
#define AFX_MOVEMENTCONTROLSVIEW_H__A9B04AD4_B17F_4798_8938_8C2FEEC14EA7__INCLUDED_

#include "DlgMovementControls.h"	// Added by ClassView
#include "RBModelerDoc.h"
#include "ModelListView.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MovementControlsView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMovementControlsView view

class CMovementControlsView : public CScrollView
{
protected:
	CMovementControlsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMovementControlsView)

// Attributes
public:
	CRBModelerDoc* GetDocument();

// Operations
public:
	CModelListView* GetModelListView ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMovementControlsView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMovementControlsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	CDlgMovementControls m_dlgMovementControls;
	//{{AFX_MSG(CMovementControlsView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVEMENTCONTROLSVIEW_H__A9B04AD4_B17F_4798_8938_8C2FEEC14EA7__INCLUDED_)
