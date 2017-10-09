// PSheetArticulation.cpp : implementation file
//

#include "stdafx.h"
#include "DMViewer.h"
#include "PSheetArticulation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSheetArticulation

IMPLEMENT_DYNAMIC(CPSheetArticulation, CPSheetLinkBase)

CPSheetArticulation::CPSheetArticulation(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(nIDCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetArticulation::CPSheetArticulation(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPSheetLinkBase(pszCaption, pParentWnd, iSelectPage)
{
	BuildPropertySheet ();
}

CPSheetArticulation::~CPSheetArticulation()
{
}


BEGIN_MESSAGE_MAP(CPSheetArticulation, CPSheetLinkBase)
	//{{AFX_MSG_MAP(CPSheetArticulation)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSheetArticulation message handlers

void CPSheetArticulation::BuildPropertySheet()
{
	m_pCdmvArticulationData = NULL;

	this->AddPage (&m_ppageArticulationData);
	this->AddPage (&m_ppageObjectData);
}

int CPSheetArticulation::DoModal() 
{
	ASSERT (m_pCdmvArticulationData);

	// Set the members of the ppages
	m_ppageArticulationData.m_pCdmvArticulationData = m_pCdmvArticulationData;
	m_ppageObjectData.m_pCdmvObject = (CdmvObject*) m_pCdmvArticulationData;

	return CPSheetLinkBase::DoModal();
}
