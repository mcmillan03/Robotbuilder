#if !defined(AFX_PSHEETHEMISPHERE_H__BEEDE4F6_3947_4A64_8FB0_B2F77AAD7055__INCLUDED_)
#define AFX_PSHEETHEMISPHERE_H__BEEDE4F6_3947_4A64_8FB0_B2F77AAD7055__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetHemisphere.h : header file
//
#include "PPageHemisphere.h"
#include "PPageCovering.h"
#include "PPagePlacement.h"
#include "PPagePhysicalProperties.h"
#include "PSheetBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetHemisphere

class CPSheetHemisphere : public CPSheetBase
{
	DECLARE_DYNAMIC(CPSheetHemisphere)

// Construction
public:
	CPSheetHemisphere(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetHemisphere(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetHemisphere)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetData (CPrimitiveHemisphere* pPrimitiveHemisphere);
	virtual ~CPSheetHemisphere();

	// Generated message map functions
protected:
	CPrimitiveHemisphere* m_pPrimitiveHemisphere;
	CPPageHemisphere m_PPageHemisphere;
	CPPagePlacement m_PPagePlacement;
	CPPageCovering m_PPageCovering;
	CPPagePhysicalProperties m_PPagePhysicalProperties;
	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetHemisphere)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETHEMISPHERE_H__BEEDE4F6_3947_4A64_8FB0_B2F77AAD7055__INCLUDED_)
