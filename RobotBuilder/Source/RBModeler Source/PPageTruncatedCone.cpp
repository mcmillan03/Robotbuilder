// PPageTruncatedCone.cpp : implementation file
//

#include "stdafx.h"
#include "rbModeler.h"
#include "PPageTruncatedCone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageTruncatedCone property page

IMPLEMENT_DYNCREATE(CPPageTruncatedCone, CPropertyPage)

CPPageTruncatedCone::CPPageTruncatedCone() : CPropertyPage(CPPageTruncatedCone::IDD)
{
	m_strtPrimitiveTruncatedConeData.dHeight = 1;
	m_strtPrimitiveTruncatedConeData.dBaseRadius = 1;
	m_strtPrimitiveTruncatedConeData.dTopRadius = .5;
	m_strtPrimitiveTruncatedConeData.nTess = 20;
	m_strtPrimitiveTruncatedConeData.bRenderBothSides = FALSE;
	m_strtPrimitiveTruncatedConeData.bUseGouraudShading = TRUE;

	m_pPrimitiveTruncatedCone = NULL;
	//{{AFX_DATA_INIT(CPPageTruncatedCone)
	//}}AFX_DATA_INIT
}

CPPageTruncatedCone::~CPPageTruncatedCone()
{
}

void CPPageTruncatedCone::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fHeight = (float) m_strtPrimitiveTruncatedConeData.dHeight;
	float fBaseRadius = (float) m_strtPrimitiveTruncatedConeData.dBaseRadius;
	float fTopRadius = (float) m_strtPrimitiveTruncatedConeData.dTopRadius;

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageTruncatedCone)
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK_BOTH_SIDES, m_strtPrimitiveTruncatedConeData.bRenderBothSides);
	DDX_Check(pDX, IDC_CHECK_GOURAUD, m_strtPrimitiveTruncatedConeData.bUseGouraudShading);
	DDX_Text(pDX, IDC_EDIT_BASE_RADIUS, fBaseRadius);
	DDV_MinMaxFloat(pDX, fBaseRadius, TRUNCATED_CONE_BASE_RADIUS_MIN, TRUNCATED_CONE_BASE_RADIUS_MAX);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, fHeight);
	DDV_MinMaxFloat(pDX, fHeight, TRUNCATED_CONE_HEIGHT_MIN, TRUNCATED_CONE_HEIGHT_MAX);
	DDX_Text(pDX, IDC_EDIT_TESS, m_strtPrimitiveTruncatedConeData.nTess);
	DDV_MinMaxInt(pDX, m_strtPrimitiveTruncatedConeData.nTess, TRUNCATED_CONE_TESS_MIN, TRUNCATED_CONE_TESS_MAX);
	DDX_Text(pDX, IDC_EDIT_TOP_RADIUS, fTopRadius);
	DDV_MinMaxFloat(pDX, fTopRadius, TRUNCATED_CONE_TOP_RADIUS_MIN, TRUNCATED_CONE_TOP_RADIUS_MAX);

	m_strtPrimitiveTruncatedConeData.dHeight = fHeight;
	m_strtPrimitiveTruncatedConeData.dBaseRadius = fBaseRadius;
	m_strtPrimitiveTruncatedConeData.dTopRadius = fTopRadius;


}


BEGIN_MESSAGE_MAP(CPPageTruncatedCone, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageTruncatedCone)
	ON_EN_CHANGE(IDC_EDIT_TOP_RADIUS, OnChangeEditTopRadius)
	ON_EN_CHANGE(IDC_EDIT_TESS, OnChangeEditTess)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, OnChangeEditHeight)
	ON_EN_CHANGE(IDC_EDIT_BASE_RADIUS, OnChangeEditBaseRadius)
	ON_BN_CLICKED(IDC_CHECK_GOURAUD, OnCheckGouraud)
	ON_BN_CLICKED(IDC_CHECK_BOTH_SIDES, OnCheckBothSides)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageTruncatedCone message handlers

void CPPageTruncatedCone::OnChangeEditTopRadius() 
{
	SetModified ();
}

void CPPageTruncatedCone::OnChangeEditTess() 
{
	SetModified ();
}

void CPPageTruncatedCone::OnChangeEditHeight() 
{
	SetModified ();
}

void CPPageTruncatedCone::OnChangeEditBaseRadius() 
{
	SetModified ();
}

void CPPageTruncatedCone::OnCheckGouraud() 
{
	SetModified ();
}

void CPPageTruncatedCone::OnCheckBothSides() 
{
	SetModified ();
}

BOOL CPPageTruncatedCone::OnApply() 
{
	// Save the data
	m_pPrimitiveTruncatedCone->SetPrimitiveTruncatedConeData (&m_strtPrimitiveTruncatedConeData);

	CRBModelerRBMGraphicView::UpdatePrimitive (m_pPrimitiveTruncatedCone);
	
	return CPropertyPage::OnApply();
}

BOOL CPPageTruncatedCone::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pPrimitiveTruncatedCone);

	m_pPrimitiveTruncatedCone->GetPrimitiveTruncatedConeData (&m_strtPrimitiveTruncatedConeData);
	
	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
