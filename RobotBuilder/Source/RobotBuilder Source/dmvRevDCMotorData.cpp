// dmvRevDCMotorData.cpp: implementation of the CdmvRevDCMotorData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvRevDCMotorData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvRevDCMotorData::CdmvRevDCMotorData()
{
	// set the actuator type
	m_ActuatorType = REV_DC_MOTOR;
	// init members
	m_strtRevDCMotorParameters.fTorqueConstant = 0;
	m_strtRevDCMotorParameters.fBackEMFConstant = 0;
	m_strtRevDCMotorParameters.fArmatureResistance = 0;
	m_strtRevDCMotorParameters.fRotorInertia = 0;
	m_strtRevDCMotorParameters.fCoulombFrictionConstant = 0;
	m_strtRevDCMotorParameters.fViscousFrictionConstant = 0;
	m_strtRevDCMotorParameters.fMaxBrushDrop = 0;
	m_strtRevDCMotorParameters.fHalfDropValue = 0;
	m_strtRevDCMotorParameters.fGearRatio = 1;
}

CdmvRevDCMotorData::~CdmvRevDCMotorData()
{

}

void CdmvRevDCMotorData::SetParameters(Float fTorqueConstant, 
									   Float fBackEMFConstant, 
									   Float fArmatureResistance, 
									   Float fRotorInertia, 
									   Float fCoulombFrictionConstant, 
									   Float fViscousFrictionConstant, 
									   Float fMaxBrushDrop, 
									   Float fHalfDropValue,
									   Float fGearRatio)
{
	m_strtRevDCMotorParameters.fTorqueConstant = fTorqueConstant;
	m_strtRevDCMotorParameters.fBackEMFConstant = fBackEMFConstant;
	m_strtRevDCMotorParameters.fArmatureResistance = fArmatureResistance;
	m_strtRevDCMotorParameters.fRotorInertia = fRotorInertia;
	m_strtRevDCMotorParameters.fCoulombFrictionConstant = fCoulombFrictionConstant;
	m_strtRevDCMotorParameters.fViscousFrictionConstant = fViscousFrictionConstant;
	m_strtRevDCMotorParameters.fMaxBrushDrop = fMaxBrushDrop;
	m_strtRevDCMotorParameters.fHalfDropValue = fHalfDropValue;
	m_strtRevDCMotorParameters.fGearRatio = fGearRatio;
}

void CdmvRevDCMotorData::SetParameters(const structRevDCMotorParameters *pstrRevDCMotorParameters)
{
	m_strtRevDCMotorParameters.fTorqueConstant = pstrRevDCMotorParameters->fTorqueConstant;
	m_strtRevDCMotorParameters.fBackEMFConstant = pstrRevDCMotorParameters->fBackEMFConstant;
	m_strtRevDCMotorParameters.fArmatureResistance = pstrRevDCMotorParameters->fArmatureResistance;
	m_strtRevDCMotorParameters.fRotorInertia = pstrRevDCMotorParameters->fRotorInertia;
	m_strtRevDCMotorParameters.fCoulombFrictionConstant = pstrRevDCMotorParameters->fCoulombFrictionConstant;
	m_strtRevDCMotorParameters.fViscousFrictionConstant = pstrRevDCMotorParameters->fViscousFrictionConstant;
	m_strtRevDCMotorParameters.fMaxBrushDrop = pstrRevDCMotorParameters->fMaxBrushDrop;
	m_strtRevDCMotorParameters.fHalfDropValue = pstrRevDCMotorParameters->fHalfDropValue;
	m_strtRevDCMotorParameters.fGearRatio = pstrRevDCMotorParameters->fGearRatio;

}

void CdmvRevDCMotorData::GetParameters(structRevDCMotorParameters *pstrtRevDCMotorParameters) const
{
	pstrtRevDCMotorParameters->fTorqueConstant = m_strtRevDCMotorParameters.fTorqueConstant;
	pstrtRevDCMotorParameters->fBackEMFConstant = m_strtRevDCMotorParameters.fBackEMFConstant;
	pstrtRevDCMotorParameters->fArmatureResistance = m_strtRevDCMotorParameters.fArmatureResistance;
	pstrtRevDCMotorParameters->fRotorInertia = m_strtRevDCMotorParameters.fRotorInertia;
	pstrtRevDCMotorParameters->fCoulombFrictionConstant = m_strtRevDCMotorParameters.fCoulombFrictionConstant;
	pstrtRevDCMotorParameters->fViscousFrictionConstant = m_strtRevDCMotorParameters.fViscousFrictionConstant;
	pstrtRevDCMotorParameters->fMaxBrushDrop = m_strtRevDCMotorParameters.fMaxBrushDrop;
	pstrtRevDCMotorParameters->fHalfDropValue = m_strtRevDCMotorParameters.fHalfDropValue;
	pstrtRevDCMotorParameters->fGearRatio = m_strtRevDCMotorParameters.fGearRatio;
}
