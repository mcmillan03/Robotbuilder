// DMTreeView.cpp : implementation of the CDMTreeView class
//

#include "stdafx.h"
#include "DMViewer.h"
//#include "WTKView.h"

#include "DMViewerDoc.h"
#include "DMTreeView.h"


#include "PSheetPrismaticLink.h"
#include "PSheetZScrewTxLink.h"
#include "PSheetArticulation.h"
#include "PSheetRevoluteLink.h"
#include "PSheetMobileBaseLink.h"
#include "PSheetSphericalLink.h"
#include "PSheetStaticRootLink.h"
#include "PSheetSecSphericalJoint.h"
#include "PSheetSecRevoluteJoint.h"
#include "PSheetSecPrismaticJoint.h"


//#include "data\dmvStaticLinkData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define N_ARTICULATION_IMAGE		0
#define N_MOBILE_BASE_LINK_IMAGE	1
#define N_REVOLUTE_LINK_IMAGE		2
#define N_ZSCREW_TX_LINK_IMAGE		3
#define N_PRISMATIC_LINK_IMAGE		4
#define N_SPHERICAL_LINK_IMAGE		5
#define N_STATIC_ROOT_LINK_IMAGE	6
#define N_CLOSED_ARTICULATION_IMAGE		7
#define N_SECONDARY_JOINT_ROOT_IMAGE	8
#define N_SECONDARY_PRISMATIC_IMAGE		10
#define N_SECONDARY_REVOLUTE_IMAGE		9
#define N_SECONDARY_SPHERICAL_IMAGE		11



#define STR_MOBILE_BASE_LINK_LABEL	"Mobile Base Link - "
#define STR_REVOLUTE_LINK_LABEL		"Revolute Link - "
#define STR_ZSCREW_TX_LINK_LABEL	"ZScrew Transform - "
#define STR_PRISMATIC_LINK_LABEL	"Prismatic Link - "
#define STR_SPHERICAL_LINK_LABEL	"Spherical Link - "
#define STR_STATIC_ROOT_LINK_LABEL	"Static Root Link - "
#define STR_ARTICULATION_LABEL		"Articulation - "
#define STR_CLOSED_ARTICULATION_LABEL	"Closed Loop Articulation - "
#define STR_SECONDARY_JOINT_ROOT_LABEL	"Secondary Joints"
#define STR_SECONDARY_REVOLUTE_LABEL	"Secondary Revolute - "
#define STR_SECONDARY_PRISMATIC_LABEL	"Secondary Prismatic - "
#define STR_SECONDARY_SPHERICAL_LABEL	"Secondary Spherical - "

/* 
General Notes

  */

/////////////////////////////////////////////////////////////////////////////
// CDMTreeView

IMPLEMENT_DYNCREATE(CDMTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CDMTreeView, CTreeView)
	//{{AFX_MSG_MAP(CDMTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(ID_POPUP_PROPERTIES, OnPopupProperties)
	ON_COMMAND(ID_POPUP_SHOWAXES, OnPopupShowAxes)
	ON_COMMAND(ID_POPUP_CAMERA_COI, OnPopupCameraCoi)
	ON_COMMAND(ID_POPUP_DELETE, OnPopupDelete)
	ON_COMMAND(ID_POPUP_SEC_JOINT_PROPERTIES, OnPopupSecJointProperties)
	ON_COMMAND(ID_POPUP_SEC_JOINT_DELETE, OnPopupSecJointDelete)
	ON_COMMAND(ID_POPUP_DELETE_RECURSIVELY, OnPopupDeleteRecursively)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(ID_POPUP_COPYLINK, OnEditCopylink)
	ON_COMMAND(ID_POPUP_PASTELINKASCHILD, OnEditPastelinkaschild)
	ON_COMMAND(ID_POPUP_CUTLINK, OnEditCutlink)
	ON_COMMAND(ID_POPUP_PASTELINKASSIBLING, OnEditPastelinkassibling)
	ON_COMMAND(ID_POPUP_PASTELINKASPARENT, OnEditPastelinkasparent)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteitem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CDMTreeView construction/destruction

CDMTreeView::CDMTreeView()
{
	m_hLastHitTreeItem = NULL;
	m_hSelectedItem = NULL;
	m_hSecondaryJointRoot = NULL;
	m_pDragImageList = NULL;
	m_bCurrentlyDragging = FALSE;
	m_bPopupDisplayedNow = FALSE;

	// Build the bitmap images used in the tree structure at the class level so
	// it doesn't have to be done each time the context menu is invoked
	m_bitmapRevoluteLink.LoadBitmap (IDB_BITMAP_REVOLUTE_LINK);
	m_bitmapPrismaticLink.LoadBitmap (IDB_BITMAP_PRISMATIC_LINK);
	m_bitmapMobileBaseLink.LoadBitmap (IDB_BITMAP_MOBILE_BASE_LINK);
	m_bitmapZScrewTxLink.LoadBitmap (IDB_BITMAP_ZSCREW_TX_LINK);
	m_bitmapSphericalLink.LoadBitmap (IDB_BITMAP_SPHERICAL_LINK);
	m_bitmapStaticRootLink.LoadBitmap (IDB_BITMAP_STATIC_ROOT_LINK);

	m_bitmapSecRevoluteJoint.LoadBitmap (IDB_BITMAP_SEC_REVOLUTE_JOINT);
	m_bitmapSecPrismaticJoint.LoadBitmap (IDB_BITMAP_SEC_PRISMATIC_JOINT);
	m_bitmapSecSphericalJoint.LoadBitmap (IDB_BITMAP_SEC_SPHERICAL_JOINT);
}

CDMTreeView::~CDMTreeView()
{
	if (m_pDragImageList)
		delete m_pDragImageList;

}

BOOL CDMTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// Add styles
	cs.style |= (TVS_HASBUTTONS | TVS_HASLINES | 
		TVS_SHOWSELALWAYS);



	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDMTreeView drawing

void CDMTreeView::OnDraw(CDC* pDC)
{
	CDMViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void CDMTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CDMTreeView diagnostics

#ifdef _DEBUG
void CDMTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDMTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CDMViewerDoc* CDMTreeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDMViewerDoc)));
	return (CDMViewerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDMTreeView message handlers

int CDMTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_ImageList.Create (IDB_IMAGELIST, 16, 1, RGB (255, 255, 255));
	GetTreeCtrl ().SetImageList (&m_ImageList, TVSIL_NORMAL);
	
	return 0;
}

void CDMTreeView::LoadNewTree()
{
	// Clear the selected links - this needs to be done first, because the call to 
	// DeleteAllItems sometimes causes an OnSelChange event which will get confuse
	// when it tries to unselect something it has already deleted
	m_hSelectedItem  = NULL;

	BOOL bReturnStatus = GetTreeCtrl ().DeleteAllItems ();
	ASSERT (bReturnStatus);
	InitializeTree ();
}

void CDMTreeView::InitializeTree()
{
	CdmvSystemData* pSystem = GetDocument()->GetSystemData ();

	// Load the base
	HTREEITEM hRoot = AddArticulationNode (pSystem);

	int nCounter;
	for (nCounter = 0; nCounter < ((CdmvArticulationData*) pSystem)->m_arrayLinks.GetSize (); nCounter++)
	{
		HTREEITEM hTreeItemParent = GetTreeItemFromLinkPointer (((CdmvArticulationData*) pSystem)->
			m_arrayLinks.GetAt (nCounter).pLinkParent);
		AddLink (((CdmvArticulationData*) pSystem)->m_arrayLinks.GetAt (nCounter).pLink, hTreeItemParent);
	}

	// No links currently selected, so clear the that member
	m_hSelectedItem = NULL;

	// For now expand the tree fully
	GetTreeCtrl().Expand (hRoot,TVE_EXPAND);
}

HTREEITEM CDMTreeView::AddArticulationNode(CdmvSystemData *pSystem)
{
	HTREEITEM hItem;
	if (((CdmvArticulationData*) pSystem)->GetArticulationType () == ARTICULATION)
	{
		CString strItem = ((CdmvArticulationData*) pSystem)->GetName ();

		hItem = GetTreeCtrl ().InsertItem (strItem, N_ARTICULATION_IMAGE, N_ARTICULATION_IMAGE, TVI_ROOT, TVI_LAST);
		ASSERT (hItem);

		// Set the item data for the new tree item.
		BOOL bReturn = GetTreeCtrl ().SetItemData (hItem, (DWORD) ((CdmvArticulationData*) pSystem));
		ASSERT (bReturn);
	}
	else if (((CdmvArticulationData*) pSystem)->GetArticulationType () == CLOSED_ARTICULATION)
	{
		CString strItem = ((CdmvArticulationData*) pSystem)->GetName ();

		hItem = GetTreeCtrl ().InsertItem (strItem, N_CLOSED_ARTICULATION_IMAGE, N_CLOSED_ARTICULATION_IMAGE, TVI_ROOT, TVI_LAST);
		ASSERT (hItem);

		// Set the item data for the new tree item.
		BOOL bReturn = GetTreeCtrl ().SetItemData (hItem, (DWORD) ((CdmvArticulationData*) pSystem));
		ASSERT (bReturn);

		// Load the closed loop's secondary joint list
		InitializeSecondaryJointList  (pSystem);
	}
	else
		ASSERT (FALSE);

	return hItem;
}

void CDMTreeView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	POINT pointPos;
	if (!GetCursorPos ((LPPOINT) &pointPos))
	{
		AfxMessageBox ("Error - Failed to retrieve the current position");
	}

	POINT ptCurrentPos;
	BOOL bReturn = GetCursorPos (&ptCurrentPos);
	ASSERT (bReturn);
	ScreenToClient (&ptCurrentPos);
	m_hLastHitTreeItem = GetTreeCtrl ().HitTest (ptCurrentPos);

	// Make sure something was actually clicked.  This will get called if the user right clicks on nothing
	if (!m_hLastHitTreeItem)
		return;

	// Get pointer to data of selected item
	CdmvObject* pObject = reinterpret_cast <CdmvObject*> (GetTreeCtrl().GetItemData 
		(m_hLastHitTreeItem));

	// Make sure there is item data associated with the selected item.  Specifically,  the secondary joint list
	// has not item data associated with it
	if (!pObject)
	{
		m_hLastHitTreeItem = 0x0;
		return;
	}

	BOOL bParentIsBase = FALSE;
	BOOL bBaseIsSelected = FALSE;
	// Check if it is a secondary joint - because if so, don't need to test for the articulation specific things
	if (pObject->GetObjectType () != SECONDARY_JOINT)
	{
		// Determine if the parent of the currently selected link is the articulation base - 
		// this will be used later to decide if adding the option to add a static root link

		HTREEITEM hItemParent = GetTreeCtrl ().GetParentItem (m_hLastHitTreeItem);
		// If this is NULL, it means that the there is no parent (the item selected is at the top level)
		if (!hItemParent)
		{
			bBaseIsSelected = TRUE;
			bParentIsBase = FALSE;
		}
		else
		{
			bBaseIsSelected = FALSE;

			DWORD dwPointer = GetTreeCtrl ().GetItemData (hItemParent);
			ASSERT (dwPointer);
			if (reinterpret_cast <CdmvObject*> (dwPointer)->GetObjectType () == ARTICULATION)
				bParentIsBase = TRUE;
			else
				bParentIsBase = FALSE;
		}
	}

	// Determine if there are any static root links in the articulation
	CdmvArticulationData *pArticulation = dynamic_cast<CdmvArticulationData*> (GetDocument ()->GetSystemData ());
	BOOL bNoStaticRootLinks;
	if (pArticulation->GetNumberOfStaticRootLinks () == 0)
		bNoStaticRootLinks = TRUE;
	else
		bNoStaticRootLinks = FALSE;


	// Only display the context menu if a tree item was successfully selected.
	if (m_hLastHitTreeItem)
	{
		// link list for nested popup
		CMenu menuLinksPopup;
		menuLinksPopup.CreatePopupMenu ();
		menuLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_LINKS_REVOLUTE, 
			"Revolute Link");
		menuLinksPopup.SetMenuItemBitmaps (ID_POPUP_LINKS_REVOLUTE, MF_BYCOMMAND, 
			&m_bitmapRevoluteLink, &m_bitmapRevoluteLink);
		menuLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_LINKS_PRISMATIC, 
			"Prismatic Link");
		menuLinksPopup.SetMenuItemBitmaps (ID_POPUP_LINKS_PRISMATIC, MF_BYCOMMAND, 
			&m_bitmapPrismaticLink, &m_bitmapPrismaticLink);
		menuLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_LINKS_MOBILE_BASE, 
			"Mobile Base Link");
		menuLinksPopup.SetMenuItemBitmaps (ID_POPUP_LINKS_MOBILE_BASE, MF_BYCOMMAND, 
			&m_bitmapMobileBaseLink, &m_bitmapMobileBaseLink);
		menuLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_LINKS_ZSCREW_TX, 
			"ZScrew Transform");
		menuLinksPopup.SetMenuItemBitmaps (ID_POPUP_LINKS_ZSCREW_TX, MF_BYCOMMAND, 
			&m_bitmapZScrewTxLink, &m_bitmapZScrewTxLink);
		menuLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_LINKS_SPHERICAL, 
			"Spherical Link");
		menuLinksPopup.SetMenuItemBitmaps (ID_POPUP_LINKS_SPHERICAL, MF_BYCOMMAND, 
			&m_bitmapSphericalLink, &m_bitmapSphericalLink);
		if (bBaseIsSelected && bNoStaticRootLinks)
			menuLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_LINKS_STATIC_ROOT, 
				"Static Root Link");
		else
			menuLinksPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_LINKS_STATIC_ROOT, 
				"Static Root Link");
		menuLinksPopup.SetMenuItemBitmaps (ID_POPUP_LINKS_STATIC_ROOT, MF_BYCOMMAND, 
			&m_bitmapStaticRootLink, &m_bitmapStaticRootLink);
		
		// link list for nested popup - for sibling adding
		CMenu menuSiblingLinksPopup;
		menuSiblingLinksPopup.CreatePopupMenu ();
		menuSiblingLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SIBLING_LINKS_REVOLUTE, 
			"Revolute Link");
		menuSiblingLinksPopup.SetMenuItemBitmaps (ID_POPUP_SIBLING_LINKS_REVOLUTE, MF_BYCOMMAND, 
			&m_bitmapRevoluteLink, &m_bitmapRevoluteLink);
		menuSiblingLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SIBLING_LINKS_PRISMATIC, 
			"Prismatic Link");
		menuSiblingLinksPopup.SetMenuItemBitmaps (ID_POPUP_SIBLING_LINKS_PRISMATIC, MF_BYCOMMAND, 
			&m_bitmapPrismaticLink, &m_bitmapPrismaticLink);
		menuSiblingLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SIBLING_LINKS_MOBILE_BASE, 
			"Mobile Base Link");
		menuSiblingLinksPopup.SetMenuItemBitmaps (ID_POPUP_SIBLING_LINKS_MOBILE_BASE, MF_BYCOMMAND, 
			&m_bitmapMobileBaseLink, &m_bitmapMobileBaseLink);
		menuSiblingLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SIBLING_LINKS_ZSCREW_TX, 
			"ZScrew Transform");
		menuSiblingLinksPopup.SetMenuItemBitmaps (ID_POPUP_SIBLING_LINKS_ZSCREW_TX, MF_BYCOMMAND, 
			&m_bitmapZScrewTxLink, &m_bitmapZScrewTxLink);
		menuSiblingLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SIBLING_LINKS_SPHERICAL, 
			"Spherical Link");
		menuSiblingLinksPopup.SetMenuItemBitmaps (ID_POPUP_SIBLING_LINKS_SPHERICAL, MF_BYCOMMAND, 
			&m_bitmapSphericalLink, &m_bitmapSphericalLink);
		if (bParentIsBase && bNoStaticRootLinks)
			menuSiblingLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SIBLING_LINKS_STATIC_ROOT, 
				"Static Root Link");
		else
			menuSiblingLinksPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_SIBLING_LINKS_STATIC_ROOT, 
				"Static Root Link");
		menuSiblingLinksPopup.SetMenuItemBitmaps (ID_POPUP_SIBLING_LINKS_STATIC_ROOT, MF_BYCOMMAND, 
			&m_bitmapStaticRootLink, &m_bitmapStaticRootLink);

		// link list for nested popup - for add as parent
		CMenu menuParentLinksPopup;
		menuParentLinksPopup.CreatePopupMenu ();
		menuParentLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PARENT_LINKS_REVOLUTE, 
			"Revolute Link");
		menuParentLinksPopup.SetMenuItemBitmaps (ID_POPUP_PARENT_LINKS_REVOLUTE, MF_BYCOMMAND, 
			&m_bitmapRevoluteLink, &m_bitmapRevoluteLink);
		menuParentLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PARENT_LINKS_PRISMATIC, 
			"Prismatic Link");
		menuParentLinksPopup.SetMenuItemBitmaps (ID_POPUP_PARENT_LINKS_PRISMATIC, MF_BYCOMMAND, 
			&m_bitmapPrismaticLink, &m_bitmapPrismaticLink);
		menuParentLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PARENT_LINKS_MOBILE_BASE, 
			"Mobile Base Link");
		menuParentLinksPopup.SetMenuItemBitmaps (ID_POPUP_PARENT_LINKS_MOBILE_BASE, MF_BYCOMMAND, 
			&m_bitmapMobileBaseLink, &m_bitmapMobileBaseLink);
		menuParentLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PARENT_LINKS_ZSCREW_TX, 
			"ZScrew Transform");
		menuParentLinksPopup.SetMenuItemBitmaps (ID_POPUP_PARENT_LINKS_ZSCREW_TX, MF_BYCOMMAND, 
			&m_bitmapZScrewTxLink, &m_bitmapZScrewTxLink);
		menuParentLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PARENT_LINKS_SPHERICAL, 
			"Spherical Link");
		menuParentLinksPopup.SetMenuItemBitmaps (ID_POPUP_PARENT_LINKS_SPHERICAL, MF_BYCOMMAND, 
			&m_bitmapSphericalLink, &m_bitmapSphericalLink);
		if (bParentIsBase && bNoStaticRootLinks)
			menuParentLinksPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PARENT_LINKS_STATIC_ROOT, 
				"Static Root Link");
		else
			menuParentLinksPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_PARENT_LINKS_STATIC_ROOT, 
				"Static Root Link");
		menuParentLinksPopup.SetMenuItemBitmaps (ID_POPUP_PARENT_LINKS_STATIC_ROOT, MF_BYCOMMAND, 
			&m_bitmapStaticRootLink, &m_bitmapStaticRootLink);
		
		// sec joint list for seconary joint nested popup
		CMenu menuSecJointPopup;
		bReturn = menuSecJointPopup.CreatePopupMenu ();
		ASSERT (bReturn);
		menuSecJointPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SEC_JOINT_REVOLUTE, 
			"Secondary Revolute Joint");
		menuSecJointPopup.SetMenuItemBitmaps (ID_POPUP_SEC_JOINT_REVOLUTE, MF_BYCOMMAND, 
			&m_bitmapSecRevoluteJoint, &m_bitmapSecRevoluteJoint);
		menuSecJointPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SEC_JOINT_PRISMATIC, 
			"Secondary Prismatic Joint");
		menuSecJointPopup.SetMenuItemBitmaps (ID_POPUP_SEC_JOINT_PRISMATIC, MF_BYCOMMAND, 
			&m_bitmapSecPrismaticJoint, &m_bitmapSecPrismaticJoint);
		menuSecJointPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SEC_JOINT_SPHERICAL, 
			"Secondary Spherical Joint");
		menuSecJointPopup.SetMenuItemBitmaps (ID_POPUP_SEC_JOINT_SPHERICAL, MF_BYCOMMAND, 
			&m_bitmapSecSphericalJoint, &m_bitmapSecSphericalJoint);


		CMenu menuPopup;
		menuPopup.CreatePopupMenu ();
		// build the item based on the object type
		// note that the object data can be NULL as in the case of the secondary joint root item
		if (pObject != NULL)
		{
			if (pObject->GetObjectType () == LINK || pObject->GetObjectType () == ARTICULATION)
			{
				menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PROPERTIES, "Properties...");
				menuPopup.AppendMenu (MF_SEPARATOR);
				if (pObject->ShowWtkAxes ())
					menuPopup.AppendMenu (MF_STRING | MF_ENABLED | MF_CHECKED, ID_POPUP_SHOWAXES, "Show Axes");
				else
					menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SHOWAXES, "Show Axes");
				// COI
				/* Removed 6/3/2003 - LMF
					Note: Because Pan mode now updates the center of interest,
					it should be possible to switch the center of interest in
					pan mode.
				
				if (GetDocument ()->GetCameraData ()->GetViewInPanMode ())
				{
					// In pan mode - COI meaningless
					if (pObject->IsCameraCenterOfInterest ())
						menuPopup.AppendMenu (MF_STRING | MF_CHECKED | MF_GRAYED, ID_POPUP_CAMERA_COI, "Center Of Interest");
					else
						menuPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_CAMERA_COI, "Center Of Interest");
				}
				else
				{ */
				
				if (pObject->IsCameraCenterOfInterest ())
					menuPopup.AppendMenu (MF_STRING | MF_ENABLED | MF_CHECKED, ID_POPUP_CAMERA_COI, "Center Of Interest");
				else
					menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_CAMERA_COI, "Center Of Interest");
				
				//}
				VERIFY (menuPopup.AppendMenu (MF_SEPARATOR));
				// Don't let the user add a child if there is already a static root link and the menu
				// is for the articulation (because that would insert a link between the root and
				// the static root link)
				if (!(pObject->GetObjectType () == ARTICULATION && !bNoStaticRootLinks))
					menuPopup.AppendMenu (MF_STRING | MF_ENABLED | MF_POPUP,(UINT) menuLinksPopup.m_hMenu, "Add Child");
				if (pObject->GetObjectType () == LINK)
				{
					menuPopup.AppendMenu (MF_STRING | MF_ENABLED | MF_POPUP,(UINT) menuSiblingLinksPopup.m_hMenu, "Add Sibling");
					// Add "Add parent" option only if it is not a static root link (because that
					// would put a link between the static root link and the root)
					if (dynamic_cast<CdmvLinkData*> (pObject)->GetLinkType () != STATIC_ROOT_LINK)
						menuPopup.AppendMenu (MF_STRING | MF_ENABLED | MF_POPUP,(UINT) menuParentLinksPopup.m_hMenu, "Add Parent");
				}
				if (pObject->GetObjectType () == LINK)
					menuPopup.AppendMenu (MF_STRING | MF_ENABLED | MF_POPUP, (UINT) menuSecJointPopup.m_hMenu,
					"Add Secondary Joint");
				if (pObject->GetObjectType () == LINK)
				{
					menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_DELETE, "Delete Link");
					menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_DELETE_RECURSIVELY, "Delete Recursively");
					menuPopup.AppendMenu (MF_SEPARATOR);
					// Don't want to put a static root link on the clipboard because too difficult
					// to manage rules for that.  So disable the cut and copy options if the currently
					// selected link is a static root link.  Note that if we are here, the pObject has
					// to be a link
					if (dynamic_cast<CdmvLinkData*> (pObject)->GetLinkType () == STATIC_ROOT_LINK)
					{
						menuPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_CUTLINK, "Cut Link");
						menuPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_COPYLINK, "Copy Link");
					}
					else
					{
						menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_CUTLINK, "Cut Link");
						menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_COPYLINK, "Copy Link");
					}
					if (GetDocument ()->GetClipboardData ())
					{
						menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PASTELINKASCHILD, "Paste Link As Child");
						menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PASTELINKASSIBLING, "Paste Link As Sibling");
						// Don't want to be able something in front of a static root link
						if (dynamic_cast<CdmvLinkData*> (pObject)->GetLinkType () != STATIC_ROOT_LINK)
							menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PASTELINKASPARENT, "Paste Link As Parent");
						else
							menuPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_PASTELINKASPARENT, "Paste Link As Parent");

					}
					else
					{
						menuPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_PASTELINKASCHILD, "Paste Link As Child");
						menuPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_PASTELINKASSIBLING, "Paste Link As Sibling");
						menuPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_PASTELINKASPARENT, "Paste Link As Parent");
					}

				}
				else if (pObject->GetObjectType () == ARTICULATION)
				{
					// Can't paste the link if there is already a static root link in the articulation
					// because this would force the static root link to not be a child of the base
					if (GetDocument ()->GetClipboardData () && bNoStaticRootLinks)
					{
						menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_PASTELINKASCHILD, "Paste Link As Child");
					}
					else
					{
						menuPopup.AppendMenu (MF_STRING | MF_GRAYED, ID_POPUP_PASTELINKASCHILD, "Paste Link As Child");
					}
				}
				m_bPopupDisplayedNow = TRUE;
				menuPopup.TrackPopupMenu (TPM_LEFTALIGN | TPM_LEFTBUTTON, pointPos.x, pointPos.y, this);
				// note - I stopped examining the return value because this will return a false
				// value if another area is right-clicked after the pop menu is created - but
				// that really isn't an error.
				m_bPopupDisplayedNow = FALSE;
			}
			if (pObject->GetObjectType () == SECONDARY_JOINT)
			{
				menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SEC_JOINT_PROPERTIES, "Properties...");
				menuPopup.AppendMenu (MF_SEPARATOR);
				menuPopup.AppendMenu (MF_STRING | MF_ENABLED, ID_POPUP_SEC_JOINT_DELETE, "Delete Secondary Joint");
				
				m_bPopupDisplayedNow = TRUE;
				menuPopup.TrackPopupMenu (TPM_LEFTALIGN | TPM_LEFTBUTTON, pointPos.x, pointPos.y, this);
				// note - I stopped examining the return value because this will return a false
				// value if another area is right-clicked after the pop menu is created - but
				// that really isn't an error.
				m_bPopupDisplayedNow = FALSE;
			}
		}
	} 
	*pResult = 0;
}

void CDMTreeView::OnPopupProperties() 
{
	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);

	if (((CdmvObject*) dwPointer)->GetObjectType () == ARTICULATION)
	{
		CPSheetArticulation psheet("Articulation Data");
		psheet.m_pCdmvArticulationData = ((CdmvArticulationData*) dwPointer);
		if (psheet.DoModal () == IDOK)
		{
			// Reset the label
			BOOL bReturn = GetTreeCtrl ().SetItemText (m_hLastHitTreeItem,  
				((CdmvArticulationData*) dwPointer)->GetName ());
			ASSERT (bReturn);
			// Now pick up the new MDH
			Quaternion qOrientation;
			CartesianVector cvPosition;
			((CdmvArticulationData*) dwPointer)->GetRefSystem (qOrientation, cvPosition);
#ifdef WTK_LICENSE_AVAILABLE
			GetWTKView ()->m_WTKGraphics.SetNodeTransform (reinterpret_cast <CdmvObject*> (dwPointer),
				qOrientation, cvPosition);
			CString strGraphicsFile, strGraphicsPath;
			((CdmvArticulationData*) GetDocument()->GetSystemData ())->GetGraphicsModel (strGraphicsFile, strGraphicsPath);
			GetWTKView ()->m_WTKGraphics.LoadNewNodeGeometry (reinterpret_cast <CdmvObject*> (dwPointer),
				strGraphicsPath + strGraphicsFile);

			// The position of some of the links may have changed so need to update the camera
			GetWTKView ()->m_WTKGraphics.UpdateCamera (FALSE);
#endif
		}
	}
	else if (((CdmvObject*) dwPointer)->GetObjectType () == LINK)
	{
		if (((CdmvLinkData*) dwPointer)->GetLinkType () == MOBILE_BASE_LINK)
		{
			CPSheetMobileBaseLink psheet ("Mobile Base Link");
			psheet.m_pCdmvMobileBaseLinkData = ((CdmvMobileBaseLinkData*) dwPointer);
			if (psheet.DoModal () == IDOK)
			{
				// Reset the label
				BOOL bReturn = GetTreeCtrl ().SetItemText (m_hLastHitTreeItem,  
					((CdmvMobileBaseLinkData*) dwPointer)->GetName ());
				ASSERT (bReturn);
//				int nLinkUID;
//				nLinkUID = ((CdmvMobileBaseLinkData*) dwPointer)->GetLinkUID ();
//				CString strLabel;
//				strLabel.Format ("%d", nLinkUID);
				// Now pick up the new MDH
				Quaternion qOrientation;
				CartesianVector cvPosition;
				((CdmvMobileBaseLinkData*) dwPointer)->GetPlacement (qOrientation, cvPosition);
#ifdef WTK_LICENSE_AVAILABLE
				GetWTKView ()->m_WTKGraphics.SetNodeTransform (reinterpret_cast <CdmvObject*> (dwPointer),
					qOrientation, cvPosition);
				CString strGraphicsFile, strGraphicsPath;
				reinterpret_cast <CdmvObject*> (dwPointer)->GetGraphicsModel (strGraphicsFile, strGraphicsPath);
				GetWTKView ()->m_WTKGraphics.LoadNewNodeGeometry (reinterpret_cast <CdmvObject*> (dwPointer),
					strGraphicsPath + strGraphicsFile);

				// The position of some of the links may have changed so need to update the camera
				GetWTKView ()->m_WTKGraphics.UpdateCamera (FALSE);
#endif
			}
		
		}
		else if (((CdmvLinkData*) dwPointer)->GetLinkType () == REVOLUTE_LINK)
		{
			CPSheetRevoluteLink psheet ("Revolute Link");
			psheet.m_pCdmvRevoluteLinkData = ((CdmvRevoluteLinkData*) dwPointer);
			if (psheet.DoModal () == IDOK)
			{
				// Reset the label
				BOOL bReturn = GetTreeCtrl ().SetItemText (m_hLastHitTreeItem,  
					((CdmvRevoluteLinkData*) dwPointer)->GetName ());
				ASSERT (bReturn);
				// change the view to reflect
				// first get the unique label
//				int nLinkUID;
//				nLinkUID = ((CdmvRevoluteLinkData*) dwPointer)->GetLinkUID ();
//				CString strLabel;
//				strLabel.Format ("%d", nLinkUID);
				// Now pick up the new MDH
				structMDHParameters strtMDHParameters;
				((CdmvRevoluteLinkData*) dwPointer)->GetMDHParameters (&strtMDHParameters);
#ifdef WTK_LICENSE_AVAILABLE
				GetWTKView ()->m_WTKGraphics.SetNodeTransform (reinterpret_cast <CdmvObject*> (dwPointer),
					strtMDHParameters);
				CString strGraphicsFile, strGraphicsPath;
				reinterpret_cast <CdmvObject*> (dwPointer)->GetGraphicsModel (strGraphicsFile, strGraphicsPath);
				GetWTKView ()->m_WTKGraphics.LoadNewNodeGeometry (reinterpret_cast <CdmvObject*> (dwPointer),
					strGraphicsPath + strGraphicsFile);
				// The position of some of the links may have changed so need to update the camera
				GetWTKView ()->m_WTKGraphics.UpdateCamera (FALSE);
#endif
			}
		}
		else if (((CdmvLinkData*) dwPointer)->GetLinkType () == ZSCREW_TX_LINK)
		{
			CPSheetZScrewTxLink psheet("ZScrew Transform");
			psheet.m_pCdmvZScrewTxLinkData = ((CdmvZScrewTxLinkData*) dwPointer);

			if (psheet.DoModal () == IDOK)
			{
				// Reset the label
				BOOL bReturn = GetTreeCtrl ().SetItemText (m_hLastHitTreeItem,  
					((CdmvZScrewTxLinkData*) dwPointer)->GetName ());
				ASSERT (bReturn);
				// change the view to reflect
				// first get the unique label
//				int nLinkUID;
//				nLinkUID = ((CdmvZScrewTxLinkData*) dwPointer)->GetLinkUID ();
//				CString strLabel;
//				strLabel.Format ("%d", nLinkUID);
				// Now pick up the new MDH
				structZScrewTxLinkParameters strtZScrewTxLinkParameters;
				((CdmvZScrewTxLinkData*) dwPointer)->GetParameters (&strtZScrewTxLinkParameters);
				structMDHParameters strtMDHParameters;
				strtMDHParameters.fa = 0;
				strtMDHParameters.fAlpha = 0;
				strtMDHParameters.fd = strtZScrewTxLinkParameters.fD;
				strtMDHParameters.fTheta = strtZScrewTxLinkParameters.fTheta;
#ifdef WTK_LICENSE_AVAILABLE
				GetWTKView ()->m_WTKGraphics.SetNodeTransform (reinterpret_cast <CdmvObject*> (dwPointer),
					strtMDHParameters);
				// The position of some of the links may have changed so need to update the camera
				GetWTKView ()->m_WTKGraphics.UpdateCamera (FALSE);
#endif
			}
		}
		else if (((CdmvLinkData*) dwPointer)->GetLinkType () == PRISMATIC_LINK)
		{
			CPSheetPrismaticLink psheet ("Prismatic Link");
			psheet.m_pCdmvPrismaticLinkData = ((CdmvPrismaticLinkData*) dwPointer);
			if (psheet.DoModal () == IDOK)
			{
				// Reset the label
				BOOL bReturn = GetTreeCtrl ().SetItemText (m_hLastHitTreeItem,  
					((CdmvPrismaticLinkData*) dwPointer)->GetName ());
				ASSERT (bReturn);
				// change the view to reflect
				// first get the unique label
//				int nLinkUID;
//				nLinkUID = ((CdmvPrismaticLinkData*) dwPointer)->GetLinkUID ();
//				CString strLabel;
//				strLabel.Format ("%d", nLinkUID);
				// Now pick up the new MDH
				structMDHParameters strtMDHParameters;
				((CdmvPrismaticLinkData*) dwPointer)->GetMDHParameters (&strtMDHParameters);
#ifdef WTK_LICENSE_AVAILABLE
				GetWTKView ()->m_WTKGraphics.SetNodeTransform (reinterpret_cast <CdmvObject*> (dwPointer),
					strtMDHParameters);
				CString strGraphicsFile, strGraphicsPath;
				reinterpret_cast <CdmvObject*> (dwPointer)->GetGraphicsModel (strGraphicsFile, strGraphicsPath);
				GetWTKView ()->m_WTKGraphics.LoadNewNodeGeometry (reinterpret_cast <CdmvObject*> (dwPointer),
					strGraphicsPath + strGraphicsFile);
				// The position of some of the links may have changed so need to update the camera
				GetWTKView ()->m_WTKGraphics.UpdateCamera (FALSE);
#endif
			}
		}
		else if (((CdmvLinkData*) dwPointer)->GetLinkType () == SPHERICAL_LINK)
		{
			CPSheetSphericalLink psheet ("Spherical Link");
			psheet.m_pCdmvSphericalLinkData = ((CdmvSphericalLinkData*) dwPointer);
			if (psheet.DoModal () == IDOK)
			{
				// Reset the label
				BOOL bReturn = GetTreeCtrl ().SetItemText (m_hLastHitTreeItem, 
					((CdmvSphericalLinkData*) dwPointer)->GetName ());
				ASSERT (bReturn);
				// change the view to reflect
				// first get the unique label
//				int nLinkUID;
//				nLinkUID = ((CdmvSphericalLinkData*) dwPointer)->GetLinkUID ();
//				CString strLabel;
//				strLabel.Format ("%d", nLinkUID);
				// Now pick up the new position and orientation
				CartesianVector cvJointOffset;
				structSphericalLinkState strtSphericalLinkState;
				((CdmvSphericalLinkData*) dwPointer)->GetJointOffset (cvJointOffset);
				((CdmvSphericalLinkData*) dwPointer)->GetLinkState (&strtSphericalLinkState);
#ifdef WTK_LICENSE_AVAILABLE
				GetWTKView ()->m_WTKGraphics.SetNodeTransformWithEulerAngles (reinterpret_cast <CdmvObject*> (dwPointer),
					strtSphericalLinkState.eaAngles, cvJointOffset);
				CString strGraphicsFile, strGraphicsPath;
				reinterpret_cast <CdmvObject*> (dwPointer)->GetGraphicsModel (strGraphicsFile, strGraphicsPath);
				GetWTKView ()->m_WTKGraphics.LoadNewNodeGeometry (reinterpret_cast <CdmvObject*> (dwPointer),
					strGraphicsPath + strGraphicsFile);
				// The position of some of the links may have changed so need to update the camera
				GetWTKView ()->m_WTKGraphics.UpdateCamera (FALSE);
#endif
			}
		}
		else if (((CdmvLinkData*) dwPointer)->GetLinkType () == STATIC_ROOT_LINK)
		{
			CPSheetStaticRootLink psheet ("Static Root Link");
			psheet.m_pCdmvStaticRootLinkData = ((CdmvStaticRootLinkData*) dwPointer);
			if (psheet.DoModal () == IDOK)
			{
				// Reset the label
				BOOL bReturn = GetTreeCtrl ().SetItemText (m_hLastHitTreeItem, 
					((CdmvPrismaticLinkData*) dwPointer)->GetName ());
				ASSERT (bReturn);
				// change the view to reflect
				// first get the unique label
//				int nLinkUID;
//				nLinkUID = ((CdmvStaticRootLinkData*) dwPointer)->GetLinkUID ();
//				CString strLabel;
//				strLabel.Format ("%d", nLinkUID);
				// Now set the MDH -- static root links always are at the origin
				structMDHParameters strtMDHParameters;
				strtMDHParameters.fa = 0;
				strtMDHParameters.fAlpha = 0;
				strtMDHParameters.fd = 0;
				strtMDHParameters.fTheta = 0;
#ifdef WTK_LICENSE_AVAILABLE
				GetWTKView ()->m_WTKGraphics.SetNodeTransform (reinterpret_cast <CdmvObject*> (dwPointer),
					strtMDHParameters);
				CString strGraphicsFile, strGraphicsPath;
				reinterpret_cast <CdmvObject*> (dwPointer)->GetGraphicsModel (strGraphicsFile, strGraphicsPath);
				GetWTKView ()->m_WTKGraphics.LoadNewNodeGeometry (reinterpret_cast <CdmvObject*> (dwPointer),
					strGraphicsPath + strGraphicsFile);
				// The position of some of the links may have changed so need to update the camera
				GetWTKView ()->m_WTKGraphics.UpdateCamera (FALSE);
#endif
			}
		}
		else
		{
			AfxMessageBox ("Not yet implemented.");
		}
	}
}


HTREEITEM CDMTreeView::AddLink(CdmvLinkData *pLink, HTREEITEM hParent)
{
	CString strLinkTitle;
	HTREEITEM hLink;
	BOOL bReturn;

	switch (pLink->GetLinkType ())
	{
	case MOBILE_BASE_LINK:
		strLinkTitle = pLink->GetName ();
		hLink = GetTreeCtrl ().InsertItem (strLinkTitle, N_MOBILE_BASE_LINK_IMAGE,
			N_MOBILE_BASE_LINK_IMAGE, hParent);
		ASSERT (hLink);
		// Set the item data for the new tree item.
		bReturn = GetTreeCtrl ().SetItemData (hLink, (DWORD) pLink);
		ASSERT (bReturn);
		break;
	case REVOLUTE_LINK:
		strLinkTitle = pLink->GetName ();
		hLink = GetTreeCtrl ().InsertItem (strLinkTitle, N_REVOLUTE_LINK_IMAGE,
			N_REVOLUTE_LINK_IMAGE, hParent);
		ASSERT (hLink);
		// Set the item data for the new tree item.
		bReturn = GetTreeCtrl ().SetItemData (hLink, (DWORD) pLink);
		ASSERT (bReturn);
		break;
	case ZSCREW_TX_LINK:
		strLinkTitle = pLink->GetName ();
		hLink = GetTreeCtrl ().InsertItem (strLinkTitle, N_ZSCREW_TX_LINK_IMAGE,
			N_ZSCREW_TX_LINK_IMAGE, hParent);
		ASSERT (hLink);
		// Set the item data for the new tree item.
		bReturn = GetTreeCtrl ().SetItemData (hLink, (DWORD) pLink);
		ASSERT (bReturn);
		break;
	case PRISMATIC_LINK:
		strLinkTitle = pLink->GetName ();
		hLink = GetTreeCtrl ().InsertItem (strLinkTitle, N_PRISMATIC_LINK_IMAGE,
			N_PRISMATIC_LINK_IMAGE, hParent);
		ASSERT (hLink);
		// Set the item data for the new tree item.
		bReturn = GetTreeCtrl ().SetItemData (hLink, (DWORD) pLink);
		ASSERT (bReturn);
		break;
	case SPHERICAL_LINK:
		strLinkTitle = pLink->GetName ();
		hLink = GetTreeCtrl ().InsertItem (strLinkTitle, N_SPHERICAL_LINK_IMAGE,
			N_SPHERICAL_LINK_IMAGE, hParent);
		ASSERT (hLink);
		// Set the item data for the new tree item.
		bReturn = GetTreeCtrl ().SetItemData (hLink, (DWORD) pLink);
		ASSERT (bReturn);
		break;
	case STATIC_ROOT_LINK:
		strLinkTitle = pLink->GetName ();
		hLink = GetTreeCtrl ().InsertItem (strLinkTitle, N_STATIC_ROOT_LINK_IMAGE,
			N_STATIC_ROOT_LINK_IMAGE, hParent);
		ASSERT (hLink);
		// Set the item data for the new tree item.
		bReturn = GetTreeCtrl ().SetItemData (hLink, (DWORD) pLink);
		ASSERT (bReturn);
		break;
	default:
		AfxMessageBox ("Link type not implemented for tree item add", MB_OK);
		hLink = NULL;
	}

	// for now to expand
	GetTreeCtrl ().EnsureVisible (hLink);
	return hLink;
}

HTREEITEM CDMTreeView::GetTreeItemFromLinkPointer(CdmvLinkData *pLink)
{
	// Get the root to start from.
	HTREEITEM hRoot = GetTreeCtrl ().GetRootItem ();
	ASSERT (hRoot);

	// The root will always be the articulation type, so start checking the pointers
	// starting with the first child of the root.

	// First check that the pLink is not NULL.  If so, it indicates that there is no parent
	// so the link will be child of the root
	if (pLink == NULL)
	{
		return hRoot;
	}
	else
	{
		HTREEITEM hFirstChild = GetTreeCtrl().GetChildItem (hRoot);
		ASSERT (hFirstChild);

		HTREEITEM hLinkItem = DescendTreeToFindItem (hFirstChild, pLink);
		ASSERT (hLinkItem);

		return hLinkItem;
	}
}

HTREEITEM CDMTreeView::DescendTreeToFindItem(HTREEITEM hItem, CdmvLinkData *pLink)
{
	if ((CdmvLinkData*) GetTreeCtrl().GetItemData (hItem) == pLink)
	{
		// Then found a match, so return the HTREEITEM
		return hItem;
	}
	
	// No match so check for children
	if (GetTreeCtrl ().ItemHasChildren (hItem))
	{
		HTREEITEM hChild = GetTreeCtrl ().GetChildItem (hItem);
		ASSERT (hChild);
		HTREEITEM hReturn;
		hReturn = DescendTreeToFindItem (hChild, pLink);
		if (hReturn != NULL)
			return hReturn;
	}

	// Otherwise look at the other siblings
	HTREEITEM hSibling = GetTreeCtrl ().GetNextSiblingItem (hItem);
	if (hSibling == NULL)
	{
		// Then the HTREEITEM has no more siblings
		return NULL;
	}
	else
	{
		// Then analyze the next sibling.
		return DescendTreeToFindItem (hSibling, pLink);
	}
}

void CDMTreeView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	// Unselect the previous one (if one is selected)
	ClearBoundingBoxOnSelectedItem ();

	// Set the new
	m_hSelectedItem = pNMTreeView->itemNew.hItem;
	ASSERT (m_hSelectedItem);

	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hSelectedItem);
	if (dwPointer != NULL)
	{
		if ( ((CdmvObject*) dwPointer)->GetObjectType () == LINK)
		{
//			unsigned int nLinkUID = ((CdmvLinkData*) dwPointer)->GetLinkUID ();
//			CString strLabel;
//			strLabel.Format ("%d", nLinkUID);
			
#ifdef WTK_LICENSE_AVAILABLE
				GetWTKView ()->m_WTKGraphics.IndicateSelectedModel (
					reinterpret_cast <CdmvObject*> (dwPointer), TRUE);
#endif
		}
	}
	


	*pResult = 0;
}


// The MFC docs recommend not saving a pointer to a view permanently so
// pick it up when needed
CWTKView* CDMTreeView::GetWTKView()
{
	return GetDocument ()->GetWTKView ();
}

void CDMTreeView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bCurrentlyDragging)
	{
		// Then dragging
		CPoint ptScreen(point);
		ClientToScreen(&ptScreen);

		// Move the drag image
		BOOL bReturnStatus = m_pDragImageList->DragMove(ptScreen);	
		ASSERT (bReturnStatus);

		// Break the message lock to update the display to highlight the drop target
		bReturnStatus = m_pDragImageList->DragShowNolock(FALSE);
		ASSERT (bReturnStatus);

		UINT unFlags;
		HTREEITEM hItem = GetTreeCtrl().HitTest(point, &unFlags);
		if (hItem != NULL)
		{
			// Select it
			bReturnStatus = GetTreeCtrl ().SelectDropTarget(hItem);
			//m_hitemDrop = hitem;
		}
		else
			bReturnStatus = GetTreeCtrl ().SelectDropTarget(NULL);

		// Lock the messages again
		bReturnStatus = m_pDragImageList->DragShowNolock(TRUE);	
		ASSERT (bReturnStatus);
	
	}

	CTreeView::OnMouseMove(nFlags, point);
}

void CDMTreeView::AddNewLink (WORD wdID)
{
	CdmvLinkData* pLink;
	BOOL bAddSibling = FALSE;

	enum {CHILD, SIBLING, PARENT} enumAddType;

	switch (wdID)
	{
	case ID_POPUP_LINKS_REVOLUTE:
		pLink = new CdmvRevoluteLinkData;
		enumAddType = CHILD;
		break;
	case ID_POPUP_LINKS_PRISMATIC:
		pLink = new CdmvPrismaticLinkData;
		enumAddType = CHILD;
		break;
	case ID_POPUP_LINKS_MOBILE_BASE:
		pLink = new CdmvMobileBaseLinkData;
		enumAddType = CHILD;
		break;
	case ID_POPUP_LINKS_ZSCREW_TX:
		pLink = new CdmvZScrewTxLinkData;
		enumAddType = CHILD;
		break;
	case ID_POPUP_LINKS_SPHERICAL:
		pLink = new CdmvSphericalLinkData;
		enumAddType = CHILD;
		break;
	case ID_POPUP_LINKS_STATIC_ROOT:
		pLink = new CdmvStaticRootLinkData;
		enumAddType = CHILD;
		break;
	case ID_POPUP_SIBLING_LINKS_REVOLUTE:
		pLink = new CdmvRevoluteLinkData;
		enumAddType = SIBLING;
		break;
	case ID_POPUP_SIBLING_LINKS_PRISMATIC:
		pLink = new CdmvPrismaticLinkData;
		enumAddType = SIBLING;
		break;
	case ID_POPUP_SIBLING_LINKS_MOBILE_BASE:
		pLink = new CdmvMobileBaseLinkData;
		enumAddType = SIBLING;
		break;
	case ID_POPUP_SIBLING_LINKS_ZSCREW_TX:
		pLink = new CdmvZScrewTxLinkData;
		enumAddType = SIBLING;
		break;
	case ID_POPUP_SIBLING_LINKS_SPHERICAL:
		pLink = new CdmvSphericalLinkData;
		enumAddType = SIBLING;
		break;
	case ID_POPUP_SIBLING_LINKS_STATIC_ROOT:
		pLink = new CdmvStaticRootLinkData;
		enumAddType = SIBLING;
		break;
	case ID_POPUP_PARENT_LINKS_REVOLUTE:
		pLink = new CdmvRevoluteLinkData;
		enumAddType = PARENT;
		break;
	case ID_POPUP_PARENT_LINKS_PRISMATIC:
		pLink = new CdmvPrismaticLinkData;
		enumAddType = PARENT;
		break;
	case ID_POPUP_PARENT_LINKS_MOBILE_BASE:
		pLink = new CdmvMobileBaseLinkData;
		enumAddType = PARENT;
		break;
	case ID_POPUP_PARENT_LINKS_ZSCREW_TX:
		pLink = new CdmvZScrewTxLinkData;
		enumAddType = PARENT;
		break;
	case ID_POPUP_PARENT_LINKS_SPHERICAL:
		pLink = new CdmvSphericalLinkData;
		enumAddType = PARENT;
		break;
	case ID_POPUP_PARENT_LINKS_STATIC_ROOT:
		pLink = new CdmvStaticRootLinkData;
		enumAddType = PARENT;
		break;
	default:
		ASSERT (FALSE);
	}

	ASSERT (pLink);
	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);

	if (enumAddType == CHILD)
	{
		// Then adding child
		if (((CdmvObject*) dwPointer)->GetObjectType () == ARTICULATION)
		{
			((CdmvArticulationData*) GetDocument ()->GetSystemData ())->InsertLinkChild (pLink,
				NULL);
		}
		else
		{
			// link is the parent
			((CdmvArticulationData*) GetDocument ()->GetSystemData ())->InsertLinkChild (pLink,
				(CdmvLinkData*) dwPointer);
		}
	}
	else if (enumAddType == SIBLING)
	{
		// Then adding sibling
		// pick up the parent of the one to add a sibling too.
		HTREEITEM hItemParent = GetTreeCtrl ().GetParentItem (m_hLastHitTreeItem);
		ASSERT (hItemParent);
		DWORD dwPointer = GetTreeCtrl ().GetItemData (hItemParent);
		ASSERT (dwPointer);

		// check if the parent is a link or the articulation htreeitem
		if (((CdmvObject*) dwPointer)->GetObjectType () == LINK)
			((CdmvArticulationData*) GetDocument ()->GetSystemData ())->InsertLinkSibling (pLink,
				(CdmvLinkData*) dwPointer);
		else
			((CdmvArticulationData*) GetDocument ()->GetSystemData ())->InsertLinkSibling (pLink,
				NULL);
	}
	else if (enumAddType == PARENT)
	{
		// Then adding parent
		((CdmvArticulationData*) GetDocument ()->GetSystemData ())->InsertLinkAsParent
			(pLink,
			(CdmvLinkData*) dwPointer);
	}
	else
	{
		ASSERT (FALSE);
	}
	// Clear the selected links - this needs to be done first, because the call to 
	// DeleteAllItems sometimes causes an OnSelChange event which will get confuse
	// when it tries to unselect something it has already deleted
	m_hSelectedItem  = NULL;

	// After inserting the link in the data redisplay the tree.  This is an 
	// inefficient method and should be changed to directly adding it to the
	// current tree when time allows.
	BOOL bReturnStatus = GetTreeCtrl ().DeleteAllItems ();
	ASSERT (bReturnStatus);
	LoadNewTree ();
	// Also reset the WTK view
#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_WTKGraphics.CreateArticulationNodes (
		dynamic_cast <CdmvArticulationData*> (GetDocument ()->GetSystemData ()));
#endif
}

void CDMTreeView::OnPopupDelete ()
{
	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);

	// Note that if it is a closed loop, the current implementation will remove all secondary joint that
	// are connected to the deleted link too.
	ASSERT (((CdmvObject*) dwPointer)->GetObjectType () == LINK);
	((CdmvArticulationData*) GetDocument ()->GetSystemData ())->DeleteLink ((CdmvLinkData*) dwPointer);
	
	// The link that was just deleted was selected, so reset the selected item
	m_hLastHitTreeItem = NULL;

	// After deleting the link redisplay the tree.  This is an 
	// inefficient method and should be changed to directly removing it to the
	// current tree when time allows.
	LoadNewTree ();
	// Also reset the WTK view
#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_WTKGraphics.CreateArticulationNodes (
		dynamic_cast <CdmvArticulationData*> (GetDocument ()->GetSystemData ()));
#endif
}

void CDMTreeView::OnPopupDeleteRecursively ()
{
	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);

	if (((CdmvObject*) dwPointer)->GetObjectType () == ARTICULATION)
	{
		AfxMessageBox ("Not currently supported.");
		return;
	}
	else
	{
		((CdmvArticulationData*) GetDocument ()->GetSystemData ())->DeleteLinkRecursively 
			((CdmvLinkData*) dwPointer);
	}

	
	// The link that was just deleted was selected, so reset the selected item
	m_hLastHitTreeItem = NULL;

	// Clear the selected links - this needs to be done first, because the call to 
	// DeleteAllItems sometimes causes an OnSelChange event which will get confuse
	// when it tries to unselect something it has already deleted
	m_hSelectedItem  = NULL;

	// After inserting the link in the data redisplay the tree.  This is an 
	// inefficient method and should be changed to directly adding it to the
	// current tree when time allows.
	BOOL bReturnStatus = GetTreeCtrl ().DeleteAllItems ();
	ASSERT (bReturnStatus);
	LoadNewTree ();
	// Also reset the WTK view
#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_WTKGraphics.CreateArticulationNodes (
		dynamic_cast <CdmvArticulationData*> (GetDocument ()->GetSystemData ()));
#endif
}



void CDMTreeView::OnRButtonDown(UINT nFlags, CPoint point) 
{
// I have a problem that I can't seem to solve, so this is temporary work around.
// The problem occurs when a tree item is selected via a right click, but then
// another right click is used to select another tree item.  When this occurs, 
// the original tree item gets stuck in some always select mode and other tree
// items can't be selected.  As a workaround, I ignore all right clicks (at this 
// level because it didn't work at the tree level) when the popup menu is displayed.
	
	if (!m_bPopupDisplayedNow)
		CTreeView::OnRButtonDown(nFlags, point);
}

BOOL CDMTreeView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// filter out commands from the add child and add sibling popup menus
	switch LOWORD (wParam)
	{
	case ID_POPUP_LINKS_REVOLUTE:
	case ID_POPUP_LINKS_PRISMATIC:
	case ID_POPUP_LINKS_MOBILE_BASE:
	case ID_POPUP_LINKS_ZSCREW_TX:
	case ID_POPUP_LINKS_SPHERICAL:
	case ID_POPUP_LINKS_STATIC_ROOT:
	case ID_POPUP_SIBLING_LINKS_REVOLUTE:
	case ID_POPUP_SIBLING_LINKS_PRISMATIC:
	case ID_POPUP_SIBLING_LINKS_MOBILE_BASE:
	case ID_POPUP_SIBLING_LINKS_ZSCREW_TX:
	case ID_POPUP_SIBLING_LINKS_SPHERICAL:
	case ID_POPUP_SIBLING_LINKS_STATIC_ROOT:
	case ID_POPUP_PARENT_LINKS_REVOLUTE:
	case ID_POPUP_PARENT_LINKS_PRISMATIC:
	case ID_POPUP_PARENT_LINKS_MOBILE_BASE:
	case ID_POPUP_PARENT_LINKS_ZSCREW_TX:
	case ID_POPUP_PARENT_LINKS_SPHERICAL:
	case ID_POPUP_PARENT_LINKS_STATIC_ROOT:
		AddNewLink (LOWORD (wParam));
		break;
	case ID_POPUP_SEC_JOINT_REVOLUTE:
	case ID_POPUP_SEC_JOINT_PRISMATIC:
	case ID_POPUP_SEC_JOINT_SPHERICAL:
		AddNewSecondaryJoint (LOWORD (wParam));
	default:
		break;
	}
	
	return CTreeView::OnCommand(wParam, lParam);
}

void CDMTreeView::InitializeSecondaryJointList(CdmvSystemData* pSystem)
{	
	ASSERT (pSystem);
	ASSERT (((CdmvArticulationData*) pSystem)->GetArticulationType () == CLOSED_ARTICULATION);

	CString strItem = STR_SECONDARY_JOINT_ROOT_LABEL;

	HTREEITEM hItem = GetTreeCtrl ().InsertItem (strItem, N_SECONDARY_JOINT_ROOT_IMAGE, N_SECONDARY_JOINT_ROOT_IMAGE, TVI_ROOT, TVI_LAST);
	ASSERT (hItem);

	// Will need the ability to add secondary joints later, so save the HITEM to a member
	m_hSecondaryJointRoot = hItem;

	// This item doesn't have any data, so make sure it is NULL
	BOOL bReturn = GetTreeCtrl ().SetItemData (hItem, NULL);
	ASSERT (bReturn);

	unsigned int uCounter;
	int nNumberSecJoints = ((CdmvArticulationData*) pSystem)->
		m_arraySecondaryJoints.GetSize ();
	for (uCounter = 0; uCounter < nNumberSecJoints; uCounter++)
	{
		AddSecondaryJoint (
			((CdmvArticulationData*) pSystem)->m_arraySecondaryJoints.GetAt (uCounter),
			hItem);
	}
}

HTREEITEM CDMTreeView::AddSecondaryJoint(CdmvSecJointData *pSecJoint, HTREEITEM hParent)
{
	CString strSecJointTitle;
	HTREEITEM hSecondaryJoint;
	BOOL bReturn;

	switch (pSecJoint->GetSecondaryJointType ())
	{
	case SEC_PRISMATIC:
		strSecJointTitle = pSecJoint->GetName ();
		hSecondaryJoint = GetTreeCtrl ().InsertItem (strSecJointTitle, N_SECONDARY_PRISMATIC_IMAGE,
			N_SECONDARY_PRISMATIC_IMAGE, hParent);
		ASSERT (hSecondaryJoint);
		// Set the item data for the new tree item.
		bReturn = GetTreeCtrl ().SetItemData (hSecondaryJoint, (DWORD) pSecJoint);
		ASSERT (bReturn);
		break;
	case SEC_REVOLUTE:
		strSecJointTitle = pSecJoint->GetName ();
		hSecondaryJoint = GetTreeCtrl ().InsertItem (strSecJointTitle, N_SECONDARY_REVOLUTE_IMAGE,
			N_SECONDARY_REVOLUTE_IMAGE, hParent);
		ASSERT (hSecondaryJoint);
		// Set the item data for the new tree item.
		bReturn = GetTreeCtrl ().SetItemData (hSecondaryJoint, (DWORD) pSecJoint);
		ASSERT (bReturn);
		break;
	case SEC_SPHERICAL:
		strSecJointTitle = pSecJoint->GetName ();
		hSecondaryJoint = GetTreeCtrl ().InsertItem (strSecJointTitle, N_SECONDARY_SPHERICAL_IMAGE,
			N_SECONDARY_SPHERICAL_IMAGE, hParent);
		ASSERT (hSecondaryJoint);
		// Set the item data for the new tree item.
		bReturn = GetTreeCtrl ().SetItemData (hSecondaryJoint, (DWORD) pSecJoint);
		ASSERT (bReturn);
		break;

	default:
		AfxMessageBox ("Secondary joint type not implemented for tree item add", MB_OK);
		hSecondaryJoint = NULL;
	}

	// for now to expand
	GetTreeCtrl ().EnsureVisible (hSecondaryJoint);
	return hSecondaryJoint;
}


void CDMTreeView::OnPopupSecJointProperties ()
{
	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);
	ASSERT (((CdmvObject*) dwPointer)->GetObjectType () == SECONDARY_JOINT);

	switch (((CdmvSecJointData*) dwPointer)->GetSecondaryJointType ())
	{
	case SEC_SPHERICAL:
		{
			CPSheetSecSphericalJoint psheet ("Secondary Spherical Joint");
			psheet.m_pCdmvSecSpherJntData = ((CdmvSecSpherJntData*) dwPointer);
			psheet.m_pCdmvArticulationData = (CdmvArticulationData*) (GetDocument ()->GetSystemData ());
			if (psheet.DoModal () == IDOK)
			{
				// Reset the label
				BOOL bReturn = GetTreeCtrl ().SetItemText (m_hLastHitTreeItem, 
					((CdmvSecSpherJntData*) dwPointer)->GetName ());
				ASSERT (bReturn);
			}
		}
		break;
	case SEC_REVOLUTE:
		{
			CPSheetSecRevoluteJoint psheet ("Secondary Revolute Joint");
			psheet.m_pCdmvSecRevJntData = ((CdmvSecRevJntData*) dwPointer);
			psheet.m_pCdmvArticulationData = (CdmvArticulationData*) (GetDocument ()->GetSystemData ());
			if (psheet.DoModal () == IDOK)
			{
				// Reset the label
				BOOL bReturn = GetTreeCtrl ().SetItemText (m_hLastHitTreeItem,  
					((CdmvSecRevJntData*) dwPointer)->GetName ());
				ASSERT (bReturn);
			}
		}
		break;
	case SEC_PRISMATIC:
		{
			CPSheetSecPrismaticJoint psheet ("Secondary Prismatic Joint");
			psheet.m_pCdmvSecPrisJntData = ((CdmvSecPrisJntData*) dwPointer);
			psheet.m_pCdmvArticulationData = (CdmvArticulationData*) (GetDocument ()->GetSystemData ());
			if (psheet.DoModal () == IDOK)
			{
				// Reset the label
				BOOL bReturn = GetTreeCtrl ().SetItemText (m_hLastHitTreeItem, 
					((CdmvSecPrisJntData*) dwPointer)->GetName ());
				ASSERT (bReturn);
			}
		}
		break;
	default:
		ASSERT (FALSE);
		break;
	}

}

void CDMTreeView::OnPopupSecJointDelete ()
{
	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);

	if (((CdmvObject*) dwPointer)->GetObjectType () != SECONDARY_JOINT)
	{
		// It is only expected that this function will be called on a secondary joint
		ASSERT (FALSE);
		return;
	}
	else
	{
		((CdmvArticulationData*) GetDocument ()->GetSystemData ())->DeleteSecJoint ((CdmvSecJointData*) dwPointer);
	}

	// After deleting the joint, redisplay the tree.  This is an 
	// inefficient method and should be changed when time allows.
//	BOOL bReturnStatus = GetTreeCtrl ().DeleteAllItems ();
//	ASSERT (bReturnStatus);
	LoadNewTree ();
	// Note that the static view is unaffected by secondary joints.
}

void CDMTreeView::AddNewSecondaryJoint(WORD wdID)
{
	CdmvSecJointData* pSecJoint;

	switch (wdID)
	{
	case ID_POPUP_SEC_JOINT_REVOLUTE:
		pSecJoint = new CdmvSecRevJntData;
		break;
	case ID_POPUP_SEC_JOINT_PRISMATIC:
		pSecJoint = new CdmvSecPrisJntData;
		break;
	case ID_POPUP_SEC_JOINT_SPHERICAL:
		pSecJoint = new CdmvSecSpherJntData;
		break;
	default:
		ASSERT (FALSE);
	}

	ASSERT (pSecJoint);
	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);

	// Set Link A and Link B to the link that the context menu was hit on.
	// The user can change the link setting if desired from the properities menu
	pSecJoint->SetLinkA (
		(CdmvArticulationData*) (GetDocument ()->GetSystemData ()),
		(CdmvLinkData*) dwPointer);
	pSecJoint->SetLinkB (
		(CdmvArticulationData*) (GetDocument ()->GetSystemData ()),
		(CdmvLinkData*) dwPointer);

	((CdmvArticulationData*) GetDocument ()->GetSystemData ())->AddSecJoint (pSecJoint);
	

	// Clear the selected links - this needs to be done first, because the call to 
	// DeleteAllItems sometimes causes an OnSelChange event which will get confuse
	// when it tries to unselect something it has already deleted
	m_hSelectedItem  = NULL;

	// After inserting the link in the data redisplay the tree.  This is an 
	// inefficient method and should be changed to directly adding it to the
	// current tree when time allows.
	BOOL bReturnStatus = GetTreeCtrl ().DeleteAllItems ();
	ASSERT (bReturnStatus);
	LoadNewTree ();
	// Note that it is not necessary to redisplay the WTK view since there are no visual changes
	// but it is done so that the bounding box of the selected link can be reset.
#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_WTKGraphics.CreateArticulationNodes (
		dynamic_cast <CdmvArticulationData*> (GetDocument ()->GetSystemData ()));
#endif
}


void CDMTreeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CDMViewerDoc* pDoc = dynamic_cast <CDMViewerDoc*> (GetDocument ());
	ASSERT (pDoc);

	pDoc->KeyDown (nChar, nRepCnt, nFlags);
	
	CTreeView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDMTreeView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	*pResult = 0;
}

void CDMTreeView::OnEditCopylink() 
{
	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);
	
	// Get a copy of the link
	CdmvLinkData *pLinkCopy = NULL;
	((CdmvArticulationData*) GetDocument ()->GetSystemData ())->CopyLink ((CdmvLinkData*) dwPointer,
		&pLinkCopy);
	ASSERT (pLinkCopy);

	// Check to see if the link clipboard is already in use and if so clear it
	CdmvLinkData * pLinkClipboard = GetDocument ()->GetClipboardData ();
	if (pLinkClipboard)
	{
		delete pLinkClipboard;
	}


	GetDocument ()->SetClipboardData (pLinkCopy);
}

void CDMTreeView::OnEditPastelinkaschild() 
{
	// Assume this will only be called if there is something on the clipboard
	ASSERT (GetDocument ()->GetClipboardData ());

	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);

	// Then adding child
	if (((CdmvObject*) dwPointer)->GetObjectType () == ARTICULATION)
	{
		((CdmvArticulationData*) GetDocument ()->GetSystemData ())->InsertLinkChild (GetDocument ()->GetClipboardData (),
			NULL);
	}
	else
	{
		// link is the parent
		((CdmvArticulationData*) GetDocument ()->GetSystemData ())->InsertLinkChild (GetDocument ()->GetClipboardData (),
			(CdmvLinkData*) dwPointer);
	}

	// Now the link is a part of articulation, so need to get a copy of it to keep on the 
	// clipboard.
	CdmvLinkData *pLinkCopy = NULL;
	((CdmvArticulationData*) GetDocument ()->GetSystemData ())->CopyLink (GetDocument ()->GetClipboardData (),
		&pLinkCopy);
	ASSERT (pLinkCopy);
	// Place the new copy on the clipboard, but don't deallocate the old, because it is now
	// a member of the articulation
	GetDocument ()->SetClipboardData (pLinkCopy);

	// Clear the selected links - this needs to be done first, because the call to 
	// DeleteAllItems sometimes causes an OnSelChange event which will get confuse
	// when it tries to unselect something it has already deleted
	m_hSelectedItem  = NULL;

	// After inserting the link in the data redisplay the tree.  This is an 
	// inefficient method and should be changed to directly adding it to the
	// current tree when time allows.
	BOOL bReturnStatus = GetTreeCtrl ().DeleteAllItems ();
	ASSERT (bReturnStatus);
	LoadNewTree ();
	// Also reset the WTK view
#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_WTKGraphics.CreateArticulationNodes (
		dynamic_cast <CdmvArticulationData*> (GetDocument ()->GetSystemData ()));
#endif
	
}

void CDMTreeView::OnEditCutlink() 
{
	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);

	// Check to see if the link clipboard is already in use and if so clear it
	if (GetDocument ()->GetClipboardData ())
	{
		delete GetDocument ()->GetClipboardData ();
	}
	
	// Save the pointer to the clipboard
	GetDocument ()->SetClipboardData ((CdmvLinkData*) dwPointer);

	// Note that if it is a closed loop, the current implementation will remove all secondary joint that
	// are connected to the deleted link too.
	ASSERT (((CdmvObject*) dwPointer)->GetObjectType () == LINK);
	((CdmvArticulationData*) GetDocument ()->GetSystemData ())->CutLink ((CdmvLinkData*) dwPointer);
	
	// The link that was just deleted was selected, so reset the selected item
	m_hLastHitTreeItem = NULL;	

	// After deleting the link redisplay the tree.  This is an 
	// inefficient method and should be changed to directly removing it to the
	// current tree when time allows.
	LoadNewTree ();
	// Also reset the WTK view
#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_WTKGraphics.CreateArticulationNodes (
		dynamic_cast <CdmvArticulationData*> (GetDocument ()->GetSystemData ()));
#endif	
}

void CDMTreeView::OnEditPastelinkassibling() 
{
	// Assume this will only be called if there is something on the clipboard
	ASSERT (GetDocument ()->GetClipboardData ());

	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);

	// Then adding sibling
	if (((CdmvObject*) dwPointer)->GetObjectType () == ARTICULATION)
	{
		((CdmvArticulationData*) GetDocument ()->GetSystemData ())->InsertLinkSibling (GetDocument ()->GetClipboardData (),
			NULL);
	}
	else
	{
		// pick up the parent of the one to add a sibling too.
		HTREEITEM hItemParent = GetTreeCtrl ().GetParentItem (m_hLastHitTreeItem);
		ASSERT (hItemParent);
		DWORD dwPointer = GetTreeCtrl ().GetItemData (hItemParent);
		ASSERT (dwPointer);

		// check if the parent is a link or the articulation htreeitem
		if (((CdmvObject*) dwPointer)->GetObjectType () == LINK)
			((CdmvArticulationData*) GetDocument ()->GetSystemData ())->InsertLinkSibling (GetDocument ()->GetClipboardData (),
				(CdmvLinkData*) dwPointer);
		else
			((CdmvArticulationData*) GetDocument ()->GetSystemData ())->InsertLinkSibling (GetDocument ()->GetClipboardData (),
				NULL);

	}	

	// Now the link is a part of articulation, so need to get a copy of it to keep on the 
	// clipboard.
	CdmvLinkData *pLinkCopy = NULL;
	((CdmvArticulationData*) GetDocument ()->GetSystemData ())->CopyLink (GetDocument ()->GetClipboardData (),
		&pLinkCopy);
	ASSERT (pLinkCopy);
	// Place the new copy on the clipboard, but don't deallocate the old, because it is now
	// a member of the articulation
	GetDocument ()->SetClipboardData (pLinkCopy);

	// Clear the selected links - this needs to be done first, because the call to 
	// DeleteAllItems sometimes causes an OnSelChange event which will get confuse
	// when it tries to unselect something it has already deleted
	m_hSelectedItem  = NULL;

	// After inserting the link in the data redisplay the tree.  This is an 
	// inefficient method and should be changed to directly adding it to the
	// current tree when time allows.
	BOOL bReturnStatus = GetTreeCtrl ().DeleteAllItems ();
	ASSERT (bReturnStatus);
	LoadNewTree ();
	// Also reset the WTK view
#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_WTKGraphics.CreateArticulationNodes (
		dynamic_cast <CdmvArticulationData*> (GetDocument ()->GetSystemData ()));
#endif
	
	

}

void CDMTreeView::OnEditPastelinkasparent() 
{
	// Assume this will only be called if there is something on the clipboard
	ASSERT (GetDocument ()->GetClipboardData ());

	DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hLastHitTreeItem);
	ASSERT (dwPointer);

	// Add the link to the articulation	
	((CdmvArticulationData*) GetDocument ()->GetSystemData ())->InsertLinkAsParent (GetDocument ()->GetClipboardData (),
			(CdmvLinkData*) dwPointer);

	// Now the link is a part of articulation, so need to get a copy of it to keep on the 
	// clipboard.
	CdmvLinkData *pLinkCopy = NULL;
	((CdmvArticulationData*) GetDocument ()->GetSystemData ())->CopyLink (GetDocument ()->GetClipboardData (),
		&pLinkCopy);
	ASSERT (pLinkCopy);
	// Place the new copy on the clipboard, but don't deallocate the old, because it is now
	// a member of the articulation
	GetDocument ()->SetClipboardData (pLinkCopy);

	// Clear the selected links - this needs to be done first, because the call to 
	// DeleteAllItems sometimes causes an OnSelChange event which will get confuse
	// when it tries to unselect something it has already deleted
	m_hSelectedItem  = NULL;

	// After inserting the link in the data redisplay the tree.  This is an 
	// inefficient method and should be changed to directly adding it to the
	// current tree when time allows.
	BOOL bReturnStatus = GetTreeCtrl ().DeleteAllItems ();
	ASSERT (bReturnStatus);
	LoadNewTree ();
	// Also reset the WTK view
#ifdef WTK_LICENSE_AVAILABLE
	GetWTKView ()->m_WTKGraphics.CreateArticulationNodes (
		dynamic_cast <CdmvArticulationData*> (GetDocument ()->GetSystemData ()));
#endif
	
	

}


void CDMTreeView::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}



void CDMTreeView::ClearBoundingBoxOnSelectedItem()
{
	// Check that it is valid -- it is invalid if nothing has been selected yet
	if (m_hSelectedItem)
	{
		DWORD dwPointer = GetTreeCtrl ().GetItemData (m_hSelectedItem);
		
		// Make sure it is valid - it might have been deleted or something
		if (dwPointer != NULL)
		{
			if ( ((CdmvObject*) dwPointer)->GetObjectType () == LINK)
			{
//				unsigned int nLinkUID = ((CdmvLinkData*) dwPointer)->GetLinkUID ();
//				CString strLabel;
//				strLabel.Format ("%d", nLinkUID);
#ifdef WTK_LICENSE_AVAILABLE
				GetWTKView ()->m_WTKGraphics.IndicateSelectedModel (
					reinterpret_cast <CdmvObject*> (dwPointer), FALSE);
#endif
			}
		}
	}
}

void CDMTreeView::OnPopupShowAxes ()
{
	// It is assumed that this will only be called if there is an item selected
	ASSERT (m_hLastHitTreeItem);

	// Get pointer to data of selected item
	CdmvObject* pObject = reinterpret_cast <CdmvObject*> (GetTreeCtrl().GetItemData 
		(m_hLastHitTreeItem));
	// Valid data should be there
	ASSERT (AfxIsValidAddress (pObject, sizeof (CdmvObject), TRUE));

	// Toggle the axes state
	if (pObject->ShowWtkAxes ())
		pObject->ShowWtkAxes (FALSE);
	else
		pObject->ShowWtkAxes (TRUE);

}

void CDMTreeView::OnPopupCameraCoi ()
{
	// It is assumed that this will only be called if there is an item selected
	ASSERT (m_hLastHitTreeItem);

	// Get pointer to data of selected item
	CdmvObject* pObject = reinterpret_cast <CdmvObject*> (GetTreeCtrl().GetItemData 
		(m_hLastHitTreeItem));
	// Valid data should be there
	ASSERT (AfxIsValidAddress (pObject, sizeof (CdmvObject), TRUE));

	// Clear the current center of interest
	dynamic_cast <CdmvArticulationData*>(GetDocument ()->GetSystemData ())->
		ClearCameraCenterOfInterest ();

	// Clear the inertial center of interest in the cfg
	GetDocument()->GetCFGData()->SetInertialAxesAsCoi(FALSE);

	// Clear the current center of interest offset
	GetDocument()->GetCameraData()->ClearCenterOfInterestOffset();

	// Set the state
	pObject->IsCameraCenterOfInterest (TRUE);

	// Update the camera
	GetWTKView ()->m_WTKGraphics.UpdateCamera (FALSE);
}
