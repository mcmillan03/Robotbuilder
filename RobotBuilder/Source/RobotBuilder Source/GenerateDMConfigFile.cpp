// GenerateDMConfigFile.cpp: implementation of the CGenerateDMConfigFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GenerateDMConfigFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGenerateDMConfigFile::CGenerateDMConfigFile()
{

}

CGenerateDMConfigFile::~CGenerateDMConfigFile()
{

}

BOOL CGenerateDMConfigFile::CreateDMConfigFile(CString strFilePath, CdmvSystemData * pSystem)
{
	ofstream dmfile;
	dmfile.open (strFilePath);
	int nIsOpen = dmfile.is_open ();
	if (!nIsOpen)
		return FALSE;
 	ASSERT (dmfile != NULL);

	OutputFileHeader (dmfile, pSystem);
	// 14 MAY 2002 Remove version to be compatible with DynaMechs
//	OutputVersion (dmfile);
	CdmvArticulationData* pCdmvArticulationData = ((CdmvArticulationData*) pSystem);
	OutputArticulation (dmfile, 0, pCdmvArticulationData);
	int nArraySize = ((CdmvArticulationData*) pSystem)->m_arrayLinks.GetSize ();
	
	if (nArraySize > 0)
	{
		BOOL bRepeat = TRUE;
		int nCurrent = 0;
		int nNextTop = 0;
		while (bRepeat)
		{
			bRepeat = GetNextTopLevelNode (pSystem, nCurrent + 1, &nNextTop);
			BuildBranch (pSystem, nCurrent, 1, dmfile, 
				nNextTop - 1);
			nCurrent = nNextTop;
		}
	}

	// If its a closed articulation, need to close the tree structure and output the
	// secondary joint list.
	if (pCdmvArticulationData->GetArticulationType () == CLOSED_ARTICULATION)
	{
		dmfile << LPCTSTR(TabCount (1)) << "}" << endl;
		OutputSecondaryJointList (dmfile, 1, pCdmvArticulationData);
	}
	
	// The closing brace for the articulation
	dmfile << "}";

	dmfile.close ();

	return TRUE;
}

BOOL CGenerateDMConfigFile::GetNextTopLevelNode(const CdmvSystemData *pSystem,
												int nCurrent, int *pnNextTop)
{
	ASSERT (pSystem);

	int nCounter;
	for (nCounter = nCurrent; nCounter < ((CdmvArticulationData*) pSystem)->m_arrayLinks.GetSize (); nCounter ++)
	{
		if (((CdmvArticulationData*) pSystem)->m_arrayLinks.GetAt (nCounter).pLinkParent == NULL)
		{
			*pnNextTop = nCounter;
			return TRUE;
		}
	}

	// else no others
	*pnNextTop = nCounter;
	return FALSE;
}


BOOL CGenerateDMConfigFile::IsBranchParent(const CdmvSystemData * pSystem, int nPotentialParentIndex,
										   int nStartLinkIndex,
										   int *pnNextBranchIndex)
{
	ASSERT (pSystem);
	
	// Save a copy of the pointer for comparison later
	CdmvLinkData* pLinkParent = ((CdmvArticulationData*) pSystem)->m_arrayLinks.GetAt (nPotentialParentIndex).pLink;

	// First check the special case that the link is the last link 
	// in the array.  Also check that there is at least two links left
	// otherwise there couldn't be a branch.
	if (nStartLinkIndex >= ((CdmvArticulationData*) pSystem)->m_arrayLinks.GetSize () - 1)
	{
		// Then obviously not a branch parent
		return FALSE;
	}

	// Now if the next link is not a child of the link that we are analyzing
	// then the link is the end of a chain and consequently can't be a parent
	// of a branch.  This check is an attempt to optimize so the entire array
	// doesn't have to be analyzed if it is not needed
	if (pLinkParent != ((CdmvArticulationData*) pSystem)->m_arrayLinks.GetAt (nStartLinkIndex).pLinkParent)
	{
		// Then obviously not a branch parent
		return FALSE;
	}

	int nCounter; // counter for 'for' loop
	for (nCounter = nStartLinkIndex + 1; nCounter < ((CdmvArticulationData*) pSystem)->m_arrayLinks.GetSize ();
		nCounter ++)
	{
		CdmvLinkPointer LinkPointer = ((CdmvArticulationData*) pSystem)->m_arrayLinks.GetAt (nCounter);

		if (LinkPointer.pLinkParent == pLinkParent)
		{
			// Then found a match.  Note that this is the second
			// match (because the first was found before this loop)
			*pnNextBranchIndex = nCounter;
			return TRUE;
		}
	}	

	// Otherwise, the loop processed all links and could not find
	// another match.
	return FALSE;
}

void CGenerateDMConfigFile::BuildBranch(const CdmvSystemData * pSystem, int nCurrentLinkIndex, int nCurrentTab, 
										ostream &OutStream, int nLastIndex)
{
	// Start the branch
	OutStream << LPCTSTR(TabCount (nCurrentTab)) << "Branch {" << endl;


	while (nCurrentLinkIndex <= nLastIndex)
	{
		// Check if the current index is a branch parent
		OutputLink (OutStream, nCurrentTab + 1, ((CdmvArticulationData*) pSystem)->m_arrayLinks.GetAt (nCurrentLinkIndex).pLink);
		nCurrentLinkIndex ++;

		int nNextBranchIndex;
		int nPotentialParentIndex = nCurrentLinkIndex-1;
		while (IsBranchParent (pSystem, nPotentialParentIndex, nCurrentLinkIndex, &nNextBranchIndex))
		{
//			OutStream << LPCTSTR(TabCount (nCurrentTab)) << "Branch {" << endl;
			// Then build the branch
			BuildBranch (pSystem, nCurrentLinkIndex,
				nCurrentTab + 1, OutStream, nNextBranchIndex - 1);
			// Now the current index is the nNextIndexAfterBranch
			nCurrentLinkIndex = nNextBranchIndex;
//			OutStream << LPCTSTR(TabCount (nCurrentTab)) << "}" << endl;
		}
	}

		OutStream << LPCTSTR(TabCount (nCurrentTab)) << "}" << endl;
}

void CGenerateDMConfigFile::OutputArticulation (ostream &OutStream, int nTabDepth, const CdmvArticulationData* 
						 pCdmvArticulationData)
{
	ASSERT (pCdmvArticulationData);
		
	if (pCdmvArticulationData->GetArticulationType () == CLOSED_ARTICULATION)
		OutStream << LPCTSTR(TabCount(nTabDepth)) << "ClosedArticulation {" << endl;
	else
		OutStream << LPCTSTR(TabCount(nTabDepth)) << "Articulation {" << endl;
	OutputObjectData (OutStream, nTabDepth, (CdmvObject*) pCdmvArticulationData);
	Quaternion qOrientation;
	CartesianVector cvPosition;
	pCdmvArticulationData->GetRefSystem (qOrientation, cvPosition);

	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Position" << "\t\t" << cvPosition[0] << "\t" <<
		cvPosition[1] << "\t" << cvPosition[2] << endl;

	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Orientation_Quat" << "\t" << qOrientation[0] << "\t" <<
		qOrientation[1] << "\t" << qOrientation[2] << "\t" << qOrientation[3] << endl;

	if (pCdmvArticulationData->GetArticulationType () == CLOSED_ARTICULATION)
		OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "TreeStructure {" << endl;


}

void CGenerateDMConfigFile::OutputFileHeader(ostream &OutStream, const CdmvSystemData *pSysterm)
{
	OutStream << "# DynaMechs V 4.0 ascii" << endl << endl;
}

void CGenerateDMConfigFile::OutputLink (ostream &OutStream, int nTabDepth, const CdmvLinkData* 
						 pCdmvLinkData)
{
	ASSERT (pCdmvLinkData);
	
	switch (pCdmvLinkData->GetLinkType ())
	{
	case MOBILE_BASE_LINK:
		OutputMobileBaseLink (OutStream, nTabDepth, (CdmvMobileBaseLinkData*) pCdmvLinkData);
		break;
	case REVOLUTE_LINK:
		OutputRevoluteLink (OutStream, nTabDepth, (CdmvRevoluteLinkData*) pCdmvLinkData);
		break;
	case ZSCREW_TX_LINK:
		OutputZScrewTxLink (OutStream, nTabDepth, (CdmvZScrewTxLinkData*) pCdmvLinkData);
		break;
	case PRISMATIC_LINK:
		OutputPrismaticLink (OutStream, nTabDepth, (CdmvPrismaticLinkData*) pCdmvLinkData);
		break;
	case STATIC_ROOT_LINK:
		OutputStaticRootLink (OutStream, nTabDepth, (CdmvStaticRootLinkData*) pCdmvLinkData);
		break;
	case SPHERICAL_LINK:
		OutputSphericalLink  (OutStream, nTabDepth, (CdmvSphericalLinkData*) pCdmvLinkData);
		break;
	default:
		ASSERT (FALSE);
	}
}

void CGenerateDMConfigFile::OutputMobileBaseLink (ostream &OutStream, int nTabDepth, const CdmvMobileBaseLinkData* 
						 pCdmvMobileBaseLinkData)
{
	ASSERT (pCdmvMobileBaseLinkData);
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "MobileBaseLink {" << endl; 
	OutputObjectData (OutStream, nTabDepth, (CdmvObject*) pCdmvMobileBaseLinkData);
	OutputRigidBodyParameters (OutStream, nTabDepth, (CdmvRigidBodyData*) pCdmvMobileBaseLinkData);
	OutputMobileBaseParameters (OutStream, nTabDepth, pCdmvMobileBaseLinkData);
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "}" << endl << endl;
}

void CGenerateDMConfigFile::OutputRevoluteLink (ostream &OutStream, int nTabDepth, const CdmvRevoluteLinkData* 
						 pCdmvRevoluteLinkData)
{
	ASSERT (pCdmvRevoluteLinkData);
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "RevoluteLink {" << endl; 
	OutputObjectData (OutStream, nTabDepth, (CdmvObject*) pCdmvRevoluteLinkData);
	OutputRigidBodyParameters (OutStream, nTabDepth, (CdmvRigidBodyData*) pCdmvRevoluteLinkData);
	OutputMDHParameters (OutStream, nTabDepth, (CdmvMDHLinkData*) pCdmvRevoluteLinkData);
	OutputActuator (OutStream, nTabDepth, pCdmvRevoluteLinkData);
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "}" << endl << endl;

}

void CGenerateDMConfigFile::OutputPrismaticLink (ostream &OutStream, int nTabDepth, const CdmvPrismaticLinkData* 
						 pCdmvPrismaticLinkData)
{
	ASSERT (pCdmvPrismaticLinkData);
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "PrismaticLink {" << endl; 
	OutputObjectData (OutStream, nTabDepth, (CdmvObject*) pCdmvPrismaticLinkData);
	OutputRigidBodyParameters (OutStream, nTabDepth, (CdmvRigidBodyData*) pCdmvPrismaticLinkData);
	OutputMDHParameters (OutStream, nTabDepth, (CdmvMDHLinkData*) pCdmvPrismaticLinkData);
	OutputJointFriction (OutStream, nTabDepth, (CdmvLinkData*) pCdmvPrismaticLinkData);
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "}" << endl << endl;
}

void CGenerateDMConfigFile::OutputZScrewTxLink (ostream &OutStream, int nTabDepth, const CdmvZScrewTxLinkData* 
						 pCdmvZScrewTxLinkData)
{
	ASSERT (pCdmvZScrewTxLinkData);

	structZScrewTxLinkParameters strtZScrewTxLinkParameters;
	pCdmvZScrewTxLinkData->GetParameters (&strtZScrewTxLinkParameters);
			
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "ZScrewTxLink {" << endl; 
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Name" << "\t\t\t\"" << LPCTSTR(pCdmvZScrewTxLinkData->GetName ()) << "\"" << endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "ZScrew_Parameters" << "\t" <<
		strtZScrewTxLinkParameters.fD << '\t' << strtZScrewTxLinkParameters.fTheta << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "}" << endl << endl;

}

CString CGenerateDMConfigFile::TabCount(int nNumTabs)
{
	CString str;
	int nCounter;
	for (nCounter = 0; nCounter < nNumTabs; nCounter++)
		str += "\t";

	return str;
}

void CGenerateDMConfigFile::OutputObjectData(ostream & OutStream, int nTabDepth, const CdmvObject * pCdmvObject)
{
	ASSERT (pCdmvObject);

	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Name" << "\t\t\"" << LPCTSTR(pCdmvObject->GetName ()) << "\"" << endl;
	CString strGraphicsFile, strGraphicsPath;
	pCdmvObject->GetGraphicsModel (strGraphicsFile, strGraphicsPath);
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Graphics_Model" << "\t\"" << LPCTSTR(strGraphicsFile) << "\"" << endl;
	OutStream << endl;
}

void CGenerateDMConfigFile::OutputRigidBodyParameters(ostream & OutStream, int nTabDepth, const CdmvRigidBodyData * pCdmvRigidBodyData)
{
	ASSERT (pCdmvRigidBodyData);

	structRigidBodyInertialParameters strtRigidBodyInertialParameters;
	pCdmvRigidBodyData->GetInertialParameters (&strtRigidBodyInertialParameters);
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Mass" << "\t\t\t" << strtRigidBodyInertialParameters.fMass << endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Inertia" << "\t\t\t" << strtRigidBodyInertialParameters.ctIbar[0][0] 
		<< '\t' << strtRigidBodyInertialParameters.ctIbar[0][1]
		<< '\t' << strtRigidBodyInertialParameters.ctIbar[0][2]
		<< endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "\t\t\t" << strtRigidBodyInertialParameters.ctIbar[1][0] 
		<< '\t' << strtRigidBodyInertialParameters.ctIbar[1][1]
		<< '\t' << strtRigidBodyInertialParameters.ctIbar[1][2]
		<< endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "\t\t\t" << strtRigidBodyInertialParameters.ctIbar[2][0] 
		<< '\t' << strtRigidBodyInertialParameters.ctIbar[2][1]
		<< '\t' << strtRigidBodyInertialParameters.ctIbar[2][2]
		<< endl;

	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Center_of_Gravity" << "\t"
		<< strtRigidBodyInertialParameters.cvCenterGravityPosition[0] << '\t'
		<< strtRigidBodyInertialParameters.cvCenterGravityPosition[1] << '\t'
		<< strtRigidBodyInertialParameters.cvCenterGravityPosition[2] << '\t'
		<< endl;
	
	OutputContactParameters (OutStream, nTabDepth, pCdmvRigidBodyData->GetContactModel ());
}

void CGenerateDMConfigFile::OutputContactParameters(ostream & OutStream, int nTabDepth, const CdmvContactModelData * pCdmvContactModelData)
{
	// The contact model may be NULL, which implies 0 contact points
	if (!pCdmvContactModelData)
	{
		OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Number_of_Contact_Points" << '\t'
			<< 0 << endl;
	}
	else
	{
		int nNumContactPoints = pCdmvContactModelData->m_arrayPosition.GetSize ();
		OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Number_of_Contact_Points" << '\t'
			<< nNumContactPoints << endl;

		int nCounter;
		for (nCounter = 0; nCounter < nNumContactPoints; nCounter++)
		{
			// need to a label for the first one
			if (nCounter == 0)
			{
				OutStream << LPCTSTR(TabCount(nTabDepth + 1)) <<
					"Contact_Locations" << '\t'
					<< pCdmvContactModelData->m_arrayPosition.GetAt (nCounter).fXval << '\t'
					<< pCdmvContactModelData->m_arrayPosition.GetAt (nCounter).fYval << '\t'
					<< pCdmvContactModelData->m_arrayPosition.GetAt (nCounter).fZval << '\t'
					<< endl;
			}
			else
			{
				OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "\t\t\t" 
					<< pCdmvContactModelData->m_arrayPosition.GetAt (nCounter).fXval << '\t'
					<< pCdmvContactModelData->m_arrayPosition.GetAt (nCounter).fYval << '\t'
					<< pCdmvContactModelData->m_arrayPosition.GetAt (nCounter).fZval << '\t'
					<< endl;
			}
		}
	}
	// Add a blank line
	OutStream << endl;
}

void CGenerateDMConfigFile::OutputMobileBaseParameters(ostream & OutStream, int nTabDepth, const CdmvMobileBaseLinkData * pCdmvMobileBaseLinkData)
{
	ASSERT (pCdmvMobileBaseLinkData);

	structMobileBaseLinkState strtMobileBaseLinkState;
	pCdmvMobileBaseLinkData->GetInitialState (&strtMobileBaseLinkState);

	OutStream << LPCTSTR(TabCount (nTabDepth + 1)) << "Position" << "\t\t" 
		<< strtMobileBaseLinkState.cvPosition[0] << '\t'
		<< strtMobileBaseLinkState.cvPosition[1] << '\t'
		<< strtMobileBaseLinkState.cvPosition[2] 
		<< endl;

	OutStream << LPCTSTR(TabCount (nTabDepth + 1)) << "Orientation_Quat" << "\t"
		<< strtMobileBaseLinkState.qOrientation[0] << '\t'
		<< strtMobileBaseLinkState.qOrientation[1] << '\t'
		<< strtMobileBaseLinkState.qOrientation[2] << '\t'
		<< strtMobileBaseLinkState.qOrientation[3] << '\t'
		<< endl;

	OutStream << LPCTSTR(TabCount (nTabDepth + 1)) << "Velocity" << "\t\t"
		<< strtMobileBaseLinkState.svVelocity[0] << '\t'
		<< strtMobileBaseLinkState.svVelocity[1] << '\t'
		<< strtMobileBaseLinkState.svVelocity[2] << '\t'
		<< strtMobileBaseLinkState.svVelocity[3] << '\t'
		<< strtMobileBaseLinkState.svVelocity[4] << '\t'
		<< strtMobileBaseLinkState.svVelocity[5] << '\t'
		<< endl;

	OutStream << endl;
}

void CGenerateDMConfigFile::OutputMDHParameters(ostream & OutStream, int nTabDepth, const CdmvMDHLinkData * pCdmvMDHLinkData)
{
	ASSERT (pCdmvMDHLinkData);

	structMDHParameters strtMDHParameters;
	pCdmvMDHLinkData->GetMDHParameters (&strtMDHParameters);

	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "MDH_Parameters" << "\t\t"
		<< strtMDHParameters.fa << '\t'
		<< strtMDHParameters.fAlpha << '\t'
		<< strtMDHParameters.fd << '\t'
		<< strtMDHParameters.fTheta << '\t'
		<< endl;

//	structMDHLinkState strtMDHLinkState;
//	pCdmvMDHLinkData->GetLinkState (&strtMDHLinkState);
	Float fInitialJointVelocity;
	fInitialJointVelocity = pCdmvMDHLinkData->GetInitialJointVelocity ();

	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Initial_Joint_Velocity" << "\t"
		<< fInitialJointVelocity << endl;

	structMDHLinkJointLimits strtMDHLinkJointLimits;
	pCdmvMDHLinkData->GetJointLimits (&strtMDHLinkJointLimits);

	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Joint_Limits" << "\t\t\t"
		<< strtMDHLinkJointLimits.fMin << '\t'
		<< strtMDHLinkJointLimits.fMax
		<< endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Joint_Limit_Spring_Constant" << "\t"
		<< strtMDHLinkJointLimits.fSpring 
		<< endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Joint_Limit_Damper_Constant" << "\t"
		<< strtMDHLinkJointLimits.fDamper
		<< endl;
		
}

void CGenerateDMConfigFile::OutputActuator(ostream & OutStream, int nTabDepth, 
										   const CdmvRevoluteLinkData * pCdmvRevoluteLinkData)
{
	ASSERT (pCdmvRevoluteLinkData);


	// first need to check that an actuator was actually assigned
	if (pCdmvRevoluteLinkData->GetActuator () == NULL)
	{
		OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Actuator_Type" << "\t\t" << 0 
			<< endl;
		OutputJointFriction (OutStream, nTabDepth, (CdmvLinkData*) pCdmvRevoluteLinkData);
	}
	else if (pCdmvRevoluteLinkData->GetActuator ()->GetActuatorType () == NO_MOTOR)
	{
		OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Actuator_Type" << "\t\t" << 0 
			<< endl;
		OutputJointFriction (OutStream, nTabDepth, (CdmvLinkData*) pCdmvRevoluteLinkData);
	}
	else if (pCdmvRevoluteLinkData->GetActuator ()->GetActuatorType () == REV_DC_MOTOR)
	{
		OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Actuator_Type" << "\t\t\t" << 1 
			<< endl;
		OutputRevDCMotor (OutStream, nTabDepth, (CdmvRevDCMotorData*) pCdmvRevoluteLinkData->GetActuator ());
	}


}

void CGenerateDMConfigFile::OutputJointFriction(ostream &OutStream, int nTabDepth, const CdmvLinkData *pCdmvLinkData)
{
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Joint_Friction" << "\t\t"
		<< pCdmvLinkData->GetJointFriction () << endl;
}

void CGenerateDMConfigFile::OutputRevDCMotor(ostream &OutStream, int nTabDepth, const CdmvRevDCMotorData *pCdmvRevDCMotorData)
{
	structRevDCMotorParameters strtRevDCMotorParameters;
	pCdmvRevDCMotorData->GetParameters (&strtRevDCMotorParameters);
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Motor_Torque_Constant" << "\t\t"
		<< strtRevDCMotorParameters.fTorqueConstant << endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Motor_BackEMF_Constant" << "\t\t"
		<< strtRevDCMotorParameters.fBackEMFConstant << endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Motor_Armature_Resistance" << "\t"
		<< strtRevDCMotorParameters.fArmatureResistance << endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Motor_Inertia" << "\t\t\t"
		<< strtRevDCMotorParameters.fRotorInertia << endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Motor_Coulomb_Friction_Constant" << "\t"
		<< strtRevDCMotorParameters.fCoulombFrictionConstant << endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Motor_Viscous_Friction_Constant" << "\t"
		<< strtRevDCMotorParameters.fViscousFrictionConstant << endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Motor_Max_Brush_Drop" << "\t\t"
		<< strtRevDCMotorParameters.fMaxBrushDrop << endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Motor_Half_Drop_Value" << "\t\t"
		<< strtRevDCMotorParameters.fHalfDropValue << endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Motor_Gear_Ratio" << "\t\t"
		<< strtRevDCMotorParameters.fGearRatio << endl;

}


void CGenerateDMConfigFile::OutputStaticRootLink (ostream &OutStream, int nTabDepth, const CdmvStaticRootLinkData* 
	 pCdmvStaticRootLinkData)
{
	ASSERT (pCdmvStaticRootLinkData);
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "StaticRootLink {" << endl; 
	OutputObjectData (OutStream, nTabDepth, (CdmvObject*) pCdmvStaticRootLinkData);
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "}" << endl << endl;
}

void CGenerateDMConfigFile::OutputSphericalLink (ostream &OutStream, int nTabDepth, const CdmvSphericalLinkData* 
	 pCdmvSphericalLinkData)
{
	ASSERT (pCdmvSphericalLinkData);
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "SphericalLink {" << endl; 
	OutputObjectData (OutStream, nTabDepth, (CdmvObject*) pCdmvSphericalLinkData);
	OutputRigidBodyParameters (OutStream, nTabDepth, (CdmvRigidBodyData*) pCdmvSphericalLinkData);
	OutputSphericalParameters (OutStream, nTabDepth, pCdmvSphericalLinkData);
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "}" << endl << endl;
}

void CGenerateDMConfigFile::OutputSphericalParameters (ostream &OutStream, int nTabDepth, const CdmvSphericalLinkData* 
	 pCdmvSphericalLinkData)
{
	CartesianVector cvJointOffsetPosition;
	pCdmvSphericalLinkData->GetJointOffset (cvJointOffsetPosition);

	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Position_From_Inboard_Link" << "\t\t"
		<< cvJointOffsetPosition[0] << '\t'
		<< cvJointOffsetPosition[1] << '\t'
		<< cvJointOffsetPosition[2] << '\t'
		<< endl;

	structSphericalLinkState strtSphericalLinkState;
	pCdmvSphericalLinkData->GetLinkState (&strtSphericalLinkState);

	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Initial_Joint_Angles" << "\t\t"
		<< strtSphericalLinkState.eaAngles[0] << '\t'
		<< strtSphericalLinkState.eaAngles[1] << '\t'
		<< strtSphericalLinkState.eaAngles[2] << '\t'
		<< endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Initial_Angular_Velocity" << "\t\t"
		<< strtSphericalLinkState.fAngularVelocity[0] << '\t'
		<< strtSphericalLinkState.fAngularVelocity[1] << '\t'
		<< strtSphericalLinkState.fAngularVelocity[2] << '\t'
		<< endl;

	structSphericalLinkJointLimits strtSphericalLinkJointLimits;
	pCdmvSphericalLinkData->GetJointLimits (&strtSphericalLinkJointLimits);

	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Axes_Limits" << "\t\t"
		<< strtSphericalLinkJointLimits.fJointLimits[0] << '\t'
		<< strtSphericalLinkJointLimits.fJointLimits[1] << '\t'
		<< strtSphericalLinkJointLimits.fJointLimits[2] << '\t'
		<< endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Joint_Limit_Spring_Constant" << "\t\t"
		<< strtSphericalLinkJointLimits.fSpring << endl;
	OutStream << LPCTSTR(TabCount(nTabDepth + 1)) << "Joint_Limit_Damper_Constant" << "\t\t"
		<< strtSphericalLinkJointLimits.fDamper << endl;

	OutputJointFriction (OutStream, nTabDepth, (CdmvLinkData*) pCdmvSphericalLinkData);
}


void CGenerateDMConfigFile::OutputSecondaryJointList(ostream &OutStream, int nTabDepth, 
				const CdmvArticulationData *pCdmvClosedArticulationData)
{
	ASSERT (pCdmvClosedArticulationData);

	OutStream << LPCTSTR(TabCount (nTabDepth)) << "SecondaryJoints {" << endl;

	int nCounter; // counter 'for' loop
	int nNumberOfSecJoints; // number of secondary joints in closed articulation
	nNumberOfSecJoints = pCdmvClosedArticulationData->m_arraySecondaryJoints.GetSize ();

	for (nCounter = 0; nCounter < nNumberOfSecJoints; nCounter++)
	{
		OutputSecondaryJoint (OutStream, nTabDepth + 1, 
			pCdmvClosedArticulationData->m_arraySecondaryJoints.GetAt (nCounter));
	}

	OutStream << LPCTSTR(TabCount (nTabDepth)) << "}" << endl;
}

void CGenerateDMConfigFile::OutputSecondaryJoint(ostream &OutStream, int nTabDepth, const CdmvSecJointData *pCdmvSecJointData)
{
	ASSERT (pCdmvSecJointData);

	switch (pCdmvSecJointData->GetSecondaryJointType ())
	{
	case SEC_PRISMATIC:
		OutputSecPrismaticJoint (OutStream, nTabDepth, (CdmvSecPrisJntData*) pCdmvSecJointData);
		break;
	case SEC_REVOLUTE:
		OutputSecRevoluteJoint (OutStream, nTabDepth, (CdmvSecRevJntData*) pCdmvSecJointData);
		break;
	case SEC_SPHERICAL:
		OutputSecSphericalJoint (OutStream, nTabDepth, (CdmvSecSpherJntData*) pCdmvSecJointData);
		break;
	default:
		ASSERT (FALSE);
	}
}

void CGenerateDMConfigFile::OutputSecPrismaticJoint(ostream &OutStream, int nTabDepth, const CdmvSecPrisJntData *pCdmvSecPrisJntData)
{
	ASSERT (pCdmvSecPrisJntData);

	if (pCdmvSecPrisJntData->GetSoftOrHard () == SOFT_SEC_JOINT)
	{
		OutStream << LPCTSTR(TabCount (nTabDepth)) << "SoftPrismaticJoint {" << endl;
		OutStream << LPCTSTR(TabCount (nTabDepth + 1)) << "Name" << "\t\t" << "\"" <<
			LPCTSTR(pCdmvSecPrisJntData->GetName ()) << "\"" << endl;
	}
	else
	{
		OutStream << LPCTSTR(TabCount (nTabDepth)) << "HardPrismaticJoint {" << endl;
		OutStream << LPCTSTR(TabCount (nTabDepth + 1)) << "Name" << "\t\t" << "\"" <<
			LPCTSTR(pCdmvSecPrisJntData->GetName ()) << "\"" << endl;
		OutputStabilization (OutStream, nTabDepth + 1, pCdmvSecPrisJntData);
	}

	OutputSecondaryJointParameters (OutStream, nTabDepth + 1, pCdmvSecPrisJntData);
	OutputSecPrismaticJointParameters (OutStream, nTabDepth + 1, pCdmvSecPrisJntData);

	OutStream << LPCTSTR(TabCount (nTabDepth)) << "}" << endl;
}

void CGenerateDMConfigFile::OutputSecRevoluteJoint(ostream &OutStream, int nTabDepth, const CdmvSecRevJntData *pCdmvSecRevJntData)
{
	ASSERT (pCdmvSecRevJntData);

	if (pCdmvSecRevJntData->GetSoftOrHard () == SOFT_SEC_JOINT)
	{
		OutStream << LPCTSTR(TabCount (nTabDepth)) << "SoftRevoluteJoint {" << endl;
		OutStream << LPCTSTR(TabCount (nTabDepth + 1)) << "Name" << "\t\t" << "\"" <<
			LPCTSTR(pCdmvSecRevJntData->GetName ()) << "\"" << endl;
	}
	else
	{
		OutStream << LPCTSTR(TabCount (nTabDepth)) << "HardRevoluteJoint {" << endl;
		OutStream << LPCTSTR(TabCount (nTabDepth + 1)) << "Name" << "\t\t" << "\"" <<
			LPCTSTR(pCdmvSecRevJntData->GetName ()) << "\"" << endl;
		OutputStabilization (OutStream, nTabDepth + 1, pCdmvSecRevJntData);
	}

	OutputSecondaryJointParameters (OutStream, nTabDepth + 1, pCdmvSecRevJntData);
	OutputSecRevoluteJointParameters (OutStream, nTabDepth + 1, pCdmvSecRevJntData);

	OutStream << LPCTSTR(TabCount (nTabDepth)) << "}" << endl;
}

void CGenerateDMConfigFile::OutputSecSphericalJoint(ostream &OutStream, int nTabDepth, const CdmvSecSpherJntData *pCdmvSecSpherJntData)
{
	ASSERT (pCdmvSecSpherJntData);

	if (pCdmvSecSpherJntData->GetSoftOrHard () == SOFT_SEC_JOINT)
	{
		OutStream << LPCTSTR(TabCount (nTabDepth)) << "SoftSphericalJoint {" << endl;
		OutStream << LPCTSTR(TabCount (nTabDepth + 1)) << "Name" << "\t\t" << "\"" <<
			LPCTSTR(pCdmvSecSpherJntData->GetName ()) << "\"" << endl;
	}
	else
	{
		OutStream << LPCTSTR(TabCount (nTabDepth)) << "HardSphericalJoint {" << endl;
		OutStream << LPCTSTR(TabCount (nTabDepth + 1)) << "Name" << "\t\t" << "\"" <<
			LPCTSTR(pCdmvSecSpherJntData->GetName ()) << "\"" << endl;
		OutputStabilization (OutStream, nTabDepth + 1, pCdmvSecSpherJntData);
	}

	OutputSecondaryJointParameters (OutStream, nTabDepth + 1, pCdmvSecSpherJntData);
	OutputSecSphericalJointParameters (OutStream, nTabDepth + 1, pCdmvSecSpherJntData);

	OutStream << LPCTSTR(TabCount (nTabDepth)) << "}" << endl;
}

void CGenerateDMConfigFile::OutputSecondaryJointParameters(ostream &OutStream, int nTabDepth, const CdmvSecJointData *pCdmvSecJointData)
{
	ASSERT (pCdmvSecJointData);

	structSecondaryJointParameters strtSecondaryJointParameters;
	pCdmvSecJointData->GetSecondaryJointParameters (&strtSecondaryJointParameters);

	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Link_A_Name" << "\t" << "\"" << 
		LPCTSTR(strtSecondaryJointParameters.pLinkA->GetName ()) << "\"" << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Link_B_Name" << "\t" << "\"" << 
		LPCTSTR(strtSecondaryJointParameters.pLinkB->GetName ()) << "\"" << endl;
	OutStream << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Joint_A_Position" << "\t" << 
		strtSecondaryJointParameters.cvPositionA[0] << '\t' <<
		strtSecondaryJointParameters.cvPositionA[1] << '\t' <<
		strtSecondaryJointParameters.cvPositionA[2] << '\t' <<
		endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Rotation_Matrix_A" << "\t" << 
		strtSecondaryJointParameters.rmRotationA[0][0] << '\t' <<
		strtSecondaryJointParameters.rmRotationA[0][1] << '\t' <<
		strtSecondaryJointParameters.rmRotationA[0][2] << '\t' <<
		endl <<
		LPCTSTR(TabCount (nTabDepth)) << "\t\t\t" <<
		strtSecondaryJointParameters.rmRotationA[1][0] << '\t' <<
		strtSecondaryJointParameters.rmRotationA[1][1] << '\t' <<
		strtSecondaryJointParameters.rmRotationA[1][2] << '\t' <<
		endl <<
		LPCTSTR(TabCount (nTabDepth)) << "\t\t\t" <<
		strtSecondaryJointParameters.rmRotationA[2][0] << '\t' <<
		strtSecondaryJointParameters.rmRotationA[2][1] << '\t' <<
		strtSecondaryJointParameters.rmRotationA[2][2] << '\t' <<
		endl;
	OutStream << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Joint_B_Position" << "\t" << 
		strtSecondaryJointParameters.cvPositionB[0] << '\t' <<
		strtSecondaryJointParameters.cvPositionB[1] << '\t' <<
		strtSecondaryJointParameters.cvPositionB[2] << '\t' <<
		endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Rotation_Matrix_B" << "\t" << 
		strtSecondaryJointParameters.rmRotationB[0][0] << '\t' <<
		strtSecondaryJointParameters.rmRotationB[0][1] << '\t' <<
		strtSecondaryJointParameters.rmRotationB[0][2] << '\t' <<
		endl <<
		LPCTSTR(TabCount (nTabDepth)) << "\t\t\t" <<
		strtSecondaryJointParameters.rmRotationB[1][0] << '\t' <<
		strtSecondaryJointParameters.rmRotationB[1][1] << '\t' <<
		strtSecondaryJointParameters.rmRotationB[1][2] << '\t' <<
		endl <<
		LPCTSTR(TabCount (nTabDepth)) << "\t\t\t" <<
		strtSecondaryJointParameters.rmRotationB[2][0] << '\t' <<
		strtSecondaryJointParameters.rmRotationB[2][1] << '\t' <<
		strtSecondaryJointParameters.rmRotationB[2][2] << '\t' <<
		endl;
	OutStream << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Joint_Friction" << "\t" << 
		strtSecondaryJointParameters.FJointFriction << endl;
	OutStream << endl;
	
}

void CGenerateDMConfigFile::OutputSecPrismaticJointParameters(ostream &OutStream, int nTabDepth, const CdmvSecPrisJntData *pCdmvSecPrisJntData)
{
	ASSERT (pCdmvSecPrisJntData);

	structSecondaryPrismaticJointData strtSecondaryPrismaticJointData;
	pCdmvSecPrisJntData->GetSecPrismaticJointData (&strtSecondaryPrismaticJointData);

	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Position_Constraint_Spring" << "\t" << 
		strtSecondaryPrismaticJointData.dLinearConstraintSpring << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Position_Constraint_Damper" << "\t" << 
		strtSecondaryPrismaticJointData.dLinearConstraintDamper << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Orientation_Constraint_Spring" << "\t" << 
		strtSecondaryPrismaticJointData.dAngularConstraintSpring << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Orientation_Constraint_Damper" << "\t" << 
		strtSecondaryPrismaticJointData.dAngularConstraintDamper << endl;
}

void CGenerateDMConfigFile::OutputSecSphericalJointParameters(ostream &OutStream, int nTabDepth, const CdmvSecSpherJntData *pCdmvSecSpherJntData)
{
	ASSERT (pCdmvSecSpherJntData);
	
	structSecondarySphericalJointData strtSecondarySphericalJointData;
	pCdmvSecSpherJntData->GetSecSphericalJointData (&strtSecondarySphericalJointData);

	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Position_Constraint_Spring" << "\t" << 
		strtSecondarySphericalJointData.dLinearConstraintSpring << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Position_Constraint_Damper" << "\t" << 
		strtSecondarySphericalJointData.dLinearConstraintDamper << endl;
}

void CGenerateDMConfigFile::OutputSecRevoluteJointParameters(ostream &OutStream, int nTabDepth, const CdmvSecRevJntData *pCdmvSecRevJntData)
{
	ASSERT (pCdmvSecRevJntData);
	
	structSecondaryRevoluteJointData strtSecondaryRevoluteJointData;
	pCdmvSecRevJntData->GetSecRevoluteJointData (&strtSecondaryRevoluteJointData);

	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Position_Constraint_Spring" << "\t" << 
		strtSecondaryRevoluteJointData.dLinearConstraintSpring << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Position_Constraint_Damper" << "\t" << 
		strtSecondaryRevoluteJointData.dLinearConstraintDamper << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Orientation_Constraint_Spring" << "\t" << 
		strtSecondaryRevoluteJointData.dAngularConstraintSpring << endl;
	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Orientation_Constraint_Damper" << "\t" << 
		strtSecondaryRevoluteJointData.dAngularConstraintDamper << endl;
}

void CGenerateDMConfigFile::OutputStabilization(ostream &OutStream, int nTabDepth, const CdmvSecJointData *pCdmvSecJointData)
{
	ASSERT (pCdmvSecJointData);


	CString strStabilization;

	switch (pCdmvSecJointData->GetStabilizationType ())
	{
	case STABILIZATION_NONE:
		strStabilization = "NONE";
		break;
	case STABILIZATION_BAUMGARTE:
		strStabilization = "BAUMGARTE";
		break;
	case STABILIZATION_SPRING_DAMPER:
		strStabilization = "SPRING_DAMPER";
		break;
	default:
		ASSERT (FALSE);
		break;
	}

	OutStream << LPCTSTR(TabCount (nTabDepth)) << "Stabilization" << "\t" << LPCTSTR(strStabilization) << endl;
	OutStream << endl;
}

void CGenerateDMConfigFile::OutputVersion(ostream &OutStream)
{
	OutStream << "Version 1" << endl << endl;
}
