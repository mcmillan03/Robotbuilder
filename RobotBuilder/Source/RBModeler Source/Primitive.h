// Primitive.h: interface for the CPrimitive class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRIMITIVE_H__B9BD8D02_832B_432E_B792_0179AADA7EC6__INCLUDED_)
#define AFX_PRIMITIVE_H__B9BD8D02_832B_432E_B792_0179AADA7EC6__INCLUDED_

#include "PrimitiveCovering.h"	// Added by ClassView
#include "PrimitivePlacement.h"	// Added by ClassView
#include "PrimitiveScale.h"
#include <wt.h> // for WTFUZZ
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PRIMITIVE_MASS_MIN	1.0e-6f
#define PRIMITIVE_MASS_MAX	1.0e6f

class CPrimitivePlacement;

class CPrimitive  
{
public:
	virtual void GetCenterOfGravity (double dPos[3]) const = 0;
	virtual void GetInertiaTensor (double dIcg[3][3]) const = 0;
	void GetTransformedInertiaTensor (double dIbar[3][3]);
	void SetMass (double dMass);
	double GetMass () const;
	CPrimitiveScale* GetPrimitiveScale ();
	CPrimitivePlacement* GetPrimitivePlacement ();
	CPrimitiveCovering* GetPrimitiveCovering ();
	void SetName (CString strName);
	CString GetName ();
	CPrimitive();
	virtual ~CPrimitive();
	void IsCameraCenterOfInterest (BOOL bIsCOI);
	BOOL IsCameraCenterOfInterest () const;
	BOOL ShowWtkAxes () const;
	void ShowWtkAxes (BOOL bShow);

protected:
	float m_fAxisLength;
	double m_dMass;
	CPrimitivePlacement m_PrimitivePlacement;
	CPrimitiveCovering m_PrimitiveCovering;
	CPrimitiveScale m_PrimitiveScale;
	CString m_strName;
	BOOL m_bShowWtkAxes;
	BOOL m_bCameraCenterOfInterest;
};

#endif // !defined(AFX_PRIMITIVE_H__B9BD8D02_832B_432E_B792_0179AADA7EC6__INCLUDED_)
