#if !defined(AFX_PPAGEARTICULATIONDATA_H__EAB91270_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_PPAGEARTICULATIONDATA_H__EAB91270_FEA6_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageArticulationData.h : header file
//

#include "dmvArticulationData.h"
#include "PPageLinkBase.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageArticulationData dialog

class CPPageArticulationData : public CPPageLinkBase
{
	DECLARE_DYNCREATE(CPPageArticulationData)

// Construction
public:
	CdmvArticulationData* m_pCdmvArticulationData;
	CPPageArticulationData();
	~CPPageArticulationData();

// Dialog Data
	//{{AFX_DATA(CPPageArticulationData)
	enum { IDD = IDD_ARTICULATION_DATA };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA
	CartesianVector m_cvPosition;
	Quaternion m_qOrientation;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageArticulationData)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPPageArticulationData)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEARTICULATIONDATA_H__EAB91270_FEA6_11D3_A7DF_0000E8978554__INCLUDED_)
