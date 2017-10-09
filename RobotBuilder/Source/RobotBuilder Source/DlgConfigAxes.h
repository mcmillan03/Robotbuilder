#if !defined(AFX_DLGCONFIGAXES_H__E0CD4554_7E0E_4574_86D7_3CDE29C9B84B__INCLUDED_)
#define AFX_DLGCONFIGAXES_H__E0CD4554_7E0E_4574_86D7_3CDE29C9B84B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConfigAxes.h : header file
//

#include "dmvCFGData.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigAxes dialog

class CDlgConfigAxes : public CDialog
{
// Construction
public:
	BOOL ValidateData();
	BOOL ValidateAndSaveData();
	CDlgConfigAxes(CWnd* pParent = NULL);   // standard constructor
	void SetDataClass (CdmvCFGData* pCdmvCFGData);
private:
// Dialog Data
	//{{AFX_DATA(CDlgConfigAxes)
	enum { IDD = IDD_CONFIG_AXES };
	double	m_dInertialAxesLength;
	int		m_nInertialAxesWidth;
	double	m_dLinkAxesLength;
	int		m_nLinkAxesWidth;
	//}}AFX_DATA
	CdmvCFGData* m_pCdmvCFGData;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConfigAxes)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgConfigAxes)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONFIGAXES_H__E0CD4554_7E0E_4574_86D7_3CDE29C9B84B__INCLUDED_)
