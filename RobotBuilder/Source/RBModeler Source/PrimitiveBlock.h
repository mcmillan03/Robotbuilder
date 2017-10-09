// PrimitiveBlock.h: interface for the CPrimitiveBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMITIVEBLOCK_H__9BBB4C2A_2188_4D04_8F3D_8F5FC23C2577__INCLUDED_)
#define AFX_PRIMITIVEBLOCK_H__9BBB4C2A_2188_4D04_8F3D_8F5FC23C2577__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Primitive.h"

#define BLOCK_LENGTH_MIN	WTK_MIN
#define BLOCK_LENGTH_MAX	1.0e6f

typedef struct
{
	double dLengthX;
	double dLengthY;
	double dLengthZ;
	BOOL bRenderBothSides;
} structPrimitiveBlockData;

class CPrimitiveBlock : public CPrimitive  
{
public:
	void GetCenterOfGravity (double dPos[3]) const;
	void GetInertiaTensor (double dIcg[3][3]) const;
	void SetPrimitiveBlockData (const structPrimitiveBlockData* pstrtPrimitiveBlockData);
	void GetPrimitiveBlockData (structPrimitiveBlockData* pstrtPrimitiveBlockData) const;
	CPrimitiveBlock();
	virtual ~CPrimitiveBlock();
protected:
	structPrimitiveBlockData m_strtPrimitiveBlockData;
};

#endif // !defined(AFX_PRIMITIVEBLOCK_H__9BBB4C2A_2188_4D04_8F3D_8F5FC23C2577__INCLUDED_)
