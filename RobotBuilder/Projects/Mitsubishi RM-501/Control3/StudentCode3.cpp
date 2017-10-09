
#include "stdafx.h"
#include "Control.h"

/**
*     Student Name #1
*     Student Name #2
*/

/**
*
* Routine to (1) compute the joint angles to generate a desired circular motion
* 	for the Mitsubishi RM-501, (2) implement PD control for the DC motors of
*	the Mitsubishi to follow the trajectory, and (3) output the desired and
*	actual positions of the gripper.
*
* Parameters:
*	SimulationTimeInSeconds - total simulation time in seconds.
*	ActualJointAnglesInPulseUnits - an array of 5 ints that is an input
*		containing the actual positions of the joints in pulse units.
*	ActualJointVelocitiesInPulseUnitsPerSecond - an array of 5 ints that is
*		an input containing the actual angular velocities of the joints in
*		pulse units per second.
*	InputVoltage - an array of 5 floats that is an output and will pass back
*		the DC motor voltage to achieve the desired joint angles.
*	DesiredJointAnglesInPulseUnits - an array of 5 ints that is the output
*		and will pass back the desired joint values (in pulse units).
*	DesiredGripperPosition - an array of 3 floats that is an output and will
*		pass back the desired position of the gripper.
*	ActualGripperPosition - an array of 3 floats that is an output and will
*		pass back the actual position of the gripper.
*
*/
void ComputeInputVoltage (double SimulationTimeInSeconds, const int ActualJointAnglesInPulseUnits[],
						 const int ActualJointVelocitiesInPulseUnitsPerSecond[],
						 float InputVoltage[], int DesiredJointAnglesInPulseUnits[], 
						 float DesiredGripperPosition[], float ActualGripperPosition[])
{
	float DesiredTransform[4][4];

	// Setup the initial desired transform (the x and y position components will be
	// adjusted later).
	DesiredTransform[0][0] = -1;
	DesiredTransform[0][1] = 0;
	DesiredTransform[0][2] = 0;
	DesiredTransform[0][3] = 275;

	DesiredTransform[1][0] = 0;
	DesiredTransform[1][1] = 1;
	DesiredTransform[1][2] = 0;
	DesiredTransform[1][3] = 0;

	DesiredTransform[2][0] = 0;
	DesiredTransform[2][1] = 0;
	DesiredTransform[2][2] = -1;
	DesiredTransform[2][3] = 54;

	DesiredTransform[3][0] = 0;
	DesiredTransform[3][1] = 0;
	DesiredTransform[3][2] = 0;
	DesiredTransform[3][3] = 1; 

	// Get the joint angles for that transform
	InverseKinematics (DesiredTransform, DesiredJointAnglesInPulseUnits);

	// Return the gripper position
	DesiredGripperPosition[0] = 0;
	DesiredGripperPosition[1] = 0;
	DesiredGripperPosition[2] = 0;


	int i;
	// Compute the DC motor voltages to implement PD control
	for (i = 0; i < 5; i++)
	{
		InputVoltage[i] = 0;
	}


	// Find the actual gripper position
	ActualGripperPosition[0] = 0;
	ActualGripperPosition[1] = 0;
	ActualGripperPosition[2] = 0;

}

