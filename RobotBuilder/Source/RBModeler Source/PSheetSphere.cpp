// PSheetSphere.cpp : implementation file
//

#include "stdafx.h"
#include "RBModeler.h"
#include "PSheetSphere.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetSphere

IMPLEMENT_DYNAMIC(CPSheetSphere, CPSheetBase)

CPSheetSphere::CPSheetSphere(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetSphere::CPSheetSphere(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetSphere::~CPSheetSphere()
{
}


BEGIN_MESSAGE_MAP(CPSheetSphere, CPSheetBase)
	//{{AFX_MSG_MAP(CPSheetSphere)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetSphere message handlers

void CPSheetSphere::BuildPropertySheet()
{
	m_pPrimitiveSphere = NULL;

	AddPage (&m_PPageSphere);
	AddPage (&m_PPageCovering);
	AddPage (&m_PPagePlacement);
	AddPage (&m_PPagePhysicalProperties);
}

int CPSheetSphere::DoModal() 
{
	m_PPageSphere.m_pPrimitiveSphere = m_pPrimitiveSphere;
	m_PPageCovering.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveSphere);
	m_PPagePlacement.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveSphere);
	m_PPagePhysicalProperties.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveSphere);

	return CPSheetBase::DoModal();
}

void CPSheetSphere::SetData(CPrimitiveSphere *pSpherePrimitive)
{
	ASSERT (pSpherePrimitive);

	m_pPrimitiveSphere = pSpherePrimitive;
}
