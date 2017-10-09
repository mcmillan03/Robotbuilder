
#include "stdafx.h"
#include <math.h>

/**
*     Student Name #1
*     Student Name #2
*/

/**
*
* Changes the input array of joint angles from pulse units referenced to 
*   the nest position, to units of radians referenced to the Denavit-Hartenberg
*   zero position for the Mitsubishi RM-501
*
* Parameters:
*	a - an array of 5 floats holding the joint angles inputed (in pulse units)
*	JointAnglesInRadians - an array of 5 floats that is the output and will 
*       pass back the translated joint values (in radians referenced to the 
*       Denavit-Hartenberg zero position) to Control
*
*/
void TranslatePulseUnitsToRadians (const float a[], float JointAnglesInRadians[]) 
{
	JointAnglesInRadians[0] = a[0];
	JointAnglesInRadians[1] = a[1];
	JointAnglesInRadians[2] = a[2];
	JointAnglesInRadians[3] = a[3];
	JointAnglesInRadians[4] = a[4];
}

/**
*
* Finds the transform ^S T_T
*
* Parameters:
*	JointAnglesInRadians - an array of 5 floats that is the output and will 
*       pass back the translated joint values (in radians referenced to the 
*       Denavit-Hartenberg zero position)
*	Transform - the 4x4 of floats that passes back the transform
*
*/
void GetTransform (const float JointAnglesInRadians[], float Transform[][4])
{
	Transform[0][0] = 1;
	Transform[0][1] = 0;
	Transform[0][2] = 0;
	Transform[0][3] = 0;

	Transform[1][0] = 0;
	Transform[1][1] = 1;
	Transform[1][2] = 0;
	Transform[1][3] = 0;

	Transform[2][0] = 0;
	Transform[2][1] = 0;
	Transform[2][2] = 1;
	Transform[2][3] = 0;

	Transform[3][0] = 0;
	Transform[3][1] = 0;
	Transform[3][2] = 0;
	Transform[3][3] = 1; 
}