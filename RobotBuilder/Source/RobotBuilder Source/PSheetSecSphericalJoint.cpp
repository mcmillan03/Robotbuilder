// PSheetSecSphericalJoint.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PSheetSecSphericalJoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetSecSphericalJoint

IMPLEMENT_DYNAMIC(CPSheetSecSphericalJoint, CPSheetLinkBase)

CPSheetSecSphericalJoint::CPSheetSecSphericalJoint(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(nIDCaption, pParentWnd, iSelectPage), m_ppageObjectData (FALSE)
{
	BuildPropertySheet ();
}

CPSheetSecSphericalJoint::CPSheetSecSphericalJoint(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(pszCaption, pParentWnd, iSelectPage), m_ppageObjectData (FALSE)
{
	BuildPropertySheet ();
}

CPSheetSecSphericalJoint::~CPSheetSecSphericalJoint()
{
}


BEGIN_MESSAGE_MAP(CPSheetSecSphericalJoint, CPSheetLinkBase)
	//{{AFX_MSG_MAP(CPSheetSecSphericalJoint)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetSecSphericalJoint message handlers

void CPSheetSecSphericalJoint::BuildPropertySheet()
{
	m_pCdmvSecSpherJntData = NULL;
	m_pCdmvArticulationData = NULL;

	this->AddPage (&m_ppageSecJointData);
	this->AddPage (&m_ppageSecSphericalJointData);
	this->AddPage (&m_ppageObjectData);
}

int CPSheetSecSphericalJoint::DoModal() 
{
	ASSERT (m_pCdmvSecSpherJntData);
	ASSERT (m_pCdmvArticulationData);

	m_ppageSecJointData.m_pCdmvSecJointData = (CdmvSecJointData*) m_pCdmvSecSpherJntData;
	m_ppageSecJointData.m_pCdmvArticulationData = m_pCdmvArticulationData;
	m_ppageSecSphericalJointData.m_pCdmvSecSpherJntData = m_pCdmvSecSpherJntData;
	m_ppageObjectData.m_pCdmvObject = (CdmvObject*) m_pCdmvSecSpherJntData;
	
	return CPSheetLinkBase::DoModal();
}
