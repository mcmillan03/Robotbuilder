// WndWTK.cpp : implementation file
//

#include "stdafx.h"

#include "WndWTK.h"
#include "RBModelerRBMGraphicView.h"
#include "RBModeler.h"
#include "MainFrm.h"
#include "ModelView.h"
#include "RBModelerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWndWTK


CWndWTK::CWndWTK()
{
	m_pCameraControl = NULL;
	m_bWtkInitialized = FALSE;
}

CWndWTK::~CWndWTK()
{
	if (m_pCameraControl)
		delete m_pCameraControl;
}


BEGIN_MESSAGE_MAP(CWndWTK, CWnd)
	//{{AFX_MSG_MAP(CWndWTK)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndWTK message handlers

void CWndWTK::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	

}

void CWndWTK::InitializeWTKWindow()
{
	WTnode *root;
	/* Do this WTK initializing stuff the first time this routine
	 * is called.  This routine will get called once for each document,
	 * so it's important to only initialize WTK once.
	 */

	/* Don't use WTK's standard window, use this view */
	WTinit_usewindow (this->GetSafeHwnd());

	/* Now it's safe to initialize the universe */
	WTuniverse_new (WTDISPLAY_DEFAULT, WTWINDOW_DEFAULT);
	root = WTuniverse_getrootnodes();

	/* Don't use WTK's message pump, use MFC's */
	WTuniverse_setoption (WTOPTION_USEWTPUMP, FALSE);


	WTwindow_sethithervalue (WTuniverse_getwindows (), 0.05f);

	/* Initialize the mouse sensor */
	WTsensor* pMouse = WTmouse_new ();
	WTviewpoint_addsensor (WTuniverse_getviewpoints(), pMouse);
	WTsensor_setsensitivity(WTuniverse_getsensors(),0.5f*WTnode_getradius(root));
	
	// Set the foreground drawing function to draw axes
	WTwindow_setfgactions (WTuniverse_getwindows(), 
		CRBModelerRBMGraphicView::WTKFGDrawCallback);

	WTwindow_zoomviewpoint(WTuniverse_getwindows());

	WTwindow_setviewangle (WTuniverse_getwindows(), (float) PI/20);

	// Set the background color of the universe
	WTuniverse_setbgrgb (GetRValue (INITIAL_WTK_BACKGROUND_COLOR),
		GetGValue (INITIAL_WTK_BACKGROUND_COLOR), GetBValue (INITIAL_WTK_BACKGROUND_COLOR));

	// Set up my own view control
	m_pCameraControl = new CCameraControl (pMouse, WTuniverse_getviewpoints ());
	WTsensor_setupdatefn (WTuniverse_getsensors (), MyWTKMouseMove); 

	/* Always call this before WTuniverse_go() or ...go1() */
	WTuniverse_ready ();
	WTuniverse_go1 ();

	// WTK has been initialized now
	m_bWtkInitialized = TRUE;
}


void CWndWTK::MyWTKMouseMove (WTsensor* wtSensor)
{


	WTp3 wtp3Translation;
	WTq wtqRotation;

	WTp3_init(wtp3Translation);
	WTq_init(wtqRotation);
	
	// Read the current mouse state
	WTmouse_rawupdate(wtSensor);
	// Determine window mouse is in
	WTwindow* wtWindow; 
	wtWindow = WTmouse_whichwindow(wtSensor);
	if (wtWindow == NULL) // Then not in WTK window
	{
		WTsensor_setrecord(wtSensor, wtp3Translation, wtqRotation);

		return;
	}

	// Get window height and width
	int nWndPosX, nWndPosY, nWndWidth, nWndHeight;
	WTwindow_getposition(wtWindow, &nWndPosX, &nWndPosY, &nWndWidth, &nWndHeight);
	// Get raw x and y mouse values in screen coordinates
	WTmouse_rawdata* wtmouseRawData;
	wtmouseRawData = (WTmouse_rawdata *)WTsensor_getrawdata(wtSensor);

	// Check button states
	int nButtonData;
	BOOL flagLeftButton, flagRightButton;
	nButtonData = WTsensor_getmiscdata (wtSensor);
	flagLeftButton = nButtonData & WTMOUSE_LEFTDOWN;
	flagRightButton = nButtonData & WTMOUSE_RIGHTDOWN;

	// Get a pointer to the CWndWTK class
	CRBModelerApp* pApp = (CRBModelerApp*)AfxGetApp();
	CMainFrame *pFrameWnd = (CMainFrame*)pApp->m_pMainWnd;
	CRBModelerDoc* pDoc = (CRBModelerDoc*)pFrameWnd->GetActiveDocument ();
	CModelView* pModelView = (CModelView*) pDoc->GetModelView ();

	if (flagLeftButton | flagRightButton)
	{
		if (pDoc->GetCameraData ()->GetViewInPanMode ())
			pModelView->m_wndGraphic.m_pCameraControl->UpdatePanView (nWndPosX, nWndPosY, nWndWidth, nWndHeight,
				flagLeftButton, flagRightButton, wtmouseRawData->pos[X], wtmouseRawData->pos[Y]);
		else
		{
			// Then examine, determine if using viewport frame for update
			if (pDoc->GetCameraData ()->GetUseViewportFrameForExamineView ())
				pModelView->m_wndGraphic.m_pCameraControl->UpdateExamineView2 (nWndPosX, nWndPosY, nWndWidth, nWndHeight,
					flagLeftButton, flagRightButton, wtmouseRawData->pos[X], wtmouseRawData->pos[Y]);
			else
				pModelView->m_wndGraphic.m_pCameraControl->UpdateExamineView (nWndPosX, nWndPosY, nWndWidth, nWndHeight,
					flagLeftButton, flagRightButton, wtmouseRawData->pos[X], wtmouseRawData->pos[Y]);
		}
	}

}

BOOL CWndWTK::DestroyWindow() 
{
	// before deleting the universe, kill the timer
	KillTimer (m_nTimerID);

	WTuniverse_delete ();

	return CWnd::DestroyWindow();
}

void CWndWTK::OnTimer(UINT nIDEvent) 
{
	WTuniverse_go1 ();
	
	CWnd::OnTimer(nIDEvent);
}

void CWndWTK::OnDestroy() 
{
	CWnd::OnDestroy();
	
	// before deleting the universe, kill the timer
	KillTimer (m_nTimerID);

	WTuniverse_delete ();
	
}

int CWndWTK::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	InitializeWTKWindow ();

	m_nTimerID = SetTimer (1, 70, NULL);

	return 0;
}

void CWndWTK::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect (&rect);

	// Todo: figure out why I have to explicitly tell this guy to move
	MoveWindow (0, 0, cx, cy, TRUE);
	
}

void CWndWTK::SetViewpointOrientation(WTq wtqQuat)
{
	WTviewpoint* wtviewpoint = WTuniverse_getviewpoints ();

	WTviewpoint_setorientation (wtviewpoint, wtqQuat);
	
	WTwindow_zoomviewpoint (WTuniverse_getwindows());

	CRBModelerRBMGraphicView::UpdateCamera (TRUE);

}

// Zooms the viewpoint - but routes the call through the normal camera control,
// so the camera control states will be updated.
void CWndWTK::ZoomViewpoint(BOOL bZoomIn)
{
	// Get a pointer to the CWndWTK class
	CRBModelerApp* pApp = (CRBModelerApp*)AfxGetApp();
	CMainFrame *pFrameWnd = (CMainFrame*)pApp->m_pMainWnd;
	CRBModelerDoc* pDoc = (CRBModelerDoc*)pFrameWnd->GetActiveDocument ();
	CModelView* pModelView = (CModelView*) pDoc->GetModelView ();

	// The actual window values don't matter, becuase this is a constant zoom.
	// The zoom is set to zoom in at the rate equal when the mouse is 25% down
	// the window and zoom out at the rate equal when the mouse is 75% down
	double dMousePosY;
	if (bZoomIn)
		dMousePosY = 48;
	else
		dMousePosY = 52;
	if (pDoc->GetCameraData ()->GetViewInPanMode ())
		pModelView->m_wndGraphic.m_pCameraControl->UpdatePanView (0, 0, 100, 100,
			FALSE, TRUE, 50, dMousePosY);
	else
	{
		// Then examine, determine if using viewport frame for update
		if (pDoc->GetCameraData ()->GetUseViewportFrameForExamineView ())
			pModelView->m_wndGraphic.m_pCameraControl->UpdateExamineView2 (0, 0, 100, 100,
			FALSE, TRUE, 50, dMousePosY);
		else
			pModelView->m_wndGraphic.m_pCameraControl->UpdateExamineView (0, 0, 100, 100,
			FALSE, TRUE, 50, dMousePosY);
	}
}


BOOL CWndWTK::IsWtkInitialized() const
{
	return m_bWtkInitialized;
}