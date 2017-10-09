// ModelListView.cpp : implementation of the CModelListView class
//

#include "stdafx.h"
#include "RBModeler.h"

#include "RBModelerDoc.h"
#include "ModelListView.h"
#include "RBModelerRBMGraphicView.h"

#include "PSheetSphere.h"
#include "PSheetBlock.h"
#include "PSheetCone.h"
#include "PSheetCylinder.h"
#include "PSheetHemisphere.h"
#include "PSheetTruncatedCone.h"

#include "PrimitiveSphere.h"
#include "PrimitiveBlock.h"
#include "PrimitiveCone.h"
#include "PrimitiveCylinder.h"
#include "PrimitiveHemisphere.h"
#include "PrimitiveTruncatedCone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelListView

IMPLEMENT_DYNCREATE(CModelListView, CListView)

BEGIN_MESSAGE_MAP(CModelListView, CListView)
	//{{AFX_MSG_MAP(CModelListView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(ID_POPUP_RENAME, OnPopupRename)
	ON_COMMAND(ID_POPUP_PROPERTIES, OnPopupProperties)
	ON_COMMAND(ID_POPUP_DELETE, OnPopupDelete)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_COMMAND(ID_POPUP_PRIMITIVE_BLOCK, OnPopupAddBlock)
	ON_COMMAND(ID_POPUP_PRIMITIVE_CONE, OnPopupAddCone)
	ON_COMMAND(ID_POPUP_PRIMITIVE_CYLINDER, OnPopupAddCylinder)
	ON_COMMAND(ID_POPUP_PRIMITIVE_HEMISPHERE, OnPopupAddHemisphere)
	ON_COMMAND(ID_POPUP_PRIMITIVE_SPHERE, OnPopupAddSphere)
	ON_COMMAND(ID_POPUP_PRIMITIVE_TRUNCATED_CONE, OnPopupAddTruncatedCone)
	ON_COMMAND(ID_POPUP_SHOWAXES, OnPopupShowAxes)
	ON_COMMAND(ID_POPUP_CAMERA_COI, OnPopupCameraCOI)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CModelListView construction/destruction

CModelListView::CModelListView()
{

}

CModelListView::~CModelListView()
{
}

BOOL CModelListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= (LVS_REPORT | LVS_EDITLABELS | LVS_SORTASCENDING | LVS_NOSORTHEADER | LVS_SHOWSELALWAYS);

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CModelListView drawing

void CModelListView::OnDraw(CDC* pDC)
{
	CRBModelerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void CModelListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: You may populate your ListView with items by directly accessing
	// Setep Header Control for the Listview
/*	HDITEM HDItem;
	HDItem.mask = HDI_TEXT | HDI_FORMAT;
	HDItem.pszText = "Howdy";
	HDItem.cchTextMax = 5;
	HDItem.fmt = HDF_CENTER | HDF_STRING;

	GetListCtrl ().GetHeaderCtrl ()->InsertItem (0, &HDItem);

	
	
	//  its List control through a call to GetListCtrl().
	GetListCtrl ().InsertItem (0, "Item2", 2);
	GetListCtrl ().InsertItem (1, "Item1", 1);

	LVITEM lvitem;
	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = 1;
	lvitem.iSubItem = 1;
	lvitem.pszText = "Sphere";
	lvitem.cchTextMax = 6;
	lvitem.iImage = 3;

	GetListCtrl ().SetItem (&lvitem);
	GetListCtrl ().SetItem (0, 1, LVIF_TEXT, "Cone", 0, 0, 0, 0);
	DWORD dwError = GetLastError ();
*/

}

/////////////////////////////////////////////////////////////////////////////
// CModelListView diagnostics

#ifdef _DEBUG
void CModelListView::AssertValid() const
{
	CListView::AssertValid();
}

void CModelListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CRBModelerDoc* CModelListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRBModelerDoc)));
	return (CRBModelerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CModelListView message handlers

int CModelListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_ImageList.Create (IDB_IMAGELIST, 16, 1, RGB (255, 255, 255));
	// todo: use user-defined states to create custom images
	GetListCtrl ().SetImageList (&m_ImageList, LVSIL_SMALL);
	

	GetListCtrl ().InsertColumn (0, "Name", LVCFMT_CENTER, 87);
	GetListCtrl ().InsertColumn (1, "Primitive Type", LVCFMT_CENTER, 90, 1);

	// Load the bitmaps for the context menu
	m_bitmapPrimitives[BMP_PRIMITIVE_SPHERE].LoadBitmap (IDB_PRIMITIVE_SPHERE);
	m_bitmapPrimitives[BMP_PRIMITIVE_BLOCK].LoadBitmap (IDB_PRIMITIVE_BLOCK);
	m_bitmapPrimitives[BMP_PRIMITIVE_CONE].LoadBitmap (IDB_PRIMITIVE_CONE);
	m_bitmapPrimitives[BMP_PRIMITIVE_CYLINDER].LoadBitmap (IDB_PRIMITIVE_CYLINDER);
	m_bitmapPrimitives[BMP_PRIMITIVE_HEMISPHERE].LoadBitmap (IDB_PRIMITIVE_HEMISPHERE);
	m_bitmapPrimitives[BMP_PRIMITIVE_TRUNCATED_CONE].LoadBitmap (IDB_PRIMITIVE_TRUNCATED_CONE);	

	return 0;
}


void CModelListView::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	// if there is text, make it the new label
	if (pDispInfo->item.pszText)
	{
		// Make it the name of the primitive - note the item data
		// is the lParam of the item is the settable user data
		CPrimitive* pPrimitive = (CPrimitive*) pDispInfo->item.lParam;
		ASSERT (pPrimitive);
		pPrimitive->SetName (pDispInfo->item.pszText);
		// Force the rearrangement so that it the order is maintained with the
		// the new name.
		SortItem (pDispInfo->item.iItem);
		// Register the model change
		ModelStateChanged ("Rename Item");
		// This is a continuation of the workaround to force the correct sort after a lable
		// edit.  If I return TRUE to keep the label change, the framework will change the
		// item with the wrong index because the order has changed since I resort it.  The
		// name change has already taken effect though by the forced sort, so I will return
		// FALSE.
		*pResult = 0;
	}
	else
	{
		*pResult = 0;
	}

}

// return value for this notification is not used by the framework
void CModelListView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// I think only one or zero can be selected when this is handled
	ASSERT (GetListCtrl ().GetSelectedCount () == 1 ||
		GetListCtrl ().GetSelectedCount () == 0);

	// If there isn't any selected, don't do anything.  Otherwise open the
	// the property box of the selected item
	if (GetListCtrl ().GetSelectedCount () > 0)
	{
		POSITION posSelectedItem = GetListCtrl ().GetFirstSelectedItemPosition ();
		// This should contain a value since there is one selected
		ASSERT (posSelectedItem);
		
		// Get the index in the list of the selected item
		int nListIndex = GetListCtrl ().GetNextSelectedItem (posSelectedItem);
		ASSERT (nListIndex >= 0);

		ShowPrimitiveProperties (nListIndex);

	}
	// else there isn't one selected so don't do anything

	*pResult = 0;
}

void CModelListView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POINT pointPos;
	if (!GetCursorPos ((LPPOINT) &pointPos))
	{
		AfxMessageBox ("Error - Failed to retrieve the current position");
	}
	
	// Primitives menu
	CMenu menuPrimitivesPopup;
	menuPrimitivesPopup.CreatePopupMenu ();
	menuPrimitivesPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PRIMITIVE_BLOCK, 
		"Block");
	menuPrimitivesPopup.SetMenuItemBitmaps (ID_POPUP_PRIMITIVE_BLOCK, MF_BYCOMMAND, 
		&m_bitmapPrimitives[BMP_PRIMITIVE_BLOCK], &m_bitmapPrimitives[BMP_PRIMITIVE_BLOCK]);

	menuPrimitivesPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PRIMITIVE_CONE, 
		"Cone");
	menuPrimitivesPopup.SetMenuItemBitmaps (ID_POPUP_PRIMITIVE_CONE, MF_BYCOMMAND, 
		&m_bitmapPrimitives[BMP_PRIMITIVE_CONE], &m_bitmapPrimitives[BMP_PRIMITIVE_CONE]);

	menuPrimitivesPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PRIMITIVE_CYLINDER, 
		"Cylinder");
	menuPrimitivesPopup.SetMenuItemBitmaps (ID_POPUP_PRIMITIVE_CYLINDER, MF_BYCOMMAND, 
		&m_bitmapPrimitives[BMP_PRIMITIVE_CYLINDER], &m_bitmapPrimitives[BMP_PRIMITIVE_CYLINDER]);

	menuPrimitivesPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PRIMITIVE_HEMISPHERE, 
		"Hemisphere");
	menuPrimitivesPopup.SetMenuItemBitmaps (ID_POPUP_PRIMITIVE_HEMISPHERE, MF_BYCOMMAND, 
		&m_bitmapPrimitives[BMP_PRIMITIVE_HEMISPHERE], &m_bitmapPrimitives[BMP_PRIMITIVE_HEMISPHERE]);

	menuPrimitivesPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PRIMITIVE_SPHERE, 
		"Sphere");
	menuPrimitivesPopup.SetMenuItemBitmaps (ID_POPUP_PRIMITIVE_SPHERE, MF_BYCOMMAND, 
		&m_bitmapPrimitives[BMP_PRIMITIVE_SPHERE], &m_bitmapPrimitives[BMP_PRIMITIVE_SPHERE]);

	menuPrimitivesPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PRIMITIVE_TRUNCATED_CONE, 
		"Truncated Cone");
	menuPrimitivesPopup.SetMenuItemBitmaps (ID_POPUP_PRIMITIVE_TRUNCATED_CONE, MF_BYCOMMAND, 
		&m_bitmapPrimitives[BMP_PRIMITIVE_TRUNCATED_CONE], &m_bitmapPrimitives[BMP_PRIMITIVE_TRUNCATED_CONE]);

	

	CMenu menuPopup;
	menuPopup.CreatePopupMenu ();
	// Build the menu based on the number selected
//	menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_ADD, "Add");
	menuPopup.AppendMenu (MF_STRING | MF_ENABLED | MF_POPUP,(UINT) menuPrimitivesPopup.m_hMenu, "Add");
	if (m_Clipboard.GetNumberOfPrimitives () > 0)
		menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_EDIT_PASTE, "Paste");
	else
		menuPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_EDIT_PASTE, "Paste");


	if (GetListCtrl ().GetSelectedCount () > 0)
	{
		menuPopup.AppendMenu (MF_SEPARATOR);
		menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_DELETE, "Delete");
		menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_EDIT_CUT, "Cut");
		menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_EDIT_COPY, "Copy");
//		menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PASTE, "Paste");

		if (GetListCtrl ().GetSelectedCount () == 1)
		{
			POSITION posItem = GetListCtrl ().GetFirstSelectedItemPosition ();
			ASSERT (posItem);
			int nListIndex = GetListCtrl ().GetNextSelectedItem (posItem);
			ASSERT (nListIndex >= 0);
			CPrimitive *pPrimitive = reinterpret_cast<CPrimitive*> (GetListCtrl ().GetItemData (nListIndex));
			ASSERT (pPrimitive);

			
			menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_RENAME, "Rename");
			menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PROPERTIES, "Properties...");

			menuPopup.AppendMenu (MF_SEPARATOR);
			if (pPrimitive->ShowWtkAxes ())
				menuPopup.AppendMenu (MF_STRING | MF_ENABLED | MF_CHECKED, ID_POPUP_SHOWAXES, "Show Axes");
			else
				menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SHOWAXES, "Show Axes");
			// COI
			if (GetDocument ()->GetCameraData ()->GetViewInPanMode ())
			{
				// In pan mode - COI meaningless
				if (pPrimitive->IsCameraCenterOfInterest ())
					menuPopup.AppendMenu (MF_STRING | MF_CHECKED | MF_GRAYED, ID_POPUP_CAMERA_COI, "Center Of Interest");
				else
					menuPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_CAMERA_COI, "Center Of Interest");
			}
			else
			{
				if (pPrimitive->IsCameraCenterOfInterest ())
					menuPopup.AppendMenu (MF_STRING | MF_ENABLED | MF_CHECKED, ID_POPUP_CAMERA_COI, "Center Of Interest");
				else
					menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_CAMERA_COI, "Center Of Interest");
			}
		
		}
	}

	menuPopup.TrackPopupMenu (TPM_LEFTALIGN | TPM_LEFTBUTTON, pointPos.x, pointPos.y, this);

	*pResult = 0;
}

void CModelListView::OnPopupRename() 
{
	// I believe this should only be called when there is one and only one
	// item selected
	ASSERT (GetListCtrl ().GetSelectedCount () == 1);

	POSITION posItem = GetListCtrl ().GetFirstSelectedItemPosition ();
	ASSERT (posItem);
	int nListIndex = GetListCtrl ().GetNextSelectedItem (posItem);
	ASSERT (nListIndex >= 0);

	// Rename the label
	GetListCtrl ().EditLabel (nListIndex);
}

void CModelListView::OnPopupProperties() 
{
	// I believe this should only be called when there is one and only one
	// item selected
	ASSERT (GetListCtrl ().GetSelectedCount () == 1);

	POSITION posItem = GetListCtrl ().GetFirstSelectedItemPosition ();
	ASSERT (posItem);
	int nListIndex = GetListCtrl ().GetNextSelectedItem (posItem);
	ASSERT (nListIndex >= 0);

	// Show the properties
	ShowPrimitiveProperties (nListIndex);
}

void CModelListView::OnPopupDelete() 
{
	// I can't use the GetFirstSelected... outright because if I delete an item
	// in changes the indexing which confuses the GetNextSelected...
	// So, I will save the indexes in an array then go backwards through the array
	// to delete the elements
	int nNumSelected = GetListCtrl ().GetSelectedCount ();
	ASSERT (nNumSelected > 0);

	// Allocate the array
	int* pIndexArray;
	try {
		pIndexArray = new int [nNumSelected];
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}


	// Copy the array
	POSITION posSelected = GetListCtrl ().GetFirstSelectedItemPosition ();
	ASSERT (posSelected);
	int nIndex = 0;
	while (posSelected)
	{
		// Get the index to the selected item
		pIndexArray[nIndex] = GetListCtrl ().GetNextSelectedItem (posSelected);	
		nIndex++;
	}
	ASSERT (nNumSelected == nIndex);

	// Now go through the array backwards and delete them

	for (nIndex = nNumSelected - 1; nIndex >= 0; nIndex--)
	{
		// Get the data of the selected item
		CPrimitive* pPrimitive = (CPrimitive*) GetListCtrl ().GetItemData (pIndexArray[nIndex]);
		ASSERT (pPrimitive);
		// Remove it from the list
		DeletePrimitiveFromList (pIndexArray[nIndex]);
		// Remove from 3D view
		CRBModelerRBMGraphicView::DeletePrimitive (pPrimitive);
		// delete it
		GetModel ()->DeletePrimitive (pPrimitive);
	}
	
	// Deallocate the index array
	delete [] pIndexArray;

	ModelStateChanged ("Delete");
}

// I use my own clipboard for this version
void CModelListView::OnEditCopy() 
{
	int nNumberSelected = GetListCtrl ().GetSelectedCount ();
	// It is assumed that the copy button will only be enabled when there are 
	// list items selected
	ASSERT (nNumberSelected > 0);

	// Clear any data currently on the clipboard
	m_Clipboard.EmptyAndDeallocateClipboardData ();

	// Add each selected item to my clipboard
	POSITION posSelected = GetListCtrl ().GetFirstSelectedItemPosition ();
	ASSERT (posSelected);

	while (posSelected)
	{
		// Get the index to the selected item
		int nSelectedIndex = GetListCtrl ().GetNextSelectedItem (posSelected);
		// Get the data of the selected item
		CPrimitive* pPrimitive = (CPrimitive*) GetListCtrl ().GetItemData (nSelectedIndex);
		ASSERT (pPrimitive);
		m_Clipboard.AddPrimitive (pPrimitive);
	}
}

void CModelListView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	if (GetListCtrl ().GetSelectedCount () > 0)
		pCmdUI->Enable ();
	else
		pCmdUI->Enable (FALSE);
	
}

void CModelListView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// Only enable when it has the focus and there is something to paste
	if (GetFocus () == this && m_Clipboard.GetNumberOfPrimitives () > 0)
		pCmdUI->Enable ();
	else
		pCmdUI->Enable (FALSE);	
}

void CModelListView::AddPrimitive(CPrimitive *pPrimitive)
{
	CString strPrimitiveLabel; // holds the text for the 'Primitive Type' column
	int nImageIndex; // holds the index for the image

	if (typeid (*pPrimitive) == typeid (CPrimitiveSphere))
	{
		strPrimitiveLabel = "Sphere";
		nImageIndex = N_SPHERE_IMAGE;
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveBlock))
	{
		strPrimitiveLabel = "Block";
		nImageIndex = N_BLOCK_IMAGE;
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveCone))
	{
		strPrimitiveLabel = "Cone";
		nImageIndex = N_CONE_IMAGE;
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveCylinder))
	{
		strPrimitiveLabel = "Cylinder";
		nImageIndex = N_CYLINDER_IMAGE;
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveHemisphere))
	{
		strPrimitiveLabel = "Hemisphere";
		nImageIndex = N_HEMISPHERE_IMAGE;
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveTruncatedCone))
	{
		strPrimitiveLabel = "TruncatedCone";
		nImageIndex = N_TRUNCATED_CONE_IMAGE;
	}
	else
	{
		ASSERT (FALSE);
	}

	// The index doesn't really matter since the list has a style set to alphabetize
	int nNewIndex = GetListCtrl ().InsertItem (0, pPrimitive->GetName (), nImageIndex);
	ASSERT (nNewIndex != -1);
	// Set the text in the second column
	BOOL bSuccess = GetListCtrl ().SetItem (nNewIndex, 1, LVIF_TEXT, strPrimitiveLabel, 0, 0, 0, 0);
	ASSERT (bSuccess);
	// Save the pointer as the item data
	bSuccess = GetListCtrl ().SetItemData (nNewIndex, reinterpret_cast<DWORD> (pPrimitive));
	ASSERT (bSuccess);
}

void CModelListView::LoadNewModel(CModel *pModel)
{
	// First clear the list control
	BOOL bSuccess = GetListCtrl ().DeleteAllItems ();
	ASSERT (bSuccess);
	
	// Go through each primitive of the model and add it
	int nCounter;
	for (nCounter = 0; nCounter < pModel->GetNumberOfPrimitives (); nCounter++)
	{
		AddPrimitive (pModel->GetPrimitive (nCounter));
	}
}

void CModelListView::OnEditPaste() 
{
	// Add a copy of each thing on the clipboard to the model, to the list and to the
	// 3D view

	// It is assumed that this will only be called if there is something on the clipboard
	ASSERT (m_Clipboard.GetNumberOfPrimitives () > 0);

	int nNumberOfPrimitives = m_Clipboard.GetNumberOfPrimitives ();
	int nCounter;
	for (nCounter = 0; nCounter < nNumberOfPrimitives; nCounter++)
	{
		CPrimitive* pPrimitive = m_Clipboard.GetPrimitiveCopy (nCounter);
		ASSERT (pPrimitive);

		// Add to model
		GetModel ()->AddPrimitive (pPrimitive);
		// Add to List
		this->AddPrimitive (pPrimitive);
		// Add to 3D view
		CRBModelerRBMGraphicView::AddPrimitive (pPrimitive);
	}
	
	ModelStateChanged ("Paste");
}

CModel* CModelListView::GetModel()
{
	CModel* pModel = GetDocument ()->GetModel ();
	ASSERT (pModel);

	return pModel;
}

void CModelListView::DeletePrimitiveFromList(int nIndex)
{
	BOOL bSuccess = GetListCtrl ().DeleteItem (nIndex);
	ASSERT (bSuccess);
}

// basically same as OnEditCopy, but delete them too
void CModelListView::OnEditCut() 
{
	int nNumberSelected = GetListCtrl ().GetSelectedCount ();
	// It is assumed that the copy button will only be enabled when there are 
	// list items selected
	ASSERT (nNumberSelected > 0);

	// Clear any data currently on the clipboard
	m_Clipboard.EmptyAndDeallocateClipboardData ();

	// Add each selected item to my clipboard
	POSITION posSelected = GetListCtrl ().GetFirstSelectedItemPosition ();
	ASSERT (posSelected);

	while (posSelected)
	{
		// Get the index to the selected item
		int nSelectedIndex = GetListCtrl ().GetNextSelectedItem (posSelected);
		// Get the data of the selected item
		CPrimitive* pPrimitive = (CPrimitive*) GetListCtrl ().GetItemData (nSelectedIndex);
		ASSERT (pPrimitive);
		m_Clipboard.AddPrimitive (pPrimitive);
	}

	// I can't use the GetFirstSelected... outright because if I delete an item
	// in changes the indexing which confuses the GetNextSelected...
	// So, I will save the indexes in an array then go backwards through the array
	// to delete the elements (or I could make a recursive call to a delete function)
	int nNumSelected = GetListCtrl ().GetSelectedCount ();
	ASSERT (nNumSelected > 0);

	// Allocate the array
	int* pIndexArray;
	try {
		pIndexArray = new int [nNumSelected];
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}


	// Copy the array
	posSelected = GetListCtrl ().GetFirstSelectedItemPosition ();
	ASSERT (posSelected);
	int nIndex = 0;
	while (posSelected)
	{
		// Get the index to the selected item
		pIndexArray[nIndex] = GetListCtrl ().GetNextSelectedItem (posSelected);	
		nIndex++;
	}
	ASSERT (nNumSelected == nIndex);

	// Now go through the array backwards and delete them

	for (nIndex = nNumSelected - 1; nIndex >= 0; nIndex--)
	{
		// Get the data of the selected item
		CPrimitive* pPrimitive = (CPrimitive*) GetListCtrl ().GetItemData (pIndexArray[nIndex]);
		ASSERT (pPrimitive);
		// Remove it from the list
		DeletePrimitiveFromList (pIndexArray[nIndex]);
		// Remove from 3D view
		CRBModelerRBMGraphicView::DeletePrimitive (pPrimitive);
		// delete it
		GetModel ()->DeletePrimitive (pPrimitive);
	}
	
	// Deallocate the index array
	delete [] pIndexArray;
	
	ModelStateChanged ("Delete - Cut");
}

void CModelListView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	if (GetListCtrl ().GetSelectedCount () > 0)
		pCmdUI->Enable ();
	else
		pCmdUI->Enable (FALSE);
}

void CModelListView::SortItem(int nIndex)
{
	// There should be a better way to do this, but I can't seem to find it.
	// In order to sort, I will remove it from the list, then reinsert it.  Upon
	// insertion, the framework properly sorts it.

	// First save a copy of the data
	CPrimitive* pPrimitive = reinterpret_cast <CPrimitive*> (GetListCtrl ().GetItemData (nIndex));
	ASSERT (pPrimitive);
	// Now delete it from the list
	DeletePrimitiveFromList (nIndex);
	// Add it back in
	AddPrimitive (pPrimitive);
}

void CModelListView::ModelStateChanged(CString strDescription)
{
	m_UndoRedoData.SetCurrentData (GetModel (), strDescription);	
}

void CModelListView::OnEditUndo() 
{
	/* 21 JUN 2002 SJR - this was not implemented completely and kind of buggy
		The functionality was removed for now 
	CModel* pUndoModel = m_UndoRedoData.PopUndoData ();
	ASSERT (pUndoModel);

	// Set the undo model as the current model in the document - this will take
	// care of deallocating the current model
	GetDocument()->SetModel (pUndoModel);

	// Now reload the list with the undo model
	LoadNewModel (pUndoModel);

	// Now update the 3D view
	CRBModelerRBMGraphicView::LoadNewModel (pUndoModel); */
}

void CModelListView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_UndoRedoData.GetIsUndoAvailable ());	
}

// Intended to be called from the document when a new model is opened/newed
void CModelListView::LoadNewModelAndReset(CModel *pModel)
{
	ASSERT (pModel);

	// Clear the Undo Redo data since its a new document
	m_UndoRedoData.EmptyAndDeallocateUndoRedoData ();

	// Load the list view with the model
	LoadNewModel (pModel);

	// Set the current data as the current model
	m_UndoRedoData.SetCurrentData (pModel, "");

}

void CModelListView::OnEditRedo() 
{
	/* 21 JUN 2002 SJR - this was not implemented completely and kind of buggy
		The functionality was removed for now 
	CModel* pRedoModel = m_UndoRedoData.PopRedoData ();
	ASSERT (pRedoModel);

	// Set the undo model as the current model in the document - this will take
	// care of deallocating the current model
	GetDocument()->SetModel (pRedoModel);

	// Now reload the list with the redo model
	LoadNewModel (pRedoModel);

	// Now update the 3D view
	CRBModelerRBMGraphicView::LoadNewModel (pRedoModel);*/
}

void CModelListView::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable (m_UndoRedoData.GetIsRedoAvailable ());	
}

void CModelListView::ShowPrimitiveProperties(int nIndex)
{
	CPrimitive* pPrimitive; // Pointer to data

	// Get the data
	pPrimitive = reinterpret_cast <CPrimitive*> (GetListCtrl ().GetItemData (nIndex));
	ASSERT (pPrimitive);

	// Open properties based on primitive type
	if (typeid (*pPrimitive) == typeid (CPrimitiveSphere))
	{
		CPSheetSphere PSheet ("Sphere Properties");
		PSheet.SetData (dynamic_cast <CPrimitiveSphere*> (pPrimitive));

		if (PSheet.DoModal () == IDOK)
		{
			// Note the 3D view is updated inside the PPage class by the OnApply handler

			// So save the data for the undo/redo
			m_UndoRedoData.SetCurrentData (GetModel (), "Primitive Properties Change");
		}
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveBlock))
	{
		CPSheetBlock PSheet ("Block Properties");
		PSheet.SetData (dynamic_cast <CPrimitiveBlock*> (pPrimitive));

		if (PSheet.DoModal () == IDOK)
		{
			// Note the 3D view is updated inside the PPage class by the OnApply handler

			// So save the data for the undo/redo
			m_UndoRedoData.SetCurrentData (GetModel (), "Primitive Properties Change");
		}
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveCone))
	{
		CPSheetCone PSheet ("Cone Properties");
		PSheet.SetData (dynamic_cast <CPrimitiveCone*> (pPrimitive));

		if (PSheet.DoModal () == IDOK)
		{
			// Note the 3D view is updated inside the PPage class by the OnApply handler

			// So save the data for the undo/redo
			m_UndoRedoData.SetCurrentData (GetModel (), "Primitive Properties Change");
		}
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveCylinder))
	{
		CPSheetCylinder PSheet ("Cylinder Properties");
		PSheet.SetData (dynamic_cast <CPrimitiveCylinder*> (pPrimitive));

		if (PSheet.DoModal () == IDOK)
		{
			// Note the 3D view is updated inside the PPage class by the OnApply handler

			// So save the data for the undo/redo
			m_UndoRedoData.SetCurrentData (GetModel (), "Primitive Properties Change");
		}
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveHemisphere))
	{
		CPSheetHemisphere PSheet ("Hemisphere Properties");
		PSheet.SetData (dynamic_cast <CPrimitiveHemisphere*> (pPrimitive));

		if (PSheet.DoModal () == IDOK)
		{
			// Note the 3D view is updated inside the PPage class by the OnApply handler

			// So save the data for the undo/redo
			m_UndoRedoData.SetCurrentData (GetModel (), "Primitive Properties Change");
		}
	}
	else if (typeid (*pPrimitive) == typeid (CPrimitiveTruncatedCone))
	{
		CPSheetTruncatedCone PSheet ("Truncated Cone Properties");
		PSheet.SetData (dynamic_cast <CPrimitiveTruncatedCone*> (pPrimitive));

		if (PSheet.DoModal () == IDOK)
		{
			// Note the 3D view is updated inside the PPage class by the OnApply handler

			// So save the data for the undo/redo
			m_UndoRedoData.SetCurrentData (GetModel (), "Primitive Properties Change");
		}
	}

	
	else
		ASSERT (FALSE);

}


void CModelListView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	// Obtain a pointer to the primitive
	CPrimitive* pPrimitive = reinterpret_cast <CPrimitive*> 
		(GetListCtrl ().GetItemData (pNMListView->iItem));
	ASSERT (pPrimitive);

	// Note the uChanged field does not seem to be updated in pNMListView
	// Note: This function is called by the framework after the new primitive
	// has been create, but before it has been added to the graphic view.  Consequently,
	// I needed to add the special logic to only deselect the bounding box if
	// the item's previous state was selected (which is not the case when it
	// it is first created)
	if (pNMListView->uNewState & LVIS_SELECTED)
		CRBModelerRBMGraphicView::ShowBoundingBox (TRUE, pPrimitive);
	else if (pNMListView->uOldState & LVIS_SELECTED)
		CRBModelerRBMGraphicView::ShowBoundingBox (FALSE, pPrimitive);

	*pResult = 0;
}

void CModelListView::OnPopupAddBlock ()
{
	GetDocument ()->AddPrimitive (PT_BLOCK);
}

void CModelListView::OnPopupAddCone ()
{
	GetDocument ()->AddPrimitive (PT_CONE);
}

void CModelListView::OnPopupAddCylinder ()
{
	GetDocument ()->AddPrimitive (PT_CYLINDER);
}

void CModelListView::OnPopupAddHemisphere ()
{
	GetDocument ()->AddPrimitive (PT_HEMISPHERE);
}

void CModelListView::OnPopupAddSphere ()
{
	GetDocument ()->AddPrimitive (PT_SPHERE);
}

void CModelListView::OnPopupAddTruncatedCone ()
{
	GetDocument ()->AddPrimitive (PT_TRUNCATED_CONE);
}




void CModelListView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// todo: handle key board shortcuts to operate on the list
//	switch (nChar)
//	{
//	case VK_DELETE:
//		break;
//	}
	
	CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CModelListView::OnPopupShowAxes()
{
	// I believe this should only be called when there is one and only one
	// item selected
	ASSERT (GetListCtrl ().GetSelectedCount () == 1);

	POSITION posItem = GetListCtrl ().GetFirstSelectedItemPosition ();
	ASSERT (posItem);
	int nListIndex = GetListCtrl ().GetNextSelectedItem (posItem);
	ASSERT (nListIndex >= 0);

	CPrimitive *pPrimitive = reinterpret_cast<CPrimitive*> (GetListCtrl ().GetItemData (nListIndex));
	ASSERT (pPrimitive);

	// Toggle the axes state
	if (pPrimitive->ShowWtkAxes ())
		pPrimitive->ShowWtkAxes (FALSE);
	else
		pPrimitive->ShowWtkAxes (TRUE);
}

void CModelListView::OnPopupCameraCOI()
{
	// I believe this should only be called when there is one and only one
	// item selected
	ASSERT (GetListCtrl ().GetSelectedCount () == 1);

	POSITION posItem = GetListCtrl ().GetFirstSelectedItemPosition ();
	ASSERT (posItem);
	int nListIndex = GetListCtrl ().GetNextSelectedItem (posItem);
	ASSERT (nListIndex >= 0);

	CPrimitive *pPrimitive = reinterpret_cast<CPrimitive*> (GetListCtrl ().GetItemData (nListIndex));
	ASSERT (pPrimitive);

	// Get the model and clear the current COI
	GetDocument()->GetModel()->ClearCameraCenterOfInterest ();

	// Set as the new COI
	pPrimitive->IsCameraCenterOfInterest (TRUE);

	// Update the camera
	CRBModelerRBMGraphicView::UpdateCamera (FALSE);
}
