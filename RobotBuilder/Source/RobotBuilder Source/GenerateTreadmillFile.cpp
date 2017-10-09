// GenerateTreadmillFile.cpp: implementation of the CGenerateTreadmillFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "GenerateTreadmillFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGenerateTreadmillFile::CGenerateTreadmillFile()
{

}

CGenerateTreadmillFile::~CGenerateTreadmillFile()
{

}

BOOL CGenerateTreadmillFile::CreateTreadmillFile(CString strFile, const CdmvTreadmillData *pCdmvTreadmillData)
{
	ofstream ostrmTreadmillFile;
	ostrmTreadmillFile.open (strFile);
	int nIsOpen = ostrmTreadmillFile.is_open ();
	if (!nIsOpen)
	{
		AfxMessageBox ("Invalid file name.");
		return FALSE;
	}
 	ASSERT (ostrmTreadmillFile != NULL);

	ASSERT (pCdmvTreadmillData);

	// Pick up the data
	structEnvTreadmillData strtEnvTreadmillData;
	pCdmvTreadmillData->GetParameters (&strtEnvTreadmillData);

	// Output version
	ostrmTreadmillFile << "Version" << '\t' << 1 << endl << endl;

	// Normal Direction
	ostrmTreadmillFile << "Normal_Direction\t" <<
		strtEnvTreadmillData.cvNormal[0] << '\t' <<
		strtEnvTreadmillData.cvNormal[1] << '\t' <<
		strtEnvTreadmillData.cvNormal[2] << '\t' << endl;

	// Velocity Direction
	ostrmTreadmillFile << "Velocity_Direction\t" <<
		strtEnvTreadmillData.cvVelocityDirection[0] << '\t' << 
		strtEnvTreadmillData.cvVelocityDirection[1] << '\t' <<
		strtEnvTreadmillData.cvVelocityDirection[2] << '\t' << endl;

	// Position
	ostrmTreadmillFile << "Position\t" <<
		strtEnvTreadmillData.cvPosition[0] << '\t' << 
		strtEnvTreadmillData.cvPosition[1] << '\t' <<
		strtEnvTreadmillData.cvPosition[2] << '\t' << endl;

	// Width
	ostrmTreadmillFile << "Width\t" << 
		strtEnvTreadmillData.dWidth << endl;

	// Length
	ostrmTreadmillFile << "Length\t" << 
		strtEnvTreadmillData.dLength << endl;

	// Velocity Magnitude
	ostrmTreadmillFile << "Velocity_Mag\t" <<
		strtEnvTreadmillData.dVelocityMagnitude << endl;

	// Color
	ostrmTreadmillFile << "Color\t" << (int) (GetRValue(strtEnvTreadmillData.crColor)) <<
		'\t' << (int) (GetGValue(strtEnvTreadmillData.crColor)) << 
		'\t' << (int) (GetBValue(strtEnvTreadmillData.crColor)) << endl;

	// Close the file
	ostrmTreadmillFile.close ();

	return TRUE;

}
