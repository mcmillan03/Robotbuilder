// ParserGeneral.h: interface for the CParserGeneral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERGENERAL_H__9DACDE45_D678_47C2_BEB4_B5E71E0534B1__INCLUDED_)
#define AFX_PARSERGENERAL_H__9DACDE45_D678_47C2_BEB4_B5E71E0534B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
#include <fstream>
#include <string>

#define RB_FILE_MAX_LINE	256
#define RB_FILE_COMMENT_CHAR	'#'

using namespace std;

class CParserGeneral  
{
public:
	CParserGeneral();
	virtual ~CParserGeneral();
protected:
	static BOOL ReadStringInDoubleQuotes (ifstream & istrmFile, string & strField);
	static string StripQuotes (string strStringInQuotes);
	static void EatWhite (ifstream &istrmModelFile);
	static BOOL GotoNextData (ifstream &istrmModelFile, int & rnCurrentLineNumber);
};

#endif // !defined(AFX_PARSERGENERAL_H__9DACDE45_D678_47C2_BEB4_B5E71E0534B1__INCLUDED_)
