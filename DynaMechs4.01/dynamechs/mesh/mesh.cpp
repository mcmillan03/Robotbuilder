/*****************************************************************************
 * Copyright 1999,
 *****************************************************************************
 *     File: mesh.cpp
 *   Author: Duane Marhefka
 *  Project: DynaMechs 3.0 - GLUT example
 *  Created:
 *  Summary:
 *      $Id:
 *****************************************************************************/

#include <GL/glut.h>

#include <dmGLMouse.hpp>
#include <dmGLPolarCamera_zup.hpp>

#include <dm.h>
#include <dmSystem.hpp>
#include <dmEnvironment.hpp>
#include <dmIntegRK45.hpp>

#include <dmu.h>
#include <dmLoader.hpp>

dmGLMouse *mouse;
dmGLPolarCamera_zup *camera;
GLfloat view_mat[4][4];

Float idt, actual_idt;
int paused_flag = false;

dmSystem *G_robot;
dmIntegRK45 *G_integrator;

int render_rate;
int timer_count = 0;

//----------------------------------------------------------------------------
//    Summary: Initialize material property and light source.
// Parameters:
//    Returns:
//----------------------------------------------------------------------------
void myinit (void)
{
   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

   glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv (GL_LIGHT0, GL_POSITION, light_position);

   glEnable (GL_LIGHTING);
   glEnable (GL_LIGHT0);
   glDepthFunc(GL_LESS);
   glEnable(GL_DEPTH_TEST);

   glShadeModel(GL_FLAT);
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
}
//----------------------------------------------------------------------------
//    Summary:
// Parameters:
//    Returns:
//----------------------------------------------------------------------------
void display (void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode (GL_MODELVIEW);
   glPushMatrix ();

   // ===============================================================
   (dmEnvironment::getEnvironment())->draw();

   glPushAttrib(GL_ALL_ATTRIB_BITS);
   G_robot->draw();
   glPopAttrib();
   // ===============================================================

   glPopMatrix ();

   glFlush ();
   glutSwapBuffers();
}

//----------------------------------------------------------------------------
//    Summary:
// Parameters:
//    Returns:
//----------------------------------------------------------------------------
void myReshape(int w, int h)
{
   glViewport (0, 0, w, h);
   mouse->win_size_x = w;
   mouse->win_size_y = h;

   camera->setPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0, 200.0);

   camera->setViewMat(view_mat);
   camera->applyView();
}

//----------------------------------------------------------------------------
//    Summary:
// Parameters:
//    Returns:
//----------------------------------------------------------------------------
void processKeyboard(unsigned char key, int, int)
{
   switch (key)
   {
      case 27:
         glutDestroyWindow(glutGetWindow());
         exit(1);
         break;

      case 'p':
         paused_flag = !paused_flag;
         break;
   }
}


//----------------------------------------------------------------------------
//    Summary:
// Parameters:
//    Returns:
//----------------------------------------------------------------------------
void updateSim()
{
   if (!paused_flag)
     {
       actual_idt = idt;
       G_integrator->simulate(actual_idt);
     }

   camera->update(mouse);
   camera->applyView();

   display();
}

//----------------------------------------------------------------------------
//    Summary:
// Parameters:
//    Returns:
//----------------------------------------------------------------------------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);

   //=========================
   char *filename = "mesh.cfg";
   if (argc > 1)
   {
      filename = argv[1];
   }

   glutInitWindowSize(480, 360);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutCreateWindow("Spherical Joint Mesh");

   myinit();
   mouse = dmGLMouse::dmInitGLMouse();

   camera = new dmGLPolarCamera_zup();
   camera->setRadius(10.0);
   camera->setCOI(2.0, 2.0, 2.5);
   camera->setTranslationScale(0.02f);

// ===========================================================================
// setting up a forgiving data path
   vector<string> path;
   path.push_back("./mesh");
   path.push_back("../mesh");
   path.push_back("../../mesh");
   dmLoader::setDataPath(path);

// ===========================================================================
   string foundName;
   if (!dmLoader::findFile(filename, NULL, foundName))
   {
      cerr << "Error: file not found: " << filename << endl;
      exit(1);
   }
   // load robot stuff
   ifstream cfg_ptr(foundName.c_str());
   if (!cfg_ptr)
   {
      cerr << "Error: file failed to open: " << foundName << endl;
      exit(1);
   }

   // Read simulation timing information.
   readConfigParameterLabel(cfg_ptr,"Integration_Stepsize");
   cfg_ptr >> idt;
   if (idt <= 0.0)
   {
      cerr << "main error: invalid integration stepsize: " << idt << endl;
      exit(3);
   }

   readConfigParameterLabel(cfg_ptr,"Display_Update_Rate");
   cfg_ptr >> render_rate;
   if (render_rate < 1) render_rate = 1;

// ===========================================================================
// Initialize DynaMechs environment - must occur before any linkage systems
   string env_flname;
   readConfigParameterLabel(cfg_ptr,"Environment_Parameter_File");
   readFilename(cfg_ptr, env_flname);
   dmEnvironment *environment = dmLoader::loadENVFile(env_flname);
   environment->drawInit();
   dmEnvironment::setEnvironment(environment);

// ===========================================================================
// Initialize a DynaMechs linkage system
   string robot_flname;
   readConfigParameterLabel(cfg_ptr,"Robot_Parameter_File");
   readFilename(cfg_ptr, robot_flname);
   G_robot = dmLoader::loadDMFile(robot_flname);

   G_integrator = new dmIntegRK45();
   G_integrator->addSystem(G_robot);
   G_integrator->setMaxSteps(400);
   G_integrator->setErrorBound((Float)1.e-4, (Float)1.e-4);

   glutReshapeFunc(myReshape);
   glutKeyboardFunc(processKeyboard);
   glutDisplayFunc(display);
   glutIdleFunc(updateSim);

   cout << endl;
   cout << "p - toggles dynamic simulation" << endl;
   cout << "Use mouse to rotate/move/zoom the camera" << endl << endl;

   glutMainLoop();
   return 0;             /* ANSI C requires main to return int. */
}
