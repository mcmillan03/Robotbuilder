// PPageLinkBase.cpp : implementation file
//

#include "stdafx.h"
#include "DMViewer.h"
#include "PPageLinkBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageLinkBase property page

IMPLEMENT_DYNCREATE(CPPageLinkBase, CPropertyPage)

CPPageLinkBase::CPPageLinkBase(UINT nIDTemplate) : CPropertyPage(nIDTemplate)
{
	//{{AFX_DATA_INIT(CPPageLinkBase)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPPageLinkBase::~CPPageLinkBase()
{
}

void CPPageLinkBase::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageLinkBase)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPageLinkBase, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageLinkBase)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageLinkBase message handlers

CPPageLinkBase::CPPageLinkBase()
{

}

void CPPageLinkBase::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CPropertyPage::OnOK();
}
