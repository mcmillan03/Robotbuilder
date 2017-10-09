// DlgSimulationData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgSimulationData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSimulationData dialog


CDlgSimulationData::CDlgSimulationData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSimulationData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSimulationData)
	m_nDisplayRate = 0;
	m_strEnvironmentFile = _T("");
	m_dStepSize = 0.0;
	m_bRealTime = FALSE;
	m_dEulerStepSize = MINIMUM_EULER_STEP_SIZE;
	m_dRK4StepSize = MINIMUM_RK4_STEP_SIZE;
	m_dRK45Epsilon = MINIMUM_RK45_EPSILON;
	m_dRK45MinimumStepSize = MINIMUM_RK45_MINIMUM_STEP_SIZE;
	m_nIntegratorType = 0;
	m_dInertialAxesLength = 0.0;
	m_nInertialAxesWidth = 0;
	m_dLinkAxesLength = 0.0;
	m_nLinkAxesWidth = 0;
	m_strArticulationFile = _T("");
	m_strControlFile = _T("");
	//}}AFX_DATA_INIT

	m_pCdmvCFGData = NULL;
	m_pCCameraData = NULL;
}


void CDlgSimulationData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSimulationData)
	DDX_Control(pDX, IDC_EDIT_RK45_MINIMUM_STEP_SIZE, m_editRK45MinimumStepSize);
	DDX_Control(pDX, IDC_EDIT_RK45_EPSILON, m_editRK45Epsilon);
	DDX_Control(pDX, IDC_EDIT_RK4_STEP_SIZE, m_editRK4StepSize);
	DDX_Control(pDX, IDC_EDIT_EULER_STEP_SIZE, m_editEulerStepSize);
	DDX_Text(pDX, IDC_EDIT_DISPLAY_RATE, m_nDisplayRate);
	DDV_MinMaxInt(pDX, m_nDisplayRate, MINIMUM_DISPLAY_RATE, MAXIMUM_DISPLAY_RATE);
	DDX_Text(pDX, IDC_EDIT_ENVIRONMENT_FILE, m_strEnvironmentFile);
	DDX_Text(pDX, IDC_EDIT_STEP_SIZE, m_dStepSize);
	DDV_MinMaxDouble(pDX, m_dStepSize, MINIMUM_CONTROL_STEP_SIZE, MAXIMUM_CONTROL_STEP_SIZE);
	DDX_Check(pDX, IDC_CHECK_REAL_TIME, m_bRealTime);
	DDX_Text(pDX, IDC_EDIT_EULER_STEP_SIZE, m_dEulerStepSize);
	DDV_MinMaxDouble(pDX, m_dEulerStepSize, MINIMUM_EULER_STEP_SIZE, MAXIMUM_EULER_STEP_SIZE);
	DDX_Text(pDX, IDC_EDIT_RK4_STEP_SIZE, m_dRK4StepSize);
	DDV_MinMaxDouble(pDX, m_dRK4StepSize, MINIMUM_RK4_STEP_SIZE, MAXIMUM_RK4_STEP_SIZE);
	DDX_Text(pDX, IDC_EDIT_RK45_EPSILON, m_dRK45Epsilon);
	DDV_MinMaxDouble(pDX, m_dRK45Epsilon, MINIMUM_RK45_EPSILON, MAXIMUM_RK45_EPSILON);
	DDX_Text(pDX, IDC_EDIT_RK45_MINIMUM_STEP_SIZE, m_dRK45MinimumStepSize);
	DDV_MinMaxDouble(pDX, m_dRK45MinimumStepSize, MINIMUM_RK45_MINIMUM_STEP_SIZE, MAXIMUM_RK45_MINIMUM_STEP_SIZE);
	DDX_Radio(pDX, IDC_RADIO_PLACEMENT, m_nIntegratorType);
	DDX_Text(pDX, IDC_EDIT_INERTIAL_AXES_LENGTH, m_dInertialAxesLength);
	DDV_MinMaxDouble(pDX, m_dInertialAxesLength, MINIMUM_AXES_LENGTH, MAXIMUM_AXES_LENGTH);
	DDX_Text(pDX, IDC_EDIT_INERTIAL_AXES_WIDTH, m_nInertialAxesWidth);
	DDV_MinMaxInt(pDX, m_nInertialAxesWidth, MINIMUM_AXES_WIDTH, MAXIMUM_AXES_WIDTH);
	DDX_Text(pDX, IDC_EDIT_LINK_AXES_LENGTH, m_dLinkAxesLength);
	DDV_MinMaxDouble(pDX, m_dLinkAxesLength, MINIMUM_AXES_LENGTH, MAXIMUM_AXES_LENGTH);
	DDX_Text(pDX, IDC_EDIT_LINK_AXES_WIDTH, m_nLinkAxesWidth);
	DDV_MinMaxInt(pDX, m_nLinkAxesWidth, MINIMUM_AXES_WIDTH, MAXIMUM_AXES_WIDTH);
	DDX_Text(pDX, IDC_EDIT_ARTICULATION_FILE, m_strArticulationFile);
	DDX_Text(pDX, IDC_EDIT_CONTROL_FILE, m_strControlFile);
	DDX_Check(pDX, IDC_SETINERTIALAXESASCOI, m_bInertialAxesAsCoi);
	DDX_Check(pDX, IDC_USEYANDZ, m_bUseInertialZ);
	DDX_Text(pDX, IDC_EDIT_CENTER_OF_INTEREST, m_strCenterOfInterest);
	DDX_Text(pDX, IDC_EDIT_COI_OFFSET_X, m_dCoiOffsetX);
	DDX_Text(pDX, IDC_EDIT_COI_OFFSET_Y, m_dCoiOffsetY);
	DDX_Text(pDX, IDC_EDIT_COI_OFFSET_Z, m_dCoiOffsetZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSimulationData, CDialog)
	//{{AFX_MSG_MAP(CDlgSimulationData)
	ON_BN_CLICKED(IDC_RADIO_EULER, OnRadioEuler)
	ON_BN_CLICKED(IDC_RADIO_PLACEMENT, OnRadioPlacement)
	ON_BN_CLICKED(IDC_RADIO_RK4, OnRadioRk4)
	ON_BN_CLICKED(IDC_RADIO_RK45, OnRadioRk45)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_ART_AND_CONTROL, OnItemchangingListArtAndControl)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_COLOR, OnButtonChooseColor)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_CURRENT_COI, OnButtonLoadCurrentCoi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSimulationData message handlers

void CDlgSimulationData::SetDataClass(CdmvCFGData *pCdmvCFGData)
{
	ASSERT (pCdmvCFGData);

	m_pCdmvCFGData = pCdmvCFGData;
}

void CDlgSimulationData::SetCameraDataClass (CCameraData* pCCameraData)
{
	ASSERT (pCCameraData);

	m_pCCameraData = pCCameraData;
}

void CDlgSimulationData::SetSystemDataClass (CdmvSystemData* pCdmvSystemData)
{
	ASSERT (pCdmvSystemData);

	m_pCdmvSystemData = pCdmvSystemData;
}

BOOL CDlgSimulationData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make sure the data and camera classes have been set
	ASSERT (m_pCdmvCFGData);
	ASSERT (m_pCCameraData);

	// Populate the data members with known values
	m_bRealTime = m_pCdmvCFGData->GetRealTime ();
	m_dStepSize = m_pCdmvCFGData->GetControlStepSize ();
	m_nDisplayRate = m_pCdmvCFGData->GetSimulationDisplayRate ();
	// This is display only - just show the file
	CString strEnvironmentPath;
	m_pCdmvCFGData->GetEnvironmentFile (m_strEnvironmentFile, strEnvironmentPath);
	INTEGRATOR_TYPE theIntegratorType = m_pCdmvCFGData->GetIntegratorType ();
	if (theIntegratorType == INTEGRATOR_PLACEMENT)
	{
		m_nIntegratorType = INTEGRATOR_DLG_PLACEMENT;
		OnRadioPlacement ();
	}
	else if (theIntegratorType == INTEGRATOR_EULER)
	{
		m_nIntegratorType = INTEGRATOR_DLG_EULER;
		m_dEulerStepSize = m_pCdmvCFGData->GetIntegratorEulerParameters ();
		OnRadioEuler ();
	}
	else if (theIntegratorType == INTEGRATOR_RUNGE_KUTTA_4)
	{
		m_nIntegratorType = INTEGRATOR_DLG_RK4;
		m_dRK4StepSize = m_pCdmvCFGData->GetIntegratorRungeKutta4Parameters ();
		OnRadioRk4 ();
	}
	else if (theIntegratorType == INTEGRATOR_ADAPTIVE_4_5_RUNGE_KUTTA)
	{
		m_nIntegratorType = INTEGRATOR_DLG_RK45;
		m_pCdmvCFGData->GetIntegratorAdaptive45RungeKuttaParameters (&m_dRK45Epsilon,
			&m_dRK45MinimumStepSize);
		OnRadioRk45 ();
	}
	else
	{
		// Unexpected integrator
		ASSERT (0);
	}

	// Get the articulation file
	CString strPath;
	m_pCdmvCFGData->GetFirstArticulationFile (m_strArticulationFile, strPath);

	// Get the control file
	m_pCdmvCFGData->GetFirstControlFile (m_strControlFile, strPath);

	// Initialize the axes data
	m_pCdmvCFGData->GetInertialAxesData (m_nInertialAxesWidth, m_dInertialAxesLength);
	m_pCdmvCFGData->GetLinkAxesData (m_nLinkAxesWidth, m_dLinkAxesLength);

	// Initialize the background color example button
	m_crBackgroundColor = m_pCdmvCFGData->GetBackgroundColor ();

	// Initialize the Center of Interest
	m_strCenterOfInterest = m_pCdmvCFGData->GetCenterOfInterestName();
	
	// Initialize the Center of Interest Offset
	m_pCdmvCFGData->GetCoiOffset(&m_dCoiOffsetX, &m_dCoiOffsetY, &m_dCoiOffsetZ);
	
	// Initialize the Center of Interest Checkboxes
	m_bInertialAxesAsCoi = m_pCdmvCFGData->GetInertialAxesAsCoi();

	// Reset the dialog items with the newly retrieved data
	BOOL bSuccess;
	bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSimulationData::OnRadioEuler() 
{
	m_editEulerStepSize.EnableWindow (TRUE);
	m_editRK4StepSize.EnableWindow (FALSE);
	m_editRK45Epsilon.EnableWindow (FALSE);
	m_editRK45MinimumStepSize.EnableWindow (FALSE);
}

void CDlgSimulationData::OnRadioPlacement() 
{
	m_editEulerStepSize.EnableWindow (FALSE);
	m_editRK4StepSize.EnableWindow (FALSE);
	m_editRK45Epsilon.EnableWindow (FALSE);
	m_editRK45MinimumStepSize.EnableWindow (FALSE);	
}

void CDlgSimulationData::OnRadioRk4() 
{
	m_editEulerStepSize.EnableWindow (FALSE);
	m_editRK4StepSize.EnableWindow (TRUE);
	m_editRK45Epsilon.EnableWindow (FALSE);
	m_editRK45MinimumStepSize.EnableWindow (FALSE);
}

void CDlgSimulationData::OnRadioRk45() 
{
	m_editEulerStepSize.EnableWindow (FALSE);
	m_editRK4StepSize.EnableWindow (FALSE);
	m_editRK45Epsilon.EnableWindow (TRUE);
	m_editRK45MinimumStepSize.EnableWindow (TRUE);	
}

void CDlgSimulationData::OnOK() 
{
	// Validation
	if (UpdateData (TRUE))
	{
		// Save the data
		m_pCdmvCFGData->SetControlStepSize (m_dStepSize);
		m_pCdmvCFGData->SetSimulationDisplayRate (m_nDisplayRate);
		m_pCdmvCFGData->SetRealTime (m_bRealTime);

		if (m_nIntegratorType == INTEGRATOR_DLG_PLACEMENT)
		{
			m_pCdmvCFGData->SetIntegratorType (INTEGRATOR_PLACEMENT);
		}
		else if (m_nIntegratorType == INTEGRATOR_DLG_EULER)
		{
			m_pCdmvCFGData->SetIntegratorType (INTEGRATOR_EULER);
			m_pCdmvCFGData->SetIntegratorEulerParameters (m_dEulerStepSize);
		}
		else if (m_nIntegratorType == INTEGRATOR_DLG_RK4)
		{
			m_pCdmvCFGData->SetIntegratorType (INTEGRATOR_RUNGE_KUTTA_4);
			m_pCdmvCFGData->SetIntegratorRungeKutta4Parameters (m_dRK4StepSize);
		}
		else if (m_nIntegratorType = INTEGRATOR_DLG_RK45)
		{
			m_pCdmvCFGData->SetIntegratorType (INTEGRATOR_ADAPTIVE_4_5_RUNGE_KUTTA);
			m_pCdmvCFGData->SetIntegratorAdaptive45RungeKuttaParameters (m_dRK45Epsilon,
				m_dRK45MinimumStepSize);
		}
		else
		{
			// Unexpected integrator
			ASSERT (0);
		}

		m_pCdmvCFGData->SetInertialAxesData (m_nInertialAxesWidth, m_dInertialAxesLength);
		m_pCdmvCFGData->SetLinkAxesData (m_nLinkAxesWidth, m_dLinkAxesLength);

		m_pCdmvCFGData->SetBackgroundColor (m_crBackgroundColor);

		m_pCdmvCFGData->SetCenterOfInterestName(m_strCenterOfInterest);
		
		m_pCdmvCFGData->SetCoiOffset(m_dCoiOffsetX, m_dCoiOffsetY, m_dCoiOffsetZ);
		
		m_pCdmvCFGData->SetInertialAxesAsCoi(m_bInertialAxesAsCoi);
		
		m_pCdmvCFGData->SetUseInertialZ(m_bUseInertialZ);

		CDialog::OnOK();
	}
	
}


// This is called when an item is changing from non-selected to selected.  We don't want
// user input (or selectable items) in the list, so returning 1 in this function blocks
// the selection
void CDlgSimulationData::OnItemchangingListArtAndControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 1;
}

void CDlgSimulationData::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
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

void CDlgSimulationData::OnButtonChooseColor() 
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

void CDlgSimulationData::OnButtonLoadCurrentCoi() 
{
	// Save the contents of any data entered/changed in other edit boxes
	UpdateData();

	// Get the name of the current Center of Interest
	m_strCenterOfInterest = ((CdmvArticulationData*) m_pCdmvSystemData)->GetCenterOfInterestName();
		
	// Get the current Center of Interest Offset
	WTp3 wtp3Offset;
	m_pCCameraData->GetCenterOfInterestOffset (wtp3Offset);
	m_dCoiOffsetX = (double) wtp3Offset[X];
	m_dCoiOffsetY = (double) wtp3Offset[Y];
	m_dCoiOffsetZ = (double) wtp3Offset[Z];

	UpdateData(FALSE);	
}
