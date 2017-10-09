#if !defined(AFX_PPAGELINKDATA_H__03703C82_005E_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_PPAGELINKDATA_H__03703C82_005E_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageLinkData.h : header file
//

#include "PPageLinkBase.h"
#include "dmvLinkData.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageLinkData dialog

class CPPageLinkData : public CPPageLinkBase
{
	DECLARE_DYNCREATE(CPPageLinkData)

// Construction
public:
	CPPageLinkData();
	~CPPageLinkData();
	CdmvLinkData* m_pCdmvLinkData;
// Dialog Data
	//{{AFX_DATA(CPPageLinkData)
	enum { IDD = IDD_LINK_DATA_PP };
	float	m_fJointFriction;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageLinkData)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageLinkData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGELINKDATA_H__03703C82_005E_11D4_A7DF_0000E8978554__INCLUDED_)
