// Control.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Control.h"

#include <dmSystem.hpp>
#include <dmIntegrator.hpp>
#include <dmEnvironment.hpp>
#include <RBUserIOData.h>

#include <dmIntegPlacement.hpp>
#include <dmLink.hpp>
#include <dmArticulation.hpp>
#include <dmu.h>

#include <sstream>

#include "type_def.h" // required for invkin method parameters

#define OUTPUTFILE "MitsuProject3.txt"  // The output file name

/*** PROTOTYPES ***/
extern "C" {void invkin(matx44 X, enum STATUS_SET STATUS, array6 ANG);}
void TranslateRadiansToPulseUnits (const float fJointAnglesInRadians[], int nJointAnglesInPulseUnits[]);
void ComputeJointAngles (double dSimulationTimeInSeconds, int nJointAnglesInPulseUnits[], 
						 float fToolPosition[]);
void ComputeInputVoltage (double SimulationTimeInSeconds, const int ActualJointAnglesInPulseUnits[],
						 const int ActualJointVelocitiesInPulseUnitsPerSecond[],
						 float InputVoltage[], int DesiredJointAnglesInPulseUnits[], 
						 float DesiredGripperPosition[], float ActualGripperPosition[]);
void TranslateRadiansRatesToPulseUnitsRates (const float fJointVelocitiesInRadiansPerSecond [], 
		int nJointVelocitiesInPulseUnitsPerSecond[]);

/*** GLOBALS ***/
#define NUM_LINKS	7

/// Array of pointers to links in the system.
dmLink *g_pLinks[NUM_LINKS];
/// Used to determine when to output
int g_nLastTimeMSPrint = -99999; // Initialize to a really negative number (ie greater than
	// the desired output period) so that output is created at time 0
/// Used to know when to clear the output file.
bool g_bFirstTimeThroughControl = true;

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
	// Make sure the pointer is not null
	if (!pSystem)
	{
		MessageBox (NULL, "pSystem NULL", "Error", MB_ICONERROR);
		return 1;
	}

	// Obtain pointer to articulation 
	// Note dmSystem is the parent of dmArticulation
	dmArticulation* pArticulation = (dynamic_cast <dmArticulation*> (pSystem));
	if (!pArticulation)
	{
		MessageBox (NULL, "pArticulation NULL", "Error", MB_ICONERROR);
		return 1;
	}

	// Find each of the links of interest.  The order is important, because the
	// joint values are applied expecting a certain order.
	g_pLinks[0] = dynamic_cast <dmLink*> (dmuFindObject ("body", pArticulation));
	g_pLinks[1] = dynamic_cast <dmLink*> (dmuFindObject ("upperarm", pArticulation));
	g_pLinks[2] = dynamic_cast <dmLink*> (dmuFindObject ("forearm", pArticulation));
	g_pLinks[3] = dynamic_cast <dmLink*> (dmuFindObject ("wrist_pitch", pArticulation));
	g_pLinks[4] = dynamic_cast <dmLink*> (dmuFindObject ("wrist_roll", pArticulation));
	g_pLinks[5] = dynamic_cast <dmLink*> (dmuFindObject ("gripper1", pArticulation));
	g_pLinks[6] = dynamic_cast <dmLink*> (dmuFindObject ("gripper2", pArticulation));

	// Verify the links were found
	int i;
	for (i = 0; i < NUM_LINKS; i++)
		if (!g_pLinks[i])
		{
			MessageBox (NULL, "Failed to find link", "Error", MB_ICONERROR);
			return 1;
		}

	bool bReturn;
	bReturn = pRBUserIOData->SetNumberOfOutputLists (1);
	if (!bReturn) return 1;

	const int nPosX = 10;
	const int nPosY = 10;
	const int nWidth = 400;
	const int nHeight = 600;
	string strLabels; // Tab delimited labels

	strLabels = "Time\tPxd\tPyd\tPzd\tPx\tPy\tPz";

	bReturn = pRBUserIOData->SetupOutputList (0, nPosX, nPosY, nWidth, nHeight, strLabels);
	if (!bReturn)
	{
		MessageBox (NULL, "SetupOutputList Failed", "Error", MB_ICONERROR);
		return 1;
	}

	return 0;
}

/**
*
* Called by RobotBuilder to let the control do clean up and resource deallocation.
*
* @param pSystem a pointer to DynaMechs' representation of the system
*
* @param pRBUserIOData a pointer to the class that manages the user settable
*		IO capabilities during simulation mode.  This function must
*		call CleanUp to deallocate User IO elements.
*
* @return 0 (other values reserved for future use)
*
*/
CONTROL_API int UninitializeDMControl(dmSystem* pSystem, RBUserIOData *pRBUserIOData)
{
	// Deallocate any UserIO elements
	pRBUserIOData->CleanUp ();

	return 0;
}

/**
*
* Called by RobotBuilder to compute the control for current state.
*	This implementation supports the placement integrator or a dynamic integrator
* The output differs depending on the integrator.
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
	float fDesiredJointAnglesInRadians[5];
	int nDesiredJointAnglesInPulseUnits[5];
	float fDesiredGripperPosition[3];
	float fActualGripperPosition[3];
	Float fActualJointAnglesInRadians[5];
	Float fActualJointVelocitiesInRadiansPerSecond[5];
	int nActualJointAnglesInPulseUnits[5];
	int nActualJointVelocitiesInPulseUnitsPerSecond[5];
	Float fInputVoltage[5];
	
	int i;
	// Get the current joint states
	for (i = 0; i < 5; i++)
	{
		g_pLinks[i]->getState (&(fActualJointAnglesInRadians[i]), 
			&(fActualJointVelocitiesInRadiansPerSecond[i])); 
	}

	// Translate to pulse units
	TranslateRadiansToPulseUnits (fActualJointAnglesInRadians, nActualJointAnglesInPulseUnits);
	TranslateRadiansRatesToPulseUnitsRates (fActualJointVelocitiesInRadiansPerSecond, 
		nActualJointVelocitiesInPulseUnitsPerSecond);

	// Call student code to find the joint angles
	ComputeInputVoltage (fTime, nActualJointAnglesInPulseUnits, nActualJointVelocitiesInPulseUnitsPerSecond,
		fInputVoltage, nDesiredJointAnglesInPulseUnits, fDesiredGripperPosition, fActualGripperPosition);

	// if PLACEMENT integrator, use placement
	if (typeid (*pIntegrator) == typeid(dmIntegPlacement))
	{
		// Find in radians to set the articulation joints
		fDesiredJointAnglesInRadians[0] = DEG_2_RAD(-nDesiredJointAnglesInPulseUnits[0] / 40.0 - 150);
		fDesiredJointAnglesInRadians[1] = DEG_2_RAD(-nDesiredJointAnglesInPulseUnits[1] / 40.0 - 100);
		fDesiredJointAnglesInRadians[2] = DEG_2_RAD(-nDesiredJointAnglesInPulseUnits[2] / 40.0 +  90);
		fDesiredJointAnglesInRadians[3] = DEG_2_RAD(180 -(nDesiredJointAnglesInPulseUnits[3] - nDesiredJointAnglesInPulseUnits[4]) * 3 / 80.0);
		fDesiredJointAnglesInRadians[4] = DEG_2_RAD(-(nDesiredJointAnglesInPulseUnits[3] + nDesiredJointAnglesInPulseUnits[4]) * 3 / 80.0); 
		for (i = 0; i < 5; i++)
		{
			// Need to pass the data as a Float array (which in the current
			// DynaMechs build it typedefed to float, but to faciliate working
			// with double precision DynaMechs, I'll make a copy)
			Float q[1];
			q[0] = fDesiredJointAnglesInRadians[i];
			
			// Apply the joint positions - the state derivate doesn't matter, because
			// no integration is occurring, so just send a copy of the state to make
			// the compiler happy.
			g_pLinks[i]->setState (q, q);
		}

		// If first time through, erase the old output file and start over
		if (g_bFirstTimeThroughControl)
		{
			g_bFirstTimeThroughControl = false;
			// Clear the output file by overwriting the whole file with a new header
			ofstream strmOut;
			string strOutputFile = pRBUserIOData->GetProjectDirectory () + '\\' + OUTPUTFILE;
			strmOut.open (strOutputFile.c_str ());
			strmOut << 
				"                     Project 3 - Placement" << endl << endl;
			strmOut <<
				"Time    Px      Py      Pz      a1      a2      a3      a4      a5" << endl;
			strmOut <<
				"----   -----   -----   -----   -----   -----   -----   -----   -----" << endl;
			strmOut.close ();
		}

		// Output the data at the beginning
		if (fTime < 3.2)
		{
			// Only output the data every 50ms, but try to be somewhat robust, in case this
			// is hit at non-50ms intervals
			int nTimeMS = (int) (fTime * 1000 + .5f); // Round time the closest ms
			if (nTimeMS >= g_nLastTimeMSPrint + 50)
			{
				g_nLastTimeMSPrint = nTimeMS;
				ofstream strmOut;
				// Open the file in append mode
				string strOutputFile = pRBUserIOData->GetProjectDirectory () + '\\' + OUTPUTFILE;
				strmOut.open (strOutputFile.c_str (), ios::app);

				int nIsOpen = strmOut.is_open ();
				if (!nIsOpen)
				{
					MessageBox (NULL, "Failed to open output file", "Error", MB_ICONERROR);
					return 1;
				}

 				// Set output format to fixed (not scientific) and right aligned
				strmOut.flags (ios::fixed | ios::right);

				strmOut << setprecision (2) << setw (3) << fTime << "   " << setprecision(1) << 
					setw(5) << fDesiredGripperPosition[0] << "   " << 
					setw(5) << fDesiredGripperPosition[1] << "   " <<
					setw(5) << fDesiredGripperPosition[2] << "   ";
				for (i= 0; i < 5; i++)
					strmOut << setw(5) << setprecision(0) << nDesiredJointAnglesInPulseUnits[i] << "   ";

				strmOut << endl;

				strmOut.close ();			
				//// Display in output control too
				// Build the string to output to
				ostringstream strmData; // Holds the value to send to the UserIO
				strmData.flags (ios::fixed);

				strmData << setprecision (2) << setw (3) << fTime << '\t' << setprecision(1) << 
					setw(5) << fDesiredGripperPosition[0] << '\t' << 
					setw(5) << fDesiredGripperPosition[1] << '\t' <<
					setw(5) << fDesiredGripperPosition[2] << '\t' <<
					setw(5) << fActualGripperPosition[0] << '\t' <<
					setw(5) << fActualGripperPosition[1] << '\t' <<
					setw(5) << fActualGripperPosition[2];

				bool bReturn;
				bReturn = pRBUserIOData->SetOutputListData (0, strmData.str ());
				if (!bReturn)
				{
					MessageBox (NULL, "SetOutputListData Failed", "Error", MB_ICONERROR);
					return 1;
				}
			}
		}
	}
	else // The integrator is dynamic
	{
		// Negate the input voltage to drive the actual to the desired
		for (i = 0; i < 5; i++)
			fInputVoltage[i] *= -1;
			
		// Pass the joint input calculated by the student code into the joint
		for (i = 0; i < 5; i++)
		{
			g_pLinks[i]->setJointInput (&(fInputVoltage[i]));
		}

		// If first time through, erase the old output file and start over
		if (g_bFirstTimeThroughControl)
		{
			g_bFirstTimeThroughControl = false;
			// Clear the output file by overwriting the whole file with a new header
			ofstream strmOut;
			string strOutputFile = pRBUserIOData->GetProjectDirectory () + '\\' + OUTPUTFILE;
			strmOut.open (strOutputFile.c_str ());
			strmOut << 
				"                         Project 3" << endl << endl;
			strmOut << 
				"              Desired                 Actual" << endl;
			strmOut <<
				"Time    Px      Py      Pz      Px      Py      Pz" << endl;
			strmOut <<
				"----   -----   -----   -----   -----   -----   -----" << endl;
			strmOut.close ();
		}

		// Output the data at the beginning
		if (fTime < 3.2)
		{
			// Only output the data every 50ms, but try to be somewhat robust, in case this
			// is hit at non-50ms intervals
			int nTimeMS = (int) (fTime * 1000 + .5f); // Round time the closest ms
			if (nTimeMS >= g_nLastTimeMSPrint + 50)
			{
				g_nLastTimeMSPrint = nTimeMS;
				ofstream strmOut;
				// Open the file in append mode
				string strOutputFile = pRBUserIOData->GetProjectDirectory () + '\\' + OUTPUTFILE;
				strmOut.open (strOutputFile.c_str (), ios::app);

				int nIsOpen = strmOut.is_open ();
				if (!nIsOpen)
				{
					MessageBox (NULL, "Failed to open output file", "Error", MB_ICONERROR);
					return 1;
				}

 				// Set output format to fixed (not scientific) and right aligned
				strmOut.flags (ios::fixed | ios::right);

				strmOut << setprecision (2) << setw (3) << fTime << "   " << setprecision(1) << 
					setw(5) << fDesiredGripperPosition[0] << "   " << 
					setw(5) << fDesiredGripperPosition[1] << "   " <<
					setw(5) << fDesiredGripperPosition[2] << "   " <<
					setw(5) << fActualGripperPosition[0] << "   " <<
					setw(5) << fActualGripperPosition[1] << "   " <<
					setw(5) << fActualGripperPosition[2];

				strmOut << endl;

				strmOut.close ();


				//// Display in output control too
				// Build the string to output to
				ostringstream strmData; // Holds the value to send to the UserIO
				strmData.flags (ios::fixed);

				strmData << setprecision (2) << setw (3) << fTime << '\t' << setprecision(1) << 
					setw(5) << fDesiredGripperPosition[0] << '\t' << 
					setw(5) << fDesiredGripperPosition[1] << '\t' <<
					setw(5) << fDesiredGripperPosition[2] << '\t' <<
					setw(5) << fActualGripperPosition[0] << '\t' <<
					setw(5) << fActualGripperPosition[1] << '\t' <<
					setw(5) << fActualGripperPosition[2];

				bool bReturn;
				bReturn = pRBUserIOData->SetOutputListData (0, strmData.str ());
				if (!bReturn)
				{
					MessageBox (NULL, "SetOutputListData Failed", "Error", MB_ICONERROR);
					return 1;
				}
			}
		}
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
* @return 0 (other values reserved for future use)
*
*/
CONTROL_API int HandleKeyPress (UINT nChar, int nRepCnt)
{
	return 0;
}


/**
*
* Wrapper for Dr. Orin's invkin.  This function provides an interface to
*	that function, so the student code section will follow the same naming
*	and variable convections used throughout the project
*
* @param fTransform a 4x4 input array that contains the desired transform
* @param nJointAnglesInPulseUnits an output array of 5 ints that will receive
*	the joint angles (in pulse units) needed to attain the inputted transform.
*
*/
void InverseKinematics (const float fTransform[][4], int nJointAnglesInPulseUnits[])
{
	// It looks like the invkin.c code was translated from Pascal and so some
	// things don't make sense
	enum STATUS_SET status = VALID_SOLUTION; // This is not used, probably was
		// a return value in Pascal
	int nJointAnglesFromInvKin[6]; // The invkin returns the joint angles
		// in an array of six elements (last not used), so I need to allocate that much 
		// to prevent a buffer overflow, then copy the result to return.
	matx44 mat;	// Copy into non-const
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mat[i][j] = fTransform[i][j];

	invkin (mat, status, nJointAnglesFromInvKin);

	// Copy the returned values to the five element array to return
	for (i = 0; i < 5; i++)
		nJointAnglesInPulseUnits[i] = nJointAnglesFromInvKin[i];
}

/**
*
* Translates the joint angles from radians to pulse units (in absolute position terms).
*
* @param fJointAnglesInRadians an input array of joint angles in radians
* @param nJointAnglesInPulseUnits the output array of joint angles in pulse units
*
*/
void TranslateRadiansToPulseUnits (const float fJointAnglesInRadians[], int nJointAnglesInPulseUnits[])
{
	nJointAnglesInPulseUnits[0] = -(RAD_2_DEG(fJointAnglesInRadians[0]) + 150) * 40;
	nJointAnglesInPulseUnits[1] = -(RAD_2_DEG(fJointAnglesInRadians[1]) + 100) * 40;
	nJointAnglesInPulseUnits[2] = -(RAD_2_DEG(fJointAnglesInRadians[2]) -  90) * 40;
	nJointAnglesInPulseUnits[3] = -(RAD_2_DEG(fJointAnglesInRadians[3] + fJointAnglesInRadians[4]) - 180) * 40.0 / 3.0;
	nJointAnglesInPulseUnits[4] = (RAD_2_DEG(fJointAnglesInRadians[3] - fJointAnglesInRadians[4]) - 180) * 40.0 / 3.0;
}

/**
*
* Translates the joint angles rates from radians per second to pulse units 
*   per second.
*
* @param fJointVelocitiesInRadiansPerSecond an input array of joint angles rates in radians
*	per second
* @param fJointVelocitiesInPulseUnitsPerSecond the output array of joint angles rates in pulse 
*	units per second
*
*/
void TranslateRadiansRatesToPulseUnitsRates (const float fJointVelocitiesInRadiansPerSecond [], 
		int nJointVelocitiesInPulseUnitsPerSecond[])
{
	int i;
	for (i = 0; i < 3; i++)
		nJointVelocitiesInPulseUnitsPerSecond[i] = - RAD_2_DEG(fJointVelocitiesInRadiansPerSecond[i]) * 40.0;
	nJointVelocitiesInPulseUnitsPerSecond[3] = - RAD_2_DEG(fJointVelocitiesInRadiansPerSecond[3]) * 40.0 / 3.0;
	nJointVelocitiesInPulseUnitsPerSecond[4] = - RAD_2_DEG(fJointVelocitiesInRadiansPerSecond[4]) * 40.0 / 3.0;

}
