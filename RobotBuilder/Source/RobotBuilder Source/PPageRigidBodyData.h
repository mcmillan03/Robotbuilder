#if !defined(AFX_PPAGERIGIDBODYDATA_H__85567269_FF09_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PPAGERIGIDBODYDATA_H__85567269_FF09_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageRigidBodyData.h : header file
//

#include "dmvRigidBodyData.h"
#include "DlgContactPosition.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageRigidBodyData dialog

class CPPageRigidBodyData : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageRigidBodyData)

// Construction
public:
	CPPageRigidBodyData();
	~CPPageRigidBodyData();
	CdmvRigidBodyData* m_pCdmvRigidBodyData;

// Dialog Data
	//{{AFX_DATA(CPPageRigidBodyData)
	enum { IDD = IDD_RIGID_BODY_DATA };
	CListBox	m_listboxContacts;
	//}}AFX_DATA
	structRigidBodyInertialParameters m_strtRigidBodyInertialParameters;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageRigidBodyData)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EditContact ();	
	// Generated message map functions
	//{{AFX_MSG(CPPageRigidBodyData)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAddContact();
	afx_msg void OnButtonDeleteContact();
	afx_msg void OnButtonEditContact();
	afx_msg void OnDblclkListContacts();
	afx_msg LRESULT OnQuerySiblings(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void MakeInertialParametersReadOnly (BOOL bEnableReadOnly);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGERIGIDBODYDATA_H__85567269_FF09_11D3_A7DF_0000E8978554__INCLUDED_)
