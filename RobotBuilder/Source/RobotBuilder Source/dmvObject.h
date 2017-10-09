// dmvObject.h: interface for the CdmvObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVOBJECT_H__32B7BEF3_DB46_11D3_8421_B909FA2E8733__INCLUDED_)
#define AFX_DMVOBJECT_H__32B7BEF3_DB46_11D3_8421_B909FA2E8733__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <dmObject.hpp>

#include <wt.h>

#include <dm.h>

typedef enum {ARTICULATION, LINK, SECONDARY_JOINT, NOT_SUPPORTED} ObjectType;

// design: I've kind of specialized this class.  I should create a WtkObject class
// with this as a base class, and derive all the objects that can have Wtk representations
// from it

class CdmvObject  
{
public:
	BOOL UseRbmData () const;
	void UseRbmData (BOOL bUseRbmData);
	void IsCameraCenterOfInterest (BOOL bIsCOI);
	BOOL IsCameraCenterOfInterest () const;
	BOOL ShowWtkAxes () const;
	void ShowWtkAxes (BOOL bShow);
	CdmvObject (const CdmvObject &dmvObject);
	WTnode* GetWtkGeometryNode ();
	void SetWtkGeometryNode (WTnode *pWtkGeometryNode);
	dmObject* GetDynaMechsObject ();
	void SetDynaMechsObject (dmObject *pdmObject);
	WTnode* GetWtkNode ();
	void SetWtkNode (WTnode* pWtkNode);
	ObjectType GetObjectType () const;
	CString GetName () const;
	void SetGraphicsModel (CString strGraphicsFile, CString strPath);
//	void setUserData (void* pData);
	void SetName (const char* szName);
	CdmvObject();
	virtual ~CdmvObject();
	void GetGraphicsModel (CString &rstrGraphicsFile, CString &rstrGraphicsPath) const;
protected:
	BOOL m_bUseRbmData;
	BOOL m_bShowWtkAxes;
	CString m_strGraphicsFile;
	CString m_strGraphicsPath;
	CString m_strName;
	ObjectType m_ObjectType;
	dmObject *m_pDynaMechsObject;
	WTnode *m_pWtkNode;
	WTnode *m_pWtkGeometryNode;
	BOOL m_bCameraCenterOfInterest;
};

#endif // !defined(AFX_DMVOBJECT_H__32B7BEF3_DB46_11D3_8421_B909FA2E8733__INCLUDED_)
