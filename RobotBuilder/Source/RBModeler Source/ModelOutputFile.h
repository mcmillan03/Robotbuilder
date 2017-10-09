// ModelOutputFile.h: interface for the CModelOutputFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODELOUTPUTFILE_H__D3AEB9E7_AA20_4898_A6B5_E9B3948BFE6C__INCLUDED_)
#define AFX_MODELOUTPUTFILE_H__D3AEB9E7_AA20_4898_A6B5_E9B3948BFE6C__INCLUDED_


#include "Model.h"
#include "PrimitiveSphere.h"
#include "PrimitiveBlock.h"
#include "PrimitiveCone.h"
#include "PrimitiveCylinder.h"
#include "PrimitiveHemisphere.h"
#include "PrimitiveTruncatedCone.h"

#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CModelOutputFile  
{
public:
	BOOL OutputModelFile (CString strOutputFile, CModel* pModel);
	CModelOutputFile();
	virtual ~CModelOutputFile();

protected:
	void OutputPrimitiveMass(ofstream &ostrmModelFile, CPrimitive *pPrimitive);
	void OutputPrimitiveHemisphere (ofstream& ostrmModelFile, CPrimitiveHemisphere* pPrimitiveHemisphere);
	void OutputPrimitiveTruncatedCone (ofstream& ostrmModelFile, CPrimitiveTruncatedCone* pPrimitiveTruncatedCone);
	void OutputPrimitiveCylinder (ofstream& ostrmModelFile, CPrimitiveCylinder* pPrimitiveCylinder);
	void OutputPrimitiveBlock (ofstream& ostrmModelFile, CPrimitiveBlock* pPrimitiveBlock);
	void OutputPrimitiveCone (ofstream& ostrmModelFile, CPrimitiveCone* pPrimitiveCone);
	void OutputPrimitiveScale (ofstream &ostrmModelFile, CPrimitiveScale*);
	void OutputPrimitiveName (ofstream& ostrmModelFile, CPrimitive* pPrimitive);
	void OutputPrimitiveSphere (ofstream& ostrmModelFile, CPrimitiveSphere* pPrimitiveSphere);
	void OutputPrimitivePlacement (ofstream &ostrmModelFile, CPrimitivePlacement* pPrimitivePlacement);
	void OutputPrimitiveCovering (ofstream& ostrmModelFile, CPrimitiveCovering* pPrimitiveCovering);
	void OutputVersion (ofstream& ostrmModelFile);
};

#endif // !defined(AFX_MODELOUTPUTFILE_H__D3AEB9E7_AA20_4898_A6B5_E9B3948BFE6C__INCLUDED_)
