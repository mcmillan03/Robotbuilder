// dmvCFGData.cpp: implementation of the CdmvCFGData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "dmvCFGData.h"
#include "DMViewerDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvCFGData::CdmvCFGData()
{
	// Initialize members
	m_bRealTime = FALSE;
	m_dControlStepSize = .01;
	m_dEulerStepSize = .01;
	m_dRungeKutta45Epsilon = .000001;
	m_dRungeKutta45MinimumStepSize = .000001;
	m_dRungeKutta4StepSize = .00001;
	m_IntegratorType = INTEGRATOR_ADAPTIVE_4_5_RUNGE_KUTTA;
	m_nRate = 10;
	m_dInertialAxesLength = 1;
	m_nInertialAxesWidth = 2;
	m_nLinkAxesWidth = 1;
	m_dLinkAxesLength = .75;
	m_crBackgroundColor = INITIAL_WTK_BACKGROUND_COLOR;
	m_bInertialAxesAsCoi = TRUE;
	m_bUseInertialZ = TRUE;
	m_dCoiOffsetX = 0.0;
	m_dCoiOffsetY = 0.0;
	m_dCoiOffsetZ = 0.0;
	m_strCenterOfInterest.LoadString(IDS_STRING_INERTIAL_AXES);
	m_bDataChanged = FALSE;
	m_dViewAngleDeg = 9.0;
  //m_bLogoLoaded = 0;

	// Initialize the default user camera orientation
	WTp3 wtp3 = {0, 0, -1};
	WTq_construct (wtp3, 0.0f, m_wtqQuat);
	WTp3_copy(wtp3, m_wtp3Pos);
}

CdmvCFGData::~CdmvCFGData()
{

}

void CdmvCFGData::SetControlStepSize(double dControlStepSize)
{
	ASSERT (dControlStepSize >= MINIMUM_CONTROL_STEP_SIZE || dControlStepSize <= MAXIMUM_CONTROL_STEP_SIZE);

	if (m_dControlStepSize != dControlStepSize)
	{
		m_dControlStepSize = dControlStepSize;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetSimulationDisplayRate(int nRate)
{
	ASSERT (nRate >= MINIMUM_DISPLAY_RATE || nRate <= MAXIMUM_DISPLAY_RATE);

	if (m_nRate != nRate)
	{
		m_nRate = nRate;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetEnvironmentFile(CString strEnvironmentFile, CString strEnvironmentPath)
{
	if (m_strEnvironmentFile != strEnvironmentFile)
	{
		m_strEnvironmentFile = strEnvironmentFile;
		m_bDataChanged = TRUE;
	}
	if (m_strEnvironmentPath != strEnvironmentPath)
	{
		m_strEnvironmentPath = strEnvironmentPath;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetIntegratorType(INTEGRATOR_TYPE eIntegrator)
{
	if (m_IntegratorType != eIntegrator)
	{
		m_IntegratorType = eIntegrator;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetIntegratorEulerParameters(double dStepSize)
{
	ASSERT (dStepSize >= MINIMUM_EULER_STEP_SIZE && dStepSize <= MAXIMUM_EULER_STEP_SIZE);
	
	if (m_dEulerStepSize != dStepSize)
	{
		m_dEulerStepSize = dStepSize;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetIntegratorRungeKutta4Parameters(double dStepSize)
{
	ASSERT (dStepSize >= MINIMUM_RK4_STEP_SIZE && dStepSize <= MAXIMUM_RK4_STEP_SIZE);
	
	if (m_dRungeKutta4StepSize != dStepSize)
	{
		m_dRungeKutta4StepSize = dStepSize;
		m_bDataChanged = TRUE;
	}

}

void CdmvCFGData::SetIntegratorAdaptive45RungeKuttaParameters(double dEpsilon, 
															  double dMinimumStepSize)
{
	ASSERT (dEpsilon >= MINIMUM_RK45_EPSILON && dEpsilon <= MAXIMUM_RK45_EPSILON);
	ASSERT (dMinimumStepSize >= MINIMUM_RK45_MINIMUM_STEP_SIZE && dMinimumStepSize
		<= MAXIMUM_RK45_MINIMUM_STEP_SIZE);

	if (m_dRungeKutta45Epsilon != dEpsilon)
	{
		m_dRungeKutta45Epsilon = dEpsilon;
		m_bDataChanged = TRUE;
	}

	if (m_dRungeKutta45MinimumStepSize != dMinimumStepSize)
	{
		m_dRungeKutta45MinimumStepSize = dMinimumStepSize;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::ClearArticulationFileAndControlFileList()
{
	m_ArticulationAndControlFileArray.RemoveAll ();
}

void CdmvCFGData::AddArticulationFileAndControlFile(CString strArticulationFile,
													CString strArticulationPath, 
													CString strControlFile,
													CString strControlPath)
{
	structArticulationAndControlFilePair strEntry;
	strEntry.strArticulationFile = strArticulationFile;
	strEntry.strArticulationPath = strArticulationPath;
	strEntry.strControlDLL = strControlFile;
	strEntry.strControlPath = strControlPath;
	m_ArticulationAndControlFileArray.Add (strEntry);
}

void CdmvCFGData::SetRealTime(BOOL bDoRealTime)
{
	if (m_bRealTime != bDoRealTime)
	{
		m_bRealTime = bDoRealTime;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetCenterOfInterestName(CString strCenterOfInterestName)
{
	if (m_strCenterOfInterest != strCenterOfInterestName)
	{
		m_strCenterOfInterest = strCenterOfInterestName;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetCoiOffset(double dCoiOffsetX, double dCoiOffsetY, double dCoiOffsetZ)
{
	if (m_dCoiOffsetX != dCoiOffsetX)
	{
		m_dCoiOffsetX = dCoiOffsetX;
		m_bDataChanged = TRUE;
	}
	if (m_dCoiOffsetY != dCoiOffsetY)
	{
		m_dCoiOffsetY = dCoiOffsetY;
		m_bDataChanged = TRUE;
	}
	if (m_dCoiOffsetZ != dCoiOffsetZ)
	{
		m_dCoiOffsetZ = dCoiOffsetZ;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetInertialAxesAsCoi(BOOL bInertialAxesAsCoi)
{
	if (m_bInertialAxesAsCoi != bInertialAxesAsCoi)
	{
		m_bInertialAxesAsCoi = bInertialAxesAsCoi;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetUseInertialZ(BOOL bUseInertialZ)
{
	if (m_bUseInertialZ != bUseInertialZ)
	{
		m_bUseInertialZ = bUseInertialZ;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetViewAngle_Degree(double dViewAngleDeg)
{
	if (m_dViewAngleDeg != dViewAngleDeg)
	{
		m_dViewAngleDeg = dViewAngleDeg;
		m_bDataChanged = TRUE;
	}
}


// The next four functions are temporary hacks until I expand RB to support multiple
// articulation/controls
void CdmvCFGData::GetFirstControlFile(CString &rstrControlFile, CString &rstrControlPath) const
{
	ASSERT (m_ArticulationAndControlFileArray.GetSize () <= 1);

	if (m_ArticulationAndControlFileArray.GetSize () > 0)
	{
		rstrControlFile = m_ArticulationAndControlFileArray.GetAt (0).strControlDLL;
		rstrControlPath = m_ArticulationAndControlFileArray.GetAt (0).strControlPath;
	}
	else
	{
		rstrControlFile = "";
		rstrControlPath = "";
	}
}

void CdmvCFGData::SetFirstControlFile(CString strControlFile, CString strControlPath)
{
	ASSERT (m_ArticulationAndControlFileArray.GetSize () <= 1);
	
	// Get the articulation if there is one, delete the array, and add the new entry
	CString strCurrentArticulationFile, strCurrentArticulationPath;
	if (m_ArticulationAndControlFileArray.GetSize () > 0)
	{
		strCurrentArticulationFile =  m_ArticulationAndControlFileArray.GetAt (0).strArticulationFile;
		strCurrentArticulationPath =  m_ArticulationAndControlFileArray.GetAt (0).strArticulationPath;
	}
	else
	{
		strCurrentArticulationFile = "";
		strCurrentArticulationPath = "";
	}

	m_ArticulationAndControlFileArray.RemoveAll ();

	structArticulationAndControlFilePair strEntry;
	strEntry.strArticulationFile = strCurrentArticulationFile;
	strEntry.strArticulationPath = strCurrentArticulationPath;
	strEntry.strControlDLL = strControlFile;
	strEntry.strControlPath = strControlPath;
	m_ArticulationAndControlFileArray.Add (strEntry);
}

void CdmvCFGData::GetFirstArticulationFile(CString &rstrArticulationFile, CString &rstrArticulationPath) const
{
	ASSERT (m_ArticulationAndControlFileArray.GetSize () <= 1);

	if (m_ArticulationAndControlFileArray.GetSize () > 0)
	{
		rstrArticulationFile = m_ArticulationAndControlFileArray.GetAt (0).strArticulationFile;
		rstrArticulationPath = m_ArticulationAndControlFileArray.GetAt (0).strArticulationPath;
	}
	else
	{
		rstrArticulationFile = "";
		rstrArticulationPath = "";
	}
}

void CdmvCFGData::SetFirstArticulationFile(CString strArticulationFile, CString strArticulationPath)
{
	ASSERT (m_ArticulationAndControlFileArray.GetSize () <= 1);
	
	// Get the control if there is one, delete the array, and add the new entry
	CString strCurrentControlFile, strCurrentControlPath;
	if (m_ArticulationAndControlFileArray.GetSize () > 0)
	{
		strCurrentControlFile =  m_ArticulationAndControlFileArray.GetAt (0).strControlDLL;
		strCurrentControlPath =  m_ArticulationAndControlFileArray.GetAt (0).strControlPath;
	}
	else
	{
		strCurrentControlFile =  "";
		strCurrentControlPath =  "";
	}

	m_ArticulationAndControlFileArray.RemoveAll ();

	structArticulationAndControlFilePair strEntry;
	strEntry.strArticulationFile = strArticulationFile;
	strEntry.strArticulationPath = strArticulationPath;
	strEntry.strControlDLL = strCurrentControlFile;
	strEntry.strControlPath = strCurrentControlPath;
	m_ArticulationAndControlFileArray.Add (strEntry);
}

void CdmvCFGData::GetInertialAxesData (int &rnWidth, double &rdLength) const
{
	rnWidth = m_nInertialAxesWidth;
	rdLength = m_dInertialAxesLength;
}

void CdmvCFGData::GetLinkAxesData (int &rnWidth, double &rdLength) const
{
	rnWidth = m_nLinkAxesWidth;
	rdLength = m_dLinkAxesLength;
}

void CdmvCFGData::SetInertialAxesData(int nWidth, double dLength)
{
	if (m_nInertialAxesWidth != nWidth)
	{
		m_nInertialAxesWidth = nWidth;
		m_bDataChanged = TRUE;
	}

	if (m_dInertialAxesLength != dLength)
	{
		m_dInertialAxesLength = dLength;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetLinkAxesData(int nWidth, double dLength)
{
	if (m_nLinkAxesWidth != nWidth)
	{
		m_nLinkAxesWidth = nWidth;
		m_bDataChanged = TRUE;
	}

	if (m_dLinkAxesLength != dLength)
	{
		m_dLinkAxesLength = dLength;
		m_bDataChanged = TRUE;
	}
}

COLORREF CdmvCFGData::GetBackgroundColor() const
{
	return m_crBackgroundColor;
}

void CdmvCFGData::SetBackgroundColor(COLORREF crBackgroundColor)
{
	if (m_crBackgroundColor != crBackgroundColor)
	{
		m_crBackgroundColor = crBackgroundColor;
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetOrientationQuaternion(WTq wtqQuat)
{
	if (!WTq_equal(wtqQuat, m_wtqQuat))
	{
		WTq_copy(wtqQuat, m_wtqQuat);
		m_bDataChanged = TRUE;
	}
}

void CdmvCFGData::SetOrientationPosition(WTp3 wtp3Pos)
{
	if (!WTp3_equal(wtp3Pos, m_wtp3Pos))
	{
		WTp3_copy(wtp3Pos, m_wtp3Pos);
		m_bDataChanged = TRUE;
	}
}

BOOL CdmvCFGData::DataHasChanged()
{
	return m_bDataChanged;
}

void CdmvCFGData::ResetDataChanged()
{
	m_bDataChanged = FALSE;
}

void CdmvCFGData::GetOrientation(WTq wtq) const
{
	WTq_copy (m_wtqQuat, wtq);
}

void CdmvCFGData::GetPosition(WTp3 wtp3) const
{
	WTp3_copy (m_wtp3Pos, wtp3);
}

/*int CdmvCFGData::GetLogoLoadFlag ()
{
	return m_bLogoLoaded;
}
void CdmvCFGData::SetLogoLoadFlag ()
{
	m_bLogoLoaded = 1;
}*/

