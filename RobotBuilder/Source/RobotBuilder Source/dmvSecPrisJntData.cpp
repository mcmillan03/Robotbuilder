// dmvSecPrisJntData.cpp: implementation of the CdmvSecPrisJntData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvSecPrisJntData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvSecPrisJntData::CdmvSecPrisJntData()
{
	m_SecondaryJointType = SEC_PRISMATIC;

	m_strtSecondaryPrismaticJointData.dAngularConstraintDamper = 0;
	m_strtSecondaryPrismaticJointData.dAngularConstraintSpring = 0;
	m_strtSecondaryPrismaticJointData.dLinearConstraintDamper = 0;
	m_strtSecondaryPrismaticJointData.dLinearConstraintSpring = 0;

	// Set the default name
	m_strName = "Secondary Prismatic Joint";
}

CdmvSecPrisJntData::~CdmvSecPrisJntData()
{

}

void CdmvSecPrisJntData::SetConstraintParams(double dLinearConstraintSpring, double dLinearConstraintDamper, double dAngularConstraintSpring, double dAngularConstraintDamper)
{
	m_strtSecondaryPrismaticJointData.dAngularConstraintDamper = dAngularConstraintDamper;
	m_strtSecondaryPrismaticJointData.dAngularConstraintSpring = dAngularConstraintSpring;
	m_strtSecondaryPrismaticJointData.dLinearConstraintDamper = dLinearConstraintDamper;
	m_strtSecondaryPrismaticJointData.dLinearConstraintSpring = dLinearConstraintSpring;
}

void CdmvSecPrisJntData::GetSecPrismaticJointData(structSecondaryPrismaticJointData *pstrtSecondaryPrismaticJointData) const
{
	ASSERT (pstrtSecondaryPrismaticJointData);
		
	pstrtSecondaryPrismaticJointData->dAngularConstraintDamper = m_strtSecondaryPrismaticJointData.dAngularConstraintDamper;
	pstrtSecondaryPrismaticJointData->dAngularConstraintSpring = m_strtSecondaryPrismaticJointData.dAngularConstraintSpring;
	pstrtSecondaryPrismaticJointData->dLinearConstraintDamper = m_strtSecondaryPrismaticJointData.dLinearConstraintDamper;
	pstrtSecondaryPrismaticJointData->dLinearConstraintSpring = m_strtSecondaryPrismaticJointData.dLinearConstraintSpring;

}

void CdmvSecPrisJntData::SetSecPrismaticJointData(const structSecondaryPrismaticJointData *pstrtSecondaryPrismaticJointData)
{
	ASSERT (pstrtSecondaryPrismaticJointData);
	
	m_strtSecondaryPrismaticJointData.dAngularConstraintDamper = pstrtSecondaryPrismaticJointData->dAngularConstraintDamper;
	m_strtSecondaryPrismaticJointData.dAngularConstraintSpring = pstrtSecondaryPrismaticJointData->dAngularConstraintSpring;
	m_strtSecondaryPrismaticJointData.dLinearConstraintDamper = pstrtSecondaryPrismaticJointData->dLinearConstraintDamper;
	m_strtSecondaryPrismaticJointData.dLinearConstraintSpring = pstrtSecondaryPrismaticJointData->dLinearConstraintSpring;

}
