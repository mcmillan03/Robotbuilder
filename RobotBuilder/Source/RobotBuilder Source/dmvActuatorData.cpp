// dmvActuatorData.cpp: implementation of the CdmvActuatorData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvActuatorData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvActuatorData::CdmvActuatorData()
{
	m_ActuatorType = NO_MOTOR;
}

CdmvActuatorData::~CdmvActuatorData()
{

}

ActuatorType CdmvActuatorData::GetActuatorType() const
{
	return m_ActuatorType;
}
