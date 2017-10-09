// ParserXan.h: interface for the CParserXan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERXAN_H__D2B2173D_F9F1_445E_82EC_68A95D0E4EFF__INCLUDED_)
#define AFX_PARSERXAN_H__D2B2173D_F9F1_445E_82EC_68A95D0E4EFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserGeneral.h"
#include "ModelParserTypes.h"
#include <wt.h>

class CParserXan : public CParserGeneral  
{
public:
	CParserXan();
	virtual ~CParserXan();
	static BOOL ParseXanFileAndBuildGeometry (CString strFile, WTgeometry **pwtGeometry);
private:
	static void BuildGeometry (structMaterial *pstrtMaterial, int nNumberOfVertices, const structVertex *pstrtVertices, int nNumberOfFaces, const structFace *pstrtFaces,
							   WTgeometry **pwtgeometry);
	static void FreeAllocatedMemory (structVertex *pstrtVertices, int nNumberOfFaces, structFace *pstrtFaces);
	static void ValidationError (ifstream & istrmXanFile, int nCurrentLineNumber, CString strFilename, CString strMessage);
	static void FormatError (ifstream & istrmXanFile, int nCurrentLineNumber, CString strFilename, CString strMessage);
	static void ParseError (ifstream & istrmXanFile, int nCurrentLineNumber, CString strFilename, CString strMessage);

};

#endif // !defined(AFX_PARSERXAN_H__D2B2173D_F9F1_445E_82EC_68A95D0E4EFF__INCLUDED_)
