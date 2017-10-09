// PPageSecSphericalJointData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PPageSecSphericalJointData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageSecSphericalJointData property page

IMPLEMENT_DYNCREATE(CPPageSecSphericalJointData, CPropertyPage)

CPPageSecSphericalJointData::CPPageSecSphericalJointData() : CPropertyPage(CPPageSecSphericalJointData::IDD)
{
	//{{AFX_DATA_INIT(CPPageSecSphericalJointData)
	//}}AFX_DATA_INIT
	m_strtSecondarySphericalJointData.dLinearConstraintDamper = 0;
	m_strtSecondarySphericalJointData.dLinearConstraintSpring = 0;

	m_pCdmvSecSpherJntData = NULL;
}

CPPageSecSphericalJointData::~CPPageSecSphericalJointData()
{
}

void CPPageSecSphericalJointData::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageSecSphericalJointData)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_LINEAR_CONSTRAINT_DAMPER, m_strtSecondarySphericalJointData.dLinearConstraintDamper);
	DDV_MinMaxDouble(pDX,  m_strtSecondarySphericalJointData.dLinearConstraintDamper, SEC_JOINT_LINEAR_DAMPER_MIN, SEC_JOINT_LINEAR_DAMPER_MAX);
	DDX_Text(pDX, IDC_EDIT_LINEAR_CONSTRAINT_SPRING, m_strtSecondarySphericalJointData.dLinearConstraintSpring);
	DDV_MinMaxDouble(pDX,  m_strtSecondarySphericalJointData.dLinearConstraintSpring, SEC_JOINT_LINEAR_SPRING_MIN, SEC_JOINT_LINEAR_SPRING_MAX);
}


BEGIN_MESSAGE_MAP(CPPageSecSphericalJointData, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageSecSphericalJointData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageSecSphericalJointData message handlers

void CPPageSecSphericalJointData::OnOK() 
{
	ASSERT (m_pCdmvSecSpherJntData);

	m_pCdmvSecSpherJntData->SetSecSphericalJointData (&m_strtSecondarySphericalJointData);
	
	CPropertyPage::OnOK();
}

BOOL CPPageSecSphericalJointData::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	

	ASSERT (m_pCdmvSecSpherJntData);

	m_pCdmvSecSpherJntData->GetSecSphericalJointData (&m_strtSecondarySphericalJointData);

	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
