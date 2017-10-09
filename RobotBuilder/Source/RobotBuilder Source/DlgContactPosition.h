#if !defined(AFX_DLGCONTACTPOSITION_H__A63391A4_F1D2_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DLGCONTACTPOSITION_H__A63391A4_F1D2_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgContactPosition.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgContactPosition dialog

class CDlgContactPosition : public CDialog
{
// Construction
public:
	CDlgContactPosition(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgContactPosition)
	enum { IDD = IDD_CONTACT_POSITION };
	float	m_fPositionX;
	float	m_fPositionY;
	float	m_fPositionZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgContactPosition)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgContactPosition)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONTACTPOSITION_H__A63391A4_F1D2_11D3_A7DF_0000E8978554__INCLUDED_)
