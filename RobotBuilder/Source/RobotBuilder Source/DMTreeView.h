// DMTreeView.h : interface of the CDMTreeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMTREEVIEW_H__6BC5BDF1_EC4B_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMTREEVIEW_H__6BC5BDF1_EC4B_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include <typeinfo.h>
//#include "DlgMobileBaseLinkProperties.h"
//#include "DlgRevoluteLinkProperties.h"



class CdmvSystemData;
class CDMViewerDoc;
class CdmvLinkData;
class CdmvMobileBaseLinkData;
class CdmvObject;
class CWTKView;
class CdmvSecJointData;

class CDMTreeView : public CTreeView
{
protected: // create from serialization only
	CDMTreeView();
	DECLARE_DYNCREATE(CDMTreeView)

// Attributes
public:
	CDMViewerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMTreeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ClearBoundingBoxOnSelectedItem ();
//	HTREEITEM AddMobileBase (CdmvSystemData*, HTREEITEM hParent);
	void LoadNewTree ();
	virtual ~CDMTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CImageList m_ImageList;
	
// Generated message map functions
protected:
	void AddNewSecondaryJoint (WORD wdID);
	HTREEITEM AddSecondaryJoint (CdmvSecJointData *pSecJoint, HTREEITEM hParent);
	void InitializeSecondaryJointList (CdmvSystemData* pSystem);
	BOOL m_bPopupDisplayedNow;
	BOOL m_bCurrentlyDragging;
	CImageList* m_pDragImageList;
	CWTKView* GetWTKView ();
	HTREEITEM m_hLastHitTreeItem;
	HTREEITEM m_hSecondaryJointRoot;
	HTREEITEM DescendTreeToFindItem (HTREEITEM hItem, CdmvLinkData* pLink);
	HTREEITEM GetTreeItemFromLinkPointer (CdmvLinkData* pLink);
	HTREEITEM AddLink (CdmvLinkData* pLink, HTREEITEM hParent);
	HTREEITEM AddArticulationNode (CdmvSystemData* pSystem);
	void AddNewLink (WORD wdID);
	void InitializeTree (); 
	//{{AFX_MSG(CDMTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPopupProperties();
	afx_msg void OnPopupShowAxes();
	afx_msg void OnPopupCameraCoi();
	afx_msg void OnPopupDelete ();
	afx_msg void OnPopupSecJointProperties ();
	afx_msg void OnPopupSecJointDelete ();
	afx_msg void OnPopupDeleteRecursively ();
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditCopylink();
	afx_msg void OnEditPastelinkaschild();
	afx_msg void OnEditCutlink();
	afx_msg void OnEditPastelinkassibling();
	afx_msg void OnEditPastelinkasparent();
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	// Bitmaps for the context menu
	CBitmap m_bitmapRevoluteLink;
	CBitmap m_bitmapPrismaticLink;
	CBitmap m_bitmapStaticRootLink;
	CBitmap m_bitmapMobileBaseLink;
	CBitmap m_bitmapSphericalLink;
	CBitmap m_bitmapZScrewTxLink;
	CBitmap m_bitmapSecRevoluteJoint;
	CBitmap m_bitmapSecPrismaticJoint;
	CBitmap m_bitmapSecSphericalJoint;
	/// This stores which is the currently selected tree item (indicated with
	/// a bounding box in the graphics view.  Note this could be different than
	/// the m_hLastHitTreeItem because that is updated with a right click, but this isn't)
	HTREEITEM m_hSelectedItem;
};

#ifndef _DEBUG  // debug version in DMTreeView.cpp
inline CDMViewerDoc* CDMTreeView::GetDocument()
   { return (CDMViewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMTREEVIEW_H__6BC5BDF1_EC4B_11D3_A7DF_0000E8978554__INCLUDED_)
