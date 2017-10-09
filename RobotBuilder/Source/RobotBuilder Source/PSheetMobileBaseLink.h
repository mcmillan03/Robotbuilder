#if !defined(AFX_PSHEETMOBILEBASELINK_H__376966C2_005D_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_PSHEETMOBILEBASELINK_H__376966C2_005D_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetMobileBaseLink.h : header file
//

#include "PSheetLinkBase.h"
#include "PPageMobileBaseLinkData.h"
#include "PPageObjectData.h"
#include "PPageRigidBodyData.h"
#include "PPageLinkData.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetMobileBaseLink

class CPSheetMobileBaseLink : public CPSheetLinkBase
{
	DECLARE_DYNAMIC(CPSheetMobileBaseLink)

// Construction
public:
	CPSheetMobileBaseLink(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetMobileBaseLink(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetMobileBaseLink)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSheetMobileBaseLink();
	CdmvMobileBaseLinkData* m_pCdmvMobileBaseLinkData;
	// Generated message map functions
protected:
	CPPageMobileBaseLinkData m_ppageMobileBaseLinkData;
	CPPageObjectData m_ppageObjectData;
	CPPageRigidBodyData m_ppageRigidBodyData;
	CPPageLinkData m_ppageLinkData;
	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetMobileBaseLink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETMOBILEBASELINK_H__376966C2_005D_11D4_A7DF_0000E8978554__INCLUDED_)
