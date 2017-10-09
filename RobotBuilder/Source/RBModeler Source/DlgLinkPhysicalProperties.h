#if !defined(AFX_DLGLINKPHYSICALPROPERTIES_H__966847FD_901F_4DE9_9964_BD60C631460A__INCLUDED_)
#define AFX_DLGLINKPHYSICALPROPERTIES_H__966847FD_901F_4DE9_9964_BD60C631460A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLinkPhysicalProperties.h : header file
//

class CModel;

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkPhysicalProperties dialog

class CDlgLinkPhysicalProperties : public CDialog
{
// Construction
public:
	BOOL GetUseUserSuppliedDataForPhysicalData () const;
	void SetModel (const CModel *pModel);
	CDlgLinkPhysicalProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLinkPhysicalProperties)
	enum { IDD = IDD_LINK_PHYSICAL_PROPERTIES };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLinkPhysicalProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	double	m_dInertiaTensor[3][3];
	double	m_dCenterOfGravityX;
	double	m_dCenterOfGravityY;
	double	m_dCenterOfGravityZ;
	double	m_dTotalMass;
	BOOL	m_bAutoCalculatedData;

protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgLinkPhysicalProperties)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLINKPHYSICALPROPERTIES_H__966847FD_901F_4DE9_9964_BD60C631460A__INCLUDED_)
