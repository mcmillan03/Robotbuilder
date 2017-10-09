// DlgConfigProperties.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgConfigProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigProperties dialog


CDlgConfigProperties::CDlgConfigProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfigProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConfigProperties)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgConfigProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConfigProperties)
	DDX_Control(pDX, IDC_TAB_MAIN, m_tabctrlTabMain);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConfigProperties, CDialog)
	//{{AFX_MSG_MAP(CDlgConfigProperties)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, OnSelchangeTabMain)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_MAIN, OnSelchangingTabMain)
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnButtonHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigProperties message handlers

void CDlgConfigProperties::SetDataClass(CdmvCFGData *pCdmvCFGData)
{
	ASSERT (pCdmvCFGData);

	// Update all of the tab dialog classes with the data class pointer
	m_dlgConfigSimulation.SetDataClass(pCdmvCFGData);
	m_dlgConfigAxes.SetDataClass(pCdmvCFGData);
	m_dlgConfigFiles.SetDataClass(pCdmvCFGData);
	m_dlgConfigBackground.SetDataClass(pCdmvCFGData);
	m_dlgConfigCamera.SetDataClass(pCdmvCFGData);
}

void CDlgConfigProperties::OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int nCurrentIndex = m_tabctrlTabMain.GetCurSel ();
	ASSERT (nCurrentIndex > -1);

	switch (nCurrentIndex)
	{
	case TAB_SIMULATION:	// Simulation Tab
		m_dlgConfigAxes.ShowWindow (SW_HIDE);
		m_dlgConfigFiles.ShowWindow (SW_HIDE);
		m_dlgConfigBackground.ShowWindow (SW_HIDE);
		m_dlgConfigCamera.ShowWindow (SW_HIDE);
		m_dlgConfigSimulation.ShowWindow (SW_SHOW);
		break;
	case TAB_AXES:			// Axes Tab
		m_dlgConfigSimulation.ShowWindow (SW_HIDE);
		m_dlgConfigFiles.ShowWindow (SW_HIDE);
		m_dlgConfigBackground.ShowWindow (SW_HIDE);
		m_dlgConfigCamera.ShowWindow (SW_HIDE);
		m_dlgConfigAxes.ShowWindow (SW_SHOW);
		break;
	case TAB_FILES:			// Files Tab
		m_dlgConfigSimulation.ShowWindow (SW_HIDE);
		m_dlgConfigBackground.ShowWindow (SW_HIDE);
		m_dlgConfigAxes.ShowWindow (SW_HIDE);
		m_dlgConfigCamera.ShowWindow (SW_HIDE);
		m_dlgConfigFiles.ShowWindow (SW_SHOW);
		break;
	case TAB_CAMERA:		// Camera Tab
		m_dlgConfigSimulation.ShowWindow (SW_HIDE);
		m_dlgConfigBackground.ShowWindow (SW_HIDE);
		m_dlgConfigAxes.ShowWindow (SW_HIDE);
		m_dlgConfigFiles.ShowWindow (SW_HIDE);
		m_dlgConfigCamera.ShowWindow (SW_SHOW);
		break;
	case TAB_BACKGROUND:	// Background Tab
		m_dlgConfigSimulation.ShowWindow (SW_HIDE);
		m_dlgConfigAxes.ShowWindow (SW_HIDE);
		m_dlgConfigFiles.ShowWindow (SW_HIDE);
		m_dlgConfigCamera.ShowWindow (SW_HIDE);
		m_dlgConfigBackground.ShowWindow (SW_SHOW);
		break;

	default:
		ASSERT (FALSE);
	}
	
	*pResult = 0;
}

void CDlgConfigProperties::OnSelchangingTabMain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	BOOL bSuccess;

	bSuccess = ValidateData();

	if (!bSuccess)
		*pResult = 1;
	else
		*pResult = 0;
}

void CDlgConfigProperties::OnOK() 
{
	// Check that the current tab is updated and valid

	if (ValidateAndSaveData())
	{
		CDialog::OnOK();
	}
}

void CDlgConfigProperties::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgConfigProperties::OnButtonHelp() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CDlgConfigProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Setup the Tab Control
	int nIndex;
	nIndex = m_tabctrlTabMain.InsertItem (TAB_SIMULATION, "Simulation");
	ASSERT (nIndex > -1);
	nIndex = m_tabctrlTabMain.InsertItem (TAB_AXES, "Axes");
	ASSERT (nIndex > -1);
	nIndex = m_tabctrlTabMain.InsertItem (TAB_FILES, "Files");
	ASSERT (nIndex > -1);
	nIndex = m_tabctrlTabMain.InsertItem (TAB_CAMERA, "Camera");
	ASSERT (nIndex > -1);
	nIndex = m_tabctrlTabMain.InsertItem (TAB_BACKGROUND, "Background");
	ASSERT (nIndex > -1);
	
	// Create the child windows for the tab ctrl
	CRect rectPlacement;
	m_tabctrlTabMain.GetWindowRect (&rectPlacement);
	ScreenToClient (rectPlacement);

	// Simulation Tab
	BOOL bSuccess = m_dlgConfigSimulation.Create(IDD_CONFIG_SIMULATION, this);
	ASSERT (bSuccess);
	m_dlgConfigSimulation.MoveWindow (rectPlacement.left+7, rectPlacement.top+21,
		rectPlacement.Width()-14, rectPlacement.Height()-27);

	// Axes Tab
	bSuccess = m_dlgConfigAxes.Create(IDD_CONFIG_AXES, this);
	ASSERT (bSuccess);
	m_dlgConfigAxes.MoveWindow (rectPlacement.left+7, rectPlacement.top+21,
		rectPlacement.Width()-14, rectPlacement.Height()-27);


	// Files Tab
	bSuccess = m_dlgConfigFiles.Create(IDD_CONFIG_FILES, this);
	ASSERT (bSuccess);
	m_dlgConfigFiles.MoveWindow (rectPlacement.left+7, rectPlacement.top+21,
		rectPlacement.Width()-14, rectPlacement.Height()-27);

	// Camera Tab
	bSuccess = m_dlgConfigCamera.Create(IDD_CONFIG_CAMERA, this);
	ASSERT (bSuccess);
	m_dlgConfigCamera.MoveWindow (rectPlacement.left+7, rectPlacement.top+21,
		rectPlacement.Width()-14, rectPlacement.Height()-27);

	// Background Tab
	bSuccess = m_dlgConfigBackground.Create(IDD_CONFIG_BACKGROUND, this);
	ASSERT (bSuccess);
	m_dlgConfigBackground.MoveWindow (rectPlacement.left+7, rectPlacement.top+21,
		rectPlacement.Width()-14, rectPlacement.Height()-27);
	
	// Set the tab control to the simulation tab
	m_tabctrlTabMain.SetCurSel(TAB_SIMULATION);

	// Start out by enabling the simulation window
	m_dlgConfigAxes.ShowWindow (SW_HIDE);
	m_dlgConfigFiles.ShowWindow (SW_HIDE);
	m_dlgConfigCamera.ShowWindow (SW_HIDE);
	m_dlgConfigBackground.ShowWindow (SW_HIDE);
	m_dlgConfigSimulation.ShowWindow (SW_SHOW);

	bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgConfigProperties::ValidateData()
{
	// If it has not been created, don't attempt to validate it
	if (m_tabctrlTabMain.GetSafeHwnd ())
	{
		int nIndex = m_tabctrlTabMain.GetCurSel();
		ASSERT (nIndex > -1);

		BOOL bSuccess;
		switch (nIndex)
		{
		case TAB_SIMULATION:
			bSuccess = m_dlgConfigSimulation.ValidateData();
			break;
		case TAB_AXES:
			bSuccess = m_dlgConfigAxes.ValidateData();
			break;
		case TAB_FILES:
			bSuccess = m_dlgConfigFiles.ValidateData();
			break;
		case TAB_BACKGROUND:
			bSuccess = m_dlgConfigBackground.ValidateData();
			break;
		case TAB_CAMERA:
			bSuccess = m_dlgConfigCamera.ValidateData();
			break;
		default:
			ASSERT(FALSE);
		}

		return bSuccess;
	}
	else
	{
		// Window hasn't been created, so nothing to validate
		return TRUE;
	}
}


BOOL CDlgConfigProperties::ValidateAndSaveData()
{
	return (m_dlgConfigSimulation.ValidateAndSaveData() &&
		m_dlgConfigAxes.ValidateAndSaveData() &&
		m_dlgConfigFiles.ValidateAndSaveData() &&
		m_dlgConfigBackground.ValidateAndSaveData() &&
		m_dlgConfigCamera.ValidateAndSaveData());
}

void CDlgConfigProperties::SetCameraDataClass(CCameraData *pCCameraData)
{
	ASSERT (pCCameraData);

	m_dlgConfigCamera.SetCameraDataClass(pCCameraData);
}

void CDlgConfigProperties::SetSystemDataClass(CdmvSystemData *pCdmvSystemData)
{
	ASSERT (pCdmvSystemData);

	m_dlgConfigCamera.SetSystemDataClass(pCdmvSystemData);
}

void CDlgConfigProperties::SetViewpointPointer(CWTKView* pWTKView)
{
	m_dlgConfigCamera.SetViewpointPointer(pWTKView);
}
