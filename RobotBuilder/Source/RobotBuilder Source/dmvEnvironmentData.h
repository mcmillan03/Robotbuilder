// dmvEnvironmentData.h: interface for the CdmvEnvironmentData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVENVIRONMENTDATA_H__EAB38EC1_148C_11D4_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVENVIRONMENTDATA_H__EAB38EC1_148C_11D4_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dm.h>
#include "dmvObject.h"

#define ENV_PLANAR_SPRING_MIN	0.0
#define ENV_PLANAR_SPRING_MAX	1.0e6
#define ENV_PLANAR_DAMPER_MIN	0.0
#define ENV_PLANAR_DAMPER_MAX	1.0e6
#define ENV_NORMAL_SPRING_MIN	0.0
#define ENV_NORMAL_SPRING_MAX	1.0e6
#define ENV_NORMAL_DAMPER_MIN	0.0
#define ENV_NORMAL_DAMPER_MAX	1.0e6
#define ENV_STATIC_FRICTION_MIN	0.0
#define ENV_STATIC_FRICTION_MAX	1.0e6
#define ENV_KINETIC_FRICTION_MIN	0.0
#define ENV_KINETIC_FRICTION_MAX	1.0e6

typedef enum {ENV_TERRAIN, ENV_TREADMILL} enumEnvironmentType;

typedef struct
{
	enumEnvironmentType eEnvironmentType;
	CartesianVector cvGravity;
	CString strDataFile;
	CString strDataPath;
	Float fGroundPlanarSpringConstant;
	Float fGroundNormalSpringConstant;
	Float fGroundPlanarDamperConstant;
	Float fGroundNormalDamperConstant;
	Float fu_s;
	Float fu_k;
} structEnvironmentData;

class CdmvEnvironmentData  : public CdmvObject
{
public:
	enumEnvironmentType GetEnvironmentType () const;
	//	BOOL ParseEnvironmentFile (CString strFile);
	void GetDataFile (CString & rstrFile, CString & rstrPath);
	void SetEnvironmentData (const structEnvironmentData* pstrtEnvironmentData);
	void GetEnvironmentData (structEnvironmentData* pstrtEnvironmentData) const;
	void SetCoefficientStaticFriction(Float u_s);
	void SetCoefficientKineticFriction(Float u_k);
	void SetGroundNormalDamperConstant (Float fDamperConstant);
	void SetGroundPlanarDamperConstant (Float fDamperConstant);
	void SetGroundNormalSpringConstant (Float fSpringConstant);
	void SetGroundPlanarSpringConstant (Float fSpringConstant);
	void SetDataFile (CString strTerrainFile, CString strPath);
	void SetGravity (CartesianVector cv);
	CdmvEnvironmentData();
	virtual ~CdmvEnvironmentData();
private:
	structEnvironmentData m_strtEnvironmentData;

protected:
	void SetEnvironmentType (enumEnvironmentType theEnvironmentType);
};

#endif // !defined(AFX_DMVENVIRONMENTDATA_H__EAB38EC1_148C_11D4_A7DF_0000E8978554__INCLUDED_)
