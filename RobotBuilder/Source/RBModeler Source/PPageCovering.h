#if !defined(AFX_PPAGECOVERING_H__DB40CB44_4E49_43DC_A7D6_BE1EE3575876__INCLUDED_)
#define AFX_PPAGECOVERING_H__DB40CB44_4E49_43DC_A7D6_BE1EE3575876__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageCovering.h : header file
//

#include "Primitive.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageCovering dialog

class CPPageCovering : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageCovering)

// Construction
public:
	CPPageCovering();
	~CPPageCovering();
	CPrimitive* m_pPrimitive;

// Dialog Data
	//{{AFX_DATA(CPPageCovering)
	enum { IDD = IDD_COVERING };
	//}}AFX_DATA
protected:
	CButton	m_radioCoveringType;
	CEdit	m_editTexture;
	CButton	m_butColor;
	CButton	m_butBrowse;
	int		m_nCoveringType;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageCovering)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	structPrimitiveCoveringData m_strtPrimitiveCoveringData;
	// Generated message map functions
	//{{AFX_MSG(CPPageCovering)
	afx_msg void OnButtonColor();
	afx_msg void OnButtonBrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioTypeColor();
	afx_msg void OnRadioTexture();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnChangeEditTexture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGECOVERING_H__DB40CB44_4E49_43DC_A7D6_BE1EE3575876__INCLUDED_)
