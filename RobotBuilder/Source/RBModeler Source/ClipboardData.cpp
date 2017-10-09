// ClipboardData.cpp: implementation of the CClipboardData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "ClipboardData.h"
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

CClipboardData::CClipboardData()
{

}

CClipboardData::~CClipboardData()
{
	EmptyAndDeallocateClipboardData ();
}

// deallocates the elements then resizes the array to 0
void CClipboardData::EmptyAndDeallocateClipboardData()
{
	// delete each of the individual elements
	int nCounter;
	for (nCounter = 0; nCounter < m_arrayPrimitives.GetSize (); nCounter++)
	{
		delete m_arrayPrimitives.GetAt (nCounter);
	}
	m_arrayPrimitives.RemoveAll ();
}


int CClipboardData::GetNumberOfPrimitives()
{
	return m_arrayPrimitives.GetSize ();
}

void CClipboardData::AddPrimitive(CPrimitive *pPrimitive)
{
	ASSERT (pPrimitive);
	// Create a copy to store on the clipboard
	CPrimitive* pPrimitiveCopy;
	try {
		if (typeid (*pPrimitive) == typeid (CPrimitiveSphere))
			pPrimitiveCopy = new CPrimitiveSphere(*(reinterpret_cast<CPrimitiveSphere*> (pPrimitive)));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveCone))
			pPrimitiveCopy = new CPrimitiveCone(*(reinterpret_cast<CPrimitiveCone*> (pPrimitive)));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveBlock))
			pPrimitiveCopy = new CPrimitiveBlock(*(reinterpret_cast<CPrimitiveBlock*> (pPrimitive)));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveCylinder))
			pPrimitiveCopy = new CPrimitiveCylinder(*(reinterpret_cast<CPrimitiveCylinder*> (pPrimitive)));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveHemisphere))
			pPrimitiveCopy = new CPrimitiveHemisphere(*(reinterpret_cast<CPrimitiveHemisphere*> (pPrimitive)));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveTruncatedCone))
			pPrimitiveCopy = new CPrimitiveTruncatedCone(*(reinterpret_cast<CPrimitiveTruncatedCone*> (pPrimitive)));
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

// note this is a copy so it is still 'on' the clipboard
CPrimitive* CClipboardData::GetPrimitiveCopy(int nIndex)
{
	ASSERT (nIndex < m_arrayPrimitives.GetSize ());
	CPrimitive* pPrimitive = m_arrayPrimitives.GetAt (nIndex);
	ASSERT (pPrimitive);
	CPrimitive* pPrimitiveCopy;
	try {
		if (typeid (*pPrimitive) == typeid (CPrimitiveSphere))
			pPrimitiveCopy = new CPrimitiveSphere(*(reinterpret_cast<CPrimitiveSphere*> (pPrimitive)));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveCone))
			pPrimitiveCopy = new CPrimitiveCone(*(reinterpret_cast<CPrimitiveCone*> (pPrimitive)));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveBlock))
			pPrimitiveCopy = new CPrimitiveBlock(*(reinterpret_cast<CPrimitiveBlock*> (pPrimitive)));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveCylinder))
			pPrimitiveCopy = new CPrimitiveCylinder(*(reinterpret_cast<CPrimitiveCylinder*> (pPrimitive)));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveHemisphere))
			pPrimitiveCopy = new CPrimitiveHemisphere(*(reinterpret_cast<CPrimitiveHemisphere*> (pPrimitive)));
		else if (typeid (*pPrimitive) == typeid (CPrimitiveTruncatedCone))
			pPrimitiveCopy = new CPrimitiveTruncatedCone(*(reinterpret_cast<CPrimitiveTruncatedCone*> (pPrimitive)));
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
	return pPrimitiveCopy;
}
