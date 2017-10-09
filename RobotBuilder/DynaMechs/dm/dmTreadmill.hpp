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
 *     File: dmTreadmill.hpp
 *   Author: Steven Rodenbaugh
 *  Created: 2000
 *  Summary: class definition for a dynamic environment with a treadmill
 *****************************************************************************/

#ifndef _DM_TREADMILL_HPP
#define _DM_TREADMILL_HPP

#include <dm.h>
#include <dmObject.hpp>
#include <dmEnvironment.hpp>

#include <vector>

//======================================================================

/**
   The treadmill is a dynamic environment requiring simulation to update its
   state.  It can be thought of as surface with a horizontal velocity
   component.  It has a length along the direction of motion, width
   perpendicular in the horizontal plane, and a normal (up) direction.

   It is derived from {\tt dmEnvironment}, and when hydrodynamics are enabled
   in the build, this class appends to the base class state vectors.
 
	To define the treadmill environment, call the member functions to define
	its properties.  {\tt setNormal} defines the normal to the treadmill surface
	in terms of the ICS.  {\tt setVelocityDirection} defines the direction of the
	positive velocity.  This vector must be orthonormal to the normal vector.
	The extents of the treadmill surface are defined with {\tt setWidth} and
	{\tt setLength}.  The treadmill coordinate system origin is located at the
	center of the treadmill.  The width is defined along the treadmill's Y and
	the length is along the X (velocity direction).  When any of theses functions
	are called, {\tt computeOrientation} is called to redefine the class's internal
	data structures that hold the the transform to the treadmill coordinate
	system and the extents of the treadmill.  The setup functions can not be 
	called after simulation has started (because only tracking one state variable).

	Use {\tt getState} and {\tt setState} to query and set the velocity of the
	treadmill.  Recall that {\tt synchronizeState} after changing the state.

   Several functions are used to internally manage the the movement of anchor
	points for the contact model for contact points in contact with the treadmill.
	{\tt trackPoint} adds an anchor point to the list, {\tt resetPoint} changes the
	position of the anchor point (used when the point is sliding),
	{\tt getPointLocation} returns the current position of the anchor point
	in terms of the ICS, and {\tt freePoint} stops the tracking of an anchor point
	(for when the point is no longer in contact with the surface).

Todo:
- Add a parser for the treadmill data file (now can only create
	a treadmill by function calls)

See also {\tt dmContactModel}, {\tt dmIntegrator} */

//======================================================================

class DM_DLL_API dmTreadmill : public dmEnvironment
{
public:
   ///
   dmTreadmill();
   ///
   virtual ~dmTreadmill();

   ///
   void setPosition(const CartesianVector position);
   ///
   void getPosition(CartesianVector pos) const;

   ///
   void setWidth (Float width);
   ///
   Float getWidth() const;

   ///
   void setLength (Float length);
   ///
   Float getLength() const;

   // dmSystem functions
   ///
   virtual unsigned int getNumDOFs() const
      {
         return dmEnvironment::getNumDOFs() + 1;
      }
   ///
   virtual void setState(Float treadmill_pos[], Float treadmill_vel[]);
   ///
   virtual void getState(Float treadmill_pos[], Float treadmill_vel[]) const;

   ///
   void setVelocityDirection(const CartesianVector v_dir);
   ///
   void getVelocityDirection(CartesianVector v_dir) const;

   ///
   void setNormalDirection(const CartesianVector normal);
   ///
   void getNormalDirection(CartesianVector normal) const;

   ///
   Float getGroundElevation(CartesianVector contact_pos,
                                   CartesianVector ground_normal,
											  bool* off_treadmill);

	///
	void resetPoint (int pointID, const CartesianVector new_point);

	///
	void freePoint (int pointID);

	///
	int trackPoint (CartesianVector pt);

	///
	void getPointLocation(int pointID, CartesianVector point);
	
   ///
   virtual void pushForceStates();
   ///
   virtual void popForceStates();
   
	// dynamics algorithm
   ///
   virtual void dynamics(Float *qy, Float *qdy);
   virtual void draw() const;

protected: // Functions
   void computeOrientation();


private: // Functions
   dmTreadmill(const dmTreadmill &);
   dmTreadmill &operator=(const dmTreadmill &);
	int findFreeIndexInPointList ();
	void savePointStates ();
	void restoreSavedPointStates ();


private: // Variables
   Float m_half_width;
   Float m_half_length;
   CartesianVector m_position;
   CartesianVector m_normal;    // normalized
   CartesianVector m_forward;   // normalized
   CartesianVector m_treadmill_y;      // normalized

   Float m_q, m_qd, m_qdd;

   CartesianVector m_tzi; // ICS z in terms of treadmill coords;
   HomogeneousTransformationMatrix m_iTt, m_tTi;
	Float m_ground_level; // ground level below the lowest point on the treadmill

	struct TreadmillPointInfoStruct
	{
		CartesianVector point;
		bool active;
		bool initially_off_treadmill;
		double initial_treadmill_state;
	};
   vector<TreadmillPointInfoStruct*> m_point_list;
   vector<TreadmillPointInfoStruct*> m_point_list_stored;


};

#endif
