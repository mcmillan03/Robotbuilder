// DlgRotationEulerAngles.cpp : implementation file
//

#include "stdafx.h"
#include "RBModeler.h"
#include "DlgRotationEulerAngles.h"
#include "wt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRotationEulerAngles dialog


CDlgRotationEulerAngles::CDlgRotationEulerAngles(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRotationEulerAngles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRotationEulerAngles)
	m_dEulerX = 0.0;
	m_dEulerY = 0.0;
	m_dEulerZ = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgRotationEulerAngles::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fEulerX = (float) m_dEulerX;
	float fEulerY = (float) m_dEulerY;
	float fEulerZ = (float) m_dEulerZ;
	
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRotationEulerAngles)
	DDX_Text(pDX, IDC_EDIT_EULER_X, fEulerX);
	DDX_Text(pDX, IDC_EDIT_EULER_Y, fEulerY);
	DDX_Text(pDX, IDC_EDIT_EULER_Z, fEulerZ);
	//}}AFX_DATA_MAP

	m_dEulerX = fEulerX;
	m_dEulerY = fEulerY;
	m_dEulerZ = fEulerZ;
}


BEGIN_MESSAGE_MAP(CDlgRotationEulerAngles, CDialog)
	//{{AFX_MSG_MAP(CDlgRotationEulerAngles)
	ON_EN_CHANGE(IDC_EDIT_EULER_X, OnChangeEditEulerX)
	ON_EN_CHANGE(IDC_EDIT_EULER_Y, OnChangeEditEulerY)
	ON_EN_CHANGE(IDC_EDIT_EULER_Z, OnChangeEditEulerZ)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRotationEulerAngles message handlers

BOOL CDlgRotationEulerAngles::ValidateAndSaveEulerAngles(double dRotation[][3])
{
	BOOL bSuccess;
	bSuccess = UpdateData (TRUE);

	// If validation failed, don't do anything and return FALSE
	if (bSuccess)
	{
		// Convert it to a 3by3
		WTm3 wtm3Rotation;
		WTeuler_2m3 (m_dEulerX*PI/180, m_dEulerY*PI/180, m_dEulerZ*PI/180, wtm3Rotation);

		// Return the new rotation matrix
		int i,j;
		for (i=0;i<3;i++)
			for (j=0;j<3;j++)
				dRotation[i][j] = wtm3Rotation[i][j];

		return TRUE;
	}
	else
	{
		// Validation failed
		return FALSE;
	}
}

void CDlgRotationEulerAngles::CalculateEulerAngles(double dRotation[][3])
{
	// Build a WTm3 to use
	WTm3 wtm3Rotation;
	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			wtm3Rotation[i][j] = dRotation[i][j];
	WTp3 wtp3Euler1,wtp3Euler2;

	// WTK returns two possible values for Euler angles, one with y in +/- PI/2 and the
	// other with y in PI/2 to PI
	WTm3_2euler (wtm3Rotation, wtp3Euler1, wtp3Euler2);

	// Arbitrarly choose the first
	m_dEulerX = wtp3Euler1[X]*180/PI;
	m_dEulerY = wtp3Euler1[Y]*180/PI;
	m_dEulerZ = wtp3Euler1[Z]*180/PI;

	// Show the new data
	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
}

void CDlgRotationEulerAngles::OnChangeEditEulerX() 
{
	dynamic_cast <CPropertyPage*> (GetParent ())->SetModified ();
}

void CDlgRotationEulerAngles::OnChangeEditEulerY() 
{
	dynamic_cast <CPropertyPage*> (GetParent ())->SetModified ();
}

void CDlgRotationEulerAngles::OnChangeEditEulerZ() 
{
	dynamic_cast <CPropertyPage*> (GetParent ())->SetModified ();
}

void CDlgRotationEulerAngles::OnCancel ()
{
	// Implement to make sure the dialog is never cancelled
}

void CDlgRotationEulerAngles::OnOK ()
{
	// Implement to make sure the dialog is never OKed and always stays there
}
