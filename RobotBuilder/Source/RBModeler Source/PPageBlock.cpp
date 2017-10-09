// PPageBlock.cpp : implementation file
//

#include "stdafx.h"
#include "rbModeler.h"
#include "PPageBlock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageBlock property page

IMPLEMENT_DYNCREATE(CPPageBlock, CPropertyPage)

CPPageBlock::CPPageBlock() : CPropertyPage(CPPageBlock::IDD)
{
	m_strtPrimitiveBlockData.dLengthX = 1;
	m_strtPrimitiveBlockData.dLengthY = 1;
	m_strtPrimitiveBlockData.dLengthZ = 1;
	m_strtPrimitiveBlockData.bRenderBothSides = FALSE;

	m_pPrimitiveBlock = NULL;
	//{{AFX_DATA_INIT(CPPageBlock)
	//}}AFX_DATA_INIT
}

CPPageBlock::~CPPageBlock()
{
}

void CPPageBlock::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fLengthX = (float) m_strtPrimitiveBlockData.dLengthX;
	float fLengthY = (float) m_strtPrimitiveBlockData.dLengthY;
	float fLengthZ = (float) m_strtPrimitiveBlockData.dLengthZ;

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageBlock)
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK_BOTH_SIDES, m_strtPrimitiveBlockData.bRenderBothSides);
	DDX_Text(pDX, IDC_EDIT_XLENGTH, fLengthX);
	DDV_MinMaxFloat(pDX, fLengthX, BLOCK_LENGTH_MIN, BLOCK_LENGTH_MAX);
	DDX_Text(pDX, IDC_EDIT_YLENGTH, fLengthY);
	DDV_MinMaxFloat(pDX, fLengthY, BLOCK_LENGTH_MIN, BLOCK_LENGTH_MAX);
	DDX_Text(pDX, IDC_EDIT_ZLENGTH, fLengthZ);
	DDV_MinMaxFloat(pDX, fLengthZ, BLOCK_LENGTH_MIN, BLOCK_LENGTH_MAX);

	m_strtPrimitiveBlockData.dLengthX = fLengthX;
	m_strtPrimitiveBlockData.dLengthY = fLengthY;
	m_strtPrimitiveBlockData.dLengthZ = fLengthZ;
}


BEGIN_MESSAGE_MAP(CPPageBlock, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageBlock)
	ON_BN_CLICKED(IDC_CHECK_BOTH_SIDES, OnCheckBothSides)
	ON_EN_CHANGE(IDC_EDIT_XLENGTH, OnChangeEditXlength)
	ON_EN_CHANGE(IDC_EDIT_YLENGTH, OnChangeEditYlength)
	ON_EN_CHANGE(IDC_EDIT_ZLENGTH, OnChangeEditZlength)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageBlock message handlers

BOOL CPPageBlock::OnApply() 
{
	ASSERT (m_pPrimitiveBlock);

	// Save the data
	m_pPrimitiveBlock->SetPrimitiveBlockData (&m_strtPrimitiveBlockData);

	CRBModelerRBMGraphicView::UpdatePrimitive (m_pPrimitiveBlock);
	
	return CPropertyPage::OnApply();
}

BOOL CPPageBlock::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pPrimitiveBlock);

	m_pPrimitiveBlock->GetPrimitiveBlockData (&m_strtPrimitiveBlockData);
	
	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CPPageBlock::OnCheckBothSides() 
{
	SetModified ();
}

void CPPageBlock::OnChangeEditXlength() 
{
	SetModified ();
}

void CPPageBlock::OnChangeEditYlength() 
{
	SetModified ();
}

void CPPageBlock::OnChangeEditZlength() 
{
	SetModified ();
}
