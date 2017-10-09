// PPageCylinder.cpp : implementation file
//

#include "stdafx.h"
#include "rbModeler.h"
#include "PPageCylinder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageCylinder property page

IMPLEMENT_DYNCREATE(CPPageCylinder, CPropertyPage)

CPPageCylinder::CPPageCylinder() : CPropertyPage(CPPageCylinder::IDD)
{
	//{{AFX_DATA_INIT(CPPageCylinder)
	//}}AFX_DATA_INIT
	m_strtPrimitiveCylinderData.dRadius = 1;
	m_strtPrimitiveCylinderData.dHeight = 1;
	m_strtPrimitiveCylinderData.nTess = 20;
	m_strtPrimitiveCylinderData.bUseGouraudShading = TRUE;
	m_strtPrimitiveCylinderData.bRenderBothSides = FALSE;

	m_pPrimitiveCylinder = NULL;
}

CPPageCylinder::~CPPageCylinder()
{
}

void CPPageCylinder::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fHeight = (float) m_strtPrimitiveCylinderData.dHeight;
	float fRadius = (float) m_strtPrimitiveCylinderData.dRadius;
	
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageCylinder)
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK_BOTH_SIDES, m_strtPrimitiveCylinderData.bRenderBothSides);
	DDX_Check(pDX, IDC_CHECK_GOURAUD, m_strtPrimitiveCylinderData.bUseGouraudShading);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, fHeight);
	DDV_MinMaxFloat(pDX, fHeight, CYLINDER_HEIGHT_MIN, CYLINDER_HEIGHT_MAX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, fRadius);
	DDV_MinMaxFloat(pDX, fRadius, CYLINDER_RADIUS_MIN, CYLINDER_RADIUS_MAX);
	DDX_Text(pDX, IDC_EDIT_TESS, m_strtPrimitiveCylinderData.nTess);
	DDV_MinMaxInt(pDX, m_strtPrimitiveCylinderData.nTess, CYLINDER_TESS_MIN, CYLINDER_TESS_MAX);

	m_strtPrimitiveCylinderData.dHeight = fHeight;
	m_strtPrimitiveCylinderData.dRadius = fRadius;
}


BEGIN_MESSAGE_MAP(CPPageCylinder, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageCylinder)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, OnChangeEditHeight)
	ON_EN_CHANGE(IDC_EDIT_RADIUS, OnChangeEditRadius)
	ON_EN_CHANGE(IDC_EDIT_TESS, OnChangeEditTess)
	ON_BN_CLICKED(IDC_CHECK_GOURAUD, OnCheckGouraud)
	ON_BN_CLICKED(IDC_CHECK_BOTH_SIDES, OnCheckBothSides)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageCylinder message handlers

BOOL CPPageCylinder::OnApply() 
{
	ASSERT (m_pPrimitiveCylinder);

	// Save the data
	m_pPrimitiveCylinder->SetPrimitiveCylinderData (&m_strtPrimitiveCylinderData);

	CRBModelerRBMGraphicView::UpdatePrimitive (m_pPrimitiveCylinder);
	
	return CPropertyPage::OnApply();
}

BOOL CPPageCylinder::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pPrimitiveCylinder);

	m_pPrimitiveCylinder->GetPrimitiveCylinderData (&m_strtPrimitiveCylinderData);
	
	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPPageCylinder::OnChangeEditHeight() 
{
	SetModified ();
}

void CPPageCylinder::OnChangeEditRadius() 
{
	SetModified ();
}

void CPPageCylinder::OnChangeEditTess() 
{
	SetModified ();
}

void CPPageCylinder::OnCheckGouraud() 
{
	SetModified ();
}

void CPPageCylinder::OnCheckBothSides() 
{
	SetModified ();
}
