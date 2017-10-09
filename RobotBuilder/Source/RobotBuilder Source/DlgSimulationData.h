#if !defined(AFX_DLGSIMULATIONDATA_H__2B1F6323_1D30_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_DLGSIMULATIONDATA_H__2B1F6323_1D30_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSimulationData.h : header file
//

#include "dmvCFGData.h"
#include "CameraData.h"
#include "dmvArticulationData.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSimulationData dialog

class CDlgSimulationData : public CDialog
{
private:
	/// Symbolic names for the integrator type values in the dialog
	enum {INTEGRATOR_DLG_PLACEMENT, INTEGRATOR_DLG_EULER, INTEGRATOR_DLG_RK4, INTEGRATOR_DLG_RK45};

// Construction
public:
	void SetDataClass (CdmvCFGData* pCdmvCFGData);
	void SetCameraDataClass (CCameraData* pCCameraData);
	void SetSystemDataClass (CdmvSystemData* pCdmvSystemData);
	CDlgSimulationData(CWnd* pParent = NULL);   // standard constructor
private:
// Dialog Data
	//{{AFX_DATA(CDlgSimulationData)
	enum { IDD = IDD_SIMULATTION_DATA };
	CEdit	m_editRK45MinimumStepSize;
	CEdit	m_editRK45Epsilon;
	CEdit	m_editRK4StepSize;
	CEdit	m_editEulerStepSize;
	int		m_nDisplayRate;
	CString	m_strEnvironmentFile;
	double	m_dStepSize;
	BOOL	m_bRealTime;
	double	m_dEulerStepSize;
	double	m_dRK4StepSize;
	double	m_dRK45Epsilon;
	double	m_dRK45MinimumStepSize;
	int		m_nIntegratorType;
	double	m_dInertialAxesLength;
	int		m_nInertialAxesWidth;
	double	m_dLinkAxesLength;
	int		m_nLinkAxesWidth;
	CString	m_strArticulationFile;
	CString	m_strControlFile;
	BOOL	m_bInertialAxesAsCoi;
	BOOL	m_bUseInertialZ;
	CString	m_strCenterOfInterest;
	double	m_dCoiOffsetX;
	double	m_dCoiOffsetY;
	double	m_dCoiOffsetZ;
	//}}AFX_DATA
	CdmvCFGData* m_pCdmvCFGData;
	CCameraData* m_pCCameraData;
	CdmvSystemData* m_pCdmvSystemData;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSimulationData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COLORREF m_crBackgroundColor;

	CString GetCoiName();
	// Generated message map functions
	//{{AFX_MSG(CDlgSimulationData)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioEuler();
	afx_msg void OnRadioPlacement();
	afx_msg void OnRadioRk4();
	afx_msg void OnRadioRk45();
	virtual void OnOK();
	afx_msg void OnItemchangingListArtAndControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnButtonChooseColor();
	afx_msg void OnButtonLoadCurrentCoi();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSIMULATIONDATA_H__2B1F6323_1D30_11D4_A7DF_0000E8978554__INCLUDED_)
