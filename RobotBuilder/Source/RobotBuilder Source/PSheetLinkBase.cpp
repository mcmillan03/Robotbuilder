// PSheetLinkBase.cpp : implementation file
//

#include "stdafx.h"
#include "DMViewer.h"
#include "PSheetLinkBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetLinkBase

IMPLEMENT_DYNAMIC(CPSheetLinkBase, CPropertySheet)

CPSheetLinkBase::CPSheetLinkBase(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	this->m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

CPSheetLinkBase::CPSheetLinkBase(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	this->m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

CPSheetLinkBase::~CPSheetLinkBase()
{
}


BEGIN_MESSAGE_MAP(CPSheetLinkBase, CPropertySheet)
	//{{AFX_MSG_MAP(CPSheetLinkBase)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetLinkBase message handlers


int CPSheetLinkBase::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertySheet::DoModal();
}
