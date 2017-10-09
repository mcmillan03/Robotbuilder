// dmvRevoluteLinkData.cpp: implementation of the CdmvRevoluteLinkData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "dmvRevoluteLinkData.h"
#include "dmvRevDCMotorData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvRevoluteLinkData::CdmvRevoluteLinkData()
{
	// init members
	m_pActuator = NULL;

	// set the link type
	m_LinkType = REVOLUTE_LINK;

	// Set the default name
	m_strName = "Revolute Link";
}

CdmvRevoluteLinkData::~CdmvRevoluteLinkData()
{
	// if there is an actuator, free the mem
	if (m_pActuator)
		delete m_pActuator;
}

void CdmvRevoluteLinkData::SetActuator(CdmvActuatorData *pActuator)
{
	ASSERT (m_pActuator == NULL);
	m_pActuator = pActuator;
}

CdmvActuatorData* CdmvRevoluteLinkData::GetActuator() const
{
	return m_pActuator;
}

void CdmvRevoluteLinkData::DeleteActuator()
{
	if (m_pActuator)
		delete m_pActuator;

	m_pActuator = NULL;
}

CdmvRevoluteLinkData::CdmvRevoluteLinkData(const CdmvRevoluteLinkData &rCdmvRevoluteLinkData): CdmvMDHLinkData(rCdmvRevoluteLinkData)
{
	// First check if an actuator is allocated
	if (rCdmvRevoluteLinkData.GetActuator ())
	{
		// Allocate the same type of actuator
		if (rCdmvRevoluteLinkData.GetActuator ()->GetActuatorType () == NO_MOTOR)
		{
			try {
				m_pActuator = new CdmvActuatorData (*(rCdmvRevoluteLinkData.GetActuator ()));
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}
		}
		else if (rCdmvRevoluteLinkData.GetActuator ()->GetActuatorType () == REV_DC_MOTOR)
		{
			try {
				m_pActuator = new CdmvRevDCMotorData 
					(*(dynamic_cast<CdmvRevDCMotorData*>(rCdmvRevoluteLinkData.GetActuator ())));
			}
			catch (CMemoryException*)
			{
				AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
				AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
				// Throw exception to next handler to break out of this function
				throw;
			}
		}
	}
	else
	{
		// No actuator
		m_pActuator = NULL;
	}
}
