// Control.cpp : Defines the entry point for the DLL application.
// Cart project developed by Scott McMillan

#include "stdafx.h"
#include "Control.h"
#include <dmArticulation.hpp>
#include <dmu.h>
#include <dmRevoluteLink.hpp>

/*** GLOBALS ***/
dmRevoluteLink* g_pWheel[4];
Float g_fDesiredPos[4];

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
CONTROL_API int InitializeDMControl(dmSystem* pSystem, RBUserIOData *pRBUserIOData)
{
	dmArticulation* pArticulation = dynamic_cast<dmArticulation*> (pSystem);

   dmObject *pObject;
   pObject = dmuFindObject("Wheel1", pArticulation);
   g_pWheel[0] = dynamic_cast<dmRevoluteLink*>(pObject);

   pObject = dmuFindObject("Wheel2", pArticulation);
   g_pWheel[1] = dynamic_cast<dmRevoluteLink*>(pObject);

   pObject = dmuFindObject("Wheel3", pArticulation);
   g_pWheel[2] = dynamic_cast<dmRevoluteLink*>(pObject);

   pObject = dmuFindObject("Wheel4", pArticulation);
   g_pWheel[3] = dynamic_cast<dmRevoluteLink*>(pObject);

	if (!g_pWheel[0] || !g_pWheel[1] || !g_pWheel[2] || !g_pWheel[3])
	{
		MessageBox (NULL, "Couldn't find the links.", "Error", MB_ICONERROR);
		return 1;
	}
	else
	{
		for (int i=0; i<4; i++)
		{
			Float dummy;
			g_pWheel[i]->getState(&g_fDesiredPos[i], &dummy);
		}
		return 0;
	}
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
CONTROL_API int UninitializeDMControl(dmSystem* pSystem, RBUserIOData *pRBUserIOData)
{
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
CONTROL_API int ComputeDMControl(dmSystem* pSystem, dmIntegrator* pIntegrator, 
								   dmEnvironment* pEnvironment, RBUserIOData *pRBUserIOData,
                           float fTime)

{
   Float joint_input;
   Float joint_pos;
   Float joint_vel;

   Float delta_pos = 20.0*sin(0.40*fTime);

   for (int i=0; i<4; i++)
   {
      g_pWheel[i]->getState(&joint_pos, &joint_vel);
      joint_input = 75.0*(g_fDesiredPos[i] + delta_pos - joint_pos) -
         2.0*joint_vel;

      g_pWheel[i]->setJointInput(&joint_input);
   }
	
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