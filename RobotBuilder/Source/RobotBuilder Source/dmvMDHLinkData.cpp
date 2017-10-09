// dmvMDHLinkData.cpp: implementation of the CdmvMDHLinkData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvMDHLinkData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvMDHLinkData::CdmvMDHLinkData()
{
	// init members
	m_strtMDHParameters.fa = 0;
	m_strtMDHParameters.fAlpha = 0;
	m_strtMDHParameters.fd = 0;
	m_strtMDHParameters.fTheta = 0;

	m_strtMDHLinkJointLimits.fMin = 0;
	m_strtMDHLinkJointLimits.fMax = 0;
	m_strtMDHLinkJointLimits.fSpring = 0;
	m_strtMDHLinkJointLimits.fDamper = 0;

	m_strtMDHLinkState.fq = 0;
	m_strtMDHLinkState.fqd = 0;
}

CdmvMDHLinkData::~CdmvMDHLinkData()
{

}
/*
void CdmvMDHLinkData::setState(Float *q, Float *qd)
{
	m_strtMDHLinkState.fq = *q;
	m_strtMDHLinkState.fqd = *qd;
}

void CdmvMDHLinkData::getState(Float *q, Float *qd)
{
	*q = m_strtMDHLinkState.fq;
	*qd = m_strtMDHLinkState.fqd;
}
*/
void CdmvMDHLinkData::SetJointLimits(Float fMin, Float fMax, Float fSpring, Float fDamper)
{
	// just store the info
	m_strtMDHLinkJointLimits.fMin = fMin;
	m_strtMDHLinkJointLimits.fMax = fMax;
	m_strtMDHLinkJointLimits.fSpring = fSpring;
	m_strtMDHLinkJointLimits.fDamper = fDamper;
}

void CdmvMDHLinkData::SetMDHParameters(Float fa, Float fAlpha, Float fd, Float fTheta)
{
	// just store the info
	m_strtMDHParameters.fa = fa;
	m_strtMDHParameters.fAlpha = fAlpha;
	m_strtMDHParameters.fd = fd;
	m_strtMDHParameters.fTheta = fTheta;

	// this data will be set in the wtk wnd when the link is added
}

void CdmvMDHLinkData::GetLinkParameters(Float *pfParameters) const
{
	
	*(pfParameters + 0) = m_strtMDHParameters.fa;
	*(pfParameters + 1) = m_strtMDHParameters.fAlpha;
	*(pfParameters + 2) = m_strtMDHParameters.fd;
	*(pfParameters + 3) = m_strtMDHParameters.fTheta;

}

void CdmvMDHLinkData::SetJointLimits(const structMDHLinkJointLimits *pstrtMDHLinkJointLimits)
{
	m_strtMDHLinkJointLimits.fDamper  = pstrtMDHLinkJointLimits->fDamper;
	m_strtMDHLinkJointLimits.fMax  = pstrtMDHLinkJointLimits->fMax;
	m_strtMDHLinkJointLimits.fMin  = pstrtMDHLinkJointLimits->fMin;
	m_strtMDHLinkJointLimits.fSpring  = pstrtMDHLinkJointLimits->fSpring;
}

void CdmvMDHLinkData::GetJointLimits(structMDHLinkJointLimits *pstrtMDHLinkJointLimits) const
{
	pstrtMDHLinkJointLimits->fDamper = m_strtMDHLinkJointLimits.fDamper;
	pstrtMDHLinkJointLimits->fMax = m_strtMDHLinkJointLimits.fMax;
	pstrtMDHLinkJointLimits->fMin = m_strtMDHLinkJointLimits.fMin;
	pstrtMDHLinkJointLimits->fSpring = m_strtMDHLinkJointLimits.fSpring;

}


//void CdmvMDHLinkData::GetLinkState(structMDHLinkState *pstrtMDHLinkState) const
//{
//	pstrtMDHLinkState->fq = m_strtMDHLinkState.fq;
//	pstrtMDHLinkState->fqd = m_strtMDHLinkState.fqd;
//}

//void CdmvMDHLinkData::SetLinkState(const structMDHLinkState *pstrtMDHLinkState)
//{
//	m_strtMDHLinkState.fq = pstrtMDHLinkState->fq;
//	m_strtMDHLinkState.fqd = pstrtMDHLinkState->fqd;
//}

void CdmvMDHLinkData::GetMDHParameters(structMDHParameters *pstrtMDHParameters) const
{
	pstrtMDHParameters->fa = m_strtMDHParameters.fa;
	pstrtMDHParameters->fAlpha = m_strtMDHParameters.fAlpha;
	pstrtMDHParameters->fd = m_strtMDHParameters.fd;
	pstrtMDHParameters->fTheta = m_strtMDHParameters.fTheta;
}

void CdmvMDHLinkData::SetMDHParameters(const structMDHParameters *pstrtMDHParameters)
{
	m_strtMDHParameters.fa = pstrtMDHParameters->fa;
	m_strtMDHParameters.fAlpha = pstrtMDHParameters->fAlpha;
	m_strtMDHParameters.fd = pstrtMDHParameters->fd;
	m_strtMDHParameters.fTheta = pstrtMDHParameters->fTheta;	
}

Float CdmvMDHLinkData::GetInitialJointVelocity() const
{
	return m_strtMDHLinkState.fqd;
}

void CdmvMDHLinkData::SetInitialJointVelocity(Float fInitialJointVelocity)
{
	m_strtMDHLinkState.fqd = fInitialJointVelocity;
}
