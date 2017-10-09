#if !defined(AFX_DLGCONFIGFILES_H__23A8B824_B82E_497A_B04B_BBB3ED792595__INCLUDED_)
#define AFX_DLGCONFIGFILES_H__23A8B824_B82E_497A_B04B_BBB3ED792595__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConfigFiles.h : header file
//

#include "dmvCFGData.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigFiles dialog

class CDlgConfigFiles : public CDialog
{
// Construction
public:
	BOOL ValidateAndSaveData();
	BOOL ValidateData();
	CDlgConfigFiles(CWnd* pParent = NULL);   // standard constructor
	void SetDataClass (CdmvCFGData *pCdmvCFGData);
private:
// Dialog Data
	//{{AFX_DATA(CDlgConfigFiles)
	enum { IDD = IDD_CONFIG_FILES };
	CString	m_strEnvironmentFile;
	CString	m_strArticulationFile;
	CString	m_strControlFile;
	//}}AFX_DATA
	CdmvCFGData* m_pCdmvCFGData;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConfigFiles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConfigFiles)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONFIGFILES_H__23A8B824_B82E_497A_B04B_BBB3ED792595__INCLUDED_)
