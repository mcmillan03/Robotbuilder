#if !defined(AFX_PSHEETPRISMATICLINK_H__E60B03C5_1267_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_PSHEETPRISMATICLINK_H__E60B03C5_1267_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetPrismaticLink.h : header file
//

#include "dmvPrismaticLinkData.h"
#include "PPageObjectData.h"	// Added by ClassView
#include "PPageLinkData.h"
#include "PPageRigidBodyData.h"
#include "PPageMDHLinkData.h"
#include "PSheetLinkBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetPrismaticLink

class CPSheetPrismaticLink : public CPSheetLinkBase
{
	DECLARE_DYNAMIC(CPSheetPrismaticLink)

// Construction
public:
	CPSheetPrismaticLink(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetPrismaticLink(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetPrismaticLink)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	CdmvPrismaticLinkData* m_pCdmvPrismaticLinkData;
	virtual ~CPSheetPrismaticLink();

	// Generated message map functions
protected:
	CPPageObjectData m_ppageObjectData;
	CPPageLinkData m_ppageLinkData;
	CPPageRigidBodyData m_ppageRigidBodyData;
	CPPageMDHLinkData m_ppageMDHLinkData;
	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetPrismaticLink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETPRISMATICLINK_H__E60B03C5_1267_11D4_A7DF_0000E8978554__INCLUDED_)
