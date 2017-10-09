// ParserDat.h: interface for the CParserDat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERDAT_H__BE8BEF68_ED06_464D_B619_753B34E353A7__INCLUDED_)
#define AFX_PARSERDAT_H__BE8BEF68_ED06_464D_B619_753B34E353A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserGeneral.h"
#include "ModelParserTypes.h"
#include <wt.h>

class CParserDat : public CParserGeneral  
{
public:
	CParserDat();
	virtual ~CParserDat();
	static BOOL ParseDatFileAndBuildGeometry (CString strFile, WTgeometry **pwtGeometry);
private:
	static void BuildGeometry (int nNumberOfVertices, const structVertex *pstrtVertices, int nNumberOfFaces, const structFace *pstrtFaces,
							   WTgeometry **pwtgeometry);
	static void FreeAllocatedMemory (structVertex *pstrtVertices, int nNumberOfFaces, structFace *pstrtFaces);
	static void ValidationError (ifstream & istrmXanFile, int nCurrentLineNumber, CString strFilename, CString strMessage);
	static void FormatError (ifstream & istrmXanFile, int nCurrentLineNumber, CString strFilename, CString strMessage);
	static void ParseError (ifstream & istrmXanFile, int nCurrentLineNumber, CString strFilename, CString strMessage);

};

#endif // !defined(AFX_PARSERDAT_H__BE8BEF68_ED06_464D_B619_753B34E353A7__INCLUDED_)
