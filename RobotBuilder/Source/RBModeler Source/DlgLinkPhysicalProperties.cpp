// DlgLinkPhysicalProperties.cpp : implementation file
//

#include "stdafx.h"
#include "rbmodeler.h"
#include "DlgLinkPhysicalProperties.h"
#include "Model.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkPhysicalProperties dialog


CDlgLinkPhysicalProperties::CDlgLinkPhysicalProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLinkPhysicalProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLinkPhysicalProperties)
	m_dCenterOfGravityX = 0.0;
	m_dCenterOfGravityY = 0.0;
	m_dCenterOfGravityZ = 0.0;
	m_dTotalMass = 0.0;
	m_bAutoCalculatedData = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgLinkPhysicalProperties::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fCenterOfGravityX = (float) m_dCenterOfGravityX;
	float fCenterOfGravityY = (float) m_dCenterOfGravityY;
	float fCenterOfGravityZ = (float) m_dCenterOfGravityZ;

	float fInertiaTensor[3][3];
	int i, j;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			fInertiaTensor[i][j] = (float) m_dInertiaTensor[i][j];

	float fTotalMass = m_dTotalMass;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLinkPhysicalProperties)
	DDX_Text(pDX, IDC_EDIT_CENTER_OF_GRAVITY_X, fCenterOfGravityX);
	DDX_Text(pDX, IDC_EDIT_CENTER_OF_GRAVITY_Y, fCenterOfGravityY);
	DDX_Text(pDX, IDC_EDIT_CENTER_OF_GRAVITY_Z, fCenterOfGravityZ);
	DDX_Text(pDX, IDC_EDIT_TOTAL_MASS, fTotalMass);
	DDX_Check(pDX, IDC_CHECK_USE_USER_DATA, m_bAutoCalculatedData);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR11, fInertiaTensor[0][0]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR12, fInertiaTensor[0][1]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR13, fInertiaTensor[0][2]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR21, fInertiaTensor[1][0]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR22, fInertiaTensor[1][1]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR23, fInertiaTensor[1][2]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR31, fInertiaTensor[2][0]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR32, fInertiaTensor[2][1]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR33, fInertiaTensor[2][2]);
}


BEGIN_MESSAGE_MAP(CDlgLinkPhysicalProperties, CDialog)
	//{{AFX_MSG_MAP(CDlgLinkPhysicalProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkPhysicalProperties message handlers

BOOL CDlgLinkPhysicalProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLinkPhysicalProperties::SetModel(const CModel *pModel)
{
	// Start off by reseting the data
	m_dCenterOfGravityX = m_dCenterOfGravityY = m_dCenterOfGravityZ = 0;

	// Get COG from the model
	double dCenterOfGravity[3];
	pModel->GetModelCenterOfGravity (dCenterOfGravity);
	m_dCenterOfGravityX = dCenterOfGravity[0];
	m_dCenterOfGravityY = dCenterOfGravity[1];
	m_dCenterOfGravityZ = dCenterOfGravity[2];

	// Get inertia from model
	pModel->GetModelInertia (m_dInertiaTensor);

	// Get the total mass from the model
	m_dTotalMass = pModel->GetModelMass ();

	// Get state of user specified data
	m_bAutoCalculatedData = ! pModel->UseUserSuppliedDataForPhysicalData ();
}

BOOL CDlgLinkPhysicalProperties::GetUseUserSuppliedDataForPhysicalData() const
{
	return !m_bAutoCalculatedData;
}
