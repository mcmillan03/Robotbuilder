// PrimitiveCylinder.cpp: implementation of the CPrimitiveCylinder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "PrimitiveCylinder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrimitiveCylinder::CPrimitiveCylinder()
{
	m_strtPrimitiveCylinderData.dRadius = 1;
	m_strtPrimitiveCylinderData.dHeight = 1;
	m_strtPrimitiveCylinderData.nTess = 20;
	m_strtPrimitiveCylinderData.bUseGouraudShading = TRUE;
	m_strtPrimitiveCylinderData.bRenderBothSides = FALSE;
	m_strName = "Cylinder";

}

CPrimitiveCylinder::~CPrimitiveCylinder()
{

}

void CPrimitiveCylinder::SetPrimitiveCylinderData(const structPrimitiveCylinderData *pstrtPrimitiveCylinderData)
{
	ASSERT (pstrtPrimitiveCylinderData);

	m_strtPrimitiveCylinderData.dRadius = pstrtPrimitiveCylinderData->dRadius;
	m_strtPrimitiveCylinderData.dHeight = pstrtPrimitiveCylinderData->dHeight;
	m_strtPrimitiveCylinderData.nTess = pstrtPrimitiveCylinderData->nTess;
	m_strtPrimitiveCylinderData.bUseGouraudShading = pstrtPrimitiveCylinderData->bUseGouraudShading;
	m_strtPrimitiveCylinderData.bRenderBothSides = pstrtPrimitiveCylinderData->bRenderBothSides;
}

void CPrimitiveCylinder::GetPrimitiveCylinderData(structPrimitiveCylinderData *pstrtPrimitiveCylinderData) const
{
	ASSERT (pstrtPrimitiveCylinderData);

	pstrtPrimitiveCylinderData->dRadius = m_strtPrimitiveCylinderData.dRadius;
	pstrtPrimitiveCylinderData->dHeight = m_strtPrimitiveCylinderData.dHeight;
	pstrtPrimitiveCylinderData->nTess = m_strtPrimitiveCylinderData.nTess;
	pstrtPrimitiveCylinderData->bUseGouraudShading = m_strtPrimitiveCylinderData.bUseGouraudShading;
	pstrtPrimitiveCylinderData->bRenderBothSides = m_strtPrimitiveCylinderData.bRenderBothSides;
}

void CPrimitiveCylinder::GetInertiaTensor(double dIcg[][3]) const
{
	// Zero the elements
	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			dIcg[i][j] = 0;

	// Get the scale
	structPrimitiveScaleData strtPrimitiveScaleData;
	m_PrimitiveScale.GetPrimitiveScaleAbsoluteData (&strtPrimitiveScaleData);	
	
	// Get the lengths and scale them
	double dX, dY, dZ;
	dX = m_strtPrimitiveCylinderData.dRadius * strtPrimitiveScaleData.dXScale;
	dZ = m_strtPrimitiveCylinderData.dRadius * strtPrimitiveScaleData.dZScale;
	dY = m_strtPrimitiveCylinderData.dHeight * strtPrimitiveScaleData.dYScale;

	// Use the formulas to find the values
	dIcg[0][0] = 1.0/4.0 * m_dMass * dZ*dZ + 1.0/12.0 * m_dMass * dY*dY;
	dIcg[1][1] = 1.0/4.0 * m_dMass * (dX*dX + dZ*dZ);
	dIcg[2][2] = 1.0/4.0 * m_dMass * dX*dX + 1.0/12.0 * m_dMass * dY*dY;
	
}

void CPrimitiveCylinder::GetCenterOfGravity(double dPos[]) const
{
	structPrimitivePlacementData strtPrimitivePlacementData;
	m_PrimitivePlacement.GetPrimitivePlacementData (&strtPrimitivePlacementData);

	dPos[0] = strtPrimitivePlacementData.dTranslationX;
	dPos[1] = strtPrimitivePlacementData.dTranslationY;
	dPos[2] = strtPrimitivePlacementData.dTranslationZ;

}


