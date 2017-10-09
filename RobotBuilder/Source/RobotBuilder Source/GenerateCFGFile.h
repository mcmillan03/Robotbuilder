// GenerateCFGFile.h: interface for the CGenerateCFGFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERATECFGFILE_H__2B1F6321_1D30_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_GENERATECFGFILE_H__2B1F6321_1D30_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DMViewerDoc.h"
#include "dmvCFGData.h"
#include "wt.h"

#include <fstream> // for ostream
using namespace std; 

class CGenerateCFGFile  
{
public:
	static void OutputFileHeader (ostream &strmCFG);
	static BOOL CreateCFGFile (CString strFile, const CdmvCFGData* pCFGData);
	CGenerateCFGFile();
	virtual ~CGenerateCFGFile();

};

#endif // !defined(AFX_GENERATECFGFILE_H__2B1F6321_1D30_11D4_A7DF_0000E8978554__INCLUDED_)
