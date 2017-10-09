// dmvSphericalLinkData.cpp: implementation of the CdmvSphericalLinkData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvSphericalLinkData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CdmvSphericalLinkData::CdmvSphericalLinkData()
{
	// init members
	m_cvJointOffsetPosition[0] = 0;
	m_cvJointOffsetPosition[1] = 0;
	m_cvJointOffsetPosition[2] = 0;

	m_strtSphericalLinkState.eaAngles[0] = 0;
	m_strtSphericalLinkState.eaAngles[1] = 0;
	m_strtSphericalLinkState.eaAngles[2] = 0;
	int nCounter; // counter for 'for' loop
	for (nCounter = 0; nCounter < NUM_DOFS; nCounter++)
		m_strtSphericalLinkState.fAngularVelocity[nCounter] = 0;

	for (nCounter = 0; nCounter < NUM_DOFS; nCounter++)
		m_strtSphericalLinkJointLimits.fJointLimits[nCounter] = 0;
	m_strtSphericalLinkJointLimits.fSpring = 0;
	m_strtSphericalLinkJointLimits.fDamper = 0;

	// set the link type
	m_LinkType = SPHERICAL_LINK;

	// Set the default name
	m_strName = "Spherical Link";
}

CdmvSphericalLinkData::~CdmvSphericalLinkData()
{

}

void CdmvSphericalLinkData::SetJointOffset(CartesianVector cvPosition)
{
	m_cvJointOffsetPosition[0] = cvPosition[0];
	m_cvJointOffsetPosition[1] = cvPosition[1];
	m_cvJointOffsetPosition[2] = cvPosition[2];
}

void CdmvSphericalLinkData::SetInitialState(EulerAngles eaAngles, double dAngularVelocity[])
{
	m_strtSphericalLinkState.eaAngles[0] = eaAngles[0];
	m_strtSphericalLinkState.eaAngles[1] = eaAngles[1];
	m_strtSphericalLinkState.eaAngles[2] = eaAngles[2];	
	
	int nCounter; // counter for 'for' loop
	// note that it is imperative that if DynaMechs changes its definition of NUM_DOFS,
	// then the value in this class must be updated too.
	for (nCounter = 0; nCounter < NUM_DOFS; nCounter++)
		m_strtSphericalLinkState.fAngularVelocity[nCounter] = dAngularVelocity[nCounter];
}

void CdmvSphericalLinkData::SetJointLimits(double dJointLimits[], double dSpring, double dDamper)
{
	int nCounter; // counter for 'for' loop
	for (nCounter = 0; nCounter < NUM_DOFS; nCounter++)
		m_strtSphericalLinkJointLimits.fJointLimits[nCounter] = dJointLimits[nCounter];
	m_strtSphericalLinkJointLimits.fSpring = dSpring;
	m_strtSphericalLinkJointLimits.fDamper = dDamper;
}

void CdmvSphericalLinkData::GetJointOffset(CartesianVector cvPosition) const
{
	cvPosition[0] = m_cvJointOffsetPosition[0];
	cvPosition[1] = m_cvJointOffsetPosition[1];
	cvPosition[2] = m_cvJointOffsetPosition[2];
}

void CdmvSphericalLinkData::GetJointLimits(structSphericalLinkJointLimits *pstrtSphericalLinkJointLimits) const
{
	pstrtSphericalLinkJointLimits->fDamper = m_strtSphericalLinkJointLimits.fDamper;
	pstrtSphericalLinkJointLimits->fSpring = m_strtSphericalLinkJointLimits.fSpring;
	pstrtSphericalLinkJointLimits->fJointLimits[0] = m_strtSphericalLinkJointLimits.fJointLimits[0];
	pstrtSphericalLinkJointLimits->fJointLimits[1] = m_strtSphericalLinkJointLimits.fJointLimits[1];
	pstrtSphericalLinkJointLimits->fJointLimits[2] = m_strtSphericalLinkJointLimits.fJointLimits[2];
}

void CdmvSphericalLinkData::SetJointLimits(const structSphericalLinkJointLimits *pstrtSphericalLinkJointLimits)
{
	m_strtSphericalLinkJointLimits.fDamper = pstrtSphericalLinkJointLimits->fDamper;
	m_strtSphericalLinkJointLimits.fSpring = pstrtSphericalLinkJointLimits->fSpring;
	m_strtSphericalLinkJointLimits.fJointLimits[0] = pstrtSphericalLinkJointLimits->fJointLimits[0];
	m_strtSphericalLinkJointLimits.fJointLimits[1] = pstrtSphericalLinkJointLimits->fJointLimits[1];
	m_strtSphericalLinkJointLimits.fJointLimits[2] = pstrtSphericalLinkJointLimits->fJointLimits[2];
}

void CdmvSphericalLinkData::GetLinkState(structSphericalLinkState *pstrtSphericalLinkState) const
{
	pstrtSphericalLinkState->eaAngles[0] = m_strtSphericalLinkState.eaAngles[0];
	pstrtSphericalLinkState->eaAngles[1] = m_strtSphericalLinkState.eaAngles[1];
	pstrtSphericalLinkState->eaAngles[2] = m_strtSphericalLinkState.eaAngles[2];

	pstrtSphericalLinkState->fAngularVelocity[0] = m_strtSphericalLinkState.fAngularVelocity[0];
	pstrtSphericalLinkState->fAngularVelocity[1] = m_strtSphericalLinkState.fAngularVelocity[1];
	pstrtSphericalLinkState->fAngularVelocity[2] = m_strtSphericalLinkState.fAngularVelocity[2];
}

void CdmvSphericalLinkData::SetLinkState(const structSphericalLinkState *pstrtSphericalLinkState)
{
	m_strtSphericalLinkState.eaAngles[0] = pstrtSphericalLinkState->eaAngles[0];
	m_strtSphericalLinkState.eaAngles[1] = pstrtSphericalLinkState->eaAngles[1];
	m_strtSphericalLinkState.eaAngles[2] = pstrtSphericalLinkState->eaAngles[2];

	m_strtSphericalLinkState.fAngularVelocity[0] = pstrtSphericalLinkState->fAngularVelocity[0];
	m_strtSphericalLinkState.fAngularVelocity[1] = pstrtSphericalLinkState->fAngularVelocity[1];
	m_strtSphericalLinkState.fAngularVelocity[2] = pstrtSphericalLinkState->fAngularVelocity[2];

}
