// Primitive.cpp: implementation of the CPrimitive class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Primitive.h"
#include "RBMath.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrimitive::CPrimitive()
{
	m_strName = "";
	m_dMass = 1;
	m_bCameraCenterOfInterest = FALSE;
	m_bShowWtkAxes = FALSE;
}

CPrimitive::~CPrimitive()
{

}

CString CPrimitive::GetName()
{
	return m_strName;
}

void CPrimitive::SetName(CString strName)
{
	m_strName = strName;
}

CPrimitiveCovering* CPrimitive::GetPrimitiveCovering()
{
	return &m_PrimitiveCovering;
}

CPrimitivePlacement* CPrimitive::GetPrimitivePlacement()
{
	return &m_PrimitivePlacement;
}

CPrimitiveScale* CPrimitive::GetPrimitiveScale()
{
	return &m_PrimitiveScale;
}

double CPrimitive::GetMass() const
{
	return m_dMass;
}

void CPrimitive::SetMass(double dMass)
{
	ASSERT (dMass >= 0);

	m_dMass = dMass;
}

void CPrimitive::GetTransformedInertiaTensor (double dIbar[3][3])
{
	// iRcg*Icg*cgRi + m(s^T*s*I-s*s^T)
	
	// First get local inertia tensor
	double dIcg[3][3];
	GetInertiaTensor (dIcg);

	// Transform it
	structPrimitivePlacementData strtPrimitivePlacementData;
	m_PrimitivePlacement.GetPrimitivePlacementData (&strtPrimitivePlacementData);

	// Transpose the rotation
	double dRotationTransposed[3][3];
	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			dRotationTransposed[i][j] = strtPrimitivePlacementData.dRotationMatrix[j][i];
	
	double dIntermediateProduct[3][3];
	// Recall that the rotation matrices in RM are transposes of craig notation, 
	// so need to transpose beforing using them
	CRBMath::Multiply3by3DoubleMatrices (dRotationTransposed,dIcg,dIntermediateProduct);
	CRBMath::Multiply3by3DoubleMatrices (dIntermediateProduct,strtPrimitivePlacementData.dRotationMatrix,dIbar);

	// 3D parallel axis
	// todo: make a generalize math lib
	// s*s^T
	// First put the position in an array
	double dS[3];
	GetCenterOfGravity (dS);
	double dSMatrix[3][3];
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			dSMatrix[i][j] = -1*dS[i]*dS[j];

	// Get S inner product
	double dInnerProduct = 0;
	for (i=0;i<3;i++)
		dInnerProduct += dS[i] * dS[i];

	// Add the inner product to the diag
	for (i=0;i<3;i++)
		dSMatrix[i][i] =+ dInnerProduct;

	// Scale by the mass
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			dSMatrix[i][j] *= m_dMass;

	// Add to the transformed Icg
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			dIbar[i][j] += dSMatrix[i][j];
}

void CPrimitive::ShowWtkAxes(BOOL bShow)
{
	m_bShowWtkAxes = bShow;
}

BOOL CPrimitive::ShowWtkAxes() const
{
	return m_bShowWtkAxes;
}

BOOL CPrimitive::IsCameraCenterOfInterest() const
{
	return m_bCameraCenterOfInterest;
}

void CPrimitive::IsCameraCenterOfInterest(BOOL bIsCOI)
{
	m_bCameraCenterOfInterest = bIsCOI;
}