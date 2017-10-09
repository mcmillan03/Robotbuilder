// ParserEnvironment.h: interface for the CParserEnvironment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERENVIRONMENT_H__FD1B48C9_7276_4890_9771_AF93713B39BC__INCLUDED_)
#define AFX_PARSERENVIRONMENT_H__FD1B48C9_7276_4890_9771_AF93713B39BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvEnvironmentData.h"
#include "ParserGeneral.h"

class CParserEnvironment : public CParserGeneral
{
public:
	static BOOL ParseEnvironmentFile (CString strFile, CdmvEnvironmentData** ppCdmvEnvironmentData);
	CParserEnvironment();
	virtual ~CParserEnvironment();

private:
	static void ParseError (ifstream & istrmEnvFile, int nCurrentLineNumber, 
		CdmvEnvironmentData ** ppCdmvEnvironmentData, CString strMessage);
	static void FormatError (ifstream & istrmEnvFile, int nCurrentLineNumber,
		CdmvEnvironmentData ** ppCdmvEnvironmentData, CString strMessage);
	static BOOL ParseEnvironmentFileVersion1 (ifstream& istrmEnvFile, int & rnCurrentLineNumber, 
		CdmvEnvironmentData	**ppCdmvEnvironmentData);
	static void ValidationError(ifstream & istrmEnvFile, int nCurrentLineNumber,
										CdmvEnvironmentData ** ppCdmvEnvironmentData,
										CString strMessage);
};

#endif // !defined(AFX_PARSERENVIRONMENT_H__FD1B48C9_7276_4890_9771_AF93713B39BC__INCLUDED_)
