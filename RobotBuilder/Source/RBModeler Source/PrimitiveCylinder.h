// PrimitiveCylinder.h: interface for the CPrimitiveCylinder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMITIVECYLINDER_H__F388A1E8_6B18_44C5_A3C3_4FDF18384659__INCLUDED_)
#define AFX_PRIMITIVECYLINDER_H__F388A1E8_6B18_44C5_A3C3_4FDF18384659__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CYLINDER_RADIUS_MIN	WTK_MIN
#define CYLINDER_RADIUS_MAX	1.0e6f
#define CYLINDER_HEIGHT_MIN	WTK_MIN
#define CYLINDER_HEIGHT_MAX	1.0e6f
#define CYLINDER_TESS_MIN	3
#define CYLINDER_TESS_MAX	1e6


#include "Primitive.h"

typedef struct
{
	double dHeight;
	double dRadius;
	int nTess; // number of polygons to approximate the cylinder
	BOOL bUseGouraudShading;
	BOOL bRenderBothSides;
} structPrimitiveCylinderData;


class CPrimitiveCylinder : public CPrimitive  
{
public:
	void GetCenterOfGravity (double dPos[3]) const;
	void GetInertiaTensor (double dIcg[3][3]) const;
	void SetPrimitiveCylinderData (const structPrimitiveCylinderData* pstrtPrimitiveCylinderData);
	void GetPrimitiveCylinderData (structPrimitiveCylinderData *pstrtPrimitiveCylinderData) const;
	CPrimitiveCylinder();
	virtual ~CPrimitiveCylinder();
protected:
	structPrimitiveCylinderData m_strtPrimitiveCylinderData;
};

#endif // !defined(AFX_PRIMITIVECYLINDER_H__F388A1E8_6B18_44C5_A3C3_4FDF18384659__INCLUDED_)
