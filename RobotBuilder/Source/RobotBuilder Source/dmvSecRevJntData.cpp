// dmvSecRevJntData.cpp: implementation of the CdmvSecRevJntData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvSecRevJntData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvSecRevJntData::CdmvSecRevJntData()
{
	m_SecondaryJointType = SEC_REVOLUTE;

	m_strtSecondaryRevoluteJointData.dAngularConstraintDamper = 0;
	m_strtSecondaryRevoluteJointData.dAngularConstraintSpring = 0;
	m_strtSecondaryRevoluteJointData.dLinearConstraintDamper = 0;
	m_strtSecondaryRevoluteJointData.dLinearConstraintSpring = 0;

	// Set the default name
	m_strName = "Secondary Revolute Joint";

}

CdmvSecRevJntData::~CdmvSecRevJntData()
{

}

void CdmvSecRevJntData::SetConstraintParams(double dLinearConstraintSpring, double dLinearConstraintDamper, double dAngularConstraintSpring, double dAngularConstraintDamper)
{
	m_strtSecondaryRevoluteJointData.dAngularConstraintDamper = dAngularConstraintDamper;
	m_strtSecondaryRevoluteJointData.dAngularConstraintSpring = dAngularConstraintSpring;
	m_strtSecondaryRevoluteJointData.dLinearConstraintDamper = dLinearConstraintDamper;
	m_strtSecondaryRevoluteJointData.dLinearConstraintSpring = dLinearConstraintSpring;
}

void CdmvSecRevJntData::GetSecRevoluteJointData(structSecondaryRevoluteJointData *pstrtSecondaryRevoluteJointData) const
{
	ASSERT (pstrtSecondaryRevoluteJointData);
		
	pstrtSecondaryRevoluteJointData->dAngularConstraintDamper = m_strtSecondaryRevoluteJointData.dAngularConstraintDamper;
	pstrtSecondaryRevoluteJointData->dAngularConstraintSpring = m_strtSecondaryRevoluteJointData.dAngularConstraintSpring;
	pstrtSecondaryRevoluteJointData->dLinearConstraintDamper = m_strtSecondaryRevoluteJointData.dLinearConstraintDamper;
	pstrtSecondaryRevoluteJointData->dLinearConstraintSpring = m_strtSecondaryRevoluteJointData.dLinearConstraintSpring;

}

void CdmvSecRevJntData::SetSecRevoluteJointData(const structSecondaryRevoluteJointData *pstrtSecondaryRevoluteJointData)
{
	ASSERT (pstrtSecondaryRevoluteJointData);
	
	m_strtSecondaryRevoluteJointData.dAngularConstraintDamper = pstrtSecondaryRevoluteJointData->dAngularConstraintDamper;
	m_strtSecondaryRevoluteJointData.dAngularConstraintSpring = pstrtSecondaryRevoluteJointData->dAngularConstraintSpring;
	m_strtSecondaryRevoluteJointData.dLinearConstraintDamper = pstrtSecondaryRevoluteJointData->dLinearConstraintDamper;
	m_strtSecondaryRevoluteJointData.dLinearConstraintSpring = pstrtSecondaryRevoluteJointData->dLinearConstraintSpring;
}
