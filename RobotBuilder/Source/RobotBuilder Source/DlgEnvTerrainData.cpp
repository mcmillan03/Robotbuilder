// DlgEnvTerrainData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgEnvTerrainData.h"
#include "GenerateTerrainFile.h"
#include "DlgEnvSaveTerrainFile.h"
#include "FindFile.h"
#include "DMViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvTerrainData dialog


CDlgEnvTerrainData::CDlgEnvTerrainData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnvTerrainData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEnvTerrainData)
	//m_dGridResolution = 0.0;
  m_dXGridResolution = 0.0;
  m_dYGridResolution = 0.0;
	m_nXDim = 0;
	m_nYDim = 0;
	m_dZValue = 0.0;
	m_nXIndex = 0;
	m_nYIndex = 0;
	m_nCoveringType = -1;
	m_strTextureFile = _T("");
	m_dSizeY = 0.0;
	m_dSizeX = 0.0;
	m_bWireframeOverlay = FALSE;
  m_dWireframeLnWidth = 0.5;
  m_dWireframeElevation = .04;
	//}}AFX_DATA_INIT
	m_strTexturePath = "";
	m_strTerrainPath = "";
	m_strTerrainFile = "";
	m_pCdmvTerrainData = NULL;
	m_bInitDialogCalledYet = FALSE;
	m_nArrayXDim = 0;
	m_nArrayYDim = 0;
}


void CDlgEnvTerrainData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEnvTerrainData)
	DDX_Control(pDX, IDC_EDIT_TEXTURE_FILE, m_editTextureFile);
	DDX_Control(pDX, IDC_BUTTON_COLOR_EXAMPLE, m_buttonColorExample);
	DDX_Control(pDX, IDC_BUTTON_WIREFRAME_COLOR, m_buttonWireframeColorExample);
	DDX_Control(pDX, IDC_BUTTON_BROWSE, m_buttonTextureBrowse);
	DDX_Control(pDX, IDC_BUTTON_CHOOSE_COLOR, m_buttonChooseColor);
	DDX_Control(pDX, IDC_BUTTON_CHOOSE_WIREFRAME_COLOR, m_buttonChooseWireframeColor);
	DDX_Control(pDX, IDC_SPIN_Y_INDEX, m_spinYIndex);
	DDX_Control(pDX, IDC_SPIN_X_INDEX, m_spinXIndex);
	DDX_Control(pDX, IDC_EDIT_WIREFRAME_LN_WIDTH, m_editWireframeLnWidth);
	DDX_Control(pDX, IDC_EDIT_WIREFRAME_ELEVATION, m_editWireframeElevation);
	//DDX_Text(pDX, IDC_EDIT_GRID_RESOLUTION, m_dGridResolution);
  DDX_Text(pDX, IDC_EDIT_XGRID_RESOLUTION, m_dXGridResolution);
  DDX_Text(pDX, IDC_EDIT_YGRID_RESOLUTION, m_dYGridResolution);
	//DDV_MinMaxDouble(pDX, m_dGridResolution, TERRAIN_RESOLUTION_MIN, TERRAIN_RESOLUTION_MAX);
  DDV_MinMaxDouble(pDX, m_dXGridResolution, TERRAIN_RESOLUTION_MIN, TERRAIN_RESOLUTION_MAX);
  DDV_MinMaxDouble(pDX, m_dYGridResolution, TERRAIN_RESOLUTION_MIN, TERRAIN_RESOLUTION_MAX);
	DDX_Text(pDX, IDC_EDIT_X_DIM, m_nXDim);
	DDV_MinMaxInt(pDX, m_nXDim, TERRAIN_DIM_MIN, TERRAIN_DIM_MAX);
	DDX_Text(pDX, IDC_EDIT_Y_DIM, m_nYDim);
	DDV_MinMaxInt(pDX, m_nYDim, TERRAIN_DIM_MIN, TERRAIN_DIM_MAX);
	DDX_Text(pDX, IDC_EDIT_Z_VALUE, m_dZValue);
	DDX_Text(pDX, IDC_EDIT_X_INDEX, m_nXIndex);
	DDX_Text(pDX, IDC_EDIT_Y_INDEX, m_nYIndex);
	DDX_Radio(pDX, IDC_RADIO_COLOR, m_nCoveringType);
	DDX_Text(pDX, IDC_EDIT_TEXTURE_FILE, m_strTextureFile);
	DDX_Text(pDX, IDC_EDIT_SIZE_Y, m_dSizeY);
	DDX_Text(pDX, IDC_EDIT_SIZE_X, m_dSizeX);
	DDX_Text(pDX, IDC_EDIT_WIREFRAME_LN_WIDTH, m_dWireframeLnWidth);
	DDX_Text(pDX, IDC_EDIT_WIREFRAME_ELEVATION, m_dWireframeElevation);
	DDX_Control(pDX, IDC_CHECK_WIREFRAME_OVERLAY, m_checkWireframeOverlay);
	DDX_Check(pDX, IDC_CHECK_WIREFRAME_OVERLAY, m_bWireframeOverlay);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEnvTerrainData, CDialog)
	//{{AFX_MSG_MAP(CDlgEnvTerrainData)
	ON_EN_SETFOCUS(IDC_EDIT_Z_VALUE, OnSetfocusEditZValue)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_Y_INDEX, OnDeltaposSpinYIndex)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_X_INDEX, OnDeltaposSpinXIndex)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_DEPTH, OnButtonApplyDepth)
	ON_EN_CHANGE(IDC_EDIT_X_INDEX, OnChangeEditXIndex)
	ON_EN_CHANGE(IDC_EDIT_Y_INDEX, OnChangeEditYIndex)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_RADIO_COLOR, OnRadioColor)
	ON_BN_CLICKED(IDC_RADIO_TEXTURE, OnRadioTexture)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_COLOR, OnButtonChooseColor)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_EN_KILLFOCUS(IDC_EDIT_GRID_RESOLUTION, OnKillfocusEditGridResolution)
	ON_EN_KILLFOCUS(IDC_EDIT_X_DIM, OnKillfocusEditXDim)
	ON_EN_KILLFOCUS(IDC_EDIT_Y_DIM, OnKillfocusEditYDim)
	ON_BN_CLICKED(IDC_CHECK_WIREFRAME_OVERLAY, OnCheckWireframeOverlay)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_WIREFRAME_COLOR, OnButtonChooseWireframeColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvTerrainData message handlers


/*********************************************************************\
*  Function: CDlgEnvTerrainData::SetDataClassPointer
*
*  Description: Sets the pointer to the terrain class that contains
*		the data this dialog box will display and manipulate
*
*  Returns:  void 
*  Argument: CdmvEnvTerrainData *pCdmvEnvTerrainData
*
*  Created:  4/22/2001  Steven Rodenbaugh
\*********************************************************************/
void CDlgEnvTerrainData::SetDataClassPointer(CdmvTerrainData *pCdmvTerrainData)
{
	ASSERT (pCdmvTerrainData);

	m_pCdmvTerrainData = pCdmvTerrainData;
}


/*********************************************************************\
*  Function: CDlgEnvTerrainData::SaveDialogData
*
*  Description: Called by the parent dialog to save the data before closing.
*
*  Returns:  void 
*
*  Created:  4/25/2001  Steven Rodenbaugh
\*********************************************************************/
void CDlgEnvTerrainData::SaveDialogData()
{
	// Update data should already have been called

	// Update the local copy of the Z matrix with the current extents
	SetArrayDimensions (m_nXDim, m_nYDim);

	// Set the saved array dimensions
	m_pCdmvTerrainData->SetDimensions (m_nXDim, m_nYDim);
	
	// Save the Z matrix
	int i, j;
	for (i = 0; i < m_nArrayXDim; i++)
		for (j = 0; j < m_nArrayYDim; j++)
			m_pCdmvTerrainData->SetZValue (i, j, GetZValue (i, j));


	//m_pCdmvTerrainData->SetGridResolution (m_dGridResolution);
  m_pCdmvTerrainData->SetXYGridResolution (m_dXGridResolution, m_dYGridResolution);

	if (m_nCoveringType == RB_COVERING_COLOR)
		m_pCdmvTerrainData->SetCovering (m_crCoveringColor);
	else
		m_pCdmvTerrainData->SetCovering (m_strTextureFile, m_strTexturePath);

  m_pCdmvTerrainData->SetWireframe (m_crWireframeColor, m_dWireframeLnWidth, m_dWireframeElevation);

}

BOOL CDlgEnvTerrainData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT (m_pCdmvTerrainData);

	//m_dGridResolution = m_pCdmvTerrainData->GetGridResolution ();
  m_dXGridResolution = m_pCdmvTerrainData->GetXGridResolution ();
  m_dYGridResolution = m_pCdmvTerrainData->GetYGridResolution ();
	m_nXDim = m_pCdmvTerrainData->GetXDim ();
	m_nYDim = m_pCdmvTerrainData->GetYDim ();

	// Set the ranges on the spin controls
	m_spinXIndex.SetRange (0, m_nXDim - 1);
	m_spinYIndex.SetRange (0, m_nYDim - 1);


	// Work around because CHANGE is detected in the edit boxes before they
	// are initialized by InitDialog
	m_bInitDialogCalledYet = TRUE;

	// Allocate the Z matrix
	SetArrayDimensions (m_nXDim, m_nYDim);

	// Build a copy of the Z matrix
	int i, j;
	for (i = 0; i < m_nArrayXDim; i++)
		for (j = 0; j < m_nArrayYDim; j++)
			SetZValue (i, j, m_pCdmvTerrainData->GetZValue (i, j));

	// Set the initial Z value
	m_dZValue = GetZValue (m_nXIndex, m_nYIndex);

	// Pick up the covering info
	TerrainCoveringType theTerrainCoveringType;
	m_pCdmvTerrainData->GetCoveringInfo (theTerrainCoveringType,
		m_crCoveringColor, m_strTextureFile, m_strTexturePath);

	if (theTerrainCoveringType == TERRAIN_COVERING_COLOR)
	{
		m_nCoveringType = RB_COVERING_COLOR;

		m_buttonTextureBrowse.EnableWindow (FALSE);
		m_editTextureFile.EnableWindow (FALSE);
		m_buttonChooseColor.EnableWindow (TRUE);
	}
	else
	{
		m_nCoveringType = RB_COVERING_TEXTURE;

		m_buttonTextureBrowse.EnableWindow (TRUE);
		m_editTextureFile.EnableWindow (TRUE);
		m_buttonChooseColor.EnableWindow (FALSE);
	}

	// Calculate the size
	//m_dSizeX = (m_nXDim - 1) * m_dGridResolution;
  m_dSizeX = (m_nXDim - 1) * m_dXGridResolution;
	//m_dSizeY = (m_nYDim - 1) * m_dGridResolution;
  m_dSizeY = (m_nYDim - 1) * m_dYGridResolution;

  /// Get the wireframe overlay info
  m_pCdmvTerrainData->GetWireframeInfo (m_bWireframeOverlay,
    m_crWireframeColor, m_dWireframeLnWidth, m_dWireframeElevation);

  // Enable/disable the wireframe parameters
  if (!m_bWireframeOverlay)
	{//Disable all parameters
    m_buttonChooseWireframeColor.EnableWindow(FALSE);
    m_editWireframeLnWidth.EnableWindow(FALSE);
    m_editWireframeElevation.EnableWindow(FALSE);
	}
  else
  {//Enable all parameters
    m_buttonChooseWireframeColor.EnableWindow(TRUE);
    m_editWireframeLnWidth.EnableWindow(TRUE);
    m_editWireframeElevation.EnableWindow(TRUE);
	}

	BOOL bReturn = UpdateData (FALSE);
	ASSERT (bReturn);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEnvTerrainData::OnSetfocusEditZValue() 
{
	// Need to check if the current indices are out of range before
	// trying to accept input
	// To check the indices, need to update and pick up the new values.  This 
	// might be weird to the user because it might cause an error when the user
	// clicks in the windows, but I think it works the best.  (Watching kill focus
	// on each control doesn't work because then the user can't hit the cancel
	// button without validating.)
	UpdateData ();

	// If the current indices are out of range, reset them to 0
	if (m_nXIndex > m_nXDim - 1)
	{
		m_nXIndex = 0; 
	}

	if (m_nYIndex > m_nYDim - 1)
	{
		m_nYIndex = 0; 
	}

	// Update the display
	BOOL bReturn = UpdateData (FALSE);
	ASSERT (bReturn);
	// Need to specifically tell the Z display to update (because the above
	// doesn't cause a CHANGE event to occur
	UpdateZDisplay ();
}

void CDlgEnvTerrainData::OnDeltaposSpinYIndex(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	// Reset the ranges on the spin controls -- need to get the new dimensions

	BOOL b = UpdateData ();
	if (!b)
	{
		// Don't update
		*pResult = 1;
		pNMUpDown->iDelta = 0;
	}
	else
	{
		// Update the range
		m_spinYIndex.SetRange (0, m_nYDim - 1);
	}

	*pResult = 0;
}

void CDlgEnvTerrainData::OnDeltaposSpinXIndex(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	// Reset the ranges on the spin controls -- need to get the new dimensions
	if (!UpdateData ())
	{
		// Don't update
		*pResult = 1;
		pNMUpDown->iDelta = 0;
	}
	else
	{
		// Update the range
		m_spinXIndex.SetRange (0, m_nXDim - 1);
	}
	
	*pResult = 0;
}

void CDlgEnvTerrainData::OnButtonApplyDepth() 
{
	// Make sure the indices are in range of the specifed dimensions

	// Pick up the new data)
	if (!UpdateData ())
	{
		// Validation error, so return
		return;
	}

	// Check the index ranges
	if (m_nXIndex > m_nXDim - 1 || m_nYIndex > m_nYDim)
	{
		// Give a message warning that the indices are out of range and will be reset
		AfxMessageBox ("The specified indices are out of range and will be reset");

		// Reset the indices
		m_nXIndex = 0;
		m_nYIndex = 0; 

		BOOL bReturn = UpdateData (FALSE);
		ASSERT (bReturn);
		
		// Need to specifically tell the Z display to update (because the above
		// doesn't cause a CHANGE event to occur
		UpdateZDisplay ();
		
		// Don't do anything, just return and let the user give valid indices
		return;
	}


	// The dimensions are OK, because they are updated with any change to the index box
	// Everything is fine, so set the data
	SetZValue (m_nXIndex, m_nYIndex, m_dZValue);
}

void CDlgEnvTerrainData::OnChangeEditXIndex() 
{
	UpdateZDisplay ();
}

void CDlgEnvTerrainData::OnChangeEditYIndex() 
{
	UpdateZDisplay ();
}

void CDlgEnvTerrainData::UpdateZDisplay()
{
	if (m_bInitDialogCalledYet)
	{
		if (!UpdateData ())
			return;

		// Update the dimensions in the data
		SetArrayDimensions (m_nXDim, m_nYDim);

		// Retrieve the value at that Z
		m_dZValue = GetZValue (m_nXIndex, m_nYIndex);

		BOOL bReturn = UpdateData (FALSE);
		ASSERT (bReturn);
	}
}

void CDlgEnvTerrainData::SetArrayDimensions(int XNewDim, int YNewDim)
{
	ASSERT (XNewDim >= TERRAIN_DIM_MIN && XNewDim <= TERRAIN_DIM_MAX);
	ASSERT (YNewDim >= TERRAIN_DIM_MIN && YNewDim <= TERRAIN_DIM_MAX);
	
	int i;
	int XOldDim = m_nArrayXDim;
	int YOldDim = m_nArrayYDim;
	// Look at each X row of Y values and add or subtract as needed
	for (i = 0; i < min(XNewDim, XOldDim); i++)
	{
		if (YNewDim > YOldDim)
		{
			m_arrayZ.InsertAt (i * YNewDim + YOldDim, 0, YNewDim - YOldDim);
		}
		else
		{
			m_arrayZ.RemoveAt (i * YNewDim + YNewDim, YOldDim - YNewDim);			
		}
	}

	// Add X lines
	if (XNewDim > XOldDim)
	{
		m_arrayZ.InsertAt (XOldDim * YNewDim, 0, (XNewDim - XOldDim) * YNewDim);
	}
	else
	{
		m_arrayZ.RemoveAt (XNewDim * YNewDim, (XOldDim - XNewDim) * YOldDim);
	}

	// Same the new dimensions
	m_nArrayXDim = XNewDim;
	m_nArrayYDim = YNewDim;
}

double CDlgEnvTerrainData::GetZValue(int nXIndex, int nYIndex)
{
	ASSERT (nXIndex >= 0 && nXIndex < m_nArrayXDim);
	ASSERT (nYIndex >= 0 && nYIndex < m_nArrayYDim);

	// Note: X rows of Y values
	return m_arrayZ.GetAt (nXIndex*m_nArrayYDim + nYIndex);
}

void CDlgEnvTerrainData::SetZValue(int nXIndex, int nYIndex, double dZValue)
{
	ASSERT (nXIndex >= 0 && nXIndex < m_nArrayXDim);
	ASSERT (nYIndex >= 0 && nYIndex < m_nArrayYDim);

	// Note: X rows of Y values
	m_arrayZ.SetAt (nXIndex*m_nArrayYDim + nYIndex, dZValue);
}

void CDlgEnvTerrainData::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
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
		
		COLORREF crBrushColor = m_crCoveringColor;
	
		// Create a brush which will be used to draw the rect
		CBrush brushBackground (crBrushColor);

		CBrush* pbrushOld = dc.SelectObject (&brushBackground);

		bSuccess = dc.Rectangle (rectClient);
		ASSERT (bSuccess);

		// Restore the previous brush to prevent GDI leaks
		dc.SelectObject (pbrushOld);
		
		dc.Detach ();
	}
  
	else if (nIDCtl == IDC_BUTTON_WIREFRAME_COLOR)
	{
		CDC dc;
		BOOL bSuccess = dc.Attach (lpDrawItemStruct->hDC);
		ASSERT (bSuccess);
	
		// Get a pointer to the button
		CButton* pButton = static_cast <CButton*> (GetDlgItem (IDC_BUTTON_WIREFRAME_COLOR));
		ASSERT (pButton);
		// Get the dimension of the button
		CRect rectClient;
		pButton->GetClientRect (rectClient);
		
		COLORREF crBrushColor = m_crWireframeColor;
	
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

void CDlgEnvTerrainData::OnRadioColor() 
{
	m_buttonTextureBrowse.EnableWindow (FALSE);
	m_editTextureFile.EnableWindow (FALSE);
	m_buttonChooseColor.EnableWindow (TRUE);

}

void CDlgEnvTerrainData::OnRadioTexture() 
{
	m_buttonTextureBrowse.EnableWindow (TRUE);
	m_editTextureFile.EnableWindow (TRUE);
	m_buttonChooseColor.EnableWindow (FALSE);
	
}

void CDlgEnvTerrainData::OnButtonChooseColor() 
{
	// Open the color dialog
	CColorDialog dlg;

	// Initialize the color choice to the current color and automatically
	// expand the custom dialog part so the user will see the initial color.
	dlg.m_cc.Flags |= (CC_RGBINIT | CC_FULLOPEN);
	dlg.m_cc.rgbResult = m_crCoveringColor;

	if (dlg.DoModal () == IDOK)
	{
		COLORREF crColor = dlg.GetColor ();
		m_crCoveringColor = crColor;

		// Cause a repaint on the button to show the new color
		CButton* pButton = static_cast <CButton*> (GetDlgItem (IDC_BUTTON_COLOR_EXAMPLE));
		pButton->Invalidate (TRUE);
	}	
}


void CDlgEnvTerrainData::SetFilename(CString strTerrainFile, CString strTerrainPath)
{
	m_strTerrainFile = strTerrainFile;
	m_strTerrainPath = strTerrainPath;
}

void CDlgEnvTerrainData::OnOK() 
{
	// Validate
	if (!UpdateData ())
		return;
	
  // Save the Wireframe Overlay checkbox & parameters in TerrainData
  m_pCdmvTerrainData->SetWireframeOverlay(m_bWireframeOverlay);
  m_pCdmvTerrainData->SetWireframe(m_crWireframeColor, m_dWireframeLnWidth, m_dWireframeElevation);
  // Get the new values & draw
  WTwindow_setdrawfn (WTuniverse_getwindows(), CWTKGraphics::WTKFGDrawTerrainGrid);

	// Save the data
	SaveDialogData ();
	
	// Show save dialog box question
	CDlgEnvSaveTerrainFile dlg;

	// Set the data and filename
	dlg.SetDataPointer (m_pCdmvTerrainData);
	dlg.SetFileName (m_strTerrainFile, m_strTerrainPath);

	// Show the dialog
	dlg.DoModal ();
	
	// Save the filename
	dlg.GetFilename (m_strTerrainFile, m_strTerrainPath);

	CDialog::OnOK();
}

void CDlgEnvTerrainData::GetFileName(CString &rstrTerrainFile, CString &rstrTerrainPath) const
{
	rstrTerrainFile = m_strTerrainFile;
	rstrTerrainPath = m_strTerrainPath;
}


void CDlgEnvTerrainData::OnButtonBrowse() 
{
	CFileDialog dlg (TRUE, /* make an open dlg */
		".jpg", /* default extension */
		m_strTextureFile, /* initial filename */
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"All Supported Files (*.jpg;*.rgb;*.tga)|\
*.jpg;*.rgb;*.tga|JPEG Files (*.jpg)|*.jpg|RGB Format (*.rgb)|*.rgb|Targa Files (*.tga)|*.tga||",	/* filter */
		NULL /* parent */
		);
	
	if (m_strTexturePath.GetLength () > 0)
		dlg.m_ofn.lpstrInitialDir = m_strTexturePath;

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

		// Save the data
		m_strTextureFile = strFile;
		m_strTexturePath = strPath;
		// Set the text
		SetDlgItemText (IDC_EDIT_TEXTURE_FILE, strFile);
	}	

}

void CDlgEnvTerrainData::OnKillfocusEditGridResolution() 
{
	if (!UpdateData ())
		return;

	// Recalculate the size
	//m_dSizeX = (m_nXDim - 1) * m_dGridResolution;
  m_dSizeX = (m_nXDim - 1) * m_dXGridResolution;
	//m_dSizeY = (m_nYDim - 1) * m_dGridResolution;
  m_dSizeY = (m_nYDim - 1) * m_dYGridResolution;

	// Redisplay the data
	BOOL bResult = UpdateData (FALSE);
	ASSERT (bResult);
}

void CDlgEnvTerrainData::OnKillfocusEditXDim() 
{
	if (!UpdateData ())
		return;

	// Recalculate the size
	//m_dSizeX = (m_nXDim - 1) * m_dGridResolution;
  m_dSizeX = (m_nXDim - 1) * m_dXGridResolution;
	//m_dSizeY = (m_nYDim - 1) * m_dGridResolution;
  m_dSizeY = (m_nYDim - 1) * m_dYGridResolution;

	// Redisplay the data
	BOOL bResult = UpdateData (FALSE);
	ASSERT (bResult);	
}

void CDlgEnvTerrainData::OnKillfocusEditYDim() 
{
	if (!UpdateData ())
		return;

	// Recalculate the size
	//m_dSizeX = (m_nXDim - 1) * m_dGridResolution;
  m_dSizeX = (m_nXDim - 1) * m_dXGridResolution;
	//m_dSizeY = (m_nYDim - 1) * m_dGridResolution;
  m_dSizeY = (m_nYDim - 1) * m_dYGridResolution;

	// Redisplay the data
	BOOL bResult = UpdateData (FALSE);
	ASSERT (bResult);	
}

void CDlgEnvTerrainData::OnCheckWireframeOverlay() 
{
//ifdef ROBOTBUILDER
	// Update the Data
	VERIFY (UpdateData ());
	// If Wireframe overlay on terrain is checked,
  // enable all the parameters
  if (m_bWireframeOverlay) {
    m_buttonChooseWireframeColor.EnableWindow(TRUE);
    m_editWireframeLnWidth.EnableWindow(TRUE);
    m_editWireframeElevation.EnableWindow(TRUE);
    // Update the check box, if it has changed
		VERIFY(UpdateData(FALSE));
  }
  else {
    m_buttonChooseWireframeColor.EnableWindow(FALSE);
    m_editWireframeLnWidth.EnableWindow(FALSE);
    m_editWireframeElevation.EnableWindow(FALSE);
  }
//#endif
}

void CDlgEnvTerrainData::OnButtonChooseWireframeColor() 
{
	// Open the color dialog
	CColorDialog dlg;

	// Initialize the color choice to the current color and automatically
	// expand the custom dialog part so the user will see the initial color.
	dlg.m_cc.Flags |= (CC_RGBINIT | CC_FULLOPEN);
	dlg.m_cc.rgbResult = m_crWireframeColor;

	if (dlg.DoModal () == IDOK)
	{
		COLORREF crColor = dlg.GetColor ();
		m_crWireframeColor = crColor;

		// Cause a repaint on the button to show the new color
		CButton* pButton = static_cast <CButton*> (GetDlgItem (IDC_BUTTON_WIREFRAME_COLOR));
		pButton->Invalidate (TRUE);
	}	
}
