// CameraControl.cpp: implementation of the CExamineView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CameraControl.h"

#ifdef ROBOTBUILDER
#include "DMViewerDoc.h"
#include "MainFrm.h"
#include "DMViewer.h"
#endif

#ifdef ROBOTMODELER
#include "..\RBModeler Source\RBModelerRBMGraphicView.h"
#include "..\RBModeler Source\RBModelerDoc.h"
#include "..\RBModeler Source\MainFrm.h"
#include "..\RBModeler Source\RBModeler.h"
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Default constructor
CCameraControl::CCameraControl(WTsensor *pwtMouse, WTviewpoint *pwtViewpoint)
{
	m_pwtSensor = pwtMouse;
	m_pwtViewpoint = pwtViewpoint;

	// Setup defaults
	m_dRotationScale = 1.0;
	m_dZoomScale = 40.0;
	m_dPanScale = .5;
	m_dMaxRadius = 99999.0;
	m_dMinRadius = 1;
	WTp3_init(m_wtp3ExamineCOI);
	WTp3_init(m_wtp3ExamineSphericalCoord);
}

CCameraControl::~CCameraControl()
{
}


void CCameraControl::UpdateExamineView (int nWndPosX, int nWndPosY,
					int nWndWidth, int nWndHeight, BOOL bLeftButton, BOOL bRightButton,
					double dMousePosX, double dMousePosY)
{
	// This function doesn't set the center - it uses the previous set center
	
	// If the mouse is in the WTK window, then update the spherical coord
	// according to the mouse movement.  If the mouse is not in the window
	// then ignore it.
	if ((dMousePosX<=nWndPosX+nWndWidth) && (dMousePosX>=nWndPosX) && 
		  (dMousePosY<=nWndPosY+nWndHeight) && (dMousePosY>=nWndPosY))
	{
		double dMouseRate = WTsensor_getangularrate(m_pwtSensor);

		// Left button down rotates the viewpoint
		if (bLeftButton)
		{
			Rotate(dMousePosX, dMousePosY, dMouseRate, nWndPosX, nWndPosY,
						 nWndWidth, nWndHeight);
		}
		
		// Right button down zooms the viewpoint
		if (bRightButton)
		{
			Zoom(dMousePosY, nWndPosY, nWndHeight, FALSE);
		}		
	}

	// Orient the view everytime, whether there is a mouse update or not
	OrientExamineView();
}

void CCameraControl::UpdateExamineView2 (int nWndPosX, int nWndPosY,
					int nWndWidth, int nWndHeight, BOOL bLeftButton, BOOL bRightButton,
					double dMousePosX, double dMousePosY)
{
	double dDeltaThetaX, dDeltaThetaY;
	double dMouseRate = WTsensor_getangularrate(m_pwtSensor);

	WTp3 wtp3CameraToCoi;

	if (bLeftButton)
	{
		// Determine delta thetaX
		dDeltaThetaY = dMouseRate / m_dRotationScale * ((dMousePosX - 
			(nWndPosX + nWndWidth/2))/(nWndWidth/2));

		// Determine delta phi
		dDeltaThetaX = dMouseRate / m_dRotationScale * ((dMousePosY - 
			(nWndPosY + nWndHeight/2))/(nWndHeight/2));

		// Build rotation matrix from the current viewpoint orientation to the
		// new viewport orientation by rotating about the fixed coordinate system.
		WTm3 wtm3VP2NewVP;

		wtm3VP2NewVP[0][0] = (float) cos(dDeltaThetaY); 
		wtm3VP2NewVP[0][1] = (float) (-sin(dDeltaThetaX)*sin(dDeltaThetaY));
		wtm3VP2NewVP[0][2] = (float) (cos(dDeltaThetaX)*sin(dDeltaThetaY));
		wtm3VP2NewVP[1][0] = (float) 0;
		wtm3VP2NewVP[1][1] = (float) cos(dDeltaThetaX);
		wtm3VP2NewVP[1][2] = (float) sin(dDeltaThetaX);
		wtm3VP2NewVP[2][0] = (float) -sin(dDeltaThetaY);
		wtm3VP2NewVP[2][1] = (float) (-sin(dDeltaThetaX)*cos(dDeltaThetaY));
		wtm3VP2NewVP[2][2] = (float) (cos(dDeltaThetaX)*cos(dDeltaThetaY));

		// Pick up the current orientation of the viewport.
		WTq wtqWorld2VP;
		WTviewpoint_getorientation (m_pwtViewpoint, wtqWorld2VP);
		WTm3 wtm3World2VP;
		WTq_2m3 (wtqWorld2VP, wtm3World2VP);

		// Combine to get the total rotation to the new viewpoint
		WTm3 wtm3World2NewVP;
		WTm3_multm3 (wtm3VP2NewVP, wtm3World2VP, wtm3World2NewVP);
		
		// Convert to a quaternion
		WTq wtqWorld2NewVP;
		WTm3_2q (wtm3World2NewVP, wtqWorld2NewVP);

		// Set as the new orientation
		WTviewpoint_setorientation (m_pwtViewpoint, wtqWorld2NewVP);

		// Find the direction of the z axis of the world rotated by this quaternion
		WTp3 wtp3ZinNewVP;
		WTq_2dir (wtqWorld2NewVP, wtp3ZinNewVP);

		// The direction of the camera is the previous found rotated world Z negated
		WTp3 wtp3CameraInNewVP;
		WTp3_invert (wtp3ZinNewVP, wtp3CameraInNewVP);
		// Scale to the radius
		WTp3_mults (wtp3CameraInNewVP, m_wtp3ExamineSphericalCoord[EV_RAD]);
		// Offset for the COI
		WTp3_add (wtp3CameraInNewVP, m_wtp3ExamineCOI, wtp3CameraToCoi);
		// Set the position of the viewport
		WTviewpoint_setposition (m_pwtViewpoint, wtp3CameraToCoi);
	}
	else if (bRightButton)
	{
		// Calculate the new radius
		Zoom(dMousePosY, nWndPosY, nWndHeight, FALSE);

		// Pick up the current orientation of the viewport.
		WTq wtqWorld2VP;
		WTviewpoint_getorientation (m_pwtViewpoint, wtqWorld2VP);

		// Find the direction of the z axis of the world rotated by this quaternion
		WTp3 wtp3ZinNewVP;
		WTq_2dir (wtqWorld2VP, wtp3ZinNewVP);

		// The direction of the camera is the previous found rotated world Z negated
		WTp3 wtp3CameraInNewVP;
		WTp3_invert (wtp3ZinNewVP, wtp3CameraInNewVP);
		// Scale to the radius
		WTp3_mults (wtp3CameraInNewVP, m_wtp3ExamineSphericalCoord[EV_RAD]);
		// Offset for the COI
		WTp3_add (wtp3CameraInNewVP, m_wtp3ExamineCOI, wtp3CameraToCoi);
		// Set the position of the viewport
		WTviewpoint_setposition (m_pwtViewpoint, wtp3CameraToCoi);
	}

	UpdateCameraDirectedLight ();

	// Note that this viewing method doesn't call OrientView, because phi and theta weren't
	// calculated 
}

void CCameraControl::UpdatePanView (int nWndPosX, int nWndPosY,
					int nWndWidth, int nWndHeight, BOOL bLeftButton, BOOL bRightButton,
					double dMousePosX, double dMousePosY)
{
	double dMouseRate = WTsensor_getangularrate(m_pwtSensor);

	// Left button down pans
	if (bLeftButton)
	{
		Pan (dMousePosX, dMousePosY, dMouseRate, nWndPosX, nWndPosY,
					 nWndWidth, nWndHeight);
	}

	// Right button down zooms the viewpoint
	if (bRightButton)
	{
		Zoom(dMousePosY, nWndPosY, nWndHeight, TRUE);
		
		// This is possibly a problem...Pan and Examine
		// are now basically the same mode. Previously,
		// Pan mode ignored the center of interest, making
		// the following line unnecessary. Now that it actively
		// affects the center of interest, there maybe should
		// be a re-write of the entire class. I didn't realize
		// how much it affected until too late.
		//
		// LMF
		OrientExamineView();
	}
}

void CCameraControl::UpdateExamineView(WTp3 wtp3Center)
{

	// Update the sphere's center position
	WTp3_copy(wtp3Center, m_wtp3ExamineCOI);


	// Orient the view everytime, whether there is a mouse update or not
	OrientExamineView();
}

void CCameraControl::Rotate(double dMousePosX, double dMousePosY, double dMouseRate,
								  int nWindowPosX, int nWindowPosY, int nWindowWidth, 
								  int nWindowHeight)
{
	double dDeltaTheta, dDeltaPhi;

	// Determine delta theta
	dDeltaTheta = dMouseRate / m_dRotationScale * ((dMousePosX - 
		(nWindowPosX + nWindowWidth/2))/(nWindowWidth/2));

	// Determine delta phi
	dDeltaPhi = dMouseRate / m_dRotationScale * ((dMousePosY - 
		(nWindowPosY + nWindowHeight/2))/(nWindowHeight/2));

	m_wtp3ExamineSphericalCoord[EV_THETA] += (float) dDeltaTheta;
	m_wtp3ExamineSphericalCoord[EV_PHI] += (float) dDeltaPhi;

	// Check boundary conditions
	// Rap around 360 deg
	if (m_wtp3ExamineSphericalCoord[EV_THETA] > PIT2)
		m_wtp3ExamineSphericalCoord[EV_THETA] -= PIT2;
	if (m_wtp3ExamineSphericalCoord[EV_THETA] < -PIT2)
		m_wtp3ExamineSphericalCoord[EV_THETA] += PIT2;

	if (m_wtp3ExamineSphericalCoord[EV_PHI] > PIT2)
		m_wtp3ExamineSphericalCoord[EV_PHI] -= PIT2;
	if (m_wtp3ExamineSphericalCoord[EV_PHI] < -PIT2)
		m_wtp3ExamineSphericalCoord[EV_PHI] += PIT2;
}

void CCameraControl::Zoom(double dMousePosY, int nWindowPosY, 
								  int nWindowHeight, BOOL bPanMode)
{
	double dDeltaRadius;
	double dMouseRate = WTsensor_getangularrate(m_pwtSensor);

	// Determine delta radius
	dDeltaRadius = dMouseRate * m_dZoomScale * ((dMousePosY - (nWindowPosY + nWindowHeight/2))
		/(nWindowHeight/2));

	//if (bPanMode)
	//{
		// ## In pan mode, directly move the viewpoint
		// Build the delta vector
	//	WTp3 wtp3Delta;
	//	WTp3_init (wtp3Delta);
	//	wtp3Delta[Z] = (float) -dDeltaRadius;
	//	WTviewpoint_translate (m_pwtViewpoint, wtp3Delta, WTFRAME_VPOINT);

	//}


	// Update the radius
		m_wtp3ExamineSphericalCoord[EV_RAD] += (float) dDeltaRadius;

	// Check boundary conditions
	if (m_wtp3ExamineSphericalCoord[EV_RAD] > m_dMaxRadius)
		m_wtp3ExamineSphericalCoord[EV_RAD] = (float) m_dMaxRadius;
	if (m_wtp3ExamineSphericalCoord[EV_RAD] < m_dMinRadius)
		m_wtp3ExamineSphericalCoord[EV_RAD] = (float) m_dMinRadius;

}

void CCameraControl::Pan (double dMousePosX, double dMousePosY, double dMouseRate,
					int nWindowPosX, int nWindowPosY, int nWindowWidth, int nWindowHeight)
{
	double dDeltaX, dDeltaY;

	// Determine delta X
	dDeltaX = dMouseRate / m_dPanScale * ((dMousePosX - 
		(nWindowPosX + nWindowWidth/2))/(nWindowWidth/2));

	// Determine delta Y
	dDeltaY = dMouseRate / m_dPanScale * ((dMousePosY - 
		(nWindowPosY + nWindowHeight/2))/(nWindowHeight/2));
	
	// ## Move the viewpoint
	// Build the vector the holds the movement
	WTp3 wtp3Delta;
	wtp3Delta[X] = (float) dDeltaX;
	wtp3Delta[Y] = (float) dDeltaY;
	wtp3Delta[Z] = (float) 0;

	// Get a pointer to the CameraData class
#ifdef ROBOTBUILDER
	CDMViewerApp* pApp = (CDMViewerApp*)AfxGetApp();
	CMainFrame *pFrameWnd = (CMainFrame*)pApp->m_pMainWnd;
	CDMViewerDoc* pDoc = (CDMViewerDoc*)pFrameWnd->GetActiveDocument ();
	CCameraData* pCCameraData = (CCameraData*) pDoc->GetCameraData ();
#else
	CRBModelerApp* pApp = (CRBModelerApp*)AfxGetApp();
	CMainFrame *pFrameWnd = (CMainFrame*)pApp->m_pMainWnd;
	CRBModelerDoc* pDoc = (CRBModelerDoc*)pFrameWnd->GetActiveDocument ();
	CCameraData* pCCameraData = (CCameraData*) pDoc->GetCameraData ();
#endif
	
	// Get the COI node
#ifdef ROBOTBUILDER
	WTnode* wtnodeCOI;
	wtnodeCOI = dynamic_cast <CdmvArticulationData*> (pDoc->GetSystemData ())->
		GetCameraCenterOfInterest ();
#else
	CPrimitive* pPrimitive;
	WTnode* wtnodeCOI;
	pPrimitive = (pDoc->GetModel ()) -> GetCameraCenterOfInterest ();
	if (pPrimitive)
	{
		CRBModelerRBMGraphicView::GetPrimitiveNode(pPrimitive);
	}
	else
	{
		wtnodeCOI = NULL;
	}
#endif

	// Get the original offset
	WTp3 wtp3COIOffset;
	pCCameraData->GetCenterOfInterestOffset (wtp3COIOffset);
	WTp3 wtp3WorldOrigin = {0.0,0.0,0.0}, wtp3NewCOIOffset, wtp3COIDelta, wtp3WorldDelta = {0.0,0.0,0.0};

	// Get the viewpoint origin in world coordinates
	WTviewpoint_local2world(m_pwtViewpoint, wtp3WorldOrigin, wtp3WorldOrigin);
	
	// Update the Camera
	WTviewpoint_translate (m_pwtViewpoint, wtp3Delta, WTFRAME_VPOINT);
	UpdateCameraDirectedLight ();

	// Calculate the world delta to the new camera origin
	WTviewpoint_local2world(m_pwtViewpoint, wtp3WorldDelta, wtp3WorldDelta);
	WTp3_subtract(wtp3WorldDelta, wtp3WorldOrigin, wtp3WorldDelta);

	// Update the Examine view center
	WTp3_add(m_wtp3ExamineCOI, wtp3WorldDelta, m_wtp3ExamineCOI);
		
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
		WTm4_rotatep3 (wtm4_world2coi, wtp3WorldDelta, wtp3COIDelta);
		wtp3COIDelta[Y] = -wtp3COIDelta[Y];
		wtp3COIDelta[Z] = -wtp3COIDelta[Z];
	}
	else
	{
		//WTp3_copy(wtp3WorldDelta, wtp3COIDelta);
		wtp3COIDelta[X] = wtp3WorldDelta[X];
		wtp3COIDelta[Y] = wtp3WorldDelta[Z];
		wtp3COIDelta[Z] = -wtp3WorldDelta[Y];
	}

	// Update the COI offset
	WTp3_add(wtp3COIOffset, wtp3COIDelta, wtp3NewCOIOffset);
	pCCameraData->SetCenterOfInterestOffset(wtp3NewCOIOffset);

}


void CCameraControl::OrientExamineView()
{
	WTp3 wtp3ViewpointPos, wtp3Temp;
	WTq qRotation;

	// Copy the sphere's center to wtp3ViewpointPos for transformation
	WTp3_copy(m_wtp3ExamineCOI, wtp3ViewpointPos);

	// Offset wtp3ViewpointPos by the radius of the sphere
	wtp3ViewpointPos[Z] -= m_wtp3ExamineSphericalCoord[EV_RAD];

	// Transform phi into a quaternion
	WTeuler_2q(m_wtp3ExamineSphericalCoord[EV_PHI], 0.0f, 0.0f, qRotation);
	// Rotate pos about the sphere's center and put the result in temp
	WTp3_rotatept(wtp3ViewpointPos, qRotation, wtp3Temp, m_wtp3ExamineCOI);

	// Transform theta into a quaternion
	WTeuler_2q(0.0f, -m_wtp3ExamineSphericalCoord[EV_THETA], 0.0f, qRotation);
	// Rotate temp about the sphere's center and put the result in wtp3ViewpointPos
	WTp3_rotatept(wtp3Temp, qRotation, wtp3ViewpointPos, m_wtp3ExamineCOI);

	// Reset the viewpoint orientation
	WTq qNoRotation;
	WTeuler_2q(0,0.0f,0.0f,qNoRotation);

	// Set viewpoint 
	WTviewpoint_setposition(m_pwtViewpoint, wtp3ViewpointPos);
	WTviewpoint_setorientation(m_pwtViewpoint, qNoRotation);
	WTviewpoint_rotate(m_pwtViewpoint, Y, -m_wtp3ExamineSphericalCoord[EV_THETA], WTFRAME_VPOINT);
	WTviewpoint_rotate(m_pwtViewpoint, X, m_wtp3ExamineSphericalCoord[EV_PHI], WTFRAME_VPOINT);

	UpdateCameraDirectedLight ();


}


// Used to calculated the theta, phi, and radius for the current
// relationship between the COI and the viewpoint
void CCameraControl::RecalculateExamineViewParameters (WTp3 wtp3Center)
{
	// ## Save the new center
	WTp3_copy(wtp3Center, m_wtp3ExamineCOI);

	// ## Find Radius
	// Get the viewpoint position
	WTp3 wtp3ViewpointPosition;
	WTviewpoint_getposition (m_pwtViewpoint, wtp3ViewpointPosition);

	// Find the difference in the vectors
	WTp3 wtp3Difference;
	WTp3_subtract (wtp3Center, wtp3ViewpointPosition, wtp3Difference);
	// Find the magnitude
	double dDifferenceMag = WTp3_mag (wtp3Difference); 
	// Make sure the value is within the valid range
	if (dDifferenceMag > m_dMaxRadius)
		dDifferenceMag = (float) m_dMaxRadius;
	if (dDifferenceMag < m_dMinRadius)
		dDifferenceMag = (float) m_dMinRadius;
	// Save the final value
	m_wtp3ExamineSphericalCoord[EV_RAD] = (float) dDifferenceMag;
	
	// ## Find theta
	// Use the difference vector from above
	m_wtp3ExamineSphericalCoord[EV_THETA] = (float) -atan2 (wtp3Difference[X], wtp3Difference[Z]);
//	m_wtp3ExamineSphericalCoord[EV_THETA] = (float) atan2 (wtp3Difference[Z], wtp3Difference[X]);
//	m_wtp3ExamineSphericalCoord[EV_THETA] += PI/2;
//	m_wtp3ExamineSphericalCoord[EV_THETA] *= -1;

	// ## Find phi
	// First get magnitude of component in X-Z plane
	double dXZMag = sqrt (wtp3Difference[Z] * wtp3Difference[Z] + wtp3Difference[X] *
		wtp3Difference[X]);
	m_wtp3ExamineSphericalCoord[EV_PHI] = (float) - atan2 (wtp3Difference[Y], (float)dXZMag);
	
	// Update the view
	OrientExamineView ();
}

void CCameraControl::UpdateCameraDirectedLight()
{
	WTp3 wtp3CameraDirection;
	WTviewpoint_getdirection (m_pwtViewpoint, wtp3CameraDirection);
#ifdef ROBOTBUILDER
	WTnode* wtnodeCameraDirectedLight = ((CDMViewerDoc*)(((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetActiveDocument ()))->GetWTKView ()->m_WTKGraphics.GetCameraDirectedLight ();
#endif
#ifdef ROBOTMODELER
	WTnode* wtnodeCameraDirectedLight = CRBModelerRBMGraphicView::GetCameraDirectedLight ();
#endif

	// If the user loads custom lights, the directed light on the camera will not be created
	if (wtnodeCameraDirectedLight)
		VERIFY(WTlightnode_setdirection (wtnodeCameraDirectedLight, wtp3CameraDirection));
}

void CCameraControl::UpdateExamineView2(WTp3 wtp3Center)
{
	WTp3_copy (wtp3Center, m_wtp3ExamineCOI);

	// Pick up the current orientation of the viewport.
	WTq wtqWorld2VP;
	WTviewpoint_getorientation (m_pwtViewpoint, wtqWorld2VP);

	// Find the direction of the z axis of the world rotated by this quaternion
	WTp3 wtp3ZinNewVP;
	WTq_2dir (wtqWorld2VP, wtp3ZinNewVP);

	// The direction of the camera is the previous found rotated world Z negated
	WTp3 wtp3CameraInNewVP;
	WTp3_invert (wtp3ZinNewVP, wtp3CameraInNewVP);
	// Scale to the radius
	WTp3_mults (wtp3CameraInNewVP, m_wtp3ExamineSphericalCoord[EV_RAD]);
	// Offset for the COI
	WTp3 wtp3CameraToCoi;
	WTp3_add (wtp3CameraInNewVP, m_wtp3ExamineCOI, wtp3CameraToCoi);
	// Set the position of the viewport
	WTviewpoint_setposition (m_pwtViewpoint, wtp3CameraToCoi);

}

void CCameraControl::UpdatePanView2()
{
	UpdateCameraDirectedLight();
}
