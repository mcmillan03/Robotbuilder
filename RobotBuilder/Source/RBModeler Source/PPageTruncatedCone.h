#if !defined(AFX_PPAGETRUNCATEDCONE_H__FFB63019_6DA8_4268_9016_C5F88974D2FC__INCLUDED_)
#define AFX_PPAGETRUNCATEDCONE_H__FFB63019_6DA8_4268_9016_C5F88974D2FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageTruncatedCone.h : header file
//
#include "PrimitiveTruncatedCone.h"
#include "RBModelerRBMGraphicView.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageTruncatedCone dialog

class CPPageTruncatedCone : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageTruncatedCone)

// Construction
public:
	CPrimitiveTruncatedCone* m_pPrimitiveTruncatedCone;
	CPPageTruncatedCone();
	~CPPageTruncatedCone();

// Dialog Data
	//{{AFX_DATA(CPPageTruncatedCone)
	enum { IDD = IDD_PRIMITIVE_TRUNCATED_CONE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageTruncatedCone)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	structPrimitiveTruncatedConeData m_strtPrimitiveTruncatedConeData;
	// Generated message map functions
	//{{AFX_MSG(CPPageTruncatedCone)
	afx_msg void OnChangeEditTopRadius();
	afx_msg void OnChangeEditTess();
	afx_msg void OnChangeEditHeight();
	afx_msg void OnChangeEditBaseRadius();
	afx_msg void OnCheckGouraud();
	afx_msg void OnCheckBothSides();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGETRUNCATEDCONE_H__FFB63019_6DA8_4268_9016_C5F88974D2FC__INCLUDED_)
