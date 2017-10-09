// dmvSecJointData.cpp: implementation of the CdmvSecJointData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvSecJointData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvSecJointData::CdmvSecJointData()
{
	// loop will copy both positions and rotations
	unsigned int i;
	unsigned int j;
	for (i = 0; i < 3; i++)
	{
		m_strtSecondaryJointParameters.cvPositionA[i] = 0;
		m_strtSecondaryJointParameters.cvPositionB[i] = 0;
		for (j = 0; j < 3; j++)
		{
			m_strtSecondaryJointParameters.rmRotationA[i][j] = 0;
			m_strtSecondaryJointParameters.rmRotationB[i][j] = 0;
		}
	}
	m_strtSecondaryJointParameters.pLinkA = NULL;
	m_strtSecondaryJointParameters.pLinkB = NULL;
	m_strtSecondaryJointParameters.nStabilization = STABILIZATION_BAUMGARTE;
	m_strtSecondaryJointParameters.nSoftOrHard = HARD_SEC_JOINT;
	// Initialize Object type as secondary link
	m_ObjectType = SECONDARY_JOINT;
	m_strtSecondaryJointParameters.FJointFriction = 0.0;
}

CdmvSecJointData::~CdmvSecJointData()
{

}

void CdmvSecJointData::SetKinematics(CartesianVector cvPositionA,
									 CartesianVector cvPositionB, 
									 RotationMatrix rmRotationA, 
									 RotationMatrix rmRotationB)
{
	// loop will copy both positions and rotations
	unsigned int i;
	unsigned int j;
	for (i = 0; i < 3; i++)
	{
		m_strtSecondaryJointParameters.cvPositionA[i] = cvPositionA[i];
		m_strtSecondaryJointParameters.cvPositionB[i] = cvPositionB[i];
		for (j = 0; j < 3; j++)
		{
			m_strtSecondaryJointParameters.rmRotationA[i][j] =
				rmRotationA[i][j];
			m_strtSecondaryJointParameters.rmRotationB[i][j] =
				rmRotationB[i][j];
		}
	}
}

void CdmvSecJointData::SetLinkA(CdmvArticulationData *pClosedArticulation, 
								CdmvLinkData *pLink)
{
	// In the current implementation, I don't need the articulation pointer, but
	// I will go ahead and save it for now
//	m_strtSecondaryJointParameters.pClosedArticulationA = pClosedArticulation;
	m_strtSecondaryJointParameters.pLinkA = pLink;

}

void CdmvSecJointData::SetLinkB(CdmvArticulationData *pClosedArticulation, CdmvLinkData *pLink)
{
//	m_strtSecondaryJointParameters.pClosedArticulationB = pClosedArticulation;
	m_strtSecondaryJointParameters.pLinkB = pLink;
}

void CdmvSecJointData::SetArticulation(CdmvArticulationData *pClosedArticulation)
{
//	m_strtSecondaryJointParameters.pClosedArticulation = pClosedArticulation;
}

SecondaryJointType CdmvSecJointData::GetSecondaryJointType() const
{
	return m_SecondaryJointType;
}



CdmvLinkData* CdmvSecJointData::GetLinkA() const
{
	return m_strtSecondaryJointParameters.pLinkA;
}

CdmvLinkData* CdmvSecJointData::GetLinkB() const
{
	return m_strtSecondaryJointParameters.pLinkB;
}

void CdmvSecJointData::GetSecondaryJointParameters(structSecondaryJointParameters *pstrtSecondaryJointParameters) const
{
	ASSERT (pstrtSecondaryJointParameters);
	
	pstrtSecondaryJointParameters->cvPositionA[0] = m_strtSecondaryJointParameters.cvPositionA[0];
	pstrtSecondaryJointParameters->cvPositionA[1] = m_strtSecondaryJointParameters.cvPositionA[1];
	pstrtSecondaryJointParameters->cvPositionA[2] = m_strtSecondaryJointParameters.cvPositionA[2];

	pstrtSecondaryJointParameters->cvPositionB[0] = m_strtSecondaryJointParameters.cvPositionB[0];
	pstrtSecondaryJointParameters->cvPositionB[1] = m_strtSecondaryJointParameters.cvPositionB[1];
	pstrtSecondaryJointParameters->cvPositionB[2] = m_strtSecondaryJointParameters.cvPositionB[2];

	pstrtSecondaryJointParameters->rmRotationA[0][0] = m_strtSecondaryJointParameters.rmRotationA[0][0];
	pstrtSecondaryJointParameters->rmRotationA[0][1] = m_strtSecondaryJointParameters.rmRotationA[0][1];
	pstrtSecondaryJointParameters->rmRotationA[0][2] = m_strtSecondaryJointParameters.rmRotationA[0][2];
	pstrtSecondaryJointParameters->rmRotationA[1][0] = m_strtSecondaryJointParameters.rmRotationA[1][0];
	pstrtSecondaryJointParameters->rmRotationA[1][1] = m_strtSecondaryJointParameters.rmRotationA[1][1];
	pstrtSecondaryJointParameters->rmRotationA[1][2] = m_strtSecondaryJointParameters.rmRotationA[1][2];
	pstrtSecondaryJointParameters->rmRotationA[2][0] = m_strtSecondaryJointParameters.rmRotationA[2][0];
	pstrtSecondaryJointParameters->rmRotationA[2][1] = m_strtSecondaryJointParameters.rmRotationA[2][1];
	pstrtSecondaryJointParameters->rmRotationA[2][2] = m_strtSecondaryJointParameters.rmRotationA[2][2];

	pstrtSecondaryJointParameters->rmRotationB[0][0] = m_strtSecondaryJointParameters.rmRotationB[0][0];
	pstrtSecondaryJointParameters->rmRotationB[0][1] = m_strtSecondaryJointParameters.rmRotationB[0][1];
	pstrtSecondaryJointParameters->rmRotationB[0][2] = m_strtSecondaryJointParameters.rmRotationB[0][2];
	pstrtSecondaryJointParameters->rmRotationB[1][0] = m_strtSecondaryJointParameters.rmRotationB[1][0];
	pstrtSecondaryJointParameters->rmRotationB[1][1] = m_strtSecondaryJointParameters.rmRotationB[1][1];
	pstrtSecondaryJointParameters->rmRotationB[1][2] = m_strtSecondaryJointParameters.rmRotationB[1][2];
	pstrtSecondaryJointParameters->rmRotationB[2][0] = m_strtSecondaryJointParameters.rmRotationB[2][0];
	pstrtSecondaryJointParameters->rmRotationB[2][1] = m_strtSecondaryJointParameters.rmRotationB[2][1];
	pstrtSecondaryJointParameters->rmRotationB[2][2] = m_strtSecondaryJointParameters.rmRotationB[2][2];

	pstrtSecondaryJointParameters->pLinkA = m_strtSecondaryJointParameters.pLinkA;
	pstrtSecondaryJointParameters->pLinkB = m_strtSecondaryJointParameters.pLinkB;

	pstrtSecondaryJointParameters->nStabilization = m_strtSecondaryJointParameters.nStabilization;
	pstrtSecondaryJointParameters->nSoftOrHard = m_strtSecondaryJointParameters.nSoftOrHard;

	pstrtSecondaryJointParameters->FJointFriction = m_strtSecondaryJointParameters.FJointFriction;
}



void CdmvSecJointData::SetSecondaryJointParameters(const structSecondaryJointParameters *pstrtSecondaryJointParameters)
{
	m_strtSecondaryJointParameters.cvPositionA[0] = pstrtSecondaryJointParameters->cvPositionA[0];
	m_strtSecondaryJointParameters.cvPositionA[1] = pstrtSecondaryJointParameters->cvPositionA[1];
	m_strtSecondaryJointParameters.cvPositionA[2] = pstrtSecondaryJointParameters->cvPositionA[2];

	m_strtSecondaryJointParameters.cvPositionB[0] = pstrtSecondaryJointParameters->cvPositionB[0];
	m_strtSecondaryJointParameters.cvPositionB[1] = pstrtSecondaryJointParameters->cvPositionB[1];
	m_strtSecondaryJointParameters.cvPositionB[2] = pstrtSecondaryJointParameters->cvPositionB[2];

	m_strtSecondaryJointParameters.rmRotationA[0][0] = pstrtSecondaryJointParameters->rmRotationA[0][0];
	m_strtSecondaryJointParameters.rmRotationA[0][1] = pstrtSecondaryJointParameters->rmRotationA[0][1];
	m_strtSecondaryJointParameters.rmRotationA[0][2] = pstrtSecondaryJointParameters->rmRotationA[0][2];
	m_strtSecondaryJointParameters.rmRotationA[1][0] = pstrtSecondaryJointParameters->rmRotationA[1][0];
	m_strtSecondaryJointParameters.rmRotationA[1][1] = pstrtSecondaryJointParameters->rmRotationA[1][1];
	m_strtSecondaryJointParameters.rmRotationA[1][2] = pstrtSecondaryJointParameters->rmRotationA[1][2];
	m_strtSecondaryJointParameters.rmRotationA[2][0] = pstrtSecondaryJointParameters->rmRotationA[2][0];
	m_strtSecondaryJointParameters.rmRotationA[2][1] = pstrtSecondaryJointParameters->rmRotationA[2][1];
	m_strtSecondaryJointParameters.rmRotationA[2][2] = pstrtSecondaryJointParameters->rmRotationA[2][2];

	m_strtSecondaryJointParameters.rmRotationB[0][0] = pstrtSecondaryJointParameters->rmRotationB[0][0];
	m_strtSecondaryJointParameters.rmRotationB[0][1] = pstrtSecondaryJointParameters->rmRotationB[0][1];
	m_strtSecondaryJointParameters.rmRotationB[0][2] = pstrtSecondaryJointParameters->rmRotationB[0][2];
	m_strtSecondaryJointParameters.rmRotationB[1][0] = pstrtSecondaryJointParameters->rmRotationB[1][0];
	m_strtSecondaryJointParameters.rmRotationB[1][1] = pstrtSecondaryJointParameters->rmRotationB[1][1];
	m_strtSecondaryJointParameters.rmRotationB[1][2] = pstrtSecondaryJointParameters->rmRotationB[1][2];
	m_strtSecondaryJointParameters.rmRotationB[2][0] = pstrtSecondaryJointParameters->rmRotationB[2][0];
	m_strtSecondaryJointParameters.rmRotationB[2][1] = pstrtSecondaryJointParameters->rmRotationB[2][1];
	m_strtSecondaryJointParameters.rmRotationB[2][2] = pstrtSecondaryJointParameters->rmRotationB[2][2];

	m_strtSecondaryJointParameters.pLinkA = pstrtSecondaryJointParameters->pLinkA;
	m_strtSecondaryJointParameters.pLinkB = pstrtSecondaryJointParameters->pLinkB;

	m_strtSecondaryJointParameters.nStabilization = pstrtSecondaryJointParameters->nStabilization;
	m_strtSecondaryJointParameters.nSoftOrHard = pstrtSecondaryJointParameters->nSoftOrHard;

	m_strtSecondaryJointParameters.FJointFriction = pstrtSecondaryJointParameters->FJointFriction;
}

void CdmvSecJointData::SetStabilizationType(StabilizationType stabilization)
{
	m_strtSecondaryJointParameters.nStabilization = stabilization;	
}

void CdmvSecJointData::initSoftJoint()
{
	// dummy function called by parser, but not used here
}

void CdmvSecJointData::SetSoftOrHard(int nSoftOrHard)
{
	m_strtSecondaryJointParameters.nSoftOrHard = nSoftOrHard;
}

int CdmvSecJointData::GetSoftOrHard() const
{
	return m_strtSecondaryJointParameters.nSoftOrHard;
}

StabilizationType CdmvSecJointData::GetStabilizationType() const
{
	return m_strtSecondaryJointParameters.nStabilization;
}

Float CdmvSecJointData::GetJointFriction() const
{
	return m_strtSecondaryJointParameters.FJointFriction;
}

void CdmvSecJointData::SetJointFriction(Float FJointFriction)
{
	m_strtSecondaryJointParameters.FJointFriction = FJointFriction;
}
