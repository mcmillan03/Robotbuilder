// ParserModel.cpp: implementation of the CParserModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "ParserModel.h"
#include "PrimitiveSphere.h"
#include "PrimitiveBlock.h"
#include "PrimitiveCone.h"
#include "PrimitiveCylinder.h"
#include "PrimitiveHemisphere.h"
#include "PrimitiveTruncatedCone.h"
#include "FindFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


/*
Format Notes:

* Comments given by RB_COMMENT_CHAR
* Data lines must end with a newline (ie NOT an EOF at end of file)
* Lines cannont exceed RB_FILE_MAX_LINE - 1
* It's OK to have comments after the useful data.
* Most of these restrictions can be eased with by putting more time into coding
	if desired.

  */

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserModel::CParserModel()
{

}

CParserModel::~CParserModel()
{

}

// This will return NULL if it fails to open the file
// This news a CModel, so delete when done
BOOL CParserModel::ParseModelFile(CString strFilePath, CModel** ppModel)
{
	// Line number
	int nCurrentLineNumber = 1;

	// Make sure that the pointer to the CModel class is NULL because that
	// is used by the error handlers to determine if need to call deallocate the 
	// class on an error.
	*ppModel = NULL;

	// Open the file
	ifstream istrmModelFile (strFilePath);
	if (!istrmModelFile) 
	{
		CString strErrorMessage;
		strErrorMessage = _T("Failed to open the model file ") + strFilePath;
		AfxMessageBox (strErrorMessage);
		return FALSE;
	}

	// Advance to the first token in case it starts as blanks.
	if (!GotoNextData (istrmModelFile, nCurrentLineNumber))
	{
		FormatError(istrmModelFile, nCurrentLineNumber, 
			ppModel, "Error before first valid token.", strFilePath);
		return FALSE;
	}

   // Create the model
 	try {
		*ppModel = new CModel;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	string strLabel;
	int nFormatVersion; // Holds format version of file
	istrmModelFile >> strLabel >> nFormatVersion;

	if (!istrmModelFile.good () || strLabel != "Format:")
	{
		ParseError (istrmModelFile, nCurrentLineNumber, 
			ppModel, "Expected: Format: <integer>", strFilePath);
		return FALSE;
	}
	if (!GotoNextData (istrmModelFile, nCurrentLineNumber))
	{
		FormatError (istrmModelFile, nCurrentLineNumber, ppModel,
			"Error after Format field.", strFilePath);
		return FALSE;			
	}

	// Parse based on version
	if (nFormatVersion == 1)
	{
		// Read the background color
		int nRGBParts[3];
		istrmModelFile >> strLabel >> nRGBParts[0] >> nRGBParts[1] >> nRGBParts[2];
		if (!istrmModelFile.good () || strLabel != "BackgroundColor:")
		{
			ParseError (istrmModelFile, nCurrentLineNumber, ppModel,
				"Expected: BackgroundColor: <int> <int> <int>", strFilePath);
			return FALSE;
		}
		if (nRGBParts[0] < 0 || nRGBParts[0] > 255 ||
			nRGBParts[1] < 0 || nRGBParts[1] > 255 ||
			nRGBParts[2] < 0 || nRGBParts[2] > 255)
		{
			CString strError;
			strError = "0 <= Color <= 255";
			ValidationError (istrmModelFile, nCurrentLineNumber, ppModel, strError, strFilePath);
			return FALSE;
		}
		// Save the data
		(*ppModel)->SetBackgroundColor (RGB (nRGBParts[0], nRGBParts[1], nRGBParts[2]));
		if (!GotoNextData (istrmModelFile, nCurrentLineNumber))
		{
			FormatError (istrmModelFile, nCurrentLineNumber, ppModel, 
				"Error after BackgroundColor field.", strFilePath);
			return FALSE;			
		}

		// Read if need to override the automatically calculated physical data
		BOOL bUseUserSuppliedDataForPhysicalData;
		string strUseUserSuppliedDataForPhysicalData;
		istrmModelFile >> strLabel >> strUseUserSuppliedDataForPhysicalData;
		if (!istrmModelFile.good () || strLabel != "UseUserSuppliedDataForPhysicalData:")
		{
			ParseError (istrmModelFile, nCurrentLineNumber, ppModel,
				"Expected: UseUserSuppliedDataForPhysicalData: <BOOL>", strFilePath);
			return FALSE;
		}
		// Validate
		if (strUseUserSuppliedDataForPhysicalData != "TRUE" &&
			strUseUserSuppliedDataForPhysicalData != "FALSE")
		{
			CString strError;
			strError.Format ("Valid options are TRUE or FALSE for UseUserSuppliedDataForPhysicalData data.");
			ValidationError (istrmModelFile, nCurrentLineNumber, ppModel, strError, strFilePath);
			return FALSE;
		}
		// Save the data
		if (strUseUserSuppliedDataForPhysicalData == "TRUE")
			bUseUserSuppliedDataForPhysicalData = TRUE;
		else
			bUseUserSuppliedDataForPhysicalData = FALSE;
		(*ppModel)->UseUserSuppliedDataForPhysicalData (bUseUserSuppliedDataForPhysicalData);
		if (!GotoNextData (istrmModelFile, nCurrentLineNumber))
		{
			FormatError (istrmModelFile, nCurrentLineNumber, ppModel, 
				"Error after UseUserSuppliedDataForPhysicalData field.", strFilePath);
			return FALSE;			
		}

		// Read the number of primitives
		int nNumberOfPrimitives;
		istrmModelFile >> strLabel >> nNumberOfPrimitives;
		if (!istrmModelFile.good () || strLabel != "NumPrimitives:")
		{
			ParseError (istrmModelFile, nCurrentLineNumber, ppModel,
				"Expected: NumPrimitives: <integer>", strFilePath);
			return FALSE;
		}
		if (nNumberOfPrimitives < 0 || 
			nNumberOfPrimitives > 1e6)
		{
			CString strError;
			strError.Format ("%d <= NumPrimitives <= %d",
				0, 1e6);
			ValidationError (istrmModelFile, nCurrentLineNumber, ppModel, strError, strFilePath);
			return FALSE;
		}
		
		// Iterate through all of the primitives
		int nCounter = 0;
		while (nCounter < nNumberOfPrimitives)
		{
			// The end of the file shouldn't be encounter within this loop
			if (!GotoNextData (istrmModelFile, nCurrentLineNumber))
			{
				FormatError (istrmModelFile, nCurrentLineNumber, ppModel, 
					"Error before primitive description.", strFilePath);
				return FALSE;			
			}

			// Parse the type of primitive
			string strPrimitive;
			istrmModelFile >> strPrimitive;
			if (!GotoNextData (istrmModelFile, nCurrentLineNumber))
			{
				FormatError (istrmModelFile, nCurrentLineNumber, ppModel, 
					"Error after primitive type.", strFilePath);
				return FALSE;			
			}
			if (strPrimitive == "SPHERE")
			{
				if (!ParsePrimitiveSphere (ppModel, istrmModelFile, nCurrentLineNumber, strFilePath))
					return FALSE;
			}
			else if (strPrimitive == "CYLINDER")
			{
				if (!ParsePrimitiveCylinder (ppModel, istrmModelFile, nCurrentLineNumber, strFilePath))
					return FALSE;
			}
			else if (strPrimitive == "BLOCK")
			{
				if (!ParsePrimitiveBlock (ppModel, istrmModelFile, nCurrentLineNumber, strFilePath))
					return FALSE;
			}
			else if (strPrimitive == "CONE")
			{
				if (!ParsePrimitiveCone (ppModel, istrmModelFile, nCurrentLineNumber, strFilePath))
					return FALSE;
			}
			else if (strPrimitive == "HEMISPHERE")
			{
				if (!ParsePrimitiveHemisphere (ppModel, istrmModelFile, nCurrentLineNumber, strFilePath))
					return FALSE;
			}
			else if (strPrimitive == "TRUNCATED_CONE")
			{
				if (!ParsePrimitiveTruncatedCone (ppModel, istrmModelFile, nCurrentLineNumber, strFilePath))
					return FALSE;
			}
			else
			{
				ValidationError (istrmModelFile, nCurrentLineNumber, ppModel,
					"Unexpected token.  Valid tokens are {SPHERE, CYLINDER, BLOCK, CONE, HEMISPHERE, TRUNCATED_CONE}",
					strFilePath);
				return FALSE;
			}

			// Increment the current primitive count
			nCounter ++;
		}
	}
	else
	{
		// Unknown format
		FormatError (istrmModelFile, nCurrentLineNumber, ppModel, 
			"Unknown Format type.", strFilePath);
		return FALSE;			
	}

	return TRUE;
}
		

BOOL CParserModel::ParsePrimitiveSphere(CModel **ppModel, ifstream &istrmModelFile, int &rnCurrentLineNumber, CString strFile)
{

	// Add the new primitive to the model
	CPrimitiveSphere* pPrimitiveSphere = dynamic_cast <CPrimitiveSphere*> ((*ppModel)->NewPrimitive (PT_SPHERE));
	ASSERT (pPrimitiveSphere);

	// Parse the scale
	if (!ParsePrimitiveScale (pPrimitiveSphere->GetPrimitiveScale (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the placement
	if (!ParsePrimitivePlacement (pPrimitiveSphere->GetPrimitivePlacement (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the covering
	if (!ParsePrimitiveCovering (pPrimitiveSphere->GetPrimitiveCovering (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive name
	if (!ParsePrimitiveName (pPrimitiveSphere, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive mass
	if (!ParsePrimitiveMass (pPrimitiveSphere, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;


	// Parse the parameters specific to a sphere
	string strLabel;
	structPrimitiveSphereData strtPrimitiveSphereData;
	istrmModelFile >> strLabel >> strtPrimitiveSphereData.dRadius
		>> strtPrimitiveSphereData.nLatitudeCount
		>> strtPrimitiveSphereData.nLongitudeCount
		>> strtPrimitiveSphereData.bRenderBothSides
		>> strtPrimitiveSphereData.bUseGouraudShading;
	if (!istrmModelFile.good () || strLabel != "Parameters:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Parameters: <double> <int> <int> <int> <int>", strFile);
		return FALSE;
	}
	if (strtPrimitiveSphereData.dRadius < SPHERE_RADIUS_MIN || 
		strtPrimitiveSphereData.dRadius > SPHERE_RADIUS_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Radius <= %.2f",
			SPHERE_RADIUS_MIN, SPHERE_RADIUS_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	if (strtPrimitiveSphereData.nLatitudeCount < SPHERE_LATITUDE_COUNT_MIN || 
		strtPrimitiveSphereData.nLatitudeCount > SPHERE_LATITUDE_COUNT_MAX)
	{
		CString strError;
		strError.Format ("%d <= Latitude Count <= %d",
			SPHERE_LATITUDE_COUNT_MIN, SPHERE_LATITUDE_COUNT_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}	
	if (strtPrimitiveSphereData.nLatitudeCount < SPHERE_LONGITUDE_COUNT_MIN || 
		strtPrimitiveSphereData.nLatitudeCount > SPHERE_LONGITUDE_COUNT_MAX)
	{
		CString strError;
		strError.Format ("%d <= Longitude Count <= %d",
			SPHERE_LONGITUDE_COUNT_MIN, SPHERE_LONGITUDE_COUNT_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	// Don't GotoNextData.  It will be done when looping through each primitive and 
	// also makes it so that the EOF can be on a data line.


	pPrimitiveSphere->SetPrimitiveSphereData (&strtPrimitiveSphereData);

	return TRUE;
}


BOOL CParserModel::ParsePrimitiveBlock(CModel **ppModel, ifstream &istrmModelFile,
													int &rnCurrentLineNumber, CString strFile)
{
	// Add the new primitive to the model
	CPrimitiveBlock* pPrimitiveBlock = dynamic_cast <CPrimitiveBlock*> ((*ppModel)->NewPrimitive (PT_BLOCK));
	ASSERT (pPrimitiveBlock);

	// Parse the scale
	if (!ParsePrimitiveScale (pPrimitiveBlock->GetPrimitiveScale (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the placement
	if (!ParsePrimitivePlacement (pPrimitiveBlock->GetPrimitivePlacement (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the covering
	if (!ParsePrimitiveCovering (pPrimitiveBlock->GetPrimitiveCovering (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive name
	if (!ParsePrimitiveName (pPrimitiveBlock, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive mass
	if (!ParsePrimitiveMass (pPrimitiveBlock, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;

	// Parse the parameters specific to a block
	string strLabel;
	structPrimitiveBlockData strtPrimitiveBlockData;
	istrmModelFile >> strLabel >> strtPrimitiveBlockData.dLengthX
		>> strtPrimitiveBlockData.dLengthY
		>> strtPrimitiveBlockData.dLengthZ
		>> strtPrimitiveBlockData.bRenderBothSides;
	if (!istrmModelFile.good () || strLabel != "Parameters:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Parameters: <double> <double> <double> <int>", strFile);
		return FALSE;
	}
	if (strtPrimitiveBlockData.dLengthX < BLOCK_LENGTH_MIN || 
		strtPrimitiveBlockData.dLengthX > BLOCK_LENGTH_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Length X <= %.2f",
			BLOCK_LENGTH_MIN, BLOCK_LENGTH_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	if (strtPrimitiveBlockData.dLengthY < BLOCK_LENGTH_MIN || 
		strtPrimitiveBlockData.dLengthY > BLOCK_LENGTH_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Length Y <= %.2f",
			BLOCK_LENGTH_MIN, BLOCK_LENGTH_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}	
	if (strtPrimitiveBlockData.dLengthZ < BLOCK_LENGTH_MIN || 
		strtPrimitiveBlockData.dLengthZ > BLOCK_LENGTH_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Length Z <= %.2f",
			BLOCK_LENGTH_MIN, BLOCK_LENGTH_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	// Don't GotoNextData.  It will be done when looping through each primitive and 
	// also makes it so that the EOF can be on a data line.

	pPrimitiveBlock->SetPrimitiveBlockData (&strtPrimitiveBlockData);

	return TRUE;
}

BOOL CParserModel::ParsePrimitiveCylinder(CModel **ppModel, ifstream &istrmModelFile,
													int &rnCurrentLineNumber, CString strFile)
{
	// Add the new primitive to the model
	CPrimitiveCylinder* pPrimitiveCylinder = dynamic_cast <CPrimitiveCylinder*> ((*ppModel)->NewPrimitive (PT_CYLINDER));
	ASSERT (pPrimitiveCylinder);

	// Parse the scale
	if (!ParsePrimitiveScale (pPrimitiveCylinder->GetPrimitiveScale (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the placement
	if (!ParsePrimitivePlacement (pPrimitiveCylinder->GetPrimitivePlacement (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the covering
	if (!ParsePrimitiveCovering (pPrimitiveCylinder->GetPrimitiveCovering (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive name
	if (!ParsePrimitiveName (pPrimitiveCylinder, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive mass
	if (!ParsePrimitiveMass (pPrimitiveCylinder, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;

	// Parse the parameters specific to a cylinder
	string strLabel;
	structPrimitiveCylinderData strtPrimitiveCylinderData;
	istrmModelFile >> strLabel
		>> strtPrimitiveCylinderData.dHeight
		>> strtPrimitiveCylinderData.dRadius
		>> strtPrimitiveCylinderData.nTess
		>> strtPrimitiveCylinderData.bRenderBothSides
		>> strtPrimitiveCylinderData.bUseGouraudShading;
	if (!istrmModelFile.good () || strLabel != "Parameters:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Parameters: <double> <double> <int> <int> <int>", strFile);
		return FALSE;
	}
	if (strtPrimitiveCylinderData.dHeight < CYLINDER_HEIGHT_MIN || 
		strtPrimitiveCylinderData.dHeight > CYLINDER_HEIGHT_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Height <= %.2f",
			CYLINDER_HEIGHT_MIN, CYLINDER_HEIGHT_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	if (strtPrimitiveCylinderData.dRadius < CYLINDER_RADIUS_MIN || 
		strtPrimitiveCylinderData.dRadius > CYLINDER_RADIUS_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Radius <= %.2f",
			CYLINDER_RADIUS_MIN, CYLINDER_RADIUS_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}	
	if (strtPrimitiveCylinderData.nTess < CYLINDER_TESS_MIN || 
		strtPrimitiveCylinderData.nTess > CYLINDER_TESS_MAX)
	{
		CString strError;
		strError.Format ("%d <= Tesselation <= %d",
			CYLINDER_TESS_MIN, CYLINDER_TESS_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	// Don't GotoNextData.  It will be done when looping through each primitive and 
	// also makes it so that the EOF can be on a data line.

	pPrimitiveCylinder->SetPrimitiveCylinderData (&strtPrimitiveCylinderData);

	return TRUE;
}

BOOL CParserModel::ParsePrimitiveCone(CModel **ppModel, ifstream &istrmModelFile,
													int &rnCurrentLineNumber, CString strFile)
{
	// Add the new primitive to the model
	CPrimitiveCone* pPrimitiveCone = dynamic_cast <CPrimitiveCone*> ((*ppModel)->NewPrimitive (PT_CONE));
	ASSERT (pPrimitiveCone);

	// Parse the scale
	if (!ParsePrimitiveScale (pPrimitiveCone->GetPrimitiveScale (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the placement
	if (!ParsePrimitivePlacement (pPrimitiveCone->GetPrimitivePlacement (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the covering
	if (!ParsePrimitiveCovering (pPrimitiveCone->GetPrimitiveCovering (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive name
	if (!ParsePrimitiveName (pPrimitiveCone, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive mass
	if (!ParsePrimitiveMass (pPrimitiveCone, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;

	
	// Parse the parameters specific to a cone
	string strLabel;
	structPrimitiveConeData strtPrimitiveConeData;
	istrmModelFile >> strLabel
		>> strtPrimitiveConeData.dHeight
		>> strtPrimitiveConeData.dRadius
		>> strtPrimitiveConeData.nTess
		>> strtPrimitiveConeData.bRenderBothSides;
	if (!istrmModelFile.good () || strLabel != "Parameters:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Parameters: <double> <double> <int> <int>", strFile);
		return FALSE;
	}
	if (strtPrimitiveConeData.dHeight < CONE_HEIGHT_MIN || 
		strtPrimitiveConeData.dHeight > CONE_HEIGHT_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Height <= %.2f",
			CONE_HEIGHT_MIN, CONE_HEIGHT_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	if (strtPrimitiveConeData.dRadius < CONE_RADIUS_MIN || 
		strtPrimitiveConeData.dRadius > CONE_RADIUS_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Radius <= %.2f",
			CONE_RADIUS_MIN, CONE_RADIUS_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}	
	if (strtPrimitiveConeData.nTess < CONE_TESS_MIN || 
		strtPrimitiveConeData.nTess > CONE_TESS_MAX)
	{
		CString strError;
		strError.Format ("%d <= Tesselation <= %d",
			CONE_TESS_MIN, CONE_TESS_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	// Don't GotoNextData.  It will be done when looping through each primitive and 
	// also makes it so that the EOF can be on a data line.
	
	pPrimitiveCone->SetPrimitiveConeData (&strtPrimitiveConeData);

	return TRUE;
}

BOOL CParserModel::ParsePrimitiveHemisphere(CModel **ppModel, ifstream &istrmModelFile,
													int &rnCurrentLineNumber, CString strFile)
{
	// Add the new primitive to the model
	CPrimitiveHemisphere* pPrimitiveHemisphere = dynamic_cast <CPrimitiveHemisphere*> ((*ppModel)->NewPrimitive (PT_HEMISPHERE));
	ASSERT (pPrimitiveHemisphere);

	// Parse the scale
	if (!ParsePrimitiveScale (pPrimitiveHemisphere->GetPrimitiveScale (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the placement
	if (!ParsePrimitivePlacement (pPrimitiveHemisphere->GetPrimitivePlacement (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the covering
	if (!ParsePrimitiveCovering (pPrimitiveHemisphere->GetPrimitiveCovering (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive name
	if (!ParsePrimitiveName (pPrimitiveHemisphere, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive mass
	if (!ParsePrimitiveMass (pPrimitiveHemisphere, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;

	
	// Parse the parameters specific to a hemisphere
	string strLabel;
	structPrimitiveHemisphereData strtPrimitiveHemisphereData;
	istrmModelFile >> strLabel
		>> strtPrimitiveHemisphereData.dRadius
		>> strtPrimitiveHemisphereData.nLatitudeCount
		>> strtPrimitiveHemisphereData.nLongitudeCount
		>> strtPrimitiveHemisphereData.bRenderBothSides
		>> strtPrimitiveHemisphereData.bUseGouraudShading;
	if (!istrmModelFile.good () || strLabel != "Parameters:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Parameters: <double> <int> <int> <int> <int>", strFile);
		return FALSE;
	}
	if (strtPrimitiveHemisphereData.dRadius < HEMISPHERE_RADIUS_MIN || 
		strtPrimitiveHemisphereData.dRadius > HEMISPHERE_RADIUS_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Radius <= %.2f",
			HEMISPHERE_RADIUS_MIN, HEMISPHERE_RADIUS_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	if (strtPrimitiveHemisphereData.nLatitudeCount < HEMISPHERE_LATITUDE_MIN || 
		strtPrimitiveHemisphereData.nLatitudeCount > HEMISPHERE_LATITUDE_MAX)
	{
		CString strError;
		strError.Format ("%d <= Latitude Count <= %d",
			HEMISPHERE_LATITUDE_MIN, HEMISPHERE_LATITUDE_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}	
	if (strtPrimitiveHemisphereData.nLongitudeCount < HEMISPHERE_LONGITUDE_MIN || 
		strtPrimitiveHemisphereData.nLongitudeCount > HEMISPHERE_LONGITUDE_MAX)
	{
		CString strError;
		strError.Format ("%d <= Longitude Count <= %d",
			HEMISPHERE_LONGITUDE_MIN, HEMISPHERE_LONGITUDE_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	// Don't GotoNextData.  It will be done when looping through each primitive and 
	// also makes it so that the EOF can be on a data line.

	pPrimitiveHemisphere->SetPrimitiveHemisphereData (&strtPrimitiveHemisphereData);

	return TRUE;
}

BOOL CParserModel::ParsePrimitiveTruncatedCone(CModel **ppModel, ifstream &istrmModelFile,
													int &rnCurrentLineNumber, CString strFile)
{
	// Add the new primitive to the model
	CPrimitiveTruncatedCone* pPrimitiveTruncatedCone = dynamic_cast <CPrimitiveTruncatedCone*> ((*ppModel)->NewPrimitive (PT_TRUNCATED_CONE));
	ASSERT (pPrimitiveTruncatedCone);

	// Parse the scale
	if (!ParsePrimitiveScale (pPrimitiveTruncatedCone->GetPrimitiveScale (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the placement
	if (!ParsePrimitivePlacement (pPrimitiveTruncatedCone->GetPrimitivePlacement (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse the covering
	if (!ParsePrimitiveCovering (pPrimitiveTruncatedCone->GetPrimitiveCovering (), istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive name
	if (!ParsePrimitiveName (pPrimitiveTruncatedCone, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	// Parse primitive mass
	if (!ParsePrimitiveMass (pPrimitiveTruncatedCone, istrmModelFile, 
			ppModel, rnCurrentLineNumber, strFile))
		return FALSE;
	
	// Parse the parameters specific to a truncated cone
	string strLabel;
	structPrimitiveTruncatedConeData strtPrimitiveTruncatedConeData;
	istrmModelFile >> strLabel
		>> strtPrimitiveTruncatedConeData.dHeight
		>> strtPrimitiveTruncatedConeData.dTopRadius
		>> strtPrimitiveTruncatedConeData.dBaseRadius
		>> strtPrimitiveTruncatedConeData.nTess
		>> strtPrimitiveTruncatedConeData.bRenderBothSides
		>> strtPrimitiveTruncatedConeData.bUseGouraudShading;
	if (!istrmModelFile.good () || strLabel != "Parameters:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Parameters: <double> <double> <double> <int> <int> <int>", strFile);
		return FALSE;
	}
	if (strtPrimitiveTruncatedConeData.dHeight < TRUNCATED_CONE_HEIGHT_MIN || 
		strtPrimitiveTruncatedConeData.dHeight > TRUNCATED_CONE_HEIGHT_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Height <= %.2f",
			TRUNCATED_CONE_HEIGHT_MIN, TRUNCATED_CONE_HEIGHT_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	if (strtPrimitiveTruncatedConeData.dTopRadius < TRUNCATED_CONE_TOP_RADIUS_MIN || 
		strtPrimitiveTruncatedConeData.dTopRadius > TRUNCATED_CONE_TOP_RADIUS_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Top Radius <= %.2f",
			TRUNCATED_CONE_TOP_RADIUS_MIN, TRUNCATED_CONE_TOP_RADIUS_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	if (strtPrimitiveTruncatedConeData.dBaseRadius < TRUNCATED_CONE_BASE_RADIUS_MIN || 
		strtPrimitiveTruncatedConeData.dBaseRadius > TRUNCATED_CONE_BASE_RADIUS_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Base Radius <= %.2f",
			TRUNCATED_CONE_BASE_RADIUS_MIN, TRUNCATED_CONE_BASE_RADIUS_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}	
	if (strtPrimitiveTruncatedConeData.nTess < TRUNCATED_CONE_TESS_MIN || 
		strtPrimitiveTruncatedConeData.nTess > TRUNCATED_CONE_TESS_MAX)
	{
		CString strError;
		strError.Format ("%d <= Tesselation <= %d",
			TRUNCATED_CONE_TESS_MIN, TRUNCATED_CONE_TESS_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	// Don't GotoNextData.  It will be done when looping through each primitive and 
	// also makes it so that the EOF can be on a data line.
	
	pPrimitiveTruncatedCone->SetPrimitiveTruncatedConeData (&strtPrimitiveTruncatedConeData);

	return TRUE;
}

BOOL CParserModel::ParsePrimitiveMass (CPrimitive* pPrimitive, ifstream &istrmModelFile,
								 CModel **ppModel, int &rnCurrentLineNumber, CString strFile)
{
	ASSERT (AfxIsValidAddress (pPrimitive, sizeof(CPrimitive), TRUE));

	string strLabel;
	double dMass;

	istrmModelFile >> strLabel >> dMass;
	if (!istrmModelFile.good () || strLabel != "Mass:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Mass: <double>", strFile);
		return FALSE;
	}
	if (dMass < PRIMITIVE_MASS_MIN || dMass > PRIMITIVE_MASS_MAX)
	{
		CString strError;
		strError.Format ("%.2f <= Mass <= %.2f",
			PRIMITIVE_MASS_MIN, PRIMITIVE_MASS_MAX);
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	if (!GotoNextData (istrmModelFile, rnCurrentLineNumber))
	{
		FormatError (istrmModelFile, rnCurrentLineNumber, ppModel, 
			"Error after mass.", strFile);
		return FALSE;			
	}

	// Save the data
	pPrimitive->SetMass (dMass);

	return TRUE;
}


BOOL CParserModel::ParsePrimitiveScale(CPrimitiveScale *pPrimitiveScale, ifstream &istrmModelFile,
													CModel **ppModel, int &rnCurrentLineNumber, CString strFile)
{
	ASSERT (pPrimitiveScale);

	string strLabel;
	structPrimitiveScaleData strtPrimitiveScaleData;
	istrmModelFile >> strLabel >>
		strtPrimitiveScaleData.dXScale >> 
		strtPrimitiveScaleData.dYScale >> 
		strtPrimitiveScaleData.dZScale;
	if (!istrmModelFile.good () || strLabel != "Scale:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Scale: <double> <double> <double>", strFile);
		return FALSE;
	}
	if (strtPrimitiveScaleData.dXScale <= 0 ||
		strtPrimitiveScaleData.dYScale <= 0 ||
		strtPrimitiveScaleData.dZScale <= 0)
	{
		CString strError;
		strError.Format ("Scale can't be less than or equal to 0");
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}
	if (!GotoNextData (istrmModelFile, rnCurrentLineNumber))
	{
		FormatError (istrmModelFile, rnCurrentLineNumber, ppModel, 
			"Error after scale.", strFile);
		return FALSE;			
	}	

	pPrimitiveScale->SetPrimitiveScaleAbsoluteData (&strtPrimitiveScaleData);

	return TRUE;
}


void CParserModel::ParseError(ifstream &istrmModelFile, int nCurrentLineNumber,
						   CModel **ppModel, CString strMessage, CString strFile)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Parse error in model file (%s) on line %d.\n%s",
			strFile, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmModelFile.close ();
	if (*ppModel)
	{
		delete *ppModel;
		*ppModel = NULL;
	}
}

void CParserModel::FormatError(ifstream &istrmModelFile, int nCurrentLineNumber,
						   CModel **ppModel, CString strMessage, CString strFile)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Format error in model file (%s) on line %d.\n%s",
			strFile, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmModelFile.close ();
	if (*ppModel)
	{
		delete *ppModel;
		*ppModel = NULL;
	}
}


void CParserModel::ValidationError(ifstream &istrmModelFile, int nCurrentLineNumber,
						   CModel **ppModel, CString strMessage, CString strFile)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Validation error in model file (%s) on line %d.\n%s",
			strFile, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmModelFile.close ();
	if (*ppModel)
	{
		delete *ppModel;
		*ppModel = NULL;
	}
}

BOOL CParserModel::ParsePrimitivePlacement(CPrimitivePlacement *pPrimitivePlacement, ifstream &istrmModelFile,
													CModel **ppModel, int &rnCurrentLineNumber, CString strFile)
{

	string strLabel;
	structPrimitivePlacementData strtPrimitivePlacementData;
	istrmModelFile >> strLabel >>
		strtPrimitivePlacementData.dTranslationX >> 
		strtPrimitivePlacementData.dTranslationY >> 
		strtPrimitivePlacementData.dTranslationZ;
	if (!istrmModelFile.good () || strLabel != "Translation:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Translation: <double> <double> <double>", strFile);
		return FALSE;
	}
	if (!GotoNextData (istrmModelFile, rnCurrentLineNumber))
	{
		FormatError (istrmModelFile, rnCurrentLineNumber, ppModel, 
			"Error after translation field.", strFile);
		return FALSE;			
	}	
	istrmModelFile >> strLabel >>
		strtPrimitivePlacementData.dRotationMatrix[0][0] >> 
		strtPrimitivePlacementData.dRotationMatrix[0][1] >> 
		strtPrimitivePlacementData.dRotationMatrix[0][2];
	if (!istrmModelFile.good () || strLabel != "Rotation:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Rotation: <double> <double> <double>", strFile);
		return FALSE;
	}
	if (!GotoNextData (istrmModelFile, rnCurrentLineNumber))
	{
		FormatError (istrmModelFile, rnCurrentLineNumber, ppModel, 
			"Error after rotation field.", strFile);
		return FALSE;			
	}	
	istrmModelFile >> 
		strtPrimitivePlacementData.dRotationMatrix[1][0] >> 
		strtPrimitivePlacementData.dRotationMatrix[1][1] >> 
		strtPrimitivePlacementData.dRotationMatrix[1][2];
	if (!istrmModelFile.good ())
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: <double> <double> <double>", strFile);
		return FALSE;
	}
	if (!GotoNextData (istrmModelFile, rnCurrentLineNumber))
	{
		FormatError (istrmModelFile, rnCurrentLineNumber, ppModel, 
			"Error after rotation field.", strFile);
		return FALSE;			
	}
	istrmModelFile >> 
		strtPrimitivePlacementData.dRotationMatrix[2][0] >> 
		strtPrimitivePlacementData.dRotationMatrix[2][1] >> 
		strtPrimitivePlacementData.dRotationMatrix[2][2];
	if (!istrmModelFile.good ())
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: <double> <double> <double>", strFile);
		return FALSE;
	}
	if (!GotoNextData (istrmModelFile, rnCurrentLineNumber))
	{
		FormatError (istrmModelFile, rnCurrentLineNumber, ppModel, 
			"Error after rotation field.", strFile);
		return FALSE;			
	}
	
	pPrimitivePlacement->SetPrimitivePlacementData (&strtPrimitivePlacementData);

	return TRUE;
}

BOOL CParserModel::ParsePrimitiveCovering(CPrimitiveCovering *pPrimitiveCovering, ifstream &istrmModelFile,
													CModel **ppModel, int &rnCurrentLineNumber, CString strFile)
{
	ASSERT (pPrimitiveCovering);

	string strLabel, strCoveringType;
	istrmModelFile >> strLabel >> strCoveringType;
	if (!istrmModelFile.good () || strLabel != "Covering:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Covering: <string> ...", strFile);
		return FALSE;
	}
	if (strCoveringType == "SIMPLE_COLOR")
	{
		int nRGBParts[3];
		istrmModelFile >> nRGBParts[0] >> nRGBParts[1] >> nRGBParts[2];
		if (!istrmModelFile.good ())
		{
			ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
				"Expected: Covering: SIMPLE_COLOR <int> <int> <int>", strFile);
			return FALSE;
		}
		if (nRGBParts[0] < 0 || nRGBParts[0] > 255 ||
			nRGBParts[1] < 0 || nRGBParts[1] > 255 ||
			nRGBParts[2] < 0 || nRGBParts[2] > 255)
		{
			CString strError;
			strError = "0 <= Color <= 255";
			ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
			return FALSE;
		}
		if (!GotoNextData (istrmModelFile, rnCurrentLineNumber))
		{
			FormatError (istrmModelFile, rnCurrentLineNumber, ppModel, 
				"Error after covering field.", strFile);
			return FALSE;			
		}	
		// Build the struct to pass the data
		structPrimitiveCoveringData strtPrimitiveCoveringData;
		strtPrimitiveCoveringData.covCovering = SIMPLE_COLOR;
		strtPrimitiveCoveringData.crColor = RGB (nRGBParts[0],
			nRGBParts[1], nRGBParts[2]);
		pPrimitiveCovering->SetPrimitiveCoveringData (&strtPrimitiveCoveringData);	
	}
	else if (strCoveringType == "TEXTURE")
	{
		string strTexture;
		if (!ReadStringInDoubleQuotes (istrmModelFile, strTexture))
		{
			ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
				"Expected: Covering: TEXTURE \"<string>\"", strFile);
			return FALSE;
		}
		if (!GotoNextData (istrmModelFile, rnCurrentLineNumber))
		{
			FormatError (istrmModelFile, rnCurrentLineNumber, ppModel, 
				"Error after covering field.", strFile);
			return FALSE;			
		}	

		CString strTexturePath = "";
		CString strTextureFile = strTexture.c_str ();
		BOOL bFindFile = CFindFile::FindFile (TEXTURE_FILE_TYPE, 
			strTextureFile, strTexturePath);
		if (!bFindFile)
		{
			CString strError;
			strError.Format ("Warning: The texture file %s could not be found in the search path.",
				strTextureFile);
			AfxMessageBox (strError);
		}
		
		// Build the struct to pass the data
		structPrimitiveCoveringData strtPrimitiveCoveringData;
		strtPrimitiveCoveringData.covCovering = TEXTURE;
		strtPrimitiveCoveringData.strTextureFile = strTextureFile;
		strtPrimitiveCoveringData.strTexturePath = strTexturePath;
		pPrimitiveCovering->SetPrimitiveCoveringData (&strtPrimitiveCoveringData);
	}
	else
	{
		CString strError;
		strError =  "Unexpected token.  Valid tokens are {SIMPLE_COLOR, TEXTURE}.";
		ValidationError (istrmModelFile, rnCurrentLineNumber, ppModel, strError, strFile);
		return FALSE;
	}

	return TRUE;
}

BOOL CParserModel::ParsePrimitiveName(CPrimitive *pPrimitive, ifstream &istrmModelFile,
													CModel **ppModel, int &rnCurrentLineNumber, CString strFile)
{
	string strLabel, strName;
	istrmModelFile >> strLabel;
	if (!istrmModelFile.good () || strLabel != "Name:")
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Name: \"<string>\"", strFile);
		return FALSE;
	}
	if (!ReadStringInDoubleQuotes (istrmModelFile, strName))
	{
		ParseError (istrmModelFile, rnCurrentLineNumber, ppModel,
			"Expected: Name: \"<string>\"", strFile);
		return FALSE;
	}
	if (!GotoNextData (istrmModelFile, rnCurrentLineNumber))
	{
		FormatError (istrmModelFile, rnCurrentLineNumber, ppModel, 
			"Error after name field.", strFile);
		return FALSE;			
	}	

	// Now add name to primitive
	pPrimitive->SetName (strName.c_str ());

	// Parsed name successfully
	return TRUE;
}