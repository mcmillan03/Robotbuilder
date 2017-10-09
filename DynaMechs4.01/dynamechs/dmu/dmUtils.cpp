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
 *     File: dmUtils.cpp
 *   Author: Scott McMillan
 *  Created:
 *  Summary: A collection of miscellaneous useful functions
 *****************************************************************************/

#include <dm.h>
#include <dmu.h>
#include <dmObject.hpp>
#include <dmSystem.hpp>
#include <dmArticulation.hpp>
#include <dmClosedArticulation.hpp>
#include <dmLink.hpp>
#include <dmSecondaryJoint.hpp>

//----------------------------------------------------------------------------
dmObject *dmuFindObject(const string &label, dmArticulation *system)
{
   string name;

   if ((system == NULL) || (label.empty()) || (label[0] == '\0'))
   {
      return NULL;
   }

   // check the System object first
   name = system->getName();
   if (!name.empty() && name == label)
   {
      return system;
   }

   // check the links
   for (unsigned int j=0; j<system->getNumLinks(); j++)
   {
      dmLink *link = system->getLink(j);
      name = link->getName();
      if (!name.empty() && name == label)
      {
         return link;
      }
   }

   // if system is a closed articulation, check the secondary joints
   dmClosedArticulation *CArt =
      dynamic_cast<dmClosedArticulation*>(system);
   if (CArt)
   {
      // Check 'Hard' secondary joints.
      unsigned int j;
      for (j=0; j<CArt->getNumHardSecondaryJoints(); j++)
      {
         dmSecondaryJoint *secJoint = CArt->getHardSecondaryJoint(j);
         name = secJoint->getName();
         if (!name.empty() && name == label)
         {
            return secJoint;
         }
      }

      // Check 'Soft' secondary joints.
      for (j=0; j<CArt->getNumSoftSecondaryJoints(); j++)
      {
         dmSecondaryJoint *secJoint = CArt->getSoftSecondaryJoint(j);
         name = secJoint->getName();
         if (!name.empty() && name == label)
         {
            return secJoint;
         }
      }
   }

   return NULL;
}

//----------------------------------------------------------------------------
bool strToken(ifstream &cfg_ptr, string &token)
{
   register int i;
   register unsigned char c = '\0';

   const unsigned int BUF_SIZE = 2047;
   char line[BUF_SIZE + 1];

   bool stop = false;

   // Strip off blank lines and comment lines.
   while (!stop && ((i = cfg_ptr.get()) != EOF))
   {
      c = (unsigned char) i;

      if ((c == '\n') || (c == COMMENT_CHAR))
      {
         while ((c != '\n') && ((i = cfg_ptr.get()) != EOF))
         {
            c = (unsigned char) i;
         }
      }
      else
      {
         stop = true;
      }
   }

   if (!stop)
   {
      cerr << "Error: unexpected EOF encountered." << endl;
      exit(4);
   }

   cfg_ptr.putback(c);

   // Read in the strings until label is found or EOF encountered.
   while ((cfg_ptr >> line))
   {
      if ((line[0] != COMMENT_CHAR) && (line[0] != '\n'))
      {
         token = string(line);
         return true;
      }
      else
      {
         c = '\0';
         while ((c != '\n') && ((i = cfg_ptr.get()) != EOF))
         {
            c =  (unsigned char) i;
         }
      }
   }

   cerr << "Error: unexpected EOF encountered." << endl;
   exit(4);
}

//----------------------------------------------------------------------------
bool readFilename(ifstream &cfg_ptr, string &filename)
{
   // HACK - I dislike having to fix the buffer size
   const unsigned int BUF_SIZE = 2047;
   char buf[BUF_SIZE + 1];

   if (cfg_ptr.getline(buf, BUF_SIZE, '\042'))
   {
      if (cfg_ptr.getline(buf, BUF_SIZE, '\042'))
      {
         if (strlen(buf) > 0)
         {
            //cerr << "readFilename: " << filename << endl;
            filename = string(buf);
            return true;
         }
      }
   }
   return false;
}

//----------------------------------------------------------------------------
void readConfigParameterLabel(ifstream &cfg_ptr, const string &label)
{
   string token;
   strToken(cfg_ptr, token);

   while (token != label)
   {
      cerr << "Warning: skipped unrecognized parameter: " << token << endl;
      cerr << "   Wanted: " << label << endl;
      strToken(cfg_ptr, token);
   }
}
