// dmvLinkData.h: interface for the CdmvLinkData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVLINKDATA_H__32B7BEF4_DB46_11D3_8421_B909FA2E8733__INCLUDED_)
#define AFX_DMVLINKDATA_H__32B7BEF4_DB46_11D3_8421_B909FA2E8733__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "dmvObject.h"

#define LINK_MASS_MIN	1.0e-6
#define LINK_MASS_MAX	1.0e6
#define LINK_INERTIA_DIAGONAL_MIN	0.0
#define LINK_INERTIA_DIAGONAL_MAX	1.0e6
#define LINK_JOINT_FRICTION_MIN 0.0
#define LINK_JOINT_FRICTION_MAX	1.0e6

// to know the link type
typedef enum {MOBILE_BASE_LINK, PRISMATIC_LINK, REVOLUTE_LINK, SPHERICAL_LINK,
	STATIC_ROOT_LINK, ZSCREW_TX_LINK} LinkType;


class CdmvLinkData : public CdmvObject
{
public:
//	unsigned int GetLinkUID () const;
	Float GetJointFriction () const;
	LinkType GetLinkType () const;
	virtual BOOL GetLinkParameters (Float* pfParameters);
	void SetJointFriction (Float fJointFriction);
	CdmvLinkData();
	virtual ~CdmvLinkData();

protected:
//	const unsigned int m_nLinkUID;
	Float m_FJointFriction;
	LinkType m_LinkType;

};

#endif // !defined(AFX_DMVLINKDATA_H__32B7BEF4_DB46_11D3_8421_B909FA2E8733__INCLUDED_)
