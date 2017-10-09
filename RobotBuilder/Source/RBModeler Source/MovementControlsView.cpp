// MovementControlsView.cpp : implementation file
//

#include "stdafx.h"
#include "RBModeler.h"
#include "MovementControlsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMovementControlsView

IMPLEMENT_DYNCREATE(CMovementControlsView, CScrollView)

CMovementControlsView::CMovementControlsView()
{
}

CMovementControlsView::~CMovementControlsView()
{
	m_dlgMovementControls.DestroyWindow ();
}


BEGIN_MESSAGE_MAP(CMovementControlsView, CScrollView)
	//{{AFX_MSG_MAP(CMovementControlsView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMovementControlsView drawing

void CMovementControlsView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

//	m_dlgMovementControls.ShowWindow (SW_SHOW);
}

/////////////////////////////////////////////////////////////////////////////
// CMovementControlsView diagnostics

#ifdef _DEBUG
void CMovementControlsView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMovementControlsView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMovementControlsView message handlers

int CMovementControlsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect (0, 0, 100, 100);

//	((CWnd) m_dlgMovementControls).Create 
//		(NULL, NULL, WS_VISIBLE, &rect, this, 0, NULL);

	BOOL bReturn = m_dlgMovementControls.Create (IDD_MOVEMENT_CONTROLS, this);
	ASSERT (bReturn);

	return 0;
}



BOOL CMovementControlsView::OnEraseBkgnd(CDC* pDC) 
{
	COLORREF crDialogBackground = ::GetSysColor (COLOR_3DFACE);
	CBrush brushBackground (crDialogBackground);

	CRect rectClient;
	GetClientRect (rectClient);
	pDC->FillRect (rectClient, &brushBackground);

	
	// Return 0 to indicate that this function completed the erase
	return 0;
	//return CView::OnEraseBkgnd(pDC);
}

void CMovementControlsView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	CRect rectDialog;

	m_dlgMovementControls.GetClientRect (rectDialog);

	this->SetScrollSizes (MM_TEXT, CSize (rectDialog.Width (), rectDialog.Height ()));

}

CRBModelerDoc* CMovementControlsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRBModelerDoc)));
	return (CRBModelerDoc*)m_pDocument;
}

CModelListView* CMovementControlsView::GetModelListView()
{
	return GetDocument ()->GetModelListView ();
}


void CMovementControlsView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// todo: set a state variable to make this more efficient when entering the view window
	// by watching for non-client mousemoves/ client mousemoves
		
	// Note this only captures mouse events in the view outside the dialog box.
	m_dlgMovementControls.RefreshPrimitiveComboBox ();
	
	CScrollView::OnMouseMove(nFlags, point);
}
