// Math.h: interface for the CRBMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATH_H__4C64E6F0_F0A7_4063_AC39_654A0AD78CB5__INCLUDED_)
#define AFX_MATH_H__4C64E6F0_F0A7_4063_AC39_654A0AD78CB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRBMath  
{
public:
	static void Transpose3by3Double (const double dMatrix[3][3], double dMatrixT[3][3]);
	static void Multiply3by3DoubleMatrices (const double dMatrix1[3][3], const double dMatrix2[3][3], double dProduct[3][3]);
	CRBMath();
	virtual ~CRBMath();

};

#endif // !defined(AFX_MATH_H__4C64E6F0_F0A7_4063_AC39_654A0AD78CB5__INCLUDED_)
