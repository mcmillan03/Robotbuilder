// FindFile.h: interface for the CFindFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINDFILE_H__EC9CEB51_267A_11D4_8426_00C04F666666__INCLUDED_)
#define AFX_FINDFILE_H__EC9CEB51_267A_11D4_8426_00C04F666666__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum _FileSearchTypes
{
	MODEL_FILE_TYPE, ARTICULATION_FILE_TYPE, ENVIRONMENT_FILE_TYPE, 
		TERRAIN_FILE_TYPE, CONTROL_FILE_TYPE, TREADMILL_FILE_TYPE, TEXTURE_FILE_TYPE
};

#define FILE_NOT_FOUND_MSG  "The selected file is not in the standard search path for the application or will be preempted by another file in the standard search path of the same name.\nNote if the full path is saved, though, the file might not be found on another computer or configuration.\n\nDo you want to save the full path name to work around the problem?"
#define N_MAX_CURRENT_DIRECTORY_SIZE	255

class CFindFile  
{
public:
	static CString GetCFGFilePath ();
	static CString GetInitialWorkingDirectory ();
	static void SetCFGFilePath (CString strCFGFileFullPath);
//	static BOOL IsFilePathInSearchPath (int nType, CString strPathName);
//	static BOOL IsDirectoryInSearchPath (int nType, CString strPath);
//	static void InitializeCustomPaths ();
	static void InitializeFindFile ();
	static BOOL FindFile (int nType, CString strFileName, CString & rstrFullPath);
	CFindFile();
	virtual ~CFindFile();
private:
//	static int MapFileTypeToPathIndex (int nType);
//	static CArray <CString, CString> m_arrayPaths[N_NUM_FILE_TYPES];
	static CString m_strInitialWorkingDirectory;
	static CString m_strCFGDirectory;
//	enum {INI_PATH_INDEX = 0, EXE_PATH_INDEX = 1};
};

#endif // !defined(AFX_FINDFILE_H__EC9CEB51_267A_11D4_8426_00C04F666666__INCLUDED_)
