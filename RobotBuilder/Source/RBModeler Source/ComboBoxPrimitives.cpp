// ComboBoxPrimitives.cpp : implementation file
//

#include "stdafx.h"
#include "RBModeler.h"
#include "ComboBoxPrimitives.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Model.h"
#include "DlgMovementControls.h"
#include "PrimitiveBlock.h"
#include "PrimitiveCone.h"
#include "PrimitiveCylinder.h"
#include "PrimitiveHemisphere.h"
#include "PrimitiveSphere.h"
#include "PrimitiveTruncatedCone.h"

#define N_UNIVERSE_INDEX	0
#define N_LOCAL_INDEX		1
#define STR_UNIVERSE_LABEL	"Link frame"
#define STR_LOCAL_LABEL		"Local frame"

/////////////////////////////////////////////////////////////////////////////
// CComboBoxPrimitives

CComboBoxPrimitives::CComboBoxPrimitives()
{
}

CComboBoxPrimitives::~CComboBoxPrimitives()
{
}


BEGIN_MESSAGE_MAP(CComboBoxPrimitives, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxPrimitives)
	ON_WM_CREATE()
	ON_WM_COMPAREITEM()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboBoxPrimitives message handlers


void CComboBoxPrimitives::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC dc;
	dc.Attach (lpDrawItemStruct->hDC);
	int nIndex = lpDrawItemStruct->itemID;
	
	CRect rect = lpDrawItemStruct->rcItem;
	
	CBrush* pBrush;
	// First see if the state is enabled
	if (lpDrawItemStruct->itemState & ODS_DISABLED)
	{
		pBrush = new CBrush (::GetSysColor (COLOR_3DFACE));
	}
	else
	{
		pBrush = new CBrush (::GetSysColor ((lpDrawItemStruct->itemState & ODS_SELECTED) ?
			COLOR_HIGHLIGHT : COLOR_WINDOW));
	}

	dc.FillRect (rect, pBrush);
	delete pBrush;

	if (lpDrawItemStruct->itemState & ODS_FOCUS)
		dc.DrawFocusRect (rect);

	if (nIndex >= 0)
	{
		CString strLabel; // holds the text description for the current combo box item
		CBitmap bitmapPrimitive;

		// Remember the zero and one entries are special cases
		if (nIndex == N_UNIVERSE_INDEX)
		{
			strLabel = STR_UNIVERSE_LABEL;
			bitmapPrimitive.LoadBitmap (IDB_AXES);
		}
		else if (nIndex == N_LOCAL_INDEX)
		{
			strLabel = STR_LOCAL_LABEL;
			bitmapPrimitive.LoadBitmap (IDB_AXES);
		}
		else
		{
			CPrimitive* pPrimitive = reinterpret_cast <CPrimitive*> (GetItemDataPtr (nIndex));
			CString strNameLabel = pPrimitive->GetName ();
			CString strTypeLabel;

			if (typeid (*pPrimitive) == typeid (CPrimitiveBlock))
			{
				strTypeLabel = " - Block";
				bitmapPrimitive.LoadBitmap (IDB_PRIMITIVE_BLOCK);
			}
			else if (typeid (*pPrimitive) == typeid (CPrimitiveCone))
			{
				strTypeLabel = " - Cone";
				bitmapPrimitive.LoadBitmap (IDB_PRIMITIVE_CONE);
			}
			else if (typeid (*pPrimitive) == typeid (CPrimitiveCylinder))
			{
				strTypeLabel = " - Cylinder";
				bitmapPrimitive.LoadBitmap (IDB_PRIMITIVE_CYLINDER);
			}
			else if (typeid (*pPrimitive) == typeid (CPrimitiveHemisphere))
			{
				strTypeLabel = " - Hemisphere";
				bitmapPrimitive.LoadBitmap (IDB_PRIMITIVE_HEMISPHERE);
			}
			else if (typeid (*pPrimitive) == typeid (CPrimitiveSphere))
			{
				strTypeLabel = " - Sphere";
				bitmapPrimitive.LoadBitmap (IDB_PRIMITIVE_SPHERE);
			}
			else if (typeid (*pPrimitive) == typeid (CPrimitiveTruncatedCone))
			{
				strTypeLabel = " - Truncated Cone";
				bitmapPrimitive.LoadBitmap (IDB_PRIMITIVE_TRUNCATED_CONE);
			}
			else
			{
				ASSERT (FALSE);
			}

			// Form the whole label to use
			strLabel = strNameLabel + strTypeLabel;
		}

		// Check if enabled
		if (lpDrawItemStruct->itemState & ODS_DISABLED)
		{
			dc.SetBkColor (::GetSysColor (COLOR_3DFACE));
			dc.SetTextColor (::GetSysColor (COLOR_GRAYTEXT));
		}
		else
		{
			dc.SetBkColor (::GetSysColor ((lpDrawItemStruct->itemState & ODS_SELECTED) ?
				COLOR_HIGHLIGHT : COLOR_WINDOW));
			dc.SetTextColor (::GetSysColor ((lpDrawItemStruct->itemState & ODS_SELECTED) ?
				COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));
		}

		// The default font is not like the normal font so select the same font as used
		// in the list boxes.
		// todo: request the font from the OS to match other fonts
		CFont font;
		BOOL bReturn = font.CreatePointFont (80, "MS Sans Serif", &dc);
		ASSERT (bReturn);

		CFont* pOldFont = dc.SelectObject (&font);


		CDC dcMem;
		dcMem.CreateCompatibleDC (&dc);
		CBrush* pBrushBitmapBG = new CBrush (::GetSysColor ((lpDrawItemStruct->itemState & ODS_SELECTED) ?
			COLOR_HIGHLIGHT : COLOR_WINDOW));
		dcMem.FillRect (CRect (0, 0, 16, 16), pBrushBitmapBG);
		delete pBrushBitmapBG;
		CBitmap* pOldBitmap = dcMem.SelectObject (&bitmapPrimitive);

		if (lpDrawItemStruct->itemState & ODS_SELECTED)
			dc.BitBlt (rect.left, rect.top, 16, 16, &dcMem, 0, 0, MERGEPAINT);
		else
			dc.BitBlt (rect.left, rect.top, 16, 16, &dcMem, 0, 0, MERGECOPY);

//			dc.SetTextColor (COLOR_BACKGROUND);
		dc.TextOut (rect.left + 18, rect.top + 1, strLabel);

		dcMem.SelectObject (pOldBitmap);
		dc.SelectObject (pOldFont);
	}

	dc.Detach ();		
}

void CComboBoxPrimitives::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemHeight = 16;	
	
}

int CComboBoxPrimitives::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
{
	// return -1 = item 1 sorts before item 2
	// return 0 = item 1 and item 2 sort the same
	// return 1 = item 1 sorts after item 2

	// Note this function is called in the implementation of the AddString function.  
	// Consequently, I can't used the item data for the newly added item because it
	// can't be set until the item has been added.
	
	CString strText1, strText2;


	if (lpCompareItemStruct->itemID2 == 0xFFFFFFFF)
		return -1;

	GetLBText (lpCompareItemStruct->itemID1, strText1);
	GetLBText (lpCompareItemStruct->itemID2, strText2);

	if (strText1.CompareNoCase (strText2) < 0)
		return -1;
	else if (strText1.CompareNoCase (strText2) > 0)
		return 1;
	else 
	{
		ASSERT (strText1.CompareNoCase (strText2) == 0);
		return 0;
	}
		
	return 0;
}

void CComboBoxPrimitives::RefreshList (CModel* pModel)
{
	ASSERT (pModel);

	if (!IsComboBoxListValid (pModel))
		RefreshComboBox (pModel);
}

int CComboBoxPrimitives::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Initialize the list to hold the universe and the local special cases
	int nIndex = InsertString (N_UNIVERSE_INDEX, STR_UNIVERSE_LABEL);
	ASSERT (nIndex == N_UNIVERSE_INDEX);
	int nReturn = SetItemDataPtr (N_UNIVERSE_INDEX, NULL);
	ASSERT (nReturn != CB_ERR);

	nIndex = InsertString (N_LOCAL_INDEX, STR_LOCAL_LABEL);
	ASSERT (nIndex == N_LOCAL_INDEX);
	nReturn = SetItemDataPtr (N_LOCAL_INDEX, NULL);
	ASSERT (nReturn != CB_ERR);

	// Now set the current selection so there will always be a valid selection
	nReturn = SetCurSel (N_UNIVERSE_INDEX);
	ASSERT (nReturn != CB_ERR);

	return 0;
}

int CComboBoxPrimitives::OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
{
	
	return CComboBox::OnCompareItem(nIDCtl, lpCompareItemStruct);
}

BOOL CComboBoxPrimitives::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= (WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST |CBS_OWNERDRAWFIXED | 
		WS_VSCROLL | CBS_SORT | CBS_HASSTRINGS);
	
	return CComboBox::PreCreateWindow(cs);
}

void CComboBoxPrimitives::OnSetFocus(CWnd* pOldWnd) 
{
	CComboBox::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	
}

// Returns TRUE is the current (it doesn't look at the whole list, just the current) is valid
// FALSE if the selection is no longer found in the model
BOOL CComboBoxPrimitives::IsCurrentSelectionValid(CModel* pModel)
{
	ASSERT (pModel);
	// Used to determine if need to refresh the list box because the current selection
	// is no longer valid.
	// The determination of validity is based on finding a primitive in the model with the
	// same memory location and the names still match.

	// First get the current selection
	int nCurrentIndex = GetCurSel ();
	ASSERT  (nCurrentIndex != CB_ERR);

	// If local or universe is selected, it is always valid so return true
	if (nCurrentIndex == N_UNIVERSE_INDEX || nCurrentIndex == N_LOCAL_INDEX)
		return TRUE;

	// Else need to look through the list and see if the pointer is valid
	CPrimitive* pCurrentPrimitive = reinterpret_cast <CPrimitive*> 
		(GetItemDataPtr (nCurrentIndex));
	ASSERT (pCurrentPrimitive);
	
	int nNumberOfPrimitives = pModel->GetNumberOfPrimitives ();
	int nCounter;

	for (nCounter = 0; nCounter < nNumberOfPrimitives; nCounter++)
	{
		CPrimitive* pPrimitive = pModel->GetPrimitive (nCounter);

		// Just want to try to find a match with the pointers because the item
		// data only stores the pointer
		if (reinterpret_cast <void*> (pPrimitive) ==
			reinterpret_cast <void*> (pCurrentPrimitive))
		{
			// Then found a match so make sure the names match
			CString strSelectedText;
			GetLBText (nCurrentIndex, strSelectedText);
			if (pPrimitive->GetName () == strSelectedText)
				return TRUE;
			else
			{
				// The label has changed so we need to update the list
				return FALSE;
			}
		}
	}

	// Then went through all the primitives in the current model and couldn't find a match
	// Thus the primitive no longer exists and need to repopulate list
	return FALSE;
}

BOOL CComboBoxPrimitives::IsComboBoxListValid(CModel* pModel)
{
	// This is built to be very generic.  For now, there are only two options (relative to
	// local and link), so this will always be valid

	return TRUE;

	ASSERT (pModel);

	// First check that the number in the list is the same as the number of primitives
	int nNumberOfPrimitives = pModel->GetNumberOfPrimitives ();
	int nNumberInList = GetCount ();
	ASSERT (nNumberInList != CB_ERR);

	// Recall there also always two special cases of universe and local
	if (nNumberOfPrimitives != nNumberInList - 2)
	{
		return FALSE;
	}

	// Same number, but need to verify that each primitive in the list is in the model
	int nListIndex;
	for (nListIndex = 0; nListIndex < nNumberInList; nListIndex++)
	{
		// Recall that the special cases of univer and local won't have associated primitives
		if (nListIndex != N_UNIVERSE_INDEX && nListIndex != N_LOCAL_INDEX)
		{
			void* pvoidPrimitive = GetItemDataPtr (nListIndex);
			// Now look through model for a match
			int nPrimitiveIndex;
			for (nPrimitiveIndex = 0; nPrimitiveIndex < nNumberOfPrimitives; nPrimitiveIndex++)
			{
				CPrimitive* pPrimitive = pModel->GetPrimitive (nPrimitiveIndex);
				ASSERT (pPrimitive);

				if (pvoidPrimitive == reinterpret_cast <void*> (pPrimitive))
				{
					// Then matched the pointer values so make sure the name is the same
					CString strListText;
					GetLBText (nListIndex, strListText);
					if (pPrimitive->GetName () != strListText)
					{
						// Then a name change has occurred and list refresh is needed
						return FALSE;
					}
					else
					{
						// break for looking for this primitive since it was found
						break;
					}
				}
				// else keep looking at the rest of the primitives in the model
			}

			// Check if the index reached the max.  This implies that the pointer could
			// not be found in the model so the list needs refreshed
			if (nPrimitiveIndex == nNumberOfPrimitives)
			{
				return FALSE;
			}
		}
	}

	// If make it this far, no inconsistancies were found so the list is OK
	return TRUE;
}

void CComboBoxPrimitives::RefreshCurrentSelection(CModel *pModel)
{
	ASSERT (pModel);
	if (!IsCurrentSelectionValid (pModel))
	{
		// Force a refresh of the list
		RefreshComboBox (pModel);
	}
}

void CComboBoxPrimitives::RefreshComboBox(CModel *pModel)
{
	ASSERT (pModel);

	// First clear the combo box
	Clear ();
	ResetContent ();

	int nNumberOfPrimitives = pModel->GetNumberOfPrimitives ();
	int nCounter;

	for (nCounter = 0; nCounter < nNumberOfPrimitives; nCounter++)
	{
		// Uncomment this to show all of the primitives.  This functionality will be used 
		// in the next version.

//		int nIndex;
//		int nReturn;
//		CString strName = pModel->GetPrimitive (nCounter)->GetName ();
//		nIndex = AddString (strName);
//		ASSERT (nIndex != CB_ERR && nIndex != CB_ERRSPACE);
//		nReturn = SetItemDataPtr (nIndex, reinterpret_cast <void*> (pModel->GetPrimitive (nCounter)));
//		ASSERT (nReturn != CB_ERR);
	}

	// Insert two additional options that will always be available
	int nReturn;
	nReturn = InsertString (N_UNIVERSE_INDEX, STR_UNIVERSE_LABEL);
	ASSERT (nReturn == N_UNIVERSE_INDEX);
	nReturn = SetItemDataPtr (N_UNIVERSE_INDEX, NULL);
	ASSERT (nReturn != CB_ERR);
	nReturn = InsertString (N_LOCAL_INDEX, STR_LOCAL_LABEL);
	ASSERT (nReturn == N_LOCAL_INDEX);
	nReturn = SetItemDataPtr (N_LOCAL_INDEX, NULL);
	ASSERT (nReturn != CB_ERR);

	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);	
}

// The pointer to the model is used just to make sure the current selection is still valid.
// It is likely to be as long as the list is refreshed when the control gets focus, but it
// is just added for safety.
void CComboBoxPrimitives::GetCurrentSelection(CModel* pModel,
		UINT* puWRTType, CPrimitive **ppPrimitive)
{
	// Just to make sure the returned selection is still valid - though I anticipate that
	// it always will be
	ASSERT (pModel);
	if (!IsCurrentSelectionValid (pModel))
		RefreshList (pModel);

	int nCurrentIndex = GetCurSel ();
	ASSERT (nCurrentIndex != CB_ERR);

	if (nCurrentIndex == N_UNIVERSE_INDEX)
	{
		*puWRTType = MODIFY_WRT_UNIVERSE;
		*ppPrimitive = NULL;
	}
	else if (nCurrentIndex == N_LOCAL_INDEX)
	{
		*puWRTType = MODIFY_WRT_LOCAL;
		*ppPrimitive = NULL;
	}
	else
	{
		*puWRTType = MODIFY_WRT_PRIMITIVE;
		*ppPrimitive = reinterpret_cast <CPrimitive*> (GetItemDataPtr (nCurrentIndex));
	}
}
