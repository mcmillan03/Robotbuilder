// dmvRigidBodyData.cpp: implementation of the CdmvRigidBodyData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "dmvRigidBodyData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvRigidBodyData::CdmvRigidBodyData()
{
	// init members
	m_strtRigidBodyInertialParameters.fMass = 1;
	int nCounter, nInnerCounter; // counters for nested 'for' loops
	for (nCounter = 0; nCounter < 3; nCounter++)
		for (nInnerCounter = 0; nInnerCounter < 3; nInnerCounter++)
		{
			if (nCounter == nInnerCounter)
				m_strtRigidBodyInertialParameters.ctIbar[nCounter][nInnerCounter] = 1;
			else
				m_strtRigidBodyInertialParameters.ctIbar[nCounter][nInnerCounter] = 0;
		}
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[0] = 0;
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[1] = 0;
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[2] = 0;

	m_pContactModel = NULL;

}

CdmvRigidBodyData::~CdmvRigidBodyData()
{
//	while (!m_listForces.IsEmpty ())
//	{
//		delete m_listForces.RemoveHead ();
//	}
	if (m_pContactModel)
		delete m_pContactModel;
}

void CdmvRigidBodyData::SetInertiaParameters(Float fMass, CartesianTensor ctIbar, CartesianVector cvCenterGravityPosition)
{
	m_strtRigidBodyInertialParameters.fMass = fMass;
	int nCounter, nInnerCounter; // counters for nested 'for' loops
	for (nCounter = 0; nCounter < 3; nCounter++)
		for (nInnerCounter = 0; nInnerCounter < 3; nInnerCounter++)
			m_strtRigidBodyInertialParameters.ctIbar[nCounter][nInnerCounter] = ctIbar[nCounter][nInnerCounter];
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[0] = cvCenterGravityPosition[0];
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[1] = cvCenterGravityPosition[1];
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[2] = cvCenterGravityPosition[2];
}

void CdmvRigidBodyData::SetContactModel(CdmvContactModelData *pContactModel)
{
	m_pContactModel = pContactModel;
}

CdmvContactModelData* CdmvRigidBodyData::GetContactModel() const
{
	return m_pContactModel;
}

void CdmvRigidBodyData::DeleteContactModel ()
{
	if (m_pContactModel)
	{
		delete m_pContactModel;
		m_pContactModel = NULL;
	}
}

void CdmvRigidBodyData::GetInertialParameters(
	structRigidBodyInertialParameters *pstrtRigidBodyInertialParameters) const
{
	pstrtRigidBodyInertialParameters->fMass = m_strtRigidBodyInertialParameters.fMass;
	pstrtRigidBodyInertialParameters->cvCenterGravityPosition[0] = 
		m_strtRigidBodyInertialParameters.cvCenterGravityPosition[0];
	pstrtRigidBodyInertialParameters->cvCenterGravityPosition[1] = 
		m_strtRigidBodyInertialParameters.cvCenterGravityPosition[1];
	pstrtRigidBodyInertialParameters->cvCenterGravityPosition[2] = 
		m_strtRigidBodyInertialParameters.cvCenterGravityPosition[2];

	int i, j; // counters for 'for' loop
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			pstrtRigidBodyInertialParameters->ctIbar[i][j] = 
				m_strtRigidBodyInertialParameters.ctIbar[i][j];
		}
	}

}

void CdmvRigidBodyData::SetInertialParameters(const structRigidBodyInertialParameters *pstrtRigidBodyInertialParameters)
{
	m_strtRigidBodyInertialParameters.fMass = pstrtRigidBodyInertialParameters->fMass;
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[0] = 
		pstrtRigidBodyInertialParameters->cvCenterGravityPosition[0];
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[1] = 
		pstrtRigidBodyInertialParameters->cvCenterGravityPosition[1];
	m_strtRigidBodyInertialParameters.cvCenterGravityPosition[2] = 
		pstrtRigidBodyInertialParameters->cvCenterGravityPosition[2];

	int i, j; // counters for 'for' loop
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			m_strtRigidBodyInertialParameters.ctIbar[i][j] = 
				pstrtRigidBodyInertialParameters->ctIbar[i][j];
		}
	}
}

CdmvRigidBodyData::CdmvRigidBodyData(const CdmvRigidBodyData &rCdmvRigidBodyData)
{
	structRigidBodyInertialParameters strtRigidBodyInertialParameters;

	rCdmvRigidBodyData.GetInertialParameters (&strtRigidBodyInertialParameters);
	m_strtRigidBodyInertialParameters.fMass = strtRigidBodyInertialParameters.fMass;

	int i, j;
	for (i = 0; i < 3; i++)
	{
		m_strtRigidBodyInertialParameters.cvCenterGravityPosition[i] = 
			strtRigidBodyInertialParameters.cvCenterGravityPosition[i];
		for (j = 0; j < 3; j++)
			m_strtRigidBodyInertialParameters.ctIbar[i][j] = 
				strtRigidBodyInertialParameters.ctIbar[i][j];
	}

	if (rCdmvRigidBodyData.GetContactModel ())
	{
		try {
			m_pContactModel = new CdmvContactModelData (*(rCdmvRigidBodyData.GetContactModel ()));
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}
	}
	else
	{
		// No contact model
		m_pContactModel = NULL;
	}
}
