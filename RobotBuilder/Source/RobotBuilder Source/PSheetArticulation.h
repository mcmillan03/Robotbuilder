#if !defined(AFX_PSHEETARTICULATION_H__85567262_FF09_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PSHEETARTICULATION_H__85567262_FF09_11D3_A7DF_0000E8978554__INCLUDED_

#include "PPageArticulationData.h"	// Added by ClassView
#include "PPageObjectData.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetArticulation.h : header file
//
#include "PSheetLinkBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetArticulation

class CPSheetArticulation : public CPSheetLinkBase
{
	DECLARE_DYNAMIC(CPSheetArticulation)

// Construction
public:
	CPSheetArticulation(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetArticulation(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetArticulation)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	CdmvArticulationData* m_pCdmvArticulationData;
	virtual ~CPSheetArticulation();
protected:
	void BuildPropertySheet ();

	// Generated message map functions
protected:
	CPPageObjectData m_ppageObjectData;
	CPPageArticulationData m_ppageArticulationData;
	//{{AFX_MSG(CPSheetArticulation)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETARTICULATION_H__85567262_FF09_11D3_A7DF_0000E8978554__INCLUDED_)
