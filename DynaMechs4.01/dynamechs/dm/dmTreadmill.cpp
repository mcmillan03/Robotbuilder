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
 *     File: dmTreadmill.cpp
 *   Author: Steven J. Rodenbaugh
 *  Created: 1999
 *  Summary: Class implementation of dmConveyor, a type of dmEnvironment
 *****************************************************************************/

#include <dm.h>
#include <dmEnvironment.hpp>
#include <dmTreadmill.hpp>

//============================================================================
// class dmEnvironment : public dmObject
//============================================================================

//----------------------------------------------------------------------------
//    Summary: Constructor for dmEnvironment class loads in all sorts of stuff
// Parameters: cfg_ptr - ifstream containing the necessary parameters to
//                initialize this class
//    Returns: none
//----------------------------------------------------------------------------
dmTreadmill::dmTreadmill()
      : dmEnvironment(),
        m_half_width(1),
        m_half_length(1),
        m_q(0),
        m_qd(0),
        m_qdd(0)
        //m_conveyor_filename(NULL)
{
   // Initialize member variables
   for (unsigned int i=0; i<3; i++)
   {
      m_position[i] = 0;
      m_normal[i]   = 0;
      m_forward[i]  = 0;
      m_treadmill_y[i]     = 0;
   }

   m_forward[0] = 1;
   m_treadmill_y[1] = 1;
   m_normal[2] = 1;


	const int initial_contact_point = 20; // this is just an estimate to allocate
		// the structs before the simulation.  If more contact points are in
		// contact as the same time, the structs will automatically grow.
	// Create several points initially, so don't have to while simulating
	while (m_point_list.size () < initial_contact_point)
	{
		TreadmillPointInfoStruct* point_info = new TreadmillPointInfoStruct;
		point_info->active = false;
		m_point_list.push_back (point_info);
	}
	while (m_point_list_stored.size () < initial_contact_point)
	{
		TreadmillPointInfoStruct* point_info = new TreadmillPointInfoStruct;
		point_info->active = false;
		m_point_list_stored.push_back (point_info);
	}

}

//----------------------------------------------------------------------------
dmTreadmill::~dmTreadmill()
{
	// Free the point lists
	TreadmillPointInfoStruct* point_info;
	while (m_point_list.size ())
	{
		point_info = m_point_list.back ();
		m_point_list.pop_back ();
		delete point_info;
	}
	while (m_point_list_stored.size ())
	{
		point_info = m_point_list_stored.back ();
		m_point_list_stored.pop_back ();
		delete point_info;
	}
}


//----------------------------------------------------------------------------
void dmTreadmill::computeOrientation()
{
   // Find y direction of treamdill (note m_normal and m_forward should be
	// orthonormal)
   crossproduct (m_normal, m_forward, m_treadmill_y);  // (z_dir, x_dir, y_dir);

   // Build the transform from treadmill to ICS in conveyor
   // Build the transform from ICS to treadmill
   // Build the Rotation matrix from ICS to treadmill Transposed (ie so
   //    treadmill to ICS)
   RotationMatrix tRi;
   m_iTt[0][0] = m_tTi[0][0] = tRi[0][0] = m_forward[0];
   m_iTt[1][0] = m_tTi[0][1] = tRi[0][1] = m_forward[1];
   m_iTt[2][0] = m_tTi[0][2] = tRi[0][2] = m_forward[2];
   m_iTt[0][1] = m_tTi[1][0] = tRi[1][0] = m_treadmill_y[0];
   m_iTt[1][1] = m_tTi[1][1] = tRi[1][1] = m_treadmill_y[1];
   m_iTt[2][1] = m_tTi[1][2] = tRi[1][2] = m_treadmill_y[2];
   m_iTt[0][2] = m_tTi[2][0] = tRi[2][0] = m_normal[0];
   m_iTt[1][2] = m_tTi[2][1] = tRi[2][1] = m_normal[1];
   m_iTt[2][2] = m_tTi[2][2] = tRi[2][2] = m_normal[2];

   CartesianVector tPi_org; // vector from treadmill to ICS in treadmill
   rotateCartesianVector (tRi,m_position,tPi_org);
   // Finish building the cTi (need to negatate since m_position should have been negated)
   m_tTi[0][3] = -tPi_org[0];
   m_tTi[1][3] = -tPi_org[1];
   m_tTi[2][3] = -tPi_org[2];
   m_tTi[3][0] = m_tTi[3][1] = m_tTi[3][2] = 0;
   m_tTi[3][3] = 1;
   // Finish building the iTc
   m_iTt[0][3] = m_position[0];
   m_iTt[1][3] = m_position[1];
   m_iTt[2][3] = m_position[2];
   m_iTt[3][0] = m_iTt[3][1] = m_iTt[3][2] = 0;
   m_iTt[3][3] = 1;
   // Save the ICS z direction in treadmill
   // todo: maybe more efficient to get from m_eTc
   const CartesianVector izi = {0, 0, 1}; // ICS z in terms of ICS
		// ?? Should this be in relative of the system gravity vector, rather than ICS ??
   rotateCartesianVector (tRi, izi, m_tzi); // ICS z in terms of treadmill

	// Find the extents of the treadmill top belt surface
	// each vector is a the quadrant corner in terms of the treadmill CS
	CartesianVector tpc1 = {m_half_length, m_half_width, 0};
	CartesianVector tpc2 = {-m_half_length, m_half_width, 0};
	CartesianVector tpc3 = {-m_half_length, -m_half_width, 0};
	CartesianVector tpc4 = {m_half_length, -m_half_width, 0};

	CartesianVector ipc1, ipc2, ipc3, ipc4;
	transformCartesianVector (m_iTt, tpc1, ipc1);
	transformCartesianVector (m_iTt, tpc2, ipc2);
	transformCartesianVector (m_iTt, tpc3, ipc3);
	transformCartesianVector (m_iTt, tpc4, ipc4);

	// Find the lowest point in ICS
	m_ground_level = ipc1[2];
	if (ipc2[2] < m_ground_level)
		m_ground_level = ipc2[2];
	if (ipc3[2] < m_ground_level)
		m_ground_level = ipc3[2];
	if (ipc4[2] < m_ground_level)
		m_ground_level = ipc4[2];

	// Drop the ground level by a little bit proportional to the average of the length
	// and width
	m_ground_level -= (m_half_width + m_half_length);
}


//----------------------------------------------------------------------------
void dmTreadmill::getPosition(CartesianVector position) const
{
   position[0] = m_position[0];
   position[1] = m_position[1];
   position[2] = m_position[2];
}

//----------------------------------------------------------------------------
void dmTreadmill::setPosition(const CartesianVector position)
{
   m_position[0] = position[0];
   m_position[1] = position[1];
   m_position[2] = position[2];

	computeOrientation ();
}


//----------------------------------------------------------------------------
void dmTreadmill::getNormalDirection(CartesianVector normal) const
{
   normal[0] = m_normal[0];
   normal[1] = m_normal[1];
   normal[2] = m_normal[2];
}

//----------------------------------------------------------------------------
void dmTreadmill::setNormalDirection(const CartesianVector normal)
{
   m_normal[0] = normal[0];
   m_normal[1] = normal[1];
   m_normal[2] = normal[2];

   if (normalize(m_normal) == (Float)0)
   {
      m_normal[2] = 1;
   }
   computeOrientation();
}


//----------------------------------------------------------------------------
void dmTreadmill::getVelocityDirection(CartesianVector v_dir) const
{
   v_dir[0] = m_forward[0];
   v_dir[1] = m_forward[1];
   v_dir[2] = m_forward[2];
}

//----------------------------------------------------------------------------
void dmTreadmill::setVelocityDirection(const CartesianVector v_dir)
{
   m_forward[0] = v_dir[0];
   m_forward[1] = v_dir[1];
   m_forward[2] = v_dir[2];

   if (normalize(m_forward) == (Float)0)
   {
      m_forward[0] = 1;
   }
   computeOrientation();
}

//----------------------------------------------------------------------------
void dmTreadmill::setWidth(Float width)
{
   m_half_width = width*0.5;

	// New treadmill extents so need to reevaluate
	computeOrientation();
}

//----------------------------------------------------------------------------
Float dmTreadmill::getWidth() const
{
   return m_half_width*2;
}

//----------------------------------------------------------------------------
void dmTreadmill::setLength(Float length)
{
   m_half_length = length*0.5;

	// New treadmill extents so need to reevaluate
	computeOrientation();
}

//----------------------------------------------------------------------------
Float dmTreadmill::getLength() const
{
   return m_half_length*2;
}

//----------------------------------------------------------------------------
void dmTreadmill::setState(Float q[], Float qd[])
{
   unsigned int offset = dmEnvironment::getNumDOFs();
   m_q  =  q[offset];  // treadmill pos
   m_qd = qd[offset];  // treadmill vel

   if (offset)
      dmEnvironment::setState(q, qd);
}

//----------------------------------------------------------------------------
void dmTreadmill::getState(Float q[], Float qd[]) const
{
   unsigned int offset = dmEnvironment::getNumDOFs();
   q[offset]  = m_q;   // treadmill pos
   qd[offset] = m_qd;  // treadmill vel

   if (offset)
      dmEnvironment::getState(q, qd);
}

//----------------------------------------------------------------------------
void dmTreadmill::dynamics(Float *qy, Float *qdy)
{
   unsigned int offset = dmEnvironment::getNumDOFs();
   m_q = qy[offset];
   qdy[offset] = m_qd = qy[getNumDOFs() + offset];
   qdy[getNumDOFs() + offset] = m_qdd;

   if (offset)
      dmEnvironment::dynamics(qy, qdy);
}

// ---------------------------------------------------------------------
// Function : getGroundElevation
// Purpose  : Compute ground location and normal from gridded elevation data.
// Inputs   : Current contact position wrt ICS
// Outputs  : Ground elevation along ICS z-axis, and normal at this point.
// ---------------------------------------------------------------------
Float dmTreadmill::getGroundElevation(CartesianVector contact_pos,
                                      CartesianVector ground_normal,
												  bool *off_treadmill)
{
	// Put the point in treadmill coordinates.
	CartesianVector contact_pos_in_treadmill;
	transformCartesianVector (m_tTi, contact_pos, contact_pos_in_treadmill);
	
	// Find the point on treadmill
	// Drop to treadmill, then scale the x and y by the same amount in the drop
	// with ratio given by the ICS z in treadmill coords
	const Float ratio = contact_pos_in_treadmill[2] / m_tzi[2];
	// Now adjust to drop on treadmill
	CartesianVector contact_on_treadmill_in_treadmill;
	contact_on_treadmill_in_treadmill[2] = 0; // on the treadmill
	contact_on_treadmill_in_treadmill[0] = contact_pos_in_treadmill[0] - ratio*m_tzi[0];
	contact_on_treadmill_in_treadmill[1] = contact_pos_in_treadmill[1] - ratio*m_tzi[1];

	// Now check if it is in bounds
	bool out_of_range = false;
	// Check x bounds
	if (contact_on_treadmill_in_treadmill[0] < -m_half_length || contact_on_treadmill_in_treadmill[0] > m_half_length)
		out_of_range = true;
	// Check y bounds
	if (contact_on_treadmill_in_treadmill[1] < -m_half_width || contact_on_treadmill_in_treadmill[1] > m_half_width)
		out_of_range = true;

	// Transform the point back to ICS
	CartesianVector contact_pos_on_treadmill_in_ics;
	transformCartesianVector (m_iTt, contact_on_treadmill_in_treadmill, contact_pos_on_treadmill_in_ics);
	// Now the z componenent will be the elevation
	
	// Set the normal for the return
	ground_normal[0] = m_normal[0];
	ground_normal[1] = m_normal[1];
	ground_normal[2] = m_normal[2];

	// If the point is off the treadmill, return a point much lower than the conveyor
	if (out_of_range)
	{
		// Reset the normal to ICS z
		ground_normal[0] = 0;
		ground_normal[1] = 0;
		ground_normal[2] = 1;
		*off_treadmill = true;
		return m_ground_level;
	}
	else
	{
		*off_treadmill = false;
		return contact_pos_on_treadmill_in_ics[2];
	}
}

// ---------------------------------------------------------------------
int dmTreadmill::trackPoint(CartesianVector pt)
{
	int index; // Index to place the new point

	index = findFreeIndexInPointList ();

	// Check if there is space available in the current list.  If not
	// allocate additional space
	if (index == -1)
	{
		// Allocate the space
		TreadmillPointInfoStruct* point_info = new TreadmillPointInfoStruct;
		// todo: check if allocation was successful

		// Set the data in the struct
		point_info->point[0] = pt[0];
		point_info->point[1] = pt[1];
		point_info->point[2] = pt[2];
		point_info->active = true;
		Float q, qd;
		getState (&q, &qd);
		point_info->initial_treadmill_state = q;

		// Add the new point to the list
		m_point_list.push_back(point_info);

		// Save the index for returning as the id
		index = m_point_list.size () - 1;
	}
	else
	{
		// Else space already allocated, so set the data
		m_point_list[index]->point[0] = pt[0];
		m_point_list[index]->point[1] = pt[1];
		m_point_list[index]->point[2] = pt[2];
		m_point_list[index]->active = true;
		Float q, qd;
		getState (&q, &qd);
		m_point_list[index]->initial_treadmill_state = q;
	}


	// Verify the point is initially on the treadmill.
	CartesianVector ground_normal;
	bool off_treadmill;
	getGroundElevation (pt, ground_normal, &off_treadmill);
	if (off_treadmill)
	{
		m_point_list[index]->initially_off_treadmill = true;
	}
	else
	{
		m_point_list[index]->initially_off_treadmill = false;
	}

	// Return the index

	return index;
}

// ---------------------------------------------------------------------
void dmTreadmill::freePoint(int pointID)
{
	// First check that the id is valid
	if (pointID < 0 || pointID >= m_point_list.size ())
	{
		cerr << "Invalid index in dmConveyor::freePoint\n";
		// Maybe I should exit here??
		exit (3);
	}
	else
	{
		// Set the point as inactive
		m_point_list[pointID]->active = false;
	}
}

// ---------------------------------------------------------------------
void dmTreadmill::savePointStates()
{
	// Rather than allocate and deallocate space all of the time,
	// just modify the saved list as needed.

	// First check if the stored list is large than the current list and
	// adjust as needed. (Though in the current implementenation this state is not 
	// anticipated to occur)
	while (m_point_list_stored.size ()  > m_point_list.size())
	{
		TreadmillPointInfoStruct* point_info = m_point_list_stored.back ();
		m_point_list_stored.pop_back ();
		delete point_info;
	}

	// Allocate more space to the saved list if needed
	while (m_point_list_stored.size () < m_point_list.size ())
	{
		TreadmillPointInfoStruct* point_info = new TreadmillPointInfoStruct;
		m_point_list_stored.push_back (point_info);
	}

	// Save the data in the current point list to the saved point list
	int n; // counter for 'for' loop
	for (n = 0; n < m_point_list.size (); n++)
	{
		m_point_list_stored[n]->point[0] = m_point_list[n]->point[0];
		m_point_list_stored[n]->point[1] = m_point_list[n]->point[1];
		m_point_list_stored[n]->point[2] = m_point_list[n]->point[2];
		m_point_list_stored[n]->active = m_point_list[n]->active;
		m_point_list_stored[n]->initially_off_treadmill = m_point_list[n]->initially_off_treadmill;
		m_point_list_stored[n]->initial_treadmill_state = m_point_list[n]->initial_treadmill_state;

	}
}

// ---------------------------------------------------------------------
int dmTreadmill::findFreeIndexInPointList()
{
	int n; // counter for 'for' loop
	int size; // size of point list

	size = m_point_list.size ();
	for (n = 0; n < size; n++)
	{
		// Check if not active and if so, return the index
		if (!m_point_list[n]->active)
			return n;
	}

	// If got this far, the code went through the whole list and found all
	// were active.  Return -1 to indicate none available
	return -1;
}

// ---------------------------------------------------------------------
void dmTreadmill::getPointLocation(int pointID, CartesianVector point)
{
	// Check that pointID is valid
	if (pointID < 0 || pointID > m_point_list.size ())
	{
		cerr << "Invalid pointID in dmConveyor::getPointLocation.\n";
		exit (3);
	}

	// Check the pointID is active
	if (!m_point_list[pointID]->active)
	{
		cerr << "Point not active in dmConveyor::getPointLocation.\n";
		exit (3);
	}
		
	// If initially off the treadmill, the anchor point is still in its
	// initial spot
	if (m_point_list[pointID]->initially_off_treadmill)
	{
		point[0] = m_point_list[pointID]->point[0];
		point[1] = m_point_list[pointID]->point[1];
		point[2] = m_point_list[pointID]->point[2];
	}
	else
	{
		// Calcuate where the point as moved

		// First get current state of treadmill
		Float q, qd;
		getState (&q, &qd);

		// Find the state difference
		Float state_difference = q - m_point_list[pointID]->initial_treadmill_state;

		// Scale the velocity vector by the state difference and sum with the current
		// anchor point
		point[0] = m_point_list[pointID]->point[0] + state_difference * m_forward[0];
		point[1] = m_point_list[pointID]->point[1] + state_difference * m_forward[1];
		point[2] = m_point_list[pointID]->point[2] + state_difference * m_forward[2];
	}
}

// ---------------------------------------------------------------------
void dmTreadmill::restoreSavedPointStates()
{
	// See notes for savePointStates
	while (m_point_list.size ()  > m_point_list_stored.size())
	{
		TreadmillPointInfoStruct* point_info = m_point_list.back ();
		m_point_list.pop_back ();
		delete point_info;
	}

	// Allocate more space to the saved list if needed
	while (m_point_list.size () < m_point_list_stored.size ())
	{
		TreadmillPointInfoStruct* point_info = new TreadmillPointInfoStruct;
		m_point_list.push_back (point_info);
	}

	// Save the data in the current point list to the saved point list
	int n; // counter for 'for' loop
	for (n = 0; n < m_point_list.size (); n++)
	{
		m_point_list[n]->point[0] = m_point_list_stored[n]->point[0];
		m_point_list[n]->point[1] = m_point_list_stored[n]->point[1];
		m_point_list[n]->point[2] = m_point_list_stored[n]->point[2];
		m_point_list[n]->active = m_point_list_stored[n]->active;
		m_point_list[n]->initially_off_treadmill = m_point_list_stored[n]->initially_off_treadmill;
		m_point_list[n]->initial_treadmill_state = m_point_list_stored[n]->initial_treadmill_state;
	}
}

// ---------------------------------------------------------------------
void dmTreadmill::resetPoint(int pointID, const CartesianVector new_point)
{
	// Check that pointID is valid
	if (pointID < 0 || pointID > m_point_list.size ())
	{
		cerr << "Invalid pointID in dmTreadmill::resetPoint.\n";
		exit (3);
	}

	// Else space already allocated, so set the data
	m_point_list[pointID]->point[0] = new_point[0];
	m_point_list[pointID]->point[1] = new_point[1];
	m_point_list[pointID]->point[2] = new_point[2];
	m_point_list[pointID]->active = true;

	// reset the treadmill state to the current state
	Float q, qd;
	getState (&q, &qd);
	m_point_list[pointID]->initial_treadmill_state = q;

	// This code models the treadmill, such that the anchor can not slide
	// off it.  Consequently, the state of initially_off_treadmill remains the
	// same.  Once the contact slides off, the contact state will be broken
	// in the contact algorithm, and the anchor point reset.
}

// ---------------------------------------------------------------------
void dmTreadmill::pushForceStates()
{
	savePointStates ();	
}

// The push and pop names may be misleading since they only interface a
// buffer of one element (fixed)
// ---------------------------------------------------------------------
void dmTreadmill::popForceStates()
{
	restoreSavedPointStates ();
}
