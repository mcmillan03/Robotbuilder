// PrimitiveScale1.h: interface for the CPrimitiveScale class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMITIVESCALE1_H__75C76A54_7A09_431E_9948_2CFADE95B12F__INCLUDED_)
#define AFX_PRIMITIVESCALE1_H__75C76A54_7A09_431E_9948_2CFADE95B12F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct
{
	double dXScale;
	double dYScale;
	double dZScale;
} structPrimitiveScaleData;

// Notes:
// The data needs to be saved in an absolute format to persist between sessions.  WTK, though
// makes changes relative to the current state so that information needs to be stored too.

class CPrimitiveScale  
{
public:
	void GetPrimitiveScaleRelativeData (structPrimitiveScaleData* pstrtPrimitiveScaleRelativeData) const;
	void SetPrimitiveScaleAbsoluteData (const structPrimitiveScaleData* pstrtPrimitiveScaleData);
	void AlterScale (double dScaleFactor, UINT uAxis);
	CPrimitiveScale();
	virtual ~CPrimitiveScale();
	void ResetRelativeScaleData();
	void GetPrimitiveScaleAbsoluteData(structPrimitiveScaleData *pstrtPrimitiveScaleAbsoluteData) const;
private:
	structPrimitiveScaleData m_strtPrimitiveScaleRelativeData;
	structPrimitiveScaleData m_strtPrimitiveScaleAbsoluteData;
};

#endif // !defined(AFX_PRIMITIVESCALE1_H__75C76A54_7A09_431E_9948_2CFADE95B12F__INCLUDED_)
