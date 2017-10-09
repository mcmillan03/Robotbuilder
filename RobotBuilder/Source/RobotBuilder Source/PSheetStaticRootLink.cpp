// PSheetStaticRootLink.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PSheetStaticRootLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetStaticRootLink

IMPLEMENT_DYNAMIC(CPSheetStaticRootLink, CPSheetLinkBase)

CPSheetStaticRootLink::CPSheetStaticRootLink(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetStaticRootLink::CPSheetStaticRootLink(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetStaticRootLink::~CPSheetStaticRootLink()
{
}


BEGIN_MESSAGE_MAP(CPSheetStaticRootLink, CPSheetLinkBase)
	//{{AFX_MSG_MAP(CPSheetStaticRootLink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetStaticRootLink message handlers

void CPSheetStaticRootLink::BuildPropertySheet()
{
	m_pCdmvStaticRootLinkData = NULL;

	this->AddPage (&m_ppageObjectData);
}

int CPSheetStaticRootLink::DoModal() 
{
	ASSERT (m_pCdmvStaticRootLinkData);
	
	m_ppageObjectData.m_pCdmvObject = (CdmvObject*) m_pCdmvStaticRootLinkData;
	
	return CPSheetLinkBase::DoModal();
}
