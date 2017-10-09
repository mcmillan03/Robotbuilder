#if !defined(AFX_PSHEETREVOLUTELINK_H__85567265_FF09_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PSHEETREVOLUTELINK_H__85567265_FF09_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetRevoluteLink.h : header file
//

#include "dmvRevoluteLinkData.h"
#include "PPageObjectData.h"	// Added by ClassView
#include "PPageActuatorData.h"
#include "PPageRigidBodyData.h"
#include "PPageMDHLinkData.h"
#include "PSheetLinkBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetRevoluteLink

class CPSheetRevoluteLink : public CPSheetLinkBase
{
	DECLARE_DYNAMIC(CPSheetRevoluteLink)

// Construction
public:
	CPSheetRevoluteLink(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetRevoluteLink(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetRevoluteLink)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	CdmvRevoluteLinkData* m_pCdmvRevoluteLinkData;
	virtual ~CPSheetRevoluteLink();
protected:
	void BuildPropertySheet ();


	// Generated message map functions
protected:
	CPPageObjectData m_ppageObjectData;
	CPPageActuatorData m_ppageActuatorData;
	CPPageRigidBodyData m_ppageRigidBodyData;
	CPPageMDHLinkData m_ppageMDHLinkData;
	//{{AFX_MSG(CPSheetRevoluteLink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETREVOLUTELINK_H__85567265_FF09_11D3_A7DF_0000E8978554__INCLUDED_)
