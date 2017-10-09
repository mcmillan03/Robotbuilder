// ParserPlayback.cpp: implementation of the CParserPlayback class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "ParserPlayback.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserPlayback::CParserPlayback()
{

}

CParserPlayback::~CParserPlayback()
{

}

void CParserPlayback::ValidationError(ifstream &istrmPlaybackFile, int nCurrentLineNumber,
									 CPlaybackData *pPlaybackData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Validation error in Playback file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	// Reset the playback data to initial values
	pPlaybackData->CleanUp ();
	istrmPlaybackFile.close ();
}

void CParserPlayback::ParseError(ifstream &istrmPlaybackFile, int nCurrentLineNumber,
								CPlaybackData *pPlaybackData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Parse error in Playback file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	// Reset the playback data to initial values
	pPlaybackData->CleanUp ();
	istrmPlaybackFile.close ();
}

void CParserPlayback::FormatError(ifstream &istrmPlaybackFile, int nCurrentLineNumber,
								 CPlaybackData *pPlaybackData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Format error in Playback file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	// Reset the playback data to initial values
	pPlaybackData->CleanUp ();
	istrmPlaybackFile.close ();
}

BOOL CParserPlayback::ParsePlaybackFile (CString strFile, CPlaybackData *pPlaybackData)
{
	// Line Number
	int nCurrentLineNumber = 1;
		
	// Open the file
	ifstream istrmPlaybackFile (strFile);
	if (!istrmPlaybackFile) 
	{
		AfxMessageBox ("Failed to open Playback file.");
		return FALSE;
	}

	// Advance to the first token in case it starts as blanks.
	if (!GotoNextData (istrmPlaybackFile, nCurrentLineNumber))
	{
		FormatError(istrmPlaybackFile, nCurrentLineNumber, pPlaybackData,
			"Error before Version field.");
		return FALSE;
	}

	// Clear any data in there already
	pPlaybackData->CleanUp ();

	// Reset the pointers to the beginning
	pPlaybackData->ResetPlayback ();

	// The first real line will be the format type
	string strLabel;
	int nFormatVersion = 1; // Holds format version of file
	istrmPlaybackFile >> strLabel >> nFormatVersion;

	if (!istrmPlaybackFile.good () || strLabel != "Version")
	{
		ParseError (istrmPlaybackFile, nCurrentLineNumber, pPlaybackData,
			"Expected: Version <integer>");
		return FALSE;
	}
	if (!GotoNextData (istrmPlaybackFile, nCurrentLineNumber))
	{
		FormatError (istrmPlaybackFile, nCurrentLineNumber, pPlaybackData,
			"Error after Version field.");
		return FALSE;			
	}
	
	// Call the correct procedure to parse the detected version type.
	switch (nFormatVersion)
	{
	case 1:
		if (!ParseFileVersion1 (istrmPlaybackFile, nCurrentLineNumber, pPlaybackData))
		{
			return FALSE;
		}
		break;
	default:
		AfxMessageBox ("Unsupported version of Playback file.");
		return FALSE;
	}

	// Close the stream
	istrmPlaybackFile.close ();

	return TRUE;
}

BOOL CParserPlayback::ParseFileVersion1 (ifstream & istrmPlaybackFile, int & rnCurrentLineNumber,
		CPlaybackData *pPlaybackData)
{
	string strLabel;

	// Articulation File
	istrmPlaybackFile >> strLabel;
	if (!istrmPlaybackFile.good () || strLabel != "Articulation_File")
	{
		ParseError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData,
			"Expected: Articulation_File \"<string>\"");
		return FALSE;
	}
	string stringArticulationFile;
	if (!ReadStringInDoubleQuotes (istrmPlaybackFile, stringArticulationFile))
	{
		ParseError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData,
			"Expected: Articulation_File \"<string>\"");
		return FALSE;
	}
	if (!GotoNextData (istrmPlaybackFile, rnCurrentLineNumber))
	{
		FormatError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData,
			"Error after Articulation_File field.");
		return FALSE;			
	}

	// Environment File
	istrmPlaybackFile >> strLabel;
	if (!istrmPlaybackFile.good () || strLabel != "Environment_File")
	{
		ParseError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData,
			"Expected: Environment_File \"<string>\"");
		return FALSE;
	}
	string stringEnvironmentFile;
	if (!ReadStringInDoubleQuotes (istrmPlaybackFile, stringEnvironmentFile))
	{
		ParseError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData,
			"Expected: Environment_File \"<string>\"");
		return FALSE;
	}
	if (!GotoNextData (istrmPlaybackFile, rnCurrentLineNumber))
	{
		FormatError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData,
			"Error after Environment_File field.");
		return FALSE;			
	}

	// Articulation file time
	DWORD dwArticulationFileTimeHigh, dwArticulationFileTimeLow;
	istrmPlaybackFile >> strLabel >> dwArticulationFileTimeHigh >> dwArticulationFileTimeLow;
	if (!istrmPlaybackFile.good () || strLabel != "Articulation_File_Time")
	{
		ParseError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData,
			"Expected: Articulation_File_Time <unsigned int> <unsigned int>");
		return FALSE;
	}
	if (!GotoNextData (istrmPlaybackFile, rnCurrentLineNumber))
	{
		FormatError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData, 
			"Error after Articulation_File_Time field.");
		return FALSE;			
	}

	// Environment file time
	DWORD dwEnvironmentFileTimeHigh, dwEnvironmentFileTimeLow;
	istrmPlaybackFile >> strLabel >> dwEnvironmentFileTimeHigh >> dwEnvironmentFileTimeLow;
	if (!istrmPlaybackFile.good () || strLabel != "Environment_File_Time")
	{
		ParseError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData,
			"Expected: Environment_File_Time <unsigned int> <unsigned int>");
		return FALSE;
	}
	if (!GotoNextData (istrmPlaybackFile, rnCurrentLineNumber))
	{
		FormatError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData, 
			"Error after Environment_File_Time field.");
		return FALSE;			
	}
	
	// Number of items
	int nNumberOfItems;
	istrmPlaybackFile >> strLabel >> nNumberOfItems;
	if (!istrmPlaybackFile.good () || strLabel != "Number_Of_Items")
	{
		ParseError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData,
			"Expected: Number_Of_Items <int>");
		return FALSE;
	}
	if (nNumberOfItems < 1 || nNumberOfItems > INT_MAX)
	{
		CString strError;
		strError.Format ("%d <= Number_Of_Items <= %d", 1, INT_MAX);
		ValidationError (istrmPlaybackFile, rnCurrentLineNumber,  pPlaybackData, strError);
		return FALSE;		
	}
	if (!GotoNextData (istrmPlaybackFile, rnCurrentLineNumber))
	{
		FormatError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData, 
			"Error after Number_Of_Items field.");
		return FALSE;			
	}

	// Copy the file times to the FILETIME structures to pass
	FILETIME filetimeArticulation;
	filetimeArticulation.dwHighDateTime = dwArticulationFileTimeHigh;
	filetimeArticulation.dwLowDateTime = dwArticulationFileTimeLow;
	FILETIME filetimeEnvironment;
	filetimeEnvironment.dwHighDateTime = dwEnvironmentFileTimeHigh;
	filetimeEnvironment.dwLowDateTime = dwEnvironmentFileTimeLow;

	// Initialize the playback
	pPlaybackData->InitializeFromFile (nNumberOfItems, stringArticulationFile.c_str(),
		stringEnvironmentFile.c_str (), filetimeArticulation, filetimeEnvironment);

	// Go through the file picking up the snapshot data
	
	BOOL bContinue = TRUE; // Variable to control when to leave the loop
	while (bContinue)
	{
		// Pick up timestamp
		double dTime;
		istrmPlaybackFile >> dTime;
		if (!istrmPlaybackFile.good () || strLabel != "Number_Of_Items")
		{
			ParseError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData,
				"Expected: <float> (time)");
			return FALSE;
		}
		if (!GotoNextData (istrmPlaybackFile, rnCurrentLineNumber))
		{
			FormatError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData, 
				"Error after time field.");
			return FALSE;			
		}
		// Create a new snapshot
		pPlaybackData->AddSnapShot (dTime);

		// Pick up position and orientation for each item
		int nItemCount;
		for (nItemCount = 0; nItemCount < nNumberOfItems; nItemCount++)
		{
			WTp3 wtp3Position;
			istrmPlaybackFile >> wtp3Position[0] >> wtp3Position[1] >> wtp3Position[2];
			WTm3 wtm3Orientation;
			int i,j;
			for (i = 0; i < 3; i++)
				for (j = 0; j < 3; j++)
					istrmPlaybackFile >> wtm3Orientation[i][j];
			if (!istrmPlaybackFile.good () || strLabel != "Number_Of_Items")
			{
				ParseError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData,
					"Expected: <float> (time)");
				return FALSE;
			}
			if (!GotoNextData (istrmPlaybackFile, rnCurrentLineNumber))
			{
				if (nItemCount == nNumberOfItems - 1)
				{
					// Then at last item - this indicates the end of the file
					bContinue = FALSE;
				}
				else
				{
					// Got an error in the middle of the snapshot data
					FormatError (istrmPlaybackFile, rnCurrentLineNumber, pPlaybackData, 
						"Error after time field.");
					return FALSE;			
				}
			}
			// Save the data
			pPlaybackData->AddItemData (wtp3Position, wtm3Orientation);
		}
	}
	
	return TRUE;
}
