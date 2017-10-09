// Control.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Control.h"
#include <dmTreadmill.hpp>

/*** GLOBALS ***/


/*** METHODS ***/

/**
*
* DLL entry.
*
*/
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

/**
*
* Called by RobotBuilder to initialize the controller
*
* @param pSystem a pointer to DynaMechs' representation
*		of the system
*
* @param pRBUserIOData a pointer to the class that manages
*		the user settable IO capabilities during the Simulate
*		mode
*
* @return a 1 to stop the simulation from occurring (used
*		if the something in the initialization function 
*		failed), otherwise return 0 (other values
*		reserved for future use).
*
*/

CONTROL_API int InitializeDMControl(dmSystem* pSystem, 
									RBUserIOData *pRBUserIOData)
{

	// Setup slider
   bool bReturn = pRBUserIOData->SetNumberOfSliders (1);
   if (!bReturn) 
	{
		MessageBox (NULL, "SetNumberOfSliders Failed", "Error", MB_ICONERROR);
		return 1;
	}
   bReturn = pRBUserIOData->SetupSlider (0, 10, 10, 200, 50, 0, 250, 100, "Treadmill Velocity - cm/s");
   if (!bReturn) 
	{
		MessageBox (NULL, "SetupSlider Failed", "Error", MB_ICONERROR);
		return 1;
	}

	return 0;
}

/**
*
* Called by RobotBuilder to let the control do cleanup
*		and resource deallocation.
*
* @param pSystem a pointer to DynaMechs' representation 
*		of the system
*
* @param pRBUserIOData a pointer to the class that manages
*		the user settable IO capabilities during the Simulate
*		mode
*
* @return an int (presently arbitrary, but available for
*		future use)
*
*/
CONTROL_API int UninitializeDMControl(dmSystem* pSystem, 
									RBUserIOData* pRBUserIOData)
{
	// Deallocate any UserIO elements
	pRBUserIOData->CleanUp ();

	return 0;
}

/**
*
* Called by RobotBuilder to compute the control for
*		current state.
*
* @param pSystem a pointer to DynaMechs' representation
*		of the system
*
* @param pIntegrator a pointer to the integrator used
*		by DynaMechs
*
* @param pEnvironment a pointer to the DynaMechs'
*		environment
*
* @param pRBUserIOData a pointer to the class that manages
*		the user settable IO capabilities during simulation
*		mode 
*
* @param fTime the current simulation time
*
* @return a 1 to stop the simulation from occurring
*		(used if the something in the control function
*		failed), otherwise return 0 (other values
*		reserved for future use)
*
*/
CONTROL_API int ComputeDMControl(dmSystem* pSystem, 
								dmIntegrator* pIntegrator, 
								dmEnvironment* pEnvironment,
								RBUserIOData *pRBUserIOData,
                        float fTime)

{
	bool bReturn; // Holds return values

	// Get the slider value
	int nSliderValue;
	bReturn = pRBUserIOData->GetSliderValue (0, nSliderValue);
	if (!bReturn)
	{
		MessageBox (NULL, "GetSliderValue Failed", "Error", MB_ICONERROR);
		return 1;
	}
	
	//// Set the treadmill velocity
	Float q[1], qd[1]; // State variable and derivative for treadmill
	
	// Get pointer to treadmill
	dmTreadmill* pTreadmill = dynamic_cast <dmTreadmill*> (pEnvironment);

	// Get current state
	pTreadmill->getState (q, qd);

	// Change the velocity
	qd[0] = nSliderValue / 100.0; // Change to m/s

	// Write the state back
	pTreadmill->setState (q, qd);

	// Resync the integrator because the state derivative was overwritten
	pIntegrator->synchronizeState ();

	return 0;
}

/**
*
* Passes keypresses captured in RobotBuilder during 
*		simulation and passes them to control algorithm to 
*		provide interactive control (like tuning gains).
*
* @param nChar the character pressed
*
* @param nRepCnt the number of times the character has
*		been pressed since the system last told control 
*		about the key press (implements typematic)
*
* @return an int (presently arbitrary, but available 
*		for future use)
*
*/
CONTROL_API int HandleKeyPress (UINT nChar, int nRepCnt)
{
	return 0;
}