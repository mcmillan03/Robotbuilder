// PPageSecJointData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PPageSecJointData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageSecJointData property page

IMPLEMENT_DYNCREATE(CPPageSecJointData, CPropertyPage)

CPPageSecJointData::CPPageSecJointData() : CPropertyPage(CPPageSecJointData::IDD)
{
	//{{AFX_DATA_INIT(CPPageSecJointData)
	m_nLinkAIndex = 0;
	m_nLinkBIndex = 0;
	m_nStabilization = 0;
	m_nJointType = 0;
	//}}AFX_DATA_INIT

	m_pCdmvSecJointData = NULL;

	// loop will copy both positions and rotations
	unsigned int i;
	unsigned int j;
	for (i = 0; i < 3; i++)
	{
		m_strtSecondaryJointParameters.cvPositionA[i] = 0;
		m_strtSecondaryJointParameters.cvPositionB[i] = 0;
		for (j = 0; j < 3; j++)
		{
			m_strtSecondaryJointParameters.rmRotationA[i][j] = 0;
			m_strtSecondaryJointParameters.rmRotationB[i][j] = 0;
		}
	}
	m_strtSecondaryJointParameters.pLinkA = NULL;
	m_strtSecondaryJointParameters.pLinkB = NULL;
	m_strtSecondaryJointParameters.nStabilization = STABILIZATION_NONE;
	m_strtSecondaryJointParameters.nSoftOrHard = SOFT_SEC_JOINT;
	m_strtSecondaryJointParameters.FJointFriction = 0;
}

CPPageSecJointData::~CPPageSecJointData()
{
}

void CPPageSecJointData::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageSecJointData)
	DDX_Control(pDX, IDC_COMBO_STABILIZATION, m_comboStabilization);
	DDX_Control(pDX, IDC_COMBO_LINK_B, m_comboLinkB);
	DDX_Control(pDX, IDC_COMBO_LINK_A, m_comboLinkA);
	DDX_CBIndex(pDX, IDC_COMBO_LINK_A, m_nLinkAIndex);
	DDX_CBIndex(pDX, IDC_COMBO_LINK_B, m_nLinkBIndex);
	DDX_CBIndex(pDX, IDC_COMBO_STABILIZATION, m_nStabilization);
	DDX_CBIndex(pDX, IDC_COMBO_JOINT_TYPE, m_nJointType);
	//}}AFX_DATA_MAP

	// verify that link A and link B are different -- place after the exchange of B so
	// the b combobox gets the focus on a fail
//	if (pDX->m_bSaveAndValidate && m_nLinkAIndex == m_nLinkBIndex)
//	{
//		MessageBox ("Link A and Link B cannot be the same.");
//		pDX->Fail ();
//	}

	DDX_Text(pDX, IDC_EDIT_A_POSITION1, m_strtSecondaryJointParameters.cvPositionA[0]);
	DDX_Text(pDX, IDC_EDIT_A_POSITION2, m_strtSecondaryJointParameters.cvPositionA[1]);
	DDX_Text(pDX, IDC_EDIT_A_POSITION3, m_strtSecondaryJointParameters.cvPositionA[2]);
	DDX_Text(pDX, IDC_EDIT_A_ROTATION11, m_strtSecondaryJointParameters.rmRotationA[0][0]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationA[0][0], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_A_ROTATION12, m_strtSecondaryJointParameters.rmRotationA[0][1]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationA[0][1], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_A_ROTATION13, m_strtSecondaryJointParameters.rmRotationA[0][2]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationA[0][2], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_A_ROTATION21, m_strtSecondaryJointParameters.rmRotationA[1][0]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationA[1][0], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_A_ROTATION22, m_strtSecondaryJointParameters.rmRotationA[1][1]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationA[1][1], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_A_ROTATION23, m_strtSecondaryJointParameters.rmRotationA[1][2]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationA[1][2], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_A_ROTATION31, m_strtSecondaryJointParameters.rmRotationA[2][0]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationA[2][0], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_A_ROTATION32, m_strtSecondaryJointParameters.rmRotationA[2][1]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationA[2][1], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_A_ROTATION33, m_strtSecondaryJointParameters.rmRotationA[2][2]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationA[2][2], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_B_POSITION1, m_strtSecondaryJointParameters.cvPositionB[0]);
	DDX_Text(pDX, IDC_EDIT_B_POSITION2, m_strtSecondaryJointParameters.cvPositionB[1]);
	DDX_Text(pDX, IDC_EDIT_B_POSITION3, m_strtSecondaryJointParameters.cvPositionB[2]);
	DDX_Text(pDX, IDC_EDIT_B_ROTATION11, m_strtSecondaryJointParameters.rmRotationB[0][0]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationB[0][0], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_B_ROTATION12, m_strtSecondaryJointParameters.rmRotationB[0][1]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationB[0][1], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_B_ROTATION13, m_strtSecondaryJointParameters.rmRotationB[0][2]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationB[0][2], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_B_ROTATION21, m_strtSecondaryJointParameters.rmRotationB[1][0]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationB[1][0], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_B_ROTATION22, m_strtSecondaryJointParameters.rmRotationB[1][1]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationB[1][1], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_B_ROTATION23, m_strtSecondaryJointParameters.rmRotationB[1][2]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationB[1][2], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_B_ROTATION31, m_strtSecondaryJointParameters.rmRotationB[2][0]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationB[2][0], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_B_ROTATION32, m_strtSecondaryJointParameters.rmRotationB[2][1]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationB[2][1], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_B_ROTATION33, m_strtSecondaryJointParameters.rmRotationB[2][2]);
	DDV_MinMaxDouble(pDX,  m_strtSecondaryJointParameters.rmRotationB[2][2], SECONDARY_JOINT_ROTATION_MATRIX_MIN, SECONDARY_JOINT_ROTATION_MATRIX_MAX);
	DDX_Text(pDX, IDC_EDIT_JOINT_FRICTION, m_strtSecondaryJointParameters.FJointFriction);
	DDV_MinMaxDouble(pDX, m_strtSecondaryJointParameters.FJointFriction, SEC_JOINT_FRICTION_MIN, SEC_JOINT_FRICTION_MAX);

}


BEGIN_MESSAGE_MAP(CPPageSecJointData, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageSecJointData)
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_CBN_SELCHANGE(IDC_COMBO_JOINT_TYPE, OnSelchangeComboJointType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageSecJointData message handlers

void CPPageSecJointData::OnOK() 
{
	m_strtSecondaryJointParameters.nStabilization = MapComboBoxToStabilization (m_nStabilization);
	m_strtSecondaryJointParameters.nSoftOrHard = MapComboBoxToJointType (m_nJointType);

	// Set the pointer to the links
	m_strtSecondaryJointParameters.pLinkA = (CdmvLinkData*) m_comboLinkA.GetItemData (m_nLinkAIndex);
	m_strtSecondaryJointParameters.pLinkB = (CdmvLinkData*) m_comboLinkB.GetItemData (m_nLinkBIndex);
	
	ASSERT (m_pCdmvSecJointData);
	m_pCdmvSecJointData->SetSecondaryJointParameters (&m_strtSecondaryJointParameters);
	
	CPropertyPage::OnOK();
}

BOOL CPPageSecJointData::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ASSERT (m_pCdmvSecJointData);
	m_pCdmvSecJointData->GetSecondaryJointParameters (&m_strtSecondaryJointParameters);
	m_nStabilization = MapStabilizationToComboBox (
		m_strtSecondaryJointParameters.nStabilization);
	m_nJointType = MapJointTypeToComboBox (
		m_strtSecondaryJointParameters.nSoftOrHard);
		
	// Only want the stabilization combo enabled when Hard Sec Joint is selected
	if (m_nJointType == CB_SOFT_SEC_JOINT)
		m_comboStabilization.EnableWindow (FALSE);
	else
		m_comboStabilization.EnableWindow (TRUE);
	
	
	ASSERT (m_pCdmvArticulationData);
	
	int nCounter;
	int nNumberOfLinks = m_pCdmvArticulationData->m_arrayLinks.GetSize ();
	int nReturn;

	// just add empty strings to reserve the space -- will be filled when the
	// combo box is filled
	// While going through the list, find index of the currently selected link
	// Also set the data as a pointer to the link, so the link pointer can be
	// retrieved by combo box index number in the OnOK
	for (nCounter = 0; nCounter < nNumberOfLinks; nCounter++)
	{
		nReturn = m_comboLinkA.AddString ("");
		ASSERT (nReturn != CB_ERR && nReturn != CB_ERRSPACE);
		nReturn = m_comboLinkB.AddString ("");
		ASSERT (nReturn != CB_ERR && nReturn != CB_ERRSPACE);
		CdmvLinkData* pLink = m_pCdmvArticulationData->m_arrayLinks.GetAt (nCounter).pLink;
		if (pLink == m_strtSecondaryJointParameters.pLinkA)
			m_nLinkAIndex = nCounter;
		if (pLink == m_strtSecondaryJointParameters.pLinkB)
			m_nLinkBIndex = nCounter;
		nReturn = m_comboLinkA.SetItemData (nCounter, (DWORD) pLink);
		ASSERT (nReturn != CB_ERR);
		nReturn = m_comboLinkB.SetItemData (nCounter, (DWORD) pLink);
		ASSERT (nReturn != CB_ERR);
	}


	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPPageSecJointData::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemHeight = 16;	
//	CPropertyPage::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CPPageSecJointData::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
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
		CBitmap bitmapLink;
		CString strLinkLabel = m_pCdmvArticulationData->m_arrayLinks.GetAt (nIndex).pLink->GetName ();
		switch (m_pCdmvArticulationData->m_arrayLinks.GetAt (nIndex).pLink->GetLinkType ())
		{
		case REVOLUTE_LINK:
			bitmapLink.LoadBitmap (IDB_BITMAP_REVOLUTE_LINK);
			break;
		case PRISMATIC_LINK:
			bitmapLink.LoadBitmap (IDB_BITMAP_PRISMATIC_LINK);
			break;
		case STATIC_ROOT_LINK:
			bitmapLink.LoadBitmap (IDB_BITMAP_STATIC_ROOT_LINK);
			break;
		case MOBILE_BASE_LINK:
			bitmapLink.LoadBitmap (IDB_BITMAP_MOBILE_BASE_LINK);
			break;
		case SPHERICAL_LINK:
			bitmapLink.LoadBitmap (IDB_BITMAP_SPHERICAL_LINK);
			break;
		case ZSCREW_TX_LINK:
			bitmapLink.LoadBitmap (IDB_BITMAP_ZSCREW_TX_LINK);
			break;
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
		CBitmap* pOldBitmap = dcMem.SelectObject (&bitmapLink);

		if (lpDrawItemStruct->itemState & ODS_SELECTED)
			dc.BitBlt (rect.left, rect.top, 16, 16, &dcMem, 0, 0, MERGEPAINT);
		else
			dc.BitBlt (rect.left, rect.top, 16, 16, &dcMem, 0, 0, MERGECOPY);

		dcMem.SelectObject (pOldBitmap);

		dc.TextOut (rect.left + 18, rect.top + 1, strLinkLabel);
	}

	dc.Detach ();
//	CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

// to abstract the order in the combo box from the definition of stabilization in the sec joint class
int CPPageSecJointData::MapStabilizationToComboBox(StabilizationType nStabilization)
{
	switch (nStabilization)
	{
	case STABILIZATION_NONE:
		return CB_NONE;
		break;
	case STABILIZATION_BAUMGARTE:
		return CB_BAUMGARTE;
		break;
	case STABILIZATION_SPRING_DAMPER:
		return CB_SPRING_DAMPER;
		break;
	default:
		ASSERT (FALSE);
		return -1; // just to make compiler happy
		break;
	}
}

StabilizationType CPPageSecJointData::MapComboBoxToStabilization(int nCBStablization)
{
	switch (nCBStablization)
	{
	case CB_NONE:
		return STABILIZATION_NONE;
		break;
	case CB_BAUMGARTE:
		return STABILIZATION_BAUMGARTE;
		break;
	case CB_SPRING_DAMPER:
		return STABILIZATION_SPRING_DAMPER;
		break;
	default:
		ASSERT (FALSE);
		return STABILIZATION_NONE; // just to make compiler happy
		break;
	}
}

int CPPageSecJointData::MapComboBoxToJointType(int nSoftOrHard)
{

	switch (nSoftOrHard)
	{
	case CB_SOFT_SEC_JOINT:
		return SOFT_SEC_JOINT;
		break;
	case CB_HARD_SEC_JOINT:
		return HARD_SEC_JOINT;
		break;
	default:
		ASSERT (FALSE);
		return -1; // just to make compiler happy
		break;
	}
}

int CPPageSecJointData::MapJointTypeToComboBox(int nSoftOrHard)
{
	switch (nSoftOrHard)
	{
	case SOFT_SEC_JOINT:
		return CB_SOFT_SEC_JOINT;
		break;
	case HARD_SEC_JOINT:
		return CB_HARD_SEC_JOINT;
		break;
	default:
		ASSERT (FALSE);
		return -1; // just to make compiler happy
		break;
	}
}

void CPPageSecJointData::OnSelchangeComboJointType() 
{
	UpdateData (TRUE);
	
	// Only want the stabilization combo enabled when Hard Sec Joint is selected
	if (m_nJointType == CB_SOFT_SEC_JOINT)
		m_comboStabilization.EnableWindow (FALSE);
	else
		m_comboStabilization.EnableWindow (TRUE);
}
