// GenerateEnvironmentFile.h: interface for the CGenerateEnvironmentFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERATEENVIRONMENTFILE_H__860E6183_1B75_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_GENERATEENVIRONMENTFILE_H__860E6183_1B75_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvEnvironmentData.h"

#include <fstream> // for ostream
using namespace std; 

class CGenerateEnvironmentFile  
{
public:
	static BOOL CreateEnvironmentFile (CString strFilePath, CdmvEnvironmentData* pEnvironment);
	CGenerateEnvironmentFile();
	virtual ~CGenerateEnvironmentFile();

protected:
	static void OutputFileHeader (ostream &strmEnvironmentFile, CdmvEnvironmentData* pEnvironment);
};

#endif // !defined(AFX_GENERATEENVIRONMENTFILE_H__860E6183_1B75_11D4_A7DF_0000E8978554__INCLUDED_)
