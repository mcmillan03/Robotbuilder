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
 *     File: simple.cpp
 *   Author: Scott McMillan
 *  Created: 20 March 1997
 *  Summary: simple GLUT example
 *****************************************************************************/

#include <GL/glut.h>

#include <dmTime.h>
#include <dmGLMouse.hpp>
#include <dmGLPolarCamera_zup.hpp>

#include <dm.h>            // DynaMechs typedefs, globals, etc.
#include <dmArticulation.hpp>      // DynaMechs simulation code.
#include <dmEnvironment.hpp>
#include <dmMobileBaseLink.hpp>
#include <dmContactModel.hpp>
#include <dmIntegRK4.hpp>

#include <dmLoader.hpp>
#include <glLoadModels.h>

dmGLMouse *mouse;
dmGLPolarCamera_zup *camera;
GLfloat view_mat[4][4];

Float idt;
Float sim_time=0.0;
Float rtime=0.0;
bool  paused_flag = true;

dmArticulation *G_robot;
dmIntegRK4 *G_integrator;

dmTimespec tv, last_tv;

int render_rate;
int render_count = 0;
int timer_count = 0;
int motion_plan_rate;       // fixed rate of 100Hz
int motion_plan_count = 0;  // counter for motion planning updates

float cmd_direction = 0.0;
float cmd_speed = 0.0;

//     light_position is NOT default value
GLfloat light_position[] = { 1.0, -1.0, 1.0, 0.0 };

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

   glDisable (GL_LIGHTING);

   glBegin(GL_LINES);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(2.0, 0.0, 0.0);
   glVertex3f(0.0, 0.0, 0.0);
   glEnd();

   glBegin(GL_LINES);
   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(0.0, 2.0, 0.0);
   glVertex3f(0.0, 0.0, 0.0);
   glEnd();

   glBegin(GL_LINES);
   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(0.0, 0.0, 2.0);
   glVertex3f(0.0, 0.0, 0.0);
   glEnd();

   glEnable (GL_LIGHTING);

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

   //if (w <= h)
   //    glOrtho (-2.5, 2.5, -2.5*(GLfloat)h/(GLfloat)w,
   //        2.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   //else
   //    glOrtho (-2.5*(GLfloat)w/(GLfloat)h,
   //        2.5*(GLfloat)w/(GLfloat)h, -2.5, 2.5, -10.0, 10.0);

   camera->setPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0, 200.0);

   //glMatrixMode (GL_MODELVIEW);
   //glLoadIdentity();
   //glTranslatef(0,0,-10.0);

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
void processSpecialKeys(int key, int, int)
{
   switch (key)
   {
      case GLUT_KEY_LEFT:
         cmd_direction += 5.0;
         if (cmd_direction > 180.0) cmd_direction -= 360.0;
         break;
      case GLUT_KEY_RIGHT:
         cmd_direction -= 5.0;
         if (cmd_direction < -180.0) cmd_direction += 360.0;
         break;
      case GLUT_KEY_UP:
         cmd_speed += 0.01f;
         if (cmd_speed > 0.25f) cmd_speed = 0.25f;
         break;
      case GLUT_KEY_DOWN:
         cmd_speed -= 0.01f;
         if (cmd_speed < 0.0) cmd_speed = 0.0;
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
      for (int i=0; i<render_rate; i++)
      {
         //computeControl(sim_time);
         G_integrator->simulate(idt);
         sim_time += idt;
      }
   }

   camera->update(mouse);
   camera->applyView();

   glLightfv (GL_LIGHT0, GL_POSITION, light_position);

   display();

   // compute render rate
   timer_count++;
   dmGetSysTime(&tv);
   double elapsed_time = ((double) tv.tv_sec - last_tv.tv_sec) +
      (1.0e-9*((double) tv.tv_nsec - last_tv.tv_nsec));

   if (elapsed_time > 2.5)
   {
      rtime += elapsed_time;
      cerr << "time/real_time: " << sim_time << '/' << rtime
           << "  frame_rate: " << (double) timer_count/elapsed_time << endl;

      timer_count = 0;
      last_tv.tv_sec = tv.tv_sec;
      last_tv.tv_nsec = tv.tv_nsec;
   }
}

//----------------------------------------------------------------------------
//    Summary:
// Parameters:
//    Returns:
//----------------------------------------------------------------------------
int main(int argc, char** argv)
{
   int i, j;

   glutInit(&argc, argv);

   glutInitWindowSize(700, 512);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutCreateWindow("Simple DynaMechs Example");

   myinit();
   mouse = dmGLMouse::dmInitGLMouse();

   for (i=0; i<4; i++)
   {
      for (j=0; j<4; j++)
      {
         view_mat[i][j] = 0.0;
      }
      view_mat[i][i] = 1.0;
   }
   view_mat[3][2] = -10.0;
   camera = new dmGLPolarCamera_zup();
   camera->setRadius(30.0);
   camera->setCOI(10.0, 10.0, 5.0);
   camera->setTranslationScale(0.02f);

// ===========================================================================
// setting up a forgiving data path
   vector<string> path;
   path.push_back("./models");
   path.push_back("../models");
   path.push_back("../../models");
   dmLoader::setDataPath(path);

   // Initialize simulation timing information.
   idt = 0.00500f;
   render_rate = 20;

// ===========================================================================
// Initialize DynaMechs environment - must occur before any linkage systems

   string foundName;
   if (!dmLoader::findFile("terrain_sm.dat", NULL, foundName))
   {
      cerr << "Error: file not found: terrain_sm.dat" << endl;
      exit(1);
   }

   CartesianVector gravity = {0.0, 0.0, (Float)-9.81};
   dmEnvironment *environment = new dmEnvironment();
   dmEnvironment::setEnvironment(environment);
   environment->setGravity(gravity);
   environment->loadTerrainData(foundName);
   environment->setGroundPlanarSpringConstant((Float)5500.);
   environment->setGroundNormalSpringConstant((Float)7500.);
   environment->setGroundPlanarDamperConstant((Float)50.0);
   environment->setGroundNormalDamperConstant((Float)50.0);
   environment->setFrictionCoeffs((Float)0.4, (Float)0.15);  // make it slick
   environment->drawInit();

// ===========================================================================
// build a simple DynaMechs system - a single rigid body
   G_robot = new dmArticulation;
   dmMobileBaseLink *ref = new dmMobileBaseLink;

   if (!dmLoader::findFile("obj_cube_center.xan", NULL, foundName))
   {
      cerr << "Error: file not found: obj_cube_center.xan" << endl;
      exit(1);
   }
   GLuint *dlist = new GLuint;
   *dlist = dmGLLoadFile_xan(foundName);
   ref->setUserData(dlist);

   CartesianTensor I_bar = {{(Float)0.7,   0.0,         0.0},
                            {0.0,          (Float)0.7,  0.0},
                            {0.0,          0.0,         (Float)0.7}};
   CartesianVector cg_pos = {0.,0.,0.};
   ref->setInertiaParameters(0.5, I_bar, cg_pos);

   CartesianVector contact_pos[8] = {{-1.0,  1.0, -1.0},
                                     { 1.0,  1.0, -1.0},
                                     {-1.0, -1.0, -1.0},
                                     { 1.0, -1.0, -1.0},
                                     {-1.0,  1.0,  1.0},
                                     { 1.0,  1.0,  1.0},
                                     {-1.0, -1.0,  1.0},
                                     { 1.0, -1.0,  1.0}};

   dmContactModel *contact_model = new dmContactModel;
   contact_model->setContactPoints(4, contact_pos);
   ref->addForce(contact_model);

   contact_model = new dmContactModel;
   contact_model->setContactPoints(4, &contact_pos[4]);
   ref->addForce(contact_model);

   Float q[7] = {0., 0., 0., 1.0,   // quat
                 17., 17., 15.};    // pos
   SpatialVector vel = {-10.0, 0., 0.0, 0., 0., 0.};
   ref->setState(q, vel);

   G_robot->addLink(ref, NULL);

   // Setup the integrator
   G_integrator = new dmIntegRK4();
   G_integrator->addSystem(G_robot);

// ===========================================================================

   //initControl(G_robot);

   glutReshapeFunc(myReshape);
   glutKeyboardFunc(processKeyboard);
   glutSpecialFunc(processSpecialKeys);
   glutDisplayFunc(display);
   glutIdleFunc(updateSim);

   dmGetSysTime(&last_tv);

   cout << endl;
   cout << "p - toggles dynamic simulation" << endl;
   cout << "Use mouse to rotate/move/zoom the camera" << endl << endl;

   glutMainLoop();
   return 0;             /* ANSI C requires main to return int. */
}
