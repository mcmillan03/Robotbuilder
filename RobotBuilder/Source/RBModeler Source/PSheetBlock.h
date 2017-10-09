#if !defined(AFX_PSHEETBLOCK_H__3B763DBC_417E_46C9_AB4E_EE5DF5C7D27C__INCLUDED_)
#define AFX_PSHEETBLOCK_H__3B763DBC_417E_46C9_AB4E_EE5DF5C7D27C__INCLUDED_

#include "PPageCovering.h"	// Added by ClassView
#include "PPageBlock.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetBlock.h : header file
//
#include "PPageBlock.h"
#include "PPageCovering.h"
#include "PPagePlacement.h"
#include "PPagePhysicalProperties.h"
#include "PSheetBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetBlock

class CPSheetBlock : public CPSheetBase
{
	DECLARE_DYNAMIC(CPSheetBlock)

// Construction
public:
	CPSheetBlock(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetBlock(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetBlock)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetData (CPrimitiveBlock* pPrimitiveBlock);
	virtual ~CPSheetBlock();

	// Generated message map functions
protected:
	CPrimitiveBlock* m_pPrimitiveBlock;
	CPPageBlock m_PPageBlock;
	CPPagePlacement m_PPagePlacement;
	CPPageCovering m_PPageCovering;
	CPPagePhysicalProperties m_PPagePhysicalProperties;
	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetBlock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETBLOCK_H__3B763DBC_417E_46C9_AB4E_EE5DF5C7D27C__INCLUDED_)
