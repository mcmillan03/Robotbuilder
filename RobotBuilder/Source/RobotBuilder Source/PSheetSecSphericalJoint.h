#if !defined(AFX_PSHEETSECSPHERICALJOINT_H__A28CDAC4_30DE_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_PSHEETSECSPHERICALJOINT_H__A28CDAC4_30DE_11D4_A7DF_0000E8978554__INCLUDED_

#include "PSheetLinkBase.h"
#include "PPageSecJointData.h"	// Added by ClassView
#include "PPageObjectData.h"
#include "PPageSecSphericalJointData.h"
#include "dmvSecSpherJntData.h"
#include "dmvArticulationData.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetSecSphericalJoint.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPSheetSecSphericalJoint

class CPSheetSecSphericalJoint : public CPSheetLinkBase
{
	DECLARE_DYNAMIC(CPSheetSecSphericalJoint)

// Construction
public:
	CPSheetSecSphericalJoint(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetSecSphericalJoint(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetSecSphericalJoint)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	CdmvSecSpherJntData* m_pCdmvSecSpherJntData;
	CdmvArticulationData* m_pCdmvArticulationData;
	virtual ~CPSheetSecSphericalJoint();

	// Generated message map functions
protected:
	CPPageSecJointData m_ppageSecJointData;
	CPPageObjectData m_ppageObjectData;
	CPPageSecSphericalJointData m_ppageSecSphericalJointData;
		

	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetSecSphericalJoint)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETSECSPHERICALJOINT_H__A28CDAC4_30DE_11D4_A7DF_0000E8978554__INCLUDED_)
