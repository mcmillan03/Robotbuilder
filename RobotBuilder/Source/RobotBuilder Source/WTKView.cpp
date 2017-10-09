// WTKView.cpp : implementation of the CWTKView class
//

#include "stdafx.h"
#include "DMViewer.h"

#include "DMViewerDoc.h"
#include "WTKView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWTKView

IMPLEMENT_DYNCREATE(CWTKView, CView)

BEGIN_MESSAGE_MAP(CWTKView, CView)
	//{{AFX_MSG_MAP(CWTKView)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWTKView construction/destruction

CWTKView::CWTKView()
{
	// TODO: add construction code here

}

CWTKView::~CWTKView()
{
}

BOOL CWTKView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWTKView drawing

void CWTKView::OnDraw(CDC* pDC)
{
	CDMViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CWTKView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CRect rectPlacement;
	GetWindowRect (&rectPlacement);
	ScreenToClient (rectPlacement);

#ifdef WTK_LICENSE_AVAILABLE
	// design: this snippet should probably be somewhere else so because the window
	// isn't created by the time of the first initial update
	if (m_wndWTK.GetSafeHwnd () == NULL)
	{
		if (!m_wndWTK.Create (NULL, "WTKBase", WS_VISIBLE | WS_CHILD, rectPlacement,
			this, 0))
			AfxMessageBox ("WTK window create failed!", MB_OK);
		// build current scenegraph
		m_WTKGraphics.BuildBaseSceneGraph ();
		// Show the current environment (intitial default)
		m_WTKGraphics.CreateEnvironmentNode (GetDocument ()->GetEnvironmentData ());
		// Show initial articulation
		m_WTKGraphics.CreateArticulationNodes (dynamic_cast <CdmvArticulationData*> (GetDocument ()->GetSystemData ()));
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CWTKView diagnostics

#ifdef _DEBUG
void CWTKView::AssertValid() const
{
	CView::AssertValid();
}

void CWTKView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDMViewerDoc* CWTKView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDMViewerDoc)));
	return (CDMViewerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWTKView message handlers
void CWTKView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

void CWTKView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	TRACE ("CWTKView Size\n");
	
	if(m_wndWTK.GetSafeHwnd ())
	{
		HWND hwnd;
		hwnd = WTwindow_getidx(WTuniverse_getwindows());
		if(hwnd) ::SendMessage(hwnd,WM_SIZE,0,MAKELPARAM(cx,cy));

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

void CWTKView::OnMove(int x, int y) 
{
	CView::OnMove(x, y);
	
	
	if(m_wndWTK.GetSafeHwnd ())
	{
		HWND hwnd;
		hwnd = WTwindow_getidx(WTuniverse_getwindows());
		if(hwnd) ::SendMessage(hwnd,WM_MOVE,0,MAKELPARAM(x,y));
	}
	
}

void CWTKView::OnPaint() 
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
	
	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages
}


// direct key to doc to give to control dll
void CWTKView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CDMViewerDoc* pDoc = dynamic_cast <CDMViewerDoc*> (GetDocument ());
	ASSERT (pDoc);

	pDoc->KeyDown (nChar, nRepCnt, nFlags);
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CWTKView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CView::OnEraseBkgnd(pDC);
   return 1;
}
