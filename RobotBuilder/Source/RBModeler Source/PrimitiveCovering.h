// PrimitiveCovering.h: interface for the CPrimitiveCovering class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMITIVECOVERING_H__EA381421_5797_4BB8_A9F5_4774EB7A6DD9__INCLUDED_)
#define AFX_PRIMITIVECOVERING_H__EA381421_5797_4BB8_A9F5_4774EB7A6DD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum {SIMPLE_COLOR, TEXTURE} enumCovering;

typedef struct
{
	enumCovering covCovering;
	COLORREF crColor;
	CString strTextureFile;
	CString strTexturePath;
} structPrimitiveCoveringData;


class CPrimitiveCovering  
{
public:
	void GetPrimitiveCoveringData (structPrimitiveCoveringData* pstrtPrimitiveCoveringData) const;
	void SetPrimitiveCoveringData (const structPrimitiveCoveringData* pstrtPrimitiveCoveringData);
	CPrimitiveCovering();
	virtual ~CPrimitiveCovering();
protected:
	structPrimitiveCoveringData m_strtPrimitiveCoveringData;

};

#endif // !defined(AFX_PRIMITIVECOVERING_H__EA381421_5797_4BB8_A9F5_4774EB7A6DD9__INCLUDED_)
