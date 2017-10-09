// WTKGraphics.cpp: implementation of the CWTKGraphics class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "WTKGraphics.h"

#include "dmvArticulationData.h"
#include "dmvSphericalLinkData.h"
#include "dmvStaticRootLinkData.h"
#include "dmvPrismaticLinkData.h"
#include "dmvTreadmillData.h"
#include "dmvTerrainData.h"
#include "dmvLinkData.h"
#include "ParserTreadmill.h"
#include "ParserXan.h"
#include "ParserDat.h"
#include "ParserCmb.h"
#include "MainFrm.h"
#include "dmvCFGData.h"
#include "DMViewerDoc.h"
#include <Model.h>
#include <RBMGraphicView.h>
#include <ParserModel.h>

#include <dmTreadmill.hpp>
#include <dmArticulation.hpp>

#include <float.h> // for _finite test

#define ROLLER_RADIUS_SCALE 15

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWTKGraphics::CWTKGraphics()
{
	m_wtnodeCameraDirectedLight = NULL;
//  LogoLoaded = 0; //Sets the LogoLoading Flag False
}

CWTKGraphics::~CWTKGraphics()
{

}


BOOL CWTKGraphics::CreateNewNode(WTnode* wtnodeParent, CdmvObject* pCdmvObject)
{
	// This assumes that the parent has already been created.
	ASSERT (wtnodeParent);
	
	WTnode* wtnodeNewNode = WTmovsepnode_new (NULL);
	ASSERT (wtnodeNewNode);

	if (WTmovnode_attach (wtnodeParent, wtnodeNewNode, WTNODE_APPEND) == FALSE)
	{
		// then failure - possibly the parent is not a movable
		AfxMessageBox ("Failed to attach node.", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	pCdmvObject->SetWtkNode (wtnodeNewNode);

	return TRUE;
}


// Only builds the geometry if there is none allocated for the pCdmvObject!!
BOOL CWTKGraphics::SetNodeGeometry(CdmvObject *pCdmvObject, CString strGraphicPath)
{
	WTnode* wtnodeModel = NULL;

	// Get the sep node that is the parent of the geometry that will be added
	WTnode* wtnode;
	wtnode = pCdmvObject->GetWtkNode ();
	ASSERT (wtnode);

	// Check if there is a geometry already and if so, leave
	if (pCdmvObject->GetWtkGeometryNode ())
	{
		return TRUE;
	}

	// Check if no graphic specified
	if (strGraphicPath.GetLength () == 0)
	{
		// then its empty so just return from here -- but since not really
		// any failures, return true
		return TRUE;
	}

	// Get the file extension
	CString strExtension = (strGraphicPath.Right (3));
	// Make upper so compares aren't case sensitive;
	strExtension.MakeUpper  ();
	if (strExtension == "DAT")
	{
		// then run the custom parser/loader
		// Create an object 
		WTgeometry* wtgeometryModel; // the dat parser just builds a geometry
		if (CParserDat::ParseDatFileAndBuildGeometry (strGraphicPath, &wtgeometryModel))
		{
			// now create a geometry node with the geometry
			wtnodeModel = WTgeometrynode_new (wtnode , wtgeometryModel);
			ASSERT (wtnodeModel);
			pCdmvObject->SetWtkGeometryNode (wtnodeModel);
		}
	}
	else if (strExtension == "XAN")
	{
		// then run the custom parser/loader
		// Create an object 
		WTgeometry* wtgeometryModel; // the dat parser just builds a geometry
		if (CParserXan::ParseXanFileAndBuildGeometry (strGraphicPath, &wtgeometryModel))
		{
			// now create a geometry node with the geometry
			wtnodeModel = WTgeometrynode_new (wtnode , wtgeometryModel);
			ASSERT (wtnodeModel);
			pCdmvObject->SetWtkGeometryNode (wtnodeModel);
		}
	}
	else if (strExtension == "CMB")
	{
		// then run the custom parser/loader
		// Create an object 
		WTnode* wtsepnodeModel;
		if (CParserCmb::ParseCmbFileAndBuildGeometry (strGraphicPath, &wtsepnodeModel))
		{
			// Add model tree to the scenegraph
			FLAG flagStatus = WTnode_addchild (wtnode, wtsepnodeModel);
			ASSERT (flagStatus);
			pCdmvObject->SetWtkGeometryNode (wtsepnodeModel);
		}
	}
	else if (strExtension == "RBM")
	{
		CModel* pModel;
		if (CParserModel::ParseModelFile (strGraphicPath, &pModel))
		{
			// Build the model
			WTnode* wtsepnodeModel;
			CRBMGraphicView::LoadNewModel (pModel, &wtsepnodeModel);

			// Add model tree to the scenegraph
			FLAG flagStatus = WTnode_addchild (wtnode, wtsepnodeModel);
			ASSERT (flagStatus);
			pCdmvObject->SetWtkGeometryNode (wtsepnodeModel);
		}

	}

	else // let WTK try
	{
		// must load into a node
		wtnodeModel = WTgeometrynode_load (wtnode,
			(char*) LPCTSTR (strGraphicPath), 1.0f);
		if (wtnodeModel == NULL)
		{
			AfxMessageBox ("Failed to load geometry!", MB_OK | MB_ICONEXCLAMATION);
			return FALSE;
		}

		pCdmvObject->SetWtkGeometryNode (wtnodeModel);
		
//		FLAG flagStatus = WTnode_setname (wtnodeModel, STR_GEOMETRY_NAME);
//		ASSERT (flagStatus);
	}

	return TRUE;

}

BOOL CWTKGraphics::GetReferenceSystemNode(WTnode **pwtnodeRefSys)
{
	*pwtnodeRefSys = WTuniverse_findnodebyname (STR_REFSYS_NODE_NAME, 0);

	if (*pwtnodeRefSys == NULL)
		return FALSE;
	else
		return TRUE;
}


void CWTKGraphics::SetNodeTransform(CdmvObject* pCdmvObject, structMDHParameters strtMDHParameters)
{
	WTm4 wtm4Transform; // will have the transform for the link
	WTnode* wtnode = NULL;

	// translate the MDH parameters to a 4x4 matrix
	DHto4x4Matrix (&strtMDHParameters, wtm4Transform);

	// Get a pointer to the node
	wtnode = pCdmvObject->GetWtkNode ();
	ASSERT (wtnode);
	
	BOOL bReturn;
	bReturn = WTnode_settransform (wtnode, wtm4Transform);
	ASSERT (bReturn);

	WTp3 wtp3Pos;
	wtp3Pos[X] = wtm4Transform[0][3]; wtp3Pos[Y] = wtm4Transform[1][3];
	wtp3Pos[Z] = wtm4Transform[2][3];
	WTnode_settranslation (wtnode, wtp3Pos);
}

// design: consider making a wtk math library
void CWTKGraphics::DHto4x4Matrix(const structMDHParameters *pstrtMDHParameters, WTm4& rwtm4TransformMatrix)
{

/*	rwtm4TransformMatrix[0][0] = cosf (pstrtMDHParameters->fTheta);
	rwtm4TransformMatrix[0][1] = -sinf (pstrtMDHParameters->fTheta);
	rwtm4TransformMatrix[0][2] = 0;
	rwtm4TransformMatrix[0][3] = pstrtMDHParameters->fa;

	rwtm4TransformMatrix[1][0] = sinf (pstrtMDHParameters->fTheta) * cosf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[1][1] = cosf (pstrtMDHParameters->fTheta) * cosf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[1][2] = -sinf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[1][3] = -sinf (pstrtMDHParameters->fAlpha) * pstrtMDHParameters->fd;

	rwtm4TransformMatrix[2][0] = sinf (pstrtMDHParameters->fTheta) * sinf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[2][1] = cosf (pstrtMDHParameters->fTheta) * sinf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[2][2] = cosf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[2][3] = cosf (pstrtMDHParameters->fAlpha) * pstrtMDHParameters->fd;
	
	rwtm4TransformMatrix[3][0] = 0;
	rwtm4TransformMatrix[3][1] = 0;
	rwtm4TransformMatrix[3][2] = 0;
	rwtm4TransformMatrix[3][3] = 1; */
	
	// Dynamechs view the rotations as forward references.
	
	rwtm4TransformMatrix[0][0] = cosf (pstrtMDHParameters->fTheta);
	rwtm4TransformMatrix[1][0] = -sinf (pstrtMDHParameters->fTheta);
	rwtm4TransformMatrix[2][0] = 0;
	rwtm4TransformMatrix[0][3] = pstrtMDHParameters->fa;

	rwtm4TransformMatrix[0][1] = sinf (pstrtMDHParameters->fTheta) * cosf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[1][1] = cosf (pstrtMDHParameters->fTheta) * cosf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[2][1] = -sinf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[1][3] = -sinf (pstrtMDHParameters->fAlpha) * pstrtMDHParameters->fd;

	rwtm4TransformMatrix[0][2] = sinf (pstrtMDHParameters->fTheta) * sinf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[1][2] = cosf (pstrtMDHParameters->fTheta) * sinf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[2][2] = cosf (pstrtMDHParameters->fAlpha);
	rwtm4TransformMatrix[2][3] = cosf (pstrtMDHParameters->fAlpha) * pstrtMDHParameters->fd;
	
	rwtm4TransformMatrix[3][0] = 0;
	rwtm4TransformMatrix[3][1] = 0;
	rwtm4TransformMatrix[3][2] = 0;
	rwtm4TransformMatrix[3][3] = 1; 

}

void CWTKGraphics::GetNodeFromLabel (CString strLabel, int nOccurrence, 
											   WTnode** pwtnode)

{
	*pwtnode = WTuniverse_findnodebyname (
		const_cast <char*> (LPCSTR (strLabel)), nOccurrence);

	// This function could be used to see if a particular name exists, rather
	// than wanting a pointer to a node.  Consequently, it is up to the caller
	// to verify that a non-NULL value was returned if it is going to be used
	// as a pointer.
}

void CWTKGraphics::DeleteNodeGeometry(CdmvObject *pCdmvObject)
{
	// Most links will have just one child, the model.  The expection is
	// the refsys node which will have the root link and its model, so 
	// only delete children if they are a model.  In general the model,
	// can be a WTgeometry or a seperated tree structure of nodes.

	if (pCdmvObject->GetWtkGeometryNode ())
	{
		FLAG flagStatus = WTnode_delete (pCdmvObject->GetWtkGeometryNode ());
		ASSERT (flagStatus);

		// Reset the graphic pointer to NULL
		pCdmvObject->SetWtkGeometryNode (NULL);
	}
}


BOOL CWTKGraphics::BuildBaseSceneGraph()
{
	// Reset the universe by deleting all non-root nods
	WTnode_vacuum ();

	CreateLightNodes ();
	CreateSystemTransform ();

	WTwindow_zoomviewpoint(WTuniverse_getwindows());
	return TRUE;
}

void CWTKGraphics::SetNodeTransform(CdmvObject* pCdmvObject, Quaternion qOrientation, CartesianVector cvPosition)
{
	WTnode* wtnodeLink;
	// Get a pointer to the node
	wtnodeLink = pCdmvObject->GetWtkNode ();
	
	// Check that a valid node was found - there doesn't have to be one defined
	if (wtnodeLink)
	{
		ASSERT (AfxIsValidAddress (wtnodeLink, sizeof (WTnode*)));
		
		WTp3 wtp3Pos;
		wtp3Pos[X] = cvPosition[0]; wtp3Pos[Y] = cvPosition[1]; wtp3Pos[Z] = cvPosition[2];
		FLAG flagStatus = WTnode_settranslation (wtnodeLink, wtp3Pos);
		ASSERT (flagStatus);

		// now set the orientation
		WTm3 wtm3Rotation;
		QuaternionToForwardRotation (qOrientation, wtm3Rotation);
		flagStatus = WTnode_setrotation (wtnodeLink, wtm3Rotation);
		ASSERT (flagStatus);
	}
}

void CWTKGraphics::IndicateSelectedModel(CdmvObject* pCdmvObject, BOOL bEnable)
{
	WTnode* wtnodeLink = NULL;

	wtnodeLink = pCdmvObject->GetWtkGeometryNode ();

	// There might not be a geometry node
	if(wtnodeLink)
	{
		FLAG flagStatus = WTnode_boundingbox (wtnodeLink, bEnable);
		ASSERT (flagStatus);
	}

/*	// In the current implementation, the only child should be the geometry node
	int nNumChildren = WTnode_numchildren (wtnodeLink);
	// some links don't have associated geometries, so need to check that there is a child
	if (nNumChildren > 0)
	{
		ASSERT (nNumChildren == 1);
		WTnode* wtnodeGeometry = WTnode_getchild (wtnodeLink, 0);

		// currently, make the indication by enabling/disabling the bounding box
		FLAG flagStatus = WTnode_boundingbox (wtnodeGeometry, bEnable);
		ASSERT (flagStatus);		
	}

*/
}

BOOL CWTKGraphics::CreateReferenceSystemNode(CdmvArticulationData* pCdmvArticulationData)
{
	// then create then its the mobile joint so attach it to the root
	WTnode* wtnodeRoot;
	WTnode* wtnodeNewNode;
	wtnodeRoot = WTuniverse_getrootnodes();
	wtnodeNewNode = WTmovsepnode_new (wtnodeRoot);
	ASSERT (wtnodeNewNode);

	pCdmvArticulationData->SetWtkNode(wtnodeNewNode);

//	FLAG flagStatus = WTnode_setname (wtnodeNewLink, STR_REFSYS_NODE_NAME);
//	ASSERT (flagStatus);

	Quaternion qOrientation;
	CartesianVector cvPosition;
	pCdmvArticulationData->GetRefSystem (qOrientation, cvPosition);
	SetNodeTransform (pCdmvArticulationData, qOrientation, cvPosition);

	WTnode_setname (wtnodeNewNode, STR_ARTICULATION_NAME);

	return TRUE;
}


BOOL CWTKGraphics::CreateLightNodes()
{
	BOOL bReturnStatus;
	WTnode* wtnodeRoot = NULL;
	WTnode* wtnodeLight = NULL;

	wtnodeRoot = WTuniverse_getrootnodes ();
	ASSERT (wtnodeRoot);

	/* Load a lights file */
	if (!WTlightnode_load (wtnodeRoot,"RobotBuilderLights.wtk")) {
		
		// Ambient light
		VERIFY(wtnodeLight = WTlightnode_newambient (wtnodeRoot));
		WTlightnode_setintensity (wtnodeLight, 0.95f);

		// Point light
//		WTnode* wtnodeLight2;
//		VERIFY(wtnodeLight2 = WTlightnode_newpoint (wtnodeRoot));
//		WTp3 wtp3Pos = {0, 0, 1000};
//		VERIFY(WTlightnode_setposition (wtnodeLight2, wtp3Pos));
//		WTlightnode_setintensity (wtnodeLight2, .15);

		VERIFY(m_wtnodeCameraDirectedLight = WTlightnode_newdirected (wtnodeRoot));
		WTp3 wtp3Direction = {0, 0, 1}; // Will be updated by camera
		VERIFY(WTlightnode_setdirection (m_wtnodeCameraDirectedLight, wtp3Direction));
		WTlightnode_setintensity (m_wtnodeCameraDirectedLight, CAMERA_LIGHT_INTENSITY);



		bReturnStatus = TRUE;
	}
	else
	{
		// Loaded light file.
		// Make sure the directed light on the camera is NULL, because there isn't one
		VERIFY(m_wtnodeCameraDirectedLight = WTlightnode_newdirected (wtnodeRoot));
		WTp3 wtp3Direction = {0, 0, 1}; // Will be updated by camera
		VERIFY(WTlightnode_setdirection (m_wtnodeCameraDirectedLight, wtp3Direction));
		WTlightnode_setintensity (m_wtnodeCameraDirectedLight, CAMERA_LIGHT_INTENSITY);

		bReturnStatus = TRUE;
	}

	return bReturnStatus;
}

BOOL CWTKGraphics::CreateSystemTransform()
{
	WTnode* wtnodeRoot = NULL;

	wtnodeRoot = WTuniverse_getrootnodes ();
	ASSERT (wtnodeRoot);
	
	WTnode* wtnodeUniverseAdjust = WTxformnode_new (wtnodeRoot);
	WTm3 wtm3Orientation;
	WTm3_init (wtm3Orientation);
	wtm3Orientation[1][1] = 0;
	wtm3Orientation[1][2] = -1;
	wtm3Orientation[2][1] = 1;
	wtm3Orientation[2][2] = 0;
//	FLAG flagStatus = WTnode_setrotation (wtnodeUniverseAdjust, wtm3Orientation);
//	ASSERT (flagStatus);
	WTnode_rotation (wtnodeUniverseAdjust, 0, 1.5708f, 0, WTFRAME_PARENT);

	return TRUE;
}

void CWTKGraphics::QuaternionToForwardRotation(Quaternion q, WTm3 &wtm3)
{
	wtm3[0][0] = 1 - 2*q[1]*q[1] - 2*q[2]*q[2];
	wtm3[0][1] = 2 * (q[0]*q[1] + q[2]*q[3]);
	wtm3[0][2] = 2 * (q[0]*q[2] - q[1]*q[3]);

	wtm3[1][0] = 2 * (q[0]*q[1] - q[2]*q[3]);
	wtm3[1][1] = 1 - 2*q[0]*q[0] - 2*q[2]*q[2];
	wtm3[1][2] = 2 * (q[1]*q[2] + q[0]*q[3]);

	wtm3[2][0] = 2 * (q[0]*q[2] + q[1]*q[3]);
	wtm3[2][1] = 2 * (q[1]*q[2] - q[0]*q[3]);
	wtm3[2][2] = 1 - 2*q[0]*q[0] - 2*q[1]*q[1];
}

void CWTKGraphics::EulerAnglesToForwardRotation(EulerAngles eaAngles, WTm3 &wtm3)
{
	Float fPhi = eaAngles[0];
	Float fTheta = eaAngles[1];
	Float fPsi = eaAngles[2];

	wtm3[0][0] = cos(fTheta) * cos(fPsi);
	wtm3[1][0] = sin(fPhi) * sin(fTheta) * cos(fPsi) -
		cos(fPhi) * sin(fPsi);
	wtm3[2][0] = cos(fPhi) * sin(fTheta) * cos(fPsi) + sin(fPhi) * sin(fPsi);

	wtm3[0][1] = cos(fTheta) * sin(fPsi);
	wtm3[1][1] = sin(fPhi) * sin(fTheta) * sin(fPsi) + cos(fPhi) * cos(fPsi);
	wtm3[2][1] = cos(fPhi) * sin(fTheta) * sin(fPsi) - sin(fPhi) * cos(fPsi);

	wtm3[0][2] = -sin(fTheta);
	wtm3[1][2] = sin(fPhi) * cos(fTheta);
	wtm3[2][2] = cos(fPhi) * cos(fTheta);  

/*
   wtm3[0][0] = 1;
   wtm3[1][0] = 0;
   wtm3[2][0] = 0;

   wtm3[0][1] = 0;
   wtm3[1][1] = 0;
   wtm3[2][1] = -1;

   wtm3[0][2] = 0;
   wtm3[1][2] = 1;
   wtm3[2][2] = 0;
   R[0][0] = m_ctheta*m_cpsi;
   R[1][0] = m_sphi*(m_stheta*m_cpsi) - m_cphi*m_spsi;
   R[2][0] = m_cphi*(m_stheta*m_cpsi) + m_sphi*m_spsi;

   R[0][1] = m_ctheta*m_spsi;
   R[1][1] = m_sphi*(m_stheta*m_spsi) + m_cphi*m_cpsi;
   R[2][1] = m_cphi*(m_stheta*m_spsi) - m_sphi*m_cpsi;

   R[0][2] =-m_stheta;
   R[1][2] = m_sphi*m_ctheta;
   R[2][2] = m_cphi*m_ctheta;

   p[0] = m_p[0];
   p[1] = m_p[1];
   p[2] = m_p[2];	
	
	
	*/
}

// This function couldn't be named SetLinkTransform because both EulerAngles
// and Quaternion are typedef'ed as float arrays
void CWTKGraphics::SetNodeTransformWithEulerAngles(CdmvObject *pCdmvObject, EulerAngles eaAngles, CartesianVector cvPosition)
{
	WTnode* wtnode;
	// Get a pointer to the node
	wtnode = pCdmvObject->GetWtkNode ();
	ASSERT (wtnode);
	
	WTp3 wtp3Pos;
	wtp3Pos[X] = cvPosition[0]; wtp3Pos[Y] = cvPosition[1]; wtp3Pos[Z] = cvPosition[2];
	FLAG flagStatus = WTnode_settranslation (wtnode, wtp3Pos);
	ASSERT (flagStatus);

	// now set the orientation
	WTm3 wtm3Rotation;
	EulerAnglesToForwardRotation (eaAngles, wtm3Rotation);
	flagStatus = WTnode_setrotation (wtnode, wtm3Rotation);
	ASSERT (flagStatus);
}

BOOL CWTKGraphics::CreateEnvironmentNode(CdmvEnvironmentData *pEnvironment)
{
	// Delete the current environment
	DeleteEnvironmentNode (pEnvironment);

	BOOL bReturnStatus;
	WTnode* root = WTuniverse_getrootnodes();
	WTgeometry *geom = NULL;

	// A design possibility would be to add a virtual draw function for the enviroment, and
	// let the class do the drawing.  This would be a more object oriented approach, but since
	// the rest of the graphics were drawn this way, I drew the environment the same.
	
	// Build the environment by the its type
	if (typeid (*pEnvironment) == typeid(CdmvTreadmillData))
	{
		// Draw conveyor from class data
		// Get a pointer to the treadmill by casting
		CdmvTreadmillData *pTreadmill = dynamic_cast <CdmvTreadmillData*> (pEnvironment);

		// Create the node with root as the parent and add the components as children
		WTnode* wtmovsepnodeTreadmillBase;
		wtmovsepnodeTreadmillBase = WTmovsepnode_new (root);
		WTnode_setname (wtmovsepnodeTreadmillBase, STR_ENVIRONMENT_NAME);

		///// Find rotation of treadmill /////
		// Get the normal and velocity vectors.  They are stored as unit vectors
		CartesianVector cvTreadmillNormal, cvTreadmillVelocity;
		WTp3 wtp3TreadmillNormal, wtp3TreadmillVelocity;
		pTreadmill->GetNormal (cvTreadmillNormal);
		pTreadmill->GetVelocityDirection (cvTreadmillVelocity);
		int i;
		for (i = 0; i < 3; i++)
		{
			wtp3TreadmillNormal[i] = cvTreadmillNormal[i];
			wtp3TreadmillVelocity[i] = cvTreadmillVelocity[i];
		}

		// Find the y axis by the crossproduct
		WTp3 wtp3TreadmillY;
		WTp3_cross (wtp3TreadmillNormal, wtp3TreadmillVelocity, wtp3TreadmillY);

		// Build the rotation matrix
		// notation u for universe, t for treadmill
		// Recall WTK uses right to left method (vectors are rows) - transpose
		// to Orin's notation
		WTm3 wtm3_tRu;
		for (i = 0; i < 3; i++)
		{
			wtm3_tRu[0][i] = wtp3TreadmillVelocity[i];
			wtm3_tRu[1][i] = wtp3TreadmillY[i];
			wtm3_tRu[2][i] = wtp3TreadmillNormal[i];
		}

		// Rotate the base of the treadmill
		WTnode_setrotation (wtmovsepnodeTreadmillBase, wtm3_tRu);
		

		//// Set the position of the treadmill //////
		CartesianVector cvPosition;
		pTreadmill->GetPosition (cvPosition);
		WTp3 wtp3TreadmillPosition;
		for (i = 0; i < 3; i++)
			wtp3TreadmillPosition[i] = cvPosition[i];
		WTnode_settranslation (wtmovsepnodeTreadmillBase, wtp3TreadmillPosition);

		////// Build the colors for use in the geometries /////////
		WTmtable* wtmtable;
		wtmtable = WTmtable_new (
			WTMAT_AMBIENT | WTMAT_DIFFUSE ,
			1, /* estimated entries */
			NULL /* unique name - if NULL WTK makes up one*/);
		ASSERT (wtmtable);

		int nMTableIndex = 0; // index in to material table
		nMTableIndex = WTmtable_newentry (wtmtable);
		// Verify that this is the only entry in the table
		ASSERT (nMTableIndex == 0);

		COLORREF crTreadmillColor;
		crTreadmillColor = pTreadmill->GetColor ();
		float fColor[3] = {GetRValue(crTreadmillColor)/255.0, GetGValue(crTreadmillColor)/255.0, GetBValue (crTreadmillColor)/255.0};
		float fColorWhite[3] = {1, 1, 1};

		FLAG flagReturn;

		flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
			fColor, WTMAT_AMBIENT);
		ASSERT (flagReturn);

		flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
			fColorWhite, WTMAT_DIFFUSE);
		ASSERT (flagReturn);

		///// Roller definitions ////////
		// The ratios were arbitrarily selected - change them if desired
		const double dRollerHeight = ((CdmvTreadmillData*) pEnvironment)->GetWidth ();
		const double dRollerRadius = max((dRollerHeight +  ((CdmvTreadmillData*) pEnvironment)->GetLength ()) / 2
			/ ROLLER_RADIUS_SCALE, WTK_MIN); // The rotation speed depends on this
			// If the equation is changed in UpdateEnvironment (or make it a static member)
		const double dRollerEndHeight = max(dRollerHeight / 50, WTK_MIN);
		const int nRollerTesselation = 20;

		// Create rollers
		WTgeometry* wtgeometryRoller;
		wtgeometryRoller = WTgeometry_newcylinder (
			dRollerHeight,
			dRollerRadius, 
			nRollerTesselation, 
			FALSE, /* don't render both sides */
			TRUE); /* use gouraud shading */
		ASSERT (wtgeometryRoller);

		// Color the roller
		WTgeometry_setmtable (wtgeometryRoller, wtmtable);
		flagReturn = WTgeometry_setmatid (wtgeometryRoller, nMTableIndex);
		ASSERT (flagReturn);

		// Create the node for the roller
		WTnode* wtgeomnodeRoller = WTgeometrynode_new (
			NULL, wtgeometryRoller);
		ASSERT (wtgeomnodeRoller);		

		// Create a sep node for the roller
		WTnode* wtmovsepnodeRollerBack = WTmovsepnode_new (wtmovsepnodeTreadmillBase);
		
		// Create a sep node for the roller
		WTnode* wtmovsepnodeRoller = WTmovsepnode_new (wtmovsepnodeRollerBack);
		
		// Add roller geometry
		flagReturn = WTnode_addchild (wtmovsepnodeRoller, wtgeomnodeRoller);
		ASSERT (flagReturn);

		// Build a vector for WTK use for placement
		WTp3 wtp3TranslationRollerBack;
		// Note the position is the position of the center
		const double dLength = ((CdmvTreadmillData*) pEnvironment)->GetLength (); // get the length
		wtp3TranslationRollerBack[X] = - dLength / 2;
		wtp3TranslationRollerBack[Y] = 0;
		wtp3TranslationRollerBack[Z] = -1*dRollerRadius;		
		FLAG flagStatus = WTnode_settranslation (wtmovsepnodeRollerBack, wtp3TranslationRollerBack);
		ASSERT (flagStatus);
		
		// Create the textured roller end so that the user can easily see the treadmill is moving
		WTgeometry* wtgeometryRollerEnd;
		wtgeometryRollerEnd = WTgeometry_newcylinder (
			dRollerEndHeight,
			dRollerRadius, 
			nRollerTesselation, 
			FALSE, /* don't render both sides */
			TRUE); /* use gouraud shading */
		ASSERT (wtgeometryRollerEnd);
		
		// Apply texture to geometry
		CString strRollerGraphicFile = _T("rollerend.jpg");
		CString strRollerGraphicPath, strRollerGraphicPathAndFile;
		CFindFile::FindFile (TEXTURE_FILE_TYPE, strRollerGraphicFile, strRollerGraphicPath);
		strRollerGraphicPathAndFile = strRollerGraphicPath + strRollerGraphicFile;
		flagStatus;
		// Maybe I am trusting WTK too much with the const_cast?
		flagStatus = WTgeometry_settexture (wtgeometryRollerEnd,
			strRollerGraphicPathAndFile.GetBuffer (strRollerGraphicPathAndFile.GetLength ()),
			TRUE, // for shading 
			FALSE); // for transparent
		// Don't assert on the return, because the texture could just be
		// missing ...
		if (!flagStatus)
			AfxMessageBox ("Missing treadmill roller texture (rollerend.jpg).");

		// Create a node for the geometry
		WTnode* wtgeomnodeRollerEnd = WTgeometrynode_new (
			NULL, wtgeometryRollerEnd);

		// Create the mov sep node for the roller end
		WTnode* wtmovsepnodeRollerEndFront = WTmovsepnode_new (
			wtmovsepnodeRoller);
		ASSERT (wtmovsepnodeRollerEndFront);	
		
		// Add the roller end geometry
		flagReturn = WTnode_addchild (wtmovsepnodeRollerEndFront, wtgeomnodeRollerEnd);
		ASSERT (flagReturn);

		WTp3 wtp3RollerEndFrontPosition = {0, -(dRollerEndHeight/2 + dRollerHeight / 2), 0};

		flagStatus = WTnode_settranslation (wtmovsepnodeRollerEndFront, wtp3RollerEndFrontPosition);
		ASSERT (flagStatus);

		/////
		// Create the mov sep node for the roller end
		WTnode* wtmovsepnodeRollerEndBack = WTmovsepnode_new (
			wtmovsepnodeRoller);
		ASSERT (wtmovsepnodeRollerEndBack);	

		// Add the roller end geometry
		flagReturn = WTnode_addchild (wtmovsepnodeRollerEndBack, wtgeomnodeRollerEnd);
		ASSERT (flagReturn);

		WTp3 wtp3RollerEndBackPosition = {0, (dRollerEndHeight/2 + dRollerHeight / 2), 0};

		flagStatus = WTnode_settranslation (wtmovsepnodeRollerEndBack, wtp3RollerEndBackPosition);
		ASSERT (flagStatus);
		
		// Set the name of the node so it can be easily accessed later
		flagStatus = WTnode_setname (wtmovsepnodeRoller, "Roller");
		ASSERT (flagStatus);
			
		///// Front Roller
		// Create a sep node for the roller
		WTnode* wtmovsepnodeRollerFront = WTmovsepnode_new (wtmovsepnodeTreadmillBase);
		
		// Add roller geometry
		flagReturn = WTnode_addchild (wtmovsepnodeRollerFront, wtmovsepnodeRoller);
		ASSERT (flagReturn);

		// Set position
		WTp3 wtp3TranslationRollerFront;
		wtp3TranslationRollerFront[X] = dLength / 2;
		wtp3TranslationRollerFront[Y] = 0;
		wtp3TranslationRollerFront[Z] = -1*dRollerRadius;		
		flagStatus = WTnode_settranslation (wtmovsepnodeRollerFront, wtp3TranslationRollerFront);
		ASSERT (flagStatus);

		// design: consider making multiple instances of the one roller

		
		// Belt parameters
		const double dBeltWidth = dRollerHeight;
		const double dBeltLength = dLength;
		const double dBeltThickness = dRollerRadius / 10;

		// Draw top platform
		WTgeometry* wtgeometryBelt;
		wtgeometryBelt = WTgeometry_newblock (
			dBeltLength, /*X*/
			dBeltWidth, /*Y*/
			dBeltThickness, /*Z*/
			FALSE); /* Render both sides */
		ASSERT (wtgeometryBelt);

		// Color the roller
		WTgeometry_setmtable (wtgeometryBelt, wtmtable);
		flagReturn = WTgeometry_setmatid (wtgeometryBelt, nMTableIndex);
		ASSERT (flagReturn);

		// Create a containing geometry node
		WTnode* wtnodegeometryBelt = WTgeometrynode_new (NULL, wtgeometryBelt);
		
		// Node for the top belt
		WTnode* wtmovsepnodeBeltTop = WTmovsepnode_new (wtmovsepnodeTreadmillBase);
		ASSERT (wtmovsepnodeBeltTop);	

		// Add in the geometry
		WTnode_addchild (wtmovsepnodeBeltTop, wtnodegeometryBelt);

		// Node for the bottom belt
		WTnode* wtmovsepnodeBeltBottom = WTmovsepnode_new (wtmovsepnodeTreadmillBase);
		ASSERT (wtmovsepnodeBeltBottom);	

		// Add in the geometry
		WTnode_addchild (wtmovsepnodeBeltBottom, wtnodegeometryBelt);

		// Position the bottom belt
		WTp3 wtp3BeltBottomTranslation;
		wtp3BeltBottomTranslation[X] = 0;
		wtp3BeltBottomTranslation[Y] = 0;
		wtp3BeltBottomTranslation[Z] = -2 * dRollerRadius;
		flagStatus = WTnode_settranslation (wtmovsepnodeBeltBottom, 
			wtp3BeltBottomTranslation);
		ASSERT (flagStatus);
	}
	else
	{

		CdmvTerrainData *pCdmvTerrainData = dynamic_cast <CdmvTerrainData*> (pEnvironment);

		// based on info on page 6-21
		// initialize the geometry
		geom = WTgeometry_begin ();
		ASSERT (geom);

		// add the vertices
		int i, j;
		for (i = 0; i < pCdmvTerrainData->GetXDim (); i++)
		{
			for (j = 0; j < pCdmvTerrainData->GetYDim (); j++)
			{
				WTp3 wtp3; // put the vertex points in here
				//wtp3[X] = i * pCdmvTerrainData->GetGridResolution ();
        wtp3[X] = i * pCdmvTerrainData->GetXGridResolution ();
				//wtp3[Y] = j * pCdmvTerrainData->GetGridResolution ();
        wtp3[Y] = j * pCdmvTerrainData->GetYGridResolution ();
				wtp3[Z] = pCdmvTerrainData->GetZValue (i, j);

				WTvertex* wtvertex = WTgeometry_newvertex (geom, wtp3);
				ASSERT (wtvertex);
			}
		}

		// now add the triangle polygons - 
		// note this is based on GL_TRIANGLE_STRIP geometries (how
		// it is implemented in regular DynaMechs), so after the
		// first two vertices, each new vertex will add two more triangles

		FLAG flagStatus;
		for (i = 1; i < pCdmvTerrainData->GetYDim (); i++)
		{
			for (j = 1; j < pCdmvTerrainData->GetXDim (); j++)
			{

				WTpoly* wtpolyTriangle1;
				WTpoly* wtpolyTriangle2;

				// create the new poly
				wtpolyTriangle1 = WTgeometry_beginpoly (geom);
				ASSERT (wtpolyTriangle1);

				// add the vertices to the poly - make CCW to define front face
				flagStatus = WTpoly_addvertex (wtpolyTriangle1, i + j*pCdmvTerrainData->GetYDim ());
				ASSERT (flagStatus);
				flagStatus = WTpoly_addvertex (wtpolyTriangle1, i + (j-1)*pCdmvTerrainData->GetYDim ());
				ASSERT (flagStatus);
				flagStatus = WTpoly_addvertex (wtpolyTriangle1, (i-1) + (j-1)*pCdmvTerrainData->GetYDim ());
				ASSERT (flagStatus);
				// close the poly
				flagStatus = WTpoly_close (wtpolyTriangle1);	
				ASSERT (flagStatus);
				WTpoly_setbothsides (wtpolyTriangle1, TRUE);

				// create the next triangle
				wtpolyTriangle2 = WTgeometry_beginpoly (geom);
				ASSERT (wtpolyTriangle2);

				flagStatus = WTpoly_addvertex (wtpolyTriangle2, (i-1) + j*pCdmvTerrainData->GetYDim ());
				ASSERT (flagStatus);
				flagStatus = WTpoly_addvertex (wtpolyTriangle2, i + j*pCdmvTerrainData->GetYDim ());
				ASSERT (flagStatus);
				flagStatus = WTpoly_addvertex (wtpolyTriangle2, (i-1) + (j-1)*pCdmvTerrainData->GetYDim ());
				ASSERT (flagStatus);


				// close the poly
				flagStatus = WTpoly_close (wtpolyTriangle2);	
				ASSERT (flagStatus);
				WTpoly_setbothsides (wtpolyTriangle2, TRUE);

			}
		}

		// now close the geometry
		flagStatus = WTgeometry_close (geom);
		ASSERT (flagStatus);

		// now compute the normals for shading purposes
//		WTvertex* wtvertex;
//		WTgeometry_beginedit (geom);
//		wtvertex = WTgeometry_getvertices (geom);
//		while (wtvertex)
//		{
//			WTgeometry_computevertexnormal (geom, wtvertex);
//			wtvertex = WTvertex_next (wtvertex);
//		}
//		WTgeometry_endedit (geom);

		
		COLORREF crColor;
		TerrainCoveringType theTerrainCoveringType;
		CString strTextureFile, strTexturePath;
		pCdmvTerrainData->GetCoveringInfo (theTerrainCoveringType,
			crColor, strTextureFile, strTexturePath);
		if (theTerrainCoveringType == TERRAIN_COVERING_COLOR)
		{
//			WTgeometry_setrgb (geom, GetRValue(crColor), 
//				GetGValue(crColor), GetBValue (crColor));

			// Now at the color information
			WTmtable* wtmtable;
			wtmtable = WTmtable_new (
				WTMAT_AMBIENT | WTMAT_DIFFUSE ,
				1, /* estimated entries */
				NULL /* unique name - if NULL WTK makes up one*/);
			ASSERT (wtmtable);

			int nMTableIndex = 0; // index in to material table
			nMTableIndex = WTmtable_newentry (wtmtable);
			// Verify that this is the only entry in the table
			ASSERT (nMTableIndex == 0);

			float fColor[3] = {GetRValue(crColor)/255.0, GetGValue(crColor)/255.0, GetBValue (crColor)/255.0};
			float fColorWhite[3] = {1, 1, 1};

			FLAG flagReturn;

			flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
				fColor, WTMAT_AMBIENT);
			ASSERT (flagReturn);

			flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
				fColorWhite, WTMAT_DIFFUSE);
			ASSERT (flagReturn);

			WTgeometry_setmtable (geom, wtmtable);
			flagReturn = WTgeometry_setmatid (geom, nMTableIndex);
			ASSERT (flagReturn);
      
      /// Set the wireframe only rendering for the terrain
      //WTgeometry_setrenderingstyle(geom,WTRENDER_ANTIALIAS|WTRENDER_WIREFRAME,TRUE);

		}
		else
		{
			CString strTexturePathAndFile = strTexturePath + strTextureFile;
			// Copy this to another buffer because WTK, wants a non-const value
			TCHAR* szTexturePathAndFile = new TCHAR [strTexturePathAndFile.GetLength () + 1];
			_tcscpy (szTexturePathAndFile, strTexturePathAndFile);

			// Apply a texture
			WTgeometry_settexture (
				geom, // terrain geometry
				szTexturePathAndFile, // texture
				TRUE, // do shading
				FALSE); // no transparent
			// If this fails, it is probably because the texture was not found.  This is not
			// a critical failure - the program will just continue executing.
			
			// Clean up
			delete [] szTexturePathAndFile;
		}
		WTnode *wtnodeTerrain;
		wtnodeTerrain = WTgeometrynode_new (root, geom);
		WTnode_setname (wtnodeTerrain, STR_ENVIRONMENT_NAME);

		bReturnStatus = TRUE;

	}

	return bReturnStatus;
}

BOOL CWTKGraphics::UpdateTransforms(dmSystem *pSystem, CdmvSystemData *pCdmvSystemData,
												CPlaybackData *pPlaybackData, GraphicsMode theGraphicsMode)
{
	if (theGraphicsMode == GRAPHICS_REGULAR || theGraphicsMode == GRAPHICS_RECORD)
		ASSERT (pSystem);
	ASSERT (pPlaybackData);

	WTm3 wtm3Rotation;
	WTp3 wtp3Position;

	CdmvArticulationData *pCdmvArticulationData = dynamic_cast <CdmvArticulationData*> (pCdmvSystemData);

	RotationMatrix rmRotation;
	CartesianVector cvPosition;

	if (theGraphicsMode == GRAPHICS_PLAYBACK)
	{
		pPlaybackData->GetNextSnapShotItem (wtp3Position, wtm3Rotation);
	}
	else
	{

		pSystem->getPose(rmRotation, cvPosition);

		// Copy to WTK datatypes
		int i, j;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
				wtm3Rotation[i][j] = rmRotation[i][j];
			wtp3Position[i] = cvPosition[i];
		}
		
		// If in record mode, save the data to the PlaybackData
		if (theGraphicsMode == GRAPHICS_RECORD)
		{
			pPlaybackData->AddItemData (wtp3Position, wtm3Rotation);
		}
	}

	FLAG flagStatus;
	flagStatus = WTnode_setrotation (pCdmvArticulationData->GetWtkNode (), wtm3Rotation);
	ASSERT (flagStatus);
	flagStatus = WTnode_settranslation (pCdmvArticulationData->GetWtkNode (), wtp3Position);
	ASSERT (flagStatus);

	dmArticulation* pArticulation = dynamic_cast<dmArticulation*> (pSystem);
	
	// Go through all of the links, get their state, and update the display
	int nCounter;
	for (nCounter = 0; nCounter < pCdmvArticulationData->m_arrayLinks.GetSize (); nCounter++)
	{

		if (theGraphicsMode == GRAPHICS_PLAYBACK)
		{
			pPlaybackData->GetNextSnapShotItem (wtp3Position, wtm3Rotation);
		}
		else
		{
			dmLink* pLink;
			pLink = dynamic_cast <dmLink*>
				(pCdmvArticulationData->m_arrayLinks.GetAt (nCounter).pLink->GetDynaMechsObject ());

			pLink->getPose (rmRotation, cvPosition);

			// Make sure the all the numbers returned by DynaMechs are finite (ie not +/- INF or NaN).
			// If so, this would indicate an instability, and simulation should be stopped.
			BOOL bUnstable = FALSE;
			int i,j;
			for (i = 0; i < 3; i++)
			{
				for (j = 0; j < 3; j++)
				{
					if (!_finite(rmRotation[i][j]))
					{
						bUnstable = TRUE;
	

					}
				}
				if (!_finite(cvPosition[i]))
				{
					bUnstable = TRUE;
					
				}
			}
			if (bUnstable)
			{
				// DynaMechs is crashing, so alert user
				AfxMessageBox ("The simulation engine, DynaMechs, is generating invalid data,\nindicating \
the simulation has become unstable.\nSimulation will now be aborted.");

				// If unstable and in Record mode, delete the current snapshot, because
				// it is not complete
				if (theGraphicsMode == GRAPHICS_RECORD)
					pPlaybackData->DeleteCurrentSnapShot ();

				// This shouldn't happen when in playback, because it shouldn't have been
				// recorded
				if (theGraphicsMode == GRAPHICS_PLAYBACK)
					ASSERT (0);

				return FALSE;
			}

			// Copy to WTK datatypes
			for (i = 0; i < 3; i++)
			{
				for (j = 0; j < 3; j++)
					wtm3Rotation[i][j] = rmRotation[i][j];
				wtp3Position[i] = cvPosition[i];
			}

			// If in record mode, save the data to the PlaybackData
			if (theGraphicsMode == GRAPHICS_RECORD)
			{
				pPlaybackData->AddItemData (wtp3Position, wtm3Rotation);
			}

		}

		FLAG flagStatus;
		flagStatus = WTnode_setrotation (
			pCdmvArticulationData->m_arrayLinks.GetAt (nCounter).pLink->GetWtkNode (), wtm3Rotation);
		ASSERT (flagStatus);

		flagStatus = WTnode_settranslation (
		pCdmvArticulationData->m_arrayLinks.GetAt (nCounter).pLink->GetWtkNode (), wtp3Position);
		ASSERT (flagStatus);

		// DEBUG
		if (nCounter == 3)
		{
			TRACE ("%f %f %f\n", wtm3Rotation[0][0],wtm3Rotation[0][1], wtm3Rotation[0][2]);
		}

	}

	// Update the camera - in case things changed.
	CDMViewerDoc* pDoc = (CDMViewerDoc*)((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetActiveDocument ();
	CdmvCFGData* pCdmvCFGData = pDoc->GetCFGData ();
	UpdateCamera (TRUE, pCdmvCFGData->GetUseInertialZ());
	
	return TRUE;
}

void CWTKGraphics::UpdateEnvironment(dmEnvironment *pEnvironment, double dDisplayStepTime,
												CPlaybackData *pPlaybackData, GraphicsMode theGraphicsMode)
{
	ASSERT (pPlaybackData);

	// Check if treadmill type
	if (typeid (*pEnvironment) == typeid (dmTreadmill))
	{
		// Then update treadmill

		// Find the Roller nodes
		WTnode* wtnodeRoller = WTuniverse_findnodebyname ("Roller", 0);
		ASSERT (wtnodeRoller);

		if (theGraphicsMode == GRAPHICS_PLAYBACK)
		{
			WTp3 wtp3Position;
			WTm3 wtm3Rotation;
			// Get the pose of the first roller
			pPlaybackData->GetNextSnapShotItem (wtp3Position, wtm3Rotation);
			VERIFY(WTnode_settranslation (wtnodeRoller, wtp3Position));
			VERIFY(WTnode_setrotation (wtnodeRoller, wtm3Rotation));
		}
		else
		{
			// Find the velocity
			Float q[1], qd[1]; // Need to change if support hydrodynamics
			((dmTreadmill*) pEnvironment)->getState (q, qd);

			double dVelocity = qd[0];
			double dWidth = ((dmTreadmill*) pEnvironment)->getWidth ();

			// Hardcode the roller dimension
			const double dRollerRadius = max((dWidth +  ((CdmvTreadmillData*) pEnvironment)->GetLength ()) / 2
				/ ROLLER_RADIUS_SCALE, WTK_MIN); // The rotation speed depends on this

			// Calculate how far to rotate the rollers
			double dRotation = dVelocity * dDisplayStepTime / dRollerRadius;

			// Cause incremental rotation
			// Apparently this is in degress
			FLAG flagStatus = WTnode_rotation (wtnodeRoller, dRotation, 0, 0, WTFRAME_LOCAL);
			ASSERT (flagStatus);

			if (theGraphicsMode == GRAPHICS_RECORD)
			{
				WTp3 wtp3Position;
				WTm3 wtm3Rotation;
				// Get the pose of the first roller
				VERIFY(WTnode_gettranslation (wtnodeRoller, wtp3Position));
				VERIFY(WTnode_getrotation (wtnodeRoller, wtm3Rotation));
				pPlaybackData->AddItemData (wtp3Position, wtm3Rotation);
			}
		}
	}
}

// Clears the scenegraph and the data structures that hold pointers to the WTK nodes
void CWTKGraphics::DeleteArticulation(CdmvArticulationData *pCdmvArticulationData)
{
	ASSERT (pCdmvArticulationData);

	// Deallocate the nodes
	WTnode* wtnodeArticulation = WTuniverse_findnodebyname (STR_ARTICULATION_NAME, 0);

	if (wtnodeArticulation)
	{
		FLAG flagResult = WTnode_delete (wtnodeArticulation);
		ASSERT (flagResult);
	}

	// Clear the articulation
	pCdmvArticulationData->SetWtkNode (NULL);
	pCdmvArticulationData->SetWtkGeometryNode (NULL);

	int nNumLinks = pCdmvArticulationData->m_arrayLinks.GetSize ();
	int i;

	for (i = 0; i < nNumLinks; i++)
	{
		pCdmvArticulationData->m_arrayLinks.GetAt (i).pLink->SetWtkNode (NULL);
		pCdmvArticulationData->m_arrayLinks.GetAt (i).pLink->SetWtkGeometryNode (NULL);
	}

}

void CWTKGraphics::DeleteEnvironmentNode(CdmvEnvironmentData *pCdmvEnvironmentData)
{
	ASSERT (pCdmvEnvironmentData);

	// Deallocate the nodes
	WTnode* wtnodeEnvironment = WTuniverse_findnodebyname (STR_ENVIRONMENT_NAME, 0);

	if (wtnodeEnvironment)
	{
		FLAG flagResult = WTnode_delete (wtnodeEnvironment);
		ASSERT (flagResult);
	}

	if (pCdmvEnvironmentData->GetWtkNode ())
	{		
		// Clear out the WTK data from the environment
		pCdmvEnvironmentData->SetWtkNode (NULL);
		pCdmvEnvironmentData->SetWtkGeometryNode (NULL);
	}
}

BOOL CWTKGraphics::CreateArticulationNodes(CdmvArticulationData *pCdmvArticulationData)
{
	DeleteArticulation (pCdmvArticulationData);

	// Add in the reference node
	CreateReferenceSystemNode (pCdmvArticulationData);
	CString strGraphicsFile, strGraphicsPath;
	pCdmvArticulationData->GetGraphicsModel (strGraphicsFile, strGraphicsPath);
	SetNodeGeometry (pCdmvArticulationData, strGraphicsPath + strGraphicsFile);

	// The link at 0 in the array is assumed to be the root
	if (pCdmvArticulationData->m_arrayLinks.GetSize () > 0)
	{
		// Now add the rest of the links
		CString strUniqueLabel;
		int nCounter;
		for (nCounter = 0; nCounter <
				pCdmvArticulationData->m_arrayLinks.GetSize (); nCounter++)
		{
			CdmvLinkPointer theLinkPointer = (pCdmvArticulationData)->m_arrayLinks.GetAt (nCounter);

			// test if there actually a parent or not -- there can be multiple at the root level
			if (theLinkPointer.pLinkParent != NULL)
			{
				CreateNewNode (theLinkPointer.pLinkParent->GetWtkNode (), theLinkPointer.pLink);
			}
			else
			{
				// Otherwise, its a child of the articulation
				CreateNewNode (pCdmvArticulationData->GetWtkNode(), theLinkPointer.pLink);
			}

			CString strGraphicsFile, strGraphicsPath;
			theLinkPointer.pLink->GetGraphicsModel (strGraphicsFile, strGraphicsPath);
			SetNodeGeometry (theLinkPointer.pLink, strGraphicsPath + strGraphicsFile);

			// The link is tranformed differently depending on the type.
			LinkType theLinkType;
			theLinkType = theLinkPointer.pLink->GetLinkType ();
			if (theLinkType == REVOLUTE_LINK || theLinkType == ZSCREW_TX_LINK || theLinkType == PRISMATIC_LINK)
			{
				structMDHParameters strtMDHParameters;
				Float afMDHParameters[4];
				if (theLinkType == REVOLUTE_LINK || theLinkType == PRISMATIC_LINK)
					dynamic_cast <CdmvMDHLinkData*> (theLinkPointer.pLink)->GetLinkParameters (afMDHParameters);
				else
					// then ZSCREW_TX_LINK
					dynamic_cast <CdmvZScrewTxLinkData*> (theLinkPointer.pLink)->GetLinkParameters (afMDHParameters);
				
				strtMDHParameters.fa = afMDHParameters[0];
				strtMDHParameters.fAlpha = afMDHParameters[1];
				strtMDHParameters.fd = afMDHParameters[2];
				strtMDHParameters.fTheta = afMDHParameters[3];
	
				SetNodeTransform (theLinkPointer.pLink, strtMDHParameters);
			}
				else if (theLinkType == MOBILE_BASE_LINK)
			{
				Quaternion qOrientation;
				CartesianVector cvPosition;
				dynamic_cast <CdmvMobileBaseLinkData*> (theLinkPointer.pLink)->GetPlacement (qOrientation, cvPosition);

				SetNodeTransform (theLinkPointer.pLink, qOrientation, cvPosition);
			}

			else if (theLinkType == SPHERICAL_LINK)
			{
				structSphericalLinkState strtSphericalLinkState;
				CartesianVector cvPosition;

				dynamic_cast <CdmvSphericalLinkData*> (theLinkPointer.pLink)->GetJointOffset (cvPosition);
				dynamic_cast <CdmvSphericalLinkData*> (theLinkPointer.pLink)->GetLinkState (&strtSphericalLinkState);
				
				SetNodeTransformWithEulerAngles (theLinkPointer.pLink, strtSphericalLinkState.eaAngles, cvPosition);
			}
			else if (theLinkType == STATIC_ROOT_LINK)
			{
				// always at 0
				structMDHParameters strtMDHParameters;
				strtMDHParameters.fa = 0;
				strtMDHParameters.fAlpha = 0;
				strtMDHParameters.fd = 0;
				strtMDHParameters.fTheta = 0;

				SetNodeTransform (theLinkPointer.pLink, strtMDHParameters);
			}
			else
			{
				//ASSERT (FALSE);
			}

		}
	}

	// Update the camera - in case things changed.
	UpdateCamera (TRUE);

	return TRUE;
}

BOOL CWTKGraphics::ResetArticulationToInitialValues(CdmvArticulationData *pCdmvArticulationData)
{
	ASSERT (pCdmvArticulationData);

	Quaternion qOrientation;
	CartesianVector cvPosition;
	pCdmvArticulationData->GetRefSystem (qOrientation, cvPosition);
	SetNodeTransform (pCdmvArticulationData, qOrientation, cvPosition);

	// The link at 0 in the array is assumed to be the root
	if (pCdmvArticulationData->m_arrayLinks.GetSize () > 0)
	{
		// Now set the rest of the links
		int nCounter;
		for (nCounter = 0; nCounter <
				pCdmvArticulationData->m_arrayLinks.GetSize (); nCounter++)
		{
			CdmvLinkPointer theLinkPointer = (pCdmvArticulationData)->m_arrayLinks.GetAt (nCounter);


//			SetNodeGeometry (theLinkPointer.pLink, 
//					theLinkPointer.pLink->GetGraphicsModel ());

			// The link is tranformed differently depending on the type.
			LinkType theLinkType;
			theLinkType = theLinkPointer.pLink->GetLinkType ();
			if (theLinkType == REVOLUTE_LINK || theLinkType == ZSCREW_TX_LINK || theLinkType == PRISMATIC_LINK)
			{
				structMDHParameters strtMDHParameters;
				Float afMDHParameters[4];
				if (theLinkType == REVOLUTE_LINK || theLinkType == PRISMATIC_LINK)
					dynamic_cast <CdmvMDHLinkData*> (theLinkPointer.pLink)->GetLinkParameters (afMDHParameters);
				else
					// then ZSCREW_TX_LINK
					dynamic_cast <CdmvZScrewTxLinkData*> (theLinkPointer.pLink)->GetLinkParameters (afMDHParameters);
				
				strtMDHParameters.fa = afMDHParameters[0];
				strtMDHParameters.fAlpha = afMDHParameters[1];
				strtMDHParameters.fd = afMDHParameters[2];
				strtMDHParameters.fTheta = afMDHParameters[3];
	
				SetNodeTransform (theLinkPointer.pLink, strtMDHParameters);
			}
				else if (theLinkType == MOBILE_BASE_LINK)
			{
				Quaternion qOrientation;
				CartesianVector cvPosition;
				dynamic_cast <CdmvMobileBaseLinkData*> (theLinkPointer.pLink)->GetPlacement (qOrientation, cvPosition);

				SetNodeTransform (theLinkPointer.pLink, qOrientation, cvPosition);
			}

			else if (theLinkType == SPHERICAL_LINK)
			{
				structSphericalLinkState strtSphericalLinkState;
				CartesianVector cvPosition;

				dynamic_cast <CdmvSphericalLinkData*> (theLinkPointer.pLink)->GetJointOffset (cvPosition);
				dynamic_cast <CdmvSphericalLinkData*> (theLinkPointer.pLink)->GetLinkState (&strtSphericalLinkState);
				
				SetNodeTransformWithEulerAngles (theLinkPointer.pLink, strtSphericalLinkState.eaAngles, cvPosition);
			}
			else if (theLinkType == STATIC_ROOT_LINK)
			{
				// always at 0
				structMDHParameters strtMDHParameters;
				strtMDHParameters.fa = 0;
				strtMDHParameters.fAlpha = 0;
				strtMDHParameters.fd = 0;
				strtMDHParameters.fTheta = 0;

				SetNodeTransform (theLinkPointer.pLink, strtMDHParameters);
			}
			else
			{
				ASSERT (FALSE);
			}

		}
	}

	// Update the camera - in case things changed.
	CDMViewerDoc* pDoc = (CDMViewerDoc*)((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetActiveDocument ();
	CdmvCFGData* pCdmvCFGData = pDoc->GetCFGData ();
	UpdateCamera (TRUE, pCdmvCFGData->GetUseInertialZ());

	return TRUE;
}

BOOL CWTKGraphics::ResetEnvironmentToInitialValues(CdmvEnvironmentData *pCdmvEnvironmentData)
{
	return TRUE;
}

void CWTKGraphics::LoadNewNodeGeometry(CdmvObject *pCdmvObject, CString strGraphicPath)
{
	// Delete the current one
	DeleteNodeGeometry (pCdmvObject);

	SetNodeGeometry(pCdmvObject, strGraphicPath);
}

void CWTKGraphics::WTKFGDrawCallback(WTwindow *wtkWindow, FLAG flagEye)
{
	CDMViewerDoc* pDoc = (CDMViewerDoc*)((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetActiveDocument ();
	CdmvCFGData* pCdmvCFGData = pDoc->GetCFGData ();

	if (pCdmvCFGData)
	{
		// Common initializations for universe frame
		WTp3 wtp3_uOrigin = {0, 0, 0};
		WTp3 wtp3_uX, wtp3_uY, wtp3_uZ;
		WTp2 wtp2_sOrigin;
		WTp2 wtp2_sX, wtp2_sY, wtp2_sZ;
		
		// Get the orientation of the viewpoint
		WTq wtqWorldToViewpoint;
		WTviewpoint_getorientation (WTuniverse_getviewpoint (), wtqWorldToViewpoint);
		// Get the 3x3 form
		WTm3 wtm3_uRv;
		WTq_2m3 (wtqWorldToViewpoint, wtm3_uRv);

		int nWndPosX, nWndPosY, nWndWidth, nWndHeight;
		WTwindow_getposition (wtkWindow, &nWndPosX, &nWndPosY, &nWndWidth, &nWndHeight);

		if (pDoc->ShowInertialAxes ())
		{
			
			int nInertialAxesWidth; // pixel count of interial axes width
			double dInertialAxesLength; // length of axes in universe units
			pCdmvCFGData->GetInertialAxesData (nInertialAxesWidth, dInertialAxesLength);

			WTp3 wtp3_uX = {dInertialAxesLength, 0, 0};
			WTp3 wtp3_uY = {0, 0, dInertialAxesLength};
			WTp3 wtp3_uZ = {0, -dInertialAxesLength, 0};


			WTwindow_projectpoint (wtkWindow, NULL, wtp3_uOrigin, wtp2_sOrigin);
			WTwindow_projectpoint (wtkWindow, NULL, wtp3_uX, wtp2_sX);
			WTwindow_projectpoint (wtkWindow, NULL, wtp3_uY, wtp2_sY);
			WTwindow_projectpoint (wtkWindow, NULL, wtp3_uZ, wtp2_sZ);


			// Draw the universe's axes
			WTwindow_set2Dfont (wtkWindow, 0);
			WTwindow_set2Dlinewidth (wtkWindow, nInertialAxesWidth);
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

		int nLinkAxesWidth; // pixel count of link axes width
		double dLinkAxesLength; // length of axes in universe units
		pCdmvCFGData->GetLinkAxesData (nLinkAxesWidth, dLinkAxesLength);

		// Pick up the system
		CdmvArticulationData* pArticulation = 
			dynamic_cast <CdmvArticulationData*> (pDoc->GetSystemData ());

		// Could get a callback to repaint the window during a reset (after the system
		// has been deleted, but before a new one has been allocated.  So check if got
		// data, and if not, skip over it
		if (pArticulation)
		{

			// Pick up the root node for later calculations
			WTnode* wtnoderoot = WTuniverse_getrootnodes ();
			ASSERT (wtnoderoot);
			
			WTwindow_set2Dlinewidth (wtkWindow, nLinkAxesWidth);
			WTwindow_set2Dcolor (wtkWindow, 255, 255, 255);

			if (pArticulation->ShowWtkAxes ())
			{
				// Build the axes for the articulation frame
				WTnode* wtnode = pArticulation->GetWtkNode ();

				// This will try to draw before, the articulation has been created (race 
				// condition), so only continue if got a valid pointer
				if (AfxIsValidAddress (wtnode, sizeof (WTnode*), TRUE))
				{

					// Check if supposed to show them
					// Get the path, so can retrieve the entire transform
					WTnodepath* wtnodepath = WTnodepath_new (wtnode, wtnoderoot, 
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
					WTp3 wtp3_pX = {dLinkAxesLength, 0, 0};
					WTp3 wtp3_pY = {0, dLinkAxesLength, 0};
					WTp3 wtp3_pZ = {0, 0, dLinkAxesLength};
					WTp3 wtp3_pOrigin = {0, 0, 0};

					// Transform the points to universe coordinates
					WTm4_xformp3 (wtm4_uTp, wtp3_pOrigin, wtp3_uOrigin);
					WTm4_xformp3 (wtm4_uTp, wtp3_pX, wtp3_uX);
					WTm4_xformp3 (wtm4_uTp, wtp3_pY, wtp3_uY);
					WTm4_xformp3 (wtm4_uTp, wtp3_pZ, wtp3_uZ);

					// Project to screen coordinates
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

			// Go through each link
			int nNumLinks = pArticulation->GetNumberOfLinks ();
			int i;
			for (i = 0; i < nNumLinks; i++)
			{
				// Get the pointer to the link
				CdmvLinkPointer LinkPointer = pArticulation->m_arrayLinks.GetAt (i);
				ASSERT (AfxIsValidAddress (LinkPointer.pLink, sizeof (CdmvLinkData), TRUE));

				// See if supposed to show the axes
				if (LinkPointer.pLink->ShowWtkAxes ())
				{
					// Get the pointer to the WTK node for the link
					WTnode* wtnode = LinkPointer.pLink->GetWtkNode ();

					// Make sure a geometry has been generated, sometimes there are race conditions
					// where this callback is called after a file has been loaded, but
					// before geometries have been drawn
					if (AfxIsValidAddress (wtnode, sizeof (WTnode*), TRUE))
					{

						// Get the path, so can retrieve the entire transform
						WTnodepath* wtnodepath = WTnodepath_new (wtnode, wtnoderoot, 
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
						WTp3 wtp3_pX = {dLinkAxesLength, 0, 0};
						WTp3 wtp3_pY = {0, dLinkAxesLength, 0};
						WTp3 wtp3_pZ = {0, 0, dLinkAxesLength};
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

/*		//  todo: this is a 2D overlay for the terrain - delete it if decide not to use it.
		// if terrain
		CdmvEnvironmentData* pEnvironment = pDoc->GetEnvironmentData ();
		if (typeid (*pEnvironment) == typeid(CdmvTerrainData))
		{
			CdmvTerrainData *pCdmvTerrainData = dynamic_cast <CdmvTerrainData*> (pEnvironment);

			WTp3* wtp3Vertices = new WTp3[pCdmvTerrainData->GetXDim ()*pCdmvTerrainData->GetYDim ()];

			// add the vertices
			int i, j;
			for (i = 0; i < pCdmvTerrainData->GetXDim (); i++)
			{
				for (j = 0; j < pCdmvTerrainData->GetYDim (); j++)
				{
					// Note the transformation from DynaMechs to WTK coordinate frames
					wtp3Vertices[i*pCdmvTerrainData->GetYDim ()+j][X] = i * pCdmvTerrainData->GetGridResolution ();
					wtp3Vertices[i*pCdmvTerrainData->GetYDim ()+j][Z] = j * pCdmvTerrainData->GetGridResolution ();
					wtp3Vertices[i*pCdmvTerrainData->GetYDim ()+j][Y] = -1*pCdmvTerrainData->GetZValue (i, j);
//Steven's, incorrect:					wtp3Vertices[i*pCdmvTerrainData->GetXDim ()+j][X] = i * pCdmvTerrainData->GetGridResolution ();
//					wtp3Vertices[i*pCdmvTerrainData->GetXDim ()+j][Z] = j * pCdmvTerrainData->GetGridResolution ();
//					wtp3Vertices[i*pCdmvTerrainData->GetXDim ()+j][Y] = -1*pCdmvTerrainData->GetZValue (i, j);
				}
			}

			// now add the triangle polygons - 
			// note this is based on GL_TRIANGLE_STRIP geometries (how
			// it is implemented in regular DynaMechs), so after the
			// first two vertices, each new vertex will add two more triangles

			for (i = 1; i < pCdmvTerrainData->GetYDim (); i++)
			{
				for (j = 1; j < pCdmvTerrainData->GetXDim (); j++)
				{

					WTp2 wtp2Vertex1, wtp2Vertex2, wtp2Vertex3;
					WTwindow_projectpoint (wtkWindow, NULL, 
						wtp3Vertices[i + j*pCdmvTerrainData->GetYDim ()], wtp2Vertex1);
					WTwindow_projectpoint (wtkWindow, NULL, 
						wtp3Vertices[i + (j-1)*pCdmvTerrainData->GetYDim ()], wtp2Vertex2);
					WTwindow_projectpoint (wtkWindow, NULL, 
						wtp3Vertices[(i-1) + (j-1)*pCdmvTerrainData->GetYDim ()], wtp2Vertex3);

					WTwindow_draw2Dline (wtkWindow, wtp2Vertex1[X]/nWndWidth, wtp2Vertex1[Y]/nWndHeight,
						wtp2Vertex2[X]/nWndWidth, wtp2Vertex2[Y]/nWndHeight);
					WTwindow_draw2Dline (wtkWindow, wtp2Vertex2[X]/nWndWidth, wtp2Vertex2[Y]/nWndHeight,
						wtp2Vertex3[X]/nWndWidth, wtp2Vertex3[Y]/nWndHeight);
					WTwindow_draw2Dline (wtkWindow, wtp2Vertex3[X]/nWndWidth, wtp2Vertex3[Y]/nWndHeight,
						wtp2Vertex1[X]/nWndWidth, wtp2Vertex1[Y]/nWndHeight);


          ///Second triangle
					WTwindow_projectpoint (wtkWindow, NULL, 
						wtp3Vertices[(i-1) + j*pCdmvTerrainData->GetYDim ()], wtp2Vertex1);
					WTwindow_projectpoint (wtkWindow, NULL, 
						wtp3Vertices[i + j*pCdmvTerrainData->GetYDim ()], wtp2Vertex2);
					WTwindow_projectpoint (wtkWindow, NULL, 
						wtp3Vertices[(i-1) + (j-1)*pCdmvTerrainData->GetYDim ()], wtp2Vertex3);

					WTwindow_draw2Dline (wtkWindow, wtp2Vertex1[X]/nWndWidth, wtp2Vertex1[Y]/nWndHeight,
						wtp2Vertex2[X]/nWndWidth, wtp2Vertex2[Y]/nWndHeight);
					WTwindow_draw2Dline (wtkWindow, wtp2Vertex2[X]/nWndWidth, wtp2Vertex2[Y]/nWndHeight,
						wtp2Vertex3[X]/nWndWidth, wtp2Vertex3[Y]/nWndHeight);
					WTwindow_draw2Dline (wtkWindow, wtp2Vertex3[X]/nWndWidth, wtp2Vertex3[Y]/nWndHeight,
						wtp2Vertex1[X]/nWndWidth, wtp2Vertex1[Y]/nWndHeight);

				}
			}

			// Deallocate the vertices
			delete [] wtp3Vertices;

		}
*/
  }
/*  //if(pCdmvCFGData->GetLogoLoadFlag()==FALSE)
  if(pCdmvCFGData->GetLogoLoadFlag()==0)
  {
    /// Load a start-up logo image file to display only once initially
    WTwindow_loadimage (wtkWindow, "lg.dll", 1.0, TRUE, TRUE);
    pCdmvCFGData->SetLogoLoadFlag();
    AfxMessageBox ("Logo loaded!\nNeed to put a delay?");
    // Why is this kept called? Flag setting problem???
    // Put in delay so that start-up logo is displayed for some time.. 
  }*/
}


void CWTKGraphics::WTKFGDrawTerrainGrid(WTwindow *wtkWindow, FLAG flagEye)
{
  CDMViewerDoc* pDocT = (CDMViewerDoc*)((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetActiveDocument ();
  
		CdmvEnvironmentData* pEnvironmentT = pDocT->GetEnvironmentData ();
		if (typeid (*pEnvironmentT) == typeid(CdmvTerrainData))	//Only do for Terrain, not Treadmill
		{
			CdmvTerrainData *pCdmvTerrainDataT = dynamic_cast <CdmvTerrainData*> (pEnvironmentT);

      BOOL WireframeOnOff;
      COLORREF crWireframeColor;

      double dWireframeLnWidth, dWireframeElevation ;
      pCdmvTerrainDataT->GetWireframeInfo (WireframeOnOff,
        crWireframeColor, dWireframeLnWidth, dWireframeElevation);
      //Checks if Wireframe Overlay On or Off & run code accordingly
      if(WireframeOnOff)
      {
  			WTp3* wtp3VerticesT = new WTp3[pCdmvTerrainDataT->GetXDim ()*pCdmvTerrainDataT->GetYDim ()];

	  		// Add the vertices
		  	int i, j;
			  for (i = 0; i < pCdmvTerrainDataT->GetXDim (); i++)
			  {
  				for (j = 0; j < pCdmvTerrainDataT->GetYDim (); j++)
				  {
  					// Transform from DynaMechs to WTK coordinate frames
	  				//wtp3VerticesT[i*pCdmvTerrainDataT->GetYDim ()+j][X] = i * pCdmvTerrainDataT->GetGridResolution ();
            wtp3VerticesT[i*pCdmvTerrainDataT->GetYDim ()+j][X] = i * pCdmvTerrainDataT->GetXGridResolution ();
	  				//wtp3VerticesT[i*pCdmvTerrainDataT->GetYDim ()+j][Z] = j * pCdmvTerrainDataT->GetGridResolution ();
            wtp3VerticesT[i*pCdmvTerrainDataT->GetYDim ()+j][Z] = j * pCdmvTerrainDataT->GetYGridResolution ();
	  				wtp3VerticesT[i*pCdmvTerrainDataT->GetYDim ()+j][Y] = -dWireframeElevation -1*pCdmvTerrainDataT->GetZValue (i, j);
	  			}
	  		}

  			WTp3* wtp3Tmp3DTriangle1 = new WTp3[3];	//Temp storage for drawing triangle terrain 3D lines
  			WTp3* wtp3Tmp3DTriangle2 = new WTp3[3];	//Temp storage for drawing triangle terrain 3D lines

        float WireframeCrRed, WireframeCrGreen, WireframeCrBlue;
        WireframeCrRed = GetRValue(crWireframeColor);
        WireframeCrGreen = GetGValue(crWireframeColor);
        WireframeCrBlue = GetBValue(crWireframeColor);

  			for (i = 1; i < pCdmvTerrainDataT->GetYDim (); i++)
	  		{
		  		for (j = 1; j < pCdmvTerrainDataT->GetXDim (); j++)
			  	{
				  	//First triangle
					  WTp3_copy (wtp3VerticesT[i + j*pCdmvTerrainDataT->GetYDim ()], wtp3Tmp3DTriangle1[0]);
            WTp3_copy (wtp3VerticesT[i + (j-1)*pCdmvTerrainDataT->GetYDim ()], wtp3Tmp3DTriangle1[1]);
            WTp3_copy (wtp3VerticesT[(i-1) + (j-1)*pCdmvTerrainDataT->GetYDim ()], wtp3Tmp3DTriangle1[2]);
		  			//Second triangle
            WTp3_copy (wtp3VerticesT[(i-1) + j*pCdmvTerrainDataT->GetYDim ()], wtp3Tmp3DTriangle2[0]);
				  	WTp3_copy (wtp3VerticesT[i + j*pCdmvTerrainDataT->GetYDim ()], wtp3Tmp3DTriangle2[1]);
					  WTp3_copy (wtp3VerticesT[(i-1) + (j-1)*pCdmvTerrainDataT->GetYDim ()], wtp3Tmp3DTriangle2[2]);

            WTwindow_set3Dlinewidth(wtkWindow, dWireframeLnWidth);
            WTwindow_set3Dcolor(wtkWindow, WireframeCrRed, WireframeCrGreen, WireframeCrBlue);

            WTwindow_draw3Dlines (wtkWindow, wtp3Tmp3DTriangle1, 3, WTLINE_CLOSE);
            WTwindow_draw3Dlines (wtkWindow, wtp3Tmp3DTriangle2, 3, WTLINE_CLOSE);
				  }
			  }
			
			  delete [] wtp3Tmp3DTriangle1;	//Deallocate the 1st triangle array
			  delete [] wtp3Tmp3DTriangle2;	//Deallocate the 2nd triangle array
        // Deallocate the vertices
	  		delete [] wtp3VerticesT;
      }// End of if(WireframeOnOff)
		}
}


void CWTKGraphics::UpdateCamera(BOOL bRecalculateExamineView, BOOL bMaintainInertialZ)
{
	// Find the current camera mode
	CDMViewerApp* pApp = (CDMViewerApp*)AfxGetApp();
	CMainFrame *pFrameWnd = (CMainFrame*)pApp->m_pMainWnd;
	CDMViewerDoc* pDoc = (CDMViewerDoc*)pFrameWnd->GetActiveDocument ();

// EDIT 5/22/2003:
// Previously, RobotBuilder treated Pan and Examine completely differently
// As part of the changes to pan mode, the center of interest is now actively
// updated. As such, the camera is now updated regardless of whether the
// camera is in Pan or Examine mode
//
// Note that the "UpdateExamineView" functions are now a bit of a misnomer,
// as they are used to update the camera regardless of whether the camera
// is in pan _or_ examine mode

//	if (!pDoc->GetCameraData ()->GetViewInPanMode ())
//	{
		// Then examine mode
		// Get the COI node
		WTnode* wtnodeCOI;
		wtnodeCOI = dynamic_cast <CdmvArticulationData*> (pDoc->GetSystemData ())->
			GetCameraCenterOfInterest ();

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

			WTm4_xformp3 (wtm4_world2coi, wtp3Offset, wtp3COI);

			if (bMaintainInertialZ)
			{
				WTp3 wtp3LastCOI;
				WTp3 wtp3Delta;
				WTm4 wtm4_coi2world;

				WTm4_invert(wtm4_world2coi, wtm4_coi2world);

				WTm4_xformp3 (m_wtm4LastTransform, wtp3Offset, wtp3LastCOI);

				wtp3Delta[X] = 0;
				wtp3Delta[Y] = wtp3LastCOI[Y] - wtp3COI[Y];
				wtp3Delta[Z] = 0;
				
				// fix the inertial Z (WTK Y) coordinate
				wtp3COI[Y] = wtp3LastCOI[Y];

				// transform back to local coordinates
				WTm4_rotatep3 (wtm4_coi2world, wtp3Delta, wtp3Delta);
				WTp3_add(wtp3Delta, wtp3Offset, wtp3Offset);

				pDoc->GetCameraData ()->SetCenterOfInterestOffset(wtp3Offset);

				// save the transform for next time
				WTm4_copy(wtm4_world2coi, m_wtm4LastTransform);
			}


//			wtp3COI[X] = wtm4_world2coi[3][0];
//			wtp3COI[Y] = wtm4_world2coi[3][1];
//			wtp3COI[Z] = wtm4_world2coi[3][2];

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
			pDoc->GetWTKView ()->m_wndWTK.m_pCameraControl->RecalculateExamineViewParameters (wtp3COI);
		else
		{
			if (pDoc->GetCameraData ()->GetUseViewportFrameForExamineView ())
				pDoc->GetWTKView ()->m_wndWTK.m_pCameraControl->UpdateExamineView2 (wtp3COI);
			else
				pDoc->GetWTKView ()->m_wndWTK.m_pCameraControl->UpdateExamineView (wtp3COI);
		}

// See Note Above		
//	}
//	// else don't need to update anything because in pan mode, but do need to update the light
//	else
//	{
//		pDoc->GetWTKView ()->m_wndWTK.m_pCameraControl->UpdatePanView2 ();
//	}
}

WTnode* CWTKGraphics::GetCameraDirectedLight()
{
	return m_wtnodeCameraDirectedLight;
}


void CWTKGraphics::SetLastTransform()
{
	// Find the current camera mode
	CDMViewerApp* pApp = (CDMViewerApp*)AfxGetApp();
	CMainFrame *pFrameWnd = (CMainFrame*)pApp->m_pMainWnd;
	CDMViewerDoc* pDoc = (CDMViewerDoc*)pFrameWnd->GetActiveDocument ();

	// Then examine mode
	// Get the COI node
	WTnode* wtnodeCOI;
	wtnodeCOI = dynamic_cast <CdmvArticulationData*> (pDoc->GetSystemData ())->
	GetCameraCenterOfInterest ();

	// Get the offset
	WTp3 wtp3Offset;
	pDoc->GetCameraData ()->GetCenterOfInterestOffset (wtp3Offset);

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
		FLAG flagSuccess = WTnodepath_gettransform (wtnodepath, m_wtm4LastTransform);
		ASSERT (flagSuccess);
		// Done with nodepath, so delete it
		VERIFY(WTnodepath_delete (wtnodepath));
	}
}
