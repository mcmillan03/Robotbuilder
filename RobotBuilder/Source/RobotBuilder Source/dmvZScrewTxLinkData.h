// dmvZScrewTxLinkData.h: interface for the CdmvZScrewTxLinkData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVZSCREWTXLINKDATA_H__75A06B67_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVZSCREWTXLINKDATA_H__75A06B67_DBFE_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvLinkData.h"

typedef struct
{
	Float fD;
	Float fTheta;
} structZScrewTxLinkParameters;

class CdmvZScrewTxLinkData : public CdmvLinkData  
{
public:
	void SetJointParameters (double dD, double dTheta);
	void SetParameters (const structZScrewTxLinkParameters* pstrtZScrewTxLinkParameters);
	void GetParameters (structZScrewTxLinkParameters* pstrtZScrewTxLinkParameters) const;
	virtual BOOL GetLinkParameters (Float* fMDHParameters);
	CdmvZScrewTxLinkData();
	CdmvZScrewTxLinkData(Float fD, Float fTheta);
	virtual ~CdmvZScrewTxLinkData();
protected:
	structZScrewTxLinkParameters m_strtZScrewTxLinkParameters;

};

#endif // !defined(AFX_DMVZSCREWTXLINKDATA_H__75A06B67_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
