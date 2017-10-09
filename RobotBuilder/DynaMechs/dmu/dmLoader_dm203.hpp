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
 *     File: dmLoader_dm203.hpp
 *   Author: Scott McMillan
 *  Created: 12 August 2001
 *  Summary: loader for version 2.0.3 DynaMechs configuration files
 *****************************************************************************/

#ifndef _DM_LOADER_DM203
#define _DM_LOADER_DM203

#include <dm.h>
#include <GL/gl.h>

#include <dmu.h>
#include <dmLoader_dm.hpp>


/**

Loader for V 2.0.3 configuration files (deprecated).

Configuration file readers, {\tt dmLoader\_dm} and its subclasses, are being
supplied with the dmutils library that can be used to instantiate and intialize
all types of objects.

Comments begin with the hash (\#) character and continues to the end of the
line.  Blocks are delimited by braces (\{\}) and are preceded by a label
denoting the type of block.

The configuration files begin with a comment line specifying the format of its
contents.  This class, supporting files for version 2.0.3, is provided for
backward compatibility and the comment appears follows:
\begin{verbatim}
# DynaMechs V 2.0.3 ascii
\end{verbatim}

This configuration format begins with a specification of 3D models to
represent various objects indexed in later blocks.  This block appears as
follows (for example):
\begin{verbatim}
Graphics_Models {
    Number_Graphics_Models  2
    "models/obj_cube_center.xan"
    "models/obj_cylinder_x.xan"
}
\end{verbatim}

Next comes the System block which contains one reference member block and any
number of articulation blocks that are attached to the reference member:
\begin{verbatim}
System {
    (reference member info)

    (articulation 0 info)
         :
         :
    (articulation n info)
}
\end{verbatim}

Reference member blocks can be one of two types:

\begin{verbatim}
StaticRefMember {
    Graphics_Model_Index             i

    Position                         x   y   z
    Orientation_Quat                 a_x a_y a_z  s
}
\end{verbatim}

\begin{verbatim}
DynamicRefMember {
    Graphics_Model_Index             i

    (rigid body parameters)

    Position                         x   y   z
    Orientation_Quat                 a_x a_y a_z  s
    Velocity                         w_x w_y w_z  v_x v_y v_z
}
\end{verbatim}
where specifications for rigid body parameters can be found below and the {\tt
Velocity} parameters specify the initial spatial (angular and linear) velocity
with respect to the inertial coordinate system.

Articulation blocks are indicated by the following:
\begin{verbatim}
Articulation {
    (links and branches)
}
\end{verbatim}

A simple serial chain of links is the simplest form of an articulation and is
organized as follows:
\begin{verbatim}
Articulation {
    (link 0)
    (link 1)
       :
       :
    (link n)
}
\end{verbatim}

Chains can be branched to form more complex articulations.  A branch after link
1 is organized as follows:
\begin{verbatim}
Articulation {
    (link 0)
    (link 1)
    Branch {
        (link 2)
        (link 3)
    }
    (link 4)
       :
       :
    (links n)
}
\end{verbatim}
This has the following topology (note the first link of any branch is connected
to the reference member, r):
\begin{verbatim}
 r - 0 - 1 - 2 - 3
           \
             4 - ... - n
\end{verbatim}
Also note that branch can occur anywhere after the first link (a branch before
the first link is the same as a different articulation.  Branches can also be
nested.  This structure supports all tree topologies.

The library supports a number of "link" types that could correspond to a
constant transformation (with no dynamic properties), or a rigid body
connected to the previous link through a "joint" with some number of degrees
of freedom.  The possible link types supported in the various versions are
given below.  Tokens specific to a subset of the versions are given in the
comments following the pertinent lines.

A constant screw transformation about the z axis is given as follows
\begin{verbatim}
ZScrewTxLink {
    ZScrew_Parameters                d  theta
}
\end{verbatim}

A three DOF link (three orientation DOFs) is used to simulate a ball-in-socket
joint using Euler angles:
\begin{verbatim}
SphericalLink {
    Graphics_Model_Index             i

    (rigid body parameters)

    Position_From_Inboard_Link       x y z
    Initial_Joint_Angles             phi theta psi
    Initial_Angular_Velocity         w_x w_y w_z
    Axes_Limits                      phi theta psi
    Joint_Limit_Spring_Constant      K_limit
    Joint_Limit_Damper_Constant      B_limit
    Joint_Friction                   u
}
\end{verbatim}
where specifications for rigid body parameters can be found below.

A one DOF prismatic (translational) link is specified as follows:
\begin{verbatim}
PrismaticLink {
    Graphics_Model_Index             i

    (rigid body parameters)

    MDH_Parameters                   a  alpha  d  theta
    Initial_Joint_Velocity           qd
    Joint_Limits                     q_min q_max
    Joint_Limit_Spring_Constant      K_limit
    Joint_Limit_Damper_Constant      B_limit

    Joint_Friction                   u
}
\end{verbatim}

A one DOF rotational link is specified two different ways (with and without
motor model).  The version without a motor is specified as follows:
\begin{verbatim}
RevoluteLink {
    Graphics_Model_Index             i

    (rigid body parameters)

    MDH_Parameters                   a  alpha  d  theta
    Initial_Joint_Velocity           qd
    Joint_Limits                     q_min q_max
    Joint_Limit_Spring_Constant      K_limit
    Joint_Limit_Damper_Constant      B_limit

    Actuator_Type                    0
    Joint_Friction                   u
}
\end{verbatim}
The version with a motor is specified as follows:
\begin{verbatim}
RevoluteLink {
    Graphics_Model_Index             i

    (rigid body parameters)

    MDH_Parameters                   a  alpha  d  theta
    Initial_Joint_Velocity           qd
    Joint_Limits                     q_min q_max
    Joint_Limit_Spring_Constant      K_limit
    Joint_Limit_Damper_Constant      B_limit

    Actuator_Type                    1

    Motor_Torque_Constant            K_t
    Motor_BackEMF_Constant           K_b
    Motor_Armature_Resistance        R_a
    Motor_Inertia                    J_m
    Motor_Coulomb_Friction_Constant  u_c
    Motor_Viscous_Friction_Constant  u_v
    Motor_Max_Brush_Drop             V_max
    Motor_Half_Drop_Value            V_half
}
\end{verbatim}

The following is the order of the rigid body parameters:
\begin{verbatim}
    Mass                             m
    Inertia                          i_11 i_12 i_13  # 3x3 matrix - 9 floats
                                     i_21 i_22 i_23
                                     i_31 i_32 i_33
    Center_of_Gravity                cg_x cg_y cg_z

    (contact model parameters)
\end{verbatim}
In the case of hydrodynamic simulation, additional parameters are also
required resulting the following alternate form:
\begin{verbatim}
    Mass                             m
    Inertia                          i_11 i_12 i_13  # 3x3 matrix - 9 floats
                                     i_21 i_22 i_23
                                     i_31 i_32 i_33
    Center_of_Gravity                cg_x cg_y cg_z

    Volume                           V
    Added_Mass                       # 6x6 matrix - 36 floats
                                     i_11 i_12 i_13 i_14 i_15 i_16
                                     i_21 i_22 i_23 i_24 i_25 i_26
                                     i_31 i_32 i_33 i_34 i_35 i_36
                                     i_41 i_42 i_43 i_44 i_45 i_46
                                     i_51 i_52 i_53 i_54 i_55 i_56
                                     i_61 i_62 i_63 i_64 i_65 i_66
    Center_of_Bouyancy               cb_x cb_y cb_z
    Drag_Axis                        i                # (0=x, 1=y, 2=z)
    Cylinder_Bounds                  x0 xf
    Cylinder_Radius                  r
    Drag_Coefficient                 C_d

    (contact model parameters)
\end{verbatim}

The contact model parameters consist of the following:
\begin{verbatim}
    Number_of_Contact_Points   n
    Contact_Locations          x_1 y_1 z_1
                                    :
                               x_n y_n z_n
\end{verbatim}
Note that the {\tt Contact\_Locations} values are not needed if the {\tt
Number\_of\_Contact\_Points} is zero.

 */

//----------------------------------------------------------------------------

class DMU_DLL_API dmLoader_dm203 : public dmLoader_dm
{
public:
   /** Constructor. */
   dmLoader_dm203();

   /** Destructor. */
   virtual ~dmLoader_dm203() {}

   /** Non-reentrant loader function (i.e. loads one model at a time)
    */
   virtual dmSystem *load(ifstream &cfg_ptr);

protected:
   // allocates memory (using new) and returns a pointer to it
   GLuint *getGraphicsModelIndex(ifstream &cfg_ptr);
   void    loadModels(ifstream &cfg_ptr);

   void setStaticRefMemParameters(dmSystem *robot, ifstream &cfg_ptr);

private:
   dmLoader_dm203(const dmLoader_dm203 &);              // not implemented
   dmLoader_dm203 & operator=(const dmLoader_dm203 &);  // not implemented

   dmSystem *loadSystem(ifstream &cfg_ptr);
   void parseBranch(ifstream &cfg_ptr,
                    dmArticulation *articulation, dmLink *parent);

protected:
   vector<GLuint> m_solid_models;
};

#endif
