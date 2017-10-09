// PPageSecPrismaticJointData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PPageSecPrismaticJointData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageSecPrismaticJointData property page

IMPLEMENT_DYNCREATE(CPPageSecPrismaticJointData, CPropertyPage)

CPPageSecPrismaticJointData::CPPageSecPrismaticJointData() : CPropertyPage(CPPageSecPrismaticJointData::IDD)
{
	//{{AFX_DATA_INIT(CPPageSecPrismaticJointData)
	//}}AFX_DATA_INIT
	m_strtSecondaryPrismaticJointData.dLinearConstraintDamper = 0;
	m_strtSecondaryPrismaticJointData.dLinearConstraintSpring = 0;
	m_strtSecondaryPrismaticJointData.dAngularConstraintDamper = 0;
	m_strtSecondaryPrismaticJointData.dAngularConstraintSpring = 0;

	m_pCdmvSecPrisJntData = NULL;

}

CPPageSecPrismaticJointData::~CPPageSecPrismaticJointData()
{
}

void CPPageSecPrismaticJointData::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageSecPrismaticJointData)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_ANGULAR_CONSTRAINT_DAMPER, m_strtSecondaryPrismaticJointData.dAngularConstraintDamper);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryPrismaticJointData.dAngularConstraintDamper, SEC_JOINT_ANGULAR_DAMPER_MIN, SEC_JOINT_ANGULAR_DAMPER_MAX);
	DDX_Text(pDX, IDC_EDIT_ANGULAR_CONSTRAINT_SPRING, m_strtSecondaryPrismaticJointData.dAngularConstraintSpring);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryPrismaticJointData.dAngularConstraintSpring, SEC_JOINT_ANGULAR_SPRING_MIN, SEC_JOINT_ANGULAR_SPRING_MAX);
	DDX_Text(pDX, IDC_EDIT_LINEAR_CONSTRAINT_DAMPER, m_strtSecondaryPrismaticJointData.dLinearConstraintDamper);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryPrismaticJointData.dLinearConstraintDamper, SEC_JOINT_LINEAR_DAMPER_MIN, SEC_JOINT_LINEAR_DAMPER_MAX);
	DDX_Text(pDX, IDC_EDIT_LINEAR_CONSTRAINT_SPRING, m_strtSecondaryPrismaticJointData.dLinearConstraintSpring);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryPrismaticJointData.dLinearConstraintSpring, SEC_JOINT_LINEAR_SPRING_MIN, SEC_JOINT_LINEAR_SPRING_MAX);
}


BEGIN_MESSAGE_MAP(CPPageSecPrismaticJointData, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageSecPrismaticJointData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageSecPrismaticJointData message handlers

void CPPageSecPrismaticJointData::OnOK() 
{
	ASSERT (m_pCdmvSecPrisJntData);

	m_pCdmvSecPrisJntData->SetSecPrismaticJointData (&m_strtSecondaryPrismaticJointData);

	CPropertyPage::OnOK();
}

BOOL CPPageSecPrismaticJointData::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pCdmvSecPrisJntData);

	m_pCdmvSecPrisJntData->GetSecPrismaticJointData (&m_strtSecondaryPrismaticJointData);

	BOOL bReturn = UpdateData (FALSE);
	ASSERT (bReturn);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
