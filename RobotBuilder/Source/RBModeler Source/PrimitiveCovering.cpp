// PrimitiveCovering.cpp: implementation of the CPrimitiveCovering class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "PrimitiveCovering.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrimitiveCovering::CPrimitiveCovering()
{
	m_strtPrimitiveCoveringData.covCovering = SIMPLE_COLOR;
	m_strtPrimitiveCoveringData.crColor = RGB (192, 192, 192);
}

CPrimitiveCovering::~CPrimitiveCovering()
{

}

void CPrimitiveCovering::SetPrimitiveCoveringData(const structPrimitiveCoveringData *pstrtPrimitiveCoveringData)
{
	m_strtPrimitiveCoveringData.covCovering = pstrtPrimitiveCoveringData->covCovering;
	m_strtPrimitiveCoveringData.crColor = pstrtPrimitiveCoveringData->crColor;
	m_strtPrimitiveCoveringData.strTextureFile = pstrtPrimitiveCoveringData->strTextureFile;
	m_strtPrimitiveCoveringData.strTexturePath = pstrtPrimitiveCoveringData->strTexturePath;
}

void CPrimitiveCovering::GetPrimitiveCoveringData(structPrimitiveCoveringData *pstrtPrimitiveCoveringData) const
{
	pstrtPrimitiveCoveringData->covCovering = m_strtPrimitiveCoveringData.covCovering;
	pstrtPrimitiveCoveringData->crColor = m_strtPrimitiveCoveringData.crColor;
	pstrtPrimitiveCoveringData->strTextureFile = m_strtPrimitiveCoveringData.strTextureFile;
	pstrtPrimitiveCoveringData->strTexturePath = m_strtPrimitiveCoveringData.strTexturePath;
}
