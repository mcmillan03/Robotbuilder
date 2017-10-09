// Control.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Control.h"

#include <crtdbg.h>

#include <dmLink.hpp>
#include <dmArticulation.hpp>
#include <dmu.h>

#include <math.h>
#include <strstream>
#include <fstream>

#define PI 3.14159265359

/*** Motor Parameters (mks units) ***/
#define	DC_MOTOR_K_TAU	0.0603
#define	DC_MOTOR_K_B	0.0603
#define	DC_MOTOR_R		1.16
#define DC_MOTOR_J		1.34e-5
#define DC_MOTOR_B		0

/*** Output File Name ***/
#define OUTPUT_FILE		"whegdata.csv"

/*** Data file rate (update period in seconds of sim time) ***/
#define DATA_OUTPUT_RATE	0.1


/*** GLOBALS ***/
dmLink* g_pWheg[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
double g_dLastOutputTime = -1, g_dLastDataOutputTime = -1;
bool g_bFirstTimeThroughControl = true;

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
* Called by RobotBuilder to intialize the controller
*
* @param pSystem a pointer to DynaMechs' representation of the system
*
* @param pRBUserIOData a pointer to the class that manages the user settable
*		IO capabilities during simulation mode
*
* @return a 1 to stop the simulation from occurring (used if the something in
*		the initialization function failed), otherwise return 0 (other values
*		reserved for future use).
*
*/

CONTROL_API int InitializeDMControl(dmSystem* pSystem, RBUserIOData *pRBUserIOData)
{
	// Cast the system to the articulation
	dmArticulation* pArticulation = dynamic_cast <dmArticulation*> (pSystem);
	_ASSERTE (pArticulation);

	// Get the wheg links
	g_pWheg[0] = dynamic_cast <dmLink*> (dmuFindObject ("Wheg 1", pArticulation));
	_ASSERTE (g_pWheg[0]);
	g_pWheg[1] = dynamic_cast <dmLink*> (dmuFindObject ("Wheg 2", pArticulation));
	_ASSERTE (g_pWheg[1]);
	g_pWheg[2] = dynamic_cast <dmLink*> (dmuFindObject ("Wheg 3", pArticulation));
	_ASSERTE (g_pWheg[2]);
	g_pWheg[3] = dynamic_cast <dmLink*> (dmuFindObject ("Wheg 4", pArticulation));
	_ASSERTE (g_pWheg[3]);
	g_pWheg[4] = dynamic_cast <dmLink*> (dmuFindObject ("Wheg 5", pArticulation));
	_ASSERTE (g_pWheg[4]);
	g_pWheg[5] = dynamic_cast <dmLink*> (dmuFindObject ("Wheg 6", pArticulation));
	_ASSERTE (g_pWheg[5]);

	// Setup the slider controls
	bool bReturn = pRBUserIOData->SetNumberOfSliders (4);
	_ASSERTE (bReturn);
	bReturn = pRBUserIOData->SetupSlider (0, 10, 40, 200, 50, 0, 48, 12, "DC Motor Voltage (V)");
    _ASSERTE (bReturn);
	bReturn = pRBUserIOData->SetupSlider (1, 10, 100, 200, 50, 0, 200, 60, "Wheg Spring Constant (x10)");
    _ASSERTE (bReturn);
	bReturn = pRBUserIOData->SetupSlider (2, 10, 160, 200, 80, 0, 50, 40, "Wheg Damper Constant (x1000)");
	_ASSERTE (bReturn);
	bReturn = pRBUserIOData->SetupSlider (3, 10, 240, 200, 50, 1, 25, 12, "Gear Ratio");
	_ASSERTE (bReturn);
			
	// Setup Output Control
	bReturn = pRBUserIOData->SetNumberOfLabels(1);
	_ASSERTE (bReturn);
	bReturn = pRBUserIOData->SetupLabel(0,10,360,300,"Wheg Position");
	_ASSERTE (bReturn);
	bReturn = pRBUserIOData->SetNumberOfOutputLists (1);
	_ASSERTE (bReturn);
	bReturn = pRBUserIOData->SetupOutputList (0, 10, 380, 300, 250, "Time\t1\t2\t3\t4\t5\t6"); 
	_ASSERTE (bReturn);

	return 0;
}

/**
*
* Called by RobotBuilder to let the control do clean up and resource deallocation.
*	In this implementation, it closes the MitsuParam exectuable and deletes the temporary
*	parameter file.
*
* @param pSystem a pointer to DynaMechs' representation of the system
*
* @return an int (presently arbitrary, but available for for future use)
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
* Called by RobotBuilder to compute the control for current state.
*
* @param pSystem a pointer to DynaMechs' representation of the system
*
* @param pIntegrator a pointer to the integrator used by DynaMechs
*
* @param pEnvironment a pointer to the DynaMechs' environment
*
* @param pRBUserIOData a pointer to the class that manages the user settable
*		IO capabilities during simulation mode 
*
* @param time the current simulation time
*
* @return a 1 to stop the simulation from occurring (used if the something in
*		the control function failed), otherwise return 0 (other values
*		reserved for future use)
*
*/
CONTROL_API int ComputeDMControl(dmSystem* pSystem, dmIntegrator* pIntegrator, 
								   dmEnvironment* pEnvironment, RBUserIOData *pRBUserIOData,
                           float fTime)

{
	// Get data from the UI
	Float FPos[6][3], FRate[6][3], FTorque[6][1];
	double dMotorAccel;
	static double dMotorPos = 0.0, dMotorRate = 0.0;
	static float FDesiredPhase[6], fLastTime = 0.0;
	int nVoltage, nSpring, nDamper, nGearRatio;
	string strOutputFile = pRBUserIOData->GetProjectDirectory () + '\\' + OUTPUT_FILE;
	static ofstream datafile(strOutputFile.c_str(),ios::out | ios::trunc);
	
	// Retrieve Constants from the UI
	bool bReturn = pRBUserIOData->GetSliderValue (1, nSpring);
	_ASSERTE (bReturn);
	bReturn = pRBUserIOData->GetSliderValue (2, nDamper);
	_ASSERTE (bReturn);
	bReturn = pRBUserIOData->GetSliderValue (3, nGearRatio);
	_ASSERTE (bReturn);
	bReturn = pRBUserIOData->GetSliderValue (0, nVoltage);
	_ASSERTE (bReturn);

	// Retrieve Wheg Rates and Positions
	for (int i=0;i < 6;i++)
	{
		g_pWheg[i]->getState (FPos[i], FRate[i]);
	}

	// If this is the first simulation time, initialize phasings and output file
	if (g_bFirstTimeThroughControl)
	{
		for (int i = 0; i < 6; i++)
		{
			FDesiredPhase[i] = FPos[i][0];
		}

		// Clear the old datafile by overwriting with a new header
		g_bFirstTimeThroughControl = false;
		// Clear the output file by overwriting the whole file with a new header
		ofstream datafile;
		string strOutputFile = pRBUserIOData->GetProjectDirectory () + '\\' + OUTPUT_FILE;
		datafile.open (strOutputFile.c_str ());

		datafile << ",,,,,Relative Position (rads),,,,,,Absolute Position (rads),,,,,,Rate (rads/sec),,,,,,Torque (N-m),,,,," << endl;
		datafile << "Time,Motor Voltage (V),Spring Constant (N/rad), Damper Constant (N/rad/s), Gear Ratio,1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5,6" << endl << endl;
		
		datafile.close();
	}
	
	// Calculate Torques
	for (i = 0;i < 6;i++)
	{	
		FTorque[i][0] = nSpring/10.0*(dMotorPos/nGearRatio - FPos[i][0] + FDesiredPhase[i]) + nDamper/1000.0*(dMotorRate/nGearRatio - FRate[i][0]);
		g_pWheg[i]->setJointInput(FTorque[i]);
	}

	// Calculate New Motor State
	dMotorAccel = (DC_MOTOR_K_TAU*((nVoltage-DC_MOTOR_K_B*dMotorRate))/DC_MOTOR_R - DC_MOTOR_B*dMotorRate -
					(1.0/nGearRatio)*(FTorque[0][0] + FTorque[1][0] + FTorque[2][0] + FTorque[3][0] + FTorque[4][0] + FTorque[5][0]))
					/DC_MOTOR_J;
	dMotorPos += dMotorRate*(fTime - fLastTime);
	dMotorRate += dMotorAccel*(fTime - fLastTime);
	
	// Update the time to calculate delta t next iteration
	fLastTime = fTime;

	// Update the data file
	if (g_dLastDataOutputTime + DATA_OUTPUT_RATE  <= fTime)
	{
		ofstream datafile;
		// Open the file in append mode
		string strOutputFile = pRBUserIOData->GetProjectDirectory () + '\\' + OUTPUT_FILE;
		datafile.open (strOutputFile.c_str (), ios::app);

		int nIsOpen = datafile.is_open ();
		if (!nIsOpen)
		{
			MessageBox (NULL, "Failed to open output file", "Error", MB_ICONERROR);
			return 1;
		}

		datafile << fTime << "," << nVoltage << "," << nSpring/10.0 << "," <<
			nDamper/1000.0 << "," << nGearRatio;
		for (i=0;i < 6; i++)
		{
			datafile << "," << dMotorPos/nGearRatio - FPos[i][0] + FDesiredPhase[i];
		}
		for (i=0;i < 6; i++)
		{
			datafile << "," << fmod(FPos[i][0],(float)(2*PI));
		}
		for (i=0;i < 6; i++)
		{
			datafile << "," << FRate[i][0];
		}
		for (i=0;i < 6; i++)
		{
			datafile << "," << FTorque[i][0];
		}
		datafile << endl;

		datafile.close();

		g_dLastDataOutputTime = fTime;
	}

	if (g_dLastOutputTime + 1.0 <= fTime)
	{
		// Put the data into a string to be used for the display routine
		strstream strmData;
		strmData << fTime;
				
		for (i=0;i < 6; i++)
		{
			strmData << '\t' << dMotorPos/nGearRatio - FPos[i][0] + FDesiredPhase[i];
		}

		strmData << ends;
		
		bReturn = pRBUserIOData->SetOutputListData (0, strmData.str ());
		_ASSERTE (bReturn);

		// Save the output time
		g_dLastOutputTime = fTime;
	}

	return 0;
}

/**
*
* Passes keypresses captured in RobotBuilder during simulation and passes them
*	to control algorithm to provide interactive control (like tuning gains).
*
* @param nChar the character pressed
*
* @param nRepCnt the number of times the character has been pressed since the
*	system last told control about the key press (implements typematic)
*
* @return an int (presently arbitrary, but available for for future use)
*
*/
CONTROL_API int HandleKeyPress (UINT nChar, int nRepCnt)
{
	return 0;
}