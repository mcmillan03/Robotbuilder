// Math.cpp: implementation of the CRBMath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "rbModeler.h"
#include "RBMath.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRBMath::CRBMath()
{

}

CRBMath::~CRBMath()
{

}

// todo: generalize to other matrices
void CRBMath::Multiply3by3DoubleMatrices(const double dMatrix1[][3], const double dMatrix2[][3], double dProduct[][3])
{
	int i,j,k;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			double dTempSum = 0;
			for (k=0;k<3;k++)
			{
				dTempSum += dMatrix1[i][k] * dMatrix2[k][j];
			}
			dProduct[i][j] = dTempSum;
		}
	}
}


void CRBMath::Transpose3by3Double(const double dMatrix[][3], double dMatrixT[][3])
{
	int i,j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			dMatrixT[i][j] = dMatrix[j][i];
		}
	}
}
