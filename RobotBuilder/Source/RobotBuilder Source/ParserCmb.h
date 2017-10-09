// ParserCmb.h: interface for the CParserCmb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERCMB_H__DAC1F88A_EC2F_4CA3_A198_860970E3E144__INCLUDED_)
#define AFX_PARSERCMB_H__DAC1F88A_EC2F_4CA3_A198_860970E3E144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserGeneral.h"
#include "ModelParserTypes.h"
#include <wt.h>

class CParserCmb : public CParserGeneral  
{
public:
	CParserCmb();
	virtual ~CParserCmb();
	static BOOL ParseCmbFileAndBuildGeometry (CString strFile, WTnode **pwtmovsepnode);
private:
	static void BuildGeometry (CStringArray *parrayFiles, WTnode **pwtmovsepnode);
	static void ValidationError (ifstream & istrmCmbFile, int nCurrentLineNumber, CString strFilename, CString strMessage);
	static void FormatError (ifstream & istrmCmbFile, int nCurrentLineNumber, CString strFilename, CString strMessage);
	static void ParseError (ifstream & istrmCmbFile, int nCurrentLineNumber, CString strFilename, CString strMessage);


};

#endif // !defined(AFX_PARSERCMB_H__DAC1F88A_EC2F_4CA3_A198_860970E3E144__INCLUDED_)
