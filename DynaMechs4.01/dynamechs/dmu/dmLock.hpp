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
 *     File: dmLock.hpp
 *   Author: Tom Stimson
 *  Created: 22 October 2000
 *  Summary: Binary semaphore.
 *****************************************************************************/

/*
 * Copyright (c) 1997-1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */


#ifndef __DM_LOCK_HPP
#define __DM_LOCK_HPP

#include <dmu.h>

#if defined(sgi)
# include <mutex.h>
# include <time.h>
#elif defined(vxw)
# include <semLib.h>
#elif defined(WIN32)
//do nothing
#else // assume posix
# include <pthread.h>
#endif

//----------------------------------------------------------------------------

/** This implementation of a cross-platform lock is largely derived from
    the stl_threads.h file of SGI's STL v3.3, which contains the above
    notice.  For the original code, see http://www.sgi.com/Technology/STL.
*/

class DMU_DLL_API dmLock
{
public:
   ///
   dmLock();
   ///
   ~dmLock();

   /// Get the lock.
   void acquire();

   /// Release the lock.
   void release();

private:
   // not implemented
   dmLock(const dmLock &);
   dmLock &operator=(const dmLock &);

private:
#if defined(WIN32) || defined(sgi)
   volatile unsigned long m_lock;
   unsigned long m_last;
   unsigned long m_max;
   static unsigned long s_low_max;
   static unsigned long s_high_max;
#elif defined(vxw)
   SEM_ID m_lock;
#else // assume posix
   pthread_mutex_t m_lock;
#endif
};

#endif
