// Control.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Control.h"


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