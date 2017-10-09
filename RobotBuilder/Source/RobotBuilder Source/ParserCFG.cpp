// ParserCFG.cpp: implementation of the CParserCFG class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "ParserCFG.h"
#include "FindFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserCFG::CParserCFG()
{

}

CParserCFG::~CParserCFG()
{

}

BOOL CParserCFG::ParseCFGFile(CString strFile, CdmvCFGData *pCdmvCFGData)
{
	// Line Number
	int nCurrentLineNumber = 1;

	// Open the file
	ifstream istrmCFGFile (strFile);
	if (!istrmCFGFile) 
	{
		AfxMessageBox ("Failed to open CFG file.");
		return FALSE;
	}

	// Advance to the first token in case it starts as blanks.
	if (!GotoNextData (istrmCFGFile, nCurrentLineNumber))
	{
		FormatError(istrmCFGFile, nCurrentLineNumber,
			"Error before Version field.");
		return FALSE;
	}

	// The first real line will be the format type
	// The label is there just for clarity and will not actually be parsed
	string strLabel;
	int nFormatVersion = 1; // Holds format version of file
	istrmCFGFile >> strLabel >> nFormatVersion;

	if (!istrmCFGFile.good () || strLabel != "Version")
	{
		ParseError (istrmCFGFile, nCurrentLineNumber,
			"Expected: Version <integer>");
		return FALSE;
	}
	if (!GotoNextData (istrmCFGFile, nCurrentLineNumber))
	{
		FormatError (istrmCFGFile, nCurrentLineNumber,
			"Error after Version field.");
		return FALSE;			
	}
	
	// Call the correct procedure to parse the detected version type.
	switch (nFormatVersion)
	{
	case 1:
		if (!ParseFileVersion1 (istrmCFGFile, nCurrentLineNumber, pCdmvCFGData))
		{
			return FALSE;
		}
		break;
	case 2:
		if (!ParseFileVersion2 (istrmCFGFile, nCurrentLineNumber, pCdmvCFGData))
		{
			return FALSE;
		}
		break;
	case 3:
		if (!ParseFileVersion3 (istrmCFGFile, nCurrentLineNumber, pCdmvCFGData))
		{
			return FALSE;
		}
		break;
	default:
		AfxMessageBox ("Unsupported version of CFG file.");
		return FALSE;
	}

	// Close the stream
	istrmCFGFile.close ();

	return TRUE;
}

void CParserCFG::ParseError(ifstream &istrmCFGFile, int nCurrentLineNumber,
							CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Parse error in CFG file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmCFGFile.close ();
}

void CParserCFG::FormatError(ifstream &istrmCFGFile, int nCurrentLineNumber,
							 CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Format error in CFG file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmCFGFile.close ();
}

BOOL CParserCFG::ParseFileVersion1(ifstream &istrmCFGFile, int & rnCurrentLineNumber, 
								   CdmvCFGData *pCdmvCFGData)
{
	string strLabel; // Holder for the data labels

	// Read the control step size
	double dControlStepSize;
	istrmCFGFile >> strLabel >> dControlStepSize;
	if (!istrmCFGFile.good () || strLabel != "Control_Step_Size")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Control_Step_Size <floating_point>");
		return FALSE;
	}
	// Validate the data
	if (dControlStepSize < MINIMUM_CONTROL_STEP_SIZE || dControlStepSize > MAXIMUM_CONTROL_STEP_SIZE)
	{
		CString strError;
		strError.Format ("%f <= Control_Step_Size <= %f", MINIMUM_CONTROL_STEP_SIZE, MAXIMUM_CONTROL_STEP_SIZE);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetControlStepSize (dControlStepSize);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Control_Step_Size field.");
		return FALSE;			
	}

	// Read the simulation display rate
	int nSimulationDisplayRate;
	istrmCFGFile >> strLabel >> nSimulationDisplayRate;
	if (!istrmCFGFile.good () || strLabel != "Simulation_Display_Rate")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Simulation_Display_Rate <integer>");
		return FALSE;
	}
	// Validate the data
	if (nSimulationDisplayRate < MINIMUM_DISPLAY_RATE || nSimulationDisplayRate > MAXIMUM_DISPLAY_RATE)
	{
		CString strError;
		strError.Format ("%d <= Simulation_Display_Rate <= %d",
			MINIMUM_DISPLAY_RATE, MAXIMUM_DISPLAY_RATE);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetSimulationDisplayRate (nSimulationDisplayRate);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Simulation_Display_Rate field.");
		return FALSE;			
	}

	// Read the Real-time setting
	string strRealTime;
	istrmCFGFile >> strLabel >> strRealTime;
	if (!istrmCFGFile.good () || strLabel != "Real-time")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Real-time <string>");
		return FALSE;
	}
	// Save the data
	if (strRealTime == "TRUE")
		pCdmvCFGData->SetRealTime (TRUE);
	else if (strRealTime == "FALSE")
		pCdmvCFGData->SetRealTime (FALSE);
	else
	{
		// Validation error
		ValidationError (istrmCFGFile, rnCurrentLineNumber,
			"Real-time <string> (where string is in {TRUE, FALSE})");
		return FALSE;
	}
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Real-time field");
		return FALSE;			
	}

	// Inertial Axes
	double dAxesLength;
	int nAxesWidth;
	istrmCFGFile >> strLabel >> dAxesLength >> nAxesWidth;
	if (!istrmCFGFile.good () || strLabel != "Inertial_Axes")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Inertial_Axes <floating_point> <int>");
		return FALSE;
	}
	// Validate the data
	if (dAxesLength < MINIMUM_AXES_LENGTH || dAxesLength > MAXIMUM_AXES_LENGTH)
	{
		CString strError;
		strError.Format ("%f <= Inertial_Axes_Length <= %f", MINIMUM_AXES_LENGTH, MAXIMUM_AXES_LENGTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Validate the data
	if (nAxesWidth < MINIMUM_AXES_WIDTH || nAxesWidth > MAXIMUM_AXES_WIDTH)
	{
		CString strError;
		strError.Format ("%d <= Inertial_Axes_Width <= %d", MINIMUM_AXES_WIDTH, MAXIMUM_AXES_WIDTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetInertialAxesData (nAxesWidth, dAxesLength);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Inertial_Axes field.");
		return FALSE;			
	}
	
	// Link Axes
	istrmCFGFile >> strLabel >> dAxesLength >> nAxesWidth;
	if (!istrmCFGFile.good () || strLabel != "Link_Axes")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Link_Axes <floating_point> <int>");
		return FALSE;
	}
	// Validate the data
	if (dAxesLength < MINIMUM_AXES_LENGTH || dAxesLength > MAXIMUM_AXES_LENGTH)
	{
		CString strError;
		strError.Format ("%f <= Link_Axes_Length <= %f", MINIMUM_AXES_LENGTH, MAXIMUM_AXES_LENGTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Validate the data
	if (nAxesWidth < MINIMUM_AXES_WIDTH || nAxesWidth > MAXIMUM_AXES_WIDTH)
	{
		CString strError;
		strError.Format ("%d <= Link_Axes_Width <= %d", MINIMUM_AXES_WIDTH, MAXIMUM_AXES_WIDTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetLinkAxesData (nAxesWidth, dAxesLength);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Link_Axes field.");
		return FALSE;			
	}
	
	// Background color
	unsigned short sColor[3];
	istrmCFGFile >> strLabel >> sColor[0] >> sColor[1] >> sColor[2];
	if (!istrmCFGFile.good () || strLabel != "Background_Color")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Background_Color <byte> <byte> <byte>");
		return FALSE;
	}
	// Validate the data
	if (sColor[0] < 0 || sColor[0] > 255 ||
		sColor[1] < 0 || sColor[1] > 255 ||
		sColor[2] < 0 || sColor[2] > 255)
	{
		CString strError;
		strError = "0 <= Color_element <= 255";
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	COLORREF crColor = RGB (sColor[0], sColor[1], sColor[2]);
	pCdmvCFGData->SetBackgroundColor (crColor);	
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Background_Color field.");
		return FALSE;			
	}

	// Read the integrator type
	string strIntegrator;
	istrmCFGFile >> strLabel >> strIntegrator;
	if (!istrmCFGFile.good () || strLabel != "Integrator")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Integrator <string>");
		return FALSE;
	}
	// Set the integrator type
	if (strIntegrator == "EULER")
	{
		// EULER integrator
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_EULER);
		// Read the euler parameters on the next line
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
		double dStepSize;
		istrmCFGFile >> strLabel >> dStepSize;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Step_Size")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Step_Size <floating_point>");
			return FALSE;
		}
		// Validate the data
		if (dStepSize < MINIMUM_EULER_STEP_SIZE || dStepSize > MAXIMUM_EULER_STEP_SIZE)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Step_Size <= %f",
				MINIMUM_EULER_STEP_SIZE, MAXIMUM_EULER_STEP_SIZE);
			ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
			return FALSE;		
		}
		pCdmvCFGData->SetIntegratorEulerParameters (dStepSize);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Step_Size field.");
			return FALSE;			
		}
	}
	else if(strIntegrator == "RUNGE-KUTTA4")
	{
		// Fourth order Runge-Kutta
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_RUNGE_KUTTA_4);
		// Read the integrator parameters on the next line
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
		double dStepSize;
		istrmCFGFile >> strLabel >> dStepSize;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Step_Size")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Step_Size <floating_point>");
			return FALSE;
		}
		// Validate the data
		if (dStepSize < MINIMUM_RK4_STEP_SIZE || dStepSize > MAXIMUM_RK4_STEP_SIZE)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Step_Size <= %f", MINIMUM_RK4_STEP_SIZE,
				MAXIMUM_RK4_STEP_SIZE);
			ValidationError (istrmCFGFile, rnCurrentLineNumber,
				strError);
			return FALSE;		
		}
		pCdmvCFGData->SetIntegratorRungeKutta4Parameters (dStepSize);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Step_Size field.");
			return FALSE;			
		}
	}
	else if(strIntegrator == "ADAPTIVE_4_5_RUNGE-KUTTA")
	{
		// Adaptive step size 4th-5th order Runge-Kutta
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_ADAPTIVE_4_5_RUNGE_KUTTA);
		// Read the integrator parameters on the next line
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
		// Read epsilon
		double dEpsilon;
		istrmCFGFile >> strLabel >> dEpsilon;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Epsilon")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Epsilon <floating_point>");
			return FALSE;
		}
		// Validate the data
		if (dEpsilon < MINIMUM_RK45_EPSILON || dEpsilon > MAXIMUM_RK45_EPSILON)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Epsilon <= %f",
				MINIMUM_RK45_EPSILON, MAXIMUM_RK45_EPSILON);
			ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
			return FALSE;		
		}
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Epsilon field.");
			return FALSE;			
		}
		// Read minimum step size
		double dMinimumStepSize;
		istrmCFGFile >> strLabel >> dMinimumStepSize;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Minimum_Step_Size")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Minimum_Step_Size <floating_point>");
			return FALSE;
		}
		if (dMinimumStepSize < MINIMUM_RK45_MINIMUM_STEP_SIZE || dMinimumStepSize > MAXIMUM_RK45_MINIMUM_STEP_SIZE)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Minimum_Step_Size <= %f",
				MINIMUM_RK45_MINIMUM_STEP_SIZE, MAXIMUM_RK45_MINIMUM_STEP_SIZE);
			ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
			return FALSE;		
		}
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Minimum_Step_Size field.");
			return FALSE;			
		}
		// Save the data
		pCdmvCFGData->SetIntegratorAdaptive45RungeKuttaParameters (dEpsilon, dMinimumStepSize);
	}
	else if (strIntegrator == "PLACEMENT")
	{
		// Placement Integrator
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_PLACEMENT);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
	}
	else
	{
		// Unknown integrator
		CString strError;
		strError.Format (
			"Integrator <string> (where string is in {EULER, RUNGE-KUTTA4, ADAPTIVE_4_5_RUNGE-KUTTA, PLACEMENT}");
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;
	}

	// Read the environment file
	string stringEnvironmentFile;
	istrmCFGFile >> strLabel;
	if (!ReadStringInDoubleQuotes (istrmCFGFile, stringEnvironmentFile))
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Environment_Parameter_File \"<string>\"");
		return FALSE;
	}
	if (!istrmCFGFile.good () || strLabel != "Environment_Parameter_File")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Environment_Parameter_File \"<string>\"");
		return FALSE;
	}
	// Check to see if the files can be found
	CString strEnvironmentPath = "";
	CString strEnvironmentFile = stringEnvironmentFile.c_str ();
	if (!strEnvironmentFile.IsEmpty ())
	{
		BOOL bFindFile = CFindFile::FindFile (ENVIRONMENT_FILE_TYPE, 
			strEnvironmentFile, strEnvironmentPath);
		// If the file is not found, the user will get a message when it
		// is attempted to be opened
	}

	// Save the data
	pCdmvCFGData->SetEnvironmentFile (strEnvironmentFile, strEnvironmentPath);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Environment_Parameter_File field");
		return FALSE;			
	}


	// The rest of the data is a list of control and .dm files in the simulation
	// First clear the current list of control and articulation files
	pCdmvCFGData->ClearArticulationFileAndControlFileList ();
	string stringArticulationFile; // Holds the read in articulation file
	string stringControlDLL; // Holds the read in control file
	// Loop till end of file
	while (1)
	{
		// Read the control file
		istrmCFGFile >> strLabel;
		if (!ReadStringInDoubleQuotes (istrmCFGFile, stringControlDLL))
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Control_Dll_File \"<string>\"");
			return FALSE;
		}
		if (!istrmCFGFile.good () || strLabel != "Control_Dll_File")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Control_Dll_File \"<string>\"");
			return FALSE;
		}
		// Save the data with its articulation
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Control_Dll_File field.");
			return FALSE;			
		}

		istrmCFGFile >> strLabel;
		if (!ReadStringInDoubleQuotes (istrmCFGFile, stringArticulationFile))
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Articulation_File \"<string>\"");
			return FALSE;
		}
		if (!istrmCFGFile.good () || strLabel != "Articulation_File")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Articulation_File \"<string>\"");
			return FALSE;
		}
		// Check to see if the files can be found
		CString strArticulationPath = "";
		CString strArticulationFile = stringArticulationFile.c_str ();
		if (!strArticulationFile.IsEmpty ())
		{
			BOOL bFindFile = CFindFile::FindFile (ARTICULATION_FILE_TYPE, 
				strArticulationFile, strArticulationPath);
			// If the file is not found, the user will get a message when it
			// is attempted to be opened

		}
		CString strControlPath = "";
		CString strControlFile = stringControlDLL.c_str ();
		if (!strControlFile.IsEmpty ())
		{
			BOOL bFindFile = CFindFile::FindFile (CONTROL_FILE_TYPE, 
				strControlFile, strControlPath);
			if (!bFindFile)
			{
				CString strError;
				strError.Format ("Warning: The control file %s could not be found in the search path.",
					strControlFile);
				AfxMessageBox (strError);
			}
		}

		// Save the data
		pCdmvCFGData->AddArticulationFileAndControlFile (strArticulationFile,
			strArticulationPath, strControlFile, strControlPath);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			// If this is FALSE, then the end of the file has been reached
			return TRUE;			
		}
	}

	return TRUE;
}

BOOL CParserCFG::ParseFileVersion2(ifstream &istrmCFGFile, int & rnCurrentLineNumber, 
								   CdmvCFGData *pCdmvCFGData)
{
	string strLabel; // Holder for the data labels

	// Read the control step size
	double dControlStepSize;
	istrmCFGFile >> strLabel >> dControlStepSize;
	if (!istrmCFGFile.good () || strLabel != "Control_Step_Size")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Control_Step_Size <floating_point>");
		return FALSE;
	}
	// Validate the data
	if (dControlStepSize < MINIMUM_CONTROL_STEP_SIZE || dControlStepSize > MAXIMUM_CONTROL_STEP_SIZE)
	{
		CString strError;
		strError.Format ("%f <= Control_Step_Size <= %f", MINIMUM_CONTROL_STEP_SIZE, MAXIMUM_CONTROL_STEP_SIZE);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetControlStepSize (dControlStepSize);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Control_Step_Size field.");
		return FALSE;			
	}

	// Read the simulation display rate
	int nSimulationDisplayRate;
	istrmCFGFile >> strLabel >> nSimulationDisplayRate;
	if (!istrmCFGFile.good () || strLabel != "Simulation_Display_Rate")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Simulation_Display_Rate <integer>");
		return FALSE;
	}
	// Validate the data
	if (nSimulationDisplayRate < MINIMUM_DISPLAY_RATE || nSimulationDisplayRate > MAXIMUM_DISPLAY_RATE)
	{
		CString strError;
		strError.Format ("%d <= Simulation_Display_Rate <= %d",
			MINIMUM_DISPLAY_RATE, MAXIMUM_DISPLAY_RATE);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetSimulationDisplayRate (nSimulationDisplayRate);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Simulation_Display_Rate field.");
		return FALSE;			
	}

	// Read the Real-time setting
	string strRealTime;
	istrmCFGFile >> strLabel >> strRealTime;
	if (!istrmCFGFile.good () || strLabel != "Real-time")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Real-time <string>");
		return FALSE;
	}
	// Save the data
	if (strRealTime == "TRUE")
		pCdmvCFGData->SetRealTime (TRUE);
	else if (strRealTime == "FALSE")
		pCdmvCFGData->SetRealTime (FALSE);
	else
	{
		// Validation error
		ValidationError (istrmCFGFile, rnCurrentLineNumber,
			"Real-time <string> (where string is in {TRUE, FALSE})");
		return FALSE;
	}
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Real-time field");
		return FALSE;			
	}

	// Inertial Axes
	double dAxesLength;
	int nAxesWidth;
	istrmCFGFile >> strLabel >> dAxesLength >> nAxesWidth;
	if (!istrmCFGFile.good () || strLabel != "Inertial_Axes")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Inertial_Axes <floating_point> <int>");
		return FALSE;
	}
	// Validate the data
	if (dAxesLength < MINIMUM_AXES_LENGTH || dAxesLength > MAXIMUM_AXES_LENGTH)
	{
		CString strError;
		strError.Format ("%f <= Inertial_Axes_Length <= %f", MINIMUM_AXES_LENGTH, MAXIMUM_AXES_LENGTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Validate the data
	if (nAxesWidth < MINIMUM_AXES_WIDTH || nAxesWidth > MAXIMUM_AXES_WIDTH)
	{
		CString strError;
		strError.Format ("%d <= Inertial_Axes_Width <= %d", MINIMUM_AXES_WIDTH, MAXIMUM_AXES_WIDTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetInertialAxesData (nAxesWidth, dAxesLength);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Inertial_Axes field.");
		return FALSE;			
	}
	
	// Link Axes
	istrmCFGFile >> strLabel >> dAxesLength >> nAxesWidth;
	if (!istrmCFGFile.good () || strLabel != "Link_Axes")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Link_Axes <floating_point> <int>");
		return FALSE;
	}
	// Validate the data
	if (dAxesLength < MINIMUM_AXES_LENGTH || dAxesLength > MAXIMUM_AXES_LENGTH)
	{
		CString strError;
		strError.Format ("%f <= Link_Axes_Length <= %f", MINIMUM_AXES_LENGTH, MAXIMUM_AXES_LENGTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Validate the data
	if (nAxesWidth < MINIMUM_AXES_WIDTH || nAxesWidth > MAXIMUM_AXES_WIDTH)
	{
		CString strError;
		strError.Format ("%d <= Link_Axes_Width <= %d", MINIMUM_AXES_WIDTH, MAXIMUM_AXES_WIDTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetLinkAxesData (nAxesWidth, dAxesLength);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Link_Axes field.");
		return FALSE;			
	}
	
	// Background color
	unsigned short sColor[3];
	istrmCFGFile >> strLabel >> sColor[0] >> sColor[1] >> sColor[2];
	if (!istrmCFGFile.good () || strLabel != "Background_Color")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Background_Color <byte> <byte> <byte>");
		return FALSE;
	}
	// Validate the data
	if (sColor[0] < 0 || sColor[0] > 255 ||
		sColor[1] < 0 || sColor[1] > 255 ||
		sColor[2] < 0 || sColor[2] > 255)
	{
		CString strError;
		strError = "0 <= Color_element <= 255";
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	COLORREF crColor = RGB (sColor[0], sColor[1], sColor[2]);
	pCdmvCFGData->SetBackgroundColor (crColor);	
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Background_Color field.");
		return FALSE;			
	}

	// Read the integrator type
	string strIntegrator;
	istrmCFGFile >> strLabel >> strIntegrator;
	if (!istrmCFGFile.good () || strLabel != "Integrator")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Integrator <string>");
		return FALSE;
	}
	// Set the integrator type
	if (strIntegrator == "EULER")
	{
		// EULER integrator
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_EULER);
		// Read the euler parameters on the next line
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
		double dStepSize;
		istrmCFGFile >> strLabel >> dStepSize;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Step_Size")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Step_Size <floating_point>");
			return FALSE;
		}
		// Validate the data
		if (dStepSize < MINIMUM_EULER_STEP_SIZE || dStepSize > MAXIMUM_EULER_STEP_SIZE)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Step_Size <= %f",
				MINIMUM_EULER_STEP_SIZE, MAXIMUM_EULER_STEP_SIZE);
			ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
			return FALSE;		
		}
		pCdmvCFGData->SetIntegratorEulerParameters (dStepSize);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Step_Size field.");
			return FALSE;			
		}
	}
	else if(strIntegrator == "RUNGE-KUTTA4")
	{
		// Fourth order Runge-Kutta
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_RUNGE_KUTTA_4);
		// Read the integrator parameters on the next line
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
		double dStepSize;
		istrmCFGFile >> strLabel >> dStepSize;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Step_Size")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Step_Size <floating_point>");
			return FALSE;
		}
		// Validate the data
		if (dStepSize < MINIMUM_RK4_STEP_SIZE || dStepSize > MAXIMUM_RK4_STEP_SIZE)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Step_Size <= %f", MINIMUM_RK4_STEP_SIZE,
				MAXIMUM_RK4_STEP_SIZE);
			ValidationError (istrmCFGFile, rnCurrentLineNumber,
				strError);
			return FALSE;		
		}
		pCdmvCFGData->SetIntegratorRungeKutta4Parameters (dStepSize);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Step_Size field.");
			return FALSE;			
		}
	}
	else if(strIntegrator == "ADAPTIVE_4_5_RUNGE-KUTTA")
	{
		// Adaptive step size 4th-5th order Runge-Kutta
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_ADAPTIVE_4_5_RUNGE_KUTTA);
		// Read the integrator parameters on the next line
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
		// Read epsilon
		double dEpsilon;
		istrmCFGFile >> strLabel >> dEpsilon;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Epsilon")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Epsilon <floating_point>");
			return FALSE;
		}
		// Validate the data
		if (dEpsilon < MINIMUM_RK45_EPSILON || dEpsilon > MAXIMUM_RK45_EPSILON)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Epsilon <= %f",
				MINIMUM_RK45_EPSILON, MAXIMUM_RK45_EPSILON);
			ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
			return FALSE;		
		}
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Epsilon field.");
			return FALSE;			
		}
		// Read minimum step size
		double dMinimumStepSize;
		istrmCFGFile >> strLabel >> dMinimumStepSize;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Minimum_Step_Size")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Minimum_Step_Size <floating_point>");
			return FALSE;
		}
		if (dMinimumStepSize < MINIMUM_RK45_MINIMUM_STEP_SIZE || dMinimumStepSize > MAXIMUM_RK45_MINIMUM_STEP_SIZE)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Minimum_Step_Size <= %f",
				MINIMUM_RK45_MINIMUM_STEP_SIZE, MAXIMUM_RK45_MINIMUM_STEP_SIZE);
			ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
			return FALSE;		
		}
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Minimum_Step_Size field.");
			return FALSE;			
		}
		// Save the data
		pCdmvCFGData->SetIntegratorAdaptive45RungeKuttaParameters (dEpsilon, dMinimumStepSize);
	}
	else if (strIntegrator == "PLACEMENT")
	{
		// Placement Integrator
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_PLACEMENT);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
	}
	else
	{
		// Unknown integrator
		CString strError;
		strError.Format (
			"Integrator <string> (where string is in {EULER, RUNGE-KUTTA4, ADAPTIVE_4_5_RUNGE-KUTTA, PLACEMENT}");
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;
	}

	// Read the Inertial Axes as COI Setting
	string strInertialAxesAsCOI;
	istrmCFGFile >> strLabel >> strInertialAxesAsCOI;
	if (!istrmCFGFile.good () || strLabel != "Inertial_Axes_As_COI")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Inertial_Axes_As_COI <string>");
		return FALSE;
	}
	// Save the data
	if (strInertialAxesAsCOI == "TRUE")
		pCdmvCFGData->SetInertialAxesAsCoi (TRUE);
	else if (strInertialAxesAsCOI == "FALSE")
		pCdmvCFGData->SetInertialAxesAsCoi (FALSE);
	else
	{
		// Validation error
		ValidationError (istrmCFGFile, rnCurrentLineNumber,
			"Inertial_Axes_As_COI <string> (where string is in {TRUE, FALSE})");
		return FALSE;
	}
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Inertial_Axes_As_COI field");
		return FALSE;			
	}

	// Read the Use Z of Inertial Setting
	string strUseZofInertial;
	istrmCFGFile >> strLabel >> strUseZofInertial;
	if (!istrmCFGFile.good () || strLabel != "Stabilize_Vertical_Camera_Position")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Stabilize_Vertical_Camera_Position <string>");
		return FALSE;
	}
	// Save the data
	if (strUseZofInertial == "TRUE")
		pCdmvCFGData->SetUseInertialZ (TRUE);
	else if (strUseZofInertial == "FALSE")
		pCdmvCFGData->SetUseInertialZ (FALSE);
	else
	{
		// Validation error
		ValidationError (istrmCFGFile, rnCurrentLineNumber,
			"Stabilize_Vertical_Camera_Position <string> (where string is in {TRUE, FALSE})");
		return FALSE;
	}
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Stabilize_Vertical_Camera_Position field");
		return FALSE;			
	}

	// Read the Center of Interest name
	string strCOIName;
	istrmCFGFile >> strLabel;
	if (!ReadStringInDoubleQuotes (istrmCFGFile, strCOIName))
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: COI_Name \"<string>\"");
		return FALSE;
	}
	if (!istrmCFGFile.good () || strLabel != "COI_Name")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: COI_Name \"<string>\"");
		return FALSE;
	}
	
	// Save the data
	pCdmvCFGData->SetCenterOfInterestName (CString(strCOIName.c_str()) );
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after COI_Name field");
		return FALSE;			
	}

	// Read the Center of Interest Offset
	double dOffsetX, dOffsetY, dOffsetZ;
	istrmCFGFile >> strLabel >> dOffsetX >> dOffsetY >> dOffsetZ;
	if (!istrmCFGFile.good () || strLabel != "COI_Offset")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: COI_Offset <floating_point> <floating_point> <floating_point>");
		return FALSE;
	}
	
	// Save the data
	pCdmvCFGData->SetCoiOffset (dOffsetX, dOffsetY, dOffsetZ);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after COI_Offset field.");
		return FALSE;			
	}

	// Read the camera orientation
	WTq wtq;
	istrmCFGFile >> strLabel >> wtq[0]>> wtq[1] >> wtq[2] >> wtq[3];
	if (!istrmCFGFile.good() || strLabel != "Camera_Orientation")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Camera_Orientation <floating_point> <floating_point> <floating_point> <floating_point>");
		return FALSE;
	}

	// Save the data
	pCdmvCFGData->SetOrientationQuaternion(wtq);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Camera_Orientation field.");
		return FALSE;			
	}

	// Read the camera position
	WTp3 wtp3;
	istrmCFGFile >> strLabel >> wtp3[0] >> wtp3[1] >> wtp3[2];
	if (!istrmCFGFile.good() || strLabel != "Camera_Position")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Camera_Position <floating_point> <floating_point> <floating_point> <floating_point>");
		return FALSE;
	}

	// Save the data
	pCdmvCFGData->SetOrientationPosition(wtp3);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Camera_Position field.");
		return FALSE;			
	}

	// Read the environment file
	string stringEnvironmentFile;
	istrmCFGFile >> strLabel;
	if (!ReadStringInDoubleQuotes (istrmCFGFile, stringEnvironmentFile))
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Environment_Parameter_File \"<string>\"");
		return FALSE;
	}
	if (!istrmCFGFile.good () || strLabel != "Environment_Parameter_File")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Environment_Parameter_File \"<string>\"");
		return FALSE;
	}
	// Check to see if the files can be found
	CString strEnvironmentPath = "";
	CString strEnvironmentFile = stringEnvironmentFile.c_str ();
	if (!strEnvironmentFile.IsEmpty ())
	{
		BOOL bFindFile = CFindFile::FindFile (ENVIRONMENT_FILE_TYPE, 
			strEnvironmentFile, strEnvironmentPath);
		// If the file is not found, the user will get a message when it
		// is attempted to be opened
	}

	// Save the data
	pCdmvCFGData->SetEnvironmentFile (strEnvironmentFile, strEnvironmentPath);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Environment_Parameter_File field");
		return FALSE;			
	}


	// The rest of the data is a list of control and .dm files in the simulation
	// First clear the current list of control and articulation files
	pCdmvCFGData->ClearArticulationFileAndControlFileList ();
	string stringArticulationFile; // Holds the read in articulation file
	string stringControlDLL; // Holds the read in control file
	// Loop till end of file
	while (1)
	{
		// Read the control file
		istrmCFGFile >> strLabel;
		if (!ReadStringInDoubleQuotes (istrmCFGFile, stringControlDLL))
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Control_Dll_File \"<string>\"");
			return FALSE;
		}
		if (!istrmCFGFile.good () || strLabel != "Control_Dll_File")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Control_Dll_File \"<string>\"");
			return FALSE;
		}
		// Save the data with its articulation
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Control_Dll_File field.");
			return FALSE;			
		}

		istrmCFGFile >> strLabel;
		if (!ReadStringInDoubleQuotes (istrmCFGFile, stringArticulationFile))
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Articulation_File \"<string>\"");
			return FALSE;
		}
		if (!istrmCFGFile.good () || strLabel != "Articulation_File")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Articulation_File \"<string>\"");
			return FALSE;
		}
		// Check to see if the files can be found
		CString strArticulationPath = "";
		CString strArticulationFile = stringArticulationFile.c_str ();
		if (!strArticulationFile.IsEmpty ())
		{
			BOOL bFindFile = CFindFile::FindFile (ARTICULATION_FILE_TYPE, 
				strArticulationFile, strArticulationPath);
			// If the file is not found, the user will get a message when it
			// is attempted to be opened

		}
		CString strControlPath = "";
		CString strControlFile = stringControlDLL.c_str ();
		if (!strControlFile.IsEmpty ())
		{
			BOOL bFindFile = CFindFile::FindFile (CONTROL_FILE_TYPE, 
				strControlFile, strControlPath);
			if (!bFindFile)
			{
				CString strError;
				strError.Format ("Warning: The control file %s could not be found in the search path.",
					strControlFile);
				AfxMessageBox (strError);
			}
		}

		// Save the data
		pCdmvCFGData->AddArticulationFileAndControlFile (strArticulationFile,
			strArticulationPath, strControlFile, strControlPath);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			// If this is FALSE, then the end of the file has been reached
			return TRUE;			
		}
	}

	return TRUE;
}


BOOL CParserCFG::ParseFileVersion3(ifstream &istrmCFGFile, int & rnCurrentLineNumber, 
								   CdmvCFGData *pCdmvCFGData)
{
	string strLabel; // Holder for the data labels

	// Read the control step size
	double dControlStepSize;
	istrmCFGFile >> strLabel >> dControlStepSize;
	if (!istrmCFGFile.good () || strLabel != "Control_Step_Size")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Control_Step_Size <floating_point>");
		return FALSE;
	}
	// Validate the data
	if (dControlStepSize < MINIMUM_CONTROL_STEP_SIZE || dControlStepSize > MAXIMUM_CONTROL_STEP_SIZE)
	{
		CString strError;
		strError.Format ("%f <= Control_Step_Size <= %f", MINIMUM_CONTROL_STEP_SIZE, MAXIMUM_CONTROL_STEP_SIZE);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetControlStepSize (dControlStepSize);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Control_Step_Size field.");
		return FALSE;			
	}

	// Read the simulation display rate
	int nSimulationDisplayRate;
	istrmCFGFile >> strLabel >> nSimulationDisplayRate;
	if (!istrmCFGFile.good () || strLabel != "Simulation_Display_Rate")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Simulation_Display_Rate <integer>");
		return FALSE;
	}
	// Validate the data
	if (nSimulationDisplayRate < MINIMUM_DISPLAY_RATE || nSimulationDisplayRate > MAXIMUM_DISPLAY_RATE)
	{
		CString strError;
		strError.Format ("%d <= Simulation_Display_Rate <= %d",
			MINIMUM_DISPLAY_RATE, MAXIMUM_DISPLAY_RATE);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetSimulationDisplayRate (nSimulationDisplayRate);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Simulation_Display_Rate field.");
		return FALSE;			
	}

	// Read the Real-time setting
	string strRealTime;
	istrmCFGFile >> strLabel >> strRealTime;
	if (!istrmCFGFile.good () || strLabel != "Real-time")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Real-time <string>");
		return FALSE;
	}
	// Save the data
	if (strRealTime == "TRUE")
		pCdmvCFGData->SetRealTime (TRUE);
	else if (strRealTime == "FALSE")
		pCdmvCFGData->SetRealTime (FALSE);
	else
	{
		// Validation error
		ValidationError (istrmCFGFile, rnCurrentLineNumber,
			"Real-time <string> (where string is in {TRUE, FALSE})");
		return FALSE;
	}
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Real-time field");
		return FALSE;			
	}

	// Inertial Axes
	double dAxesLength;
	int nAxesWidth;
	istrmCFGFile >> strLabel >> dAxesLength >> nAxesWidth;
	if (!istrmCFGFile.good () || strLabel != "Inertial_Axes")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Inertial_Axes <floating_point> <int>");
		return FALSE;
	}
	// Validate the data
	if (dAxesLength < MINIMUM_AXES_LENGTH || dAxesLength > MAXIMUM_AXES_LENGTH)
	{
		CString strError;
		strError.Format ("%f <= Inertial_Axes_Length <= %f", MINIMUM_AXES_LENGTH, MAXIMUM_AXES_LENGTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Validate the data
	if (nAxesWidth < MINIMUM_AXES_WIDTH || nAxesWidth > MAXIMUM_AXES_WIDTH)
	{
		CString strError;
		strError.Format ("%d <= Inertial_Axes_Width <= %d", MINIMUM_AXES_WIDTH, MAXIMUM_AXES_WIDTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetInertialAxesData (nAxesWidth, dAxesLength);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Inertial_Axes field.");
		return FALSE;			
	}
	
	// Link Axes
	istrmCFGFile >> strLabel >> dAxesLength >> nAxesWidth;
	if (!istrmCFGFile.good () || strLabel != "Link_Axes")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Link_Axes <floating_point> <int>");
		return FALSE;
	}
	// Validate the data
	if (dAxesLength < MINIMUM_AXES_LENGTH || dAxesLength > MAXIMUM_AXES_LENGTH)
	{
		CString strError;
		strError.Format ("%f <= Link_Axes_Length <= %f", MINIMUM_AXES_LENGTH, MAXIMUM_AXES_LENGTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Validate the data
	if (nAxesWidth < MINIMUM_AXES_WIDTH || nAxesWidth > MAXIMUM_AXES_WIDTH)
	{
		CString strError;
		strError.Format ("%d <= Link_Axes_Width <= %d", MINIMUM_AXES_WIDTH, MAXIMUM_AXES_WIDTH);
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvCFGData->SetLinkAxesData (nAxesWidth, dAxesLength);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Link_Axes field.");
		return FALSE;			
	}
	
	// Background color
	unsigned short sColor[3];
	istrmCFGFile >> strLabel >> sColor[0] >> sColor[1] >> sColor[2];
	if (!istrmCFGFile.good () || strLabel != "Background_Color")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Background_Color <byte> <byte> <byte>");
		return FALSE;
	}
	// Validate the data
	if (sColor[0] < 0 || sColor[0] > 255 ||
		sColor[1] < 0 || sColor[1] > 255 ||
		sColor[2] < 0 || sColor[2] > 255)
	{
		CString strError;
		strError = "0 <= Color_element <= 255";
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;		
	}
	// Save the data
	COLORREF crColor = RGB (sColor[0], sColor[1], sColor[2]);
	pCdmvCFGData->SetBackgroundColor (crColor);	
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Background_Color field.");
		return FALSE;			
	}

	// Read the integrator type
	string strIntegrator;
	istrmCFGFile >> strLabel >> strIntegrator;
	if (!istrmCFGFile.good () || strLabel != "Integrator")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Integrator <string>");
		return FALSE;
	}
	// Set the integrator type
	if (strIntegrator == "EULER")
	{
		// EULER integrator
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_EULER);
		// Read the euler parameters on the next line
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
		double dStepSize;
		istrmCFGFile >> strLabel >> dStepSize;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Step_Size")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Step_Size <floating_point>");
			return FALSE;
		}
		// Validate the data
		if (dStepSize < MINIMUM_EULER_STEP_SIZE || dStepSize > MAXIMUM_EULER_STEP_SIZE)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Step_Size <= %f",
				MINIMUM_EULER_STEP_SIZE, MAXIMUM_EULER_STEP_SIZE);
			ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
			return FALSE;		
		}
		pCdmvCFGData->SetIntegratorEulerParameters (dStepSize);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Step_Size field.");
			return FALSE;			
		}
	}
	else if(strIntegrator == "RUNGE-KUTTA4")
	{
		// Fourth order Runge-Kutta
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_RUNGE_KUTTA_4);
		// Read the integrator parameters on the next line
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
		double dStepSize;
		istrmCFGFile >> strLabel >> dStepSize;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Step_Size")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Step_Size <floating_point>");
			return FALSE;
		}
		// Validate the data
		if (dStepSize < MINIMUM_RK4_STEP_SIZE || dStepSize > MAXIMUM_RK4_STEP_SIZE)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Step_Size <= %f", MINIMUM_RK4_STEP_SIZE,
				MAXIMUM_RK4_STEP_SIZE);
			ValidationError (istrmCFGFile, rnCurrentLineNumber,
				strError);
			return FALSE;		
		}
		pCdmvCFGData->SetIntegratorRungeKutta4Parameters (dStepSize);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Step_Size field.");
			return FALSE;			
		}
	}
	else if(strIntegrator == "ADAPTIVE_4_5_RUNGE-KUTTA")
	{
		// Adaptive step size 4th-5th order Runge-Kutta
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_ADAPTIVE_4_5_RUNGE_KUTTA);
		// Read the integrator parameters on the next line
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
		// Read epsilon
		double dEpsilon;
		istrmCFGFile >> strLabel >> dEpsilon;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Epsilon")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Epsilon <floating_point>");
			return FALSE;
		}
		// Validate the data
		if (dEpsilon < MINIMUM_RK45_EPSILON || dEpsilon > MAXIMUM_RK45_EPSILON)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Epsilon <= %f",
				MINIMUM_RK45_EPSILON, MAXIMUM_RK45_EPSILON);
			ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
			return FALSE;		
		}
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Epsilon field.");
			return FALSE;			
		}
		// Read minimum step size
		double dMinimumStepSize;
		istrmCFGFile >> strLabel >> dMinimumStepSize;
		if (!istrmCFGFile.good () || strLabel != "Integrator_Parameter_Minimum_Step_Size")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Integrator_Parameter_Minimum_Step_Size <floating_point>");
			return FALSE;
		}
		if (dMinimumStepSize < MINIMUM_RK45_MINIMUM_STEP_SIZE || dMinimumStepSize > MAXIMUM_RK45_MINIMUM_STEP_SIZE)
		{
			CString strError;
			strError.Format ("%f <= Integrator_Parameter_Minimum_Step_Size <= %f",
				MINIMUM_RK45_MINIMUM_STEP_SIZE, MAXIMUM_RK45_MINIMUM_STEP_SIZE);
			ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
			return FALSE;		
		}
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator_Parameter_Minimum_Step_Size field.");
			return FALSE;			
		}
		// Save the data
		pCdmvCFGData->SetIntegratorAdaptive45RungeKuttaParameters (dEpsilon, dMinimumStepSize);
	}
	else if (strIntegrator == "PLACEMENT")
	{
		// Placement Integrator
		pCdmvCFGData->SetIntegratorType (INTEGRATOR_PLACEMENT);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Integrator field.");
			return FALSE;			
		}
	}
	else
	{
		// Unknown integrator
		CString strError;
		strError.Format (
			"Integrator <string> (where string is in {EULER, RUNGE-KUTTA4, ADAPTIVE_4_5_RUNGE-KUTTA, PLACEMENT}");
		ValidationError (istrmCFGFile, rnCurrentLineNumber, strError);
		return FALSE;
	}

	// Read the Inertial Axes as COI Setting
	string strInertialAxesAsCOI;
	istrmCFGFile >> strLabel >> strInertialAxesAsCOI;
	if (!istrmCFGFile.good () || strLabel != "Inertial_Axes_As_COI")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Inertial_Axes_As_COI <string>");
		return FALSE;
	}
	// Save the data
	if (strInertialAxesAsCOI == "TRUE")
		pCdmvCFGData->SetInertialAxesAsCoi (TRUE);
	else if (strInertialAxesAsCOI == "FALSE")
		pCdmvCFGData->SetInertialAxesAsCoi (FALSE);
	else
	{
		// Validation error
		ValidationError (istrmCFGFile, rnCurrentLineNumber,
			"Inertial_Axes_As_COI <string> (where string is in {TRUE, FALSE})");
		return FALSE;
	}
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Inertial_Axes_As_COI field");
		return FALSE;			
	}

	// Read the Use Z of Inertial Setting
	string strUseZofInertial;
	istrmCFGFile >> strLabel >> strUseZofInertial;
	if (!istrmCFGFile.good () || strLabel != "Stabilize_Vertical_Camera_Position")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Stabilize_Vertical_Camera_Position <string>");
		return FALSE;
	}
	// Save the data
	if (strUseZofInertial == "TRUE")
		pCdmvCFGData->SetUseInertialZ (TRUE);
	else if (strUseZofInertial == "FALSE")
		pCdmvCFGData->SetUseInertialZ (FALSE);
	else
	{
		// Validation error
		ValidationError (istrmCFGFile, rnCurrentLineNumber,
			"Stabilize_Vertical_Camera_Position <string> (where string is in {TRUE, FALSE})");
		return FALSE;
	}
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Stabilize_Vertical_Camera_Position field");
		return FALSE;			
	}

	// Read the Center of Interest name
	string strCOIName;
	istrmCFGFile >> strLabel;
	if (!ReadStringInDoubleQuotes (istrmCFGFile, strCOIName))
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: COI_Name \"<string>\"");
		return FALSE;
	}
	if (!istrmCFGFile.good () || strLabel != "COI_Name")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: COI_Name \"<string>\"");
		return FALSE;
	}
	
	// Save the data
	pCdmvCFGData->SetCenterOfInterestName (CString(strCOIName.c_str()) );
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after COI_Name field");
		return FALSE;			
	}

	// Read the Center of Interest Offset
	double dOffsetX, dOffsetY, dOffsetZ;
	istrmCFGFile >> strLabel >> dOffsetX >> dOffsetY >> dOffsetZ;
	if (!istrmCFGFile.good () || strLabel != "COI_Offset")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: COI_Offset <floating_point> <floating_point> <floating_point>");
		return FALSE;
	}
	
	// Save the data
	pCdmvCFGData->SetCoiOffset (dOffsetX, dOffsetY, dOffsetZ);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after COI_Offset field.");
		return FALSE;			
	}

	// Read the camera orientation
	WTq wtq;
	istrmCFGFile >> strLabel >> wtq[0]>> wtq[1] >> wtq[2] >> wtq[3];
	if (!istrmCFGFile.good() || strLabel != "Camera_Orientation")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Camera_Orientation <floating_point> <floating_point> <floating_point> <floating_point>");
		return FALSE;
	}

	// Save the data
	pCdmvCFGData->SetOrientationQuaternion(wtq);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Camera_Orientation field.");
		return FALSE;			
	}

	// Read the camera position
	WTp3 wtp3;
	istrmCFGFile >> strLabel >> wtp3[0] >> wtp3[1] >> wtp3[2];
	if (!istrmCFGFile.good() || strLabel != "Camera_Position")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Camera_Position <floating_point> <floating_point> <floating_point> <floating_point>");
		return FALSE;
	}

	// Save the data
	pCdmvCFGData->SetOrientationPosition(wtp3);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Camera_Position field.");
		return FALSE;			
	}

	// Read the ViewAngle Degree
	double dViewAngleDeg;
	istrmCFGFile >> strLabel >> dViewAngleDeg;
	if (!istrmCFGFile.good () || strLabel != "View_Angle_Degrees")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: View_Angle_Degrees <floating_point>");
		return FALSE;
	}
	
	// Save the data
	pCdmvCFGData->SetViewAngle_Degree (dViewAngleDeg);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after View_Angle_Degrees field.");
		return FALSE;			
	}

	// Read the environment file
	string stringEnvironmentFile;
	istrmCFGFile >> strLabel;
	if (!ReadStringInDoubleQuotes (istrmCFGFile, stringEnvironmentFile))
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Environment_Parameter_File \"<string>\"");
		return FALSE;
	}
	if (!istrmCFGFile.good () || strLabel != "Environment_Parameter_File")
	{
		ParseError (istrmCFGFile, rnCurrentLineNumber,
			"Expected: Environment_Parameter_File \"<string>\"");
		return FALSE;
	}
	// Check to see if the files can be found
	CString strEnvironmentPath = "";
	CString strEnvironmentFile = stringEnvironmentFile.c_str ();
	if (!strEnvironmentFile.IsEmpty ())
	{
		BOOL bFindFile = CFindFile::FindFile (ENVIRONMENT_FILE_TYPE, 
			strEnvironmentFile, strEnvironmentPath);
		// If the file is not found, the user will get a message when it
		// is attempted to be opened
	}

	// Save the data
	pCdmvCFGData->SetEnvironmentFile (strEnvironmentFile, strEnvironmentPath);
	if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
	{
		FormatError (istrmCFGFile, rnCurrentLineNumber,
			"Error after Environment_Parameter_File field");
		return FALSE;			
	}


	// The rest of the data is a list of control and .dm files in the simulation
	// First clear the current list of control and articulation files
	pCdmvCFGData->ClearArticulationFileAndControlFileList ();
	string stringArticulationFile; // Holds the read in articulation file
	string stringControlDLL; // Holds the read in control file
	// Loop till end of file
	while (1)
	{
		// Read the control file
		istrmCFGFile >> strLabel;
		if (!ReadStringInDoubleQuotes (istrmCFGFile, stringControlDLL))
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Control_Dll_File \"<string>\"");
			return FALSE;
		}
		if (!istrmCFGFile.good () || strLabel != "Control_Dll_File")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Control_Dll_File \"<string>\"");
			return FALSE;
		}
		// Save the data with its articulation
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			FormatError (istrmCFGFile, rnCurrentLineNumber,
				"Error after Control_Dll_File field.");
			return FALSE;			
		}

		istrmCFGFile >> strLabel;
		if (!ReadStringInDoubleQuotes (istrmCFGFile, stringArticulationFile))
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Articulation_File \"<string>\"");
			return FALSE;
		}
		if (!istrmCFGFile.good () || strLabel != "Articulation_File")
		{
			ParseError (istrmCFGFile, rnCurrentLineNumber,
				"Expected: Articulation_File \"<string>\"");
			return FALSE;
		}
		// Check to see if the files can be found
		CString strArticulationPath = "";
		CString strArticulationFile = stringArticulationFile.c_str ();
		if (!strArticulationFile.IsEmpty ())
		{
			BOOL bFindFile = CFindFile::FindFile (ARTICULATION_FILE_TYPE, 
				strArticulationFile, strArticulationPath);
			// If the file is not found, the user will get a message when it
			// is attempted to be opened

		}
		CString strControlPath = "";
		CString strControlFile = stringControlDLL.c_str ();
		if (!strControlFile.IsEmpty ())
		{
			BOOL bFindFile = CFindFile::FindFile (CONTROL_FILE_TYPE, 
				strControlFile, strControlPath);
			if (!bFindFile)
			{
				CString strError;
				strError.Format ("Warning: The control file %s could not be found in the search path.",
					strControlFile);
				AfxMessageBox (strError);
			}
		}

		// Save the data
		pCdmvCFGData->AddArticulationFileAndControlFile (strArticulationFile,
			strArticulationPath, strControlFile, strControlPath);
		if (!GotoNextData (istrmCFGFile, rnCurrentLineNumber))
		{
			// If this is FALSE, then the end of the file has been reached
			return TRUE;			
		}
	}

	return TRUE;
}

void CParserCFG::ValidationError(ifstream &istrmCFGFile, int nCurrentLineNumber, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Validation error in CFG file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmCFGFile.close ();
}
