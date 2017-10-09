// PPageArticulationData.cpp : implementation file
//

#include "stdafx.h"
#include "DMViewer.h"
#include "PPageArticulationData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageArticulationData property page

IMPLEMENT_DYNCREATE(CPPageArticulationData, CPPageLinkBase)

CPPageArticulationData::CPPageArticulationData() : CPPageLinkBase(CPPageArticulationData::IDD)
{
	//{{AFX_DATA_INIT(CPPageArticulationData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_cvPosition[0] = 0.0f;
	m_cvPosition[1] = 0.0f;
	m_cvPosition[2] = 0.0f;

	m_qOrientation[0] = 0.0f;
	m_qOrientation[1] = 0.0f;
	m_qOrientation[2] = 0.0f;
	m_qOrientation[3] = 0.0f;

	m_pCdmvArticulationData = NULL;
}

CPPageArticulationData::~CPPageArticulationData()
{
}

void CPPageArticulationData::DoDataExchange(CDataExchange* pDX)
{
	CPPageLinkBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageArticulationData)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_POS1, m_cvPosition[0]);
	DDX_Text(pDX, IDC_EDIT_POS2, m_cvPosition[1]);
	DDX_Text(pDX, IDC_EDIT_POS3, m_cvPosition[2]);
	DDX_Text(pDX, IDC_EDIT_QUAT1, m_qOrientation[0]);
	DDX_Text(pDX, IDC_EDIT_QUAT2, m_qOrientation[1]);
	DDX_Text(pDX, IDC_EDIT_QUAT3, m_qOrientation[2]);
	DDX_Text(pDX, IDC_EDIT_QUAT4, m_qOrientation[3]);

}


BEGIN_MESSAGE_MAP(CPPageArticulationData, CPPageLinkBase)
	//{{AFX_MSG_MAP(CPPageArticulationData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageArticulationData message handlers

void CPPageArticulationData::OnOK() 
{
	ASSERT (m_pCdmvArticulationData);

	m_pCdmvArticulationData->SetReferenceSystem (m_qOrientation, m_cvPosition);
	
	CPPageLinkBase::OnOK();
}

BOOL CPPageArticulationData::OnInitDialog() 
{
	CPPageLinkBase::OnInitDialog();
	
	ASSERT (m_pCdmvArticulationData);

	m_pCdmvArticulationData->GetRefSystem (m_qOrientation, m_cvPosition);
	
	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
