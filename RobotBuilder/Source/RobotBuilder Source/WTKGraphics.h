// WTKGraphics.h: interface for the CWTKGraphics class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WTKGRAPHICS_H__1C4966BB_9AD9_42FE_8428_4A948EF03EE8__INCLUDED_)
#define AFX_WTKGRAPHICS_H__1C4966BB_9AD9_42FE_8428_4A948EF03EE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wt.h>

#include <dm.h>
#include "dmvMDHLinkData.h"
#include "dmvMobileBaseLinkData.h"
#include "dmvSystemData.h"
#include "dmvRevoluteLinkData.h"
#include "dmvZScrewTxLinkData.h"
#include "dmvEnvironmentData.h"
#include "FindFile.h"

#include "dmvArticulationData.h"
#include "PlaybackData.h"

#include <dmEnvironment.hpp>
#include <dmSystem.hpp>

#define STR_REFSYS_NODE_NAME	"ReferenceSystemNode"
#define STR_AXES_NODE_NAME		"AxesNode"
#define STR_ENVIRONMENT_NAME		"EnvironmentNode"
#define STR_ARTICULATION_NAME	"ArticulationNode"

#define CAMERA_LIGHT_INTENSITY 0.30f

typedef enum {GRAPHICS_REGULAR, GRAPHICS_RECORD, GRAPHICS_PLAYBACK} GraphicsMode;

class CWTKGraphics  
{
public:
	void SetLastTransform(void);
	WTnode* GetCameraDirectedLight ();
	void UpdateCamera (BOOL bRecalculateExamineView, BOOL bMaintainInertialZ = false);
	static void WTKFGDrawCallback (WTwindow* wtkWindow, FLAG flagEye);
	static void WTKFGDrawTerrainGrid (WTwindow* wtkWindow, FLAG flagEye);
	void LoadNewNodeGeometry (CdmvObject *pCdmvObject, CString strGraphicPath);
	BOOL ResetEnvironmentToInitialValues (CdmvEnvironmentData *pCdmvEnvironmentData);
	BOOL ResetArticulationToInitialValues (CdmvArticulationData *pCdmvArticulationData);
	BOOL CreateArticulationNodes (CdmvArticulationData *pCdmvArticulationData);
	CWTKGraphics();
	virtual ~CWTKGraphics();
	void SetNodeTransformWithEulerAngles (CdmvObject *pCdmvObject, EulerAngles eaAngles, CartesianVector cvPosition);
	void QuaternionToForwardRotation (Quaternion q, WTm3 &wtm3);
	void EulerAnglesToForwardRotation (EulerAngles eaAngles, WTm3 &wtm3);
	BOOL CreateReferenceSystemNode (CdmvArticulationData *pCdmvArticulationData);
	void IndicateSelectedModel (CdmvObject *pCdmvObject, BOOL bEnable);
	void SetNodeTransform (CdmvObject *pCdmvObject, Quaternion qOrientation, CartesianVector cvPosition);
	BOOL BuildBaseSceneGraph ();
	BOOL CreateNewNode(WTnode* wtnodeParent, CdmvObject* pCdmvObject);
	void SetNodeTransform (CdmvObject *pCdmvObject, structMDHParameters strtMDHParameters);
	BOOL SetNodeGeometry (CdmvObject *pCdmvObject, CString strGraphicPath);
	void UpdateEnvironment (dmEnvironment* pEnvironment, double dDisplayStepTime,
												CPlaybackData *pPlaybackData, GraphicsMode theGraphicsMode);
	BOOL UpdateTransforms (dmSystem *pSystem, CdmvSystemData *pCdmvSystemData,
												CPlaybackData *pPlaybackData, GraphicsMode theGraphicsMode);
	BOOL CreateEnvironmentNode (CdmvEnvironmentData* pEnvironment);

private:
	void DeleteEnvironmentNode (CdmvEnvironmentData* pCdmvEnvironmentData);
	void DeleteArticulation (CdmvArticulationData* pCdmvArticulationData);
	BOOL m_bShowAxes;
	WTnode* m_wtnodeCameraDirectedLight;

protected:
  int LogoLoaded;
	WTm4 m_wtm4LastTransform;
	CFindFile *m_pFindFile;
	BOOL CreateSystemTransform ();
	BOOL CreateLightNodes ();
	void DHto4x4Matrix (const structMDHParameters* pstrtMDHParameters, WTm4& rwtm4TransformMatrix);
	BOOL GetReferenceSystemNode (WTnode** pwtnodeRefSys);
	void DeleteNodeGeometry (CdmvObject *pCdmvObject);
	void GetNodeFromLabel (CString strLabel, int nOccurrence, WTnode** pwtnode);

};

#endif // !defined(AFX_WTKGRAPHICS_H__1C4966BB_9AD9_42FE_8428_4A948EF03EE8__INCLUDED_)
