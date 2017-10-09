// ParserEnvironment.cpp: implementation of the CParserEnvironment class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "ParserEnvironment.h"
#include "dmvTerrainData.h"
#include "dmvTreadmillData.h"
#include "FindFile.h"
#include <iostream>
#include <fstream>
#include <string>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserEnvironment::CParserEnvironment()
{

}

CParserEnvironment::~CParserEnvironment()
{

}


/*********************************************************************\
*  Function: CParserEnvironment::ParseEnvironmentFile
*
*  Description: Parses the environment text file, creates a class for
*		the data, and places the data in the class.  This supports
*		version changes in the environment file if desired and placing
*		comments in the file.  Error messages are displayed to the user
*		where a parse or format error is encountered.
*
*  Returns:  BOOL - FALSE if an error occurred during parsing
*					otherwise TRUE.  If FALSE is returned, the value
*					returned by ppCdmvEnvironmentData will be invalid
*					and if it was allocated in this function,
*					it will be deallocated before returning.
*  Argument: CString strFile
*  Argument: CdmvEnvironmentData **ppCdmvEnvironmentData
*
*  Created:  4/27/2001  Steven Rodenbaugh
\*********************************************************************/
BOOL CParserEnvironment::ParseEnvironmentFile(CString strFile, CdmvEnvironmentData 
											  **ppCdmvEnvironmentData)
{
	int nCurrentLineNumber = 1;

	// Make sure the pointer is pointing to a NULL when it comes in, because 
	// that value is tested to see if the class has been allocated in the following code
	*ppCdmvEnvironmentData = NULL;

	// Open the file
	ifstream istrmEnvFile (strFile);
	if (!istrmEnvFile) 
	{
		AfxMessageBox ("Failed to open environment file.");
		return FALSE;
	}

	// Advance to the first token in case it starts as blanks.
	if (!GotoNextData (istrmEnvFile, nCurrentLineNumber))
	{
		FormatError(istrmEnvFile, nCurrentLineNumber, 
			ppCdmvEnvironmentData, "Error before Version.");
		return FALSE;
	}

	// 14 MAY 2002 - Removed version number to be compatible with DyanMechs 
//	// The first real line will be the format type
//	// The label is there just for clarity and will not actually be parsed
//	string strLabel;
//	int nFormatVersion = 1; // Holds format version of file
//	istrmEnvFile >> strLabel >> nFormatVersion;
//
//	if (!istrmEnvFile.good () || strLabel != "Version")
//	{
//		ParseError (istrmEnvFile, nCurrentLineNumber, 
//			ppCdmvEnvironmentData, "Expected: Version <integer>");
//		return FALSE;
//	}
//	if (!GotoNextData (istrmEnvFile, nCurrentLineNumber))
//	{
//		FormatError (istrmEnvFile, nCurrentLineNumber, 
//			ppCdmvEnvironmentData, "Error after Version number.");
//		return FALSE;			
//	}
//	
//	// Call the correct procedure to parse the detected version type.
//	switch (nFormatVersion)
//	{
//	case 1:
		if (!ParseEnvironmentFileVersion1 (istrmEnvFile, nCurrentLineNumber, 
			ppCdmvEnvironmentData))
		{
			return FALSE;
		}
//		break;
//	default:
//		AfxMessageBox ("Unsupported version of environment file.");
//		return FALSE;
//	}

	istrmEnvFile.close ();

	return TRUE;
}

BOOL CParserEnvironment::ParseEnvironmentFileVersion1(ifstream &istrmEnvFile, int & rnCurrentLineNumber,
													  CdmvEnvironmentData ** ppCdmvEnvironmentData)
{
	string strLabel;

	// Read the environment type
	string strEnvironmentType;
	istrmEnvFile >>  strLabel >> strEnvironmentType;
	if (!istrmEnvFile.good () || strLabel != "Environment_Type")
	{
		ParseError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Expected: Environment_Type <env_string>");
		return FALSE;
	}



	// Create the class
	try
	{
		if (strEnvironmentType == "TERRAIN")
		{
			*ppCdmvEnvironmentData = new CdmvTerrainData;
		}
		else if (strEnvironmentType == "TREADMILL")
		{
			*ppCdmvEnvironmentData = new CdmvTreadmillData;
		}
		else
		{
			ValidationError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
				"Valid environment types are TERRAIN or TREADMILL");
			return FALSE;
		}
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}
	if (!GotoNextData (istrmEnvFile, rnCurrentLineNumber))
	{
		FormatError(istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Error after Environment_Type.");
		return FALSE;			
	}
	// Read Gravity
	CartesianVector cvGravity;
	istrmEnvFile >> strLabel >> cvGravity[0] >> cvGravity[1] >> cvGravity[2];
	if (!istrmEnvFile.good () || strLabel != "Gravity_Vector")
	{
		ParseError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Expected: Gravity_Vector <float> <float> <float>");
		return FALSE;
	}
	(*ppCdmvEnvironmentData)->SetGravity (cvGravity);
	if (!GotoNextData (istrmEnvFile, rnCurrentLineNumber))
	{
		FormatError(istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Error after Gravity_Vector field.");
		return FALSE;			
	}

	// Get the data file
	string stringDataFile;
	istrmEnvFile >> strLabel;
	if (!ReadStringInDoubleQuotes (istrmEnvFile, stringDataFile))
	{
		ParseError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Expected: Data_Filename \"<file_string>\"");
		return FALSE;
	}
	if (!istrmEnvFile.good () || strLabel != "Data_Filename")
	{
		ParseError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Expected: Data_Filename \"<file_string>\"");
		return FALSE;
	}
	// Check to see if the files can be found
	CString strDataPath = "";
	CString strDataFile = stringDataFile.c_str ();
	BOOL bFindFile;
	if ((*ppCdmvEnvironmentData)->GetEnvironmentType () == ENV_TERRAIN)
		bFindFile = CFindFile::FindFile (TERRAIN_FILE_TYPE, strDataFile, strDataPath);
	else if ((*ppCdmvEnvironmentData)->GetEnvironmentType () == ENV_TREADMILL)
		bFindFile = CFindFile::FindFile (TREADMILL_FILE_TYPE, strDataFile, strDataPath);
	else
		// Unexpected state
		ASSERT (FALSE);
	if (!bFindFile)
	{
		CString strError;
		strError.Format ("Warning: The data file %s could not be found in the search path.", 
			strDataFile);
		AfxMessageBox (strError);
	}	
	(*ppCdmvEnvironmentData)->SetDataFile (strDataFile, strDataPath);
	if (!GotoNextData (istrmEnvFile, rnCurrentLineNumber))
	{
		FormatError(istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Error after Data_Filename field.");
		return FALSE;			
	}

	// Get Ground Planar Spring
	double dPlanarSpring;
	istrmEnvFile >> strLabel >> dPlanarSpring;
	if (!istrmEnvFile.good () || strLabel != "Ground_Planar_Spring_Constant")
	{
		ParseError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
				"Expected: Ground_Planar_Spring_Constant <float>");
		return FALSE;
	}
	if (dPlanarSpring < ENV_PLANAR_SPRING_MIN || dPlanarSpring > ENV_PLANAR_SPRING_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Ground_Planar_Spring_Constant <= %.1f", ENV_PLANAR_SPRING_MIN,
			ENV_PLANAR_SPRING_MAX);
		ValidationError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData, strError);
		return FALSE;
	}
	(*ppCdmvEnvironmentData)->SetGroundPlanarSpringConstant (dPlanarSpring);
	if (!GotoNextData (istrmEnvFile, rnCurrentLineNumber))
	{
		FormatError(istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Error after the Ground_Planar_Spring_Constant.");
		return FALSE;			
	}

	// Get Ground Normal Spring Constant
	double dNormalSpring;
	istrmEnvFile >> strLabel >> dNormalSpring;
	if (!istrmEnvFile.good () || strLabel != "Ground_Normal_Spring_Constant")
	{
		ParseError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Expected: Ground_Normal_Spring_Constant <float>");
		return FALSE;
	}
	if (dNormalSpring < ENV_NORMAL_SPRING_MIN || dNormalSpring > ENV_NORMAL_SPRING_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Ground_Normal_Spring_Constant <= %.1f", ENV_NORMAL_SPRING_MIN,
			ENV_NORMAL_SPRING_MAX);
		ValidationError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData, strError);
		return FALSE;
	}
	(*ppCdmvEnvironmentData)->SetGroundNormalSpringConstant (dNormalSpring);
	if (!GotoNextData (istrmEnvFile, rnCurrentLineNumber))
	{
		FormatError(istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Error after Ground_Normal_Spring_Constant.");
		return FALSE;			
	}

	// Get Ground Planar Damper Constant
	double dPlanarDamper;
	istrmEnvFile >> strLabel >> dPlanarDamper;
	if (!istrmEnvFile.good () || strLabel != "Ground_Planar_Damper_Constant")
	{
		ParseError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData, 
			"Expected: Ground_Planar_Damper_Constant <floating_point>");
		return FALSE;
	}
	if (dPlanarDamper < ENV_PLANAR_DAMPER_MIN || dPlanarDamper > ENV_PLANAR_DAMPER_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Ground_Planar_Damper_Constant <= %.1f", ENV_PLANAR_DAMPER_MIN,
			ENV_PLANAR_DAMPER_MAX);
		ValidationError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData, strError);
		return FALSE;
	}
	(*ppCdmvEnvironmentData)->SetGroundPlanarDamperConstant (dPlanarDamper);
	if (!GotoNextData (istrmEnvFile, rnCurrentLineNumber))
	{
		FormatError(istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Error after Ground_Planar_Damper_Constant.");
		return FALSE;			
	}

	// Get Ground Normal Damper Constant
	double dNormalDamper;
	istrmEnvFile >> strLabel >> dNormalDamper;
	if (!istrmEnvFile.good () || strLabel != "Ground_Normal_Damper_Constant")
	{
		ParseError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Expected: Ground_Normal_Damper_Constant <float>");
		return FALSE;
	}
	if (dNormalDamper < ENV_NORMAL_DAMPER_MIN || dNormalDamper > ENV_NORMAL_DAMPER_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Ground_Normal_Damper_Constant <= %.1f", ENV_NORMAL_DAMPER_MIN,
			ENV_NORMAL_DAMPER_MAX);
		ValidationError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData, strError);
		return FALSE;
	}
	(*ppCdmvEnvironmentData)->SetGroundNormalDamperConstant (dNormalDamper);
	if (!GotoNextData (istrmEnvFile, rnCurrentLineNumber))
	{
		FormatError(istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Error after Ground_Normal_Damper_Constant");
		return FALSE;			
	}

	// Get Static Friction Coefficieint
	double d_us;
	istrmEnvFile >> strLabel >> d_us;
	if (!istrmEnvFile.good () || strLabel != "Ground_Static_Friction_Coeff")
	{
		ParseError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Expected: Ground_Static_Friction_Coeff <float>");
		return FALSE;
	}
	if (d_us < ENV_STATIC_FRICTION_MIN || d_us > ENV_STATIC_FRICTION_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Ground_Static_Friction_Coeff <= %.1f", ENV_STATIC_FRICTION_MIN,
			ENV_STATIC_FRICTION_MAX);
		ValidationError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData, strError);
		return FALSE;
	}
	(*ppCdmvEnvironmentData)->SetCoefficientStaticFriction (d_us);
	if (!GotoNextData (istrmEnvFile, rnCurrentLineNumber))
	{
		FormatError(istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Error after Ground_Static_Friction_Coeff.");
		return FALSE;			
	}

	double a =ENV_STATIC_FRICTION_MAX;
	double b = ENV_STATIC_FRICTION_MIN;

	// Get Kinetic Friction Coefficieint
	double d_uk;
	istrmEnvFile >> strLabel >> d_uk;
	if (!istrmEnvFile.good () || strLabel != "Ground_Kinetic_Friction_Coeff")
	{
		ParseError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Expected: Ground_Kinetic_Friction_Coeff <float>");
		return FALSE;
	}
	if (d_uk < ENV_KINETIC_FRICTION_MIN || d_uk > ENV_KINETIC_FRICTION_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Ground_Kinetic_Friction_Coeff <= %.1f", ENV_KINETIC_FRICTION_MIN,
			ENV_KINETIC_FRICTION_MAX);
		ValidationError (istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData, strError);
		return FALSE;
	}
	(*ppCdmvEnvironmentData)->SetCoefficientKineticFriction (d_uk);
/*	if (!GotoNextData (istrmEnvFile, rnCurrentLineNumber))
	{
		FormatError(istrmEnvFile, rnCurrentLineNumber, ppCdmvEnvironmentData,
			"Error after Ground_Kinetic_Friction_Coeff.");
		return FALSE;			
	}
*/
	return TRUE;
}



// Called when unexpectedly reaches the end of file or
// comes across a data/label field when not expecting it
void CParserEnvironment::FormatError(ifstream & istrmEnvFile, int nCurrentLineNumber,
									 CdmvEnvironmentData ** ppCdmvEnvironmentData,
									 CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Format error in environment file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmEnvFile.close ();
	if (*ppCdmvEnvironmentData)
	{
		delete *ppCdmvEnvironmentData;
		*ppCdmvEnvironmentData = NULL;
	}
}

// Called when can't properly parse a data field
void CParserEnvironment::ParseError(ifstream & istrmEnvFile, int nCurrentLineNumber,
									CdmvEnvironmentData ** ppCdmvEnvironmentData,
									CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Parse error in environment file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmEnvFile.close ();
	if (*ppCdmvEnvironmentData)
	{
		delete *ppCdmvEnvironmentData;
		*ppCdmvEnvironmentData = NULL;
	}
}

void CParserEnvironment::ValidationError(ifstream & istrmEnvFile, int nCurrentLineNumber,
									CdmvEnvironmentData ** ppCdmvEnvironmentData,
									CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Validation error in environment file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmEnvFile.close ();
	if (*ppCdmvEnvironmentData)
	{
		delete *ppCdmvEnvironmentData;
		*ppCdmvEnvironmentData = NULL;
	}
}