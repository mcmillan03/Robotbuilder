// CameraData.cpp: implementation of the CCameraData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "CameraData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCameraData::CCameraData()
{
	WTp3_init (m_wtp3CoiOffset);

  m_ViewAngleDeg = 9;

	// Initialize in examine mode
	m_bPanMode = FALSE;

	m_bUseViewportFrameForExamineView = FALSE;
}

CCameraData::~CCameraData()
{

}


void CCameraData::GetViewAngleDegree (float ViewAngleDeg) const
{
  ViewAngleDeg = m_ViewAngleDeg;
}
void CCameraData::SetViewAngleDegree (const float ViewAngleDeg) 
{
  m_ViewAngleDeg = ViewAngleDeg;
}


void CCameraData::GetCenterOfInterestOffset(WTp3 wtp3Offset) const
{
	WTp3_copy (m_wtp3CoiOffset, wtp3Offset);
}

void CCameraData::SetCenterOfInterestOffset(const WTp3 wtp3Offset)
{
	WTp3_copy (wtp3Offset, m_wtp3CoiOffset);
}

void CCameraData::SetViewInPanMode(BOOL bViewInPanMode)
{
	m_bPanMode = bViewInPanMode;
}

BOOL CCameraData::GetViewInPanMode() const
{
	return m_bPanMode;
}

BOOL CCameraData::GetUseViewportFrameForExamineView() const
{
	return m_bUseViewportFrameForExamineView;
}

void CCameraData::SetUseViewportFrameForExamineView(BOOL bUseViewport)
{
	m_bUseViewportFrameForExamineView = bUseViewport;
}

void CCameraData::ClearCenterOfInterestOffset()
{
	WTp3 wtp3={0,0,0};
	SetCenterOfInterestOffset(wtp3);
}
