// ExamineView.h: interface for the CExamineView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERACONTROL_H__B99955D5_BF54_11D2_BBE8_00C04F960CF3__INCLUDED_)
#define AFX_CAMERACONTROL_H__B99955D5_BF54_11D2_BBE8_00C04F960CF3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <wt.h>

#define EV_THETA	0
#define EV_PHI		1
#define EV_RAD		2

class CCameraControl  
{
private:
	/// Center of sphere in examine view
	WTp3 m_wtp3ExamineCOI;
	/// Polar coordinate of a point on the sphrere
	WTp3 m_wtp3ExamineSphericalCoord;
	/// Rotation, pan, and zoom scale factors
	double m_dRotationScale, m_dZoomScale, m_dPanScale; 
	// Max and Min sphere radius
	double m_dMinRadius, m_dMaxRadius; 
	// Sensor to be used, assumed a mouse
	WTsensor *m_pwtSensor; 
	// Viewpoint to update
	WTviewpoint *m_pwtViewpoint; 

protected:
	void Rotate (double dMouseX, double dMouseY, double dMouseRate,
					int nWindowPosX, int nWindowPosY, int nWindowWidth, int nWindowHeight);
	void Pan (double dMouseX, double dMouseY, double dMouseRate,
					int nWindowPosX, int nWindowPosY, int nWindowWidth, int nWindowHeight);
	void OrientExamineView();
	void Zoom (double dMouseY, int nWindowPosY, int nWindowHeight,
					BOOL bPanMode);

public:
	void UpdatePanView2(void);
	void UpdateExamineView2(WTp3 wtp3Center);
	void UpdateCameraDirectedLight ();
	CCameraControl(WTsensor *mouse, WTviewpoint *view);
	void UpdateExamineView (WTp3 wtp3Center);
	void UpdateExamineView (int nWndPosX, int nWndPosY,
					int nWndWidth, int nWndHeight, BOOL bLeftButton, BOOL bRightButton,
					double dMousePosX, double dMousePosY);
	void UpdateExamineView2 (int nWndPosX, int nWndPosY,
					int nWndWidth, int nWndHeight, BOOL bLeftButton, BOOL bRightButton,
					double dMousePosX, double dMousePosY);
	void UpdatePanView (int nWndPosX, int nWndPosY,
					int nWndWidth, int nWndHeight, BOOL bLeftButton, BOOL bRightButton,
					double dMousePosX, double dMousePosY);
	void RecalculateExamineViewParameters (WTp3 wtp3Center);

	virtual ~CCameraControl();

};

#endif // !defined(AFX_CAMERACONTROL_H__B99955D5_BF54_11D2_BBE8_00C04F960CF3__INCLUDED_)
