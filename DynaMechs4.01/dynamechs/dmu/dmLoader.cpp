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
 *     File: dmLoader.cpp
 *   Author: Scott McMillan
 *  Created: 12 February 2001
 *****************************************************************************/

#ifdef WIN32
# include <windows.h>
#endif

#include <dmLoader.hpp>
#include <dmLoader_dm203.hpp>
#include <dmLoader_dm21.hpp>
#include <dmLoader_dm30.hpp>
#include <dmLoader_dm40.hpp>
#include <dmLoader_env.hpp>

#include <stdio.h>
#include <ctype.h>

#ifndef WIN32
# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include <errno.h>
# if defined(vxw)
#  include <sysSymTbl.h>
#  include <symLib.h>
#  include <loadLib.h>
# else
#  include <dlfcn.h>
# endif
#endif


//----------------------------------------------------------------------------
// model and image paths

vector<string> dmLoader::s_data_path;

#ifdef WIN32
string dmLoader::s_dir_separators("\\/");
#else
string dmLoader::s_dir_separators("/");
#endif

dmLock dmLoader::s_lock;

//----------------------------------------------------------------------------
class dmLoaderStaticInitializer
{
public:
   dmLoaderStaticInitializer()
      {
         vector<string> path;
         if (getenv("DM_DATA_PATH"))
         {
            dmLoader::splitString(getenv("DM_DATA_PATH"), path);
         }
         dmLoader::setDataPath(path);
      }
   ~dmLoaderStaticInitializer() {}
};

static dmLoaderStaticInitializer initializer;


//----------------------------------------------------------------------------
dmLoader::dmLoader() :
      m_line_num(0),
      m_line(),
      m_current_pos(0)
{
}

//----------------------------------------------------------------------------
dmLoader::~dmLoader()
{
}

//----------------------------------------------------------------------------
void dmLoader::splitString(
   const string &str, vector<string> &vec, const string &delimiters)
{
   vec.clear();
   string::size_type start = 0;
   string::size_type next;
   while ((next = str.find_first_of(delimiters, start)) != string::npos)
   {
      vec.push_back(str.substr(start, next-start));
      start = next+1;
   }
   if (start != str.length())
      vec.push_back(str.substr(start, next-start));
}

//----------------------------------------------------------------------------
void dmLoader::setDataPath(const vector<string> &path)
{
   s_lock.acquire();
   if (!path.empty())
      s_data_path = path;
   else
   {
      s_data_path.clear();
      s_data_path.push_back(string("."));
   }
   s_lock.release();
}

//----------------------------------------------------------------------------
void dmLoader::getDataPath(vector<string> &path)
{
   s_lock.acquire();
   path = s_data_path;
   s_lock.release();
}

//----------------------------------------------------------------------------
// strips any path information from filename
string dmLoader::extractFilenameFromPath(const string &filepath)
{
   string::size_type pos = filepath.find_last_of(s_dir_separators);
   if (pos == string::npos)
      return filepath;
   else if (pos == filepath.length()-1)
      return string("");
   else
      return filepath.substr(pos+1);
}

//----------------------------------------------------------------------------
// strips any path information from filename
string dmLoader::extractDirectoryFromPath(const string &filepath)
{
   string::size_type pos = filepath.find_last_of(s_dir_separators);
   if (pos == string::npos)
      return string("");
   else if (pos == filepath.length()-1)
      return filepath;
   else
      return filepath.substr(0, pos);
}

//----------------------------------------------------------------------------
// extracts extension of filename
string dmLoader::extractExtensionFromFilename(const string &filename)
{
   string::size_type pos = filename.rfind('.');
   if (pos == string::npos || pos == filename.length()-1)
      return string("");
   else
      return filename.substr(pos+1);
}

//----------------------------------------------------------------------------
bool dmLoader::compareExtension(const string &filename, const string &ext)
{
   if (strCaseCmp(extractExtensionFromFilename(filename).c_str(),
                  ext.c_str()) == 0)
      return true;
   else
      return false;
}

//----------------------------------------------------------------------------
bool dmLoader::checkFile(const string &filename)
{
   FILE *fh = fopen(filename.c_str(), "rb");
   if (fh)
   {
      fclose(fh);
      return true;
   }
   return false;
}

//----------------------------------------------------------------------------
bool dmLoader::searchDir(
   const string &directory, const string &filename, string &foundname)
{
#if defined(WIN32)
   string search_string = directory + "/*";
   BOOL ret = true;
   WIN32_FIND_DATA find_data;
   HANDLE hFind = FindFirstFile(search_string.c_str(), &find_data);
   while (hFind != INVALID_HANDLE_VALUE && ret)
   {
      if (strCaseCmp(find_data.cFileName, filename.c_str()) == 0)
      {
         foundname = find_data.cFileName;
         FindClose(hFind);
         return true;
      }
      ret = FindNextFile(hFind, &find_data);
   }
   FindClose(hFind);
   return false;
#elif defined(vxw)
   // HACK This isn't thread safe.
   DIR *dir = opendir((char *)directory.c_str());
   if (dir)
   {
      dirent *dp;
      while ((dp = readdir(dir)) != NULL)
      {
         if (strCaseCmp(dp->d_name, filename.c_str()) == 0)
         {
            foundname = dp->d_name;
            closedir(dir);
            return true;
         }
      }
      closedir(dir);
   }
   return false;
#else
   long namemax = pathconf(directory.c_str(), _PC_NAME_MAX);
   if (namemax <= 0)
   {
      if (errno != 0 && errno != EINVAL)
         return false;
      else
         // _PC_NAME_MAX is not supported by the underlying filesystem.
         // Use a large default number and hope for the best.
         namemax = 10240;
   }

   DIR *dir = opendir(directory.c_str());
   if (dir)
   {
      dirent *dp = (dirent*)malloc(sizeof(dirent) + namemax + 1);
      if (dp)
      {
         dirent *dpp;
         while (readdir_r(dir, dp, &dpp) == 0 && dpp == dp)
         {
            if (strCaseCmp(dp->d_name, filename.c_str()) == 0)
            {
               foundname = dp->d_name;
               closedir(dir);
               free(dp);
               return true;
            }
         }
         free(dp);
      }
      closedir(dir);
   }
   return false;
#endif
}

//----------------------------------------------------------------------------
bool dmLoader::findFile(const string &filepath,
                        const string *alternate_path,
                        string &foundname)
{
   // Try filename "as is" (including any path).
   foundname = filepath;
   if (checkFile(foundname))
      return true;

   string fname = extractFilenameFromPath(filepath);
   string pname(filepath, 0, filepath.length() - fname.length());
   string tmp_path;
   string tmp_name;

   // Try case insensitive in given path.
   if (searchDir(pname, fname, tmp_name))
   {
      foundname = pname + "/" + tmp_name;
      return true;
   }

   if (alternate_path && !alternate_path->empty())
   {
      // strip trailing slashes
      string alt = *alternate_path;
      while (alt.find_last_of(s_dir_separators) == alt.length()-1)
         alt.resize(alt.length()-1);

      // Try case sensitive in alternate path.
      foundname = alt + "/" + fname;
      if (checkFile(foundname))
         return true;

      // Try case insensitive in alternate path.
      if (searchDir(alt, fname, tmp_name))
      {
         foundname = alt + "/" + tmp_name;
         return true;
      }

      tmp_path = alt + "/" + pname;

      // Try case sensitive in alternative path + given path.
      foundname = tmp_path + "/" + fname;
      if (checkFile(foundname))
         return true;

      // Try case insensitive in alternative path + given path.
      if (searchDir(tmp_path, fname, tmp_name))
      {
         foundname = tmp_path + "/" + tmp_name;
         return true;
      }
   }

   // Try the search paths.
   vector<string> path;
   getDataPath(path);
   for (vector<string>::const_iterator it = path.begin();
        it != path.end(); ++it)
   {
      // Try case sensitive.
      foundname = *it + "/" + fname;
      if (checkFile(foundname))
         return true;

      // Try case insensitive.
      if (searchDir(*it, fname, tmp_name))
      {
         foundname = *it + "/" + tmp_name;
         return true;
      }

      tmp_path = *it + "/" + pname;

      // Try case sensitive.
      foundname = tmp_path + "/" + fname;
      if (checkFile(foundname))
         return true;

      // Try case insensitive.
      if (searchDir(tmp_path, fname, tmp_name))
      {
         foundname = tmp_path + "/" + tmp_name;
         return true;
      }
   }

   foundname = "";
   return false;
}

//----------------------------------------------------------------------------
void dmLoader::toUpper(string &str)
{
   string::iterator end = str.end();
   for (string::iterator elt = str.begin(); elt != end; ++elt)
   {
      *elt = toupper(*elt);
   }
}

//----------------------------------------------------------------------------
void dmLoader::toLower(string &str)
{
   string::iterator end = str.end();
   for (string::iterator elt = str.begin(); elt != end; ++elt)
   {
      *elt = tolower(*elt);
   }
}

//----------------------------------------------------------------------------
int dmLoader::strCaseCmp(const char *s1, const char *s2 )
{
    int l1 = strlen ( s1 ) ;
    int l2 = strlen ( s2 ) ;

    //if ( l1 != l2 ) return FALSE ;
    int min_len = (l1<l2 ? l1 : l2);

    for (int i = 0; i < min_len; i++)
    {
        int c1 = s1[i];
        if (c1 >= 'A' && c1 <= 'Z')
            c1 += ('a' - 'A');

        int c2 = s2[i];
        if (c2 >= 'A' && c2 <= 'Z')
            c2 += ('a' - 'A');

        if (c1 == c2)
            continue;

        else if (c1 < c2) return -1;
        else              return 1;
    }

    if (l1 == l2)
        return 0;
    else if (l1 < l2)
        return -1;
    else // (l1 > l2)
        return 1;
}

//----------------------------------------------------------------------------
void dmLoader::strToken(string &tok)
{
   m_current_pos = m_line.find_first_not_of(" \t\n\r", m_current_pos);
   if (m_current_pos == string::npos)
   {
      tok.erase();
      return;
   }

   string::size_type new_pos = m_line.find_first_of(" \t\n\r", m_current_pos);

   if (new_pos != string::npos)
   {
      tok = m_line.substr(m_current_pos, new_pos - m_current_pos);
      m_current_pos = new_pos + 1;
   }
   else
   {
      if (m_current_pos < m_line.length())
      {
         tok = m_line.substr(m_current_pos, m_line.length() - m_current_pos);
         m_current_pos = m_line.length();
      }
      else
         tok.erase();
   }
}

//----------------------------------------------------------------------------
void dmLoader::parseToken(ifstream &cfg_ptr, string &tok)
{
   if (cfg_ptr.eof())
   {
      cerr << "dmLoader::parseToken error1: unexpected EOF encountered"
           << endl;
      exit(1);
   }

   strToken(tok);

   while (tok.empty() || tok[0] == COMMENT_CHAR)
   {
      if (!cfg_ptr.eof())
      {
         char tmp[256];
         cfg_ptr.getline(tmp, 255);
         m_line_num++;
         m_line = string(tmp); // inefficient copy

         //cerr << "got line: " << m_line << endl;

         m_current_pos = 0;
         strToken(tok);
      }
      else
      {
         cerr << "dmLoader::parseToken error2: unexpected EOF encountered"
              << endl;
         exit(2);
      }
   }
}

//----------------------------------------------------------------------------
Float dmLoader::parseFloat(ifstream &cfg_ptr)
{
   string tok;
   parseToken(cfg_ptr, tok);
   return (Float)atof(tok.c_str());
}

//----------------------------------------------------------------------------
int dmLoader::parseInt(ifstream &cfg_ptr)
{
   string tok;
   parseToken(cfg_ptr, tok);
   return atoi(tok.c_str());
}

//----------------------------------------------------------------------------
void dmLoader::readConfigParameterLabel(ifstream &cfg_ptr,
                                        const string &label)
{
   string tok;
   while (tok != label)
   {
      parseToken(cfg_ptr, tok);
   }
}

//----------------------------------------------------------------------------
//    Summary: scan file until first double quote enclosed string is found,
//             and return this string.
// Parameters: cfg_ptr - ifstream reference to file to be scanned
//             filename - string scanned between double quotes (on return)
//    Returns: true if a double-quote enclosed string is found, else false
//----------------------------------------------------------------------------
bool dmLoader::getStringParameter(ifstream &cfg_ptr, string &name)
{
   string tok;
   parseToken(cfg_ptr, tok);

   const string delim = "\042";

   string::size_type pos = tok.find_first_of(delim);
   if (pos != string::npos)
   {
      string::size_type pos2 = tok.find_first_of(delim, pos + 1);
      if (pos2 != string::npos)
      {
         name = tok.substr(pos + 1, pos2 - pos - 1);
         return true;
      }
   }

   return false;
}

//----------------------------------------------------------------------------
bool dmLoader::getStringParameter(ifstream &cfg_ptr,
                                  const string &label,
                                  string &name)
{
   readConfigParameterLabel(cfg_ptr, label.c_str());
   return getStringParameter(cfg_ptr, name);
}

//----------------------------------------------------------------------------
void dmLoader::parseToBlockBegin(ifstream &cfg_ptr)
{
   string tok;

   do
   {
      parseToken(cfg_ptr, tok);
   } while (tok[0] != BLOCK_BEGIN_CHAR);
}

//----------------------------------------------------------------------------
void dmLoader::parseToBlockEnd(ifstream &cfg_ptr)
{
   unsigned int indent_level = 1;
   string tok;

   do
   {
      parseToken(cfg_ptr, tok);

      if (tok[0] == BLOCK_END_CHAR)
      {
         indent_level--;
      }
      else if (tok[0] == BLOCK_BEGIN_CHAR)
      {
         indent_level++;
      }
   } while ((tok[0] != BLOCK_END_CHAR) || (indent_level != 0));
}

//----------------------------------------------------------------------------
dmSystem* dmLoader::loadDMFile(const string &filename)
{
   dmSystem *robot = NULL;

   string foundName;
   if (!findFile(filename, NULL, foundName))
   {
      cerr << "dmLoader::loadDMFile() error: file not found: "
           << filename << endl;
      exit(6);
   }

   ifstream cfg_ptr(foundName.c_str());
   if (!cfg_ptr)
   {
      cerr << "dmLoader::loadDMFile() error: Unable to open robot "
           << "configuration file: " << foundName << endl;
      exit(7);
   }

   char line[256] = "\0";    // initialize the line to empty
   cfg_ptr.getline(line, 256);

   // Right now I support a number of formats and use the initial comment
   // string to determine which format the remainder of the file is in.

   if (strcmp(line, "# DynaMechs V 4.0 ascii") == 0)
   {
      dmLoader_dm40 ldr;
      robot = ldr.load(cfg_ptr);
   }
   else if (strcmp(line, "# DynaMechs V 3.0 ascii") == 0)
   {
      dmLoader_dm30 ldr;
      robot = ldr.load(cfg_ptr);
   }
   else if (strcmp(line, "# DynaMechs V 2.1 ascii") == 0)
   {
      dmLoader_dm21 ldr;
      robot = ldr.load(cfg_ptr);
   }
   else if (strcmp(line, "# DynaMechs V 2.0.3 ascii") == 0)
   {
      dmLoader_dm203 ldr;
      robot = ldr.load(cfg_ptr);
   }
   else
   {
      cerr << "dmLoader::loadDMFile() error: unknown format on line 1"
           << ": \"" << line << "\"" << endl;
   }

   cfg_ptr.close();
   return robot;
}

//----------------------------------------------------------------------------
dmEnvironment* dmLoader::loadENVFile(const string &filename)
{
   string foundName;
   if (!findFile(filename, NULL, foundName))
   {
      cerr << "dmLoader::loadEnvFile() error: file not found: "
           << filename << endl;
      return NULL;
   }

   dmLoader_env ldr;
   dmEnvironment *env = ldr.load(foundName);
   return env;
}
