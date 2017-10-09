#if !defined(AFX_DLGENVIRONMENTDATA_H__860E6182_1B75_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_DLGENVIRONMENTDATA_H__860E6182_1B75_11D4_A7DF_0000E8978554__INCLUDED_

#include "dmvEnvironmentData.h"	// Added by ClassView
#include "dmvTreadmillData.h"
#include "dmvTerrainData.h"
#include "DlgEnvTreadmillData.h"
#include "DlgEnvTerrainData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEnvironmentData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvironmentData dialog

class CDlgEnvironmentData : public CDialog
{
// Construction
public:
	void SetDataClassPointer (CdmvEnvironmentData** ppCdmvEnvironment);
	CDlgEnvironmentData(CWnd* pParent = NULL);   // standard constructor
	~CDlgEnvironmentData ();

// Dialog Data
	//{{AFX_DATA(CDlgEnvironmentData)
	enum { IDD = IDD_ENVIRONMENT_DATA };
	int		m_nEnvironmentType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEnvironmentData)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDlgEnvTreadmillData m_dlgTreadmill;
	CDlgEnvTerrainData m_dlgTerrain;
	structEnvironmentData m_strtEnvironmentData;
	CdmvEnvironmentData** m_ppCdmvEnvironmentData;
	CdmvTreadmillData* m_pCdmvTreadmillData;
	CdmvTerrainData* m_pCdmvTerrainData;
	// enumerate symbols for the radio box
	enum enumRBEnvironmentTypes {RB_TERRAIN, RB_TREADMILL};

	// Generated message map functions
	//{{AFX_MSG(CDlgEnvironmentData)
	virtual void OnOK();
	afx_msg void OnRadioTreadmill();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioTerrain();
	afx_msg void OnButtonEditDetails();
	afx_msg void OnButtonBrowse();
	virtual void OnCancel();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGENVIRONMENTDATA_H__860E6182_1B75_11D4_A7DF_0000E8978554__INCLUDED_)
