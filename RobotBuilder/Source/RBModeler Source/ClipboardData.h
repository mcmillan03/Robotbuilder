// ClipboardData.h: interface for the CClipboardData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIPBOARDDATA_H__4C598822_85B8_4037_B48F_99EA07E4AD47__INCLUDED_)
#define AFX_CLIPBOARDDATA_H__4C598822_85B8_4037_B48F_99EA07E4AD47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h> // array template support
#include "Primitive.h"

class CClipboardData  
{
public:
	CPrimitive* GetPrimitiveCopy(int nIndex);
	void AddPrimitive (CPrimitive* pPrimitive);
	int GetNumberOfPrimitives ();
	void EmptyAndDeallocateClipboardData ();
	CClipboardData();
	virtual ~CClipboardData();
	CArray <CPrimitive *, CPrimitive *> m_arrayPrimitives;
};

#endif // !defined(AFX_CLIPBOARDDATA_H__4C598822_85B8_4037_B48F_99EA07E4AD47__INCLUDED_)
