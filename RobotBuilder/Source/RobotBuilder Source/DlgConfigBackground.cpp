// DlgConfigBackground.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgConfigBackground.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigBackground dialog


CDlgConfigBackground::CDlgConfigBackground(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfigBackground::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConfigBackground)
	//}}AFX_DATA_INIT
	m_pCdmvCFGData = NULL;
}


void CDlgConfigBackground::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConfigBackground)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConfigBackground, CDialog)
	//{{AFX_MSG_MAP(CDlgConfigBackground)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_COLOR, OnButtonChooseColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigBackground message handlers
void CDlgConfigBackground::SetDataClass(CdmvCFGData *pCdmvCFGData)
{
	ASSERT (pCdmvCFGData);

	m_pCdmvCFGData = pCdmvCFGData;
}

BOOL CDlgConfigBackground::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Make sure the data class has been set
	ASSERT (m_pCdmvCFGData);

	// Initialize the background color example button
	m_crBackgroundColor = m_pCdmvCFGData->GetBackgroundColor ();

	return TRUE;
}

void CDlgConfigBackground::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (nIDCtl == IDC_BUTTON_COLOR_EXAMPLE)
	{
		CDC dc;
		BOOL bSuccess = dc.Attach (lpDrawItemStruct->hDC);
		ASSERT (bSuccess);
	
		// Get a pointer to the button
		CButton* pButton = static_cast <CButton*> (GetDlgItem (IDC_BUTTON_COLOR_EXAMPLE));
		ASSERT (pButton);
		// Get the dimension of the button
		CRect rectClient;
		pButton->GetClientRect (rectClient);
		
		COLORREF crBrushColor = m_crBackgroundColor;
	
		// Create a brush which will be used to draw the rect
		CBrush brushBackground (crBrushColor);

		CBrush* pbrushOld = dc.SelectObject (&brushBackground);

		bSuccess = dc.Rectangle (rectClient);
		ASSERT (bSuccess);

		// Restore the previous brush to prevent GDI leaks
		dc.SelectObject (pbrushOld);
		
		dc.Detach ();
	}
	else
	{	
		CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
	}
}

void CDlgConfigBackground::OnButtonChooseColor() 
{
	// Open the color dialog
	CColorDialog dlg;

	// Initialize the color choice to the current color and automatically
	// expand the custom dialog part so the user will see the initial color.
	dlg.m_cc.Flags |= (CC_RGBINIT | CC_FULLOPEN);
	dlg.m_cc.rgbResult = m_crBackgroundColor;

	if (dlg.DoModal () == IDOK)
	{
		COLORREF crColor = dlg.GetColor ();
		m_crBackgroundColor = crColor;

		// Cause a repaint on the button to show the new color
		CButton* pButton = static_cast <CButton*> (GetDlgItem (IDC_BUTTON_COLOR_EXAMPLE));
		pButton->Invalidate (TRUE);
	}		
}

BOOL CDlgConfigBackground::ValidateAndSaveData()
{
	//Validation
	if (ValidateData())
	{
		// Save the data
		m_pCdmvCFGData->SetBackgroundColor(m_crBackgroundColor);

		return TRUE;
	}
	else
	{	//Validation failed
		return FALSE;
	}
}


BOOL CDlgConfigBackground::ValidateData()
{
	return UpdateData(TRUE);
}
