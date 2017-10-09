// dmvContactModelData.cpp: implementation of the CdmvContactModelData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvContactModelData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvContactModelData::CdmvContactModelData()
{
	// note MFC constructs the array as empty
}

CdmvContactModelData::~CdmvContactModelData()
{
	// everything is on the stack, so no need to free
	// just remove everything from the array
	m_arrayPosition.RemoveAll ();
}

void CdmvContactModelData::SetContactPoints(int nNumPoints, CartesianVector* pPositions)
{

	
	// note this doesn't strictly set the size, but allocates memory so the 
	// array won't have to be grown dynamically
	m_arrayPosition.SetSize (nNumPoints);

	// now copy all of the positions into structs to add to the array
	int nCounter; 
	for (nCounter = 0; nCounter < nNumPoints; nCounter++)
	{
		// first build a structCartesianVector to add the array
		structCartesianVector strtCartesianVector;
		strtCartesianVector.fXval = (*(pPositions + nCounter))[0];
		strtCartesianVector.fYval = (*(pPositions + nCounter))[1];
		strtCartesianVector.fZval = (*(pPositions + nCounter))[2];

		// add to the array
		m_arrayPosition.SetAt (nCounter, strtCartesianVector);
	}
}

	

CdmvContactModelData::CdmvContactModelData(CdmvContactModelData &rCdmvContactModelData):CdmvObject (rCdmvContactModelData)
{
	int i, nSize;
	nSize = rCdmvContactModelData.m_arrayPosition.GetSize ();
	for (i = 0; i < nSize; i++)
		m_arrayPosition.Add (rCdmvContactModelData.m_arrayPosition.GetAt (i)); // 

}
