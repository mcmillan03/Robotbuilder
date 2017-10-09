// GenerateTouch.cpp: implementation of the CGenerateTouch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "GenerateTouch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGenerateTouch::CGenerateTouch()
{

}

CGenerateTouch::~CGenerateTouch()
{

}

// Touches a file
BOOL CGenerateTouch::Touch(CString strFilePath)
{
	// Open the file (implicitly clear it if it already exists)
	ofstream strmFile;
	strmFile.open (strFilePath);
	int nIsOpen = strmFile.is_open ();
	if (!nIsOpen)
		return FALSE;
 	ASSERT (strmFile != NULL);

	// Close the file
	strmFile.close ();

	return TRUE;
}
