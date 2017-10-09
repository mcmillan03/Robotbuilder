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
 *     File: dmLoader_dm21.cpp
 *   Author: Scott McMillan
 *  Created: 12 August 2001
 *  Summary: Loader for V 2.1 DynaMechs configuration files
 *****************************************************************************/

#include <dmLoader_dm21.hpp>

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

//----------------------------------------------------------------------------
dmLoader_dm21::dmLoader_dm21()
      : dmLoader_dm203()
{
}

//----------------------------------------------------------------------------
void dmLoader_dm21::parseBranch(ifstream &cfg_ptr,
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
      if (tok == "Articulation")
      {
         parseToBlockBegin(cfg_ptr);

         string art_name;
         getStringParameter(cfg_ptr, "Name", art_name);  // ignored

         parseBranch(cfg_ptr, articulation, last_link);
      }
      else if (tok == "Branch")
      {
         parseToBlockBegin(cfg_ptr);
         parseBranch(cfg_ptr, articulation, last_link);
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

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            link->setName(object_name);
         }

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

         string object_name;
         if (getStringParameter(cfg_ptr, "Name", object_name))
         {
            link->setName(object_name);
         }

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

         string object_name;
         int got_name = getStringParameter(cfg_ptr, "Name", object_name);

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
         cerr << "dmLoader_dm21::parseBranch error: Invalid Joint_Type: "
              << tok << ", line " << m_line_num << endl;
         exit(3);
      }
   }
}

//----------------------------------------------------------------------------
dmSystem *dmLoader_dm21::loadSystem(ifstream &cfg_ptr)
{
   dmLink *parent_link = NULL;

   dmArticulation *robot = new dmArticulation();
   if (robot == NULL)
   {
      cerr << "dmLoader_dm21::loadSystem error: "
           << "unable to allocate dmArticulation" << endl;
      cfg_ptr.close();
      exit(4);
   }

   parseToBlockBegin(cfg_ptr);

   // NEW label the system object
   string sys_name;
   if (getStringParameter(cfg_ptr, "Name", sys_name))
   {
      robot->setName(sys_name);
   }

   // ============= Get RefMember info. =================
   string tok;
   do
   {
      parseToken(cfg_ptr, tok);

   } while (tok != "StaticRefMember" && tok != "DynamicRefMember");

   parseToBlockBegin(cfg_ptr);
   string object_name;
   bool got_ref_name = getStringParameter(cfg_ptr, "Name", object_name);
   GLuint *dlist_index = getGraphicsModelIndex(cfg_ptr);

   // dmStaticRefMember corresponds to the 3.0 Ref System within dmSystem now
   if (tok == "StaticRefMember")
   {
      // ignoring the StaticRefMember name (using System name)

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
         if (got_ref_name)
         {
            dref->setName(object_name);
         }
         dref->setUserData((void *) dlist_index);
         setRigidBodyParameters(dref, cfg_ptr);
         setMobileBaseParameters(dref, cfg_ptr);

         robot->addLink(dref, NULL);
         parent_link = dref;
      }
      else
      {
         cerr << "dmLoader_dm21::loadSystem error: unable to allocate "
              << "dmDynamicRefMember" << endl;
         cfg_ptr.close();
         exit(1);
      }
   }

   else
   {
      cerr << "dmLoader_dm21::loadSystem error: unknown RefMember type: "
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
dmSystem *dmLoader_dm21::load(ifstream &cfg_ptr)
{
   m_line_num = 1;
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
         cerr << "dmLoader_dm21 error: unknown token on line " << m_line_num
              << ": " << tok << endl;
      }
   } while (models_flag || system_flag);

   return robot;
}
