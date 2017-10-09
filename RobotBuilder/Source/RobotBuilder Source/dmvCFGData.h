// dmvCFGData.h: interface for the CdmvCFGData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVCFGDATA_H__8FDBFAEE_4FC5_437D_A15E_2C655456A95E__INCLUDED_)
#define AFX_DMVCFGDATA_H__8FDBFAEE_4FC5_437D_A15E_2C655456A95E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wt.h"

enum INTEGRATOR_TYPE {INTEGRATOR_EULER, INTEGRATOR_RUNGE_KUTTA_4,
	INTEGRATOR_ADAPTIVE_4_5_RUNGE_KUTTA, INTEGRATOR_PLACEMENT};

typedef struct
{
	CString strArticulationFile;
	CString strArticulationPath;
	CString strControlDLL;
	CString strControlPath;
} structArticulationAndControlFilePair;

typedef CArray <structArticulationAndControlFilePair, structArticulationAndControlFilePair&>
	ArticulationAndControlFileArray;

#define MINIMUM_CONTROL_STEP_SIZE	.0001	// smallest control step supported by system
#define MAXIMUM_CONTROL_STEP_SIZE	1000.0	// 
#define MINIMUM_DISPLAY_RATE	1
#define MAXIMUM_DISPLAY_RATE	1000
#define MINIMUM_EULER_STEP_SIZE		.000001
#define MAXIMUM_EULER_STEP_SIZE		1.0
#define MINIMUM_RK4_STEP_SIZE .0000001
#define MAXIMUM_RK4_STEP_SIZE	1.0
#define MINIMUM_RK45_EPSILON .000001
#define MAXIMUM_RK45_EPSILON	1.0
#define MINIMUM_RK45_MINIMUM_STEP_SIZE	.000001
#define MAXIMUM_RK45_MINIMUM_STEP_SIZE		1.0
#define MINIMUM_AXES_LENGTH	.000001
#define MAXIMUM_AXES_LENGTH	1.0e6
#define MINIMUM_AXES_WIDTH	1
#define MAXIMUM_AXES_WIDTH	1000000



class CdmvCFGData  
{
public:
	void GetPosition(WTp3 wtp3) const;
	void GetOrientation(WTq wtq) const;
	void ResetDataChanged();
	BOOL DataHasChanged();
  /*BOOL GetLogoLoadFlag();
  void SetLogoLoadFlag();*/
	void SetOrientationPosition(WTp3 wtp3Pos);
	void SetOrientationQuaternion(WTq wtqQuat);
	void SetBackgroundColor (COLORREF crBackgroundColor);
	COLORREF GetBackgroundColor () const;
	void SetLinkAxesData (int nWidth, double dLength);
	void SetInertialAxesData (int nWidth, double dLength);
	void GetInertialAxesData (int &rnWidth, double &rdLength) const; 
	void GetLinkAxesData (int &rnWidth, double &rdLength) const; 
	void SetFirstArticulationFile (CString strArticulationFile, CString strArticulationPath);
	void GetFirstArticulationFile (CString &rstrArticulationFile, CString &rstrArticulationPath) const;
	void SetFirstControlFile (CString strControlFile, CString strControlPath);
	void GetFirstControlFile (CString &rstrControlFile, CString &rstrControlPath) const;
	void SetRealTime (BOOL bDoRealTime);
	void AddArticulationFileAndControlFile (CString strArticulationFile, CString strArticulationPath,
		CString strControlFile, CString strControlPath);
	void ClearArticulationFileAndControlFileList ();
	void SetIntegratorAdaptive45RungeKuttaParameters  (double dEpsilon, double dMinimumStepSize);
	void SetIntegratorRungeKutta4Parameters (double dStepSize);
	void SetIntegratorEulerParameters (double dStepSize);
	void SetIntegratorType (INTEGRATOR_TYPE eIntegrator);
	void SetEnvironmentFile (CString strEnvironmentFile, CString strEnvironmentPath);
	void SetSimulationDisplayRate (int nRate);
	void SetControlStepSize (double dControlStepSize);
	void SetInertialAxesAsCoi(BOOL bInertialAxesAsCoi);
	void SetCoiOffset (double dCoiOffsetX, double dCoiOffsetY, double dCoiOffsetZ);
	void SetUseInertialZ(BOOL bUseInertialZ);
	void SetCenterOfInterestName(CString strCenterOfInterestName);
  void SetViewAngle_Degree (double dViewAngleDeg);
	CdmvCFGData();
	virtual ~CdmvCFGData();

	BOOL GetRealTime () const {return m_bRealTime;}
	const ArticulationAndControlFileArray& GetArticulationAndControlFileArray () const 
		{return m_ArticulationAndControlFileArray;}
	void GetIntegratorAdaptive45RungeKuttaParameters  (double *pdEpsilon, double *pdMinimumStepSize) const
	{*pdEpsilon = m_dRungeKutta45Epsilon; *pdMinimumStepSize = m_dRungeKutta45MinimumStepSize;}
	double GetIntegratorRungeKutta4Parameters () const {return m_dRungeKutta4StepSize;}
	double GetIntegratorEulerParameters () const {return m_dEulerStepSize;}
	INTEGRATOR_TYPE GetIntegratorType () const {return m_IntegratorType;}
	void GetEnvironmentFile (CString &rstrEnvironmentFile, CString &rstrEnvironmentPath) const 
		{rstrEnvironmentFile = m_strEnvironmentFile; rstrEnvironmentPath = m_strEnvironmentPath;}
	int GetSimulationDisplayRate () const {return m_nRate;}
	double GetControlStepSize () const {return m_dControlStepSize;}
	BOOL GetInertialAxesAsCoi() const {return m_bInertialAxesAsCoi;}
	void GetCoiOffset (double *pdCoiOffsetX, double *pdCoiOffsetY, double *pdCoiOffsetZ) const
	{*pdCoiOffsetX = m_dCoiOffsetX; *pdCoiOffsetY = m_dCoiOffsetY; *pdCoiOffsetZ = m_dCoiOffsetZ;}
	BOOL GetUseInertialZ() const {return m_bUseInertialZ;}
	CString GetCenterOfInterestName() const {return m_strCenterOfInterest;}
  void GetViewAngle_Degree (double *pdViewAngle) const
	{*pdViewAngle = m_dViewAngleDeg;}
	
protected:
	/// Array of articulation and control pairs.  The program should be able
	/// to support multiple articulations and each one needs a control.
	ArticulationAndControlFileArray m_ArticulationAndControlFileArray;
	/// Control step size
	double m_dControlStepSize;
	/// Display rate (multiple of the control step size)
	int m_nRate;
	/// Holds the value of the environment file for the current CFG
	CString m_strEnvironmentFile;
	/// Holds the path the the environment file for the current CFG
	CString m_strEnvironmentPath;
	/// Holds whether the simulation slows to real time
	BOOL m_bRealTime;
	/// Euler stepsize
	double m_dEulerStepSize;
	/// Runge-Kutta 4th order step size
	double m_dRungeKutta4StepSize;
	/// The integrator type
	INTEGRATOR_TYPE m_IntegratorType;
	/// 4th/5th order adaptive step size Runge Kutta epsilon (steps over discontinuties)
	double m_dRungeKutta45Epsilon ;
	/// 4th/5th order adaptive step size Runge Kutta minimum step size
	double m_dRungeKutta45MinimumStepSize;
	/// Inertial axes 2D line overlay width (in pixels)
	int m_nInertialAxesWidth;
	/// The length of the inertial axes (in universe units)
	double m_dInertialAxesLength;
	/// Link axes 2D line overlay width (in pixels)
	int m_nLinkAxesWidth;
	/// The length of the link axes (in universe units)
	double m_dLinkAxesLength;
	/// Background color of WTK graphics window
	COLORREF m_crBackgroundColor;
	/// Center of Interest
	CString m_strCenterOfInterest;
	/// Center of Interest Offsets
	double m_dCoiOffsetX, m_dCoiOffsetY, m_dCoiOffsetZ;
	/// Holds whether the Inertial Axis is the center of interest
	BOOL m_bInertialAxesAsCoi;
	/// Holds whether Z of Inertial Axes is used for center of interest
	/// to prevent the terrain from "bouncing"
	BOOL m_bUseInertialZ;
	/// ViewAngle Degree
	double m_dViewAngleDeg;
	/// These ALWAYS stay in synch with what's actually in the
	/// configuration file so that the "Reset" functionality
	/// can be implemented
	WTq m_wtqQuat;
	WTp3 m_wtp3Pos;
	BOOL m_bDataChanged;
  //int m_bLogoLoaded;
};

#endif // !defined(AFX_DMVCFGDATA_H__8FDBFAEE_4FC5_437D_A15E_2C655456A95E__INCLUDED_)
