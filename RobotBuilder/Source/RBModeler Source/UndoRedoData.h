// UndoRedoData.h: interface for the CUndoRedoData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNDOREDODATA_H__44A972EF_454A_4A70_BA59_3ECF3DBDD37A__INCLUDED_)
#define AFX_UNDOREDODATA_H__44A972EF_454A_4A70_BA59_3ECF3DBDD37A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h> // array template support
#include "Model.h"
	typedef struct
	{
		CModel* pModel;
		CString strDescription;
	} ModelData;
class CUndoRedoData  
{


public:
	CString GetRedoDescription (int nIndex);
	CString GetUndoDescription (int nIndex);
	int GetNumberOfRedoStates ();
	int GetNumberOfUndoStates ();
	CModel* PopRedoData ();
	void SetCurrentData (const CModel *pModel, CString strDescription);
	CModel* PopUndoData ();
	BOOL GetIsRedoAvailable ();
	BOOL GetIsUndoAvailable ();
	void EmptyAndDeallocateUndoRedoData ();
	CUndoRedoData();
	virtual ~CUndoRedoData();
protected:
	void PushUndoData (CModel* pModel, CString strDescription);
	void PushRedoData (CModel* pModel, CString strDescription);
	void EmptyUndoStack ();
	void EmptyRedoStack ();
	CArray <ModelData, ModelData> m_arrayUndo;
	CArray <ModelData, ModelData> m_arrayRedo;
	ModelData m_CurrentModel;
};

#endif // !defined(AFX_UNDOREDODATA_H__44A972EF_454A_4A70_BA59_3ECF3DBDD37A__INCLUDED_)
