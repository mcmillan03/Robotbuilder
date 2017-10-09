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
 *     File: dmLoader_dm30.cpp
 *   Author: Scott McMillan
 *  Created: 12 August 2001
 *  Summary: load v4.0 configuration files and piece together a complete
 *           dmSystem for simulation.
 *****************************************************************************/

#include <dm.h>
#include <dmLoader_dm40.hpp>

#include <dmObject.hpp>
#include <dmSystem.hpp>
#include <dmArticulation.hpp>
#include <dmClosedArticulation.hpp>
#include <dmLink.hpp>
#include <dmZScrewTxLink.hpp>
#include <dmStaticRootLink.hpp>
#include <dmMDHLink.hpp>
#include <dmRevoluteLink.hpp>
#include <dmPrismaticLink.hpp>
#include <dmSphericalLink.hpp>
#include <dmMobileBaseLink.hpp>
#include <dmQuaternionLink.hpp>
#include <dmActuator.hpp>
#include <dmRevDCMotor.hpp>
#include <dmContactModel.hpp>

#include <glLoadModels.h>

#include <dmSecondaryJoint.hpp>
#include <dmSecondaryPrismaticJoint.hpp>
#include <dmSecondaryRevoluteJoint.hpp>
#include <dmSecondarySphericalJoint.hpp>

#include <typeinfo>

//----------------------------------------------------------------------------
void dmLoader_dm40::setQuaternionLinkParameters(dmQuaternionLink *link,
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

   Float q[4];
   readConfigParameterLabel(cfg_ptr, "Orientation_Quat");
   for (i=0; i<4; i++)
   {
      q[i] = parseFloat(cfg_ptr);
   }

   Float qd[3];
   readConfigParameterLabel(cfg_ptr, "Initial_Angular_Velocity");
   for (i=0; i<3; i++)
   {
      qd[i] = parseFloat(cfg_ptr);
   }
   link->setState(q, qd);

   setJointFriction(link, cfg_ptr);
}

//----------------------------------------------------------------------------
void dmLoader_dm40::setSecondaryJoint(ifstream &cfg_ptr,
                                      dmSecondaryJoint *joint,
                                      dmClosedArticulation *articulation)
{
   register int i, j;
   string object_name;

   joint->setArticulation(articulation);

   if (getStringParameter(cfg_ptr, "Link_A_Name", object_name))
   {
      dmObject *link_A = dmuFindObject(object_name, articulation);
      if (link_A == NULL)
      {
         cerr << "Invalid secondary joint link A: '" << object_name << "'."
              << endl;
         exit(3);
      }

      if ((typeid(*link_A) == typeid(dmStaticRootLink)) ||
          (typeid(*link_A) == typeid(dmMobileBaseLink)) ||
          (typeid(*link_A) == typeid(dmPrismaticLink))  ||
          (typeid(*link_A) == typeid(dmRevoluteLink))   ||
          (typeid(*link_A) == typeid(dmSphericalLink))  ||
          (typeid(*link_A) == typeid(dmQuaternionLink)) ||
          (typeid(*link_A) == typeid(dmZScrewTxLink)) )
      {
         joint->setLinkA(dynamic_cast<dmLink *>(link_A));
      }
      else
      {
         cerr << "Invalid secondary joint link type: "
              << (typeid(*link_A)).name() << "." << endl;
         exit(3);
      }
   }
   else
   {
      cerr << "Secondary joint links must have names." << endl;
      exit(3);
   }

   if (getStringParameter(cfg_ptr, "Link_B_Name", object_name))
   {
      dmObject *link_B = dmuFindObject(object_name, articulation);
      if (link_B == NULL)
      {
         cerr << "Invalid secondary joint link B: '"
              << object_name << "'." << endl;
         exit(3);
      }

      if ((typeid(*link_B) == typeid(dmStaticRootLink)) ||
          (typeid(*link_B) == typeid(dmMobileBaseLink)) ||
          (typeid(*link_B) == typeid(dmPrismaticLink))  ||
          (typeid(*link_B) == typeid(dmRevoluteLink))   ||
          (typeid(*link_B) == typeid(dmSphericalLink))  ||
          (typeid(*link_B) == typeid(dmQuaternionLink)) ||
          (typeid(*link_B) == typeid(dmZScrewTxLink)))
      {
         joint->setLinkB(dynamic_cast<dmLink *>(link_B));
      }
      else
      {
         cerr << "Invalid secondary joint link type: "
              << (typeid(*link_B)).name() << "." << endl;
         exit(3);
      }
   }
   else
   {
      cerr << "Secondary joint links must have names." << endl;
      exit(3);
   }

   CartesianVector a_pos;
   readConfigParameterLabel(cfg_ptr, "Joint_A_Position");
   for (i=0; i<3; i++)
   {
      a_pos[i] = parseFloat(cfg_ptr);
   }

   RotationMatrix a_rot;
   readConfigParameterLabel(cfg_ptr, "Rotation_Matrix_A");
   for (i = 0; i < 3; i++)
   {
      for (j=0; j<3; j++)
      {
         a_rot[i][j] = parseFloat(cfg_ptr);
      }
   }

   CartesianVector b_pos;
   readConfigParameterLabel(cfg_ptr, "Joint_B_Position");
   for (i=0; i<3; i++)
   {
      b_pos[i] = parseFloat(cfg_ptr);
   }

   RotationMatrix b_rot;
   readConfigParameterLabel(cfg_ptr, "Rotation_Matrix_B");
   for (i = 0; i < 3; i++)
   {
      for (j=0; j<3; j++)
      {
         b_rot[i][j] = parseFloat(cfg_ptr);
      }
   }

   joint->setKinematics(a_pos, b_pos, a_rot, b_rot);

   readConfigParameterLabel(cfg_ptr, "Joint_Friction");
   Float joint_friction = parseFloat(cfg_ptr);
   joint->setJointFriction(joint_friction);
}

//----------------------------------------------------------------------------
void dmLoader_dm40::setStabilization(ifstream &cfg_ptr,
                                     dmSecondaryJoint *joint)
{
   string stabName;

   readConfigParameterLabel(cfg_ptr, "Stabilization");
   parseToken(cfg_ptr, stabName);

   if (stabName == "NONE")
   {
      joint->setStabilizationType(dmSecondaryJoint::NONE);
   }
   else if (stabName == "BAUMGARTE")
   {
      joint->setStabilizationType(dmSecondaryJoint::BAUMGARTE);
   }
   else if (stabName == "SPRING_DAMPER")
   {
      joint->setStabilizationType(dmSecondaryJoint::SPRING_DAMPER);
   }
   else
   {
      cerr << "dmLoader_dm40::setStabilization error: "
           << "Unrecognizable stabilization type: " << stabName << endl;
      exit(3);
   }
}


//----------------------------------------------------------------------------
void dmLoader_dm40::setSecondaryPrismaticJoint(ifstream &cfg_ptr,
                                              dmSecondaryPrismaticJoint *joint)
{
   readConfigParameterLabel(cfg_ptr, "Position_Constraint_Spring");
   Float linear_constraint_spring = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Position_Constraint_Damper");
   Float linear_constraint_damper = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Orientation_Constraint_Spring");
   Float angular_constraint_spring = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Orientation_Constraint_Damper");
   Float angular_constraint_damper = parseFloat(cfg_ptr);

   joint->setConstraintParams(linear_constraint_spring,
                              linear_constraint_damper,
                              angular_constraint_spring,
                              angular_constraint_damper);
}


//----------------------------------------------------------------------------
void dmLoader_dm40::setSecondaryRevoluteJoint(ifstream &cfg_ptr,
                                              dmSecondaryRevoluteJoint *joint)
{
   readConfigParameterLabel(cfg_ptr, "Position_Constraint_Spring");
   Float linear_constraint_spring = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Position_Constraint_Damper");
   Float linear_constraint_damper = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Orientation_Constraint_Spring");
   Float angular_constraint_spring = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Orientation_Constraint_Damper");
   Float angular_constraint_damper = parseFloat(cfg_ptr);

   joint->setConstraintParams(linear_constraint_spring,
                              linear_constraint_damper,
                              angular_constraint_spring,
                              angular_constraint_damper);
}

//----------------------------------------------------------------------------
void dmLoader_dm40::setSecondarySphericalJoint(ifstream &cfg_ptr,
                                              dmSecondarySphericalJoint *joint)
{
   readConfigParameterLabel(cfg_ptr, "Position_Constraint_Spring");
   Float linear_constraint_spring = parseFloat(cfg_ptr);

   readConfigParameterLabel(cfg_ptr, "Position_Constraint_Damper");
   Float linear_constraint_damper = parseFloat(cfg_ptr);

   joint->setConstraintParams(linear_constraint_spring,
                              linear_constraint_damper);
}

//----------------------------------------------------------------------------
void dmLoader_dm40::setRevDCMotorParameters(dmRevDCMotor *actuator,
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

   readConfigParameterLabel(cfg_ptr, "Motor_Gear_Ratio");
   Float gear_ratio = parseFloat(cfg_ptr);


   actuator->setParameters(torque_constant,
                           back_EMF_constant,
                           armature_resistance,
                           rotor_inertia,
                           coulomb_friction_constant,
                           viscous_friction_constant,
                           max_brush_drop,
                           half_drop_value,
                           gear_ratio);
}


//----------------------------------------------------------------------------
void dmLoader_dm40::parseSecondaryJoints(ifstream &cfg_ptr,
                                         dmClosedArticulation *articulation)
{
   string tok;

   for (;;)
   {
      // get next token
      parseToken(cfg_ptr, tok);

      if (tok == "HardRevoluteJoint")
      {
         parseToBlockBegin(cfg_ptr);

         dmSecondaryRevoluteJoint *joint = new dmSecondaryRevoluteJoint;

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            joint->setName(object_name);
         }

         setStabilization(cfg_ptr, joint);
         setSecondaryJoint(cfg_ptr, joint, articulation);
         setSecondaryRevoluteJoint(cfg_ptr, joint);

         parseToBlockEnd(cfg_ptr);

         articulation->addHardSecondaryJoint(joint);
      }
      else if (tok == "SoftRevoluteJoint")
      {
         parseToBlockBegin(cfg_ptr);

         dmSecondaryRevoluteJoint *joint = new dmSecondaryRevoluteJoint();

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            joint->setName(object_name);
         }

         setSecondaryJoint(cfg_ptr, joint, articulation);
         setSecondaryRevoluteJoint(cfg_ptr, joint);

         parseToBlockEnd(cfg_ptr);

         articulation->addSoftSecondaryJoint(joint);
      }
      else if (tok == "HardPrismaticJoint")
      {
         parseToBlockBegin(cfg_ptr);

         dmSecondaryPrismaticJoint *joint = new dmSecondaryPrismaticJoint();

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            joint->setName(object_name);
         }

         setStabilization(cfg_ptr, joint);
         setSecondaryJoint(cfg_ptr, joint, articulation);
         setSecondaryPrismaticJoint(cfg_ptr, joint);

         parseToBlockEnd(cfg_ptr);

         articulation->addHardSecondaryJoint(joint);
      }
      else if (tok == "SoftPrismaticJoint")
      {
         parseToBlockBegin(cfg_ptr);

         dmSecondaryPrismaticJoint *joint = new dmSecondaryPrismaticJoint();

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            joint->setName(object_name);
         }

         setSecondaryJoint(cfg_ptr, joint, articulation);
         setSecondaryPrismaticJoint(cfg_ptr, joint);

         parseToBlockEnd(cfg_ptr);

         articulation->addSoftSecondaryJoint(joint);
      }
      else if (tok == "HardSphericalJoint")
      {
         parseToBlockBegin(cfg_ptr);

         dmSecondarySphericalJoint *joint = new dmSecondarySphericalJoint();

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            joint->setName(object_name);
         }

         setStabilization(cfg_ptr, joint);
         setSecondaryJoint(cfg_ptr, joint, articulation);
         setSecondarySphericalJoint(cfg_ptr, joint);

         parseToBlockEnd(cfg_ptr);

         articulation->addHardSecondaryJoint(joint);
      }
      else if (tok == "SoftSphericalJoint")
      {
         parseToBlockBegin(cfg_ptr);

         dmSecondarySphericalJoint *joint = new dmSecondarySphericalJoint();

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            joint->setName(object_name);
         }

         setSecondaryJoint(cfg_ptr, joint, articulation);
         setSecondarySphericalJoint(cfg_ptr, joint);

         parseToBlockEnd(cfg_ptr);

         articulation->addSoftSecondaryJoint(joint);
      }
      else if (tok[0] == BLOCK_END_CHAR)
      {
         break;
      }
      else
      {
         cerr << "Error: Invalid Secondary_Joint_Type: " << tok
              << ", line " << m_line_num << endl;
         exit(3);
      }
   }
}

//----------------------------------------------------------------------------
void dmLoader_dm40::parseBranch(ifstream &cfg_ptr,
                                dmArticulation *articulation,
                                dmLink *parent)
{
   string tok;

   dmLink* last_link = parent;

   for (;;)
   {
      // get next token
      parseToken(cfg_ptr, tok);

      // allocate a link and pass stream reference
      if (tok == "Branch")
      {
         parseToBlockBegin(cfg_ptr);

         parseBranch(cfg_ptr, articulation, last_link);
      }
      else if (tok == "StaticRootLink")
      {
         parseToBlockBegin(cfg_ptr);

         dmStaticRootLink *link = new dmStaticRootLink();

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            link->setName(object_name);
         }

         getGraphicsModel(cfg_ptr, link);

         parseToBlockEnd(cfg_ptr);

         articulation->addLink(link, last_link);
         last_link = link;
      }
      else if (tok == "MobileBaseLink")
      {
         parseToBlockBegin(cfg_ptr);

         dmMobileBaseLink *link = new dmMobileBaseLink();

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            link->setName(object_name);
         }

         getGraphicsModel(cfg_ptr, link);

         setRigidBodyParameters(link, cfg_ptr);
         setMobileBaseParameters(link, cfg_ptr);

         parseToBlockEnd(cfg_ptr);

         articulation->addLink(link, last_link);
         last_link = link;
      }
      else if (tok == "RevoluteLink")
      {
         parseToBlockBegin(cfg_ptr);

         dmRevoluteLink *link = new dmRevoluteLink();

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            link->setName(object_name);
         }

         getGraphicsModel(cfg_ptr, link);

         setRigidBodyParameters(link, cfg_ptr);
         setMDHParameters(link, cfg_ptr);
         setActuator(link, cfg_ptr);

         parseToBlockEnd(cfg_ptr);

         articulation->addLink(link, last_link);
         last_link = link;
      }
      else if (tok == "PrismaticLink")
      {
         parseToBlockBegin(cfg_ptr);

         dmPrismaticLink *link = new dmPrismaticLink();

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            link->setName(object_name);
         }

         getGraphicsModel(cfg_ptr, link);

         setRigidBodyParameters(link, cfg_ptr);
         setMDHParameters(link, cfg_ptr);
         setJointFriction(link, cfg_ptr);

         parseToBlockEnd(cfg_ptr);

         articulation->addLink(link, last_link);
         last_link = link;
      }
      else if (tok == "SphericalLink")
      {
         parseToBlockBegin(cfg_ptr);

         dmSphericalLink *link = new dmSphericalLink();

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            link->setName(object_name);
         }

         getGraphicsModel(cfg_ptr, link);

         setRigidBodyParameters(link, cfg_ptr);
         setSphericalLinkParameters(link, cfg_ptr);

         parseToBlockEnd(cfg_ptr);

         articulation->addLink(link, last_link);
         last_link = link;
      }
      else if (tok == "QuaternionLink")
      {
         parseToBlockBegin(cfg_ptr);

         dmQuaternionLink *link = new dmQuaternionLink;

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            link->setName(object_name);
         }

         getGraphicsModel(cfg_ptr, link);

         setRigidBodyParameters(link, cfg_ptr);
         setQuaternionLinkParameters(link, cfg_ptr);

         parseToBlockEnd(cfg_ptr);

         articulation->addLink(link, last_link);
         last_link = link;
      }
      else if (tok == "ZScrewTxLink" ||
               tok == "ZScrewLinkTx")    // deprecated
      {
         parseToBlockBegin(cfg_ptr);

         string object_name;
         bool got_name = getStringParameter(cfg_ptr, "Name", object_name);

         // Get Inboard to Chain base transformation info.
         readConfigParameterLabel(cfg_ptr, "ZScrew_Parameters");

         Float d = parseFloat(cfg_ptr);
         Float theta = parseFloat(cfg_ptr);

         dmZScrewTxLink *link = new dmZScrewTxLink(d, theta);
         if (got_name)
         {
            link->setName(object_name);
         }
         parseToBlockEnd(cfg_ptr);

         articulation->addLink(link, last_link);
         last_link = link;
      }
      else if (tok[0] == BLOCK_END_CHAR)
      {
         break;
      }
      else
      {
         cerr << "Error: Invalid Joint_Type: " << tok
              << ", line " << m_line_num <<endl;
         exit(3);
      }
   }
}

//----------------------------------------------------------------------------
dmClosedArticulation *dmLoader_dm40::loadClosedArticulation(ifstream &cfg_ptr)
{
   dmClosedArticulation *robot = new dmClosedArticulation();;
   if (robot == NULL)
   {
      cerr << "dmLoader_dm40::loadClosedArticulation error: "
           << "unable to allocate dmClosedArticulation" << endl;
      cfg_ptr.close();
      exit(4);
   }

   parseToBlockBegin(cfg_ptr);

   // label the system object
   string sys_name;

   if (getStringParameter(cfg_ptr, "Name", sys_name))
   {
      robot->setName(sys_name);
   }

   string object_name;
   if (getStringParameter(cfg_ptr, "Graphics_Model", object_name) &&
       !object_name.empty())
   {
      GLuint *dlist = new GLuint;
      *dlist = glLoadModel(object_name.c_str());
      robot->setUserData((void *) dlist);
   }

   // ================== NEW Get Reference System info. =====================
   unsigned int i;
   CartesianVector pos;
   Quaternion quat;

   readConfigParameterLabel(cfg_ptr, "Position");
   for (i=0; i<3; i++)
   {
      pos[i] = parseFloat(cfg_ptr);
   }
   readConfigParameterLabel(cfg_ptr, "Orientation_Quat");
   for (i=0; i<4; i++)
   {
      quat[i] = parseFloat(cfg_ptr);
   }

   robot->setRefSystem(quat, pos);

   // ======== Load in the tree structure of the closed articulation.========
   readConfigParameterLabel(cfg_ptr, "TreeStructure");
   parseToBlockBegin(cfg_ptr);
   parseBranch(cfg_ptr, robot, NULL);

   // ======= Load in the secondary joints of the closed articulation. ======
   readConfigParameterLabel(cfg_ptr, "SecondaryJoints");
   parseToBlockBegin(cfg_ptr);
   parseSecondaryJoints(cfg_ptr, robot);
   parseToBlockEnd(cfg_ptr);

   // ======= Initialize internal data structures for kinematic loops. ======
   robot->initKinematicLoopVars();

   return robot;
}

//----------------------------------------------------------------------------
dmSystem *dmLoader_dm40::load(ifstream &cfg_ptr)
{
   m_line_num = 1;
   bool system_flag = true;

   dmSystem *robot = NULL;

   do
   {
      string tok;
      parseToken(cfg_ptr, tok);

      if (tok == "Articulation")
      {
         robot = loadArticulation(cfg_ptr);
         system_flag = false;
      }
      else if (tok == "ClosedArticulation")
      {
         robot = loadClosedArticulation(cfg_ptr);
         system_flag = false;
      }
      else
      {
         cerr << "dmLoadFile_dm40 error: unknown token on line " << m_line_num
              << ": " << tok << endl;
      }
   } while (system_flag);

   return robot;
}
