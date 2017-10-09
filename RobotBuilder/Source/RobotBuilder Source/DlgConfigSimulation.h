#if !defined(AFX_DLGCONFIGSIMULATION_H__AAAB8E13_F9FD_4059_8C43_32220A9E4D7C__INCLUDED_)
#define AFX_DLGCONFIGSIMULATION_H__AAAB8E13_F9FD_4059_8C43_32220A9E4D7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConfigSimulation.h : header file
//
#include "dmvCFGData.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigSimulation dialog

class CDlgConfigSimulation : public CDialog
{
private:
	/// Symbolic names for the integrator type values in the dialog
	enum {INTEGRATOR_DLG_PLACEMENT, INTEGRATOR_DLG_EULER, INTEGRATOR_DLG_RK4, INTEGRATOR_DLG_RK45};
// Construction
public:
	BOOL ValidateData();
	BOOL ValidateAndSaveData();
	CDlgConfigSimulation(CWnd* pParent = NULL);   // standard constructor
	void SetDataClass(CdmvCFGData *pCdmvCFGData);
private:
// Dialog Data
	//{{AFX_DATA(CDlgConfigSimulation)
	enum { IDD = IDD_CONFIG_SIMULATION };
	CEdit	m_editRK45MinimumStepSize;
	CEdit	m_editRK45Epsilon;
	CEdit	m_editRK4StepSize;
	CEdit	m_editEulerStepSize;
	int		m_nDisplayRate;
	double	m_dStepSize;
	BOOL	m_bRealTime;
	double	m_dEulerStepSize;
	double	m_dRK4StepSize;
	double	m_dRK45Epsilon;
	double	m_dRK45MinimumStepSize;
	int		m_nIntegratorType;
	//}}AFX_DATA
	CdmvCFGData* m_pCdmvCFGData;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConfigSimulation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConfigSimulation)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioEuler();
	afx_msg void OnRadioPlacement();
	afx_msg void OnRadioRk4();
	afx_msg void OnRadioRk45();
	afx_msg void OnItemchangingListArtAndControl(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONFIGSIMULATION_H__AAAB8E13_F9FD_4059_8C43_32220A9E4D7C__INCLUDED_)
