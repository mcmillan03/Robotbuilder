// dmvSecJointData.h: interface for the CdmvSecJointData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVSECJOINTDATA_H__984CD363_28CF_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVSECJOINTDATA_H__984CD363_28CF_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SECONDARY_JOINT_ROTATION_MATRIX_MIN	-1.0
#define SECONDARY_JOINT_ROTATION_MATRIX_MAX	1.0

#define SEC_JOINT_LINEAR_SPRING_MIN	0.0
#define SEC_JOINT_LINEAR_SPRING_MAX	1.0e6
#define SEC_JOINT_LINEAR_DAMPER_MIN	0.0
#define SEC_JOINT_LINEAR_DAMPER_MAX	1.0e6
#define SEC_JOINT_ANGULAR_SPRING_MIN	0.0
#define SEC_JOINT_ANGULAR_SPRING_MAX	1.0e6
#define SEC_JOINT_ANGULAR_DAMPER_MIN	0.0
#define SEC_JOINT_ANGULAR_DAMPER_MAX	1.0e6
#define SEC_JOINT_FRICTION_MIN 0.0
#define SEC_JOINT_FRICTION_MAX	1.0e6

#include <dm.h>
#include "dmvObject.h"

class CdmvLinkData;
class CdmvArticulationData;

typedef enum {SEC_PRISMATIC, SEC_SPHERICAL, SEC_REVOLUTE} SecondaryJointType;

typedef enum {STABILIZATION_NONE, STABILIZATION_BAUMGARTE, STABILIZATION_SPRING_DAMPER} StabilizationType;

enum {SOFT_SEC_JOINT, HARD_SEC_JOINT};

typedef struct {
//	CdmvClosedArticulationData* pClosedArticulation;
	CartesianVector cvPositionA;
	RotationMatrix rmRotationA;
	CdmvLinkData* pLinkA;
//	CdmvClosedArticulationData* pClosedArticulationA;
	CartesianVector cvPositionB; 
	RotationMatrix rmRotationB;
	CdmvLinkData* pLinkB;
//	CdmvClosedArticulationData* pClosedArticulationB;
	StabilizationType nStabilization;
	int nSoftOrHard;
	Float FJointFriction;
} structSecondaryJointParameters;

class CdmvSecJointData : public CdmvObject
{
public:
	void SetJointFriction (Float FJointFriction);
	Float GetJointFriction () const;
	StabilizationType GetStabilizationType () const;
	int GetSoftOrHard () const;
	void SetSoftOrHard (int nSoftOrHard);
	void initSoftJoint ();
	void SetStabilizationType (StabilizationType stabilization);
	void SetSecondaryJointParameters (const structSecondaryJointParameters *pstrtSecondaryJointParameters);
	void GetSecondaryJointParameters (structSecondaryJointParameters* pstrtSecondaryJointParameters) const;
	CdmvLinkData* GetLinkB () const;
	CdmvLinkData* GetLinkA () const;
	SecondaryJointType GetSecondaryJointType () const;
	void SetArticulation (CdmvArticulationData* pClosedArticulation);
	void SetLinkB (CdmvArticulationData* pClosedArticulation, CdmvLinkData *pLink);
	void SetLinkA (CdmvArticulationData* pClosedArticulation, CdmvLinkData *pLink);
	void SetKinematics (CartesianVector cvPositionA, CartesianVector cvPositionB, RotationMatrix rmRotationA, RotationMatrix rmRotationB);
	CdmvSecJointData();
	virtual ~CdmvSecJointData();
protected:
	structSecondaryJointParameters m_strtSecondaryJointParameters;
	SecondaryJointType m_SecondaryJointType;
};

#endif // !defined(AFX_DMVSECJOINTDATA_H__984CD363_28CF_11D4_A7DF_0000E8978554__INCLUDED_)
