// PrimitivePlacement.cpp: implementation of the CPrimitivePlacement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RBModeler.h"
#include "PrimitivePlacement.h"
#include "DlgMovementControls.h"
#include "Primitive.h"
#include "wt.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrimitivePlacement::CPrimitivePlacement()
{
	m_strtPrimitivePlacementData.dTranslationX = 0;
	m_strtPrimitivePlacementData.dTranslationY = 0;
	m_strtPrimitivePlacementData.dTranslationZ = 0;
	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			if (i==j)
				m_strtPrimitivePlacementData.dRotationMatrix[i][j] = 1;
			else
				m_strtPrimitivePlacementData.dRotationMatrix[i][j] = 0;


}

CPrimitivePlacement::~CPrimitivePlacement()
{

}

void CPrimitivePlacement::AlterTranslation(double dChange, UINT uAxis, 
		UINT uWithRespectToType, CPrimitive* pPrimitive)
{	
	// Build the translation vector
	WTp3 wtp3Change;
	WTp3_init (wtp3Change);
	switch (uAxis)
	{
	case AXIS_X:
		wtp3Change[X] = dChange;
		break;
	case AXIS_Y:
		wtp3Change[Y] = dChange;
		break;
	case AXIS_Z:
		wtp3Change[Z] = dChange;
		break;
	default:
		ASSERT (FALSE);
	}

	switch (uWithRespectToType)
	{	
	case MODIFY_WRT_LOCAL:
		// Use WTK's functions because no real need to write my own
		
		// Build the WTK 3D rotation matrix
		WTm3 wtm3_uRp;
		int i, j; // Temporary counters
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				wtm3_uRp[i][j] = m_strtPrimitivePlacementData.dRotationMatrix[i][j];
		// Find the quaternion representation
		WTq wtq;
		WTm3_2q (wtm3_uRp, wtq);
		// Apply the rotation to the vector
		WTp3 wtp3Universe;
//		WTp3_rotate (wtp3Change, wtq, wtp3Universe);
		WTp3_multm3 (wtp3Change, wtm3_uRp, wtp3Universe);
		// Change the translation vector
		m_strtPrimitivePlacementData.dTranslationX += wtp3Universe[X];
		m_strtPrimitivePlacementData.dTranslationY += wtp3Universe[Y];
		m_strtPrimitivePlacementData.dTranslationZ += wtp3Universe[Z];
		break;
	case MODIFY_WRT_UNIVERSE:
		m_strtPrimitivePlacementData.dTranslationX += wtp3Change[X];
		m_strtPrimitivePlacementData.dTranslationY += wtp3Change[Y];
		m_strtPrimitivePlacementData.dTranslationZ += wtp3Change[Z];
		break;
	case MODIFY_WRT_PRIMITIVE:
		// Build 3D rotation from u(niverse) to Primitive p1 (with respect to)
		WTm3 wtm3_uRp1;
		structPrimitivePlacementData strtPrimitivePlacementDataWRTPrimitive;
		ASSERT (pPrimitive);
		pPrimitive->GetPrimitivePlacement()->GetPrimitivePlacementData (&strtPrimitivePlacementDataWRTPrimitive);
		for (i=0; i<3; i++)
			for (j=0; j<3; j++)
				wtm3_uRp1[i][j] = strtPrimitivePlacementDataWRTPrimitive.dRotationMatrix[i][j];
		// Change to quaternion representation
		WTq wtq_uRp1;
		WTm3_2q (wtm3_uRp1, wtq_uRp1);
		// Apply the rotation to the vector in terms of p1
		WTp3 wtp3_Vu;
		WTp3_rotate (wtp3Change, wtq_uRp1, wtp3_Vu);
		// Change the translation vector
		m_strtPrimitivePlacementData.dTranslationX += wtp3_Vu[X];
		m_strtPrimitivePlacementData.dTranslationY += wtp3_Vu[Y];
		m_strtPrimitivePlacementData.dTranslationZ += wtp3_Vu[Z];
		break;
	default:
		ASSERT (FALSE);
		
	}
	
}

void CPrimitivePlacement::AlterRotation (double dAngle, UINT uAxis, 
	UINT uWithRespectToType, CPrimitive* pPrimitive)
{
	// Rotation is a special case of the a general transform that has no change
	// in the position vector.  For now, save the current position, call the
	// AlterTransform function, then replace the position with the saved value
	// (It would be more efficient to implement rotation specific code and it
	// is should be down when time allows).

	// Save the current position
	WTp3 wtp3CurrentPos;
	wtp3CurrentPos[X] = m_strtPrimitivePlacementData.dTranslationX;
	wtp3CurrentPos[Y] = m_strtPrimitivePlacementData.dTranslationY;
	wtp3CurrentPos[Z] = m_strtPrimitivePlacementData.dTranslationZ;

	// Call the transform function
	AlterSpatialTransform (dAngle, uAxis, uWithRespectToType, pPrimitive);

	// Restore the original position
	m_strtPrimitivePlacementData.dTranslationX = wtp3CurrentPos[X];
	m_strtPrimitivePlacementData.dTranslationY = wtp3CurrentPos[Y];
	m_strtPrimitivePlacementData.dTranslationZ = wtp3CurrentPos[Z];

}

void CPrimitivePlacement::GetPrimitivePlacementData(structPrimitivePlacementData *pstrtPrimitivePlacementData) const
{
	ASSERT (pstrtPrimitivePlacementData);

	pstrtPrimitivePlacementData->dTranslationX = m_strtPrimitivePlacementData.dTranslationX;
	pstrtPrimitivePlacementData->dTranslationY = m_strtPrimitivePlacementData.dTranslationY;
	pstrtPrimitivePlacementData->dTranslationZ = m_strtPrimitivePlacementData.dTranslationZ;

	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			pstrtPrimitivePlacementData->dRotationMatrix[i][j] = m_strtPrimitivePlacementData.dRotationMatrix[i][j];

}

void CPrimitivePlacement::SetPrimitivePlacementData(const structPrimitivePlacementData* pstrtPrimitivePlacementData)
{
	ASSERT (pstrtPrimitivePlacementData);

	m_strtPrimitivePlacementData.dTranslationX = pstrtPrimitivePlacementData->dTranslationX;
	m_strtPrimitivePlacementData.dTranslationY = pstrtPrimitivePlacementData->dTranslationY;
	m_strtPrimitivePlacementData.dTranslationZ = pstrtPrimitivePlacementData->dTranslationZ;

	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			m_strtPrimitivePlacementData.dRotationMatrix[i][j] = pstrtPrimitivePlacementData->dRotationMatrix[i][j];
}

//!!! WARNING - the variable names are misleading -- see SJR's thesis for an explanation
// Remember that WTK uses right-to-left rotation notation
void CPrimitivePlacement::AlterSpatialTransform(double dAngle, UINT uAxis, UINT uWithRespectToType, CPrimitive *pPrimitive)
{
	// Create the 3D rotation matrix
	WTm4 wtm4RotationTransform;
	// WTK initialize a 4x4 as the I4 matrix
	WTm4_init (wtm4RotationTransform);

	switch (uAxis)
	{
	case AXIS_X:
		wtm4RotationTransform[1][1] = cos (dAngle * PI/180);
		wtm4RotationTransform[1][2] = - sin (dAngle * PI/180);
		wtm4RotationTransform[2][1] = sin (dAngle * PI/180);
		wtm4RotationTransform[2][2] = cos (dAngle * PI/180);
		break;
	case AXIS_Y:
		wtm4RotationTransform[0][0] = cos (dAngle * PI/180);
		wtm4RotationTransform[0][2] = sin (dAngle * PI/180);
		wtm4RotationTransform[2][0] = - sin (dAngle * PI/180);
		wtm4RotationTransform[2][2] = cos (dAngle * PI/180);
		break;
	case AXIS_Z:
		wtm4RotationTransform[0][0] = cos (dAngle * PI/180);
		wtm4RotationTransform[0][1] = -sin (dAngle * PI/180);
		wtm4RotationTransform[1][0] = sin (dAngle * PI/180);
		wtm4RotationTransform[1][1] = cos (dAngle * PI/180);
		break;
	}

	// Build the transform from the universe to this primitive
	WTm4 wtm4_uTp1;
	WTm4_init (wtm4_uTp1);
	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			wtm4_uTp1[i][j] = m_strtPrimitivePlacementData.dRotationMatrix[i][j];
//	wtm4_uTp1[0][3] = m_strtPrimitivePlacementData.dTranslationX;
//	wtm4_uTp1[1][3] = m_strtPrimitivePlacementData.dTranslationY;
//	wtm4_uTp1[2][3] = m_strtPrimitivePlacementData.dTranslationZ;
	wtm4_uTp1[3][0] = m_strtPrimitivePlacementData.dTranslationX;
	wtm4_uTp1[3][1] = m_strtPrimitivePlacementData.dTranslationY;
	wtm4_uTp1[3][2] = m_strtPrimitivePlacementData.dTranslationZ;


	WTm4 wtm4_uTpfinal;
	// Apply the spatial rotation
	switch (uWithRespectToType)
	{
	case MODIFY_WRT_LOCAL:
		// Just multiply the transforms with WTK
		WTm4 wtm4InverseRotationTransform2;
		WTm4_invert (wtm4RotationTransform, wtm4InverseRotationTransform2);
		WTm4_multm4 (wtm4InverseRotationTransform2, wtm4_uTp1, wtm4_uTpfinal);
		break;
	case MODIFY_WRT_UNIVERSE:
		WTm4 wtm4InverseRotationTransform;
		int nIsNonSingular;
		nIsNonSingular =1;
		WTm4_transpose (wtm4RotationTransform, wtm4InverseRotationTransform);
		ASSERT (nIsNonSingular); // If this fails it implies the coordinate system in not linearly independent
		WTm4_multm4 (  
			wtm4_uTp1, wtm4InverseRotationTransform, wtm4_uTpfinal);
//		WTm4 wtm4_uTpfinal2;
//		WTm4_multm4 (wtm4RotationTransform,  wtm4_uTp1, 
//			wtm4_uTpfinal2);
//		wtm4_uTpfinal[0][3] = wtm4_uTpfinal2[0][3];
//		wtm4_uTpfinal[1][3] = wtm4_uTpfinal2[1][3];
//		wtm4_uTpfinal[2][3] = wtm4_uTpfinal2[2][3];
//		wtm4_uTpfinal[3][3] = wtm4_uTpfinal2[3][3];

//		// Transform that translates from u to p1
//		WTm4 wtm4_translate_u2p1;
//		WTm4_init (wtm4_translate_u2p1);
//		// Copy the translation part
//		for (i = 0; i < 3; i++)
//			wtm4_translate_u2p1[i][3] = wtm4_uTp1[i][3];
//		// Translate to origin
//		WTm4 wtm4_translate_p12u;
//		WTm4_init (wtm4_translate_p12u);
//		for (i = 0; i < 3; i++)
//			wtm4_translate_p12u[i][3] = -wtm4_uTp1[i][3];
//		WTm4 wtm4_temp;
//		WTm4_multm4 (wtm4_translate_u2p1, wtm4RotationTransform, wtm4_temp);
//		WTm4 wtm4_temp2;
//		WTm4_multm4 (wtm4_temp, wtm4_translate_p12u, wtm4_temp2);
//		WTm4_multm4 (wtm4_temp2, wtm4_uTp1, wtm4_uTpfinal);






		break;
	case MODIFY_WRT_PRIMITIVE:
		ASSERT (pPrimitive);
		// todo: implement
		break;
	default:
		ASSERT (FALSE);
	}

	// Save the final transform in the member data structs
	for (i=0;i<3;i++)
		for(j=0;j<3;j++)
			m_strtPrimitivePlacementData.dRotationMatrix[i][j] = wtm4_uTpfinal[i][j];
//	m_strtPrimitivePlacementData.dTranslationX = wtm4_uTpfinal[0][3];
//	m_strtPrimitivePlacementData.dTranslationY = wtm4_uTpfinal[1][3];
//	m_strtPrimitivePlacementData.dTranslationZ = wtm4_uTpfinal[2][3];
	m_strtPrimitivePlacementData.dTranslationX = wtm4_uTpfinal[3][0];
	m_strtPrimitivePlacementData.dTranslationY = wtm4_uTpfinal[3][1];
	m_strtPrimitivePlacementData.dTranslationZ = wtm4_uTpfinal[3][2];


}
