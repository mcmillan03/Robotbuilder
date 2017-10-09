#if !defined(AFX_PPAGEPHYSICALPROPERTIES_H__64C5F8BD_257C_4655_A09B_049B9D6CB9B2__INCLUDED_)
#define AFX_PPAGEPHYSICALPROPERTIES_H__64C5F8BD_257C_4655_A09B_049B9D6CB9B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPagePhysicalProperties.h : header file
//

#include "Primitive.h"

/////////////////////////////////////////////////////////////////////////////
// CPPagePhysicalProperties dialog

class CPPagePhysicalProperties : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPagePhysicalProperties)

// Construction
public:
	CPrimitive* m_pPrimitive;
	CPPagePhysicalProperties();
	~CPPagePhysicalProperties();

// Dialog Data
	//{{AFX_DATA(CPPagePhysicalProperties)
	enum { IDD = IDD_PHYSICAL_PROPERTIES };
	double	m_dMass;
	//}}AFX_DATA
	double m_dInertiaTensor[3][3];
	double m_dCOG[3];

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPagePhysicalProperties)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPagePhysicalProperties)
	afx_msg void OnChangeEditMass();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEPHYSICALPROPERTIES_H__64C5F8BD_257C_4655_A09B_049B9D6CB9B2__INCLUDED_)
