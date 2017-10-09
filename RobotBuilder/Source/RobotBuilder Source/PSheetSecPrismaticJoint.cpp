// PSheetSecPrismaticJoint.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PSheetSecPrismaticJoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetSecPrismaticJoint

IMPLEMENT_DYNAMIC(CPSheetSecPrismaticJoint, CPSheetLinkBase)

CPSheetSecPrismaticJoint::CPSheetSecPrismaticJoint(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(nIDCaption, pParentWnd, iSelectPage), m_ppageObjectData (FALSE)
{
	BuildPropertySheet ();
}

CPSheetSecPrismaticJoint::CPSheetSecPrismaticJoint(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(pszCaption, pParentWnd, iSelectPage), m_ppageObjectData (FALSE)
{
	BuildPropertySheet ();
}

CPSheetSecPrismaticJoint::~CPSheetSecPrismaticJoint()
{
}


BEGIN_MESSAGE_MAP(CPSheetSecPrismaticJoint, CPSheetLinkBase)
	//{{AFX_MSG_MAP(CPSheetSecPrismaticJoint)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetSecPrismaticJoint message handlers

void CPSheetSecPrismaticJoint::BuildPropertySheet()
{
	m_pCdmvSecPrisJntData = NULL;
	m_pCdmvArticulationData = NULL;

	this->AddPage (&m_ppageSecJointData);
	this->AddPage (&m_ppageSecPrismaticJointData);
	this->AddPage (&m_ppageObjectData);
}

int CPSheetSecPrismaticJoint::DoModal() 
{
	ASSERT (m_pCdmvSecPrisJntData);
	ASSERT (m_pCdmvArticulationData);

	m_ppageSecJointData.m_pCdmvSecJointData = (CdmvSecJointData*) m_pCdmvSecPrisJntData;
	m_ppageSecJointData.m_pCdmvArticulationData = m_pCdmvArticulationData;
	m_ppageSecPrismaticJointData.m_pCdmvSecPrisJntData = m_pCdmvSecPrisJntData;
	m_ppageObjectData.m_pCdmvObject = (CdmvObject*) m_pCdmvSecPrisJntData;
	
	return CPSheetLinkBase::DoModal();
}
