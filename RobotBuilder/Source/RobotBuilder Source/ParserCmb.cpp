// ParserCmb.cpp: implementation of the CParserCmb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "ParserCmb.h"
#include "ParserXan.h"
#include "FindFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserCmb::CParserCmb()
{

}

CParserCmb::~CParserCmb()
{

}

BOOL CParserCmb::ParseCmbFileAndBuildGeometry (CString strFile, WTnode **pwtmovsepnode)
{
	// Line Number
	int nCurrentLineNumber = 1;

	// Open the file
	ifstream istrmCmbFile (strFile);
	if (!istrmCmbFile) 
	{
		CString strError;
		strError.Format ("Failed to open %s.", strFile);
		AfxMessageBox (strError);
		return FALSE;
	}

	// Advance to the first token in case it starts as blanks.
	if (!GotoNextData (istrmCmbFile, nCurrentLineNumber))
	{
		FormatError(istrmCmbFile, nCurrentLineNumber, strFile,
			"Error before first field.");
		return FALSE;
	}

	// Read in number of files
	int nNumberOfFiles;
	istrmCmbFile >> nNumberOfFiles;
	if (!istrmCmbFile.good ())
	{
		ParseError (istrmCmbFile, nCurrentLineNumber, strFile,
			"Expected: <int - file count>");
		return FALSE;
	}
	// Validate the data
	if (nNumberOfFiles < MODEL_CMB_FILE_COUNT_MIN || nNumberOfFiles > MODEL_CMB_FILE_COUNT_MAX)
	{
		CString strError;
		strError.Format ("%d <= Vertices <= %d", MODEL_CMB_FILE_COUNT_MIN, MODEL_CMB_FILE_COUNT_MAX);
		ValidationError (istrmCmbFile, nCurrentLineNumber, strFile, strError);
		return FALSE;		
	}
	if (!GotoNextData (istrmCmbFile, nCurrentLineNumber))
	{
		FormatError (istrmCmbFile, nCurrentLineNumber, strFile,
			"Error after File Count field.");
		return FALSE;			
	}

	// Read the files into an array
	CStringArray arrayFiles;
	int i;
	for (i = 0; i < nNumberOfFiles; i++)
	{
		string strCurrentGraphicsFile;
		if (!ReadStringInDoubleQuotes (istrmCmbFile, strCurrentGraphicsFile))
		{
			ParseError (istrmCmbFile, nCurrentLineNumber, strFile,
				"Expected: \"<graphics_file_string>\"");
			return FALSE;
		}
		if (!istrmCmbFile.good ())
		{
			ParseError (istrmCmbFile, nCurrentLineNumber, strFile,
				"Expected: \"<graphics_file_string>\"");
			return FALSE;
		}
		// Save the data
		arrayFiles.Add (strCurrentGraphicsFile.c_str ());

		// Don't do this on the last one in case the file doesn't have a trailing endl
		if (i < nNumberOfFiles - 1)
		{
			if (!GotoNextData (istrmCmbFile, nCurrentLineNumber))
			{
				FormatError (istrmCmbFile, nCurrentLineNumber, strFile,
					"Error after Graphics File field.");
				return FALSE;			
			}
		}
	}

	// Close the file
	istrmCmbFile.close ();

	// Build it
	BuildGeometry (&arrayFiles, pwtmovsepnode);
		
	return TRUE;
}

void CParserCmb::ValidationError(ifstream &istrmCmbFile, int nCurrentLineNumber, 
									   CString strFilename, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Validation error in %s on line %d.\n%s",
			strFilename, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmCmbFile.close ();
}

void CParserCmb::ParseError(ifstream &istrmCmbFile, int nCurrentLineNumber, 
									   CString strFilename, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Parse error in %s on line %d.\n%s",
			strFilename, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmCmbFile.close ();
}

void CParserCmb::FormatError(ifstream &istrmCmbFile, int nCurrentLineNumber, 
									   CString strFilename, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Format error in %s on line %d.\n%s",
			strFilename, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmCmbFile.close ();
}

void CParserCmb::BuildGeometry (CStringArray *parrayFiles, WTnode **pwtmovsepnode)
{
	// Create the node with no parent and add the children
	*pwtmovsepnode = WTmovsepnode_new (NULL);

	// Go through and build each xan
	int nCounter;
	for (nCounter = 0; nCounter < parrayFiles->GetSize (); nCounter++)
	{
		WTgeometry* wtgeometry;
		// Try to find the file - Note if it fails, the next Parser function
		// will provide an error dialog that the file can't be found
		CString strModelFile = parrayFiles->GetAt (nCounter); // Copy the model file
		CString strModelPath; // Holds path to the model
		BOOL bFindFile = CFindFile::FindFile (MODEL_FILE_TYPE, 
			strModelFile, strModelPath);
		if (CParserXan::ParseXanFileAndBuildGeometry (strModelPath + strModelFile,
			&wtgeometry)) // if this fails, the xan parser will show an error to the user
		{
			// Place geometry in a geometry node
			WTnode* wtgeometrynode = WTgeometrynode_new (NULL, wtgeometry);
			ASSERT (wtgeometrynode);

			// Add as a child
			FLAG flagStatus = WTnode_addchild (*pwtmovsepnode, wtgeometrynode);
			ASSERT (flagStatus);
		}
	}

}
