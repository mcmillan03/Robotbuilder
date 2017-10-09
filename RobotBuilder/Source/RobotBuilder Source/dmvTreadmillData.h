// dmvTreadmillData.h: interface for the CdmvTreadmillData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVTREADMILLDATA_H__C8FE66B5_99D5_4067_880E_BB43A92D518D__INCLUDED_)
#define AFX_DMVTREADMILLDATA_H__C8FE66B5_99D5_4067_880E_BB43A92D518D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TREADMILL_WIDTH_MIN	WTK_MIN
#define TREADMILL_WIDTH_MAX	1.0e6
#define TREADMILL_LENGTH_MIN	WTK_MIN
#define TREADMILL_LENGTH_MAX	1.0e6

#include "dmvEnvironmentData.h"
#include "dm.h"	// Added by ClassView

typedef struct
{
	CartesianVector cvPosition;
	CartesianVector cvVelocityDirection;
	CartesianVector cvNormal;
	double dVelocityMagnitude;
	double dLength;
	double dWidth;
	COLORREF crColor;
} structEnvTreadmillData;


class CdmvTreadmillData : public CdmvEnvironmentData
{
public:
	Float GetVelocityMagnitude () const;
	COLORREF GetColor () const;
	void GetVelocityDirection (CartesianVector cvVelocity) const;
	void GetNormal (CartesianVector cvNormal) const;
	void ResetTreadmillData ();
	void SetColor (COLORREF crColor);
	void SetVelocityMagnitude (Float fVelocityMagnitude);
	static BOOL ValidateNormalAndVelocity (const CartesianVector cvNormal, const CartesianVector cvVelocity);
	void SetLength (Float fLength);
	void SetPosition (const CartesianVector cvPosition);
	void SetNormalAndVelocityDirection (CartesianVector cvNormal, CartesianVector cvVelocity);
	void SetWidth (Float fWidth);
	void SetParameters (const structEnvTreadmillData* pstrtEnvTreadmillData);
	void GetParameters (structEnvTreadmillData* pstrtEnvTreadmillData) const;
	void GetPosition (CartesianVector & rcvPosition) const;
	double GetLength () const;
	double GetWidth () const;
	CdmvTreadmillData();
	virtual ~CdmvTreadmillData();

//	BOOL ParseTreadmillFile (CString strFile);
protected:
	COLORREF m_crTreadmillColor;
	double m_dVelocityMag;
	double m_dLength;
	double m_dWidth;
	CartesianVector m_cvPosition;
	CartesianVector m_cvVelocity;
	CartesianVector m_cvNormal;
};



#endif // !defined(AFX_DMVTREADMILLDATA_H__C8FE66B5_99D5_4067_880E_BB43A92D518D__INCLUDED_)
