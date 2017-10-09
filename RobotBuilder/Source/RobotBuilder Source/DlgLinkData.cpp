// DlgLinkData.cpp : implementation file
//

#include "stdafx.h"
#include "DMViewer.h"
#include "DlgLinkData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkData dialog


CDlgLinkData::CDlgLinkData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLinkData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLinkData)
	m_fJointFriction = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgLinkData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLinkData)
	DDX_Text(pDX, IDC_EDIT_JOINT_FRICTION, m_fJointFriction);
	DDV_MinMaxFloat(pDX, m_fJointFriction, LINK_JOINT_FRICTION_MIN, LINK_JOINT_FRICTION_MAX);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLinkData, CDialog)
	//{{AFX_MSG_MAP(CDlgLinkData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkData message handlers

void CDlgLinkData::SaveDialogData()
{
	ASSERT (m_pCdmvLinkData);

#ifdef DEBUG
	// The client should have already called UpdateData.
	BOOL bReturnStatus = UpdateData (TRUE);
	ASSERT (bReturnStatus);
#endif
	m_pCdmvLinkData->SetJointFriction (m_fJointFriction);

}

BOOL CDlgLinkData::OnInitDialog() 
{
	ASSERT (m_pCdmvLinkData);
	
	CDialog::OnInitDialog();
	
	m_fJointFriction = m_pCdmvLinkData->GetJointFriction ();

	// Set DDX the dialog data.
	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
