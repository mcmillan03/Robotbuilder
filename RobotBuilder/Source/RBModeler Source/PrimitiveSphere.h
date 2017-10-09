// PrimitiveSphere.h: interface for the CPrimitiveSphere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMITIVESPHERE_H__0285626A_242D_489D_A3BD_851BF4358F51__INCLUDED_)
#define AFX_PRIMITIVESPHERE_H__0285626A_242D_489D_A3BD_851BF4358F51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Primitive.h"

#define SPHERE_RADIUS_MIN	WTK_MIN
#define SPHERE_RADIUS_MAX  1.0e6f
#define SPHERE_LATITUDE_COUNT_MIN	2
#define SPHERE_LATITUDE_COUNT_MAX	1e6
#define SPHERE_LONGITUDE_COUNT_MIN	3
#define SPHERE_LONGITUDE_COUNT_MAX	1e6

typedef struct
{
	double dRadius;
	int nLatitudeCount;
	int nLongitudeCount;
	BOOL bRenderBothSides;
	BOOL bUseGouraudShading;
} structPrimitiveSphereData;

class CPrimitiveSphere : public CPrimitive 
{
public:
	void GetInertiaTensor (double dIcg[3][3]) const;
	void GetCenterOfGravity (double dPos[3]) const;
	void GetPrimitiveSphereData (structPrimitiveSphereData* pstrtPrimitiveSphereData) const;
	void SetPrimitiveSphereData (const structPrimitiveSphereData* pstrtPrimitiveSphereData);
	CPrimitiveSphere();
	virtual ~CPrimitiveSphere();
protected:
	structPrimitiveSphereData m_strtPrimitiveSphereData;

};

#endif // !defined(AFX_PRIMITIVESPHERE_H__0285626A_242D_489D_A3BD_851BF4358F51__INCLUDED_)
