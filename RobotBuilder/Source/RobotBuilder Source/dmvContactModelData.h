// dmvContactModelData.h: interface for the CdmvContactModelData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVCONTACTMODELDATA_H__5E3B29A6_DBDC_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVCONTACTMODELDATA_H__5E3B29A6_DBDC_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvObject.h"

// implement a struct form of the cartesian vector (because functions
// don't like to return arrays
typedef struct
{
	Float fXval;
	Float fYval;
	Float fZval;
} structCartesianVector;

class CdmvContactModelData : public CdmvObject  
{
public:
	CdmvContactModelData (CdmvContactModelData& rCdmvContactModelData);// const deleted from arg#1 to fix a problem
	void SetContactPoints (int nNumPoints, CartesianVector* pPositions);
	CdmvContactModelData();
	virtual ~CdmvContactModelData();
	// design: this should be protected with access/set functions
	CArray<structCartesianVector, structCartesianVector&> m_arrayPosition;
protected:

};

#endif // !defined(AFX_DMVCONTACTMODELDATA_H__5E3B29A6_DBDC_11D3_A7DF_0000E8978554__INCLUDED_)
