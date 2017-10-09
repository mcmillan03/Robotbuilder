// DlgRotationQuaternion.cpp : implementation file
//

#include "stdafx.h"
#include "RBModeler.h"
#include "DlgRotationQuaternion.h"
#include "wt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRotationQuaternion dialog


CDlgRotationQuaternion::CDlgRotationQuaternion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRotationQuaternion::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRotationQuaternion)
	m_dQuaternion1 = 0.0;
	m_dQuaternion2 = 0.0;
	m_dQuaternion3 = 0.0;
	m_dQuaternion4 = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgRotationQuaternion::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fQuaternion1 = (float) m_dQuaternion1;
	float fQuaternion2 = (float) m_dQuaternion2;
	float fQuaternion3 = (float) m_dQuaternion3;
	float fQuaternion4 = (float) m_dQuaternion4;

	
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRotationQuaternion)
	DDX_Text(pDX, IDC_EDIT_QUATERNION_1, fQuaternion1);
	DDV_MinMaxFloat(pDX, fQuaternion1, -1., 1.);
	DDX_Text(pDX, IDC_EDIT_QUATERNION_2, fQuaternion2);
	DDV_MinMaxFloat(pDX, fQuaternion2, -1., 1.);
	DDX_Text(pDX, IDC_EDIT_QUATERNION_3, fQuaternion3);
	DDV_MinMaxFloat(pDX, fQuaternion3, -1., 1.);
	DDX_Text(pDX, IDC_EDIT_QUATERNION_4, fQuaternion4);
	DDV_MinMaxFloat(pDX, fQuaternion4, -1., 1.);
	//}}AFX_DATA_MAP

	m_dQuaternion1 = fQuaternion1;
	m_dQuaternion2 = fQuaternion2;
	m_dQuaternion3 = fQuaternion3;
	m_dQuaternion4 = fQuaternion4;
}


BEGIN_MESSAGE_MAP(CDlgRotationQuaternion, CDialog)
	//{{AFX_MSG_MAP(CDlgRotationQuaternion)
	ON_EN_CHANGE(IDC_EDIT_QUATERNION_1, OnChangeEditQuaternion1)
	ON_EN_CHANGE(IDC_EDIT_QUATERNION_2, OnChangeEditQuaternion2)
	ON_EN_CHANGE(IDC_EDIT_QUATERNION_3, OnChangeEditQuaternion3)
	ON_EN_CHANGE(IDC_EDIT_QUATERNION_4, OnChangeEditQuaternion4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRotationQuaternion message handlers

void CDlgRotationQuaternion::CalculateRotationQuaternion(double arRotation[3][3] )
{
	// Build up a WTK WTm3 for the calculation
	WTm3 wtm3Rotation;
	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			wtm3Rotation[i][j] = arRotation[i][j];
	WTq wtqRotation;
	WTm3_2q (wtm3Rotation, wtqRotation);

	// Place the in the edit boxes
	m_dQuaternion1 = wtqRotation[X];
	m_dQuaternion2 = wtqRotation[Y];
	m_dQuaternion3 = wtqRotation[Z];
	m_dQuaternion4 = wtqRotation[W];

	// Update the display
	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
}

BOOL CDlgRotationQuaternion::ValidateAndSaveQuaternion(double dRotation[3][3])
{
	BOOL bSuccess = UpdateData (TRUE);

	// If OK, save the data
	if (bSuccess)
	{
		// Make a WTq and convert it
		WTq wtqRotation;
		wtqRotation[X] = m_dQuaternion1;
		wtqRotation[Y] = m_dQuaternion2;
		wtqRotation[Z] = m_dQuaternion3;
		wtqRotation[W] = m_dQuaternion4;

		WTm3 wtm3Rotation;
		WTq_2m3 (wtqRotation, wtm3Rotation);

		// Return the new rotation
		int i,j;
		for (i=0;i<3;i++)
			for (j=0;j<3;j++)
				dRotation[i][j] = wtm3Rotation[i][j];

		return TRUE;
	}
	else
		return FALSE;
}

void CDlgRotationQuaternion::OnChangeEditQuaternion1() 
{
	dynamic_cast <CPropertyPage*> (GetParent ())->SetModified ();
}

void CDlgRotationQuaternion::OnChangeEditQuaternion2() 
{
	dynamic_cast <CPropertyPage*> (GetParent ())->SetModified ();
}

void CDlgRotationQuaternion::OnChangeEditQuaternion3() 
{
	dynamic_cast <CPropertyPage*> (GetParent ())->SetModified ();
}

void CDlgRotationQuaternion::OnChangeEditQuaternion4() 
{
	dynamic_cast <CPropertyPage*> (GetParent ())->SetModified ();
}

void CDlgRotationQuaternion::OnCancel ()
{
	// Implement to make sure the dialog is never cancelled
}

void CDlgRotationQuaternion::OnOK ()
{
	// Implement to make sure the dialog is never OKed and always stays there
}
