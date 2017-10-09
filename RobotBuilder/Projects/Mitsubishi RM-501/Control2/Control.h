
// Steps to make a custom control.
// 1. Set up the location of the include files.  This is set in 
//    Project->Settings->C++ tab->Category: Preprocessor and then enter
//		the paths in the "Additional include directories" edit box.  Paths to the location
//    of DynaMechs (for example, ..\DynaMechs\dm, ..\DynaMechs\dmu) and the path
//    to the RBUserIOData (for example ..\RBUserIOData).  Note that DynaMechs is divided into
//		components.  You need to specifiy the dm directory for the DynaMechs classes
//		and specify the dmu directory for DynaMechs utilies like the FindLink function.  
// 2. Tell the linker to link to the DynaMechs and RBUserIOData libraries.  Enter this in
//	   Projects->Settings->Link tab->Category: Input and then enter the libraries
//	   dm.lib and dmu.lib (only needed if you use the DynaMechs utilities like FindLink) for 
//    DynaMechs and RBUserIOData.lib for the data library in the 
//    "Object/library modules" edit box.
// 3. Tell the linker where the DynaMechs and RBUserIOData libraries are.  Specify in 
//    Projects->Settings->Link tab->Category: Input in the edit box labeled 
//    "Additional library path:" (for example ..\DynaMechs\lib and ..\RBUserIOData).
// 4. Name the output file.  By default it will be named Control.dll, but you may
//		want to specify something more meaningfull that describes what it does.
//		This is done in Project->Settings->Link tab->Category: General in the 
//		"Output file name" edit box


// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CONTROL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CONTROL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef CONTROL_EXPORTS
#define CONTROL_API __declspec(dllexport)
#else
#define CONTROL_API __declspec(dllimport)
#endif

// DynaMechs
class  dmSystem;
class dmIntegrator;
class dmEnvironment;

// User settable GUI components.
class RBUserIOData;

extern "C" {
CONTROL_API int InitializeDMControl(dmSystem* pSystem, RBUserIOData *pRBUserIOData);
CONTROL_API int UninitializeDMControl(dmSystem* pSystem, RBUserIOData *pRBUserIOData);
CONTROL_API int ComputeDMControl(dmSystem* pSystem, dmIntegrator* pIntegrator, 
								   dmEnvironment* pEnvironment, RBUserIOData *pRBUserIOData, float time);
CONTROL_API int HandleKeyPress (UINT nChar, int nRepCnt);
}

void InverseKinematics (const float fT[][4], int nJointAnglesInPulseUnits[]);
