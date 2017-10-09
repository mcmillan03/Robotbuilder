// DlgEnvSaveTerrainFile.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgEnvSaveTerrainFile.h"
#include "GenerateTerrainFile.h"
#include "GenerateTouch.h"
#include "FindFile.h"
#include "DMViewerDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvSaveTerrainFile dialog


CDlgEnvSaveTerrainFile::CDlgEnvSaveTerrainFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnvSaveTerrainFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEnvSaveTerrainFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgEnvSaveTerrainFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEnvSaveTerrainFile)
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_buttonSave);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEnvSaveTerrainFile, CDialog)
	//{{AFX_MSG_MAP(CDlgEnvSaveTerrainFile)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_AS, OnButtonSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvSaveTerrainFile message handlers

void CDlgEnvSaveTerrainFile::OnButtonSave() 
{
	// This should only be called if a filename has been supplied
	ASSERT (m_strFilename != "");	

	if (CGenerateTerrainFile::CreateTerrainFile (m_strPath + m_strFilename, m_pCdmvTerrainData))
	{
		// Done, so leave dialog
		OnOK ();
	}
	// If the output failed, the outputter will display an error message and then return
	// back to the dialog box (possibly to let the user choose a different name)
}

void CDlgEnvSaveTerrainFile::OnButtonSaveAs() 
{
	CFileDialog dlg (FALSE, /* make an save dlg */
		".dat", /* default extension */
		m_strFilename, /* initial filename */
		OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"Terrain File (*.dat)|*.dat;||",	/* filter */
		NULL /* parent */
		);
	
	if (m_strPath.GetLength () > 0)
		dlg.m_ofn.lpstrInitialDir = m_strPath;

	if (dlg.DoModal () == IDOK)
	{	
		CString strPath;
		CString strFile = dlg.GetFileName ();
		
		// Need to touch the file to see if the find file can find it.
		// Note this should never fail, because the save dialog makes sure
		// the save directory is writable
		if (!CGenerateTouch::Touch (dlg.GetPathName ()))
		{
			AfxMessageBox (_T("The file could not be written.  Please verify that the file or directory is not read-only."));
			return;
		}
		
		BOOL bFindFile = CFindFile::FindFile (TERRAIN_FILE_TYPE, 
			strFile, strPath);
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

		if (!CGenerateTerrainFile::CreateTerrainFile (strPath + strFile, m_pCdmvTerrainData))
		{
			// This should never fail, because write problems should be caught above
			// with the touch.
			ASSERT (FALSE);
		}

		m_strFilename = strFile;
		m_strPath = strPath;
		OnOK ();
	}	
	

}

void CDlgEnvSaveTerrainFile::SetDataPointer(CdmvTerrainData *pCdmvTerrainData)
{
	m_pCdmvTerrainData = pCdmvTerrainData;
}

void CDlgEnvSaveTerrainFile::SetFileName(CString strFilename, CString strPath)
{
	m_strFilename = strFilename;
	m_strPath = strPath;
}

// Provide a get in case the filename was changed by a save as
void CDlgEnvSaveTerrainFile::GetFilename(CString &rstrFilename, CString &rstrPath) const
{
	rstrFilename = m_strFilename;
	rstrPath = m_strPath;
}

BOOL CDlgEnvSaveTerrainFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make sure the data has been set
	ASSERT (m_pCdmvTerrainData);

	// If no filename has been supplied, assume one has not been given, so
	// disable the save button
	if (m_strFilename == "")
		m_buttonSave.EnableWindow (FALSE);

	// Set the details text type specific to the type (treadmill or terrain)
	SetDlgItemText (IDC_STATIC_DETAILS_TYPE, "terrain file.");
	SetDlgItemText (IDC_STATIC_DETAILS_TYPE2, "terrain data.");

	SetWindowText ("Save Terrain Data to File?");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


