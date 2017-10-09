// PrimitiveSphere.cpp: implementation of the CPrimitiveSphere class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "PrimitiveSphere.h"
#include "RBMath.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrimitiveSphere::CPrimitiveSphere()
{
	m_strtPrimitiveSphereData.dRadius = 1;
	m_strtPrimitiveSphereData.nLatitudeCount = 10;
	m_strtPrimitiveSphereData.nLongitudeCount = 10;
	m_strtPrimitiveSphereData.bRenderBothSides = FALSE;
	m_strtPrimitiveSphereData.bUseGouraudShading = TRUE;
	m_strName = "Sphere";
}

CPrimitiveSphere::~CPrimitiveSphere()
{

}

void CPrimitiveSphere::SetPrimitiveSphereData(const structPrimitiveSphereData *pstrtPrimitiveSphereData)
{
	m_strtPrimitiveSphereData.dRadius = pstrtPrimitiveSphereData->dRadius;
	m_strtPrimitiveSphereData.nLatitudeCount = pstrtPrimitiveSphereData->nLatitudeCount;
	m_strtPrimitiveSphereData.nLongitudeCount = pstrtPrimitiveSphereData->nLongitudeCount;
	m_strtPrimitiveSphereData.bRenderBothSides = pstrtPrimitiveSphereData->bRenderBothSides;
	m_strtPrimitiveSphereData.bUseGouraudShading = pstrtPrimitiveSphereData->bUseGouraudShading;
}

void CPrimitiveSphere::GetPrimitiveSphereData(structPrimitiveSphereData *pstrtPrimitiveSphereData) const
{
	pstrtPrimitiveSphereData->dRadius = m_strtPrimitiveSphereData.dRadius;
	pstrtPrimitiveSphereData->nLatitudeCount = m_strtPrimitiveSphereData.nLatitudeCount;
	pstrtPrimitiveSphereData->nLongitudeCount = m_strtPrimitiveSphereData.nLongitudeCount;
	pstrtPrimitiveSphereData->bRenderBothSides = m_strtPrimitiveSphereData.bRenderBothSides;
	pstrtPrimitiveSphereData->bUseGouraudShading = m_strtPrimitiveSphereData.bUseGouraudShading;
}

void CPrimitiveSphere::GetCenterOfGravity(double dPos[]) const
{
	// For sphere this is the location of the local coordinate system
	structPrimitivePlacementData strtPrimitivePlacementData;
	m_PrimitivePlacement.GetPrimitivePlacementData (&strtPrimitivePlacementData);

	dPos[0] = strtPrimitivePlacementData.dTranslationX;
	dPos[1] = strtPrimitivePlacementData.dTranslationY;
	dPos[2] = strtPrimitivePlacementData.dTranslationZ;
}

void CPrimitiveSphere::GetInertiaTensor(double dIcg[][3]) const
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
	dX = dY = dZ = m_strtPrimitiveSphereData.dRadius;

	// Now scale the axes
	dX *= strtPrimitiveScaleData.dXScale;
	dY *= strtPrimitiveScaleData.dYScale;
	dZ *= strtPrimitiveScaleData.dZScale;

	// Calculate
	dIcg[0][0] = m_dMass * (dY*dY+dZ*dZ) / 5.0;
	dIcg[1][1] = m_dMass * (dX*dX+dZ*dZ) / 5.0;
	dIcg[2][2] = m_dMass * (dX*dX+dY*dY) / 5.0;
}


