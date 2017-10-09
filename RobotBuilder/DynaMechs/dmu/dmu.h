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
 *     File: dmu.h
 *   Author: Scott McMillan
 *  Created:
 *  Summary: A collection of miscellaneous useful functions
 *****************************************************************************/

#ifndef _DMU_H
#define _DMU_H

#if defined(WIN32) && defined(_DLL)
// The next define will come from the makefile for archive objects.
#ifdef dmu_DLL_FILE
#define DMU_DLL_API __declspec(dllexport)
#else
#define DMU_DLL_API __declspec(dllimport)
#endif
#else
#define DMU_DLL_API
#endif

#include <dm.h>
#include <string>

class dmObject;
class dmSystem;
class dmArticulation;
class dmEnvironment;

/** Find a dmObject with the given name in the specified dmArticulation.
    @param name String containing the name to find.
    @param system Pointer to system in which to search.
    @return Pointer to object.  NULL if object with given name is not found or
            system is NULL.
 */
DMU_DLL_API dmObject *dmuFindObject(const string &name,
                                    dmArticulation *system);

/** Scan file from the current position until first double-quote enclosed
    string is found, and return this string.
    @param cfg_ptr ifstream referenc to file to be scanned.  The search will
                   begin a the current stream position.
    @param filename string containing the quote enclosed string.
    @return true if a double-quote enclosed string was found; otherwise, false.
*/
DMU_DLL_API bool readFilename(ifstream &cfg_ptr, string &filename);

/** Scan a file from the current position until a particular string is found.
    It will exit (not return) if the EOF is encountered before the search
    string is found.
    @param cfg_ptr ifstream referenc to file to be scanned.  The search will
                   begin a the current stream position.
    @param label string to be searched for.
*/
DMU_DLL_API void readConfigParameterLabel(ifstream &cfg_ptr,
                                          const string &label);

const char COMMENT_CHAR = '#';

#endif
