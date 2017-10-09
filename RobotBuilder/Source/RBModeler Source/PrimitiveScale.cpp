// PrimitiveScale.cpp: implementation of the CPrimitiveScale class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "PrimitiveScale.h"
#include "DlgMovementControls.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrimitiveScale::CPrimitiveScale()
{
	m_strtPrimitiveScaleRelativeData.dXScale = 1;
	m_strtPrimitiveScaleRelativeData.dYScale = 1;
	m_strtPrimitiveScaleRelativeData.dZScale = 1;

	m_strtPrimitiveScaleAbsoluteData.dXScale = 1;
	m_strtPrimitiveScaleAbsoluteData.dYScale = 1;
	m_strtPrimitiveScaleAbsoluteData.dZScale = 1;
}

CPrimitiveScale::~CPrimitiveScale()
{

}

// This function should be called to 'zero' out the relative scale data after that
// data has been applied to the current geometry
void CPrimitiveScale::ResetRelativeScaleData()
{
	m_strtPrimitiveScaleRelativeData.dXScale = 1;
	m_strtPrimitiveScaleRelativeData.dYScale = 1;
	m_strtPrimitiveScaleRelativeData.dZScale = 1;
}


void CPrimitiveScale::GetPrimitiveScaleAbsoluteData(structPrimitiveScaleData *pstrtPrimitiveScaleAbsoluteData) const
{
	ASSERT (pstrtPrimitiveScaleAbsoluteData);

	pstrtPrimitiveScaleAbsoluteData->dXScale = m_strtPrimitiveScaleAbsoluteData.dXScale;
	pstrtPrimitiveScaleAbsoluteData->dYScale = m_strtPrimitiveScaleAbsoluteData.dYScale;
	pstrtPrimitiveScaleAbsoluteData->dZScale = m_strtPrimitiveScaleAbsoluteData.dZScale;
}

void CPrimitiveScale::AlterScale(double dScaleFactor, UINT uAxis)
{
	// Build the vector of factors in each direction
	double dScaleFactorVector[3] = {1, 1, 1};
	switch (uAxis)
	{
	case AXIS_X:
		dScaleFactorVector[0] = dScaleFactor;
		break;
	case AXIS_Y:
		dScaleFactorVector[1] = dScaleFactor;
		break;
	case AXIS_Z:
		dScaleFactorVector[2] = dScaleFactor;
		break;
	default:
		ASSERT (FALSE);
	}

	
	// First store in the data structure for the relative change to the current state
	// of the geometry

	// At this point it is assumed the relative data will be reset by the drawing logic
	// before this is called.  It could be implemeneted not to and the factors just be
	// be multiplied, but I am not expecting that now.
	ASSERT ((int) (m_strtPrimitiveScaleRelativeData.dXScale + .5) ==
			(int) (m_strtPrimitiveScaleRelativeData.dYScale + .5) ==
			(int) (m_strtPrimitiveScaleRelativeData.dZScale + .5) == 1);
	// Also assume that we don't want a scale factor of 0
	ASSERT (dScaleFactor != 0);

	m_strtPrimitiveScaleRelativeData.dXScale = dScaleFactorVector[0];
	m_strtPrimitiveScaleRelativeData.dYScale = dScaleFactorVector[1];
	m_strtPrimitiveScaleRelativeData.dZScale = dScaleFactorVector[2];


	// Also need to save the absolute scale of the geometry.  The passed value scales the
	// geometry relative to the current state, so need to multiply the scale factor
	m_strtPrimitiveScaleAbsoluteData.dXScale *= dScaleFactorVector[0];
	m_strtPrimitiveScaleAbsoluteData.dYScale *= dScaleFactorVector[1];
	m_strtPrimitiveScaleAbsoluteData.dZScale *= dScaleFactorVector[2];

}

// This saves the new absolute as well as calculating the relative scale that needs to be
// applied to the graphic
void CPrimitiveScale::SetPrimitiveScaleAbsoluteData(const structPrimitiveScaleData *pstrtPrimitiveScaleData)
{
	ASSERT (pstrtPrimitiveScaleData);
	
	// Scale values can't be zero
	ASSERT (pstrtPrimitiveScaleData->dXScale != 0 &&
		pstrtPrimitiveScaleData->dYScale != 0 &&
		pstrtPrimitiveScaleData->dZScale != 0);

	// At this point, I am assuming there aren't any pending relative changes.  (This can
	// this can be added in the future by multiplying the new by the current relative 
	// scale)
	ASSERT ((int) (m_strtPrimitiveScaleRelativeData.dXScale + .5) == 
		(int) (m_strtPrimitiveScaleRelativeData.dYScale + .5) ==
		(int) (m_strtPrimitiveScaleRelativeData.dZScale + .5) == 1);

	// Calculate the relative changes that need to be made to the current graphic
	m_strtPrimitiveScaleRelativeData.dXScale = pstrtPrimitiveScaleData->dXScale / 
		m_strtPrimitiveScaleAbsoluteData.dXScale;
	m_strtPrimitiveScaleRelativeData.dYScale = pstrtPrimitiveScaleData->dYScale / 
		m_strtPrimitiveScaleAbsoluteData.dYScale;
	m_strtPrimitiveScaleRelativeData.dZScale = pstrtPrimitiveScaleData->dZScale / 
		m_strtPrimitiveScaleAbsoluteData.dZScale;

	// Now save the new absolue data
	m_strtPrimitiveScaleAbsoluteData.dXScale = pstrtPrimitiveScaleData->dXScale;
	m_strtPrimitiveScaleAbsoluteData.dYScale = pstrtPrimitiveScaleData->dYScale;
	m_strtPrimitiveScaleAbsoluteData.dZScale = pstrtPrimitiveScaleData->dZScale;

}


void CPrimitiveScale::GetPrimitiveScaleRelativeData(structPrimitiveScaleData *pstrtPrimitiveScaleRelativeData) const
{
	ASSERT (pstrtPrimitiveScaleRelativeData);

	pstrtPrimitiveScaleRelativeData->dXScale = m_strtPrimitiveScaleRelativeData.dXScale;
	pstrtPrimitiveScaleRelativeData->dYScale = m_strtPrimitiveScaleRelativeData.dYScale;
	pstrtPrimitiveScaleRelativeData->dZScale = m_strtPrimitiveScaleRelativeData.dZScale;

}
