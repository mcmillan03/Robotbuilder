#if !defined(AFX_PSHEETCONE_H__EB897B95_E127_474F_9D0F_F0F3FABC8D4A__INCLUDED_)
#define AFX_PSHEETCONE_H__EB897B95_E127_474F_9D0F_F0F3FABC8D4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetCone.h : header file
//
#include "PPageCone.h"
#include "PPageCovering.h"
#include "PPagePlacement.h"
#include "PPagePhysicalProperties.h"
#include "PSheetBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetCone

class CPSheetCone : public CPSheetBase
{
	DECLARE_DYNAMIC(CPSheetCone)

// Construction
public:
	CPSheetCone(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetCone(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetCone)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetData (CPrimitiveCone* pPrimitiveCone);
	virtual ~CPSheetCone();

	// Generated message map functions
protected:
	CPrimitiveCone* m_pPrimitiveCone;
	CPPageCone m_PPageCone;
	CPPagePlacement m_PPagePlacement;
	CPPageCovering m_PPageCovering;
	CPPagePhysicalProperties m_PPagePhysicalProperties;
	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetCone)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETCONE_H__EB897B95_E127_474F_9D0F_F0F3FABC8D4A__INCLUDED_)
