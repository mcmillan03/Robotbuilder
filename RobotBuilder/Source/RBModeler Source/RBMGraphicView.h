// RBMGraphicView.h: interface for the CRBMGraphicView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RBMGraphicView_H__00AFC7E5_4F5C_409F_B1AD_0C9AE8D883CF__INCLUDED_)
#define AFX_RBMGraphicView_H__00AFC7E5_4F5C_409F_B1AD_0C9AE8D883CF__INCLUDED_

#include "Model.h"
#include "Primitive.h"
#include "wt.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRBMGraphicView  
{
public:
	static void SetPrimitiveScale (CPrimitive *pPrimitive, WTnode* wtnodePrimitive);
	static void SetPrimitiveCovering (CPrimitive *pPrimitive, WTnode* wtnodePrimitive);
	static void SetPrimitivePlacement (CPrimitive* pPrimitive, WTnode* wtnodePrimitive);
	static void AddPrimitive (CPrimitive* pPrimitive, WTnode* wtnodeParent);
	static void LoadNewModel (const CModel* pModel, WTnode** pwtsepnodeBase);
	CRBMGraphicView();
	virtual ~CRBMGraphicView();

};

#endif // !defined(AFX_RBMGraphicView_H__00AFC7E5_4F5C_409F_B1AD_0C9AE8D883CF__INCLUDED_)
