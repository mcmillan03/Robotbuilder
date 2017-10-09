// PrimitiveCone.cpp: implementation of the CPrimitiveCone class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "PrimitiveCone.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrimitiveCone::CPrimitiveCone()
{
	m_strtPrimitiveConeData.dHeight = 1;
	m_strtPrimitiveConeData.dRadius = 1;
	m_strtPrimitiveConeData.nTess = 20;
	m_strtPrimitiveConeData.bRenderBothSides = FALSE;
	m_strName = "Cone";

}

CPrimitiveCone::~CPrimitiveCone()
{

}

void CPrimitiveCone::GetPrimitiveConeData(structPrimitiveConeData *pstrtPrimitiveConeData) const
{
	ASSERT (pstrtPrimitiveConeData);

	pstrtPrimitiveConeData->dHeight = m_strtPrimitiveConeData.dHeight;
	pstrtPrimitiveConeData->dRadius = m_strtPrimitiveConeData.dRadius;
	pstrtPrimitiveConeData->nTess = m_strtPrimitiveConeData.nTess;
	pstrtPrimitiveConeData->bRenderBothSides = m_strtPrimitiveConeData.bRenderBothSides;
}

void CPrimitiveCone::SetPrimitiveConeData(const structPrimitiveConeData *pstrtPrimitiveConeData)
{
	ASSERT (pstrtPrimitiveConeData);

	m_strtPrimitiveConeData.dHeight = pstrtPrimitiveConeData->dHeight;
	m_strtPrimitiveConeData.dRadius = pstrtPrimitiveConeData->dRadius;
	m_strtPrimitiveConeData.nTess = pstrtPrimitiveConeData->nTess;
	m_strtPrimitiveConeData.bRenderBothSides = pstrtPrimitiveConeData->bRenderBothSides;
}

void CPrimitiveCone::GetCenterOfGravity(double dPos[]) const
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
	// Subtract to translate the to the base (the coords are halfway up the height along y)
	wtp3_pPcog[1] = m_strtPrimitiveConeData.dHeight / 2.0 * strtPrimitiveScaleData.dYScale; 
	// Move to cog from base
	wtp3_pPcog[1] -= m_strtPrimitiveConeData.dHeight / 4.0 * strtPrimitiveScaleData.dYScale;

	// Rotate the cog in primitive coords to be in terms of the link coords
	WTp3 wtp3_lPcog; // position of the cog in link coords
	WTp3_multm3 (wtp3_pPcog, wtm3_pRl, wtp3_lPcog);

	// Sum the position of the link with the cog offset
	dPos[0] = strtPrimitivePlacementData.dTranslationX + wtp3_lPcog[0];
	dPos[1] = strtPrimitivePlacementData.dTranslationY + wtp3_lPcog[1];
	dPos[2] = strtPrimitivePlacementData.dTranslationZ + wtp3_lPcog[2];
}

void CPrimitiveCone::GetInertiaTensor(double dIcg[][3]) const
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
	dX = m_strtPrimitiveConeData.dRadius * strtPrimitiveScaleData.dXScale;
	dZ = m_strtPrimitiveConeData.dRadius * strtPrimitiveScaleData.dZScale;
	dY = m_strtPrimitiveConeData.dHeight * strtPrimitiveScaleData.dYScale;

	// Use the formulas to find the values
	dIcg[0][0] = 3.0/20.0 * m_dMass * dZ*dZ + 3.0/80.0 * m_dMass * dY*dY;
	dIcg[1][1] = 3.0/20.0 * m_dMass * (dX*dX + dZ*dZ);
	dIcg[2][2] = 3.0/20.0 * m_dMass * dX*dX + 3.0/80.0 * m_dMass * dY*dY;
}


