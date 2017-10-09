#if !defined(AFX_PSHEETCYLINDER_H__DE50423A_7F0F_4F43_A3F1_D5FB01E5BB5E__INCLUDED_)
#define AFX_PSHEETCYLINDER_H__DE50423A_7F0F_4F43_A3F1_D5FB01E5BB5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetCylinder.h : header file
//
#include "PPageCylinder.h"
#include "PPageCovering.h"
#include "PPagePlacement.h"
#include "PPagePhysicalProperties.h"
#include "PSheetBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetCylinder

class CPSheetCylinder : public CPSheetBase
{
	DECLARE_DYNAMIC(CPSheetCylinder)

// Construction
public:
	CPSheetCylinder(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetCylinder(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetCylinder)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetData (CPrimitiveCylinder* pPrimitiveCylinder);
	virtual ~CPSheetCylinder();

	// Generated message map functions
protected:
	CPrimitiveCylinder* m_pPrimitiveCylinder;
	CPPageCylinder m_PPageCylinder;
	CPPagePlacement m_PPagePlacement;
	CPPageCovering m_PPageCovering;
	CPPagePhysicalProperties m_PPagePhysicalProperties;
	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetCylinder)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETCYLINDER_H__DE50423A_7F0F_4F43_A3F1_D5FB01E5BB5E__INCLUDED_)
