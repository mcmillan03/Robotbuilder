// GenerateTerrainFile.cpp: implementation of the CGenerateTerrainFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "GenerateTerrainFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGenerateTerrainFile::CGenerateTerrainFile()
{

}

CGenerateTerrainFile::~CGenerateTerrainFile()
{

}


BOOL CGenerateTerrainFile::CreateTerrainFile (CString strFilePath, CdmvTerrainData* pCdmvTerrainData)
{
	ofstream strmTerrainFile;
	strmTerrainFile.open (strFilePath);
	int nIsOpen = strmTerrainFile.is_open ();
	if (!nIsOpen)
		return FALSE;
 	ASSERT (strmTerrainFile != NULL);

	OutputFileHeader (strmTerrainFile, pCdmvTerrainData);

	// 17 MAY 2002 - Removed version # from file to be compatible with DynaMechs
  // December 8, 2003. Added the Version back to accomodate the Wireframe Overlay
	
  // Output version
	strmTerrainFile << "Version " << 2 << endl;

	// Output the dimensions and resolution
//  double dXGridResolution, dYGridResolution;
//  pCdmvTerrainData->GetXYGridResolution (dXGridResolution, dYGridResolution);
	strmTerrainFile << pCdmvTerrainData->GetXDim () << ' ' <<
		pCdmvTerrainData->GetYDim () << ' ' <<
//		pCdmvTerrainData->GetGridResolution () << endl;
//    dXGridResolution << ' ' << dYGridResolution << endl;
    pCdmvTerrainData->GetXGridResolution () << ' ' << pCdmvTerrainData->GetYGridResolution () << endl;
	// Output the matrix
	int i, j;
	for (i = 0; i < pCdmvTerrainData->GetXDim (); i++)
	{
		for (j = 0; j < pCdmvTerrainData->GetYDim (); j++)
		{
			strmTerrainFile <<  pCdmvTerrainData->GetZValue (i, j) << '\t';
		}
		strmTerrainFile << endl;
	}

	// Output covering data
	CString strTextureFile, strTexturePath;
	COLORREF crCoveringColor;
	TerrainCoveringType theTerrainCoveringType;
	pCdmvTerrainData->GetCoveringInfo(theTerrainCoveringType,
		crCoveringColor, strTextureFile, strTexturePath);
	if (theTerrainCoveringType == TERRAIN_COVERING_COLOR)
	{
		strmTerrainFile << "Covering\t" << "COLOR\t" << (int) (GetRValue(crCoveringColor)) <<
			'\t' << (int) (GetGValue(crCoveringColor)) << '\t' << (int) (GetBValue(crCoveringColor)) << endl;
	}
	else
	{
		strmTerrainFile << "Covering\t" << "TEXTURE\t" << "\"" << 
			LPCTSTR(strTextureFile) << "\"" << endl;
	}

  // Output the Wireframe data
  BOOL bWireframeOverlay;
  string strWireframeOnOff;
  COLORREF crWireframeColor;
  double dWireframeLnWidth, dWireframeElevation;
  pCdmvTerrainData->GetWireframeInfo (bWireframeOverlay, 
    crWireframeColor, dWireframeLnWidth, dWireframeElevation);
  if (bWireframeOverlay)
  {
    strWireframeOnOff = "ON";
  }
  else
  {
    strWireframeOnOff = "OFF";
  }
  strmTerrainFile << "Wireframe\t" << strWireframeOnOff << '\t' << (int) (GetRValue(crWireframeColor)) <<
			'\t' << (int) (GetGValue(crWireframeColor)) << '\t' << (int) (GetBValue(crWireframeColor)) << '\t' <<
      dWireframeLnWidth << '\t' << dWireframeElevation << endl;
	
	strmTerrainFile.close ();

	return TRUE;
}


void CGenerateTerrainFile::OutputFileHeader(ostream &strmTerrainFile, 
												CdmvTerrainData *pCdmvTerrainData)
{
	strmTerrainFile << "# Terrain File" << endl << endl;
}
