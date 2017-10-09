// PSheetRevoluteLink.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PSheetRevoluteLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetRevoluteLink

IMPLEMENT_DYNAMIC(CPSheetRevoluteLink, CPSheetLinkBase)

CPSheetRevoluteLink::CPSheetRevoluteLink(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetRevoluteLink::CPSheetRevoluteLink(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetRevoluteLink::~CPSheetRevoluteLink()
{
}


BEGIN_MESSAGE_MAP(CPSheetRevoluteLink, CPSheetLinkBase)
	//{{AFX_MSG_MAP(CPSheetRevoluteLink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetRevoluteLink message handlers

int CPSheetRevoluteLink::DoModal() 
{
	ASSERT (m_pCdmvRevoluteLinkData);
	
	m_ppageObjectData.m_pCdmvObject = (CdmvObject*) m_pCdmvRevoluteLinkData;
	m_ppageActuatorData.m_pCdmvRevoluteLinkData = m_pCdmvRevoluteLinkData;
	m_ppageRigidBodyData.m_pCdmvRigidBodyData = (CdmvRigidBodyData*) m_pCdmvRevoluteLinkData;
	m_ppageMDHLinkData.m_pCdmvMDHLinkData = (CdmvMDHLinkData*) m_pCdmvRevoluteLinkData;

	return CPSheetLinkBase::DoModal();
}

void CPSheetRevoluteLink::BuildPropertySheet()
{
	
	m_pCdmvRevoluteLinkData = NULL;

	this->AddPage (&m_ppageActuatorData);
	this->AddPage (&m_ppageMDHLinkData);
	this->AddPage (&m_ppageRigidBodyData);
	this->AddPage (&m_ppageObjectData);
}
