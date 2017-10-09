// DMViewer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DMViewer.h"

#include "MainFrm.h"
#include "DMViewerDoc.h"
#include "DMTreeView.h"

#include "FindFile.h"
#include "HyperLink.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDMViewerApp

BEGIN_MESSAGE_MAP(CDMViewerApp, CWinApp)
	//{{AFX_MSG_MAP(CDMViewerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SIM_TIME, OnUpdateIndicatorSimTime)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMViewerApp construction

CDMViewerApp::CDMViewerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDMViewerApp object

CDMViewerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDMViewerApp initialization

BOOL CDMViewerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	CFindFile::InitializeFindFile();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDMViewerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CDMTreeView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Lower my thread priority - this slows it down very slightly, but without it,
	// Explorer and other applications can become almost unresponsive
	AfxGetThread ()->SetThreadPriority (THREAD_PRIORITY_LOWEST);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_linkBugEmail;
	CHyperLink	m_linkHyperLinkClass;
	CHyperLink	m_linkRobotBuilderWebsite;
	CHyperLink	m_linkDynaMechs;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_LINK_BUG_EMAIL, m_linkBugEmail);
	DDX_Control(pDX, IDC_LINK_HYPERLINK_CLASS, m_linkHyperLinkClass);
	DDX_Control(pDX, IDC_LINK_ROBOTBUILDER_WEBSITE, m_linkRobotBuilderWebsite);
	DDX_Control(pDX, IDC_LINK_DYNAMECHS, m_linkDynaMechs);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDMViewerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDMViewerApp message handlers


BOOL CDMViewerApp::OnIdle(LONG lCount) 
{
	// Let the app doing any required processing.
	if (CWinApp::OnIdle(lCount))
		return TRUE;
	// Returning false every once in a while, will give the processor a break - otherwise,
	// the CPU goes to 100% because it is trying to update WTK all of the time
//	if (lCount > 5)
//		return FALSE;

	return ((CDMViewerDoc*) ((CFrameWnd*) this->GetMainWnd ())->GetActiveDocument ())->OnAppIdle (lCount);
}


void CDMViewerApp::UpdateMRU(CCmdUI* pCmdUI)
{
	OnUpdateRecentFileMenu (pCmdUI);
}


void CDMViewerApp::OnUpdateIndicatorSimTime(CCmdUI* pCmdUI)
{
	double dSimulationTimeS = ((CDMViewerDoc*) ((CFrameWnd*) this->GetMainWnd ())->GetActiveDocument ())->GetDynaMechs ()->GetSimulationTime ();

	// Change to a string
	CString strSimulationTime;
	int nMilliseconds = (int) (((int) (dSimulationTimeS * 1000 + .5) % 1000) );
	int nSeconds = (int) (floor (dSimulationTimeS)) % 60;
	int nMinutes = (int) ((floor (dSimulationTimeS) - nSeconds) / 60) % 60;
	strSimulationTime.Format ("%5d:%02d.%03d", nMinutes, nSeconds, nMilliseconds);
	pCmdUI->SetText(strSimulationTime);
	pCmdUI->Enable(true);
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Add underlines to the hyperlinks
	DWORD dwRemove=0L, dwAdd=0L;
	dwAdd = CHyperLink::StyleUnderline;
	m_linkDynaMechs.ModifyLinkStyle(dwRemove, dwAdd);
	m_linkHyperLinkClass.ModifyLinkStyle(dwRemove, dwAdd);
	m_linkRobotBuilderWebsite.ModifyLinkStyle(dwRemove, dwAdd);
	m_linkBugEmail.ModifyLinkStyle(dwRemove, dwAdd);

	// Specify URL of some of the links
	m_linkHyperLinkClass.SetURL ("http://www.codeguru.com/controls/hyperlinkex.shtml");
	m_linkBugEmail.SetURL ("mailto:RobotBuilderBugs@ee.eng.ohio-state.edu");
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
