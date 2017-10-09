// PPageMDHLinkData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PPageMDHLinkData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageMDHLinkData property page

IMPLEMENT_DYNCREATE(CPPageMDHLinkData, CPPageLinkBase)

CPPageMDHLinkData::CPPageMDHLinkData() : CPPageLinkBase(CPPageMDHLinkData::IDD)
{
	//{{AFX_DATA_INIT(CPPageMDHLinkData)
	//}}AFX_DATA_INIT
	// init members
	m_strtMDHParameters.fa = 0;
	m_strtMDHParameters.fAlpha = 0;
	m_strtMDHParameters.fd = 0;
	m_strtMDHParameters.fTheta = 0;

	m_strtMDHLinkJointLimits.fMin = 0;
	m_strtMDHLinkJointLimits.fMax = 0;
	m_strtMDHLinkJointLimits.fSpring = 0;
	m_strtMDHLinkJointLimits.fDamper = 0;

	m_fInitialJointVelocity = 0;

	m_pCdmvMDHLinkData = NULL;
}

CPPageMDHLinkData::~CPPageMDHLinkData()
{
}

void CPPageMDHLinkData::DoDataExchange(CDataExchange* pDX)
{
	CPPageLinkBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageMDHLinkData)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_JOINT_DAMPER, m_strtMDHLinkJointLimits.fDamper);
	DDV_MinMaxDouble(pDX, m_strtMDHLinkJointLimits.fDamper, MDH_LINK_JOINT_DAMPER_MIN, MDH_LINK_JOINT_DAMPER_MAX);
	DDX_Text(pDX, IDC_EDIT_JOINT_MAXIMUM, m_strtMDHLinkJointLimits.fMax);
	DDX_Text(pDX, IDC_EDIT_JOINT_MINIMUM, m_strtMDHLinkJointLimits.fMin);
	DDX_Text(pDX, IDC_EDIT_JOINT_SPRING, m_strtMDHLinkJointLimits.fSpring);
	DDV_MinMaxDouble(pDX, m_strtMDHLinkJointLimits.fSpring, MDH_LINK_JOINT_SPRING_MIN, MDH_LINK_JOINT_SPRING_MAX);
	DDX_Text(pDX, IDC_EDIT_MDH_A, m_strtMDHParameters.fa);
	DDX_Text(pDX, IDC_EDIT_MDH_ALPHA, m_strtMDHParameters.fAlpha);
	DDV_MinMaxDouble(pDX, m_strtMDHParameters.fAlpha, MDH_LINK_ALPHA_MIN, MDH_LINK_ALPHA_MAX);
	DDX_Text(pDX, IDC_EDIT_MDH_D, m_strtMDHParameters.fd);
	DDX_Text(pDX, IDC_EDIT_MDH_THETA, m_strtMDHParameters.fTheta);
	DDX_Text(pDX, IDC_EDIT_STATE_DQ, m_fInitialJointVelocity);
}


BEGIN_MESSAGE_MAP(CPPageMDHLinkData, CPPageLinkBase)
	//{{AFX_MSG_MAP(CPPageMDHLinkData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageMDHLinkData message handlers

void CPPageMDHLinkData::OnOK() 
{
	ASSERT (m_pCdmvMDHLinkData);

	m_pCdmvMDHLinkData->SetMDHParameters (&m_strtMDHParameters);
	m_pCdmvMDHLinkData->SetInitialJointVelocity (m_fInitialJointVelocity);
	m_pCdmvMDHLinkData->SetJointLimits (&m_strtMDHLinkJointLimits);
	

	CPPageLinkBase::OnOK();
}

BOOL CPPageMDHLinkData::OnInitDialog() 
{
	CPPageLinkBase::OnInitDialog();
	
	ASSERT (m_pCdmvMDHLinkData);
	m_pCdmvMDHLinkData->GetMDHParameters (&m_strtMDHParameters);
	m_fInitialJointVelocity = m_pCdmvMDHLinkData->GetInitialJointVelocity ();
	m_pCdmvMDHLinkData->GetJointLimits (&m_strtMDHLinkJointLimits);

	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
