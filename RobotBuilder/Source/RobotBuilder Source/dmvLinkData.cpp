// dmvLinkData.cpp: implementation of the CdmvLinkData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvLinkData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//static unsigned int g_nCurrentLinkUID = 0;

CdmvLinkData::CdmvLinkData()
{
	// init members
	m_FJointFriction = 0;
	// specify the object type
	m_ObjectType = LINK;
	// Since this new link was created, need to increment the g_nCurrentLinkUID
//	g_nCurrentLinkUID++;
}

CdmvLinkData::~CdmvLinkData()
{

}

void CdmvLinkData::SetJointFriction(Float fJointFriction)
{
	m_FJointFriction = fJointFriction;
}


BOOL CdmvLinkData::GetLinkParameters(Float* pfParameters)
{
	// This should be implemented in a derived class
	return FALSE;
}

LinkType CdmvLinkData::GetLinkType() const
{
	return m_LinkType;
}

Float CdmvLinkData::GetJointFriction() const
{
	return m_FJointFriction;
}


