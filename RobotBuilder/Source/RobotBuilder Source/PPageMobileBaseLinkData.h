#if !defined(AFX_PPAGEMOBILEBASELINKDATA_H__E3DE82C4_FFCF_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PPAGEMOBILEBASELINKDATA_H__E3DE82C4_FFCF_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageMobileBaseLinkData.h : header file
//

#include "PPageLinkBase.h"
#include "dmvMobileBaseLinkData.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageMobileBaseLinkData dialog

class CPPageMobileBaseLinkData : public CPPageLinkBase
{
	DECLARE_DYNCREATE(CPPageMobileBaseLinkData)

// Construction
public:
	CPPageMobileBaseLinkData();
	~CPPageMobileBaseLinkData();

// Dialog Data
	//{{AFX_DATA(CPPageMobileBaseLinkData)
	enum { IDD = IDD_MOBILE_BASE_LINK_DATA };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA
	structMobileBaseLinkState m_strtMobileBaseLinkState;
	CdmvMobileBaseLinkData* m_pCdmvMobileBaseLinkData;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageMobileBaseLinkData)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageMobileBaseLinkData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEMOBILEBASELINKDATA_H__E3DE82C4_FFCF_11D3_A7DF_0000E8978554__INCLUDED_)
