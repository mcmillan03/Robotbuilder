// DlgContactPosition.cpp : implementation file
//

#include "stdafx.h"
#include "DMViewer.h"
#include "DlgContactPosition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgContactPosition dialog


CDlgContactPosition::CDlgContactPosition(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgContactPosition::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgContactPosition)
	m_fPositionX = 0.0f;
	m_fPositionY = 0.0f;
	m_fPositionZ = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgContactPosition::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgContactPosition)
	DDX_Text(pDX, IDC_EDIT_POS_X, m_fPositionX);
	DDX_Text(pDX, IDC_EDIT_POS_Y, m_fPositionY);
	DDX_Text(pDX, IDC_EDIT_POS_Z, m_fPositionZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgContactPosition, CDialog)
	//{{AFX_MSG_MAP(CDlgContactPosition)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgContactPosition message handlers
