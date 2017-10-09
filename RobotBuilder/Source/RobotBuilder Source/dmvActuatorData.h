// dmvActuatorData.h: interface for the CdmvActuatorData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVACTUATORDATA_H__75A06B63_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVACTUATORDATA_H__75A06B63_DBFE_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvObject.h"

// to know the Actuator type
typedef enum {NO_MOTOR, REV_DC_MOTOR} ActuatorType;


class CdmvActuatorData : public CdmvObject  
{
public:
//	void SetActuatorType (ActuatorType Actuator);
	ActuatorType GetActuatorType () const;
	CdmvActuatorData();
	virtual ~CdmvActuatorData();
protected:
	ActuatorType m_ActuatorType;
};

#endif // !defined(AFX_DMVACTUATORDATA_H__75A06B63_DBFE_11D3_A7DF_0000E8978554__INCLUDED_)
