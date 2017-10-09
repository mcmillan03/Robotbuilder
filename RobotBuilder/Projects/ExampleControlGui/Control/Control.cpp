// Control.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Control.h"

#include <strstream>
#include <sstream>


/*** GLOBALS ***/
double g_dLastOutputTime = -1;
int g_nNumberButtonClicks = 0;


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
   bReturn = pRBUserIOData->SetupSlider (0, 10, 10, 200, 50, 0, 25, 1, "Slider");
   if (!bReturn) 
	{
		MessageBox (NULL, "SetupSlider Failed", "Error", MB_ICONERROR);
		return 1;
	}
	// Setup output list
	bReturn = pRBUserIOData->SetNumberOfOutputLists (1);
   if (!bReturn) 
	{
		MessageBox (NULL, "SetNumberOfOutputLists Failed", "Error", MB_ICONERROR);
		return 1;
	}
   bReturn = pRBUserIOData->SetupOutputList (0, 10, 75, 200, 100, "Time\tSlider Data"); 
   if (!bReturn) 
	{
		MessageBox (NULL, "SetupOutputList Failed", "Error", MB_ICONERROR);
		return 1;
	}
	// Setup button
	bReturn = pRBUserIOData->SetNumberOfButtons (1);
   if (!bReturn) 
	{
		MessageBox (NULL, "SetNumberOfButtons Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupButton (0, 50, 200, 80, 40, "Button");
   if (!bReturn) 
	{
		MessageBox (NULL, "SetupButton Failed", "Error", MB_ICONERROR);
		return 1;
	}
	// Setup labels
	bReturn = pRBUserIOData->SetNumberOfLabels (3);
   if (!bReturn) 
	{
		MessageBox (NULL, "SetNumberOfLabels Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (0, 10, 275, 25, "Button Click Times: 0");
   if (!bReturn) 
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (1, 150, 350, 12, "Not Checked");
   if (!bReturn) 
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (2, 130, 460, 25, "plus 1 is 2");
   if (!bReturn) 
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	// Setup check box
	bReturn = pRBUserIOData->SetNumberOfCheckBoxes (1);
   if (!bReturn) 
	{
		MessageBox (NULL, "SetNumberOfCheckBoxes Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupCheckBox (0, 10, 350, false, "Check Box");
   if (!bReturn) 
	{
		MessageBox (NULL, "SetupCheckBox Failed", "Error", MB_ICONERROR);
		return 1;
	}
	// Setup edit box
	bReturn = pRBUserIOData->SetNumberOfEdits (1);
   if (!bReturn) 
	{
		MessageBox (NULL, "SetNumberOfEdits Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupEdit (0, 10, 425, 100, "1", "Enter a Number:");
   if (!bReturn) 
	{
		MessageBox (NULL, "SetupEdit Failed", "Error", MB_ICONERROR);
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
	
	// Output slider data once a second
	if (g_dLastOutputTime + 1  <= fTime)
	{
		// Put the data into a string to be used for the display routine
		strstream strmData;
		strmData << fTime << '\t' << nSliderValue << ends;

		bReturn = pRBUserIOData->SetOutputListData (0, strmData.str ());
		if (!bReturn) 
		{
			MessageBox (NULL, "SetOutputListData Failed", "Error", MB_ICONERROR);
			return 1;
		}

		// Save the output time
		g_dLastOutputTime = fTime;
	}

	// Check button
	bool bButtonClicked;
	bReturn = pRBUserIOData->GetButtonClicked (0, bButtonClicked);
	if (!bReturn) 
	{
		MessageBox (NULL, "GetButtonClicked Failed", "Error", MB_ICONERROR);
		return 1;
	}
	
	ostringstream strmData; // Output stream used to set several labels

	if (bButtonClicked)
	{
		// Output to label
		strmData.str("");
		strmData << "Button Click Times: " << ++g_nNumberButtonClicks << ends;
		bReturn = pRBUserIOData->SetLabelValue (0, strmData.str ());
		if (!bReturn) 
		{
			MessageBox (NULL, "SetOutputListData Failed", "Error", MB_ICONERROR);
			return 1;
		}
	}

	// Check the check box
	bool bCheckBoxValue;
	bReturn = pRBUserIOData->GetCheckBoxValue (0, bCheckBoxValue);
	if (!bReturn) 
	{
		MessageBox (NULL, "GetCheckBoxValue Failed", "Error", MB_ICONERROR);
		return 1;
	}

	if (bCheckBoxValue)
	{
		strmData.str("");
		strmData << "Checked" << ends;
		pRBUserIOData->SetLabelValue (1, strmData.str ());
	}
	else
	{
		strmData.str("");
		strmData << "Not Checked" << ends;
		pRBUserIOData->SetLabelValue (1, strmData.str ());
	}
	
	// Read edit
	string strValue;
	bReturn = pRBUserIOData->GetEditValue (0, strValue);
	if (!bReturn)
	{
		MessageBox (NULL, "GetEditValue Failed", "Error", MB_ICONERROR);
		return 1;
	}

	double dEditValue = atof (strValue.c_str ()); // will return 0 if it is not a number

	dEditValue += 1.0;

	strmData.str("");
	strmData << "plus 1 is " << dEditValue << ends;
	pRBUserIOData->SetLabelValue (2, strmData.str ());

	
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