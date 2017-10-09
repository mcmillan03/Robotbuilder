// DynaMechs.cpp: implementation of the CDynaMechs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DynaMechs.h"
#include "dmIntegPlacement.hpp"
#include "dmIntegRK45.hpp"
#include "dmIntegEuler.hpp"
#include "dmIntegRK4.hpp"
#include "dmClosedArticulation.hpp"
#include "dmStaticRootLink.hpp"
#include "dmRevoluteLink.hpp"
#include "dmContactModel.hpp"
#include "dmRevDCMotor.hpp"
#include "dmPrismaticLink.hpp"
#include "dmSphericalLink.hpp"
#include "dmZScrewTxLink.hpp"
#include "dmSecondaryRevoluteJoint.hpp"
#include "dmSecondaryPrismaticJoint.hpp"
#include "dmSecondarySphericalJoint.hpp"
#include <dmTreadmill.hpp>

#include "dmvArticulationData.h"
#include "dmvMobileBaseLinkData.h"
#include "dmvStaticRootLinkData.h"
#include "dmvRevoluteLinkData.h"
#include "dmvContactModelData.h"
#include "dmvRevDCMotorData.h"
#include "dmvSphericalLinkData.h"
#include "dmvZScrewTxLinkData.h"
#include "dmvSecRevJntData.h"
#include "dmvSecPrisJntData.h"
#include "dmvSecSpherJntData.h"
#include "dmvTerrainData.h"
#include "dmvTreadmillData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
Note some of the variable names, specifically the ones related to secondary joints
following the naming conventions of DynaMechs 3.0
*/

CDynaMechs::CDynaMechs()
{
	m_pIntegrator = NULL;
	m_pSystem = NULL;
	m_pPlayerToolkit = NULL;
	m_pEnvironment = NULL;
	m_pCdmvSystemData = NULL;
	
	m_hControlDLL = NULL;
	DMControlComputeControlFunc = NULL;
	DMControlInitializeFunc = NULL;
	DMControlUninitializeFunc = NULL;
	DMControlKeyPressFunc = NULL;

	// simulation vars
	m_dSimulationTime = 0;
	m_dIntegrationStepSize = .01;
	m_dLastControlTime = -9999999; // Initialize to more negative than control step size so that
		// control is called at simulation time 0
	m_dControlStepSize = .01;
	m_nCurrentDisplayCount = 0;
	m_nDisplayRate = 2;

	m_bNoDisplayMode = FALSE;
	m_pdlgNoDisplayModeStatus = NULL;

	m_dwTickCountAtSimStart = 0;

	m_bRealTime = TRUE;

	m_dwDontSimulateStartTime = 0;
	m_dDontSimulateTotalTime = 0.0;
	m_bDontSimulateMode = FALSE;
}

CDynaMechs::~CDynaMechs()
{
	// This is a bad hack.  If this destructor is called while the program is exiting, the
	// framework has already worked to deallocate the memory in the dll.  Consequently, an
	// error will occur if the Uninitialize tries to deallocate memory, because it has
	// already been reclaimed.  If I set the function to NULL, I effectively don't make the
	// call, but still do the rest of the cleanup in ResetDynaMechs ()
	DMControlUninitializeFunc = NULL;
	ResetDynaMechs ();
	// Note if the NoDisplayMode status window is displayed, it will be destroyed when
	// ResetDynaMechs is called 

}

BOOL CDynaMechs::InitializeDynaMechs(CdmvSystemData *pCdmvSystemData, CdmvEnvironmentData 
									 *pCdmvEnvironmentData,	CString strControlDLLFile,
                            RBUserIOData** ppRBUserIOData, CPlaybackData* pPlaybackData)
{
	// To permit this to be re-entrant, first call a reset function which
	// deletes any existing configurations
	BOOL bReturnStatus = ResetDynaMechs ();
	ASSERT (bReturnStatus);

	m_pEnvironment = LoadEnvironmentDataIntoDynaMechs (pCdmvEnvironmentData);
	if (!m_pEnvironment)
	{
		return FALSE;
	}
	dmEnvironment::setEnvironment (m_pEnvironment);
//	m_pSystem = dmuLoadFile_dm((char*) LPCTSTR (strDMConfigFile));
	m_pSystem = LoadDMDataIntoDynaMechs (pCdmvSystemData);
	if (!m_pSystem)
	{
		// Then failed to load robot
		return FALSE;
	}

   // If there currently is RBUserIOData, deallocate it
   if (*ppRBUserIOData)
      delete *ppRBUserIOData;

 	// Allocate new
	try {
		*ppRBUserIOData = new RBUserIOData;
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}  

   // Save a local copy of the data for convenience (the class is only created here)
   m_pRBUserIOData = *ppRBUserIOData;

	// Set the project directory in the class, so it can be retrieved in the control
	// if desired
	string stringCfgDirectory = CFindFile::GetCFGFilePath ();
	m_pRBUserIOData->SetProjectDirectory (stringCfgDirectory);


	// Setup the integrator
	// Get the integrator type
	INTEGRATOR_TYPE IntegratorType = m_pCdmvCFGData->GetIntegratorType ();
	switch (IntegratorType)
	{
	case INTEGRATOR_PLACEMENT:
		m_pIntegrator = new dmIntegPlacement;
		m_dControlStepSize = m_pCdmvCFGData->GetControlStepSize ();
		m_dIntegrationStepSize = m_dControlStepSize;
		break;
	case INTEGRATOR_EULER:
		m_pIntegrator = new dmIntegEuler;
		m_dControlStepSize = m_pCdmvCFGData->GetControlStepSize ();
		m_dIntegrationStepSize = m_pCdmvCFGData->GetIntegratorEulerParameters ();
		break;
	case INTEGRATOR_RUNGE_KUTTA_4:
		m_pIntegrator = new dmIntegRK4;
		m_dControlStepSize = m_pCdmvCFGData->GetControlStepSize ();
		m_dIntegrationStepSize = m_pCdmvCFGData->GetIntegratorRungeKutta4Parameters ();
		break;
	case INTEGRATOR_ADAPTIVE_4_5_RUNGE_KUTTA:
		m_pIntegrator = new dmIntegRK45;
		m_dControlStepSize = m_pCdmvCFGData->GetControlStepSize ();
		m_dIntegrationStepSize = m_dControlStepSize;
		// Pick up the parameters
		double dEpsilon, dMinimumStepSize;
		m_pCdmvCFGData->GetIntegratorAdaptive45RungeKuttaParameters (&dEpsilon, &dMinimumStepSize);
		// Need to set the epsilon for the integrator, but the function to set
		// this also needs a value for the Max Accuracy; therefore, pick up
		// the current value to be used in the setErrorBound function
		Float fDynaMechsEpsilon, fDynaMechsMaxAccuracy;
		dynamic_cast <dmIntegRK45*> (m_pIntegrator)->getErrorBound (fDynaMechsEpsilon, fDynaMechsMaxAccuracy); 
		// Set the Euler step size over discontinuities
		dynamic_cast <dmIntegRK45*> (m_pIntegrator)->setEulerStep (dMinimumStepSize);
		break;
	default:
		// Unexpected integrator
		ASSERT (0);
		break;
	}
	ASSERT (m_pIntegrator);

	// Add the systems to the integrator
	bool bSuccess = m_pIntegrator->addSystem(m_pEnvironment);
	ASSERT (bSuccess);
	bSuccess = m_pIntegrator->addSystem(m_pSystem);
	ASSERT (bSuccess);

	// Save a copy of the system - this instance of CDynaMechs is specific to this system
	m_pCdmvSystemData = pCdmvSystemData;

	// Get the display rate
	m_nDisplayRate = m_pCdmvCFGData->GetSimulationDisplayRate ();

	// Do real time?
	m_bRealTime = m_pCdmvCFGData->GetRealTime ();

	// Save a copy of the playback data
	ASSERT (pPlaybackData);
	m_pPlaybackData = pPlaybackData;

	if (!InitializeControl (strControlDLLFile))
		return FALSE;

	return TRUE;
}

BOOL CDynaMechs::ResetDynaMechs()
{
	if (m_hControlDLL)
	{
		UninitializeControl ();

		BOOL bReturnStatus = AfxFreeLibrary (m_hControlDLL);
		ASSERT (bReturnStatus);
		m_hControlDLL = NULL;

		DMControlComputeControlFunc = NULL;
		DMControlInitializeFunc = NULL;
		DMControlUninitializeFunc = NULL;
		DMControlKeyPressFunc = NULL;
	}

	// Destroy the status window if in no display mode
	if (m_pdlgNoDisplayModeStatus)
	{
		DestroyNoDisplayModeStatusDlg ();
	}

	if (m_pIntegrator)
	{
		delete m_pIntegrator;
		m_pIntegrator = NULL;
	}

	if (m_pSystem)
	{
		delete m_pSystem;
		m_pSystem = NULL;
	}
	if (m_pEnvironment)
	{
		delete m_pEnvironment;
		m_pEnvironment = NULL;
	}

	// Reset simulation vars that need to be re-initialized;
	m_dSimulationTime = 0;
	m_dLastControlTime = -9999999;// Initialize to more negative than control step size so that
		// control is called at simulation time 0
	m_nCurrentDisplayCount = INT_MAX; // Initialize to a large number to force
		// a repaint at the beginning
	m_pCdmvSystemData = NULL;
	m_bPlaybackMode = FALSE; // Default to not being in playback mode.
	m_dSimulationStartTime = 0; // Reset the start simulation time to 0

	return TRUE;
}


BOOL CDynaMechs::InitializeControl(CString strControlDLLFile)
{
	ASSERT (m_hControlDLL == NULL);

	m_hControlDLL = AfxLoadLibrary (strControlDLLFile);
	if (!m_hControlDLL)
	{
		AfxMessageBox ("The Control DLL failed to load properly.  Please check\
the path and file name");
		return FALSE;
	}

/*	DMControlInitializeFunc = (int (*) (dmSystem*, RBUserIOData*)) GetProcAddress (m_hControlDLL,
		"?InitializeDMControl@@YAHPAVdmSystem@@PAVRBUserIOData@@@Z");
	DMControlComputeControlFunc = (int (*) (dmSystem*, dmIntegrator*, dmEnvironment*, RBUserIOData*, float)) GetProcAddress (m_hControlDLL,
 		"?ComputeDMControl@@YAHPAVdmSystem@@PAVdmIntegrator@@PAVdmEnvironment@@PAVRBUserIOData@@M@Z");
	DMControlUninitializeFunc = (int (*) (dmSystem*)) GetProcAddress (m_hControlDLL,
		"?UninitializeDMControl@@YAHPAVdmSystem@@@Z");
	DMControlKeyPressFunc = (int (*) (UINT, int)) GetProcAddress (m_hControlDLL,
		"?HandleKeyPress@@YAHIH@Z");
*/
	DMControlInitializeFunc = (int (*) (dmSystem*, RBUserIOData*)) GetProcAddress (m_hControlDLL,
		"InitializeDMControl");
	DMControlComputeControlFunc = (int (*) (dmSystem*, dmIntegrator*, dmEnvironment*, RBUserIOData*, float)) GetProcAddress (m_hControlDLL,
 		"ComputeDMControl");
	DMControlUninitializeFunc = (int (*) (dmSystem*, RBUserIOData*)) GetProcAddress (m_hControlDLL,
		"UninitializeDMControl");
	DMControlKeyPressFunc = (int (*) (UINT, int)) GetProcAddress (m_hControlDLL,
		"HandleKeyPress");


	// Note that the DMControlKeyPressFunc function is optional in the sense that if
	// it is not defined in the controll DLL the function GetProcAddress will fail, but
	// this will not result in a program error because it is verified that the DMControlKeyPressFunc
	// is not NULL before it is called.

	if (DMControlComputeControlFunc == NULL ||
		DMControlInitializeFunc == NULL ||
		DMControlUninitializeFunc == NULL )
	{
		AfxMessageBox ("The functions in the control DLL are not defined properly.");
		return FALSE;
	}

	int nControlInitReturn = DMControlInitializeFunc (m_pSystem, m_pRBUserIOData);
	if (nControlInitReturn == 1)
	{
		// The control has aborted initialization
		return FALSE;
	}

	// If in NoDisplayMode, create the status window and save the pointer
	if (m_bNoDisplayMode)
	{
		CreateNoDisplayModeStatusDlg ();
	}

	// Store the current tick count (used for real-time option)
	m_dwTickCountAtSimStart = GetTickCount ();
		
	// Clear any stopped time from previous simulations
	m_dDontSimulateTotalTime = 0;
	m_bDontSimulateMode = FALSE;
	return TRUE;
}


void CDynaMechs::UninitializeControl()
{
	if (DMControlUninitializeFunc)
		DMControlUninitializeFunc (m_pSystem, m_pRBUserIOData);
	

}

int CDynaMechs::ComputeControl(float time)
{
	ASSERT (DMControlComputeControlFunc);
	ASSERT (AfxIsValidAddress (m_pSystem, sizeof(dmSystem), TRUE));
	return DMControlComputeControlFunc (m_pSystem, m_pIntegrator, m_pEnvironment,
        m_pRBUserIOData, time);
}

BOOL CDynaMechs::UpdateDisplay(GraphicsMode theGraphicsMode)
{
	if (m_pPlayerToolkit)
	{
		// If the update transforms function returns false, it indicates that DynaMechs has become
		// unstable and simulation must stop.
		if (!m_pPlayerToolkit->UpdateTransforms (m_pSystem, m_pCdmvSystemData,
				m_pPlaybackData, theGraphicsMode))
			return FALSE;

		m_pPlayerToolkit->UpdateEnvironment (m_pEnvironment, m_dControlStepSize * m_nDisplayRate,
				m_pPlaybackData, theGraphicsMode);
	}

	return TRUE;
}

// Edit 9/12/00 SJR - Added no display mode option.
BOOL CDynaMechs::UpdateSimulation(GraphicsMode theGraphicsMode)
{

	if (m_bRealTime || m_bPlaybackMode) // Playback mode always attempts to be realtime
	{
		DWORD dwTickCountCurrent;
		dwTickCountCurrent = GetTickCount ();

		// Check if during the last call, the code was in the not simulating mode
		// (this is needed so real time can sync up with the simulation time, so
		// it only needs to be done in real time mode)
		if (m_bDontSimulateMode)
		{
			// Then last time, the code was not simulating.
			// Change the state.
			m_bDontSimulateMode = FALSE;

			// Need to calculate how long it was not simulating and check for rollover
			DWORD dwTickCountDelta;
			if (dwTickCountCurrent >= m_dwDontSimulateStartTime)
				dwTickCountDelta = dwTickCountCurrent - m_dwDontSimulateStartTime;
			else
				dwTickCountDelta = UINT_MAX - (m_dwDontSimulateStartTime - dwTickCountCurrent);

			m_dDontSimulateTotalTime += dwTickCountDelta / 1000.0;
		}			

		// Find the tick and check for rollover
		DWORD dwTickCountDelta;
		if (dwTickCountCurrent >= m_dwTickCountAtSimStart)
			dwTickCountDelta = dwTickCountCurrent - m_dwTickCountAtSimStart;
		else
			dwTickCountDelta = UINT_MAX - (m_dwTickCountAtSimStart - dwTickCountCurrent);

		// This is a workaround.  This simulation runs in idle time - when the application
		// receives WM_IDLE messages.  The problem is that the OS doesn't send WM_IDLE messages
		// when parts of the user interface are in use (like holding the left mouse button
		// down on a scroll bar or leaving a menu open).  When this happens, the real time clock
		// gets way ahead of the simulation because the simulation is not updating because
		// it's not getting WM_IDLE messages.  To work around this, if the tick count
		// is above some threshold, I will assume that we are in that case.  Note it is possible
		// that I am not in that case too, because we would see similar results if the simulation
		// was taking too long and beginning to lag behind the real time clock.  So to not
		// waste the time, I will advance the clock a little bit too.
		double dOffsetTime = (m_dSimulationTime - m_dSimulationStartTime) - (dwTickCountDelta/1000.0 - m_dDontSimulateTotalTime);
		if (dOffsetTime > 0)
		{
			// Then simulation is ahead of real time, so wait for real time to catch up
			return TRUE;
		}
		else if (dOffsetTime < -.200)
		{
			// Then simulation is really behind, try to sync times - see note above
			m_dDontSimulateTotalTime += (abs(dOffsetTime) - .10);
		}
	}

	if (m_bPlaybackMode)
	{

		// Peek at the next time and see at end of simulation
		double dNextTime = m_pPlaybackData->PeekNextSnapShotTime (); 

		// Make sure not at the end of the snap shots - this is in case
		// the user hits play after a forced pause at the end of a playback
		if (dNextTime == PLAYBACK_END)
		{
			AfxGetMainWnd ()->PostMessage (WM_COMMAND, ID_BUTTON_PAUSE);
			return TRUE;
		}
		
		// Get the next snap shot
		double dSnapShotTime;
		m_pPlaybackData->GetNextSnapShot (dSnapShotTime);

#ifdef WTK_LICENSE_AVAILABLE
		// Update the display
		UpdateDisplay (GRAPHICS_PLAYBACK);
#endif

		// Peek at the next time and see if it is time to display the next snapshot
		dNextTime = m_pPlaybackData->PeekNextSnapShotTime (); 

		// Make sure not at the end of the snap shots
		if (dNextTime == PLAYBACK_END)
		{
			AfxGetMainWnd ()->PostMessage (WM_COMMAND, ID_BUTTON_PAUSE);
			return TRUE;
		}

		// Set the sim time to the next time
		m_dSimulationTime = dNextTime;
	}
	else
	{
		// Regular simulation

		// We would like for the record mode to store the state at time = 0.
		// This is a special case check to accomplish that.
		if (theGraphicsMode == GRAPHICS_RECORD && m_dSimulationTime == 0)
		{
			// Then recording and time = 0 - so save a record for playback data.
			// Do this by running the UpdateDisplay function - this is a little
			// inefficient, because the display won't change, but I think it will
			// make the code more straightforward.
			if (theGraphicsMode == GRAPHICS_RECORD)
			{
				m_pPlaybackData->AddSnapShot (m_dSimulationTime);
			}
#ifdef WTK_LICENSE_AVAILABLE
			if (!UpdateDisplay (theGraphicsMode))
				return FALSE;
#endif
		}

		bool bCalledControlThisTime = FALSE;
		// See if the time since the last control call, rounded to the nearest millisecond is
		// greater than or equal to the control step size
		if (((m_dSimulationTime - m_dLastControlTime) * 1000 + .5)/1000 >= m_dControlStepSize)
		{
			int nComputeControlReturn = ComputeControl (m_dSimulationTime);
			if (nComputeControlReturn == 1)
			{
				// Then abort simulation, as told to by the controller
				return FALSE;
			}

			bCalledControlThisTime = TRUE; // Called compute control this time through the loop
				// This is used later, so the screen updates are relative to when the control
				// is updated.
			m_dLastControlTime = m_dSimulationTime;
	
		}

		// Integrator requires a float
		float fSimulationStepSize = (float) m_dIntegrationStepSize;
		m_pIntegrator->simulate (fSimulationStepSize);
		m_dSimulationTime += m_dIntegrationStepSize;

		
		// Want the display updates to be relative to the control calls, so check if control
		// was called this time.
		if (bCalledControlThisTime)
		{
			if (m_bNoDisplayMode)
			{
				CString strSimulationTime;
				int nMilliseconds = (int) (((int) (m_dSimulationTime * 1000 + .5) % 1000) );
				int nSeconds = (int) (floor (m_dSimulationTime)) % 60;
				int nMinutes = (int) ((floor (m_dSimulationTime) - nSeconds) / 60) % 60;
				strSimulationTime.Format ("%d : %02d.%03d", nMinutes, nSeconds, nMilliseconds);
				m_pdlgNoDisplayModeStatus->SetDlgItemText (IDC_STATIC_SIMULATION_TIME, strSimulationTime);
			}
			else
			{
				if (m_nCurrentDisplayCount < m_nDisplayRate)
					m_nCurrentDisplayCount ++;
				else
				{
					// If in record mode, add the next snapshot
					if (theGraphicsMode == GRAPHICS_RECORD)
					{
						m_pPlaybackData->AddSnapShot (m_dSimulationTime);
					}
	#ifdef WTK_LICENSE_AVAILABLE
					if (!UpdateDisplay (theGraphicsMode))
						return FALSE;
	#endif
					m_nCurrentDisplayCount = 0;
				}
			}
		}
	}


	return TRUE;
}

void CDynaMechs::SetPlayerPointer(CWTKGraphics *pPlayer)
{
	m_pPlayerToolkit = pPlayer;
}


void CDynaMechs::KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// At this point, I am not passing on the information in nFlags field
	// because it seems unlikely that it will be helpful
	if (DMControlKeyPressFunc)
	{
		DMControlKeyPressFunc (nChar, nRepCnt);
	}
}

BOOL CDynaMechs::GetNoDisplayMode()
{
	return m_bNoDisplayMode;
}

void CDynaMechs::SetNoDisplayMode(BOOL bNoDisplayMode)
{
	if (bNoDisplayMode == m_bNoDisplayMode)
	{
		// Then already set up for that state so ignore it
		return;
	}
	else
	{
		m_bNoDisplayMode = bNoDisplayMode;
		if (bNoDisplayMode)
			CreateNoDisplayModeStatusDlg ();
		else
			DestroyNoDisplayModeStatusDlg ();
	}
}

void CDynaMechs::CreateNoDisplayModeStatusDlg()
{
	ASSERT (m_pdlgNoDisplayModeStatus == NULL);

	m_pdlgNoDisplayModeStatus = new CDlgNoDisplayModeStatus;
	m_pdlgNoDisplayModeStatus->Create (IDD_NODISPLAYMODE_STATUS, NULL);
	ASSERT (m_pdlgNoDisplayModeStatus);
	m_pdlgNoDisplayModeStatus->ShowWindow (TRUE);
	CRect rectParent;
	CRect rectClientArea;
	m_pdlgNoDisplayModeStatus->GetParent ()->GetClientRect (rectParent);
	m_pdlgNoDisplayModeStatus->GetClientRect (rectClientArea);
	CRect rectNew (rectParent.right / 2 - rectClientArea.right / 2,
		rectParent.bottom / 2 - rectClientArea.bottom / 2,
		0,
		0);
	rectNew.bottom = rectNew.top + rectClientArea.Height ();
	rectNew.right = rectNew.left + rectClientArea.Width ();
	m_pdlgNoDisplayModeStatus->ClientToScreen (rectNew);
	m_pdlgNoDisplayModeStatus->MoveWindow (rectNew);
}

void CDynaMechs::DestroyNoDisplayModeStatusDlg()
{
	ASSERT (m_pdlgNoDisplayModeStatus);
	BOOL bSuccess = m_pdlgNoDisplayModeStatus->DestroyWindow ();
	// If the main window is closed while the simulation is running, the status
	// the status window appears to be destroyed by the framework, so this may
	// return FALSE and still be OK (but in other circumstances it should return TRUE);
	delete m_pdlgNoDisplayModeStatus;
	m_pdlgNoDisplayModeStatus = NULL;
}

double CDynaMechs::GetSimulationTime() const
{
	return m_dSimulationTime;
}


// This is needed for the real time option, to record when the simulation is not playing
void CDynaMechs::DontSimulate()
{
	// Check if not simulating during the last step
	if (!m_bDontSimulateMode)
	{
		// Set the dontsimulate state.
		m_bDontSimulateMode = TRUE;

		// Record the start of the dontsimulate time
		m_dwDontSimulateStartTime = GetTickCount ();
	}

	// else don't do anything, it will keep accumulating the dontsimulate time
}


void CDynaMechs::SetCFGDataPointer(const CdmvCFGData *pCdmvCFGData)
{
	 m_pCdmvCFGData = pCdmvCFGData;
}


dmSystem* CDynaMechs::LoadDMDataIntoDynaMechs(CdmvSystemData *pCdmvSystemData)
{

	
	dmSystem* pDynaMechsSystem;

	// Allocate the Articulation
	if (dynamic_cast <CdmvArticulationData*> (pCdmvSystemData)
		->GetArticulationType () == OPEN_ARTICULATION)
	{
		// Allocate new
		try {
			pDynaMechsSystem = new dmArticulation;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}		
	}
	else if (dynamic_cast <CdmvArticulationData*> (pCdmvSystemData)
		->GetArticulationType () == CLOSED_ARTICULATION)
	{
		// Allocate new
		try {
			pDynaMechsSystem = new dmClosedArticulation;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}		
	}
	else
	{
		// Unknown state
		ASSERT (FALSE);
	}

	// Save the pointer
	pCdmvSystemData->SetDynaMechsObject (pDynaMechsSystem);

	LoadObjectName (pCdmvSystemData, pDynaMechsSystem);
	LoadArticulationReferenceSystem (dynamic_cast <CdmvArticulationData*> (pCdmvSystemData),
		dynamic_cast <dmArticulation*> (pDynaMechsSystem));

	// Need to store the DynaMechs links in an array first so that the links are all allocated
	// before they are added to the articulation (because don't know the parrent pointer yet)
	CdmvArticulationData* pCdmvArticulationData = dynamic_cast <CdmvArticulationData*> (pCdmvSystemData);
	dmArticulation* pdmArticulation = dynamic_cast <dmArticulation*> (pDynaMechsSystem);
	int nNumLinks = pCdmvArticulationData->m_arrayLinks.GetSize ();
	dmLink** pLinkArray;
	try {
		pLinkArray = new dmLink*[nNumLinks];
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	// Allocate the links
	int i;
	for (i = 0; i < nNumLinks; i++)
	{
		CdmvLinkData *pLink = pCdmvArticulationData->m_arrayLinks.GetAt (i).pLink;
		
		if (pLink->GetLinkType () == MOBILE_BASE_LINK)
		{
			dmMobileBaseLink *pDynaMechsLink;
			try {
				pDynaMechsLink = new dmMobileBaseLink;
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}
			
			LoadObjectName (pLink, pDynaMechsLink);
			LoadRigidBody (dynamic_cast <CdmvRigidBodyData*> (pLink),
				dynamic_cast <dmRigidBody*> (pDynaMechsLink));
			structMobileBaseLinkState strtMobileBaseLinkState;
			(dynamic_cast <CdmvMobileBaseLinkData*> (pLink))->GetInitialState (&strtMobileBaseLinkState);
			// Copy the state to an array
			Float fState[7];
			int j;
			for (j = 0; j < 7; j++)
			{
				if (j < 4)
					fState[j] = strtMobileBaseLinkState.qOrientation [j];
				else
					fState[j] = strtMobileBaseLinkState.cvPosition [j-4];
			}
			(dynamic_cast <dmMobileBaseLink*> (pDynaMechsLink))->setState (
				fState, strtMobileBaseLinkState.svVelocity);
			pLinkArray[i] = pDynaMechsLink;

			pLink->SetDynaMechsObject (pDynaMechsLink);
		}
		else if (pLink->GetLinkType () == STATIC_ROOT_LINK)
		{
			dmStaticRootLink *pDynaMechsLink;
			try {
				pDynaMechsLink = new dmStaticRootLink;
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}
			
			LoadObjectName (pLink, pDynaMechsLink);
			pLinkArray[i] = pDynaMechsLink;

			pLink->SetDynaMechsObject (pDynaMechsLink);
		}
		else if (pLink->GetLinkType () == REVOLUTE_LINK)
		{
			dmRevoluteLink *pDynaMechsLink;
			try {
				pDynaMechsLink = new dmRevoluteLink;
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}
			
			LoadObjectName (pLink, pDynaMechsLink);
			LoadRigidBody (dynamic_cast <CdmvRigidBodyData*> (pLink),
				dynamic_cast <dmRigidBody*> (pDynaMechsLink));
			LoadMDHData (dynamic_cast <CdmvMDHLinkData*> (pLink), pDynaMechsLink);
			LoadRevoluteActuator (dynamic_cast <CdmvRevoluteLinkData*> (pLink), pDynaMechsLink);

			pLinkArray[i] = pDynaMechsLink;

			pLink->SetDynaMechsObject (pDynaMechsLink);
		}
		else if (pLink->GetLinkType () == PRISMATIC_LINK)
		{
			dmPrismaticLink *pDynaMechsLink;
			try {
				pDynaMechsLink = new dmPrismaticLink;
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}
			
			LoadObjectName (pLink, pDynaMechsLink);
			LoadRigidBody (dynamic_cast <CdmvRigidBodyData*> (pLink),
				dynamic_cast <dmRigidBody*> (pDynaMechsLink));
			LoadMDHData (dynamic_cast <CdmvMDHLinkData*> (pLink), pDynaMechsLink);
			LoadJointFriction (pLink, pDynaMechsLink);

			pLinkArray[i] = pDynaMechsLink;

			pLink->SetDynaMechsObject (pDynaMechsLink);
		}
		else if (pLink->GetLinkType () == SPHERICAL_LINK)
		{
			dmSphericalLink *pDynaMechsLink;
			try {
				pDynaMechsLink = new dmSphericalLink;
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}
			
			LoadObjectName (pLink, pDynaMechsLink);
			LoadRigidBody (dynamic_cast <CdmvRigidBodyData*> (pLink),
				dynamic_cast <dmRigidBody*> (pDynaMechsLink));

			CartesianVector cvPosition;
			dynamic_cast <CdmvSphericalLinkData*> (pLink)->GetJointOffset (cvPosition);
			pDynaMechsLink->setJointOffset (cvPosition);

			// State
			structSphericalLinkState strtSphericalLinkState;
			dynamic_cast <CdmvSphericalLinkData*> (pLink)->GetLinkState (&strtSphericalLinkState);
			pDynaMechsLink->setState (strtSphericalLinkState.eaAngles, strtSphericalLinkState.fAngularVelocity);

			// Joint Limits
			structSphericalLinkJointLimits strtSphericalLinkJointLimits;
			dynamic_cast <CdmvSphericalLinkData*> (pLink)->GetJointLimits (&strtSphericalLinkJointLimits);
			pDynaMechsLink->setJointLimits (strtSphericalLinkJointLimits.fJointLimits, 
				strtSphericalLinkJointLimits.fSpring, strtSphericalLinkJointLimits.fDamper);

			
			LoadJointFriction (pLink, pDynaMechsLink);

			pLinkArray[i] = pDynaMechsLink;

			pLink->SetDynaMechsObject (pDynaMechsLink);
		}
		else if (pLink->GetLinkType () == ZSCREW_TX_LINK)
		{
			// In the current implementation of DynaMechs, I can only set the parameters
			// in the constructor.

			structZScrewTxLinkParameters strtZScrewTxLinkParameters;
			dynamic_cast <CdmvZScrewTxLinkData*> (pLink)->GetParameters (&strtZScrewTxLinkParameters);

			dmZScrewTxLink *pDynaMechsLink;
			try {
				pDynaMechsLink = new dmZScrewTxLink (strtZScrewTxLinkParameters.fD,
					strtZScrewTxLinkParameters.fTheta);
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}
			
			LoadObjectName (pLink, pDynaMechsLink);

			pLinkArray[i] = pDynaMechsLink;

			pLink->SetDynaMechsObject (pDynaMechsLink);
		}
		else 
		{
			// Unknown link
			ASSERT (FALSE);
		}
	}

	// Add the created links to DynaMechs
	// Loop through all the links
	int j;
	for (i = 0; i < nNumLinks; i++)
	{
		CdmvLinkPointer LinkInfo;
		LinkInfo = pCdmvArticulationData->m_arrayLinks.GetAt (i);
		// Find the parent link index in the link array so the new DynaMechs parent can be found
		if (LinkInfo.pLinkParent != NULL)
		{
			// Find the parent
			for (j = 0; j < nNumLinks; j++)
			{
				if (LinkInfo.pLinkParent == 
					pCdmvArticulationData->m_arrayLinks.GetAt (j).pLink)
				{
					// Found the parent index in the link array so get out of the loop
					break;
				}
			}
			// Make sure the parent was found, otherwise have a problem
			ASSERT (j != nNumLinks);

			pdmArticulation->addLink (pLinkArray[i], pLinkArray[j]);
		}
		else
		{
			// Parent is NULL
			pdmArticulation->addLink (pLinkArray[i], NULL);
		}
	}


	// If closed loop, load the secondary joints
	if (dynamic_cast <CdmvArticulationData*> (pCdmvSystemData)->GetArticulationType () == CLOSED_ARTICULATION)
	{
		CdmvArticulationData* pCdmvClosedArticulationData = 
			dynamic_cast <CdmvArticulationData*> (pCdmvSystemData);
		dmClosedArticulation *pdmClosedArticulation = dynamic_cast <dmClosedArticulation*> (pdmArticulation);

		int nNumSecondaryJoints = pCdmvClosedArticulationData->m_arraySecondaryJoints.GetSize ();

		// Allocate an array to hold a copy of the pointer of the secondary joint data
		dmSecondaryJoint** pSecJointArray;
		try {
			pSecJointArray = new dmSecondaryJoint*[nNumSecondaryJoints];
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}

		// Go through the secondary joints
		for (i = 0; i < nNumSecondaryJoints; i++)
		{
			CdmvSecJointData *pCdmvSecJointData = pCdmvClosedArticulationData->m_arraySecondaryJoints.GetAt (i);

			if (pCdmvSecJointData->GetSecondaryJointType () == SEC_REVOLUTE)
			{
				dmSecondaryRevoluteJoint *pdmSecJoint;
				try {
					pdmSecJoint = new dmSecondaryRevoluteJoint;
				}
				catch (CMemoryException*)
				{
					AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
					AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
					// Throw exception to next handler to break out of this function
					throw;
				}
				
				LoadSecondaryJoint (pCdmvSecJointData, pdmSecJoint, pdmClosedArticulation);

				// Load revolute specific data
				structSecondaryRevoluteJointData strtSecondaryRevoluteJointData;
				dynamic_cast <CdmvSecRevJntData*> (pCdmvSecJointData)->
					GetSecRevoluteJointData (&strtSecondaryRevoluteJointData);
				pdmSecJoint->setConstraintParams (
					strtSecondaryRevoluteJointData.dLinearConstraintSpring,
					strtSecondaryRevoluteJointData.dLinearConstraintDamper,
					strtSecondaryRevoluteJointData.dAngularConstraintSpring,
					strtSecondaryRevoluteJointData.dAngularConstraintDamper);

				if (pCdmvSecJointData->GetSoftOrHard ())
				{
					LoadStabilization (pCdmvSecJointData, pdmSecJoint);
					pdmClosedArticulation->addHardSecondaryJoint (pdmSecJoint);
				}
				else
				{
					pdmClosedArticulation->addSoftSecondaryJoint (pdmSecJoint);
				}

				pSecJointArray[i] = pdmSecJoint;

				pCdmvSecJointData->SetDynaMechsObject (pdmSecJoint);
			}
			else if (pCdmvSecJointData->GetSecondaryJointType () == SEC_PRISMATIC)
			{
				dmSecondaryPrismaticJoint *pdmSecJoint;
				try {
					pdmSecJoint = new dmSecondaryPrismaticJoint;
				}
				catch (CMemoryException*)
				{
					AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
					AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
					// Throw exception to next handler to break out of this function
					throw;
				}
				
				LoadSecondaryJoint (pCdmvSecJointData, pdmSecJoint, pdmClosedArticulation);

				// Load prismatic specific data
				structSecondaryPrismaticJointData strtSecondaryPrismaticJointData;
				dynamic_cast <CdmvSecPrisJntData*> (pCdmvSecJointData)->
					GetSecPrismaticJointData (&strtSecondaryPrismaticJointData);
				pdmSecJoint->setConstraintParams (
					strtSecondaryPrismaticJointData.dLinearConstraintSpring,
					strtSecondaryPrismaticJointData.dLinearConstraintDamper,
					strtSecondaryPrismaticJointData.dAngularConstraintSpring,
					strtSecondaryPrismaticJointData.dAngularConstraintDamper);

				if (pCdmvSecJointData->GetSoftOrHard ())
				{
					LoadStabilization (pCdmvSecJointData, pdmSecJoint);
					pdmClosedArticulation->addHardSecondaryJoint (pdmSecJoint);
				}
				else
				{
					pdmClosedArticulation->addSoftSecondaryJoint (pdmSecJoint);
				}

				pSecJointArray[i] = pdmSecJoint;

				pCdmvSecJointData->SetDynaMechsObject (pdmSecJoint);
			}
			else if (pCdmvSecJointData->GetSecondaryJointType () == SEC_SPHERICAL)
			{
				dmSecondarySphericalJoint *pdmSecJoint;
				try {
					pdmSecJoint = new dmSecondarySphericalJoint;
				}
				catch (CMemoryException*)
				{
					AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
					AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
					// Throw exception to next handler to break out of this function
					throw;
				}
				
				LoadSecondaryJoint (pCdmvSecJointData, pdmSecJoint, pdmClosedArticulation);

				// Load prismatic specific data
				structSecondarySphericalJointData strtSecondarySphericalJointData;
				dynamic_cast <CdmvSecSpherJntData*> (pCdmvSecJointData)->
					GetSecSphericalJointData (&strtSecondarySphericalJointData);
				pdmSecJoint->setConstraintParams (
					strtSecondarySphericalJointData.dLinearConstraintSpring,
					strtSecondarySphericalJointData.dLinearConstraintDamper);

				if (pCdmvSecJointData->GetSoftOrHard ())
				{
					LoadStabilization (pCdmvSecJointData, pdmSecJoint);
					pdmClosedArticulation->addHardSecondaryJoint (pdmSecJoint);
				}
				else
				{
					pdmClosedArticulation->addSoftSecondaryJoint (pdmSecJoint);
				}

				pSecJointArray[i] = pdmSecJoint;

				pCdmvSecJointData->SetDynaMechsObject (pdmSecJoint);
			}
			else
			{
				// Unsupported secondary joint
				ASSERT (FALSE);
			}
		}

		// Now that all the links are allocated, set the A and B links for each
		// Find the link index like what was done above to find the parent
		for (i = 0; i < nNumSecondaryJoints; i++)
		{
			CdmvSecJointData *pCdmvSecJointData = pCdmvClosedArticulationData->m_arraySecondaryJoints.GetAt (i);
			
			// Set the articulation
			pSecJointArray[i]->setArticulation (pdmClosedArticulation);

			// Find the A link
			for (j = 0; j < nNumLinks; j++)
			{
				if (pCdmvSecJointData->GetLinkA () == 
					pCdmvArticulationData->m_arrayLinks.GetAt (j).pLink)
				{
					// Found the link A index in the link array so get out of the loop
					break;
				}
			}
			// Make sure the link A was found, otherwise have a problem
			ASSERT (j != nNumLinks);

			pSecJointArray[i]->setLinkA (pLinkArray[j]);
	
			// Find the B link
			for (j = 0; j < nNumLinks; j++)
			{
				if (pCdmvSecJointData->GetLinkB () == 
					pCdmvArticulationData->m_arrayLinks.GetAt (j).pLink)
				{
					// Found the link B index in the link array so get out of the loop
					break;
				}
			}
			// Make sure the link B was found, otherwise have a problem
			ASSERT (j != nNumLinks);

			pSecJointArray[i]->setLinkB (pLinkArray[j]);
		}

		// Need to call to initialize
		pdmClosedArticulation->initKinematicLoopVars ();
	}

	// Finished with the link array so deallocated it
	delete [] pLinkArray;

	return pDynaMechsSystem;

}

void CDynaMechs::LoadObjectName(const CdmvObject *pCdmvObject, dmObject *pdmObject)
{
	string stringName = pCdmvObject->GetName ();
	pdmObject->setName (stringName);
}

void CDynaMechs::LoadArticulationReferenceSystem(const CdmvArticulationData *pCdmvArticulationData,
												 dmArticulation *pdmArticulation)
{
	Quaternion qOrientation;
	CartesianVector cvPosition;
	pCdmvArticulationData->GetRefSystem (qOrientation, cvPosition);
	pdmArticulation->setRefSystem (qOrientation, cvPosition);
}

void CDynaMechs::LoadRigidBody(const CdmvRigidBodyData *pCdmvRigidBodyData, dmRigidBody *pdmRigidBody)
{
	structRigidBodyInertialParameters strtRigidBodyInertialParameters;
	pCdmvRigidBodyData->GetInertialParameters (&strtRigidBodyInertialParameters);
	pdmRigidBody->setInertiaParameters (strtRigidBodyInertialParameters.fMass,
		strtRigidBodyInertialParameters.ctIbar, strtRigidBodyInertialParameters.cvCenterGravityPosition);

	//  Load contact model data
	CdmvContactModelData* pCdmvContactModelData = pCdmvRigidBodyData->GetContactModel ();
	// Check if a contact model was given
	if (pCdmvContactModelData)
	{
		// Allocate one in DynaMechs
		dmContactModel *pdmContactModel;
		try {
			pdmContactModel = new dmContactModel;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}

		// Allocate one in DynaMechs
		CartesianVector *pcvContactPoints;
		int nNumPoints = pCdmvContactModelData->m_arrayPosition.GetSize ();
		try {
			pcvContactPoints = new CartesianVector[nNumPoints];
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}
		int i;
		for (i = 0; i < nNumPoints; i++)
		{
			pcvContactPoints[i][0] = pCdmvContactModelData->m_arrayPosition.GetAt(i).fXval;
			pcvContactPoints[i][1] = pCdmvContactModelData->m_arrayPosition.GetAt(i).fYval;
			pcvContactPoints[i][2] = pCdmvContactModelData->m_arrayPosition.GetAt(i).fZval;
		}
		pdmContactModel->setContactPoints (nNumPoints, pcvContactPoints);

		// Add the contact model to the rigid body
		pdmRigidBody->addForce (pdmContactModel);

		delete [] pcvContactPoints;
	}
}

void CDynaMechs::LoadMDHData(const CdmvMDHLinkData *pCdmvMDHLinkData, dmMDHLink *pdmMDHLink)
{
	// Set a, alpha, d, theta
	structMDHParameters strtMDHParameters;
	pCdmvMDHLinkData->GetMDHParameters (&strtMDHParameters);
	pdmMDHLink->setMDHParameters (strtMDHParameters.fa,
		strtMDHParameters.fAlpha, strtMDHParameters.fd, strtMDHParameters.fTheta);

	// Picks up the joint state (different depending on prismatic or revolute)
	Float q, qd;
	pdmMDHLink->getState (&q, &qd);
	Float fInitialVelocity = pCdmvMDHLinkData->GetInitialJointVelocity ();
	// Set the initial joint velocity by setting the initial state
	pdmMDHLink->setState (&q, &fInitialVelocity);

	// Joint limits
	structMDHLinkJointLimits strtMDHLinkJointLimits;
	pCdmvMDHLinkData->GetJointLimits (&strtMDHLinkJointLimits);
	pdmMDHLink->setJointLimits (strtMDHLinkJointLimits.fMin, strtMDHLinkJointLimits.fMax,
		strtMDHLinkJointLimits.fSpring, strtMDHLinkJointLimits.fDamper);
}



void CDynaMechs::LoadRevoluteActuator(const CdmvRevoluteLinkData *pCdmvRevoluteLinkData, dmRevoluteLink *pdmRevoluteLink)
{
	CdmvActuatorData *pCdmvActuatorData = pCdmvRevoluteLinkData->GetActuator ();
	if (pCdmvActuatorData)
	{
		// Then there is an actuator, so load it
		if (pCdmvActuatorData->GetActuatorType () == REV_DC_MOTOR)
		{
			// It's a REV_DC_MOTOR, so add one
			dmRevDCMotor *pdmRevDCMotor;
			try {
				pdmRevDCMotor = new dmRevDCMotor;
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}
			
			// Set the parameters
			structRevDCMotorParameters strtRevDCMotorParameters;
			dynamic_cast <CdmvRevDCMotorData*> (pCdmvActuatorData)->GetParameters (
				&strtRevDCMotorParameters);
			pdmRevDCMotor->setParameters (
				strtRevDCMotorParameters.fTorqueConstant,
				strtRevDCMotorParameters.fBackEMFConstant,
				strtRevDCMotorParameters.fArmatureResistance,
				strtRevDCMotorParameters.fRotorInertia,
				strtRevDCMotorParameters.fCoulombFrictionConstant,
				strtRevDCMotorParameters.fViscousFrictionConstant,
				strtRevDCMotorParameters.fMaxBrushDrop,
				strtRevDCMotorParameters.fHalfDropValue,
				strtRevDCMotorParameters.fGearRatio);

			// Add the actuator to the link
			pdmRevoluteLink->setActuator (pdmRevDCMotor);
		}
		else
		{
			// Unidentified motor
			ASSERT (FALSE);
		}
	}
	else
	{
		// No acutator, so set friction
		LoadJointFriction (pCdmvRevoluteLinkData, pdmRevoluteLink);
	}
}

void CDynaMechs::LoadJointFriction(const CdmvLinkData *pCdmvLinkData, dmLink *pdmLink)
{
	pdmLink->setJointFriction (pCdmvLinkData->GetJointFriction ());
}

void CDynaMechs::LoadSecondaryJoint(const CdmvSecJointData *pCdmvSecJointData, 
									dmSecondaryJoint *pdmSecJoint, dmClosedArticulation *pdmClosedArticulation)
{
	// Tell the joint which articulation is belongs to.
	pdmSecJoint->setArticulation (pdmClosedArticulation);

	structSecondaryJointParameters strtSecondaryJointParameters;
	pCdmvSecJointData->GetSecondaryJointParameters (&strtSecondaryJointParameters);

	pdmSecJoint->setKinematics (strtSecondaryJointParameters.cvPositionA,
		strtSecondaryJointParameters.cvPositionB, strtSecondaryJointParameters.rmRotationA,
		strtSecondaryJointParameters.rmRotationB);

	pdmSecJoint->setJointFriction (strtSecondaryJointParameters.FJointFriction);
}

void CDynaMechs::LoadStabilization(CdmvSecJointData *pCdmvSecJointData, dmSecondaryJoint *pdmSecJoint)
{
	StabilizationType Stabilization = pCdmvSecJointData->GetStabilizationType ();
	// Translate between RB and DynaMechs enums
	if (Stabilization == STABILIZATION_NONE)
		pdmSecJoint->setStabilizationType (dmSecondaryJoint::NONE);
	else if (Stabilization == STABILIZATION_BAUMGARTE)
		pdmSecJoint->setStabilizationType (dmSecondaryJoint::BAUMGARTE);
	else if (Stabilization == STABILIZATION_SPRING_DAMPER)
		pdmSecJoint->setStabilizationType (dmSecondaryJoint::SPRING_DAMPER);
	else
	{
		// Unexpected stabilization
		ASSERT (FALSE);
	}
}	

dmEnvironment* CDynaMechs::LoadEnvironmentDataIntoDynaMechs(CdmvEnvironmentData *pCdmvEnvironmentData)
{
	dmEnvironment* pDynaMechsEnvironment;

	// Allocate the environment
	if (pCdmvEnvironmentData->GetEnvironmentType () == ENV_TERRAIN)
	{
		// Allocate new
		try {
			pDynaMechsEnvironment = new dmEnvironment;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}		
	}
	else if (pCdmvEnvironmentData->GetEnvironmentType () == ENV_TREADMILL)
	{
		// Allocate new
		try {
			pDynaMechsEnvironment = new dmTreadmill;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}		
	}
	else
	{
		// Unknown state
		ASSERT (FALSE);
	}
	
	// Save the pointer
	pCdmvEnvironmentData->SetDynaMechsObject (pDynaMechsEnvironment);

	// Pick up the RB environment data
	structEnvironmentData strtEnvironmentData;
	pCdmvEnvironmentData->GetEnvironmentData (&strtEnvironmentData);
	// Push the data fields
	pDynaMechsEnvironment->setGravity (strtEnvironmentData.cvGravity);
	pDynaMechsEnvironment->setGroundNormalDamperConstant (strtEnvironmentData.fGroundNormalDamperConstant);
	pDynaMechsEnvironment->setGroundNormalSpringConstant (strtEnvironmentData.fGroundNormalSpringConstant);
	pDynaMechsEnvironment->setGroundPlanarDamperConstant (strtEnvironmentData.fGroundPlanarDamperConstant);
	pDynaMechsEnvironment->setGroundPlanarSpringConstant (strtEnvironmentData.fGroundPlanarSpringConstant);
	pDynaMechsEnvironment->setFrictionCoeffs (strtEnvironmentData.fu_s,
		strtEnvironmentData.fu_k);

	if (pCdmvEnvironmentData->GetEnvironmentType () == ENV_TERRAIN)
	{
		CdmvTerrainData *pCdmvTerrainData = dynamic_cast 
			<CdmvTerrainData*> (pCdmvEnvironmentData);
		
		// Build a 2D matrix of Floats to pass the depth array as
		int nXDim = pCdmvTerrainData->GetXDim ();
		int nYDim = pCdmvTerrainData->GetYDim ();

		Float ** ppDepthArray;
		// Allocate new
		try {
			ppDepthArray = new Float *[nXDim];

			int i, j;
			for (i = 0; i < nXDim; i++)
			{
				ppDepthArray[i] = new Float[nYDim];

				for (j = 0; j < nYDim; j++)
				{
					ppDepthArray[i][j] = pCdmvTerrainData->GetZValue (i, j);
				}
			}	
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}			

/*		pDynaMechsEnvironment->loadTerrainData (nXDim, nYDim,
			pCdmvTerrainData->GetGridResolution (),
			ppDepthArray);
*/
    pDynaMechsEnvironment->loadTerrainData (nXDim, nYDim,
      pCdmvTerrainData->GetXGridResolution (), pCdmvTerrainData->GetYGridResolution (),
			ppDepthArray);

		// Free the memory used to pass in the terrain
		int i;
		for (i = 0; i < nXDim; i++)
			delete [] ppDepthArray[i];
		delete [] ppDepthArray;
	}
	else if (pCdmvEnvironmentData->GetEnvironmentType () == ENV_TREADMILL)
	{
		CdmvTreadmillData *pCdmvTreadmillData = dynamic_cast 
			<CdmvTreadmillData*> (pCdmvEnvironmentData);
		dmTreadmill* pDynaMechsTreadmill = dynamic_cast 
			<dmTreadmill*> (pDynaMechsEnvironment);

		pDynaMechsTreadmill->setWidth (pCdmvTreadmillData->GetWidth ());
		pDynaMechsTreadmill->setLength (pCdmvTreadmillData->GetLength ());
		CartesianVector cvPosition;
		pCdmvTreadmillData->GetPosition (cvPosition);
		pDynaMechsTreadmill->setPosition (cvPosition);
		// Velocity and Normal are normalized and consistent
		CartesianVector cvVelocity;
		pCdmvTreadmillData->GetVelocityDirection (cvVelocity);
		pDynaMechsTreadmill->setVelocityDirection (cvVelocity);
		CartesianVector cvNormal;
		pCdmvTreadmillData->GetNormal (cvNormal);
		pDynaMechsTreadmill->setNormalDirection (cvNormal);
		// Set state for initial velocity magnitude - this will have to be changed
		// if RB begins to support hydrodynamics
		Float q[] = {0};
		Float qd[] = {0};
		qd[0] = pCdmvTreadmillData->GetVelocityMagnitude ();
		pDynaMechsTreadmill->setState (q, qd);

	}
	else
	{
		// Unexpected state
		ASSERT (FALSE);
	}


	return pDynaMechsEnvironment;
}

BOOL CDynaMechs::InitializePlayback(double dStartTime, double dEndTime, 
												CdmvSystemData *pCdmvSystemData,
												CdmvEnvironmentData *pCdmvEnvironmentData,
												CPlaybackData* pPlaybackData)
{
	// To permit this to be re-entrant, first call a reset function which
	// deletes any existing configurations
	BOOL bReturnStatus = ResetDynaMechs ();
	ASSERT (bReturnStatus);

	// Initialize the sim time to the start time
	m_dSimulationTime = dStartTime;

	// Set a variable to tell this class it's in the playback mode
	m_bPlaybackMode = TRUE;

	// Allocate the an empty environment, so the playback's CWTKGraphics::UpdateEnvironment
	// will know the type of environment
	if (pCdmvEnvironmentData->GetEnvironmentType () == ENV_TERRAIN)
	{
		// Allocate new
		try {
			m_pEnvironment = new dmEnvironment;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}		
	}
	else if (pCdmvEnvironmentData->GetEnvironmentType () == ENV_TREADMILL)
	{
		// Allocate new
		try {
			m_pEnvironment = new dmTreadmill;
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}		
	}
	else
	{
		// Unknown state
		ASSERT (FALSE);
	}
	// Save the playback data
	ASSERT (pPlaybackData);
	m_pPlaybackData = pPlaybackData;

	// Save a copy of the system - this instance of CDynaMechs is specific to this system
	m_pCdmvSystemData = pCdmvSystemData;

	// Reset the playback data for proper playback
	m_pPlaybackData->ResetPlayback ();

	// Store the current tick count (used for real-time option)
	m_dwTickCountAtSimStart = GetTickCount ();
		
	// Clear any stopped time from previous simulations
	m_dDontSimulateTotalTime = 0;
	m_bDontSimulateMode = FALSE;

	m_dSimulationStartTime = dStartTime; 
	m_dPlaybackStopTime = dEndTime;

	return TRUE;
}
