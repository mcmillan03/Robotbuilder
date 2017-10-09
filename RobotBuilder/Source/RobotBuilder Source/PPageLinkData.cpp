// PPageLinkData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PPageLinkData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageLinkData property page

IMPLEMENT_DYNCREATE(CPPageLinkData, CPPageLinkBase)

CPPageLinkData::CPPageLinkData() : CPPageLinkBase(CPPageLinkData::IDD)
{
	//{{AFX_DATA_INIT(CPPageLinkData)
	m_fJointFriction = 0.0f;
	//}}AFX_DATA_INIT
	m_pCdmvLinkData = NULL;
}

CPPageLinkData::~CPPageLinkData()
{
}

void CPPageLinkData::DoDataExchange(CDataExchange* pDX)
{
	CPPageLinkBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageLinkData)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_JOINT_FRICTION, m_fJointFriction);
	DDV_MinMaxFloat(pDX, m_fJointFriction, LINK_JOINT_FRICTION_MIN, LINK_JOINT_FRICTION_MAX);
}


BEGIN_MESSAGE_MAP(CPPageLinkData, CPPageLinkBase)
	//{{AFX_MSG_MAP(CPPageLinkData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageLinkData message handlers

void CPPageLinkData::OnOK() 
{
	ASSERT (m_pCdmvLinkData);

	m_pCdmvLinkData->SetJointFriction (m_fJointFriction);
	
	CPPageLinkBase::OnOK();
}

BOOL CPPageLinkData::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pCdmvLinkData);

	m_fJointFriction = m_pCdmvLinkData->GetJointFriction ();

	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
