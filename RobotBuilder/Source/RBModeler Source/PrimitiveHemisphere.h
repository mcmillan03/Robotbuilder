// PrimitiveHemisphere.h: interface for the CPrimitiveHemisphere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMITIVEHEMISPHERE_H__BC2089EC_862D_4984_B740_140696617D3E__INCLUDED_)
#define AFX_PRIMITIVEHEMISPHERE_H__BC2089EC_862D_4984_B740_140696617D3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define HEMISPHERE_RADIUS_MIN	WTK_MIN
#define HEMISPHERE_RADIUS_MAX	1.0e6f
#define HEMISPHERE_LATITUDE_MIN	2
#define HEMISPHERE_LATITUDE_MAX	1e6
#define HEMISPHERE_LONGITUDE_MIN	3
#define HEMISPHERE_LONGITUDE_MAX	1e6

#include "Primitive.h"

typedef struct
{
	double dRadius;
	int nLatitudeCount;
	int nLongitudeCount;
	BOOL bRenderBothSides;
	BOOL bUseGouraudShading;
} structPrimitiveHemisphereData;

class CPrimitiveHemisphere : public CPrimitive  
{
public:
	void GetCenterOfGravity (double dPos[3]) const;
	void GetInertiaTensor (double dIcg[3][3]) const;
	void SetPrimitiveHemisphereData (const structPrimitiveHemisphereData* pstrtPrimitiveHemisphereData);
	void GetPrimitiveHemisphereData (structPrimitiveHemisphereData* pstrtPrimitiveHemisphereData) const;
	CPrimitiveHemisphere();
	virtual ~CPrimitiveHemisphere();
protected:
	structPrimitiveHemisphereData m_strtPrimitiveHemisphereData;
};

#endif // !defined(AFX_PRIMITIVEHEMISPHERE_H__BC2089EC_862D_4984_B740_140696617D3E__INCLUDED_)
