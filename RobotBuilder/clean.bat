
REM Remove the .lib created by building RobotBuilder and RobotModeler
del /Q *.lib

REM Remove the exports and intermediate files too
del /Q *.exp *.ilk

REM Goto projects directory and clean up
cd Projects

REM Remove the intermediate and precompiled 
del /Q /S *.ilk *.exp *.lib *.obj *.pch *.pdb *.idb *.pdb

REM Note - don't remove the *.opt files - they save workspace information too (like release build info)
REM Remove non-required project files too
del /Q /S *.ncb *.plg