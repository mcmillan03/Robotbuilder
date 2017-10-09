#if !defined(AFX_PSHEETSECPRISMATICJOINT_H__EEDB2FFF_2B1E_492D_AB47_900F11B5AC88__INCLUDED_)
#define AFX_PSHEETSECPRISMATICJOINT_H__EEDB2FFF_2B1E_492D_AB47_900F11B5AC88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PSheetSecPrismaticJoint.h : header file
//

#include "PSheetLinkBase.h"
#include "PPageSecJointData.h"	// Added by ClassView
#include "PPageObjectData.h"
#include "PPageSecPrismaticJointData.h"
#include "dmvSecPrisJntData.h"
#include "dmvArticulationData.h"

/////////////////////////////////////////////////////////////////////////////
// CPSheetSecPrismaticJoint

class CPSheetSecPrismaticJoint : public CPSheetLinkBase
{
	DECLARE_DYNAMIC(CPSheetSecPrismaticJoint)

// Construction
public:
	CPSheetSecPrismaticJoint(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPSheetSecPrismaticJoint(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CdmvSecPrisJntData* m_pCdmvSecPrisJntData;
	CdmvArticulationData* m_pCdmvArticulationData;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSheetSecPrismaticJoint)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSheetSecPrismaticJoint();

	// Generated message map functions
protected:
	CPPageSecJointData m_ppageSecJointData;
	CPPageObjectData m_ppageObjectData;
	CPPageSecPrismaticJointData m_ppageSecPrismaticJointData;
	

	void BuildPropertySheet ();
	//{{AFX_MSG(CPSheetSecPrismaticJoint)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSHEETSECPRISMATICJOINT_H__EEDB2FFF_2B1E_492D_AB47_900F11B5AC88__INCLUDED_)
