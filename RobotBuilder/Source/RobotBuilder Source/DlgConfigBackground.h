#if !defined(AFX_DLGCONFIGBACKGROUND_H__7DEAFCA1_12F6_4775_99C2_92A2CAB41837__INCLUDED_)
#define AFX_DLGCONFIGBACKGROUND_H__7DEAFCA1_12F6_4775_99C2_92A2CAB41837__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgConfigBackground.h : header file
//

#include "dmvCFGData.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgConfigBackground dialog

class CDlgConfigBackground : public CDialog
{
// Construction
public:
	BOOL ValidateData();
	BOOL ValidateAndSaveData();
	CDlgConfigBackground(CWnd* pParent = NULL);   // standard constructor
	void SetDataClass (CdmvCFGData* pCdmvCFGData);

private:	
// Dialog Data
	//{{AFX_DATA(CDlgConfigBackground)
	enum { IDD = IDD_CONFIG_BACKGROUND };
	//}}AFX_DATA
	CdmvCFGData* m_pCdmvCFGData;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgConfigBackground)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COLORREF m_crBackgroundColor;
	// Generated message map functions
	//{{AFX_MSG(CDlgConfigBackground)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonChooseColor();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONFIGBACKGROUND_H__7DEAFCA1_12F6_4775_99C2_92A2CAB41837__INCLUDED_)
