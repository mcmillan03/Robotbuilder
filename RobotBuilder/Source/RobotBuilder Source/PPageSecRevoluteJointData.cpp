// PPageSecRevoluteJointData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PPageSecRevoluteJointData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageSecRevoluteJointData property page

IMPLEMENT_DYNCREATE(CPPageSecRevoluteJointData, CPropertyPage)

CPPageSecRevoluteJointData::CPPageSecRevoluteJointData() : CPropertyPage(CPPageSecRevoluteJointData::IDD)
{
	//{{AFX_DATA_INIT(CPPageSecRevoluteJointData)
	//}}AFX_DATA_INIT

	m_strtSecondaryRevoluteJointData.dLinearConstraintDamper = 0;
	m_strtSecondaryRevoluteJointData.dLinearConstraintSpring = 0;
	m_strtSecondaryRevoluteJointData.dAngularConstraintDamper = 0;
	m_strtSecondaryRevoluteJointData.dAngularConstraintSpring = 0;

	m_pCdmvSecRevJntData = NULL;
}

CPPageSecRevoluteJointData::~CPPageSecRevoluteJointData()
{
}

void CPPageSecRevoluteJointData::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageSecRevoluteJointData)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_ANGULAR_CONSTRAINT_DAMPER, m_strtSecondaryRevoluteJointData.dAngularConstraintDamper);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryRevoluteJointData.dAngularConstraintDamper, SEC_JOINT_ANGULAR_DAMPER_MIN, SEC_JOINT_ANGULAR_DAMPER_MAX);
	DDX_Text(pDX, IDC_EDIT_ANGULAR_CONSTRAINT_SPRING, m_strtSecondaryRevoluteJointData.dAngularConstraintSpring);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryRevoluteJointData.dAngularConstraintSpring, SEC_JOINT_ANGULAR_SPRING_MIN, SEC_JOINT_ANGULAR_SPRING_MAX);
	DDX_Text(pDX, IDC_EDIT_LINEAR_CONSTRAINT_DAMPER, m_strtSecondaryRevoluteJointData.dLinearConstraintDamper);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryRevoluteJointData.dLinearConstraintDamper, SEC_JOINT_LINEAR_DAMPER_MIN, SEC_JOINT_LINEAR_DAMPER_MAX);
	DDX_Text(pDX, IDC_EDIT_LINEAR_CONSTRAINT_SPRING, m_strtSecondaryRevoluteJointData.dLinearConstraintSpring);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryRevoluteJointData.dLinearConstraintSpring, SEC_JOINT_LINEAR_SPRING_MIN, SEC_JOINT_LINEAR_SPRING_MAX);

}


BEGIN_MESSAGE_MAP(CPPageSecRevoluteJointData, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageSecRevoluteJointData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageSecRevoluteJointData message handlers

void CPPageSecRevoluteJointData::OnOK() 
{
	ASSERT (m_pCdmvSecRevJntData);

	m_pCdmvSecRevJntData->SetSecRevoluteJointData (&m_strtSecondaryRevoluteJointData);
	

	CPropertyPage::OnOK();
}

BOOL CPPageSecRevoluteJointData::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pCdmvSecRevJntData);

	m_pCdmvSecRevJntData->GetSecRevoluteJointData (&m_strtSecondaryRevoluteJointData);

	BOOL bReturn = UpdateData (FALSE);
	ASSERT (bReturn);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
