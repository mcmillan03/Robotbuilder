// PSheetSecRevoluteJoint.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PSheetSecRevoluteJoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetSecRevoluteJoint

IMPLEMENT_DYNAMIC(CPSheetSecRevoluteJoint, CPSheetLinkBase)

CPSheetSecRevoluteJoint::CPSheetSecRevoluteJoint(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(nIDCaption, pParentWnd, iSelectPage), m_ppageObjectData (FALSE)
{
	BuildPropertySheet ();
}

CPSheetSecRevoluteJoint::CPSheetSecRevoluteJoint(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(pszCaption, pParentWnd, iSelectPage), m_ppageObjectData (FALSE)
{
	BuildPropertySheet ();
}

CPSheetSecRevoluteJoint::~CPSheetSecRevoluteJoint()
{
}


BEGIN_MESSAGE_MAP(CPSheetSecRevoluteJoint, CPSheetLinkBase)
	//{{AFX_MSG_MAP(CPSheetSecRevoluteJoint)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetSecRevoluteJoint message handlers

int CPSheetSecRevoluteJoint::DoModal() 
{
	ASSERT (m_pCdmvSecRevJntData);
	ASSERT (m_pCdmvArticulationData);

	m_ppageSecJointData.m_pCdmvSecJointData = (CdmvSecJointData*) m_pCdmvSecRevJntData;
	m_ppageSecJointData.m_pCdmvArticulationData = m_pCdmvArticulationData;
	m_ppageSecRevoluteJointData.m_pCdmvSecRevJntData = m_pCdmvSecRevJntData;
	m_ppageObjectData.m_pCdmvObject = (CdmvObject*) m_pCdmvSecRevJntData;
	
	return CPSheetLinkBase::DoModal();
}

void CPSheetSecRevoluteJoint::BuildPropertySheet()
{
	m_pCdmvSecRevJntData = NULL;
	m_pCdmvArticulationData = NULL;

	this->AddPage (&m_ppageSecJointData);
	this->AddPage (&m_ppageSecRevoluteJointData);
	this->AddPage (&m_ppageObjectData);
}
