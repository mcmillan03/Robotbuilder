// PSheetMobileBaseLink.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PSheetMobileBaseLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetMobileBaseLink

IMPLEMENT_DYNAMIC(CPSheetMobileBaseLink, CPSheetLinkBase)

CPSheetMobileBaseLink::CPSheetMobileBaseLink(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetMobileBaseLink::CPSheetMobileBaseLink(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetMobileBaseLink::~CPSheetMobileBaseLink()
{
}


BEGIN_MESSAGE_MAP(CPSheetMobileBaseLink, CPSheetLinkBase)
	//{{AFX_MSG_MAP(CPSheetMobileBaseLink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetMobileBaseLink message handlers

int CPSheetMobileBaseLink::DoModal() 
{
	ASSERT (m_pCdmvMobileBaseLinkData);

	m_ppageMobileBaseLinkData.m_pCdmvMobileBaseLinkData = m_pCdmvMobileBaseLinkData;
	m_ppageRigidBodyData.m_pCdmvRigidBodyData = (CdmvRigidBodyData*) m_pCdmvMobileBaseLinkData;
	m_ppageLinkData.m_pCdmvLinkData = (CdmvLinkData*) m_pCdmvMobileBaseLinkData;
	m_ppageObjectData.m_pCdmvObject = (CdmvObject*) m_pCdmvMobileBaseLinkData;
	
	return CPSheetLinkBase::DoModal();
}

void CPSheetMobileBaseLink::BuildPropertySheet()
{
	m_pCdmvMobileBaseLinkData = NULL;

	this->AddPage (&m_ppageMobileBaseLinkData);
	this->AddPage (&m_ppageRigidBodyData);
	this->AddPage (&m_ppageLinkData);
	this->AddPage (&m_ppageObjectData);

}
