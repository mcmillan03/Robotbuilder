#if !defined(AFX_PPAGEMDHLINKDATA_H__E3DE82C2_FFCF_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PPAGEMDHLINKDATA_H__E3DE82C2_FFCF_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageMDHLinkData.h : header file
//

#include "dmvMDHLinkData.h"
#include "PPageLinkBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageMDHLinkData dialog

class CPPageMDHLinkData : public CPPageLinkBase
{
	DECLARE_DYNCREATE(CPPageMDHLinkData)

// Construction
public:
	CPPageMDHLinkData();
	~CPPageMDHLinkData();

// Dialog Data
	//{{AFX_DATA(CPPageMDHLinkData)
	enum { IDD = IDD_MDH_LINK_DATA };
	//}}AFX_DATA
	structMDHLinkJointLimits m_strtMDHLinkJointLimits;
	Float m_fInitialJointVelocity;
	structMDHParameters m_strtMDHParameters;
	CdmvMDHLinkData* m_pCdmvMDHLinkData;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageMDHLinkData)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageMDHLinkData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEMDHLINKDATA_H__E3DE82C2_FFCF_11D3_A7DF_0000E8978554__INCLUDED_)
