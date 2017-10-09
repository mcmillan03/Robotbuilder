// PSheetCylinder.cpp : implementation file
//

#include "stdafx.h"
#include "rbModeler.h"
#include "PSheetCylinder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetCylinder

IMPLEMENT_DYNAMIC(CPSheetCylinder, CPSheetBase)

CPSheetCylinder::CPSheetCylinder(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetCylinder::CPSheetCylinder(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetCylinder::~CPSheetCylinder()
{
}


BEGIN_MESSAGE_MAP(CPSheetCylinder, CPSheetBase)
	//{{AFX_MSG_MAP(CPSheetCylinder)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetCylinder message handlers

void CPSheetCylinder::BuildPropertySheet()
{
	m_pPrimitiveCylinder = NULL;

	AddPage (&m_PPageCylinder);
	AddPage (&m_PPageCovering);
	AddPage (&m_PPagePlacement);
	AddPage (&m_PPagePhysicalProperties);

}

void CPSheetCylinder::SetData(CPrimitiveCylinder *pPrimitiveCylinder)
{
	ASSERT (pPrimitiveCylinder);

	m_pPrimitiveCylinder = pPrimitiveCylinder;

}

int CPSheetCylinder::DoModal() 
{
	m_PPageCylinder.m_pPrimitiveCylinder = m_pPrimitiveCylinder;
	m_PPageCovering.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveCylinder);
	m_PPagePlacement.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveCylinder);
	m_PPagePhysicalProperties.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveCylinder);

	return CPSheetBase::DoModal();
}
