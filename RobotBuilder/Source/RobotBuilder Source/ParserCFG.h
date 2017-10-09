// ParserCFG.h: interface for the CParserCFG class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERCFG_H__285067B5_BC1F_49E8_9299_76A35BCD9107__INCLUDED_)
#define AFX_PARSERCFG_H__285067B5_BC1F_49E8_9299_76A35BCD9107__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserGeneral.h"
#include "dmvCFGData.h"
#include "wt.h"

class CParserCFG : public CParserGeneral  
{
public:
	static BOOL ParseCFGFile(CString strFile, CdmvCFGData *pCdmvCFGData);
	CParserCFG();
	virtual ~CParserCFG();

private:
	static void ValidationError (ifstream & istrmCFGFile, int nCurrentLineNumber, CString strMessage);
	static BOOL ParseFileVersion1 (ifstream & istrmCFGFile, int & rnCurrentLineNumber, CdmvCFGData* pCdmvCFGData);
	static BOOL ParseFileVersion2 (ifstream & istrmCFGFile, int & rnCurrentLineNumber, CdmvCFGData* pCdmvCFGData);
	static BOOL ParseFileVersion3 (ifstream & istrmCFGFile, int & rnCurrentLineNumber, CdmvCFGData* pCdmvCFGData);
	static void FormatError (ifstream & istrmCFGFile, int nCurrentLineNumber, CString strMessage);
	static void ParseError (ifstream & istrmCFGFile, int nCurrentLineNumber, CString strMessage);
};

#endif // !defined(AFX_PARSERCFG_H__285067B5_BC1F_49E8_9299_76A35BCD9107__INCLUDED_)
