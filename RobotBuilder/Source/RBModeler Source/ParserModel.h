// ParserModel.h: interface for the CParserModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSER_MODEL_H__B826F491_7B13_485D_957C_49EE34CBC85F__INCLUDED_)
#define AFX_PARSER_MODEL_H__B826F491_7B13_485D_957C_49EE34CBC85F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Model.h"
#include "ParserGeneral.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

class CParserModel : public CParserGeneral  
{
public:
	static BOOL ParseModelFile (CString strFilePath, CModel** ppModel);
	CParserModel();
	virtual ~CParserModel();

protected:
	static BOOL ParsePrimitiveMass (CPrimitive* pPrimitive, ifstream &istrmModelFile,
									 CModel **ppModel, int &rnCurrentLineNumber, CString strFile);
	static BOOL ParsePrimitiveScale (CPrimitiveScale* pPrimitiveScale, ifstream &istrmModelFile,
									 CModel **ppModel, int &rnCurrentLineNumber, CString strFile);
	static BOOL ParsePrimitiveName (CPrimitive* pPrimitive, ifstream& istrmModelFile,
									 CModel **ppModel, int &rnCurrentLineNumber, CString strFile);
	static BOOL ParsePrimitiveCovering (CPrimitiveCovering* pPrimitiveCovering, ifstream& strmModelFile,
									 CModel **ppModel, int &rnCurrentLineNumber, CString strFile);
	static BOOL ParsePrimitivePlacement (CPrimitivePlacement* pPrimitivePlacement, ifstream &istrmModelFile,
									 CModel **ppModel, int &rnCurrentLineNumber, CString strFile);

	static BOOL ParsePrimitiveTruncatedCone (CModel **ppModel, ifstream &istrmModelFile, int &rnCurrentLineNumber, CString strFile);
	static BOOL ParsePrimitiveHemisphere (CModel **ppModel, ifstream &istrmModelFile, int &rnCurrentLineNumber, CString strFile);
	static BOOL ParsePrimitiveCone (CModel **ppModel, ifstream &istrmModelFile, int &rnCurrentLineNumber, CString strFile);
	static BOOL ParsePrimitiveCylinder (CModel **ppModel, ifstream &istrmModelFile, int &rnCurrentLineNumber, CString strFile);
	static BOOL ParsePrimitiveBlock (CModel **ppModel, ifstream &istrmModelFile, int &rnCurrentLineNumber, CString strFile);
	static BOOL ParsePrimitiveSphere (CModel **ppModel, ifstream &istrmModelFile, int &rnCurrentLineNumber, CString strFile);
	static void ValidationError(ifstream &istrmModelFile, int nCurrentLineNumber,
						   CModel **ppModel, CString strMessage, CString strFile);
	static void FormatError(ifstream &istrmModelFile, int nCurrentLineNumber,
						   CModel **ppModel, CString strMessage, CString strFile);
	static void ParseError(ifstream &istrmModelFile, int nCurrentLineNumber,
						   CModel **ppModel, CString strMessage, CString strFile);

};

#endif // !defined(AFX_PARSER_MODEL_H__B826F491_7B13_485D_957C_49EE34CBC85F__INCLUDED_)
