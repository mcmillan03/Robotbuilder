// DlgEnvSaveTreadmillFile.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgEnvSaveTreadmillFile.h"
#include "GenerateTreadmillFile.h"
#include "GenerateTouch.h"
#include "FindFile.h"
#include "DMViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvSaveTreadmillFile dialog


CDlgEnvSaveTreadmillFile::CDlgEnvSaveTreadmillFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnvSaveTreadmillFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEnvSaveTreadmillFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgEnvSaveTreadmillFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEnvSaveTreadmillFile)
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_buttonSave);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEnvSaveTreadmillFile, CDialog)
	//{{AFX_MSG_MAP(CDlgEnvSaveTreadmillFile)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_AS, OnButtonSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvSaveTreadmillFile message handlers

void CDlgEnvSaveTreadmillFile::OnButtonSave() 
{
	// This should only be called if a filename has been supplied
	ASSERT (m_strFilename != "");	

	if (CGenerateTreadmillFile::CreateTreadmillFile (m_strPath + m_strFilename, m_pCdmvTreadmillData))
	{
		// Done, so leave dialog
		OnOK ();
	}
	// If the output failed, the outputter will display an error message and then return
	// back to the dialog box (possibly to let the user choose a different name)
}

void CDlgEnvSaveTreadmillFile::OnButtonSaveAs() 
{
	CFileDialog dlg (FALSE, /* make an save dlg */
		".dat", /* default extension */
		m_strFilename, /* initial filename */
		OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"Treadmill File (*.dat)|*.dat;||",	/* filter */
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

		BOOL bFindFile = CFindFile::FindFile (TREADMILL_FILE_TYPE, 
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

		if (!CGenerateTreadmillFile::CreateTreadmillFile (strPath + strFile, m_pCdmvTreadmillData))
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

void CDlgEnvSaveTreadmillFile::SetDataPointer(CdmvTreadmillData *pCdmvTreadmillData)
{
	m_pCdmvTreadmillData = pCdmvTreadmillData;
}

void CDlgEnvSaveTreadmillFile::SetFileName(CString strFilename, CString strPath)
{
	m_strFilename = strFilename;
	m_strPath = strPath;
}

// Provide a get in case the filename was changed by a save as
void CDlgEnvSaveTreadmillFile::GetFilename(CString &rstrFilename, CString &rstrPath) const
{
	rstrFilename = m_strFilename;
	rstrPath = m_strPath;
}

BOOL CDlgEnvSaveTreadmillFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make sure the data has been set
	ASSERT (m_pCdmvTreadmillData);

	// If no filename has been supplied, assume one has not been given, so
	// disable the save button
	if (m_strFilename == "")
		m_buttonSave.EnableWindow (FALSE);

	// Set the details text type specific to the type (treadmill or terrain)
	SetDlgItemText (IDC_STATIC_DETAILS_TYPE, "treadmill file.");
	SetDlgItemText (IDC_STATIC_DETAILS_TYPE2, "treadmill data.");

	SetWindowText ("Save Treadmill Data to File?");


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


