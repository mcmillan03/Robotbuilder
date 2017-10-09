@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by DMVIEWER.HPJ. >"hlp\DMViewer.hm"
echo. >>"hlp\DMViewer.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\DMViewer.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\DMViewer.hm"
echo. >>"hlp\DMViewer.hm"
echo // Prompts (IDP_*) >>"hlp\DMViewer.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\DMViewer.hm"
echo. >>"hlp\DMViewer.hm"
echo // Resources (IDR_*) >>"hlp\DMViewer.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\DMViewer.hm"
echo. >>"hlp\DMViewer.hm"
echo // Dialogs (IDD_*) >>"hlp\DMViewer.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\DMViewer.hm"
echo. >>"hlp\DMViewer.hm"
echo // Frame Controls (IDW_*) >>"hlp\DMViewer.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\DMViewer.hm"
REM -- Make help for Project DMVIEWER


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\DMViewer.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\DMViewer.hlp" goto :Error
if not exist "hlp\DMViewer.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\DMViewer.hlp" Debug
if exist Debug\nul copy "hlp\DMViewer.cnt" Debug
if exist Release\nul copy "hlp\DMViewer.hlp" Release
if exist Release\nul copy "hlp\DMViewer.cnt" Release
echo.
goto :done

:Error
echo hlp\DMViewer.hpj(1) : error: Problem encountered creating help file

:done
echo.
