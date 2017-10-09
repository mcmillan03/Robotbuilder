// dmvRigidBodyData.h: interface for the CdmvRigidBodyData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVRIGIDBODYDATA_H__5E3B29A5_DBDC_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVRIGIDBODYDATA_H__5E3B29A5_DBDC_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dm.h>
#include "dmvContactModelData.h"

#define RIGID_BODY_NUM_CONTACTS_MIN	0
#define RIGID_BODY_NUM_CONTACTS_MAX	1e6

typedef struct
{
	Float fMass;
	CartesianTensor ctIbar;
	CartesianVector cvCenterGravityPosition;
} structRigidBodyInertialParameters;

class CdmvRigidBodyData  
{
public:
	CdmvRigidBodyData (const CdmvRigidBodyData& rCdmvRigidBodyData);
	void SetInertialParameters (const structRigidBodyInertialParameters* pstrtRigidBodyInertialParameters);
	void GetInertialParameters (structRigidBodyInertialParameters* pstrtRigidBodyInertialParameters) const;
	void DeleteContactModel ();
	CdmvContactModelData* GetContactModel () const;
	void SetContactModel (CdmvContactModelData* pContactModel);
	void SetInertiaParameters (Float fMass, CartesianTensor ctIbar, CartesianVector cvCenterGravityPosition);
	CdmvRigidBodyData();
	virtual ~CdmvRigidBodyData();
protected:
	structRigidBodyInertialParameters m_strtRigidBodyInertialParameters;
//	CList <CdmvContactModelData*, CdmvContactModelData*> m_listForces;
	CdmvContactModelData* m_pContactModel;

};

#endif // !defined(AFX_DMVRIGIDBODYDATA_H__5E3B29A5_DBDC_11D3_A7DF_0000E8978554__INCLUDED_)
