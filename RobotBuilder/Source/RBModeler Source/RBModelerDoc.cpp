// RBModelerDoc.cpp : implementation of the CRBModelerDoc class
//

#include "stdafx.h"
#include "RBModeler.h"

#include "RBModelerDoc.h"
#include "Model.h"
#include "ParserModel.h"
#include "ModelOutputFile.h"
#include "WndWTK.h"
#include "DlgCameraControl.h"
#include "FindFile.h"
#include "DlgLinkPhysicalProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRBModelerDoc

IMPLEMENT_DYNCREATE(CRBModelerDoc, CDocument)

BEGIN_MESSAGE_MAP(CRBModelerDoc, CDocument)
	//{{AFX_MSG_MAP(CRBModelerDoc)
	ON_COMMAND(ID_PRIMITIVES_ADD_SPHERE, OnPrimitivesAddSphere)
	ON_COMMAND(ID_PRIMITIVES_ADD_BLOCK, OnPrimitivesAddBlock)
	ON_COMMAND(ID_PRIMITIVES_ADD_CONE, OnPrimitivesAddCone)
	ON_COMMAND(ID_PRIMITIVES_ADD_CYLINDER, OnPrimitivesAddCylinder)
	ON_COMMAND(ID_PRIMITIVES_ADD_HEMISPHERE, OnPrimitivesAddHemisphere)
	ON_COMMAND(ID_PRIMITIVES_ADD_TRUNCATEDCONE, OnPrimitivesAddTruncatedcone)
	ON_COMMAND(ID_BUTTON_VIEW_LEFT, OnButtonViewLeft)
	ON_COMMAND(ID_BUTTON_VIEW_BACK, OnButtonViewBack)
	ON_COMMAND(ID_BUTTON_VIEW_BOTTOM, OnButtonViewBottom)
	ON_COMMAND(ID_BUTTON_VIEW_FRONT, OnButtonViewFront)
	ON_COMMAND(ID_BUTTON_VIEW_RIGHT, OnButtonViewRight)
	ON_COMMAND(ID_BUTTON_VIEW_TOP, OnButtonViewTop)
	ON_COMMAND(ID_BUTTON_ZOOM_IN, OnButtonZoomIn)
	ON_COMMAND(ID_BUTTON_ZOOM_OUT, OnButtonZoomOut)
	ON_COMMAND(ID_VIEW_CAMERACONTROL, OnViewCameracontrol)
	ON_COMMAND(ID_BUTTON_HIDE_LOCAL_AXES, OnButtonHideLocalAxes)
	ON_COMMAND(ID_BUTTON_SHOW_LOCAL_AXES, OnButtonShowLocalAxes)
	ON_COMMAND(ID_BUTTON_TOGGLE_AXES, OnButtonToggleAxes)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TOGGLE_AXES, OnUpdateButtonToggleAxes)
	ON_COMMAND(ID_FILE_SETBACKGROUNDCOLOR, OnFileSetbackgroundcolor)
	ON_COMMAND(ID_PROPERTIES_PHYSICALPROPERTIES, OnPropertiesPhysicalproperties)
	ON_COMMAND(ID_VIEW_CAMERALIGHT, OnViewCameralight)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAMERALIGHT, OnUpdateViewCameralight)
	ON_COMMAND(ID_HELP_USERSGUIDE, OnHelpUsersguide)
	ON_COMMAND(ID_HELP_TUTORIAL, OnHelpTutorial)
	ON_COMMAND(ID_BUTTONPAN, OnButtonpan)
	ON_COMMAND(ID_BUTTONEXAMINE, OnButtonexamine)
	ON_UPDATE_COMMAND_UI(ID_BUTTONEXAMINE, OnUpdateButtonexamine)
	ON_UPDATE_COMMAND_UI(ID_BUTTONPAN, OnUpdateButtonpan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRBModelerDoc construction/destruction

CRBModelerDoc::CRBModelerDoc()
{
	m_pModel = NULL;
}

CRBModelerDoc::~CRBModelerDoc()
{
}

BOOL CRBModelerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	// Create a model
	CModel* pNewModel;
	// create a copy of it
	try {
		pNewModel = new CModel;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	m_pModel = pNewModel;

//	// temporarily intialize it with some models
//	CPrimitive* pPrimitive = m_pModel->NewPrimitive (PT_SPHERE);
//	pPrimitive->SetName ("Test Sphere");
//	// end temp intialize
	

	// Update the views
	GetModelListView ()->LoadNewModelAndReset (pNewModel);
	// Need to check if the window exists first, because the first time it
	// is run, this code is called before MFC has drawn the WTK window (so
	// the code can't be run yet).
	if (GetModelView()->GetWTKWnd ()->GetSafeHwnd ())
	{
		CRBModelerRBMGraphicView::InitializeScene ();
		CRBModelerRBMGraphicView::LoadNewModel (m_pModel);
	}

	// Reset the FindFile stuff
	CFindFile::SetCFGFilePath ("");

	// OnNewDocument is called by the framework before the WTK window has been created.  This can't
	// be called before the window is created, otherwise there is an access violation.
	// Note the background color will be initialized to INITIAL_WTK_BACKGROUND_COLOR in
	// the initialization of the CWndWTK class.
	if (GetModelView ()->m_wndGraphic.IsWtkInitialized ())
		WTuniverse_setbgrgb (GetRValue (m_pModel->GetBackgroundColor ()),
			GetGValue (m_pModel->GetBackgroundColor ()), GetBValue (m_pModel->GetBackgroundColor ()));


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRBModelerDoc serialization

void CRBModelerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRBModelerDoc diagnostics

#ifdef _DEBUG
void CRBModelerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRBModelerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRBModelerDoc commands

void CRBModelerDoc::OnPrimitivesAddSphere() 
{
	AddPrimitive (PT_SPHERE);	
}

// Handles adding new primitive
void CRBModelerDoc::AddPrimitive(PrimitiveType thePrimitiveType)
{
//	ASSERT (m_pModel);
	
	// Create the new primvitive in the model
	CPrimitive* pPrimitive = m_pModel->NewPrimitive (thePrimitiveType);
	ASSERT (pPrimitive);

	// Add the primitive to the list view
	GetModelListView ()->AddPrimitive (pPrimitive);
	// Make it known that a state change occurred
	GetModelListView ()->ModelStateChanged ("Add Geometry");

	// Add the primitive to the 3D view
	CRBModelerRBMGraphicView::AddPrimitive (pPrimitive);
}

// returns a pointer to the model list view - it is not saved statically because MFC
// reserves the right to change the pointer to it.
CModelListView* CRBModelerDoc::GetModelListView()
{
	POSITION posView = GetFirstViewPosition ();
	CModelListView* pListView;
	pListView = (CModelListView*) GetNextView (posView);
	ASSERT (pListView);

	return pListView;
}

// This will probably change!!
CModelView* CRBModelerDoc::GetModelView()
{
	POSITION posView = GetFirstViewPosition ();
	CModelView* pModelView;
	// First it gets a pointer to the list view
	GetNextView (posView);
	// Then obtains a pointer to the model view
	pModelView = (CModelView*) GetNextView (posView);
	ASSERT (pModelView);

	return pModelView;
}


void CRBModelerDoc::DeleteContents() 
{
	if (m_pModel)
	{
		delete m_pModel;
		m_pModel = NULL;
	}
	
	CDocument::DeleteContents();
}

CModel* CRBModelerDoc::GetModel()
{
	return m_pModel;
}

void CRBModelerDoc::SetModel(CModel *pModel)
{
	ASSERT (pModel);
		
	// Delete the current model
	// Note that DeleteContents is called by the framework on an open request so
	// the m_pModel will already be deleted by the time it gets here.
	if (m_pModel)
		delete m_pModel;

	// Set the current model
	m_pModel = pModel;
}


BOOL CRBModelerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// Set the FindFile stuff - Need to set this before calling the parser
	// so the parser will lookup in the correct path for the files.  This uses
	// the same code from RobotBuilder, but in this app, this should probably
	// be called SetModelFilePath
	CFindFile::SetCFGFilePath (lpszPathName);

	CParserModel theParser;
	CModel* pModel;
	if (theParser.ParseModelFile (lpszPathName, &pModel))
	{
		// Save the new model as the current model
		SetModel (pModel);
		// Update the views
		GetModelListView ()->LoadNewModelAndReset (pModel);
		// Need to check if the window exists first, because the first time it
		// is run, this code is called before MFC has drawn the WTK window (so
		// the code can't be run yet).
		if (GetModelView()->GetWTKWnd ()->GetSafeHwnd ())
		{
			CRBModelerRBMGraphicView::InitializeScene ();
			CRBModelerRBMGraphicView::LoadNewModel (m_pModel);
		}

		// Set the background color
		WTuniverse_setbgrgb (GetRValue (m_pModel->GetBackgroundColor ()),
			GetGValue (m_pModel->GetBackgroundColor ()), GetBValue (m_pModel->GetBackgroundColor ()));

	}
	else
	{
		// Failed to load the model
		// Initialize to the same state as a new document
		OnNewDocument ();
		// Set the FindFile stuff
		CFindFile::SetCFGFilePath ("");
		// Return false to indicate the document failed to open - this prevents the window
		// title from updating with the filename that failed to open.
		return FALSE;
	}

	// Reset the view
	OnButtonViewFront ();

	
	return TRUE;
}

BOOL CRBModelerDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	CModelOutputFile theFileGenerator;

	if (!theFileGenerator.OutputModelFile (lpszPathName, GetModel ()))
		return FALSE;
	else
	{
		// Set the FindFile stuff - this will reset the cfg path for the find file
		// operations
		CFindFile::SetCFGFilePath (lpszPathName);

		return TRUE;
	}
}

void CRBModelerDoc::OnPrimitivesAddBlock() 
{
	AddPrimitive (PT_BLOCK);	
}

void CRBModelerDoc::OnPrimitivesAddCone() 
{
	AddPrimitive (PT_CONE);	
}

void CRBModelerDoc::OnPrimitivesAddCylinder() 
{
	AddPrimitive (PT_CYLINDER);	
}

void CRBModelerDoc::OnPrimitivesAddHemisphere() 
{
	AddPrimitive (PT_HEMISPHERE);	
}

void CRBModelerDoc::OnPrimitivesAddTruncatedcone() 
{
	AddPrimitive (PT_TRUNCATED_CONE);	
}


void CRBModelerDoc::OnButtonViewLeft() 
{
	WTp3 wtp3 = {0, -1, 0};
	WTq wtq;

	WTq_construct (wtp3, PI/2, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetModelView ()->GetWTKWnd ()->SetViewpointOrientation (wtq);
#endif
}

void CRBModelerDoc::OnButtonViewBack() 
{
	WTp3 wtp3 = {0, -1, 0};
	WTq wtq;

	WTq_construct (wtp3, PI, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetModelView ()->GetWTKWnd ()->SetViewpointOrientation (wtq);
#endif	
}

void CRBModelerDoc::OnButtonViewBottom() 
{
	WTp3 wtp3 = {1, 0, 0};
	WTq wtq;

	WTq_construct (wtp3, -PI/2, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetModelView ()->GetWTKWnd ()->SetViewpointOrientation (wtq);
#endif	
}

void CRBModelerDoc::OnButtonViewFront() 
{
	WTp3 wtp3 = {0, 0, -1};
	WTq wtq;

	WTq_construct (wtp3, 0.0f, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetModelView ()->GetWTKWnd ()->SetViewpointOrientation (wtq);
#endif
}

void CRBModelerDoc::OnButtonViewRight() 
{
	WTp3 wtp3 = {0, -1, 0};
	WTq wtq;

	WTq_construct (wtp3, -PI/2, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetModelView ()->GetWTKWnd ()->SetViewpointOrientation (wtq);
#endif	
}

void CRBModelerDoc::OnButtonViewTop() 
{
	WTp3 wtp3 = {1, 0, 0};
	WTq wtq;

	WTq_construct (wtp3, PI/2, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetModelView ()->GetWTKWnd ()->SetViewpointOrientation (wtq);
#endif
}

void CRBModelerDoc::OnButtonZoomIn() 
{
#ifdef WTK_LICENSE_AVAILABLE
	GetModelView ()->GetWTKWnd ()->ZoomViewpoint (TRUE);
#endif
}

void CRBModelerDoc::OnButtonZoomOut() 
{
#ifdef WTK_LICENSE_AVAILABLE
	GetModelView ()->GetWTKWnd ()->ZoomViewpoint (FALSE);
#endif
}

CCameraData* CRBModelerDoc::GetCameraData()
{
	return &m_CameraData;
}

void CRBModelerDoc::OnViewCameracontrol() 
{
	// Dialog
	CDlgCameraControl dlg;
	
	// Set the data for the dialog
	dlg.SetDataClassPointer (&m_CameraData);

	// Save if the current camera control type
	BOOL bPanMode = m_CameraData.GetViewInPanMode ();
	BOOL bUseViewport = m_CameraData.GetUseViewportFrameForExamineView ();

	// Set if the inertial axes are the COI
	// If the COI is the intertial axes, the following will come back NULL, otherwise
	// it will return a pointer to the WTK node that is the COI.
	if (!m_pModel->GetCameraCenterOfInterest ())
		dlg.SetInertialAxesAsCoi (TRUE);
	else
		dlg.SetInertialAxesAsCoi (FALSE);


	// Display dialog
	dlg.DoModal ();

	// Update the COI - if the inertial axes are selected as the COI, this will make sure
	// that no other WTK node is selected (which implies that inertial axes will be used)
	if (dlg.GetInertialAxesAsCoi ())
		m_pModel->ClearCameraCenterOfInterest ();


	// If changing from pan to examine, need to reorient the view to the spherical
	// coords from the current location.
	if (bPanMode && !m_CameraData.GetViewInPanMode ())
	{
		CRBModelerRBMGraphicView::UpdateCamera (TRUE);
	}
	// If in examine view - update in case of change of COI
	else if (!m_CameraData.GetViewInPanMode ())
	{
		CRBModelerRBMGraphicView::UpdateCamera (FALSE);
	}

	// If changing to inertial frame examine view, need to reorient
	if (bUseViewport && !m_CameraData.GetViewInPanMode () && 
		!m_CameraData.GetUseViewportFrameForExamineView ())
	{
		CRBModelerRBMGraphicView::UpdateCamera (TRUE);
	}	
}

void CRBModelerDoc::OnButtonHideLocalAxes() 
{
	// Go through each primitive and disable
	int i;
	for (i = 0; i < m_pModel->GetNumberOfPrimitives (); i++)
		m_pModel->GetPrimitive(i)->ShowWtkAxes (FALSE);	
}

void CRBModelerDoc::OnButtonShowLocalAxes() 
{
	// Go through each primitive and enable
	int i;
	for (i = 0; i < m_pModel->GetNumberOfPrimitives (); i++)
		m_pModel->GetPrimitive(i)->ShowWtkAxes (TRUE);	
}

void CRBModelerDoc::OnButtonToggleAxes() 
{
	m_bShowInertialAxes = !m_bShowInertialAxes;
}

BOOL CRBModelerDoc::ShowInertialAxes() const
{
	return m_bShowInertialAxes;
}

void CRBModelerDoc::OnUpdateButtonToggleAxes(CCmdUI* pCmdUI) 
{
	if (m_bShowInertialAxes)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CRBModelerDoc::OnFileSetbackgroundcolor() 
{
	// Open the color dialog
	CColorDialog dlg;
	
	// Initialize the color choice to the current color and automatically
	// expand the custom dialog part so the user will see the initial color.
	dlg.m_cc.Flags |= (CC_RGBINIT | CC_FULLOPEN);
	dlg.m_cc.rgbResult = m_pModel->GetBackgroundColor ();
	
	if (dlg.DoModal () == IDOK)
	{
		COLORREF crColor = dlg.GetColor ();
		m_pModel->SetBackgroundColor (crColor);

		// Update the universe color
		WTuniverse_setbgrgb (GetRValue (crColor),
			GetGValue (crColor), GetBValue (crColor));
	}
	
}

void CRBModelerDoc::OnPropertiesPhysicalproperties() 
{
	CDlgLinkPhysicalProperties dlg;

	dlg.SetModel (GetModel ());
	if (dlg.DoModal () == IDOK)
		GetModel ()->UseUserSuppliedDataForPhysicalData (dlg.GetUseUserSuppliedDataForPhysicalData ());
	
}

void CRBModelerDoc::OnViewCameralight() 
{
	WTnode* wtnodeCameraLight = CRBModelerRBMGraphicView::GetCameraDirectedLight ();
	if (WTlightnode_getintensity (wtnodeCameraLight) > 0)
		WTlightnode_setintensity (wtnodeCameraLight, 0);
	else
		WTlightnode_setintensity (wtnodeCameraLight, CAMERA_LIGHT_INTENSITY);
}

void CRBModelerDoc::OnUpdateViewCameralight(CCmdUI* pCmdUI) 
{
	WTnode* wtnodeCameraLight = CRBModelerRBMGraphicView::GetCameraDirectedLight ();
	if (WTlightnode_getintensity (wtnodeCameraLight) > 0)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}


void CRBModelerDoc::OnHelpUsersguide() 
{
	CString strDirectory = CFindFile::GetInitialWorkingDirectory () + _T("\\Docs");

	SHELLEXECUTEINFO theShellExecuteInfo;
	theShellExecuteInfo.cbSize = sizeof (SHELLEXECUTEINFO);
	theShellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	theShellExecuteInfo.hwnd = NULL; /* Parent window */
	theShellExecuteInfo.lpVerb = TEXT("open"); /* Verb */
	theShellExecuteInfo.lpFile = TEXT ("RobotModeler User's Guide.pdf");
	theShellExecuteInfo.lpParameters = NULL;
	theShellExecuteInfo.lpDirectory = strDirectory; /* Working Directory */
	theShellExecuteInfo.nShow = SW_SHOW;

	// The following are optional and will not be accessed because the way the
	// fMask field has been defined
	/*theShellExecuteInfo.lpIDList = NULL;
	theShellExecuteInfo.lpClass = NULL;
	theShellExecuteInfo.hkeyClass = NULL;
	theShellExecuteInfo.dwHotKey = NULL;
	theShellExecuteInfo.hIcon = NULL;
	theShellExecuteInfo.hMonitor = NULL;*/

	// Try to spawn.  If the function fails, it will display an error message to the
	// user, so there isn't a need for me to.
	ShellExecuteEx (&theShellExecuteInfo);
	
}

void CRBModelerDoc::OnHelpTutorial() 
{
		CString strDirectory = CFindFile::GetInitialWorkingDirectory () + _T("\\Docs");

	SHELLEXECUTEINFO theShellExecuteInfo;
	theShellExecuteInfo.cbSize = sizeof (SHELLEXECUTEINFO);
	theShellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	theShellExecuteInfo.hwnd = NULL; /* Parent window */
	theShellExecuteInfo.lpVerb = TEXT("open"); /* Verb */
	theShellExecuteInfo.lpFile = TEXT ("RobotBuilder Tutorial.pdf");
	theShellExecuteInfo.lpParameters = NULL;
	theShellExecuteInfo.lpDirectory = strDirectory; /* Working Directory */
	theShellExecuteInfo.nShow = SW_SHOW;

	// The following are optional and will not be accessed because the way the
	// fMask field has been defined
	/*theShellExecuteInfo.lpIDList = NULL;
	theShellExecuteInfo.lpClass = NULL;
	theShellExecuteInfo.hkeyClass = NULL;
	theShellExecuteInfo.dwHotKey = NULL;
	theShellExecuteInfo.hIcon = NULL;
	theShellExecuteInfo.hMonitor = NULL;*/

	// Try to spawn.  If the function fails, it will display an error message to the
	// user, so there isn't a need for me to.
	ShellExecuteEx (&theShellExecuteInfo);
	
}

void CRBModelerDoc::OnButtonpan() 
{
	m_CameraData.SetViewInPanMode(TRUE);	
}

void CRBModelerDoc::OnButtonexamine() 
{
	m_CameraData.SetViewInPanMode(FALSE);

	// Update the camera to adjust for the (possibly) new center
	CRBModelerRBMGraphicView::UpdateCamera (FALSE);
}

void CRBModelerDoc::OnUpdateButtonexamine(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable (TRUE);
	if (!m_CameraData.GetViewInPanMode())
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CRBModelerDoc::OnUpdateButtonpan(CCmdUI* pCmdUI) 
{
	if (m_CameraData.GetViewInPanMode())
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}
