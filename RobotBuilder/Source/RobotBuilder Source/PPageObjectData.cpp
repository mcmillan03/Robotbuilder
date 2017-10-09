// PPageObjectData.cpp : implementation file
//

#include "stdafx.h"
#include "DMViewer.h"
#include "PPageObjectData.h"
#include "FindFile.h"
#include "DMViewerDoc.h"
#include "Model.h"
#include "ParserModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPageObjectData property page

IMPLEMENT_DYNCREATE(CPPageObjectData, CPPageLinkBase)

CPPageObjectData::CPPageObjectData(BOOL bEnableModelSetting) : CPPageLinkBase(CPPageObjectData::IDD)
{
	//{{AFX_DATA_INIT(CPPageObjectData)
	m_strGraphicsFile = _T("");
	m_strLinkName = _T("");
	//}}AFX_DATA_INIT
	m_strGraphicsPath = "";
	m_pCdmvObject = NULL;
	m_bEnableModelSetting = bEnableModelSetting;
}

CPPageObjectData::~CPPageObjectData()
{
}

void CPPageObjectData::DoDataExchange(CDataExchange* pDX)
{
	CPPageLinkBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPageObjectData)
	DDX_Control(pDX, IDC_STATIC_GRAPHICS_MODEL_GROUP_BOX, m_staticGraphicsModelGroupBox);
	DDX_Control(pDX, IDC_BUTTON_BROWSE, m_buttonBrowse);
	DDX_Control(pDX, IDC_EDIT_MODEL_PATH, m_editGraphicsFile);
	DDX_Text(pDX, IDC_EDIT_MODEL_PATH, m_strGraphicsFile);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_LINK_NAME, m_strLinkName);
	if (pDX->m_bSaveAndValidate)
	{
		if (m_strLinkName.FindOneOf ("\n\r\t") != -1)
		{
			AfxMessageBox ("Illegal character in name.", MB_OK);
			pDX->Fail ();
		}
	}
}


BEGIN_MESSAGE_MAP(CPPageObjectData, CPPageLinkBase)
	//{{AFX_MSG_MAP(CPPageObjectData)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPageObjectData message handlers

void CPPageObjectData::OnOK() 
{
	ASSERT (m_pCdmvObject);

	m_pCdmvObject->SetGraphicsModel (m_strGraphicsFile, m_strGraphicsPath);
	m_pCdmvObject->SetName (m_strLinkName);
	
	CPPageLinkBase::OnOK();
}

BOOL CPPageObjectData::OnInitDialog() 
{
	CPPageLinkBase::OnInitDialog();
	
	ASSERT (m_pCdmvObject);
	m_strLinkName = m_pCdmvObject->GetName ();
	m_pCdmvObject->GetGraphicsModel (m_strGraphicsFile, m_strGraphicsPath);

	if (!m_bEnableModelSetting)
	{
		m_editGraphicsFile.ShowWindow (SW_HIDE);
		m_buttonBrowse.ShowWindow (SW_HIDE);
		m_staticGraphicsModelGroupBox.ShowWindow (SW_HIDE);
	}
	
	// Set DDX the dialog data.
	BOOL bReturnStatus = UpdateData (FALSE);
	ASSERT (bReturnStatus);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPPageObjectData::OnButtonBrowse() 
{
	// First save the data in the controls, so if OK is chosen, the correct
	// data is displayed
	BOOL bReturnStatus = UpdateData (TRUE);
	ASSERT (bReturnStatus);
	

	CFileDialog dlg (TRUE, /* make an open dlg */
		".dat", /* default extension */
		m_strGraphicsFile, /* initial filename */
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, /* styles */
		"All Supported Files (*.dat;*.xan;*.rbm;*.cmb;*.slp;*.wrl;*.dxf;*.3ds;*.nff;*.bff;*.geo;*.obj)|\
*.dat;*.xan;*.rbm;*.cmb;*.slp;*.wrl;*.dxf;*.3ds;*.nff;*.bff;*.geo;*.obj|GLAnimate Files (*.dat)|*.dat|XAnimate Files (*.xan)|*.xan|\
RobotModeler Files (*.rbm)|*.rbm|Combined XAnimate Files (*.cmb)|*.cmb|ProEngineer Files (*.slp)|*.slp|\
VRML Files (*.wrl)|*.wrl|AutoCAD Files (*.dxf)|*.dxf|3D Studio Files (*.3ds)|*.3ds|Sense8 Files (*.nff)|*.nff|\
Old Sense8 Files (*.bff)|*.bff|VideoScape Files (*.geo)|*.geo|Wavefront Files (*.obj)|*.obj||",	/* filter */
		NULL /* parent */
		);

	// Set initial path
	if (m_strGraphicsPath.GetLength () > 0)
		dlg.m_ofn.lpstrInitialDir = m_strGraphicsPath;

	if (dlg.DoModal () == IDOK)
	{	
		CString strPath;
		CString strFile = dlg.GetFileName ();
		
		BOOL bFindFile = CFindFile::FindFile (MODEL_FILE_TYPE, 
			strFile, strPath);
		if (!bFindFile || ((strPath + strFile) != dlg.GetPathName ()))
		{
			if (IDYES == AfxMessageBox (FILE_NOT_FOUND_MSG, MB_YESNO))
			{
				strFile = dlg.GetPathName ();
				strPath = "";
			}
			else
			{
				// strFile stays the same
				// Strip off the file name from the full path
				strPath = (dlg.GetPathName ()).Left (dlg.GetPathName ().GetLength () -
					strFile.GetLength ());
			}
		}
		
		m_strGraphicsFile = strFile;
		m_strGraphicsPath = strPath;

		// Check if it is an .rbm file
		CString strExtension = m_strGraphicsFile.Right (4);
		strExtension.MakeUpper ();
		if (strExtension == ".RBM")
		{
			// Then the graphics file is .rbm file

			// Now determine if the object type is one that needs the physical parameters
			// in the .rmb file
			if (m_pCdmvObject->GetObjectType () == LINK)
			{
				// Get a copy of the link pointer
				CdmvLinkData* pLink = dynamic_cast <CdmvLinkData*> (m_pCdmvObject);

				// Check if this a link that has physical paramters
				if (pLink->GetLinkType () == MOBILE_BASE_LINK || pLink->GetLinkType () == PRISMATIC_LINK ||
					pLink->GetLinkType () == REVOLUTE_LINK || pLink->GetLinkType () == SPHERICAL_LINK)
				{
					// Then this link has physical parameters that should be read from
					// the .rbm file.

					// Attempt to parse the model file
					CModel* pModel;
					if (CParserModel::ParseModelFile (m_strGraphicsPath + m_strGraphicsFile, &pModel))
					{
						// Then successfully parsed the model file
						// Check if need to use calculated data or if it will be supplied
						// by the user in RobotBuilder
						if (!pModel->UseUserSuppliedDataForPhysicalData ())
						{
							// Tell RB that the data from the .rbm file should be used
							m_pCdmvObject->UseRbmData (TRUE);

							//// Save the data
							// Save it in a structure
							structRigidBodyInertialParameters strtRigidBodyInertialParameters;
							strtRigidBodyInertialParameters.fMass = pModel->GetModelMass ();
							
							double dCenterOfGravity[3];
							pModel->GetModelCenterOfGravity (dCenterOfGravity);
							
							double dInertia[3][3];
							pModel->GetModelInertia (dInertia);
							
							int i, j;
							for (i = 0; i < 3; i ++)
							{
								for (j = 0; j < 3; j++)
								{
									strtRigidBodyInertialParameters.ctIbar[i][j] = dInertia[i][j];
								}
								strtRigidBodyInertialParameters.cvCenterGravityPosition[i] = dCenterOfGravity[i];
							}

							// Tell the other property pages about it.  This message will
							// be interpretted by the RigidBodyProperties page
							QuerySiblings (1, reinterpret_cast <LPARAM> (&strtRigidBodyInertialParameters));
						}
						else
						{
							// Not using automatically calculated physical data
							m_pCdmvObject->UseRbmData (FALSE);
						}

					}
					else
					{
						// Then failed to parse the model file.  Consequently, will not use
						// the parameter data from the .rbm file, but will use the data
						// from the .dm file
						CString strError;
						strError.Format ("Warning: The model file %s could not be parsed.\nRobotBuilder will revert to using the physical parameters from the .dm file.", 
							m_strGraphicsFile);
						AfxMessageBox (strError);

						m_pCdmvObject->UseRbmData (FALSE);
					}
				}
			}
		}
		else
		{
			// Then it's not a .rbm file, so make sure the dmObject knows that
			m_pCdmvObject->UseRbmData (FALSE);
		}
		
		// Now update to reflect the change
		bReturnStatus = UpdateData (FALSE);
		ASSERT (bReturnStatus);
	}	
}
