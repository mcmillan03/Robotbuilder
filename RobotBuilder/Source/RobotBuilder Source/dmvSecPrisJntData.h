// dmvSecPrisJntData.h: interface for the CdmvSecPrisJntData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVSECPRISJNTDATA_H__984CD364_28CF_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVSECPRISJNTDATA_H__984CD364_28CF_11D4_A7DF_0000E8978554__INCLUDED_

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
} structSecondaryPrismaticJointData;

class CdmvSecPrisJntData : public CdmvSecJointData  
{
public:
	void SetSecPrismaticJointData (const structSecondaryPrismaticJointData* pstrtSecondaryPrismaticJointData);
	void GetSecPrismaticJointData (structSecondaryPrismaticJointData* pstrtSecondaryPrismaticJointData) const;
	void SetConstraintParams (double dLinearConstraintSpring, double dLinearConstraintDamper, double dAngularConstraintSpring, double dAngularConstraintDamper);
	CdmvSecPrisJntData();
	virtual ~CdmvSecPrisJntData();
protected:
	structSecondaryPrismaticJointData m_strtSecondaryPrismaticJointData;

};

#endif // !defined(AFX_DMVSECPRISJNTDATA_H__984CD364_28CF_11D4_A7DF_0000E8978554__INCLUDED_)
