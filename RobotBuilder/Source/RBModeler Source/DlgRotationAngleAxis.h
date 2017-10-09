#if !defined(AFX_DLGROTATIONANGLEAXIS_H__26F3E6C8_1590_4CFD_AE63_C477ED97E7F1__INCLUDED_)
#define AFX_DLGROTATIONANGLEAXIS_H__26F3E6C8_1590_4CFD_AE63_C477ED97E7F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRotationAngleAxis.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRotationAngleAxis dialog

class CDlgRotationAngleAxis : public CDialog
{
// Construction
public:
	BOOL ValidateAndSaveAngleAxis (double dRotation[3][3]);
	void CalculateAngleAxis (double dRotation[3][3]);
	CDlgRotationAngleAxis(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRotationAngleAxis)
	enum { IDD = IDD_ROTATION_ANGLE_AXIS };
	double	m_dAngle;
	double	m_dAxisX;
	double	m_dAxisY;
	double	m_dAxisZ;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRotationAngleAxis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRotationAngleAxis)
	afx_msg void OnChangeEditAxisX();
	afx_msg void OnChangeEditAxisY();
	afx_msg void OnChangeEditAxisZ();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGROTATIONANGLEAXIS_H__26F3E6C8_1590_4CFD_AE63_C477ED97E7F1__INCLUDED_)
