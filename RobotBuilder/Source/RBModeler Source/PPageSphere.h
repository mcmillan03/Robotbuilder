#if !defined(AFX_PPAGESPHERE_H__34882C50_DFF5_42A5_9318_C8A8987AE5AB__INCLUDED_)
#define AFX_PPAGESPHERE_H__34882C50_DFF5_42A5_9318_C8A8987AE5AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageSphere.h : header file
//

#include "PrimitiveSphere.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageSphere dialog

class CPPageSphere : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageSphere)

// Construction
public:
	CPrimitiveSphere* m_pPrimitiveSphere;
	CPPageSphere();
	~CPPageSphere();

// Dialog Data
	//{{AFX_DATA(CPPageSphere)
	enum { IDD = IDD_PRIMITIVE_SPHERE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageSphere)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	structPrimitiveSphereData m_strtPrimitiveSphereData;
	// Generated message map functions
	//{{AFX_MSG(CPPageSphere)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditRadius();
	afx_msg void OnChangeEditLongitude();
	afx_msg void OnChangeEditLatitude();
	afx_msg void OnCheckGouraud();
	afx_msg void OnCheckBothSides();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGESPHERE_H__34882C50_DFF5_42A5_9318_C8A8987AE5AB__INCLUDED_)
