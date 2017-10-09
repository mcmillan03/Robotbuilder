// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DMViewer.h"

#include <crtdbg.h>

#include "MainFrm.h"
#include "DMTreeView.h"
#include "WTKView.h"
#include "IOView.h"
#include "DMViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_VIEW_TOGGLESTATE, OnViewTogglestate)
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Global help commands
// todo:
// Uncomment the next four to enable the context sensitive help
// I disabled them because I ran out of time to implement the help
//	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
//	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
//	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
//	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)

//	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
//	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SIM_TIME,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

BOOL g_bEditState = TRUE;
BOOL g_bClosingByRequest = FALSE;

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	g_bEditState = TRUE;
}

CMainFrame::~CMainFrame()
{
}

void ExitFunction ()
{
	if (!g_bEditState && !g_bClosingByRequest)
		AfxMessageBox ("An unstable condition has occurred in DynaMechs.\n\
A temporary copy of the articulation has been saved in temp.dm.\n\
Please review the parameters, environment, and control algorithms to make sure\n\
the simulation remains stable.\n\
The application will now terminate.");
}



int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Note: there are quite a few reported memory leaks.  They seem to be from STL, WTK, and
	// DynaMechs.
	//	_CrtSetBreakAlloc (543);
	atexit (ExitFunction);

   // Workaround for bug in strtok
   // Crashes if first call made to strtok uses first arg of NULL.
   strtok("","");
   
   if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
/*
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}
*/

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar)/* ||
		!m_wndReBar.AddBar(&m_wndDlgBar)*/)
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CDMTreeView), CSize(200, 200), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CWTKView), CSize(200, 200), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

//	m_wndSplitter.GetPane (0, 0)->ShowWindow (SW_HIDE);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
/*
CWTKView* CMainFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CWTKView* pView = DYNAMIC_DOWNCAST(CWTKView, pWnd);
	return pView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.

	CWTKView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CMainFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.
	CWTKView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CWTKView,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}
*/

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnTimer(nIDEvent);
}



void CMainFrame::OnViewTogglestate() 
{
	g_bEditState = !g_bEditState;

	if (!g_bEditState)
	{
		// Clear the selection box (bounding box) from the graphics view.  Note currently
		// selected item stored in the tree view class
		((CDMViewerDoc*) this->GetActiveDocument ())->GetTreeView ()->ClearBoundingBoxOnSelectedItem ();

		m_wndSplitter.ReplaceView(0,0,RUNTIME_CLASS(CIOView));
		((CDMViewerDoc*) this->GetActiveDocument ())->OnViewTogglestate ();
	}
	else
	{
		m_wndSplitter.ReplaceView(0,0,RUNTIME_CLASS(CDMTreeView));
		((CDMViewerDoc*) this->GetActiveDocument ())->OnViewTogglestate ();
	}
	
}

void CMainFrame::OnClose() 
{
	g_bClosingByRequest = TRUE;
	
	CFrameWnd::OnClose();
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
   TRACE ("ERASE MAINFRAME\n");
   
	return CFrameWnd::OnEraseBkgnd(pDC);
}

// On Dr. Orin's (slower) computer, the toolbar would not always update the state of
// the toolbar buttons completely.  The toolbar updates happen in idle time, and they
// might not have had enough time to repaint.  This forces a redraw.
void CMainFrame::InvalidateToolBar()
{
	m_wndToolBar.Invalidate ();
}
