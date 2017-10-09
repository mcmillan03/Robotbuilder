// PSheetBase.cpp : implementation file
//

#include "stdafx.h"
#include "RBModeler.h"
#include "PSheetBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetBase

IMPLEMENT_DYNAMIC(CPSheetBase, CPropertySheet)

CPSheetBase::CPSheetBase(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
//	this->m_psh.dwFlags |= PSH_NOAPPLYNOW;
}


CPSheetBase::CPSheetBase(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
//	this->m_psh.dwFlags |= PSH_NOAPPLYNOW;
}

CPSheetBase::~CPSheetBase()
{
}


BEGIN_MESSAGE_MAP(CPSheetBase, CPropertySheet)
	//{{AFX_MSG_MAP(CPSheetBase)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetBase message handlers

