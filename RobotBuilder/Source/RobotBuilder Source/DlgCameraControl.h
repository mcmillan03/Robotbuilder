#if !defined(AFX_DLGCAMERACONTROL_H__7B674542_D2C5_48B8_A6E3_91C2250824DB__INCLUDED_)
#define AFX_DLGCAMERACONTROL_H__7B674542_D2C5_48B8_A6E3_91C2250824DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCameraControl.h : header file
//

#include "CameraData.h"

// Note on conditional compiliation:
//	When RobotModeler was originally written, this dialog did not
//	contain the option to maintain Inertial Z as the center of
//	interest. As this dialog seemed the most logical place to add
//	it for RobotBuilder, the required changes were made. Unfortunately,
//	RobotModeler neither has a configuration file, nor does it make
//	sense to even offer this option. Consequently, all of the details
//	of this option are conditionally compiled here. It would probably
//	have made more sense to split the code base for this dialog, but
//	as this was the only difference, it seemed reasonable. If future
//	differences are made, however, it might be wise to create unique
//	dialog boxes for each program.
//		-- LMF

#ifdef ROBOTBUILDER
	#include "dmvCFGData.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCameraControl dialog

class CDlgCameraControl : public CDialog
{
// Construction
public:
#ifdef ROBOTBUILDER
	CdmvCFGData* m_pCdmvCFGData;
	void SetCFGClassPointer(CdmvCFGData* pCdmvCFGData);
	BOOL m_bUseInertialZ;
#endif
	BOOL ValidateAndSaveData();
	BOOL GetInertialAxesAsCoi () const;
	void SetInertialAxesAsCoi (BOOL bSetInertialAxesAsCoi);
	void SetDataClassPointer (CCameraData* pCameraData);
	CDlgCameraControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCameraControl)
	enum { IDD = IDD_CAMERA_CONTROL };
	CButton	m_checkUseViewportFrame;
	CButton	m_checkSetInertialAxesAsCoi;
	CButton m_checkUseInertialZ;
	CEdit	m_editOffsetZ;
	CEdit	m_editOffsetY;
	CEdit	m_editOffsetX;
	CEdit	m_editViewAngleDeg;
	double	m_dViewAngleDeg;
	double	m_dOffsetX;
	double	m_dOffsetY;
	double	m_dOffsetZ;
	int		m_nControlType;
	BOOL	m_bSetInertialAxesAsCoi;
	BOOL	m_bUseViewportFrame;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCameraControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Enumerate the types for the radio buttons
	enum {CAMERA_CONTROL_RADIO_PAN, CAMERA_CONTROL_RADIO_EXAMINE};

	// Generated message map functions
	//{{AFX_MSG(CDlgCameraControl)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//afx_msg void OnRadioExamine();
	//afx_msg void OnRadioPan();
	afx_msg void OnCheckInertial();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CCameraData* m_pCameraData;
  float viewangleDeg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCAMERACONTROL_H__7B674542_D2C5_48B8_A6E3_91C2250824DB__INCLUDED_)
