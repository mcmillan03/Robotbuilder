#if !defined(AFX_DLGENVSAVETERRAINFILE_H__783D2410_0C8C_47D0_9750_23DD641C7DF9__INCLUDED_)
#define AFX_DLGENVSAVETERRAINFILE_H__783D2410_0C8C_47D0_9750_23DD641C7DF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEnvSaveTerrainFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvSaveTerrainFile dialog


#include "dmvTerrainData.h"

class CDlgEnvSaveTerrainFile : public CDialog
{
// Construction
public:
	void GetFilename (CString &rstrFilename, CString &rstrPath) const;
	void SetFileName (CString strFilename, CString strPath);
	void SetDataPointer (CdmvTerrainData *pCdmvTerrainData);
	CDlgEnvSaveTerrainFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEnvSaveTerrainFile)
	enum { IDD = IDD_ENV_DETAILS_FILE_SAVE };
	CButton	m_buttonSave;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEnvSaveTerrainFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEnvSaveTerrainFile)
	afx_msg void OnButtonSave();
	afx_msg void OnButtonSaveAs();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strFilename;
	CString m_strPath;
	CdmvTerrainData* m_pCdmvTerrainData;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGENVSAVETERRAINFILE_H__783D2410_0C8C_47D0_9750_23DD641C7DF9__INCLUDED_)
