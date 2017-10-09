// dmvPrismaticLinkData.cpp: implementation of the CdmvPrismaticLinkData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvPrismaticLinkData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvPrismaticLinkData::CdmvPrismaticLinkData()
{
	// set the link type
	m_LinkType = PRISMATIC_LINK;

	// Set the default name
	m_strName = "Prismatic Link";
}

CdmvPrismaticLinkData::~CdmvPrismaticLinkData()
{

}
