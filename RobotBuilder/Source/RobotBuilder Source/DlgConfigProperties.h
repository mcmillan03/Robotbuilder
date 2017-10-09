#if !defined(AFX_DLGCONFIGPROPERTIES_H__66B82E5F_93DE_4F40_AE6B_E2FAD6586205__INCLUDED_)
#define AFX_DLGCONFIGPROPERTIES_H__66B82E5F_93DE_4F40_AE6B_E2FAD6586205__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConfigProperties.h : header file
//

#include "dmvCFGData.h"
#include "CameraData.h"
#include "DlgConfigAxes.h"
#include "DlgConfigBackground.h"
#include "DlgConfigSimulation.h"
#include "DlgConfigFiles.h"
#include "DlgConfigCamera.h"
#include "WTKView.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigProperties dialog

class CDlgConfigProperties : public CDialog
{
// Construction
public:
	void SetViewpointPointer(CWTKView* pWTKView);
	void SetCameraDataClass (CCameraData* pCCameraData);
	BOOL ValidateAndSaveData();
	BOOL ValidateData();
	CDlgConfigProperties(CWnd* pParent = NULL);   // standard constructor
	void SetDataClass(CdmvCFGData *pCdmvCFGData);
	void SetSystemDataClass(CdmvSystemData *pCdmvSystemData);
private:
// Dialog Data
	//{{AFX_DATA(CDlgConfigProperties)
	enum { IDD = IDD_SIMULATION_DATA };
	CTabCtrl	m_tabctrlTabMain;
	CDlgConfigAxes			m_dlgConfigAxes;
	CDlgConfigBackground	m_dlgConfigBackground;
	CDlgConfigFiles			m_dlgConfigFiles;
	CDlgConfigSimulation	m_dlgConfigSimulation;
	CDlgConfigCamera		m_dlgConfigCamera;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConfigProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	enum {TAB_SIMULATION, TAB_AXES, TAB_FILES, TAB_CAMERA, TAB_BACKGROUND};
	// Generated message map functions
	//{{AFX_MSG(CDlgConfigProperties)
	afx_msg void OnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingTabMain(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonHelp();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONFIGPROPERTIES_H__66B82E5F_93DE_4F40_AE6B_E2FAD6586205__INCLUDED_)
