// PSheetSphericalLink.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PSheetSphericalLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetSphericalLink

IMPLEMENT_DYNAMIC(CPSheetSphericalLink, CPSheetLinkBase)

CPSheetSphericalLink::CPSheetSphericalLink(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetSphericalLink::CPSheetSphericalLink(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetSphericalLink::~CPSheetSphericalLink()
{
}


BEGIN_MESSAGE_MAP(CPSheetSphericalLink, CPSheetLinkBase)
	//{{AFX_MSG_MAP(CPSheetSphericalLink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetSphericalLink message handlers

int CPSheetSphericalLink::DoModal() 
{
	ASSERT (m_pCdmvSphericalLinkData);
	
	m_ppageSphericalLinkData.m_pCdmvSphericalLinkData = m_pCdmvSphericalLinkData;
	m_ppageObjectData.m_pCdmvObject = (CdmvObject*) m_pCdmvSphericalLinkData;
	m_ppageRigidBodyData.m_pCdmvRigidBodyData = (CdmvRigidBodyData*) m_pCdmvSphericalLinkData;
	m_ppageLinkData.m_pCdmvLinkData = (CdmvLinkData*) m_pCdmvSphericalLinkData;
	
	return CPSheetLinkBase::DoModal();
}

void CPSheetSphericalLink::BuildPropertySheet()
{
	m_pCdmvSphericalLinkData = NULL;

	this->AddPage (&m_ppageSphericalLinkData);
	this->AddPage (&m_ppageLinkData);
	this->AddPage (&m_ppageRigidBodyData);
	this->AddPage (&m_ppageObjectData);
}
