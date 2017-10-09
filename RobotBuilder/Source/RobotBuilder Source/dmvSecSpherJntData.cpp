// dmvSecSpherJntData.cpp: implementation of the CdmvSecSpherJntData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvSecSpherJntData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvSecSpherJntData::CdmvSecSpherJntData()
{
	m_SecondaryJointType = SEC_SPHERICAL;

	m_strtSecondarySphericalJointData.dLinearConstraintDamper = 0;
	m_strtSecondarySphericalJointData.dLinearConstraintSpring = 0;

	// Set the default name
	m_strName = "Secondary Spherical Joint";

}

CdmvSecSpherJntData::~CdmvSecSpherJntData()
{

}

void CdmvSecSpherJntData::SetConstraintParams(double dLinearConstraintSpring, double dLinearConstraintDamper)
{
	m_strtSecondarySphericalJointData.dLinearConstraintDamper = dLinearConstraintDamper;
	m_strtSecondarySphericalJointData.dLinearConstraintSpring = dLinearConstraintSpring;

}

void CdmvSecSpherJntData::GetSecSphericalJointData(structSecondarySphericalJointData *pstrtSecondarySphericalJointData) const
{
	ASSERT (pstrtSecondarySphericalJointData);

	pstrtSecondarySphericalJointData->dLinearConstraintDamper = m_strtSecondarySphericalJointData.dLinearConstraintDamper;
	pstrtSecondarySphericalJointData->dLinearConstraintSpring = m_strtSecondarySphericalJointData.dLinearConstraintSpring;
}

void CdmvSecSpherJntData::SetSecSphericalJointData(const structSecondarySphericalJointData *pstrtSecondarySphericalJointData)
{
	ASSERT (pstrtSecondarySphericalJointData);

	m_strtSecondarySphericalJointData.dLinearConstraintDamper = pstrtSecondarySphericalJointData->dLinearConstraintDamper;
	m_strtSecondarySphericalJointData.dLinearConstraintSpring = pstrtSecondarySphericalJointData->dLinearConstraintSpring;
}
