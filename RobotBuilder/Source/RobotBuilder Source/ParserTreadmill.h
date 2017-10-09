// ParserTreadmill.h: interface for the CParserTreadmill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERTREADMILL_H__684FBF6C_C929_401F_A5E3_97A3B8060CEB__INCLUDED_)
#define AFX_PARSERTREADMILL_H__684FBF6C_C929_401F_A5E3_97A3B8060CEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserGeneral.h"
#include "dmvTreadmillData.h"

class CParserTreadmill : public CParserGeneral  
{
public:
	static BOOL ParseTreadmillFile (CString strFile, CdmvTreadmillData* pCdmvTreadmillData);
	CParserTreadmill();
	virtual ~CParserTreadmill();
private:
	static void ValidationError (ifstream & istrmTreadmillFile, int nCurrentLineNumber, CdmvTreadmillData* pCdmvTreadmillData, CString strMessage);
	static BOOL ParseFileVersion1 (ifstream & istrmTreadmillFile, int & rnCurrentLineNumber, CdmvTreadmillData* pCdmvTreadmillData);
	static void FormatError (ifstream & istrmTreadmillFile, int nCurrentLineNumber, CdmvTreadmillData* pCdmvTreadmillData, CString strMessage);
	static void ParseError (ifstream & istrmTreadmillFile, int nCurrentLineNumber, CdmvTreadmillData* pCdmvTreadmillData, CString strMessage);
};

#endif // !defined(AFX_PARSERTREADMILL_H__684FBF6C_C929_401F_A5E3_97A3B8060CEB__INCLUDED_)
