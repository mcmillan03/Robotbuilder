// PPageZScrewTxLinkData.cpp : implementation file
//

#include "stdafx.h"
#include "DMViewer.h"
#include "PPageZScrewTxLinkData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageZScrewTxLinkData property page

IMPLEMENT_DYNCREATE(CPPageZScrewTxLinkData, CPPageLinkBase)

CPPageZScrewTxLinkData::CPPageZScrewTxLinkData() : CPPageLinkBase(CPPageZScrewTxLinkData::IDD)
{
	//{{AFX_DATA_INIT(CPPageZScrewTxLinkData)
	//}}AFX_DATA_INIT
	m_pCdmvZScrewTxLinkData = NULL;
	m_strtZScrewTxLinkParameters.fD = 0.0f;
	m_strtZScrewTxLinkParameters.fTheta = 0.0f;
}

CPPageZScrewTxLinkData::~CPPageZScrewTxLinkData()
{
}

void CPPageZScrewTxLinkData::DoDataExchange(CDataExchange* pDX)
{
	CPPageLinkBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageZScrewTxLinkData)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_MDH_D, m_strtZScrewTxLinkParameters.fD);
	DDX_Text(pDX, IDC_EDIT_MDH_THETA, m_strtZScrewTxLinkParameters.fTheta);
}


BEGIN_MESSAGE_MAP(CPPageZScrewTxLinkData, CPPageLinkBase)
	//{{AFX_MSG_MAP(CPPageZScrewTxLinkData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageZScrewTxLinkData message handlers

BOOL CPPageZScrewTxLinkData::OnInitDialog() 
{
	CPPageLinkBase::OnInitDialog();
	
	ASSERT (m_pCdmvZScrewTxLinkData);

	m_pCdmvZScrewTxLinkData->GetParameters (&m_strtZScrewTxLinkParameters);
	
	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPPageZScrewTxLinkData::OnOK() 
{
	ASSERT (m_pCdmvZScrewTxLinkData);

	m_pCdmvZScrewTxLinkData->SetParameters (&m_strtZScrewTxLinkParameters);
	
	CPPageLinkBase::OnOK();
}


