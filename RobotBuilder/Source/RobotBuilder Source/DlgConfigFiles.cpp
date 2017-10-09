// DlgConfigFiles.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgConfigFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigFiles dialog


CDlgConfigFiles::CDlgConfigFiles(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfigFiles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConfigFiles)
	m_strEnvironmentFile = _T("");
	m_strArticulationFile = _T("");
	m_strControlFile = _T("");
	//}}AFX_DATA_INIT

	m_pCdmvCFGData = NULL;
}


void CDlgConfigFiles::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConfigFiles)
	DDX_Text(pDX, IDC_EDIT_ENVIRONMENT_FILE, m_strEnvironmentFile);
	DDX_Text(pDX, IDC_EDIT_ARTICULATION_FILE, m_strArticulationFile);
	DDX_Text(pDX, IDC_EDIT_CONTROL_FILE, m_strControlFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConfigFiles, CDialog)
	//{{AFX_MSG_MAP(CDlgConfigFiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigFiles message handlers

void CDlgConfigFiles::SetDataClass(CdmvCFGData *pCdmvCFGData)
{
	ASSERT (pCdmvCFGData);

	m_pCdmvCFGData = pCdmvCFGData;
}

BOOL CDlgConfigFiles::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make sure the data class has been set
	ASSERT (m_pCdmvCFGData);
	
	// All of these are display only
	
	// Get the environment file
	CString strEnvironmentPath;
	m_pCdmvCFGData->GetEnvironmentFile (m_strEnvironmentFile, strEnvironmentPath);	
	
	// Get the articulation file
	CString strPath;
	m_pCdmvCFGData->GetFirstArticulationFile (m_strArticulationFile, strPath);

	// Get the control file
	m_pCdmvCFGData->GetFirstControlFile (m_strControlFile, strPath);

	// Update the dialog with this data
	BOOL bSuccess;
	bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgConfigFiles::ValidateData()
{
	//This dialog is read only, so data must be valid
	return TRUE;
}

BOOL CDlgConfigFiles::ValidateAndSaveData()
{
	//This dialog is read only, so there is no data to save
	return ValidateData();
}
