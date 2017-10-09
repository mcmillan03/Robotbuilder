// dmvTerrainData.cpp: implementation of the CdmvTerrainData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvTerrainData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvTerrainData::CdmvTerrainData()
{
	ResetTerrainData ();

	SetEnvironmentType (ENV_TERRAIN);
}

CdmvTerrainData::~CdmvTerrainData()
{

}

void CdmvTerrainData::SetZValue(int nXIndex, int nYIndex, double dZValue)
{
	ASSERT (nXIndex >= 0 && nXIndex < m_nXDim);
	ASSERT (nYIndex >= 0 && nYIndex < m_nYDim);

	// Note: X rows of Y values
	m_arrayZ.SetAt (nXIndex*m_nYDim + nYIndex, dZValue);
}

void CdmvTerrainData::SetDimensions(int XNewDim, int YNewDim)
{
	ASSERT (XNewDim >= TERRAIN_DIM_MIN && XNewDim <= TERRAIN_DIM_MAX);
	ASSERT (YNewDim >= TERRAIN_DIM_MIN && YNewDim <= TERRAIN_DIM_MAX);
	
	int i;
	int XOldDim = m_nXDim;
	int YOldDim = m_nYDim;
	// Look at each X row of Y values and add or subtract as needed
	for (i = 0; i < min(XNewDim, XOldDim); i++)
	{
		if (YNewDim > YOldDim)
		{
			m_arrayZ.InsertAt (i * YNewDim + YOldDim, 0, YNewDim - YOldDim);
		}
		else
		{
			m_arrayZ.RemoveAt (i * YNewDim + YNewDim, YOldDim - YNewDim);			
		}
	}

	// Add X lines
	if (XNewDim > XOldDim)
	{
		m_arrayZ.InsertAt (XOldDim * YNewDim, 0, (XNewDim - XOldDim) * YNewDim);
	}
	else
	{
		m_arrayZ.RemoveAt (XNewDim * YNewDim, (XOldDim - XNewDim) * YOldDim);
	}

	// Same the new dimensions
	m_nXDim = XNewDim;
	m_nYDim = YNewDim;
			
}

void CdmvTerrainData::SetGridResolution(double dGridResolution)
{
	ASSERT (dGridResolution >= TERRAIN_RESOLUTION_MIN && dGridResolution <= TERRAIN_RESOLUTION_MAX);

	m_dGridResolution = dGridResolution;
  // Version 2 of Terrain file, also need to save value to the X&Y GridResolution
  m_dXGridResolution = dGridResolution;
  m_dYGridResolution = dGridResolution;
}

void CdmvTerrainData::SetXYGridResolution(double dXGridResolution, double dYGridResolution)
{
	ASSERT (dXGridResolution >= TERRAIN_RESOLUTION_MIN && dXGridResolution <= TERRAIN_RESOLUTION_MAX);
  ASSERT (dYGridResolution >= TERRAIN_RESOLUTION_MIN && dYGridResolution <= TERRAIN_RESOLUTION_MAX);

	m_dXGridResolution = dXGridResolution;
  m_dYGridResolution = dYGridResolution;
}

void CdmvTerrainData::SetCovering(COLORREF crColor)
{
	m_crColor = crColor;

	m_TerrainCoveringType = TERRAIN_COVERING_COLOR;
}

void CdmvTerrainData::SetCovering(CString strTextureFile, CString strTexturePath)
{
	m_strTextureFile = strTextureFile;
	m_strTexturePath = strTexturePath;

	m_TerrainCoveringType = TERRAIN_COVERING_TEXTURE;
}

int CdmvTerrainData::GetXDim() const
{
	return m_nXDim;
}

int CdmvTerrainData::GetYDim() const
{
	return m_nYDim;
}

double CdmvTerrainData::GetGridResolution() const
{
	return m_dGridResolution;
}

double CdmvTerrainData::GetXGridResolution() const
{
	return m_dXGridResolution;
}
double CdmvTerrainData::GetYGridResolution() const
{
	return m_dYGridResolution;
}
/*
void GetXYGridResolution (double dXGridResolution, double dYGridResolution) 
{
  dXGridResolution = m_dXGridResolution;
  dYGridResolution = m_dYGridResolution;
}
*/
double CdmvTerrainData::GetZValue(int nXIndex, int nYIndex) const
{
	ASSERT (nXIndex >= 0 && nXIndex < m_nXDim);
	ASSERT (nYIndex >= 0 && nYIndex < m_nYDim);

	// Note: X rows of Y values
	return m_arrayZ.GetAt (nXIndex*m_nYDim + nYIndex);
}

void CdmvTerrainData::ResetTerrainData()
{
	m_nXDim = 2;
	m_nYDim = 2;	
	m_dGridResolution = 1;
  m_dXGridResolution = 1;
  m_dYGridResolution = 1;
	m_TerrainCoveringType = TERRAIN_COVERING_COLOR;
	m_crColor = RGB (0, 0, 0);
	m_strTextureFile = "";
	m_strTexturePath = "";
	m_arrayZ.RemoveAll ();
	m_arrayZ.InsertAt (0, 0, 4);

  m_bWireframeOverlay = FALSE;
  m_crWireframeColor = RGB (0, 0, 0);
  m_dWireframeLnWidth = 1.0;
  m_dWireframeElevation = 0.05;
}



void CdmvTerrainData::GetCoveringInfo(TerrainCoveringType &rTerrainCoveringType, COLORREF &rColor,
									  CString &rstrTextureFile, CString &rstrTexturePath)
{
	rTerrainCoveringType = m_TerrainCoveringType;
	rColor = m_crColor;
	rstrTextureFile = m_strTextureFile;
	rstrTexturePath = m_strTexturePath;
}

void CdmvTerrainData::GetWireframeInfo (BOOL &bWireframeOverlay, COLORREF &rWireframeColor,
                    double &dWireframeLnWidth, double &dWireframeElevation)
{
    bWireframeOverlay = m_bWireframeOverlay;
    rWireframeColor = m_crWireframeColor;
    dWireframeLnWidth = m_dWireframeLnWidth;
    dWireframeElevation = m_dWireframeElevation;
}

void CdmvTerrainData::SetWireframe(COLORREF crWireframeColor, double dWireframeLnWidth, double dWireframeElevation)
{
	m_crWireframeColor = crWireframeColor;
  m_dWireframeLnWidth = dWireframeLnWidth;
  m_dWireframeElevation = dWireframeElevation;
}

void CdmvTerrainData::SetWireframeOverlay(BOOL bWireframeOverlay)
{
  if (m_bWireframeOverlay != bWireframeOverlay)
	{
		m_bWireframeOverlay = bWireframeOverlay;
		//m_bDataChanged = TRUE;
	}
}