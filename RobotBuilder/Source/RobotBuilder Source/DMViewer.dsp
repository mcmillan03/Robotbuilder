# Microsoft Developer Studio Project File - Name="DMViewer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DMViewer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DMViewer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DMViewer.mak" CFG="DMViewer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DMViewer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DMViewer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DMViewer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "c:\Program Files\wtk" /I "c:\Program Files\wtk\lib" /I "c:\Program Files\wtk\include" /I "..\..\..\DynaMechs4.0\dynamechs\dm" /I "..\RBModler" /I "..\..\..\RBUserIOData" /I "..\..\DynaMechs4.0\dynamechs\dmu" /I "..\RBModeler Source" /I "." /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "ROBOTBUILDER" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib wtk.lib wsock32.lib winmm.lib dm.lib RBUserIOData.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /out:"..\..\RobotBuilder.exe" /libpath:"c:\Program Files\wtk\lib" /libpath:"..\..\..\DynaMechs4.0\dynamechs\lib\platform.msvc60.i686" /libpath:"..\..\..\RBUserIOData\release"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "DMViewer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "c:\Program Files\wtk\include" /I "..\..\..\DynaMechs4.0\dynamechs\dm" /I "..\RBModler" /I "..\..\..\RBUserIOData" /I "..\..\DynaMechs4.0\dynamechs\dmu" /I "..\RBModeler Source" /I "." /D "_DEBUG" /D "USE_DM_DLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "ROBOTBUILDER" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib wtk.lib wsock32.lib winmm.lib dm.lib RBUserIOData.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrt.lib" /out:"../../RobotBuilderd.exe" /pdbtype:sept /libpath:"c:\Program Files\wtk\lib" /libpath:"..\..\..\DynaMechs4.0\dynamechs\lib\platform.msvc60.i686" /libpath:"..\..\..\RBUserIOData\debug"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "DMViewer - Win32 Release"
# Name "DMViewer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CameraControl.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCameraControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConfigAxes.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConfigBackground.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConfigCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConfigFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConfigProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConfigSimulation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgContactPosition.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnvironmentData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnvSaveTerrainFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnvSaveTreadmillFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnvTerrainData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEnvTreadmillData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNoDisplayModeStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRevDCMotorData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSimulationData.cpp
# End Source File
# Begin Source File

SOURCE=.\DMSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\DMTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvActuatorData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvArticulationData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvCFGData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvContactModelData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvEnvironmentData.cpp
# End Source File
# Begin Source File

SOURCE=.\DMViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\DMViewer.rc
# End Source File
# Begin Source File

SOURCE=.\DMViewerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvMDHLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvMobileBaseLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvObject.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvPrismaticLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvRevDCMotorData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvRevoluteLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvRigidBodyData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvSecJointData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvSecPrisJntData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvSecRevJntData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvSecSpherJntData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvSphericalLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvStaticRootLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvSystemData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvTerrainData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvTreadmillData.cpp
# End Source File
# Begin Source File

SOURCE=.\dmvZScrewTxLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\DynaMechs.cpp
# End Source File
# Begin Source File

SOURCE=.\FindFile.cpp
# End Source File
# Begin Source File

SOURCE=.\GenerateCFGFile.cpp
# End Source File
# Begin Source File

SOURCE=.\GenerateDMConfigFile.cpp
# End Source File
# Begin Source File

SOURCE=.\GenerateEnvironmentFile.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneratePlaybackFile.cpp
# End Source File
# Begin Source File

SOURCE=.\GenerateTerrainFile.cpp
# End Source File
# Begin Source File

SOURCE=.\GenerateTouch.cpp
# End Source File
# Begin Source File

SOURCE=.\GenerateTreadmillFile.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\IOView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\Model.cpp"
# End Source File
# Begin Source File

SOURCE=.\ParserCFG.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserCmb.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserDat.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserDM.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserEnvironment.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserGeneral.cpp
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\ParserModel.cpp"
# End Source File
# Begin Source File

SOURCE=.\ParserPlayback.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserTerrain.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserTreadmill.cpp
# End Source File
# Begin Source File

SOURCE=.\ParserXan.cpp
# End Source File
# Begin Source File

SOURCE=.\PlaybackData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageActuatorData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageArticulationData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageLinkBase.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageMDHLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageMobileBaseLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageObjectData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageRigidBodyData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageSecJointData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageSecPrismaticJointData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageSecRevoluteJointData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageSecSphericalJointData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageSphericalLinkData.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageZScrewTxLinkData.cpp
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\Primitive.cpp"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveBlock.cpp"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveCone.cpp"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveCovering.cpp"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveCylinder.cpp"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveHemisphere.cpp"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitivePlacement.cpp"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveScale.cpp"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveSphere.cpp"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveTruncatedCone.cpp"
# End Source File
# Begin Source File

SOURCE=.\PSheetArticulation.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetLinkBase.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetMobileBaseLink.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetPrismaticLink.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetRevoluteLink.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetSecPrismaticJoint.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetSecRevoluteJoint.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetSecSphericalJoint.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetSphericalLink.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetStaticRootLink.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetZScrewTxLink.cpp
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\RBMath.cpp"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\RBMGraphicView.cpp"
# End Source File
# Begin Source File

SOURCE=.\hlp\RobotBuilder.hpj

!IF  "$(CFG)" == "DMViewer - Win32 Release"

!ELSEIF  "$(CFG)" == "DMViewer - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__ROBOT="hlp\AfxCore.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
TargetName=RobotBuilderd
InputPath=.\hlp\RobotBuilder.hpj
InputName=RobotBuilder

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WndWTK.cpp
# End Source File
# Begin Source File

SOURCE=.\WTKGraphics.cpp
# End Source File
# Begin Source File

SOURCE=.\WTKView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CameraControl.h
# End Source File
# Begin Source File

SOURCE=.\CameraData.h
# End Source File
# Begin Source File

SOURCE=.\DlgCameraControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgConfigAxes.h
# End Source File
# Begin Source File

SOURCE=.\DlgConfigBackground.h
# End Source File
# Begin Source File

SOURCE=.\DlgConfigCamera.h
# End Source File
# Begin Source File

SOURCE=.\DlgConfigFiles.h
# End Source File
# Begin Source File

SOURCE=.\DlgConfigProperties.h
# End Source File
# Begin Source File

SOURCE=.\DlgConfigSimulation.h
# End Source File
# Begin Source File

SOURCE=.\DlgContactPosition.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnvironmentData.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnvSaveTerrainFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnvSaveTreadmillFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnvTerrainData.h
# End Source File
# Begin Source File

SOURCE=.\DlgEnvTreadmillData.h
# End Source File
# Begin Source File

SOURCE=.\DlgLinkData.h
# End Source File
# Begin Source File

SOURCE=.\DlgNoDisplayModeStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgRevDCMotorData.h
# End Source File
# Begin Source File

SOURCE=.\DlgSimulationData.h
# End Source File
# Begin Source File

SOURCE=.\DMSplitter.h
# End Source File
# Begin Source File

SOURCE=.\DMTreeView.h
# End Source File
# Begin Source File

SOURCE=.\dmvActuatorData.h
# End Source File
# Begin Source File

SOURCE=.\dmvArticulationData.h
# End Source File
# Begin Source File

SOURCE=.\dmvCFGData.h
# End Source File
# Begin Source File

SOURCE=.\dmvContactModelData.h
# End Source File
# Begin Source File

SOURCE=.\dmvEnvironmentData.h
# End Source File
# Begin Source File

SOURCE=.\DMViewer.h
# End Source File
# Begin Source File

SOURCE=.\DMViewerDoc.h
# End Source File
# Begin Source File

SOURCE=.\dmvLinkData.h
# End Source File
# Begin Source File

SOURCE=.\dmvMDHLinkData.h
# End Source File
# Begin Source File

SOURCE=.\dmvMobileBaseLinkData.h
# End Source File
# Begin Source File

SOURCE=.\dmvObject.h
# End Source File
# Begin Source File

SOURCE=.\dmvPrismaticLinkData.h
# End Source File
# Begin Source File

SOURCE=.\dmvRevDCMotorData.h
# End Source File
# Begin Source File

SOURCE=.\dmvRevoluteLinkData.h
# End Source File
# Begin Source File

SOURCE=.\dmvRigidBodyData.h
# End Source File
# Begin Source File

SOURCE=.\dmvSecJointData.h
# End Source File
# Begin Source File

SOURCE=.\dmvSecPrisJntData.h
# End Source File
# Begin Source File

SOURCE=.\dmvSecRevJntData.h
# End Source File
# Begin Source File

SOURCE=.\dmvSecSpherJntData.h
# End Source File
# Begin Source File

SOURCE=.\dmvSphericalLinkData.h
# End Source File
# Begin Source File

SOURCE=.\dmvStaticRootLinkData.h
# End Source File
# Begin Source File

SOURCE=.\dmvSystemData.h
# End Source File
# Begin Source File

SOURCE=.\dmvTerrainData.h
# End Source File
# Begin Source File

SOURCE=.\dmvTreadmillData.h
# End Source File
# Begin Source File

SOURCE=.\dmvZScrewTxLinkData.h
# End Source File
# Begin Source File

SOURCE=.\DynaMechs.h
# End Source File
# Begin Source File

SOURCE=.\FindFile.h
# End Source File
# Begin Source File

SOURCE=.\GenerateCFGFile.h
# End Source File
# Begin Source File

SOURCE=.\GenerateDMConfigFile.h
# End Source File
# Begin Source File

SOURCE=.\GenerateEnvironmentFile.h
# End Source File
# Begin Source File

SOURCE=.\GeneratePlaybackFile.h
# End Source File
# Begin Source File

SOURCE=.\GenerateTerrainFile.h
# End Source File
# Begin Source File

SOURCE=.\GenerateTouch.h
# End Source File
# Begin Source File

SOURCE=.\GenerateTreadmillFile.h
# End Source File
# Begin Source File

SOURCE=.\hyperlink.h
# End Source File
# Begin Source File

SOURCE=.\IOView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\Model.h"
# End Source File
# Begin Source File

SOURCE=.\ModelParserTypes.h
# End Source File
# Begin Source File

SOURCE=.\ParserCFG.h
# End Source File
# Begin Source File

SOURCE=.\ParserCmb.h
# End Source File
# Begin Source File

SOURCE=.\ParserDat.h
# End Source File
# Begin Source File

SOURCE=.\ParserDM.h
# End Source File
# Begin Source File

SOURCE=.\ParserEnvironment.h
# End Source File
# Begin Source File

SOURCE=.\ParserGeneral.h
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\ParserModel.h"
# End Source File
# Begin Source File

SOURCE=.\ParserPlayback.h
# End Source File
# Begin Source File

SOURCE=.\ParserTerrain.h
# End Source File
# Begin Source File

SOURCE=.\ParserTreadmill.h
# End Source File
# Begin Source File

SOURCE=.\ParserXan.h
# End Source File
# Begin Source File

SOURCE=.\PlaybackData.h
# End Source File
# Begin Source File

SOURCE=.\PPageActuatorData.h
# End Source File
# Begin Source File

SOURCE=.\PPageArticulationData.h
# End Source File
# Begin Source File

SOURCE=.\PPageLinkBase.h
# End Source File
# Begin Source File

SOURCE=.\PPageLinkData.h
# End Source File
# Begin Source File

SOURCE=.\PPageMDHLinkData.h
# End Source File
# Begin Source File

SOURCE=.\PPageMobileBaseLinkData.h
# End Source File
# Begin Source File

SOURCE=.\PPageObjectData.h
# End Source File
# Begin Source File

SOURCE=.\PPageRigidBodyData.h
# End Source File
# Begin Source File

SOURCE=.\PPageSecJointData.h
# End Source File
# Begin Source File

SOURCE=.\PPageSecPrismaticJointData.h
# End Source File
# Begin Source File

SOURCE=.\PPageSecRevoluteJointData.h
# End Source File
# Begin Source File

SOURCE=.\PPageSecSphericalJointData.h
# End Source File
# Begin Source File

SOURCE=.\PPageSphericalLinkData.h
# End Source File
# Begin Source File

SOURCE=.\PPageZScrewTxLinkData.h
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\Primitive.h"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveBlock.h"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveCone.h"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveCovering.h"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveCylinder.h"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveHemisphere.h"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitivePlacement.h"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveScale.h"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveSphere.h"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\PrimitiveTruncatedCone.h"
# End Source File
# Begin Source File

SOURCE=.\PSheetArticulation.h
# End Source File
# Begin Source File

SOURCE=.\PSheetLinkBase.h
# End Source File
# Begin Source File

SOURCE=.\PSheetMobileBaseLink.h
# End Source File
# Begin Source File

SOURCE=.\PSheetPrismaticLink.h
# End Source File
# Begin Source File

SOURCE=.\PSheetRevoluteLink.h
# End Source File
# Begin Source File

SOURCE=.\PSheetSecPrismaticJoint.h
# End Source File
# Begin Source File

SOURCE=.\PSheetSecRevoluteJoint.h
# End Source File
# Begin Source File

SOURCE=.\PSheetSecSphericalJoint.h
# End Source File
# Begin Source File

SOURCE=.\PSheetSphericalLink.h
# End Source File
# Begin Source File

SOURCE=.\PSheetStaticRootLink.h
# End Source File
# Begin Source File

SOURCE=.\PSheetZScrewTxLink.h
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\RBMath.h"
# End Source File
# Begin Source File

SOURCE="..\RBModeler Source\RBMGraphicView.h"
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "DMViewer - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=RobotBuilder
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "DMViewer - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=RobotBuilderd
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WTKGraphics.h
# End Source File
# Begin Source File

SOURCE=.\WTKView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\DMViewer.ico
# End Source File
# Begin Source File

SOURCE=.\res\DMViewer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DMViewerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tb_tree_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RobotBuilder.cnt

!IF  "$(CFG)" == "DMViewer - Win32 Release"

!ELSEIF  "$(CFG)" == "DMViewer - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Debug
InputPath=.\hlp\RobotBuilder.cnt
InputName=RobotBuilder

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# End Group
# Begin Group "RBModler Source Files"

# PROP Default_Filter ""
# End Group
# Begin Group "RBModler Header Files"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\WndWTK.h
# End Source File
# End Target
# End Project
# Section DMViewer : {E9E074CF-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcColor
# 	2:10:HeaderFile:vccolor.h
# 	2:8:ImplFile:vccolor.cpp
# End Section
# Section DMViewer : {E9E074D8-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFont
# 	2:10:HeaderFile:vcfont.h
# 	2:8:ImplFile:vcfont.cpp
# End Section
# Section DMViewer : {E9E07504-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesMarker
# 	2:10:HeaderFile:vcseriesmarker.h
# 	2:8:ImplFile:vcseriesmarker.cpp
# End Section
# Section DMViewer : {E9E074E8-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLegend
# 	2:10:HeaderFile:vclegend.h
# 	2:8:ImplFile:vclegend.cpp
# End Section
# Section DMViewer : {E9E074DA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcBrush
# 	2:10:HeaderFile:vcbrush.h
# 	2:8:ImplFile:vcbrush.cpp
# End Section
# Section DMViewer : {3A2B370C-BA0A-11D1-B137-0000F8753F5D}
# 	2:21:DefaultSinkHeaderFile:mschart.h
# 	2:16:DefaultSinkClass:CMSChart
# End Section
# Section DMViewer : {E9E074EA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataGrid
# 	2:10:HeaderFile:vcdatagrid.h
# 	2:8:ImplFile:vcdatagrid.cpp
# End Section
# Section DMViewer : {E9E074D3-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcMarker
# 	2:10:HeaderFile:vcmarker.h
# 	2:8:ImplFile:vcmarker.cpp
# End Section
# Section DMViewer : {E9E0751B-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisGrid
# 	2:10:HeaderFile:vcaxisgrid.h
# 	2:8:ImplFile:vcaxisgrid.cpp
# End Section
# Section DMViewer : {E9E07508-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLabel
# 	2:10:HeaderFile:vclabel.h
# 	2:8:ImplFile:vclabel.cpp
# End Section
# Section DMViewer : {E9E074FA-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcWeighting
# 	2:10:HeaderFile:vcweighting.h
# 	2:8:ImplFile:vcweighting.cpp
# End Section
# Section DMViewer : {E9E0751F-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTick
# 	2:10:HeaderFile:vctick.h
# 	2:8:ImplFile:vctick.cpp
# End Section
# Section DMViewer : {E9E0752A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPoints
# 	2:10:HeaderFile:vcdatapoints.h
# 	2:8:ImplFile:vcdatapoints.cpp
# End Section
# Section DMViewer : {E9E074EE-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLightSources
# 	2:10:HeaderFile:vclightsources.h
# 	2:8:ImplFile:vclightsources.cpp
# End Section
# Section DMViewer : {E9E074E2-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcBackdrop
# 	2:10:HeaderFile:vcbackdrop.h
# 	2:8:ImplFile:vcbackdrop.cpp
# End Section
# Section DMViewer : {E9E07523-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcValueScale
# 	2:10:HeaderFile:vcvaluescale.h
# 	2:8:ImplFile:vcvaluescale.cpp
# End Section
# Section DMViewer : {E9E07513-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesCollection
# 	2:10:HeaderFile:vcseriescollection.h
# 	2:8:ImplFile:vcseriescollection.cpp
# End Section
# Section DMViewer : {E9E074DE-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFill
# 	2:10:HeaderFile:vcfill.h
# 	2:8:ImplFile:vcfill.cpp
# End Section
# Section DMViewer : {E9E0750A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLabels
# 	2:10:HeaderFile:vclabels.h
# 	2:8:ImplFile:vclabels.cpp
# End Section
# Section DMViewer : {E9E074F2-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcView3d
# 	2:10:HeaderFile:vcview3d.h
# 	2:8:ImplFile:vcview3d.cpp
# End Section
# Section DMViewer : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section DMViewer : {E9E07517-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcCategoryScale
# 	2:10:HeaderFile:vccategoryscale.h
# 	2:8:ImplFile:vccategoryscale.cpp
# End Section
# Section DMViewer : {E9E07527-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPlot
# 	2:10:HeaderFile:vcplot.h
# 	2:8:ImplFile:vcplot.cpp
# End Section
# Section DMViewer : {E9E074CD-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcRect
# 	2:10:HeaderFile:vcrect.h
# 	2:8:ImplFile:vcrect.cpp
# End Section
# Section DMViewer : {E9E074E6-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFootnote
# 	2:10:HeaderFile:vcfootnote.h
# 	2:8:ImplFile:vcfootnote.cpp
# End Section
# Section DMViewer : {E9E0750E-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPoint
# 	2:10:HeaderFile:vcdatapoint.h
# 	2:8:ImplFile:vcdatapoint.cpp
# End Section
# Section DMViewer : {E9E074D6-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLocation
# 	2:10:HeaderFile:vclocation.h
# 	2:8:ImplFile:vclocation.cpp
# End Section
# Section DMViewer : {E9E07502-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeriesPosition
# 	2:10:HeaderFile:vcseriesposition.h
# 	2:8:ImplFile:vcseriesposition.cpp
# End Section
# Section DMViewer : {3A2B370A-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CMSChart
# 	2:10:HeaderFile:mschart.h
# 	2:8:ImplFile:mschart.cpp
# End Section
# Section DMViewer : {E9E074D1-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPen
# 	2:10:HeaderFile:vcpen.h
# 	2:8:ImplFile:vcpen.cpp
# End Section
# Section DMViewer : {E9E0751D-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcIntersection
# 	2:10:HeaderFile:vcintersection.h
# 	2:8:ImplFile:vcintersection.cpp
# End Section
# Section DMViewer : {E9E074D5-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTextLayout
# 	2:10:HeaderFile:vctextlayout.h
# 	2:8:ImplFile:vctextlayout.cpp
# End Section
# Section DMViewer : {E9E07506-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcStatLine
# 	2:10:HeaderFile:vcstatline.h
# 	2:8:ImplFile:vcstatline.cpp
# End Section
# Section DMViewer : {E9E074EC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLightSource
# 	2:10:HeaderFile:vclightsource.h
# 	2:8:ImplFile:vclightsource.cpp
# End Section
# Section DMViewer : {E9E074DC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcShadow
# 	2:10:HeaderFile:vcshadow.h
# 	2:8:ImplFile:vcshadow.cpp
# End Section
# Section DMViewer : {E9E074FC-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcWall
# 	2:10:HeaderFile:vcwall.h
# 	2:8:ImplFile:vcwall.cpp
# End Section
# Section DMViewer : {E9E07511-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcSeries
# 	2:10:HeaderFile:vcseries.h
# 	2:8:ImplFile:vcseries.cpp
# End Section
# Section DMViewer : {E9E07521-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisScale
# 	2:10:HeaderFile:vcaxisscale.h
# 	2:8:ImplFile:vcaxisscale.cpp
# End Section
# Section DMViewer : {E9E074F0-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLight
# 	2:10:HeaderFile:vclight.h
# 	2:8:ImplFile:vclight.cpp
# End Section
# Section DMViewer : {E9E074E0-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcFrame
# 	2:10:HeaderFile:vcframe.h
# 	2:8:ImplFile:vcframe.cpp
# End Section
# Section DMViewer : {E9E07515-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxisTitle
# 	2:10:HeaderFile:vcaxistitle.h
# 	2:8:ImplFile:vcaxistitle.cpp
# End Section
# Section DMViewer : {E9E074C9-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcCoor
# 	2:10:HeaderFile:vccoor.h
# 	2:8:ImplFile:vccoor.cpp
# End Section
# Section DMViewer : {E9E074E4-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcTitle
# 	2:10:HeaderFile:vctitle.h
# 	2:8:ImplFile:vctitle.cpp
# End Section
# Section DMViewer : {E9E074F4-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcPlotBase
# 	2:10:HeaderFile:vcplotbase.h
# 	2:8:ImplFile:vcplotbase.cpp
# End Section
# Section DMViewer : {E9E074CB-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcLCoor
# 	2:10:HeaderFile:vclcoor.h
# 	2:8:ImplFile:vclcoor.cpp
# End Section
# Section DMViewer : {E9E0750C-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcDataPointLabel
# 	2:10:HeaderFile:vcdatapointlabel.h
# 	2:8:ImplFile:vcdatapointlabel.cpp
# End Section
# Section DMViewer : {E9E07525-BA0A-11D1-B137-0000F8753F5D}
# 	2:5:Class:CVcAxis
# 	2:10:HeaderFile:vcaxis.h
# 	2:8:ImplFile:vcaxis.cpp
# End Section
