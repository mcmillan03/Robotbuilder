// DMViewer.h : main header file for the DMVIEWER application
//

#if !defined(AFX_DMVIEWER_H__6BC5BDE7_EC4B_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVIEWER_H__6BC5BDE7_EC4B_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <dm.h>

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDMViewerApp:
// See DMViewer.cpp for the implementation of this class
//

class CDMViewerApp : public CWinApp
{
public:
	void UpdateMRU (CCmdUI* pCmdUI);
	CDMViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMViewerApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDMViewerApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateIndicatorSimTime(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



inline Float dotProduct (const CartesianVector cvA, const CartesianVector cvB)
{
	return sqrt (cvA[0] * cvB[0] + cvA[1] * cvB[1] + cvA[2] * cvB[2]);
}


inline bool normalizeCartesianVector (CartesianVector cv)
{
	// Check if all elements are zero, and if so return false
	if (cv[0] == 0.0 && cv[1] == 0.0 && cv[2] == 0.0)
		return false;

	// Otherwise normalize
	Float length = 0;
	length = sqrt(cv[0]*cv[0] + cv[1]*cv[1] + cv[2]*cv[2]);
	cv[0] /= length;
	cv[1] /= length;
	cv[2] /= length;

	// Return true when the normal was successfully calculated
	return true;
}

/* Now in DynaMechs
inline void copyCartesianVector (const CartesianVector source, CartesianVector destination)
{
	destination[0] = source[0];
	destination[1] = source[1];
	destination[2] = source[2];
}


inline void rotateCartesianVector (const RotationMatrix R, const CartesianVector p,
											  CartesianVector result)
{
	result[0] = R[0][0]*p[0] + R[0][1]*p[1] + R[0][2]*p[2];
	result[1] = R[1][0]*p[0] + R[1][1]*p[1] + R[1][2]*p[2];
	result[2] = R[2][0]*p[0] + R[2][1]*p[1] + R[2][2]*p[2];
}

inline void transformCartesianVector (const HomogeneousTransformationMatrix T,
												  const CartesianVector p,
												  CartesianVector result)
{
	result[0] = T[0][0]*p[0] + T[0][1]*p[1] + T[0][2]*p[2] + T[0][3];
	result[1] = T[1][0]*p[0] + T[1][1]*p[1] + T[1][2]*p[2] + T[1][3];
	result[2] = T[2][0]*p[0] + T[2][1]*p[1] + T[2][2]*p[2] + T[2][3];
}

inline Float magnitudeCartesianVector (const CartesianVector p)
{
	return sqrt (p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
}

inline void transposeRotationMatrix (const RotationMatrix R, RotationMatrix R_T)
{
	int i,j; // Counters
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			R_T[j][i] = R[i][j];
}
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMVIEWER_H__6BC5BDE7_EC4B_11D3_A7DF_0000E8978554__INCLUDED_)
