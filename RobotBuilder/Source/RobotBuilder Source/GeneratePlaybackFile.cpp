// GeneratePlaybackFile.cpp: implementation of the CGeneratePlaybackFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "GeneratePlaybackFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <wt.h> // WTK stuff

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeneratePlaybackFile::CGeneratePlaybackFile()
{

}

CGeneratePlaybackFile::~CGeneratePlaybackFile()
{

}

BOOL CGeneratePlaybackFile::CreatePlaybackFile(CString strFilePath, CPlaybackData *pPlaybackData)
{
	ASSERT (AfxIsValidAddress (pPlaybackData, sizeof(CPlaybackData)));

	ofstream strmPlaybackFile;
	strmPlaybackFile.open (strFilePath);
	int nIsOpen = strmPlaybackFile.is_open ();
	if (!nIsOpen)
		return FALSE;
 	ASSERT (strmPlaybackFile != NULL);

	// Pick up the header information about the playback file
	int nNumberOfItems;
	CString strArticulationFile, strEnvironmentFile;
	FILETIME filetimeArticulation, filetimeEnvironment;
	pPlaybackData->GetPlaybackInfo  (nNumberOfItems, strArticulationFile, strEnvironmentFile, 
		filetimeArticulation, filetimeEnvironment);

	// Output a comment line describing the file
	strmPlaybackFile << "# Robotbuilder playback file\n\n";

	// Output a version
	strmPlaybackFile << "Version 1\n\n";

	// Output information about the playback
	strmPlaybackFile << "Articulation_File\t" << "\"" << LPCTSTR(strArticulationFile) << "\"" << endl;
	strmPlaybackFile << "Environment_File\t" << "\"" << LPCTSTR(strEnvironmentFile) << "\"" << endl;
	strmPlaybackFile << "Articulation_File_Time\t" << filetimeArticulation.dwHighDateTime << '\t' <<
		filetimeArticulation.dwLowDateTime << endl;
	strmPlaybackFile << "Environment_File_Time\t" << filetimeEnvironment.dwHighDateTime << '\t' <<
		filetimeEnvironment.dwLowDateTime << endl;
	strmPlaybackFile << "Number_Of_Items\t" << nNumberOfItems << endl << endl;

	// Reset the playback to the beginning
	pPlaybackData->ResetPlayback ();

	// Output each snapshot
	while (pPlaybackData->PeekNextSnapShotTime () != PLAYBACK_END)
	{
		// Get the next snap shot
		double dTime;
		VERIFY(pPlaybackData->GetNextSnapShot (dTime));

		// Output the time stamp
		strmPlaybackFile << dTime << endl;

		// Output the position and orientation for each itme
		int i;
		for (i = 0; i < nNumberOfItems; i++)
		{
			WTp3 wtp3Position;
			WTm3 wtm3Orientation;

			// Pick up the data
			pPlaybackData->GetNextSnapShotItem (wtp3Position, wtm3Orientation);

			// Output it to the file
			strmPlaybackFile << wtp3Position[0] << "\t" <<
				wtp3Position[1] << "\t" << wtp3Position[2] << "\t";
			int j,k;
			for (j = 0; j < 3; j++)
				for (k = 0; k < 3; k++)
					strmPlaybackFile << wtm3Orientation[j][k] << "\t";

			// End the line
			strmPlaybackFile << endl;
		}
	}


	// Close the stream
	strmPlaybackFile.close ();

	return TRUE;
}
