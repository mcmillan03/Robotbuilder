// PPageHemisphere.cpp : implementation file
//

#include "stdafx.h"
#include "rbModeler.h"
#include "PPageHemisphere.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageHemisphere property page

IMPLEMENT_DYNCREATE(CPPageHemisphere, CPropertyPage)

CPPageHemisphere::CPPageHemisphere() : CPropertyPage(CPPageHemisphere::IDD)
{
	m_strtPrimitiveHemisphereData.dRadius = 1;
	m_strtPrimitiveHemisphereData.nLatitudeCount = 5;
	m_strtPrimitiveHemisphereData.nLongitudeCount = 5;
	m_strtPrimitiveHemisphereData.bRenderBothSides = FALSE;
	m_strtPrimitiveHemisphereData.bUseGouraudShading = TRUE;

	m_pPrimitiveHemisphere = NULL;
	//{{AFX_DATA_INIT(CPPageHemisphere)
	//}}AFX_DATA_INIT
}

CPPageHemisphere::~CPPageHemisphere()
{
}

void CPPageHemisphere::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fRadius = (float) m_strtPrimitiveHemisphereData.dRadius;

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageHemisphere)
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK_BOTH_SIDES, m_strtPrimitiveHemisphereData.bRenderBothSides);
	DDX_Check(pDX, IDC_CHECK_GOURAUD, m_strtPrimitiveHemisphereData.bUseGouraudShading);
	DDX_Text(pDX, IDC_EDIT_LATITUDE, m_strtPrimitiveHemisphereData.nLatitudeCount);
	DDV_MinMaxInt(pDX, m_strtPrimitiveHemisphereData.nLatitudeCount, HEMISPHERE_LATITUDE_MIN, HEMISPHERE_LATITUDE_MAX);
	DDX_Text(pDX, IDC_EDIT_LONGITUDE, m_strtPrimitiveHemisphereData.nLongitudeCount);
	DDV_MinMaxInt(pDX, m_strtPrimitiveHemisphereData.nLongitudeCount, HEMISPHERE_LONGITUDE_MIN, HEMISPHERE_LONGITUDE_MAX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, fRadius);
	DDV_MinMaxFloat(pDX, fRadius, HEMISPHERE_RADIUS_MIN, HEMISPHERE_RADIUS_MAX);

	m_strtPrimitiveHemisphereData.dRadius = fRadius;
}


BEGIN_MESSAGE_MAP(CPPageHemisphere, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageHemisphere)
	ON_EN_CHANGE(IDC_EDIT_RADIUS, OnChangeEditRadius)
	ON_EN_CHANGE(IDC_EDIT_LONGITUDE, OnChangeEditLongitude)
	ON_EN_CHANGE(IDC_EDIT_LATITUDE, OnChangeEditLatitude)
	ON_BN_CLICKED(IDC_CHECK_GOURAUD, OnCheckGouraud)
	ON_BN_CLICKED(IDC_CHECK_BOTH_SIDES, OnCheckBothSides)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageHemisphere message handlers

void CPPageHemisphere::OnChangeEditRadius() 
{
	SetModified ();
}

void CPPageHemisphere::OnChangeEditLongitude() 
{
	SetModified ();
}

void CPPageHemisphere::OnChangeEditLatitude() 
{
	SetModified ();
}

void CPPageHemisphere::OnCheckGouraud() 
{
	SetModified ();
}

void CPPageHemisphere::OnCheckBothSides() 
{
	SetModified ();
}

BOOL CPPageHemisphere::OnApply() 
{
	ASSERT (m_pPrimitiveHemisphere);

	// Save the data
	m_pPrimitiveHemisphere->SetPrimitiveHemisphereData (&m_strtPrimitiveHemisphereData);

	CRBModelerRBMGraphicView::UpdatePrimitive (m_pPrimitiveHemisphere);
	
	return CPropertyPage::OnApply();
}

BOOL CPPageHemisphere::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pPrimitiveHemisphere);

	m_pPrimitiveHemisphere->GetPrimitiveHemisphereData (&m_strtPrimitiveHemisphereData);
	
	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
