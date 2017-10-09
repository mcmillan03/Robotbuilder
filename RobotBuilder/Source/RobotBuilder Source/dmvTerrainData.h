// dmvTerrainData.h: interface for the CdmvTerrainData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVTERRAINDATA_H__0ED04537_1372_4F5B_9598_10DEAF8AD230__INCLUDED_)
#define AFX_DMVTERRAINDATA_H__0ED04537_1372_4F5B_9598_10DEAF8AD230__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvEnvironmentData.h"

#define TERRAIN_DIM_MIN	2
#define TERRAIN_DIM_MAX	1e5
#define TERRAIN_RESOLUTION_MIN	1.0e-6
#define TERRAIN_RESOLUTION_MAX	1e5

typedef enum {TERRAIN_COVERING_COLOR, TERRAIN_COVERING_TEXTURE} TerrainCoveringType;

class CdmvTerrainData : public CdmvEnvironmentData
{
public:
	void GetCoveringInfo (TerrainCoveringType& rTerrainCoveringType, COLORREF& rColor,
		CString& rstrTextureFile, CString &rstrTexturePath);
  void GetWireframeInfo (BOOL &bWireframeOverlay, COLORREF& rWireframeColor,
    double& dWireframeLnWidth, double& dWireframeElevation);
	void ResetTerrainData ();
	double GetZValue (int nXIndex, int nYIndex) const;
	double GetGridResolution () const;
  double GetXGridResolution () const;
  double GetYGridResolution () const;
  //void GetXYGridResolution (double dXGridResolution, double dYGridResolution) const;
	int GetYDim () const;
	int GetXDim () const;
	void SetDimensions (int XDim, int YDim);
	void SetCovering (CString strTextureFile, CString strTexturePath);
	void SetCovering (COLORREF crColor);
	void SetWireframeOverlay(BOOL bWireframeOnOff);
  void SetWireframe (COLORREF crWireframeColor, double dWireframeLnWidth, double dWireframeElevation);
	void SetGridResolution (double dGridResolution);
  void SetXYGridResolution (double dXGridResolution, double dYGridResolution);
	void SetZValue (int nXIndex, int nYIndex, double dZValue);
	CdmvTerrainData();
	virtual ~CdmvTerrainData();
private:
	// Allocate the matrix as an array so it is easy to grow and shrink
	CArray<double, double> m_arrayZ;
	int m_nXDim;
	int m_nYDim;
	double m_dGridResolution;
	double m_dXGridResolution;
	double m_dYGridResolution;
	TerrainCoveringType m_TerrainCoveringType;
	COLORREF m_crColor;
	CString m_strTextureFile;
	CString m_strTexturePath;
  BOOL m_bWireframeOverlay;
	COLORREF m_crWireframeColor;
	double m_dWireframeLnWidth;
	double m_dWireframeElevation;

};

#endif // !defined(AFX_DMVTERRAINDATA_H__0ED04537_1372_4F5B_9598_10DEAF8AD230__INCLUDED_)
