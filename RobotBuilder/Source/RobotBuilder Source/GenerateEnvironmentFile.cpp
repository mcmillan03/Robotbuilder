// GenerateEnvironmentFile.cpp: implementation of the CGenerateEnvironmentFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "GenerateEnvironmentFile.h"
#include "dmvTreadmillData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGenerateEnvironmentFile::CGenerateEnvironmentFile()
{

}

CGenerateEnvironmentFile::~CGenerateEnvironmentFile()
{

}

BOOL CGenerateEnvironmentFile::CreateEnvironmentFile(CString strFilePath, CdmvEnvironmentData *pEnvironment)
{
	ofstream strmEnvironmentFile;
	strmEnvironmentFile.open (strFilePath);
	int nIsOpen = strmEnvironmentFile.is_open ();
	if (!nIsOpen)
		return FALSE;
 	ASSERT (strmEnvironmentFile != NULL);

	OutputFileHeader (strmEnvironmentFile, pEnvironment);

	structEnvironmentData strtEnvironmentData;
	pEnvironment->GetEnvironmentData (&strtEnvironmentData);

	// Specify the environment type by the details file
	if (typeid (*pEnvironment) == typeid (CdmvTreadmillData))
	{
		strmEnvironmentFile << "Environment_Type" << "\t" << "TREADMILL" << endl;
	}
	else
	{
		strmEnvironmentFile << "Environment_Type" << "\t" << "TERRAIN" << endl;
	}


	strmEnvironmentFile << "Gravity_Vector" << "\t\t" << 
		strtEnvironmentData.cvGravity[0] << "\t" <<
		strtEnvironmentData.cvGravity[1] << "\t" <<
		strtEnvironmentData.cvGravity[2] << endl;

	// Specify the environment type by the details file

	strmEnvironmentFile << "Data_Filename"  << "\t\t" <<
		"\"" << LPCTSTR(strtEnvironmentData.strDataFile) << "\"" << endl << endl;
	strmEnvironmentFile << "Ground_Planar_Spring_Constant" << "\t\t" <<
		strtEnvironmentData.fGroundPlanarSpringConstant << endl;
	strmEnvironmentFile << "Ground_Normal_Spring_Constant" << "\t\t" <<
		strtEnvironmentData.fGroundNormalSpringConstant<< endl;
	strmEnvironmentFile << "Ground_Planar_Damper_Constant" << "\t\t" <<
		strtEnvironmentData.fGroundPlanarDamperConstant << endl;
	strmEnvironmentFile << "Ground_Normal_Damper_Constant" << "\t\t" <<
		strtEnvironmentData.fGroundNormalDamperConstant << endl << endl;

	strmEnvironmentFile << "Ground_Static_Friction_Coeff" << "\t\t" <<
		strtEnvironmentData.fu_s<< endl;
	strmEnvironmentFile << "Ground_Kinetic_Friction_Coeff" << "\t\t" <<
		strtEnvironmentData.fu_k << endl << endl;

	strmEnvironmentFile.close ();

	return TRUE;		
}

void CGenerateEnvironmentFile::OutputFileHeader(ostream &strmEnvironmentFile, CdmvEnvironmentData *pEnvironment)
{
	strmEnvironmentFile << "# Environment File" << endl << endl;
}
