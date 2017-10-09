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
 *     File: dmLoader_dm30.hpp
 *   Author: Scott McMillan
 *  Created: 30 July 2001
 *  Summary: loader for version 3.0 DynaMechs configuration files
 *****************************************************************************/

#ifndef _DM_LOADER_DM30
#define _DM_LOADER_DM30

#include <dmu.h>
#include <dmLoader_dm.hpp>

class dmSystem;
class dmArticulation;
class dmLink;
class dmMobileBaseLink;
class dmSphericalLink;
class dmRevoluteLink;
class dmRevDCMotor;
class dmMDHLink;
class dmRigidBody;

/**

Loader for V 3.0 configuration files.

Configuration file readers, {\tt dmLoader\_dm} and its subclasses, are being
supplied with the dmutils library that can be used to instantiate and intialize
all types of objects.

Comments begin with the hash (\#) character and continues to the end of the
line.  Blocks are delimited by braces (\{\}) and are preceded by a label
denoting the type of block.

The configuration files begin with a comment line specifying the format of its
contents.  This class, supporting files for version 3.0, is provided for
backward compatibility and the comment appears follows:
\begin{verbatim}
# DynaMechs V 3.0 ascii
\end{verbatim}

This format differs from the previous version (2.1) in a number of significant
ways:
\begin{itemize}
\item The Articulation class has been merged with the System class
(i.e., a system consists of only one articulation)
\item Reference members are no longer used in 3.0.  A static reference member
specification (basically a constant position and orientation) has been moved to
the specification of the System/Articulation.  A dynamic reference member is
now specified as a MobileBaseLink as the first link in the System.
\item The initial list of graphics models has been eliminated and instead of
Graphics\_Model\_Indices within the specifications of the links, the filename
is provided in the Graphics\_Model field.
\end{itemize}

The top-level block is the system block which contains all of the links (rigid
bodies and transforms) for the multibody system it contains.  The label for
this block depends on the type of system it describes.  Currently only the
'Articulation' type (describing a tree structure) is supported and is specified
as follows:
\begin{verbatim}
Articulation {
    Name                             "some_label"
    Graphics_Model                   "some_model_file"
    Position                         x   y   z
    Orientation_Quat                 a_x a_y a_z  s

    (link and branches)
}
\end{verbatim}
The Name is a label given to the dmArticulation object.  A graphics model can
be associated with the base by specifying a valid file in the Graphics\_Model
field.  An empty field ("") corresponds to no model.  The Position and
Orientation\_Quat specifies the position and orientation of the inertial
coordinate system relative to which the system is simulated.

The Articulation block contains any combination of branches an links to
describe any tree structure.  Some examples of these are given as follows.

A simple serial chain of links can be organized as follows:
\begin{verbatim}
Articulation {
    Name                             "some_label"
    Graphics_Model                   "some_model_file"
    Position                         x   y   z
    Orientation_Quat                 a_x a_y a_z  s

    (link 0)
    (link 1)
       :
       :
    (link n)
}
\end{verbatim}

A Branch can occur anywhere (even before any links).  Branches
that occur at the beginning can be used to describe multiple independent
systems as follows:
\begin{verbatim}
Articulation {
    Name                             "some_label"
    Graphics_Model                   "some_model_file"
    Position                         x   y   z
    Orientation_Quat                 a_x a_y a_z  s

    Branch {
        (link 0)
        (link 1)
    }
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
which has the following topology:
\begin{verbatim}
  r - 0 - 1
  r - 2 - 3
  r - 4 - ... - n
\end{verbatim}
Note the first link of any branch is connected to the inertial coordinate
system, r) consisting of three distinct serial chains.  It is recommended that
you load separate configuration files, creating separate dmSystems, and
assigning multiple systems to a single dmIntegrator class.

A Branch after a link is used to connect two or more links to the same one:
\begin{verbatim}
Articulation {
    Name                             "some_label"
    Graphics_Model                   "some_model_file"
    Position                         x   y   z
    Orientation_Quat                 a_x a_y a_z  s

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
which has the following topology:
\begin{verbatim}
  r - 0 - 1 - 2 - 3
           \
             4 - ... - n
\end{verbatim}
Branches can also be nested resulting in the ability of specifying all tree
topologies.

The library supports a number of "link" types that could correspond to a
constant transformation (with no dynamic properties), or a rigid body
connected to the previous link through a "joint" with some number of degrees
of freedom.  The possible link types supported in the various versions are
given below.  Tokens specific to a subset of the versions are given in the
comments following the pertinent lines.

A constant screw transformation about the z axis is given as follows
\begin{verbatim}
ZScrewTxLink {
    Name                             "some_label"
    ZScrew_Parameters                d  theta
}
\end{verbatim}

A full six DOF "link" has been introduced in this Version 3.0 which takes the
place of the DynamicRefMember (the separate reference member specification has
been deprecated).  Use of this link only makes sense as the first link in a
particular tree where its state is specified with respect to the inertial
coordinate system, but placing it anywhere else in the configuration
will (as of version 4.0) properly simulate relative to its inboard link:
\begin{verbatim}
MobilBaseLink {
    Name                             "some_label"
    Graphics_Model                   "model_filename"

    (rigid body parameters)

    Position                         x   y   z
    Orientation_Quat                 a_x a_y a_z  s
    Velocity                         w_x w_y w_z  v_x v_y v_z
}
\end{verbatim}
where specifications for rigid body parameters can be found below and the {\tt
Velocity} parameters specify the initial spatial (angular and linear) velocity
with respect to the inboard link's coordinate system.

A three DOF link (three orientation DOFs) is used to simulate a ball-in-socket
joint using Euler angles:
\begin{verbatim}
SphericalLink {
    Name                             "some_label"
    Graphics_Model                   "model_filename"

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

A one DOF translational link is specified as follows:
\begin{verbatim}
PrismaticLink {
    Name                             "some_label"
    Graphics_Model                   "model_filename"

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
    Name                             "some_label"
    Graphics_Model                   "model_filename"

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
    Name                             "some_label"
    Graphics_Model                   "model_filename"

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
    Drag_Axis                        i               # (0=x, 1=y, 2=z)
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

class DMU_DLL_API dmLoader_dm30 : public dmLoader_dm
{
public:
   /** Constructor. */
   dmLoader_dm30() : dmLoader_dm() {}

   /** Destructor. */
   virtual ~dmLoader_dm30() {}

   /** Non-reentrant loader function (i.e. loads one model at a time)
    */
   virtual dmSystem *load(ifstream &cfg_ptr);

protected:
   void getGraphicsModel(ifstream &cfg_ptr, dmLink *link);
   dmArticulation* loadArticulation(ifstream &cfg_ptr);

private:
   dmLoader_dm30(const dmLoader_dm30 &);              // not implemented
   dmLoader_dm30 & operator=(const dmLoader_dm30 &);  // not implemented

   void parseBranch(ifstream &cfg_ptr,
                    dmArticulation *articulation,
                    dmLink *parent);
};

#endif
