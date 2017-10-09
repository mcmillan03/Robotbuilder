// DlgEnvironmentData.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgEnvironmentData.h"
#include "DlgEnvTreadmillData.h"
#include "ParserTerrain.h"
#include "ParserTreadmill.h"
#include "FindFile.h"
#include "DMViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvironmentData dialog


CDlgEnvironmentData::CDlgEnvironmentData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnvironmentData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEnvironmentData)
	m_nEnvironmentType = 0;
	//}}AFX_DATA_INIT
	m_strtEnvironmentData.cvGravity[0] = 0;
	m_strtEnvironmentData.cvGravity[1] = 0;
	m_strtEnvironmentData.cvGravity[2] = 0;

	m_strtEnvironmentData.fGroundNormalDamperConstant = 0;
	m_strtEnvironmentData.fGroundNormalSpringConstant = 0;
	m_strtEnvironmentData.fGroundPlanarDamperConstant = 0;
	m_strtEnvironmentData.fGroundPlanarSpringConstant = 0;
	m_strtEnvironmentData.fu_k = 0;
	m_strtEnvironmentData.fu_s = 0;
	m_strtEnvironmentData.strDataFile = "";
	m_strtEnvironmentData.eEnvironmentType = ENV_TERRAIN;

	m_ppCdmvEnvironmentData = NULL;
	m_pCdmvTerrainData = NULL;
	m_pCdmvTreadmillData = NULL;
}

CDlgEnvironmentData::~CDlgEnvironmentData ()
{
}


void CDlgEnvironmentData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEnvironmentData)
	DDX_Radio(pDX, IDC_RADIO_TERRAIN, m_nEnvironmentType);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_DETAILS_FILE, m_strtEnvironmentData.strDataFile);
	DDX_Text(pDX, IDC_EDIT_GRAVITY_X, m_strtEnvironmentData.cvGravity[0]);
	DDX_Text(pDX, IDC_EDIT_GRAVITY_Y, m_strtEnvironmentData.cvGravity[1]);
	DDX_Text(pDX, IDC_EDIT_GRAVITY_Z, m_strtEnvironmentData.cvGravity[2]);
	DDX_Text(pDX, IDC_EDIT_NORMAL_DAMPER_CONSTANT, 
		m_strtEnvironmentData.fGroundNormalDamperConstant);
	DDV_MinMaxInt(pDX, m_strtEnvironmentData.fGroundNormalDamperConstant,
		ENV_NORMAL_DAMPER_MIN, ENV_NORMAL_DAMPER_MAX);
	DDX_Text(pDX, IDC_EDIT_NORMAL_SPRING_CONSTANT, 
		m_strtEnvironmentData.fGroundNormalSpringConstant);
	DDV_MinMaxInt(pDX, m_strtEnvironmentData.fGroundNormalSpringConstant,
		ENV_NORMAL_SPRING_MIN, ENV_NORMAL_SPRING_MAX);
	DDX_Text(pDX, IDC_EDIT_PLANAR_DAMPER_CONSTANT, 
		m_strtEnvironmentData.fGroundPlanarDamperConstant);
	DDV_MinMaxInt(pDX, m_strtEnvironmentData.fGroundPlanarDamperConstant,
		ENV_PLANAR_DAMPER_MIN, ENV_PLANAR_DAMPER_MAX);
	DDX_Text(pDX, IDC_EDIT_PLANAR_SPRING_CONSTANT, 
		m_strtEnvironmentData.fGroundPlanarSpringConstant);
	DDV_MinMaxInt(pDX, m_strtEnvironmentData.fGroundPlanarSpringConstant,
		ENV_PLANAR_SPRING_MIN, ENV_PLANAR_SPRING_MAX);
	DDX_Text(pDX, IDC_EDIT_UK, m_strtEnvironmentData.fu_k);
	DDV_MinMaxInt(pDX, m_strtEnvironmentData.fu_k,
		ENV_KINETIC_FRICTION_MIN, ENV_KINETIC_FRICTION_MAX);
	DDX_Text(pDX, IDC_EDIT_US, m_strtEnvironmentData.fu_s);
	DDV_MinMaxInt(pDX, m_strtEnvironmentData.fu_s,
		ENV_STATIC_FRICTION_MIN, ENV_STATIC_FRICTION_MAX);
}


BEGIN_MESSAGE_MAP(CDlgEnvironmentData, CDialog)
	//{{AFX_MSG_MAP(CDlgEnvironmentData)
	ON_BN_CLICKED(IDC_RADIO_CONVEYOR, OnRadioTreadmill)
	ON_BN_CLICKED(IDC_RADIO_TERRAIN, OnRadioTerrain)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_DETAILS, OnButtonEditDetails)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvironmentData message handlers

int CDlgEnvironmentData::DoModal() 
{
	ASSERT (m_ppCdmvEnvironmentData);
	
	(*m_ppCdmvEnvironmentData)->GetEnvironmentData (&m_strtEnvironmentData);

	return CDialog::DoModal();
}

void CDlgEnvironmentData::OnOK() 
{
	// Make sure the environment stuff is OK first
	if (!UpdateData ())
		return;
	
	if (m_nEnvironmentType == RB_TERRAIN)
	{
		// Update the type
		m_strtEnvironmentData.eEnvironmentType = ENV_TERRAIN;

		// Save the general environment information
		m_pCdmvTerrainData->SetEnvironmentData (&m_strtEnvironmentData);

		// Now need to see if this is new data or not by looking at the type of the original
		// environment
		if ((*m_ppCdmvEnvironmentData)->GetEnvironmentType () != ENV_TERRAIN)
		{
			// It's different so delete the previous environment
			delete *m_ppCdmvEnvironmentData;
			// Set the pointer to the new environment
			*m_ppCdmvEnvironmentData = m_pCdmvTerrainData;
		}
	}
	else // it's a RB_CONVEYOR
	{
		// Update the type
		m_strtEnvironmentData.eEnvironmentType = ENV_TREADMILL;

		// Save the general environment information
		m_pCdmvTreadmillData->SetEnvironmentData (&m_strtEnvironmentData);

		// Now need to see if this is new data or not by looking at the type of the original
		// environment
		if ((*m_ppCdmvEnvironmentData)->GetEnvironmentType () != ENV_TREADMILL)
		{
			// It's different so delete the previous environment
			delete *m_ppCdmvEnvironmentData;
			// Set the pointer to the new environment
			*m_ppCdmvEnvironmentData = m_pCdmvTreadmillData;
		}
	}

	CDialog::OnOK();
}

//void CDlgEnvironmentData::OnButtonTerrainBrowse() 
//{
//	CFileDialog dlg (TRUE, /* make an open dlg */
//		".dat", /* default extension */
//		NULL, /* initial filename */
//		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
//		"Terrain Files (*.dat)|*.dat||",	/* filter */
//		NULL /* parent */
//		);
//	
//	if (dlg.DoModal () == IDOK)
//	{	
//		m_strtEnvironmentData.strTerrainFile = dlg.GetPathName ();
//		// Now update to reflect the change
//		UpdateData (FALSE);
//	}		
//}

void CDlgEnvironmentData::OnRadioTreadmill() 
{
	// Check if changed
	if (m_nEnvironmentType != RB_TREADMILL)
	{
		// Then save new type
		m_nEnvironmentType = RB_TREADMILL;

		// Clear the details file because it no longer applies to this data
		m_strtEnvironmentData.strDataFile = "";
		SetDlgItemText (IDC_EDIT_DETAILS_FILE, "");

		// Set the details file title
		SetDlgItemText (IDC_STATIC_DETAILS_FILE, "Treadmill File:");

		// Set the button text
		SetDlgItemText (IDC_BUTTON_EDIT_DETAILS, "Edit Treadmill Data...");
	}
}

void CDlgEnvironmentData::OnRadioTerrain() 
{
	// Check if changed
	if (m_nEnvironmentType != RB_TERRAIN)
	{
		// Then save new type
		m_nEnvironmentType = RB_TERRAIN;

		// Clear the details file because it no longer applies to this data
		m_strtEnvironmentData.strDataFile = "";
		SetDlgItemText (IDC_EDIT_DETAILS_FILE, "");

		// Set the details file title
		SetDlgItemText (IDC_STATIC_DETAILS_FILE, "Terrain File:");

		// Set the button text
		SetDlgItemText (IDC_BUTTON_EDIT_DETAILS, "Edit Terrain Data...");
	}
}


BOOL CDlgEnvironmentData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Create a temporary class to hold the data for the dialog boxes.

	// Show and select the currently selected environment type
	if ((*m_ppCdmvEnvironmentData)->GetEnvironmentType () == ENV_TERRAIN)
	{
		// Save the data as terrain via downcast
		m_pCdmvTerrainData = dynamic_cast<CdmvTerrainData*>(*m_ppCdmvEnvironmentData);

		m_nEnvironmentType = RB_TERRAIN;

		// Create a class to hold the data for the treadmill in case it is
		// switched to that
		try {
			m_pCdmvTreadmillData = new CdmvTreadmillData;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}

		// Copy the common data
		structEnvironmentData strtEnvironmentData; // holds the common data
		(*m_ppCdmvEnvironmentData)->GetEnvironmentData (&strtEnvironmentData);
		m_pCdmvTreadmillData->SetEnvironmentData (&strtEnvironmentData);

		// Set the details file title
		SetDlgItemText (IDC_STATIC_DETAILS_FILE, "Terrain File:");

		// Set the button text
		SetDlgItemText (IDC_BUTTON_EDIT_DETAILS, "Edit Terrain Data...");
	}
	else
	{
		// Save the data as treadmill via down cast
		m_pCdmvTreadmillData = dynamic_cast<CdmvTreadmillData*>(*m_ppCdmvEnvironmentData);

		m_nEnvironmentType = RB_TREADMILL;

		// Create a class to hold the data for the conveyor, in case it is
		// switch to that
		try {
			m_pCdmvTerrainData = new CdmvTerrainData;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}
		
		// Copy the common data
		structEnvironmentData strtEnvironmentData; // holds the common data
		(*m_ppCdmvEnvironmentData)->GetEnvironmentData (&strtEnvironmentData);
		m_pCdmvTreadmillData->SetEnvironmentData (&strtEnvironmentData);

		// Set the details file title
		SetDlgItemText (IDC_STATIC_DETAILS_FILE, "Treadmill File:");

		// Set the button text
		SetDlgItemText (IDC_BUTTON_EDIT_DETAILS, "Edit Treadmill Data...");
	}
	

	// Update the dialog box to show the correct radio box selection of the environment type
	BOOL bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/*********************************************************************\
*  Function: CDlgEnvironmentData::SetDataClassPointer
*
*  Description: Sets the pointer to the pointer of the class describing the
*		environment.  The pointer to pointer is needed, so if the environment
*		type is changed, and a new environment class needs to be created, it
*		can be returned.
*
*  Returns:  void 
*  Argument: CdmvEnvironmentData **ppCdmvEnvironment - a pointer
*		containing a pointer to the environment
*
*  Created:  4/22/2001  Steven Rodenbaugh
\*********************************************************************/
void CDlgEnvironmentData::SetDataClassPointer(CdmvEnvironmentData **ppCdmvEnvironmentData)
{
	// Make sure the pointer is not NULL
	ASSERT (ppCdmvEnvironmentData);
	ASSERT (*ppCdmvEnvironmentData);

	// Save the pointer
	m_ppCdmvEnvironmentData = ppCdmvEnvironmentData;
}


void CDlgEnvironmentData::OnButtonEditDetails() 
{
	// Pick up the current environment type
	// It is updated everytime either are clicked, so don't need to 
	// do an UpdateData
	if (m_nEnvironmentType == RB_TERRAIN)
	{
		CDlgEnvTerrainData dlg;
		// Set the data pointer and file name
		dlg.SetDataClassPointer (m_pCdmvTerrainData);
		dlg.SetFilename (m_strtEnvironmentData.strDataFile, m_strtEnvironmentData.strDataPath);
		if (dlg.DoModal () == IDOK)
		{
			// Pick up the new filename -- note it might be the same
			dlg.GetFileName (m_strtEnvironmentData.strDataFile, m_strtEnvironmentData.strDataPath);

			// Display the new filename
			SetDlgItemText (IDC_EDIT_DETAILS_FILE, m_strtEnvironmentData.strDataFile);
		}
	}
	else if (m_nEnvironmentType == RB_TREADMILL)
	{
		CDlgEnvTreadmillData dlg;
		// Set the data pointer and file name
		dlg.SetDataClassPointer (m_pCdmvTreadmillData);
		dlg.SetFilename (m_strtEnvironmentData.strDataFile, m_strtEnvironmentData.strDataPath);
		if (dlg.DoModal () == IDOK)
		{
			// Pick up the new filename -- note it might be the same
			dlg.GetFilename (m_strtEnvironmentData.strDataFile, m_strtEnvironmentData.strDataPath);

			// Display the new filename
			SetDlgItemText (IDC_EDIT_DETAILS_FILE, m_strtEnvironmentData.strDataFile);
		}
	}
	else
	{
		// Unknown state
		ASSERT (FALSE);
	}
	
}

void CDlgEnvironmentData::OnButtonBrowse() 
{
	CFileDialog dlg (TRUE, /* make an open dlg */
		".dat", /* default extension */
		m_strtEnvironmentData.strDataFile, /* initial filename */
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"File (*.dat)|*.dat;||",	/* filter */
		NULL /* parent */
		);

	if (m_strtEnvironmentData.strDataPath.GetLength () > 0)
		dlg.m_ofn.lpstrInitialDir = m_strtEnvironmentData.strDataPath;
	
	if (dlg.DoModal () == IDOK)
	{	

		CString strPath;
		CString strFile = dlg.GetFileName ();
		BOOL bFindFile;
		
		if (m_nEnvironmentType == RB_TERRAIN)
		{
			bFindFile = CFindFile::FindFile (TERRAIN_FILE_TYPE, 
				strFile, strPath);
		}
		else if (m_nEnvironmentType == RB_TREADMILL)
		{
			bFindFile = CFindFile::FindFile (TREADMILL_FILE_TYPE, 
				strFile, strPath);
		}
		else
		{
			// Unknown state
			ASSERT (FALSE);
		}

		if (!bFindFile || ((strPath + strFile) != dlg.GetPathName ()))
		{
			if (IDYES == AfxMessageBox (FILE_NOT_FOUND_MSG, MB_YESNO))
			{
				strFile = dlg.GetPathName ();
				strPath = "";
			}
			else
			{
				// strFile stays the same
				// Strip off the file name from the full path
				strPath = (dlg.GetPathName ()).Left (dlg.GetPathName ().GetLength () -
					strFile.GetLength ());
			}
		}
	
		m_strtEnvironmentData.strDataFile = strFile;
		m_strtEnvironmentData.strDataPath = strPath;

		if (m_nEnvironmentType == RB_TERRAIN)
		{
			if (!CParserTerrain::ParseTerrainFile (strPath + strFile, m_pCdmvTerrainData))
			{
				// Failed to open, so reset the data -- the data is reset in the parser
				m_strtEnvironmentData.strDataFile = "";
				m_strtEnvironmentData.strDataPath = "";
			}
		}
		else if (m_nEnvironmentType == RB_TREADMILL)
		{
			if (!CParserTreadmill::ParseTreadmillFile (strPath + strFile, m_pCdmvTreadmillData))
			{
				// Failed to open, so reset the data -- the data is reset in the parser
				m_strtEnvironmentData.strDataFile = "";
				m_strtEnvironmentData.strDataPath = "";
			}
		}
		else
		{
			// Unknown state
			ASSERT(FALSE);
		}
	}	
	
	// Reset the displayed filename
	SetDlgItemText (IDC_EDIT_DETAILS_FILE, m_strtEnvironmentData.strDataFile);	
}

void CDlgEnvironmentData::OnCancel() 
{
	// Decide which to deallocate by seeing which is same as the saved
	// data pointer outside the class

	if (*m_ppCdmvEnvironmentData == m_pCdmvTerrainData)
	{
		// Then not using the conveyor so deallocate
		delete m_pCdmvTreadmillData;
		// Just to remind that it has been deallocated
		m_pCdmvTreadmillData = NULL;
	}
	else
	{
		// Then not using the terrain so deallocate
		delete m_pCdmvTerrainData;
		// Just to remind that it has been deallocated
		m_pCdmvTerrainData = NULL;
	}	
	CDialog::OnCancel();
}

// This is called if the close button is pressed on the title bar
void CDlgEnvironmentData::OnClose() 
{
	// Decide which to deallocate by seeing which is same as the saved
	// data pointer outside the class

	if (*m_ppCdmvEnvironmentData == m_pCdmvTerrainData)
	{
		// Then not using the conveyor so deallocate
		delete m_pCdmvTreadmillData;
		// Just to remind that it has been deallocated
		m_pCdmvTreadmillData = NULL;
	}
	else
	{
		// Then not using the terrain so deallocate
		delete m_pCdmvTerrainData;
		// Just to remind that it has been deallocated
		m_pCdmvTerrainData = NULL;
	}	
	CDialog::OnCancel();	
	CDialog::OnClose();
}
