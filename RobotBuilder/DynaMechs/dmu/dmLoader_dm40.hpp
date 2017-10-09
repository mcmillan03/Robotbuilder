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
 *     File: dmLoader_dm40.hpp
 *   Author: Scott McMillan
 *  Created: 12 August 2001
 *  Summary: loader for version 3.0 DynaMechs configuration files
 *****************************************************************************/

#ifndef _DM_LOADER_DM40
#define _DM_LOADER_DM40

#include <dmu.h>
#include <dmLoader_dm30.hpp>

class dmClosedArticulation;
class dmQuaternionLink;
class dmSecondaryJoint;
class dmSecondaryPrismaticJoint;
class dmSecondaryRevoluteJoint;
class dmSecondarySphericalJoint;

/**

Loader for V 4.0 configuration files.

Configuration file readers, {\tt dmLoader\_dm} and its subclasses, are being
supplied with the dmutils library that can be used to instantiate and intialize
all types of objects.

Comments begin with the hash (\#) character and continues to the end of the
line.  Blocks are delimited by braces (\{\}) and are preceded by a label
denoting the type of block.

The configuration files begin with a comment line specifying the format of its
contents.  This class supports files for version 4.0 and the comment appears
follows:
\begin{verbatim}
# DynaMechs V 4.0 ascii
\end{verbatim}

This format builds on the previous version (3.0). While supporting 3.0's
'Articulation' system type, this format also adds the following:
\begin{itemize}
\item A new ClosedArticulation that can be used in place of the 'Articulation'
block.  This block contains a TreeStructure block similar to the 'Articulation'
block and a 'SecondaryJoints' block that defines the loop closures.
\item A StaticRootLink class that aids in closing loops.
\item A QuaternionLink class that has the DOFs as a SphericalLinkClass without
the singularity around gimbal lock.
\end{itemize}

The top-level block is the system block which contains all of the links (rigid
bodies and transforms) for the multibody system it contains.  The label for
this block depends on the type of system it describes.  The dmLoader_dm30
(version 3.0) class describes the format for the 'Articulation' type
(describing an open-chain tree structure).  The following describes the format
for the new 'ClosedArticulation' system:
\begin{verbatim}
ClosedArticulation {
    Name                             "some_label"
    Graphics_Model                   "some_model_file"
    Position                         x   y   z
    Orientation_Quat                 a_x a_y a_z  s

    (TreeStructure block)
    (SecondaryJoints block)
}
\end{verbatim}
The Name is a label given to the dmClosedArticulation object.  A graphics model
can be associated with the base by specifying a valid file in the
Graphics\_Model field.  An empty field ("") corresponds to no model.  The
Position and Orientation\_Quat specifies the position and orientation of the
inertial coordinate system relative to which the system is simulated.

The 'TreeStructure' block is similar to the 'Articulation' block except the
toplevel Name, Graphics\_Model, Position, and Orientation\_Quat have been moved
outside this block (above).  Links are organized as before.  For example, a
simple serial chain of links can be organized as follows:
\begin{verbatim}
TreeStructure {
    (link 0)
    (link 1)
       :
       :
    (link n)
}
\end{verbatim}

A Branch after a link is used to connect two or more links to it:
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

A non-link with no translation or rotation is introduced in version 4.0
that will aid in loop closures at the start of the tree structur (it makes no
sense to use it elsewhere).  It is given as follows:
\begin{verbatim}
StaticRootLink {
    Name                             "some_label"
    Graphics_Model                   "model_filename"
}

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

Version 4.0, introduces a new link with the same three rotational DOFs as the
spherical link.  Using a quaternion this link does not suffer from the gimbal
lock problem that the spherical link does.  This link is specified as follows:
\begin{verbatim}
QuaternionLink {
    Name                             "some_label"
    Graphics_Model                   "model_filename"

    (rigid body parameters)

    Position_From_Inboard_Link       x y z
    Orientation_Quat                 a_x a_y a_z  s
    Initial_Angular_Velocity         w_x w_y w_z
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
    Motor_Gear_Ratio                 n
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

The second block inside of the 'ClosedArticulation' block will define any loop
closures.  It does so, by defining a set of secondary joints that connect two
links.  It is organized as follows:
\begin{verbatim}
SecondaryJoints {
    (secondary joint 1)
    (secondary joint 2)
        :
        :
    (secondary joint n)
}
\end{verbatim}

Six types of secondary joints are supported in this version -- revolute,
prismatic, and spherical -- each with hard or soft constraints.  Each has the
following basic form:
\begin{verbatim}
<TypeName> {
    Name                  "some_label"
    Stabilization         NONE|BAUMGARTE|SPRING_DAMPER   # Hard only

    Link_A_Name           "inboard link label"
    Link_B_Name           "outboard link label"

    Joint_A_Position      pA_x pA_y pA_z
    Rotation_Matrix_A     RA_11 RA_12 RA_13
                          RA_21 RA_22 RA_23
                          RA_31 RA_32 RA_33

    Joint_B_Position      pB_x pB_y pB_z
    Rotation_Matrix_B     RB_11 RB_12 RB_13
                          RB_21 RB_22 RB_23
                          RB_31 RB_32 RB_33

    Joint_Friction        u

    (Type specific parameters - see below)
}

The Stabilization parameter is specified as one of the given tokens (no
quotes) and is applicable to hard constrained secondary joints only.
To identify the two links on either side of the closure link name parameters
must be specified in the TreeStructure section (above) and then the two links
in question are identified by name in the Link\_A\_Name and Link\_B\_Name
parameters (using quotes).  The position and orientation of the secondary
joint relative to the two links are specified in the Joint\_?\_Position and
Rotation\_Matrix\_? parameters.  Joint\_Friction is the same parameter as that
used in the regular link types.

Specific parameters for the hard and soft, secondary, prismatic and revolute
joints types are listed as follows:
\begin{verbatim}
    Position_Constraint_Spring        K_p
    Position_Constraint_Damper        B_p

    Orientation_Constraint_Spring     K_r
    Orientation_Constraint_Damper     B_r
\end{verbatim}

Specific parameters for the hard and soft, secondary spherical joints are
listed as follows:
\begin{verbatim}
    Position_Constraint_Spring        K_p
    Position_Constraint_Damper        B_p
\end{verbatim}


 */

//----------------------------------------------------------------------------

class DMU_DLL_API dmLoader_dm40 : public dmLoader_dm30
{
public:
   /** Constructor. */
   dmLoader_dm40() : dmLoader_dm30() {}

   /** Destructor. */
   virtual ~dmLoader_dm40() {}

   /** Non-reentrant loader function (i.e. loads one model at a time)
    */
   virtual dmSystem *load(ifstream &cfg_ptr);

protected:
   void setRevDCMotorParameters(dmRevDCMotor *actuator,
                                          ifstream &cfg_ptr);

   void setQuaternionLinkParameters(dmQuaternionLink *link,
                                    ifstream &cfg_ptr);
   void setSecondaryJoint(ifstream &cfg_ptr, dmSecondaryJoint *joint,
                          dmClosedArticulation *articulation);
   void setStabilization(ifstream &cfg_ptr, dmSecondaryJoint *joint);
   void setSecondaryPrismaticJoint(ifstream &cfg_ptr,
                                   dmSecondaryPrismaticJoint *joint);
   void setSecondaryRevoluteJoint(ifstream &cfg_ptr,
                                  dmSecondaryRevoluteJoint *joint);
   void setSecondarySphericalJoint(ifstream &cfg_ptr,
                                   dmSecondarySphericalJoint *joint);
   void parseSecondaryJoints(ifstream &cfg_ptr,
                             dmClosedArticulation *articulation);

   virtual dmClosedArticulation* loadClosedArticulation(ifstream &cfg_ptr);

private:
   dmLoader_dm40(const dmLoader_dm40 &);              // not implemented
   dmLoader_dm40 & operator=(const dmLoader_dm40 &);  // not implemented

   void parseBranch(ifstream &cfg_ptr,
                    dmArticulation *articulation,
                    dmLink *parent);
};

#endif
