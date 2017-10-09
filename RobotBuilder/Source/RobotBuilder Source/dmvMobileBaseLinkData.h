// dmvMobileBaseLinkData.h: interface for the CdmvMobileBaseLinkData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVMOBILEBASELINKDATA_H__5E3B29A4_DBDC_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVMOBILEBASELINKDATA_H__5E3B29A4_DBDC_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvLinkData.h"
#include "dmvRigidBodyData.h"

typedef struct
{
	CartesianVector cvPosition;
	Quaternion qOrientation;
	SpatialVector svVelocity;
} structMobileBaseLinkState;

class CdmvMobileBaseLinkData : public CdmvLinkData, public CdmvRigidBodyData  
{
public:
	void GetPlacement (Quaternion qOrientation, CartesianVector cvPosition);
	void SetState (structMobileBaseLinkState* pstrtMobileBaseLinkState);
	void GetInitialState (structMobileBaseLinkState* pstrtMobileBaseLinkState) const; 
	void SetInitialState (CartesianVector cvPosition, Quaternion qOrientation, SpatialVector svVelocity);
	CdmvMobileBaseLinkData();
	virtual ~CdmvMobileBaseLinkData();
protected:
	structMobileBaseLinkState m_strtMobileBaseLinkState;

};

#endif // !defined(AFX_DMVMOBILEBASELINKDATA_H__5E3B29A4_DBDC_11D3_A7DF_0000E8978554__INCLUDED_)
