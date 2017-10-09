#if !defined(AFX_DLGREVDCMOTORDATA_H__3EC42AA2_F828_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DLGREVDCMOTORDATA_H__3EC42AA2_F828_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRevDCMotorData.h : header file
//

#include "dmvRevDCMotorData.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgRevDCMotorData dialog

class CDlgRevDCMotorData : public CDialog
{
// Construction
public:
	void OnCancel ();
	void SaveDialogData ();
	CDlgRevDCMotorData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRevDCMotorData)
	enum { IDD = IDD_REV_DC_MOTOR_DATA };
	//}}AFX_DATA
	structRevDCMotorParameters m_strtRevDCMotorParameters;
	CdmvRevDCMotorData* m_pCdmvRevDCMotorData;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRevDCMotorData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRevDCMotorData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREVDCMOTORDATA_H__3EC42AA2_F828_11D3_A7DF_0000E8978554__INCLUDED_)
