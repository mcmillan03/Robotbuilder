// dmvArticulationData.h: interface for the CdmvArticulationData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVARTICULATIONDATA_H__32B7BEF2_DB46_11D3_8421_B909FA2E8733__INCLUDED_)
#define AFX_DMVARTICULATIONDATA_H__32B7BEF2_DB46_11D3_8421_B909FA2E8733__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "dmvLinkData.h"
#include "dmvSystemData.h"
#include "dmvSecJointData.h"
#include "resource.h"


//class CdmvSystemData;

//typedef struct
//{
//	CdmvLinkData* pLink;
//	CdmvLinkData* pLinkParent;
//	WTnode* wtnodeLink;
//} structLinkPointer;

// a container class to hold link data
class CdmvLinkPointer
{
public:
	CdmvLinkData* pLink;
	CdmvLinkData* pLinkParent;
};

typedef enum {OPEN_ARTICULATION, CLOSED_ARTICULATION} ArticulationType;

class CdmvArticulationData : public CdmvSystemData
{
public:
	void ClearCameraCenterOfInterest ();
	WTnode* GetCameraCenterOfInterest ();
	int GetNumberOfLinks () const;
	// enumerate validation errors
	enum {ART_ERROR_NONE, ART_ERROR_TOO_MANY_STATIC_ROOT_LINK, ART_ERROR_STATIC_ROOT_LINK_BAD_PLACE};

	int GetNumberOfStaticRootLinks () const;
	int ValidateArticulation () const;
	void InsertLinkAsParent (CdmvLinkData* pNewLink, CdmvLinkData *pOldLink);
	void CopyLink (CdmvLinkData* pLink, CdmvLinkData **ppNewLink);
	void CutLink (CdmvLinkData *pLink);
	CdmvLinkData* FindLinkByName (CString strName) const;
	ArticulationType GetArticulationType () const;
	void DeleteLinkRecursively (CdmvLinkData *pLink);
	void DeleteLink (CdmvLinkData* pLink);
	void InsertLinkSibling (CdmvLinkData* pLink, CdmvLinkData* pLinkParent);
	void InsertLinkChild (CdmvLinkData* pLink, CdmvLinkData* pLinkParent);
	void GetRefSystem (Quaternion quat, CartesianVector pos) const;
	void AddLink (CdmvLinkData * pLink, CdmvLinkData * pLinkParent);
	void SetReferenceSystem (Quaternion quat, CartesianVector pos);
	CdmvArticulationData();
	virtual ~CdmvArticulationData();
	CArray <CdmvLinkPointer, CdmvLinkPointer> m_arrayLinks;
	CString GetCenterOfInterestName();
	
	// Closed loop functions
	void AddHardSecJoint (CdmvSecJointData* pSecJoint);
	void AddSoftSecJoint (CdmvSecJointData* pSecJoint);
	void DeleteSecJointsByLink (CdmvLinkData *pLinkData);
	void DeleteSecJoint (CdmvSecJointData *pSecJoint);
	void AddSecJoint (CdmvSecJointData* pSecJoint);
	CArray <CdmvSecJointData*, CdmvSecJointData*> m_arraySecondaryJoints;
protected:
	Quaternion m_qOrientation;
	CartesianVector m_cvPosition;
	ArticulationType m_ArticulationType;
};



#endif // !defined(AFX_DMVARTICULATIONDATA_H__32B7BEF2_DB46_11D3_8421_B909FA2E8733__INCLUDED_)
