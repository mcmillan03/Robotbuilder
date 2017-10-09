// DlgConfigSimulation.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgConfigSimulation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigSimulation dialog


CDlgConfigSimulation::CDlgConfigSimulation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfigSimulation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConfigSimulation)
	m_nDisplayRate = 0;
	m_dStepSize = 0.0;
	m_bRealTime = FALSE;
	m_dEulerStepSize = MINIMUM_EULER_STEP_SIZE;
	m_dRK4StepSize = MINIMUM_RK4_STEP_SIZE;
	m_dRK45Epsilon = MINIMUM_RK45_EPSILON;
	m_dRK45MinimumStepSize = MINIMUM_RK45_MINIMUM_STEP_SIZE;
	m_nIntegratorType = 0;
	//}}AFX_DATA_INIT
}


void CDlgConfigSimulation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConfigSimulation)
	DDX_Control(pDX, IDC_EDIT_RK45_MINIMUM_STEP_SIZE, m_editRK45MinimumStepSize);
	DDX_Control(pDX, IDC_EDIT_RK45_EPSILON, m_editRK45Epsilon);
	DDX_Control(pDX, IDC_EDIT_RK4_STEP_SIZE, m_editRK4StepSize);
	DDX_Control(pDX, IDC_EDIT_EULER_STEP_SIZE, m_editEulerStepSize);
	DDX_Text(pDX, IDC_EDIT_DISPLAY_RATE, m_nDisplayRate);
	DDV_MinMaxInt(pDX, m_nDisplayRate, MINIMUM_DISPLAY_RATE, MAXIMUM_DISPLAY_RATE);
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConfigSimulation, CDialog)
	//{{AFX_MSG_MAP(CDlgConfigSimulation)
	ON_BN_CLICKED(IDC_RADIO_EULER, OnRadioEuler)
	ON_BN_CLICKED(IDC_RADIO_PLACEMENT, OnRadioPlacement)
	ON_BN_CLICKED(IDC_RADIO_RK4, OnRadioRk4)
	ON_BN_CLICKED(IDC_RADIO_RK45, OnRadioRk45)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigSimulation message handlers
void CDlgConfigSimulation::SetDataClass(CdmvCFGData *pCdmvCFGData)
{
	ASSERT (pCdmvCFGData);

	m_pCdmvCFGData = pCdmvCFGData;
}

BOOL CDlgConfigSimulation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make sure the data class has been set
	ASSERT (m_pCdmvCFGData);

	// Populate the data members with known values
	m_bRealTime = m_pCdmvCFGData->GetRealTime ();
	m_dStepSize = m_pCdmvCFGData->GetControlStepSize ();
	m_nDisplayRate = m_pCdmvCFGData->GetSimulationDisplayRate ();
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

	// Reset the dialog items with the newly retrieved data
	BOOL bSuccess;
	bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgConfigSimulation::OnRadioEuler() 
{
	m_editEulerStepSize.EnableWindow (TRUE);
	m_editRK4StepSize.EnableWindow (FALSE);
	m_editRK45Epsilon.EnableWindow (FALSE);
	m_editRK45MinimumStepSize.EnableWindow (FALSE);
}

void CDlgConfigSimulation::OnRadioPlacement() 
{
	m_editEulerStepSize.EnableWindow (FALSE);
	m_editRK4StepSize.EnableWindow (FALSE);
	m_editRK45Epsilon.EnableWindow (FALSE);
	m_editRK45MinimumStepSize.EnableWindow (FALSE);	
}

void CDlgConfigSimulation::OnRadioRk4() 
{
	m_editEulerStepSize.EnableWindow (FALSE);
	m_editRK4StepSize.EnableWindow (TRUE);
	m_editRK45Epsilon.EnableWindow (FALSE);
	m_editRK45MinimumStepSize.EnableWindow (FALSE);
}

void CDlgConfigSimulation::OnRadioRk45() 
{
	m_editEulerStepSize.EnableWindow (FALSE);
	m_editRK4StepSize.EnableWindow (FALSE);
	m_editRK45Epsilon.EnableWindow (TRUE);
	m_editRK45MinimumStepSize.EnableWindow (TRUE);	
}

void CDlgConfigSimulation::OnItemchangingListArtAndControl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 1;
}

BOOL CDlgConfigSimulation::ValidateAndSaveData()
{
	// Validation
	if (ValidateData())
	{
		// Save the data
		m_pCdmvCFGData->SetControlStepSize(m_dStepSize);
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

		return TRUE;
	}
	else
	{	// Validation failed
		return FALSE;
	}
}

BOOL CDlgConfigSimulation::ValidateData()
{
	return UpdateData (TRUE);
}
