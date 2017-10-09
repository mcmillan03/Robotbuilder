// FindFile.cpp: implementation of the CFindFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "FindFile.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define GRAPHICS_DIR	"Graphics"
#define CONTROL_DIR		"Control"
#define ARTICULATION_DIR	"Articulation"
#define ENVIRONMENT_DIR		"Environment"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//CArray<CString, CString> CFindFile::m_arrayPaths[N_NUM_FILE_TYPES];
CString CFindFile::m_strInitialWorkingDirectory = "";
CString CFindFile::m_strCFGDirectory = "";


CFindFile::CFindFile()
{

}

CFindFile::~CFindFile()
{

}

BOOL CFindFile::FindFile(int nType, CString strFileName, CString & rstrPathToFile)
{
	CString strFullPathToFile;

	// Make sure some valid data is passed in.  This will be checked by making sure
	// the string is as least 3 characters long (because all these files have a dot
	// 2 or 3 letter extension.  (Note this would validate some complex combinations as valid
	// that might not be (ie strFileName = ".\.\.\.\.\."))
	if (strFileName.GetLength () < 3)
		return FALSE;

	// Check the directory the cfg is in
	// Make sure one has been specified (there can be valid cases where one is not
	// like the robot is being designed from scratch
	if (m_strCFGDirectory.GetLength () > 0)
	{
		rstrPathToFile =  m_strCFGDirectory + '\\';
		strFullPathToFile = rstrPathToFile + strFileName;
		if (GetFileAttributes (strFullPathToFile) != -1)
		{
			// Found it
			return TRUE;
		}
	}
	
	// Build the subdirectory (this will be used to search relative to the .cfg and 
	// the exe directories.
	CString strSubDirectory;
	if (nType == MODEL_FILE_TYPE || nType == TERRAIN_FILE_TYPE ||
		nType == TREADMILL_FILE_TYPE || nType == TEXTURE_FILE_TYPE)
		strSubDirectory = GRAPHICS_DIR;
	else if (nType == CONTROL_FILE_TYPE)
		strSubDirectory = CONTROL_DIR;
	else if (nType == ENVIRONMENT_FILE_TYPE)
		strSubDirectory = ENVIRONMENT_DIR;
	else if (nType == ARTICULATION_FILE_TYPE)
		strSubDirectory = ARTICULATION_DIR;
	else
		// Unexpected state
		ASSERT (FALSE);	
	
	// Check the type directories under the cfg dir
	// Make sure one has been specified 
	if (m_strCFGDirectory.GetLength () > 0)
	{
		rstrPathToFile =  m_strCFGDirectory + '\\' + strSubDirectory + '\\';
		strFullPathToFile =  rstrPathToFile + strFileName;
		if (GetFileAttributes (strFullPathToFile) != -1)
		{
			// Found it
			return TRUE;
		}
	}

	// Check the initial working directory
	ASSERT (m_strInitialWorkingDirectory.GetLength () > 0);
	rstrPathToFile =  m_strInitialWorkingDirectory + '\\';
	strFullPathToFile = rstrPathToFile + strFileName;
	if (GetFileAttributes (strFullPathToFile) != -1)
	{
		// Found it
		return TRUE;
	}

	// Check the specific subdirectories relative to the initial working directory
	rstrPathToFile =  m_strInitialWorkingDirectory + '\\' + strSubDirectory + '\\';
	strFullPathToFile = rstrPathToFile +  strFileName;
	if (GetFileAttributes (strFullPathToFile) != -1)
	{
		// Found it
		return TRUE;
	}


	
	// Check if the file passed in was a full path
	// See note below why need to check for full path (otherwise it will find it 
	// relative to the current directory)
	// First check if it is a full path - two conditions will be checked.  First, the
	// first letter should not be a . (period).  This lets us use relative path names
	// without breaking any rules (like accidently finding a file relative to the
	// current directory).  Next there needs to be at least 1 backslash.
	if ((strFileName.GetAt (0) != '.') && (strFileName.Find ('\\', 0) != -1))
	{
		rstrPathToFile = "";
		strFullPathToFile = strFileName;
		if (GetFileAttributes (strFullPathToFile) != -1)
		{
			// Found it
			return TRUE;
		}
	}

	// Note that we don't want to check relative to the current path, because things
	// that work relative to the current path might not work in the future if the 
	// relative path is different.  For example, one might assume that opening a .env
	// file with a terrain.dat file in the same directory should work.  The problem is what
	// if the .env file is in a non-standard directory, but that directory is saved by
	// the program (by the dialog box that prompts the user because the directory is
	// non-standard).  If the user saves the .cfg with that data, the next time the .cfg
	// is loaded, the terrain.dat file will not be able to be found, thus creating an
	// inconsistency I avoid by not checking the current directory.


	// If get this far, then the file was not found in the search path,
	// It is up to the caller to give a meaningful error message

	// Return the path as empty
	rstrPathToFile = "";
	return FALSE;
}


/*
int CFindFile::MapFileTypeToPathIndex(int nType)
{
	switch (nType)
	{
	case MODEL_PATH:
		return 0;
		break;
	case TERRAIN_PATH:
		return 0;
		break;
	case ENVIRONMENT_PATH:
		return 1;
		break;
	case ARTICULATION_PATH:
		return 2;
		break;
	case CONTROLDLL_PATH:
		return 3;
		break;
	}

	// Shouldn't ever get here
	ASSERT (FALSE);
	// Return a number only to make the compiler happy
	return 0;

}
*/
void CFindFile::InitializeFindFile()
{
	// When this is constructed, I assume that the current directory will be the
	// path to executable.
	char szCurrentDirectory[N_MAX_CURRENT_DIRECTORY_SIZE];
	DWORD dwReturn = GetCurrentDirectory (N_MAX_CURRENT_DIRECTORY_SIZE, szCurrentDirectory);
	ASSERT (dwReturn);

	m_strInitialWorkingDirectory = szCurrentDirectory;


/*	int nCounter;
	for (nCounter = 0; nCounter < N_NUM_FILE_TYPES; nCounter++)
	{
		m_arrayPaths[nCounter].RemoveAll ();

		// Next read the respective path from the registry
		m_arrayPaths[nCounter].Add (".");
		// Finally add the exe path
		m_arrayPaths[nCounter].Add (m_strExeDirectory);
		// add the current path to each array
		m_arrayPaths[nCounter].Add (".");
	}

	InitializeCustomPaths ();*/
}
/*
void CFindFile::InitializeCustomPaths()
{
	char szPathBuffer[N_MAX_CURRENT_DIRECTORY_SIZE];
	// now pick up the stored paths from the ini
	GetPrivateProfileString ("Paths", "Model_Path", ".", szPathBuffer, N_MAX_CURRENT_DIRECTORY_SIZE,
		"RobotBuilder.INI");
	m_arrayPaths[0].SetAt (INI_PATH_INDEX, szPathBuffer);
	GetPrivateProfileString ("Paths", "Environment_Path", ".", szPathBuffer, N_MAX_CURRENT_DIRECTORY_SIZE,
		"RobotBuilder.INI");
	m_arrayPaths[1].SetAt (INI_PATH_INDEX, szPathBuffer);
	GetPrivateProfileString ("Paths", "Articulation_Path", ".", szPathBuffer, N_MAX_CURRENT_DIRECTORY_SIZE,
		"RobotBuilder.INI");
	m_arrayPaths[2].SetAt (INI_PATH_INDEX, szPathBuffer);
	GetPrivateProfileString ("Paths", "ControlDLL_Path", ".", szPathBuffer, N_MAX_CURRENT_DIRECTORY_SIZE,
		"RobotBuilder.INI");
	m_arrayPaths[3].SetAt (INI_PATH_INDEX, szPathBuffer);



}


// just a string compare so strPath should NOT end with a \ or file name
BOOL CFindFile::IsDirectoryInSearchPath(int nType, CString strPath)
{
	// map type to array index
	int nTypeIndex = MapFileTypeToPathIndex (nType);

	// just look at path in ini and exe path
	if (m_arrayPaths[nTypeIndex].GetAt (INI_PATH_INDEX) == strPath ||
		m_arrayPaths[nTypeIndex].GetAt (EXE_PATH_INDEX) == strPath)
		return TRUE;
	else
		return FALSE;
}

// expects strPathName to be the form returned by a GetPathName call on a CFileDialog
BOOL CFindFile::IsFilePathInSearchPath(int nType, CString strPathName)
{
	int nLastBackslashLocation = strPathName.ReverseFind ('\\');
	if (nLastBackslashLocation < 1)
	{
		// then note found
		return FALSE;
	}
	strPathName.Left (nLastBackslashLocation - 1);
	return IsDirectoryInSearchPath (nType, strPathName);
}
*/
// Input is the full path to the CFG File, or NULL string if no CFG specified
void CFindFile::SetCFGFilePath(CString strCFGFileFullPath)
{
	// Check if empty string, if so save it to reset the string
	if (strCFGFileFullPath.GetLength () == 0)
	{
		m_strCFGDirectory = "";
	}
	else
	{
		// Remove the filename
		int nLastBackslashLocation = strCFGFileFullPath.ReverseFind ('\\');
		// Verify that the backslash preceding the file name was found.
		ASSERT (nLastBackslashLocation > 1);
		// Remove the filename and store the path
		m_strCFGDirectory = strCFGFileFullPath.Left (nLastBackslashLocation);
	}
}

// When this class is initialized, it is initialized with the current working directory.
// This returns that string
CString CFindFile::GetInitialWorkingDirectory()
{
	return m_strInitialWorkingDirectory;
}

// This returns the currently saved path to the cfg.  If no cfg has been chosen,
// it will be empty
CString CFindFile::GetCFGFilePath()
{
	return m_strCFGDirectory;
}
