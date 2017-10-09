// ModelOutputFile.cpp: implementation of the CModelOutputFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "ModelOutputFile.h"

#include "PrimitivePlacement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "PrimitiveCovering.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModelOutputFile::CModelOutputFile()
{

}

CModelOutputFile::~CModelOutputFile()
{

}

BOOL CModelOutputFile::OutputModelFile(CString strOutputFile, CModel *pModel)
{
	ASSERT (pModel);

	ofstream ostrmModelFile;

	int n = ostrmModelFile.is_open ();
	
	ostrmModelFile.open (LPCTSTR(strOutputFile));
	int nIsOpen = ostrmModelFile.is_open ();
	if (!nIsOpen)
		return FALSE;

 	ASSERT (ostrmModelFile != NULL);

	OutputVersion (ostrmModelFile);

	// Output the background color
	COLORREF crBackground = pModel->GetBackgroundColor ();
	ostrmModelFile << "BackgroundColor:\t"
		<< static_cast <int> (GetRValue (crBackground)) << '\t'
		<< static_cast <int> (GetGValue (crBackground)) << '\t'
		<< static_cast <int> (GetBValue (crBackground)) << '\n';
	
	// Output whether to use user supplied inertial data or not
	string strUseUserSuppliedDataForPhysicalData;
	if (pModel->UseUserSuppliedDataForPhysicalData ())
		ostrmModelFile << "UseUserSuppliedDataForPhysicalData: TRUE" << endl;
	else
		ostrmModelFile << "UseUserSuppliedDataForPhysicalData: FALSE" << endl;

	// Output the number of primitives
	int nNumberOfPrimitives = pModel->GetNumberOfPrimitives ();
	ostrmModelFile << "NumPrimitives:\t" << nNumberOfPrimitives << '\n';

	// Now output each primitive
	int nIndex;
	CPrimitive* pPrimitive = NULL;
	for (nIndex = 0; nIndex < nNumberOfPrimitives; nIndex++)
	{
		pPrimitive = pModel->GetPrimitive (nIndex);
		ASSERT (pPrimitive);
		if (typeid (*pPrimitive) == typeid (CPrimitiveSphere))
			OutputPrimitiveSphere (ostrmModelFile, dynamic_cast <CPrimitiveSphere*> (pPrimitive));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveBlock))
			OutputPrimitiveBlock (ostrmModelFile, dynamic_cast <CPrimitiveBlock*> (pPrimitive));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveCone))
			OutputPrimitiveCone (ostrmModelFile, dynamic_cast <CPrimitiveCone*> (pPrimitive));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveCylinder))
			OutputPrimitiveCylinder (ostrmModelFile, dynamic_cast <CPrimitiveCylinder*> (pPrimitive));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveHemisphere))
			OutputPrimitiveHemisphere (ostrmModelFile, dynamic_cast <CPrimitiveHemisphere*> (pPrimitive));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveTruncatedCone))
			OutputPrimitiveTruncatedCone (ostrmModelFile, dynamic_cast <CPrimitiveTruncatedCone*> (pPrimitive));
		else
			ASSERT (FALSE);
	}
	
	// Close the output stream
	ostrmModelFile.close ();

	// Otherwise everything went fine
	return TRUE;
}

void CModelOutputFile::OutputVersion(ofstream &ostrmModelFile)
{
	ostrmModelFile << "Format:\t" << 1 << '\n';
}

void CModelOutputFile::OutputPrimitiveCovering(ofstream &ostrmModelFile, CPrimitiveCovering* pPrimitiveCovering)
{
	ASSERT (pPrimitiveCovering);

	ostrmModelFile << "\tCovering:\t\t";
	
	structPrimitiveCoveringData strtPrimitiveCoveringData;

	pPrimitiveCovering->GetPrimitiveCoveringData (&strtPrimitiveCoveringData);

	if (strtPrimitiveCoveringData.covCovering == TEXTURE)
		ostrmModelFile << "TEXTURE\t" << "\"" << 
		 LPCTSTR(strtPrimitiveCoveringData.strTextureFile) << "\"" << "\n";
	else if (strtPrimitiveCoveringData.covCovering == SIMPLE_COLOR)
		ostrmModelFile << "SIMPLE_COLOR\t"
		<< static_cast <int> (GetRValue (strtPrimitiveCoveringData.crColor)) << '\t'
		<< static_cast <int> (GetGValue (strtPrimitiveCoveringData.crColor)) << '\t'
		<< static_cast <int> (GetBValue (strtPrimitiveCoveringData.crColor)) << '\n';
	else
		ASSERT (FALSE);
}

void CModelOutputFile::OutputPrimitivePlacement(ofstream &ostrmModelFile, CPrimitivePlacement* pPrimitivePlacement)
{
	ASSERT (pPrimitivePlacement);

	structPrimitivePlacementData strtPrimitivePlacementData;
	pPrimitivePlacement->GetPrimitivePlacementData (&strtPrimitivePlacementData);

	ostrmModelFile << "\tTranslation:\t" <<
		strtPrimitivePlacementData.dTranslationX << '\t' <<
		strtPrimitivePlacementData.dTranslationY << '\t' <<
		strtPrimitivePlacementData.dTranslationZ << '\n';

	ostrmModelFile << "\tRotation:\t\t" <<
		strtPrimitivePlacementData.dRotationMatrix[0][0] << '\t' <<
		strtPrimitivePlacementData.dRotationMatrix[0][1] << '\t' << 
		strtPrimitivePlacementData.dRotationMatrix[0][2] << "\n\t\t\t" << 
		strtPrimitivePlacementData.dRotationMatrix[1][0] << '\t' <<
		strtPrimitivePlacementData.dRotationMatrix[1][1] << '\t' << 
		strtPrimitivePlacementData.dRotationMatrix[1][2] << "\n\t\t\t" << 
		strtPrimitivePlacementData.dRotationMatrix[2][0] << '\t' <<
		strtPrimitivePlacementData.dRotationMatrix[2][1] << '\t' << 
		strtPrimitivePlacementData.dRotationMatrix[2][2] << "\n";

}

void CModelOutputFile::OutputPrimitiveSphere(ofstream &ostrmModelFile, CPrimitiveSphere *pPrimitiveSphere)
{
	ASSERT (pPrimitiveSphere);

	ostrmModelFile << "SPHERE\n";

	OutputPrimitiveScale (ostrmModelFile, pPrimitiveSphere->GetPrimitiveScale ());
	OutputPrimitivePlacement (ostrmModelFile, pPrimitiveSphere->GetPrimitivePlacement ());
	OutputPrimitiveCovering (ostrmModelFile, pPrimitiveSphere->GetPrimitiveCovering ());
	OutputPrimitiveName (ostrmModelFile, pPrimitiveSphere);
	OutputPrimitiveMass (ostrmModelFile, pPrimitiveSphere);

	// Output parameters specific to sphere
	structPrimitiveSphereData strtPrimitiveSphereData;
	pPrimitiveSphere->GetPrimitiveSphereData (&strtPrimitiveSphereData);

	ostrmModelFile << "\tParameters:\t" << 
		strtPrimitiveSphereData.dRadius << '\t' <<
		strtPrimitiveSphereData.nLatitudeCount << '\t' <<
		strtPrimitiveSphereData.nLongitudeCount << '\t' <<
		strtPrimitiveSphereData.bRenderBothSides << '\t' <<
		strtPrimitiveSphereData.bUseGouraudShading << '\n';
}

void CModelOutputFile::OutputPrimitiveName(ofstream &ostrmModelFile, CPrimitive *pPrimitive)
{
	ASSERT (pPrimitive);

	ostrmModelFile << '\t' << 
		"Name:\t\t\"" << 
		LPCTSTR (pPrimitive->GetName ()) <<
		"\"\n";
}

void CModelOutputFile::OutputPrimitiveMass(ofstream &ostrmModelFile, CPrimitive *pPrimitive)
{
	ASSERT (pPrimitive);

	ostrmModelFile << '\t' << 
		"Mass:\t\t" << 
		pPrimitive->GetMass () <<
		endl;
}

void CModelOutputFile::OutputPrimitiveScale(ofstream &ostrmModelFile, CPrimitiveScale * pPrimitiveScale)
{
	ASSERT (pPrimitiveScale);

	structPrimitiveScaleData strtPrimitiveScaleAbsoluteData;
	pPrimitiveScale->GetPrimitiveScaleAbsoluteData (&strtPrimitiveScaleAbsoluteData);
	
	ostrmModelFile << "\tScale:\t\t" << 
		strtPrimitiveScaleAbsoluteData.dXScale << '\t' <<
		strtPrimitiveScaleAbsoluteData.dYScale << '\t' <<
		strtPrimitiveScaleAbsoluteData.dZScale << '\n';
}

void CModelOutputFile::OutputPrimitiveCone(ofstream &ostrmModelFile, CPrimitiveCone *pPrimitiveCone)
{
	ASSERT (pPrimitiveCone);

	ostrmModelFile << "CONE\n";

	OutputPrimitiveScale (ostrmModelFile, pPrimitiveCone->GetPrimitiveScale ());
	OutputPrimitivePlacement (ostrmModelFile, pPrimitiveCone->GetPrimitivePlacement ());
	OutputPrimitiveCovering (ostrmModelFile, pPrimitiveCone->GetPrimitiveCovering ());
	OutputPrimitiveName (ostrmModelFile, pPrimitiveCone);
	OutputPrimitiveMass (ostrmModelFile, pPrimitiveCone);

	// Output parameters specific to cone
	structPrimitiveConeData strtPrimitiveConeData;
	pPrimitiveCone->GetPrimitiveConeData (&strtPrimitiveConeData);

	ostrmModelFile << "\tParameters:\t" << 
		strtPrimitiveConeData.dHeight << '\t' <<
		strtPrimitiveConeData.dRadius << '\t' <<
		strtPrimitiveConeData.nTess << '\t' <<
		strtPrimitiveConeData.bRenderBothSides << '\n';
}

void CModelOutputFile::OutputPrimitiveBlock(ofstream &ostrmModelFile, CPrimitiveBlock *pPrimitiveBlock)
{
	ASSERT (pPrimitiveBlock);

	ostrmModelFile << "BLOCK\n";

	OutputPrimitiveScale (ostrmModelFile, pPrimitiveBlock->GetPrimitiveScale ());
	OutputPrimitivePlacement (ostrmModelFile, pPrimitiveBlock->GetPrimitivePlacement ());
	OutputPrimitiveCovering (ostrmModelFile, pPrimitiveBlock->GetPrimitiveCovering ());
	OutputPrimitiveName (ostrmModelFile, pPrimitiveBlock);
	OutputPrimitiveMass (ostrmModelFile, pPrimitiveBlock);

	// Output parameters specific to block
	structPrimitiveBlockData strtPrimitiveBlockData;
	pPrimitiveBlock->GetPrimitiveBlockData (&strtPrimitiveBlockData);

	ostrmModelFile << "\tParameters:\t" << 
		strtPrimitiveBlockData.dLengthX << '\t' <<
		strtPrimitiveBlockData.dLengthY << '\t' <<
		strtPrimitiveBlockData.dLengthZ << '\t' <<
		strtPrimitiveBlockData.bRenderBothSides << '\n';

}

void CModelOutputFile::OutputPrimitiveCylinder(ofstream &ostrmModelFile, CPrimitiveCylinder *pPrimitiveCylinder)
{
	ASSERT (pPrimitiveCylinder);

	ostrmModelFile << "CYLINDER\n";

	OutputPrimitiveScale (ostrmModelFile, pPrimitiveCylinder->GetPrimitiveScale ());
	OutputPrimitivePlacement (ostrmModelFile, pPrimitiveCylinder->GetPrimitivePlacement ());
	OutputPrimitiveCovering (ostrmModelFile, pPrimitiveCylinder->GetPrimitiveCovering ());
	OutputPrimitiveName (ostrmModelFile, pPrimitiveCylinder);
	OutputPrimitiveMass (ostrmModelFile, pPrimitiveCylinder);

	// Output parameters specific to cylinder
	structPrimitiveCylinderData strtPrimitiveCylinderData;
	pPrimitiveCylinder->GetPrimitiveCylinderData (&strtPrimitiveCylinderData);

	ostrmModelFile << "\tParameters:\t" << 
		strtPrimitiveCylinderData.dHeight << '\t' <<
		strtPrimitiveCylinderData.dRadius << '\t' <<
		strtPrimitiveCylinderData.nTess << '\t' <<
		strtPrimitiveCylinderData.bRenderBothSides << '\t' <<
		strtPrimitiveCylinderData.bUseGouraudShading << '\n';
}

void CModelOutputFile::OutputPrimitiveHemisphere(ofstream &ostrmModelFile, CPrimitiveHemisphere *pPrimitiveHemisphere)
{
	ASSERT (pPrimitiveHemisphere);

	ostrmModelFile << "HEMISPHERE\n";

	OutputPrimitiveScale (ostrmModelFile, pPrimitiveHemisphere->GetPrimitiveScale ());
	OutputPrimitivePlacement (ostrmModelFile, pPrimitiveHemisphere->GetPrimitivePlacement ());
	OutputPrimitiveCovering (ostrmModelFile, pPrimitiveHemisphere->GetPrimitiveCovering ());
	OutputPrimitiveName (ostrmModelFile, pPrimitiveHemisphere);
	OutputPrimitiveMass (ostrmModelFile, pPrimitiveHemisphere);

	// Output parameters specific to hemisphere
	structPrimitiveHemisphereData strtPrimitiveHemisphereData;
	pPrimitiveHemisphere->GetPrimitiveHemisphereData (&strtPrimitiveHemisphereData);

	ostrmModelFile << "\tParameters:\t" << 
		strtPrimitiveHemisphereData.dRadius << '\t' <<
		strtPrimitiveHemisphereData.nLatitudeCount << '\t' <<
		strtPrimitiveHemisphereData.nLongitudeCount << '\t' <<
		strtPrimitiveHemisphereData.bRenderBothSides << '\t' <<
		strtPrimitiveHemisphereData.bUseGouraudShading << '\n';

}

void CModelOutputFile::OutputPrimitiveTruncatedCone(ofstream &ostrmModelFile, CPrimitiveTruncatedCone *pPrimitiveTruncatedCone)
{
	ASSERT (pPrimitiveTruncatedCone);

	ostrmModelFile << "TRUNCATED_CONE\n";

	OutputPrimitiveScale (ostrmModelFile, pPrimitiveTruncatedCone->GetPrimitiveScale ());
	OutputPrimitivePlacement (ostrmModelFile, pPrimitiveTruncatedCone->GetPrimitivePlacement ());
	OutputPrimitiveCovering (ostrmModelFile, pPrimitiveTruncatedCone->GetPrimitiveCovering ());
	OutputPrimitiveName (ostrmModelFile, pPrimitiveTruncatedCone);
	OutputPrimitiveMass (ostrmModelFile, pPrimitiveTruncatedCone);

	// Output parameters specific to cone
	structPrimitiveTruncatedConeData strtPrimitiveTruncatedConeData;
	pPrimitiveTruncatedCone->GetPrimitiveTruncatedConeData (&strtPrimitiveTruncatedConeData);

	ostrmModelFile << "\tParameters:\t" << 
		strtPrimitiveTruncatedConeData.dHeight << '\t' <<
		strtPrimitiveTruncatedConeData.dTopRadius << '\t' <<
		strtPrimitiveTruncatedConeData.dBaseRadius << '\t' <<
		strtPrimitiveTruncatedConeData.nTess << '\t' <<
		strtPrimitiveTruncatedConeData.bRenderBothSides << '\t' <<
		strtPrimitiveTruncatedConeData.bUseGouraudShading << '\n';
}
