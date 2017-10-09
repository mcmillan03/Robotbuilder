// ParserDM.cpp: implementation of the CParserDM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "ParserDM.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "dmvArticulationData.h"
#include "dmvStaticRootLinkData.h"
#include "dmvMobileBaseLinkData.h"
#include "dmvRevoluteLinkData.h"
#include "dmvPrismaticLinkData.h"
#include "dmvSphericalLinkData.h"
#include "dmvZScrewTxLinkData.h"
#include "dmvContactModelData.h"
#include "dmvSecRevJntData.h"
#include "FindFile.h"
#include <Model.h>
#include <ParserModel.h>



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CParserDM::CParserDM()
{

}

CParserDM::~CParserDM()
{

}

// The parser will allocate the CdmvSystemData class.  If the parsing fails,
// it will take care of deallocating the class
BOOL CParserDM::ParseDMFile(CString strFile, CdmvSystemData **ppCdmvSystemData)
{
	// Line number
	int nCurrentLineNumber = 1;

	// Make sure that the pointer to the CdmvSystemData class is NULL because that
	// is used by the error handlers to determine if need to call deallocate the 
	// class on an error.
	*ppCdmvSystemData = NULL;

	// Open the file
	ifstream istrmDMFile (strFile);
	if (!istrmDMFile) 
	{
		AfxMessageBox ("Failed to open DM file.");
		return FALSE;
	}

	// Advance to the first token in case it starts as blanks.
	if (!GotoNextData (istrmDMFile, nCurrentLineNumber))
	{
		FormatError(istrmDMFile, nCurrentLineNumber, 
			ppCdmvSystemData, "Error before first valid token.");
		return FALSE;
	}

	// 14 MAY 2002 - Removed version number to be compatible with DynaMechs.
//	// The first real line will be the format type
//	string strLabel;
//	int nFormatVersion; // Holds format version of file
//	istrmDMFile >> strLabel >> nFormatVersion;
//
//	if (!istrmDMFile.good () || strLabel != "Version")
//	{
//		ParseError (istrmDMFile, nCurrentLineNumber, 
//			ppCdmvSystemData, "Expected: Version <integer>");
//		return FALSE;
//	}
//	if (!GotoNextData (istrmDMFile, nCurrentLineNumber))
//	{
//		FormatError (istrmDMFile, nCurrentLineNumber, ppCdmvSystemData,
//			"after Version field.");
//		return FALSE;			
//	}
//	
//	// Call the correct procedure to parse the detected version type.
//	switch (nFormatVersion)
//	{
//	case 1:
		if (!ParseFileVersion1 (istrmDMFile, nCurrentLineNumber, ppCdmvSystemData))
		{
			return FALSE;
		}
//		break;
//	default:
//		AfxMessageBox ("Unsupported version of DM file.");
//		return FALSE;
//	}

	// Make sure the articulation is valid
	int nResult = dynamic_cast<CdmvArticulationData*> (*ppCdmvSystemData)->ValidateArticulation ();
	if (nResult == CdmvArticulationData::ART_ERROR_TOO_MANY_STATIC_ROOT_LINK)
	{
		CString strErrorMessage;
		strErrorMessage = "There can only be one static root link in an articulation.";
		ValidationError (istrmDMFile, nCurrentLineNumber, ppCdmvSystemData, strErrorMessage);
	}
	else if (nResult == CdmvArticulationData::ART_ERROR_STATIC_ROOT_LINK_BAD_PLACE)
	{
		CString strErrorMessage;
		strErrorMessage = "The static root link can only be a child of the articulation base.";
		ValidationError (istrmDMFile, nCurrentLineNumber, ppCdmvSystemData, strErrorMessage);
	}
	else if (nResult != CdmvArticulationData::ART_ERROR_NONE)
	{
		ASSERT (FALSE);
	}
	// If get here then validated all right.

		
	// Close the stream
	istrmDMFile.close ();

	return TRUE;
}

void CParserDM::ParseError(ifstream &istrmDMFile, int nCurrentLineNumber,
						   CdmvSystemData **ppCdmvSystemData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Parse error in DM file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmDMFile.close ();
	if (*ppCdmvSystemData)
	{
		delete *ppCdmvSystemData;
		*ppCdmvSystemData = NULL;
	}
}

void CParserDM::FormatError(ifstream &istrmDMFile, int nCurrentLineNumber,
						   CdmvSystemData **ppCdmvSystemData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Format error in DM file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmDMFile.close ();
	if (*ppCdmvSystemData)
	{
		delete *ppCdmvSystemData;
		*ppCdmvSystemData = NULL;
	}
}


void CParserDM::ValidationError(ifstream &istrmDMFile, int nCurrentLineNumber,
						   CdmvSystemData **ppCdmvSystemData, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Validation error in DM file on line %d.\n%s",
			nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmDMFile.close ();
	if (*ppCdmvSystemData)
	{
		delete *ppCdmvSystemData;
		*ppCdmvSystemData = NULL;
	}
}

BOOL CParserDM::ParseFileVersion1(ifstream &istrmDMFile, int & rnCurrentLineNumber,
								  CdmvSystemData **ppCdmvSystemData)
{
	string strLabel; // Holder for the data labels

	// Read the articulation type
	string strArticulationType;
	istrmDMFile >> strArticulationType;
	if (!istrmDMFile.good ())
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, 
			ppCdmvSystemData, "Expected: <articulation_type_string>");
		return FALSE;
	}
	// Move to the next data
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, 
			ppCdmvSystemData, "Error after articulation type.");
		return FALSE;			
	}
	if (strArticulationType == "Articulation")
	{
		return ParseArticulation (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
	}
	else if (strArticulationType == "ClosedArticulation")
	{
		return ParseClosedArticulation (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
	}
	else
	{
		// Invalid articulation specified
		ValidationError (istrmDMFile, rnCurrentLineNumber, 
			ppCdmvSystemData,
			"<articulation_type_string> (where articulation_type_string is in {Articulation, ClosedArticulation})");
		return FALSE;
	}
}




BOOL CParserDM::ParseArticulation(ifstream &istrmDMFile, int & rnCurrentLineNumber,
								  CdmvSystemData **ppCdmvSystemData)
{
	try {
		*ppCdmvSystemData = new CdmvArticulationData;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	if (!ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData))
		return FALSE;

	// Parse the name
	if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
		dynamic_cast<CdmvObject*> (*ppCdmvSystemData)))
		return FALSE;

	// Parse the graphic
	if (!ParseGraphicsFile (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
		dynamic_cast<CdmvObject*> (*ppCdmvSystemData)))
		return FALSE;

	// Parse pose.
	if (!ParseArticulationPose (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
		dynamic_cast<CdmvArticulationData*> (*ppCdmvSystemData)))
		return FALSE;

	// There have to be links.
	return ParseLinkBranch (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, NULL);
}



BOOL CParserDM::ParseClosedArticulation(ifstream &istrmDMFile, int & rnCurrentLineNumber,
										CdmvSystemData **ppCdmvSystemData)
{
	try {
		*ppCdmvSystemData = new CdmvArticulationData;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	if (!ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData))
		return FALSE;

	// Name
	if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, *ppCdmvSystemData))
		return FALSE;

	// Graphics Model
	if (!ParseGraphicsFile (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, *ppCdmvSystemData))
		return FALSE;

	// Pose
	if (!ParseArticulationPose (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
		dynamic_cast<CdmvArticulationData*> (*ppCdmvSystemData)))
		return FALSE;

	string strLabel;
	// Next there is a label indicating the beginning of the tree structure definition
	istrmDMFile >> strLabel;
	if (!istrmDMFile.good () || strLabel != "TreeStructure")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: TreeStructure");
		return FALSE;
	}

	if (!ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData))
		return FALSE;

	if (!ParseLinkBranch (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, NULL))
		return FALSE;

	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Orientation_Quat field.");
		return FALSE;			
	}

	// Load in the secondary joints
	// Next there is a label indicating the beginning of the tree structure definition
	istrmDMFile >> strLabel;
	if (!istrmDMFile.good () || strLabel != "SecondaryJoints")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: SecondaryJoints");
		return FALSE;
	}

	if (!ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData))
		return FALSE;

	// This also parses the closing brace
	if (!ParseSecondaryJoints (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
		dynamic_cast<CdmvArticulationData*> (*ppCdmvSystemData)))
		return FALSE;

	return TRUE;
}

BOOL CParserDM::ParseGraphicsFile(ifstream &istrmDMFile, int & rnCurrentLineNumber, 
								  CdmvSystemData **ppCdmvSystemData, CdmvObject* pCdmvObject)
{
	string strLabel, stringGraphicsFile;
	istrmDMFile >> strLabel;

	if (!ReadStringInDoubleQuotes (istrmDMFile, stringGraphicsFile))
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Graphics_Model \"<string>\"");
		return FALSE;
	}
	if (!istrmDMFile.good () || strLabel != "Graphics_Model")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Graphics_Model \"<string>\"");
		return FALSE;
	}
	// Check to see if the file can be found
	CString strModelPath = "";
	CString strModelFile = stringGraphicsFile.c_str ();
	// Check if a file was specified before checking if it exists
	if (strModelFile.GetLength () > 0)
	{
		BOOL bFindFile = CFindFile::FindFile (MODEL_FILE_TYPE, 
			strModelFile, strModelPath);
		if (!bFindFile)
		{
			CString strError;
			strError.Format ("Warning: The model file %s could not be found in the search path.", 
				strModelFile);
			AfxMessageBox (strError);
		}
		else
		{
			// Found file.
			// Check if it is an .rbm file
			CString strFileType = strModelFile.Right (4);
			// Make caps for case insensitive compare
			strFileType.MakeUpper ();
			if (strFileType == _T(".RBM"))
			{
				// Then the graphics file is .rbm file

				// Now determine if the object type is one that needs the physical parameters
				// in the .rmb file
				if (pCdmvObject->GetObjectType () == LINK)
				{
					// Get a copy of the link pointer
					CdmvLinkData* pLink = dynamic_cast <CdmvLinkData*> (pCdmvObject);

					// Check if this a link that has physical paramters
					if (pLink->GetLinkType () == MOBILE_BASE_LINK || pLink->GetLinkType () == PRISMATIC_LINK ||
						pLink->GetLinkType () == REVOLUTE_LINK || pLink->GetLinkType () == SPHERICAL_LINK)
					{
						// Then this link has physical parameters that should be read from
						// the .rbm file.  Note that the dm parser will still parse
						// the physical parameters from the .dm file, but if valid data
						// can be retrieved from the .rbm file, the .dm data will be discarded.

						// Attempt to parse the model file
						CModel* pModel;
						if (CParserModel::ParseModelFile (strModelPath + strModelFile, &pModel))
						{
							// Then successfully parsed the model file
							
							// Check if need to calculate the interial data or use the user
							// specified data
							if (!pModel->UseUserSuppliedDataForPhysicalData ())
							{

								// Tell RB that the data from the .rbm file should be used
								pCdmvObject->UseRbmData (TRUE);

								//// Save the data
								// Save it in a structure
								structRigidBodyInertialParameters strtRigidBodyInertialParameters;
								strtRigidBodyInertialParameters.fMass = pModel->GetModelMass ();
								
								double dCenterOfGravity[3];
								pModel->GetModelCenterOfGravity (dCenterOfGravity);
								
								double dInertia[3][3];
								pModel->GetModelInertia (dInertia);
								
								int i, j;
								for (i = 0; i < 3; i ++)
								{
									for (j = 0; j < 3; j++)
									{
										strtRigidBodyInertialParameters.ctIbar[i][j] = dInertia[i][j];
									}
									strtRigidBodyInertialParameters.cvCenterGravityPosition[i] = dCenterOfGravity[i];
								}

								// Get a copy of the pointer to the RigidBodyData
								CdmvRigidBodyData* pRigidBodyData = dynamic_cast <CdmvRigidBodyData*> (pLink);
								pRigidBodyData->SetInertialParameters (&strtRigidBodyInertialParameters);
							}
							else
							{
								// Tell RB to not use the data from the .rbm file
								pCdmvObject->UseRbmData (FALSE);

							}
						}
						else
						{
							// Then failed to parse the model file.  Consequently, will not use
							// the parameter data from the .rbm file, but will use the data
							// from the .dm file
							CString strError;
							strError.Format ("Warning: The model file %s could not be parsed.\nRobotBuilder will revert to using the physical parameters from the .dm file.", 
								strModelFile);
							AfxMessageBox (strError);

						}

					}
				}
			}
		}
	}
	pCdmvObject->SetGraphicsModel (strModelFile, strModelPath);
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Graphics_Model field.");
		return FALSE;			
	}

	return TRUE;
}

BOOL CParserDM::ParseArticulationPose(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
									  CdmvSystemData **ppCdmvSystemData, CdmvArticulationData *pCdmvArticulationData)
{
	ASSERT (pCdmvArticulationData);

	string strLabel;
	CartesianVector vPosition;

	istrmDMFile >> strLabel >> vPosition[X] >> vPosition[Y] >> vPosition[Z];

	if (!istrmDMFile.good () || strLabel != "Position")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Position <float> <float> <float>");
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Position field.");
		return FALSE;			
	}


	// Orientation Quaternion
	Quaternion qOrientation;

	istrmDMFile >> strLabel >> qOrientation[X] >> qOrientation[Y] >> qOrientation[Z] >>
		qOrientation[W];

	if (!istrmDMFile.good () || strLabel != "Orientation_Quat")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Orientation_Quat <float> <float> <float> <float>");
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Orientation_Quat field.");
		return FALSE;			
	}

	pCdmvArticulationData->SetReferenceSystem (qOrientation, vPosition);

	return TRUE;
}

BOOL CParserDM::ParseLinkBranch(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
								CdmvSystemData **ppCdmvSystemData, CdmvLinkData *pParentLink)
{

	for (;;)
	{	
		// Get next token
		string strToken;
		istrmDMFile >> strToken;
		
		// Check for the end token first (because can't call GotoNextData because there
		// might not be data after it.
		if (strToken == "}")
		{
			// Goto the next data, but don't error out.  This way, if the parser is
			// at the end of the file, it won't throw an error if there is no
			// ending newline
			GotoNextData (istrmDMFile, rnCurrentLineNumber);
			// End of block so stop parsing at this level
			return TRUE;
		}
		
		// Advance to next token
		if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
		{
			FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				"");
			return FALSE;			
		}

		if (strToken == "Branch")
		{
			if (!ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData))
				return FALSE;

			if (!ParseLinkBranch (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, pParentLink))
				return FALSE;
		}

		else if (strToken == "StaticRootLink")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvStaticRootLinkData *pLink;
			// Allocate a new link
			try {
				pLink = new CdmvStaticRootLinkData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pLink)))
				return FALSE;

			if (!ParseGraphicsFile (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				dynamic_cast<CdmvObject*> (pLink)))
				return FALSE;

			ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);

			(dynamic_cast<CdmvArticulationData*> (*ppCdmvSystemData))->AddLink (pLink, pParentLink);
			
			pParentLink = pLink;
		}
		else if (strToken == "MobileBaseLink")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvMobileBaseLinkData *pLink;
			// Allocate a new link
			try {
				pLink = new CdmvMobileBaseLinkData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pLink)))
				return FALSE;

			if (!ParseGraphicsFile (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				dynamic_cast<CdmvObject*> (pLink)))
				return FALSE;

			if (!ParseRigidBodyParameters (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pLink))
				return FALSE;

			if (!ParseMobileBaseParameters (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pLink))
				return FALSE;			

			ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);

			(dynamic_cast<CdmvArticulationData*> (*ppCdmvSystemData))->AddLink (pLink, pParentLink);
			
			pParentLink = pLink;
		}
		else if (strToken == "RevoluteLink")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvRevoluteLinkData *pLink;
			// Allocate a new link
			try {
				pLink = new CdmvRevoluteLinkData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pLink)))
				return FALSE;

			if (!ParseGraphicsFile (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				dynamic_cast<CdmvObject*> (pLink)))
				return FALSE;

			if (!ParseRigidBodyParameters (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pLink))
				return FALSE;

			if (!ParseMDHParameters (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pLink))
				return FALSE;			

			if (!ParseActuator (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, pLink))
				return FALSE;
			
			ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);

			(dynamic_cast<CdmvArticulationData*> (*ppCdmvSystemData))->AddLink (pLink, pParentLink);
			
			pParentLink = pLink;
		}
		else if (strToken == "PrismaticLink")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvPrismaticLinkData *pLink;
			// Allocate a new link
			try {
				pLink = new CdmvPrismaticLinkData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pLink)))
				return FALSE;

			if (!ParseGraphicsFile (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				dynamic_cast<CdmvObject*> (pLink)))
				return FALSE;

			if (!ParseRigidBodyParameters (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pLink))
				return FALSE;

			if (!ParseMDHParameters (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pLink))
				return FALSE;			

			if (!ParseJointFriction (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, pLink))
				return FALSE;
			
			ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);

			(dynamic_cast<CdmvArticulationData*> (*ppCdmvSystemData))->AddLink (pLink, pParentLink);
			
			pParentLink = pLink;
		}
		else if (strToken == "SphericalLink")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvSphericalLinkData *pLink;
			// Allocate a new link
			try {
				pLink = new CdmvSphericalLinkData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pLink)))
				return FALSE;

			if (!ParseGraphicsFile (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				dynamic_cast<CdmvObject*> (pLink)))
				return FALSE;

			if (!ParseRigidBodyParameters (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pLink))
				return FALSE;

			if (!ParseSphericalLinkParameters (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pLink))
				return FALSE;			

			if (!ParseJointFriction (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, pLink))
				return FALSE;
			
			ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);

			(dynamic_cast<CdmvArticulationData*> (*ppCdmvSystemData))->AddLink (pLink, pParentLink);
			
			pParentLink = pLink;
		}
		else if (strToken == "ZScrewTxLink")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvZScrewTxLinkData *pLink;
			// Allocate a new link
			try {
				pLink = new CdmvZScrewTxLinkData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pLink)))
				return FALSE;

			if (!ParseZScrewTxLinkParameters (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, pLink))
				return FALSE;
			
			ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);

			(dynamic_cast<CdmvArticulationData*> (*ppCdmvSystemData))->AddLink (pLink, pParentLink);
			
			pParentLink = pLink;
		}
		else
		{
			ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				"Unexpected token.  Valid tokens are {Branch, StaticRootLink, MobileBaseLink, RevoluteLink, PrismaticLink, SphericalLink, ZScrewTxLink, } (Brace to show end of block)}");
			return FALSE;
		}
	}
}

BOOL CParserDM::ParseToBlockBegin(ifstream &istrmDMFile, int &rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData)
{
	// We should already be advanced to the next token

	// The next token should be the begin block character {

	string strBeginBlock;

	istrmDMFile >> strBeginBlock;

	if (strBeginBlock != "{")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: {");
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after {.");
		return FALSE;			
	}

	return TRUE;
}

BOOL CParserDM::ParseName(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
						  CdmvSystemData **ppCdmvSystemData, CdmvObject *pCdmvObject)
{
	// Parse the name
	string strLabel, strName;
	istrmDMFile >> strLabel;
	if (!ReadStringInDoubleQuotes (istrmDMFile, strName))
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Name \"<string>\"");
		return FALSE;
	}
	if (!istrmDMFile.good () || strLabel != "Name")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Name \"<string>\"");
		return FALSE;
	}
	pCdmvObject->SetName (strName.c_str ());
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Name field.");
		return FALSE;			
	}

	return TRUE;
}

BOOL CParserDM::ParseToBlockEnd(ifstream &istrmDMFile, int &rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData)
{
	// We should already be advanced to the next token

	// The next token should be the end block character }

	string strEndBlock;

	istrmDMFile >> strEndBlock;

	if (strEndBlock != "}")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: }");
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after }.");
		return FALSE;			
	}

	return TRUE;
}

BOOL CParserDM::ParseRigidBodyParameters(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
										 CdmvSystemData **ppCdmvSystemData, CdmvRigidBodyData *pCdmvRigidBodyData)
{

	double dMass;
	string strLabel;

	// Mass
	istrmDMFile >> strLabel >> dMass;
	if (!istrmDMFile.good () || strLabel != "Mass")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Mass <float>");
		return FALSE;
	}
	if (dMass < LINK_MASS_MIN || dMass > LINK_MASS_MAX)
	{
		CString strError;
		strError.Format ("%f <= Mass <= %.1f",
			LINK_MASS_MIN, LINK_MASS_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Mass field.");
		return FALSE;			
	}

	// Inertia
	CartesianTensor ctIbar;
	istrmDMFile >> strLabel;
	if (!istrmDMFile.good () || strLabel != "Inertia")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Inertia <float> <float> <float>\n\t<float> <float> <float>\n\t<float> <float> <float>");
		return FALSE;
	}
	int i,j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			istrmDMFile >> ctIbar[i][j];
			if (!istrmDMFile.good ())
			{
				ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
					"Expected: Inertia <float> <float> <float>\n\t<float> <float> <float>\n\t<float> <float> <float>");
				return FALSE;
			}
			if (i == j)
			{
				if (ctIbar[i][j] < LINK_INERTIA_DIAGONAL_MIN || ctIbar[i][j] > LINK_INERTIA_DIAGONAL_MAX)
				{
					CString strError;
					strError.Format ("%.1f <= Inertia <= %.1f",
						LINK_INERTIA_DIAGONAL_MIN, LINK_INERTIA_DIAGONAL_MAX);
					ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
					return FALSE;
				}
			}
		}
		if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
		{
			FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				"Error after Inertia field.");
			return FALSE;			
		}
	}


	// Center of Gravity
	CartesianVector cvCOG;
	istrmDMFile >> strLabel >> cvCOG[0] >> cvCOG[1] >> cvCOG[2];
	if (!istrmDMFile.good () || strLabel != "Center_of_Gravity")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Center_of_Gravity <float> <float> <float>");
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Center_of_Gravity field.");
		return FALSE;			
	}

	// Only save the data if there isn't a valid .rbm file parsed (otherwise this 
	// would overwrite it)
	if (!(dynamic_cast<CdmvObject*> (pCdmvRigidBodyData))->UseRbmData ())
		pCdmvRigidBodyData->SetInertiaParameters (dMass, ctIbar, cvCOG);

	if (!ParseContactParameters(istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, pCdmvRigidBodyData))	
		return FALSE;

	// Everything parsed OK so return TRUE
	return TRUE;
}

BOOL CParserDM::ParseMobileBaseParameters(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
										  CdmvSystemData **ppCdmvSystemData, 
										  CdmvMobileBaseLinkData *pCdmvMobileBaseLinkData)
{

	ASSERT (pCdmvMobileBaseLinkData);

	string strLabel;
	CartesianVector cvPosition;

	istrmDMFile >> strLabel >> cvPosition[X] >> cvPosition[Y] >> cvPosition[Z];

	if (!istrmDMFile.good () || strLabel != "Position")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Position <float> <float> <float>");
		return FALSE;
	}
	// No validation
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Position field.");
		return FALSE;			
	}


	// Orientation Quaternion
	Quaternion qOrientation;
	istrmDMFile >> strLabel >> qOrientation[X] >> qOrientation[Y] >> qOrientation[Z] >>
		qOrientation[W];

	if (!istrmDMFile.good () || strLabel != "Orientation_Quat")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Orientation_Quat <float> <float> <float> <float>");
		return FALSE;
	}
	// No validation
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Orientation_Quat field.");
		return FALSE;			
	}

	// Derivative of state.
	SpatialVector svVelocity;
	istrmDMFile >> strLabel >> svVelocity[0] >> svVelocity[1] >> svVelocity[2] >>
		svVelocity[3] >> svVelocity[4] >> svVelocity[5] ;

	if (!istrmDMFile.good () || strLabel != "Velocity")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Velocity <float> <float> <float> <float> <float> <float>");
		return FALSE;
	}
	// No validation
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Velocity field.");
		return FALSE;			
	}
	
	pCdmvMobileBaseLinkData->SetInitialState (cvPosition, qOrientation, svVelocity);

	return TRUE;
}

BOOL CParserDM::ParseContactParameters(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
									   CdmvSystemData **ppCdmvSystemData, CdmvRigidBodyData *pCdmvRigidBodyData)
{
	// Number of contact points
	string strLabel;
	int nNumberOfContactPoints;
	istrmDMFile >> strLabel >> nNumberOfContactPoints;
	if (!istrmDMFile.good () || strLabel != "Number_of_Contact_Points")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Number_of_Contact_Points <integer>");
		return FALSE;
	}
	if (nNumberOfContactPoints < RIGID_BODY_NUM_CONTACTS_MIN || 
		nNumberOfContactPoints > RIGID_BODY_NUM_CONTACTS_MAX)
	{
		CString strError;
		strError.Format ("%d <= Number_of_Contact_Points <= %d",
			RIGID_BODY_NUM_CONTACTS_MIN, RIGID_BODY_NUM_CONTACTS_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Number_of_Contact_Points field.");
		return FALSE;			
	}

	// If there is contact points given (number of contact points > 0)
	// then allocate a contact model and add the resulting force
	// effect to the body
	if (nNumberOfContactPoints > 0)
	{
		// Read the label
		istrmDMFile >> strLabel;
		if (!istrmDMFile.good () || strLabel != "Contact_Locations")
		{
			ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				"Expected: Contact_Locations <float> <float> <float>\n <float> <float> <float> \n ...");
			return FALSE;
		}

		// Allocate space to hold the contact points
		CartesianVector *cvContactPoints;
		try {
			cvContactPoints = new CartesianVector[nNumberOfContactPoints];
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}
		
		// Read in the contact points
		int i;
		for (i = 0; i < nNumberOfContactPoints; i++)
		{
			istrmDMFile >> cvContactPoints[i][0] >> cvContactPoints[i][1] >> cvContactPoints[i][2];
			if (!istrmDMFile.good ())
			{
				ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
					"Expected: Contact_Locations <float> <float> <float>\n <float> <float> <float> \n ...");
				delete [] cvContactPoints;
				return FALSE;
			}
			// No validation
			if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
			{
				FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
					"Error after Contact_Locations field.");
				delete [] cvContactPoints;
				return FALSE;			
			}
		}		

		// Allocate the contact model
		CdmvContactModelData *pCdmvContactModelData;
		try {
			pCdmvContactModelData = new CdmvContactModelData;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}
		
		// Assign the contact points to the contact model.
		pCdmvContactModelData->SetContactPoints (nNumberOfContactPoints, cvContactPoints);
		
		// Assign the contact model to the rigid body.
		pCdmvRigidBodyData->SetContactModel (pCdmvContactModelData);

		// Deallocate the contact points
		delete [] cvContactPoints;
	}

	return TRUE;
}

BOOL CParserDM::ParseMDHParameters(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
								   CdmvSystemData **ppCdmvSystemData, CdmvMDHLinkData *pCdmvMDHLinkData)
{
	// MDH Parameters
	string strLabel;
	double dA, dAlpha, dD, dTheta;
	istrmDMFile >> strLabel >> dA >> dAlpha >> dD >> dTheta;
	if (!istrmDMFile.good () || strLabel != "MDH_Parameters")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: MDH_Parameters <float> <float> <float> <float>");
		return FALSE;
	}
	// No validation
	if (dAlpha < MDH_LINK_ALPHA_MIN || dAlpha > MDH_LINK_ALPHA_MAX)
	{
		CString strError;
		strError.Format ("%.3f <= MDH_Parameters 1 (Alpha) <= %.3f",
			MDH_LINK_ALPHA_MIN, MDH_LINK_ALPHA_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after MDH_Parameters field.");
		return FALSE;			
	}
	pCdmvMDHLinkData->SetMDHParameters (dA, dAlpha, dD, dTheta);

	// Initial velocity
	double dInitialVelocity;
	istrmDMFile >> strLabel >> dInitialVelocity;
	if (!istrmDMFile.good () || strLabel != "Initial_Joint_Velocity")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Initial_Joint_Velocity <float>");
		return FALSE;
	}
	// No validation
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Initial_Joint_Velocity field.");
		return FALSE;			
	}
	pCdmvMDHLinkData->SetInitialJointVelocity (dInitialVelocity);

	// Joint limits.
	double dMin, dMax;
	istrmDMFile >> strLabel >> dMin >> dMax;
	if (!istrmDMFile.good () || strLabel != "Joint_Limits")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Joint_Limits <float (min)> <float (max)>");
		return FALSE;
	}
	// Dynamechs will switch them if they are in the wrong order
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Joint_Limits field.");
		return FALSE;			
	}

	// Joint Limit Spring Constant
	double dSpringConstant;
	istrmDMFile >> strLabel >> dSpringConstant;
	if (!istrmDMFile.good () || strLabel != "Joint_Limit_Spring_Constant")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Joint_Limit_Spring_Constant <float>");
		return FALSE;
	}
	if (dSpringConstant < MDH_LINK_JOINT_SPRING_MIN || dSpringConstant > MDH_LINK_JOINT_SPRING_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Joint_Limit_Spring_Constant <= %.1f",
			MDH_LINK_JOINT_SPRING_MIN, MDH_LINK_JOINT_SPRING_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Joint_Limit_Spring_Constant field.");
		return FALSE;			
	}

	// Joint Limit Damper Constant
	double dDamperConstant;
	istrmDMFile >> strLabel >> dDamperConstant;
	if (!istrmDMFile.good () || strLabel != "Joint_Limit_Damper_Constant")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Joint_Limit_Damper_Constant <float>");
		return FALSE;
	}
	if (dDamperConstant < MDH_LINK_JOINT_DAMPER_MIN || dDamperConstant > MDH_LINK_JOINT_DAMPER_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Joint_Limit_Damper_Constant <= %.1f",
			MDH_LINK_JOINT_DAMPER_MIN, MDH_LINK_JOINT_DAMPER_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Joint_Limit_Damper_Constant field.");
		return FALSE;			
	}

	pCdmvMDHLinkData->SetJointLimits (dMin, dMax, dSpringConstant, dDamperConstant);

	return TRUE;
}

BOOL CParserDM::ParseActuator(ifstream &istrmDMFile, int &rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData, CdmvRevoluteLinkData *pCdmvRevoluteLinkData)
{
	string strLabel;
	
	// Actuator Type
	int nActuatorType;
	istrmDMFile >> strLabel >> nActuatorType;
	if (!istrmDMFile.good () || strLabel != "Actuator_Type")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Actuator_Type <integer>");
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Actuator_Type field.");
		return FALSE;			
	}
	if (nActuatorType == NOMOTOR)
	{
		if (!ParseJointFriction (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pCdmvRevoluteLinkData))
			return FALSE;
	}
	else if (nActuatorType == DCMOTOR)
	{
		CdmvRevDCMotorData* pCdmvRevDCMotorData;
		try {
			pCdmvRevDCMotorData = new CdmvRevDCMotorData;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}
		if (!ParseRevDCMotorParameters (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			pCdmvRevDCMotorData))
		{
			delete pCdmvRevDCMotorData;
			return FALSE;
		}
		pCdmvRevoluteLinkData->SetActuator (pCdmvRevDCMotorData);
	}
	else 
	{
		CString strError;
		strError.Format ("Actuator_Type is in {0, 1}");
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}

	return TRUE;
}

BOOL CParserDM::ParseJointFriction(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
								   CdmvSystemData **ppCdmvSystemData, CdmvLinkData *pCdmvLinkData)
{
	// Joint Friction
	string strLabel;
	double dJointFriction;
	istrmDMFile >> strLabel >> dJointFriction;
	if (!istrmDMFile.good () || strLabel != "Joint_Friction")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Joint_Friction <float>");
		return FALSE;
	}
	if (dJointFriction < LINK_JOINT_FRICTION_MIN || 
		dJointFriction > LINK_JOINT_FRICTION_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Joint_Friction <= %.1f",
			LINK_JOINT_FRICTION_MIN, LINK_JOINT_FRICTION_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Joint_Friction field.");
		return FALSE;			
	}

	pCdmvLinkData->SetJointFriction (dJointFriction);

	return TRUE;
}


BOOL CParserDM::ParseJointFriction(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
								   CdmvSystemData **ppCdmvSystemData, CdmvSecJointData *pCdmvSecJointData)
{
	// Joint Friction
	string strLabel;
	double dJointFriction;
	istrmDMFile >> strLabel >> dJointFriction;
	if (!istrmDMFile.good () || strLabel != "Joint_Friction")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Joint_Friction <float>");
		return FALSE;
	}
	if (dJointFriction < SEC_JOINT_FRICTION_MIN || 
		dJointFriction > SEC_JOINT_FRICTION_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Joint_Friction <= %.1f",
			SEC_JOINT_FRICTION_MIN, SEC_JOINT_FRICTION_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Joint_Friction field.");
		return FALSE;			
	}

	pCdmvSecJointData->SetJointFriction (dJointFriction);

	return TRUE;
}

BOOL CParserDM::ParseRevDCMotorParameters(ifstream &istrmDMFile, int &rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData, CdmvRevDCMotorData *pCdmvRevDCMotorData)
{

	// Torque constant
	string strLabel;
	double dTorqueConstant;
	istrmDMFile >> strLabel >> dTorqueConstant;
	if (!istrmDMFile.good () || strLabel != "Motor_Torque_Constant")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Motor_Torque_Constant <float>");
		return FALSE;
	}
	if (dTorqueConstant < REV_DC_MOTOR_TORQUE_CONSTANT_MIN || 
		dTorqueConstant > REV_DC_MOTOR_TORQUE_CONSTANT_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Motor_Torque_Constant <= %.1f",
			REV_DC_MOTOR_TORQUE_CONSTANT_MIN, REV_DC_MOTOR_TORQUE_CONSTANT_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Motor_Torque_Constant field.");
		return FALSE;			
	}

	// Back EMF Constant
	double dBackEMFConstant;
	istrmDMFile >> strLabel >> dBackEMFConstant;
	if (!istrmDMFile.good () || strLabel != "Motor_BackEMF_Constant")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Motor_BackEMF_Constant <float>");
		return FALSE;
	}
	if (dBackEMFConstant < REV_DC_MOTOR_BACK_EMF_CONSTANT_MIN || 
		dBackEMFConstant > REV_DC_MOTOR_BACK_EMF_CONSTANT_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Motor_BackEMF_Constant <= %.1f",
			REV_DC_MOTOR_BACK_EMF_CONSTANT_MIN, REV_DC_MOTOR_BACK_EMF_CONSTANT_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Motor_BackEMF_Constant field.");
		return FALSE;			
	}

	// Armature Resistance
	double dArmatureResistance;
	istrmDMFile >> strLabel >> dArmatureResistance;
	if (!istrmDMFile.good () || strLabel != "Motor_Armature_Resistance")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Motor_Armature_Resistance <float>");
		return FALSE;
	}
	if (dArmatureResistance < REV_DC_MOTOR_ARMATURE_RESISTANCE_MIN || 
		dArmatureResistance > REV_DC_MOTOR_ARMATURE_RESISTANCE_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Motor_Armature_Resistance <= %.1f",
			REV_DC_MOTOR_ARMATURE_RESISTANCE_MIN, REV_DC_MOTOR_ARMATURE_RESISTANCE_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Motor_Armature_Resistance field.");
		return FALSE;			
	}

	// Rotor Inertia
	double dRotorInertia;
	istrmDMFile >> strLabel >> dRotorInertia;
	if (!istrmDMFile.good () || strLabel != "Motor_Inertia")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Motor_Inertia <float>");
		return FALSE;
	}
	if (dRotorInertia < REV_DC_MOTOR_INERTIA_MIN || 
		dRotorInertia > REV_DC_MOTOR_INERTIA_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Motor_Inertia <= %.1f",
			REV_DC_MOTOR_INERTIA_MIN, REV_DC_MOTOR_INERTIA_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Motor_Inertia field.");
		return FALSE;			
	}	

	// Coulomb Friction
	double dCoulombFriction;
	istrmDMFile >> strLabel >> dCoulombFriction;
	if (!istrmDMFile.good () || strLabel != "Motor_Coulomb_Friction_Constant")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Motor_Coulomb_Friction_Constant <float>");
		return FALSE;
	}
	if (dCoulombFriction < REV_DC_MOTOR_COULOMB_FRICTION_MIN || 
		dCoulombFriction > REV_DC_MOTOR_COULOMB_FRICTION_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Motor_Coulomb_Friction_Constant <= %.1f",
			REV_DC_MOTOR_COULOMB_FRICTION_MIN, REV_DC_MOTOR_COULOMB_FRICTION_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Motor_Coulomb_Friction_Constant field.");
		return FALSE;			
	}

	// Viscous Friction
	double dViscousFriction;
	istrmDMFile >> strLabel >> dViscousFriction;
	if (!istrmDMFile.good () || strLabel != "Motor_Viscous_Friction_Constant")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Motor_Viscous_Friction_Constant <float>");
		return FALSE;
	}
	if (dViscousFriction < REV_DC_MOTOR_VISCOUS_FRICTION_MIN || 
		dViscousFriction > REV_DC_MOTOR_VISCOUS_FRICTION_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Motor_Viscous_Friction_Constant <= %.1f",
			REV_DC_MOTOR_VISCOUS_FRICTION_MIN, REV_DC_MOTOR_VISCOUS_FRICTION_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Motor_Viscous_Friction_Constant field.");
		return FALSE;			
	}	
	
	// Max Brush Drop
	double dMaxBrushDrop;
	istrmDMFile >> strLabel >> dMaxBrushDrop;
	if (!istrmDMFile.good () || strLabel != "Motor_Max_Brush_Drop")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Motor_Max_Brush_Drop <float>");
		return FALSE;
	}
	if (dMaxBrushDrop < REV_DC_MOTOR_MAX_BRUSH_DROP_MIN || 
		dMaxBrushDrop > REV_DC_MOTOR_MAX_BRUSH_DROP_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Motor_Max_Brush_Drop <= %.1f",
			REV_DC_MOTOR_MAX_BRUSH_DROP_MIN, REV_DC_MOTOR_MAX_BRUSH_DROP_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Motor_Max_Brush_Drop field.");
		return FALSE;			
	}
	
	// Half Drop
	double dHalfDrop;
	istrmDMFile >> strLabel >> dHalfDrop;
	if (!istrmDMFile.good () || strLabel != "Motor_Half_Drop_Value")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Motor_Max_Brush_Drop <float>");
		return FALSE;
	}
	if (dHalfDrop < REV_DC_MOTOR_HALF_DROP_MIN || 
		dHalfDrop > REV_DC_MOTOR_HALF_DROP_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Motor_Half_Drop_Value <= %.1f",
			REV_DC_MOTOR_HALF_DROP_MIN, REV_DC_MOTOR_HALF_DROP_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Motor_Half_Drop_Value field.");
		return FALSE;			
	}
	
	// Gear Ratio
	double dGearRatio;
	istrmDMFile >> strLabel >> dGearRatio;
	if (!istrmDMFile.good () || strLabel != "Motor_Gear_Ratio")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Motor_Gear_Ratio <float>");
		return FALSE;
	}
	if (dGearRatio < REV_DC_MOTOR_GEAR_RATIO_MIN || 
		dGearRatio > REV_DC_MOTOR_GEAR_RATIO_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Motor_Gear_Ratio <= %.1f",
			REV_DC_MOTOR_GEAR_RATIO_MIN, REV_DC_MOTOR_GEAR_RATIO_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Motor_Gear_Ratio field.");
		return FALSE;			
	}

	pCdmvRevDCMotorData->SetParameters (dTorqueConstant, dBackEMFConstant, dArmatureResistance,
		dRotorInertia, dCoulombFriction, dViscousFriction, dMaxBrushDrop,
		dHalfDrop, dGearRatio);

	return TRUE;
}

BOOL CParserDM::ParseSphericalLinkParameters(ifstream &istrmDMFile, int &rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData, CdmvSphericalLinkData *pCdmvSphericalLinkData)
{
	string strLabel;

	// Position
	CartesianVector cvPosition;
	istrmDMFile >> strLabel >> cvPosition[X] >> cvPosition[Y] >> cvPosition[Z];
	if (!istrmDMFile.good () || strLabel != "Position_From_Inboard_Link")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Position_From_Inboard_Link <float> <float> <float>");
		return FALSE;
	}
	// No validation
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Position_From_Inboard_Link field.");
		return FALSE;			
	}
	pCdmvSphericalLinkData->SetJointOffset (cvPosition);

	// Position
	EulerAngles eaOrientation;
	istrmDMFile >> strLabel >> eaOrientation[0] >> eaOrientation[1] >> eaOrientation[2];
	if (!istrmDMFile.good () || strLabel != "Initial_Joint_Angles")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Initial_Joint_Angles <float> <float> <float>");
		return FALSE;
	}
	int i;
	for (i = 0; i < 3; i++)
	{
		if (eaOrientation[i] < SPHERICAL_LINK_INITIAL_EULER_ANGLE_MIN || 
			eaOrientation[i] > SPHERICAL_LINK_INITIAL_EULER_ANGLE_MAX)
		{
			CString strError;
			strError.Format ("%.3f <= Initial_Joint_Angles <= %.3f",
				SPHERICAL_LINK_INITIAL_EULER_ANGLE_MIN, SPHERICAL_LINK_INITIAL_EULER_ANGLE_MAX);
			ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
			return FALSE;
		}		
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Initial_Joint_Angles field.");
		return FALSE;			
	}

	// Initial Derivatives
	double dInitialAngularVelocity[3];
	istrmDMFile >> strLabel >> dInitialAngularVelocity[0] >> dInitialAngularVelocity[1] >> 
		dInitialAngularVelocity[2];
	if (!istrmDMFile.good () || strLabel != "Initial_Angular_Velocity")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Initial_Angular_Velocity <float> <float> <float>");
		return FALSE;
	}
	// No validation
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Initial_Angular_Velocity field.");
		return FALSE;			
	}
	pCdmvSphericalLinkData->SetInitialState (eaOrientation, dInitialAngularVelocity);

	// Joint Limits
	double dJointLimits[3];
	istrmDMFile >> strLabel >> dJointLimits[0] >> dJointLimits[1] >> 
		dJointLimits[2];
	if (!istrmDMFile.good () || strLabel != "Axes_Limits")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Axes_Limits <float> <float> <float>");
		return FALSE;
	}
	// No validation
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Axes_Limits field.");
		return FALSE;			
	}
	
	// Spring Constant
	double dSpringConstant;
	istrmDMFile >> strLabel >> dSpringConstant;
	if (!istrmDMFile.good () || strLabel != "Joint_Limit_Spring_Constant")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Joint_Limit_Spring_Constant <float>");
		return FALSE;
	}
	if (dSpringConstant < SPHERICAL_LINK_SPRING_CONSTANT_MIN || 
		dSpringConstant > SPHERICAL_LINK_SPRING_CONSTANT_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Motor_Gear_Ratio <= %.1f",
			SPHERICAL_LINK_SPRING_CONSTANT_MIN, SPHERICAL_LINK_SPRING_CONSTANT_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Joint_Limit_Spring_Constant field.");
		return FALSE;			
	}
	
	// Damper Constant
	double dDamperConstant;
	istrmDMFile >> strLabel >> dDamperConstant;
	if (!istrmDMFile.good () || strLabel != "Joint_Limit_Damper_Constant")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Joint_Limit_Damper_Constant <float>");
		return FALSE;
	}
	if (dDamperConstant < SPHERICAL_LINK_DAMPER_CONSTANT_MIN || 
		dDamperConstant > SPHERICAL_LINK_DAMPER_CONSTANT_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Joint_Limit_Damper_Constant <= %.1f",
			SPHERICAL_LINK_SPRING_CONSTANT_MIN, SPHERICAL_LINK_SPRING_CONSTANT_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Joint_Limit_Damper_Constant field.");
		return FALSE;			
	}

	pCdmvSphericalLinkData->SetJointLimits (dJointLimits, dSpringConstant, dDamperConstant);

	return TRUE;
}

BOOL CParserDM::ParseZScrewTxLinkParameters(ifstream &istrmDMFile, int &rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData, CdmvZScrewTxLinkData *pCdmvZScrewTxLinkData)
{
	string strLabel;
	
	// Damper Constant
	double dD, dTheta;
	istrmDMFile >> strLabel >> dD >> dTheta;
	if (!istrmDMFile.good () || strLabel != "ZScrew_Parameters")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: ZScrew_Parameters <float>");
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after ZScrew_Parameters field.");
		return FALSE;			
	}

	pCdmvZScrewTxLinkData->SetJointParameters (dD, dTheta);

	return TRUE;
}

BOOL CParserDM::ParseSecondaryJoints(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
									 CdmvSystemData **ppCdmvSystemData, 
									 CdmvArticulationData *pCdmvClosedArticulationData)
{
	for (;;)
	{	
		// Get next token
		string strToken;
		istrmDMFile >> strToken;
		
		// Advance to next token
		if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
		{
			FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				"");
			return FALSE;			
		}

		if (strToken == "HardRevoluteJoint")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvSecRevJntData *pJoint;
			// Allocate a new link
			try {
				pJoint = new CdmvSecRevJntData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pJoint)))
				return FALSE;

			if (!ParseStabilization (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, pJoint))
				return FALSE;

			if (!ParseSecondaryJointData (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				pCdmvClosedArticulationData, pJoint))
				return FALSE;

			if (!ParseSecondaryRevoluteJoint (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pJoint))
				return FALSE;

			if (!ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData))
				return FALSE;

			pCdmvClosedArticulationData->AddHardSecJoint (pJoint);
		}
		else if (strToken == "SoftRevoluteJoint")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvSecRevJntData *pJoint;
			// Allocate a new link
			try {
				pJoint = new CdmvSecRevJntData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pJoint)))
				return FALSE;

			if (!ParseSecondaryJointData (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				pCdmvClosedArticulationData, pJoint))
				return FALSE;

			if (!ParseSecondaryRevoluteJoint (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pJoint))
				return FALSE;

			if (!ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData))
				return FALSE;

			pCdmvClosedArticulationData->AddSoftSecJoint (pJoint);
		}
		else if (strToken == "HardPrismaticJoint")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvSecPrisJntData *pJoint;
			// Allocate a new link
			try {
				pJoint = new CdmvSecPrisJntData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pJoint)))
				return FALSE;

			if (!ParseStabilization (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, pJoint))
				return FALSE;

			if (!ParseSecondaryJointData (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				pCdmvClosedArticulationData, pJoint))
				return FALSE;

			if (!ParseSecondaryPrismaticJoint (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pJoint))
				return FALSE;

			if (!ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData))
				return FALSE;

			pCdmvClosedArticulationData->AddHardSecJoint (pJoint);
		}
		else if (strToken == "SoftPrismaticJoint")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvSecPrisJntData *pJoint;
			// Allocate a new link
			try {
				pJoint = new CdmvSecPrisJntData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pJoint)))
				return FALSE;

			if (!ParseSecondaryJointData (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				pCdmvClosedArticulationData, pJoint))
				return FALSE;

			if (!ParseSecondaryPrismaticJoint (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pJoint))
				return FALSE;

			if (!ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData))
				return FALSE;

			pCdmvClosedArticulationData->AddSoftSecJoint (pJoint);
		}
		else if (strToken == "HardSphericalJoint")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvSecSpherJntData *pJoint;
			// Allocate a new link
			try {
				pJoint = new CdmvSecSpherJntData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pJoint)))
				return FALSE;

			if (!ParseStabilization (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, pJoint))
				return FALSE;

			if (!ParseSecondaryJointData (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				pCdmvClosedArticulationData, pJoint))
				return FALSE;

			if (!ParseSecondarySphericalJoint (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pJoint))
				return FALSE;

			if (!ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData))
				return FALSE;

			pCdmvClosedArticulationData->AddHardSecJoint (pJoint);
		}
		else if (strToken == "SoftSphericalJoint")
		{
			ParseToBlockBegin (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData);
			
			CdmvSecSpherJntData *pJoint;
			// Allocate a new link
			try {
				pJoint = new CdmvSecSpherJntData ();
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}

			if (!ParseName (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				dynamic_cast<CdmvObject*> (pJoint)))
				return FALSE;

			if (!ParseSecondaryJointData (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				pCdmvClosedArticulationData, pJoint))
				return FALSE;

			if (!ParseSecondarySphericalJoint (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				pJoint))
				return FALSE;

			if (!ParseToBlockEnd (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData))
				return FALSE;

			pCdmvClosedArticulationData->AddSoftSecJoint (pJoint);
		}
		else if (strToken == "}")
		{
			// End of block so stop parsing at this level
			return TRUE;
		}
		else
		{
			ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
				"Unexpected token.  Valid tokens are { HardRevoluteJoint, SoftRevoluteJoint, HardPrismaticJoint, SoftPrismaticJoint, HardSphericalJoint, SoftSphericalJoint, '}' (Brace to show end of block)}");
			return FALSE;
		}
	}

	// Shouldn't get here
	ASSERT (FALSE);
	return TRUE;
}

BOOL CParserDM::ParseStabilization(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
								   CdmvSystemData **ppCdmvSystemData, CdmvSecJointData *pCdmvSecJointData)
{

	// Stabilization Type
	string strLabel, strStabilization;
	istrmDMFile >> strLabel >> strStabilization;
	if (!istrmDMFile.good () || strLabel != "Stabilization")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Stabilization <string>");
		return FALSE;
	}
	if (strStabilization == "NONE")
	{
		pCdmvSecJointData->SetStabilizationType (STABILIZATION_NONE);
	}
	else if (strStabilization == "BAUMGARTE")
	{
		pCdmvSecJointData->SetStabilizationType (STABILIZATION_BAUMGARTE);
	}
	else if (strStabilization == "SPRING_DAMPER")
	{
		pCdmvSecJointData->SetStabilizationType (STABILIZATION_SPRING_DAMPER);
	}
	else
	{
		CString strError = "Invalid string expected one of {NONE, BAUMGARTE, SPRING_DAMPER}";
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Stabilization field.");
		return FALSE;			
	}

	return TRUE;
}

BOOL CParserDM::ParseSecondaryJointData(ifstream &istrmDMFile, int &rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData, 
										CdmvArticulationData *pCdmvClosedArticulationData,
										CdmvSecJointData *pCdmvSecJointData)
{
		
	string strLabel;
	pCdmvSecJointData->SetArticulation (pCdmvClosedArticulationData);

	string strLinkAName;
	istrmDMFile >> strLabel;
	if (!ReadStringInDoubleQuotes (istrmDMFile, strLinkAName))
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Link_A_Name \"<string>\"");
		return FALSE;
	}
	if (!istrmDMFile.good () || strLabel != "Link_A_Name")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Link_A_Name \"<string>\"");
		return FALSE;
	}
	CdmvLinkData *pLink = (dynamic_cast <CdmvArticulationData*> (*ppCdmvSystemData))->
		FindLinkByName (strLinkAName.c_str ());
	if (!pLink)
	{
		CString strError = "Invalid Link_A_Name.  Must already be defined.";
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Link_A_Name field.");
		return FALSE;			
	}
	// I don't believe the articulation pointer is still needed for anything anymore.
	pCdmvSecJointData->SetLinkA (pCdmvClosedArticulationData, pLink); // Save by pointer so 
		// data remains consistent even if user changes name in the interface.

	string strLinkBName;
	istrmDMFile >> strLabel;
	if (!ReadStringInDoubleQuotes (istrmDMFile, strLinkBName))
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Link_B_Name \"<string>\"");
		return FALSE;
	}
	if (!istrmDMFile.good () || strLabel != "Link_B_Name")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Link_B_Name \"<string>\"");
		return FALSE;
	}
	pLink = (dynamic_cast <CdmvArticulationData*> (*ppCdmvSystemData))->
		FindLinkByName (strLinkBName.c_str ());
	if (!pLink)
	{
		CString strError = "Invalid Link_B_Name.  Must already be defined.";
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Link_B_Name field.");
		return FALSE;			
	}
	pCdmvSecJointData->SetLinkB (pCdmvClosedArticulationData, pLink); // Save by pointer so 
		// data remains consistent even if user changes name in the interface.

	// Position of A
	CartesianVector cvPosA;
	istrmDMFile >> strLabel >> cvPosA[0] >> cvPosA[1] >> cvPosA[2];
	if (!istrmDMFile.good () || strLabel != "Joint_A_Position")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Joint_A_Position <float> <float> <float>");
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Joint_A_Position field.");
		return FALSE;			
	}
	
	// Rotation
	RotationMatrix rotA;
	istrmDMFile >> strLabel;
	if (!istrmDMFile.good () || strLabel != "Rotation_Matrix_A")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Rotation_Matrix_A <float> <float> <float>\n\t<float> <float> <float>\n\t<float> <float> <float>");
		return FALSE;
	}
	int i,j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			istrmDMFile >> rotA[i][j];
			if (!istrmDMFile.good ())
			{
				ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
					"Expected: Rotation_Matrix_A <float> <float> <float>\n\t<float> <float> <float>\n\t<float> <float> <float>");
				return FALSE;
			}
			if (rotA[i][j] < SECONDARY_JOINT_ROTATION_MATRIX_MIN || rotA[i][j] > SECONDARY_JOINT_ROTATION_MATRIX_MAX)
			{
				CString strError;
				strError.Format ("%.3f <= Rotation_Matrix_A <= %.3f",
					SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
				ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
				return FALSE;
			}
		}
		if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
		{
			FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				"Error after Rotation_Matrix_A field.");
			return FALSE;			
		}
	}

	// Position of B
	CartesianVector cvPosB;
	istrmDMFile >> strLabel >> cvPosB[0] >> cvPosB[1] >> cvPosB[2];
	if (!istrmDMFile.good () || strLabel != "Joint_B_Position")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Joint_B_Position <float> <float> <float>");
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Joint_B_Position field.");
		return FALSE;			
	}
	
	// Rotation
	RotationMatrix rotB;
	istrmDMFile >> strLabel;
	if (!istrmDMFile.good () || strLabel != "Rotation_Matrix_B")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Rotation_Matrix_B <float> <float> <float>\n\t<float> <float> <float>\n\t<float> <float> <float>");
		return FALSE;
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			istrmDMFile >> rotB[i][j];
			if (!istrmDMFile.good ())
			{
				ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
					"Expected: Rotation_Matrix_B <float> <float> <float>\n\t<float> <float> <float>\n\t<float> <float> <float>");
				return FALSE;
			}
			if (rotB[i][j] < SECONDARY_JOINT_ROTATION_MATRIX_MIN || rotB[i][j] > SECONDARY_JOINT_ROTATION_MATRIX_MAX)
			{
				CString strError;
				strError.Format ("%.3f <= Rotation_Matrix_B <= %.3f",
					SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
				ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
				return FALSE;
			}
		}
		if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
		{
			FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
				"Error after Rotation_Matrix_B field.");
			return FALSE;			
		}
	}
	
	pCdmvSecJointData->SetKinematics (cvPosA, cvPosB, rotA, rotB);

	if (!ParseJointFriction (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, pCdmvSecJointData))
		return FALSE;

	return TRUE;
}

BOOL CParserDM::ParseSecondaryRevoluteJoint(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
											CdmvSystemData **ppCdmvSystemData, CdmvSecRevJntData *pCdmvSecRevJntData)
{
	string strLabel;
	// Linear Constraint Spring
	double dLinearConstraintSpring;
	istrmDMFile >> strLabel >> dLinearConstraintSpring;
	if (!istrmDMFile.good () || strLabel != "Position_Constraint_Spring")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Position_Constraint_Spring <float>");
		return FALSE;
	}
	if (dLinearConstraintSpring < SEC_JOINT_LINEAR_SPRING_MIN || dLinearConstraintSpring > SEC_JOINT_LINEAR_SPRING_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Position_Constraint_Spring <= %.1f",
			SEC_JOINT_LINEAR_SPRING_MIN, SEC_JOINT_LINEAR_SPRING_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Position_Constraint_Spring field.");
		return FALSE;			
	}

	// Linear Constraint Damper
	double dLinearConstraintDamper;
	istrmDMFile >> strLabel >> dLinearConstraintDamper;
	if (!istrmDMFile.good () || strLabel != "Position_Constraint_Damper")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Position_Constraint_Damper <float>");
		return FALSE;
	}
	if (dLinearConstraintDamper < SEC_JOINT_LINEAR_DAMPER_MIN || dLinearConstraintDamper > SEC_JOINT_LINEAR_DAMPER_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Position_Constraint_Damper <= %.1f",
			SEC_JOINT_LINEAR_DAMPER_MIN, SEC_JOINT_LINEAR_DAMPER_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Position_Constraint_Damper field.");
		return FALSE;			
	}

	// Angular Constraint Spring
	double dAngularConstraintSpring;
	istrmDMFile >> strLabel >> dAngularConstraintSpring;
	if (!istrmDMFile.good () || strLabel != "Orientation_Constraint_Spring")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Orientation_Constraint_Spring <float>");
		return FALSE;
	}
	if (dAngularConstraintSpring < SEC_JOINT_ANGULAR_SPRING_MIN || dAngularConstraintSpring > SEC_JOINT_ANGULAR_SPRING_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Orientation_Constraint_Spring <= %.1f",
			SEC_JOINT_ANGULAR_SPRING_MIN, SEC_JOINT_ANGULAR_SPRING_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Orientation_Constraint_Spring field.");
		return FALSE;			
	}

	// Angular Constraint Damper
	double dAngularConstraintDamper;
	istrmDMFile >> strLabel >> dAngularConstraintDamper;
	if (!istrmDMFile.good () || strLabel != "Orientation_Constraint_Damper")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Orientation_Constraint_Damper <float>");
		return FALSE;
	}
	if (dAngularConstraintDamper < SEC_JOINT_ANGULAR_DAMPER_MIN || dAngularConstraintDamper > SEC_JOINT_ANGULAR_DAMPER_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Orientation_Constraint_Damper <= %.1f",
			SEC_JOINT_ANGULAR_DAMPER_MIN, SEC_JOINT_ANGULAR_DAMPER_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Orientation_Constraint_Damper field.");
		return FALSE;			
	}

	pCdmvSecRevJntData->SetConstraintParams (dLinearConstraintSpring, dLinearConstraintDamper,
		dAngularConstraintSpring, dAngularConstraintDamper);

	return TRUE;
}

BOOL CParserDM::ParseSecondaryPrismaticJoint(ifstream &istrmDMFile, int &rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData, CdmvSecPrisJntData *pCdmvSecPrisJntData)
{
	string strLabel;
	// Linear Constraint Spring
	double dLinearConstraintSpring;
	istrmDMFile >> strLabel >> dLinearConstraintSpring;
	if (!istrmDMFile.good () || strLabel != "Position_Constraint_Spring")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Position_Constraint_Spring <float>");
		return FALSE;
	}
	if (dLinearConstraintSpring < SEC_JOINT_LINEAR_SPRING_MIN || dLinearConstraintSpring > SEC_JOINT_LINEAR_SPRING_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Position_Constraint_Spring <= %.1f",
			SEC_JOINT_LINEAR_SPRING_MIN, SEC_JOINT_LINEAR_SPRING_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Position_Constraint_Spring field.");
		return FALSE;			
	}

	// Linear Constraint Damper
	double dLinearConstraintDamper;
	istrmDMFile >> strLabel >> dLinearConstraintDamper;
	if (!istrmDMFile.good () || strLabel != "Position_Constraint_Damper")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Position_Constraint_Damper <float>");
		return FALSE;
	}
	if (dLinearConstraintDamper < SEC_JOINT_LINEAR_DAMPER_MIN || dLinearConstraintDamper > SEC_JOINT_LINEAR_DAMPER_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Position_Constraint_Damper <= %.1f",
			SEC_JOINT_LINEAR_DAMPER_MIN, SEC_JOINT_LINEAR_DAMPER_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Position_Constraint_Damper field.");
		return FALSE;			
	}

	// Angular Constraint Spring
	double dAngularConstraintSpring;
	istrmDMFile >> strLabel >> dAngularConstraintSpring;
	if (!istrmDMFile.good () || strLabel != "Orientation_Constraint_Spring")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Orientation_Constraint_Spring <float>");
		return FALSE;
	}
	if (dAngularConstraintSpring < SEC_JOINT_ANGULAR_SPRING_MIN || dAngularConstraintSpring > SEC_JOINT_ANGULAR_SPRING_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Orientation_Constraint_Spring <= %.1f",
			SEC_JOINT_ANGULAR_SPRING_MIN, SEC_JOINT_ANGULAR_SPRING_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Orientation_Constraint_Spring field.");
		return FALSE;			
	}

	// Angular Constraint Damper
	double dAngularConstraintDamper;
	istrmDMFile >> strLabel >> dAngularConstraintDamper;
	if (!istrmDMFile.good () || strLabel != "Orientation_Constraint_Damper")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Orientation_Constraint_Damper <float>");
		return FALSE;
	}
	if (dAngularConstraintDamper < SEC_JOINT_ANGULAR_DAMPER_MIN || dAngularConstraintDamper > SEC_JOINT_ANGULAR_DAMPER_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Orientation_Constraint_Damper <= %.1f",
			SEC_JOINT_ANGULAR_DAMPER_MIN, SEC_JOINT_ANGULAR_DAMPER_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Orientation_Constraint_Damper field.");
		return FALSE;			
	}

	pCdmvSecPrisJntData->SetConstraintParams (dLinearConstraintSpring, dLinearConstraintDamper,
		dAngularConstraintSpring, dAngularConstraintDamper);

	return TRUE;
}

BOOL CParserDM::ParseSecondarySphericalJoint(ifstream &istrmDMFile, int &rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData, CdmvSecSpherJntData *pCdmvSecSpherJntData)
{
	string strLabel;
	// Linear Constraint Spring
	double dLinearConstraintSpring;
	istrmDMFile >> strLabel >> dLinearConstraintSpring;
	if (!istrmDMFile.good () || strLabel != "Position_Constraint_Spring")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Position_Constraint_Spring <float>");
		return FALSE;
	}
	if (dLinearConstraintSpring < SEC_JOINT_LINEAR_SPRING_MIN || dLinearConstraintSpring > SEC_JOINT_LINEAR_SPRING_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Position_Constraint_Spring <= %.1f",
			SEC_JOINT_LINEAR_SPRING_MIN, SEC_JOINT_LINEAR_SPRING_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Position_Constraint_Spring field.");
		return FALSE;			
	}

	// Linear Constraint Damper
	double dLinearConstraintDamper;
	istrmDMFile >> strLabel >> dLinearConstraintDamper;
	if (!istrmDMFile.good () || strLabel != "Position_Constraint_Damper")
	{
		ParseError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData,
			"Expected: Position_Constraint_Damper <float>");
		return FALSE;
	}
	if (dLinearConstraintDamper < SEC_JOINT_LINEAR_DAMPER_MIN || dLinearConstraintDamper > SEC_JOINT_LINEAR_DAMPER_MAX)
	{
		CString strError;
		strError.Format ("%.1f <= Position_Constraint_Damper <= %.1f",
			SEC_JOINT_LINEAR_DAMPER_MIN, SEC_JOINT_LINEAR_DAMPER_MAX);
		ValidationError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, strError);
		return FALSE;
	}
	if (!GotoNextData (istrmDMFile, rnCurrentLineNumber))
	{
		FormatError (istrmDMFile, rnCurrentLineNumber, ppCdmvSystemData, 
			"Error after Position_Constraint_Damper field.");
		return FALSE;			
	}

	pCdmvSecSpherJntData->SetConstraintParams (dLinearConstraintSpring, dLinearConstraintDamper);

	return TRUE;
}
