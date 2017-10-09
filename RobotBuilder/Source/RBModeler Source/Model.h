// Model.h: interface for the CModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEL_H__55BEC8A7_C63C_4FEF_8DBD_956BE0008FDC__INCLUDED_)
#define AFX_MODEL_H__55BEC8A7_C63C_4FEF_8DBD_956BE0008FDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Primitive.h"
#include <afxtempl.h>

typedef enum {
	PT_SPHERE, PT_BLOCK, PT_CONE, PT_CYLINDER, PT_HEMISPHERE, PT_TRUNCATED_CONE, 
	PT_USER_DEFINED} PrimitiveType;

class CModel  
{
public:
	void UseUserSuppliedDataForPhysicalData (BOOL bUseUserSuppliedDataForPhysicalData);
	BOOL UseUserSuppliedDataForPhysicalData () const;
	COLORREF GetBackgroundColor () const;
	void SetBackgroundColor (COLORREF crBackground);
	void ClearCameraCenterOfInterest ();
	CPrimitive* GetCameraCenterOfInterest () const;
	void GetModelInertia (double dInertia[3][3]) const;
	void GetModelCenterOfGravity (double dCenterOfGravity[3]) const;
	double GetModelMass () const;
	void DeletePrimitive (CPrimitive* pPrimitive);
	CPrimitive* NewPrimitive (PrimitiveType primtype);
	void AddPrimitive (CPrimitive* pPrimitive);
	CModel& CModel::operator=(const CModel &rModel);
	CModel (const CModel& ModelToCopy);
	CPrimitive* GetPrimitive (int nIndex) const;
	int GetNumberOfPrimitives () const;
	CModel();
	virtual ~CModel();
protected:
	COLORREF m_crBackgroundColor;
	int FindPrimitiveIndex (CPrimitive* pPrimitive);
	CArray <CPrimitive*, CPrimitive*> m_arrayPrimitives;
	BOOL m_bUseUserSuppliedDataForPhysicalData;


};

#endif // !defined(AFX_MODEL_H__55BEC8A7_C63C_4FEF_8DBD_956BE0008FDC__INCLUDED_)
