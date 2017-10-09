// IOView.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "IOView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIOView

IMPLEMENT_DYNCREATE(CIOView, CScrollView)

CIOView::CIOView()
{
   m_pRBUserIOData = NULL;
}

CIOView::~CIOView()
{
   int i;
   for (i = 0; i < m_SliderArray.GetSize (); i++)
   {
      m_SliderArray.GetAt (i).pSlider->DestroyWindow ();
      m_SliderArray.GetAt (i).pLabel->DestroyWindow ();
      delete m_SliderArray.GetAt (i).pSlider;
      delete m_SliderArray.GetAt (i).pLabel;
   }
   m_SliderArray.RemoveAll ();

   for (i = 0; i < m_CheckBoxArray.GetSize (); i++)
   {
      m_CheckBoxArray.GetAt (i)->DestroyWindow ();
      delete m_CheckBoxArray.GetAt (i);
   }
   m_CheckBoxArray.RemoveAll ();

   for (i = 0; i < m_LabelArray.GetSize (); i++)
   {
      m_LabelArray.GetAt (i)->DestroyWindow ();
      delete m_LabelArray.GetAt (i);
   }
   m_LabelArray.RemoveAll ();

   for (i = 0; i < m_ListArray.GetSize (); i++)
   {
      m_ListArray.GetAt (i)->DestroyWindow ();
      delete m_ListArray.GetAt (i);
   }
   m_ListArray.RemoveAll ();

   for (i = 0; i < m_EditArray.GetSize (); i++)
   {
      m_EditArray.GetAt (i).pEdit->DestroyWindow ();
      m_EditArray.GetAt (i).pLabel->DestroyWindow ();
      delete m_EditArray.GetAt (i).pEdit;
      delete m_EditArray.GetAt (i).pLabel;
   }
   m_EditArray.RemoveAll ();

   for (i = 0; i < m_ButtonArray.GetSize (); i++)
   {
      m_ButtonArray.GetAt (i).pButton->DestroyWindow ();
      delete m_ButtonArray.GetAt (i).pButton;
   }
   m_ButtonArray.RemoveAll ();
}


BEGIN_MESSAGE_MAP(CIOView, CScrollView)
	//{{AFX_MSG_MAP(CIOView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIOView drawing

void CIOView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CIOView diagnostics

#ifdef _DEBUG
void CIOView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CIOView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIOView message handlers

int CIOView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	
	// Kind of a hack -- if this view were created by the frame, this would be called.
	// Because I am 'replacing' the view in the splitter, the framework doesn't call it.
	OnInitialUpdate ();
 

	return 0;
}

void CIOView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = WINDOW_WIDTH;
   sizeTotal.cy = WINDOW_HEIGHT;
	SetScrollSizes(MM_TEXT, sizeTotal);	
}

void CIOView::SetRBUserIOData(RBUserIOData *pRBUserIOData)
{
   // Here is where everything will be dynamically created.

   int i;
 
   
   ////////// Sliders /////////////
   // Deallocate anything here - this will called after a stop press
   for (i = 0; i < m_SliderArray.GetSize (); i++)
   {
      m_SliderArray.GetAt (i).pSlider->DestroyWindow ();
      m_SliderArray.GetAt (i).pLabel->DestroyWindow ();
      delete m_SliderArray.GetAt (i).pSlider;
      delete m_SliderArray.GetAt (i).pLabel;
   }
   m_SliderArray.RemoveAll ();

   // Setup the sliders
   for (i = 0; i < pRBUserIOData->GetNumberOfSliders (); i++)
   {
      CSliderCtrl *pSlider;
      // Allocate a new one
		try {
			pSlider = new CSliderCtrl;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}
      CStatic *pLabel;
      try {
			pLabel = new CStatic;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}

      // Get the slider data
      structSliderSetup strtSliderSetup;
      pRBUserIOData->GetSliderSetup (i, &strtSliderSetup);

      // Create the window
	   // Slider
	   pSlider->Create (WS_CHILD|WS_VISIBLE|TBS_TOOLTIPS ,
		   CRect (strtSliderSetup.nPosX,
         strtSliderSetup.nPosY + strtSliderSetup.nHeight/2,
         strtSliderSetup.nPosX + strtSliderSetup.nWidth,
         strtSliderSetup.nPosY + strtSliderSetup.nHeight), this, 1);
      pSlider->SetRange (strtSliderSetup.nMinValue, strtSliderSetup.nMaxValue);
      pSlider->SetPos (strtSliderSetup.nValue);
      pLabel->Create (strtSliderSetup.strLabel.c_str (), WS_CHILD|WS_VISIBLE|SS_CENTER,
         CRect (strtSliderSetup.nPosX, strtSliderSetup.nPosY,
         strtSliderSetup.nPosX + strtSliderSetup.nWidth,
         strtSliderSetup.nPosY + strtSliderSetup.nHeight/2), this);

      // Add to the array
      structSliderElement strtSliderElement;
      strtSliderElement.pSlider = pSlider;
      strtSliderElement.pLabel = pLabel;
      m_SliderArray.Add (strtSliderElement);
   }

   /////////////// Check Boxes ////////////////////
   // Deallocate anything here - this will called after a stop press
   for (i = 0; i < m_CheckBoxArray.GetSize (); i++)
   {
      m_CheckBoxArray.GetAt (i)->DestroyWindow ();
      delete m_CheckBoxArray.GetAt (i);
   }
   m_CheckBoxArray.RemoveAll ();

   // Setup the check boxes
   for (i = 0; i < pRBUserIOData->GetNumberOfCheckBoxes (); i++)
   {
      CButton *pCheckBox;
      // Allocate a new one
		try {
			pCheckBox = new CButton;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}

      // Get the checkbox data
      structCheckBoxSetup strtCheckBoxSetup;
      pRBUserIOData->GetCheckBoxSetup (i, &strtCheckBoxSetup);

      // Find out how big the text is
      CDC* pDC = GetDC();
	   SIZE sz;
	   sz = pDC->GetTextExtent(strtCheckBoxSetup.strLabel.c_str ());
	   ReleaseDC(pDC);

      // Create the window
	   pCheckBox->Create (strtCheckBoxSetup.strLabel.c_str (),
         WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX,
		   CRect (strtCheckBoxSetup.nPosX,
         strtCheckBoxSetup.nPosY,
         strtCheckBoxSetup.nPosX + sz.cx + 25, // extra for check box size
         strtCheckBoxSetup.nPosY + sz.cy), this, 1);
      if (strtCheckBoxSetup.bValue)
         pCheckBox->SetCheck (1);
      else
         pCheckBox->SetCheck (0);

      // Add to the array
      m_CheckBoxArray.Add (pCheckBox);
   }

   ////////// Edit /////////////
   // Deallocate anything here - this will called after a stop press
   for (i = 0; i < m_EditArray.GetSize (); i++)
   {
      m_EditArray.GetAt (i).pEdit->DestroyWindow ();
      m_EditArray.GetAt (i).pLabel->DestroyWindow ();
      delete m_EditArray.GetAt (i).pEdit;
      delete m_EditArray.GetAt (i).pLabel;
   }
   m_EditArray.RemoveAll ();

   // Setup the edits
   for (i = 0; i < pRBUserIOData->GetNumberOfEdits (); i++)
   {
      CEdit *pEdit;
      // Allocate a new one
		try {
			pEdit = new CEdit;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}
      CStatic *pLabel;
      try {
			pLabel = new CStatic;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}

      // Get the edit data
      structEditSetup strtEditSetup;
      pRBUserIOData->GetEditSetup (i, &strtEditSetup);

      // Find out how big the text is
      CDC* pDC = GetDC();
	   SIZE sz;
	   sz = pDC->GetTextExtent(strtEditSetup.strLabel.c_str ());
	   ReleaseDC(pDC);
      
      // Create the window
	   // Slider
      pLabel->Create (strtEditSetup.strLabel.c_str (), WS_CHILD|WS_VISIBLE|SS_LEFT,
         CRect (strtEditSetup.nPosX, strtEditSetup.nPosY,
         strtEditSetup.nPosX + sz.cx,
         strtEditSetup.nPosY + sz.cy), this);
      pEdit->Create (WS_CHILD|WS_VISIBLE|WS_BORDER,
		   CRect (strtEditSetup.nPosX + sz.cx + 10, // little space between lable and edit
         strtEditSetup.nPosY,
         strtEditSetup.nPosX + sz.cx + strtEditSetup.nWidth,
         strtEditSetup.nPosY + sz.cy * 1.4), this, 1);
      pEdit->SetWindowText (strtEditSetup.strData.c_str ());


      // Add to the array
      structEditElement strtEditElement;
      strtEditElement.pEdit = pEdit;
      strtEditElement.pLabel = pLabel;
      m_EditArray.Add (strtEditElement);
   }
   
   ////////// Button /////////////
   // Deallocate anything here - this will called after a stop press
   for (i = 0; i < m_ButtonArray.GetSize (); i++)
   {
      m_ButtonArray.GetAt (i).pButton->DestroyWindow ();
      delete m_ButtonArray.GetAt (i).pButton;
   }
   m_ButtonArray.RemoveAll ();

   // Setup the buttons
   for (i = 0; i < pRBUserIOData->GetNumberOfButtons (); i++)
   {
      CButton *pButton;
      // Allocate a new one
		try {
			pButton = new CButton;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}

      // Get the edit data
      structButtonSetup strtButtonSetup;
      pRBUserIOData->GetButtonSetup (i, &strtButtonSetup);

		int nWidth = 0, nHeight = 0;
		// If the width or height is 0, calculate the button size based on the text.
		if (strtButtonSetup.nWidth == 0 || strtButtonSetup.nHeight == 0)
		{
			// Find out how big the text is
			CDC* pDC = GetDC();
			SIZE sz;
			sz = pDC->GetTextExtent(strtButtonSetup.strLabel.c_str ());
			ReleaseDC(pDC);

			if (strtButtonSetup.nWidth == 0)
				nWidth = max(sz.cx * 1.5, 50);
			else
				nWidth = strtButtonSetup.nWidth;

			if (strtButtonSetup.nHeight == 0)
				nHeight = max(sz.cy * 1.5, 14);
			else
				nHeight = strtButtonSetup.nHeight;
		}
		else
		{
			nWidth = strtButtonSetup.nWidth;
			nHeight = strtButtonSetup.nHeight;
		}
      
      // Create the window		
		pButton->Create (strtButtonSetup.strLabel.c_str (), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
         CRect (strtButtonSetup.nPosX, strtButtonSetup.nPosY,
         strtButtonSetup.nPosX + nWidth,
         strtButtonSetup.nPosY + nHeight), this, 0);

      // Add to the array
      structButtonElement strtButtonElement;
      strtButtonElement.pButton = pButton;
      strtButtonElement.bClicked = false;
      m_ButtonArray.Add (strtButtonElement);
   }
   

   /////////////// Labels ////////////////////
   // Deallocate anything here - this will called after a stop press
   for (i = 0; i < m_LabelArray.GetSize (); i++)
   {
      m_LabelArray.GetAt (i)->DestroyWindow ();
      delete m_LabelArray.GetAt (i);
   }
   m_LabelArray.RemoveAll ();

   // Setup the label
   for (i = 0; i < pRBUserIOData->GetNumberOfLabels (); i++)
   {
      CStatic *pLabel;
      // Allocate a new one
		try {
			pLabel = new CStatic;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}

      // Get the data
      structLabelSetup strtLabelSetup;
      pRBUserIOData->GetLabelSetup (i, &strtLabelSetup);

      // Build a string of O's to figure out how big to make the box
      CString str;
      int j = 0;
      for (j = 0; j < strtLabelSetup.nWidthInChars; j++)
      {
         str += 'O';
      }

      // Find out how big the text is
      CDC* pDC = GetDC();
	   SIZE sz;
	   sz = pDC->GetTextExtent(str);
	   ReleaseDC(pDC);

      // Create the window
	   pLabel->Create (strtLabelSetup.strValue.c_str (),
         WS_CHILD|WS_VISIBLE,
		   CRect (strtLabelSetup.nPosX,
         strtLabelSetup.nPosY,
         strtLabelSetup.nPosX + sz.cx ,
         strtLabelSetup.nPosY + sz.cy), this, 1);

      // Add to the array
      m_LabelArray.Add (pLabel);
   }

 
   /////////////// Output List ////////////////////
   // Deallocate anything here - this will called after a stop press
   for (i = 0; i < m_ListArray.GetSize (); i++)
   {
      m_ListArray.GetAt (i)->DestroyWindow ();
      delete m_ListArray.GetAt (i);
   }
   m_ListArray.RemoveAll ();

   // Setup the list
   for (i = 0; i < pRBUserIOData->GetNumberOfOutputLists (); i++)
   {
      CListCtrl *pList;
      // Allocate a new one
		try {
			pList = new CListCtrl;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}

      // Get the checkbox data
      structOutputListSetup strtOutputListSetup;
      pRBUserIOData->GetOutputListSetup (i, &strtOutputListSetup);

      // Create the window
	   pList->Create (
         WS_CHILD|WS_VISIBLE|WS_BORDER|WS_VSCROLL|WS_HSCROLL|LVS_REPORT|LVS_NOSORTHEADER,
		   CRect (strtOutputListSetup.nPosX,
         strtOutputListSetup.nPosY,
         strtOutputListSetup.nPosX + strtOutputListSetup.nWidth, // extra for check box size
         strtOutputListSetup.nPosY + strtOutputListSetup.nHeight), this, 1);
      // Add the columns - create a column for each tab separated label
      CString strLabels = strtOutputListSetup.strLabels.c_str ();
      int nIndex = 0;
      int nNextTabIndex = 0;
      int nColumnCount = 0;
      BOOL bContinue = TRUE;
      do {
         // Need to look at the index after the last one found
         // (MSDN appears to be wrong)
         nNextTabIndex = strLabels.Find ('\t', nIndex);
         if (nNextTabIndex == -1)
         {
            bContinue = FALSE;
            nNextTabIndex = strLabels.GetLength ();
         }
         CString strColumnLabel = strLabels.Mid (nIndex, nNextTabIndex - nIndex);
         pList->InsertColumn (nColumnCount, strColumnLabel);
         nColumnCount ++;
         nIndex = nNextTabIndex + 1;
      } while (bContinue);

      // Divide the columns widths evenly
      int nColumnWidth = strtOutputListSetup.nWidth / nColumnCount;
      for (i = 0; i < nColumnCount; i++)
         pList->SetColumnWidth (i, nColumnWidth);

      // Add to the array
      m_ListArray.Add (pList);
   }


/*
   /////////////// Charts ////////////////////
   // Deallocate anything here - this will called after a stop press
   for (i = 0; i < m_ChartArray.GetSize (); i++)
   {
      m_ChartArray.GetAt (i)->DestroyWindow ();
      delete m_ChartArray.GetAt (i);
   }
   m_ChartArray.RemoveAll ();

   // Setup the chartss
   for (i = 0; i < pRBUserIOData->GetNumberOfCharts (); i++)
   {
      CMSChart *pChart;
      // Allocate a new one
		try {
			pChart = new CMSChart;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}

      // Get the checkbox data
      structChartSetup strtChartSetup;
      pRBUserIOData->GetChartSetup (i, &strtChartSetup);

      // Create the window
	   pChart->Create (strtChartSetup.strLabel.c_str (),
         WS_CHILD|WS_VISIBLE,
		   CRect (strtChartSetup.nPosX,
         strtChartSetup.nPosY,
         strtChartSetup.nPosX + strtChartSetup.nSideLength,
         strtChartSetup.nPosY + strtChartSetup.nSideLength), this, 1);
      /// CHART OPTIONS
      // Set Chart Type - XY Scatter
      pChart->SetChartType (16);
      // No dynamic rotation
      pChart->SetAllowDynamicRotation (false);
      // User can't select chart objects
      pChart->SetAllowSelections (false);
      // Let the chart autoincrement (row count increases when add data)
      pChart->SetAutoIncrement (false);
      // Set draw mode to blit an offscreen drawing to the screen
      //pChart->SetDrawMode (0); - less flashing if leave set to default
      // Set one data set (need two columns for x and y)
      pChart->SetColumnCount (2);
      // Don't generate random data (let me fill the data)
      pChart->SetRandomFill (false);
      pChart->SetRowCount (1);
      // Add one data point to display a graph (if there isn't a point, it won't
      // display anything
      pChart->SetRow (1);
      pChart->SetColumn (1);
 //     pChart->SetData (1);
      pChart->SetColumn(2);
//      pChart->SetData (1);
      // Set the title
      pChart->SetTitleText (strtChartSetup.strLabel.c_str ()); 
   
      // These control painting 
      pChart->SetRepaint (true);
//     pChart->SetRedraw (true);

//     pChart->GetBackdrop ().GetFill ().GetBrush ().GetFillColor ().Set (255, 0, 0);
      pChart->GetBackdrop ().GetFill ().SetStyle (1);
      pChart->SetDrawMode (1);
      pChart->Refresh ();
      // Add to the array
      m_ChartArray.Add (pChart);
   }
*/

   // Lock the user settings
   pRBUserIOData->LockSettingsData ();
}

void CIOView::UpdateUserData(RBUserIOData *pRBUserIOData)
{
   // Query all of the controls and update the current values

   int i;
   BOOL bReturn;
   for (i = 0; i < m_SliderArray.GetSize (); i++)
   {
      bReturn = pRBUserIOData->SetSliderValue (i, m_SliderArray.GetAt (i).pSlider->GetPos ());
      ASSERT (bReturn);
   }

   // Edits
   for (i = 0; i < m_EditArray.GetSize (); i++)
   {
		CString strText;
		m_EditArray.GetAt (i).pEdit->GetWindowText (strText);
		string stringText = strText;
      bReturn = pRBUserIOData->SetEditValue (i, stringText);
      ASSERT (bReturn);
   }


   // Check Boxes
   for (i = 0; i < m_CheckBoxArray.GetSize (); i++)
   {
      bReturn = pRBUserIOData->SetCheckBoxValue (i, 
         (m_CheckBoxArray.GetAt (i)->GetCheck () == 1) ? true : false);
      ASSERT (bReturn);
   }

	// Buttons
	for (i = 0; i < m_ButtonArray.GetSize (); i++)
	{
		if (m_ButtonArray.GetAt (i).bClicked == TRUE)
		{
			// Reset the click state to false
			structButtonElement strtButtonElement;
			strtButtonElement = m_ButtonArray.GetAt (i);
			strtButtonElement.bClicked = FALSE;
			m_ButtonArray.SetAt (i, strtButtonElement);

			// Set the field in RBUserIOData
			pRBUserIOData->SetButtonClicked (i);  
		}
	}

   // Label
   for (i = 0; i < m_LabelArray.GetSize (); i++)
   {
      // First check if there is new data - this cuts down the repaints which
      // cause some flashing
      bool bNewData;
      bReturn = pRBUserIOData->IsThereNewLabelData (i, bNewData);
      ASSERT (bReturn);
      if (bNewData)
      {
         string strValue;
         bReturn = pRBUserIOData->GetLabelValue (i, strValue);
         ASSERT (bReturn);
         m_LabelArray.GetAt (i)->SetWindowText (strValue.c_str ());
      }
   }

   // Output List
   for (i = 0; i < m_ListArray.GetSize (); i++)
   {
      // First check if there is new data - this cuts down the repaints which
      // cause some flashing
      bool bNewData;
      bReturn = pRBUserIOData->IsThereNewOutputListData (i, bNewData);
      ASSERT (bReturn);
      if (bNewData)
      {
         string stringData;
         bReturn = pRBUserIOData->GetOutputListData (i, stringData);
         ASSERT (bReturn);
         // Add a new row to the output list
         int nRow = m_ListArray.GetAt (i)->GetItemCount ();
         m_ListArray.GetAt (i)->InsertItem (nRow, "");

         // Add the columns - create a column for each tab separated label
         CString strData = stringData.c_str ();
         int nIndex = 0;
         int nNextTabIndex = 0;
         int nColumnCount = 0;
         BOOL bContinue = TRUE;
         do {
            // Need to look at the index after the last one found
            // (MSDN appears to be wrong)
            nNextTabIndex = strData.Find ('\t', nIndex);
            if (nNextTabIndex == -1)
            {
               bContinue = FALSE;
               nNextTabIndex = strData.GetLength ();
            }
            CString strColumnData = strData.Mid (nIndex, nNextTabIndex - nIndex);
            // Make sure column exists
            LVCOLUMN columnInfo;
            columnInfo.mask = 0;
            if (m_ListArray.GetAt (i)->GetColumn (nColumnCount, &columnInfo))
               m_ListArray.GetAt (i)->SetItemText (nRow, nColumnCount, strColumnData);
            nColumnCount ++;
            nIndex = nNextTabIndex + 1;
         } while (bContinue);


      }
   }
/*
   // Charts
   // See if there is new data to chart and add it if so
   for (i = 0; i < m_ChartArray.GetSize (); i++)
   {
      bool bNewValue;
      bReturn = pRBUserIOData->IsThereNewChartData (i, bNewValue);
      ASSERT (bReturn);
      // If there is new data, pick it up and add it
      if (bNewValue)
      {
         double dX, dY;
         bReturn = pRBUserIOData->GetNewChartData (i, dX, dY);
         ASSERT (bReturn);
         // Add to the chart - first get a pointer for convenience
         CMSChart* pChart = m_ChartArray.GetAt (i);
 //        pChart->SetData (dX);
 //        pChart->SetData (dY);


      }

      COleSafeArray saRet;
      DWORD numElements[] = {1, 2}; // 10x10
      // Create the safe-array...
      saRet.Create(VT_R8, 2, numElements);
      // Initialize it with values...
      long index[2];
      static int j = 0;
      j ++;

      // One way to put in data
      double val = j;
      index[0] = 0;
      index[1] = 0;
      saRet.PutElement(index, &val);
      index[0] = 0;
      index[1] = 1;
      val = 2;
      saRet.PutElement(index, &val);
      // Return the safe-array encapsulated in a VARIANT...
      
      // Test ways to control repainting
      if (j%2000 == 0)
      {
        m_ChartArray.GetAt (i)->SetRedraw (true);
      }
      else
      {
         m_ChartArray.GetAt (i)->SetRedraw (false);
      }

      //m_ChartArray.GetAt (i)->SetChartData(saRet.Detach());
      int nRow = m_ChartArray.GetAt (i)->GetDataGrid ().GetRowCount ();
      m_ChartArray.GetAt (i)->GetDataGrid ().SetRowCount (nRow + 1);
      // Another way to put in data - index start at 1
      m_ChartArray.GetAt (i)->GetDataGrid ().SetData (1, 1, 1, false);
      // m_ChartArray.GetAt (i)->GetDataGrid ().SetData (1, 1, 2, false);

      //  m_ChartArray.GetAt (i)->Refresh ();
      //    m_ChartArray.GetAt (i)->SetRepaint (false);  
      //           m_ChartArray.GetAt (i)->SetRedraw (false);

   } */

}

BOOL CIOView::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect (0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
   COLORREF crBackBackground = GetSysColor (COLOR_3DFACE);
	CBrush brushBackground (crBackBackground);
	pDC->SelectObject (&brushBackground);
	pDC->Rectangle (rect);
	pDC->SelectStockObject (NULL_BRUSH); // select out brush

	return 1; // to indicate done with erasing
//	return CScrollView::OnEraseBkgnd(pDC);
}


// The windows leave the border lines on the moved window unless I force an erase
void CIOView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// This handler picks up WM_HSCROLLS from the slider bars too.  The repaint is
	// only needed when the window is moving, so don't need to if its a slider bar
	// (which is indicated by having a non-NULL pScrollBar)
	if (!pScrollBar)
		Invalidate (TRUE);
   
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

// The windows leave the border lines on the moved window unless I force an erase
void CIOView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// The IOView only supports horizontal scroll bars so don't have to worry
	// have the slider windows like in the WM_HSCROLL handler.
	Invalidate (TRUE);
	
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CIOView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// Look for button clicks.
	if (HIWORD (wParam) == BN_CLICKED)
	{
		// See if the hwnd (lParam) matches any of the pointers
		int i;
		for (i = 0; i < m_ButtonArray.GetSize (); i++)
		{
			if (m_ButtonArray.GetAt (i).pButton->GetSafeHwnd () == (HWND) lParam)
			{
				structButtonElement strtButtonElement;
				strtButtonElement = m_ButtonArray.GetAt (i);
				// Set the clicked field.
				strtButtonElement.bClicked = TRUE;
				m_ButtonArray.SetAt (i, strtButtonElement);
			}
		}
	}
	
	return CScrollView::OnCommand(wParam, lParam);
}
