// GenerateTouch.h: interface for the CGenerateTouch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERATETOUCH_H__ABF32796_7E3A_437B_9AD4_E4EB90BC4B14__INCLUDED_)
#define AFX_GENERATETOUCH_H__ABF32796_7E3A_437B_9AD4_E4EB90BC4B14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGenerateTouch  
{
public:
	static BOOL Touch (CString strFilePath);
	CGenerateTouch();
	virtual ~CGenerateTouch();

};

#endif // !defined(AFX_GENERATETOUCH_H__ABF32796_7E3A_437B_9AD4_E4EB90BC4B14__INCLUDED_)
