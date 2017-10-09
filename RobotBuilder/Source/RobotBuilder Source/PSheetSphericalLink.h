#if !defined(AFX_PSHEETSPHERICALLINK_H__3C918744_17A5_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_PSHEETSPHERICALLINK_H__3C918744_17A5_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetSphericalLink.h : header file
//
#include "PPageObjectData.h"	// Added by ClassView
#include "PPageLinkData.h"
#include "PPageRigidBodyData.h"
#include "PPageLinkData.h"
#include "PSheetLinkBase.h"
#include "PPageSphericalLinkData.h"
#include "dmvSphericalLinkData.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetSphericalLink

class CPSheetSphericalLink : public CPSheetLinkBase
{
	DECLARE_DYNAMIC(CPSheetSphericalLink)

// Construction
public:
	CPSheetSphericalLink(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetSphericalLink(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetSphericalLink)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSheetSphericalLink();
	CdmvSphericalLinkData* m_pCdmvSphericalLinkData;

	// Generated message map functions
protected:
	CPPageObjectData m_ppageObjectData;
	CPPageRigidBodyData m_ppageRigidBodyData;
	CPPageSphericalLinkData m_ppageSphericalLinkData;
	CPPageLinkData m_ppageLinkData;

	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetSphericalLink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETSPHERICALLINK_H__3C918744_17A5_11D4_A7DF_0000E8978554__INCLUDED_)
