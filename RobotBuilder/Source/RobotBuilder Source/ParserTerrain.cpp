// ParserTerrain.cpp: implementation of the CParserTerrain class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "ParserTerrain.h"
#include "FindFile.h"
#include "DMViewerDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserTerrain::CParserTerrain()
{

}

CParserTerrain::~CParserTerrain()
{

}

void CParserTerrain::ValidationError(ifstream &istrmTerrainFile, int nCurrentLineNumber,
									 CdmvTerrainData *pCdmvTerrainData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Validation error in Terrain file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	// Reset the terrain data to initial values
	pCdmvTerrainData->ResetTerrainData ();
	istrmTerrainFile.close ();
}

void CParserTerrain::ParseError(ifstream &istrmTerrainFile, int nCurrentLineNumber,
								CdmvTerrainData *pCdmvTerrainData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Parse error in Terrain file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	// Reset the terrain data to initial values
	pCdmvTerrainData->ResetTerrainData ();
	istrmTerrainFile.close ();
}

void CParserTerrain::FormatError(ifstream &istrmTerrainFile, int nCurrentLineNumber,
								 CdmvTerrainData *pCdmvTerrainData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Format error in Terrain file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	// Reset the terrain data to initial values
	pCdmvTerrainData->ResetTerrainData ();
	istrmTerrainFile.close ();
}


BOOL CParserTerrain::ParseTerrainFile(CString strFile, CdmvTerrainData *pCdmvTerrainData)
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
		AfxMessageBox ("Failed to open Terrain file.");
		return FALSE;
	}


	// Open the file
	ifstream istrmTerrainFile (strFile);
	if (!istrmTerrainFile) 
	{
		AfxMessageBox ("Failed to open Terrain file.");
		return FALSE;
	}

	// Advance to the first token in case it starts as blanks.
	if (!GotoNextData (istrmTerrainFile, nCurrentLineNumber))
	{
		FormatError(istrmTerrainFile, nCurrentLineNumber, pCdmvTerrainData,
			"Error before Version field.");
		return FALSE;
	}

	// Reset the terrain data to initial values
	pCdmvTerrainData->ResetTerrainData ();

	// 17 MAY 2002 - Removed version number to be compatible with DynaMechs
  // December 8, 2003 - Uncommented to add the Wireframe overlay option
	// The first real line will be the format type
	string strLabel;
	int nFormatVersion = 1; // Holds format version of file
  if (istrmTerrainFile.peek() != 'V') // peek at the next char	
	{// No Version field, so it's Version 1.
    nFormatVersion = 1;
	}
  else if (istrmTerrainFile.peek() == 'V') //There is a Version field
  {
	  istrmTerrainFile >> strLabel >> nFormatVersion;

	  if (!istrmTerrainFile.good () || strLabel != "Version")
	  {
  		ParseError (istrmTerrainFile, nCurrentLineNumber, pCdmvTerrainData,
			  "Expected: Version <integer>");
		  return FALSE;
	  }
	  if (!GotoNextData (istrmTerrainFile, nCurrentLineNumber))
	  {
  		FormatError (istrmTerrainFile, nCurrentLineNumber, pCdmvTerrainData,
			  "Error after Version field.");
		  return FALSE;			
	  }
  }
	// Call the correct procedure to parse the detected version type.
	switch (nFormatVersion)
	{
	case 1:
		if (!ParseFileVersion1 (istrmTerrainFile, nCurrentLineNumber, pCdmvTerrainData))
		{
			return FALSE;
		}
		break;
	case 2:
    if (!ParseFileVersion2 (istrmTerrainFile, nCurrentLineNumber, pCdmvTerrainData))
		{
			return FALSE;
		}
    break;
	default:
		AfxMessageBox ("Unsupported version of Terrain file.");
		return FALSE;
	}

	// Close the stream
	istrmTerrainFile.close ();

	return TRUE;
}

BOOL CParserTerrain::ParseFileVersion1 (ifstream & istrmTerrainFile, int & rnCurrentLineNumber, 
										  CdmvTerrainData* pCdmvTerrainData)
{
	string strLabel;

	// Read the elevation/depth data in meters.
	int nXDim, nYDim;
	double dGridResolution;
	istrmTerrainFile >> nXDim >> nYDim >> dGridResolution;
	if (!istrmTerrainFile.good ())
	{
		ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
			"Expected: <int - xdim> <int - ydim> <float - resolution>");
		return FALSE;
	}

	// Validate the data
	if (nXDim < TERRAIN_DIM_MIN || nXDim > TERRAIN_DIM_MAX)
	{
		CString strError;
		strError.Format ("%d <= X Dimension <= %d", TERRAIN_DIM_MIN, TERRAIN_DIM_MAX);
		ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
		return FALSE;		
	}
	if (nYDim < TERRAIN_DIM_MIN || nYDim > TERRAIN_DIM_MAX)
	{
		CString strError;
		strError.Format ("%d <= Y Dimension <= %d", TERRAIN_DIM_MIN, TERRAIN_DIM_MAX);
		ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
		return FALSE;		
	}
	if (dGridResolution < TERRAIN_RESOLUTION_MIN || dGridResolution > TERRAIN_RESOLUTION_MAX)
	{
		CString strError;
		strError.Format ("%f <= Grid Resolution <= %.2f", TERRAIN_RESOLUTION_MIN, TERRAIN_RESOLUTION_MAX);
		ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
		return FALSE;
	}
	// Save the data
	pCdmvTerrainData->SetDimensions (nXDim, nYDim);
	pCdmvTerrainData->SetGridResolution (dGridResolution);

	if (!GotoNextData (istrmTerrainFile, rnCurrentLineNumber))
	{
		FormatError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
			"Error after dimension/resolution field.");
		return FALSE;			
	}



	int i, j;
	double dZValue;
	for (i = 0; i < nXDim; i++)
	{
		for (j = 0; j < nYDim; j++)
		{
			istrmTerrainFile >> dZValue;
			if (!istrmTerrainFile.good ())
			{
				ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
					"Expected a matrix of z values.");
				return FALSE;
			}
			// Save the value
			pCdmvTerrainData->SetZValue (i, j, dZValue);
		}
		if (!GotoNextData (istrmTerrainFile, rnCurrentLineNumber))
		{
			//// To be compatible with DynaMechs, the next parts are optional
			// (DynaMechs does not use the following Covering field, but RB does)
			if (istrmTerrainFile.eof () && i == nXDim - 1 && j == nYDim)
			{
				// Hardcode a default value for the covering color
				pCdmvTerrainData->SetCovering (RGB (0, 0, 255));
				istrmTerrainFile.close ();

				return TRUE;
			}
			
			
			FormatError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
				"Error while parsing the matrix of z values.");
			return FALSE;			
		}
	}

	// Covering
	string strCovering;
	istrmTerrainFile >> strLabel >> strCovering;
	if (!istrmTerrainFile.good () || strLabel != "Covering")
	{
		ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
			"Expected: Covering <string> ... (the rest depends on the string value)");
		return FALSE;
	}
	if (strCovering == "COLOR")
	{
		// Pick up the RGB values
		unsigned short sColor[3];
		istrmTerrainFile >> sColor[0] >> sColor[1] >> sColor[2];
		if (!istrmTerrainFile.good ())
		{
			ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
				"Expected: Covering COLOR <byte> <byte> <byte>");
			return FALSE;
		}
		// Validate the data
		if (sColor[0] < 0 || sColor[0] > 255 ||
			sColor[1] < 0 || sColor[1] > 255 ||
			sColor[2] < 0 || sColor[2] > 255)
		{
			CString strError;
			strError = "0 <= Color_element <= 255";
			ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
			return FALSE;		
		}
		// Save the data
		COLORREF crColor = RGB (sColor[0], sColor[1], sColor[2]);
		pCdmvTerrainData->SetCovering (crColor);	
	}
	else if (strCovering == "TEXTURE")
	{
		// Pick up the texture string
		string stringTextureFile;
		if (!ReadStringInDoubleQuotes (istrmTerrainFile, stringTextureFile))
		{
			ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
				"Expected: Covering TEXTURE \"<file_string>\"");
			return FALSE;
		}
		// Check to see if the file can be found
		CString strTexturePath = "";
		CString strTextureFile = stringTextureFile.c_str ();
		BOOL bFindFile = CFindFile::FindFile (TEXTURE_FILE_TYPE, 
			strTextureFile, strTexturePath);
		if (!bFindFile)
		{
			CString strError;
			strError.Format ("Warning: The texture file %s could not be found in the search path.", 
				strTextureFile);
			AfxMessageBox (strError);
		}
		pCdmvTerrainData->SetCovering (strTextureFile, strTexturePath);	
	}
	else
	{
		// Invalid token
		CString strError = "Valid covering types are COLOR or TEXTURE";
		ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
		return FALSE;
	}

	istrmTerrainFile.close ();

	return TRUE;
}

BOOL CParserTerrain::ParseFileVersion2 (ifstream & istrmTerrainFile, int & rnCurrentLineNumber, 
										  CdmvTerrainData* pCdmvTerrainData)
{
	string strLabel;
	// Read the elevation/depth data in meters.
	int nXDim, nYDim;
	double dXGridResolution, dYGridResolution;
	istrmTerrainFile >> nXDim >> nYDim >> dXGridResolution >> dYGridResolution;
	if (!istrmTerrainFile.good ())
	{
		ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
			"Expected: <int - xdim> <int - ydim> <float - xresolution> <float - yresolution>");
		return FALSE;
	}

	// Validate the data
	if (nXDim < TERRAIN_DIM_MIN || nXDim > TERRAIN_DIM_MAX)
	{
		CString strError;
		strError.Format ("%d <= X Dimension <= %d", TERRAIN_DIM_MIN, TERRAIN_DIM_MAX);
		ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
		return FALSE;		
	}
	if (nYDim < TERRAIN_DIM_MIN || nYDim > TERRAIN_DIM_MAX)
	{
		CString strError;
		strError.Format ("%d <= Y Dimension <= %d", TERRAIN_DIM_MIN, TERRAIN_DIM_MAX);
		ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
		return FALSE;		
	}
	if (dXGridResolution < TERRAIN_RESOLUTION_MIN || dXGridResolution > TERRAIN_RESOLUTION_MAX)
	{
		CString strError;
		strError.Format ("%f <= XGrid Resolution <= %.2f", TERRAIN_RESOLUTION_MIN, TERRAIN_RESOLUTION_MAX);
		ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
		return FALSE;
	}
	if (dYGridResolution < TERRAIN_RESOLUTION_MIN || dYGridResolution > TERRAIN_RESOLUTION_MAX)
	{
		CString strError;
		strError.Format ("%f <= YGrid Resolution <= %.2f", TERRAIN_RESOLUTION_MIN, TERRAIN_RESOLUTION_MAX);
		ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
		return FALSE;
	}
	// Save the data
	pCdmvTerrainData->SetDimensions (nXDim, nYDim);
	//pCdmvTerrainData->SetGridResolution (dGridResolution);
	pCdmvTerrainData->SetXYGridResolution (dXGridResolution, dYGridResolution);

	if (!GotoNextData (istrmTerrainFile, rnCurrentLineNumber))
	{
		FormatError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
			"Error after dimension/resolution field.");
		return FALSE;			
	}


	int i, j;
	double dZValue;
	for (i = 0; i < nXDim; i++)
	{
		for (j = 0; j < nYDim; j++)
		{
			istrmTerrainFile >> dZValue;
			if (!istrmTerrainFile.good ())
			{
				ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
					"Expected a matrix of z values.");
				return FALSE;
			}
			// Save the value
			pCdmvTerrainData->SetZValue (i, j, dZValue);
		}
		if (!GotoNextData (istrmTerrainFile, rnCurrentLineNumber))
		{
			//// To be compatible with DynaMechs, the next parts are optional
			// (DynaMechs does not use the following Covering field, but RB does)
			if (istrmTerrainFile.eof () && i == nXDim - 1 && j == nYDim)
			{
				// Hardcode a default value for the covering color
				pCdmvTerrainData->SetCovering (RGB (0, 0, 255));
				istrmTerrainFile.close ();

				return TRUE;
			}
			
			FormatError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
				"Error while parsing the matrix of z values.");
			return FALSE;			
		}
	}

	// Covering
	string strCovering;
	istrmTerrainFile >> strLabel >> strCovering;
	if (!istrmTerrainFile.good () || strLabel != "Covering")
	{
		ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
			"Expected: Covering <string> ... (the rest depends on the string value)");
		return FALSE;
	}
	if (strCovering == "COLOR")
	{
		// Pick up the RGB values
		unsigned short sColor[3];
		istrmTerrainFile >> sColor[0] >> sColor[1] >> sColor[2];
		if (!istrmTerrainFile.good ())
		{
			ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
				"Expected: Covering COLOR <byte> <byte> <byte>");
			return FALSE;
		}
		// Validate the data
		if (sColor[0] < 0 || sColor[0] > 255 ||
			sColor[1] < 0 || sColor[1] > 255 ||
			sColor[2] < 0 || sColor[2] > 255)
		{
			CString strError;
			strError = "0 <= Color_element <= 255";
			ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
			return FALSE;		
		}
		// Save the data
		COLORREF crColor = RGB (sColor[0], sColor[1], sColor[2]);
		pCdmvTerrainData->SetCovering (crColor);	
	}
	else if (strCovering == "TEXTURE")
	{
		// Pick up the texture string
		string stringTextureFile;
		if (!ReadStringInDoubleQuotes (istrmTerrainFile, stringTextureFile))
		{
			ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
				"Expected: Covering TEXTURE \"<file_string>\"");
			return FALSE;
		}
		// Check to see if the file can be found
		CString strTexturePath = "";
		CString strTextureFile = stringTextureFile.c_str ();
		BOOL bFindFile = CFindFile::FindFile (TEXTURE_FILE_TYPE, 
			strTextureFile, strTexturePath);
		if (!bFindFile)
		{
			CString strError;
			strError.Format ("Warning: The texture file %s could not be found in the search path.", 
				strTextureFile);
			AfxMessageBox (strError);
		}
		pCdmvTerrainData->SetCovering (strTextureFile, strTexturePath);	
	}
	else
	{
		// Invalid token
		CString strError = "Valid covering types are COLOR or TEXTURE";
		ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
		return FALSE;
	}

  // Wireframe Overlay
  BOOL WireframeOnOff;
  string strWireframeOnOff;
	istrmTerrainFile >> strLabel >> strWireframeOnOff;
	if (!istrmTerrainFile.good () || strLabel != "Wireframe")
	{
		ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
			"Expected: Wireframe <string> <RColor> <GColor> <BColor> <double> <double>");
		return FALSE;
	}
	if (strWireframeOnOff == "ON")
	{
		// Pick up the RGB values
		unsigned short sColor[3];
    double dLineWidth, dOffset;
		istrmTerrainFile >> sColor[0] >> sColor[1] >> sColor[2] >> dLineWidth >> dOffset;
		if (!istrmTerrainFile.good ())
		{
			ParseError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData,
				"Expected: Wireframe ON <RColor> <GColor> <BColor> <double> <double>");
			return FALSE;
		}
		// Validate the data
		if (sColor[0] < 0 || sColor[0] > 255 ||
			sColor[1] < 0 || sColor[1] > 255 ||
			sColor[2] < 0 || sColor[2] > 255)
		{
			CString strError;
			strError = "0 <= Color_element <= 255";
			ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
			return FALSE;		
		}
		// Save the data & draw
    WireframeOnOff = TRUE;
		COLORREF crWireframeColor = RGB (sColor[0], sColor[1], sColor[2]);
    pCdmvTerrainData->SetWireframeOverlay(WireframeOnOff);
    pCdmvTerrainData->SetWireframe(crWireframeColor, dLineWidth, dOffset);
    WTwindow_setdrawfn (WTuniverse_getwindows(), CWTKGraphics::WTKFGDrawTerrainGrid);
	}
  else if (strWireframeOnOff == "OFF")
	{
    WireframeOnOff = FALSE;
    pCdmvTerrainData->SetWireframeOverlay(WireframeOnOff);
  }
	else
	{
		// Invalid token
		CString strError = "Valid Wireframe status are ON or OFF";
		ValidationError (istrmTerrainFile, rnCurrentLineNumber, pCdmvTerrainData, strError);
		return FALSE;
	}

	istrmTerrainFile.close ();

	return TRUE;
}