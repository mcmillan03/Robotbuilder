// PrimitiveHemisphere.cpp: implementation of the CPrimitiveHemisphere class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "PrimitiveHemisphere.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrimitiveHemisphere::CPrimitiveHemisphere()
{
	m_strtPrimitiveHemisphereData.dRadius = 1;
	m_strtPrimitiveHemisphereData.nLatitudeCount = 10;
	m_strtPrimitiveHemisphereData.nLongitudeCount = 20;
	m_strtPrimitiveHemisphereData.bRenderBothSides = TRUE;
	m_strtPrimitiveHemisphereData.bUseGouraudShading = TRUE;
	m_strName = "Hemisphere";
}

CPrimitiveHemisphere::~CPrimitiveHemisphere()
{

}

void CPrimitiveHemisphere::GetPrimitiveHemisphereData(structPrimitiveHemisphereData *pstrtPrimitiveHemisphereData) const
{
	ASSERT (pstrtPrimitiveHemisphereData);

	pstrtPrimitiveHemisphereData->dRadius = m_strtPrimitiveHemisphereData.dRadius;
	pstrtPrimitiveHemisphereData->nLatitudeCount = m_strtPrimitiveHemisphereData.nLatitudeCount;
	pstrtPrimitiveHemisphereData->nLongitudeCount = m_strtPrimitiveHemisphereData.nLongitudeCount;
	pstrtPrimitiveHemisphereData->bRenderBothSides = m_strtPrimitiveHemisphereData.bRenderBothSides;
	pstrtPrimitiveHemisphereData->bUseGouraudShading = m_strtPrimitiveHemisphereData.bUseGouraudShading;
}

void CPrimitiveHemisphere::SetPrimitiveHemisphereData(const structPrimitiveHemisphereData *pstrtPrimitiveHemisphereData)
{
	ASSERT (pstrtPrimitiveHemisphereData);

	m_strtPrimitiveHemisphereData.dRadius = pstrtPrimitiveHemisphereData->dRadius;
	m_strtPrimitiveHemisphereData.nLatitudeCount = pstrtPrimitiveHemisphereData->nLatitudeCount;
	m_strtPrimitiveHemisphereData.nLongitudeCount = pstrtPrimitiveHemisphereData->nLongitudeCount;
	m_strtPrimitiveHemisphereData.bRenderBothSides = pstrtPrimitiveHemisphereData->bRenderBothSides;
	m_strtPrimitiveHemisphereData.bUseGouraudShading = pstrtPrimitiveHemisphereData->bUseGouraudShading;
}

void CPrimitiveHemisphere::GetInertiaTensor(double dIcg[][3]) const
{
	// First zero the matrix passed in
	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			dIcg[i][j] = 0;

	// Pick up the scale
	structPrimitiveScaleData strtPrimitiveScaleData;
	m_PrimitiveScale.GetPrimitiveScaleAbsoluteData (&strtPrimitiveScaleData);

	// Initialize the axes with the radius size
	double dX,dY,dZ;
	dX = dY = dZ = m_strtPrimitiveHemisphereData.dRadius;

	// Now scale the axes
	dX *= strtPrimitiveScaleData.dXScale;
	dY *= strtPrimitiveScaleData.dYScale;
	dZ *= strtPrimitiveScaleData.dZScale;

	// Calculate 
	dIcg[0][0] = m_dMass * (dZ*dZ + 19.0/64.0*dY*dY) / 5.0;
	dIcg[1][1] = m_dMass * (dX*dX + dZ*dZ) / 5.0;
	dIcg[2][2] = m_dMass * (dX*dX + 19.0/64.0*dY*dY) / 5.0;	
}

void CPrimitiveHemisphere::GetCenterOfGravity(double dPos[]) const
{
	structPrimitivePlacementData strtPrimitivePlacementData;
	m_PrimitivePlacement.GetPrimitivePlacementData (&strtPrimitivePlacementData);

	// Copy the rotation into a WTm3
	WTm3 wtm3_pRl; // Will rotate a row vector in primitive frame to be in terms of the link frame
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			wtm3_pRl[i][j] = strtPrimitivePlacementData.dRotationMatrix[i][j];

	// Get the scale data
	structPrimitiveScaleData strtPrimitiveScaleData;
	m_PrimitiveScale.GetPrimitiveScaleAbsoluteData (&strtPrimitiveScaleData);

	// Build the position of the cog in local coordinates
	WTp3 wtp3_pPcog; // position of the cog in primitive coords
	WTp3_init (wtp3_pPcog);
	// Note local coord frame already at base 
	// Move to cog from base
	wtp3_pPcog[1] = -m_strtPrimitiveHemisphereData.dRadius * 3.0 / 8.0 * strtPrimitiveScaleData.dYScale;
	// WTK scales the hemisphere strangely.  When scaled in the y direction, the base moves
	// -h(s-1)/2 ????  - so compensate for this
	wtp3_pPcog[1] += m_strtPrimitiveHemisphereData.dRadius*(strtPrimitiveScaleData.dYScale - 1.0) / 2.0;

	// Rotate the cog in primitive coords to be in terms of the link coords
	WTp3 wtp3_lPcog; // position of the cog in link coords
	WTp3_multm3 (wtp3_pPcog, wtm3_pRl, wtp3_lPcog);

	// Sum the position of the link with the cog offset
	dPos[0] = strtPrimitivePlacementData.dTranslationX + wtp3_lPcog[0];
	dPos[1] = strtPrimitivePlacementData.dTranslationY + wtp3_lPcog[1];
	dPos[2] = strtPrimitivePlacementData.dTranslationZ + wtp3_lPcog[2];
}


