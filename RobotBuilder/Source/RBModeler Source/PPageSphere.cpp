// PPageSphere.cpp : implementation file
//

#include "stdafx.h"
#include "RBModeler.h"
#include "PPageSphere.h"
#include "RBModelerRBMGraphicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// todo: finish enabling the apply button cases

/////////////////////////////////////////////////////////////////////////////
// CPPageSphere property page

IMPLEMENT_DYNCREATE(CPPageSphere, CPropertyPage)

CPPageSphere::CPPageSphere() : CPropertyPage(CPPageSphere::IDD)
{
	//{{AFX_DATA_INIT(CPPageSphere)
	//}}AFX_DATA_INIT
	m_strtPrimitiveSphereData.dRadius = 1;
	m_strtPrimitiveSphereData.nLatitudeCount = 1;
	m_strtPrimitiveSphereData.nLongitudeCount = 1;
	m_strtPrimitiveSphereData.bRenderBothSides = FALSE;
	m_strtPrimitiveSphereData.bUseGouraudShading = FALSE;

	m_pPrimitiveSphere = NULL;
}

CPPageSphere::~CPPageSphere()
{
}

void CPPageSphere::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fRadius = (float) m_strtPrimitiveSphereData.dRadius;

	
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageSphere)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_RADIUS, fRadius);
	DDV_MinMaxFloat(pDX, fRadius, SPHERE_RADIUS_MIN, SPHERE_RADIUS_MAX);
	DDX_Check(pDX, IDC_CHECK_BOTH_SIDES, m_strtPrimitiveSphereData.bRenderBothSides);
	DDX_Check(pDX, IDC_CHECK_GOURAUD, m_strtPrimitiveSphereData.bUseGouraudShading);
	DDX_Text(pDX, IDC_EDIT_LATITUDE, m_strtPrimitiveSphereData.nLatitudeCount);
	DDV_MinMaxInt(pDX, m_strtPrimitiveSphereData.nLatitudeCount, SPHERE_LATITUDE_COUNT_MIN, SPHERE_LATITUDE_COUNT_MAX);
	DDX_Text(pDX, IDC_EDIT_LONGITUDE, m_strtPrimitiveSphereData.nLongitudeCount);
	DDV_MinMaxInt(pDX, m_strtPrimitiveSphereData.nLongitudeCount, SPHERE_LONGITUDE_COUNT_MIN, SPHERE_LONGITUDE_COUNT_MAX);

	m_strtPrimitiveSphereData.dRadius = fRadius;
}


BEGIN_MESSAGE_MAP(CPPageSphere, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageSphere)
	ON_EN_CHANGE(IDC_EDIT_RADIUS, OnChangeEditRadius)
	ON_EN_CHANGE(IDC_EDIT_LONGITUDE, OnChangeEditLongitude)
	ON_EN_CHANGE(IDC_EDIT_LATITUDE, OnChangeEditLatitude)
	ON_BN_CLICKED(IDC_CHECK_GOURAUD, OnCheckGouraud)
	ON_BN_CLICKED(IDC_CHECK_BOTH_SIDES, OnCheckBothSides)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageSphere message handlers


BOOL CPPageSphere::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	ASSERT (m_pPrimitiveSphere);

	m_pPrimitiveSphere->GetPrimitiveSphereData (&m_strtPrimitiveSphereData);
	
	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPPageSphere::OnApply() 
{
	ASSERT (m_pPrimitiveSphere);

	// Save the data
	m_pPrimitiveSphere->SetPrimitiveSphereData (&m_strtPrimitiveSphereData);

	CRBModelerRBMGraphicView::UpdatePrimitive (m_pPrimitiveSphere);
	
	return CPropertyPage::OnApply();
}

void CPPageSphere::OnChangeEditRadius() 
{
	SetModified ();	
}

void CPPageSphere::OnChangeEditLongitude() 
{
	SetModified ();	
}

void CPPageSphere::OnChangeEditLatitude() 
{
	SetModified ();	
}

void CPPageSphere::OnCheckGouraud() 
{
	SetModified ();	
}

void CPPageSphere::OnCheckBothSides() 
{
	SetModified ();	
}
