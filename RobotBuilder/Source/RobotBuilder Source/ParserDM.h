// ParserDM.h: interface for the CParserDM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSERDM_H__B1595620_0773_4C66_9C3F_F21B121112AE__INCLUDED_)
#define AFX_PARSERDM_H__B1595620_0773_4C66_9C3F_F21B121112AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParserGeneral.h"
#include "dmvSystemData.h"
#include "dmvArticulationData.h"
#include "dmvObject.h"
#include "dmvRigidBodyData.h"
#include "dmvMobileBaseLinkData.h"
#include "dmvMDHLinkData.h"
#include "dmvRevoluteLinkData.h"
#include "dmvRevDCMotorData.h"
#include "dmvSphericalLinkData.h"
#include "dmvZScrewTxLinkData.h"
#include "dmvSecJointData.h"
#include "dmvSecRevJntData.h"
#include "dmvSecPrisJntData.h"
#include "dmvSecSpherJntData.h"


enum actuatorTypes {NOMOTOR = 0, DCMOTOR = 1};


class CParserDM : public CParserGeneral  
{
public:
	CParserDM();
	virtual ~CParserDM();
	static BOOL ParseDMFile(CString strFile, CdmvSystemData **ppCdmvSystemData);

private:
	static BOOL ParseJointFriction(ifstream &istrmDMFile, int &rnCurrentLineNumber, 
				CdmvSystemData **ppCdmvSystemData, CdmvSecJointData *pCdmvSecJointData);
	static BOOL ParseSecondarySphericalJoint (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvSecSpherJntData *pCdmvSecSpherJntData);
	static BOOL ParseSecondaryPrismaticJoint (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvSecPrisJntData *pCdmvSecPrisJntData);
	static BOOL ParseSecondaryRevoluteJoint (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvSecRevJntData *pCdmvSecRevJntData);
	static BOOL ParseSecondaryJointData (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvArticulationData *pCdmvClosedArticulationData, CdmvSecJointData *pCdmvSecJointData);
	static BOOL ParseStabilization (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvSecJointData *pCdmvSecJointData);
	static BOOL ParseSecondaryJoints (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvArticulationData *pCdmvClosedArticulationData);
	static BOOL ParseZScrewTxLinkParameters (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvZScrewTxLinkData *pCdmvZScrewTxLinkData);
	static BOOL ParseSphericalLinkParameters (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvSphericalLinkData *pCdmvSphericalLinkData);
	static BOOL ParseRevDCMotorParameters (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvRevDCMotorData* pCdmvRevDCMotorData);
	static BOOL ParseJointFriction (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvLinkData* pCdmvLinkData);
	static BOOL ParseActuator (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvRevoluteLinkData* pCdmvRevoluteLinkData);
	static BOOL ParseMDHParameters (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvMDHLinkData* pCdmvMDHLinkData);
	static BOOL ParseContactParameters (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvRigidBodyData* pCdmvRigidBodyData);
	static BOOL ParseMobileBaseParameters (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData, CdmvMobileBaseLinkData *pCdmvMobileBaseLinkData);
	static BOOL ParseRigidBodyParameters (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvRigidBodyData* pCdmvRigidBodyData);
	static BOOL ParseToBlockEnd (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData);
	static BOOL ParseName (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData **ppCdmvSystemData, CdmvObject *pCdmvObject);
	static BOOL ParseToBlockBegin (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData);
	static BOOL ParseLinkBranch (ifstream & istrmDMFile, int & rnCurrentLineNumber, CdmvSystemData** ppCdmvSystemData, CdmvLinkData* pCdmvLinkData);
	static BOOL ParseArticulationPose (ifstream &strmDMFile, int & rnCurrentLineNumber,
		CdmvSystemData **ppCdmvSystemData, CdmvArticulationData *pCdmvArticulationData);
	static BOOL ParseGraphicsFile (ifstream & istrmDMFile, int & rnCurrentLineNumber, 
		CdmvSystemData **ppCdmvSystemData, CdmvObject *pCdmvObject);
	static BOOL ParseClosedArticulation (ifstream & istrmDMFile, int & rnCurrentLineNumber, 
		CdmvSystemData **ppCdmvSystemData);
	static BOOL ParseArticulation (ifstream & istrmDMFile, int & rnCurrentLineNumber, 
		CdmvSystemData **ppCdmvSystemData);
	static BOOL ParseFileVersion1 (ifstream & istrmDMFile, int & rnCurrentLineNumber, 
		CdmvSystemData **ppCdmvSystemData);
	static void FormatError (ifstream & istrmDMFile, int nCurrentLineNumber, 
		CdmvSystemData** ppCdmvSystemData, CString strMessage);
	static void ParseError (ifstream & istrmDMFile, int nCurrentLineNumber, 
		CdmvSystemData** ppCdmvSystemData, CString strMessage);
	static void ValidationError(ifstream &istrmDMFile, int nCurrentLineNumber, 
		CdmvSystemData** ppCdmvSystemData, CString strMessage);
};

#endif // !defined(AFX_PARSERDM_H__B1595620_0773_4C66_9C3F_F21B121112AE__INCLUDED_)
