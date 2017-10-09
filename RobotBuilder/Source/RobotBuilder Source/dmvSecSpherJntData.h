// dmvSecSpherJntData.h: interface for the CdmvSecSpherJntData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVSECSPHERJNTDATA_H__984CD365_28CF_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVSECSPHERJNTDATA_H__984CD365_28CF_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvSecJointData.h"

typedef struct
{
	double dLinearConstraintSpring;
	double dLinearConstraintDamper;
} structSecondarySphericalJointData;


class CdmvSecSpherJntData : public CdmvSecJointData  
{
public:
	void SetSecSphericalJointData (const structSecondarySphericalJointData* pstrtSecondarySphericalJointData);
	void GetSecSphericalJointData (structSecondarySphericalJointData *pstrtSecondarySphericalJointData) const;
	void SetConstraintParams (double dLinearConstraintSpring, double dLinearConstraintDamper);
	CdmvSecSpherJntData();
	virtual ~CdmvSecSpherJntData();
protected:
	structSecondarySphericalJointData m_strtSecondarySphericalJointData;

};

#endif // !defined(AFX_DMVSECSPHERJNTDATA_H__984CD365_28CF_11D4_A7DF_0000E8978554__INCLUDED_)
