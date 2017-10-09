#if !defined(AFX_DLGROTATIONQUATERNION_H__414D9DF3_1208_4464_8E0C_A149DCEDB9C9__INCLUDED_)
#define AFX_DLGROTATIONQUATERNION_H__414D9DF3_1208_4464_8E0C_A149DCEDB9C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRotationQuaternion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRotationQuaternion dialog

class CDlgRotationQuaternion : public CDialog
{
// Construction
public:
	BOOL ValidateAndSaveQuaternion(double dRotation[3][3]);
	void CalculateRotationQuaternion (double arRotation[3][3] );
	CDlgRotationQuaternion(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRotationQuaternion)
	enum { IDD = IDD_ROTATION_QUATERNION };
	double	m_dQuaternion1;
	double	m_dQuaternion2;
	double	m_dQuaternion3;
	double	m_dQuaternion4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRotationQuaternion)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRotationQuaternion)
	afx_msg void OnChangeEditQuaternion1();
	afx_msg void OnChangeEditQuaternion2();
	afx_msg void OnChangeEditQuaternion3();
	afx_msg void OnChangeEditQuaternion4();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGROTATIONQUATERNION_H__414D9DF3_1208_4464_8E0C_A149DCEDB9C9__INCLUDED_)
