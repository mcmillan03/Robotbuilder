/*****************************************************************************
 * DynaMechs: A Multibody Dynamic Simulation Library
 *
 * Copyright (C) 1994-2001  Scott McMillan   All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *****************************************************************************
 *     File: dmLoader_dm.cpp
 *   Author: Scott McMillan
 *  Created: 12 August 2001
 *  Summary: abstract loader base class for V 2.x configuration files
 *****************************************************************************/

#include <dmLoader_dm.hpp>

#include <glLoadModels.h>

#include <dmContactModel.hpp>
#include <dmRigidBody.hpp>
#include <dmMDHLink.hpp>
#include <dmRevDCMotor.hpp>
#include <dmRevoluteLink.hpp>
#include <dmPrismaticLink.hpp>
#include <dmSphericalLink.hpp>
#include <dmMobileBaseLink.hpp>

//----------------------------------------------------------------------------
dmLoader_dm::dmLoader_dm()
      : dmLoader()
{
}

//----------------------------------------------------------------------------
void dmLoader_dm::setContactParameters(dmRigidBody *body, ifstream &cfg_ptr)
{
   readConfigParameterLabel(cfg_ptr, "Number_of_Contact_Points");
   unsigned int num_points = (unsigned int) parseInt(cfg_ptr);

   if (num_points > 0)
   {
      readConfigParameterLabel(cfg_ptr, "Contact_Locations");

      CartesianVector *pos = new CartesianVector[num_points];

      for (unsigned int i=0; i<num_points; i++)
      {
         pos[i][0] = parseFloat(cfg_ptr);
         pos[i][1] = parseFloat(cfg_ptr);
         pos[i][2] = parseFloat(cfg_ptr);
      }

      dmContactModel *contact_model = new dmContactModel();
      contact_model->setContactPoints(num_points, pos);
      //contact_model->setEnvironment(&G_environment);
      body->addForce(contact_model);

      delete [] pos;
   }
}

//----------------------------------------------------------------------------
void dmLoader_dm::setRigidBodyParameters(dmRigidBody *body, ifstream &cfg_ptr)
{
   register int i;

// dynamic properties:
   CartesianTensor I_bar;
   CartesianVector cg_pos;

   readConfigParameterLabel(cfg_ptr, "Mass");
   Float mass = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Inertia");
   for (i=0; i<3; i++)
   {
      I_bar[i][0] = parseFloat(cfg_ptr);
      I_bar[i][1] = parseFloat(cfg_ptr);
      I_bar[i][2] = parseFloat(cfg_ptr);
   }

   readConfigParameterLabel(cfg_ptr, "Center_of_Gravity");
   for (i=0; i<3; i++)
   {
      cg_pos[i] = parseFloat(cfg_ptr);
   }

   body->setInertiaParameters(mass, I_bar, cg_pos);

#ifdef DM_HYDRODYNAMICS
// hydrodynamic properties:
   SpatialTensor I_added_mass;
   CartesianVector cb_pos;

   readConfigParameterLabel(cfg_ptr, "Volume");
   Float volume = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Added_Mass");
   for (i = 0; i < 6; i++)
      for (unsigned int j = 0; j < 6; j++)
      {
         I_added_mass[i][j] = parseFloat(cfg_ptr);
      }

   readConfigParameterLabel(cfg_ptr, "Center_of_Buoyancy");
   for (i=0; i<3; i++)
   {
      cb_pos[i] = parseFloat(cfg_ptr);
   }

// drag parameters
   readConfigParameterLabel(cfg_ptr, "Drag_Axis");
   int drag_axis = parseInt(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Cylinder_Bounds");
   Float cyl_min = parseFloat(cfg_ptr);
   Float cyl_max = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Cylinder_Radius");
   Float cyl_radius = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Drag_Coefficient");
   Float C_d = parseFloat(cfg_ptr);

   body->setHydrodynamicParameters(volume, I_added_mass, cb_pos,
                                   drag_axis,
                                   cyl_min, cyl_max, cyl_radius, C_d);
#endif

   setContactParameters(body, cfg_ptr);
}


//----------------------------------------------------------------------------
void dmLoader_dm::setJointFriction(dmLink *link, ifstream &cfg_ptr)
{
   readConfigParameterLabel(cfg_ptr, "Joint_Friction");
   Float joint_friction = parseFloat(cfg_ptr);

   link->setJointFriction(joint_friction);
}

//----------------------------------------------------------------------------
void dmLoader_dm::setMDHParameters(dmMDHLink *link, ifstream &cfg_ptr)
{
   readConfigParameterLabel(cfg_ptr, "MDH_Parameters");
   Float a     = parseFloat(cfg_ptr);
   Float alpha = parseFloat(cfg_ptr);
   Float d     = parseFloat(cfg_ptr);
   Float theta = parseFloat(cfg_ptr);

   Float q, qd;
   link->setMDHParameters(a, alpha, d, theta);
   link->getState(&q, &qd);  // either d or theta could be q this retrieves it

   readConfigParameterLabel(cfg_ptr, "Initial_Joint_Velocity");
   qd = parseFloat(cfg_ptr);

   link->setState(&q, &qd);  // essentially sets the joint velocity

   readConfigParameterLabel(cfg_ptr, "Joint_Limits");
   Float min = parseFloat(cfg_ptr);
   Float max = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Joint_Limit_Spring_Constant");
   Float spring = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Joint_Limit_Damper_Constant");
   Float damper = parseFloat(cfg_ptr);

   link->setJointLimits(min, max, spring, damper);
}

//----------------------------------------------------------------------------
void dmLoader_dm::setRevDCMotorParameters(dmRevDCMotor *actuator,
                                          ifstream &cfg_ptr)
{
   readConfigParameterLabel(cfg_ptr, "Motor_Torque_Constant");
   Float torque_constant = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Motor_BackEMF_Constant");
   Float back_EMF_constant = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Motor_Armature_Resistance");
   Float armature_resistance = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Motor_Inertia");
   Float rotor_inertia = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Motor_Coulomb_Friction_Constant");
   Float coulomb_friction_constant = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Motor_Viscous_Friction_Constant");
   Float viscous_friction_constant = parseFloat(cfg_ptr);


   readConfigParameterLabel(cfg_ptr, "Motor_Max_Brush_Drop");
   Float max_brush_drop = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Motor_Half_Drop_Value");
   Float half_drop_value = parseFloat(cfg_ptr);


   actuator->setParameters(torque_constant,
                           back_EMF_constant,
                           armature_resistance,
                           rotor_inertia,
                           coulomb_friction_constant,
                           viscous_friction_constant,
                           max_brush_drop,
                           half_drop_value);
}

//----------------------------------------------------------------------------
void dmLoader_dm::setActuator(dmRevoluteLink *link, ifstream &cfg_ptr)
{
   readConfigParameterLabel(cfg_ptr, "Actuator_Type");
   int actuator_type = parseInt(cfg_ptr);

   if (actuator_type == NOMOTOR)
   {
      setJointFriction(link, cfg_ptr);
   }
   else if (actuator_type == DCMOTOR)
   {
      dmRevDCMotor *actuator = new dmRevDCMotor();
      setRevDCMotorParameters(actuator, cfg_ptr);
      link->setActuator(actuator);
   }
   else
   {
      cerr << "dmLoader_dm::setActuator error: invalid Actuator_Type\n";
      exit(3);
   }
}

//----------------------------------------------------------------------------
void dmLoader_dm::setSphericalLinkParameters(dmSphericalLink *link,
                                             ifstream &cfg_ptr)
{
   unsigned int i;

   // Joint info:
   CartesianVector p;
   readConfigParameterLabel(cfg_ptr, "Position_From_Inboard_Link");
   for (i=0; i<3; i++)
   {
      p[i] = parseFloat(cfg_ptr);
   }
   link->setJointOffset(p);

   EulerAngles ang;
   readConfigParameterLabel(cfg_ptr, "Initial_Joint_Angles");
   for (i=0; i<3; i++)
   {
      ang[i] = parseFloat(cfg_ptr);
   }

   Float qd[dmSphericalLink::NUM_DOFS];
   readConfigParameterLabel(cfg_ptr, "Initial_Angular_Velocity");
   for (i=0; i<3; i++)
   {
      qd[i] = parseFloat(cfg_ptr);
   }
   link->setState(ang, qd);

   Float joint_limit[dmSphericalLink::NUM_DOFS];
   readConfigParameterLabel(cfg_ptr, "Axes_Limits");
   for (i=0; i<3; i++)
   {
      joint_limit[i] = parseFloat(cfg_ptr);
   }

   readConfigParameterLabel(cfg_ptr, "Joint_Limit_Spring_Constant");
   Float spring = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Joint_Limit_Damper_Constant");
   Float damper = parseFloat(cfg_ptr);

   link->setJointLimits(joint_limit, spring, damper);

   setJointFriction(link, cfg_ptr);
}

//----------------------------------------------------------------------------
// was setDynamicRefMemParameters
void dmLoader_dm::setMobileBaseParameters(dmMobileBaseLink *ref,
                                          ifstream &cfg_ptr)
{
   unsigned int i;
   Float q[7];
   SpatialVector vel;

   readConfigParameterLabel(cfg_ptr, "Position");
   for (i=4; i<7; i++)
   {
      q[i] = parseFloat(cfg_ptr);
   }

   readConfigParameterLabel(cfg_ptr, "Orientation_Quat");
   for (i=0; i<4; i++)
   {
      q[i] = parseFloat(cfg_ptr);
   }

   readConfigParameterLabel(cfg_ptr, "Velocity");
   for (i = 0; i < 6; i++)
   {
      vel[i] = parseFloat(cfg_ptr);
   }

   ref->setState(q, vel);
}
