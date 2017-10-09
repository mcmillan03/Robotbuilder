// Control.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Control.h"

#include <dmSystem.hpp>
#include <dmIntegrator.hpp>
#include <dmEnvironment.hpp>
#include <RBUserIOData.h>

#include <dmLink.hpp>
#include <dmArticulation.hpp>
#include <dmu.h>

/*** Prototypes ***/
void TranslatePulseUnitsToRadians (const float fA[], float fJointAnglesInRadians[]);
void GetTransform (const float fJointAnglesInRadians[], float fTransform[][4]);

#define RAD_2_DEG(x) ((x) * 180.0 / 3.1415926536)

/*** GLOBALS ***/
#define NUM_LINKS	7
#define OUTPUTFILE "MitsuProject1.txt"  // The output file name

/// Array of pointers to links in the system.
dmLink *g_pLinks[NUM_LINKS];
/// Used to know when to clear the output file.
bool g_bFirstTimeOutput;


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

	// Display edit boxes for the user
	int nColumn = 50;
	int nCurrentLine = 20;
	int nLineSpacing = 40;
	int nEditWidth = 100;
	bool bReturn = pRBUserIOData->SetNumberOfEdits (5);
	if (!bReturn)
	{
		MessageBox (NULL, "SetNumberOfEdits Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupEdit (0, nColumn, nCurrentLine, nEditWidth, "0", "a1");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupEdit Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;
	bReturn = pRBUserIOData->SetupEdit (1, nColumn, nCurrentLine, nEditWidth, "0", "a2");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupEdit Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;
	bReturn = pRBUserIOData->SetupEdit (2, nColumn, nCurrentLine, nEditWidth, "0", "a3");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupEdit Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;
	bReturn = pRBUserIOData->SetupEdit (3, nColumn, nCurrentLine, nEditWidth, "0", "a4");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupEdit Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;
	bReturn = pRBUserIOData->SetupEdit (4, nColumn, nCurrentLine, nEditWidth, "0", "a5");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupEdit Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;

	bReturn = pRBUserIOData->SetNumberOfCheckBoxes (1);
	if (!bReturn)
	{
		MessageBox (NULL, "SetNumberOfCheckBoxes Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupCheckBox (0, nColumn, nCurrentLine, false, "Gripper Open");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupCheckBox Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;

	bReturn = pRBUserIOData->SetNumberOfButtons (1);
	if (!bReturn)
	{
		MessageBox (NULL, "SetNumberOfButtons Failed", "Error", MB_ICONERROR);
		return 1;
	}
	const int nButtonWidth = 0; // A 0 dimension will let the button size itself to hold the given text
	const int nButtonHeight = 0; // See above
	bReturn = pRBUserIOData->SetupButton (0, nColumn, nCurrentLine, nButtonWidth, nButtonHeight, "Output to File");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupButton Failed", "Error", MB_ICONERROR);
		return 1;
	}

	// Set the state to clear the output file before the first write to it.
	g_bFirstTimeOutput = true;

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
*	In this implementation, it uses the kinematic placement integrator.
*  and specifies the values with data read in from side panel
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
                           float time)

{
	//// Pick up the data from the side panel
	bool bReturn; // Return value for edit control query

	//// Get edit box data
	string strValue; // String value read from edit control
	int nIndex; // Index to loop through the links
	float fA[NUM_LINKS]; // Joint Values
	for (nIndex = 0; nIndex < 5; nIndex++)
	{
		bReturn = pRBUserIOData->GetEditValue (nIndex, strValue);
		if (!bReturn)
		{
			MessageBox (NULL, "GetEditValue Failed", "Error", MB_ICONERROR);
			return 1;
		}
		fA[nIndex] = (float)atof (strValue.c_str ());
	}

	//// Get checkbox state
	bool bGripperOpen; // Holds the state of the gripper
	bReturn = pRBUserIOData->GetCheckBoxValue (0, bGripperOpen);
	if (!bReturn)
	{
		MessageBox (NULL, "GetCheckBoxValue Failed", "Error", MB_ICONERROR);
		return 1;
	}

	//// Get state of button
	bool bOutputTransform; // Holds the state of whether to output the data to file or not
	bReturn = pRBUserIOData->GetButtonClicked (0, bOutputTransform);
	if (!bReturn)
	{
		MessageBox (NULL, "GetButtonClicked Failed", "Error", MB_ICONERROR);
		return 1;
	}

	//// Translate to the pulse counts to radians
	float fJointAnglesInRadians[5];
	TranslatePulseUnitsToRadians (fA, fJointAnglesInRadians); 

	for (nIndex = 0; nIndex < 5; nIndex++)
	{
		// Need to pass the data as a Float array into DynaMechs
		Float q[1];
		q[0] = fJointAnglesInRadians[nIndex];
		
		// Apply the joint positions - the state derivate doesn't matter, because
		// no integration is occurring (using Placement mode), so just send a copy 
		// of the state to make the compiler happy.
		g_pLinks[nIndex]->setState (q, q);
	}
	
	//// Set the gripper - Note the gripper is implemented as two independent prismatic joints
	// to fit into DynaMechs
	if (!bGripperOpen)
	{
		// Then close gripper
		// Set up the prismatic parameters to do that
		Float q[1];

		q[0] = (Float) .05;
		g_pLinks[5]->setState (q, q);
		q[0] = (Float) -.05;
		g_pLinks[6]->setState (q, q);

	}
	else
	{
		// Open Gripper
		// Set up the prismatic parameters to do that
		Float q[1];

		q[0] = (Float) 0.4;
		g_pLinks[5]->setState (q, q);
		q[0] = (Float) -0.4;
		g_pLinks[6]->setState (q, q);
	}


	
	//// Check if output transform to file
	if (bOutputTransform)
	{
	
		// If first time outputting, clear the file
		if (g_bFirstTimeOutput)
		{
			// Clear the output file by overwriting the whole file with an endl
			ofstream strmOut;
			string strOutputFile = pRBUserIOData->GetProjectDirectory () + '\\' + OUTPUTFILE;
			strmOut.open (strOutputFile.c_str ());
			strmOut << endl;

			g_bFirstTimeOutput = false;

		}
		
		// First generate the 4x4 transform by calling the student's code
		float fTransform[4][4];
		GetTransform (fJointAnglesInRadians, fTransform);

		ofstream strmOut;
		// Open the file in append mode (note the file is clear when the at the control
		// initialization)
		string strOutputFile = pRBUserIOData->GetProjectDirectory () + '\\' + OUTPUTFILE;
		strmOut.open (strOutputFile.c_str (), ios::app);

		int nIsOpen = strmOut.is_open ();
		if (!nIsOpen)
		{
			MessageBox (NULL, "Failed to open output file", "Error", MB_ICONERROR);
			return 1;
		}

		int i, j;
		// Header
		strmOut << endl;
		strmOut << "****************************************************************************\n"; 

		// Output the user inputed pulse counts
		strmOut << "Entered pulse counts" << endl;
		for (i = 0; i < 5; i++)
			strmOut << fA[i] << "     ";
		strmOut << endl << endl;

		// Output the joint angles calculated by the student's code
		// Set output precision
		strmOut.precision (3);
 		// Set output format to fixed (not scientific) and right aligned
		strmOut.flags (ios::fixed | ios::right);
		strmOut << "Joint angles in radians (degrees)" << endl;
		for (i = 0; i < 5; i++)
			strmOut << fJointAnglesInRadians[i] << " (" << 
				RAD_2_DEG (fJointAnglesInRadians[i]) << ")     ";
		strmOut << endl << endl;

		// Output the student calculated transform
		strmOut << "Transform" << endl;
		// Only want the transform to have 2 digits of precision
		strmOut.precision (2); 
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 3; j++)
				strmOut << setw(5) << fTransform[i][j] << '\t';
			// Set field wider for translation components
			strmOut << setw(7) << fTransform[i][3];
			strmOut << endl;
		}
		strmOut << endl;

		strmOut.close ();				
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


