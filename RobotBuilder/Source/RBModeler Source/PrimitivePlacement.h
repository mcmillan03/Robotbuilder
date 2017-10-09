// PrimitivePlacement.h: interface for the CPrimitivePlacement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMITIVEPLACEMENT_H__03DC321E_0C18_488B_A296_6DDEA6124C54__INCLUDED_)
#define AFX_PRIMITIVEPLACEMENT_H__03DC321E_0C18_488B_A296_6DDEA6124C54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPrimitive;

enum {MODIFY_WRT_UNIVERSE, MODIFY_WRT_LOCAL, MODIFY_WRT_PRIMITIVE};


typedef struct
{
	double dTranslationX;
	double dTranslationY;
	double dTranslationZ;
	double dRotationMatrix[3][3];
} structPrimitivePlacementData;

class CPrimitivePlacement  
{
public:
	void AlterSpatialTransform (double dAngle, UINT uAxis, UINT uWithRespectToType, CPrimitive* pPrimitive);
	void SetPrimitivePlacementData (const structPrimitivePlacementData* pstrtPrimitivePlacementData);
	void GetPrimitivePlacementData (structPrimitivePlacementData* pstrtPrimitivePlacementData) const;
	void AlterTranslation (double dChange, UINT uAxis, 
		UINT uWithRespectToType, CPrimitive* pPrimitive);
	void AlterRotation (double dAngle, UINT uAxis, 
		UINT uWithRespectToType, CPrimitive* pPrimitive);
	CPrimitivePlacement();
	virtual ~CPrimitivePlacement();
protected:
	structPrimitivePlacementData m_strtPrimitivePlacementData;

};

#endif // !defined(AFX_PRIMITIVEPLACEMENT_H__03DC321E_0C18_488B_A296_6DDEA6124C54__INCLUDED_)
