#if !defined(AFX_DLGROTATIONEULERANGLES_H__2F2ED642_71BB_46F4_BF25_A2CFBC0C3C88__INCLUDED_)
#define AFX_DLGROTATIONEULERANGLES_H__2F2ED642_71BB_46F4_BF25_A2CFBC0C3C88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRotationEulerAngles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRotationEulerAngles dialog

class CDlgRotationEulerAngles : public CDialog
{
// Construction
public:
	void CalculateEulerAngles (double dRotation[3][3]);
	BOOL ValidateAndSaveEulerAngles(double dRotation[3][3]);
	CDlgRotationEulerAngles(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRotationEulerAngles)
	enum { IDD = IDD_ROTATION_EULER_ANGLES };
	double	m_dEulerX;
	double	m_dEulerY;
	double	m_dEulerZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRotationEulerAngles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRotationEulerAngles)
	afx_msg void OnChangeEditEulerX();
	afx_msg void OnChangeEditEulerY();
	afx_msg void OnChangeEditEulerZ();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGROTATIONEULERANGLES_H__2F2ED642_71BB_46F4_BF25_A2CFBC0C3C88__INCLUDED_)
