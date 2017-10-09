// PPageActuatorData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PPageActuatorData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageActuatorData property page

IMPLEMENT_DYNCREATE(CPPageActuatorData, CPPageLinkBase)

CPPageActuatorData::CPPageActuatorData() : CPPageLinkBase(CPPageActuatorData::IDD)
{
	//{{AFX_DATA_INIT(CPPageActuatorData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pCdmvRevoluteLinkData = NULL;
}

CPPageActuatorData::~CPPageActuatorData()
{
}

void CPPageActuatorData::DoDataExchange(CDataExchange* pDX)
{
	CPPageLinkBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageActuatorData)
	DDX_Control(pDX, IDC_COMBO_ACTUATOR_TYPE, m_comboActuatorType);
	DDX_Control(pDX, IDC_STATIC_ACTUATOR_TYPE_DATA_RECT, m_staticActuatorTypeDataRect);
	//}}AFX_DATA_MAP
	if (pDX->m_bSaveAndValidate)
	{
		if (!UpdateData (pDX->m_bSaveAndValidate))
			pDX->Fail ();
	}
}


BEGIN_MESSAGE_MAP(CPPageActuatorData, CPPageLinkBase)
	//{{AFX_MSG_MAP(CPPageActuatorData)
	ON_CBN_SELCHANGE(IDC_COMBO_ACTUATOR_TYPE, OnSelchangeComboActuatorType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageActuatorData message handlers

void CPPageActuatorData::OnOK() 
{
//	if (!UpdateData (TRUE))
//		return;
	
	int nCurrentActuatorSelection;
	nCurrentActuatorSelection = m_comboActuatorType.GetCurSel ();
	ASSERT (nCurrentActuatorSelection != CB_ERR);

	if (nCurrentActuatorSelection == CB_NO_MOTOR)
	{
		m_dlgLinkData.SaveDialogData ();

		// if there was an an actuator, delete it
		CdmvActuatorData* pActuator = m_pCdmvRevoluteLinkData->GetActuator ();

		// Check if there is an actuator and if so delete it
		if (pActuator != NULL)
		{
			m_pCdmvRevoluteLinkData->DeleteActuator ();
		}

		// Also need to delete the CRevDCMotor that was allocated for the dialog
		// since it is not being saved
		delete m_dlgRevDCMotorData.m_pCdmvRevDCMotorData;
	}
	else
	{
		m_dlgRevDCMotorData.SaveDialogData ();
		CdmvActuatorData* pActuator = m_pCdmvRevoluteLinkData->GetActuator ();

		// Check if there is an actuator and if so delete it
		if (pActuator != NULL)
		{
			m_pCdmvRevoluteLinkData->DeleteActuator ();
		}

		m_pCdmvRevoluteLinkData->SetActuator (m_dlgRevDCMotorData.m_pCdmvRevDCMotorData);
	}	
	CPPageLinkBase::OnOK();
}

void CPPageActuatorData::OnCancel() 
{
	m_dlgRevDCMotorData.OnCancel ();
	
	CPPageLinkBase::OnCancel();
}

void CPPageActuatorData::OnSelchangeComboActuatorType() 
{
	int nActuatorType = m_comboActuatorType.GetCurSel ();
	ASSERT (nActuatorType != CB_ERR);

	// enable the dialog box specific to the selected actuator type
	switch (nActuatorType)
	{
	case CB_NO_MOTOR:
		m_dlgRevDCMotorData.ShowWindow (SW_HIDE);
		m_dlgLinkData.ShowWindow (SW_SHOW);
		break;
	case CB_REV_DC_MOTOR:
		m_dlgLinkData.ShowWindow (SW_HIDE);
		m_dlgRevDCMotorData.ShowWindow (SW_SHOW);
		break;
	default:
		ASSERT (FALSE);
	}	
}

BOOL CPPageActuatorData::OnInitDialog() 
{
	CPPageLinkBase::OnInitDialog();
	
	ASSERT (m_pCdmvRevoluteLinkData);
	// 

	// I will just create a new CdmvRevDCMotorData to store the data so I can delete it
	// without having to worry about whether it is the CdmvRevDCMotorData that is actually
	// saved.  Then I can just replace the saved one (if one exists) with this one.

	// Create a new actuator, but watch for exceptions
	CdmvRevDCMotorData* pActuator;
	try {
		pActuator = new CdmvRevDCMotorData;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	// If there currently is a CdmvRevDCMotorData, populate this new one with its data
	CdmvActuatorData* pSavedActuator;
	// pick up the actuator
	pSavedActuator = m_pCdmvRevoluteLinkData->GetActuator ();
	if (pSavedActuator != NULL)
	{
		if (pSavedActuator->GetActuatorType () == REV_DC_MOTOR)
		{
			structRevDCMotorParameters strtRevDCMotorParameters;
			((CdmvRevDCMotorData*) pSavedActuator)->GetParameters (&strtRevDCMotorParameters);
			pActuator->SetParameters (&strtRevDCMotorParameters);
		}
	}


	// assign the actuator to the dialog
	m_dlgRevDCMotorData.m_pCdmvRevDCMotorData = (CdmvRevDCMotorData*) pActuator;
	// assign the link for the no motor case
	m_dlgLinkData.m_pCdmvLinkData = (CdmvLinkData*) m_pCdmvRevoluteLinkData;

	CRect rectPlacement;
	m_staticActuatorTypeDataRect.GetWindowRect (&rectPlacement);
	ScreenToClient (rectPlacement);
	if (!m_dlgRevDCMotorData.Create (IDD_REV_DC_MOTOR_DATA, this))
		AfxMessageBox ("Rev. DC Motor Data create failed!", MB_OK);
	m_dlgRevDCMotorData.MoveWindow (rectPlacement.left, rectPlacement.top,
		rectPlacement.Width(), rectPlacement.Height ());
	m_dlgRevDCMotorData.BringWindowToTop ();	
	
	if (!m_dlgLinkData.Create (IDD_LINK_DATA, this))
		AfxMessageBox ("Link Data create failed!", MB_OK);
	m_dlgLinkData.MoveWindow (rectPlacement.left, rectPlacement.top,
		rectPlacement.Width(), rectPlacement.Height ());
	m_dlgRevDCMotorData.BringWindowToTop ();	

	int nComboBoxStatus;
	// pick up the actuator
	pSavedActuator = m_pCdmvRevoluteLinkData->GetActuator ();
	if (pSavedActuator != NULL)
	{
		if (pSavedActuator->GetActuatorType () == REV_DC_MOTOR)
		{
			m_dlgLinkData.ShowWindow (SW_HIDE);
			m_dlgRevDCMotorData.ShowWindow (SW_SHOW);
			nComboBoxStatus = m_comboActuatorType.SetCurSel (CB_REV_DC_MOTOR);
			ASSERT (nComboBoxStatus != CB_ERR);
		}
		else
		{
			m_dlgLinkData.ShowWindow (SW_SHOW);
			m_dlgRevDCMotorData.ShowWindow (SW_HIDE);
			nComboBoxStatus = m_comboActuatorType.SetCurSel (CB_NO_MOTOR);
			ASSERT (nComboBoxStatus != CB_ERR);
		}
	}
	else
	{
		m_dlgLinkData.ShowWindow (SW_SHOW);
		m_dlgRevDCMotorData.ShowWindow (SW_HIDE);
		nComboBoxStatus = m_comboActuatorType.SetCurSel (CB_NO_MOTOR);
		ASSERT (nComboBoxStatus != CB_ERR);
	}
	
	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPPageActuatorData::UpdateData(BOOL bSaveAndValidate)
{
	// First update this and if it fails return
//	if (!CPPageLinkBase::UpdateData (bSaveAndValidate))
//		return FALSE;

	int nCurrentActuatorSelection;

	// only try if the box has been created
	if (!m_comboActuatorType.GetSafeHwnd ())
		return TRUE;

	nCurrentActuatorSelection = m_comboActuatorType.GetCurSel ();
	ASSERT (nCurrentActuatorSelection != CB_ERR);

	if (nCurrentActuatorSelection == CB_NO_MOTOR)
	{
		return m_dlgLinkData.UpdateData (bSaveAndValidate);
	}
	else
	{
		return m_dlgRevDCMotorData.UpdateData (bSaveAndValidate);
	}
}
