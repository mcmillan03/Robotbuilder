// PSheetHemisphere.cpp : implementation file
//

#include "stdafx.h"
#include "rbModeler.h"
#include "PSheetHemisphere.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetHemisphere

IMPLEMENT_DYNAMIC(CPSheetHemisphere, CPSheetBase)

CPSheetHemisphere::CPSheetHemisphere(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetHemisphere::CPSheetHemisphere(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetHemisphere::~CPSheetHemisphere()
{
}


BEGIN_MESSAGE_MAP(CPSheetHemisphere, CPSheetBase)
	//{{AFX_MSG_MAP(CPSheetHemisphere)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetHemisphere message handlers

void CPSheetHemisphere::BuildPropertySheet()
{
	m_pPrimitiveHemisphere = NULL;

	AddPage (&m_PPageHemisphere);
	AddPage (&m_PPageCovering);
	AddPage (&m_PPagePlacement);
	AddPage (&m_PPagePhysicalProperties);

}

void CPSheetHemisphere::SetData(CPrimitiveHemisphere *pPrimitiveHemisphere)
{
	ASSERT (pPrimitiveHemisphere);

	m_pPrimitiveHemisphere = pPrimitiveHemisphere;

}

int CPSheetHemisphere::DoModal() 
{
	m_PPageHemisphere.m_pPrimitiveHemisphere = m_pPrimitiveHemisphere;
	m_PPageCovering.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveHemisphere);
	m_PPagePlacement.m_pPrimitive = dynamic_cast <CPrimitive*> (m_pPrimitiveHemisphere);
	m_PPagePhysicalProperties.m_pPrimitive  = dynamic_cast <CPrimitive*> (m_pPrimitiveHemisphere);
	
	return CPSheetBase::DoModal();
}
