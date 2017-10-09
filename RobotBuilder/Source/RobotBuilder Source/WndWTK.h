#if !defined(AFX_WNDWTK_H__A30D5B1F_CD44_11D3_8411_F7B460660733__INCLUDED_)
#define AFX_WNDWTK_H__A30D5B1F_CD44_11D3_8411_F7B460660733__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WndWTK.h : header file
//
#include "wt.h"
#include "CameraControl.h"
/////////////////////////////////////////////////////////////////////////////
// CWndWTK window

class CWndWTK : public CWnd
{
// Construction
public:
	CWndWTK();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndWTK)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetViewpointPosition(WTp3 wtp3Pos);
	void GetViewpointPosition(WTp3 wtp3Pos);
	void GetViewpointOrientation(WTq wtqQuat);
	BOOL IsWtkInitialized () const;
	void ZoomViewpoint (BOOL bZoomIn);
	void SetViewpointOrientation (WTq wtqQuat);
	void InitializeWTKWindow ();
	virtual ~CWndWTK();
	static void MyWTKMouseMove (WTsensor* wtSensor);
	CCameraControl* m_pCameraControl;

	// Generated message map functions
protected:
	//{{AFX_MSG(CWndWTK)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT m_nTimerID;
	/// Holds the state if WTK has been initialized (by calling InitializeWTKWindow)
	/// (Even though it is called from OnCreate, there are states when the this window
	/// exists, but WTK has not been initialized
	BOOL m_bWtkInitialized;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDWTK_H__A30D5B1F_CD44_11D3_8411_F7B460660733__INCLUDED_)
