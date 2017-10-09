// ModelView.cpp : implementation of the CModelView class
//

#include "stdafx.h"
#include "RBModeler.h"

#include "RBModelerDoc.h"
#include "ModelView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelView

IMPLEMENT_DYNCREATE(CModelView, CView)

BEGIN_MESSAGE_MAP(CModelView, CView)
	//{{AFX_MSG_MAP(CModelView)
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelView construction/destruction

CModelView::CModelView()
{
	// TODO: add construction code here

}

CModelView::~CModelView()
{
}

BOOL CModelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CModelView drawing

void CModelView::OnDraw(CDC* pDC)
{
	CRBModelerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CModelView diagnostics

#ifdef _DEBUG
void CModelView::AssertValid() const
{
	CView::AssertValid();
}

void CModelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRBModelerDoc* CModelView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRBModelerDoc)));
	return (CRBModelerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CModelView message handlers

void CModelView::OnMove(int x, int y) 
{
	CView::OnMove(x, y);
	
	if(m_wndGraphic.GetSafeHwnd ())
	{
		HWND hwnd;
		hwnd = WTwindow_getidx(WTuniverse_getwindows());
		if(hwnd) ::SendMessage(hwnd,WM_MOVE,0,MAKELPARAM(x,y));


		// When the CView window is resized, WTK also needs to know where the new window
		// starts at.  I tell it with a Move message.  Otherwise, WTK gets confused.  Specifically,
		// if I don't send this message, it thinks the mouse is in another window (and
		// consequently doesn't do camera control) in new regions of the window exposed by
		// changing the window size.
		CRect rectWindow;
		GetWindowRect(rectWindow);
		if (hwnd) ::SendMessage (hwnd, WM_MOVE, 0, MAKELPARAM(rectWindow.left, rectWindow.top));	
	
	}
}

void CModelView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if(m_wndGraphic.GetSafeHwnd ())
	{
		HWND hwnd;
		hwnd = WTwindow_getidx(WTuniverse_getwindows());
		if(hwnd) ::SendMessage(hwnd,WM_SIZE,0,MAKELPARAM(cx,cy));
	}		
}

void CModelView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	CRect rectPlacement;
	GetWindowRect (&rectPlacement);
	ScreenToClient (rectPlacement);

#ifdef WTK_LICENSE_AVAILABLE
	if (m_wndGraphic.GetSafeHwnd () == NULL)
	{
		if (!m_wndGraphic.Create (NULL, "WTKBase", WS_VISIBLE | WS_CHILD, rectPlacement,
			this, 0))
			AfxMessageBox ("WTK window create failed!", MB_OK);
		// build current scenegraph
		CRBModelerRBMGraphicView::InitializeScene ();
		// Add the current model
		CRBModelerRBMGraphicView::LoadNewModel (GetDocument ()->GetModel ());
	}
#endif
}

CWndWTK* CModelView::GetWTKWnd()
{
	return &m_wndGraphic;
}

void CModelView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Periodically, the WTK window gets confused about where it really is.  This
	// is an attempt to remind it.
	CRect rectWindow;
	GetWindowRect(rectWindow);
	HWND hwnd;
	hwnd = WTwindow_getidx(WTuniverse_getwindows());
	if (hwnd) ::SendMessage (hwnd, WM_MOVE, 0, MAKELPARAM(rectWindow.left, rectWindow.top));
	if (hwnd) ::SendMessage(hwnd,WM_SIZE,0,MAKELPARAM(rectWindow.Width (), rectWindow.Height ()));
	
	// Do not call CView::OnPaint() for painting messages
}
