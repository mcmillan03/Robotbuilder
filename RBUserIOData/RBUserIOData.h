// RBUserIOData.h: interface for the RBUserIOData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RBUSERIODATA_H__17FCA64D_AA0A_4179_8D16_B9085089E38B__INCLUDED_)
#define AFX_RBUSERIODATA_H__17FCA64D_AA0A_4179_8D16_B9085089E38B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

using namespace std;

#define MAX_SIZE_X 1000
#define MAX_SIZE_Y 1000
#define MAX_NUMBER_OF_CONTROLS   1000

typedef struct
{
   int nPosX;
   int nPosY;
   int nWidth;
   int nHeight;
   int nMinValue;
   int nMaxValue;
   int nValue;
   string strLabel;
} structSliderSetup;

typedef struct
{
   int nPosX;
   int nPosY;
   bool bValue;
   string strLabel;
} structCheckBoxSetup;

typedef struct
{
   int nPosX;
   int nPosY;
   int nWidthInChars;
   bool bNewData;
   string strValue;
} structLabelSetup;

typedef struct
{
   int nPosX;
   int nPosY;
   int nWidth;
   int nHeight;
   bool bNewData;
	string strData;
   string strLabels;
} structOutputListSetup;

typedef struct
{
   int nPosX;
   int nPosY;
   int nWidth;
	string strData;
   string strLabel;
} structEditSetup;

typedef struct
{
   int nPosX;
   int nPosY;
	int nWidth;
	int nHeight;
   bool bClicked;
   string strLabel;
} structButtonSetup;

/*
typedef struct
{
   int nPosX;
   int nPosY;
   int nSideLength;
   string strLabel;
	bool bNewData;
	double dXValue;
	double dYValue;
} structChartSetup;*/

enum {
	NO_RBUSERIODATA_ERROR,
   ERROR_INVALID_POSX, // The position should be between 0 and MAX_SIZE_X
   ERROR_INVALID_POSY, // The position should be between 0 and MAX_SIZE_Y
   ERROR_INVALID_WIDTH, // The width should be between 0 and MAX_SIZE_X
   ERROR_INVALID_HEIGHT, // The height should be between 0 and MAX_SIZE_Y
   ERROR_INVALID_CONTROL_INDEX, // The specified index is not valid.  It must be 0 to the
      // number of controls specified
   ERROR_INVALID_NUMBER_OF_CONTROLS, // The number of controls (slider, chart, etc.)
      // must be 0 to MAX_NUMBER_OF_CONTROLS
	ERROR_NO_NEW_DATA, // New was attempted to be retrieved, but there is no
		// new data - consequently, the call is not necessary
   ERROR_SETUP_LOCKED // The setup was attempted to be changed after it was locked by
		// RobotBuilder

};


class RBUserIOData  
{
public:
	int GetLastError () const;
	void CleanUp ();
/*	// Charts
   bool GetNewChartData (int nIndex, double &rdX, double &rdY);
	bool SetNewChartData (int nIndex, double dX, double dY);
	bool GetChartSetup (int nIndex, structChartSetup* pstrtChartSetup);
	int GetNumberOfCharts () const;
	bool SetupChart (int nIndex, int nPosX, int nPosY, int nSideLength, string strLabel);
	bool SetNumberOfCharts (int nNumber);
	bool IsThereNewChartData (int nIndex, bool &rbNewData); */

	// Sliders
   bool GetSliderValue (int nIndex, int &rnValue);
	bool SetSliderValue (int nIndex, int nValue);
	bool GetSliderSetup (int nIndex, structSliderSetup* pstrtSliderSetup);
	int GetNumberOfSliders () const;
	bool SetupSlider (int nIndex, int nPosX, int nPosY, int nWidth, int nHeight, int nMinValue, int nMaxValue, int nInitalValue, string strLabel);
	bool SetNumberOfSliders (int nNumber);

   // Check box
   bool GetCheckBoxValue (int nIndex, bool &rbValue);
	bool SetCheckBoxValue (int nIndex, bool bValue);
	bool GetCheckBoxSetup (int nIndex, structCheckBoxSetup* pstrtCheckBoxSetup);
	int GetNumberOfCheckBoxes () const;
	bool SetupCheckBox (int nIndex, int nPosX, int nPosY, bool bInitalValue, string strLabel);
	bool SetNumberOfCheckBoxes (int nNumber);

   // Edit box
   bool GetEditValue (int nIndex, string &rstrValue);
	bool SetEditValue (int nIndex, string strValue);
	bool GetEditSetup (int nIndex, structEditSetup* pstrtEditSetup);
	int GetNumberOfEdits () const;
	bool SetupEdit (int nIndex, int nPosX, int nPosY, int nWidth, string strInitialData, string strLabel);
	bool SetNumberOfEdits (int nNumber);

   // Button
   bool GetButtonClicked (int nIndex, bool &rbClicked);
	bool SetButtonClicked (int nIndex);
	bool GetButtonSetup (int nIndex, structButtonSetup* pstrtButtonSetup);
	int GetNumberOfButtons () const;
	bool SetupButton (int nIndex, int nPosX, int nPosY, int nWidth, int nHeight, string strLabel);
	bool SetNumberOfButtons (int nNumber);
   
	// Label
   bool GetLabelValue (int nIndex, string &rstrValue);
	bool SetLabelValue (int nIndex, string strValue);
	bool GetLabelSetup (int nIndex, structLabelSetup* pstrtLabelSetup);
	int GetNumberOfLabels () const;
	bool SetupLabel (int nIndex, int nPosX, int nPosY, int nWidthInChars, string strInitalValue);
	bool SetNumberOfLabels (int nNumber);
   bool IsThereNewLabelData (int nIndex, bool &rbNewData);

   // Output List
   bool GetOutputListData (int nIndex, string &rstrData);
	bool SetOutputListData (int nIndex, string strData);
	bool GetOutputListSetup (int nIndex, structOutputListSetup* pstrtOutputListSetup);
	int GetNumberOfOutputLists () const;
	bool SetupOutputList (int nIndex, int nPosX, int nPosY, int nWidth, int nHeight, 
      string strLabels);
	bool SetNumberOfOutputLists (int nNumber);
   bool IsThereNewOutputListData (int nIndex, bool &rbNewData);

	// Project Directory
	string GetProjectDirectory () const;
	void SetProjectDirectory (string strDirectory);

	void LockSettingsData ();
//	int GetNumberOfOutputWindows () const;
//	void SetNumberOfOutputWindows (int nNumber);
	RBUserIOData();
	virtual ~RBUserIOData();

private:
//	structChartSetup* m_pstrtChartSetup;
//	int m_nNumberOfCharts;
   structButtonSetup* m_pstrtButtonSetup;
	int m_nNumberOfButtons;
   structEditSetup* m_pstrtEditSetup;
	int m_nNumberOfEdits;
   structOutputListSetup* m_pstrtOutputListSetup;
	int m_nNumberOfOutputLists;
   structLabelSetup* m_pstrtLabelSetup;
	int m_nNumberOfLabels;
   structCheckBoxSetup* m_pstrtCheckBoxSetup;
	int m_nNumberOfCheckBoxes;
	structSliderSetup* m_pstrtSliderSetup;
	int m_nNumberOfSliders;
	bool m_bLockSettingsData;
	int m_nNumberOfOutputWindows;
   int m_nLastError;

	string m_strProjectDirectory;
};


#endif // !defined(AFX_RBUSERIODATA_H__17FCA64D_AA0A_4179_8D16_B9085089E38B__INCLUDED_)
