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
 *     File: dmIntegEuler.hpp
 *   Author: Steven Rodenbaugh (based on work by Scott McMillan)
 *  Summary: Integrator stub for a kinematic simulator (position only)
 *****************************************************************************/

#ifndef _DM_INTEG_PLACEMENT_HPP
#define _DM_INTEG_PLACEMENT_HPP

#include <dm.h>
#include <dmIntegrator.hpp>

//============================================================================

/**
This 'integrator' can be used in a kinematic simulation where the links are
placed in the desired position by the 'controller'.  This class serves as an 
intergrator class placeholder so the user can instantiate a kinematic or
dynamic integrator class using the same DynaMechs code.
*/

//======================================================================

class DM_DLL_API dmIntegPlacement : public dmIntegrator  
{
   public:
   ///
   dmIntegPlacement();
   ///
   virtual ~dmIntegPlacement();
   ///
   void synchronizeState () {};
   ///
   void simulate (Float &idt) {};

private:
   // not implemented
   dmIntegPlacement(const dmIntegPlacement &);
   dmIntegPlacement &operator=(const dmIntegPlacement &);
   
   bool allocateStateVariables ();
};

#endif