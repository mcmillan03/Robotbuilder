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
 *     File: dmLoader_dm.hpp
 *   Author: Scott McMillan
 *  Created: 14 August 2001
 *  Summary: Abstract base class for DynaMechs configuration file loaders.
 *****************************************************************************/

#ifndef _DM_LOADER_DM
#define _DM_LOADER_DM

#include <dm.h>
#include <GL/gl.h>

#include <dmu.h>
#include <dmLoader.hpp>

class dmSystem;
class dmArticulation;
class dmLink;
class dmMobileBaseLink;
class dmSphericalLink;
class dmRevoluteLink;
class dmRevDCMotor;
class dmMDHLink;
class dmRigidBody;

//----------------------------------------------------------------------------

class DMU_DLL_API dmLoader_dm : public dmLoader
{
public:
   /** Constructor. */
   dmLoader_dm();

   /** Destructor. */
   virtual ~dmLoader_dm() {}

   /** non-reentrant loader function to be implemented by the subclasses */
   virtual dmSystem *load(ifstream &cfg_ptr) = 0;

protected:
   void setContactParameters(dmRigidBody *body, ifstream &cfg_ptr);
   void setRigidBodyParameters(dmRigidBody *body, ifstream &cfg_ptr);
   void setJointFriction(dmLink *link, ifstream &cfg_ptr);
   void setMDHParameters(dmMDHLink *link, ifstream &cfg_ptr);
   virtual void setRevDCMotorParameters(dmRevDCMotor *actuator, ifstream &cfg_ptr);
   void setActuator(dmRevoluteLink *link, ifstream &cfg_ptr);
   void setSphericalLinkParameters(dmSphericalLink *link, ifstream &cfg_ptr);
   void setMobileBaseParameters(dmMobileBaseLink *ref, ifstream &cfg_ptr);

private:
   dmLoader_dm(const dmLoader_dm &);              // not implemented
   dmLoader_dm & operator=(const dmLoader_dm &);  // not implemented
};

#endif
