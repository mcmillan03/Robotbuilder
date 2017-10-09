#if !defined(AFX_PPAGECONE_H__EF3B5F32_283C_4DE4_B958_CF5401678B1A__INCLUDED_)
#define AFX_PPAGECONE_H__EF3B5F32_283C_4DE4_B958_CF5401678B1A__INCLUDED_

#include "PrimitiveCone.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageCone.h : header file
//
#include "PrimitiveCone.h"
#include "RBModelerRBMGraphicView.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageCone dialog

class CPPageCone : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageCone)

// Construction
public:
	CPrimitiveCone* m_pPrimitiveCone;
	CPPageCone();
	~CPPageCone();

// Dialog Data
	//{{AFX_DATA(CPPageCone)
	enum { IDD = IDD_PRIMITIVE_CONE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageCone)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	structPrimitiveConeData m_strtPrimitiveConeData;
	// Generated message map functions
	//{{AFX_MSG(CPPageCone)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditTess();
	afx_msg void OnChangeEditRadius();
	afx_msg void OnChangeEditHeight();
	afx_msg void OnCheckBothSides();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGECONE_H__EF3B5F32_283C_4DE4_B958_CF5401678B1A__INCLUDED_)
