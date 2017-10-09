// PSheetZScrewTxLink.cpp : implementation file
//

#include "stdafx.h"
#include "DMViewer.h"
#include "PSheetZScrewTxLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetZScrewTxLink

IMPLEMENT_DYNAMIC(CPSheetZScrewTxLink, CPSheetLinkBase)

CPSheetZScrewTxLink::CPSheetZScrewTxLink(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
:CPSheetLinkBase(nIDCaption, pParentWnd, iSelectPage),m_ppageObjectData (FALSE)
{
	BuildPropertySheet ();
}

CPSheetZScrewTxLink::CPSheetZScrewTxLink(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(pszCaption, pParentWnd, iSelectPage),m_ppageObjectData (FALSE)
{
	BuildPropertySheet ();
}

CPSheetZScrewTxLink::~CPSheetZScrewTxLink()
{
}


BEGIN_MESSAGE_MAP(CPSheetZScrewTxLink, CPSheetLinkBase)
	//{{AFX_MSG_MAP(CPSheetZScrewTxLink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetZScrewTxLink message handlers

void CPSheetZScrewTxLink::BuildPropertySheet()
{
	// Initialize the members
	m_pCdmvZScrewTxLinkData = NULL;
	// Add the pages.
	this->AddPage (&m_ppageZScrewTxLinkData);
	this->AddPage (&m_ppageObjectData);
}

int CPSheetZScrewTxLink::DoModal() 
{
	ASSERT (m_pCdmvZScrewTxLinkData);
	
	// Perform the initializations here of the component pages
	m_ppageZScrewTxLinkData.m_pCdmvZScrewTxLinkData = m_pCdmvZScrewTxLinkData;
	m_ppageObjectData.m_pCdmvObject = (CdmvObject*) m_pCdmvZScrewTxLinkData;
	
	return CPSheetLinkBase::DoModal();
}
