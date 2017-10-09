#if !defined(AFX_PPAGESECPRISMATICJOINTDATA_H__451043BE_EECA_4ACD_8047_267411E21C9D__INCLUDED_)
#define AFX_PPAGESECPRISMATICJOINTDATA_H__451043BE_EECA_4ACD_8047_267411E21C9D__INCLUDED_

#include "dmvSecPrisJntData.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageSecPrismaticJointData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageSecPrismaticJointData dialog

class CPPageSecPrismaticJointData : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageSecPrismaticJointData)

// Construction
public:
	CdmvSecPrisJntData* m_pCdmvSecPrisJntData;
	CPPageSecPrismaticJointData();
	~CPPageSecPrismaticJointData();

// Dialog Data
	//{{AFX_DATA(CPPageSecPrismaticJointData)
	enum { IDD = IDD_SEC_PRISMATIC_JOINT_DATA };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageSecPrismaticJointData)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	structSecondaryPrismaticJointData m_strtSecondaryPrismaticJointData;
	// Generated message map functions
	//{{AFX_MSG(CPPageSecPrismaticJointData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGESECPRISMATICJOINTDATA_H__451043BE_EECA_4ACD_8047_267411E21C9D__INCLUDED_)
