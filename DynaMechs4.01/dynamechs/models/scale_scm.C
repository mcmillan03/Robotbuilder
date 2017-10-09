// ***************************************************************************
//     File: glLoadModels.C
//   Author: Scott McMillan
//  Project: 
//  Created: 21 May 1997
//  Summary: 
// Modified: 
// Archived: 
// ***************************************************************************

#include <fstream.h>
#include <iostream.h>
#include <string.h>

//----------------------------------------------------------------------------
void main(int argc, char **argv)
{
   register int i,j;
   ifstream data_ptr;

   data_ptr.open(argv[1]);
   if (!data_ptr)
   {
      cerr << "loadModel_scm: Error unable to open data file: "
           << argv[1] << endl;
      exit(4);
   }

   int num_faces, num_vertices, num_vertices_tot;
   float alpha, shininess;
   float color[4] = {0.0, 0.0, 0.0, 1.0};
   float vertex[3];

      data_ptr >> color[0] >> color[1] >> color[2];  // emission color
      cout << color[0] << ' ' << color[1] << ' ' << color[2] << endl;
      data_ptr >> color[0] >> color[1] >> color[2];  // ambient color
      cout << color[0] << ' ' << color[1] << ' ' << color[2] << endl;
      data_ptr >> color[0] >> color[1] >> color[2];  // diffuse color
      cout << color[0] << ' ' << color[1] << ' ' << color[2] << endl;
      data_ptr >> color[0] >> color[1] >> color[2];  // specular color
      cout << color[0] << ' ' << color[1] << ' ' << color[2] << endl;
      data_ptr >> shininess;
      cout << shininess << endl;
      data_ptr >> alpha;
      cout << alpha << endl << endl;
      
      data_ptr >> num_faces;
      cout << num_faces << endl;
      data_ptr >> num_vertices_tot;
      cout << num_vertices_tot << endl;
      
      for (i=0; i<num_faces; i++)
      {
         data_ptr >> num_vertices;
         cout << endl << num_vertices << endl;

         for (j=0; j<num_vertices; j++)
         {
            data_ptr >> vertex[0] >> vertex[1] >> vertex[2];
            cout << 5.0*vertex[0] << ' ' << 5.0*vertex[1] << ' '
                 << 5.0*vertex[2] << endl;
         }
      }
}
