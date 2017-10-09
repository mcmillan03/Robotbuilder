#if !defined(AFX_DLGENVTERRAINDATA_H__A710B988_7A1B_4A9F_85F9_80F15EB5317E__INCLUDED_)
#define AFX_DLGENVTERRAINDATA_H__A710B988_7A1B_4A9F_85F9_80F15EB5317E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEnvTerrainData.h : header file
//

#include "dmvTerrainData.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEnvTerrainData dialog

class CDlgEnvTerrainData : public CDialog
{
	enum {RB_COVERING_COLOR, RB_COVERING_TEXTURE};
	
	// Construction
public:
	void GetFileName (CString &rstrTerrainFile, CString &rstrTerrainPath) const;
	void SetFilename (CString strTerrainFile, CString strTerrainPath);
	void SaveDialogData ();
	void SetDataClassPointer (CdmvTerrainData* pCdmvTerrainData);
	CDlgEnvTerrainData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgEnvTerrainData)
	enum { IDD = IDD_ENV_TERRAIN_DATA };
	CEdit	m_editTextureFile;
  CEdit m_editWireframeLnWidth;
  CEdit m_editWireframeElevation;
	CButton	m_buttonColorExample;
  CButton	m_buttonWireframeColorExample;
	CButton	m_buttonTextureBrowse;
	CButton	m_buttonChooseColor;
	CButton	m_buttonChooseWireframeColor;
	CButton	m_checkWireframeOverlay;
	CSpinButtonCtrl	m_spinYIndex;
	CSpinButtonCtrl	m_spinXIndex;
	//double	m_dGridResolution;
	double	m_dXGridResolution;
	double	m_dYGridResolution;
	int		m_nXDim;
	int		m_nYDim;
	double	m_dZValue;
	int		m_nXIndex;
	int		m_nYIndex;
	int		m_nCoveringType;
	CString	m_strTextureFile;
	double	m_dSizeY;
	double	m_dSizeX;
  double  m_dWireframeLnWidth;
  double  m_dWireframeElevation;
	BOOL	m_bWireframeOverlay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEnvTerrainData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgEnvTerrainData)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusEditZValue();
	afx_msg void OnDeltaposSpinYIndex(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinXIndex(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonApplyDepth();
	afx_msg void OnChangeEditXIndex();
	afx_msg void OnChangeEditYIndex();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnRadioColor();
	afx_msg void OnRadioTexture();
	afx_msg void OnButtonChooseColor();
	virtual void OnOK();
	afx_msg void OnButtonBrowse();
	afx_msg void OnKillfocusEditGridResolution();
	afx_msg void OnKillfocusEditXDim();
	afx_msg void OnKillfocusEditYDim();
	afx_msg void OnCheckWireframeOverlay();
	afx_msg void OnButtonChooseWireframeColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strTerrainFile;
	CString m_strTerrainPath;
	CString m_strTexturePath;
	COLORREF m_crCoveringColor;
  COLORREF m_crWireframeColor;
	void SetZValue (int nXIndex, int nYIndex, double dZValue);
	double GetZValue (int nXIndex, int nYIndex);
	void SetArrayDimensions (int nXDim, int nYDim);
	void UpdateZDisplay ();
	BOOL m_bInitDialogCalledYet;
	CdmvTerrainData* m_pCdmvTerrainData;
	CArray <double, double> m_arrayZ;
	int m_nArrayYDim;
	int m_nArrayXDim;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGENVTERRAINDATA_H__A710B988_7A1B_4A9F_85F9_80F15EB5317E__INCLUDED_)
