// dmvObject.cpp: implementation of the CdmvObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmvObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdmvObject::CdmvObject():
m_bUseRbmData (FALSE)
{
	m_strName = "";
	m_strGraphicsFile = "";
	m_strGraphicsPath = "";
	m_ObjectType = NOT_SUPPORTED;
	m_pWtkNode = NULL;
	m_pWtkGeometryNode = NULL;
	m_pDynaMechsObject = NULL;
	m_bShowWtkAxes = FALSE;
	m_bCameraCenterOfInterest = FALSE;
}

CdmvObject::~CdmvObject()
{
	
}

void CdmvObject::SetName(const char* szName)
{
	m_strName = szName;
}

void CdmvObject::SetGraphicsModel(CString strGraphicsFile, CString strGraphicsPath)
{
	// save the model's path
	m_strGraphicsFile = strGraphicsFile;	
	m_strGraphicsPath = strGraphicsPath;
}

void CdmvObject::GetGraphicsModel (CString &rstrGraphicsFile, CString &rstrGraphicsPath) const
{
	rstrGraphicsFile = m_strGraphicsFile;
	rstrGraphicsPath = m_strGraphicsPath;
}

CString CdmvObject::GetName() const
{
	return m_strName;
}

ObjectType CdmvObject::GetObjectType() const
{
	return m_ObjectType;
}

void CdmvObject::SetWtkNode(WTnode *pWtkNode)
{

	m_pWtkNode = pWtkNode;
}

WTnode* CdmvObject::GetWtkNode()
{
	return m_pWtkNode;
}

void CdmvObject::SetDynaMechsObject(dmObject *pdmObject)
{
	m_pDynaMechsObject = pdmObject;
}

dmObject* CdmvObject::GetDynaMechsObject()
{
	return m_pDynaMechsObject;
}

// Save the node that contains the graphical representation
void CdmvObject::SetWtkGeometryNode(WTnode *pWtkGeometryNode)
{
	m_pWtkGeometryNode = pWtkGeometryNode;
}

WTnode* CdmvObject::GetWtkGeometryNode()
{
	return m_pWtkGeometryNode;
}

CdmvObject::CdmvObject(const CdmvObject &dmvObject)
{
	m_ObjectType = dmvObject.GetObjectType ();
	m_strName = dmvObject.GetName ();
	dmvObject.GetGraphicsModel (m_strGraphicsFile, m_strGraphicsPath);
	// This object needs to have its own copy of WTK and DynaMechs pointers
	m_pDynaMechsObject = NULL;
	m_pWtkGeometryNode = NULL;
	m_pWtkNode = NULL;
	m_bShowWtkAxes = dmvObject.ShowWtkAxes ();
	m_bCameraCenterOfInterest = FALSE;
}

void CdmvObject::ShowWtkAxes(BOOL bShow)
{
	m_bShowWtkAxes = bShow;
}

BOOL CdmvObject::ShowWtkAxes() const
{
	return m_bShowWtkAxes;
}

BOOL CdmvObject::IsCameraCenterOfInterest() const
{
	return m_bCameraCenterOfInterest;
}

void CdmvObject::IsCameraCenterOfInterest(BOOL bIsCOI)
{
	m_bCameraCenterOfInterest = bIsCOI;
}

// Sets whether to use the physical parameter data (center of gravity, mass,
// and inertia) is from the Rbm graphic file.  Note that this is only set if the 
// graphic file is a .rbm and it was successfully parsed.
void CdmvObject::UseRbmData(BOOL bUseRbmData)
{
	m_bUseRbmData = bUseRbmData;
}

// See note for UseRbmData above
BOOL CdmvObject::UseRbmData() const
{
	return m_bUseRbmData;
}
