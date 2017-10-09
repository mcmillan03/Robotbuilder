// dmvMobileBaseLinkData.cpp: implementation of the CdmvMobileBaseLinkData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvMobileBaseLinkData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvMobileBaseLinkData::CdmvMobileBaseLinkData()
{
	// init members
	m_strtMobileBaseLinkState.cvPosition[0] = 0;
	m_strtMobileBaseLinkState.cvPosition[1] = 0;
	m_strtMobileBaseLinkState.cvPosition[2] = 0;
	m_strtMobileBaseLinkState.qOrientation[0] = 0;
	m_strtMobileBaseLinkState.qOrientation[1] = 0;
	m_strtMobileBaseLinkState.qOrientation[2] = 0;
	m_strtMobileBaseLinkState.qOrientation[3] = 0;
	m_strtMobileBaseLinkState.svVelocity[0] = 0;
	m_strtMobileBaseLinkState.svVelocity[1] = 0;
	m_strtMobileBaseLinkState.svVelocity[2] = 0;
	m_strtMobileBaseLinkState.svVelocity[3] = 0;
	m_strtMobileBaseLinkState.svVelocity[4] = 0;
	m_strtMobileBaseLinkState.svVelocity[5] = 0;

	// set the link type
	m_LinkType = MOBILE_BASE_LINK;

	// Set the default name
	m_strName = "Mobile Base Link";

}

CdmvMobileBaseLinkData::~CdmvMobileBaseLinkData()
{

}

void CdmvMobileBaseLinkData::SetInitialState(CartesianVector cvPosition, 
											 Quaternion qOrientation,
											 SpatialVector svVelocity)
{
	// note that the first array of floats passed in is a concatenation of the
	// orientation in a quaternion in the first four floats and the position
	// in the last three floats

	m_strtMobileBaseLinkState.qOrientation[0] = qOrientation[0];
	m_strtMobileBaseLinkState.qOrientation[1] = qOrientation[1];
	m_strtMobileBaseLinkState.qOrientation[2] = qOrientation[2];
	m_strtMobileBaseLinkState.qOrientation[3] = qOrientation[3];
	m_strtMobileBaseLinkState.cvPosition[0] = cvPosition[0];
	m_strtMobileBaseLinkState.cvPosition[1] = cvPosition[1];
	m_strtMobileBaseLinkState.cvPosition[2] = cvPosition[2];
	m_strtMobileBaseLinkState.svVelocity[0] = svVelocity[0];
	m_strtMobileBaseLinkState.svVelocity[1] = svVelocity[1];
	m_strtMobileBaseLinkState.svVelocity[2] = svVelocity[2];
	m_strtMobileBaseLinkState.svVelocity[3] = svVelocity[3];
	m_strtMobileBaseLinkState.svVelocity[4] = svVelocity[4];
	m_strtMobileBaseLinkState.svVelocity[5] = svVelocity[5];
}

void CdmvMobileBaseLinkData::GetInitialState(structMobileBaseLinkState *pstrtMobileBaseLinkState) const
{
	pstrtMobileBaseLinkState->qOrientation[0] = m_strtMobileBaseLinkState.qOrientation[0];
	pstrtMobileBaseLinkState->qOrientation[1] = m_strtMobileBaseLinkState.qOrientation[1];
	pstrtMobileBaseLinkState->qOrientation[2] = m_strtMobileBaseLinkState.qOrientation[2];
	pstrtMobileBaseLinkState->qOrientation[3] = m_strtMobileBaseLinkState.qOrientation[3];
	pstrtMobileBaseLinkState->cvPosition[0] = m_strtMobileBaseLinkState.cvPosition[0];
	pstrtMobileBaseLinkState->cvPosition[1] = m_strtMobileBaseLinkState.cvPosition[1];
	pstrtMobileBaseLinkState->cvPosition[2] = m_strtMobileBaseLinkState.cvPosition[2];
	pstrtMobileBaseLinkState->svVelocity[0] = m_strtMobileBaseLinkState.svVelocity[0];
	pstrtMobileBaseLinkState->svVelocity[1] = m_strtMobileBaseLinkState.svVelocity[1];
	pstrtMobileBaseLinkState->svVelocity[2] = m_strtMobileBaseLinkState.svVelocity[2];
	pstrtMobileBaseLinkState->svVelocity[3] = m_strtMobileBaseLinkState.svVelocity[3];
	pstrtMobileBaseLinkState->svVelocity[4] = m_strtMobileBaseLinkState.svVelocity[4];
	pstrtMobileBaseLinkState->svVelocity[5] = m_strtMobileBaseLinkState.svVelocity[5];
}

void CdmvMobileBaseLinkData::SetState(structMobileBaseLinkState *pstrtMobileBaseLinkState)
{
	m_strtMobileBaseLinkState.qOrientation[0] = pstrtMobileBaseLinkState->qOrientation[0];
	m_strtMobileBaseLinkState.qOrientation[1] = pstrtMobileBaseLinkState->qOrientation[1];
	m_strtMobileBaseLinkState.qOrientation[2] = pstrtMobileBaseLinkState->qOrientation[2];
	m_strtMobileBaseLinkState.qOrientation[3] = pstrtMobileBaseLinkState->qOrientation[3];
	m_strtMobileBaseLinkState.cvPosition[0] = pstrtMobileBaseLinkState->cvPosition[0];
	m_strtMobileBaseLinkState.cvPosition[1] = pstrtMobileBaseLinkState->cvPosition[1];
	m_strtMobileBaseLinkState.cvPosition[2] = pstrtMobileBaseLinkState->cvPosition[2];
	m_strtMobileBaseLinkState.svVelocity[0] = pstrtMobileBaseLinkState->svVelocity[0];
	m_strtMobileBaseLinkState.svVelocity[1] = pstrtMobileBaseLinkState->svVelocity[1];
	m_strtMobileBaseLinkState.svVelocity[2] = pstrtMobileBaseLinkState->svVelocity[2];
	m_strtMobileBaseLinkState.svVelocity[3] = pstrtMobileBaseLinkState->svVelocity[3];
	m_strtMobileBaseLinkState.svVelocity[4] = pstrtMobileBaseLinkState->svVelocity[4];
	m_strtMobileBaseLinkState.svVelocity[5] = pstrtMobileBaseLinkState->svVelocity[5];

}

void CdmvMobileBaseLinkData::GetPlacement(Quaternion qOrientation, CartesianVector cvPosition)
{
	qOrientation[0] = m_strtMobileBaseLinkState.qOrientation[0];
	qOrientation[1] = m_strtMobileBaseLinkState.qOrientation[1];
	qOrientation[2] = m_strtMobileBaseLinkState.qOrientation[2];
	qOrientation[3] = m_strtMobileBaseLinkState.qOrientation[3];

	cvPosition[0] = m_strtMobileBaseLinkState.cvPosition[0];
	cvPosition[1] = m_strtMobileBaseLinkState.cvPosition[1];
	cvPosition[2] = m_strtMobileBaseLinkState.cvPosition[2];
}
