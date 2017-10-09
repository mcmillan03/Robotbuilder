// RBMGraphicView.cpp: implementation of the CRBMGraphicView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "RBMGraphicView.h"
#include "PrimitiveScale.h"

#include "PrimitiveSphere.h"
#include "PrimitiveBlock.h"
#include "PrimitiveCone.h"
#include "PrimitiveCylinder.h"
#include "PrimitiveHemisphere.h"
#include "PrimitiveTruncatedCone.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRBMGraphicView::CRBMGraphicView()
{

}

CRBMGraphicView::~CRBMGraphicView()
{

}


void CRBMGraphicView::LoadNewModel(const CModel *pModel, WTnode** pwtsepnodeBase)
{
	ASSERT (pModel);

	// create the base node for the model
	*pwtsepnodeBase = WTsepnode_new (NULL);
	ASSERT (*pwtsepnodeBase);

	// Add each primitive to the model
	int nNumberOfPrimitives = pModel->GetNumberOfPrimitives ();
	int nIndex;
	for (nIndex = 0; nIndex < nNumberOfPrimitives; nIndex ++)
	{	
		AddPrimitive (pModel->GetPrimitive (nIndex), *pwtsepnodeBase);
	}
}

void CRBMGraphicView::AddPrimitive(CPrimitive *pPrimitive, WTnode* wtnodeParent)
{
	ASSERT (pPrimitive);
	ASSERT (wtnodeParent);
	
	WTgeometry* wtgeomPrimitive;

	// Build geometry based on type
	if (typeid (*pPrimitive) == typeid (CPrimitiveSphere))
	{
		structPrimitiveSphereData strtPrimitiveSphereData;
		const CPrimitiveSphere* pPrimitiveSphere = dynamic_cast <const CPrimitiveSphere*> (pPrimitive);
		ASSERT (pPrimitiveSphere);

		pPrimitiveSphere->GetPrimitiveSphereData (&strtPrimitiveSphereData);

		wtgeomPrimitive = WTgeometry_newsphere (
			strtPrimitiveSphereData.dRadius,
			strtPrimitiveSphereData.nLatitudeCount,
			strtPrimitiveSphereData.nLongitudeCount,
			strtPrimitiveSphereData.bRenderBothSides,
			strtPrimitiveSphereData.bUseGouraudShading);
		ASSERT (wtgeomPrimitive);
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveBlock))
	{
		structPrimitiveBlockData strtPrimitiveBlockData;
		const CPrimitiveBlock* pPrimitiveBlock = dynamic_cast <const CPrimitiveBlock*> (pPrimitive);
		ASSERT (pPrimitiveBlock);

		pPrimitiveBlock->GetPrimitiveBlockData (&strtPrimitiveBlockData);

		wtgeomPrimitive = WTgeometry_newblock (
			strtPrimitiveBlockData.dLengthX,
			strtPrimitiveBlockData.dLengthY,
			strtPrimitiveBlockData.dLengthZ,
			strtPrimitiveBlockData.bRenderBothSides);
		ASSERT (wtgeomPrimitive);
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveCone))
	{
		structPrimitiveConeData strtPrimitiveConeData;
		const CPrimitiveCone* pPrimitiveCone = dynamic_cast <const CPrimitiveCone*> (pPrimitive);
		ASSERT (pPrimitiveCone);

		pPrimitiveCone->GetPrimitiveConeData (&strtPrimitiveConeData);

		wtgeomPrimitive = WTgeometry_newcone (
			strtPrimitiveConeData.dHeight,
			strtPrimitiveConeData.dRadius,
			strtPrimitiveConeData.nTess,
			strtPrimitiveConeData.bRenderBothSides);
		ASSERT (wtgeomPrimitive);
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveCylinder))
	{
		structPrimitiveCylinderData strtPrimitiveCylinderData;
		const CPrimitiveCylinder* pPrimitiveCylinder = dynamic_cast <const CPrimitiveCylinder*> (pPrimitive);
		ASSERT (pPrimitiveCylinder);

		pPrimitiveCylinder->GetPrimitiveCylinderData (&strtPrimitiveCylinderData);

		wtgeomPrimitive = WTgeometry_newcylinder (
			strtPrimitiveCylinderData.dHeight,
			strtPrimitiveCylinderData.dRadius,
			strtPrimitiveCylinderData.nTess,
			strtPrimitiveCylinderData.bRenderBothSides,
			strtPrimitiveCylinderData.bUseGouraudShading);
		ASSERT (wtgeomPrimitive);
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveHemisphere))
	{
		structPrimitiveHemisphereData strtPrimitiveHemisphereData;
		const CPrimitiveHemisphere* pPrimitiveHemisphere = dynamic_cast <const CPrimitiveHemisphere*> (pPrimitive);
		ASSERT (pPrimitiveHemisphere);

		pPrimitiveHemisphere->GetPrimitiveHemisphereData (&strtPrimitiveHemisphereData);

		wtgeomPrimitive = WTgeometry_newhemisphere (
			strtPrimitiveHemisphereData.dRadius,
			strtPrimitiveHemisphereData.nLatitudeCount,
			strtPrimitiveHemisphereData.nLongitudeCount,
			strtPrimitiveHemisphereData.bRenderBothSides,
			strtPrimitiveHemisphereData.bUseGouraudShading);
		ASSERT (wtgeomPrimitive);
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveTruncatedCone))
	{
		structPrimitiveTruncatedConeData strtPrimitiveTruncatedConeData;
		const CPrimitiveTruncatedCone* pPrimitiveTruncatedCone = dynamic_cast <const CPrimitiveTruncatedCone*> (pPrimitive);
		ASSERT (pPrimitiveTruncatedCone);

		pPrimitiveTruncatedCone->GetPrimitiveTruncatedConeData (&strtPrimitiveTruncatedConeData);

		wtgeomPrimitive = WTgeometry_newtruncone (
			strtPrimitiveTruncatedConeData.dHeight,
			strtPrimitiveTruncatedConeData.dTopRadius,
			strtPrimitiveTruncatedConeData.dBaseRadius,
			strtPrimitiveTruncatedConeData.nTess,
			strtPrimitiveTruncatedConeData.bRenderBothSides,
			strtPrimitiveTruncatedConeData.bUseGouraudShading);
		ASSERT (wtgeomPrimitive);
	}


	else
		ASSERT (FALSE);

	// Create the node that everything will attach to
	WTnode* wtmovgeomnodePrimitive = WTmovgeometrynode_new (
		wtnodeParent, wtgeomPrimitive);
	ASSERT (wtmovgeomnodePrimitive);

	// Set the name of the node as the pointer to be able to find it again
	char szName[8 + 1];
	sprintf (szName, "%08x", (int) pPrimitive);
	FLAG flagStatus = WTnode_setname (wtmovgeomnodePrimitive, szName);
	ASSERT (flagStatus);

	// Add the covering and place it
	SetPrimitivePlacement (pPrimitive, wtmovgeomnodePrimitive);
	SetPrimitiveCovering (pPrimitive, wtmovgeomnodePrimitive);
	SetPrimitiveScale (pPrimitive, wtmovgeomnodePrimitive);
}

void CRBMGraphicView::SetPrimitivePlacement(CPrimitive *pPrimitive,
											  WTnode* wtnodePrimitive)
{
	ASSERT (pPrimitive);
	ASSERT (wtnodePrimitive);

	// Get the placement class.
	CPrimitivePlacement* pPrimitivePlacement = pPrimitive->GetPrimitivePlacement ();
	ASSERT (pPrimitivePlacement);
	// Get the placement data.
	structPrimitivePlacementData strtPrimitivePlacementData;
	pPrimitivePlacement->GetPrimitivePlacementData (&strtPrimitivePlacementData);
	// Build a vector for WTK use for placement
	WTp3 wtp3Translation;
	wtp3Translation[X] = strtPrimitivePlacementData.dTranslationX;
	wtp3Translation[Y] = strtPrimitivePlacementData.dTranslationY;
	wtp3Translation[Z] = strtPrimitivePlacementData.dTranslationZ;
	FLAG flagStatus = WTnode_settranslation (wtnodePrimitive, wtp3Translation);
	ASSERT (flagStatus);

	// Build a WTm3 to set the orientation
	WTm3 wtm3Rotation;
	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			wtm3Rotation[i][j] = strtPrimitivePlacementData.dRotationMatrix[i][j];
	flagStatus = WTnode_setrotation (wtnodePrimitive, wtm3Rotation);
	ASSERT (flagStatus);
}

void CRBMGraphicView::SetPrimitiveCovering(CPrimitive *pPrimitive,
											  WTnode* wtnodePrimitive)
{
	ASSERT (pPrimitive);
	ASSERT (wtnodePrimitive);

	// Obtain a pointer to the geometry from the movgeomnode describing the primitive
	WTgeometry* wtgeometry;
	wtgeometry = WTnode_getgeometry (wtnodePrimitive);
	ASSERT (wtgeometry);

	// Get the covering information
	CPrimitiveCovering* pPrimitiveCovering = pPrimitive->GetPrimitiveCovering ();
	ASSERT (pPrimitiveCovering);

	// Add the covering based on the covering type
	structPrimitiveCoveringData strtPrimitiveCoveringData;
	pPrimitiveCovering->GetPrimitiveCoveringData (&strtPrimitiveCoveringData);
	unsigned char ucRed, ucGreen, ucBlue;
	float fColors[3]; // array of colors to pass into to create the material table
	int nMTableIndex; // Material table index
	float fShininess = 100;
	switch (strtPrimitiveCoveringData.covCovering)
	{
	case SIMPLE_COLOR:
		// Set the color of the geometry
		ucRed =   (0x000000FF & strtPrimitiveCoveringData.crColor) >> 0;
		ucGreen = (0x0000FF00 & strtPrimitiveCoveringData.crColor) >> 8;
		ucBlue =  (0x00FF0000 & strtPrimitiveCoveringData.crColor) >> 16;
		
		fColors[0] = ucRed / 255.0;
		fColors[1] = ucGreen / 255.0;
		fColors[2] = ucBlue / 255.0;

		// Now at the color information
		WTmtable* wtmtable;
		wtmtable = WTmtable_new (
			WTMAT_AMBIENT | WTMAT_DIFFUSE | WTMAT_SPECULAR | WTMAT_SHININESS,
			1, /* estimated entries */
			NULL /* unique name - if NULL WTK makes up one*/);
		ASSERT (wtmtable);

		nMTableIndex = WTmtable_newentry (wtmtable);
		// Verify that this is the only entry in the table
		ASSERT (nMTableIndex == 0);

		FLAG flagReturn;
		flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
			fColors, WTMAT_AMBIENT);
		ASSERT (flagReturn);

		flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
			fColors, WTMAT_DIFFUSE);
		ASSERT (flagReturn);

		fColors[0] = fColors[1] = fColors[2] = 0;

		flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
			fColors, WTMAT_SPECULAR);
		ASSERT (flagReturn);

		flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
			&fShininess, WTMAT_SHININESS);
		ASSERT (flagReturn);

		WTgeometry_setmtable (wtgeometry, wtmtable);
		flagReturn = WTgeometry_setmatid (wtgeometry, nMTableIndex);
		ASSERT (flagReturn);	
		
		break;
	case TEXTURE:
		FLAG flagStatus;
		// Maybe I am trusting WTK too much with the const_cast?
		flagStatus = WTgeometry_settexture (wtgeometry,
			const_cast <char*> (LPCTSTR(strtPrimitiveCoveringData.strTexturePath + 
			  strtPrimitiveCoveringData.strTextureFile)), 
			FALSE, // for shading -- since there user can't really
					// affect the color of the light, I am not
					// going to let the color of the light effect
					// the texture
			FALSE); // for transparent
		// Don't assert on the return, because the texture could just be
		// missing ...
		if (!flagStatus)
			TRACE ("Failed to load texture.\n");
		break;
	default:
		ASSERT (FALSE);
	}
}

void CRBMGraphicView::SetPrimitiveScale(CPrimitive *pPrimitive, WTnode *wtnodePrimitive)
{
	ASSERT (pPrimitive);
	ASSERT (wtnodePrimitive);

	// Get the scale class.
	CPrimitiveScale* pPrimitiveScale = pPrimitive->GetPrimitiveScale ();
	ASSERT (pPrimitiveScale);
	// Get the scale data.
	structPrimitiveScaleData strtPrimitiveScaleRelativeData;
	pPrimitiveScale->GetPrimitiveScaleAbsoluteData(&strtPrimitiveScaleRelativeData);
	// Obtain a pointer to the geometry from the movgeomnode describing the primitive
	WTgeometry* wtgeometry;
	wtgeometry = WTnode_getgeometry (wtnodePrimitive);
	ASSERT (wtgeometry);
	// Get the center to scale about
	WTp3 wtp3Midpoint;
	WTgeometry_getmidpoint (wtgeometry, wtp3Midpoint);
	// Build the scaling vector
	WTp3 wtp3Scale;
	wtp3Scale[X] = strtPrimitiveScaleRelativeData.dXScale;
	wtp3Scale[Y] = strtPrimitiveScaleRelativeData.dYScale;
	wtp3Scale[Z] = strtPrimitiveScaleRelativeData.dZScale;
	// Apply scale - use stretch function so can indepently scale the axes
	WTgeometry_stretch (wtgeometry, wtp3Scale, wtp3Midpoint);
}
