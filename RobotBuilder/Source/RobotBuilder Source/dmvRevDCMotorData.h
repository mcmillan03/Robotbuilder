// dmvRevDCMotorData.h: interface for the CdmvRevDCMotorData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVREVDCMOTORDATA_H__75A06B64_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVREVDCMOTORDATA_H__75A06B64_DBFE_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvActuatorData.h"

#define REV_DC_MOTOR_TORQUE_CONSTANT_MIN	0.0
#define REV_DC_MOTOR_TORQUE_CONSTANT_MAX	1.0e6
#define REV_DC_MOTOR_BACK_EMF_CONSTANT_MIN	0.0
#define REV_DC_MOTOR_BACK_EMF_CONSTANT_MAX	1.0e6
#define REV_DC_MOTOR_ARMATURE_RESISTANCE_MIN	0.0
#define REV_DC_MOTOR_ARMATURE_RESISTANCE_MAX	1.0e6
#define REV_DC_MOTOR_INERTIA_MIN	0.0
#define REV_DC_MOTOR_INERTIA_MAX	1.0e6
#define REV_DC_MOTOR_COULOMB_FRICTION_MIN	0.0
#define REV_DC_MOTOR_COULOMB_FRICTION_MAX	1.0e6
#define REV_DC_MOTOR_VISCOUS_FRICTION_MIN	0.0
#define REV_DC_MOTOR_VISCOUS_FRICTION_MAX	1.0e6
#define REV_DC_MOTOR_MAX_BRUSH_DROP_MIN	0.0
#define REV_DC_MOTOR_MAX_BRUSH_DROP_MAX	1.0e6
#define REV_DC_MOTOR_HALF_DROP_MIN	0.0
#define REV_DC_MOTOR_HALF_DROP_MAX	1.0e6
#define REV_DC_MOTOR_GEAR_RATIO_MIN	0.0
#define REV_DC_MOTOR_GEAR_RATIO_MAX	1.0e6

typedef struct 
{
	Float fTorqueConstant;
	Float fBackEMFConstant;
	Float fArmatureResistance;
	Float fRotorInertia;
	Float fCoulombFrictionConstant;
	Float fViscousFrictionConstant;
	Float fMaxBrushDrop;
	Float fHalfDropValue;
	Float fGearRatio;
} structRevDCMotorParameters;


class CdmvRevDCMotorData : public CdmvActuatorData  
{
public:
	void GetParameters (structRevDCMotorParameters* pstrtRevDCMotorParameters) const;
	void SetParameters (const structRevDCMotorParameters* pstrRevDCMotorParameters);
	void SetParameters (Float fTorqueConstant, Float fBackEMFConstant, 
		Float fArmatureResistance, Float fRotorInertia, 
		Float fCoulombFrictionConstant, Float fViscousFrictionConstant, 
		Float fMaxBrushDrop, Float fHalfDropValue, Float fGearRatio);
	CdmvRevDCMotorData();
	virtual ~CdmvRevDCMotorData();
protected:
	structRevDCMotorParameters m_strtRevDCMotorParameters;
};

#endif // !defined(AFX_DMVREVDCMOTORDATA_H__75A06B64_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
