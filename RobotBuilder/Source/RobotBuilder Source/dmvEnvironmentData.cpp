// dmvEnvironmentData.cpp: implementation of the CdmvEnvironmentData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvEnvironmentData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvEnvironmentData::CdmvEnvironmentData()
{
	m_strtEnvironmentData.eEnvironmentType = ENV_TERRAIN;

	m_strtEnvironmentData.cvGravity[0] = 0;
	m_strtEnvironmentData.cvGravity[1] = 0;
	m_strtEnvironmentData.cvGravity[2] = (Float) 9.81;


	m_strtEnvironmentData.fGroundNormalDamperConstant = 0;
	m_strtEnvironmentData.fGroundNormalSpringConstant = 0;
	m_strtEnvironmentData.fGroundPlanarDamperConstant = 0;
	m_strtEnvironmentData.fGroundPlanarSpringConstant = 0;
	m_strtEnvironmentData.fu_k = 0;
	m_strtEnvironmentData.fu_s = 0;
	m_strtEnvironmentData.strDataFile = "";
	m_strtEnvironmentData.strDataPath = "";
}

CdmvEnvironmentData::~CdmvEnvironmentData()
{

}

void CdmvEnvironmentData::SetGravity(CartesianVector cv)
{
	m_strtEnvironmentData.cvGravity[0] = cv[0];
	m_strtEnvironmentData.cvGravity[1] = cv[1];
	m_strtEnvironmentData.cvGravity[2] = cv[2];
}

void CdmvEnvironmentData::SetDataFile(CString strDataFile, CString strPath)
{
	m_strtEnvironmentData.strDataFile = strDataFile;
	m_strtEnvironmentData.strDataPath = strPath;

}

void CdmvEnvironmentData::SetGroundPlanarSpringConstant(Float fSpringConstant)
{
	m_strtEnvironmentData.fGroundPlanarSpringConstant = fSpringConstant;
}

void CdmvEnvironmentData::SetGroundNormalSpringConstant(Float fSpringConstant)
{
	m_strtEnvironmentData.fGroundNormalSpringConstant = fSpringConstant;
}

void CdmvEnvironmentData::SetGroundPlanarDamperConstant(Float fDamperConstant)
{
	m_strtEnvironmentData.fGroundPlanarDamperConstant = fDamperConstant;
}

void CdmvEnvironmentData::SetGroundNormalDamperConstant(Float fDamperConstant)
{
	m_strtEnvironmentData.fGroundNormalDamperConstant = fDamperConstant;
}

void CdmvEnvironmentData::SetCoefficientStaticFriction(Float u_s)
{
	m_strtEnvironmentData.fu_s = u_s;
}

void CdmvEnvironmentData::SetCoefficientKineticFriction(Float u_k)
{
	m_strtEnvironmentData.fu_k = u_k;
}


void CdmvEnvironmentData::GetEnvironmentData(structEnvironmentData *pstrtEnvironmentData) const
{
	pstrtEnvironmentData->eEnvironmentType = m_strtEnvironmentData.eEnvironmentType;

	pstrtEnvironmentData->cvGravity[0] = m_strtEnvironmentData.cvGravity[0];
	pstrtEnvironmentData->cvGravity[1] = m_strtEnvironmentData.cvGravity[1];
	pstrtEnvironmentData->cvGravity[2] = m_strtEnvironmentData.cvGravity[2];

	pstrtEnvironmentData->fGroundNormalDamperConstant = 
		m_strtEnvironmentData.fGroundNormalDamperConstant;
	pstrtEnvironmentData->fGroundNormalSpringConstant =
		m_strtEnvironmentData.fGroundNormalSpringConstant;
	pstrtEnvironmentData->fGroundPlanarDamperConstant =
		m_strtEnvironmentData.fGroundPlanarDamperConstant;
	pstrtEnvironmentData->fGroundPlanarSpringConstant =
		m_strtEnvironmentData.fGroundPlanarSpringConstant;
	pstrtEnvironmentData->fu_k =
		m_strtEnvironmentData.fu_k;
	pstrtEnvironmentData->fu_s =
		m_strtEnvironmentData.fu_s;
	pstrtEnvironmentData->strDataFile =
		m_strtEnvironmentData.strDataFile;
	pstrtEnvironmentData->strDataPath =
		m_strtEnvironmentData.strDataPath;
}

void CdmvEnvironmentData::SetEnvironmentData(const structEnvironmentData *pstrtEnvironmentData)
{
	m_strtEnvironmentData.eEnvironmentType = pstrtEnvironmentData->eEnvironmentType;

	m_strtEnvironmentData.cvGravity[0] = pstrtEnvironmentData->cvGravity[0];
	m_strtEnvironmentData.cvGravity[1] = pstrtEnvironmentData->cvGravity[1];
	m_strtEnvironmentData.cvGravity[2] = pstrtEnvironmentData->cvGravity[2];

	m_strtEnvironmentData.fGroundNormalDamperConstant = 
		pstrtEnvironmentData->fGroundNormalDamperConstant;
	m_strtEnvironmentData.fGroundNormalSpringConstant = 
		pstrtEnvironmentData->fGroundNormalSpringConstant;
	m_strtEnvironmentData.fGroundPlanarDamperConstant = 
		pstrtEnvironmentData->fGroundPlanarDamperConstant;
	m_strtEnvironmentData.fGroundPlanarSpringConstant = 
		pstrtEnvironmentData->fGroundPlanarSpringConstant;
	m_strtEnvironmentData.fu_k = 
		pstrtEnvironmentData->fu_k;
	m_strtEnvironmentData.fu_s = 
		pstrtEnvironmentData->fu_s;
	m_strtEnvironmentData.strDataFile = 
		pstrtEnvironmentData->strDataFile;
	m_strtEnvironmentData.strDataPath = 
		pstrtEnvironmentData->strDataPath;
}

void CdmvEnvironmentData::GetDataFile(CString &rstrFile, CString &rstrPath)
{
	rstrFile =  m_strtEnvironmentData.strDataFile;
	rstrPath =  m_strtEnvironmentData.strDataPath;
}


enumEnvironmentType CdmvEnvironmentData::GetEnvironmentType() const
{
	return m_strtEnvironmentData.eEnvironmentType;
}

void CdmvEnvironmentData::SetEnvironmentType(enumEnvironmentType theEnvironmentType)
{
	m_strtEnvironmentData.eEnvironmentType = theEnvironmentType;
}
