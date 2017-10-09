// PPageSphericalLinkData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PPageSphericalLinkData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageSphericalLinkData property page

IMPLEMENT_DYNCREATE(CPPageSphericalLinkData, CPPageLinkBase)

CPPageSphericalLinkData::CPPageSphericalLinkData() : CPPageLinkBase(CPPageSphericalLinkData::IDD)
{
	//{{AFX_DATA_INIT(CPPageSphericalLinkData)
	//}}AFX_DATA_INIT
	m_strtSphericalLinkJointLimits.fDamper = 0;
	m_strtSphericalLinkJointLimits.fSpring = 0;
	m_strtSphericalLinkJointLimits.fJointLimits[0] = 0;
	m_strtSphericalLinkJointLimits.fJointLimits[1] = 0;
	m_strtSphericalLinkJointLimits.fJointLimits[2] = 0;

	m_strtSphericalLinkState.eaAngles[0] = 0;
	m_strtSphericalLinkState.eaAngles[1] = 0;
	m_strtSphericalLinkState.eaAngles[2] = 0;
	m_strtSphericalLinkState.fAngularVelocity[0] = 0;
	m_strtSphericalLinkState.fAngularVelocity[1] = 0;
	m_strtSphericalLinkState.fAngularVelocity[2] = 0;

	m_cvJointOffsetPosition[0] = 0;
	m_cvJointOffsetPosition[1] = 0;
	m_cvJointOffsetPosition[2] = 0;

	m_pCdmvSphericalLinkData = NULL;
}

CPPageSphericalLinkData::~CPPageSphericalLinkData()
{
}

void CPPageSphericalLinkData::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageSphericalLinkData)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_AXES_LIMIT_X, m_strtSphericalLinkJointLimits.fJointLimits[0]);
	DDX_Text(pDX, IDC_EDIT_AXES_LIMIT_Y, m_strtSphericalLinkJointLimits.fJointLimits[1]);
	DDX_Text(pDX, IDC_EDIT_AXES_LIMIT_Z, m_strtSphericalLinkJointLimits.fJointLimits[2]);
	DDX_Text(pDX, IDC_EDIT_DAMPER_CONSTANT, m_strtSphericalLinkJointLimits.fDamper);
	DDV_MinMaxDouble(pDX,  m_strtSphericalLinkJointLimits.fDamper, SPHERICAL_LINK_DAMPER_CONSTANT_MIN, SPHERICAL_LINK_DAMPER_CONSTANT_MAX);
	DDX_Text(pDX, IDC_EDIT_INITIAL_ANGULAR_VELOCITY_X, m_strtSphericalLinkState.fAngularVelocity[0]);
	DDX_Text(pDX, IDC_EDIT_INITIAL_ANGULAR_VELOCITY_Y, m_strtSphericalLinkState.fAngularVelocity[1]);
	DDX_Text(pDX, IDC_EDIT_INITIAL_ANGULAR_VELOCITY_Z, m_strtSphericalLinkState.fAngularVelocity[2]);
	DDX_Text(pDX, IDC_EDIT_INITIAL_JOINT_ANGLE_1, m_strtSphericalLinkState.eaAngles[0]);
	DDV_MinMaxDouble(pDX,  m_strtSphericalLinkState.eaAngles[0], SPHERICAL_LINK_INITIAL_EULER_ANGLE_MIN, SPHERICAL_LINK_INITIAL_EULER_ANGLE_MAX);
	DDX_Text(pDX, IDC_EDIT_INITIAL_JOINT_ANGLE_2, m_strtSphericalLinkState.eaAngles[1]);
	DDV_MinMaxDouble(pDX,  m_strtSphericalLinkState.eaAngles[1], SPHERICAL_LINK_INITIAL_EULER_ANGLE_MIN, SPHERICAL_LINK_INITIAL_EULER_ANGLE_MAX);
	DDX_Text(pDX, IDC_EDIT_INITIAL_JOINT_ANGLE_3, m_strtSphericalLinkState.eaAngles[2]);
	DDV_MinMaxDouble(pDX,  m_strtSphericalLinkState.eaAngles[2], SPHERICAL_LINK_INITIAL_EULER_ANGLE_MIN, SPHERICAL_LINK_INITIAL_EULER_ANGLE_MAX);
	DDX_Text(pDX, IDC_EDIT_JOINT_OFFSET_X, m_cvJointOffsetPosition[0]);
	DDX_Text(pDX, IDC_EDIT_JOINT_OFFSET_Y, m_cvJointOffsetPosition[1]);
	DDX_Text(pDX, IDC_EDIT_JOINT_OFFSET_Z, m_cvJointOffsetPosition[2]);
	DDX_Text(pDX, IDC_EDIT_SPRING_CONSTANT, m_strtSphericalLinkJointLimits.fSpring);
	DDV_MinMaxDouble(pDX,  m_strtSphericalLinkJointLimits.fSpring, SPHERICAL_LINK_SPRING_CONSTANT_MIN, SPHERICAL_LINK_SPRING_CONSTANT_MAX);
}


BEGIN_MESSAGE_MAP(CPPageSphericalLinkData, CPPageLinkBase)
	//{{AFX_MSG_MAP(CPPageSphericalLinkData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageSphericalLinkData message handlers

BOOL CPPageSphericalLinkData::OnInitDialog() 
{
	CPPageLinkBase::OnInitDialog();
	
	ASSERT (m_pCdmvSphericalLinkData);

	m_pCdmvSphericalLinkData->GetLinkState (&m_strtSphericalLinkState);
	m_pCdmvSphericalLinkData->GetJointLimits (&m_strtSphericalLinkJointLimits);
	m_pCdmvSphericalLinkData->GetJointOffset (m_cvJointOffsetPosition);
	
	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPPageSphericalLinkData::OnOK() 
{
	m_pCdmvSphericalLinkData->SetLinkState (&m_strtSphericalLinkState);
	m_pCdmvSphericalLinkData->SetJointLimits (&m_strtSphericalLinkJointLimits);
	m_pCdmvSphericalLinkData->SetJointOffset (m_cvJointOffsetPosition);
	
	CPPageLinkBase::OnOK();
}
