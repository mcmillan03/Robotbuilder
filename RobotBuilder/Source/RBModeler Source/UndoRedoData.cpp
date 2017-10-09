// UndoRedoData.cpp: implementation of the CUndoRedoData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "UndoRedoData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUndoRedoData::CUndoRedoData()
{
	m_CurrentModel.pModel = NULL;
	m_CurrentModel.strDescription = "";
}

CUndoRedoData::~CUndoRedoData()
{
	EmptyAndDeallocateUndoRedoData ();
}

// this will create a copy of the passed pointer and save that
void CUndoRedoData::PushUndoData(CModel *pModel, CString strDescription)
{
	ASSERT (pModel);

	// Any time an undo state is added, any possible Redo states are no longer possible
	// Consequently need to clear out redo states.
	EmptyRedoStack ();

	// Note the arrays are interpretted as stacks - push/pop the last element
	ModelData NewModelData;
	NewModelData.pModel = pModel;
	NewModelData.strDescription = strDescription;

	m_arrayUndo.Add (NewModelData);
}


void CUndoRedoData::EmptyRedoStack()
{
	int nCounter;
	int nStackSize = m_arrayRedo.GetSize ();
	
	// Go through each model and deallocate it.
	for (nCounter = 0; nCounter < nStackSize; nCounter++)
	{
		ModelData Model = m_arrayRedo.GetAt (nCounter);
		delete Model.pModel;
	}

	// Now the memory for the models has been deallocated, empty the array
	m_arrayRedo.RemoveAll ();
}

void CUndoRedoData::EmptyUndoStack()
{
	int nCounter;
	int nStackSize = m_arrayUndo.GetSize ();
	
	// Go through each model and deallocate it.
	for (nCounter = 0; nCounter < nStackSize; nCounter++)
	{
		ModelData Model = m_arrayUndo.GetAt (nCounter);
		delete Model.pModel;
	}

	// Now the memory for the models has been deallocated, empty the array
	m_arrayUndo.RemoveAll ();
}

void CUndoRedoData::EmptyAndDeallocateUndoRedoData()
{
	EmptyRedoStack ();
	EmptyUndoStack ();
	
	// Also clear the current state
	if (m_CurrentModel.pModel)
	{
		delete m_CurrentModel.pModel;
		m_CurrentModel.pModel = NULL;
	}

}


BOOL CUndoRedoData::GetIsUndoAvailable()
{
	if (m_arrayUndo.GetSize () > 0)
		return TRUE;
	else
		return FALSE;
}

BOOL CUndoRedoData::GetIsRedoAvailable()
{
	if (m_arrayRedo.GetSize () > 0)
		return TRUE;
	else
		return FALSE;
}

// Do not call SetCurrentData after popping - the pop function takes care of it
CModel* CUndoRedoData::PopUndoData()
{
	// It is expected that this function will only be called if there are stacked data 
	// states
	ASSERT (m_arrayUndo.GetSize () > 0);

	int nLastIndex = m_arrayUndo.GetUpperBound ();
	ModelData MostRecentModelData = m_arrayUndo.GetAt (nLastIndex);
	// Take is off the undo stack
	m_arrayUndo.RemoveAt(nLastIndex);
	// Create a copy to return
	CModel* pNewModel;
	// create a copy of it
	try {
		pNewModel = new CModel(*MostRecentModelData.pModel);
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	// Whenever anything is popped from the undo stack, the current state is pushed
	// on to the redo stack, and the popped model is made the current state

	PushRedoData (m_CurrentModel.pModel, m_CurrentModel.strDescription);

	m_CurrentModel.pModel = MostRecentModelData.pModel;
	m_CurrentModel.strDescription = MostRecentModelData.strDescription;

	return pNewModel;

}

void CUndoRedoData::PushRedoData(CModel *pModel, CString strDescription)
{
	ASSERT (pModel);

	// Note the arrays are interpretted as stacks - push/pop the last element
	ModelData NewModelData;
	NewModelData.pModel = pModel;
	NewModelData.strDescription = strDescription;

	m_arrayRedo.Add (NewModelData);
}

void CUndoRedoData::SetCurrentData(const CModel *pModel, CString strDescription)
{
	ASSERT (pModel);


	// Push the old current state to the undo stack, but only if the data
	// is valid - this is used to determine if its the first time the SetCurrentData
	// function was called, at which point the there will not be valid data for
	// the m_CurrentModel
	if (m_CurrentModel.pModel)
		PushUndoData (m_CurrentModel.pModel, m_CurrentModel.strDescription);

	CModel* pNewModel;
	// create a copy of it
	try {
		pNewModel = new CModel(*pModel);
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	// Reset the current state
	m_CurrentModel.pModel = pNewModel;
	m_CurrentModel.strDescription = strDescription;
}

CModel* CUndoRedoData::PopRedoData()
{
	// It is expected that this function will only be called if there are stacked data 
	// states
	ASSERT (m_arrayRedo.GetSize () > 0);

	int nLastIndex = m_arrayRedo.GetUpperBound ();
	ModelData MostRecentRedoModelData = m_arrayRedo.GetAt (nLastIndex);
	// Take is off the undo stack
	m_arrayRedo.RemoveAt(nLastIndex);
	// Create a copy to return
	CModel* pNewModel;
	// create a copy of it
	try {
		pNewModel = new CModel(*MostRecentRedoModelData.pModel);
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	// Whenever anything is popped from the redo stack, the current state is pushed
	// on to the undo stack, and the popped model is made the current state

	PushUndoData (m_CurrentModel.pModel, m_CurrentModel.strDescription);

	m_CurrentModel.pModel = MostRecentRedoModelData.pModel;
	m_CurrentModel.strDescription = MostRecentRedoModelData.strDescription;

	return pNewModel;
}

int CUndoRedoData::GetNumberOfUndoStates()
{
	return m_arrayUndo.GetSize ();
}

int CUndoRedoData::GetNumberOfRedoStates()
{
	return m_arrayRedo.GetSize ();
}

// 0 based - with 0 being most recent
CString CUndoRedoData::GetUndoDescription(int nIndex)
{
	ASSERT (nIndex > 0 && nIndex < m_arrayUndo.GetSize ());

	return m_arrayUndo.GetAt (nIndex).strDescription;
}

CString CUndoRedoData::GetRedoDescription(int nIndex)
{
	ASSERT (nIndex > 0 && nIndex < m_arrayRedo.GetSize ());

	return m_arrayRedo.GetAt (nIndex).strDescription;
}
