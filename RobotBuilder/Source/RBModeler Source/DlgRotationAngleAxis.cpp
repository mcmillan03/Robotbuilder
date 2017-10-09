// DlgRotationAngleAxis.cpp : implementation file
//

#include "stdafx.h"
#include "RBModeler.h"
#include "DlgRotationAngleAxis.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRotationAngleAxis dialog

#define PI 3.141592653589793238462

CDlgRotationAngleAxis::CDlgRotationAngleAxis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRotationAngleAxis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRotationAngleAxis)
	m_dAngle = 0.0;
	m_dAxisX = 0.0;
	m_dAxisY = 0.0;
	m_dAxisZ = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgRotationAngleAxis::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fAngle = (float) m_dAngle;
	float fAxisX = (float) m_dAxisX;
	float fAxisY = (float) m_dAxisY;
	float fAxisZ = (float) m_dAxisZ;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRotationAngleAxis)
	DDX_Text(pDX, IDC_EDIT_ANGLE, fAngle);
	DDX_Text(pDX, IDC_EDIT_AXIS_X, fAxisX);
	DDX_Text(pDX, IDC_EDIT_AXIS_Y, fAxisY);
	DDX_Text(pDX, IDC_EDIT_AXIS_Z, fAxisZ);
	//}}AFX_DATA_MAP

	m_dAngle = fAngle;
	m_dAxisX = fAxisX;
	m_dAxisY = fAxisY;
	m_dAxisZ = fAxisZ;
}


BEGIN_MESSAGE_MAP(CDlgRotationAngleAxis, CDialog)
	//{{AFX_MSG_MAP(CDlgRotationAngleAxis)
	ON_EN_CHANGE(IDC_EDIT_AXIS_X, OnChangeEditAxisX)
	ON_EN_CHANGE(IDC_EDIT_AXIS_Y, OnChangeEditAxisY)
	ON_EN_CHANGE(IDC_EDIT_AXIS_Z, OnChangeEditAxisZ)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRotationAngleAxis message handlers

void CDlgRotationAngleAxis::OnChangeEditAxisX() 
{
	dynamic_cast <CPropertyPage*> (GetParent ())->SetModified ();
}

void CDlgRotationAngleAxis::OnChangeEditAxisY() 
{
	dynamic_cast <CPropertyPage*> (GetParent ())->SetModified ();
}

void CDlgRotationAngleAxis::OnChangeEditAxisZ() 
{
	dynamic_cast <CPropertyPage*> (GetParent ())->SetModified ();
}

void CDlgRotationAngleAxis::CalculateAngleAxis(double dRotation[][3])
{

	// Note this is the transpose of Craig pg 52
	m_dAngle = acos ((dRotation[0][0] + dRotation[1][1] + dRotation[2][2] - 1) / 2);

	double dDenom = 2 * sin (m_dAngle);

	// Check that the denomiator is not 0, if so the axis is undefined
	if (dDenom == 0)
	{
		m_dAxisX = m_dAxisY = m_dAxisZ = 0;
	}
	else
	{
		m_dAxisX = (dRotation[1][2] - dRotation[2][1]) / dDenom;
		m_dAxisY = (dRotation[2][0] - dRotation[0][2]) / dDenom;
		m_dAxisZ = (dRotation[0][1] - dRotation[1][0]) / dDenom;
	}

	// Change to degress
	m_dAngle *= (180/PI);

	BOOL bSuccess;
	bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);	
}

BOOL CDlgRotationAngleAxis::ValidateAndSaveAngleAxis(double dRotation[][3])
{
	BOOL bSuccess;
	bSuccess = UpdateData (TRUE);

	// If validation failed, don't do anything and return FALSE
	if (bSuccess)
	{
		double dSinAngle = sin (m_dAngle*PI/180);
		double dCosAngle = cos (m_dAngle*PI/180);
		double dVAngle = 1 - dCosAngle;
		
		double dMag = sqrt(m_dAxisX * m_dAxisX + m_dAxisY * m_dAxisY + m_dAxisZ * m_dAxisZ);
		// Make sure no divide by zero
		if (dMag == 0)
			dMag = 1;
		double dUnitX = m_dAxisX / dMag;
		double dUnitY = m_dAxisY / dMag;
		double dUnitZ = m_dAxisZ / dMag;


		// Note this is the transpose of Craig pg 52
		dRotation[0][0] = dUnitX * dUnitX * dVAngle + dCosAngle;
		dRotation[1][0] = dUnitX * dUnitY * dVAngle - dUnitZ * dSinAngle;
		dRotation[2][0] = dUnitX * dUnitZ * dVAngle + dUnitY * dSinAngle;

		dRotation[0][1] = dUnitX * dUnitY * dVAngle + dUnitZ * dSinAngle;
		dRotation[1][1] = dUnitY * dUnitY * dVAngle + dCosAngle;
		dRotation[2][1] = dUnitY * dUnitZ * dVAngle - dUnitX * dSinAngle;

		dRotation[0][2] = dUnitX * dUnitZ * dVAngle - dUnitY * dSinAngle;
		dRotation[1][2] = dUnitY * dUnitZ * dVAngle + dUnitX * dSinAngle;
		dRotation[2][2] = dUnitZ * dUnitZ * dVAngle + dCosAngle;


		return TRUE;
	}
	else
	{
		// Validation failed
		return FALSE;
	}
}

void CDlgRotationAngleAxis::OnCancel ()
{
	// Implement to make sure the dialog is never cancelled
}

void CDlgRotationAngleAxis::OnOK ()
{
	// Implement to make sure the dialog is never OKed and always stays there
}
