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
 *     File: dmLoader_env.cpp (was dmLoadfile_env.cpp)
 *   Author: Scott McMillan
 *  Created: 14 August 2001
 *  Summary: load environment files and piece together a dmEnvironment
 *****************************************************************************/

#include <dmLoader_env.hpp>
#include <dmEnvironment.hpp>

//----------------------------------------------------------------------------
dmLoader_env::dmLoader_env() : dmLoader()
{
}

//----------------------------------------------------------------------------
//    Summary: Parser for dmEnvironment class loads in all sorts of stuff
// Parameters: cfg_ptr - ifstream containing the necessary parameters to
//                       initialize this class
//    Returns: none
//----------------------------------------------------------------------------
void dmLoader_env::setEnvironmentParameters(dmEnvironment *env,
                                            ifstream &cfg_ptr)
{
   unsigned int i;

   CartesianVector gravity;
   readConfigParameterLabel(cfg_ptr, "Gravity_Vector");
   for (i=0; i<3; ++i)
   {
      gravity[i] = parseFloat(cfg_ptr);
   }
   env->setGravity(gravity);

   // get terrain model.
   string fname;            // filename w/ gridded terrain data
   if (getStringParameter(cfg_ptr, "Terrain_Data_Filename", fname))
   {
      string foundName;
      if (findFile(fname, NULL, foundName))
      {
#ifdef DEBUG
         cerr << "Terrain data file: " << foundName << endl;
#endif
         env->loadTerrainData(foundName);
      }
      else
      {
         cerr << "dmLoader_env::setEnvironmentParameters() error: "
              << "terrain data file not found: " << fname << endl;
      }
   }

   // get ground characteristics.
   Float constant;
   readConfigParameterLabel(cfg_ptr, "Ground_Planar_Spring_Constant");
   constant = parseFloat(cfg_ptr);
   env->setGroundPlanarSpringConstant(constant);

   readConfigParameterLabel(cfg_ptr, "Ground_Normal_Spring_Constant");
   constant = parseFloat(cfg_ptr);
   env->setGroundNormalSpringConstant(constant);

   readConfigParameterLabel(cfg_ptr, "Ground_Planar_Damper_Constant");
   constant = parseFloat(cfg_ptr);
   env->setGroundPlanarDamperConstant(constant);

   readConfigParameterLabel(cfg_ptr, "Ground_Normal_Damper_Constant");
   constant = parseFloat(cfg_ptr);
   env->setGroundNormalDamperConstant(constant);

   readConfigParameterLabel(cfg_ptr, "Ground_Static_Friction_Coeff");
   Float u_s = parseFloat(cfg_ptr);
   readConfigParameterLabel(cfg_ptr, "Ground_Kinetic_Friction_Coeff");
   Float u_k = parseFloat(cfg_ptr);

   if (u_k > u_s)
   {
      cerr << "dmLoader_env::setEnvironmentParameters warning: "
           << "u_k > u_s friction coefficient.\n";
   }
   env->setFrictionCoeffs(u_s, u_k);

#ifdef DM_HYDRODYNAMICS
   readConfigParameterLabel(cfg_ptr, "Fluid_Density");
   Float fluid_density = parseFloat(cfg_ptr);

   env->setFluidDensity(fluid_density);
#endif
}

//----------------------------------------------------------------------------
dmEnvironment *dmLoader_env::load(const string &filename)
{
   ifstream env_ptr(filename.c_str());
   if (!env_ptr)
   {
      cerr << "dmLoader_env::load() error: "
           << "Unable to open dmEnvironment configuration file: "
           << filename << endl;
      return NULL;
   }

   dmEnvironment *env = new dmEnvironment;
   setEnvironmentParameters(env, env_ptr);
   env_ptr.close();
   return env;
}
