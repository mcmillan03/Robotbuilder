// PSheetPrismaticLink.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PSheetPrismaticLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetPrismaticLink

IMPLEMENT_DYNAMIC(CPSheetPrismaticLink, CPSheetLinkBase)

CPSheetPrismaticLink::CPSheetPrismaticLink(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetPrismaticLink::CPSheetPrismaticLink(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetPrismaticLink::~CPSheetPrismaticLink()
{
}


BEGIN_MESSAGE_MAP(CPSheetPrismaticLink, CPSheetLinkBase)
	//{{AFX_MSG_MAP(CPSheetPrismaticLink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetPrismaticLink message handlers

void CPSheetPrismaticLink::BuildPropertySheet()
{
	m_pCdmvPrismaticLinkData = NULL;

	this->AddPage (&m_ppageLinkData);
	this->AddPage (&m_ppageMDHLinkData);
	this->AddPage (&m_ppageRigidBodyData);
	this->AddPage (&m_ppageObjectData);
}

int CPSheetPrismaticLink::DoModal() 
{
	ASSERT (m_pCdmvPrismaticLinkData);
	
	m_ppageObjectData.m_pCdmvObject = (CdmvObject*) m_pCdmvPrismaticLinkData;
	m_ppageRigidBodyData.m_pCdmvRigidBodyData = (CdmvRigidBodyData*) m_pCdmvPrismaticLinkData;
	m_ppageMDHLinkData.m_pCdmvMDHLinkData = (CdmvMDHLinkData*) m_pCdmvPrismaticLinkData;
	m_ppageLinkData.m_pCdmvLinkData = (CdmvLinkData*) m_pCdmvPrismaticLinkData;

	return CPSheetLinkBase::DoModal();
}
