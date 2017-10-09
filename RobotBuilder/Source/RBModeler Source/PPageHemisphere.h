#if !defined(AFX_PPAGEHEMISPHERE_H__A0D9F0C0_37EF_4658_A198_E4265A8A254A__INCLUDED_)
#define AFX_PPAGEHEMISPHERE_H__A0D9F0C0_37EF_4658_A198_E4265A8A254A__INCLUDED_

#include "PrimitiveHemisphere.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageHemisphere.h : header file
//
#include "PrimitiveHemisphere.h"
#include "RBModelerRBMGraphicView.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageHemisphere dialog

class CPPageHemisphere : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageHemisphere)

// Construction
public:
	CPrimitiveHemisphere* m_pPrimitiveHemisphere;
	CPPageHemisphere();
	~CPPageHemisphere();

// Dialog Data
	//{{AFX_DATA(CPPageHemisphere)
	enum { IDD = IDD_PRIMITIVE_HEMISPHERE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageHemisphere)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	structPrimitiveHemisphereData m_strtPrimitiveHemisphereData;
	// Generated message map functions
	//{{AFX_MSG(CPPageHemisphere)
	afx_msg void OnChangeEditRadius();
	afx_msg void OnChangeEditLongitude();
	afx_msg void OnChangeEditLatitude();
	afx_msg void OnCheckGouraud();
	afx_msg void OnCheckBothSides();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEHEMISPHERE_H__A0D9F0C0_37EF_4658_A198_E4265A8A254A__INCLUDED_)
