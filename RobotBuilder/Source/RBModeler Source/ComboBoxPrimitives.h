#if !defined(AFX_COMBOBOXPRIMITIVES_H__00C34D4D_EDA9_40A0_9E59_7C33D3D0FCFB__INCLUDED_)
#define AFX_COMBOBOXPRIMITIVES_H__00C34D4D_EDA9_40A0_9E59_7C33D3D0FCFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxPrimitives.h : header file
//
#include "Model.h"
/////////////////////////////////////////////////////////////////////////////
// CComboBoxPrimitives window

typedef enum {PCBT_UNIVERSE, PCBT_LOCAL, PCBT_PRIMITIVE} ePrimitiveCBType;

class CComboBoxPrimitives : public CComboBox
{
// Construction
public:
	CComboBoxPrimitives();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxPrimitives)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void GetCurrentSelection (CModel* pModel, UINT* puWRTType, CPrimitive** ppPrimitive);
	void RefreshCurrentSelection (CModel* pModel);
	void RefreshList (CModel* pModel);
	virtual ~CComboBoxPrimitives();

	// Generated message map functions
protected:
	void RefreshComboBox (CModel* pModel);
	BOOL IsComboBoxListValid (CModel* pModel);
	BOOL IsCurrentSelectionValid (CModel* pModel);
	//{{AFX_MSG(CComboBoxPrimitives)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXPRIMITIVES_H__00C34D4D_EDA9_40A0_9E59_7C33D3D0FCFB__INCLUDED_)
