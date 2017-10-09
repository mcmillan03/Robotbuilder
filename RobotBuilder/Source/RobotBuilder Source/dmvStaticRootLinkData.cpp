// dmvStaticRootLinkData.cpp: implementation of the CdmvStaticRootLinkData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvStaticRootLinkData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvStaticRootLinkData::CdmvStaticRootLinkData()
{
	// set the link type
	m_LinkType = STATIC_ROOT_LINK;

	// Set the default name
	m_strName = "Static Root Link";
}

CdmvStaticRootLinkData::~CdmvStaticRootLinkData()
{

}
