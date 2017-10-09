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
 *     File: dmLoader.hpp
 *   Author: Scott McMillan
 *  Created: 12 February 2001
 *  Summary: base class for system configuration files
 *****************************************************************************/

#ifndef _DM_DATA_LOADER
#define _DM_DATA_LOADER

#include <dmu.h>
#include <string>
#include <vector>
#include <dmLock.hpp>

const char BLOCK_BEGIN_CHAR = '{';
const char BLOCK_END_CHAR = '}';

enum actuatorTypes {NOMOTOR = 0, DCMOTOR = 1};

class dmSystem;
class dmEnvironment;

/** Abstract base class for loading DynaMechs configuration files.
    Encapsulates helper routines for file loading.
 */

class DMU_DLL_API dmLoader
{
public:
   /** Constructor. */
   dmLoader();

   /** Destructor. */
   virtual ~dmLoader() = 0;

   /** Helper function that splits a single string into multiple strings.
       @param str the string to be split
       @param vec on return contains the set of substrings
       @param delimiters the set of characters, any one of which may be
              used to delimit the substrings within the input string
   */
   static void splitString(const string &str,
                           vector<string> &vec,
                           const string &delimiters = string(";"));

   /** Set the data path used for searching for image or model files.
       @param path the path, if empty the data path will be reset to the
              default "."
   */
   static void setDataPath(const vector<string> &path);

   /** Get the current data path.
       @param path on return contains the directories that are searched
   */
   static void getDataPath(vector<string> &path);

   /** Strip the directory from the filepath.
       @param filepath string to extract filename from
       @return string containing just the filename without any directory
   */
   static string extractFilenameFromPath(const string &filepath);

   /** Strip the filename from the filepath.
       @param filepath string to extract directory from
       @return string containing just the directory without any filename
   */
   static string extractDirectoryFromPath(const string &filepath);

   /** Extract extension from the filename.
       @param filename string to extract extension from
       @return string containing just the extension.
   */
   static string extractExtensionFromFilename(const string &filename);

   /** Check to see if string has the given extension.
       @param filename filename to check the extension of
       @param extension string to check for at end of filename.
       @return true if the extension is found at the end of filename.
   */
   static bool compareExtension(const string &filename,
                                const string &extension);

   /** Performs a case insensitive search of the given directory for
       a file with the given name.
       @param directory name of the directory to search
       @param filename name of the file to find
       @param foundname on success is set to the name of the file found
       @return true if a file is found with the given name
   */
   static bool searchDir(const string &directory,
                         const string &filename,
                         string &foundname);

   /** Check to see if the given file exists and is readable.
       @param filename name of the file to check
       @return true if the file exists and is readable
   */
   static bool checkFile(const string &filename);

   /** Attempts to find a file with the given name.  If the file isn't
       found at the location given, a search will be made in the
       alternative_path directory.  If it still isn't found, a full search
       will be made in the entire data path.
       @param filepath full path name to where the file should be
       @param alternative_path an alternative directory to look in (if
              NULL, this variable will be ignored)
       @param foundname on success is set to the full path name
              of the file found
       @return true on success
   */
   static bool findFile(const string &filepath,
                        const string *alternate_path,
                        string &foundname);

   /** Perform a case insensitive comparison of the two strings.
       @param s1 a string to compare
       @param s2 a string to compare
       @return an integer less than, equal to, or greater than zero
              if s1 is found, respectively, to be less than, to match,
              or be greater than s2.
   */
   static int strCaseCmp(const char *s1, const char *s2);

   /** Convert the given string to uppercase.
       @param str the string to convert
   */
   static void toUpper(string &str);

   /** Convert the given string to lowercase.
       @param str the string to convert
   */
   static void toLower(string &str);

   /** reentrant loader function for dm configuration files */
   static dmSystem* loadDMFile(const string &filename);

   /** reentrant loader function for env configuration files */
   static dmEnvironment* loadENVFile(const string &filename);

protected:
   dmLoader(const dmLoader &);             // Not implemented.
   dmLoader &operator=(const dmLoader &);  // Not implemented.

   void strToken(string &tok);

   void  parseToken(ifstream &cfg_ptr, string &tok);
   Float parseFloat(ifstream &cfg_ptr);
   int   parseInt(ifstream &cfg_ptr);

   // Move the file position to the next '{' or '}'.
   void parseToBlockBegin(ifstream &cfg_ptr);
   void parseToBlockEnd(ifstream &cfg_ptr);

   // search through the file for the next occurence of 'label' and return with
   // the current position after that occurence.  Will call exit() if that
   // label is not found
   void readConfigParameterLabel(ifstream &cfg_ptr, const string &label);

   // Extracts the text (whitespace and all) from between double quotes.
   // Returns true if two double quotes were found
   bool getStringParameter(ifstream &cfg_ptr,
                           string &name);

   // Extracts the text (whitespace and all) from between double quotes, after
   // searching for the token equal to 'label'.
   // Returns true if two double quotes were found
   bool getStringParameter(ifstream &cfg_ptr,
                           const string &label,
                           string &name);

public:
   static string              s_dir_separators;

protected:
   unsigned int               m_line_num;
   string                     m_line;
   string::size_type          m_current_pos;

private:
   static vector<string>      s_data_path;
   static dmLock              s_lock;
};

#endif
