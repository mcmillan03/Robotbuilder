// PPageMobileBaseLinkData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PPageMobileBaseLinkData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageMobileBaseLinkData property page

IMPLEMENT_DYNCREATE(CPPageMobileBaseLinkData, CPPageLinkBase)

CPPageMobileBaseLinkData::CPPageMobileBaseLinkData() : CPPageLinkBase(CPPageMobileBaseLinkData::IDD)
{
	//{{AFX_DATA_INIT(CPPageMobileBaseLinkData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_strtMobileBaseLinkState.cvPosition[0] = 0.0f;
	m_strtMobileBaseLinkState.cvPosition[1] = 0.0f;
	m_strtMobileBaseLinkState.cvPosition[2] = 0.0f;

	m_strtMobileBaseLinkState.qOrientation[0] = 0.0f;
	m_strtMobileBaseLinkState.qOrientation[1] = 0.0f;
	m_strtMobileBaseLinkState.qOrientation[2] = 0.0f;
	m_strtMobileBaseLinkState.qOrientation[3] = 0.0f;

	m_strtMobileBaseLinkState.svVelocity[0] = 0.0f;
	m_strtMobileBaseLinkState.svVelocity[1] = 0.0f;
	m_strtMobileBaseLinkState.svVelocity[2] = 0.0f;
	m_strtMobileBaseLinkState.svVelocity[3] = 0.0f;
	m_strtMobileBaseLinkState.svVelocity[4] = 0.0f;
	m_strtMobileBaseLinkState.svVelocity[5] = 0.0f;

	m_pCdmvMobileBaseLinkData = NULL;
}

CPPageMobileBaseLinkData::~CPPageMobileBaseLinkData()
{
}

void CPPageMobileBaseLinkData::DoDataExchange(CDataExchange* pDX)
{
	CPPageLinkBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageMobileBaseLinkData)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_POS1, m_strtMobileBaseLinkState.cvPosition[0]);
	DDX_Text(pDX, IDC_EDIT_POS2, m_strtMobileBaseLinkState.cvPosition[1]);
	DDX_Text(pDX, IDC_EDIT_POS3, m_strtMobileBaseLinkState.cvPosition[2]);
	DDX_Text(pDX, IDC_EDIT_QUAT1, m_strtMobileBaseLinkState.qOrientation[0]);
	DDX_Text(pDX, IDC_EDIT_QUAT2, m_strtMobileBaseLinkState.qOrientation[1]);
	DDX_Text(pDX, IDC_EDIT_QUAT3, m_strtMobileBaseLinkState.qOrientation[2]);
	DDX_Text(pDX, IDC_EDIT_QUAT4, m_strtMobileBaseLinkState.qOrientation[3]);
	DDX_Text(pDX, IDC_EDIT_VEL1, m_strtMobileBaseLinkState.svVelocity[0]);
	DDX_Text(pDX, IDC_EDIT_VEL2, m_strtMobileBaseLinkState.svVelocity[1]);
	DDX_Text(pDX, IDC_EDIT_VEL3, m_strtMobileBaseLinkState.svVelocity[2]);
	DDX_Text(pDX, IDC_EDIT_VEL4, m_strtMobileBaseLinkState.svVelocity[3]);
	DDX_Text(pDX, IDC_EDIT_VEL5, m_strtMobileBaseLinkState.svVelocity[4]);
	DDX_Text(pDX, IDC_EDIT_VEL6, m_strtMobileBaseLinkState.svVelocity[5]);
}


BEGIN_MESSAGE_MAP(CPPageMobileBaseLinkData, CPPageLinkBase)
	//{{AFX_MSG_MAP(CPPageMobileBaseLinkData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageMobileBaseLinkData message handlers

void CPPageMobileBaseLinkData::OnOK() 
{

	ASSERT (m_pCdmvMobileBaseLinkData);

	m_pCdmvMobileBaseLinkData->SetState (&m_strtMobileBaseLinkState);

	CPPageLinkBase::OnOK();
}

BOOL CPPageMobileBaseLinkData::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pCdmvMobileBaseLinkData);

	m_pCdmvMobileBaseLinkData->GetInitialState (&m_strtMobileBaseLinkState);
		
	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
