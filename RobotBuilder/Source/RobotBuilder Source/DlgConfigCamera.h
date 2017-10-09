#if !defined(AFX_DLGCONFIGCAMERA_H__7A925028_91D3_434F_B34B_4E9F942B23F7__INCLUDED_)
#define AFX_DLGCONFIGCAMERA_H__7A925028_91D3_434F_B34B_4E9F942B23F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConfigCamera.h : header file
//

#include "CameraData.h"
#include "dmvCFGData.h"
#include "dmvSystemData.h"
#include "dmvArticulationData.h"
#include "WTKView.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigCamera dialog

class CDlgConfigCamera : public CDialog
{
// Construction
public:
	void SetViewpointPointer(CWTKView *pWTKView);
	void SetDataClass(CdmvCFGData* pCdmvCFGData);
	void SetCameraDataClass (CCameraData* pCCameraData);
	void SetSystemDataClass (CdmvSystemData* pCdmvSystemData);
	BOOL ValidateData();
	BOOL ValidateAndSaveData();
	CDlgConfigCamera(CWnd* pParent = NULL);   // standard constructor

protected:
	WTp3 m_WTp3;
	WTq m_WTq;
	CWTKView* m_pWTKView;
// Dialog Data
	//{{AFX_DATA(CDlgConfigCamera)
	enum { IDD = IDD_CONFIG_CAMERA };
	double m_dOffsetZ;
	double m_dOffsetY;
	double m_dOffsetX;
	BOOL m_bInertialAxesAsCoi;
	CString m_strCenterOfInterest;
	//}}AFX_DATA
	CdmvCFGData* m_pCdmvCFGData;
	CCameraData* m_pCCameraData;
	CdmvSystemData* m_pCdmvSystemData;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConfigCamera)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation


	// Generated message map functions
	//{{AFX_MSG(CDlgConfigCamera)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSetCamera();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONFIGCAMERA_H__7A925028_91D3_434F_B34B_4E9F942B23F7__INCLUDED_)
