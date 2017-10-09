// dmvSystemData.h: interface for the CdmvSystemData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVSYSTEMDATA_H__36B36FBF_DB1C_11D3_8421_B909FA2E8733__INCLUDED_)
#define AFX_DMVSYSTEMDATA_H__36B36FBF_DB1C_11D3_8421_B909FA2E8733__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "dmvObject.h"
//#include "dmvArticulationData.h"

class CdmvSystemData : public CdmvObject
{
public:
//	CdmvArticulationData* GetArticulation () const;
//	void setArticulation (CdmvArticulationData* pArticulation);
	CdmvSystemData();
	virtual ~CdmvSystemData();
protected:
//	CdmvArticulationData* m_pArticulation;

};

#endif // !defined(AFX_DMVSYSTEMDATA_H__36B36FBF_DB1C_11D3_8421_B909FA2E8733__INCLUDED_)
