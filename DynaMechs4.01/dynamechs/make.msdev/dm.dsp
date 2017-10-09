# Microsoft Developer Studio Project File - Name="dm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=dm - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dm.mak" CFG="dm - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dm - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dm - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dm - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib/platform.msvc60.i686"
# PROP Intermediate_Dir "../obj/platform.msvc60.i686"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /Op /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DM_EXPORTS" /YX /FD /c
# ADD CPP /nologo /G6 /MD /W3 /GR /GX /O2 /Op /I "..\dm" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "dm_DLL_FILE" /D "NO_DM_DEBUG_PRINTS" /FD /TP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib Glu32.lib Opengl32.lib /nologo /dll /incremental:yes /machine:I386 /libpath:"../lib/platform.msvc60.i686"

!ELSEIF  "$(CFG)" == "dm - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib/platform.msvc60.i686.dbg"
# PROP Intermediate_Dir "../obj/platform.msvc60.i686.dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DM_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /MDd /W3 /GR /GX /Z7 /Od /I "..\dm" /D "dm_DLL_FILE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /GZ /TP /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib Glu32.lib Opengl32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"../lib/platform.msvc60.i686.dbg"

!ENDIF 

# Begin Target

# Name "dm - Win32 Release"
# Name "dm - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\dm\dmActuator.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmArticulation.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmClosedArticulation.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmContactModel.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmEnvironment.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmForce.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmIntegEuler.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmIntegPlacement.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmIntegrator.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmIntegRK4.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmIntegRK45.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmLink.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmMDHLink.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmMobileBaseLink.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmObject.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmPrismaticLink.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmQuaternionLink.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmRevDCMotor.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmRevoluteLink.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmRigidBody.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSecondaryForce.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSecondaryJoint.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSecondaryPrismaticJoint.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSecondaryRevoluteJoint.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSecondarySphericalJoint.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSphericalLink.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmStaticRootLink.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSystem.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmTreadmill.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmZScrewTxLink.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\gldraw.cpp
# End Source File
# Begin Source File

SOURCE=..\dm\svd_linpack.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\dm\dm.h
# End Source File
# Begin Source File

SOURCE=..\dm\dmActuator.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmArticulation.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmClosedArticulation.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmContactModel.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmEnvironment.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmForce.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmIntegEuler.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmIntegPlacement.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmIntegrator.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmIntegRK4.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmIntegRK45.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmLink.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmMDHLink.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmMobileBaseLink.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmObject.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmPrismaticLink.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmQuaternionLink.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmRevDCMotor.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmRevoluteLink.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmRigidBody.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSecondaryForce.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSecondaryJoint.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSecondaryPrismaticJoint.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSecondaryRevoluteJoint.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSecondarySphericalJoint.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSphericalLink.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmStaticRootLink.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmSystem.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmTime.h
# End Source File
# Begin Source File

SOURCE=..\dm\dmTreadmill.hpp
# End Source File
# Begin Source File

SOURCE=..\dm\dmZScrewTxLink.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
