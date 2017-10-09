// PSheetTruncatedCone.cpp : implementation file
//

#include "stdafx.h"
#include "rbModeler.h"
#include "PSheetTruncatedCone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetTruncatedCone

IMPLEMENT_DYNAMIC(CPSheetTruncatedCone, CPSheetBase)

CPSheetTruncatedCone::CPSheetTruncatedCone(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetTruncatedCone::CPSheetTruncatedCone(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetTruncatedCone::~CPSheetTruncatedCone()
{
}


BEGIN_MESSAGE_MAP(CPSheetTruncatedCone, CPSheetBase)
	//{{AFX_MSG_MAP(CPSheetTruncatedCone)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetTruncatedCone message handlers

void CPSheetTruncatedCone::BuildPropertySheet()
{
	m_pPrimitiveTruncatedCone = NULL;

	AddPage (&m_PPageTruncatedCone);
	AddPage (&m_PPageCovering);
	AddPage (&m_PPagePlacement);
	AddPage (&m_PPagePhysicalProperties);
}

void CPSheetTruncatedCone::SetData(CPrimitiveTruncatedCone *pPrimitiveTruncatedCone)
{
	ASSERT (pPrimitiveTruncatedCone);

	m_pPrimitiveTruncatedCone = pPrimitiveTruncatedCone;
}

int CPSheetTruncatedCone::DoModal() 
{
	m_PPageTruncatedCone.m_pPrimitiveTruncatedCone = m_pPrimitiveTruncatedCone;
	m_PPageCovering.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveTruncatedCone);
	m_PPagePlacement.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveTruncatedCone);
	m_PPagePhysicalProperties.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveTruncatedCone);

	return CPSheetBase::DoModal();
}
