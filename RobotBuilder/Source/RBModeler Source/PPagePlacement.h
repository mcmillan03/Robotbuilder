#if !defined(AFX_PPAGEPLACEMENT_H__59BF9A28_A6EF_4917_9A74_5B61F797E94B__INCLUDED_)
#define AFX_PPAGEPLACEMENT_H__59BF9A28_A6EF_4917_9A74_5B61F797E94B__INCLUDED_

#include "PrimitivePlacement.h"	// Added by ClassView
#include "PrimitiveScale.h"
#include "DlgRotationQuaternion.h"	// Added by ClassView
#include "DlgRotationEulerAngles.h"	// Added by ClassView
#include "DlgRotationAngleAxis.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPagePlacement.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPagePlacement dialog

class CPPagePlacement : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPagePlacement)

// Construction
public:
	CPPagePlacement();
	~CPPagePlacement();

// Dialog Data
	//{{AFX_DATA(CPPagePlacement)
	enum { IDD = IDD_PLACEMENT };
	CTabCtrl	m_tabctrlRotation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPagePlacement)
	public:
	virtual BOOL OnApply();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
		CPrimitive* m_pPrimitive;
protected:
	CDlgRotationAngleAxis m_dlgRotationAngleAxis;
	enum {ROT_TAB_QUATERNION, ROT_TAB_EULER_ANGLES, ROT_TAB_ANGLE_AXIS};
	void CalculateRotationRepresentation ();
	BOOL ValidateRotation ();
	CDlgRotationEulerAngles m_dlgRotationEulerAngles;
	CDlgRotationQuaternion m_dlgRotationQuaternion;
	structPrimitivePlacementData m_strtPrimitivePlacementData;
	structPrimitiveScaleData m_strtPrimitiveScaleData;
	// Generated message map functions
	//{{AFX_MSG(CPPagePlacement)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditScaleX();
	afx_msg void OnChangeEditScaleY();
	afx_msg void OnChangeEditScaleZ();
	afx_msg void OnChangeEditTranslationX();
	afx_msg void OnChangeEditTranslationY();
	afx_msg void OnChangeEditTranslationZ();
	afx_msg void OnSelchangeTabRotation(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTabRotation(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEPLACEMENT_H__59BF9A28_A6EF_4917_9A74_5B61F797E94B__INCLUDED_)
