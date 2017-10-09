// PPagePhysicalProperties.cpp : implementation file
//

#include "stdafx.h"
#include "rbModeler.h"
#include "PPagePhysicalProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPagePhysicalProperties property page

IMPLEMENT_DYNCREATE(CPPagePhysicalProperties, CPropertyPage)

CPPagePhysicalProperties::CPPagePhysicalProperties() : CPropertyPage(CPPagePhysicalProperties::IDD)
{
	//{{AFX_DATA_INIT(CPPagePhysicalProperties)
	m_dMass = 0.0;
	//}}AFX_DATA_INIT

	m_pPrimitive = NULL;
	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			m_dInertiaTensor[i][j] = 0;
}

CPPagePhysicalProperties::~CPPagePhysicalProperties()
{
}

void CPPagePhysicalProperties::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fInertiaTensor[3][3];
	float fCOG[3];
	int i, j;

	for (i = 0; i < 3; i++)
	{
		fCOG[i] = m_dCOG[i];
		for (j = 0; j < 3; j++)
			fInertiaTensor[i][j] = (float) m_dInertiaTensor[i][j];
	}
	float fMass = (float) m_dMass;	

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPagePhysicalProperties)
	DDX_Text(pDX, IDC_EDIT_MASS, fMass);
	DDV_MinMaxFloat(pDX, fMass, PRIMITIVE_MASS_MIN, PRIMITIVE_MASS_MAX);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_COG_X, fCOG[0]);
	DDX_Text(pDX, IDC_EDIT_COG_Y, fCOG[1]);
	DDX_Text(pDX, IDC_EDIT_COG_Z, fCOG[2]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR11, fInertiaTensor[0][0]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR12, fInertiaTensor[0][1]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR13, fInertiaTensor[0][2]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR21, fInertiaTensor[1][0]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR22, fInertiaTensor[1][1]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR23, fInertiaTensor[1][2]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR31, fInertiaTensor[2][0]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR32, fInertiaTensor[2][1]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_TENSOR33, fInertiaTensor[2][2]);

	// Inertia and COG are read-only, so don't need to copy back
//	for (i = 0; i < 3; i++)
//	{
//		m_dCOG[i] = fCOG[i];
//		for (j = 0; j < 3; j++)
//			m_dInertiaTensor[i][j] = fInertiaTensor[i][j];
//	}

	m_dMass = fMass;

}


BEGIN_MESSAGE_MAP(CPPagePhysicalProperties, CPropertyPage)
	//{{AFX_MSG_MAP(CPPagePhysicalProperties)
	ON_EN_CHANGE(IDC_EDIT_MASS, OnChangeEditMass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPagePhysicalProperties message handlers

void CPPagePhysicalProperties::OnChangeEditMass() 
{
	SetModified ();	
}

BOOL CPPagePhysicalProperties::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// Make sure the primitive was set
	ASSERT (m_pPrimitive);

	// Get the mass
	m_dMass = m_pPrimitive->GetMass ();

	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPPagePhysicalProperties::OnApply() 
{
	ASSERT (m_pPrimitive);
	// Save the new mass and update the inertia tensor
	m_pPrimitive->SetMass (m_dMass);
	// Note: I can't seem how to find out if the OK or apply button was pressed
	// so I will always update the inertia tensor.
	m_pPrimitive->GetInertiaTensor (m_dInertiaTensor);
	
	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);

	return CPropertyPage::OnApply();
}

BOOL CPPagePhysicalProperties::OnSetActive() 
{
	// Since changes in other parts of the property sheet can affect these values
	// (like the translation amount), they need to be refreshed when the page is
	// made active

	// Get center of gravity (in link coordinate frame)
	m_pPrimitive->GetCenterOfGravity (m_dCOG);

	// Calculate the inertia tensor
	m_pPrimitive->GetInertiaTensor (m_dInertiaTensor);

	
	VERIFY (UpdateData (FALSE));

	return CPropertyPage::OnSetActive();
}
