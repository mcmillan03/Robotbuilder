// GeneratePlaybackFile.h: interface for the CGeneratePlaybackFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERATEPLAYBACKFILE_H__CDEEC5D3_E7EF_4361_A12C_97AE9CB24AB6__INCLUDED_)
#define AFX_GENERATEPLAYBACKFILE_H__CDEEC5D3_E7EF_4361_A12C_97AE9CB24AB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PlaybackData.h"

#include <fstream> // for ostream
using namespace std; 

class CGeneratePlaybackFile  
{
public:
	static BOOL CreatePlaybackFile (CString strFilePath, CPlaybackData* pPlaybackData);
	CGeneratePlaybackFile();
	virtual ~CGeneratePlaybackFile();

};

#endif // !defined(AFX_GENERATEPLAYBACKFILE_H__CDEEC5D3_E7EF_4361_A12C_97AE9CB24AB6__INCLUDED_)
