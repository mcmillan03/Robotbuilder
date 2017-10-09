// RBModelerDoc.h : interface of the CRBModelerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RBModelerDOC_H__94B1AB89_0700_40B5_B80E_0995B1B131C7__INCLUDED_)
#define AFX_RBModelerDOC_H__94B1AB89_0700_40B5_B80E_0995B1B131C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Model.h"
#include "ModelListView.h"
#include "ModelView.h"
#include "CameraData.h"


class CRBModelerDoc : public CDocument
{
protected: // create from serialization only
	CRBModelerDoc();
	DECLARE_DYNCREATE(CRBModelerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRBModelerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL ShowInertialAxes () const;
	CCameraData* GetCameraData ();
	void SetModel (CModel* pModel);
	CModel* GetModel ();
	CModelView* GetModelView ();
	CModelListView* GetModelListView ();
	void AddPrimitive (PrimitiveType thePrimitiveType);
	virtual ~CRBModelerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CCameraData m_CameraData;

// Generated message map functions
protected:
	CModel* m_pModel;
	//{{AFX_MSG(CRBModelerDoc)
	afx_msg void OnPrimitivesAddSphere();
	afx_msg void OnPrimitivesAddBlock();
	afx_msg void OnPrimitivesAddCone();
	afx_msg void OnPrimitivesAddCylinder();
	afx_msg void OnPrimitivesAddHemisphere();
	afx_msg void OnPrimitivesAddTruncatedcone();
	afx_msg void OnButtonViewLeft();
	afx_msg void OnButtonViewBack();
	afx_msg void OnButtonViewBottom();
	afx_msg void OnButtonViewFront();
	afx_msg void OnButtonViewRight();
	afx_msg void OnButtonViewTop();
	afx_msg void OnButtonZoomIn();
	afx_msg void OnButtonZoomOut();
	afx_msg void OnViewCameracontrol();
	afx_msg void OnButtonHideLocalAxes();
	afx_msg void OnButtonShowLocalAxes();
	afx_msg void OnButtonToggleAxes();
	afx_msg void OnUpdateButtonToggleAxes(CCmdUI* pCmdUI);
	afx_msg void OnFileSetbackgroundcolor();
	afx_msg void OnPropertiesPhysicalproperties();
	afx_msg void OnViewCameralight();
	afx_msg void OnUpdateViewCameralight(CCmdUI* pCmdUI);
	afx_msg void OnHelpUsersguide();
	afx_msg void OnHelpTutorial();
	afx_msg void OnButtonpan();
	afx_msg void OnButtonexamine();
	afx_msg void OnUpdateButtonexamine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonpan(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bShowInertialAxes;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RBModelerDOC_H__94B1AB89_0700_40B5_B80E_0995B1B131C7__INCLUDED_)
