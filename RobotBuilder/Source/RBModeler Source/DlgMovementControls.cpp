// DlgMovementControls.cpp : implementation file
//

#include "stdafx.h"
#include "RBModeler.h"
#include "DlgMovementControls.h"
#include "MovementControlsView.h"
#include "RBModelerRBMGraphicView.h"
#include "PrimitiveSphere.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// These definitions need to correspond to the respective index in the radio buttons
// in the dialog and were only defined to aid clarity
enum {RADIO_ROTATE=1, RADIO_TRANSLATE=0, RADIO_SPATIAL_TRANSFORM=2, RADIO_SCALE=3};

/////////////////////////////////////////////////////////////////////////////
// CDlgMovementControls dialog

IMPLEMENT_DYNCREATE(CDlgMovementControls, CDialog)

CDlgMovementControls::CDlgMovementControls(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMovementControls::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMovementControls)
	m_dStepSize = 1.0;
	m_nModType = 0;
	//}}AFX_DATA_INIT
}


void CDlgMovementControls::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fStepSize = (float) m_dStepSize;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMovementControls)
	DDX_Control(pDX, IDC_SPIN_STEP_SIZE, m_spinStepSize);
	DDX_Text(pDX, IDC_EDIT_STEP_SIZE, fStepSize);
	DDV_MinMaxFloat(pDX, fStepSize, 0., 999999.);
	DDX_Radio(pDX, IDC_RADIO_TRANSLATE, m_nModType);
	//}}AFX_DATA_MAP

	m_dStepSize = fStepSize;
}


BEGIN_MESSAGE_MAP(CDlgMovementControls, CDialog)
	//{{AFX_MSG_MAP(CDlgMovementControls)
	ON_BN_CLICKED(IDC_BUTTON_X_NEGATIVE, OnButtonXNegative)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_RADIO_SCALE, OnRadioScale)
	ON_BN_CLICKED(IDC_RADIO_ROTATE, OnRadioRotate)
	ON_BN_CLICKED(IDC_RADIO_TRANSLATE, OnRadioTranslate)
	ON_BN_CLICKED(IDC_BUTTON_X_POSITIVE, OnButtonXPositive)
	ON_BN_CLICKED(IDC_BUTTON_Y_POSITIVE, OnButtonYPositive)
	ON_BN_CLICKED(IDC_BUTTON_Y_NEGATIVE, OnButtonYNegative)
	ON_BN_CLICKED(IDC_BUTTON_Z_POSITIVE, OnButtonZPositive)
	ON_BN_CLICKED(IDC_BUTTON_Z_NEGATIVE, OnButtonZNegative)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIO_SPATIAL_TRANSFORM, OnRadioSpatialTransform)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMovementControls message handlers



BOOL CDlgMovementControls::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Set up the spin control
	m_spinStepSize.SetRange (0, 999999);

	// Set the combo box placement
	CStatic* pStatic = (CStatic*) GetDlgItem (IDC_STATIC_COMBO_RECT);
	ASSERT (pStatic);

	CRect rectComboWindow;
	pStatic->GetWindowRect (rectComboWindow);

	ScreenToClient (rectComboWindow);

	m_comboPrimitives.MoveWindow (rectComboWindow, TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
void CDlgMovementControls::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemHeight = 16;	
	
//	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}
*/
/*
void CDlgMovementControls::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC dc;
	dc.Attach (lpDrawItemStruct->hDC);
	int nIndex = lpDrawItemStruct->itemID;
	
	CRect rect = lpDrawItemStruct->rcItem;
	
	CBrush* pBrush = new CBrush (::GetSysColor ((lpDrawItemStruct->itemState & ODS_SELECTED) ?
		COLOR_HIGHLIGHT : COLOR_WINDOW));
	dc.FillRect (rect, pBrush);
	delete pBrush;

	if (lpDrawItemStruct->itemState & ODS_FOCUS)
		dc.DrawFocusRect (rect);

	if (nIndex >= 0)
	{
		CBitmap bitmapPrimitive;
		CPrimitive* pPrimitive = reinterpret_cast <CPrimitive*> (m_comboPrimitives.GetItemDataPtr (nIndex));
		CString strNameLabel = pPrimitive->GetName ();
		CString strTypeLabel;

		if (typeid (*pPrimitive) == typeid (CPrimitiveSphere))
		{
			strTypeLabel = " - Sphere";
			bitmapPrimitive.LoadBitmap (IDB_PRIMITIVE_SPHERE);
		}
		else
		{
			ASSERT (FALSE);
		}

		dc.SetBkColor (::GetSysColor ((lpDrawItemStruct->itemState & ODS_SELECTED) ?
			COLOR_HIGHLIGHT : COLOR_WINDOW));
		dc.SetTextColor (::GetSysColor ((lpDrawItemStruct->itemState & ODS_SELECTED) ?
			COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));

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

		dcMem.SelectObject (pOldBitmap);

		dc.TextOut (rect.left + 18, rect.top + 1, strNameLabel + strTypeLabel);
	}

	dc.Detach ();	
}
*/
CModel* CDlgMovementControls::GetModel()
{
	// Get the parent - a CView
	CMovementControlsView* pMovementControlView = static_cast <CMovementControlsView*> (GetParent ());
	ASSERT (pMovementControlView);

	// Get the doc
	CModel* pModel = pMovementControlView->GetDocument ()->GetModel ();
	ASSERT (pModel);

	return pModel;
}

void CDlgMovementControls::RefreshPrimitiveComboBox()
{
	// todo: change to pass a parameter
	m_comboPrimitives.RefreshCurrentSelection (GetModel ());

/*	TRACE ("Refresh Combo Box\n");
	// First clear the combo box
	m_comboPrimitives.Clear ();
	m_comboPrimitives.ResetContent ();

	CModel* pModel = GetModel ();
	ASSERT (pModel);

	int nNumberOfPrimitives = pModel->GetNumberOfPrimitives ();
	int nCounter;

	for (nCounter = 0; nCounter < nNumberOfPrimitives; nCounter++)
	{
		int nIndex;
		int nReturn;
		CString strName = pModel->GetPrimitive (nCounter)->GetName ();
		nIndex = m_comboPrimitives.AddString (strName);
		ASSERT (nIndex != CB_ERR && nIndex != CB_ERRSPACE);
		nReturn = m_comboPrimitives.SetItemDataPtr (nIndex, reinterpret_cast <void*> (GetModel()->GetPrimitive (nCounter)));
		ASSERT (nReturn != CB_ERR);
	}


	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);	
*/
}

/*int CDlgMovementControls::OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct) 
{
	// Note this function is called in the implementation of the AddString function.  
	// Consequently, I can't used the item data for the newly added item because it
	// can't be set until the item has been added.
	
	CString strText1, strText2;


	if (lpCompareItemStruct->itemID2 == 0xFFFFFFFF)
		return -1;

	m_comboPrimitives.GetLBText (lpCompareItemStruct->itemID1, strText1);
	m_comboPrimitives.GetLBText (lpCompareItemStruct->itemID2, strText2);

	if (strText1.CompareNoCase (strText2) < 0)
		return -1;
	else if (strText1.CompareNoCase (strText2) > 0)
		return 1;
	else 
	{
		ASSERT (strText1.CompareNoCase (strText2) == 0);
		return 0;
	}
	
//	return CDialog::OnCompareItem(nIDCtl, lpCompareItemStruct);
	return 0;
}
*/
int CDlgMovementControls::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_comboPrimitives.Create (WS_VISIBLE | WS_CHILD,
		CRect (0, 0, 10, 10), this, 1);

	return 0;
}

BOOL CDlgMovementControls::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// This forces the update of the combo box list if needed.  It needs
	// to handled here so the pointer to the current model can be passed in.
	if (HIWORD(wParam) == CBN_DROPDOWN  &&
		m_comboPrimitives.GetSafeHwnd () == (HWND) lParam)
	{
		m_comboPrimitives.RefreshList (GetModel ());

		// Return non-zero to indicate the application has handles the message
		return 1;
	}
	else
		return CDialog::OnCommand(wParam, lParam);
}

void CDlgMovementControls::OnRadioScale() 
{
	// Scale is always respect to local, so disable the primitive combo box if scale
	// is selected

	CButton* pRadioScale = reinterpret_cast <CButton*> (GetDlgItem (IDC_RADIO_SCALE));
	ASSERT (pRadioScale);

	if (pRadioScale->GetCheck ())
	{
		m_comboPrimitives.EnableWindow (FALSE);
	}
}

void CDlgMovementControls::OnRadioRotate() 
{
	// Make sure the primitive combo box is enabled because when scale is selected,
	// it is disabled

	m_comboPrimitives.EnableWindow (TRUE);
}

void CDlgMovementControls::OnRadioTranslate() 
{
	// Make sure the primitive combo box is enabled because when scale is selected,
	// it is disabled

	m_comboPrimitives.EnableWindow (TRUE);
}

void CDlgMovementControls::GeneralModify(BOOL bPositiveDirection, UINT uAxis)
{

	// Update data to get the step size and modification type
	BOOL bSuccess = UpdateData (TRUE);
	// If not successful, return because there is invalid data in the dlg box
	if (!bSuccess)
		return;

	// if the  stepsize is 0, it will cause no change in the rotation or
	// the translation, and is invalid when scaled, so return
	if (m_dStepSize == 0)
		return;

	// Negate the step size if needed.
	double dStepSize;
	if (!bPositiveDirection)
	{
		// When a negative scale is applied, it will be interpretted as the
		// the recipricol of the step size
		if (m_nModType == RADIO_SCALE)
		{
			dStepSize = 1 / m_dStepSize;
		}
		else
		{
			dStepSize = -1 * m_dStepSize;
		}
	}
	else
		dStepSize = m_dStepSize;


	// Pick up the current selection in the combo box
	CModel* pModel = GetModel ();
	CPrimitive* pComboPrimitive;
	UINT uWRTType;
	m_comboPrimitives.GetCurrentSelection (pModel, &uWRTType, &pComboPrimitive);
	// Now call the appropriate funcion to perform the desired modification
	// Get the parent
	CMovementControlsView* pMovementControlView = static_cast <CMovementControlsView*> (GetParent ());
	ASSERT (pMovementControlView);
	// Get a pointer to the list view to determine the selected items
	CModelListView* pModelListView = pMovementControlView->GetModelListView ();
	ASSERT (pModelListView);

	// Change each item
	POSITION posSelected = pModelListView->GetListCtrl ().GetFirstSelectedItemPosition ();
	// If no items are selected, this will return NULL

	// If no items selected, show a message to the user to tell them to select a primitive
	// to apply the change to.
	if (!posSelected)
		VERIFY (MessageBox (_T("Please choose a primitive in the primitive list to apply the change to."),
		  _T("Error"), MB_ICONERROR));

	while (posSelected)
	{
		// Get the index to the selected item
		int nSelectedIndex = pModelListView->GetListCtrl ().GetNextSelectedItem (posSelected);
		// Get the data of the selected item
		CPrimitive* pPrimitive = reinterpret_cast <CPrimitive*> 
			(pModelListView->GetListCtrl ().GetItemData (nSelectedIndex));
		ASSERT (pPrimitive);
		
		// Make the change
		switch (m_nModType)
		{
		case RADIO_ROTATE:
			pPrimitive->GetPrimitivePlacement ()->AlterRotation (dStepSize,
				uAxis, uWRTType, pComboPrimitive);
			// Update the 3D view
			CRBModelerRBMGraphicView::UpdatePrimitivePlacement (pPrimitive);
			break;
		case RADIO_SPATIAL_TRANSFORM:
			pPrimitive->GetPrimitivePlacement ()->AlterSpatialTransform (dStepSize, uAxis,
				uWRTType, pComboPrimitive);	
			// Update the 3D view
			CRBModelerRBMGraphicView::UpdatePrimitivePlacement (pPrimitive);
			break;
		case RADIO_TRANSLATE:
			pPrimitive->GetPrimitivePlacement ()->AlterTranslation (dStepSize,
				uAxis, uWRTType, pComboPrimitive);
			// Update the 3D view
			CRBModelerRBMGraphicView::UpdatePrimitivePlacement (pPrimitive);
			break;
		case RADIO_SCALE:
			pPrimitive->GetPrimitiveScale ()->AlterScale (dStepSize, uAxis);	
			// Update the 3D view
			CRBModelerRBMGraphicView::UpdatePrimitiveScale (pPrimitive);
			break;
		default:
			ASSERT (FALSE);
		}		

	}
}

void CDlgMovementControls::OnButtonXPositive() 
{
	GeneralModify (TRUE, AXIS_X);
}

void CDlgMovementControls::OnButtonXNegative() 
{
	GeneralModify (FALSE, AXIS_X);
}

void CDlgMovementControls::OnButtonYPositive() 
{
	GeneralModify (TRUE, AXIS_Y);
}

void CDlgMovementControls::OnButtonYNegative() 
{
	GeneralModify (FALSE, AXIS_Y);
}

void CDlgMovementControls::OnButtonZPositive() 
{
	GeneralModify (TRUE, AXIS_Z);
}

void CDlgMovementControls::OnButtonZNegative() 
{
	GeneralModify (FALSE, AXIS_Z);
}

void CDlgMovementControls::OnMouseMove(UINT nFlags, CPoint point) 
{
	// todo: set a state variable to make this more efficient when entering the dlg window
	// by watching for non-client mousemoves/ client mousemoves
	
	// Note this only captures mouse events in the dlg - not the surrounding view window
	RefreshPrimitiveComboBox ();
	
	CDialog::OnMouseMove(nFlags, point);
}

void CDlgMovementControls::OnRadioSpatialTransform() 
{
	// Make sure the primitive combo box is enabled because when scale is selected,
	// it is disabled

	m_comboPrimitives.EnableWindow (TRUE);
}

void CDlgMovementControls::OnCancel ()
{
	// Implement to make sure the dialog is never cancelled
}

void CDlgMovementControls::OnOK ()
{
	// Implement to make sure the dialog is never OKed and always stays there
}
