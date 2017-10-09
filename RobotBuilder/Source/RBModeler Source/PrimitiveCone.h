// PrimitiveCone.h: interface for the CPrimitiveCone class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMITIVECONE_H__19D68AFA_9CEF_49E6_8266_2E45228B7141__INCLUDED_)
#define AFX_PRIMITIVECONE_H__19D68AFA_9CEF_49E6_8266_2E45228B7141__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CONE_HEIGHT_MIN WTK_MIN
#define CONE_HEIGHT_MAX 1.0e6f
#define CONE_RADIUS_MIN WTK_MIN
#define CONE_RADIUS_MAX 1.0e6f
#define CONE_TESS_MIN	3
#define CONE_TESS_MAX	1e6

#include "Primitive.h"

typedef struct
{
	double dHeight;
	double dRadius;
	int nTess;
	BOOL bRenderBothSides;
} structPrimitiveConeData;

class CPrimitiveCone : public CPrimitive  
{
public:
	void GetInertiaTensor (double cIcg[3][3]) const;
	void GetCenterOfGravity (double dPos[3]) const;
	void SetPrimitiveConeData (const structPrimitiveConeData* pstrtPrimitiveConeData);
	void GetPrimitiveConeData (structPrimitiveConeData* pstrtPrimitiveCodeData) const;
	CPrimitiveCone();
	virtual ~CPrimitiveCone();
protected:
	structPrimitiveConeData m_strtPrimitiveConeData;
};

#endif // !defined(AFX_PRIMITIVECONE_H__19D68AFA_9CEF_49E6_8266_2E45228B7141__INCLUDED_)
