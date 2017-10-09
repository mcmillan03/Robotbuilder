// PPageRigidBodyData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "PPageRigidBodyData.h"


#include "dmvLinkData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageRigidBodyData property page

IMPLEMENT_DYNCREATE(CPPageRigidBodyData, CPropertyPage)

CPPageRigidBodyData::CPPageRigidBodyData() : CPropertyPage(CPPageRigidBodyData::IDD)
{
	//{{AFX_DATA_INIT(CPPageRigidBodyData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strtRigidBodyInertialParameters.fMass = 0;
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[0] = 0;
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[1] = 0;
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[2] = 0;

	int i, j; // counters for 'for' loop
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			m_strtRigidBodyInertialParameters.ctIbar[i][j] = 0;
		}
	}

	m_pCdmvRigidBodyData = NULL;

}

CPPageRigidBodyData::~CPPageRigidBodyData()
{
}

void CPPageRigidBodyData::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageRigidBodyData)
	DDX_Control(pDX, IDC_LIST_CONTACTS, m_listboxContacts);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_CENTER_GRAVITY_X, m_strtRigidBodyInertialParameters.cvCenterGravityPosition[0]);
	DDX_Text(pDX, IDC_EDIT_CENTER_GRAVITY_Y, m_strtRigidBodyInertialParameters.cvCenterGravityPosition[1]);
	DDX_Text(pDX, IDC_EDIT_CENTER_GRAVITY_Z, m_strtRigidBodyInertialParameters.cvCenterGravityPosition[2]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_11, m_strtRigidBodyInertialParameters.ctIbar[0][0]);
	DDV_MinMaxDouble(pDX,  m_strtRigidBodyInertialParameters.ctIbar[0][0], LINK_INERTIA_DIAGONAL_MIN, LINK_INERTIA_DIAGONAL_MAX);
	DDX_Text(pDX, IDC_EDIT_INERTIA_12, m_strtRigidBodyInertialParameters.ctIbar[0][1]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_13, m_strtRigidBodyInertialParameters.ctIbar[0][2]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_21, m_strtRigidBodyInertialParameters.ctIbar[1][0]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_22, m_strtRigidBodyInertialParameters.ctIbar[1][1]);
	DDV_MinMaxDouble(pDX,  m_strtRigidBodyInertialParameters.ctIbar[1][1], LINK_INERTIA_DIAGONAL_MIN, LINK_INERTIA_DIAGONAL_MAX);
	DDX_Text(pDX, IDC_EDIT_INERTIA_23, m_strtRigidBodyInertialParameters.ctIbar[1][2]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_31, m_strtRigidBodyInertialParameters.ctIbar[2][0]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_32, m_strtRigidBodyInertialParameters.ctIbar[2][1]);
	DDX_Text(pDX, IDC_EDIT_INERTIA_33, m_strtRigidBodyInertialParameters.ctIbar[2][2]);
	DDV_MinMaxDouble(pDX,  m_strtRigidBodyInertialParameters.ctIbar[2][2], LINK_INERTIA_DIAGONAL_MIN, LINK_INERTIA_DIAGONAL_MAX);
	DDX_Text(pDX, IDC_EDIT_MASS, m_strtRigidBodyInertialParameters.fMass);
	DDV_MinMaxDouble(pDX,  m_strtRigidBodyInertialParameters.fMass, LINK_MASS_MIN, LINK_MASS_MAX);
}


BEGIN_MESSAGE_MAP(CPPageRigidBodyData, CPropertyPage)
	//{{AFX_MSG_MAP(CPPageRigidBodyData)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CONTACT, OnButtonAddContact)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_CONTACT, OnButtonDeleteContact)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_CONTACT, OnButtonEditContact)
	ON_LBN_DBLCLK(IDC_LIST_CONTACTS, OnDblclkListContacts)
	ON_MESSAGE(PSM_QUERYSIBLINGS, OnQuerySiblings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageRigidBodyData message handlers

void CPPageRigidBodyData::OnOK() 
{
	ASSERT (m_pCdmvRigidBodyData);

	// Now save the inertial parameters
	m_pCdmvRigidBodyData->SetInertialParameters (&m_strtRigidBodyInertialParameters);
	
	// Delete the previously stored contact model
	m_pCdmvRigidBodyData->DeleteContactModel ();


	// Create a new contact model, but watch for exceptions
	CdmvContactModelData* pdmvContactModel = NULL;
	try {
		pdmvContactModel = new CdmvContactModelData;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	// Get the count
	int nEntryCount = m_listboxContacts.GetCount ();
	ASSERT (nEntryCount != LB_ERR);

	// Allocate space for the arrays
	float* pfPositions = NULL;
	try {
		pfPositions = new float[3*nEntryCount];
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		// Free the allocation from earlier.
		delete pdmvContactModel;
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	int nCounter;
	for (nCounter = 0; nCounter < nEntryCount; nCounter++)
	{
		// Pick up the text from the list box.
		CString strItemText;
		m_listboxContacts.GetText (nCounter, strItemText);

		// Parse the string into the allocated float array.
		int nSuccessfulConversions = sscanf (strItemText, "%f %f %f", 
			(pfPositions + 3*nCounter + 0),
			(pfPositions + 3*nCounter + 1),
			(pfPositions + 3*nCounter + 2));
		ASSERT (nSuccessfulConversions == 3);
	}

	// Set the positions in the contact model
	pdmvContactModel->SetContactPoints (nEntryCount, (float (*)[3]) pfPositions);

	// Now save contact model to the rigid body
	m_pCdmvRigidBodyData->SetContactModel (pdmvContactModel);

	// Free the previously allocation float array that held the positions for
	// the contact model
	delete [] pfPositions;
	
	CPropertyPage::OnOK();
}

BOOL CPPageRigidBodyData::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	// Populate the contact list box
	ASSERT (m_pCdmvRigidBodyData);
	// If there are 0 contact points in the config file, the parser does not set
	// a contact model.  Consequently, the code needs to check if the contact model
	// exists first
	if (m_pCdmvRigidBodyData->GetContactModel ())
	{
		int nCounter;
		int nNumPositions = m_pCdmvRigidBodyData->GetContactModel ()->m_arrayPosition.GetSize ();
		for (nCounter = 0; nCounter < nNumPositions; nCounter++)
		{
			structCartesianVector strtcvPos = m_pCdmvRigidBodyData->GetContactModel ()
				->m_arrayPosition.GetAt (nCounter);
			// Form the text string to place in the list box.
			CString strItemText;
			strItemText.Format (IDS_STRING_CONTACT_FORMAT, strtcvPos.fXval,
				strtcvPos.fYval, strtcvPos.fZval);
			int nReturn;
			// Add the string and verify success
			nReturn = m_listboxContacts.AddString (strItemText);
			ASSERT (nReturn != LB_ERR);
			if (nReturn == LB_ERRSPACE)
			{
				// Then ran out of memory.
				AfxMessageBox ("Out of Memory - Could not add contact to list", MB_OK);
			}
		}
	}

	// Set the other members
	m_pCdmvRigidBodyData->GetInertialParameters (&m_strtRigidBodyInertialParameters);

	// Set DDX the dialog data.
	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);	

	MakeInertialParametersReadOnly (TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPPageRigidBodyData::OnButtonAddContact() 
{
	CDlgContactPosition dlg;

	dlg.m_fPositionX = 0.0f;
	dlg.m_fPositionY = 0.0f;
	dlg.m_fPositionZ = 0.0f;

	if (dlg.DoModal () == IDOK)
	{
		CString strContact;
		strContact.Format (IDS_STRING_CONTACT_FORMAT, dlg.m_fPositionX, dlg.m_fPositionY,
			dlg.m_fPositionZ);
		int nReturn;
		nReturn = m_listboxContacts.AddString (strContact);
		ASSERT (nReturn != LB_ERR);
		// Should check for an out of memory condition
		if (nReturn == LB_ERRSPACE)
			AfxMessageBox ("Unable to add contact because out of memory.", MB_OK);
	}	
}

void CPPageRigidBodyData::OnButtonDeleteContact() 
{
	// Get the current selection.
	int nIndex = m_listboxContacts.GetCurSel ();
	// If there is no selection in the list box, this will return an 'error',
	// but it is OK.  Just display a message that no item was selected.
	if (nIndex == LB_ERR)
	{
		AfxMessageBox ("There is no contact selected.", MB_OK);
		return;
	}

	// Now delete the current selection
	int nReturnStatus;
	nReturnStatus = m_listboxContacts.DeleteString (nIndex);
	ASSERT (nReturnStatus != LB_ERR);		
}

void CPPageRigidBodyData::OnButtonEditContact() 
{
	EditContact ();	
}

void CPPageRigidBodyData::OnDblclkListContacts() 
{
	EditContact ();	
}

void CPPageRigidBodyData::EditContact()
{
	int nIndex = m_listboxContacts.GetCurSel ();
	// If there is no selection in the list box, this will return an 'error',
	// but it is OK.  Just display a message that no item was selected.
	if (nIndex == LB_ERR)
	{
		AfxMessageBox ("There is no contact selected.", MB_OK);
		return;
	}

	CString strText;
	m_listboxContacts.GetText (nIndex, strText);
	
	// Declare the edit dialog to set the members
	CDlgContactPosition dlg;

	// Parse out the data
	int nConversions;
	nConversions = sscanf (strText, "%f %f %f", &dlg.m_fPositionX,
		&dlg.m_fPositionY, &dlg.m_fPositionZ);
	ASSERT (nConversions == 3);
	
	if (dlg.DoModal () == IDOK)
	{
		int nReturnStatus;
		CString strItemText;
		strItemText.Format (IDS_STRING_CONTACT_FORMAT, dlg.m_fPositionX,
			dlg.m_fPositionY, dlg.m_fPositionZ);
		// Delete the string that was just edited
		nReturnStatus = m_listboxContacts.DeleteString (nIndex);
		ASSERT (nReturnStatus != LB_ERR);
		// Change the item text to reflect the edit
		nReturnStatus = m_listboxContacts.InsertString (nIndex, strItemText);
		// I am assuming that LB_ERR wont occur in releases
		ASSERT (nReturnStatus != LB_ERR);
		// But the space error should be examined.
		if (nReturnStatus == LB_ERRSPACE)
			AfxMessageBox ("Not enough space to insert in the list box.", MB_OK);
	}
}

BOOL CPPageRigidBodyData::OnSetActive() 
{
	// Make edits read-only if .rbm loaded
	if ((dynamic_cast <CdmvObject*> (m_pCdmvRigidBodyData))->UseRbmData ())
		MakeInertialParametersReadOnly (TRUE);
	else
		MakeInertialParametersReadOnly (FALSE);
	return CPropertyPage::OnSetActive();
}

// Call with TRUE parameter to make the page items read-only, otherwise they
// are editable.  
void CPPageRigidBodyData::MakeInertialParametersReadOnly (BOOL bEnableReadOnly)
{
	BOOL bEnableEditable = !bEnableReadOnly;
	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_MASS)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);

	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_CENTER_GRAVITY_X)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);
	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_CENTER_GRAVITY_Y)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);
	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_CENTER_GRAVITY_Z)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);

	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_INERTIA_11)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);
	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_INERTIA_12)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);
	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_INERTIA_13)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);
	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_INERTIA_21)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);
	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_INERTIA_22)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);
	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_INERTIA_23)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);
	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_INERTIA_31)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);
	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_INERTIA_32)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);
	VERIFY(::SendMessage (GetDlgItem (IDC_EDIT_INERTIA_33)->GetSafeHwnd (), EM_SETREADONLY, bEnableReadOnly, NULL) != 0);
}

// Handles query sibling message.
LRESULT CPPageRigidBodyData::OnQuerySiblings( WPARAM wParam, LPARAM lParam )
{
	// A wParam of 1 will be interpretted as a new physical data that this page should used
	if (wParam == 1)
	{
		// Read in from the lParam, interpretted as an array of doubles containing the values
		// of interest
		ASSERT (AfxIsValidAddress (reinterpret_cast<void*> (lParam), sizeof(double)*13, TRUE));

		m_strtRigidBodyInertialParameters = *(reinterpret_cast<structRigidBodyInertialParameters*> (lParam));
		// This will reset all of the edit's so update the data
		VERIFY (UpdateData (FALSE));
	}
	
	// Message for some other page, so return 0 so the message will be passed on
   return 0;
}