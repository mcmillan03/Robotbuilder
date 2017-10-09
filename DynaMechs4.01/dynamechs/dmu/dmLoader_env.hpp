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
 *     File: dmLoader_env.hpp
 *   Author: Scott McMillan
 *  Created: 14 August 2001
 *  Summary: Abstract base class for DynaMechs env configuration file loaders.
 *****************************************************************************/

#ifndef _DM_LOADER_ENV
#define _DM_LOADER_ENV

#include <dmLoader.hpp>

class dmEnvironment;

//----------------------------------------------------------------------------

class DMU_DLL_API dmLoader_env : public dmLoader
{
public:
   /** Constructor. */
   dmLoader_env();

   /** Destructor. */
   virtual ~dmLoader_env() {}

   /** non-reentrant loader function */
   virtual dmEnvironment *load(const string &filename);

protected:
   void setEnvironmentParameters(dmEnvironment *env, ifstream &cfg_ptr);

private:
   dmLoader_env(const dmLoader_env &);              // not implemented
   dmLoader_env & operator=(const dmLoader_env &);  // not implemented
};

#endif
