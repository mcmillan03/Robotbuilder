#if !defined(AFX_PSHEETBASE_H__D95BD6C9_F100_4AAE_B5C0_453E1F8CFE48__INCLUDED_)
#define AFX_PSHEETBASE_H__D95BD6C9_F100_4AAE_B5C0_453E1F8CFE48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetBase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPSheetBase

class CPSheetBase : public CPropertySheet
{
	DECLARE_DYNAMIC(CPSheetBase)

// Construction
public:
	CPSheetBase(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetBase(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetBase)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSheetBase();

	// Generated message map functions
protected:
	virtual void BuildPropertySheet () = 0;
	//{{AFX_MSG(CPSheetBase)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETBASE_H__D95BD6C9_F100_4AAE_B5C0_453E1F8CFE48__INCLUDED_)
