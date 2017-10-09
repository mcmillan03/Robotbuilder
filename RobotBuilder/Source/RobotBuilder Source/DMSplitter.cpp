// DMSplitter.cpp: implementation of the CDMSplitter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "DMSplitter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDMSplitter::CDMSplitter()
{
	m_nTreeViewPrevWidth = 0;
}

CDMSplitter::~CDMSplitter()
{

}

BOOL CDMSplitter::ReplaceView(int row, int col,CRuntimeClass * pViewClass)
{
	CCreateContext context;
	BOOL bSetActive;
		   

	if ((GetPane(row,col)->IsKindOf(pViewClass))==TRUE)
	   return FALSE;
					
	// Get pointer to CDocument object so that it can be used in the creation 
	// process of the new view
	CDocument * pDoc= ((CView *)GetPane(row,col))->GetDocument();
	CView * pActiveView=GetParentFrame()->GetActiveView();
	if (pActiveView==NULL || pActiveView==GetPane(row,col))
	  bSetActive=TRUE;
	else
	  bSetActive=FALSE;

	// set flag so that document will not be deleted when view is destroyed
	pDoc->m_bAutoDelete=FALSE;    
	// Delete existing view 
	((CView *) GetPane(row,col))->DestroyWindow();
	// set flag back to default 
	pDoc->m_bAutoDelete=TRUE;

	// Create new view                      
	context.m_pNewViewClass=pViewClass;
	context.m_pCurrentDoc=pDoc;
	context.m_pNewDocTemplate=NULL;
	context.m_pLastView=NULL;
	context.m_pCurrentFrame=NULL;

	// Set the size as the same size as the current view
	SIZE size;
	size.cx = m_pColInfo[0].nCurSize; // Pick up the current width
	size.cy = 10; // Arbitrarly set - will size to window

	CreateView(row,col,pViewClass,size, &context);

	CView * pNewView= (CView *)GetPane(row,col);

	if (bSetActive==TRUE)
	  GetParentFrame()->SetActiveView(pNewView);

	RecalcLayout(); 
	GetPane(row,col)->SendMessage(WM_PAINT);

	return TRUE;
}

