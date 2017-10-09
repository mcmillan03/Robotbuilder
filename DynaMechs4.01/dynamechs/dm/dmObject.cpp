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
 *     File: dmObject.cpp
 *   Author: Scott McMillan
 *  Summary: used to name and attach user data to all classes
 *****************************************************************************/

#include <dm.h>
#include <dmObject.hpp>

//============================================================================
// class dmObject
//============================================================================

//----------------------------------------------------------------------------
dmObject::dmObject()
      : m_user_data(NULL),
        m_name()
{
}

//----------------------------------------------------------------------------
dmObject::~dmObject()
{
   /* FIXME - without reference counting and not knowing which mechanism
              (malloc or new) was used I cannot dealloc the user data. */
}

//----------------------------------------------------------------------------
void dmObject::setName(const string &name)
{
   m_name = name;
}
