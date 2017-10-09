// Control.cpp : Defines the entry point for the DLL application.
//

/*******************************************************************\
	This demo was developed by Duane Marhefka and ported to RobotBuilder.
	The naming and coding conventions were left mostly unchanged.

\*******************************************************************/

#include "stdafx.h"
#include "Control.h"

#include <dmSystem.hpp>
#include <dmIntegrator.hpp>
#include <dmEnvironment.hpp>
#include <RBUserIOData.h>

#include <dmMobileBaseLink.hpp>
#include <dmMDHLink.hpp>
#include <dmContactModel.hpp>
#include <dmArticulation.hpp>
#include <dmu.h>

#include <sstream>

#define XC	0
#define YC	1
#define ZC	2

/*** GLOBALS ***/
dmMobileBaseLink *refMember;
dmMDHLink *frameLink[4];
dmMDHLink *thighLink[4];
dmMDHLink *shankLink[4];
dmMDHLink *slideLink[4];
dmContactModel *contactSensor[4];

float desHeight = 0.70f;
float desVelocity = 1.50f;

double idt = .00025;  // The timestep of the simulation (this must match the value
	// specified in the .cfg file

Float v_fwd;
Float v_lat;
Float v_vert;
Float swingTimeRemaining[4];
Float swingPeriod[] = {(Float) 0.110, (Float) 0.110, (Float) 0.160, (Float) 0.160};

float swingParam[4][4];
float ballnutParam[4][4];
float tdownSwingAng[4];
float thrustLength[4];
float ballnut[] = {0.227415f, 0.227415f, 0.227415f, 0.227415f};
float ballnutRate[4];

float t_swing[4];
float t_lift[4];
float x_o[4];
float y_o[4];
float vy_d = 1.0;
float frame_lift[4];
enum legPhase{ HOLD, COMPRESS, THRUST, FORE_LIFT, SWING };
enum legPhase legPhases[] = {HOLD, HOLD, HOLD, HOLD};
int hadContact[] = {FALSE, FALSE, FALSE, FALSE};

enum bodyPhases { INITIAL_FLIGHT, LANDING_PREP, CONTACT };
enum bodyPhases phase = INITIAL_FLIGHT;

#define RAIBERT

#ifdef RAIBERT
struct raibert_vars
{
  float T_stance[4]; // stance time of fore/hind leg
  float K_v;         // velocity error gain
  float K_h;         // height error gain
  float thrust;      // fore/hind leg thrust
};

struct raibert_vars raibert;
#endif

// UserIO stuff
enum {VALUE_LABEL, DERIVATIVE_LABEL, 
		YAW_LABEL, YAW_VALUE, YAW_DERIVATIVE,
		PITCH_LABEL, PITCH_VALUE, PITCH_DERIVATIVE,
		ROLL_LABEL, ROLL_VALUE, ROLL_DERIVATIVE,
		FWD_VEL_LABEL, FWD_VEL_VALUE,
		LAT_VEL_LABEL, LAT_VEL_VALUE,
		HEIGHT_LABEL, HEIGHT_VALUE} enumLabels;
enum {DESIRED_HEIGHT, DESIRED_VELOCITY} enumSliders;



/*** METHODS ***/
void computeEuler(Quaternion qRef, SpatialVector vRef,
		  EulerAngles euler, EulerAngles eulerRate);
void computeSplineParams( float, float, float, float, float, float * );

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

	// Setup UserIO
	
	int nValueColumn = 80; // X value for the labels in the value column
	int nDerivativeColumn = 170; // X value for the labels in the derivative column
	int nLabelColumn = 10; // Left margin of the data
	int nLineSpacing = 20; // Y count between lines
	int nFirstLine = 20; // Y count to first line
	bool bReturn; // Return values for the functions.  If a function fails, the InitializeDMControl
		// will return, and the developer can review the code for the error
	int nCurrentLine = 0; // Holds the Y for the current line
	bReturn = pRBUserIOData->SetNumberOfLabels (17);
	if (!bReturn)
	{
		MessageBox (NULL, "SetNumberOfLabels Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine = nFirstLine;
	bReturn = pRBUserIOData->SetupLabel (VALUE_LABEL, nValueColumn, nCurrentLine, 5, "Value");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (DERIVATIVE_LABEL, nDerivativeColumn, nCurrentLine, 10, "Derivative");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;
	bReturn = pRBUserIOData->SetupLabel (YAW_LABEL, nLabelColumn, nCurrentLine, 3, "Yaw");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (YAW_VALUE, nValueColumn, nCurrentLine, 8, "0");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (YAW_DERIVATIVE, nDerivativeColumn, nCurrentLine, 8, "0");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;
	bReturn = pRBUserIOData->SetupLabel (PITCH_LABEL, nLabelColumn, nCurrentLine, 5, "Pitch");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (PITCH_VALUE, nValueColumn, nCurrentLine, 5, "0");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (PITCH_DERIVATIVE, nDerivativeColumn, nCurrentLine, 8, "0");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;
	bReturn = pRBUserIOData->SetupLabel (ROLL_LABEL, nLabelColumn, nCurrentLine, 4, "Roll");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (ROLL_VALUE, nValueColumn, nCurrentLine, 5, "0");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (ROLL_DERIVATIVE, nDerivativeColumn, nCurrentLine, 8, "0");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;
	bReturn = pRBUserIOData->SetupLabel (FWD_VEL_LABEL, nLabelColumn, nCurrentLine, 7, "Fwd Vel");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (FWD_VEL_VALUE, nValueColumn, nCurrentLine, 5, "0");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;
	bReturn = pRBUserIOData->SetupLabel (LAT_VEL_LABEL, nLabelColumn, nCurrentLine, 7, "Lat Vel");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (LAT_VEL_VALUE, nValueColumn, nCurrentLine, 5, "0");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;
	bReturn = pRBUserIOData->SetupLabel (HEIGHT_LABEL, nLabelColumn, nCurrentLine, 6, "Height");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	bReturn = pRBUserIOData->SetupLabel (HEIGHT_VALUE, nValueColumn, nCurrentLine, 5, "0");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupLabel Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nLineSpacing;

	// Sliders
	const int nSliderPreSpacing = 20; // Space between first slider and the label above it
	const int nSliderWidth = 190; // Width of slider control
	const int nSliderHeight = 60; // Height of slider control
	const int nSliderSpacing = nSliderHeight + 20; // Space between the sliders
	const int nSliderColumn = nLabelColumn; // x count for start of slider controls
	bReturn = pRBUserIOData->SetNumberOfSliders (2);
	if (!bReturn)
	{
		MessageBox (NULL, "SetupSlider Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nSliderPreSpacing;
	bReturn = pRBUserIOData->SetupSlider (DESIRED_HEIGHT, nSliderColumn, nCurrentLine, 
		nSliderWidth, nSliderHeight, 65, 85, 70, "Desired Height (cm)");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupSlider Failed", "Error", MB_ICONERROR);
		return 1;
	}
	nCurrentLine += nSliderSpacing;
	bReturn = pRBUserIOData->SetupSlider (DESIRED_VELOCITY, nSliderColumn, nCurrentLine, 
		nSliderWidth, nSliderHeight, 0, 30, 15, "Desired Vel (tenths of m/s)");
	if (!bReturn)
	{
		MessageBox (NULL, "SetupSlider Failed", "Error", MB_ICONERROR);
		return 1;
	}


#ifdef RAIBERT
  // Increasing K_v decreases steady state velocity error, but produces
  // unacceptably large disturbances on height when making velocity steps.
  // Increasing K_h produces unacceptably high overshoot to height steps.
  raibert.T_stance[0] = 0.0;
  raibert.T_stance[1] = 0.0;
  raibert.T_stance[2] = 0.0;
  raibert.T_stance[3] = 0.0;
  raibert.K_v = 0.05f;
  raibert.K_h = 0.1f;
  raibert.thrust = 0.035f;
#endif
	
	dmArticulation *art = dynamic_cast<dmArticulation*>(pSystem);

  refMember = dynamic_cast<dmMobileBaseLink*>(dmuFindObject("body", art));

  // Find frame link pointers.
  frameLink[0] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg1Frame", art));
  frameLink[1] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg2Frame", art));
  frameLink[2] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg3Frame", art));
  frameLink[3] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg4Frame", art));

  // Find thigh link pointers.
  thighLink[0] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg1Thigh", art));
  thighLink[1] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg2Thigh", art));
  thighLink[2] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg3Thigh", art));
  thighLink[3] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg4Thigh", art));

  // Find shank link pointers.
  shankLink[0] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg1Shank", art));
  shankLink[1] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg2Shank", art));
  shankLink[2] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg3Shank", art));
  shankLink[3] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg4Shank", art));

  // Find slide link pointers.
  slideLink[0] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg1Slide", art));
  slideLink[1] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg2Slide", art));
  slideLink[2] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg3Slide", art));
  slideLink[3] = dynamic_cast<dmMDHLink*>(dmuFindObject("leg4Slide", art));

  // Find foot contact sensors.
  contactSensor[0] = dynamic_cast<dmContactModel*>(shankLink[0]->getForce(0));
  contactSensor[1] = dynamic_cast<dmContactModel*>(shankLink[1]->getForce(0));
  contactSensor[2] = dynamic_cast<dmContactModel*>(shankLink[2]->getForce(0));
  contactSensor[3] = dynamic_cast<dmContactModel*>(shankLink[3]->getForce(0));

  // Should check that the links were found
	
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
CONTROL_API int UninitializeDMControl(dmSystem* pSystem, RBUserIOData *pRBUserIOData)
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
                           float time)

{
  // Controller parameters
  float propGain[] =  {1000.0, 2000.0, 25800.0};  // ab/ad, swing, spring
  float derivGain[] = {  25.0,   50.0,   100.0};
  float extRetPeriod = 0.080f;

  float hardPropGain  = 75000.0;  // leg spring hard stop
  float hardDerivGain =   500.0;

  // link parameters.
  float l1 = 0.500f;       // length of shank from hinge to toe
  float l2 = 0.140f;       // length of shank from hinge to ballscrew motor
  float l3 = 0.240f;       // length of thigh from hip to shank
  float l4 = 0.360f;       // length of thigh from hip to slide mount
  float alpha = 1.91987f;  // bend angle in thigh (rad) (= 130.0 deg)
  float r = 0.496287f;     // thigh end-to-end distance
  float gamma = 0.75000f;  // angle between r and l3
  float lso = 0.185f;      // Distance from controlled (inner) ballnut side
                          // to slide rotational axis with spring at rest:
                          // ballnut (0.015) + spring (0.15) + slide 0.02)
  float shank_td = 1.55998f;  // shank state variable at touchdown
  float shank_tof = 1.55998f; // shank state variable at top of flight
  float leg_length_td = 0.556951f; // hip to toe distance at leg touchdown

  // computed link parameters
  float beta_td;             // angle between thigh and hip-to-foot vec. at td

  beta_td = 1.11450f;
  float ballnut_td = 0.227415f;
  float ballnut_tof = 0.227415f;

  float thigh_des;
  float shank_des;
  float length_des;
  float d_des;
  float beta_des;
  
  // link state variables
  float frame[4], frameRate[4];
  float thigh[4], thighRate[4];
  float shank[4], shankRate[4];
  float slide[4], slideRate[4];

  // Get state of the quadruped body.
  Float sRef[7];         // [quat pos]
  static SpatialVector vRef;    // [ang_vel lin_vel]// Using static fixed the problem of Run-time error (stack corruputed around vRef)
  refMember->getState(sRef, vRef);
  EulerAngles euler, eulerRate;

  // Compute current euler angles and rates.
  computeEuler(&sRef[0], &vRef[0], euler, eulerRate);

  v_fwd = + vRef[3]*cos(euler[0]) + vRef[4]*sin(euler[0]);
  v_lat = - vRef[3]*sin(euler[0]) + vRef[4]*cos(euler[0]);
  v_vert = vRef[5];

	// Update the UserIO stuff
	bool bReturn; // Holds the return value.  If fail, return 1, to stop the simulation.
		// The developer can then go back to find the error
	ostringstream strmData; // Holds the value to send to the UserIO
	strmData.flags (ios::fixed);
	/// Yaw
	strmData << setprecision (3) << euler[0]*180.0/3.14159 << ends;
	bReturn = pRBUserIOData->SetLabelValue (YAW_VALUE, strmData.str ());
	if (!bReturn)
	{
		MessageBox (NULL, "SetLabelValue Failed", "Error", MB_ICONERROR);
		return 1;
	}
	/// Pitch
	// Clear the string
	strmData.str("");
	strmData << setprecision (3) << euler[1]*180.0/3.14159 << ends;
	bReturn = pRBUserIOData->SetLabelValue (PITCH_VALUE, strmData.str ());
	if (!bReturn)
	{
		MessageBox (NULL, "SetLabelValue Failed", "Error", MB_ICONERROR);
		return 1;
	}
	/// Roll
	// Clear the string
	strmData.str("");
	strmData << setprecision (3) << euler[2]*180.0/3.14159 << ends;
	bReturn = pRBUserIOData->SetLabelValue (ROLL_VALUE, strmData.str ());
	if (!bReturn)
	{
		MessageBox (NULL, "SetLabelValue Failed", "Error", MB_ICONERROR);
		return 1;
	}
	/// Yaw Derivative
	// Clear the string
	strmData.str("");
	strmData << setprecision (3) << eulerRate[0]*180.0/3.14159 << ends;
	bReturn = pRBUserIOData->SetLabelValue (YAW_DERIVATIVE, strmData.str ());
	if (!bReturn)
	{
		MessageBox (NULL, "SetLabelValue Failed", "Error", MB_ICONERROR);
		return 1;
	}
	/// Pitch Derivative
	// Clear the string
	strmData.str("");
	strmData << setprecision (3) << eulerRate[1]*180.0/3.14159 << ends;
	bReturn = pRBUserIOData->SetLabelValue (PITCH_DERIVATIVE, strmData.str ());
	if (!bReturn)
	{
		MessageBox (NULL, "SetLabelValue Failed", "Error", MB_ICONERROR);
		return 1;
	}
	/// Roll Derivative
	// Clear the string
	strmData.str("");
	strmData << setprecision (3) << eulerRate[2]*180.0/3.14159 << ends;
	bReturn = pRBUserIOData->SetLabelValue (ROLL_DERIVATIVE, strmData.str ());
	if (!bReturn)
	{
		MessageBox (NULL, "SetLabelValue Failed", "Error", MB_ICONERROR);
		return 1;
	}
	/// Fwd Vel
	// Clear the string
	strmData.str("");
	strmData << setprecision (2) << v_fwd << ends;
	bReturn = pRBUserIOData->SetLabelValue (FWD_VEL_VALUE, strmData.str ());
	if (!bReturn)
	{
		MessageBox (NULL, "SetLabelValue Failed", "Error", MB_ICONERROR);
		return 1;
	}
	/// Lat Vel
	// Clear the string
	strmData.str("");
	strmData << setprecision (2) << v_lat << ends;
	bReturn = pRBUserIOData->SetLabelValue (LAT_VEL_VALUE, strmData.str ());
	if (!bReturn)
	{
		MessageBox (NULL, "SetLabelValue Failed", "Error", MB_ICONERROR);
		return 1;
	}
	/// Height
	// Clear the string
	strmData.str("");
	strmData << setprecision (2) << sRef[6] << ends;
	bReturn = pRBUserIOData->SetLabelValue (HEIGHT_VALUE, strmData.str ());
	if (!bReturn)
	{
		MessageBox (NULL, "SetLabelValue Failed", "Error", MB_ICONERROR);
		return 1;
	}

	// Pick up the desired height and velocity
	int nUserIOValue;
	bReturn = pRBUserIOData->GetSliderValue (DESIRED_HEIGHT, nUserIOValue);
	if (!bReturn)
	{
		MessageBox (NULL, "GetSliderValue Failed", "Error", MB_ICONERROR);
		return 1;
	}
	desHeight = (float)(nUserIOValue*0.001);
	bReturn = pRBUserIOData->GetSliderValue (DESIRED_VELOCITY, nUserIOValue);
	if (!bReturn)
	{
		MessageBox (NULL, "GetSliderValue Failed", "Error", MB_ICONERROR);
		return 1;
	}
	desVelocity = (float)(nUserIOValue * 0.1);


  CartesianVector position;
  position[0] = sRef[4];
  position[1] = sRef[5];
  position[2] = sRef[6];

  CartesianVector velocity;
  velocity[0] = vRef[3];
  velocity[1] = vRef[4];
  velocity[2] = vRef[5];

int i;
  // Get leg states.
  for ( i = 0; i < 4; i++)
    {
      frameLink[i]->getState(&frame[i], &frameRate[i]);
      thighLink[i]->getState(&thigh[i], &thighRate[i]);
      shankLink[i]->getState(&shank[i], &shankRate[i]);
      slideLink[i]->getState(&slide[i], &slideRate[i]);
    }

//  if (saveOutput)
//    {
//      simLog << endl
//	     << time << " "
//	     << euler[1] << " " << eulerRate[1] << " "
//	     << desVelocity << " " << v_fwd << " "
//	     << desHeight << " " << position[ZC] << " ";
//    }


  // compute swing:  the angle the hip-to-foot vector would make with the
  //                 vertical if the leg were at its touchdown length.
  //                 (ignore roll).

  float swing[4], swingRate[4];
  swing[0] =  thigh[0] + beta_td - euler[YC];
  swing[1] =  thigh[1] + beta_td - euler[YC];
  swing[2] = -thigh[2] - beta_td - euler[YC];
  swing[3] = -thigh[3] - beta_td - euler[YC];

  swingRate[0] =  thighRate[0] - eulerRate[YC];
  swingRate[1] =  thighRate[1] - eulerRate[YC];
  swingRate[2] = -thighRate[2] - eulerRate[YC];
  swingRate[3] = -thighRate[3] - eulerRate[YC];

  bool contact[4];
  for (i = 0; i < 4; i++)
    contact[i] = contactSensor[i]->getContactState(0);


  if ( (phase == INITIAL_FLIGHT) && (v_vert <= 0) )
    {
      phase = LANDING_PREP;
      hadContact[0] = hadContact[1] = FALSE;
      hadContact[2] = hadContact[3] = FALSE;

      if (position[XC] >= 16.0)
	{
	  // Get state of the quadruped body.
	  Float sRef[7];
	  SpatialVector vRef;
	  refMember->getState(sRef, vRef);

	  // set the x position to zero
	  sRef[4] = 0.0;
	  refMember->setState(sRef, vRef);
	  unsigned int sysIndex = 0;
	  pIntegrator->removeSystem (sysIndex);
	  pIntegrator->addSystem(pSystem); // resync integrator with system.
	}

#ifdef RAIBERT
      // Overwrite fuzzy with Raibert control values.
      float velErr = desVelocity - v_fwd;

      tdownSwingAng[0] = (float)(asin( (raibert.T_stance[0]*v_fwd/2.0 -  raibert.K_v*velErr)/leg_length_td ));
      tdownSwingAng[1] = (float)(asin( (raibert.T_stance[1]*v_fwd/2.0 -
			        raibert.K_v*velErr)/
				leg_length_td ));
      tdownSwingAng[2] = (float)(asin( (raibert.T_stance[2]*v_fwd/2.0 -
			        raibert.K_v*velErr)/
				leg_length_td ));
      tdownSwingAng[3] = (float)(asin( (raibert.T_stance[3]*v_fwd/2.0 -
			        raibert.K_v*velErr)/
				leg_length_td ));

      thrustLength[0] = raibert.thrust;
      thrustLength[1] = raibert.thrust;
      thrustLength[2] = raibert.thrust;
      thrustLength[3] = raibert.thrust;

#endif

      // Recompute leg swing spline for legs in SWING phase.
      for (int i = 0; i < 4; i++)
	{
	  if (legPhases[i] == SWING)
	    {
	      swingTimeRemaining[i] = swingPeriod[i] - (time - t_swing[i]);
	      computeSplineParams( swing[i], swingRate[i],
				   tdownSwingAng[i], 0.0,
				   swingTimeRemaining[i], swingParam[i] );

	      computeSplineParams( ballnut[i], ballnutRate[i],
				   ballnut_td, 0.0,
				   swingTimeRemaining[i], ballnutParam[i] );

	      t_swing[i] = time;
	    }
	}
    }

  if ( (phase == LANDING_PREP) && 
       (contact[0] || contact[1] || contact[2] || contact[3]) )
    phase = CONTACT;

  if (phase == CONTACT)
    {
      if (contact[0])
	hadContact[0] = TRUE;
      if (contact[1])
	hadContact[1] = TRUE;
      if (contact[2])
	hadContact[2] = TRUE;
      if (contact[3])
	hadContact[3] = TRUE;
    }

  if ( (phase == CONTACT) && 
       !contact[0] &&
       !contact[1] &&
       !contact[2] &&
       !contact[3] &&
       hadContact[0] &&
       hadContact[1] &&
       hadContact[2] &&
       hadContact[3] )
    {
      phase = INITIAL_FLIGHT;
    }


  for (i = 0; i < 4; i++)
    {
      // Perform leg phase switches.
      switch (legPhases[i])
	{
	case FORE_LIFT:
	  if ( (time - t_lift[i]) >= 0.050)
	    {
	      // cout << "SWING:  " << i << endl;

	      legPhases[i] = SWING;
	      t_swing[i] = time;
	      swingTimeRemaining[i] = swingPeriod[i];

	      // Compute leg spline for swing axis.
	      computeSplineParams( swing[i], swingRate[i],
				   tdownSwingAng[i], 0.0,
				   swingTimeRemaining[i],
				   swingParam[i] );

	      // Compute leg retraction spline for ballnut.
	      computeSplineParams( ballnut[i], ballnutRate[i],
				   ballnut_tof, 0.0,
				   swingTimeRemaining[i], 
				   ballnutParam[i] );
	    }

	  break;

	case SWING:
	  if ((time - t_swing[i]) >= swingTimeRemaining[i])
	    {
	      legPhases[i] = HOLD;
	      // cout << "Holding leg: " << i << endl;
	    }
	  break;

	case HOLD:
	  if (contact[i])
	    {
	      legPhases[i] = COMPRESS;
	      // cout << "Compressing leg: " << i << endl;
#ifdef RAIBERT
	      raibert.T_stance[i] = 0.0;
#endif
	    }
	  break;

	case COMPRESS:
	  if ( (slide[i] >= (ballnut_td + lso + 0.01)) && (slideRate[i] < 0) )
	    {
	      legPhases[i] = THRUST;
	      // cout << "Thrusting leg: " << i << endl;
	    }
#ifdef RAIBERT
	  raibert.T_stance[i] += (float)idt;
#endif
	  break;

	case THRUST:
	  if (!contact[i])
	    {
	      if ( (i == 0) || (i == 1) ) // fore legs
		{
		  /*
		  cout << "FORE LIFT: " << i 
		       << ", " << slide[i] - ballnut[i]
		       << ", " << "slideRate: " << slideRate[i]
		       << ", " << "ballnutRate: " << ballnutRate[i] 
		       << endl;
		       */
		  legPhases[i] = FORE_LIFT;
		  t_lift[i] = time;
		  frame_lift[i] = frame[i];

		  d_des = ballnut[i] + lso;
		  shank_des = ( gamma +
				(float)(acos((l2*l2 + r*r - d_des*d_des)/(2.0*l2*r)) ));

		  x_o[i] = ( l3*sin(thigh[i] - euler[1]) + 
			     l1*sin(thigh[i] - euler[1] + shank_des) );
		  y_o[i] = ( -l3*cos(thigh[i] - euler[1]) - 
			     l1*cos(thigh[i] - euler[1] + shank_des) );
		}
	      else  // hind legs
		{
		  legPhases[i] = SWING;
		  t_swing[i] = time;
		  swingTimeRemaining[i] = swingPeriod[i];

		  // Compute leg spline for swing axis.
		  computeSplineParams( swing[i], swingRate[i],
				       tdownSwingAng[i], 0.0,
				       swingTimeRemaining[i],
				       swingParam[i] );

		  // Compute leg retraction spline for ballnut.
		  computeSplineParams( ballnut[i], ballnutRate[i],
				       ballnut_tof, 0.0,
				       swingTimeRemaining[i], 
				       ballnutParam[i] );
		}
	    }
#ifdef RAIBERT
	  raibert.T_stance[i] += (float)idt;
#endif
	  break;

	}
    }

  float t, desPos, desRate;
  for (i = 0; i < 4; i++)
    {
      Float inputs[3];  // frame, thigh, slide (legspring)

      switch (legPhases[i])
	{

	case HOLD:
      
	  // Frame axis control.
	  //desPos = 1.570796328; // Put leg under body.
	  //desPos += asin( (raibert.T_stance[i]*v_lat/2.0)/leg_length_td );
	  //desPos += 0.200*v_lat - 0.0025d*(4.0 - position[YC]);
	  /*
	  if ( (i == 0) || (i == 1) ) // Fore legs.
	    desPos += (0.050*eulerRate[0] + 0.075*euler[0]);
	  else // Hind legs
	    desPos -= (0.050*eulerRate[0] + 0.075*euler[0]);
	    */

	  if ( (i == 0) || (i == 1) ) // Fore legs.
	    desPos = ( 1.570796328 +
		      asin( (raibert.T_stance[i]*v_lat/2.0)/leg_length_td -
			     0.100*(0.0 - v_lat) + 
			     0.050*eulerRate[0] + 0.075*euler[0] ) );
	  else // Hind legs.
	    desPos = ( 1.570796328 +
		       asin( (raibert.T_stance[i]*v_lat/2.0)/leg_length_td -
			     0.100*(0.0 - v_lat) - 
			     0.050*eulerRate[0] - 0.075*euler[0] ) );

	  desRate = 0.0;
	  inputs[0] = ( propGain[0]*(desPos - frame[i]) +
			derivGain[0]*(desRate - frameRate[i]) );

	  // Swing axis control.
	  desPos = tdownSwingAng[i];
	  desRate = 0.0;

	  // Convert swing values to thigh values.
	  if ( (i == 0) || (i == 1) )  // fore legs
	    {
	      desPos = desPos - beta_td + euler[YC];
	      desRate = desRate + eulerRate[YC];
	    }
	  else  // hind legs
	    {
	      desPos = -desPos - beta_td - euler[YC];
	      desRate = -desRate - eulerRate[YC];
	    }
	  inputs[1] = ( propGain[1]*(desPos - thigh[i]) +
			derivGain[1]*(desRate - thighRate[i]) );


	  // Slide control.
	  ballnut[i] = ballnut_td;
	  desPos = ballnut_td + lso;
	  ballnutRate[i] = desRate = 0.0;
	  if ( slide[i] >= desPos )  // Spring extended.
	    inputs[2] = ( propGain[2]*(desPos - slide[i]) +
			  derivGain[2]*(desRate - slideRate[i]) );
	  else    // Spring closed (hard stop)
	    inputs[2] = ( hardPropGain*(desPos - slide[i]) +
			  hardDerivGain*(desRate - slideRate[i]) );

	  break;


	case COMPRESS:

	  // Frame axis control (servo body roll).
	  inputs[0] = (Float)(( 100.0*(0.0 + euler[2]) +
			  5.0*(0.0 + eulerRate[2]) ));

	  // Swing axis control.
	  inputs[1] = 0.0;

	  // Slide control.
	  ballnut[i] = ballnut_td;
	  desPos = ballnut_td + lso;
	  ballnutRate[i] = desRate = 0.0;
	  if ( slide[i] >= desPos )  // Spring extended.
	    inputs[2] = ( propGain[2]*(desPos - slide[i]) +
			  derivGain[2]*(desRate - slideRate[i]) );
	  else    // Spring closed (hard stop)
	    inputs[2] = ( hardPropGain*(desPos - slide[i]) +
			  hardDerivGain*(desRate - slideRate[i]) );

	  break;


	case THRUST:

	  // Frame axis control (servo body roll).
	  inputs[0] = (Float)(( 100.0*(0.0 + euler[2]) +
			  5.0*(0.0 + eulerRate[2]) ));

	  // Swing axis control.
	  inputs[1] = 0.0;

	  // Slide control.
	  ballnut[i] = ballnut_td - thrustLength[i];
	  desPos = ballnut_td - thrustLength[i] + lso;
	  ballnutRate[i] = desRate = 0.0;
	  if ( slide[i] >= desPos )  // Spring extended.
	    inputs[2] = ( propGain[2]*(desPos - slide[i]) +
			  derivGain[2]*(desRate - slideRate[i]) );
	  else    // Spring closed (hard stop)
	    inputs[2] = ( hardPropGain*(desPos - slide[i]) +
			  hardDerivGain*(desRate - slideRate[i]) );

	  break;


	case FORE_LIFT:
	  
	  // Frame axis control.
	  desPos = frame_lift[i];
	  desRate = 0.0;
	  inputs[0] = ( propGain[0]*(desPos - frame[i]) +
			derivGain[0]*(desRate - frameRate[i]) );


	  // Swing axis control.
	  t = (time - t_lift[i]);
	  length_des = sqrt( x_o[i]*x_o[i] + 
			     (y_o[i] + vy_d*t)*(y_o[i] + vy_d*t) );

	  shank_des = (float)(acos( (length_des*length_des - l1*l1 - l3*l3)/
			    (2.0*l1*l3) ));

	  d_des = (float)(sqrt(l2*l2 + r*r - 2.0*l2*r*cos(shank_des-gamma)));

	  beta_des = atan2( (l1*sin(shank_des)/length_des),
			    (float)(((length_des*length_des + l3*l3 - l1*l1)/
			    (2.0*length_des*l3))) );

	  thigh_des = ( euler[1] - beta_des + 
			atan2( x_o[i], - (y_o[i] + vy_d*t) ) );


	  desPos = thigh_des;
	  desRate = ( -cos(thigh_des-euler[1]+shank_des)/
		      (l3*sin(shank_des))*vy_d + eulerRate[1]);
	  inputs[1] = ( propGain[1]*(desPos - thigh[i]) +
			derivGain[1]*(desRate - thighRate[i]) );


	  // slide control.
	  ballnut[i] = d_des - lso;
	  ballnutRate[i] = ( l2*r*sin(shank_des-gamma)*
			     (l3*cos(thigh_des-euler[1]) 
			      + l1*cos(thigh_des-euler[1]+shank_des))/
			     (l1*l3*d_des*sin(shank_des)) );
	  desPos = d_des;
	  desRate = ballnutRate[i];

	  if ( slide[i] >= desPos )  // Spring extended.
	    inputs[2] = ( propGain[2]*(desPos - slide[i]) +
			  derivGain[2]*(desRate - slideRate[i]) );
	  else    // Spring closed (hard stop)
	    inputs[2] = ( hardPropGain*(desPos - slide[i]) +
			  hardDerivGain*(desRate - slideRate[i]) );

	  break;

	case SWING:
	  
	  // Frame axis control.
	  //desPos = 1.570796328; // Put leg under body.
	  //desPos += asin( (raibert.T_stance[i]*v_lat/2.0)/leg_length_td );
	  //desPos += 0.200*v_lat - 0.0025*(4.0 - position[YC]);

	  /*
	  if ( (i == 0) || (i == 1) ) // Fore legs.
	    desPos += (0.050*eulerRate[0] + 0.075*euler[0]);
	  else // Hind legs
	    desPos -= (0.050*eulerRate[0] + 0.075*euler[0]);
	    */

	  if ( (i == 0) || (i == 1) ) // Fore legs.
	    desPos = ( 1.570796328 +
		       asin( (raibert.T_stance[i]*v_lat/2.0)/leg_length_td -
			     0.100*(0.0 - v_lat) + 
			     0.050*eulerRate[0] + 0.075*euler[0] ) );
	  else // Hind legs.
	    desPos = ( 1.570796328 +
		       asin( (raibert.T_stance[i]*v_lat/2.0)/leg_length_td -
			     0.100*(0.0 - v_lat) - 
			     0.050*eulerRate[0] - 0.075*euler[0] ) );


	  desRate = 0.0;
	  inputs[0] = ( propGain[0]*(desPos - frame[i]) +
			derivGain[0]*(desRate - frameRate[i]) );

	  // Swing axis control.
	  t = (time - t_swing[i]);
	  desPos = (swingParam[i][0] + swingParam[i][1]*t
		    + swingParam[i][2]*t*t + swingParam[i][3]*t*t*t);
	  desRate = (float)((swingParam[i][1] + 2.0*swingParam[i][2]*t 
		     + 3.0*swingParam[i][3]*t*t));

	  // Convert swing values to thigh values.
	  if ( (i == 0) || (i == 1) )  // fore legs
	    {
	      desPos = desPos - beta_td + euler[YC];
	      desRate = desRate + eulerRate[YC];
	    }
	  else  // hind legs
	    {
	      desPos = -desPos - beta_td - euler[YC];
	      desRate = -desRate - eulerRate[YC];
	    }
	  inputs[1] = ( propGain[1]*(desPos - thigh[i]) +
			derivGain[1]*(desRate - thighRate[i]) );

	  // slide control.
	  t = (time - t_swing[i]);
	  desPos = (ballnutParam[i][0] + ballnutParam[i][1]*t
		    + ballnutParam[i][2]*t*t + ballnutParam[i][3]*t*t*t);
	  desRate = (float)((ballnutParam[i][1] + 2.0*ballnutParam[i][2]*t 
		     + 3.0*ballnutParam[i][3]*t*t));

	  // Convert from ballnut to slide.
	  ballnut[i] = desPos;
	  ballnutRate[i] = desRate;
	  desPos = desPos + lso;
	  desRate = desRate;

	  if ( slide[i] >= desPos )  // Spring extended.
	    inputs[2] = ( propGain[2]*(desPos - slide[i]) +
			  derivGain[2]*(desRate - slideRate[i]) );
	  else    // Spring closed (hard stop)
	    inputs[2] = ( hardPropGain*(desPos - slide[i]) +
			  hardDerivGain*(desRate - slideRate[i]) );

	  break;
	}

      frameLink[i]->setJointInput( &inputs[0] );
      thighLink[i]->setJointInput( &inputs[1] );
      slideLink[i]->setJointInput( &inputs[2] );

//      if (saveOutput && ((i == 0) || (i == 2)))
//	{
//	  simLog << frame[i] << " " << frameRate[i] << " "
//		 << thigh[i] << " " << thighRate[i] << " "
//		 << ballnut[i] << " " << ballnutRate[i] << " "
//		 << slide[i] << " " << slideRate[i] << " "
//		 << inputs[0] << " "
//		 << inputs[1] << " "
//		 << inputs[2] << " ";
//	}
    }

  if ( (phase == INITIAL_FLIGHT) && (vRef[5] <= 0.0))
  {
#ifdef RAIBERT
	raibert.thrust += raibert.K_h*(desHeight - sRef[6]);
	if (raibert.thrust > 0.05)
	  {
	    raibert.thrust = 0.05f;
	    cout << "Thrust saturated..." << endl;
	  }
#endif
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


void computeEuler(Quaternion qRef, SpatialVector vRef,
		  EulerAngles euler, EulerAngles eulerRate)
{
  // Rotate about z by euler[0], than about y by euler[1],
  // then about x by euler[2].

  RotationMatrix Rcur;
  Rcur[0][0] = (Float)(1.0 - 2.0*qRef[1]*qRef[1] - 2.0*qRef[2]*qRef[2]);
  // Rcur[0][1] = 2.0*(qRef[0]*qRef[1] - qRef[2]*qRef[3]);
  // Rcur[0][2] = 2.0*(qRef[0]*qRef[2] + qRef[1]*qRef[3]);

  Rcur[1][0] = (Float)(2.0*(qRef[0]*qRef[1] + qRef[2]*qRef[3]));
  // Rcur[1][1] = 1.0 - 2.0*qRef[0]*qRef[0] - 2.0*qRef[2]*qRef[2];
  // Rcur[1][2] = 2.0*(qRef[1]*qRef[2] - qRef[0]*qRef[3]);

  Rcur[2][0] = (Float)(2.0*(qRef[0]*qRef[2] - qRef[1]*qRef[3]));
  Rcur[2][1] = (Float)(2.0*(qRef[1]*qRef[2] + qRef[0]*qRef[3]));
  Rcur[2][2] = (Float)(1.0 - 2.0*qRef[0]*qRef[0] - 2.0*qRef[1]*qRef[1]);

  // Compute current euler angles.
  euler[0] = atan2(Rcur[1][0], Rcur[0][0]);
  euler[1] = atan2(-Rcur[2][0], 
		   sqrt(Rcur[0][0]*Rcur[0][0] + 
			Rcur[1][0]*Rcur[1][0]));
  euler[2] = atan2(Rcur[2][1],Rcur[2][2]);


  // Compute current euler rates.
  eulerRate[0] = ( cos(euler[0])*tan(euler[1])*vRef[0] +
		   sin(euler[0])*tan(euler[1])*vRef[1] +
		   vRef[2] );
  eulerRate[1] = ( -sin(euler[0])*vRef[0] +
		   cos(euler[0])*vRef[1] );
  eulerRate[2] = ( cos(euler[0])/cos(euler[1])*vRef[0] +
		   sin(euler[0])/cos(euler[1])*vRef[1] );
}


//----------------------------------------------------------------------------
//    Summary: Computes cubic spline parameters. 
// Parameters: init_value - initial value of the variable
//             init_rate  - initial rate of change of the variable
//             final_value - final value of the variable
//             final_rate  - final rate of change of the variable
//             period - elapsed time between initial and final
//             splineParams - array to return spline parameters
//    Returns: None.
//----------------------------------------------------------------------------
void computeSplineParams( float init_value, float init_rate,
			  float final_value, float final_rate,
			  float period, float splineParams[4] )
{
  splineParams[0] = init_value;
  splineParams[1] = init_rate;
  splineParams[2] = (float)(( 3.0/(period*period)*(final_value - init_value)
		      - 2.0/period*init_rate - 1.0/period*final_rate ));
  splineParams[3] = (float)(( -2.0/(period*period*period)*(final_value - init_value)
		      + 1.0/(period*period)*(final_rate + init_rate) ));
}