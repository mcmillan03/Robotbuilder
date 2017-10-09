#if !defined(AFX_PPAGECYLINDER_H__B2C744D3_1C97_4A39_A4C8_863C7DED1AB0__INCLUDED_)
#define AFX_PPAGECYLINDER_H__B2C744D3_1C97_4A39_A4C8_863C7DED1AB0__INCLUDED_

#include "PrimitiveCylinder.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageCylinder.h : header file
//
#include "PrimitiveCylinder.h"
#include "RBModelerRBMGraphicView.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageCylinder dialog

class CPPageCylinder : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageCylinder)

// Construction
public:
	CPrimitiveCylinder* m_pPrimitiveCylinder;
	CPPageCylinder();
	~CPPageCylinder();

// Dialog Data
	//{{AFX_DATA(CPPageCylinder)
	enum { IDD = IDD_PRIMITIVE_CYLINDER };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageCylinder)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	structPrimitiveCylinderData m_strtPrimitiveCylinderData;
	// Generated message map functions
	//{{AFX_MSG(CPPageCylinder)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditHeight();
	afx_msg void OnChangeEditRadius();
	afx_msg void OnChangeEditTess();
	afx_msg void OnCheckGouraud();
	afx_msg void OnCheckBothSides();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGECYLINDER_H__B2C744D3_1C97_4A39_A4C8_863C7DED1AB0__INCLUDED_)
