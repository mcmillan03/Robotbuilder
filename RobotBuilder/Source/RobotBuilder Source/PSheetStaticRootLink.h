#if !defined(AFX_PSHEETSTATICROOTLINK_H__5AFE3CE2_17CE_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_PSHEETSTATICROOTLINK_H__5AFE3CE2_17CE_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetStaticRootLink.h : header file
//
#include "PPageObjectData.h"	// Added by ClassView
#include "PSheetLinkBase.h"
#include "dmvStaticRootLinkData.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetStaticRootLink

class CPSheetStaticRootLink : public CPSheetLinkBase
{
	DECLARE_DYNAMIC(CPSheetStaticRootLink)

// Construction
public:
	CPSheetStaticRootLink(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetStaticRootLink(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetStaticRootLink)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSheetStaticRootLink();
	CdmvStaticRootLinkData *m_pCdmvStaticRootLinkData;

	// Generated message map functions
protected:
	CPPageObjectData m_ppageObjectData;
	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetStaticRootLink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETSTATICROOTLINK_H__5AFE3CE2_17CE_11D4_A7DF_0000E8978554__INCLUDED_)
