// DynaMechs.h: interface for the CDynaMechs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNAMECHS_H__8255F551_0711_11D4_8425_00C04F666666__INCLUDED_)
#define AFX_DYNAMECHS_H__8255F551_0711_11D4_8425_00C04F666666__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//typedef dmArticulation CdmvArticulationData;
//typedef dmLink CdmvLinkData;

#include <dm.h>            // DynaMechs typedefs, globals, etc.
#include <dmSystem.hpp>      // DynaMechs simulation code.
#include <dmArticulation.hpp>
#include <dmClosedArticulation.hpp>
#include <dmLink.hpp>
#include <dmEnvironment.hpp>
#include <dmIntegrator.hpp>
#include <dmRigidBody.hpp>
#include <dmMobileBaseLink.hpp>
#include <dmMDHLink.hpp>
#include <dmRevoluteLink.hpp>
#include <dmSecondaryJoint.hpp>
#include "DlgNoDisplayModeStatus.h"
#include "dmvCFGData.h"
#include "dmvSystemData.h"
#include "dmvArticulationData.h"
#include "dmvRigidBodyData.h"
#include "dmvMDHLinkData.h"
#include "dmvRevoluteLinkData.h"
#include "dmvSecJointData.h"
#include "WTKGraphics.h"
#include "PlaybackData.h"
//#include "DMControl.h"

#include <RBUserIOData.h>

class CDynaMechs  
{
public:
	BOOL InitializePlayback (double dStartTime, double dEndTime, 
												CdmvSystemData *pCdmvSystemData,
												CdmvEnvironmentData *pCdmvEnvironmentData,
												CPlaybackData* pPlaybackData);
	void SetCFGDataPointer (const CdmvCFGData* pCdmvCFGData);
	void DontSimulate ();
	double GetSimulationTime () const;
	void SetNoDisplayMode (BOOL bNoDisplayMode);
	BOOL GetNoDisplayMode ();
	void KeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
	void SetPlayerPointer (CWTKGraphics *pPlayer);
	BOOL UpdateSimulation (GraphicsMode theGraphicsMode);
	BOOL UpdateDisplay (GraphicsMode theGraphicsMode);
	int ComputeControl (float time);
	void UninitializeControl ();
	BOOL InitializeDynaMechs (CdmvSystemData *pCdmvSystemData, CdmvEnvironmentData 
							*pCdmvEnvironmentData,	CString strControlDLLFile,
                      RBUserIOData** ppRBUserIOData, CPlaybackData *pPlaybackData);
	CDynaMechs();
	virtual ~CDynaMechs();
 	dmSystem * m_pSystem;
	dmEnvironment* m_pEnvironment;
	BOOL ResetDynaMechs ();
protected:
	void DestroyNoDisplayModeStatusDlg ();
	void CreateNoDisplayModeStatusDlg ();
	CDlgNoDisplayModeStatus* m_pdlgNoDisplayModeStatus;
	BOOL m_bNoDisplayMode;
	BOOL InitializeControl (CString strControlDLLFile);
	dmIntegrator *m_pIntegrator;
	CWTKGraphics* m_pPlayerToolkit;

	HINSTANCE m_hControlDLL;
	int (*DMControlKeyPressFunc)(UINT nChar, int nRepCnt);
	int (*DMControlInitializeFunc)(dmSystem*, RBUserIOData*);
	int (*DMControlComputeControlFunc)(dmSystem*, dmIntegrator*, dmEnvironment*, RBUserIOData*, float);
	int (*DMControlUninitializeFunc)(dmSystem*, RBUserIOData*);

	double m_dSimulationTime;
	int m_nDisplayRate;
	int m_nCurrentDisplayCount;
	double m_dSimulationStepSize;
	DWORD m_dwTickCountAtSimStart;
	BOOL m_bRealTime;

/*	int num_links;
	dmLink **robot_link;
	int *num_dofs;
	Float **desired_joint_pos;*/
private:
	RBUserIOData* m_pRBUserIOData;
	dmEnvironment* LoadEnvironmentDataIntoDynaMechs (CdmvEnvironmentData* pCdmvEnvironmentData);
	void LoadStabilization (CdmvSecJointData *pCdmvSecJointData, dmSecondaryJoint *pdmSecJoint);
	void LoadSecondaryJoint (const CdmvSecJointData* pCdmvSecJointData, dmSecondaryJoint *pdmSecJoint,
		dmClosedArticulation *pdmClosedArticulation);
	void LoadJointFriction (const CdmvLinkData *pCdmvLinkData, dmLink *pdmLink);
	void LoadRevoluteActuator (const CdmvRevoluteLinkData* pCdmvRevoluteLinkData, dmRevoluteLink* pdmRevoluteLink);
	void LoadMDHData (const CdmvMDHLinkData* pCdmvMDHLinkData, dmMDHLink* pdmMDHLink);
	void LoadRigidBody (const CdmvRigidBodyData* pCdmvRigidBodyData, dmRigidBody* pdmRigidBody);
	void LoadArticulationReferenceSystem (const CdmvArticulationData *pCdmvArticulationData, dmArticulation *pdmArticulation);
	void LoadObjectName (const CdmvObject* pCdmvObject, dmObject *pObject);
	dmSystem* LoadDMDataIntoDynaMechs (CdmvSystemData *pCdmvSystemData);
	double m_dLastControlTime;
	double m_dControlStepSize;
	DWORD m_dwDontSimulateStartTime;
	double m_dDontSimulateTotalTime;
	BOOL m_bDontSimulateMode;
	const CdmvCFGData * m_pCdmvCFGData;
	double m_dIntegrationStepSize;
	CdmvSystemData *m_pCdmvSystemData;
	CPlaybackData *m_pPlaybackData;
	BOOL m_bPlaybackMode;
	double m_dPlaybackStopTime;
	double m_dSimulationStartTime;

};

#endif // !defined(AFX_DYNAMECHS_H__8255F551_0711_11D4_8425_00C04F666666__INCLUDED_)
