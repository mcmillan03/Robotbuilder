// DlgConfigCamera.cpp : implementation file
//

#include "stdafx.h"
#include "dmviewer.h"
#include "DlgConfigCamera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigCamera dialog


CDlgConfigCamera::CDlgConfigCamera(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfigCamera::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConfigCamera)
	m_strCenterOfInterest = _T("");
	m_dOffsetX = 0.0;
	m_dOffsetY = 0.0;
	m_dOffsetZ = 0.0;
	m_bInertialAxesAsCoi = FALSE;
	//}}AFX_DATA_INIT
	m_pCCameraData = NULL;
	m_pCdmvCFGData = NULL;
	m_pCdmvSystemData = NULL;
	m_pWTKView = NULL;
	m_WTq[0] = 0.0;
	m_WTq[1] = 0.0;
	m_WTq[2] = 0.0;
	m_WTq[3] = 0.0;
}


void CDlgConfigCamera::DoDataExchange(CDataExchange* pDX)
{
	// The GUI should have floats because double precision extends the numbers
	// much larger than is displayed in the edit controls.  Besides, it's not likely
	// the user needs that much precision
	float fOffsetX = (float) m_dOffsetX;
	float fOffsetY = (float) m_dOffsetY;
	float fOffsetZ = (float) m_dOffsetZ;
	
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConfigCamera)
	DDX_Text(pDX, IDC_EDIT_CENTER_OF_INTEREST, m_strCenterOfInterest);
	DDX_Text(pDX, IDC_EDIT_COI_OFFSET_X, fOffsetX);
	DDX_Text(pDX, IDC_EDIT_COI_OFFSET_Y, fOffsetY);
	DDX_Text(pDX, IDC_EDIT_COI_OFFSET_Z, fOffsetZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConfigCamera, CDialog)
	//{{AFX_MSG_MAP(CDlgConfigCamera)
	ON_BN_CLICKED(IDC_BUTTON_SET_CAMERA, OnButtonSetCamera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigCamera message handlers

BOOL CDlgConfigCamera::ValidateAndSaveData()
{
	if(ValidateData())
	{
		m_pCdmvCFGData->SetCenterOfInterestName(m_strCenterOfInterest);
		m_pCdmvCFGData->SetCoiOffset(m_dOffsetX, m_dOffsetY, m_dOffsetZ);

		// Load the offsets into the camera data class
		WTp3 wtp3Offset;
		wtp3Offset[X] = m_dOffsetX ;
		wtp3Offset[Y] = m_dOffsetY;
		wtp3Offset[Z] = m_dOffsetZ;
		m_pCCameraData->SetCenterOfInterestOffset(wtp3Offset);
		m_pCdmvCFGData->SetOrientationQuaternion(m_WTq);
		m_pCdmvCFGData->SetOrientationPosition(m_WTp3);
		
		return TRUE;
	}
	else
	{	// Validation failed
		return FALSE;
	}
}

BOOL CDlgConfigCamera::ValidateData()
{
	// Is there anything to validate???
	return TRUE;
}

void CDlgConfigCamera::SetCameraDataClass(CCameraData *pCCameraData)
{
	ASSERT (pCCameraData);

	m_pCCameraData = pCCameraData;
}

BOOL CDlgConfigCamera::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make sure the data classes have been set
	ASSERT (m_pCCameraData);
	ASSERT (m_pCdmvCFGData);
	ASSERT (m_pCdmvSystemData);
	ASSERT (m_pWTKView);

	m_bInertialAxesAsCoi = m_pCdmvCFGData->GetInertialAxesAsCoi();
	m_strCenterOfInterest = m_pCdmvCFGData->GetCenterOfInterestName();
	m_pCdmvCFGData->GetCoiOffset(&m_dOffsetX, &m_dOffsetY, &m_dOffsetZ);
	m_pCdmvCFGData->GetOrientation(m_WTq);
	m_pCdmvCFGData->GetPosition(m_WTp3);
	
	BOOL bSuccess;
	bSuccess = UpdateData (FALSE);
	ASSERT (bSuccess);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgConfigCamera::SetDataClass(CdmvCFGData *pCdmvCFGData)
{
	ASSERT (pCdmvCFGData);

	m_pCdmvCFGData = pCdmvCFGData;
}

void CDlgConfigCamera::SetSystemDataClass(CdmvSystemData* pCdmvSystemData)
{
	ASSERT (pCdmvSystemData);
	
	m_pCdmvSystemData = pCdmvSystemData;
}

void CDlgConfigCamera::OnButtonSetCamera() 
{
	// get the current offset
	WTp3 wtp3Offset;
	m_pCCameraData->GetCenterOfInterestOffset (wtp3Offset);
	m_dOffsetX = wtp3Offset[X];
	m_dOffsetY = wtp3Offset[Y];
	m_dOffsetZ = wtp3Offset[Z];

	// get the current center of interest
	m_strCenterOfInterest = ((CdmvArticulationData*) m_pCdmvSystemData)->GetCenterOfInterestName();

	// get the current viewpoint orientation
	m_pWTKView->m_wndWTK.GetViewpointOrientation(m_WTq);
	m_pWTKView->m_wndWTK.GetViewpointPosition(m_WTp3);

	// update the dialog
	UpdateData(FALSE);
}

void CDlgConfigCamera::SetViewpointPointer(CWTKView *pWTKView)
{
	m_pWTKView = pWTKView;
}