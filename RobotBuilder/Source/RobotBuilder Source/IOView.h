#if !defined(AFX_IOVIEW_H__8F17DE2C_1ABC_4425_B29D_0A054533B97C__INCLUDED_)
#define AFX_IOVIEW_H__8F17DE2C_1ABC_4425_B29D_0A054533B97C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IOView.h : header file
//

//#include "mschart.h"

#include <RBUserIOData.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT   1000

typedef struct
{
   CStatic* pLabel;
   CSliderCtrl* pSlider;
} structSliderElement;

typedef struct
{
   CStatic* pLabel;
   CEdit* pEdit;
} structEditElement;

typedef struct
{
	CButton* pButton;
	BOOL bClicked;
} structButtonElement;
/////////////////////////////////////////////////////////////////////////////
// CIOView view

class CIOView : public CScrollView
{
protected:
	CIOView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIOView)

// Attributes
public:

// Operations
public:
	void UpdateUserData (RBUserIOData* pRBUserIOData);
	void SetRBUserIOData (RBUserIOData* pRBUserIOData);
   CArray<structSliderElement, structSliderElement> m_SliderArray;
   CArray<CButton*, CButton*> m_CheckBoxArray;
   CArray<CStatic*, CStatic*> m_LabelArray;
   CArray<CListCtrl*, CListCtrl*> m_ListArray;
   CArray<structEditElement, structEditElement> m_EditArray;
   CArray<structButtonElement, structButtonElement> m_ButtonArray;
	//  CArray<CMSChart*, CMSChart*> m_ChartArray;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIOView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CIOView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CIOView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	RBUserIOData* m_pRBUserIOData;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOVIEW_H__8F17DE2C_1ABC_4425_B29D_0A054533B97C__INCLUDED_)
