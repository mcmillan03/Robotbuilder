#if !defined(AFX_PPAGEZSCREWTXLINKDATA_H__EAB91264_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PPAGEZSCREWTXLINKDATA_H__EAB91264_FEA6_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageZScrewTxLinkData.h : header file
//

#include "PPageLinkBase.h"
#include "dmvZScrewTxLinkData.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageZScrewTxLinkData dialog

class CPPageZScrewTxLinkData : public CPPageLinkBase
{
	DECLARE_DYNCREATE(CPPageZScrewTxLinkData)

// Construction
public:
	CPPageZScrewTxLinkData();
	~CPPageZScrewTxLinkData();
	CdmvZScrewTxLinkData* m_pCdmvZScrewTxLinkData;

// Dialog Data
	//{{AFX_DATA(CPPageZScrewTxLinkData)
	enum { IDD = IDD_ZSCREW_TX_LINK_DATA };
	float	m_fZScrewTxD;
	float	m_fZScrewTxTheta;
	//}}AFX_DATA
protected:
	structZScrewTxLinkParameters m_strtZScrewTxLinkParameters;
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageZScrewTxLinkData)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageZScrewTxLinkData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEZSCREWTXLINKDATA_H__EAB91264_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
