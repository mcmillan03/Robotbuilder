// PSheetBlock.cpp : implementation file
//

#include "stdafx.h"
#include "rbModeler.h"
#include "PSheetBlock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetBlock

IMPLEMENT_DYNAMIC(CPSheetBlock, CPSheetBase)

CPSheetBlock::CPSheetBlock(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetBlock::CPSheetBlock(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetBlock::~CPSheetBlock()
{
}


BEGIN_MESSAGE_MAP(CPSheetBlock, CPSheetBase)
	//{{AFX_MSG_MAP(CPSheetBlock)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetBlock message handlers

void CPSheetBlock::BuildPropertySheet()
{
	m_pPrimitiveBlock = NULL;

	AddPage (&m_PPageBlock);
	AddPage (&m_PPageCovering);
	AddPage (&m_PPagePlacement);
	AddPage (&m_PPagePhysicalProperties);
}

void CPSheetBlock::SetData(CPrimitiveBlock *pPrimitiveBlock)
{
	ASSERT (pPrimitiveBlock);

	m_pPrimitiveBlock = pPrimitiveBlock;
}

int CPSheetBlock::DoModal() 
{
	m_PPageBlock.m_pPrimitiveBlock = m_pPrimitiveBlock;
	m_PPageCovering.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveBlock);
	m_PPagePlacement.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveBlock);
	m_PPagePhysicalProperties.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveBlock);
	
	return CPSheetBase::DoModal();
}
