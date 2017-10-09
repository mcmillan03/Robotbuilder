// DlgCameraControl.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgCameraControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCameraControl dialog


CDlgCameraControl::CDlgCameraControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCameraControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCameraControl)
	m_dOffsetX = 0.0;
	m_dOffsetY = 0.0;
	m_dOffsetZ = 0.0;
	m_nControlType = -1;
	m_bSetInertialAxesAsCoi = FALSE;
	m_bUseViewportFrame = FALSE;
	m_dViewAngleDeg = 9;
	//}}AFX_DATA_INIT
	m_pCameraData = NULL;

// See note in DlgCameraControl.h
#ifdef ROBOTBUILDER
	m_bUseInertialZ = FALSE;
	m_pCdmvCFGData = NULL;
#endif
}


void CDlgCameraControl::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fOffsetX = (float) m_dOffsetX;
	float fOffsetY = (float) m_dOffsetY;
	float fOffsetZ = (float) m_dOffsetZ;
	float fViewAngleDeg = (float) m_dViewAngleDeg;  //View Angle Degree edit box
	
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCameraControl)
	DDX_Control(pDX, IDC_CHECK_USE_VIEWPORT, m_checkUseViewportFrame);
	DDX_Control(pDX, IDC_CHECK_INERTIAL, m_checkSetInertialAxesAsCoi);
	// This control is actually used for both (so the control may be hidden in RBModeler
	DDX_Control(pDX, IDC_USEINERTIALZ, m_checkUseInertialZ);
	DDX_Control(pDX, IDC_EDIT_OFFSET_Z, m_editOffsetZ);
	DDX_Control(pDX, IDC_EDIT_OFFSET_Y, m_editOffsetY);
	DDX_Control(pDX, IDC_EDIT_OFFSET_X, m_editOffsetX);
	DDX_Control(pDX, IDC_EDIT_VIEWANGLE_DEG, m_editViewAngleDeg);
	DDX_Text(pDX, IDC_EDIT_VIEWANGLE_DEG, fViewAngleDeg);
	DDX_Text(pDX, IDC_EDIT_OFFSET_X, fOffsetX);
	DDX_Text(pDX, IDC_EDIT_OFFSET_Y, fOffsetY);
	DDX_Text(pDX, IDC_EDIT_OFFSET_Z, fOffsetZ);
	DDX_Radio(pDX, IDC_RADIO_PAN, m_nControlType);
	DDX_Check(pDX, IDC_CHECK_INERTIAL, m_bSetInertialAxesAsCoi);
	DDX_Check(pDX, IDC_CHECK_USE_VIEWPORT, m_bUseViewportFrame);
#ifdef ROBOTBUILDER
	DDX_Check(pDX, IDC_USEINERTIALZ, m_bUseInertialZ);
#endif
	//}}AFX_DATA_MAP

	m_dOffsetX = fOffsetX;
	m_dOffsetY = fOffsetY;
	m_dOffsetZ = fOffsetZ;
	m_dViewAngleDeg = fViewAngleDeg;  ///View angle
}


BEGIN_MESSAGE_MAP(CDlgCameraControl, CDialog)
	//{{AFX_MSG_MAP(CDlgCameraControl)
	//ON_BN_CLICKED(IDC_RADIO_EXAMINE, OnRadioExamine)
	//ON_BN_CLICKED(IDC_RADIO_PAN, OnRadioPan)
	ON_BN_CLICKED(IDC_CHECK_INERTIAL, OnCheckInertial)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCameraControl message handlers

BOOL CDlgCameraControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make the data has been set
	ASSERT (AfxIsValidAddress (m_pCameraData, sizeof (CCameraData), TRUE));

	// Get the control type
	if (m_pCameraData->GetViewInPanMode ())
		m_nControlType = CAMERA_CONTROL_RADIO_PAN;
	else
		m_nControlType = CAMERA_CONTROL_RADIO_EXAMINE;
	
	/* Removed 6/3/2003 - LMF
		Note: Because Pan mode now updates the center of interest,
		disabling this is unnecessary
	
	// Enable or disable offset
	if (m_nControlType == CAMERA_CONTROL_RADIO_PAN)
	{
		m_editOffsetX.EnableWindow (FALSE);
		m_editOffsetY.EnableWindow (FALSE);
		m_editOffsetZ.EnableWindow (FALSE);
		m_checkSetInertialAxesAsCoi.EnableWindow (FALSE);
		m_checkUseViewportFrame.EnableWindow (FALSE);
	}
	else
	{
		m_editOffsetX.EnableWindow (TRUE);
		m_editOffsetY.EnableWindow (TRUE);
		m_editOffsetZ.EnableWindow (TRUE);
		m_checkSetInertialAxesAsCoi.EnableWindow (TRUE);
		m_checkUseViewportFrame.EnableWindow (TRUE);
	}

	*/

	/// Loads the current WTK view angle to the edit box
	//m_dViewAngleDeg = 180/PI*WTwindow_getviewangle (WTuniverse_getwindows());
  // Loads the view angle to the edit box
  float ViewAngleDeg = 180/PI*WTwindow_getviewangle (WTuniverse_getwindows());
  m_pCameraData->GetViewAngleDegree (ViewAngleDeg);
	m_dViewAngleDeg = ViewAngleDeg;

	// Initialize the offset
	WTp3 wtp3Offset;
	m_pCameraData->GetCenterOfInterestOffset (wtp3Offset);
	m_dOffsetX = wtp3Offset[X];
	m_dOffsetY = wtp3Offset[Y];
	m_dOffsetZ = wtp3Offset[Z];

	m_bUseViewportFrame = m_pCameraData->GetUseViewportFrameForExamineView ();

	// Set the correct text for the checkbox --
	// In RobotBuilder, the setting is for the inertial coordinate frame
	// in RobotModeler, it is relative to the link frame.  The meaning is the same,
	// but the wording is changed to make it clear to the user.
	// Also, hide the use inertial Z control for RobotModeler, as it has no meaning here
	// (see note in DlgCameraControl.h)
#ifdef ROBOTBUILDER
	// Disable the InertialZ Checkbox if using
	// inertial axes as coi
	if (m_bSetInertialAxesAsCoi)
	{
		m_checkUseInertialZ.EnableWindow(FALSE);
	}

	m_bUseInertialZ = m_pCdmvCFGData->GetUseInertialZ();

	m_checkSetInertialAxesAsCoi.SetWindowText (_T("Set Inertial Axes as the Center of Interest"));
#else
	m_checkSetInertialAxesAsCoi.SetWindowText (_T("Set Link Axes as the Center of Interest"));
	m_checkUseInertialZ.ShowWindow(SW_HIDE);
#endif

	//  Display new data
	VERIFY (UpdateData (FALSE));
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCameraControl::SetDataClassPointer(CCameraData *pCameraData)
{
	// Make sure address is valid
	ASSERT (AfxIsValidAddress (pCameraData, sizeof (CCameraData), TRUE));

	// Save the pointer
	m_pCameraData = pCameraData;

}

void CDlgCameraControl::OnOK() 
{
	// Make the data has been set
	ASSERT (AfxIsValidAddress (m_pCameraData, sizeof (CCameraData), TRUE));

	// Pick up the data - if validation fails return
	if (!UpdateData ())
		return;

	// Save the data
	// Set the control type
	if (m_nControlType == CAMERA_CONTROL_RADIO_PAN)
		m_pCameraData->SetViewInPanMode (TRUE);
	else
		m_pCameraData->SetViewInPanMode (FALSE);

  //Set the new value for the view angle in edit box inputted by user
  WTwindow_setviewangle (WTuniverse_getwindows(), (float) m_dViewAngleDeg*PI/180);
	m_pCameraData->SetViewAngleDegree (m_dViewAngleDeg);  //Update the CameraData

	// Save the offset
	WTp3 wtp3Offset;
	wtp3Offset[X] = (float) m_dOffsetX;
	wtp3Offset[Y] = (float) m_dOffsetY;
	wtp3Offset[Z] = (float) m_dOffsetZ;
	m_pCameraData->SetCenterOfInterestOffset (wtp3Offset);
	m_pCameraData->SetUseViewportFrameForExamineView (m_bUseViewportFrame);
// see note in DlgCameraControl.h
#ifdef ROBOTBUILDER
	ASSERT (m_pCdmvCFGData);
	m_pCdmvCFGData->SetUseInertialZ(m_bUseInertialZ);
	m_pCdmvCFGData->SetInertialAxesAsCoi(m_bSetInertialAxesAsCoi);
  m_pCdmvCFGData->SetViewAngle_Degree (m_dViewAngleDeg);  //Update the CFGData too

#endif

	CDialog::OnOK();
}


/* Removed 6/3/2003 - LMF

  Note: Because Pan now actively updates center of interest,
  there is no reason why it cannot be enabled in Pan mode.


void CDlgCameraControl::OnRadioExamine() 
{
	// Update the data
	VERIFY (UpdateData ());

	// Enable or disable
	if (m_nControlType == CAMERA_CONTROL_RADIO_PAN)
	{
		m_editOffsetX.EnableWindow (FALSE);
		m_editOffsetY.EnableWindow (FALSE);
		m_editOffsetZ.EnableWindow (FALSE);
		m_checkSetInertialAxesAsCoi.EnableWindow (FALSE);
		m_checkUseViewportFrame.EnableWindow (FALSE);
	}
	else
	{
		m_editOffsetX.EnableWindow (TRUE);
		m_editOffsetY.EnableWindow (TRUE);
		m_editOffsetZ.EnableWindow (TRUE);
		m_checkSetInertialAxesAsCoi.EnableWindow (TRUE);
		m_checkUseViewportFrame.EnableWindow (TRUE);
	}
}

void CDlgCameraControl::OnRadioPan() 
{
	// Update the data
	VERIFY (UpdateData ());

	// Enable or disable
	if (m_nControlType == CAMERA_CONTROL_RADIO_PAN)
	{
		m_editOffsetX.EnableWindow (FALSE);
		m_editOffsetY.EnableWindow (FALSE);
		m_editOffsetZ.EnableWindow (FALSE);
		m_checkSetInertialAxesAsCoi.EnableWindow (FALSE);
		m_checkUseViewportFrame.EnableWindow (FALSE);
	}
	else
	{
		m_editOffsetX.EnableWindow (TRUE);
		m_editOffsetY.EnableWindow (TRUE);
		m_editOffsetZ.EnableWindow (TRUE);
		m_checkSetInertialAxesAsCoi.EnableWindow (TRUE);
		m_checkUseViewportFrame.EnableWindow (TRUE);
	}
}
*/

// Should be called before domodal to set up the initial state
void CDlgCameraControl::SetInertialAxesAsCoi(BOOL bSetInertialAxesAsCoi)
{
	m_bSetInertialAxesAsCoi = bSetInertialAxesAsCoi;

// see not in DlgCameraControl.h
#ifdef ROBOTBUILDER
	//if inertial axes is the center of interest,
	//make sure the use inertial z is checked
	if (m_bSetInertialAxesAsCoi) {
		m_bUseInertialZ = TRUE;
	}
#endif
}

// Call after DoModal to get the state
BOOL CDlgCameraControl::GetInertialAxesAsCoi() const
{
	return m_bSetInertialAxesAsCoi;
}

BOOL CDlgCameraControl::ValidateAndSaveData()
{
	return TRUE;
}

// see note in DlgCameraControl.h
#ifdef ROBOTBUILDER
void CDlgCameraControl::SetCFGClassPointer(CdmvCFGData *pCdmvCFGData)
{
	m_pCdmvCFGData = pCdmvCFGData;	
}
#endif

void CDlgCameraControl::OnCheckInertial() 
{
// see note in DlgCameraControl.h
#ifdef ROBOTBUILDER
	// Update the Data
	VERIFY (UpdateData ());

	// If inertial axes is center of interest,
	// check and disable use inertial z
	if (m_bSetInertialAxesAsCoi) {
		m_bUseInertialZ = TRUE;
		m_checkUseInertialZ.EnableWindow(FALSE);

		// Update the check box, if it has changed
		VERIFY(UpdateData(FALSE));
	}
	else {
		m_checkUseInertialZ.EnableWindow(TRUE);
	}
#endif
}
