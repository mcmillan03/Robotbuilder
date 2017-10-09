#if !defined(AFX_PPAGEOBJECTDATA_H__EAB9126E_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PPAGEOBJECTDATA_H__EAB9126E_FEA6_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageObjectData.h : header file
//

#include "dmvObject.h"
#include "PPageLinkBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageObjectData dialog

class CPPageObjectData : public CPPageLinkBase
{
	DECLARE_DYNCREATE(CPPageObjectData)

// Construction
public:
	CPPageObjectData(BOOL bEnableModelSetting = TRUE);
	~CPPageObjectData();
	CdmvObject* m_pCdmvObject;

// Dialog Data
	//{{AFX_DATA(CPPageObjectData)
	enum { IDD = IDD_OBJECT_DATA };
	CButton	m_staticGraphicsModelGroupBox;
	CButton	m_buttonBrowse;
	CEdit	m_editGraphicsFile;
	CString	m_strGraphicsFile;
	CString	m_strLinkName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageObjectData)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strGraphicsPath;
	BOOL m_bEnableModelSetting;
	// Generated message map functions
	//{{AFX_MSG(CPPageObjectData)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEOBJECTDATA_H__EAB9126E_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
