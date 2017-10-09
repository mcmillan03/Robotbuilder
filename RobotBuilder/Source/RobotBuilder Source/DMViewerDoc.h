// DMViewerDoc.h : interface of the CDMViewerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMVIEWERDOC_H__6BC5BDED_EC4B_11D3_A7DF_0000E8978554__INCLUDED_)
#define AFX_DMVIEWERDOC_H__6BC5BDED_EC4B_11D3_A7DF_0000E8978554__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dmvSystemData.h"
#include "DMTreeView.h"
#include "WTKView.h"
#include "GenerateDMConfigFile.h"
#include "GenerateEnvironmentFile.h"
#include "DynaMechs.h"
#include "dmvEnvironmentData.h"
#include "FindFile.h"
#include "dmvCFGData.h"
#include "IOView.h"
#include "PlaybackData.h"
#include "CameraData.h"

#include <RBUserIOData.h>

#define INITIAL_WTK_BACKGROUND_COLOR RGB(125, 158, 192)


class CDMViewerDoc : public CDocument
{
protected: // create from serialization only
	CDMViewerDoc();
	DECLARE_DYNCREATE(CDMViewerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDMViewerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL OnAppIdle (LONG lCount);
	CdmvSystemData* GetSystemData ();
	virtual ~CDMViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	CdmvLinkData* GetClipboardData () const;
	void SetClipboardData (CdmvLinkData* pLinkData);
	CCameraData* GetCameraData ();
	BOOL ShowInertialAxes () const {return m_bShowAxes;}
	CdmvCFGData* GetCFGData () {return m_pCdmvCFGData;}
	int GetNumberOfMovableObjects ();
	CIOView* GetIOView ();
	CWTKView* GetWTKView ();
	CDMTreeView* GetTreeView ();
	const CDynaMechs* GetDynaMechs () const;
	void KeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
	CdmvEnvironmentData* GetEnvironmentData ();
	afx_msg void OnViewTogglestate();
protected:
	CdmvLinkData* m_pLinkClipboard; // This is clipboard for the CDMTreeView.  The
	// problem is that the view is destroyed when simulation mode is entered, so the
	// clipboard data will be lost if it is saved locally.
	BOOL m_bShowAxes;
	void ResetSimulationPropertiesToDefaults ();
	void UpdateSimulationWithCFGParameters ();
	BOOL ValidateStateBeforeDynaMechs ();
	void DeleteCFG ();
	void OpenArticulationFile (CString strFile, CString strPath);
	void UpdateArticulationDisplay ();
	void DeleteEnvironment ();
	void DeleteArticulation ();
	void UpdateEnvironmentDisplay ();
	void OpenEnvironmentFile (CString strFile, CString strPath);
	BOOL m_bEditState;
	BOOL m_bPlay;
	/// Tells if in recording state
	BOOL m_bRecordMode;  
	/// Tells if in playback mode
	BOOL m_bPlaybackMode;
	
	BOOL m_bSystemChanged;

	CdmvSystemData *m_pSystemData;

	CdmvEnvironmentData *m_pEnvironmentData;
	BOOL m_bEnvironmentChanged;

	CDynaMechs m_DynaMechs;

	CFindFile m_FindFile;

	CdmvCFGData *m_pCdmvCFGData;

    RBUserIOData *m_pRBUserIOData;

	CPlaybackData m_PlaybackData;

	CCameraData m_CameraData;

	/// Holds the playback path
	CString m_strPlaybackPath;
	/// Holds the playback file - should be empty if none loaded
	CString m_strPlaybackFile;
	/// Holds if the playback file has been changed, but not saved to disk
	BOOL m_bPlaybackChanged;

	//{{AFX_MSG(CDMViewerDoc)
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonPause();
	afx_msg void OnUpdateButtonPlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonPause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewTogglestate(CCmdUI* pCmdUI);
	afx_msg void OnButtonStop();
	afx_msg void OnUpdateButtonStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnEnvironmentNewEnvironmentFile();
	afx_msg void OnEnvironmentEditEnvironmentProperities();
	afx_msg void OnEnvironmentSaveEnvironment();
	afx_msg void OnEnvironmentSaveEnvironmentAs();
	afx_msg void OnEnvironmentOpenEnvironmentFile();
	afx_msg void OnArticulationOpenArticulationFile();
	afx_msg void OnArticulationSaveArticulationFile();
	afx_msg void OnArticulationSaveArticulationFileAs();
	afx_msg void OnControlSelectControlDll();
	afx_msg void OnUpdateArticulationNewarticulationfile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArticulationOpenarticulationfile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArticulationSavearticulationfile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateArticulationSavearticulationfileas(CCmdUI* pCmdUI);
	afx_msg void OnUpdateControlSelectcontroldll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEnvironmentEditenvironmentproperities(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEnvironmentNewenvironmentfile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEnvironmentOpenenvironmentfile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEnvironmentSaveenvironment(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEnvironmentSaveenvironmentas(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnCfgfileEditSimulationProperties();
	afx_msg void OnUpdateFileMruFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnButtonViewUser();
	afx_msg void OnButtonViewLeft();
	afx_msg void OnButtonViewBack();
	afx_msg void OnButtonViewBottom();
	afx_msg void OnButtonViewFront();
	afx_msg void OnButtonViewRight();
	afx_msg void OnButtonViewTop();
	afx_msg void OnButtonZoomIn();
	afx_msg void OnButtonZoomOut();
	afx_msg void OnButtonToggleAxes();
	afx_msg void OnUpdateButtonToggleAxes(CCmdUI* pCmdUI);
	afx_msg void OnSetupDefaultpaths();
	afx_msg void OnSetupNodisplaymodeduringsimulation();
	afx_msg void OnUpdateSetupNodisplaymodeduringsimulation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCfgfileEditsimulationproperties(CCmdUI* pCmdUI);
	afx_msg void OnArticulationNewArticulationFile();
	afx_msg void OnButtonRecord();
	afx_msg void OnUpdateButtonRecord(CCmdUI* pCmdUI);
	afx_msg void OnButtonPlayback();
	afx_msg void OnUpdateButtonPlayback(CCmdUI* pCmdUI);
	afx_msg void OnPlaybackOpenplaybackfile();
	afx_msg void OnUpdatePlaybackOpenplaybackfile(CCmdUI* pCmdUI);
	afx_msg void OnPlaybackSaveplayback();
	afx_msg void OnUpdatePlaybackSaveplayback(CCmdUI* pCmdUI);
	afx_msg void OnPlaybackSaveplaybackfileas();
	afx_msg void OnUpdatePlaybackSaveplaybackfileas(CCmdUI* pCmdUI);
	afx_msg void OnButtonBuild();
	afx_msg void OnUpdateButtonBuild(CCmdUI* pCmdUI);
	afx_msg void OnButtonShowLinkAxes();
	afx_msg void OnButtonHideLinkAxes();
	afx_msg void OnViewCameracontrol();
	afx_msg void OnButtonRbmodler();
	afx_msg void OnViewCameralight();
	afx_msg void OnUpdateViewCameralight(CCmdUI* pCmdUI);
	afx_msg void OnHelpUsersguide();
	afx_msg void OnButtonexamine();
	afx_msg void OnUpdateButtonexamine(CCmdUI* pCmdUI);
	afx_msg void OnButtonpan();
	afx_msg void OnUpdateButtonpan(CCmdUI* pCmdUI);
	afx_msg void OnHelpTutorial();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DMVIEWERDOC_H__6BC5BDED_EC4B_11D3_A7DF_0000E8978554__INCLUDED_)
