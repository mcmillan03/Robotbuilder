#if !defined(AFX_PSHEETSPHERE_H__0BEAF3DB_AD9C_4653_8379_F10AD92FAC07__INCLUDED_)
#define AFX_PSHEETSPHERE_H__0BEAF3DB_AD9C_4653_8379_F10AD92FAC07__INCLUDED_

#include "PPageSphere.h"	// Added by ClassView
#include "PrimitiveSphere.h"
#include "PSheetBase.h"
#include "PPageCovering.h"	// Added by ClassView
#include "PPagePlacement.h"	// Added by ClassView
#include "PPagePhysicalProperties.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetSphere.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPSheetSphere

class CPSheetSphere : public CPSheetBase
{
	DECLARE_DYNAMIC(CPSheetSphere)

// Construction
public:
	CPSheetSphere(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetSphere(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetSphere)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetData (CPrimitiveSphere* pSpherePrimitive);
	virtual ~CPSheetSphere();

	// Generated message map functions
protected:
	CPPagePlacement m_PPagePlacement;
	CPPageCovering m_PPageCovering;
	CPrimitiveSphere* m_pPrimitiveSphere;
	CPPagePhysicalProperties m_PPagePhysicalProperties;
	void BuildPropertySheet ();
	CPPageSphere m_PPageSphere;
	//{{AFX_MSG(CPSheetSphere)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETSPHERE_H__0BEAF3DB_AD9C_4653_8379_F10AD92FAC07__INCLUDED_)
