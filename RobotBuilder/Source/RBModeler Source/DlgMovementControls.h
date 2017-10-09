#if !defined(AFX_DLGMOVEMENTCONTROLS_H__13FD0CF4_778B_467D_B074_8F19E3F67B98__INCLUDED_)
#define AFX_DLGMOVEMENTCONTROLS_H__13FD0CF4_778B_467D_B074_8F19E3F67B98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMovementControls.h : header file
//
#include "Model.h"
#include "ComboBoxPrimitives.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CDlgMovementControls dialog
enum {AXIS_X, AXIS_Y, AXIS_Z};

class CDlgMovementControls : public CDialog
{
// Construction
public:
	void GeneralModify (BOOL bPositiveDirection, UINT uAxis);
	CComboBoxPrimitives m_comboPrimitives;
	void RefreshPrimitiveComboBox ();
	CDlgMovementControls(CWnd* pParent = NULL);   // standard constructor
	DECLARE_DYNCREATE(CDlgMovementControls)
	CModel* GetModel ();

// Dialog Data
	//{{AFX_DATA(CDlgMovementControls)
	enum { IDD = IDD_MOVEMENT_CONTROLS };
	CSpinButtonCtrl	m_spinStepSize;
	double	m_dStepSize;
	int		m_nModType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMovementControls)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMovementControls)
	afx_msg void OnButtonXNegative();
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRadioScale();
	afx_msg void OnRadioRotate();
	afx_msg void OnRadioTranslate();
	afx_msg void OnButtonXPositive();
	afx_msg void OnButtonYPositive();
	afx_msg void OnButtonYNegative();
	afx_msg void OnButtonZPositive();
	afx_msg void OnButtonZNegative();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRadioSpatialTransform();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOVEMENTCONTROLS_H__13FD0CF4_778B_467D_B074_8F19E3F67B98__INCLUDED_)
