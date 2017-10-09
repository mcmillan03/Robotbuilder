// DlgConfigAxes.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgConfigAxes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigAxes dialog


CDlgConfigAxes::CDlgConfigAxes(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfigAxes::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConfigAxes)
	m_dInertialAxesLength = 0.0;
	m_nInertialAxesWidth = 0;
	m_dLinkAxesLength = 0.0;
	m_nLinkAxesWidth = 0;
	//}}AFX_DATA_INIT
	m_pCdmvCFGData = NULL;
}


void CDlgConfigAxes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConfigAxes)
	DDX_Text(pDX, IDC_EDIT_INERTIAL_AXES_LENGTH, m_dInertialAxesLength);
	DDV_MinMaxDouble(pDX, m_dInertialAxesLength, MINIMUM_AXES_LENGTH, MAXIMUM_AXES_LENGTH);
	DDX_Text(pDX, IDC_EDIT_INERTIAL_AXES_WIDTH, m_nInertialAxesWidth);
	DDV_MinMaxInt(pDX, m_nInertialAxesWidth, MINIMUM_AXES_WIDTH, MAXIMUM_AXES_WIDTH);
	DDX_Text(pDX, IDC_EDIT_LINK_AXES_LENGTH, m_dLinkAxesLength);
	DDV_MinMaxDouble(pDX, m_dLinkAxesLength, MINIMUM_AXES_LENGTH, MAXIMUM_AXES_LENGTH);
	DDX_Text(pDX, IDC_EDIT_LINK_AXES_WIDTH, m_nLinkAxesWidth);
	DDV_MinMaxInt(pDX, m_nLinkAxesWidth, MINIMUM_AXES_WIDTH, MAXIMUM_AXES_WIDTH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConfigAxes, CDialog)
	//{{AFX_MSG_MAP(CDlgConfigAxes)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigAxes message handlers

void CDlgConfigAxes::SetDataClass(CdmvCFGData *pCdmvCFGData)
{
	ASSERT (pCdmvCFGData);

	m_pCdmvCFGData = pCdmvCFGData;
}

BOOL CDlgConfigAxes::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make sure the data class has been set
	ASSERT (m_pCdmvCFGData);

	// Populate the data members with known values
	// Initialize the axes data
	m_pCdmvCFGData->GetInertialAxesData (m_nInertialAxesWidth, m_dInertialAxesLength);
	m_pCdmvCFGData->GetLinkAxesData (m_nLinkAxesWidth, m_dLinkAxesLength);

	// Reset the dialog items with the newly retrieved data
	BOOL bSuccess;
	bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgConfigAxes::ValidateAndSaveData()
{
	//Validate
	if (ValidateData())
	{
		//Save the data
		m_pCdmvCFGData->SetInertialAxesData (m_nInertialAxesWidth, m_dInertialAxesLength);
		m_pCdmvCFGData->SetLinkAxesData (m_nLinkAxesWidth, m_dLinkAxesLength);

		return TRUE;
	}
	else
	{	//Validation failed

		return FALSE;
	}
}

BOOL CDlgConfigAxes::ValidateData()
{
	return UpdateData(TRUE);
}
