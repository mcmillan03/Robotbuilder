// dmvSecRevJntData.h: interface for the CdmvSecRevJntData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVSECREVJNTDATA_H__984CD362_28CF_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVSECREVJNTDATA_H__984CD362_28CF_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "dmvSecJointData.h"

typedef struct
{
	double dLinearConstraintSpring;
	double dLinearConstraintDamper;
	double dAngularConstraintSpring;
	double dAngularConstraintDamper;
} structSecondaryRevoluteJointData;

class CdmvSecRevJntData : public CdmvSecJointData
{
public:
	void SetSecRevoluteJointData (const structSecondaryRevoluteJointData *pstrtSecondaryRevoluteJointData);
	void GetSecRevoluteJointData (structSecondaryRevoluteJointData* pstrtSecondaryRevoluteJointData) const;
	void SetConstraintParams (double dLinearConstraintSpring, double dLinearConstraintDamper, double dAngularConstraintSpring, double dAngularConstraintDamper);
	CdmvSecRevJntData();
	virtual ~CdmvSecRevJntData();
protected:
	structSecondaryRevoluteJointData m_strtSecondaryRevoluteJointData;

};

#endif // !defined(AFX_DMVSECREVJNTDATA_H__984CD362_28CF_11D4_A7DF_0000E8978554__INCLUDED_)
