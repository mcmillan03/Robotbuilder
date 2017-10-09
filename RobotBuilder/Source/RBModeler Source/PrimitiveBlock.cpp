// PrimitiveBlock.cpp: implementation of the CPrimitiveBlock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "PrimitiveBlock.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrimitiveBlock::CPrimitiveBlock()
{
	m_strtPrimitiveBlockData.dLengthX = 1;
	m_strtPrimitiveBlockData.dLengthY = 1;
	m_strtPrimitiveBlockData.dLengthZ = 1;
	m_strtPrimitiveBlockData.bRenderBothSides = FALSE;
	m_strName = "Block";
}

CPrimitiveBlock::~CPrimitiveBlock()
{

}

void CPrimitiveBlock::GetPrimitiveBlockData(structPrimitiveBlockData *pstrtPrimitiveBlockData) const
{
	ASSERT (pstrtPrimitiveBlockData);

	pstrtPrimitiveBlockData->dLengthX = m_strtPrimitiveBlockData.dLengthX;
	pstrtPrimitiveBlockData->dLengthY = m_strtPrimitiveBlockData.dLengthY;
	pstrtPrimitiveBlockData->dLengthZ = m_strtPrimitiveBlockData.dLengthZ;
	pstrtPrimitiveBlockData->bRenderBothSides = m_strtPrimitiveBlockData.bRenderBothSides;
}

void CPrimitiveBlock::SetPrimitiveBlockData(const structPrimitiveBlockData *pstrtPrimitiveBlockData)
{
	ASSERT (pstrtPrimitiveBlockData);

	m_strtPrimitiveBlockData.dLengthX = pstrtPrimitiveBlockData->dLengthX;
	m_strtPrimitiveBlockData.dLengthY = pstrtPrimitiveBlockData->dLengthY;
	m_strtPrimitiveBlockData.dLengthZ = pstrtPrimitiveBlockData->dLengthZ;
	m_strtPrimitiveBlockData.bRenderBothSides = pstrtPrimitiveBlockData->bRenderBothSides;
}

void CPrimitiveBlock::GetInertiaTensor(double dIcg[][3]) const
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
	dX = m_strtPrimitiveBlockData.dLengthX * strtPrimitiveScaleData.dXScale;
	dY = m_strtPrimitiveBlockData.dLengthY * strtPrimitiveScaleData.dYScale;
	dZ = m_strtPrimitiveBlockData.dLengthZ * strtPrimitiveScaleData.dZScale;

	// Use the formulas to find the values
	dIcg[0][0] = m_dMass * (dZ*dZ + dY*dY) / 12.0;
	dIcg[1][1] = m_dMass * (dZ*dZ + dX*dX) / 12.0;
	dIcg[2][2] = m_dMass * (dX*dX + dY*dY) / 12.0;
}

void CPrimitiveBlock::GetCenterOfGravity(double dPos[]) const
{
	structPrimitivePlacementData strtPrimitivePlacementData;
	m_PrimitivePlacement.GetPrimitivePlacementData (&strtPrimitivePlacementData);

	dPos[0] = strtPrimitivePlacementData.dTranslationX;
	dPos[1] = strtPrimitivePlacementData.dTranslationY;
	dPos[2] = strtPrimitivePlacementData.dTranslationZ;

}

