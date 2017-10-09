#if !defined(AFX_PPAGESPHERICALLINKDATA_H__5AFE3CE4_17CE_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_PPAGESPHERICALLINKDATA_H__5AFE3CE4_17CE_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageSphericalLinkData.h : header file
//

#include "PPageLinkBase.h"
#include "dmvSphericalLinkData.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageSphericalLinkData dialog

class CPPageSphericalLinkData : public CPPageLinkBase
{
	DECLARE_DYNCREATE(CPPageSphericalLinkData)

// Construction
public:
	CdmvSphericalLinkData* m_pCdmvSphericalLinkData;
	CPPageSphericalLinkData();
	~CPPageSphericalLinkData();

// Dialog Data
	//{{AFX_DATA(CPPageSphericalLinkData)
	enum { IDD = IDD_SPHERICAL_LINK_DATA };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageSphericalLinkData)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	structSphericalLinkJointLimits m_strtSphericalLinkJointLimits;
	structSphericalLinkState m_strtSphericalLinkState;
	CartesianVector m_cvJointOffsetPosition;
	// Generated message map functions
	//{{AFX_MSG(CPPageSphericalLinkData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGESPHERICALLINKDATA_H__5AFE3CE4_17CE_11D4_A7DF_0000E8978554__INCLUDED_)
