#if !defined(AFX_PSHEETSECREVOLUTEJOINT_H__943C8CC6_35B5_4C04_B85A_0A00C5C69C02__INCLUDED_)
#define AFX_PSHEETSECREVOLUTEJOINT_H__943C8CC6_35B5_4C04_B85A_0A00C5C69C02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetSecRevoluteJoint.h : header file
//
#include "PSheetLinkBase.h"
#include "PPageSecJointData.h"	// Added by ClassView
#include "PPageObjectData.h"
#include "PPageSecRevoluteJointData.h"
#include "dmvSecRevJntData.h"
#include "dmvArticulationData.h"
/////////////////////////////////////////////////////////////////////////////
// CPSheetSecRevoluteJoint

class CPSheetSecRevoluteJoint : public CPSheetLinkBase
{
	DECLARE_DYNAMIC(CPSheetSecRevoluteJoint)

// Construction
public:
	CPSheetSecRevoluteJoint(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetSecRevoluteJoint(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CdmvSecRevJntData* m_pCdmvSecRevJntData;
	CdmvArticulationData* m_pCdmvArticulationData;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetSecRevoluteJoint)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSheetSecRevoluteJoint();

	// Generated message map functions
protected:
	CPPageSecJointData m_ppageSecJointData;
	CPPageObjectData m_ppageObjectData;
	CPPageSecRevoluteJointData m_ppageSecRevoluteJointData;

	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetSecRevoluteJoint)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETSECREVOLUTEJOINT_H__943C8CC6_35B5_4C04_B85A_0A00C5C69C02__INCLUDED_)
