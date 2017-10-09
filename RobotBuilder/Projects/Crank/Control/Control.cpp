// Control.cpp : Defines the entry point for the DLL application.
// Developed by Scott McMillan with control GUI by Steven

#include "stdafx.h"
#include "Control.h"

#include <dmLink.hpp>
#include <dmArticulation.hpp>
#include <dmu.h>

#include <strstream>

/*** GLOBALS ***/
dmLink* g_pCrank = NULL;
double g_dLastOutputTime = -1;


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
	// Cast the system to the articulation
	dmArticulation* pArticulation = dynamic_cast <dmArticulation*> (pSystem);
	if (!pArticulation)
	{
		MessageBox (NULL, "Articulation cast failed", "Error", MB_ICONERROR);
		return 1;
	}

	// Find the crank link
	g_pCrank = dynamic_cast <dmLink*> (dmuFindObject ("crank", pArticulation));
	if (!g_pCrank)
	{
		MessageBox (NULL, "Failed to find crank.", "Error", MB_ICONERROR);
		return 1;
	}

	// Setup the GUI controls
   bool bReturn = pRBUserIOData->SetNumberOfSliders (1);
	if (!bReturn)
	{
		MessageBox (NULL, "SetNumberOfSliders failed", "Error", MB_ICONERROR);
		return 1;
	}
   bReturn = pRBUserIOData->SetupSlider (0, 10, 280, 200, 50, 0, 25, 1, "Crank Torque (milliNm)");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupSlider failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetNumberOfOutputLists (1);
	if (!bReturn)
	{
		MessageBox (NULL, "SetNumberOfOutputLists failed", "Error", MB_ICONERROR);
		return 1;
	}
   bReturn = pRBUserIOData->SetupOutputList (0, 10, 10, 200, 250, "Time\tCrank Rate"); 
	if (!bReturn)
	{
		MessageBox (NULL, "SetupOutputList failed", "Error", MB_ICONERROR);
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
CONTROL_API int UninitializeDMControl(dmSystem* pSystem, RBUserIOData* pRBUserIOData)
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
CONTROL_API int ComputeDMControl(dmSystem* pSystem, dmIntegrator* pIntegrator, 
								   dmEnvironment* pEnvironment, RBUserIOData *pRBUserIOData,
                           float fTime)

{
	// Pick up the crank torque from the UI
	int nCrankTorque;
	bool bReturn = pRBUserIOData->GetSliderValue (0, nCrankTorque); 
	if (!bReturn)
	{
		MessageBox (NULL, "GetSliderValue failed", "Error", MB_ICONERROR);
		return 1;
	}
//	char test[100];
//	sprintf(test,"%d",nCrankTorque);
//	MessageBox (NULL, test, "Crank int", MB_ICONERROR);
	// Set the torque in DynaMechs
	Float FCrankTorque[1] = {(Float)((nCrankTorque*0.001))};
	
//	sprintf(test,"%f",FCrankTorque[0]);
//	MessageBox (NULL, test, "Error", MB_ICONERROR);
	g_pCrank->setJointInput (FCrankTorque);

	if (g_dLastOutputTime + 1  <= fTime)
	{
		Float FPos[3], FRate[3];
		g_pCrank->getState (FPos, FRate);

		// Put the data into a string to be used for the display routine
		strstream strmData;
		strmData << fTime << '\t' << FRate[0] << ends;

		bReturn = pRBUserIOData->SetOutputListData (0, strmData.str ());
		if (!bReturn)
		{
			MessageBox (NULL, "SetOutputListData failed", "Error", MB_ICONERROR);
			return 1;
		}

		// Save the output time
		g_dLastOutputTime = fTime;
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