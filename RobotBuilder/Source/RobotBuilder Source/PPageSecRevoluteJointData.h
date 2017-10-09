#if !defined(AFX_PPAGESECREVOLUTEJOINTDATA_H__07276755_89F2_4A46_9F27_15E71764978F__INCLUDED_)
#define AFX_PPAGESECREVOLUTEJOINTDATA_H__07276755_89F2_4A46_9F27_15E71764978F__INCLUDED_

#include "dmvSecRevJntData.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageSecRevoluteJointData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPPageSecRevoluteJointData dialog

class CPPageSecRevoluteJointData : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageSecRevoluteJointData)

// Construction
public:
	CdmvSecRevJntData* m_pCdmvSecRevJntData;
	CPPageSecRevoluteJointData();
	~CPPageSecRevoluteJointData();

// Dialog Data
	//{{AFX_DATA(CPPageSecRevoluteJointData)
	enum { IDD = IDD_SEC_REVOLUTE_JOINT_DATA };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageSecRevoluteJointData)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	structSecondaryRevoluteJointData m_strtSecondaryRevoluteJointData;
	// Generated message map functions
	//{{AFX_MSG(CPPageSecRevoluteJointData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGESECREVOLUTEJOINTDATA_H__07276755_89F2_4A46_9F27_15E71764978F__INCLUDED_)
