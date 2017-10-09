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
 *     File: dmLock.cpp
 *   Author: Tom Stimson
 *  Created: 22 October 2000
 *  Summary: Binary semaphore.
 *****************************************************************************/

#if defined(WIN32)
#include <windows.h>
#endif

#include <dmLock.hpp>

#if defined(WIN32) || defined(sgi)
unsigned long dmLock::s_low_max = 30;
unsigned long dmLock::s_high_max = 1000;
#endif

//----------------------------------------------------------------------------
dmLock::dmLock()
{
#if defined(WIN32) || defined(sgi)
   m_lock = 0;
   m_last = 0;
   m_max = s_low_max;
#elif defined(vxw)
   m_lock = semBCreate(SEM_Q_FIFO, SEM_FULL);
#else
   pthread_mutex_init(&m_lock, NULL);
#endif
}

//----------------------------------------------------------------------------
dmLock::~dmLock()
{
#if defined(WIN32) || defined(sgi)
   // nothing to do
#elif defined(vxw)
   semDelete(m_lock);
#else
   pthread_mutex_destroy(&m_lock);
#endif
}



//----------------------------------------------------------------------------
// Atomic swap on unsigned long
// This is guaranteed to behave as though it were atomic only if all
// possibly concurrent updates use _Atomic_swap.
#if defined(sgi)
inline unsigned long dmAtomicSwap(unsigned long * __p, unsigned long __q) {
# if __mips < 3 || !(defined (_ABIN32) || defined(_ABI64))
   return test_and_set(__p, __q);
# else
   return __test_and_set(__p, (unsigned long)__q);
# endif
}
#elif defined(WIN32)
inline unsigned long dmAtomicSwap(unsigned long * __p, unsigned long __q) {
   return (unsigned long) InterlockedExchange((LPLONG)__p, (LONG)__q);
}
#endif


//----------------------------------------------------------------------------
void dmLock::acquire()
{
#if defined(WIN32) || defined(sgi)
   if (!dmAtomicSwap((unsigned long*)&m_lock, 1)) {
      return;
   }
   unsigned spin_max = m_max;
   unsigned last_spins = m_last;
   volatile unsigned junk = 17;      // Value doesn't matter.
   unsigned i;
   for (i = 0; i < spin_max; ++i) {
      if (i < last_spins/2 || m_lock) {
         junk *= junk; junk *= junk;
         junk *= junk; junk *= junk;
         continue;
      }
      if (!dmAtomicSwap((unsigned long*)&m_lock, 1)) {
         // got it!
         // Spinning worked.  Thus we're probably not being scheduled
         // against the other process with which we were contending.
         // Thus it makes sense to spin longer the next time.
         m_last = i;
         m_max = s_high_max;
         return;
      }
   }
   // We are probably being scheduled against the other process.  Sleep.
   m_max = s_low_max;
   for (i = 0 ;; ++i) {
      int log_nsec = i + 6;

      if (log_nsec > 27) log_nsec = 27;
      if (!dmAtomicSwap((unsigned long *)&m_lock, 1)) {
         return;
      }
# if defined(WIN32)
      if (log_nsec <= 20) {
         Sleep(0);
      } else {
         Sleep(1 << (log_nsec - 20));
      }
# else
      struct timespec ts;
      /* Max sleep is 2**27nsec ~ 60msec      */
      ts.tv_sec = 0;
      ts.tv_nsec = 1 << log_nsec;
      nanosleep(&ts, 0);
# endif
   }
#elif defined(vxw)
   semTake(m_lock, WAIT_FOREVER);
#else
   pthread_mutex_lock(&m_lock);
#endif
}

//----------------------------------------------------------------------------
void dmLock::release()
{
#if defined(WIN32) || defined(sgi)
   dmAtomicSwap((unsigned long *)&m_lock, 0);
#elif defined(vxw)
   semGive(m_lock);
#else
   pthread_mutex_unlock(&m_lock);
#endif
}
