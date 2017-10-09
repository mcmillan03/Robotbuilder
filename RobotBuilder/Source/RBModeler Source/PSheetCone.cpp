// PSheetCone.cpp : implementation file
//

#include "stdafx.h"
#include "rbModeler.h"
#include "PSheetCone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetCone

IMPLEMENT_DYNAMIC(CPSheetCone, CPSheetBase)

CPSheetCone::CPSheetCone(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetCone::CPSheetCone(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetCone::~CPSheetCone()
{
}


BEGIN_MESSAGE_MAP(CPSheetCone, CPSheetBase)
	//{{AFX_MSG_MAP(CPSheetCone)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetCone message handlers

void CPSheetCone::SetData(CPrimitiveCone *pPrimitiveCone)
{
	ASSERT (pPrimitiveCone);

	m_pPrimitiveCone = pPrimitiveCone;

}

void CPSheetCone::BuildPropertySheet()
{
	m_pPrimitiveCone = NULL;

	AddPage (&m_PPageCone);
	AddPage (&m_PPageCovering);
	AddPage (&m_PPagePlacement);
	AddPage (&m_PPagePhysicalProperties);

}

int CPSheetCone::DoModal() 
{
	m_PPageCone.m_pPrimitiveCone = m_pPrimitiveCone;
	m_PPageCovering.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveCone);
	m_PPagePlacement.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveCone);
	m_PPagePhysicalProperties.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveCone);

	return CPSheetBase::DoModal();
}
