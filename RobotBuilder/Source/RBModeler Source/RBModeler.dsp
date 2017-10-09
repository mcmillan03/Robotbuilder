# Microsoft Developer Studio Project File - Name="RBModeler" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RBModeler - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RBModeler.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RBModeler.mak" CFG="RBModeler - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RBModeler - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RBModeler - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RBModeler - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "c:\Program Files\wtk\include" /I "..\RobotBuilder Source" /I "..\..\..\DynaMechs4.0\dynamechs\dm" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "ROBOTMODELER" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib wtk.lib wsock32.lib winmm.lib dm.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /out:"../../RobotModeler.exe" /libpath:"c:\Program Files\wtk\lib" /libpath:"..\..\..\DynaMechs4.0\dynamechs\lib\platform.msvc60.i686" /libpath:"..\..\..\RBUserIOData\release"

!ELSEIF  "$(CFG)" == "RBModeler - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "c:\Program Files\wtk\include" /I "..\..\..\DynaMechs4.0\dynamechs\dm" /I "..\RBModler" /I "..\..\..\RBUserIOData" /I "..\..\DynaMechs4.0\dynamechs\dmu" /I "..\RBModeler Source" /I "..\RobotBuilder Source" /I "." /D "_DEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "ROBOTMODELER" /FR /Yu"stdafx.h" /FD /GZ /c
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
# ADD LINK32 opengl32.lib wtk.lib wsock32.lib winmm.lib dm.lib RBUserIOData.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrt.lib" /out:"../../RobotModelerd.exe" /pdbtype:sept /libpath:"c:\Program Files\wtk\lib" /libpath:"..\..\..\DynaMechs4.0\dynamechs\lib\platform.msvc60.i686" /libpath:"..\..\..\RBUserIOData\debug"

!ENDIF 

# Begin Target

# Name "RBModeler - Win32 Release"
# Name "RBModeler - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE="..\RobotBuilder Source\CameraControl.cpp"
# End Source File
# Begin Source File

SOURCE="..\RobotBuilder Source\CameraData.cpp"
# End Source File
# Begin Source File

SOURCE=.\ClipboardData.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboBoxPrimitives.cpp
# End Source File
# Begin Source File

SOURCE="..\RobotBuilder Source\DlgCameraControl.cpp"
# End Source File
# Begin Source File

SOURCE=.\DlgLinkPhysicalProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMovementControls.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRotationAngleAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRotationEulerAngles.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRotationQuaternion.cpp
# End Source File
# Begin Source File

SOURCE="..\RobotBuilder Source\FindFile.cpp"
# End Source File
# Begin Source File

SOURCE="..\RobotBuilder Source\HyperLink.cpp"
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Model.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelListView.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelOutputFile.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelView.cpp
# End Source File
# Begin Source File

SOURCE=.\MovementControlsView.cpp
# End Source File
# Begin Source File

SOURCE="..\RobotBuilder Source\ParserGeneral.cpp"
# End Source File
# Begin Source File

SOURCE=.\ParserModel.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageBlock.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageCone.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageCovering.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageCylinder.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageHemisphere.cpp
# End Source File
# Begin Source File

SOURCE=.\PPagePhysicalProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\PPagePlacement.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageSphere.cpp
# End Source File
# Begin Source File

SOURCE=.\PPageTruncatedCone.cpp
# End Source File
# Begin Source File

SOURCE=.\Primitive.cpp
# End Source File
# Begin Source File

SOURCE=.\PrimitiveBlock.cpp
# End Source File
# Begin Source File

SOURCE=.\PrimitiveCone.cpp
# End Source File
# Begin Source File

SOURCE=.\PrimitiveCovering.cpp
# End Source File
# Begin Source File

SOURCE=.\PrimitiveCylinder.cpp
# End Source File
# Begin Source File

SOURCE=.\PrimitiveHemisphere.cpp
# End Source File
# Begin Source File

SOURCE=.\PrimitivePlacement.cpp
# End Source File
# Begin Source File

SOURCE=.\PrimitiveScale.cpp
# End Source File
# Begin Source File

SOURCE=.\PrimitiveSphere.cpp
# End Source File
# Begin Source File

SOURCE=.\PrimitiveTruncatedCone.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetBase.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetBlock.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetCone.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetCylinder.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetHemisphere.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetSphere.cpp
# End Source File
# Begin Source File

SOURCE=.\PSheetTruncatedCone.cpp
# End Source File
# Begin Source File

SOURCE=.\RBMath.cpp
# End Source File
# Begin Source File

SOURCE=.\RBMGraphicView.cpp
# End Source File
# Begin Source File

SOURCE=.\RBModeler.cpp
# End Source File
# Begin Source File

SOURCE=.\RBModeler.rc
# End Source File
# Begin Source File

SOURCE=.\RBModelerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\RBModelerRBMGraphicView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UndoRedoData.cpp
# End Source File
# Begin Source File

SOURCE=.\WndWTK.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="..\RobotBuilder Source\CameraControl.h"
# End Source File
# Begin Source File

SOURCE="..\RobotBuilder Source\CameraData.h"
# End Source File
# Begin Source File

SOURCE=.\ClipboardData.h
# End Source File
# Begin Source File

SOURCE=.\ComboBoxPrimitives.h
# End Source File
# Begin Source File

SOURCE="..\RobotBuilder Source\DlgCameraControl.h"
# End Source File
# Begin Source File

SOURCE=.\DlgLinkPhysicalProperties.h
# End Source File
# Begin Source File

SOURCE=.\DlgMovementControls.h
# End Source File
# Begin Source File

SOURCE=.\DlgRotationAngleAxis.h
# End Source File
# Begin Source File

SOURCE=.\DlgRotationEulerAngles.h
# End Source File
# Begin Source File

SOURCE=.\DlgRotationQuaternion.h
# End Source File
# Begin Source File

SOURCE="..\RobotBuilder Source\FindFile.h"
# End Source File
# Begin Source File

SOURCE="..\RobotBuilder Source\hyperlink.h"
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Model.h
# End Source File
# Begin Source File

SOURCE=.\modellistview.h
# End Source File
# Begin Source File

SOURCE=.\ModelOutputFile.h
# End Source File
# Begin Source File

SOURCE=.\ModelView.h
# End Source File
# Begin Source File

SOURCE=.\MovementControlsView.h
# End Source File
# Begin Source File

SOURCE="..\RobotBuilder Source\ParserGeneral.h"
# End Source File
# Begin Source File

SOURCE=.\ParserModel.h
# End Source File
# Begin Source File

SOURCE=.\PPageBlock.h
# End Source File
# Begin Source File

SOURCE=.\PPageCone.h
# End Source File
# Begin Source File

SOURCE=.\PPageCovering.h
# End Source File
# Begin Source File

SOURCE=.\PPageCylinder.h
# End Source File
# Begin Source File

SOURCE=.\PPageHemisphere.h
# End Source File
# Begin Source File

SOURCE=.\PPagePhysicalProperties.h
# End Source File
# Begin Source File

SOURCE=.\PPagePlacement.h
# End Source File
# Begin Source File

SOURCE=.\PPageSphere.h
# End Source File
# Begin Source File

SOURCE=.\PPageTruncatedCone.h
# End Source File
# Begin Source File

SOURCE=.\Primitive.h
# End Source File
# Begin Source File

SOURCE=.\PrimitiveBlock.h
# End Source File
# Begin Source File

SOURCE=.\PrimitiveCone.h
# End Source File
# Begin Source File

SOURCE=.\PrimitiveCovering.h
# End Source File
# Begin Source File

SOURCE=.\PrimitiveCylinder.h
# End Source File
# Begin Source File

SOURCE=.\PrimitiveHemisphere.h
# End Source File
# Begin Source File

SOURCE=.\PrimitivePlacement.h
# End Source File
# Begin Source File

SOURCE=.\PrimitiveScale.h
# End Source File
# Begin Source File

SOURCE=.\PrimitiveSphere.h
# End Source File
# Begin Source File

SOURCE=.\PrimitiveTruncatedCone.h
# End Source File
# Begin Source File

SOURCE=.\PSheetBase.h
# End Source File
# Begin Source File

SOURCE=.\PSheetBlock.h
# End Source File
# Begin Source File

SOURCE=.\PSheetCone.h
# End Source File
# Begin Source File

SOURCE=.\PSheetCylinder.h
# End Source File
# Begin Source File

SOURCE=.\PSheetHemisphere.h
# End Source File
# Begin Source File

SOURCE=.\PSheetSphere.h
# End Source File
# Begin Source File

SOURCE=.\PSheetTruncatedCone.h
# End Source File
# Begin Source File

SOURCE=.\RBMath.h
# End Source File
# Begin Source File

SOURCE=.\RBMGraphicView.h
# End Source File
# Begin Source File

SOURCE=.\RBModeler.h
# End Source File
# Begin Source File

SOURCE=.\RBModelerDoc.h
# End Source File
# Begin Source File

SOURCE=.\RBModelerRBMGraphicView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UndoRedoData.h
# End Source File
# Begin Source File

SOURCE=.\WndWTK.h
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

SOURCE=.\res\RBModeler.ico
# End Source File
# Begin Source File

SOURCE=.\res\RBModeler.rc2
# End Source File
# Begin Source File

SOURCE=.\res\RBModelerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
