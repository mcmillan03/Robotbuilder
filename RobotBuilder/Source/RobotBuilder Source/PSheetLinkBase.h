#if !defined(AFX_PSHEETLINKBASE_H__EAB9126C_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PSHEETLINKBASE_H__EAB9126C_FEA6_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetLinkBase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPSheetLinkBase

class CPSheetLinkBase : public CPropertySheet
{
	DECLARE_DYNAMIC(CPSheetLinkBase)

// Construction
public:
	CPSheetLinkBase(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetLinkBase(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetLinkBase)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSheetLinkBase();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPSheetLinkBase)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETLINKBASE_H__EAB9126C_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
