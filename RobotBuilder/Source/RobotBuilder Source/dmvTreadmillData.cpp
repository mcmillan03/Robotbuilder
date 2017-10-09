// dmvTreadmillData.cpp: implementation of the CdmvTreadmillData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvTreadmillData.h"
#include "DMViewer.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvTreadmillData::CdmvTreadmillData()
{
	// Initialize the member data
	ResetTreadmillData ();
	// Set type
	SetEnvironmentType (ENV_TREADMILL);
}

CdmvTreadmillData::~CdmvTreadmillData()
{

}

double CdmvTreadmillData::GetWidth() const
{
	return m_dWidth;
}

double CdmvTreadmillData::GetLength() const
{
	return m_dLength;
}

void CdmvTreadmillData::GetPosition(CartesianVector &rcvPosition) const
{
	rcvPosition[X] = m_cvPosition[X];
	rcvPosition[Y] = m_cvPosition[Y];
	rcvPosition[Z] = m_cvPosition[Z];
}

void CdmvTreadmillData::GetParameters(structEnvTreadmillData *pstrtEnvTreadmillData) const
{
	for (int i = 0; i < 3; i++)
	{
		pstrtEnvTreadmillData->cvNormal[i] = m_cvNormal[i];
		pstrtEnvTreadmillData->cvPosition[i] = m_cvPosition[i];
		pstrtEnvTreadmillData->cvVelocityDirection[i] = m_cvVelocity[i];
	}

	pstrtEnvTreadmillData->dLength = m_dLength;
	pstrtEnvTreadmillData->dVelocityMagnitude = m_dVelocityMag;
	pstrtEnvTreadmillData->dWidth = m_dWidth;
	pstrtEnvTreadmillData->crColor = m_crTreadmillColor;
}

void CdmvTreadmillData::SetParameters(const structEnvTreadmillData *pstrtEnvTreadmillData)
{
	// Save the normal and velocity with the member function.  It will make sure they
	// are orthonormal
	// First copy them due to the function modifying the results but the parameter being const
	CartesianVector cvNormal, cvVelocity;
	copyCartesianVector (pstrtEnvTreadmillData->cvNormal, cvNormal);
	copyCartesianVector (pstrtEnvTreadmillData->cvVelocityDirection, cvVelocity);
	SetNormalAndVelocityDirection (cvNormal, cvVelocity);

	for (int i = 0; i < 3; i++)
	{
		m_cvPosition[i] = pstrtEnvTreadmillData->cvPosition[i];
	}

	m_dLength = pstrtEnvTreadmillData->dLength;
	m_dVelocityMag = pstrtEnvTreadmillData->dVelocityMagnitude;
	m_dWidth = pstrtEnvTreadmillData->dWidth;
	m_crTreadmillColor = pstrtEnvTreadmillData->crColor;
}


void CdmvTreadmillData::SetWidth(Float fWidth)
{
	m_dWidth = fWidth;
}


// Input the normal and velocity vector.  The function will normalize the vectors
// (in case they aren't) then make sure they are consistent by calculating the
// third component of the normal vector.  The computed normal vector is returned.
void CdmvTreadmillData::SetNormalAndVelocityDirection(CartesianVector cvNormal,
																		CartesianVector cvVelocity)
{
	if (!normalizeCartesianVector (cvNormal))
	{
		// Then normalize failed, so set vector to z
		cvNormal[2] = 1;
	}

	if (!normalizeCartesianVector (cvVelocity))
	{
		// Then normalize failed, so set vector to x
		cvVelocity[0] = 1;
	}

	// The velocity and normal vectors need to be perpendicular.  To ensure this,
	// use the knowledge that their dot product will be equal to one and calculate
	// the value of one component of the normal vector (depending on which velocity component is non-zero
	// so don't get a divide by zero)(is there a better way to do this?)
	if (cvVelocity[2] != 0)
		cvNormal[2] = (cvNormal[0] * cvVelocity[0] + cvNormal[1] * cvVelocity[1])/-cvVelocity[2];
	else if (cvVelocity[1] != 0)
		cvNormal[1] = (cvNormal[0] * cvVelocity[0] + cvNormal[2] * cvVelocity[2])/-cvVelocity[1];
	else
		cvNormal[0] = (cvNormal[2] * cvVelocity[2] + cvNormal[1] * cvVelocity[1])/-cvVelocity[0];

	// Make sure the normal is unit
	if (!normalizeCartesianVector (cvNormal))
	{
		// Then normalize failed, so set vector to x
		cvNormal[2] = 1;
	}


	// Save the vectors to the member variables
	copyCartesianVector (cvNormal, m_cvNormal);
	copyCartesianVector (cvVelocity, m_cvVelocity);
}


void CdmvTreadmillData::SetPosition(const CartesianVector cvPosition)
{
	copyCartesianVector (cvPosition, m_cvPosition);
}

void CdmvTreadmillData::SetLength(Float fLength)
{
	m_dLength = fLength;
}

// To define a consistent frame, the normal and velocity need to be perpendicular
BOOL CdmvTreadmillData::ValidateNormalAndVelocity(const CartesianVector cvNormal, const CartesianVector cvVelocity)
{
	double dResult = dotProduct (cvNormal, cvVelocity);
	// Round the number in case there a precision errors
	if (fabs(dResult) < .001)
		return TRUE;
	else
		return FALSE;
}

void CdmvTreadmillData::SetVelocityMagnitude(Float fVelocityMagnitude)
{
	m_dVelocityMag = fVelocityMagnitude;
}

void CdmvTreadmillData::SetColor(COLORREF crColor)
{
	m_crTreadmillColor = crColor;
}

void CdmvTreadmillData::ResetTreadmillData()
{	
	m_cvNormal[0] = 0;
	m_cvNormal[1] = 0;
	m_cvNormal[2] = 1;

	m_cvPosition[0] = 0;
	m_cvPosition[1] = 0;
	m_cvPosition[2] = 0;

	m_cvVelocity[0] = 1;
	m_cvVelocity[1] = 0;
	m_cvVelocity[2] = 0;

	m_dLength = 4;
	m_dWidth = 1;

	m_dVelocityMag = 0;

	m_crTreadmillColor = RGB (255, 255, 255);
}

void CdmvTreadmillData::GetNormal(CartesianVector cvNormal) const
{
	copyCartesianVector (m_cvNormal, cvNormal);
}

void CdmvTreadmillData::GetVelocityDirection(CartesianVector cvVelocity) const
{
	copyCartesianVector (m_cvVelocity, cvVelocity);

}

COLORREF CdmvTreadmillData::GetColor() const
{
	return m_crTreadmillColor;
}

Float CdmvTreadmillData::GetVelocityMagnitude() const
{
	return m_dVelocityMag;
}
