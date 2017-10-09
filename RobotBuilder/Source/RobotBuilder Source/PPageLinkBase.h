#if !defined(AFX_PPAGELINKBASE_H__EAB9126A_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PPAGELINKBASE_H__EAB9126A_FEA6_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageLinkBase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageLinkBase dialog

class CPPageLinkBase : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageLinkBase)

// Construction
public:
	CPPageLinkBase ();
	CPPageLinkBase(UINT nIDTemplate);
	~CPPageLinkBase();

// Dialog Data
	//{{AFX_DATA(CPPageLinkBase)
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageLinkBase)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageLinkBase)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGELINKBASE_H__EAB9126A_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
