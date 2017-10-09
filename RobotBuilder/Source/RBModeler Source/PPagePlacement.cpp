// PPagePlacement.cpp : implementation file
//

#include "stdafx.h"
#include "RBModeler.h"
#include "PPagePlacement.h"
#include "Primitive.h"
#include "RBModelerRBMGraphicView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPPagePlacement property page

IMPLEMENT_DYNCREATE(CPPagePlacement, CPropertyPage)

CPPagePlacement::CPPagePlacement() : CPropertyPage(CPPagePlacement::IDD)
{
	//{{AFX_DATA_INIT(CPPagePlacement)
	//}}AFX_DATA_INIT
	m_strtPrimitiveScaleData.dXScale = 0.0;
	m_strtPrimitiveScaleData.dYScale = 0.0;
	m_strtPrimitiveScaleData.dZScale = 0.0;

	m_pPrimitive = NULL;
}

CPPagePlacement::~CPPagePlacement()
{
}

void CPPagePlacement::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fXScale = (float) m_strtPrimitiveScaleData.dXScale;
	float fYScale = (float) m_strtPrimitiveScaleData.dYScale;
	float fZScale = (float) m_strtPrimitiveScaleData.dZScale;
	float fTranslationX = (float) m_strtPrimitivePlacementData.dTranslationX;
	float fTranslationY = (float) m_strtPrimitivePlacementData.dTranslationY;
	float fTranslationZ = (float) m_strtPrimitivePlacementData.dTranslationZ;

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPagePlacement)
	DDX_Control(pDX, IDC_TAB_ROTATION, m_tabctrlRotation);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_SCALE_X, fXScale);
	DDV_MinMaxFloat(pDX, fXScale, 1e-6f, 1e6);
	DDX_Text(pDX, IDC_EDIT_SCALE_Y, fYScale);
	DDV_MinMaxFloat(pDX, fYScale, 1e-6f, 1e6);
	DDX_Text(pDX, IDC_EDIT_SCALE_Z, fZScale);
	DDV_MinMaxFloat(pDX, fZScale, 1e-6f, 1e6);
	DDX_Text(pDX, IDC_EDIT_TRANSLATION_X, fTranslationX);
	DDX_Text(pDX, IDC_EDIT_TRANSLATION_Y, fTranslationY);
	DDX_Text(pDX, IDC_EDIT_TRANSLATION_Z, fTranslationZ);

	m_strtPrimitiveScaleData.dXScale = fXScale;
	m_strtPrimitiveScaleData.dYScale = fYScale;
	m_strtPrimitiveScaleData.dZScale = fZScale;
	m_strtPrimitivePlacementData.dTranslationX = fTranslationX;
	m_strtPrimitivePlacementData.dTranslationY = fTranslationY;
	m_strtPrimitivePlacementData.dTranslationZ = fTranslationZ;
}


BEGIN_MESSAGE_MAP(CPPagePlacement, CPropertyPage)
	//{{AFX_MSG_MAP(CPPagePlacement)
	ON_EN_CHANGE(IDC_EDIT_SCALE_X, OnChangeEditScaleX)
	ON_EN_CHANGE(IDC_EDIT_SCALE_Y, OnChangeEditScaleY)
	ON_EN_CHANGE(IDC_EDIT_SCALE_Z, OnChangeEditScaleZ)
	ON_EN_CHANGE(IDC_EDIT_TRANSLATION_X, OnChangeEditTranslationX)
	ON_EN_CHANGE(IDC_EDIT_TRANSLATION_Y, OnChangeEditTranslationY)
	ON_EN_CHANGE(IDC_EDIT_TRANSLATION_Z, OnChangeEditTranslationZ)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_ROTATION, OnSelchangeTabRotation)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_ROTATION, OnSelchangingTabRotation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPagePlacement message handlers

BOOL CPPagePlacement::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pPrimitive);

	m_pPrimitive->GetPrimitivePlacement ()->GetPrimitivePlacementData (&m_strtPrimitivePlacementData);
	m_pPrimitive->GetPrimitiveScale ()->GetPrimitiveScaleAbsoluteData (&m_strtPrimitiveScaleData);


	// Setup the Rotation Tab Ctrl
	int nIndex;
	nIndex = m_tabctrlRotation.InsertItem (ROT_TAB_QUATERNION, "Quaternion");
	ASSERT (nIndex > -1);
	nIndex = m_tabctrlRotation.InsertItem (ROT_TAB_EULER_ANGLES, "XYZ Euler Angles");
	ASSERT (nIndex > -1);
	nIndex = m_tabctrlRotation.InsertItem (ROT_TAB_ANGLE_AXIS, "Angle/Axis");
	ASSERT (nIndex > -1);


	// Create the child windows for the tab ctrl
	CRect rectPlacement;
	m_tabctrlRotation.GetWindowRect (&rectPlacement);
	ScreenToClient (rectPlacement);

	// Quaternion
	BOOL bSuccess = m_dlgRotationQuaternion.Create (IDD_ROTATION_QUATERNION, this);
	ASSERT (bSuccess);
	m_dlgRotationQuaternion.MoveWindow (rectPlacement.left+5, rectPlacement.top+21,
		rectPlacement.Width()-10, rectPlacement.Height ()-25);
	// Euler Angles
	bSuccess = m_dlgRotationEulerAngles.Create (IDD_ROTATION_EULER_ANGLES, this);
	ASSERT (bSuccess);
	m_dlgRotationEulerAngles.MoveWindow (rectPlacement.left+5, rectPlacement.top+21,
		rectPlacement.Width()-10, rectPlacement.Height ()-25);
	// Angle Axis
	bSuccess = m_dlgRotationAngleAxis.Create (IDD_ROTATION_ANGLE_AXIS, this);
	ASSERT (bSuccess);
	m_dlgRotationAngleAxis.MoveWindow (rectPlacement.left+5, rectPlacement.top+21,
		rectPlacement.Width()-10, rectPlacement.Height ()-25);


	m_tabctrlRotation.SetCurSel (ROT_TAB_QUATERNION);

	// Set up the correct data based on the currently stored rotation
	CalculateRotationRepresentation ();

	// Start out by enabling the quaternion window
	m_dlgRotationAngleAxis.ShowWindow (SW_HIDE);
	m_dlgRotationEulerAngles.ShowWindow (SW_HIDE);
	m_dlgRotationQuaternion.ShowWindow (SW_SHOW);

	bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPPagePlacement::OnApply() 
{
	// First validate the rotation stuff, since it isn't taken care of by the DDX
	if (ValidateRotation ())
	{
		// Then rotation OK
	
		m_pPrimitive->GetPrimitivePlacement ()->SetPrimitivePlacementData (&m_strtPrimitivePlacementData);
		m_pPrimitive->GetPrimitiveScale ()->SetPrimitiveScaleAbsoluteData (&m_strtPrimitiveScaleData);
		
		CRBModelerRBMGraphicView::UpdatePrimitivePlacement (m_pPrimitive);
		CRBModelerRBMGraphicView::UpdatePrimitiveScale (m_pPrimitive);

		return CPropertyPage::OnApply();
	}
	else
	{
		return FALSE;
	}
}

void CPPagePlacement::OnChangeEditScaleX() 
{
	SetModified (TRUE);
}

void CPPagePlacement::OnChangeEditScaleY() 
{
	SetModified (TRUE);
}

void CPPagePlacement::OnChangeEditScaleZ() 
{
	SetModified (TRUE);
}

void CPPagePlacement::OnChangeEditTranslationX() 
{
	SetModified (TRUE);
}


void CPPagePlacement::OnChangeEditTranslationY() 
{
	SetModified (TRUE);
}

void CPPagePlacement::OnChangeEditTranslationZ() 
{
	SetModified (TRUE);
}

 

void CPPagePlacement::OnSelchangeTabRotation(NMHDR* pNMHDR,
											 LRESULT* pResult) 
{
	int nCurrentIndex = m_tabctrlRotation.GetCurSel ();
	ASSERT (nCurrentIndex > -1);

	// Set up the correct data based on the currently stored rotation
	CalculateRotationRepresentation ();

	switch (nCurrentIndex)
	{
	case ROT_TAB_QUATERNION: // Quaternion tab
		m_dlgRotationQuaternion.CalculateRotationQuaternion (m_strtPrimitivePlacementData.dRotationMatrix);
		m_dlgRotationAngleAxis.ShowWindow (SW_HIDE);
		m_dlgRotationEulerAngles.ShowWindow (SW_HIDE);
		m_dlgRotationQuaternion.ShowWindow (SW_SHOW);
		break;
	case ROT_TAB_EULER_ANGLES: // Euler Angles
		m_dlgRotationEulerAngles.CalculateEulerAngles (m_strtPrimitivePlacementData.dRotationMatrix);
		m_dlgRotationAngleAxis.ShowWindow (SW_HIDE);
		m_dlgRotationQuaternion.ShowWindow (SW_HIDE);
		m_dlgRotationEulerAngles.ShowWindow (SW_SHOW);
		break;
	case ROT_TAB_ANGLE_AXIS: // Angle Axis
		m_dlgRotationAngleAxis.CalculateAngleAxis (m_strtPrimitivePlacementData.dRotationMatrix);
		m_dlgRotationQuaternion.ShowWindow (SW_HIDE);
		m_dlgRotationEulerAngles.ShowWindow (SW_HIDE);
		m_dlgRotationAngleAxis.ShowWindow (SW_SHOW);
		break;
	default:
		ASSERT (FALSE);
	}

	*pResult = 0;
}

// Used to validate and save the data on the current tab
void CPPagePlacement::OnSelchangingTabRotation(NMHDR* pNMHDR, LRESULT* pResult) 
{
	BOOL bSuccess;

	bSuccess = ValidateRotation ();

	if (!bSuccess)
		*pResult = 1;
	else
		*pResult = 0;

}

BOOL CPPagePlacement::ValidateRotation()
{
	// If it has not been created, don't attempt to validate it
	if (m_tabctrlRotation.GetSafeHwnd ())
	{
		// Obtain the current rotation representation
		int nIndex = m_tabctrlRotation.GetCurSel ();
		ASSERT (nIndex > -1);

		BOOL bSuccess;
		switch (nIndex)
		{
		case ROT_TAB_QUATERNION:
			bSuccess = m_dlgRotationQuaternion.ValidateAndSaveQuaternion (
				m_strtPrimitivePlacementData.dRotationMatrix);
			break;
		case ROT_TAB_EULER_ANGLES:
			bSuccess = m_dlgRotationEulerAngles.ValidateAndSaveEulerAngles
				(m_strtPrimitivePlacementData.dRotationMatrix);
			break;
		case ROT_TAB_ANGLE_AXIS:
			bSuccess = m_dlgRotationAngleAxis.ValidateAndSaveAngleAxis 
				(m_strtPrimitivePlacementData.dRotationMatrix);
			break;
		default:
			ASSERT (FALSE);
		}

		return bSuccess;
	}
	else
		// Window hasn't been created, so nothing to validate
		return TRUE;
}


void CPPagePlacement::CalculateRotationRepresentation()
{
	int nIndex = m_tabctrlRotation.GetCurSel ();
	ASSERT (nIndex > -1);

	switch (nIndex)
	{
	case ROT_TAB_QUATERNION:
		m_dlgRotationQuaternion.CalculateRotationQuaternion 
			(m_strtPrimitivePlacementData.dRotationMatrix);
		break;
	case ROT_TAB_EULER_ANGLES:
		m_dlgRotationEulerAngles.CalculateEulerAngles 
			(m_strtPrimitivePlacementData.dRotationMatrix);
		break;
	case ROT_TAB_ANGLE_AXIS:
		m_dlgRotationAngleAxis.CalculateAngleAxis 
			(m_strtPrimitivePlacementData.dRotationMatrix);
		break;
	default:
		ASSERT (FALSE);
	}
}

BOOL CPPagePlacement::OnKillActive() 
{
	// Called by framework when page is loosing focus

	// Validate the rotation since DDX can't
	if (ValidateRotation ())
		return CPropertyPage::OnKillActive();
	else
		// Validation failed so don't permit the page change
		return FALSE;
}
