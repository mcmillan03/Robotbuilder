#if !defined(AFX_DLGLINKDATA_H__8F337782_F467_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DLGLINKDATA_H__8F337782_F467_11D3_A7DF_0000E8978554__INCLUDED_

#include "dmvLinkData.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLinkData.h : header file
//

#include "dmvLinkData.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkData dialog

class CDlgLinkData : public CDialog
{
// Construction
public:
	CdmvLinkData* m_pCdmvLinkData;
	void SaveDialogData ();
	CDlgLinkData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLinkData)
	enum { IDD = IDD_LINK_DATA };
	float	m_fJointFriction;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLinkData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLinkData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLINKDATA_H__8F337782_F467_11D3_A7DF_0000E8978554__INCLUDED_)
