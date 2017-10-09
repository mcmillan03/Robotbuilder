// ParserPlayback.h: interface for the CParserPlayback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERPLAYBACK_H__6C3B5AFB_1773_45A9_87D5_AC7A7C01855D__INCLUDED_)
#define AFX_PARSERPLAYBACK_H__6C3B5AFB_1773_45A9_87D5_AC7A7C01855D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserGeneral.h"
#include "PlaybackData.h"

class CParserPlayback : public CParserGeneral  
{
public:
	static BOOL ParsePlaybackFile (CString strFile, CPlaybackData *pPlaybackData);
	CParserPlayback();
	virtual ~CParserPlayback();
private:
	static void ValidationError (ifstream & istrmPlaybackFile, int nCurrentLineNumber, 
		CPlaybackData *pPlaybackData, CString strMessage);
	static BOOL ParseFileVersion1 (ifstream & istrmPlaybackFile, int & rnCurrentLineNumber,
		CPlaybackData *pPlaybackData);
	static void FormatError (ifstream & istrmTerrainFile, int nCurrentLineNumber, 
		CPlaybackData *pPlaybackData,  CString strMessage);
	static void ParseError (ifstream & istrmPlaybackFile, int nCurrentLineNumber, 
		CPlaybackData *pPlaybackData,  CString strMessage);
};

#endif // !defined(AFX_PARSERPLAYBACK_H__6C3B5AFB_1773_45A9_87D5_AC7A7C01855D__INCLUDED_)
