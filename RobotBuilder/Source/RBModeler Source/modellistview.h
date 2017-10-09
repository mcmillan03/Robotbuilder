// ModelListView.h : interface of the CModelListView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELLISTVIEW_H__BF3F9BA6_CFC8_436A_BB81_371047C14328__INCLUDED_)
#define AFX_MODELLISTVIEW_H__BF3F9BA6_CFC8_436A_BB81_371047C14328__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Primitive.h"
#include "Model.h"
#include "ClipboardData.h"
#include "UndoRedoData.h"

class CRBModelerDoc;


class CModelListView : public CListView
{
protected: // create from serialization only
	CModelListView();
	DECLARE_DYNCREATE(CModelListView)

// Attributes
public:
	CRBModelerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModelListView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	void LoadNewModelAndReset (CModel* pModel);
	void ModelStateChanged (CString strDescription);
	virtual ~CModelListView();
	CUndoRedoData m_UndoRedoData;
	void AddPrimitive (CPrimitive* pPrimitive);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	enum {N_SPHERE_IMAGE = 1,
		N_CYLINDER_IMAGE, N_CONE_IMAGE, N_TRUNCATED_CONE_IMAGE,
		N_HEMISPHERE_IMAGE, N_BLOCK_IMAGE} _ImageListIndexes;

// Generated message map functions
protected:
	void ShowPrimitiveProperties (int nIndex);
	void LoadNewModel (CModel* pModel);
	void DeletePrimitiveFromList (int nIndex);
	void SortItem (int nIndex);
	CModel* GetModel ();
	CClipboardData m_Clipboard;
	CImageList m_ImageList;

	enum {BMP_PRIMITIVE_SPHERE, BMP_PRIMITIVE_BLOCK, BMP_PRIMITIVE_CONE,
		BMP_PRIMITIVE_CYLINDER, BMP_PRIMITIVE_HEMISPHERE, BMP_PRIMITIVE_TRUNCATED_CONE};
	CBitmap m_bitmapPrimitives[6];
	//{{AFX_MSG(CModelListView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPopupRename();
	afx_msg void OnPopupProperties();
	afx_msg void OnPopupDelete();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPopupAddBlock();
	afx_msg void OnPopupAddCone();
	afx_msg void OnPopupAddCylinder();
	afx_msg void OnPopupAddHemisphere();
	afx_msg void OnPopupAddSphere();
	afx_msg void OnPopupAddTruncatedCone();
	afx_msg void OnPopupShowAxes();
	afx_msg void OnPopupCameraCOI();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ModelListView.cpp
inline CRBModelerDoc* CModelListView::GetDocument()
   { return (CRBModelerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELLISTVIEW_H__BF3F9BA6_CFC8_436A_BB81_371047C14328__INCLUDED_)
