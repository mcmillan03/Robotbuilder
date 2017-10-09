// ParserTerrain.h: interface for the CParserTerrain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERTERRAIN_H__4B9F0F9C_290B_4DBE_BA4E_2C39505FBFE5__INCLUDED_)
#define AFX_PARSERTERRAIN_H__4B9F0F9C_290B_4DBE_BA4E_2C39505FBFE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserGeneral.h"
#include "dmvTerrainData.h"

class CParserTerrain : public CParserGeneral
{
public:
	static BOOL ParseTerrainFile (CString strFile, CdmvTerrainData* pCdmvTerrainData);
	CParserTerrain();
	virtual ~CParserTerrain();
private:
	static void ValidationError (ifstream & istrmTerrainFile, int nCurrentLineNumber, 
		CdmvTerrainData *pCdmvTerrainData, CString strMessage);
	static BOOL ParseFileVersion1 (ifstream & istrmTerrainFile, int & rnCurrentLineNumber, CdmvTerrainData* pCdmvTerrainData);
  static BOOL ParseFileVersion2 (ifstream & istrmTerrainFile, int & rnCurrentLineNumber, CdmvTerrainData* pCdmvTerrainData);
	static void FormatError (ifstream & istrmTerrainFile, int nCurrentLineNumber, 
		CdmvTerrainData *pCdmvTerrainData,  CString strMessage);
	static void ParseError (ifstream & istrmTerrainFile, int nCurrentLineNumber, 
		CdmvTerrainData *pCdmvTerrainData,  CString strMessage);
};

#endif // !defined(AFX_PARSERTERRAIN_H__4B9F0F9C_290B_4DBE_BA4E_2C39505FBFE5__INCLUDED_)
