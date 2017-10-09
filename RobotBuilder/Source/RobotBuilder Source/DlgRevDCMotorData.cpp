// DlgRevDCMotorData.cpp : implementation file
//

#include "stdafx.h"
#include "DMViewer.h"
#include "DlgRevDCMotorData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRevDCMotorData dialog


CDlgRevDCMotorData::CDlgRevDCMotorData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRevDCMotorData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRevDCMotorData)
	//}}AFX_DATA_INIT
	m_pCdmvRevDCMotorData = NULL;
	m_strtRevDCMotorParameters.fArmatureResistance = 0.0f;
	m_strtRevDCMotorParameters.fBackEMFConstant = 0.0f;
	m_strtRevDCMotorParameters.fCoulombFrictionConstant = 0.0f;
	m_strtRevDCMotorParameters.fHalfDropValue = 0.0f;
	m_strtRevDCMotorParameters.fMaxBrushDrop = 0.0f;
	m_strtRevDCMotorParameters.fRotorInertia = 0.0f;
	m_strtRevDCMotorParameters.fTorqueConstant = 0.0f;
	m_strtRevDCMotorParameters.fViscousFrictionConstant = 0.0f;
	m_strtRevDCMotorParameters.fGearRatio = 0.0f;
}


void CDlgRevDCMotorData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRevDCMotorData)
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_ARMATURE_RESISTANCE, m_strtRevDCMotorParameters.fArmatureResistance);
	DDV_MinMaxDouble(pDX, m_strtRevDCMotorParameters.fArmatureResistance, REV_DC_MOTOR_ARMATURE_RESISTANCE_MIN, REV_DC_MOTOR_ARMATURE_RESISTANCE_MAX);
	DDX_Text(pDX, IDC_EDIT_BACK_EMF_CONSTANT, m_strtRevDCMotorParameters.fBackEMFConstant);
	DDV_MinMaxDouble(pDX, m_strtRevDCMotorParameters.fBackEMFConstant, REV_DC_MOTOR_BACK_EMF_CONSTANT_MIN, REV_DC_MOTOR_BACK_EMF_CONSTANT_MAX);
	DDX_Text(pDX, IDC_EDIT_COULOMB_FRICTION_CONSTANT, m_strtRevDCMotorParameters.fCoulombFrictionConstant);
	DDV_MinMaxDouble(pDX, m_strtRevDCMotorParameters.fCoulombFrictionConstant, REV_DC_MOTOR_COULOMB_FRICTION_MIN, REV_DC_MOTOR_COULOMB_FRICTION_MAX);
	DDX_Text(pDX, IDC_EDIT_HALF_DROP_VALUE, m_strtRevDCMotorParameters.fHalfDropValue);
	DDV_MinMaxDouble(pDX, m_strtRevDCMotorParameters.fHalfDropValue, REV_DC_MOTOR_HALF_DROP_MIN, REV_DC_MOTOR_HALF_DROP_MAX);
	DDX_Text(pDX, IDC_EDIT_ROTOR_INERTIA, m_strtRevDCMotorParameters.fRotorInertia);
	DDV_MinMaxDouble(pDX, m_strtRevDCMotorParameters.fRotorInertia, REV_DC_MOTOR_INERTIA_MIN, REV_DC_MOTOR_INERTIA_MAX);
	DDX_Text(pDX, IDC_EDIT_TORQUE_CONSTANT, m_strtRevDCMotorParameters.fTorqueConstant);
	DDV_MinMaxDouble(pDX, m_strtRevDCMotorParameters.fTorqueConstant, REV_DC_MOTOR_TORQUE_CONSTANT_MIN, REV_DC_MOTOR_TORQUE_CONSTANT_MAX);
	DDX_Text(pDX, IDC_EDIT_VISCOUS_FRICTION_CONSTANT, m_strtRevDCMotorParameters.fViscousFrictionConstant);
	DDV_MinMaxDouble(pDX, m_strtRevDCMotorParameters.fViscousFrictionConstant, REV_DC_MOTOR_VISCOUS_FRICTION_MIN, REV_DC_MOTOR_VISCOUS_FRICTION_MAX);
	DDX_Text(pDX, IDC_EDIT_MAXIMUM_DROP_VALUE, m_strtRevDCMotorParameters.fMaxBrushDrop);
	DDV_MinMaxDouble(pDX, m_strtRevDCMotorParameters.fMaxBrushDrop, REV_DC_MOTOR_MAX_BRUSH_DROP_MIN, REV_DC_MOTOR_MAX_BRUSH_DROP_MAX);
	DDX_Text(pDX, IDC_EDIT_GEAR_RATIO, m_strtRevDCMotorParameters.fGearRatio);
	DDV_MinMaxDouble(pDX, m_strtRevDCMotorParameters.fGearRatio, REV_DC_MOTOR_GEAR_RATIO_MIN, REV_DC_MOTOR_GEAR_RATIO_MAX);
}


BEGIN_MESSAGE_MAP(CDlgRevDCMotorData, CDialog)
	//{{AFX_MSG_MAP(CDlgRevDCMotorData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRevDCMotorData message handlers

BOOL CDlgRevDCMotorData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT (m_pCdmvRevDCMotorData);
	
	m_pCdmvRevDCMotorData->GetParameters (&m_strtRevDCMotorParameters);

	// Set DDX the dialog data.
	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRevDCMotorData::SaveDialogData()
{
	// The UpdateData function should have already been called by the client

	ASSERT (m_pCdmvRevDCMotorData);
	m_pCdmvRevDCMotorData->SetParameters (&m_strtRevDCMotorParameters);
}

void CDlgRevDCMotorData::OnCancel()
{
	delete m_pCdmvRevDCMotorData;
}
