// dmvArticulationData.cpp: implementation of the CdmvArticulationData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvArticulationData.h"
#include "dmvRevoluteLinkData.h"
#include "dmvMobileBaseLinkData.h"
#include "dmvPrismaticLinkData.h"
#include "dmvStaticRootLinkData.h"
#include "dmvZScrewTxLinkData.h"
#include "dmvSphericalLinkData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// In RB, we decided to make the change between closed and open articulations transparent to
// the user.  All of the data for both types will be stored in this class, and the type
// will be determined by seeing if there are any secondary joints allocated.


CdmvArticulationData::CdmvArticulationData()
{
	// initialize members to known values
	int nCounter; // counter for 'for' loop

	for (nCounter = 0; nCounter < sizeof (m_qOrientation) / sizeof (m_qOrientation[0]); nCounter++)
		m_qOrientation[nCounter] = 0;

	for (nCounter = 0; nCounter < sizeof (m_cvPosition) / sizeof (m_cvPosition[0]); nCounter++)
		m_cvPosition[nCounter] = 0;
	
	// note MFC will construct m_arrayLinks as empty already

	// Specify the object type
	m_ObjectType = ARTICULATION;
	// Specify the object type
	m_ArticulationType = OPEN_ARTICULATION;

	// Set the default name
	m_strName = "Articulation";

	// Initialize showing axes
	ShowWtkAxes (TRUE);

}

CdmvArticulationData::~CdmvArticulationData()
{
	// on this guy's destruction, we want to deallocate all of the links in
	// the list

	CdmvLinkPointer LinkPointer;
	// go through the list freeing
	int nCounter; // counter for 'for' loop
	for (nCounter = 0; nCounter < m_arrayLinks.GetSize (); nCounter ++)
	{
		LinkPointer = m_arrayLinks.GetAt (nCounter);
		// first make sure the pointer is not NULL
		if (LinkPointer.pLink)
			delete LinkPointer.pLink; // this assumes that new was used
				// for the allocation
		// it is assumed that the parent is somewhere in the list, so it will be
		// deallocated when we get to it in the list
	}

	// Deallocate any secondary joints
	CdmvSecJointData* pSecJoint = NULL;
	// go through the list freeing
	for (nCounter = 0; nCounter < m_arraySecondaryJoints.GetSize (); nCounter ++)
	{
		pSecJoint = m_arraySecondaryJoints.GetAt (nCounter);
		// first make sure the pointer is not NULL
		if (pSecJoint)
			delete pSecJoint; // this assumes that new was used
				// for the allocation
	}
	m_arraySecondaryJoints.RemoveAll ();

}

void CdmvArticulationData::SetReferenceSystem(Quaternion quat, CartesianVector pos)
{
	int nCounter;
	for (nCounter = 0; nCounter < sizeof (m_qOrientation) / sizeof (m_qOrientation[0]); nCounter++)
	{
		m_qOrientation[nCounter] = quat[nCounter];
	}

	for (nCounter = 0; nCounter < sizeof (m_cvPosition) / sizeof (m_cvPosition[0]); nCounter++)
		m_cvPosition[nCounter] = pos[nCounter];

}

void CdmvArticulationData::AddLink(CdmvLinkData * pLink, CdmvLinkData * pLinkParent)
{

	CdmvLinkPointer LinkPointer;
	LinkPointer.pLink = pLink;
	LinkPointer.pLinkParent = pLinkParent;

	m_arrayLinks.Add (LinkPointer);
}



void CdmvArticulationData::GetRefSystem(Quaternion quat, CartesianVector pos) const
{
	int nCounter;
	for (nCounter = 0; nCounter < 4; nCounter++)
		*(quat + nCounter) = m_qOrientation[nCounter];

	for (nCounter = 0; nCounter < 3; nCounter++)
		*(pos + nCounter) = m_cvPosition[nCounter];
}

void CdmvArticulationData::InsertLinkChild(CdmvLinkData *pLink, CdmvLinkData *pLinkParent)
{
	// note the pLinkParent maybe NULL if its the new root
	ASSERT (pLink);

	// Go through the link array and change all links with the parent as the passed parent
	// to point to the new link
	int nNumLinks = m_arrayLinks.GetSize ();
	int nCounter;

	for (nCounter = 0; nCounter < nNumLinks; nCounter++)
	{
		if (m_arrayLinks.GetAt (nCounter).pLinkParent == pLinkParent)
		{
			// then need to push it down by making pLink its parent
			CdmvLinkPointer LinkMap;
			LinkMap.pLink = m_arrayLinks.GetAt (nCounter).pLink;
			LinkMap.pLinkParent = pLink;
			m_arrayLinks.SetAt (nCounter, LinkMap);
		}
	}

	// create a link map to insert
	CdmvLinkPointer LinkMap;
	LinkMap.pLink = pLink;
	LinkMap.pLinkParent = pLinkParent;

	// Search for the link array for the parent, and then insert after it
	// If the parent is NULL, then insert it first
	if (pLinkParent == NULL)
	{
		m_arrayLinks.InsertAt (0, LinkMap);
	}
	else
	{
		for (nCounter = 0; nCounter < nNumLinks; nCounter++)
		{
			if (m_arrayLinks.GetAt (nCounter).pLink == pLinkParent)
			{
				m_arrayLinks.InsertAt (nCounter + 1, LinkMap);
				break;
			}
		}
		// should find the parent
		ASSERT (nCounter != nNumLinks);
	}
	

}

void CdmvArticulationData::InsertLinkSibling(CdmvLinkData *pLink, CdmvLinkData *pLinkParent)
{

	// This function is similar to InsertLinkChild, but since a sibling is being added
	// there isn't a need to move the children down a level

	int nNumLinks = m_arrayLinks.GetSize ();
	int nCounter;

	// create a link map to insert

	ASSERT (this);
	// note the pLinkParent maybe NULL if its the new root
	ASSERT (pLink);

	CdmvLinkPointer LinkMap;
	LinkMap.pLink = pLink;
	LinkMap.pLinkParent = pLinkParent;

	// Search for the link array for the parent, and then insert after it
	// If the parent is NULL, then insert it first
	if (pLinkParent == NULL)
	{
		m_arrayLinks.InsertAt (0, LinkMap);
	}
	else
	{
		for (nCounter = 0; nCounter < nNumLinks; nCounter++)
		{
			if (m_arrayLinks.GetAt (nCounter).pLink == pLinkParent)
			{
				m_arrayLinks.InsertAt (nCounter + 1, LinkMap);
				break;
			}
		}
		// should find the parent
		ASSERT (nCounter != nNumLinks);
	}
	

}

void CdmvArticulationData::DeleteLink(CdmvLinkData *pLink)
{
	CutLink (pLink);

	// Now free the memory for the link
	delete pLink;
}

void CdmvArticulationData::DeleteLinkRecursively(CdmvLinkData *pLink)
{
	ASSERT (pLink);

	int nNumLinks = m_arrayLinks.GetSize ();
	int nCounter;
	
	CdmvLinkPointer DeletedLinkMap; // temporarily store the deleted data

	// Remove the link from the array
	for (nCounter = 0; nCounter < nNumLinks; nCounter++)
	{
		if (m_arrayLinks.GetAt (nCounter).pLink == pLink)
		{
			// Store for later use when updating the deleted link's children
			DeletedLinkMap = m_arrayLinks.GetAt (nCounter);
			// Now remove it from the array
			m_arrayLinks.RemoveAt (nCounter);
			break;
		}
	}
	ASSERT (nCounter != nNumLinks);

	// Free the link memory
	delete DeletedLinkMap.pLink;

	// Decrement the link count since one once removed
	nNumLinks --;

	// Find all links that have this link as a parent and delete them recursively
	for (nCounter = 0; nCounter < m_arrayLinks.GetSize (); nCounter++)
	{
		if (m_arrayLinks.GetAt (nCounter).pLinkParent == pLink)
		{
			DeleteLinkRecursively (m_arrayLinks.GetAt (nCounter).pLink);
			// The present implementation shouldn't allow this, but
			// restart the counter in case some links before the
			// current position were deleted
			nCounter = -1;
		}
	}
}

ArticulationType CdmvArticulationData::GetArticulationType() const
{
	// Depends if there are secondary joints allocated
	if (m_arraySecondaryJoints.GetSize () > 0)
		return CLOSED_ARTICULATION;
	else
		return OPEN_ARTICULATION;
}

/*
CdmvArticulationData::CdmvArticulationData(const CdmvArticulationData &rArticulation)
{
	// initialize members to known values
	int nCounter; // counter for 'for' loop

	for (nCounter = 0; nCounter < sizeof (m_qOrientation) / sizeof (m_qOrientation[0]); nCounter++)
		m_qOrientation[nCounter] = rArticulation.m_qOrientation[nCounter];

	for (nCounter = 0; nCounter < sizeof (m_cvPosition) / sizeof (m_cvPosition[0]); nCounter++)
		m_cvPosition[nCounter] = rArticulation.m_cvPosition[nCounter];
	
	// create a copy of the array of links -- first go through and 
	int nNumberOfLinks = rArticulation.m_arrayLinks.GetSize ();
	for (nCounter = 0; nCounter < nNumberOfLinks; nCounter++)
	{
		CdmvLinkPointer LinkPointer;
		LinkPointer.pLink = new CdmvLinkData (*(rArticulation.m_arrayLinks.GetAt (nCounter).pLink));
		// find the parent
		if (rArticulation.m_arrayLinks.GetAt (nCounter).pLinkParent == NULL)
		{
			LinkPointer.pLinkParent = NULL;
		}
		else
		{
			// Otherwise look back through the old link array to find the index number of the
			// parent and then set the pLink of that that to the pParentLink of the new link in
			// need of a parent
			int nInnerCounter;
			for (nInnerCounter = 0; nInnerCounter < nCounter; nInnerCounter)
			{
				if (rArticulation.m_arrayLinks.GetAt (nInnerCounter).pLink ==
					rArticulation.m_arrayLinks.GetAt (nCounter).pLink)
				{
					// Then found the parent index so use that info to find the parent in the new array
					LinkPointer.pLinkParent = m_arrayLinks.GetAt (nInnerCounter).pLink;
				}
			}
			// the parent should always be found
			ASSERT ((nInnerCounter == nCounter) ? FALSE : TRUE);
		}

	}

	// Specify the object type
	m_ObjectType = rArticulation.m_ObjectType;
	// Specify the object type
	m_ArticulationType = rArticulation.m_ArticulationType;

	ASSERT (FALSE); // I don't want to use this in case the pointers change ?!?!?
}
*/

CdmvLinkData* CdmvArticulationData::FindLinkByName(CString strName) const
{
	int nCounter;
	int nNumLinks = m_arrayLinks.GetSize ();
	for (nCounter = 0; nCounter < nNumLinks; nCounter++)
	{
		CString strCurrentLinkName = m_arrayLinks.GetAt (nCounter).pLink->GetName ();
		if (strCurrentLinkName == strName)
			return m_arrayLinks.GetAt (nCounter).pLink;
	}

	return NULL;
}

void CdmvArticulationData::CutLink(CdmvLinkData *pLink)
{
	ASSERT (pLink != NULL);

	int nNumLinks = m_arrayLinks.GetSize ();
	int nCounter;
	
	CdmvLinkPointer DeletedLinkMap; // temporarily store the deleted data

	// Remove the link from the array
	for (nCounter = 0; nCounter < nNumLinks; nCounter++)
	{
		if (m_arrayLinks.GetAt (nCounter).pLink == pLink)
		{
			// Store for later use when updating the deleted link's children
			DeletedLinkMap = m_arrayLinks.GetAt (nCounter);
			// Now remove it from the array
			m_arrayLinks.RemoveAt (nCounter);
			break;
		}
	}
	ASSERT (nCounter != nNumLinks);

	// Find all links that have this link as a parent and set their
	// parent to be this link's parent
	
	// since a link was deleted, decrement the size
	nNumLinks --;
	for (nCounter = 0; nCounter < nNumLinks; nCounter++)
	{
		if (m_arrayLinks.GetAt (nCounter).pLinkParent == pLink)
		{
			CdmvLinkPointer LinkMap;
			LinkMap.pLink = m_arrayLinks.GetAt (nCounter).pLink;
			LinkMap.pLinkParent = DeletedLinkMap.pLinkParent;
			m_arrayLinks.SetAt (nCounter, LinkMap);
		}
	}
	
	// If it is a closed loop, need to check the list of secondary joint for
	// this link
	if (this->GetArticulationType () == CLOSED_ARTICULATION)
	{
		DeleteSecJointsByLink (pLink);
	}
}

void CdmvArticulationData::CopyLink(CdmvLinkData *pLink, CdmvLinkData **ppNewLink)
{
	ASSERT (pLink);

	if (pLink->GetLinkType () == REVOLUTE_LINK)
	{
		CdmvRevoluteLinkData *p = dynamic_cast <CdmvRevoluteLinkData*> (pLink);
		*ppNewLink = new CdmvRevoluteLinkData ((*p));
	}
	else if (pLink->GetLinkType () == MOBILE_BASE_LINK)
	{
		CdmvMobileBaseLinkData *p = dynamic_cast <CdmvMobileBaseLinkData*> (pLink);
		*ppNewLink = new CdmvMobileBaseLinkData ((*p));
	}
	else if (pLink->GetLinkType () == PRISMATIC_LINK)
	{
		CdmvPrismaticLinkData *p = dynamic_cast <CdmvPrismaticLinkData*> (pLink);
		*ppNewLink = new CdmvPrismaticLinkData ((*p));
	}
	else if (pLink->GetLinkType () == SPHERICAL_LINK)
	{
		CdmvSphericalLinkData *p = dynamic_cast <CdmvSphericalLinkData*> (pLink);
		*ppNewLink = new CdmvSphericalLinkData ((*p));
	}
	else if (pLink->GetLinkType () == STATIC_ROOT_LINK)
	{
		CdmvStaticRootLinkData *p = dynamic_cast <CdmvStaticRootLinkData*> (pLink);
		*ppNewLink = new CdmvStaticRootLinkData ((*p));
	}
	else if (pLink->GetLinkType () == ZSCREW_TX_LINK)
	{
		CdmvZScrewTxLinkData *p = dynamic_cast <CdmvZScrewTxLinkData*> (pLink);
		*ppNewLink = new CdmvZScrewTxLinkData ((*p));
	}
	else
	{
		// Unexpected state
		ASSERT (FALSE);
	}
}

void CdmvArticulationData::InsertLinkAsParent(CdmvLinkData *pNewLink, CdmvLinkData *pOldLink)
{
	ASSERT (pNewLink && pOldLink);

	// Go through the link array to find the old link
	int nNumLinks = m_arrayLinks.GetSize ();
	int nCounter;

	for (nCounter = 0; nCounter < nNumLinks; nCounter++)
	{
		if (m_arrayLinks.GetAt (nCounter).pLink == pOldLink)
		{
			// Get a copy of the link pointer of the old link
			CdmvLinkPointer OldLinkMap;
			OldLinkMap = m_arrayLinks.GetAt (nCounter);

			// Build the new link
			CdmvLinkPointer NewLinkMap;
			NewLinkMap.pLink = pNewLink;
			NewLinkMap.pLinkParent = OldLinkMap.pLinkParent;

			// Insert the new link before this one
			m_arrayLinks.InsertAt (nCounter, NewLinkMap);

			// Change the parent of the old link to the new link
			OldLinkMap.pLinkParent = pNewLink;

			// Reset the data - note need to increment the index because it was pushed
			// back one by the new link
			m_arrayLinks.SetAt (nCounter + 1, OldLinkMap);

			// Done so return
			return;
		}
	}

	// If get here, the old link was not found -- this should never happen
	ASSERT (FALSE);
}

void CdmvArticulationData::AddSecJoint (CdmvSecJointData* pSecJoint)
{
	ASSERT (pSecJoint);

	m_arraySecondaryJoints.Add (pSecJoint);
}

void CdmvArticulationData::DeleteSecJoint(CdmvSecJointData *pSecJoint)
{
	ASSERT (pSecJoint);

	int nNumSecJoints = m_arraySecondaryJoints.GetSize ();
	int nCounter;
	
	// Remove the link from the array
	for (nCounter = 0; nCounter < nNumSecJoints; nCounter++)
	{
		if (m_arraySecondaryJoints.GetAt (nCounter) == pSecJoint)
		{
			// Now remove it from the array
			m_arraySecondaryJoints.RemoveAt (nCounter);
			// free the memory
			delete pSecJoint;
			break;
		}
	}
	ASSERT (nCounter != nNumSecJoints);
}

// to remove a the secondary joints connected to a given link pointer
void CdmvArticulationData::DeleteSecJointsByLink(CdmvLinkData *pLinkData)
{
	ASSERT (pLinkData);

	int nNumSecJoints = m_arraySecondaryJoints.GetSize ();
	int nCurrentIndex = 0;
	
	// Remove the link from the array
	while (nCurrentIndex < nNumSecJoints)
	{
		if ((m_arraySecondaryJoints.GetAt (nCurrentIndex))->GetLinkA () == pLinkData
			|| (m_arraySecondaryJoints.GetAt (nCurrentIndex))->GetLinkB () == pLinkData)
		{
			// Need to remove the secondary joint connected to the link
			m_arraySecondaryJoints.RemoveAt (nCurrentIndex);
			// Note that the index won't advance because the current index was just deleted
			// and everything in the array will shift down.  The size needs to be updated
			// though to reflect the deletion.
			nNumSecJoints --;
		}
		else
		{
			// The advance the index and look at the next joint
			nCurrentIndex ++;
		}
	}
}

void CdmvArticulationData::AddSoftSecJoint(CdmvSecJointData *pSecJoint)
{
	ASSERT (pSecJoint);

	// set the joint as soft
	pSecJoint->SetSoftOrHard (SOFT_SEC_JOINT);

	AddSecJoint (pSecJoint);
}

void CdmvArticulationData::AddHardSecJoint(CdmvSecJointData *pSecJoint)
{
	ASSERT (pSecJoint);

	// set the joint as hard
	pSecJoint->SetSoftOrHard (HARD_SEC_JOINT);

	AddSecJoint (pSecJoint);
}

// This function can be called to determine if the current articulation is valid.
// The return value has information about the error
int CdmvArticulationData::ValidateArticulation() const
{
	// Check that there is only one static root link
	if (GetNumberOfStaticRootLinks () > 1)
		return ART_ERROR_TOO_MANY_STATIC_ROOT_LINK;

	// Check if the static root link is anything but the child of the base
	if (GetNumberOfStaticRootLinks () == 1)
	{
		// Find the link
		int i;
		for (i = 0; i < m_arrayLinks.GetSize (); i++)
		{
			if (m_arrayLinks.GetAt (i).pLink->GetLinkType () == STATIC_ROOT_LINK)
			{
				// Found the static root link - check that its parent is the base
				if (m_arrayLinks.GetAt (i).pLinkParent != NULL)
					return ART_ERROR_STATIC_ROOT_LINK_BAD_PLACE;
			}
		}
	}

	// No errors detected
	return ART_ERROR_NONE;
}

// Returns the number of static root links in the articulation
int CdmvArticulationData::GetNumberOfStaticRootLinks() const
{
	int nCount = 0;

	// Go through each link
	int i;
	for (i = 0; i < m_arrayLinks.GetSize (); i++)
	{
		if (m_arrayLinks.GetAt (i).pLink->GetLinkType () == STATIC_ROOT_LINK)
			nCount ++;
	}

	return nCount;
}

// Returns number of links in the articulation
int CdmvArticulationData::GetNumberOfLinks() const
{
	return m_arrayLinks.GetSize ();
}

WTnode* CdmvArticulationData::GetCameraCenterOfInterest()
{
	// Go through each link and check the flag
	// Start with the articulation
	if (this->IsCameraCenterOfInterest ())
		return this->GetWtkNode ();

	int i;
	for (i = 0; i < m_arrayLinks.GetSize (); i++)
	{
		if (m_arrayLinks.GetAt (i).pLink->IsCameraCenterOfInterest ())
			return m_arrayLinks.GetAt (i).pLink->GetWtkNode ();
	}

	// else none selected so return NULL
	return NULL;
}

CString CdmvArticulationData::GetCenterOfInterestName()
{

	// Go through each link and check the flag
	// Start with the articulation
	if (this->IsCameraCenterOfInterest ())
		return this->GetName();

	int i;
	for (i = 0; i < m_arrayLinks.GetSize (); i++)
	{
		if (m_arrayLinks.GetAt (i).pLink->IsCameraCenterOfInterest ())
			return m_arrayLinks.GetAt (i).pLink->GetName ();
	}

	// else none selected, so it must be the Inertial Axes
	CString strReturn;
	strReturn.LoadString(IDS_STRING_INERTIAL_AXES);
	return strReturn;
}

// Go through each link and the articulation and set the state false which says
// if the item is a COI
void CdmvArticulationData::ClearCameraCenterOfInterest()
{
	// Start with the articulation
	this->IsCameraCenterOfInterest (FALSE);

	// Go through each link
	int i;
	for (i = 0; i < m_arrayLinks.GetSize (); i++)
	{
		m_arrayLinks.GetAt (i).pLink->IsCameraCenterOfInterest (FALSE);
	}
}
