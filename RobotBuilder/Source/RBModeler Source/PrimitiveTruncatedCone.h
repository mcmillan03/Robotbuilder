// PrimitiveTruncatedCone.h: interface for the CPrimitiveTruncatedCone class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMITIVETRUNCATEDCONE_H__89658B88_D16F_4DCF_8CBE_E99B4B98CFA0__INCLUDED_)
#define AFX_PRIMITIVETRUNCATEDCONE_H__89658B88_D16F_4DCF_8CBE_E99B4B98CFA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TRUNCATED_CONE_HEIGHT_MIN	WTK_MIN
#define TRUNCATED_CONE_HEIGHT_MAX	1.0e6f
#define TRUNCATED_CONE_TOP_RADIUS_MIN	WTK_MIN
#define TRUNCATED_CONE_TOP_RADIUS_MAX	1.0e6f
#define TRUNCATED_CONE_BASE_RADIUS_MIN	WTK_MIN
#define TRUNCATED_CONE_BASE_RADIUS_MAX	1.0e6f
#define TRUNCATED_CONE_TESS_MIN	3
#define TRUNCATED_CONE_TESS_MAX	1e6


#include "Primitive.h"

typedef struct
{
	double dHeight;
	double dBaseRadius;
	double dTopRadius;
	int nTess;
	BOOL bUseGouraudShading;
	BOOL bRenderBothSides;
} structPrimitiveTruncatedConeData;


class CPrimitiveTruncatedCone : public CPrimitive  
{
public:
	void GetInertiaTensor(double dIcg[][3]) const;
	void GetCenterOfGravity (double dPos[3]) const;
	void SetPrimitiveTruncatedConeData (const structPrimitiveTruncatedConeData* pstrtPrimitiveTruncatedConeData);
	void GetPrimitiveTruncatedConeData (structPrimitiveTruncatedConeData* pstrtPrimitiveTruncatedConeData) const;
	CPrimitiveTruncatedCone();
	virtual ~CPrimitiveTruncatedCone();
protected:
	structPrimitiveTruncatedConeData m_strtPrimitiveTruncatedConeData;

};

#endif // !defined(AFX_PRIMITIVETRUNCATEDCONE_H__89658B88_D16F_4DCF_8CBE_E99B4B98CFA0__INCLUDED_)
