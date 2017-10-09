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
 *     File: ring.cpp
 *   Author: Scott McMillan
 *  Created: 20 March 1997
 *  Summary: GLUT example
 *****************************************************************************/

#include <typeinfo>
#include <GL/glut.h>

#include <dmTime.h>
#include <dmGLMouse.hpp>
#include <dmGLPolarCamera_zup.hpp>

#include <dm.h>            // DynaMechs typedefs, globals, etc.
#include <dmSystem.hpp>      // DynaMechs simulation code.
#include <dmArticulation.hpp>
#include <dmForce.hpp>
#include <dmMobileBaseLink.hpp>
#include <dmLink.hpp>
#include <dmMDHLink.hpp>
#include <dmRevoluteLink.hpp>
#include <dmEnvironment.hpp>
#include <dmIntegRK4.hpp>

#include <dmu.h>
#include <dmLoader.hpp>

dmGLMouse *mouse;
char dummy[64];

dmGLPolarCamera_zup *camera;
char dummy2[64];

GLfloat view_mat[4][4];

Float idt;
Float sim_time=0.0;
Float rtime=0.0;
bool  paused_flag = true;

dmArticulation *G_robot;
char dummy3[64];
dmIntegRK4 *G_integrator;
char dummy4[64];

dmTimespec tv, last_tv;

int render_rate;
int render_count = 0;
int timer_count = 0;

//============================================================================

class dmPositionConstraint : public dmForce
{
public:
   dmPositionConstraint(dmArticulation *system, unsigned int ref_index);
   virtual ~dmPositionConstraint();

   // specific functions
   void setConstants(CartesianVector offset, Float K_spring, Float B_damper);

   // required functions
   void reset() {};
   void computeForce(const dmABForKinStruct &val, SpatialVector force);

// rendering functions (for future expansion/visualization):
   virtual void draw() const {};

private:
   dmArticulation *m_system;
   unsigned int    m_ref_index;

   CartesianVector m_offset;
   Float           m_K_spring, m_B_damper;
};

//----------------------------------------------------------------------------
dmPositionConstraint::dmPositionConstraint(dmArticulation *system,
                                           unsigned int ref_index) :
      m_system(system),
      m_ref_index(ref_index),
      m_K_spring(0.0),
      m_B_damper(0.0)
{
   m_offset[0] = m_offset[1] = m_offset[2] = 0.0;
}

//----------------------------------------------------------------------------
dmPositionConstraint::~dmPositionConstraint()
{
}

//----------------------------------------------------------------------------
void dmPositionConstraint::setConstants(CartesianVector offset,
                                        Float K_spring,
                                        Float B_damper)
{
   m_offset[0] = offset[0];
   m_offset[1] = offset[1];
   m_offset[2] = offset[2];

   m_K_spring = K_spring;
   m_B_damper = B_damper;
}

//----------------------------------------------------------------------------
void dmPositionConstraint::computeForce(const dmABForKinStruct &val,
                                        SpatialVector force)
{
   int i;

   // get ref member position info
   dmABForKinStruct ref_val;
   m_system->forwardKinematics(m_ref_index, ref_val);

   // compute delta position in ICS b/w ref mem origin and link+offset
   CartesianVector delta;
   for (i=0; i<3; i++)
   {
      delta[i] = ref_val.p_ICS[i] - val.p_ICS[i];
      for (int j=0; j<3; j++)
         delta[i] -= val.R_ICS[i][j]*m_offset[j];
   }

   // compute delta velocity in ICS b/w ref mem origin and link offset
   CartesianVector veref, vlink, velink, deltav;

   crossproduct(&val.v[0], m_offset, vlink);
   vlink[0] += val.v[3];
   vlink[1] += val.v[4];
   vlink[2] += val.v[5];

   for (i = 0; i < 3; i++)
   {
      velink[i] = val.R_ICS[i][0]*vlink[0] +
                  val.R_ICS[i][1]*vlink[1] +
                  val.R_ICS[i][2]*vlink[2];
      veref[i] = ref_val.R_ICS[i][0]*ref_val.v[3] +
                 ref_val.R_ICS[i][1]*ref_val.v[4] +
                 ref_val.R_ICS[i][2]*ref_val.v[5];
      deltav[i] = velink[i] - veref[i];
   }

   // compute spring force at origin of reference member
   CartesianVector ftemp;
   SpatialVector linear_force = {0.0,0.0,0.0, 0.0,0.0,0.0};
   for (i=0; i<3; i++)
   {
      ftemp[i] = delta[i]*m_K_spring - deltav[i]*m_B_damper;
                                        // force on link from ref mem.
   }

   // transform it to the ref mem CS
   for (i=0; i<3; i++)
   {
      for (int j=0; j<3; j++)
         linear_force[i+3] += ref_val.R_ICS[j][i]*(-ftemp[j]);
   }

   dmLink *link = m_system->getLink(m_ref_index);
   dmMobileBaseLink *rb = dynamic_cast<dmMobileBaseLink*>(link);
   if (rb)
   {
      rb->setExternalForce(linear_force);
   }

   // compute force and moment on this link at the offset position.
   for (i=0; i<3; i++)
      for (int j=0; j<3; j++)
         force[i+3] = val.R_ICS[j][i]*ftemp[j];

   crossproduct(m_offset, &force[3], &force[0]);
}

//============================================================================

//========================== control algorithm vars ==========================
unsigned int num_links = 0;
dmRevoluteLink **robot_link;
Float *desired_joint_pos;

//----------------------------------------------------------------------------
void initControl(dmArticulation *robot)
{
   unsigned int i,j;

   cerr << "initControl():" << endl;

   // count number of revolute links
   for (i = 0; i < robot->getNumLinks(); i++)
   {
      if (dynamic_cast<dmRevoluteLink*>(robot->getLink(i)))
      {
         num_links++;
      }
   }

   cerr << "Num revolute links: " << num_links << endl;

   robot_link = new dmRevoluteLink*[num_links];
   desired_joint_pos = new Float[num_links];

   j = 0;
   for (i = 0; i < robot->getNumLinks(); i++)
   {
      dmRevoluteLink *link;
      if ((link = dynamic_cast<dmRevoluteLink*>(robot->getLink(i))))
      {
         robot_link[j] = link;
         Float joint_vel;
         robot_link[j]->getState(&desired_joint_pos[j], &joint_vel);

         cerr << "  pos = " << desired_joint_pos[j] << endl;
         j++;
      }
   }

   // add a constraint force to the last link
   dmLink *ref = robot->getLink(0);
   dmRevoluteLink *link = robot_link[num_links-1];

   if (typeid(*ref) == typeid(dmMobileBaseLink))
   {
      dmPositionConstraint *constraint = new dmPositionConstraint(robot, 0);

      CartesianVector offset = {3.0, 0.0, 0.0};
      constraint->setConstants(offset, 150.0, 0.0);

      link->addForce(constraint);
      cout << "num forces " << link->getNumForces() << endl;
   }
}


//----------------------------------------------------------------------------
void computeControl(float /*time*/)
{
   Float joint_input;
   Float joint_pos;
   Float joint_vel;

   for (unsigned int i=0; i<num_links-1; i++)
   {
      robot_link[i]->getState(&joint_pos, &joint_vel);
      joint_input = 200.0*(desired_joint_pos[i] - joint_pos)
                            - 10.0*joint_vel;

      robot_link[i]->setJointInput(&joint_input);
   }
}


//----------------------------------------------------------------------------
void myinit (void)
{
   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//     light_position is NOT default value
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
void processSpecialKeys(int key, int, int)
{
   switch (key)
   {
      case GLUT_KEY_LEFT:
         break;
      case GLUT_KEY_RIGHT:
         break;
      case GLUT_KEY_UP:
         break;
      case GLUT_KEY_DOWN:
         break;
   }
}

//----------------------------------------------------------------------------
void updateSim()
{

   if (!paused_flag)
   {
      for (int i=0; i<render_rate; i++)
      {
         computeControl(sim_time);
         G_integrator->simulate(idt);
         sim_time += idt;
      }
   }

   camera->update(mouse);
   camera->applyView();

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
int main(int argc, char** argv)
{
   int i, j;

   glutInit(&argc, argv);

   //=========================
   char *filename = "ring.cfg";
   if (argc > 1)
   {
      filename = argv[1];
   }

   glutInitWindowSize(640, 480);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutCreateWindow("DynaMechs Example");

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
   path.push_back("./testdm");
   path.push_back("../testdm");
   path.push_back("../../testdm");
   path.push_back("./models");
   path.push_back("../models");
   path.push_back("../../models");
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
      cerr << "main error: invalid integration stepsize: " << idt << endl;;
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

   G_robot = dynamic_cast<dmArticulation*>(dmLoader::loadDMFile(robot_flname));

   G_integrator = new dmIntegRK4();
   G_integrator->addSystem(G_robot);

   initControl(G_robot);

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
