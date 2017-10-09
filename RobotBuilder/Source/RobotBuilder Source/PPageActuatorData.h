#if !defined(AFX_PPAGEACTUATORDATA_H__85567267_FF09_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PPAGEACTUATORDATA_H__85567267_FF09_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageActuatorData.h : header file
//

typedef enum {CB_NO_MOTOR, CB_REV_DC_MOTOR} CBActuatorTypes;



#include "DlgLinkData.h"
#include "DlgRevDCMotorData.h"
#include "dmvRevoluteLinkData.h"
#include "PPageLinkBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageActuatorData dialog


class CPPageActuatorData : public CPPageLinkBase
{
	DECLARE_DYNCREATE(CPPageActuatorData)

// Construction
public:
	CPPageActuatorData();
	~CPPageActuatorData();
	BOOL UpdateData (BOOL bSaveAndValidate);

// Dialog Data
	//{{AFX_DATA(CPPageActuatorData)
	enum { IDD = IDD_ACTUATOR_DATA };
	CComboBox	m_comboActuatorType;
	CStatic	m_staticActuatorTypeDataRect;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageActuatorData)
	public:
	virtual void OnOK();
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CdmvRevoluteLinkData* m_pCdmvRevoluteLinkData;

protected:
	CDlgRevDCMotorData m_dlgRevDCMotorData;
	CDlgLinkData m_dlgLinkData;
	// Generated message map functions
	//{{AFX_MSG(CPPageActuatorData)
	afx_msg void OnSelchangeComboActuatorType();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEACTUATORDATA_H__85567267_FF09_11D3_A7DF_0000E8978554__INCLUDED_)
