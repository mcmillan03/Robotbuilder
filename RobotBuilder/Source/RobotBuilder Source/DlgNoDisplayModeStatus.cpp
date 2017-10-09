// DlgNoDisplayModeStatus.cpp : implementation file
//

#include "stdafx.h"
#include "DMViewer.h"
#include "DlgNoDisplayModeStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNoDisplayModeStatus dialog


CDlgNoDisplayModeStatus::CDlgNoDisplayModeStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNoDisplayModeStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNoDisplayModeStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgNoDisplayModeStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNoDisplayModeStatus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNoDisplayModeStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgNoDisplayModeStatus)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNoDisplayModeStatus message handlers
