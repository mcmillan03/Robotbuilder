// RBModelerRBMGraphicView.cpp: implementation of the CRBModelerRBMGraphicView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "RBModelerRBMGraphicView.h"
#include "MainFrm.h"
#include "RBModelerDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/* General Notes.
When this was originally designed, it was decided to make the function static to mirror
WTK's function (all in C).  It makes it convienent to access the model, but it is probably
not as clean as a C++ object would have been.

  */
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WTnode* CRBModelerRBMGraphicView::m_wtnodeCameraDirectedLight = NULL;

CRBModelerRBMGraphicView::CRBModelerRBMGraphicView()
{

}

CRBModelerRBMGraphicView::~CRBModelerRBMGraphicView()
{

}

void CRBModelerRBMGraphicView::AddPrimitive(CPrimitive *pPrimitive)
{
#ifdef WTK_LICENSE_AVAILABLE
	WTnode* wtnodeModel = GetModelNode ();
	
	CRBMGraphicView::AddPrimitive (pPrimitive, wtnodeModel);

	// Set the node's data to the primitive pointer so we can relate it back
//	WTnode_setdata 

#endif
}

// This isn't a function implemented in the regular CRBMGraphicView because it is
// not a functionality needed to display a RBM Model
void CRBModelerRBMGraphicView::DeletePrimitive(const CPrimitive *pPrimitive)
{
#ifdef WTK_LICENSE_AVAILABLE
	ASSERT (pPrimitive);

	WTnode* wtnodePrimitive = GetPrimitiveNode (pPrimitive);
	ASSERT (wtnodePrimitive);

	// It is assumed that the primitive has no children, but verify that now
	ASSERT (WTnode_numchildren (wtnodePrimitive) == 0);

	// Delete the node from the scenegraph
	FLAG flagStatus = WTnode_delete (wtnodePrimitive);
	ASSERT (flagStatus);
#endif
}

void CRBModelerRBMGraphicView::LoadNewModel(const CModel *pModel)
{
#ifdef WTK_LICENSE_AVAILABLE
	WTnode* wtnodeModel;
	CRBMGraphicView::LoadNewModel (pModel, &wtnodeModel);

	// Add the node to the scenegraph
	FLAG flagStatus = WTnode_addchild (WTuniverse_getrootnodes (), wtnodeModel);
	ASSERT (flagStatus);

	// Set the name of the model so it can be found later.
	flagStatus = WTnode_setname (wtnodeModel, STR_MODEL_NAME);
	ASSERT (flagStatus);

	WTwindow_zoomviewpoint(WTuniverse_getwindows());
	// Update the camera for the new model
	UpdateCamera (TRUE);
#endif
}

// This is used to primarily to update primitive paramemters, but since
// a geometry can't be deleted from a WTmovgeometrynode, just delete the whole
// node and create a new one (because the add function also initializes the node
// with the passed orientation, position, scale, etc.
void CRBModelerRBMGraphicView::UpdatePrimitive(CPrimitive *pPrimitive)
{
#ifdef WTK_LICENSE_AVAILABLE
	DeletePrimitive (pPrimitive);

	AddPrimitive (pPrimitive);
#endif
}

void CRBModelerRBMGraphicView::UpdatePrimitivePlacement(CPrimitive *pPrimitive)
{
#ifdef WTK_LICENSE_AVAILABLE
	ASSERT (pPrimitive);

	WTnode* wtnodePrimitive = GetPrimitiveNode (pPrimitive);
	ASSERT (wtnodePrimitive);

	CRBMGraphicView::SetPrimitivePlacement (pPrimitive, wtnodePrimitive);

	// Update the camera (in case this was the COI)
	UpdateCamera (FALSE);
#endif
}

void CRBModelerRBMGraphicView::InitializeScene()
{
#ifdef WTK_LICENSE_AVAILABLE
	
	// Reset the universe by deleting all non-root nods
	WTnode_vacuum ();

	CreateLightNodes ();
	CreateSystemTransform ();
#endif
}

BOOL CRBModelerRBMGraphicView::CreateLightNodes()
{
	BOOL bReturnStatus;
	WTnode* wtnodeRoot = NULL;
	WTnode* wtnodeLight = NULL;

	wtnodeRoot = WTuniverse_getrootnodes ();
	ASSERT (wtnodeRoot);

	/* Load a lights file */
	if (!WTlightnode_load (wtnodeRoot,"RobotModelerLights.wtk")) {
		
		// Ambient light
		VERIFY(wtnodeLight = WTlightnode_newambient (wtnodeRoot));
		WTlightnode_setintensity (wtnodeLight, 0.95f);

//		WTnode* wtnodeLight2;
//		VERIFY(wtnodeLight2 = WTlightnode_newpoint (wtnodeRoot));
//		WTp3 wtp3Pos = {0, 0, 3};
//		VERIFY(WTlightnode_setposition (wtnodeLight2, wtp3Pos));
//		WTlightnode_setintensity (wtnodeLight2, .15);


		// Camera Directed light
		VERIFY(m_wtnodeCameraDirectedLight = WTlightnode_newdirected (wtnodeRoot));
		WTp3 wtp3Direction = {0, 0, -1}; // Change in camera update
		VERIFY(WTlightnode_setdirection (m_wtnodeCameraDirectedLight, wtp3Direction));
		WTlightnode_setintensity (m_wtnodeCameraDirectedLight, CAMERA_LIGHT_INTENSITY);


		bReturnStatus = TRUE;
	}
	else
	{
		// Still enable the camera light
		VERIFY(m_wtnodeCameraDirectedLight = WTlightnode_newdirected (wtnodeRoot));
		WTp3 wtp3Direction = {0, 0, -1}; // Change in camera update
		VERIFY(WTlightnode_setdirection (m_wtnodeCameraDirectedLight, wtp3Direction));
		WTlightnode_setintensity (m_wtnodeCameraDirectedLight, CAMERA_LIGHT_INTENSITY);


		bReturnStatus = TRUE;
	}

	return bReturnStatus;
}

BOOL CRBModelerRBMGraphicView::CreateSystemTransform()
{
	WTnode* wtnodeRoot = NULL;

	wtnodeRoot = WTuniverse_getrootnodes ();
	ASSERT (wtnodeRoot);
	
	WTnode* wtnodeUniverseAdjust = WTxformnode_new (wtnodeRoot);
	WTnode_rotation (wtnodeUniverseAdjust, 0, 1.5708f, 0, WTFRAME_PARENT);

	return TRUE;
}

WTnode* CRBModelerRBMGraphicView::GetModelNode()
{
	WTnode* wtnodeModel;

	// Only one main model in the Modeler.
	wtnodeModel = WTuniverse_findnodebyname (STR_MODEL_NAME, 0);
	ASSERT (wtnodeModel);

	return wtnodeModel;
}

WTnode* CRBModelerRBMGraphicView::GetPrimitiveNode(const CPrimitive *pPrimitive)
{
	ASSERT (pPrimitive);

	// Make a string out of the pointer value
	// Note the pointer is 32 bit plus NULL
	char szPrimtiveNodeName[8 + 1];

	int nNumStoredBytes = sprintf (szPrimtiveNodeName, "%08x", reinterpret_cast <const void*> (pPrimitive));

	// Make sure 8 bytes were stored (note terminating NULL not included in returned count)
	ASSERT (nNumStoredBytes == 8);

	WTnode* wtnodePrimitive = WTuniverse_findnodebyname (szPrimtiveNodeName, 0);
	// Make sure node was found.
	ASSERT (wtnodePrimitive);

	return wtnodePrimitive;
}


// Makes relative changes
void CRBModelerRBMGraphicView::UpdatePrimitiveScale(CPrimitive *pPrimitive)
{
	ASSERT (pPrimitive);

	// Get the scale class.
	CPrimitiveScale* pPrimitiveScale = pPrimitive->GetPrimitiveScale ();
	ASSERT (pPrimitiveScale);
#ifdef WTK_LICENSE_AVAILABLE
	WTnode* wtnodePrimitive = GetPrimitiveNode (pPrimitive);
	ASSERT (wtnodePrimitive);

	// Get the scale data.
	structPrimitiveScaleData strtPrimitiveScaleRelativeData;
	pPrimitiveScale->GetPrimitiveScaleRelativeData(&strtPrimitiveScaleRelativeData);
	// Obtain a pointer to the geometry from the movgeomnode describing the primitive
	WTgeometry* wtgeometry;
	wtgeometry = WTnode_getgeometry (wtnodePrimitive);
	ASSERT (wtgeometry);
	// Get the center to scale about
	WTp3 wtp3Midpoint;
	WTgeometry_getmidpoint (wtgeometry, wtp3Midpoint);
	// Build the scaling vector
	WTp3 wtp3Scale;
	wtp3Scale[X] = strtPrimitiveScaleRelativeData.dXScale;
	wtp3Scale[Y] = strtPrimitiveScaleRelativeData.dYScale;
	wtp3Scale[Z] = strtPrimitiveScaleRelativeData.dZScale;
	// Apply scale - use stretch function so can indepently scale the axes
	WTgeometry_stretch (wtgeometry, wtp3Scale, wtp3Midpoint);
#endif
	// Since the relative change has been applied, reset the relative data in the class
	pPrimitiveScale->ResetRelativeScaleData ();
}

void CRBModelerRBMGraphicView::WTKFGDrawCallback (WTwindow* wtkWindow, FLAG flagEye)
{
	// Set the window font
	WTwindow_set2Dfont (wtkWindow, 0);

	// Get the orientation of the viewpoint
	WTq wtqWorldToViewpoint;
	WTviewpoint_getorientation (WTuniverse_getviewpoint (), wtqWorldToViewpoint);
	// Get the 3x3 form
	WTm3 wtm3_uRv;
	WTq_2m3 (wtqWorldToViewpoint, wtm3_uRv);

	int nWndPosX, nWndPosY, nWndWidth, nWndHeight;
	WTwindow_getposition (wtkWindow, &nWndPosX, &nWndPosY, &nWndWidth, &nWndHeight);
	WTp3 wtp3_uOrigin = {0, 0, 0};
	WTp2 wtp2_sOrigin;
	WTp2 wtp2_sX, wtp2_sY, wtp2_sZ;

	// Get the doc
	CRBModelerApp* pApp = (CRBModelerApp*)AfxGetApp();
	CMainFrame *pFrameWnd = (CMainFrame*)pApp->m_pMainWnd;
	CRBModelerDoc* pDoc = (CRBModelerDoc*)pFrameWnd->GetActiveDocument ();

	
	if (pDoc->ShowInertialAxes ())
	{
		WTp3 wtp3_uX = {1, 0, 0};
		WTp3 wtp3_uY = {0, 0, 1};
		WTp3 wtp3_uZ = {0, -1, 0};

		WTwindow_projectpoint (wtkWindow, NULL, wtp3_uOrigin, wtp2_sOrigin);
		WTwindow_projectpoint (wtkWindow, NULL, wtp3_uX, wtp2_sX);
		WTwindow_projectpoint (wtkWindow, NULL, wtp3_uY, wtp2_sY);
		WTwindow_projectpoint (wtkWindow, NULL, wtp3_uZ, wtp2_sZ);

		// Draw the universe's axes
		WTwindow_set2Dlinewidth (wtkWindow, 2);
		WTwindow_set2Dcolor (wtkWindow, 255, 255, 255);
		WTwindow_draw2Dline (wtkWindow, wtp2_sOrigin[X]/nWndWidth, wtp2_sOrigin[Y]/nWndHeight,
			wtp2_sX[X]/nWndWidth, wtp2_sX[Y]/nWndHeight);
		WTwindow_draw2Dtext (wtkWindow, wtp2_sX[X]/nWndWidth * 1.01, wtp2_sX[Y]/nWndHeight, "X");
		WTwindow_draw2Dline (wtkWindow, wtp2_sOrigin[X]/nWndWidth, wtp2_sOrigin[Y]/nWndHeight,
			wtp2_sY[X]/nWndWidth, wtp2_sY[Y]/nWndHeight);
		WTwindow_draw2Dtext (wtkWindow, wtp2_sY[X]/nWndWidth * 1.01, wtp2_sY[Y]/nWndHeight, "Y");
		WTwindow_draw2Dline (wtkWindow, wtp2_sOrigin[X]/nWndWidth, wtp2_sOrigin[Y]/nWndHeight,
			wtp2_sZ[X]/nWndWidth, wtp2_sZ[Y]/nWndHeight);
		WTwindow_draw2Dtext (wtkWindow, wtp2_sZ[X]/nWndWidth * 1.01, wtp2_sZ[Y]/nWndHeight, "Z");
	}

	// Descend the tree to the primitives and add the axes
	// First get to the main model
	// Recall the first two children are light nodes
	// On the first call, the tree hasn't been built.  So if no children, don't do anything
	int nNumRootChildren = WTnode_numchildren (WTuniverse_getrootnodes ());
	if (nNumRootChildren > 0)
	{
		CModel* pModel = pDoc->GetModel ();

		// Make sure there is a model (might not be if this is called after DeleteContents
		// which is called if a new file is opened)
		if (pModel)
		{
			WTwindow_set2Dlinewidth (wtkWindow, 1);
			WTwindow_set2Dcolor (wtkWindow, 0, 0, 0);

			int nNumPrimitives = pModel->GetNumberOfPrimitives ();
			int nPrimitiveIndex;
			for (nPrimitiveIndex = 0; nPrimitiveIndex < nNumPrimitives; nPrimitiveIndex++)
			{
				// Get a copy of the primitive
				CPrimitive* pPrimitive = pModel->GetPrimitive (nPrimitiveIndex);
				ASSERT (pPrimitive);

				// Check if need to display the axes
				if (pPrimitive->ShowWtkAxes ())
				{
					// Then display the 
					WTnode* wtnodePrimitive = GetPrimitiveNode (pPrimitive);
					ASSERT (wtnodePrimitive);

					// Get the path, so can retrieve the entire transform
					WTnodepath* wtnodepath = WTnodepath_new (wtnodePrimitive, WTuniverse_getrootnodes (), 
						0 // which node (for multiple instances, but not used in RB, so always 0)
						);
					ASSERT (wtnodepath);

					// Get the transform
					WTm4 wtm4_uTp;
					FLAG flagSuccess = WTnodepath_gettransform (wtnodepath, wtm4_uTp);
					ASSERT (flagSuccess);

					// Done with nodepath, so delete it
					VERIFY(WTnodepath_delete (wtnodepath));

					// Local Axes
					WTp3 wtp3_pX = {1, 0, 0};
					WTp3 wtp3_pY = {0, 1, 0};
					WTp3 wtp3_pZ = {0, 0, 1};
					WTp3 wtp3_pOrigin = {0, 0, 0};

					// Transform the points to universe coordinates
					WTp3 wtp3_uX, wtp3_uY, wtp3_uZ, wtp3_uOrigin;	
					WTm4_xformp3 (wtm4_uTp, wtp3_pOrigin, wtp3_uOrigin);
					WTm4_xformp3 (wtm4_uTp, wtp3_pX, wtp3_uX);
					WTm4_xformp3 (wtm4_uTp, wtp3_pY, wtp3_uY);
					WTm4_xformp3 (wtm4_uTp, wtp3_pZ, wtp3_uZ);

					// Project to screen coordinates
					WTp2 wtp2_sOrigin;
					WTp2 wtp2_sX, wtp2_sY, wtp2_sZ;
					WTwindow_projectpoint (wtkWindow, NULL, wtp3_uOrigin, wtp2_sOrigin);
					WTwindow_projectpoint (wtkWindow, NULL, wtp3_uX, wtp2_sX);
					WTwindow_projectpoint (wtkWindow, NULL, wtp3_uY, wtp2_sY);
					WTwindow_projectpoint (wtkWindow, NULL, wtp3_uZ, wtp2_sZ);

					// Draw the universe's axes
					WTwindow_draw2Dline (wtkWindow, wtp2_sOrigin[X]/nWndWidth, wtp2_sOrigin[Y]/nWndHeight,
						wtp2_sX[X]/nWndWidth, wtp2_sX[Y]/nWndHeight);
					WTwindow_draw2Dtext (wtkWindow, wtp2_sX[X]/nWndWidth * 1.01, wtp2_sX[Y]/nWndHeight, "X");
					WTwindow_draw2Dline (wtkWindow, wtp2_sOrigin[X]/nWndWidth, wtp2_sOrigin[Y]/nWndHeight,
						wtp2_sY[X]/nWndWidth, wtp2_sY[Y]/nWndHeight);
					WTwindow_draw2Dtext (wtkWindow, wtp2_sY[X]/nWndWidth * 1.01, wtp2_sY[Y]/nWndHeight, "Y");
					WTwindow_draw2Dline (wtkWindow, wtp2_sOrigin[X]/nWndWidth, wtp2_sOrigin[Y]/nWndHeight,
						wtp2_sZ[X]/nWndWidth, wtp2_sZ[Y]/nWndHeight);
					WTwindow_draw2Dtext (wtkWindow, wtp2_sZ[X]/nWndWidth * 1.01, wtp2_sZ[Y]/nWndHeight, "Z");
				}
			}
		}
	}
}
void CRBModelerRBMGraphicView::WTKDrawCallback(WTwindow *wtkWindow, FLAG flagEye)
{
	// Get the orientation of the viewpoint
	WTq wtqWorldToViewpoint;
	WTviewpoint_getorientation (WTuniverse_getviewpoint (), wtqWorldToViewpoint);
	// Get the 3x3 form
	WTm3 wtm3_uRv;
	WTq_2m3 (wtqWorldToViewpoint, wtm3_uRv);

	WTp3 wtp3Position;
	WTviewpoint_getposition (WTuniverse_getviewpoint (), wtp3Position);

	// Build homog xform
	WTm4 wtm4_uTv, wtm4_vTu;
	WTm4_init (wtm4_uTv);
	WTm4_init (wtm4_vTu);
	int i,j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
			wtm4_uTv[i][j] = wtm3_uRv[i][j];
		wtm4_uTv[i][3] = wtp3Position[i];
	}

	// Invert it
	FLAG flagIsNonSingular = WTm4_invert (wtm4_uTv, wtm4_vTu);
	ASSERT (flagIsNonSingular);

	// Transform some points
	WTp3 wtp3_uOrigin = {0, 0, 0};
	WTp3 wtp3_uX = {1, 0, 0};
	WTp3 wtp3Points[2];

	WTm4_xformp3 (wtm4_vTu, wtp3_uOrigin, wtp3Points[0]);
	WTm4_xformp3 (wtm4_vTu, wtp3_uX, wtp3Points[1]);
	
	WTwindow_draw3Dlines (wtkWindow, wtp3Points, 2, WTLINE_SEGMENTS);
}

void CRBModelerRBMGraphicView::ShowBoundingBox(BOOL bShow, const CPrimitive *pPrimitive)
{
	ASSERT (pPrimitive);


#ifdef WTK_LICENSE_AVAILABLE	
	WTnode* wtnodePrimitive = GetPrimitiveNode (pPrimitive);
	ASSERT (wtnodePrimitive);

	// I assume it is more efficient to call only call WTnode_boundingbox when a change
	// needs to occur because WTnode_hasboundingbox, a query function, has been implemented.
	// Consequently, I use it to determine if I need to specify the state change.
	if (bShow)
	{
		if (!WTnode_hasboundingbox (wtnodePrimitive))
		{
			FLAG flagSuccess = WTnode_boundingbox (wtnodePrimitive, bShow);
			ASSERT (flagSuccess);
		}
	}
	else
	{
		if (WTnode_hasboundingbox (wtnodePrimitive))
		{
			FLAG flagSuccess = WTnode_boundingbox (wtnodePrimitive, bShow);
			ASSERT (flagSuccess);
		}		
	}
#endif
}


void CRBModelerRBMGraphicView::UpdateCamera(BOOL bRecalculateExamineView)
{
	// Find the current camera mode
	CRBModelerApp* pApp = (CRBModelerApp*)AfxGetApp();
	CMainFrame *pFrameWnd = (CMainFrame*)pApp->m_pMainWnd;
	CRBModelerDoc* pDoc = (CRBModelerDoc*)pFrameWnd->GetActiveDocument ();

	if (!pDoc->GetCameraData ()->GetViewInPanMode ())
	{
		// Then examine mode
		// Get the COI node
		WTnode* wtnodeCOI;
		CPrimitive* pPrimitiveCOI = pDoc->GetModel ()->GetCameraCenterOfInterest ();
		if (pPrimitiveCOI)
			wtnodeCOI = GetPrimitiveNode (pPrimitiveCOI);
		else // else no COI selected so use inertial axes
			wtnodeCOI = NULL;

		// Get the offset
		WTp3 wtp3Offset;
		pDoc->GetCameraData ()->GetCenterOfInterestOffset (wtp3Offset);

		WTp3 wtp3COI; // Holds the coi
		
		// If a COI node exists find its transform, otherwise set the COI as the offset
		if (wtnodeCOI)
		{
			// ## Get a transform to the COI
			// Pick up the root node for later calculations
			WTnode* wtnoderoot = WTuniverse_getrootnodes ();
			ASSERT (wtnoderoot);
			// Get the path, so can retrieve the entire transform
			WTnodepath* wtnodepath = WTnodepath_new (wtnodeCOI, wtnoderoot, 
				0 // which node (for multiple instances, but not used in RB, so always 0)
				);
			ASSERT (wtnodepath);

			// Get the transform
			WTm4 wtm4_world2coi;
			FLAG flagSuccess = WTnodepath_gettransform (wtnodepath, wtm4_world2coi);
			ASSERT (flagSuccess);

			// Done with nodepath, so delete it
			VERIFY(WTnodepath_delete (wtnodepath));

			// Transform the offset
			WTm4_xformp3 (wtm4_world2coi, wtp3Offset, wtp3COI);

		}
		else
		{
			// Transform from RB coords to WTK coords
			wtp3COI[X] = wtp3Offset[X];
			wtp3COI[Z] = wtp3Offset[Y];
			wtp3COI[Y] = -wtp3Offset[Z];

		}

		// Set the COI in the camera control and update the view
		if (bRecalculateExamineView)
			pDoc->GetModelView ()->m_wndGraphic.m_pCameraControl->RecalculateExamineViewParameters (wtp3COI);
		else
		{
			if (pDoc->GetCameraData ()->GetUseViewportFrameForExamineView ())
				pDoc->GetModelView ()->m_wndGraphic.m_pCameraControl->UpdateExamineView2 (wtp3COI);
			else
				pDoc->GetModelView ()->m_wndGraphic.m_pCameraControl->UpdateExamineView (wtp3COI);
		}
	}
	// else don't need to update anything because in pan mode
}

WTnode* CRBModelerRBMGraphicView::GetCameraDirectedLight()
{
	return m_wtnodeCameraDirectedLight;
}
