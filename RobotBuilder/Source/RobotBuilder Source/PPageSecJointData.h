#if !defined(AFX_PPAGESECJOINTDATA_H__A28CDAC2_30DE_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_PPAGESECJOINTDATA_H__A28CDAC2_30DE_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageSecJointData.h : header file
//

#include "dmvSecJointData.h"
#include "dmvArticulationData.h"


enum {CB_SOFT_SEC_JOINT, CB_HARD_SEC_JOINT};
enum {CB_NONE, CB_BAUMGARTE, CB_SPRING_DAMPER};

/////////////////////////////////////////////////////////////////////////////
// CPPageSecJointData dialog

class CPPageSecJointData : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageSecJointData)

// Construction
public:
	CdmvSecJointData* m_pCdmvSecJointData;
	CdmvArticulationData* m_pCdmvArticulationData;
	CPPageSecJointData();
	~CPPageSecJointData();

// Dialog Data
	//{{AFX_DATA(CPPageSecJointData)
	enum { IDD = IDD_SECONDARY_JOINT_DATA };
	CComboBox	m_comboStabilization;
	CComboBox	m_comboLinkB;
	CComboBox	m_comboLinkA;
	int		m_nLinkAIndex;
	int		m_nLinkBIndex;
	int		m_nStabilization;
	int		m_nJointType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageSecJointData)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int MapJointTypeToComboBox (int nSoftOrHard);
	int MapComboBoxToJointType (int nSoftOrHard);
	StabilizationType MapComboBoxToStabilization (int nCBStablization);
	int MapStabilizationToComboBox (StabilizationType nStabilization);
	structSecondaryJointParameters m_strtSecondaryJointParameters;

	// Generated message map functions
	//{{AFX_MSG(CPPageSecJointData)
	virtual BOOL OnInitDialog();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSelchangeComboJointType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGESECJOINTDATA_H__A28CDAC2_30DE_11D4_A7DF_0000E8978554__INCLUDED_)
