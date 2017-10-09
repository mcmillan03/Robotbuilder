// GenerateTreadmillFile.h: interface for the CGenerateTreadmillFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERATETREADMILLFILE_H__424BE923_6A93_42C4_B78D_6D39B785FBBD__INCLUDED_)
#define AFX_GENERATETREADMILLFILE_H__424BE923_6A93_42C4_B78D_6D39B785FBBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvTreadmillData.h"

class CGenerateTreadmillFile  
{
public:
	static BOOL CreateTreadmillFile (CString strFile, const CdmvTreadmillData* pCdmvTreadmillData);
	CGenerateTreadmillFile();
	virtual ~CGenerateTreadmillFile();

};

#endif // !defined(AFX_GENERATETREADMILLFILE_H__424BE923_6A93_42C4_B78D_6D39B785FBBD__INCLUDED_)
