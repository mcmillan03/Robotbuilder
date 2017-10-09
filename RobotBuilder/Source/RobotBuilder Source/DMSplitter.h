// DMSplitter.h: interface for the CDMSplitter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMSPLITTER_H__B3D22D51_1033_11D4_8426_00C04F666666__INCLUDED_)
#define AFX_DMSPLITTER_H__B3D22D51_1033_11D4_8426_00C04F666666__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDMSplitter : public CSplitterWnd
{
public:
	CDMSplitter();
	virtual ~CDMSplitter();

   BOOL ReplaceView(int row, int col,CRuntimeClass * pViewClass);
protected:
	int m_nTreeViewPrevWidth;
};

#endif // !defined(AFX_DMSPLITTER_H__B3D22D51_1033_11D4_8426_00C04F666666__INCLUDED_)
