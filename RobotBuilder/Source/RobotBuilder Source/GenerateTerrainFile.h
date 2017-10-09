// GenerateTerrainFile.h: interface for the CGenerateTerrainFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERATETERRAINFILE_H__4130D8D6_3ACE_4A47_B174_7BA94CFC170A__INCLUDED_)
#define AFX_GENERATETERRAINFILE_H__4130D8D6_3ACE_4A47_B174_7BA94CFC170A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvTerrainData.h"

#include <fstream> // for ostream
using namespace std; 

class CGenerateTerrainFile  
{
public:
	static BOOL CreateTerrainFile (CString strFilePath, CdmvTerrainData* pCdmvTerrainData);
	CGenerateTerrainFile();
	virtual ~CGenerateTerrainFile();
protected:
	static void OutputFileHeader (ostream &strmTerrainFile, CdmvTerrainData* pCdmvTerrainData);

};

#endif // !defined(AFX_GENERATETERRAINFILE_H__4130D8D6_3ACE_4A47_B174_7BA94CFC170A__INCLUDED_)
