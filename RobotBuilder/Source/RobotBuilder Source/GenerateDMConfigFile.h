// GenerateDMConfigFile.h: interface for the CGenerateDMConfigFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERATEDMCONFIGFILE_H__17D90131_F376_11D3_8423_00C04F666666__INCLUDED_)
#define AFX_GENERATEDMCONFIGFILE_H__17D90131_F376_11D3_8423_00C04F666666__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CdmvSystemData;


#include "dmvSystemData.h"
#include "dmvArticulationData.h"
#include "dmvSecJointData.h"
#include "dmvSecPrisJntData.h"
#include "dmvSecSpherJntData.h"
#include "dmvSecRevJntData.h"
#include "dmvLinkData.h"
#include "dmvZScrewTxLinkData.h"
#include "dmvRevoluteLinkData.h"
#include "dmvMobileBaseLinkData.h"
#include "dmvRigidBodyData.h"
#include "dmvRevDCMotorData.h"
#include "dmvPrismaticLinkData.h"
#include "dmvStaticRootLinkData.h"
#include "dmvSphericalLinkData.h"

#include <fstream> // for ostream
using namespace std; 

class CGenerateDMConfigFile  
{
public:
	static BOOL CreateDMConfigFile (CString strFilePath, CdmvSystemData* pSystem);
	CGenerateDMConfigFile();
	virtual ~CGenerateDMConfigFile();

protected:
	static void OutputStabilization (ostream &OutStream, int nTabDepth, const CdmvSecJointData* pCdmvSecJointData);
	static void OutputSecRevoluteJointParameters (ostream &OutStream, int nTabDepth, const CdmvSecRevJntData* pCdmvSecRevJntData);
	static void OutputSecSphericalJointParameters (ostream &OutStream, int nTabDepth, const CdmvSecSpherJntData* pCdmvSecSpherJntData);
	static void OutputSecPrismaticJointParameters (ostream &OutStream, int nTabDepth, const CdmvSecPrisJntData* pCdmvSecPrisJntData);
	static void OutputSecondaryJointParameters (ostream &OutStream, int nTabDepth, const CdmvSecJointData* pCmdvSecJointData);
	static void OutputSecSphericalJoint (ostream &OutStream, int nTabDepth, const CdmvSecSpherJntData* pCdmvSecSpherJntData);
	static void OutputSecRevoluteJoint (ostream &OutStream, int nTabDepth, const CdmvSecRevJntData* pCdmvSecRevJntData);
	static void OutputSecPrismaticJoint (ostream &OutStream, int nTabDepth, const CdmvSecPrisJntData* pCdmvSecPrisJntData);
	static void OutputSecondaryJoint (ostream &OutStream, int nTabDepth, const CdmvSecJointData* pCdmvSecJointData);
	static void OutputSecondaryJointList (ostream& OutStream, int nTabDepth, const CdmvArticulationData* pCdmvClosedArticulationData);
	static BOOL GetNextTopLevelNode (const CdmvSystemData *pSystem, int nCurrent, int *pnNextTop);
	static void OutputRevDCMotor (ostream &OutStream, int nTabDepth, const CdmvRevDCMotorData* pCdmvRevDCMotorData);
	static void OutputJointFriction (ostream &OutStream, int nTabDepth, const CdmvLinkData* pCdmvLinkData);
	static void OutputActuator (ostream &OutStream, int nTabDepth, const CdmvRevoluteLinkData * pCdmvRevoluteLinkData);
	static void OutputMDHParameters (ostream &OutStream, int nTabDepth, const CdmvMDHLinkData* pCdmvMDHLinkData);
	static void OutputMobileBaseParameters (ostream& OutStream, int nTabDepth, const CdmvMobileBaseLinkData* pCdmvMobileBaseLinkData);
	static void OutputContactParameters (ostream& OutStream, int nTabDepth, const CdmvContactModelData* pCdmvContactModelData);
	static void OutputRigidBodyParameters (ostream & OutStream, int nTabDepth, const CdmvRigidBodyData* pCdmvRigidBodyData);
	static void OutputObjectData (ostream& OutStream, int nTabDepth, const CdmvObject* pCdmvObject);
	static CString TabCount(int nNumTabs);
	static void OutputFileHeader (ostream &OutStream, const CdmvSystemData* pSysterm);
	static void BuildBranch (const CdmvSystemData * pSystem, int nCurrentLinkIndex, int nCurrentTab, 
										ostream &OutStream, int nLastIndex);
	static BOOL IsBranchParent (const CdmvSystemData * pSystem, int nPotentialParentIndex,
										   int nStartLinkIndex,
										   int *pnNextBranchIndex);
	static void OutputArticulation (ostream &OutStream, int nTabDepth, const CdmvArticulationData* 
						 pCdmvArticulationData);
	static void OutputLink (ostream &OutStream, int nTabDepth, const CdmvLinkData* 
						 pCdmvLinkData);
	static void OutputZScrewTxLink (ostream &OutStream, int nTabDepth, const CdmvZScrewTxLinkData* 
						 pCdmvZScrewTxLinkData);
	static void OutputRevoluteLink (ostream &OutStream, int nTabDepth, const CdmvRevoluteLinkData* 
						 pCdmvRevoluteLinkData);
	static void OutputMobileBaseLink (ostream &OutStream, int nTabDepth, const CdmvMobileBaseLinkData* 
						 pCdmvMobileBaseLinkData);
	static void OutputPrismaticLink (ostream &OutStream, int nTabDepth, const CdmvPrismaticLinkData* 
						 pCdmvPrismaticLinkData);
	static void OutputStaticRootLink (ostream &OutStream, int nTabDepth, const CdmvStaticRootLinkData* 
						 pCdmvStaticRootLinkData);
	static void OutputSphericalLink (ostream &OutStream, int nTabDepth, const CdmvSphericalLinkData* 
						 pCdmvSphericalLinkData);
	static void OutputSphericalParameters (ostream &OutStream, int nTabDepth, const CdmvSphericalLinkData* 
						 pCdmvSphericalLinkData);
	static void OutputVersion (ostream &OutStream);
private:
};

#endif // !defined(AFX_GENERATEDMCONFIGFILE_H__17D90131_F376_11D3_8423_00C04F666666__INCLUDED_)
