#if !defined(AFX_PSHEETZSCREWTXLINK_H__EAB91266_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PSHEETZSCREWTXLINK_H__EAB91266_FEA6_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetZScrewTxLink.h : header file
//

#include "PSheetLinkBase.h"
#include "PPageZScrewTxLinkData.h"
#include "PPageObjectData.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetZScrewTxLink

class CPSheetZScrewTxLink : public CPSheetLinkBase
{
	DECLARE_DYNAMIC(CPSheetZScrewTxLink)

// Construction
public:
	CPSheetZScrewTxLink(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetZScrewTxLink(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CdmvZScrewTxLinkData* m_pCdmvZScrewTxLinkData;
protected:
	CPPageZScrewTxLinkData m_ppageZScrewTxLinkData;
	CPPageObjectData m_ppageObjectData;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetZScrewTxLink)
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSheetZScrewTxLink();

	// Generated message map functions
protected:
	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetZScrewTxLink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETZSCREWTXLINK_H__EAB91266_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
