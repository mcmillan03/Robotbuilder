#if !defined(AFX_DLGENVTREADMILLDATA_H__817A274A_D74C_447F_A055_8A6871300C3F__INCLUDED_)
#define AFX_DLGENVTREADMILLDATA_H__817A274A_D74C_447F_A055_8A6871300C3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEnvTreadmillData.h : header file
//

#include "dmvTreadmillData.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvTreadmillData dialog

class CDlgEnvTreadmillData : public CDialog
{
// Construction
public:
	CString m_strFileName;
	CString m_strPath;
	void GetFilename (CString &rstrFilename, CString &rstrPath) const;
	void SetFilename (CString strTreadmillFile, CString strPath);
	void SaveDialogData ();
	void SetDataClassPointer (CdmvTreadmillData* pCdmvTreadmillData);
	CDlgEnvTreadmillData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEnvTreadmillData)
	enum { IDD = IDD_ENV_TREADMILL_DATA };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEnvTreadmillData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CdmvTreadmillData* m_pCdmvTreadmillData;
	structEnvTreadmillData m_strtEnvTreadmillData;

	// Generated message map functions
	//{{AFX_MSG(CDlgEnvTreadmillData)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonChooseColor();
	virtual void OnOK();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGENVTREADMILLDATA_H__817A274A_D74C_447F_A055_8A6871300C3F__INCLUDED_)
