// dmvRevoluteLinkData.h: interface for the CdmvRevoluteLinkData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVREVOLUTELINKDATA_H__75A06B61_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVREVOLUTELINKDATA_H__75A06B61_DBFE_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvMDHLinkData.h"
#include "dmvActuatorData.h"

class CdmvRevoluteLinkData : public CdmvMDHLinkData  
{
public:
	CdmvRevoluteLinkData (const CdmvRevoluteLinkData& rCdmvRevoluteLinkData);
	void DeleteActuator ();
	CdmvActuatorData* GetActuator () const;
	void SetActuator (CdmvActuatorData* pActuator);
	CdmvRevoluteLinkData();
	virtual ~CdmvRevoluteLinkData();
protected:
	CdmvActuatorData* m_pActuator;

};

#endif // !defined(AFX_DMVREVOLUTELINKDATA_H__75A06B61_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
