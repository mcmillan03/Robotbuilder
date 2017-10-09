// dmvMDHLinkData.h: interface for the CdmvMDHLinkData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVMDHLINKDATA_H__75A06B62_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVMDHLINKDATA_H__75A06B62_DBFE_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MDH_LINK_ALPHA_MIN	-PI*1.1 // alpha is always fixed, but theta can be a joint angle that changes
#define MDH_LINK_ALPHA_MAX	PI*1.1
#define MDH_LINK_JOINT_DAMPER_MIN	0.0
#define MDH_LINK_JOINT_DAMPER_MAX	1.0e6
#define MDH_LINK_JOINT_SPRING_MIN	0.0
#define MDH_LINK_JOINT_SPRING_MAX	1.0e6

#include "dmvLinkData.h"
#include "dmvRigidBodyData.h"
#include <dm.h>

typedef struct
{
	Float fa;
	Float fAlpha;
	Float fd;
	Float fTheta;
} structMDHParameters;

typedef struct
{
	Float fMin;
	Float fMax;
	Float fSpring;
	Float fDamper;
} structMDHLinkJointLimits;

typedef struct
{
	Float fq;
	Float fqd;
} structMDHLinkState;


class CdmvMDHLinkData : public CdmvLinkData, public CdmvRigidBodyData  
{
public:
	void SetInitialJointVelocity (Float fInitialJointVelocity);
	Float GetInitialJointVelocity () const;
	void SetMDHParameters (const structMDHParameters* pstrtMDHParameters);
	void GetMDHParameters (structMDHParameters* pstrtMDHParameters) const;
//	void SetLinkState (const structMDHLinkState* pstrtMDHLinkState);
//	void GetLinkState (structMDHLinkState* pstrtMDHLinkState) const;
	void GetJointLimits (structMDHLinkJointLimits* pstrtMDHLinkJointLimits) const;
	void SetJointLimits (const structMDHLinkJointLimits* pstrtMDHLinkJointLimits);
	virtual void GetLinkParameters (Float* pfParameters) const;
	void SetMDHParameters (Float fa, Float fAlpha, Float fd, Float fTheta);
	void SetJointLimits (Float fMin, Float fMax, Float fSpring, Float fDamper);
//	void getState (Float* q, Float* qd);
//	void setState (Float* q, Float* qd);
	CdmvMDHLinkData();
	virtual ~CdmvMDHLinkData();
	structMDHParameters m_strtMDHParameters;
protected:
	structMDHLinkJointLimits m_strtMDHLinkJointLimits;
	structMDHLinkState m_strtMDHLinkState;

};

#endif // !defined(AFX_DMVMDHLINKDATA_H__75A06B62_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
