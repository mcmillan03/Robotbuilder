#if !defined(AFX_PPAGEBLOCK_H__33CE61C3_C512_42E9_BDAB_6BABF0851279__INCLUDED_)
#define AFX_PPAGEBLOCK_H__33CE61C3_C512_42E9_BDAB_6BABF0851279__INCLUDED_

#include "PrimitiveBlock.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PPageBlock.h : header file
//

#include "PrimitiveBlock.h"
#include "RBModelerRBMGraphicView.h"

/////////////////////////////////////////////////////////////////////////////
// CPPageBlock dialog

class CPPageBlock : public CPropertyPage
{
	DECLARE_DYNCREATE(CPPageBlock)

// Construction
public:
	CPrimitiveBlock* m_pPrimitiveBlock;
	CPPageBlock();
	~CPPageBlock();

// Dialog Data
	//{{AFX_DATA(CPPageBlock)
	enum { IDD = IDD_PRIMITIVE_BLOCK };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPPageBlock)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	structPrimitiveBlockData m_strtPrimitiveBlockData;
	// Generated message map functions
	//{{AFX_MSG(CPPageBlock)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckBothSides();
	afx_msg void OnChangeEditXlength();
	afx_msg void OnChangeEditYlength();
	afx_msg void OnChangeEditZlength();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPAGEBLOCK_H__33CE61C3_C512_42E9_BDAB_6BABF0851279__INCLUDED_)
