#if !defined(AFX_PSHEETTRUNCATEDCONE_H__B929087D_56FF_4109_BD24_8ADA2F99C5D0__INCLUDED_)
#define AFX_PSHEETTRUNCATEDCONE_H__B929087D_56FF_4109_BD24_8ADA2F99C5D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetTruncatedCone.h : header file
//
#include "PPageTruncatedCone.h"
#include "PPageCovering.h"
#include "PPagePlacement.h"
#include "PPagePhysicalProperties.h"
#include "PSheetBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetTruncatedCone

class CPSheetTruncatedCone : public CPSheetBase
{
	DECLARE_DYNAMIC(CPSheetTruncatedCone)

// Construction
public:
	CPSheetTruncatedCone(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetTruncatedCone(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetTruncatedCone)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetData (CPrimitiveTruncatedCone* pPrimitiveTruncatedCone);
	virtual ~CPSheetTruncatedCone();

	// Generated message map functions
protected:
	CPrimitiveTruncatedCone* m_pPrimitiveTruncatedCone;
	CPPageTruncatedCone m_PPageTruncatedCone;
	CPPagePlacement m_PPagePlacement;
	CPPageCovering m_PPageCovering;
	CPPagePhysicalProperties m_PPagePhysicalProperties;
	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetTruncatedCone)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETTRUNCATEDCONE_H__B929087D_56FF_4109_BD24_8ADA2F99C5D0__INCLUDED_)
