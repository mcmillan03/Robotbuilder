// dmvSphericalLinkData.h: interface for the CdmvSphericalLinkData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVSPHERICALLINKDATA_H__75A06B66_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVSPHERICALLINKDATA_H__75A06B66_DBFE_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvRigidBodyData.h"
#include "dmvLinkData.h"

#define N_NUM_DOFS	3 // define here so we can define the array sizes in the
	// structs that define members in the class

#define SPHERICAL_LINK_INITIAL_EULER_ANGLE_MIN	-PI*1.1
#define SPHERICAL_LINK_INITIAL_EULER_ANGLE_MAX	PI*1.1
#define SPHERICAL_LINK_SPRING_CONSTANT_MIN	0.0
#define SPHERICAL_LINK_SPRING_CONSTANT_MAX	1.0e6
#define SPHERICAL_LINK_DAMPER_CONSTANT_MIN	0.0
#define SPHERICAL_LINK_DAMPER_CONSTANT_MAX	1.0e6


typedef struct
{
	EulerAngles eaAngles;
	Float fAngularVelocity[N_NUM_DOFS];
} structSphericalLinkState;

typedef struct
{
	Float fJointLimits[N_NUM_DOFS];
	Float fSpring;
	Float fDamper;
} structSphericalLinkJointLimits;

class CdmvSphericalLinkData : 
	public CdmvLinkData, 
	public CdmvRigidBodyData  
{


public:
	void SetLinkState (const structSphericalLinkState *pstrtSphericalLinkState);
	void GetLinkState (structSphericalLinkState *pstrtSphericalLinkState) const;
	void SetJointLimits (const structSphericalLinkJointLimits *pstrtSphericalLinkJointLimits);
	void GetJointLimits (structSphericalLinkJointLimits *pstrtSphericalLinkJointLimits) const;
	void GetJointOffset (CartesianVector cvPosition) const;
	void SetJointLimits (double dJointLimits[], double dSpring, double dDamper);
	void SetInitialState (EulerAngles eaAngles, double dAngularVelocity[]);
	void SetJointOffset (CartesianVector cvPosition);
	CdmvSphericalLinkData();
	virtual ~CdmvSphericalLinkData();
	enum {NUM_DOFS = N_NUM_DOFS};
protected:
	CartesianVector m_cvJointOffsetPosition;
	structSphericalLinkState m_strtSphericalLinkState;
	structSphericalLinkJointLimits m_strtSphericalLinkJointLimits;
};


#endif // !defined(AFX_DMVSPHERICALLINKDATA_H__75A06B66_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
