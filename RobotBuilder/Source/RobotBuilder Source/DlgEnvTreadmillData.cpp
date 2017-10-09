// DlgEnvTreadmillData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgEnvTreadmillData.h"
#include "ParserTreadmill.h"
#include "DlgEnvSaveTreadmillFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvTreadmillData dialog



CDlgEnvTreadmillData::CDlgEnvTreadmillData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnvTreadmillData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEnvTreadmillData)
	//}}AFX_DATA_INIT

	int i; // for 'for' loop
	for (i = 0; i < 3; i++)
	{
		m_strtEnvTreadmillData.cvPosition[i] = 0;
		m_strtEnvTreadmillData.cvNormal[i] = 0;
		m_strtEnvTreadmillData.cvVelocityDirection[i] = 0;
	}
	m_strtEnvTreadmillData.dVelocityMagnitude = 0;
	m_strtEnvTreadmillData.dLength = 0;
	m_strtEnvTreadmillData.dWidth = 0;

	// Initialize the data pointers to NULL
	m_pCdmvTreadmillData = NULL;

}


void CDlgEnvTreadmillData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEnvTreadmillData)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_NORMAL_DIRECTION_X, m_strtEnvTreadmillData.cvNormal[X]);
	DDX_Text(pDX, IDC_EDIT_NORMAL_DIRECTION_Y, m_strtEnvTreadmillData.cvNormal[Y]);
	DDX_Text(pDX, IDC_EDIT_NORMAL_DIRECTION_Z, m_strtEnvTreadmillData.cvNormal[Z]);
	DDX_Text(pDX, IDC_EDIT_POSITION_X, m_strtEnvTreadmillData.cvPosition[X]);
	DDX_Text(pDX, IDC_EDIT_POSITION_Y, m_strtEnvTreadmillData.cvPosition[Y]);
	DDX_Text(pDX, IDC_EDIT_POSITION_Z, m_strtEnvTreadmillData.cvPosition[Z]);
	DDX_Text(pDX, IDC_EDIT_VELOCITY_DIRECTION_X, m_strtEnvTreadmillData.cvVelocityDirection[X]);
	DDX_Text(pDX, IDC_EDIT_VELOCITY_DIRECTION_Y, m_strtEnvTreadmillData.cvVelocityDirection[Y]);
	DDX_Text(pDX, IDC_EDIT_VELOCITY_DIRECTION_Z, m_strtEnvTreadmillData.cvVelocityDirection[Z]);
	DDX_Text(pDX, IDC_EDIT_VELOCITY_MAGNITUDE, m_strtEnvTreadmillData.dVelocityMagnitude);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_strtEnvTreadmillData.dWidth);
	DDV_MinMaxDouble(pDX, m_strtEnvTreadmillData.dWidth, TREADMILL_WIDTH_MIN, TREADMILL_WIDTH_MAX);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_strtEnvTreadmillData.dLength);
	DDV_MinMaxDouble(pDX, m_strtEnvTreadmillData.dLength, TREADMILL_LENGTH_MIN, TREADMILL_LENGTH_MAX);
}


BEGIN_MESSAGE_MAP(CDlgEnvTreadmillData, CDialog)
	//{{AFX_MSG_MAP(CDlgEnvTreadmillData)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_COLOR, OnButtonChooseColor)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvTreadmillData message handlers

void CDlgEnvTreadmillData::SetDataClassPointer(CdmvTreadmillData *pCdmvTreadmillData)
{
	// I don't anticipate that this should be called twice during one instance.  I
	// suppose it's not necessarily an error though, just not expected.
	ASSERT (m_pCdmvTreadmillData == NULL);

	// Set the data member
	m_pCdmvTreadmillData = pCdmvTreadmillData;
}



/*********************************************************************\
*  Function: CDlgEnvTreadmillData::SaveDialogData
*
*  Description: Saves the data in the dialog box to the member class.
*		This function is called by the parent property page when
*		OK is pressed.
*
*  Returns:  void 
*  Argument: 
*
*  Created:  4/20/2001  Steven Rodenbaugh
\*********************************************************************/
void CDlgEnvTreadmillData::SaveDialogData()
{
	// The UpdateData function should have already been called by the client

	ASSERT (m_pCdmvTreadmillData);
	m_pCdmvTreadmillData->SetParameters (&m_strtEnvTreadmillData);
}


/*********************************************************************\
*  Function: CDlgEnvTreadmillData::OnInitDialog
*
*  Description: Called by framework upon dialog initialization
*
*  Returns:  BOOL 
*
*  Created:  4/25/2001  Steven Rodenbaugh
\*********************************************************************/
BOOL CDlgEnvTreadmillData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Verify there is a data class
	ASSERT (m_pCdmvTreadmillData);

	// Pick up the data from the class
	m_pCdmvTreadmillData->GetParameters (&m_strtEnvTreadmillData);

	// Cause the retrieved data to be displayed
	BOOL bSuccess;
	bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgEnvTreadmillData::OnButtonChooseColor() 
{
	// Open the color dialog
	CColorDialog dlg;
	
	if (dlg.DoModal () == IDOK)
	{
		COLORREF crColor = dlg.GetColor ();
		m_strtEnvTreadmillData.crColor = crColor;

		// Cause a repaint on the button to show the new color
		CButton* pButton = static_cast <CButton*> (GetDlgItem (IDC_BUTTON_COLOR_EXAMPLE));
		pButton->Invalidate (TRUE);
	}		
}

void CDlgEnvTreadmillData::SetFilename(CString strTreadmillFile, CString strPath)
{
	m_strFileName = strTreadmillFile;
	m_strPath = strPath;
}

void CDlgEnvTreadmillData::GetFilename(CString &rstrFilename, CString &rstrPath) const
{
	rstrFilename = m_strFileName;
	rstrPath = m_strPath;
}

void CDlgEnvTreadmillData::OnOK() 
{
	// Validate
	if (!UpdateData ())
		return;
	
	// Save the data
	SaveDialogData ();
	
	// Show save dialog box question
	CDlgEnvSaveTreadmillFile dlg;

	// Set the data and filename
	dlg.SetDataPointer (m_pCdmvTreadmillData);
	dlg.SetFileName (m_strFileName, m_strPath);

	// Show the dialog
	dlg.DoModal ();
	
	// Save the filename
	dlg.GetFilename (m_strFileName, m_strPath);	
	CDialog::OnOK();
}

void CDlgEnvTreadmillData::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
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
		
		COLORREF crBrushColor = m_strtEnvTreadmillData.crColor;
		
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
