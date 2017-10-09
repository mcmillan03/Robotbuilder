// PrimitiveTruncatedCone.cpp: implementation of the CPrimitiveTruncatedCone class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "PrimitiveTruncatedCone.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrimitiveTruncatedCone::CPrimitiveTruncatedCone()
{
	m_strtPrimitiveTruncatedConeData.dHeight = 1;
	m_strtPrimitiveTruncatedConeData.dBaseRadius = 1;
	m_strtPrimitiveTruncatedConeData.dTopRadius = .5;
	m_strtPrimitiveTruncatedConeData.nTess = 20;
	m_strtPrimitiveTruncatedConeData.bRenderBothSides = FALSE;
	m_strtPrimitiveTruncatedConeData.bUseGouraudShading = TRUE;
	m_strName = "Truncated Cone";
}

CPrimitiveTruncatedCone::~CPrimitiveTruncatedCone()
{

}

void CPrimitiveTruncatedCone::GetPrimitiveTruncatedConeData(structPrimitiveTruncatedConeData *pstrtPrimitiveTruncatedConeData) const
{
	ASSERT (pstrtPrimitiveTruncatedConeData);

	pstrtPrimitiveTruncatedConeData->dHeight = m_strtPrimitiveTruncatedConeData.dHeight;
	pstrtPrimitiveTruncatedConeData->dBaseRadius = m_strtPrimitiveTruncatedConeData.dBaseRadius;
	pstrtPrimitiveTruncatedConeData->dTopRadius = m_strtPrimitiveTruncatedConeData.dTopRadius;
	pstrtPrimitiveTruncatedConeData->nTess = m_strtPrimitiveTruncatedConeData.nTess;
	pstrtPrimitiveTruncatedConeData->bRenderBothSides = m_strtPrimitiveTruncatedConeData.bRenderBothSides;
	pstrtPrimitiveTruncatedConeData->bUseGouraudShading = m_strtPrimitiveTruncatedConeData.bUseGouraudShading;
}

void CPrimitiveTruncatedCone::SetPrimitiveTruncatedConeData(const structPrimitiveTruncatedConeData *pstrtPrimitiveTruncatedConeData)
{
	ASSERT (pstrtPrimitiveTruncatedConeData);

	m_strtPrimitiveTruncatedConeData.dHeight = pstrtPrimitiveTruncatedConeData->dHeight;
	m_strtPrimitiveTruncatedConeData.dBaseRadius = pstrtPrimitiveTruncatedConeData->dBaseRadius;
	m_strtPrimitiveTruncatedConeData.dTopRadius = pstrtPrimitiveTruncatedConeData->dTopRadius;
	m_strtPrimitiveTruncatedConeData.nTess = pstrtPrimitiveTruncatedConeData->nTess;
	m_strtPrimitiveTruncatedConeData.bRenderBothSides = pstrtPrimitiveTruncatedConeData->bRenderBothSides;
	m_strtPrimitiveTruncatedConeData.bUseGouraudShading = pstrtPrimitiveTruncatedConeData->bUseGouraudShading;
}

void CPrimitiveTruncatedCone::GetInertiaTensor(double dIcg[][3]) const
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
	double dX,dY,dZ, dTopRadiusX,dTopRadiusZ;
	// The dTopRadius must be smaller than the dX radius
	if (m_strtPrimitiveTruncatedConeData.dTopRadius > m_strtPrimitiveTruncatedConeData.dBaseRadius)
	{
		dTopRadiusX = dTopRadiusZ = m_strtPrimitiveTruncatedConeData.dBaseRadius;
		dX = dZ = m_strtPrimitiveTruncatedConeData.dTopRadius;
	}
	else
	{
		dTopRadiusX = dTopRadiusZ = m_strtPrimitiveTruncatedConeData.dTopRadius;
		dX = dZ = m_strtPrimitiveTruncatedConeData.dBaseRadius;
	}
	dY = m_strtPrimitiveTruncatedConeData.dHeight;

	// Now scale the axes
	dX *= strtPrimitiveScaleData.dXScale;
	dTopRadiusX *= strtPrimitiveScaleData.dXScale;
	dY *= strtPrimitiveScaleData.dYScale;
	dZ *= strtPrimitiveScaleData.dZScale;
	dTopRadiusZ *= strtPrimitiveScaleData.dZScale;

	// Use the equations for an elliptical cylinder if top and base radius are the same
	if (m_strtPrimitiveTruncatedConeData.dTopRadius == m_strtPrimitiveTruncatedConeData.dBaseRadius)
	{
		dIcg[0][0] = 1.0/4.0 * m_dMass * dZ*dZ + 1.0/12.0 * m_dMass * dY*dY;
		dIcg[1][1] = 1.0/4.0 * m_dMass * (dX*dX + dZ*dZ);
		dIcg[2][2] = 1.0/4.0 * m_dMass * dX*dX + 1.0/12.0 * m_dMass * dY*dY;
		return;
	}

	// Find total height of non-truncated cone
	double dRadiusDifference = dX - dTopRadiusX;
	double dTheta = atan (dY / dRadiusDifference);
	double dTotalHeight = tan (dTheta) * dX;

	// Find height of missing cone
	double dMissingHeight = dTotalHeight - dY;

	// Find the volume of the total elliptical cone
	double dTotalVolume = 1.0/3.0 * PI * dX * dZ * dTotalHeight;

	// Find the volumen of the missing cone from the top
	double dMissingVolume = 1.0/3.0 * PI * dTopRadiusX * dTopRadiusZ * dMissingHeight;

	// Find the density of truncated cone
	double dDensity = m_dMass / (dTotalVolume - dMissingVolume);

	// Find the mass of the total cone using a constant density that is equal
	// to the calculated density in the truncated cone
	double dTotalMass = dDensity * dTotalVolume;

	// Now find inertia of full cone at base (height along y)
	double dIc_bxx = 3.0/20.0*dTotalMass*dZ*dZ + 1.0/10.0*dTotalMass*dTotalHeight*dTotalHeight;
	double dIc_bzz = 3.0/20.0*dTotalMass*dX*dX + 1.0/10.0*dTotalMass*dTotalHeight*dTotalHeight;
	double dIc_byy = 3.0/20.0*dTotalMass*(dX*dX + dZ*dZ);

	// Find the mass of the missing cone
	double dMissingMass = dDensity * dMissingVolume;

	// Find inertia of top cone that is missing from the truncated cone at it COG
	double dIm_cgxx = 3.0/20.0*dMissingMass*dTopRadiusZ*dTopRadiusZ + 1.0/10.0*dMissingMass*dMissingHeight*dMissingHeight;
	double dIm_cgzz = 3.0/20.0*dMissingMass*dTopRadiusX*dTopRadiusX + 1.0/10.0*dMissingMass*dMissingHeight*dMissingHeight;
	double dIm_cgyy = 3.0/20.0*dMissingMass*(dTopRadiusZ*dTopRadiusZ + dTopRadiusX*dTopRadiusX);

	//  Translate the inertia of the missing cone at its COG to the base of the truncated cone
	double dIm_bxx = dIm_cgxx + dMissingMass*dY*dY;
	double dIm_bzz = dIm_cgzz + dMissingMass*dY*dY;
	double dIm_byy = dIm_cgyy;

	// Subtract to find the interia of the truncated cone at its base
	double dIt_bxx = dIc_bxx - dIm_bxx;
	double dIt_bzz = dIc_bzz - dIm_bzz;
	double dIt_byy = dIc_byy - dIm_byy;

	// Find offset to COG
	double dCog = dY * (dX*dX + 2*dX*dTopRadiusX + 3*dTopRadiusX*dTopRadiusX)/
		(4*(dX*dX + dX*dTopRadiusX + dTopRadiusX*dTopRadiusX));

	// Tranlate the inertia to the cg
	dIcg[0][0] = dIt_bxx - m_dMass*dCog*dCog;
	dIcg[1][1] = dIt_byy;
	dIcg[2][2] = dIt_bzz - m_dMass*dCog*dCog;

}

void CPrimitiveTruncatedCone::GetCenterOfGravity(double dPos[]) const
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
	wtp3_pPcog[1] = m_strtPrimitiveTruncatedConeData.dHeight / 2.0 * strtPrimitiveScaleData.dYScale; 
	// Move to cog from base
	double dTopDiameter = m_strtPrimitiveTruncatedConeData.dTopRadius * 2;
	double dBottomDiameter = m_strtPrimitiveTruncatedConeData.dBaseRadius * 2;
	wtp3_pPcog[1] -= m_strtPrimitiveTruncatedConeData.dHeight 
		* (dBottomDiameter * dBottomDiameter + 2 * dBottomDiameter * dTopDiameter +
		3 * dTopDiameter * dTopDiameter) / (4.0 * (dBottomDiameter * dBottomDiameter + 
		dBottomDiameter * dTopDiameter + dTopDiameter * dTopDiameter))
		* strtPrimitiveScaleData.dYScale;

	// Rotate the cog in primitive coords to be in terms of the link coords
	WTp3 wtp3_lPcog; // position of the cog in link coords
	WTp3_multm3 (wtp3_pPcog, wtm3_pRl, wtp3_lPcog);

	// Sum the position of the link with the cog offset
	dPos[0] = strtPrimitivePlacementData.dTranslationX + wtp3_lPcog[0];
	dPos[1] = strtPrimitivePlacementData.dTranslationY + wtp3_lPcog[1];
	dPos[2] = strtPrimitivePlacementData.dTranslationZ + wtp3_lPcog[2];
}


