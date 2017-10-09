// Model.cpp: implementation of the CModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "Model.h"

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

CModel::CModel()
{
	m_crBackgroundColor = INITIAL_WTK_BACKGROUND_COLOR;
	m_bUseUserSuppliedDataForPhysicalData = TRUE;
}

CModel::~CModel()
{
	// Clean itself up by deleting its primitives
	int nNumberOfPrimitives = m_arrayPrimitives.GetSize ();
	int nCounter;
	for (nCounter = 0; nCounter < nNumberOfPrimitives; nCounter++)
	{
		delete m_arrayPrimitives.GetAt (nCounter);
	}
	m_arrayPrimitives.RemoveAll ();
}

int CModel::GetNumberOfPrimitives() const
{
	return m_arrayPrimitives.GetSize ();
}

CPrimitive* CModel::GetPrimitive(int nIndex) const
{
	ASSERT (nIndex >= 0 && nIndex < m_arrayPrimitives.GetSize ());

	return m_arrayPrimitives.GetAt (nIndex);
}

// Copy Constructor
CModel::CModel(const CModel &ModelToCopy)
{
	// Copy the array of primitives
	int nCounter;
	int nNumberOfPrimitives = ModelToCopy.GetNumberOfPrimitives ();
	for (nCounter = 0; nCounter < nNumberOfPrimitives; nCounter++)
	{
		CPrimitive* pPrimitiveCopy;
		try {
			CPrimitive* pPrimitive = (ModelToCopy.GetPrimitive (nCounter));
			if (typeid (*pPrimitive) == typeid (CPrimitiveSphere))
				pPrimitiveCopy = new CPrimitiveSphere(*(reinterpret_cast <CPrimitiveSphere*> (pPrimitive)));
			else if (typeid (*pPrimitive) == typeid (CPrimitiveBlock))
				pPrimitiveCopy = new CPrimitiveBlock(*(reinterpret_cast <CPrimitiveBlock*> (pPrimitive)));
			else if (typeid (*pPrimitive) == typeid (CPrimitiveCone))
				pPrimitiveCopy = new CPrimitiveCone(*(reinterpret_cast <CPrimitiveCone*> (pPrimitive)));
			else if (typeid (*pPrimitive) == typeid (CPrimitiveCylinder))
				pPrimitiveCopy = new CPrimitiveCylinder(*(reinterpret_cast <CPrimitiveCylinder*> (pPrimitive)));
			else if (typeid (*pPrimitive) == typeid (CPrimitiveHemisphere))
				pPrimitiveCopy = new CPrimitiveHemisphere(*(reinterpret_cast <CPrimitiveHemisphere*> (pPrimitive)));
			else if (typeid (*pPrimitive) == typeid (CPrimitiveTruncatedCone))
				pPrimitiveCopy = new CPrimitiveTruncatedCone(*(reinterpret_cast <CPrimitiveTruncatedCone*> (pPrimitive)));
			else
				ASSERT (FALSE);
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}
		m_arrayPrimitives.Add (pPrimitiveCopy);
	}

	m_bUseUserSuppliedDataForPhysicalData = ModelToCopy.UseUserSuppliedDataForPhysicalData ();
	m_crBackgroundColor = ModelToCopy.GetBackgroundColor ();
}

// I don't anticipate this happening, but in case it does, I don't want the compiler's
// version.
CModel& CModel::operator=(const CModel &rModel)
{
	ASSERT (FALSE);
	return *this;
}

void CModel::AddPrimitive(CPrimitive *pPrimitive)
{
	ASSERT (pPrimitive);
		
	// If its a debug build, make sure the primitive that is attempting to be
	// added to the model isn't already a part of the model
#ifdef _DEBUG
	int nCounter;
	int nNumberOfPrimitives = m_arrayPrimitives.GetSize ();
	for (nCounter = 0; nCounter < nNumberOfPrimitives; nCounter++)
	{
		if (m_arrayPrimitives.GetAt (nCounter) == pPrimitive)
		{
			ASSERT (FALSE);
		}
	}
#endif // _DEBUG

	m_arrayPrimitives.Add (pPrimitive);
}

CPrimitive* CModel::NewPrimitive(PrimitiveType primtype)
{
	CPrimitive* pNewPrimitive = NULL;
	try {
		switch (primtype)
		{
		case PT_SPHERE:
			pNewPrimitive = new CPrimitiveSphere;
			break;
		case PT_BLOCK:
			pNewPrimitive = new CPrimitiveBlock;
			break;
		case PT_CONE:
			pNewPrimitive = new CPrimitiveCone;
			break;
		case PT_CYLINDER:
			pNewPrimitive = new CPrimitiveCylinder;
			break;
		case PT_HEMISPHERE:
			pNewPrimitive = new CPrimitiveHemisphere;
			break;
		case PT_TRUNCATED_CONE:
			pNewPrimitive = new CPrimitiveTruncatedCone;
			break;
		default:
			ASSERT (FALSE);
		}
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	// Add the new primitive to the model
	AddPrimitive (pNewPrimitive);

	// return a pointer to the new primitive
	return pNewPrimitive;
}

void CModel::DeletePrimitive(CPrimitive *pPrimitive)
{
	int nIndex = FindPrimitiveIndex (pPrimitive);

	// Free the memory
	delete m_arrayPrimitives.GetAt (nIndex);
	// Remove the entry from the array
	m_arrayPrimitives.RemoveAt (nIndex);

}

int CModel::FindPrimitiveIndex(CPrimitive *pPrimitive)
{
	int nCounter;
	int nNumberOfPrimitives = m_arrayPrimitives.GetSize ();

	for (nCounter = 0; nCounter < nNumberOfPrimitives; nCounter++)
	{
		if (m_arrayPrimitives.GetAt (nCounter) == pPrimitive)
		{
			// found it so break and return
			return nCounter;
		}
	}

	// If get this far, then it wasn't found, which is an unexpected situation
	ASSERT (FALSE);
	// To make compiler happy
	return -1;
}

// queries the individual primitives and sums
double CModel::GetModelMass() const
{
	double dTotalMass = 0;
	CPrimitive* pPrimitive;

	int nIndex;
	int nNumberOfPrimitives = GetNumberOfPrimitives ();
	for (nIndex = 0; nIndex < nNumberOfPrimitives; nIndex++)
	{
		pPrimitive = GetPrimitive (nIndex);
		dTotalMass += pPrimitive->GetMass ();
	}

	return dTotalMass;
}

// Finds the center of gravity for the model
void CModel::GetModelCenterOfGravity(double dCenterOfGravity[]) const
{
	// Initialize cog to 0
	int i;
	for (i = 0; i < 3; i++)
		dCenterOfGravity[i] = 0;


	CPrimitive* pPrimitive;
	int nIndex;
	int nNumberOfPrimitives = GetNumberOfPrimitives ();
	for (nIndex = 0; nIndex < nNumberOfPrimitives; nIndex++)
	{
		pPrimitive = GetPrimitive (nIndex);
		double dMass = pPrimitive->GetMass ();
		double dCog[3]; // center of gravity in link coords
		pPrimitive->GetCenterOfGravity (dCog);
		int j;
		for (j = 0; j < 3; j++)
			dCenterOfGravity[j] += dCog[j] * dMass;
	}

	// Divide by the number of primitives to average
	int j;
	for (j = 0; j < 3; j++)
		dCenterOfGravity[j] /= GetModelMass ();

}

// Finds the inertia for the model
void CModel::GetModelInertia(double dInertia[][3]) const
{

	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			dInertia[i][j] = 0;

	// Add in all the individually transformed inertia tensors
	int nNumberOfPrimitives = GetNumberOfPrimitives ();
	int nIndex;
	for (nIndex = 0; nIndex < nNumberOfPrimitives; nIndex++)
	{
		double dIbar[3][3];
		GetPrimitive (nIndex)->GetTransformedInertiaTensor (dIbar);
		
		// Add in the new inertia tensor
		for (i=0;i<3;i++)
			for (j=0;j<3;j++)
				dInertia[i][j] = dIbar[i][j];
	}
}


CPrimitive* CModel::GetCameraCenterOfInterest() const
{
	int i;
	for (i = 0; i < m_arrayPrimitives.GetSize (); i++)
	{
		CPrimitive* pPrimitive = m_arrayPrimitives.GetAt (i);
		if (pPrimitive->IsCameraCenterOfInterest ())
			return pPrimitive;
	}
	// If get here, then no primitive selected, so return NULL
	
	return NULL;
}

void CModel::ClearCameraCenterOfInterest()
{
	// Go through each primitive
	int i;
	for (i = 0; i < m_arrayPrimitives.GetSize (); i++)
	{
		m_arrayPrimitives.GetAt (i)->IsCameraCenterOfInterest (FALSE);
	}
}

void CModel::SetBackgroundColor(COLORREF crBackground)
{
	m_crBackgroundColor = crBackground;
}

COLORREF CModel::GetBackgroundColor() const
{
	return m_crBackgroundColor;
}

BOOL CModel::UseUserSuppliedDataForPhysicalData() const
{
	return m_bUseUserSuppliedDataForPhysicalData;
}

void CModel::UseUserSuppliedDataForPhysicalData(BOOL bUseUserSuppliedDataForPhysicalData)
{
	m_bUseUserSuppliedDataForPhysicalData = bUseUserSuppliedDataForPhysicalData;
}
