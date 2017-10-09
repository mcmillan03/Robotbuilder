#if !defined(AFX_PPAGESECSPHERICALJOINTDATA_H__A42E7136_3127_4AE9_BEF6_B97DE34ED8AD__INCLUDED_)
#define AFX_PPAGESECSPHERICALJOINTDATA_H__A42E7136_3127_4AE9_BEF6_B97DE34ED8AD__INCLUDED_

#include "dmvSecSpherJntData.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageSecSphericalJointData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageSecSphericalJointData dialog

class CPPageSecSphericalJointData : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageSecSphericalJointData)

// Construction
public:
	CdmvSecSpherJntData* m_pCdmvSecSpherJntData;
	CPPageSecSphericalJointData();
	~CPPageSecSphericalJointData();

// Dialog Data
	//{{AFX_DATA(CPPageSecSphericalJointData)
	enum { IDD = IDD_SEC_SPHERICAL_JOINT_DATA };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageSecSphericalJointData)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	structSecondarySphericalJointData m_strtSecondarySphericalJointData;
	// Generated message map functions
	//{{AFX_MSG(CPPageSecSphericalJointData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGESECSPHERICALJOINTDATA_H__A42E7136_3127_4AE9_BEF6_B97DE34ED8AD__INCLUDED_)
