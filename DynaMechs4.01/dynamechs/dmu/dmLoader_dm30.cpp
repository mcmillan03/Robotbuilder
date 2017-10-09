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
 *  Created: 30 July 2001
 *  Summary: load v3.0 configuration files and piece together a complete
 *           dmSystem for simulation.
 *****************************************************************************/

#include <dm.h>
#include <dmLoader_dm30.hpp>

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

#include <dmObject.hpp>
#include <dmSystem.hpp>
#include <dmArticulation.hpp>
#include <dmLink.hpp>
#include <dmZScrewTxLink.hpp>
#include <dmMDHLink.hpp>
#include <dmRevoluteLink.hpp>
#include <dmPrismaticLink.hpp>
#include <dmSphericalLink.hpp>
#include <dmMobileBaseLink.hpp>
#include <dmActuator.hpp>
#include <dmRevDCMotor.hpp>
#include <dmContactModel.hpp>

#include <glLoadModels.h>

//----------------------------------------------------------------------------
void dmLoader_dm30::getGraphicsModel(ifstream &cfg_ptr, dmLink *link)
{
   string object_name;
   if (getStringParameter(cfg_ptr, "Graphics_Model", object_name) &&
       !object_name.empty())
   {
      GLuint *dlist = new GLuint;
      *dlist = glLoadModel(object_name.c_str());
      link->setUserData((void *) dlist);
   }
}

//----------------------------------------------------------------------------
void dmLoader_dm30::parseBranch(ifstream &cfg_ptr,
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
      else if (tok == "MobileBaseLink")
      {
         if (last_link != NULL)
         {
            cerr << "dmLoadfile_dm30::parseBranch warning: mobile base "
                 << "link should only be used for first link." << endl;
         }

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
      else if (tok == "ZScrewTxLink" ||
               tok == "ZScrewLinkTx")    // deprecated
      {
         parseToBlockBegin(cfg_ptr);

         string object_name;
         bool got_name = getStringParameter(cfg_ptr, "Name", object_name);

         // Get Inboard to Chain base transformation info.
         readConfigParameterLabel(cfg_ptr, "ZScrew_Parameters");

         Float d     = parseFloat(cfg_ptr);
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
         cerr << "dmLoader_dm30::parseBranch error: Invalid Joint_Type: "
              << tok << ", line " << m_line_num <<endl;
         exit(3);
      }
   }
}

//----------------------------------------------------------------------------
dmArticulation* dmLoader_dm30::loadArticulation(ifstream &cfg_ptr)
{
   dmArticulation *robot = new dmArticulation();
   if (robot == NULL)
   {
      cerr << "dmLoader_dm30::loadArticulation error: "
           << "unable to allocate dmArticulation" << endl;
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
   //========================================================================

   // there have to be links
   parseBranch(cfg_ptr, robot, NULL);

   return robot;
}

//----------------------------------------------------------------------------
dmSystem *dmLoader_dm30::load(ifstream &cfg_ptr)
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
      else
      {
         cerr << "dmLoadFile_dm30 error: unknown token on line " << m_line_num
              << ": " << tok << endl;
      }
   } while (system_flag);

   return robot;
}
