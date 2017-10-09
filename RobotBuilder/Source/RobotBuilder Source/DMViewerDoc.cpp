// DMViewerDoc.cpp : implementation of the CDMViewerDoc class
//

#include "stdafx.h"
#include "DMViewer.h"

#include "DMViewerDoc.h"
//#include "dmvArticulationData.h"
#include "DlgEnvironmentData.h"
//#include "DlgSimulationData.h"
#include "DlgConfigProperties.h"
#include "GenerateCFGFile.h"
#include "GeneratePlaybackFile.h"
#include "FindFile.h"
#include "ParserEnvironment.h"
#include "ParserCFG.h"
#include "ParserDM.h"
#include "dmvCFGData.h"
#include "dmvArticulationData.h"
#include "CameraData.h"
#include "dmvTerrainData.h"
#include "dmvTreadmillData.h"
#include "ParserTreadmill.h"
#include "ParserTerrain.h"
#include "ParserPlayback.h"
#include "DlgCameraControl.h"
#include "MainFrm.h"

#include <RBUserIOData.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define PI  3.1415927

/////////////////////////////////////////////////////////////////////////////
// CDMViewerDoc

IMPLEMENT_DYNCREATE(CDMViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CDMViewerDoc, CDocument)
	//{{AFX_MSG_MAP(CDMViewerDoc)
	ON_COMMAND(ID_BUTTON_PLAY, OnButtonPlay)
	ON_COMMAND(ID_BUTTON_PAUSE, OnButtonPause)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_PLAY, OnUpdateButtonPlay)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_PAUSE, OnUpdateButtonPause)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TOGGLESTATE, OnUpdateViewTogglestate)
	ON_COMMAND(ID_BUTTON_STOP, OnButtonStop)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_STOP, OnUpdateButtonStop)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_COMMAND(ID_ENVIRONMENT_NEWENVIRONMENTFILE, OnEnvironmentNewEnvironmentFile)
	ON_COMMAND(ID_ENVIRONMENT_EDITENVIRONMENTPROPERITIES, OnEnvironmentEditEnvironmentProperities)
	ON_COMMAND(ID_ENVIRONMENT_SAVEENVIRONMENT, OnEnvironmentSaveEnvironment)
	ON_COMMAND(ID_ENVIRONMENT_SAVEENVIRONMENTAS, OnEnvironmentSaveEnvironmentAs)
	ON_COMMAND(ID_ENVIRONMENT_OPENENVIRONMENTFILE, OnEnvironmentOpenEnvironmentFile)
	ON_COMMAND(ID_ARTICULATION_OPENARTICULATIONFILE, OnArticulationOpenArticulationFile)
	ON_COMMAND(ID_ARTICULATION_SAVEARTICULATIONFILE, OnArticulationSaveArticulationFile)
	ON_COMMAND(ID_ARTICULATION_SAVEARTICULATIONFILEAS, OnArticulationSaveArticulationFileAs)
	ON_COMMAND(ID_CONTROL_SELECTCONTROLDLL, OnControlSelectControlDll)
	ON_UPDATE_COMMAND_UI(ID_ARTICULATION_NEWARTICULATIONFILE, OnUpdateArticulationNewarticulationfile)
	ON_UPDATE_COMMAND_UI(ID_ARTICULATION_OPENARTICULATIONFILE, OnUpdateArticulationOpenarticulationfile)
	ON_UPDATE_COMMAND_UI(ID_ARTICULATION_SAVEARTICULATIONFILE, OnUpdateArticulationSavearticulationfile)
	ON_UPDATE_COMMAND_UI(ID_ARTICULATION_SAVEARTICULATIONFILEAS, OnUpdateArticulationSavearticulationfileas)
	ON_UPDATE_COMMAND_UI(ID_CONTROL_SELECTCONTROLDLL, OnUpdateControlSelectcontroldll)
	ON_UPDATE_COMMAND_UI(ID_ENVIRONMENT_EDITENVIRONMENTPROPERITIES, OnUpdateEnvironmentEditenvironmentproperities)
	ON_UPDATE_COMMAND_UI(ID_ENVIRONMENT_NEWENVIRONMENTFILE, OnUpdateEnvironmentNewenvironmentfile)
	ON_UPDATE_COMMAND_UI(ID_ENVIRONMENT_OPENENVIRONMENTFILE, OnUpdateEnvironmentOpenenvironmentfile)
	ON_UPDATE_COMMAND_UI(ID_ENVIRONMENT_SAVEENVIRONMENT, OnUpdateEnvironmentSaveenvironment)
	ON_UPDATE_COMMAND_UI(ID_ENVIRONMENT_SAVEENVIRONMENTAS, OnUpdateEnvironmentSaveenvironmentas)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_CFGFILE_EDITSIMULATIONPROPERTIES, OnCfgfileEditSimulationProperties)
	ON_UPDATE_COMMAND_UI_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE4, OnUpdateFileMruFile)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_COMMAND(ID_BUTTON_USERVIEW, OnButtonViewUser)
	ON_COMMAND(ID_BUTTON_VIEW_LEFT, OnButtonViewLeft)
	ON_COMMAND(ID_BUTTON_VIEW_BACK, OnButtonViewBack)
	ON_COMMAND(ID_BUTTON_VIEW_BOTTOM, OnButtonViewBottom)
	ON_COMMAND(ID_BUTTON_VIEW_FRONT, OnButtonViewFront)
	ON_COMMAND(ID_BUTTON_VIEW_RIGHT, OnButtonViewRight)
	ON_COMMAND(ID_BUTTON_VIEW_TOP, OnButtonViewTop)
	ON_COMMAND(ID_BUTTON_ZOOM_IN, OnButtonZoomIn)
	ON_COMMAND(ID_BUTTON_ZOOM_OUT, OnButtonZoomOut)
	ON_COMMAND(ID_BUTTON_TOGGLE_AXES, OnButtonToggleAxes)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TOGGLE_AXES, OnUpdateButtonToggleAxes)
	ON_COMMAND(ID_SETUP_DEFAULTPATHS, OnSetupDefaultpaths)
	ON_COMMAND(ID_SETUP_NODISPLAYMODEDURINGSIMULATION, OnSetupNodisplaymodeduringsimulation)
	ON_UPDATE_COMMAND_UI(ID_SETUP_NODISPLAYMODEDURINGSIMULATION, OnUpdateSetupNodisplaymodeduringsimulation)
	ON_UPDATE_COMMAND_UI(ID_CFGFILE_EDITSIMULATIONPROPERTIES, OnUpdateCfgfileEditsimulationproperties)
	ON_COMMAND(ID_ARTICULATION_NEWARTICULATIONFILE, OnArticulationNewArticulationFile)
	ON_COMMAND(ID_BUTTON_RECORD, OnButtonRecord)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_RECORD, OnUpdateButtonRecord)
	ON_COMMAND(ID_BUTTON_PLAYBACK, OnButtonPlayback)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_PLAYBACK, OnUpdateButtonPlayback)
	ON_COMMAND(ID_PLAYBACK_OPENPLAYBACKFILE, OnPlaybackOpenplaybackfile)
	ON_UPDATE_COMMAND_UI(ID_PLAYBACK_OPENPLAYBACKFILE, OnUpdatePlaybackOpenplaybackfile)
	ON_COMMAND(ID_PLAYBACK_SAVEPLAYBACK, OnPlaybackSaveplayback)
	ON_UPDATE_COMMAND_UI(ID_PLAYBACK_SAVEPLAYBACK, OnUpdatePlaybackSaveplayback)
	ON_COMMAND(ID_PLAYBACK_SAVEPLAYBACKFILEAS, OnPlaybackSaveplaybackfileas)
	ON_UPDATE_COMMAND_UI(ID_PLAYBACK_SAVEPLAYBACKFILEAS, OnUpdatePlaybackSaveplaybackfileas)
	ON_COMMAND(ID_BUTTON_BUILD, OnButtonBuild)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_BUILD, OnUpdateButtonBuild)
	ON_COMMAND(ID_BUTTON_SHOW_LINK_AXES, OnButtonShowLinkAxes)
	ON_COMMAND(ID_BUTTON_HIDE_LINK_AXES, OnButtonHideLinkAxes)
	ON_COMMAND(ID_VIEW_CAMERACONTROL, OnViewCameracontrol)
	ON_COMMAND(ID_BUTTON_RBMODLER, OnButtonRbmodler)
	ON_COMMAND(ID_VIEW_CAMERALIGHT, OnViewCameralight)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAMERALIGHT, OnUpdateViewCameralight)
	ON_COMMAND(ID_HELP_USERSGUIDE, OnHelpUsersguide)
	ON_COMMAND(ID_BUTTONEXAMINE, OnButtonexamine)
	ON_UPDATE_COMMAND_UI(ID_BUTTONEXAMINE, OnUpdateButtonexamine)
	ON_COMMAND(ID_BUTTONPAN, OnButtonpan)
	ON_UPDATE_COMMAND_UI(ID_BUTTONPAN, OnUpdateButtonpan)
	ON_COMMAND(ID_HELP_TUTORIAL, OnHelpTutorial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMViewerDoc construction/destruction

CDMViewerDoc::CDMViewerDoc()
{
	// TODO: add one-time construction code here
	m_bPlay = FALSE;
	m_bRecordMode = FALSE;
	m_bPlaybackMode = FALSE;
	m_bEditState = TRUE;

	m_pSystemData = NULL;
	m_bSystemChanged = FALSE;

	m_pEnvironmentData = NULL;
	m_bEnvironmentChanged = FALSE;

	m_pCdmvCFGData = NULL;
	m_bShowAxes = TRUE;

    m_pRBUserIOData = NULL;

	m_pLinkClipboard = NULL;

}

CDMViewerDoc::~CDMViewerDoc()
{
//	if (m_pSystemData)
//		delete m_pSystemData;
   
   // Clean up the RBUserIOData
   if (m_pRBUserIOData)
      delete m_pRBUserIOData;

	if (m_pLinkClipboard)
		delete m_pLinkClipboard;
}

BOOL CDMViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// Allocate new environment
	try {
		m_pCdmvCFGData = new CdmvCFGData;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	OnArticulationNewArticulationFile ();
	OnEnvironmentNewEnvironmentFile ();

	// Clean up the playback data
	m_PlaybackData.CleanUp ();
//	ResetSimulationPropertiesToDefaults ();
//	m_strControlFile = "";

	// Tell the rest of the simulation about the new CFG file
	UpdateSimulationWithCFGParameters ();

	// Reset the FindFile stuff
	CFindFile::SetCFGFilePath ("");

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDMViewerDoc serialization

void CDMViewerDoc::Serialize(CArchive& ar)
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
// CDMViewerDoc diagnostics

#ifdef _DEBUG
void CDMViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDMViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDMViewerDoc commands

BOOL CDMViewerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// OnOpenDocument will call DeleteContents, so need to allocate a fresh CdmvCFGData
	// Allocate new
	try {
		m_pCdmvCFGData = new CdmvCFGData;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	// Set the FindFile stuff - Need to set this before calling the parser for the cfg
	// so the parser will lookup in the correct path for the files.
	CFindFile::SetCFGFilePath (lpszPathName);

	if (CParserCFG::ParseCFGFile (lpszPathName, m_pCdmvCFGData))
	{
		
		const ArticulationAndControlFileArray& rArticulationAndControlFileArray = 
			m_pCdmvCFGData->GetArticulationAndControlFileArray ();
		
		int i;
		for (i = 0; i < rArticulationAndControlFileArray.GetSize (); i++)
		{
			structArticulationAndControlFilePair Entry = rArticulationAndControlFileArray.GetAt (i);
			// Check if there is an articualtion file specified (it's legal not to specify one)
			if (!Entry.strArticulationFile.IsEmpty ())
			{
				OpenArticulationFile (Entry.strArticulationFile, Entry.strArticulationPath);
				UpdateArticulationDisplay ();
			}
			else
			{
				// Load an empty one
				OnArticulationNewArticulationFile ();
			}
		}

		// Check if an environment file is specified (it's legal not to specify one)
		CString strEnvironmentFile, strEnvironmentPath;
		m_pCdmvCFGData->GetEnvironmentFile (strEnvironmentFile, strEnvironmentPath);
		if (strEnvironmentFile.GetLength () > 0)
		{

			OpenEnvironmentFile (strEnvironmentFile, strEnvironmentPath);
			UpdateEnvironmentDisplay ();
		}
		else
		{
			// Load empty environment
			OnEnvironmentNewEnvironmentFile ();
		}

		ASSERT (m_pSystemData);

		// Set the center of interest
		CdmvLinkData* pLink = ((CdmvArticulationData*) m_pSystemData)->FindLinkByName(m_pCdmvCFGData->GetCenterOfInterestName());


		CString strInertialAxes;
		strInertialAxes.LoadString(IDS_STRING_INERTIAL_AXES);

		if (pLink == NULL)
		{	// this means either the articulation or the inertial axes were set 
			//	or the link couldn't be found
			
			if (m_pCdmvCFGData->GetCenterOfInterestName() == ((CdmvArticulationData*) m_pSystemData)->GetName())
			{
				// Articulation is the center of interest
				((CdmvArticulationData*) m_pSystemData)->IsCameraCenterOfInterest(TRUE);
			}
			else if (m_pCdmvCFGData->GetCenterOfInterestName() != strInertialAxes)
			{   // couldn't find the link -- will default to inertial axes
				AfxMessageBox (IDS_STRING_UNABLE_TO_LOCATE_COI, MB_OK);
			}
		}
		else
		{	// did find the link, so set it as the center of interest
			pLink->IsCameraCenterOfInterest(TRUE);
		}	

	}
	else
	{
		// Reset the cfg location for findfile
		CFindFile::SetCFGFilePath (_T(""));
		// Load an empty environment and articulation
		OnArticulationNewArticulationFile ();
		OnEnvironmentNewEnvironmentFile ();
		// Set the FindFile stuff
		CFindFile::SetCFGFilePath ("");
		// Return false to indicate failed to open
		return FALSE;
	}


	UpdateSimulationWithCFGParameters ();

	// Reset the view
	OnButtonViewUser ();

	// Reset the "dirty" bit
	m_pCdmvCFGData->ResetDataChanged();

	return TRUE;
}

CdmvSystemData* CDMViewerDoc::GetSystemData()
{
	return m_pSystemData;
}

BOOL CDMViewerDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnSaveDocument(lpszPathName))
		return FALSE;
	
//	OnArticulationSaveArticulationFile ();
//	OnEnvironmentSaveEnvironment ();
	
	// Don't need to do a find file, because the .cfg is explicitly specified, so will
	// always be found.
	
	if (!CGenerateCFGFile::CreateCFGFile (lpszPathName, m_pCdmvCFGData))
	{
		// MFC apparently prevents the code from getting here if you try to save to a read-only file
		// Gives some unclear error message. todo: figure out what is going on - maybe don't display
		// read-only files in the save dialog.
		AfxMessageBox (_T("The file could not be written.  Please verify that the file or directory is not read-only."));
		return FALSE;
	}

	
	// Set the FindFile stuff - this will reset the cfg path for the find file
	// operations
	CFindFile::SetCFGFilePath (lpszPathName);

	// Reset the "dirty" bit
	m_pCdmvCFGData->ResetDataChanged();

	return TRUE;
}



BOOL CDMViewerDoc::OnAppIdle(LONG lCount)
{
	if (m_pCdmvCFGData->DataHasChanged())
	{
		CDocument::SetModifiedFlag();
	}	

	if (m_bPlay)
	{
		if (!m_bPlaybackMode)
			GetIOView()->UpdateUserData (m_pRBUserIOData);

		GraphicsMode theGraphicsMode;
		if (m_bRecordMode)
			theGraphicsMode = GRAPHICS_RECORD;
		else if (m_bPlaybackMode)
			theGraphicsMode = GRAPHICS_PLAYBACK;
		else
			theGraphicsMode = GRAPHICS_REGULAR;

		if (!m_DynaMechs.UpdateSimulation (theGraphicsMode))
		{
			// If FALSE is returned (possibly because instability was detected in DynaMechs),
			// The following function will be called to toggle to back to the edit mode.  It is
			// assumed that whatever returned FALSE, alerted the user that simulation is being stopped.
			AfxGetMainWnd ()->PostMessage (WM_COMMAND, ID_VIEW_TOGGLESTATE);
		}

		// We're simulating or playbacking, so return TRUE to keep getting idle time calls
		return TRUE;
	}
	else
	{
		// Tell DynaMechs that it's not simulating so the real time calculations can sync up, but
		// only if in simulation mode (because that's when its real time calculations start)
		if (!m_bEditState || m_bPlaybackMode)
			m_DynaMechs.DontSimulate ();

		// Not doing much, so return false, so don't waste CPU here
		return FALSE;
	}
}




void CDMViewerDoc::OnButtonPlay() 
{
	// TODO: Add your command handler code here
	m_bPlay = TRUE;

	// Initialize the "last" transform
#ifdef WTK_LICENSE_AVAILABLE
		CWTKView* pWTKView = GetWTKView ();
		pWTKView->m_WTKGraphics.SetLastTransform();
#endif
}

void CDMViewerDoc::OnButtonPause() 
{
	// TODO: Add your command handler code here
	m_bPlay = FALSE;
}

void CDMViewerDoc::OnViewTogglestate() 
{
	ASSERT (m_pEnvironmentData);
	ASSERT (m_pSystemData);

	// If currently in playback mode, back out to edit mode first
	if (m_bEditState && m_bPlaybackMode)
		AfxGetMainWnd ()->SendMessage (WM_COMMAND, ID_BUTTON_PLAYBACK);


	m_bEditState = !m_bEditState;

	if (!m_bEditState)
	{
		if (!ValidateStateBeforeDynaMechs ())
		{
			AfxGetMainWnd ()->PostMessage (WM_COMMAND, ID_VIEW_TOGGLESTATE);
			return;
		}

		// Clear any selection (bounding boxes) from the simulation is done in the CMainFrame event handler
		// for this event (because the tree view doesn't exist when the execution hits this part of
		// the code
		
		// now tell DynaMechs to load it and reset -- if it fails, return to the edit state
		// Get the control
		CString strControlFile, strControlPath;
		m_pCdmvCFGData->GetFirstControlFile (strControlFile, strControlPath);
		if (!m_DynaMechs.InitializeDynaMechs (m_pSystemData, m_pEnvironmentData, 
         strControlPath + strControlFile, &m_pRBUserIOData, &m_PlaybackData))
      {
			AfxGetMainWnd ()->PostMessage (WM_COMMAND, ID_VIEW_TOGGLESTATE);
			return;
		}
		m_DynaMechs.SetPlayerPointer (&(GetWTKView ()->m_WTKGraphics));

      // Pass the data to the IOView
      GetIOView ()->SetRBUserIOData (m_pRBUserIOData);

//		pWTKView->m_PlayerToolkit.DisplayAxes (m_bShowAxes);
	}
	else
	{
		// Load the tree
		GetTreeView ()->LoadNewTree ();

		// make sure that play is stopped so there won't be an attempt
		// to update the display that isn't there
		m_bPlay = FALSE;
		m_bRecordMode = FALSE;

		// reset dynamics to uninitialize all the stuff
		m_DynaMechs.ResetDynaMechs ();

#ifdef WTK_LICENSE_AVAILABLE
		CWTKView* pWTKView = GetWTKView ();
		pWTKView->m_WTKGraphics.ResetArticulationToInitialValues (dynamic_cast 
			<CdmvArticulationData*> (m_pSystemData));
		pWTKView->m_WTKGraphics.ResetEnvironmentToInitialValues (m_pEnvironmentData);
#endif
	}

	// Force a repaint of the toolbar in case it can't happen automatically
	((CMainFrame*)AfxGetApp()->m_pMainWnd)->InvalidateToolBar ();	
}

void CDMViewerDoc::OnUpdateButtonPlay(CCmdUI* pCmdUI) 
{
	if (m_bEditState && !m_bPlaybackMode)
	{
		pCmdUI->Enable (FALSE);
		pCmdUI->SetCheck (0);
	}
	else if (m_bPlaybackMode && GetNumberOfMovableObjects () != 
		m_PlaybackData.GetNumberOfItems ())
	{
		// Checks that if in playback mode, that the number of movable items matches
		pCmdUI->Enable (FALSE);
		pCmdUI->SetCheck (0);
	}
	else
	{
		pCmdUI->Enable (TRUE);
		if (m_bPlay)
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}
	
}

void CDMViewerDoc::OnUpdateButtonPause(CCmdUI* pCmdUI) 
{
	if (m_bEditState && !m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else if (m_bPlaybackMode && GetNumberOfMovableObjects () != 
		m_PlaybackData.GetNumberOfItems ())
	{
		// Checks that if in playback mode, that the number of movable items matches
		pCmdUI->Enable (FALSE);
		pCmdUI->SetCheck (0);
	}
	else
		pCmdUI->Enable (TRUE);	
}

void CDMViewerDoc::OnUpdateViewTogglestate(CCmdUI* pCmdUI) 
{
	if (m_bEditState)
		pCmdUI->SetCheck (0);
	else
		pCmdUI->SetCheck (1);
}

void CDMViewerDoc::OnButtonStop() 
{
	// Stop the play mode
	m_bPlay = FALSE;
	// Stop the Record mode
	m_bRecordMode = FALSE;

	// Reset DynaMechs and tell DynaMechs to load the data again
	if (m_bPlaybackMode)
	{
		// Pick up the start and end times for the playback data - it is assumed
		// that there is valid playback data
		double dStartTime, dEndTime;
		m_PlaybackData.GetPlaybackTimes (dStartTime, dEndTime);

		m_DynaMechs.InitializePlayback (dStartTime, dEndTime, 
			m_pSystemData, m_pEnvironmentData, &m_PlaybackData);
	}
	else
	{
		CString strControlFile, strControlPath;
		m_pCdmvCFGData->GetFirstControlFile (strControlFile, strControlPath);
		m_DynaMechs.InitializeDynaMechs (m_pSystemData, m_pEnvironmentData, 
			strControlPath + strControlFile, &m_pRBUserIOData, &m_PlaybackData);

      // Pass the data to the IOView - this needs to be done since the call to 
		// InitializeDynaMechs will define a new class.
      GetIOView ()->SetRBUserIOData (m_pRBUserIOData);
	}

#ifdef WTK_LICENSE_AVAILABLE
	CWTKView* pWTKView;
	pWTKView = GetWTKView ();
	pWTKView->m_WTKGraphics.ResetArticulationToInitialValues (dynamic_cast 
		<CdmvArticulationData*> (m_pSystemData));
	pWTKView->m_WTKGraphics.ResetEnvironmentToInitialValues (m_pEnvironmentData);
//	pWTKView->m_PlayerToolkit.DisplayAxes (m_bShowAxes);
	m_DynaMechs.SetPlayerPointer (&(pWTKView->m_WTKGraphics));
#endif

	// Restore the appropriate user view
	OnButtonViewUser();
}

void CDMViewerDoc::OnUpdateButtonStop(CCmdUI* pCmdUI) 
{
	if (m_bEditState && !m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else if (m_bPlaybackMode && GetNumberOfMovableObjects () != 
		m_PlaybackData.GetNumberOfItems ())
	{
		// Checks that if in playback mode, that the number of movable items matches
		pCmdUI->Enable (FALSE);
		pCmdUI->SetCheck (0);
	}
	else
		pCmdUI->Enable (TRUE);		
}

void CDMViewerDoc::DeleteContents() 
{
	// This is called before the document is destroyed to deallocate everything
	DeleteEnvironment ();
	DeleteArticulation ();
	DeleteCFG ();

	CDocument::DeleteContents();
}

void CDMViewerDoc::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		

}

void CDMViewerDoc::OnEnvironmentNewEnvironmentFile() 
{
	DeleteEnvironment ();

	// Allocate new environment
	try {
		m_pEnvironmentData = new CdmvTerrainData;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	UpdateEnvironmentDisplay ();
}

void CDMViewerDoc::DeleteEnvironment()
{
	if (m_pEnvironmentData)
	{
		delete m_pEnvironmentData;
		m_pEnvironmentData = NULL;
	}

	// This function is called by DeleteContents, which is call by OnNewDocument, which is called
	// at startup, which occurs before the CdmvCFGData class has been allocated -- so we need to 
	// check if it has been allocated yet or not
	if (m_pCdmvCFGData)
		m_pCdmvCFGData->SetEnvironmentFile ("", "");
	m_bEnvironmentChanged = FALSE;
}

void CDMViewerDoc::OnEnvironmentEditEnvironmentProperities() 
{
	CDlgEnvironmentData dlg;
	
	dlg.SetDataClassPointer (&m_pEnvironmentData);

	if (dlg.DoModal () == IDOK)
	{
		m_bEnvironmentChanged = TRUE;
		UpdateEnvironmentDisplay ();
	}
}

void CDMViewerDoc::OnEnvironmentSaveEnvironment() 
{
	CString strEnvironmentFile, strEnvironmentPath;
	m_pCdmvCFGData->GetEnvironmentFile (strEnvironmentFile, strEnvironmentPath);
	if (strEnvironmentFile.GetLength () == 0)
	{
		// Then need to get a filename so call Save As for the environment
		// Note that SaveAs calls this function to handle the actual saving, but
		// when it does, a filename will exist
		OnEnvironmentSaveEnvironmentAs ();
	}
	else
	{
		ASSERT (m_pSystemData);
		// Have a filename so save to it
		BOOL bReturnStatus = CGenerateEnvironmentFile::CreateEnvironmentFile
			(strEnvironmentPath + strEnvironmentFile, m_pEnvironmentData);
		if (!bReturnStatus)
		{
			AfxMessageBox (_T("The file could not be written.  Please verify that the file or directory is not read-only."));
			return;
		}

		// Now that it is saved, mark as clean again
		m_bEnvironmentChanged = FALSE;
	}
}

void CDMViewerDoc::OnEnvironmentSaveEnvironmentAs() 
{
	CString strEnvironmentFile, strEnvironmentPath;
	m_pCdmvCFGData->GetEnvironmentFile (strEnvironmentFile, strEnvironmentPath);

	CFileDialog dlg (FALSE, /* make an save dlg */
		".env", /* default extension */
		strEnvironmentFile, /* initial filename */
		OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"Environment File (*.env)|*.env;||",	/* filter */
		NULL /* parent */
		);

	if (strEnvironmentPath.GetLength () > 0)
		dlg.m_ofn.lpstrInitialDir = strEnvironmentPath;
	
	if (dlg.DoModal () == IDOK)
	{	
		CString strFile = dlg.GetFileName ();
		CString strPath = (dlg.GetPathName ()).Left (dlg.GetPathName ().GetLength () -
			strFile.GetLength ());

		// Save the file
		m_pCdmvCFGData->SetEnvironmentFile (strFile, strPath);
		OnEnvironmentSaveEnvironment ();

		// Make sure the file can be found
		BOOL bFindFile = CFindFile::FindFile (ENVIRONMENT_FILE_TYPE, 
			strFile, strPath);
		if (!bFindFile || ((strPath + strFile) != dlg.GetPathName ()))
		{
			if (IDYES == AfxMessageBox (FILE_NOT_FOUND_MSG, MB_YESNO))
			{
				strFile = dlg.GetPathName ();
				strPath = "";
				// Save the full path in the file
				m_pCdmvCFGData->SetEnvironmentFile (strFile, strPath);
			}
		}
		
	}

}

void CDMViewerDoc::OnEnvironmentOpenEnvironmentFile() 
{
	// Get a copy of the current environment to initialize the open dialog
	CString strCurrentEnvironmentFile, strCurrentEnvironmentPath;
	m_pCdmvCFGData->GetEnvironmentFile (strCurrentEnvironmentFile, strCurrentEnvironmentPath);

	CFileDialog dlg (TRUE, /* make an open dlg */
		".env", /* default extension */
		strCurrentEnvironmentFile, /* initial filename */
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"Environment File (*.env)|*.env;||",	/* filter */
		NULL /* parent */
		);
	
	if (strCurrentEnvironmentPath.GetLength () > 0)
		dlg.m_ofn.lpstrInitialDir = strCurrentEnvironmentPath;

	if (dlg.DoModal () == IDOK)
	{	
		CString strPath;
		CString strFile = dlg.GetFileName ();
		
		BOOL bFindFile = CFindFile::FindFile (ENVIRONMENT_FILE_TYPE, 
			strFile, strPath);
		if (!bFindFile || ((strPath + strFile) != dlg.GetPathName ()))
		{
			if (IDYES == AfxMessageBox (FILE_NOT_FOUND_MSG, MB_YESNO))
			{
				strFile = dlg.GetPathName ();
				strPath = "";
			}
			else
			{
				// strFile stays the same
				// Strip off the file name from the full path
				strPath = (dlg.GetPathName ()).Left (dlg.GetPathName ().GetLength () -
					strFile.GetLength ());
			}
		}

		OpenEnvironmentFile (strFile, strPath);
		UpdateEnvironmentDisplay ();
	}	

}

void CDMViewerDoc::OpenEnvironmentFile(CString strFile, CString strPath)
{
	DeleteEnvironment ();
	
	// Note that the file may not exist, but if not, it will be taken care of in
	// the parser

	m_pCdmvCFGData->SetEnvironmentFile (strFile, strPath);

	if (!CParserEnvironment::ParseEnvironmentFile (strPath + strFile, &m_pEnvironmentData))
	{
		// A message box will already have been displayed
		OnEnvironmentNewEnvironmentFile ();
	}
	else 
	{ 
		// Then successfully opened the environment file
		// Open the details file
		CString strDataFile, strDataPath;
		m_pEnvironmentData->GetDataFile (strDataFile, strDataPath);
		if (m_pEnvironmentData->GetEnvironmentType () == ENV_TERRAIN)
		{
			if (!CParserTerrain::ParseTerrainFile (strDataPath + strDataFile,
				dynamic_cast <CdmvTerrainData*> (m_pEnvironmentData)))
			{
				// Failed to open the file - reset the environment
				OnEnvironmentNewEnvironmentFile ();
			}
		}
		else
		{
			// Then its ENV_CONVEYOR
			if (!CParserTreadmill::ParseTreadmillFile (strDataPath + strDataFile,
				dynamic_cast <CdmvTreadmillData*> (m_pEnvironmentData)))
			{
				// Failed to open the file - reset the environment
				OnEnvironmentNewEnvironmentFile ();
			}
		}
	}

}

void CDMViewerDoc::UpdateEnvironmentDisplay()
{
#ifdef WTK_LICENSE_AVAILABLE
	CWTKView* pWTKView;
	pWTKView = GetWTKView ();
	if (m_pSystemData != NULL && m_pEnvironmentData != NULL)
	{
		if (pWTKView->m_wndWTK.GetSafeHwnd ())
		{
			pWTKView->m_WTKGraphics.CreateEnvironmentNode (m_pEnvironmentData);
		}
	}
#endif	
}

void CDMViewerDoc::OnArticulationNewArticulationFile() 
{
	if (m_pSystemData)
	{
		delete m_pSystemData;
		m_pCdmvCFGData->SetFirstArticulationFile ("", "");
	}

	// add an articulation node to start with
	try {
		m_pSystemData = new CdmvArticulationData;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}
	
	UpdateArticulationDisplay ();

}

void CDMViewerDoc::OnArticulationOpenArticulationFile() 
{
	// Get a copy of the current articulation to initialize the open dialog
	CString strCurrentArticulationFile, strCurrentArticulationPath;
	m_pCdmvCFGData->GetFirstArticulationFile (strCurrentArticulationFile, strCurrentArticulationPath);

	CFileDialog dlg (TRUE, /* make an open dlg */
		".dm", /* default extension */
		strCurrentArticulationFile, /* initial filename */
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"Articulation File (*.dm)|*.dm||",	/* filter */
		NULL /* parent */
		);
	
	if (strCurrentArticulationPath.GetLength () > 0)
		dlg.m_ofn.lpstrInitialDir = strCurrentArticulationPath;

	if (dlg.DoModal () == IDOK)
	{	
		CString strPath;
		CString strFile = dlg.GetFileName ();
		
		BOOL bFindFile = CFindFile::FindFile (ARTICULATION_FILE_TYPE, 
			strFile, strPath);
		if (!bFindFile || ((strPath + strFile) != dlg.GetPathName ()))
		{
			if (IDYES == AfxMessageBox (FILE_NOT_FOUND_MSG, MB_YESNO))
			{
				strFile = dlg.GetPathName ();
				strPath = "";
			}
			else
			{
				// strFile stays the same
				// Strip off the file name from the full path
				strPath = (dlg.GetPathName ()).Left (dlg.GetPathName ().GetLength () -
					strFile.GetLength ());
			}
		}

		OpenArticulationFile (strFile, strPath);
		UpdateArticulationDisplay ();
	}	
}

void CDMViewerDoc::OnArticulationSaveArticulationFile() 
{
	CString strArticulationFile, strArticulationPath;
	m_pCdmvCFGData->GetFirstArticulationFile (strArticulationFile, strArticulationPath);
	if (strArticulationFile.GetLength () == 0)
	{
		// Then need to get a filename so call Save As for the articulation
		// Note that SaveAs calls this function to handle the actual saving, but
		// when it does, a filename will exist
		OnArticulationSaveArticulationFileAs ();
	}
	else
	{
		ASSERT (m_pSystemData);
		// Have a filename so save to it
		BOOL bReturnStatus = CGenerateDMConfigFile::CreateDMConfigFile
			(strArticulationPath + strArticulationFile, m_pSystemData);
		if (!bReturnStatus)
		{
			AfxMessageBox (_T("The file could not be written.  Please verify that the file or directory is not read-only."));
			return;
		}

		// Now that it is saved, mark as clean again
		m_bSystemChanged = FALSE;
	}	
}

void CDMViewerDoc::OnArticulationSaveArticulationFileAs() 
{
	CString strArticulationFile, strArticulationPath;
	m_pCdmvCFGData->GetFirstArticulationFile (strArticulationFile, strArticulationPath);

	CFileDialog dlg (FALSE, /* make an save dlg */
		".dm", /* default extension */
		strArticulationFile, /* initial filename */
		OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"Articulation File (*.dm)|*.dm||",	/* filter */
		NULL /* parent */
		);

	if (strArticulationPath.GetLength () > 0)
		dlg.m_ofn.lpstrInitialDir = strArticulationPath;
	
	if (dlg.DoModal () == IDOK)
	{	
		CString strFile = dlg.GetFileName ();
		// Strip off the file name from the full path
		CString strPath = (dlg.GetPathName ()).Left (dlg.GetPathName ().GetLength () -
			strFile.GetLength ());
		
		// Save the file and path and write the file
		m_pCdmvCFGData->SetFirstArticulationFile (strFile, strPath);
		OnArticulationSaveArticulationFile ();		
		
		// Now make sure the file can be found
		BOOL bFindFile = CFindFile::FindFile (ARTICULATION_FILE_TYPE, 
			strFile, strPath);
		if (!bFindFile || ((strPath + strFile) != dlg.GetPathName ()))
		{
			if (IDYES == AfxMessageBox (FILE_NOT_FOUND_MSG, MB_YESNO))
			{
				strFile = dlg.GetPathName ();
				strPath = "";

				// Save the new 'file' name (which just additionally includes
				// the directory information now
				m_pCdmvCFGData->SetFirstArticulationFile (strFile, strPath);

			}
		}		

	}

}

void CDMViewerDoc::DeleteArticulation ()
{
	if (m_pSystemData)
	{
		delete m_pSystemData;
		m_pSystemData = NULL;
	}

	// This function is called by DeleteContents, which is call by OnNewDocument, which is called
	// at startup, which occurs before the CdmvCFGData class has been allocated -- so we need to 
	// check if it has been allocated yet or not
	if (m_pCdmvCFGData)
		m_pCdmvCFGData->SetFirstArticulationFile ("", "");
	m_bSystemChanged = FALSE;
}

void CDMViewerDoc::UpdateArticulationDisplay()
{
	// Now display it
	GetTreeView ()->LoadNewTree ();
#ifdef WTK_LICENSE_AVAILABLE
	if (m_pSystemData != NULL)
	{
		CWTKView* pWTKView = GetWTKView ();
		if (pWTKView->m_wndWTK.GetSafeHwnd ())
		{
			pWTKView->m_WTKGraphics.CreateArticulationNodes (dynamic_cast <CdmvArticulationData*> 
				(m_pSystemData));
		}
	}

		// View the system
	if (GetWTKView ()->m_wndWTK.IsWtkInitialized ())
	{
		WTwindow_zoomviewpoint(WTuniverse_getwindows());
	
		GetWTKView ()->m_WTKGraphics.UpdateCamera (FALSE);
	}

#endif
}

void CDMViewerDoc::OpenArticulationFile(CString strFile, CString strPath)
{
	// Note that the file may not exist, but if not, it will be taken care of in
	// the parser

	// Deallocate any existing articulation
	DeleteArticulation ();

	CParserDM::ParseDMFile (strPath + strFile, &m_pSystemData);
	if (!m_pSystemData)
	{
		// force a new document action
		OnArticulationNewArticulationFile ();
	}
	else
	{
		m_pCdmvCFGData->SetFirstArticulationFile (strFile, strPath);
	}

}

void CDMViewerDoc::DeleteCFG()
{
	if (m_pCdmvCFGData)
	{
		delete m_pCdmvCFGData;
		m_pCdmvCFGData = NULL;
	}
}

void CDMViewerDoc::OnControlSelectControlDll() 
{
	// Get a copy of the current control to initialize the open dialog
	CString strCurrentControlFile, strCurrentControlPath;
	m_pCdmvCFGData->GetFirstControlFile (strCurrentControlFile, strCurrentControlPath);

	CFileDialog dlg (TRUE, /* make an open dlg */
		".dll", /* default extension */
		strCurrentControlFile, /* initial filename */
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"Control DLL (*.dll)|*.dll||",	/* filter */
		NULL /* parent */
		);

	if (strCurrentControlPath.GetLength () > 0)
		dlg.m_ofn.lpstrInitialDir = strCurrentControlPath;

	if (dlg.DoModal () == IDOK)
	{	
		CString strPath;
		CString strFile = dlg.GetFileName ();
		
		BOOL bFindFile = CFindFile::FindFile (CONTROL_FILE_TYPE, 
			strFile, strPath);
		if (!bFindFile || ((strPath + strFile) != dlg.GetPathName ()))
		{
			if (IDYES == AfxMessageBox (FILE_NOT_FOUND_MSG, MB_YESNO))
			{
				strFile = dlg.GetPathName ();
				strPath = "";
			}
			else
			{
				// strFile stays the same
				// Strip off the file name from the full path
				strPath = (dlg.GetPathName ()).Left (dlg.GetPathName ().GetLength () -
					strFile.GetLength ());
			}
		}
		
		m_pCdmvCFGData->SetFirstControlFile(strFile, strPath);			
	}		
}

BOOL CDMViewerDoc::ValidateStateBeforeDynaMechs()
{
	ASSERT (m_pSystemData);
	ASSERT (m_pEnvironmentData);

	// Needs to have a controller
	CString strCurrentControlFile, strCurrentControlPath;
	m_pCdmvCFGData->GetFirstControlFile (strCurrentControlFile, strCurrentControlPath);

	if (strCurrentControlFile.GetLength () == 0)
	{
		AfxMessageBox ("Please choose a control DLL before simulating.");
		return FALSE;
	}

	return TRUE;
}

void CDMViewerDoc::OnUpdateArticulationNewarticulationfile(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		
}

void CDMViewerDoc::OnUpdateArticulationOpenarticulationfile(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		
}

void CDMViewerDoc::OnUpdateArticulationSavearticulationfile(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		
}

void CDMViewerDoc::OnUpdateArticulationSavearticulationfileas(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		
}

void CDMViewerDoc::OnUpdateControlSelectcontroldll(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		
}

void CDMViewerDoc::OnUpdateEnvironmentEditenvironmentproperities(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		
}

void CDMViewerDoc::OnUpdateEnvironmentNewenvironmentfile(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		
}

void CDMViewerDoc::OnUpdateEnvironmentOpenenvironmentfile(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		
}

void CDMViewerDoc::OnUpdateEnvironmentSaveenvironment(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);	
}

void CDMViewerDoc::OnUpdateEnvironmentSaveenvironmentas(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		
}

void CDMViewerDoc::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		
}

void CDMViewerDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);		
		
}

CdmvEnvironmentData* CDMViewerDoc::GetEnvironmentData()
{
	return m_pEnvironmentData;
}

void CDMViewerDoc::UpdateSimulationWithCFGParameters()
{
	m_DynaMechs.SetCFGDataPointer (m_pCdmvCFGData);

	// Apply background color
	COLORREF crBackground = m_pCdmvCFGData->GetBackgroundColor ();
#ifdef WTK_LICENSE_AVAILABLE
	if (GetWTKView ()->m_wndWTK.IsWtkInitialized ())
	{	WTuniverse_setbgrgb (GetRValue (crBackground),
			GetGValue (crBackground), GetBValue (crBackground));

		// Reset Camera Perspective
		OnButtonViewUser();
	}

#endif

}

void CDMViewerDoc::OnCfgfileEditSimulationProperties() 
{
	CDlgConfigProperties dlg;
	dlg.SetDataClass (m_pCdmvCFGData);
	dlg.SetCameraDataClass (&m_CameraData);
	dlg.SetSystemDataClass (m_pSystemData);
	dlg.SetViewpointPointer(GetWTKView());

	if (dlg.DoModal () == IDOK)
	{
		// Currently, there isn't the ability to edit the other files
		// from this dialog

		// Send the new properties to the simulation
		UpdateSimulationWithCFGParameters ();
	}
}

void CDMViewerDoc::ResetSimulationPropertiesToDefaults()
{
//	m_strtCFGParameters.dIntegrationStepSize = .01;
//	m_strtCFGParameters.nDisplayRate = 1;	

	UpdateSimulationWithCFGParameters ();
}

void CDMViewerDoc::OnUpdateFileMruFile(CCmdUI* pCmdUI) 
{
	// This is a little bit of a hack, maybe there's a real way to do this but...
	// Apparently MFC's implementation of the MRU works by handling the default 
	// processing of the ON_UPDATE_COMMAND_UI of the ID_FILE_MRU_FILE1.  So if I
	// just override the command, the MRU list is never formed.  Consequently, when
	// in edit mode (which is the state during start-up -- this is necessary!!)
	// the message is passed on to an CDMViewerApp function that calls 
	// a protected CWinApp function to handle the update command (which in turn
	// builds/maintains the MRU).  Otherwise, I just do a straight disable.  Note that
	// if the message is passed on, the framework will enable all of the MRU entries, which
	// is why I don't pass it when I want them disabled.
	if (!m_bEditState || m_bPlaybackMode)
	{
		pCmdUI->Enable (FALSE);
	}
	else
	{
		pCmdUI->Enable (TRUE);	
		((CDMViewerApp*) AfxGetApp ())->UpdateMRU (pCmdUI);
	}
}

void CDMViewerDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	if (!m_bEditState || m_bPlaybackMode)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);	
		
}

void CDMViewerDoc::OnButtonViewUser()
{
#ifdef WTK_LICENSE_AVAILABLE
		WTq wtq;
		WTp3 wtp3, wtp3COIOffset;
		double x, y, z;


		// Clear the current center of interest and set to the saved one
		((CdmvArticulationData*) m_pSystemData)->ClearCameraCenterOfInterest();

		CdmvLinkData* pLink = ((CdmvArticulationData*) m_pSystemData)->FindLinkByName(m_pCdmvCFGData->GetCenterOfInterestName());

		CString strInertialAxes;
		strInertialAxes.LoadString(IDS_STRING_INERTIAL_AXES);

		if (pLink == NULL)
		{	// this means either the articulation or the inertial axes were set 
			//	or the link couldn't be found
			
			if (m_pCdmvCFGData->GetCenterOfInterestName() == ((CdmvArticulationData*) m_pSystemData)->GetName())
			{
				// Articulation is the center of interest
				((CdmvArticulationData*) m_pSystemData)->IsCameraCenterOfInterest(TRUE);
			}
			
			// the default is inertial axes
		}
		else
		{	// did find the link, so set it as the center of interest
			pLink->IsCameraCenterOfInterest(TRUE);
		}

		m_pCdmvCFGData->GetCoiOffset(&x, &y, &z);
		wtp3COIOffset[X] = x;
		wtp3COIOffset[Y] = y;
		wtp3COIOffset[Z] = z;

		m_pCdmvCFGData->GetOrientation(wtq);
		m_pCdmvCFGData->GetPosition(wtp3);
		m_CameraData.SetCenterOfInterestOffset(wtp3COIOffset);
		GetWTKView ()->m_wndWTK.SetViewpointOrientation (wtq);
		GetWTKView ()->m_wndWTK.SetViewpointPosition (wtp3);

    double ViewAngleDeg;
    m_pCdmvCFGData->GetViewAngle_Degree (&ViewAngleDeg);
    WTwindow_setviewangle (WTuniverse_getwindows(), (float) ViewAngleDeg*PI/180);
    m_CameraData.SetViewAngleDegree (ViewAngleDeg);

#endif
}

void CDMViewerDoc::OnButtonViewLeft() 
{
	WTp3 wtp3 = {0, -1, 0};
	WTq wtq;

	WTq_construct (wtp3, (float) PI/2, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_wndWTK.SetViewpointOrientation (wtq);
#endif
}

void CDMViewerDoc::OnButtonViewBack() 
{
	WTp3 wtp3 = {0, -1, 0};
	WTq wtq;

	WTq_construct (wtp3, (float) PI, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_wndWTK.SetViewpointOrientation (wtq);
#endif	
}

void CDMViewerDoc::OnButtonViewBottom() 
{
	WTp3 wtp3 = {1, 0, 0};
	WTq wtq;

	WTq_construct (wtp3, (float)  -PI/2, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_wndWTK.SetViewpointOrientation (wtq);
#endif	
}

void CDMViewerDoc::OnButtonViewFront() 
{
	WTp3 wtp3 = {0, 0, -1};
	WTq wtq;

	WTq_construct (wtp3, 0.0f, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_wndWTK.SetViewpointOrientation (wtq);
#endif
}

void CDMViewerDoc::OnButtonViewRight() 
{
	WTp3 wtp3 = {0, -1, 0};
	WTq wtq;

	WTq_construct (wtp3, (float) -PI/2, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_wndWTK.SetViewpointOrientation (wtq);
#endif	
}

void CDMViewerDoc::OnButtonViewTop() 
{
	WTp3 wtp3 = {1, 0, 0};
	WTq wtq;

	WTq_construct (wtp3, (float) PI/2, wtq);

#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_wndWTK.SetViewpointOrientation (wtq);
#endif	
}

void CDMViewerDoc::OnButtonZoomIn() 
{
#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_wndWTK.ZoomViewpoint (TRUE);
#endif
}

void CDMViewerDoc::OnButtonZoomOut() 
{
#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_wndWTK.ZoomViewpoint (FALSE);
#endif
}

void CDMViewerDoc::OnButtonToggleAxes() 
{
	m_bShowAxes	= !m_bShowAxes;

}

void CDMViewerDoc::OnUpdateButtonToggleAxes(CCmdUI* pCmdUI) 
{
	if (m_bShowAxes)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

/*
void CDMViewerDoc::OnUpdateArticulationNewclosedarticulation(CCmdUI* pCmdUI) 
{
	if (!m_bEditState)
		pCmdUI->Enable (FALSE);
	else
		pCmdUI->Enable (TRUE);
}


void CDMViewerDoc::OnArticulationNewclosedarticulation() 
{
	if (m_pSystemData)
	{
		delete m_pSystemData;
		m_pCdmvCFGData->SetFirstArticulationFile ("", "");
	}

	// add an articulation node to start with
	try {
		m_pSystemData = new CdmvClosedArticulationData;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}
	
	UpdateArticulationDisplay ();	
}
*/
void CDMViewerDoc::OnSetupDefaultpaths() 
{
//	CDlgSetupPaths dlg;
	
//	dlg.DoModal ();
}


void CDMViewerDoc::KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// The views pass key downs to here.  If in play mode, the keys are passed
	// on to the DynaMechs class
	if (!m_bEditState)
		m_DynaMechs.KeyDown (nChar, nRepCnt, nFlags);
}

void CDMViewerDoc::OnSetupNodisplaymodeduringsimulation() 
{
	// Toggle the state
	if (m_DynaMechs.GetNoDisplayMode ())
		m_DynaMechs.SetNoDisplayMode (FALSE);
	else
		m_DynaMechs.SetNoDisplayMode (TRUE);
}

void CDMViewerDoc::OnUpdateSetupNodisplaymodeduringsimulation(CCmdUI* pCmdUI) 
{
	if (!m_bEditState && !m_bRecordMode) // Can't have no display mode when recording
			// because record only captures data when the screen is updateded
	{
		pCmdUI->Enable (TRUE);
		if (m_DynaMechs.GetNoDisplayMode ())
			pCmdUI->SetCheck ();
		else
			pCmdUI->SetCheck (FALSE);
	}
	else
	{
		pCmdUI->Enable (FALSE);
		if (m_DynaMechs.GetNoDisplayMode ())
			pCmdUI->SetCheck ();
		else
			pCmdUI->SetCheck (FALSE);
	}
}

// Due to how real time is calculated, it will be difficult to sync up real time
// if it is dynamically changed during the simulation; consequently, this will
// only be edited during edit mode.
void CDMViewerDoc::OnUpdateCfgfileEditsimulationproperties(CCmdUI* pCmdUI) 
{
	if (m_bEditState && !m_bPlaybackMode)
		pCmdUI->Enable (TRUE);	
	else
		pCmdUI->Enable (FALSE);
}

const CDynaMechs* CDMViewerDoc::GetDynaMechs() const
{
	return &m_DynaMechs;
}


CDMTreeView* CDMViewerDoc::GetTreeView()
{
	POSITION positionView = GetFirstViewPosition ();
	CView *pView = GetNextView (positionView);
	if (typeid (*pView) == typeid (CDMTreeView))
		return dynamic_cast <CDMTreeView*> (pView);
	else
	{
		// Just two views, so pick up the other
		pView = GetNextView (positionView);
		// Hack - In order to support switching from any state to any state, the user
		// could go from playback to simulation.  In that case, this function won't
		// get called until after the tree view has been replaced by the IOview sim
		// window (because it is handled, and then passed down to the CDMViewerDoc
		if (typeid (*pView) == typeid (CDMTreeView))
			return dynamic_cast <CDMTreeView*> (pView);
		else
			return NULL;
	}
}

CWTKView* CDMViewerDoc::GetWTKView()
{
	POSITION positionView = GetFirstViewPosition ();
	CView *pView = GetNextView (positionView);
	if (typeid (*pView) == typeid (CWTKView))
		return dynamic_cast <CWTKView*> (pView);
	else
	{
		// Just two views, so pick up the other.
		pView = GetNextView (positionView);
		ASSERT (typeid (*pView) == typeid (CWTKView));
		return dynamic_cast <CWTKView*> (pView);
	}
}

CIOView* CDMViewerDoc::GetIOView()
{
	POSITION positionView = GetFirstViewPosition ();
	CView *pView = GetNextView (positionView);
	if (typeid (*pView) == typeid (CIOView))
		return dynamic_cast <CIOView*> (pView);
	else
	{
		// Just two views, so pick up the other.
		pView = GetNextView (positionView);
		ASSERT (typeid (*pView) == typeid (CIOView));
		return dynamic_cast <CIOView*> (pView);
	}
}


void CDMViewerDoc::OnButtonRecord() 
{
	// Toggle the record state
	m_bRecordMode = !m_bRecordMode;
	
	// If in record mode, initialize it
	if (m_bRecordMode)
	{
		// Pick up the articulation file
		CString strArticulationFile, strArticulationPath;
		m_pCdmvCFGData->GetFirstArticulationFile (strArticulationFile, strArticulationPath);
		// Pick up the environment file
		CString strEnvironmentFile, strEnvironmentPath;
		m_pCdmvCFGData->GetEnvironmentFile (strEnvironmentFile, strEnvironmentPath);
				
		m_PlaybackData.Initialize (GetNumberOfMovableObjects (),
			strArticulationPath, strArticulationFile,
			strEnvironmentPath, strEnvironmentFile);
	}

}

void CDMViewerDoc::OnUpdateButtonRecord(CCmdUI* pCmdUI) 
{
	if (m_bEditState || m_bPlaybackMode // Can't record in playback
		|| m_DynaMechs.GetNoDisplayMode ()) // Since record only captures data when the screen
														// is updated, can't record if not updating screen
	{
		pCmdUI->Enable (FALSE);
		pCmdUI->SetCheck (0);
	}
	else
	{
		pCmdUI->Enable (TRUE);
		if (m_bRecordMode)
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}	
}

// Returns the number of moveable objects in the current configuration
int CDMViewerDoc::GetNumberOfMovableObjects()
{
	// Find the number of links in the current articulation
	int nNumberOfLinks= dynamic_cast <CdmvArticulationData*> (m_pSystemData)->GetNumberOfLinks ();

	// Check if there are any moveable items in the environment
	int nNumberOfMovableEnvironmentObjects = 0;
	if (m_pEnvironmentData->GetEnvironmentType () == ENV_TREADMILL)
		// Treadmill environment has one moving roller (with two instances).
		nNumberOfMovableEnvironmentObjects = 1;

	return nNumberOfLinks + nNumberOfMovableEnvironmentObjects + 1;
		// Add one to hold the position and orientation of the articulation coordinate frame
}

void CDMViewerDoc::OnButtonPlayback() 
{
	// If in sim mode, back out to edit mode, then proceed
	if (!m_bEditState)
		AfxGetMainWnd ()->SendMessage (WM_COMMAND, ID_VIEW_TOGGLESTATE);

	
	// Toggle the playback state
	m_bPlaybackMode  = !m_bPlaybackMode;

	if (m_bPlaybackMode)
	{
		// Check if the same data
		// Pick up the articulation file
		CString strArticulationFile, strArticulationPath;
		m_pCdmvCFGData->GetFirstArticulationFile (strArticulationFile, strArticulationPath);
		// Pick up the environment file
		CString strEnvironmentFile, strEnvironmentPath;
		m_pCdmvCFGData->GetEnvironmentFile (strEnvironmentFile, strEnvironmentPath);
				

		if (!m_PlaybackData.CheckFiles (
			strArticulationPath, strArticulationFile,
			strEnvironmentPath, strEnvironmentFile, FALSE))
		{
			if (IDNO == AfxMessageBox ("Warning: The articulation or environment file has changed since recording\n\
the playback data.  Are you sure you want to run the playback?", MB_YESNO))
			{
				// Then back out
				m_bPlaybackMode = FALSE;
				return;
			}
		}

		// Disable any selection boxes (in WTK view, but selected item stored in tree view)
		GetTreeView ()->ClearBoundingBoxOnSelectedItem ();

		// Disable the tree view so it doesn't accept input
		GetTreeView ()->EnableWindow (FALSE);
		
		// Tell where to display to
		m_DynaMechs.SetPlayerPointer (&(GetWTKView ()->m_WTKGraphics));

		// Pick up the start and end times for the playback data - it is assumed
		// that there is valid playback data
		double dStartTime, dEndTime;
		m_PlaybackData.GetPlaybackTimes (dStartTime, dEndTime);

		// Initialize the playback
		m_DynaMechs.InitializePlayback (dStartTime, dEndTime, 
			m_pSystemData, m_pEnvironmentData, &m_PlaybackData);

	}
	else
	{
		// Make sure it is not playing
		m_bPlay = FALSE;

		// Hack - In order to support switching from any state to any state, the user
		// could go from playback to simulation.  In that case, this function won't
		// get called until after the tree view has been replaced by the IOview sim
		// window (because it is handled, and then passed down to the CDMViewerDoc
		CView* pView = GetTreeView ();
		if (pView)
			pView->EnableWindow (TRUE);

		// reset dynamics to uninitialize all the stuff
		m_DynaMechs.ResetDynaMechs ();

#ifdef WTK_LICENSE_AVAILABLE
		CWTKView* pWTKView = GetWTKView ();
		pWTKView->m_WTKGraphics.ResetArticulationToInitialValues (dynamic_cast 
			<CdmvArticulationData*> (m_pSystemData));
		pWTKView->m_WTKGraphics.ResetEnvironmentToInitialValues (m_pEnvironmentData);
#endif
	}

	
}

void CDMViewerDoc::OnUpdateButtonPlayback(CCmdUI* pCmdUI) 
{

	// Check to see if the number of items in the match that in the
	// playback data to decide if enable the button
	if (GetNumberOfMovableObjects () == m_PlaybackData.GetNumberOfItems () &&
		GetNumberOfMovableObjects () > 0 && m_PlaybackData.ContainsData ())
	{
		pCmdUI->Enable (TRUE);
		if (m_bPlaybackMode)
			pCmdUI->SetCheck (1);
		else
			pCmdUI->SetCheck (0);
	}
	else
		pCmdUI->Enable (FALSE);
}

void CDMViewerDoc::OnPlaybackOpenplaybackfile() 
{
	CFileDialog dlg (TRUE, /* make an open dlg */
		".rbp", /* default extension */
		m_strPlaybackFile, /* initial filename */
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"Playback File (*.rbp)|*.rbp;||",	/* filter */
		NULL /* parent */
		);
	
	if (m_strPlaybackPath.GetLength () > 0)
		dlg.m_ofn.lpstrInitialDir = m_strPlaybackPath;

	if (dlg.DoModal () == IDOK)
	{	
		m_strPlaybackFile = dlg.GetFileName ();
		// Get the full path (includes file name)
		m_strPlaybackPath = dlg.GetPathName ();
		// Subtract off the filename
		m_strPlaybackPath = m_strPlaybackPath.Left (m_strPlaybackPath.GetLength() - 
			m_strPlaybackFile.GetLength ());

		// Open the file
		if (!CParserPlayback::ParsePlaybackFile (dlg.GetPathName (), &m_PlaybackData))
		{
			// Failed to parse - the parser has already cleanup the playback data, so
			// just clear the files
			m_strPlaybackFile.Empty ();
			m_strPlaybackPath.Empty ();
		}
		else
		{
			// Opened file OK - now initialize the playback state if in the playback mode
			if (m_bPlaybackMode)
			{
				// Initialized by simulating pushing the stop button
				AfxGetMainWnd ()->SendMessage (WM_COMMAND, ID_BUTTON_STOP);
			}
		}
		

	}	
	
}

void CDMViewerDoc::OnUpdatePlaybackOpenplaybackfile(CCmdUI* pCmdUI) 
{
	// Open any time
	
}

void CDMViewerDoc::OnPlaybackSaveplayback() 
{
	if (m_strPlaybackFile.IsEmpty ())
	{
		// Then need to get a filename so call Save As for the playback
		// Note that SaveAs calls this function to handle the actual saving, but
		// when it does, a filename will exist
		OnPlaybackSaveplaybackfileas ();
	}
	else
	{
		ASSERT (AfxIsValidAddress (&m_PlaybackData, sizeof(CPlaybackData)));

		// Have a filename so save to it
		BOOL bReturnStatus = CGeneratePlaybackFile::CreatePlaybackFile
			(m_strPlaybackPath + m_strPlaybackFile, &m_PlaybackData);
		ASSERT (bReturnStatus);

		// Now that it is saved, mark as clean again
		m_bPlaybackChanged = FALSE;
	}	
}

void CDMViewerDoc::OnUpdatePlaybackSaveplayback(CCmdUI* pCmdUI) 
{
	// Only enabled if there is data 
	if (m_PlaybackData.ContainsData ())
	{
		pCmdUI->Enable (TRUE);
	}
	else
		pCmdUI->Enable (FALSE);
}

void CDMViewerDoc::OnPlaybackSaveplaybackfileas() 
{
	CFileDialog dlg (FALSE, /* make an save dlg */
		".rbp", /* default extension */
		m_strPlaybackFile, /* initial filename */
		OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"Playback File (*.rbp)|*.rbp;||",	/* filter */
		NULL /* parent */
		);

	if (m_strPlaybackPath.GetLength () > 0)
		dlg.m_ofn.lpstrInitialDir = m_strPlaybackPath;
	
	if (dlg.DoModal () == IDOK)
	{	
		m_strPlaybackFile = dlg.GetFileName ();
		// Get the full path (includes file name)
		m_strPlaybackPath = dlg.GetPathName ();
		// Subtract off the filename
		m_strPlaybackPath = m_strPlaybackPath.Left (m_strPlaybackPath.GetLength() - 
			m_strPlaybackFile.GetLength ());

		// Save it
		OnPlaybackSaveplayback ();
	}	
}

void CDMViewerDoc::OnUpdatePlaybackSaveplaybackfileas(CCmdUI* pCmdUI) 
{
	// Only enabled if there is data
	if (m_PlaybackData.ContainsData ())
	{
		pCmdUI->Enable (TRUE);
	}
	else
		pCmdUI->Enable (FALSE);	
}

void CDMViewerDoc::OnButtonBuild() 
{
	// If in sim mode, this is the same as toggling the sim button
	if (!m_bEditState)
	{
		VERIFY(AfxGetMainWnd ()->PostMessage (WM_COMMAND, ID_VIEW_TOGGLESTATE));
	}
	else if (m_bPlaybackMode) // check if in playback mode, then like toggling the playback button
	{
		VERIFY(AfxGetMainWnd ()->PostMessage (WM_COMMAND, ID_BUTTON_PLAYBACK));
	}
	
}

void CDMViewerDoc::OnUpdateButtonBuild(CCmdUI* pCmdUI) 
{
	if (m_bEditState && !m_bPlaybackMode)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CDMViewerDoc::OnButtonShowLinkAxes() 
{
	// Pick up the articulation
	CdmvArticulationData* pArticulation = dynamic_cast <CdmvArticulationData*> (m_pSystemData);

	// Show articulation axes
	pArticulation->ShowWtkAxes (TRUE);

	// Go through each link and enable
	int i;
	for (i = 0; i < pArticulation->GetNumberOfLinks (); i++)
		pArticulation->m_arrayLinks.GetAt (i).pLink->ShowWtkAxes (TRUE);
	
}

void CDMViewerDoc::OnButtonHideLinkAxes() 
{
	// Pick up the articulation
	CdmvArticulationData* pArticulation = dynamic_cast <CdmvArticulationData*> (m_pSystemData);

	// Show articulation axes
	pArticulation->ShowWtkAxes (FALSE);

	// Go through each link and enable
	int i;
	for (i = 0; i < pArticulation->GetNumberOfLinks (); i++)
		pArticulation->m_arrayLinks.GetAt (i).pLink->ShowWtkAxes (FALSE);
		
}

CCameraData* CDMViewerDoc::GetCameraData()
{
	return &m_CameraData;
}

void CDMViewerDoc::OnViewCameracontrol() 
{
	// Dialog
	CDlgCameraControl dlg;
	
	// Set the data for the dialog
	dlg.SetDataClassPointer (&m_CameraData);
	dlg.SetCFGClassPointer (m_pCdmvCFGData);

	// Save if the current camera control type
	BOOL bPanMode = m_CameraData.GetViewInPanMode ();
	BOOL bUseViewport = m_CameraData.GetUseViewportFrameForExamineView ();

	// Set if the inertial axes are the COI
	// If the COI is the intertial axes, the following will come back NULL, otherwise
	// it will return a pointer to the WTK node that is the COI.
	if (!dynamic_cast <CdmvArticulationData*> (m_pSystemData)->GetCameraCenterOfInterest ())
		dlg.SetInertialAxesAsCoi (TRUE);
	else
		dlg.SetInertialAxesAsCoi (FALSE);


	// Display dialog
	dlg.DoModal ();

	// Update the COI - if the inertial axes are selected as the COI, this will make sure
	// that no other WTK node is selected (which implies that inertial axes will be used)
	if (dlg.GetInertialAxesAsCoi ())
		dynamic_cast <CdmvArticulationData*> (m_pSystemData)->ClearCameraCenterOfInterest ();


	// If changing from pan to examine, need to reorient the view to the spherical
	// coords from the current location.
	if (bPanMode && !m_CameraData.GetViewInPanMode ())
	{
		GetWTKView ()->m_WTKGraphics.UpdateCamera (FALSE);
	}
	// If in examine view - update in case of change of COI
	else if (!m_CameraData.GetViewInPanMode ())
	{
		GetWTKView ()->m_WTKGraphics.UpdateCamera (FALSE);
	}

	// If changing to inertial frame examine view, need to reorient
	if (bUseViewport && !m_CameraData.GetViewInPanMode () && 
		!m_CameraData.GetUseViewportFrameForExamineView ())
	{
		GetWTKView ()->m_WTKGraphics.UpdateCamera (TRUE);
	}
}



// Will spawn the RBModler Executable.  It is assumed that it will be in the same
// directory RobotBuilder
void CDMViewerDoc::OnButtonRbmodler() 
{
		SHELLEXECUTEINFO theShellExecuteInfo;
		theShellExecuteInfo.cbSize = sizeof (SHELLEXECUTEINFO);
		theShellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		theShellExecuteInfo.hwnd = NULL; /* Parent window */
		theShellExecuteInfo.lpVerb = TEXT("open"); /* Verb */
		theShellExecuteInfo.lpFile = TEXT ("RobotModeler.exe");
		theShellExecuteInfo.lpParameters = NULL;
		theShellExecuteInfo.lpDirectory = CFindFile::GetInitialWorkingDirectory (); /* Working Directory */
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

void CDMViewerDoc::OnViewCameralight() 
{
	WTnode* wtnodeCameraLight = GetWTKView ()->m_WTKGraphics.GetCameraDirectedLight ();
	if (WTlightnode_getintensity (wtnodeCameraLight) > 0)
		WTlightnode_setintensity (wtnodeCameraLight, 0);
	else
		WTlightnode_setintensity (wtnodeCameraLight, CAMERA_LIGHT_INTENSITY);

}

void CDMViewerDoc::OnUpdateViewCameralight(CCmdUI* pCmdUI) 
{
	WTnode* wtnodeCameraLight = GetWTKView ()->m_WTKGraphics.GetCameraDirectedLight ();
	if (WTlightnode_getintensity (wtnodeCameraLight) > 0)
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CDMViewerDoc::SetClipboardData(CdmvLinkData *pLinkData)
{
	m_pLinkClipboard = pLinkData;
}

CdmvLinkData* CDMViewerDoc::GetClipboardData() const
{
	return m_pLinkClipboard;
}

void CDMViewerDoc::OnHelpUsersguide() 
{
	CString strDirectory = CFindFile::GetInitialWorkingDirectory () + _T("\\Docs");

	SHELLEXECUTEINFO theShellExecuteInfo;
	theShellExecuteInfo.cbSize = sizeof (SHELLEXECUTEINFO);
	theShellExecuteInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	theShellExecuteInfo.hwnd = NULL; /* Parent window */
	theShellExecuteInfo.lpVerb = TEXT("open"); /* Verb */
	theShellExecuteInfo.lpFile = TEXT ("RobotBuilder User's Guide.pdf");
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

void CDMViewerDoc::OnButtonexamine() 
{
	m_CameraData.SetViewInPanMode(FALSE);

	// Update the camera to adjust for the (possibly) new center
	GetWTKView()->m_WTKGraphics.UpdateCamera(FALSE);
}

void CDMViewerDoc::OnUpdateButtonexamine(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable (TRUE);
	if (!m_CameraData.GetViewInPanMode())
		pCmdUI->SetCheck (1);
	else
		pCmdUI->SetCheck (0);
}

void CDMViewerDoc::OnButtonpan() 
{
	m_CameraData.SetViewInPanMode(TRUE);	
}

void CDMViewerDoc::OnUpdateButtonpan(CCmdUI* pCmdUI) 
{
	if (m_CameraData.GetViewInPanMode())
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}

void CDMViewerDoc::OnHelpTutorial() 
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
