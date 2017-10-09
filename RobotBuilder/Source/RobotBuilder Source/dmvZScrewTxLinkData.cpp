// dmvZScrewTxLinkData.cpp: implementation of the CdmvZScrewTxLinkData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvZScrewTxLinkData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvZScrewTxLinkData::CdmvZScrewTxLinkData()
{
	// init members
	m_strtZScrewTxLinkParameters.fD = 0;
	m_strtZScrewTxLinkParameters.fTheta = 0;

	// set the link type
	m_LinkType = ZSCREW_TX_LINK;

	// Set the default name
	m_strName = "ZScrew Transform";
}

CdmvZScrewTxLinkData::~CdmvZScrewTxLinkData()
{
}

CdmvZScrewTxLinkData::CdmvZScrewTxLinkData(Float fD, Float fTheta)
{
	// init members
	m_strtZScrewTxLinkParameters.fD = fD;
	m_strtZScrewTxLinkParameters.fTheta = fTheta;

	// set the link type
	m_LinkType = ZSCREW_TX_LINK;
}

BOOL CdmvZScrewTxLinkData::GetLinkParameters(Float *pfMDHParameters)
{
	// return the parameters
	// the MDH parameters will be a, alpha, d, theta

	*(pfMDHParameters + 0) = 0;
	*(pfMDHParameters + 1) = 0;
	*(pfMDHParameters + 2) = m_strtZScrewTxLinkParameters.fD;
	*(pfMDHParameters + 3) = m_strtZScrewTxLinkParameters.fTheta;

	return TRUE;
}

void CdmvZScrewTxLinkData::GetParameters(structZScrewTxLinkParameters *pstrtZScrewTxLinkParameters) const
{
	pstrtZScrewTxLinkParameters->fD = m_strtZScrewTxLinkParameters.fD;
	pstrtZScrewTxLinkParameters->fTheta = m_strtZScrewTxLinkParameters.fTheta;
}

void CdmvZScrewTxLinkData::SetParameters (const structZScrewTxLinkParameters* pstrtZScrewTxLinkParameters)
{
	m_strtZScrewTxLinkParameters.fD = pstrtZScrewTxLinkParameters->fD;
	m_strtZScrewTxLinkParameters.fTheta = pstrtZScrewTxLinkParameters->fTheta;
}

void CdmvZScrewTxLinkData::SetJointParameters(double dD, double dTheta)
{
	m_strtZScrewTxLinkParameters.fD = dD;
	m_strtZScrewTxLinkParameters.fTheta = dTheta;
}
