// ParserTreadmill.cpp: implementation of the CParserTreadmill class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "ParserTreadmill.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserTreadmill::CParserTreadmill()
{

}

CParserTreadmill::~CParserTreadmill()
{

}

// todo: need to reset the conveyor values on an error, so the graphics wont try to draw
// it without all of the data
BOOL CParserTreadmill::ParseFileVersion1 (ifstream & istrmTreadmillFile, int & rnCurrentLineNumber, 
										  CdmvTreadmillData* pCdmvTreadmillData)
{
	string strLabel;

	// Normal
	CartesianVector cvNormal;
	istrmTreadmillFile >> strLabel >> cvNormal[0] >> cvNormal[1] >> cvNormal[2];
	if (!istrmTreadmillFile.good () || strLabel != "Normal_Direction")
	{
		ParseError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Expected: Normal_Direction <float> <float> <float>");
		return FALSE;
	}
	if (!GotoNextData (istrmTreadmillFile, rnCurrentLineNumber))
	{
		FormatError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData, 
			"Error after Normal_Direction field.");
		return FALSE;			
	}

	// Velocity
	CartesianVector cvVelocity;
	istrmTreadmillFile >> strLabel >> cvVelocity[0] >> cvVelocity[1] >> cvVelocity[2];
	if (!istrmTreadmillFile.good () || strLabel != "Velocity_Direction")
	{
		ParseError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Expected: Velocity_Direction <float> <float> <float>");
		return FALSE;
	}
	// Validate that the normal and velocity are linearly independent
	if (!CdmvTreadmillData::ValidateNormalAndVelocity (cvNormal, cvVelocity))
	{
		CString strError;
		strError = "The normal and velocity vectors must be linearly independent.";
		ValidationError (istrmTreadmillFile, rnCurrentLineNumber,  pCdmvTreadmillData, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvTreadmillData->SetNormalAndVelocityDirection (cvNormal, cvVelocity);
	if (!GotoNextData (istrmTreadmillFile, rnCurrentLineNumber))
	{
		FormatError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Error after Velocity_Direction field.");
		return FALSE;			
	}

	// Position of center of treadmill
	CartesianVector cvPosition;
	istrmTreadmillFile >> strLabel >> cvPosition[0] >> cvPosition[1] >> cvPosition[2];
	if (!istrmTreadmillFile.good () || strLabel != "Position")
	{
		ParseError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Expected: Position <float> <float> <float>");
		return FALSE;
	}
	// Save the data
	pCdmvTreadmillData->SetPosition (cvPosition);
	if (!GotoNextData (istrmTreadmillFile, rnCurrentLineNumber))
	{
		FormatError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Error after Position field.");
		return FALSE;			
	}

	// Width of treadmill
	Float fWidth;
	istrmTreadmillFile >> strLabel >> fWidth;
	if (!istrmTreadmillFile.good () || strLabel != "Width")
	{
		ParseError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Expected: Width <float>");
		return FALSE;
	}
	// Validate the data
	if (fWidth < TREADMILL_WIDTH_MIN || fWidth > TREADMILL_WIDTH_MAX)
	{
		CString strError;
		strError.Format ("%f <= Width <= %.1f", TREADMILL_WIDTH_MIN, TREADMILL_WIDTH_MAX);
		ValidationError (istrmTreadmillFile, rnCurrentLineNumber,  pCdmvTreadmillData, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvTreadmillData->SetWidth (fWidth);
	if (!GotoNextData (istrmTreadmillFile, rnCurrentLineNumber))
	{
		FormatError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Error after Width field.");
		return FALSE;			
	}
	
	// Length of treadmill
	Float fLength;
	istrmTreadmillFile >> strLabel >> fLength;
	if (!istrmTreadmillFile.good () || strLabel != "Length")
	{
		ParseError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Expected: Length <float>");
		return FALSE;
	}
	// Validate the data
	if (fLength < TREADMILL_LENGTH_MIN || fLength > TREADMILL_LENGTH_MAX)
	{
		CString strError;
		strError.Format ("%f <= Length <= %.1f", TREADMILL_LENGTH_MIN, TREADMILL_LENGTH_MAX);
		ValidationError (istrmTreadmillFile, rnCurrentLineNumber,  pCdmvTreadmillData, strError);
		return FALSE;		
	}
	// Save the data
	pCdmvTreadmillData->SetLength (fLength);
	if (!GotoNextData (istrmTreadmillFile, rnCurrentLineNumber))
	{
		FormatError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Error after Length field.");
		return FALSE;			
	}

	// Velocity magnitude
	Float fVelocityMagnitude;
	istrmTreadmillFile >> strLabel >> fVelocityMagnitude;
	if (!istrmTreadmillFile.good () || strLabel != "Velocity_Mag")
	{
		ParseError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Expected: Velocity_Mag <float>");
		return FALSE;
	}
	// Save the data
	pCdmvTreadmillData->SetVelocityMagnitude (fVelocityMagnitude);
	if (!GotoNextData (istrmTreadmillFile, rnCurrentLineNumber))
	{
		FormatError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Error after Velocity_Mag field.");
		return FALSE;			
	}

	
	// Rest of the data is RobotBuilder specific and not used by DynaMechs

	// CONVEYOR COLOR
	unsigned short sColor[3];
	istrmTreadmillFile >> strLabel >> sColor[0] >> sColor[1] >> sColor[2];
	if (!istrmTreadmillFile.good () || strLabel != "Color")
	{
		ParseError (istrmTreadmillFile, rnCurrentLineNumber, pCdmvTreadmillData,
			"Expected: Color <byte> <byte> <byte>");
		return FALSE;
	}
	// Validate the data
	if (sColor[0] < 0 || sColor[0] > 255 ||
		sColor[1] < 0 || sColor[1] > 255 ||
		sColor[2] < 0 || sColor[2] > 255)
	{
		CString strError;
		strError = "0 <= Color_element <= 255";
		ValidationError (istrmTreadmillFile, rnCurrentLineNumber,  pCdmvTreadmillData, strError);
		return FALSE;		
	}
	// Save the data
	COLORREF crColor = RGB (sColor[0], sColor[1], sColor[2]);
	pCdmvTreadmillData->SetColor (crColor);

	// Last data, so don't use GotoNextData in case there is no terminating newline
	
	return TRUE;
}


BOOL CParserTreadmill::ParseTreadmillFile(CString strFile, CdmvTreadmillData *pCdmvTreadmillData)
{
	// Line Number
	int nCurrentLineNumber = 1;

	// First check if it is a full path - two conditions will be checked.  First, the
	// first letter should not be a . (period).  This lets us use relative path names
	// without breaking any rules (like accidently finding a file relative to the
	// current directory).  Next there needs to be at least 1 backslash.
	// This check needs to be made, because the call to open the file will use search
	// the current directory if it is just a file name - this can lead to inconsistencies
	// depending on the current directory
	if (!((strFile.GetAt (0) != '.') && (strFile.Find ('\\', 0) != -1)))
	{
		AfxMessageBox ("Failed to open Treadmill file.");
		return FALSE;
	}

	// Open the file
	ifstream istrmTreadmillFile (strFile);
	if (!istrmTreadmillFile) 
	{
		AfxMessageBox ("Failed to open Treadmill file.");
		return FALSE;
	}

	// Advance to the first token in case it starts as blanks.
	if (!GotoNextData (istrmTreadmillFile, nCurrentLineNumber))
	{
		FormatError(istrmTreadmillFile, nCurrentLineNumber, pCdmvTreadmillData,
			"Error before Version field.");
		return FALSE;
	}

	// The first real line will be the format type
	string strLabel;
	int nFormatVersion = 1; // Holds format version of file
	istrmTreadmillFile >> strLabel >> nFormatVersion;

	if (!istrmTreadmillFile.good () || strLabel != "Version")
	{
		ParseError (istrmTreadmillFile, nCurrentLineNumber, pCdmvTreadmillData,
			"Expected: Version <integer>");
		return FALSE;
	}
	if (!GotoNextData (istrmTreadmillFile, nCurrentLineNumber))
	{
		FormatError (istrmTreadmillFile, nCurrentLineNumber, pCdmvTreadmillData,
			"Error after Version field.");
		return FALSE;			
	}
	
	// Call the correct procedure to parse the detected version type.
	switch (nFormatVersion)
	{
	case 1:
		if (!ParseFileVersion1 (istrmTreadmillFile, nCurrentLineNumber, pCdmvTreadmillData))
		{
			return FALSE;
		}
		break;
	default:
		AfxMessageBox ("Unsupported version of Treadmill file.");
		return FALSE;
	}

	// Close the stream
	istrmTreadmillFile.close ();

	return TRUE;
}

void CParserTreadmill::ValidationError(ifstream &istrmTreadmillFile, int nCurrentLineNumber, 
									   CdmvTreadmillData *pCdmvTreadmillData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Validation error in Treadmill file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	// Reset the treadmill data to initial values
	pCdmvTreadmillData->ResetTreadmillData ();
	istrmTreadmillFile.close ();
}

void CParserTreadmill::ParseError(ifstream &istrmTreadmillFile, int nCurrentLineNumber, 
									   CdmvTreadmillData *pCdmvTreadmillData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Parse error in Treadmill file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	// Reset the treadmill data to initial values
	pCdmvTreadmillData->ResetTreadmillData ();
	istrmTreadmillFile.close ();
}

void CParserTreadmill::FormatError(ifstream &istrmTreadmillFile, int nCurrentLineNumber, 
									   CdmvTreadmillData *pCdmvTreadmillData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Format error in Treadmill file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	// Reset the treadmill data to initial values
	pCdmvTreadmillData->ResetTreadmillData ();
	istrmTreadmillFile.close ();
}