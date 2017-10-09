// CameraData.h: interface for the CCameraData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERADATA_H__1C8D4F27_96C3_413C_A714_BABD6C4A76BA__INCLUDED_)
#define AFX_CAMERADATA_H__1C8D4F27_96C3_413C_A714_BABD6C4A76BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wt.h>

class CCameraData  
{
public:
	void ClearCenterOfInterestOffset();
	void SetUseViewportFrameForExamineView (BOOL bUseViewport);
	BOOL GetUseViewportFrameForExamineView () const;
	BOOL GetViewInPanMode () const;
	void SetViewInPanMode (BOOL bViewInPanMode);
	void SetCenterOfInterestOffset (const WTp3 wtp3Offset);
	void GetCenterOfInterestOffset (WTp3 wtp3Offset) const;
	void GetViewAngleDegree (float ViewAngleDeg) const;
	void SetViewAngleDegree (const float ViewAngleDeg);
	CCameraData();
	virtual ~CCameraData();
private:
  /// View angle degree
  float m_ViewAngleDeg;
	/// Offset from COI - applicable in examine mode
	WTp3 m_wtp3CoiOffset;
	/// Tells if in pan mode or not (examine mode)
	BOOL m_bPanMode;
	/// Tells if the calculations to update the camera position and orientation are
	/// relative to the viewport frame or the inertial frame translated to the COI
	BOOL m_bUseViewportFrameForExamineView;

};

#endif // !defined(AFX_CAMERADATA_H__1C8D4F27_96C3_413C_A714_BABD6C4A76BA__INCLUDED_)
