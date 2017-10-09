// RBModelerRBMGraphicView.h: interface for the CRBModelerRBMGraphicView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RBModelerRBMGRAPHICVIEW_H__D69C04E8_0CC2_490D_B57D_50E2E37CB730__INCLUDED_)
#define AFX_RBModelerRBMGRAPHICVIEW_H__D69C04E8_0CC2_490D_B57D_50E2E37CB730__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RBMGraphicView.h"
#include "Primitive.h"
#include "Model.h"
// this a wrapper class for CRBMGraphicView for RBModeler
#define STR_MODEL_NAME	"MainModel"

#define CAMERA_LIGHT_INTENSITY	0.30f

class CRBModelerRBMGraphicView : public CRBMGraphicView
{
public:
	static WTnode* GetCameraDirectedLight ();
	static void UpdateCamera(BOOL bRecalculateExamineView);
	static void ShowBoundingBox (BOOL bShow, const CPrimitive* pPrimitive);
	static void WTKDrawCallback (WTwindow* wtkWindow, FLAG flagEye);
	static void WTKFGDrawCallback (WTwindow* wtkWindow, FLAG flagEye);
	static void UpdatePrimitiveScale (CPrimitive* pPrimitive);
	static void InitializeScene ();
	static void UpdatePrimitivePlacement (CPrimitive *pPrimitive);
	static void UpdatePrimitive (CPrimitive *pPrimitive);
	static void LoadNewModel (const CModel* pModel);
	static void DeletePrimitive (const CPrimitive *pPrimitive);
	static void AddPrimitive (CPrimitive* pPrimitive);
	static WTnode* GetPrimitiveNode (const CPrimitive* pPrimitive);
	CRBModelerRBMGraphicView();
	virtual ~CRBModelerRBMGraphicView();

protected:
	static WTnode* GetModelNode ();
	static BOOL CreateSystemTransform ();
	static BOOL CreateLightNodes ();
	static WTnode* m_wtnodeCameraDirectedLight;
};

#endif // !defined(AFX_RBModelerRBMGRAPHICVIEW_H__D69C04E8_0CC2_490D_B57D_50E2E37CB730__INCLUDED_)
