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
 *     File: dmLoader_dm203.cpp
 *   Author: Scott McMillan
 *  Created: 12 August 2001 (was dmLoadFile_dm203.cpp - 26 April 1997)
 *  Summary:
 *****************************************************************************/

#include <dmLoader_dm203.hpp>

#include <glLoadModels.h>

#include <dmArticulation.hpp>
#include <dmLink.hpp>
#include <dmZScrewTxLink.hpp>
#include <dmMDHLink.hpp>
#include <dmRevoluteLink.hpp>
#include <dmPrismaticLink.hpp>
#include <dmSphericalLink.hpp>
#include <dmMobileBaseLink.hpp>

//----------------------------------------------------------------------------
dmLoader_dm203::dmLoader_dm203()
      : dmLoader_dm(),
        m_solid_models()
{
}

//----------------------------------------------------------------------------
GLuint *dmLoader_dm203::getGraphicsModelIndex(ifstream &cfg_ptr)
{
   readConfigParameterLabel(cfg_ptr, "Graphics_Model_Index");
   unsigned int gfx_model_index = (unsigned int) parseInt(cfg_ptr);

   GLuint *dlist_index = new GLuint;
   *dlist_index = 0;

   if (gfx_model_index < m_solid_models.size())
      *dlist_index = m_solid_models[gfx_model_index];

   return dlist_index;
}

//----------------------------------------------------------------------------
void dmLoader_dm203::loadModels(ifstream &cfg_ptr)
{
   // get solid object (rigid body) models.
   readConfigParameterLabel(cfg_ptr,"Number_Graphics_Models");
   unsigned int num_graphics_models = (unsigned int)parseInt(cfg_ptr);

   vector<string> filenames;

   if (num_graphics_models > 0)
   {
      string filename;

      for (unsigned int i=0; i<num_graphics_models; i++)
      {
         getStringParameter(cfg_ptr, filename);

         //cerr << "Graphics Model file #" << i << ": " << filename << endl;

         GLuint dlist = glLoadModel(filename.c_str());
         m_solid_models.push_back(dlist);
      }
   }
}

//----------------------------------------------------------------------------
void dmLoader_dm203::setStaticRefMemParameters(dmSystem *robot,
                                               ifstream &cfg_ptr)
{
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
}

//----------------------------------------------------------------------------
void dmLoader_dm203::parseBranch(ifstream &cfg_ptr,
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
      if (tok == "Articulation" || tok == "Branch")
      {
         parseToBlockBegin(cfg_ptr);
         parseBranch(cfg_ptr, articulation, last_link);
      }
      else if (tok == "RevoluteLink")
      {
         parseToBlockBegin(cfg_ptr);

         dmRevoluteLink *link = new dmRevoluteLink();

         GLuint *dlist_index = getGraphicsModelIndex(cfg_ptr);
         link->setUserData((void *) dlist_index);

         setRigidBodyParameters(link, cfg_ptr);
         setMDHParameters(link, cfg_ptr);
         setActuator(link, cfg_ptr);

         parseToBlockEnd(cfg_ptr);

         articulation->addLink(link, last_link);
         last_link = (dmLink *) link;
      }
      else if (tok == "PrismaticLink")
      {
         parseToBlockBegin(cfg_ptr);

         dmPrismaticLink *link = new dmPrismaticLink();

         GLuint *dlist_index = getGraphicsModelIndex(cfg_ptr);
         link->setUserData((void *) dlist_index);

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

         GLuint *dlist_index = getGraphicsModelIndex(cfg_ptr);
         link->setUserData((void *) dlist_index);

         setRigidBodyParameters(link, cfg_ptr);
         setSphericalLinkParameters(link, cfg_ptr);

         parseToBlockEnd(cfg_ptr);

         articulation->addLink(link, last_link);
         last_link = link;
      }
      else if (tok == "ZScrewTxLink" ||
               tok == "ZScrewLinkTx")    // deprecated
      {
         parseToBlockBegin(cfg_ptr);

         // Get Inboard to Chain base transformation info.
         readConfigParameterLabel(cfg_ptr, "ZScrew_Parameters");
         Float d     = parseFloat(cfg_ptr);
         Float theta = parseFloat(cfg_ptr);

         dmZScrewTxLink *link = new dmZScrewTxLink(d, theta);
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
         cerr << "Error: Invalid Joint_Type: " << tok << endl;
         exit(3);
      }
   }
}

//----------------------------------------------------------------------------
dmSystem *dmLoader_dm203::loadSystem(ifstream &cfg_ptr)
{
   dmLink *parent_link = NULL;

   dmArticulation *robot = new dmArticulation();
   if (robot == NULL)
   {
      cerr << "dmLoader_dm203::loadSystem error: "
           << "unable to allocate dmArticulation" << endl;
      cfg_ptr.close();
      exit(4);
   }

   string tok;
   parseToBlockBegin(cfg_ptr);

   // ============= Get RefMember info. =================
   do
   {
      parseToken(cfg_ptr, tok);

   } while (tok != "StaticRefMember" && tok != "DynamicRefMember");

   parseToBlockBegin(cfg_ptr);
   GLuint *dlist_index = getGraphicsModelIndex(cfg_ptr);


   // dmStaticRefMember corresponds to the 3.0 Ref System within dmSystem now
   if (tok == "StaticRefMember")
   {
      robot->setUserData((void *) dlist_index); // not sure anything can be
                                                // done about this graphics
                                                // model
      setStaticRefMemParameters(robot, cfg_ptr);
   }

   // dmDynamicRefMember corresponds to the 3.0 MobileBaseLink now
   else if (tok == "DynamicRefMember")
   {
      dmMobileBaseLink *dref = new dmMobileBaseLink();
      if (dref != NULL)
      {
         dref->setUserData((void *) dlist_index);
         setRigidBodyParameters(dref, cfg_ptr);
         setMobileBaseParameters(dref, cfg_ptr);

         robot->addLink(dref, NULL);
         parent_link = dref;
      }
      else
      {
         cerr << "dmLoader_dm203::loadSystem error: unable to allocate "
              << "dmMobileBaseLink" << endl;
         cfg_ptr.close();
         exit(1);
      }
   }

   else
   {
      cerr << "dmLoader_dm203::loadSystem error: unknown RefMember type: "
           << tok << endl;
      exit(3);
   }

   parseToBlockEnd(cfg_ptr);

   //========================================================================
   parseBranch(cfg_ptr, robot, parent_link);
   //========================================================================

   return robot;
}


//----------------------------------------------------------------------------
dmSystem *dmLoader_dm203::load(ifstream &cfg_ptr)
{
   m_line_num = 1;  // set to 1 b/c the first line was parsed in dmLoader
   bool models_flag = true;
   bool system_flag = true;

   dmSystem *robot = NULL;

   do
   {
      string tok;
      parseToken(cfg_ptr, tok);

      if (tok == "Graphics_Models")
      {
         parseToBlockBegin(cfg_ptr);
         loadModels(cfg_ptr);
         models_flag = false;
         parseToBlockEnd(cfg_ptr);
      }
      else if (tok == "System")
      {
         robot = loadSystem(cfg_ptr);
         system_flag = false;
      }
      else
      {
         cerr << "dmLoader_dm203 error: unknown token on line " << m_line_num
              << ": " << tok << endl;
      }
   } while (models_flag || system_flag);

   return robot;
}
