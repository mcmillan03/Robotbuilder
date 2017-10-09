// PPageCovering.cpp : implementation file
//

#include "stdafx.h"
#include "RBModeler.h"
#include "PPageCovering.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "RBModelerRBMGraphicView.h"
#include "FindFile.h"

// radio button definitions
enum {RB_SIMPLE_COLOR, RB_TEXTURE};

/////////////////////////////////////////////////////////////////////////////
// CPPageCovering property page

IMPLEMENT_DYNCREATE(CPPageCovering, CPropertyPage)

CPPageCovering::CPPageCovering() : CPropertyPage(CPPageCovering::IDD)
{
	//{{AFX_DATA_INIT(CPPageCovering)
	//}}AFX_DATA_INIT
	m_pPrimitive = NULL;
	m_nCoveringType = RB_SIMPLE_COLOR;
	m_strtPrimitiveCoveringData.strTextureFile = _T("");
	m_strtPrimitiveCoveringData.crColor = RGB(255, 0, 0);
}

CPPageCovering::~CPPageCovering()
{
}

void CPPageCovering::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageCovering)
	DDX_Control(pDX, IDC_RADIO_TYPE_COLOR, m_radioCoveringType);
	DDX_Control(pDX, IDC_EDIT_TEXTURE, m_editTexture);
	DDX_Control(pDX, IDC_BUTTON_COLOR, m_butColor);
	DDX_Control(pDX, IDC_BUTTON_BROWSE, m_butBrowse);
	DDX_Radio(pDX, IDC_RADIO_TYPE_COLOR, m_nCoveringType);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_TEXTURE, m_strtPrimitiveCoveringData.strTextureFile);
	DDV_MaxChars(pDX, m_strtPrimitiveCoveringData.strTextureFile, N_MAX_FILENAME_LENGTH);
}


BEGIN_MESSAGE_MAP(CPPageCovering, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageCovering)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_RADIO_TYPE_COLOR, OnRadioTypeColor)
	ON_BN_CLICKED(IDC_RADIO_TEXTURE, OnRadioTexture)
	ON_WM_DRAWITEM()
	ON_EN_CHANGE(IDC_EDIT_TEXTURE, OnChangeEditTexture)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageCovering message handlers

void CPPageCovering::OnButtonColor() 
{
	// Open the color dialog
	CColorDialog dlg;
	
	// Initialize the color choice to the current color and automatically
	// expand the custom dialog part so the user will see the initial color.
	dlg.m_cc.Flags |= (CC_RGBINIT | CC_FULLOPEN);
	dlg.m_cc.rgbResult = m_strtPrimitiveCoveringData.crColor;

	
	if (dlg.DoModal () == IDOK)
	{
		COLORREF crColor = dlg.GetColor ();
		m_strtPrimitiveCoveringData.crColor = crColor;

		// Cause a repaint on the button to show the new color
		CButton* pButton = static_cast <CButton*> (GetDlgItem (IDC_BUTTON_COLOR_EXAMPLE));
		pButton->Invalidate (TRUE);

		// Enable the apply button because of the color change
		SetModified (TRUE);
	}
	
}

void CPPageCovering::OnButtonBrowse() 
{
	// First save the data in the controls, so if OK is chosen, the correct
	// data is displayed
	BOOL bReturnStatus = UpdateData (TRUE);
	ASSERT (bReturnStatus);
	
	// todo:
//	char szPathBuffer[N_MAX_CURRENT_DIRECTORY_SIZE];
//	GetPrivateProfileString ("Paths", "Model_Path", ".", szPathBuffer, N_MAX_CURRENT_DIRECTORY_SIZE,
//		"RobotBuilder.INI");
//	CString strInitialDirectory = szPathBuffer;

	CFileDialog dlg (TRUE, /* make an open dlg */
		".jpg", /* default extension */
		NULL, /* initial filename */
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"All Supported Files (*.jpg;*.rgb;*.tga)|\
*.jpg;*.rgb;*.tga|JPEG Files (*.jpg)|*.jpg|RGB Format (*.rgb)|*.rgb|Targa Files (*.tga)|*.tga||",	/* filter */
		NULL /* parent */
		);

	// set initial path
	//dlg.m_ofn.lpstrInitialDir = strInitialDirectory;
	
	if (dlg.DoModal () == IDOK)
	{	
		CString strPath;
		CString strFile = dlg.GetFileName ();
		
		BOOL bFindFile = CFindFile::FindFile (TEXTURE_FILE_TYPE, 
			strFile, strPath);
		if (!bFindFile || ((strPath + strFile) != dlg.GetPathName ()))
		{
			if (IDYES == AfxMessageBox (FILE_NOT_FOUND_MSG, MB_YESNO))
			{
				strFile = dlg.GetPathName ();
				strPath = "";
			}
			else
			{
				// strFile stays the same
				// Strip off the file name from the full path
				strPath = (dlg.GetPathName ()).Left (dlg.GetPathName ().GetLength () -
					strFile.GetLength ());
			}
		}

		m_strtPrimitiveCoveringData.strTextureFile = strFile;
		m_strtPrimitiveCoveringData.strTexturePath = strPath;
			
		// Now update to reflect the change
		bReturnStatus = UpdateData (FALSE);
		ASSERT (bReturnStatus);

		// Enable the apply button
		SetModified (TRUE);
	}		
}

BOOL CPPageCovering::OnApply() 
{
	ASSERT (m_pPrimitive);

	// Save the covering type in the data struct
	if (m_nCoveringType == RB_SIMPLE_COLOR)
	{
		m_strtPrimitiveCoveringData.covCovering = SIMPLE_COLOR;
	}
	else
	{
		ASSERT (m_nCoveringType == RB_TEXTURE);

		m_strtPrimitiveCoveringData.covCovering = TEXTURE;
	}

	// Save the the covering data
	m_pPrimitive->GetPrimitiveCovering ()->SetPrimitiveCoveringData (&m_strtPrimitiveCoveringData);
	
	// Update the 3D view
	CRBModelerRBMGraphicView::UpdatePrimitive (m_pPrimitive);

	return CPropertyPage::OnApply();
}

BOOL CPPageCovering::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pPrimitive);

	m_pPrimitive->GetPrimitiveCovering ()->GetPrimitiveCoveringData (&m_strtPrimitiveCoveringData);

	// Need to properly set the radio button selection
	
	if (m_strtPrimitiveCoveringData.covCovering == SIMPLE_COLOR)
	{
		m_nCoveringType = RB_SIMPLE_COLOR;
		
		m_butBrowse.EnableWindow (FALSE);
		m_editTexture.EnableWindow (FALSE);
		m_butColor.EnableWindow (TRUE);
	}
	else
	{
		ASSERT (m_strtPrimitiveCoveringData.covCovering == TEXTURE);

		m_nCoveringType = RB_TEXTURE;

		m_butBrowse.EnableWindow (TRUE);
		m_editTexture.EnableWindow (TRUE);
		m_butColor.EnableWindow (FALSE);
	}
	

	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPPageCovering::OnRadioTypeColor() 
{
	// This will get called whenever the radio button is clicked, regardless if
	// it is the currently selected button.  Consequently, to determine when to
	// enable the apply button look at the current state of the m_butBrowse button
	// (i.e. if the color type is the current selection, the button will already be
	// disabled)
	if (m_butBrowse.IsWindowEnabled ())
	{
		m_butBrowse.EnableWindow (FALSE);
		m_editTexture.EnableWindow (FALSE);
		m_butColor.EnableWindow (TRUE);

		// Enable apply button
		SetModified (TRUE);
	}
}

void CPPageCovering::OnRadioTexture() 
{
	// See commment for OnRadioTypeColor
	if (!m_butBrowse.IsWindowEnabled ())
	{
		m_butBrowse.EnableWindow (TRUE);
		m_editTexture.EnableWindow (TRUE);
		m_butColor.EnableWindow (FALSE);

		// Enable apply button
		SetModified (TRUE);
	}
}

void CPPageCovering::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
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
		
		// Create a brush which will be used to draw the rect
		CBrush brushBackground (m_strtPrimitiveCoveringData.crColor);

		CBrush* pbrushOld = dc.SelectObject (&brushBackground);

		bSuccess = dc.Rectangle (rectClient);
		ASSERT (bSuccess);

		// Restore the previous brush to prevent GDI leaks
		dc.SelectObject (pbrushOld);
		
		dc.Detach ();
	}

	
	CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CPPageCovering::OnChangeEditTexture() 
{
	// A change in the edit box has occurred so enable the apply button
	SetModified (TRUE);
}
