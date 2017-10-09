// GenerateCFGFile.cpp: implementation of the CGenerateCFGFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "GenerateCFGFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGenerateCFGFile::CGenerateCFGFile()
{

}

CGenerateCFGFile::~CGenerateCFGFile()
{

}

BOOL CGenerateCFGFile::CreateCFGFile(CString strFilePath,  
									 const CdmvCFGData* pCdmvCFGData)
{
	ofstream strmCFG;
	strmCFG.open (strFilePath);
	int nIsOpen = strmCFG.is_open ();
	if (!nIsOpen)
		return FALSE;
 	ASSERT (strmCFG != NULL);

	OutputFileHeader (strmCFG);

	strmCFG << "Version 3" << endl;

	strmCFG << "Control_Step_Size" << "\t\t" << 
			pCdmvCFGData->GetControlStepSize () << endl;
	strmCFG << "Simulation_Display_Rate" << "\t\t" << 
			pCdmvCFGData->GetSimulationDisplayRate () << endl;
	string strRealTime;
	if (pCdmvCFGData->GetRealTime ())
		strRealTime = "TRUE";
	else
		strRealTime= "FALSE";
	strmCFG << "Real-time" << "\t\t" << 
			strRealTime << endl;

	// Output axes information
	int nWidth; double dLength;
	pCdmvCFGData->GetInertialAxesData (nWidth, dLength);
	strmCFG << "Inertial_Axes" << "\t\t" << 
			dLength << '\t' << nWidth << endl;
	pCdmvCFGData->GetLinkAxesData (nWidth, dLength);
	strmCFG << "Link_Axes" << "\t\t" << 
			dLength << '\t' << nWidth << endl;

	// Output the background color
	COLORREF crBackgroundColor = pCdmvCFGData->GetBackgroundColor ();
	strmCFG << "Background_Color\t\t" << (int) (GetRValue (crBackgroundColor)) << '\t'
		<< (int) (GetGValue (crBackgroundColor)) << '\t' << (int) (GetBValue (crBackgroundColor)) << endl;

	strmCFG << endl;

	// Integrator information
	double dStepSize, dEpsilon, dMinimumStepSize;
	switch (pCdmvCFGData->GetIntegratorType ())
	{
	case INTEGRATOR_EULER:
		// Pick up the parameters
		dStepSize = pCdmvCFGData->GetIntegratorEulerParameters ();
		strmCFG << "Integrator		EULER" << endl;
		strmCFG << "Integrator_Parameter_Step_Size\t" << dStepSize << endl;
		break;
	case INTEGRATOR_RUNGE_KUTTA_4:
		// Pick up the paramters
		dStepSize = pCdmvCFGData->GetIntegratorRungeKutta4Parameters ();
		strmCFG << "Integrator		RUNGE-KUTTA4" << endl;
		strmCFG << "Integrator_Parameter_Step_Size\t" << dStepSize << endl;
		break;
	case INTEGRATOR_ADAPTIVE_4_5_RUNGE_KUTTA:
		pCdmvCFGData->GetIntegratorAdaptive45RungeKuttaParameters (&dEpsilon,
			&dMinimumStepSize);
		strmCFG << "Integrator		ADAPTIVE_4_5_RUNGE-KUTTA" << endl;
		strmCFG << "Integrator_Parameter_Epsilon\t" << dEpsilon << endl;
		strmCFG << "Integrator_Parameter_Minimum_Step_Size\t" << dMinimumStepSize << endl;
		break;
	case INTEGRATOR_PLACEMENT:
		strmCFG << "Integrator		PLACEMENT" << endl;
		break;
	default:
		// Unexpected case
		ASSERT (0);
	}
	strmCFG << endl;

	// Output the Camera Checkbox Information
	string strCamera;
	if (pCdmvCFGData->GetInertialAxesAsCoi())
		strCamera = _T("TRUE");
	else
		strCamera = _T("FALSE");
	strmCFG << "Inertial_Axes_As_COI" << "\t\t" << 
		strCamera << endl;

	if (pCdmvCFGData->GetUseInertialZ())
		strCamera = _T("TRUE");
	else
		strCamera = _T("FALSE");
	strmCFG << "Stabilize_Vertical_Camera_Position" << "\t\t" <<
		strCamera << endl;

	// Output the center of interest name and offset
	strmCFG << "COI_Name" << "\t\t" << "\"" <<
		(LPCTSTR) pCdmvCFGData->GetCenterOfInterestName() <<
		"\"" << endl;

	double dOffsetX, dOffsetY, dOffsetZ;
	pCdmvCFGData->GetCoiOffset(&dOffsetX, &dOffsetY, &dOffsetZ);
	strmCFG << "COI_Offset" << "\t\t" <<
		dOffsetX << "\t" << dOffsetY << "\t" << dOffsetZ << endl;
	
	// Output the camera orientation and position
	WTq wtq;
	WTp3 wtp3;

	pCdmvCFGData->GetOrientation(wtq);
	pCdmvCFGData->GetPosition(wtp3);

	strmCFG << "Camera_Orientation" << "\t\t" <<
		wtq[0] << "\t" << wtq[1] << "\t" << 
		wtq[2] << "\t" << wtq[3] << endl;

	strmCFG << "Camera_Position" << "\t\t" << 
		wtp3[0] << "\t" << wtp3[1] << "\t" <<
		wtp3[2] << "\t" << endl << endl;

  // Output the view angle degree
	double dViewAngleDeg;
	pCdmvCFGData->GetViewAngle_Degree (&dViewAngleDeg);

	strmCFG << "View_Angle_Degrees" << "\t" << 
		dViewAngleDeg << "\t" << endl << endl;

	// Pick up the path and file, but just store the file so the files are
	// portable
	CString strFile, strPath;
	pCdmvCFGData->GetEnvironmentFile (strFile, strPath);
	strmCFG << "Environment_Parameter_File" << "\t" << 
		"\"" << LPCTSTR (strFile) << "\"" << endl;

	pCdmvCFGData->GetFirstControlFile (strFile, strPath);
	strmCFG << "Control_Dll_File" << "\t\t" << 
		"\"" << LPCTSTR (strFile) << "\"" << endl;

	pCdmvCFGData->GetFirstArticulationFile (strFile, strPath);
	strmCFG << "Articulation_File" << "\t\t" << 
		"\"" << LPCTSTR (strFile) << "\"" << endl;
	
	strmCFG.close ();

	return TRUE;
}

void CGenerateCFGFile::OutputFileHeader(ostream &strmCFG)
{
	strmCFG << "# simulation configuration file" << endl << endl;
}
