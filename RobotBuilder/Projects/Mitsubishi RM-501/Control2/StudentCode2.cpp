
#include "stdafx.h"
#include "Control.h"

/**
*     Student Name #1
*     Student Name #2
*/

/**
*
* Routine to compute the joint angles to generate a circular motion for the
*   Mitsubishi RM-501.
*
* Parameters:
*	SimulationTimeInSeconds - total simulation time in seconds.
*	JointAnglesInPulseUnits - an array of 5 floats that is the output and will 
*       pass back the translated joint values (in pulse units) to Control.
*	Position - an array of 3 floats that is an output and will pass back
*		the position of the gripper.
*
*/
void ComputeJointAngles (double SimulationTimeInSeconds, int JointAnglesInPulseUnits[], 
						 float Position[])
{
	// Calculate transform for the current time
	float Transform[4][4];

	Transform[0][0] = -1;
	Transform[0][1] = 0;
	Transform[0][2] = 0;
	Transform[0][3] = 275;

	Transform[1][0] = 0;
	Transform[1][1] = 1;
	Transform[1][2] = 0;
	Transform[1][3] = 0;

	Transform[2][0] = 0;
	Transform[2][1] = 0;
	Transform[2][2] = -1;
	Transform[2][3] = 54;

	Transform[3][0] = 0;
	Transform[3][1] = 0;
	Transform[3][2] = 0;
	Transform[3][3] = 1; 

	// Get the joint angles for that transform
	InverseKinematics (Transform, JointAnglesInPulseUnits);

	// Return the tool position
	Position[0] = Transform[0][3];
	Position[1] = Transform[1][3];
	Position[2] = Transform[2][3];
}


/**
*
* Changes the input array of joint angles from pulse units referenced to 
*   the nest position, to units of radians referenced to the Denavit-Hartenberg
*   zero position for the Mitsubishi RM-501
*
* Parameters:
*	@param JointAnglesInPulseUnits - an array of 5 ints holding the joint angles (in pulse units)
*	@param JointAnglesInRadians - an array of 5 floats that is the output and will 
*       pass back the translated joint values (in radians referenced to the 
*       Denavit-Hartenberg zero position)
*
*/
void TranslatePulseUnitsToRadians (const int JointAnglesInPulseUnits[], float JointAnglesInRadians[]) 
{
	JointAnglesInRadians[0] = (float) JointAnglesInPulseUnits[0];
	JointAnglesInRadians[1] = (float) JointAnglesInPulseUnits[1];
	JointAnglesInRadians[2] = (float) JointAnglesInPulseUnits[2];
	JointAnglesInRadians[3] = (float) JointAnglesInPulseUnits[3];
	JointAnglesInRadians[4] = (float) JointAnglesInPulseUnits[4];
}