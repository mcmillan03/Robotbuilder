// PPageCone.cpp : implementation file
//

#include "stdafx.h"
#include "rbModeler.h"
#include "PPageCone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageCone property page

IMPLEMENT_DYNCREATE(CPPageCone, CPropertyPage)

CPPageCone::CPPageCone() : CPropertyPage(CPPageCone::IDD)
{
	m_strtPrimitiveConeData.dHeight = 1;
	m_strtPrimitiveConeData.dRadius = 1;
	m_strtPrimitiveConeData.nTess = 20;
	m_strtPrimitiveConeData.bRenderBothSides = FALSE;

	m_pPrimitiveCone = NULL;
	//{{AFX_DATA_INIT(CPPageCone)
	//}}AFX_DATA_INIT
}

CPPageCone::~CPPageCone()
{
}

void CPPageCone::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fHeight = (float) m_strtPrimitiveConeData.dHeight;
	float fRadius = (float) m_strtPrimitiveConeData.dRadius;
	
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageCone)
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK_BOTH_SIDES, m_strtPrimitiveConeData.bRenderBothSides);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, fHeight);
	DDV_MinMaxFloat(pDX, fHeight, CONE_HEIGHT_MIN, CONE_HEIGHT_MAX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, fRadius);
	DDV_MinMaxFloat(pDX, fRadius, CONE_RADIUS_MIN, CONE_RADIUS_MAX);
	DDX_Text(pDX, IDC_EDIT_TESS, m_strtPrimitiveConeData.nTess);
	DDV_MinMaxInt(pDX, m_strtPrimitiveConeData.nTess, CONE_TESS_MIN, CONE_TESS_MAX);
	
	m_strtPrimitiveConeData.dHeight = fHeight;
	m_strtPrimitiveConeData.dRadius = fRadius;
}


BEGIN_MESSAGE_MAP(CPPageCone, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageCone)
	ON_EN_CHANGE(IDC_EDIT_TESS, OnChangeEditTess)
	ON_EN_CHANGE(IDC_EDIT_RADIUS, OnChangeEditRadius)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, OnChangeEditHeight)
	ON_BN_CLICKED(IDC_CHECK_BOTH_SIDES, OnCheckBothSides)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageCone message handlers

BOOL CPPageCone::OnApply() 
{
	ASSERT (m_pPrimitiveCone);

	// Save the data
	m_pPrimitiveCone->SetPrimitiveConeData (&m_strtPrimitiveConeData);

	CRBModelerRBMGraphicView::UpdatePrimitive (m_pPrimitiveCone);
	
	return CPropertyPage::OnApply();
}

BOOL CPPageCone::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pPrimitiveCone);

	m_pPrimitiveCone->GetPrimitiveConeData (&m_strtPrimitiveConeData);
	
	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPPageCone::OnChangeEditTess() 
{
	SetModified ();
}

void CPPageCone::OnChangeEditRadius() 
{
	SetModified ();
}

void CPPageCone::OnChangeEditHeight() 
{
	SetModified ();
}

void CPPageCone::OnCheckBothSides() 
{
	SetModified ();
}
