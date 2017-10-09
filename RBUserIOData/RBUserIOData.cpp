// RBUserIOData.cpp: implementation of the RBUserIOData class.
//
//////////////////////////////////////////////////////////////////////

#include "RBUserIOData.h"

#include <crtdbg.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RBUserIOData::RBUserIOData()
{
   m_nNumberOfOutputWindows = 0;
   m_bLockSettingsData = false;

   m_pstrtSliderSetup = NULL;
   m_nNumberOfSliders = 0;

   m_pstrtCheckBoxSetup = NULL;
   m_nNumberOfCheckBoxes = 0;

   m_pstrtLabelSetup = NULL;
   m_nNumberOfLabels = 0;

   m_pstrtOutputListSetup = NULL;
   m_nNumberOfOutputLists = 0;

	m_pstrtEditSetup = NULL;
	m_nNumberOfEdits = 0;

	m_pstrtButtonSetup = NULL;
	m_nNumberOfButtons = 0;

	m_nLastError = NO_RBUSERIODATA_ERROR;

//   m_pstrtChartSetup = NULL;
//   m_nNumberOfCharts = 0;
}

RBUserIOData::~RBUserIOData()
{

	// Note that it is upto the client to call CleanUp to deallocate the members.  I can't
	// call it here because if this is a release build, and the client is a debug build, the
	// local heaps will be different (they are allocated relative to the client heap, but
	// the destructor is called relative to the host heap) and the program will fault.
}
/*
// Calling this function will reset any output window data settings already
// specified. 
// This cannot be called during simulation
void RBUserIOData::SetNumberOfOutputWindows(int nNumber)
{
   // If given an invalid number make it 0
   if (nNumber < 0 || nNumber > 10)
      nNumber = 0;

   // Can't be called during simulation
   if (m_bLockSettingsData)
      return;

   m_nNumberOfOutputWindows = nNumber;
}

int RBUserIOData::GetNumberOfOutputWindows() const
{
   return m_nNumberOfOutputWindows;
}
*/
// This is called by RobotBuilder to remind the users not to change the settings
// data while the simulation is running.
void RBUserIOData::LockSettingsData()
{
   m_bLockSettingsData = true;
}

// Should only be called at initialization
bool RBUserIOData::SetNumberOfSliders(int nNumber)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   // If given an invalid number make it 0
   if (nNumber < 0 || nNumber > MAX_NUMBER_OF_CONTROLS)
   {
      m_nLastError = ERROR_INVALID_NUMBER_OF_CONTROLS;
      return false;
   }

   // Deallocate any slider setup elements
   if (m_pstrtSliderSetup)
   {
      delete [] m_pstrtSliderSetup;
   }

   // Allocate new setups
   m_pstrtSliderSetup = new structSliderSetup[nNumber];


   // Initialize the data in case the user forgets to
   int i;
   for (i = 0; i < nNumber; i++)
   {
      m_pstrtSliderSetup[i].nPosX = 0;
      m_pstrtSliderSetup[i].nPosY = 0;
      m_pstrtSliderSetup[i].nWidth = 0;
      m_pstrtSliderSetup[i].nHeight = 0;
      m_pstrtSliderSetup[i].strLabel = "";
      m_pstrtSliderSetup[i].nMinValue = 0;
      m_pstrtSliderSetup[i].nMaxValue = 0;
      m_pstrtSliderSetup[i].nValue = 0;
   }

   m_nNumberOfSliders = nNumber;

   return true;
}

// Should only be called at initialization after the number of controls are specified
bool RBUserIOData::SetupSlider(int nIndex, int nPosX, int nPosY, int nWidth, int nHeight,
                               int nMinValue, int nMaxValue, int nInitialValue, string strLabel)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   if (nIndex < 0 || nIndex >= m_nNumberOfSliders)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   if (nPosX < 0 || nPosX > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_POSX;
      return false;
   }

   if (nPosY < 0 || nPosY > MAX_SIZE_Y)
   {
      m_nLastError = ERROR_INVALID_POSY;
      return false;
   }
   
   if (nWidth < 0 || nWidth > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_WIDTH;
      return false;
   }

   if (nHeight < 0 || nHeight > MAX_SIZE_Y)
   {
      m_nLastError = ERROR_INVALID_HEIGHT;
      return false;
   }

   // Save the data
   m_pstrtSliderSetup[nIndex].nPosX = nPosX;
   m_pstrtSliderSetup[nIndex].nPosY = nPosY;
   m_pstrtSliderSetup[nIndex].nWidth = nWidth;
   m_pstrtSliderSetup[nIndex].nHeight = nHeight;
   m_pstrtSliderSetup[nIndex].nMinValue = nMinValue;
   m_pstrtSliderSetup[nIndex].nMaxValue = nMaxValue;
   m_pstrtSliderSetup[nIndex].nValue = nInitialValue; 
   m_pstrtSliderSetup[nIndex].strLabel = strLabel;

   return true;
}

// Intended to be used by RB
int RBUserIOData::GetNumberOfSliders() const
{
   return m_nNumberOfSliders;
}

// Intended to be used by RB
bool RBUserIOData::GetSliderSetup(int nIndex, structSliderSetup *pstrtSliderSetup)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfSliders)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   pstrtSliderSetup->nPosX = m_pstrtSliderSetup[nIndex].nPosX;
   pstrtSliderSetup->nPosY = m_pstrtSliderSetup[nIndex].nPosY;
   pstrtSliderSetup->nWidth = m_pstrtSliderSetup[nIndex].nWidth;
   pstrtSliderSetup->nHeight = m_pstrtSliderSetup[nIndex].nHeight;
   pstrtSliderSetup->nMinValue = m_pstrtSliderSetup[nIndex].nMinValue;
   pstrtSliderSetup->nMaxValue = m_pstrtSliderSetup[nIndex].nMaxValue;
   pstrtSliderSetup->nValue = m_pstrtSliderSetup[nIndex].nValue;
   pstrtSliderSetup->strLabel = m_pstrtSliderSetup[nIndex].strLabel;

   return true;
}

// Intended to be used by RB
bool RBUserIOData::SetSliderValue(int nIndex, int nValue)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfSliders)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
   m_pstrtSliderSetup[nIndex].nValue = nValue;

   return true;
}

// Intended to be used by the control dll in the compute control
bool RBUserIOData::GetSliderValue(int nIndex, int &rnValue)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfSliders)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
   rnValue = m_pstrtSliderSetup[nIndex].nValue;

   return true;
}

///////////////// CheckBox ///////////////////

// Should only be called at initialization
bool RBUserIOData::SetNumberOfCheckBoxes (int nNumber)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   // If given an invalid number make it 0
   if (nNumber < 0 || nNumber > MAX_NUMBER_OF_CONTROLS)
   {
      m_nLastError = ERROR_INVALID_NUMBER_OF_CONTROLS;
      return false;
   }

   // Deallocate any check box setup elements
   if (m_pstrtCheckBoxSetup)
   {
      delete [] m_pstrtCheckBoxSetup;
   }

   // Allocate new setups
   m_pstrtCheckBoxSetup = new structCheckBoxSetup[nNumber];

   // Initialize the data in case the user forgets to
   int i;
   for (i = 0; i < nNumber; i++)
   {
      m_pstrtCheckBoxSetup[i].nPosX = 0;
      m_pstrtCheckBoxSetup[i].nPosY = 0;
      m_pstrtCheckBoxSetup[i].strLabel = "";
      m_pstrtCheckBoxSetup[i].bValue = false;
   }

   m_nNumberOfCheckBoxes = nNumber;

   return true;
}

// Should only be called at initialization after the number of controls are specified
bool RBUserIOData::SetupCheckBox(int nIndex, int nPosX, int nPosY,
                               bool bInitialValue, string strLabel)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   if (nIndex < 0 || nIndex >= m_nNumberOfCheckBoxes)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   if (nPosX < 0 || nPosX > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_POSX;
      return false;
   }

   if (nPosY < 0 || nPosY > MAX_SIZE_Y)
   {
      m_nLastError = ERROR_INVALID_POSY;
      return false;
   }
   

   // Save the data
   m_pstrtCheckBoxSetup[nIndex].nPosX = nPosX;
   m_pstrtCheckBoxSetup[nIndex].nPosY = nPosY;
   m_pstrtCheckBoxSetup[nIndex].bValue = bInitialValue; 
   m_pstrtCheckBoxSetup[nIndex].strLabel = strLabel;

   return true;
}

// Intended to be used by RB
int RBUserIOData::GetNumberOfCheckBoxes() const
{
   return m_nNumberOfCheckBoxes;
}

// Intended to be used by RB
bool RBUserIOData::GetCheckBoxSetup(int nIndex, structCheckBoxSetup *pstrtCheckBoxSetup)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfCheckBoxes)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   pstrtCheckBoxSetup->nPosX = m_pstrtCheckBoxSetup[nIndex].nPosX;
   pstrtCheckBoxSetup->nPosY = m_pstrtCheckBoxSetup[nIndex].nPosY;
   pstrtCheckBoxSetup->bValue = m_pstrtCheckBoxSetup[nIndex].bValue;
   pstrtCheckBoxSetup->strLabel = m_pstrtCheckBoxSetup[nIndex].strLabel;

   return true;
}

// Intended to be used by RB
bool RBUserIOData::SetCheckBoxValue(int nIndex, bool bValue)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfCheckBoxes)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
   m_pstrtCheckBoxSetup[nIndex].bValue = bValue;

   return true;
}

// Intended to be used by the control dll in the compute control
bool RBUserIOData::GetCheckBoxValue(int nIndex, bool &rbValue)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfCheckBoxes)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
   rbValue = m_pstrtCheckBoxSetup[nIndex].bValue;

   return true;
}

///////////////// Edit /////////////////////

// Should only be called at initialization
bool RBUserIOData::SetNumberOfEdits(int nNumber)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   // If given an invalid number make it 0
   if (nNumber < 0 || nNumber > MAX_NUMBER_OF_CONTROLS)
   {
      m_nLastError = ERROR_INVALID_NUMBER_OF_CONTROLS;
      return false;
   }

   // Deallocate any slider setup elements
   if (m_pstrtEditSetup)
   {
      delete [] m_pstrtEditSetup;
   }

   // Allocate new setups
   m_pstrtEditSetup = new structEditSetup[nNumber];


   // Initialize the data in case the user forgets to
   int i;
   for (i = 0; i < nNumber; i++)
   {
      m_pstrtEditSetup[i].nPosX = 0;
      m_pstrtEditSetup[i].nPosY = 0;
      m_pstrtEditSetup[i].nWidth = 0;
      m_pstrtEditSetup[i].strLabel = "";
      m_pstrtEditSetup[i].strData = "";
   }

   m_nNumberOfEdits = nNumber;

   return true;
}

// Should only be called at initialization after the number of controls are specified
bool RBUserIOData::SetupEdit(int nIndex, int nPosX, int nPosY, int nWidth, 
									  string strInitialData, string strLabel)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   if (nIndex < 0 || nIndex >= m_nNumberOfEdits)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   if (nPosX < 0 || nPosX > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_POSX;
      return false;
   }

   if (nPosY < 0 || nPosY > MAX_SIZE_Y)
   {
      m_nLastError = ERROR_INVALID_POSY;
      return false;
   }
   
   if (nWidth < 0 || nWidth > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_WIDTH;
      return false;
   }

   // Save the data
   m_pstrtEditSetup[nIndex].nPosX = nPosX;
   m_pstrtEditSetup[nIndex].nPosY = nPosY;
   m_pstrtEditSetup[nIndex].nWidth = nWidth;
   m_pstrtEditSetup[nIndex].strData = strInitialData; 
   m_pstrtEditSetup[nIndex].strLabel = strLabel;

   return true;
}

// Intended to be used by RB
int RBUserIOData::GetNumberOfEdits() const
{
   return m_nNumberOfEdits;
}

// Intended to be used by RB
bool RBUserIOData::GetEditSetup(int nIndex, structEditSetup *pstrtEditSetup)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfEdits)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   pstrtEditSetup->nPosX = m_pstrtEditSetup[nIndex].nPosX;
   pstrtEditSetup->nPosY = m_pstrtEditSetup[nIndex].nPosY;
   pstrtEditSetup->nWidth = m_pstrtEditSetup[nIndex].nWidth;
   pstrtEditSetup->strData = m_pstrtEditSetup[nIndex].strData;
   pstrtEditSetup->strLabel = m_pstrtEditSetup[nIndex].strLabel;

   return true;
}

// Intended to be used by RB
bool RBUserIOData::SetEditValue(int nIndex, string strData)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfEdits)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
	// MUST copy to local, otherwise string will reference count, but the count
	// will get confused in the calling function and then result in a memory access
	// violation!!!!!
	char buffer[255];
	strncpy (buffer, strData.c_str (), 255);
   m_pstrtEditSetup[nIndex].strData = buffer;
   return true;
}

// Intended to be used by the control dll in the compute control
bool RBUserIOData::GetEditValue(int nIndex, string &rstrData)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfEdits)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
   rstrData = m_pstrtEditSetup[nIndex].strData;

   return true;
}



///////////////// Button /////////////////////

// Should only be called at initialization
bool RBUserIOData::SetNumberOfButtons(int nNumber)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   // If given an invalid number make it 0
   if (nNumber < 0 || nNumber > MAX_NUMBER_OF_CONTROLS)
   {
      m_nLastError = ERROR_INVALID_NUMBER_OF_CONTROLS;
      return false;
   }

   // Deallocate any button setup elements
   if (m_pstrtButtonSetup)
   {
      delete [] m_pstrtButtonSetup;
   }

   // Allocate new setups
   m_pstrtButtonSetup = new structButtonSetup[nNumber];


   // Initialize the data in case the user forgets to
   int i;
   for (i = 0; i < nNumber; i++)
   {
      m_pstrtButtonSetup[i].nPosX = 0;
      m_pstrtButtonSetup[i].nPosY = 0;
      m_pstrtButtonSetup[i].nWidth = 0;
      m_pstrtButtonSetup[i].nHeight = 0;
      m_pstrtButtonSetup[i].bClicked = false;
		m_pstrtButtonSetup[i].strLabel = "";
   }

   m_nNumberOfButtons = nNumber;

   return true;
}

// Should only be called at initialization after the number of controls are specified
bool RBUserIOData::SetupButton(int nIndex, int nPosX, int nPosY, int nWidth, int nHeight,
									  string strLabel)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   if (nIndex < 0 || nIndex >= m_nNumberOfButtons)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   if (nPosX < 0 || nPosX > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_POSX;
      return false;
   }

   if (nPosY < 0 || nPosY > MAX_SIZE_Y)
   {
      m_nLastError = ERROR_INVALID_POSY;
      return false;
   }
   
   if (nWidth < 0 || nWidth > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_WIDTH;
      return false;
   }

   if (nHeight < 0 || nHeight > MAX_SIZE_Y)
   {
      m_nLastError = ERROR_INVALID_WIDTH;
      return false;
   }

   // Save the data
   m_pstrtButtonSetup[nIndex].nPosX = nPosX;
   m_pstrtButtonSetup[nIndex].nPosY = nPosY;
   m_pstrtButtonSetup[nIndex].nWidth = nWidth;
   m_pstrtButtonSetup[nIndex].nHeight = nHeight;
   m_pstrtButtonSetup[nIndex].bClicked = false; 
   m_pstrtButtonSetup[nIndex].strLabel = strLabel;

   return true;
}

// Intended to be used by RB
int RBUserIOData::GetNumberOfButtons () const
{
   return m_nNumberOfButtons;
}

// Intended to be used by RB
bool RBUserIOData::GetButtonSetup(int nIndex, structButtonSetup *pstrtButtonSetup)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfButtons)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   pstrtButtonSetup->nPosX = m_pstrtButtonSetup[nIndex].nPosX;
   pstrtButtonSetup->nPosY = m_pstrtButtonSetup[nIndex].nPosY;
   pstrtButtonSetup->nWidth = m_pstrtButtonSetup[nIndex].nWidth;
   pstrtButtonSetup->nHeight = m_pstrtButtonSetup[nIndex].nHeight;
   pstrtButtonSetup->bClicked = m_pstrtButtonSetup[nIndex].bClicked;
   pstrtButtonSetup->strLabel = m_pstrtButtonSetup[nIndex].strLabel;

   return true;
}

// Intended to be used by RB
bool RBUserIOData::SetButtonClicked (int nIndex)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfButtons)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
   m_pstrtButtonSetup[nIndex].bClicked = true;

   return true;
}

// Intended to be used by the control dll in the compute control
bool RBUserIOData::GetButtonClicked (int nIndex, bool &rbClicked)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfButtons)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
   rbClicked = m_pstrtButtonSetup[nIndex].bClicked;

	//  Now that the state has been retrieved, reset the value to false
	m_pstrtButtonSetup[nIndex].bClicked = false;

   return true;
}  



///////////////// Label ///////////////////

// Should only be called at initialization
bool RBUserIOData::SetNumberOfLabels (int nNumber)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   // If given an invalid number make it 0
   if (nNumber < 0 || nNumber > MAX_NUMBER_OF_CONTROLS)
   {
      m_nLastError = ERROR_INVALID_NUMBER_OF_CONTROLS;
      return false;
   }

   // Deallocate any check box setup elements
   if (m_pstrtLabelSetup)
   {
      delete [] m_pstrtLabelSetup;
   }

   // Allocate new setups
   m_pstrtLabelSetup = new structLabelSetup[nNumber];

   // Initialize the data in case the user forgets to
   int i;
   for (i = 0; i < nNumber; i++)
   {
      m_pstrtLabelSetup[i].nPosX = 0;
      m_pstrtLabelSetup[i].nPosY = 0;
      m_pstrtLabelSetup[i].nWidthInChars = 0;
      m_pstrtLabelSetup[i].bNewData = false;
      m_pstrtLabelSetup[i].strValue = "";
   }

   m_nNumberOfLabels = nNumber;

   return true;
}

// Should only be called at initialization after the number of controls are specified
bool RBUserIOData::SetupLabel(int nIndex, int nPosX, int nPosY,
                               int nWidthInChars, string strValue)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   if (nIndex < 0 || nIndex >= m_nNumberOfLabels)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   if (nPosX < 0 || nPosX > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_POSX;
      return false;
   }

   if (nPosY < 0 || nPosY > MAX_SIZE_Y)
   {
      m_nLastError = ERROR_INVALID_POSY;
      return false;
   }
   

   // Save the data
   m_pstrtLabelSetup[nIndex].nPosX = nPosX;
   m_pstrtLabelSetup[nIndex].nPosY = nPosY;
   m_pstrtLabelSetup[nIndex].nWidthInChars = nWidthInChars; 
   m_pstrtLabelSetup[nIndex].bNewData = false;
   m_pstrtLabelSetup[nIndex].strValue = strValue;

   return true;
}

// Intended to be used by RB
int RBUserIOData::GetNumberOfLabels() const
{
   return m_nNumberOfLabels;
}

// Intended to be used by RB
bool RBUserIOData::GetLabelSetup(int nIndex, structLabelSetup *pstrtLabelSetup)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfLabels)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   pstrtLabelSetup->nPosX = m_pstrtLabelSetup[nIndex].nPosX;
   pstrtLabelSetup->nPosY = m_pstrtLabelSetup[nIndex].nPosY;
   pstrtLabelSetup->nWidthInChars = m_pstrtLabelSetup[nIndex].nWidthInChars;
   pstrtLabelSetup->bNewData = m_pstrtLabelSetup[nIndex].bNewData;
   pstrtLabelSetup->strValue = m_pstrtLabelSetup[nIndex].strValue;

   return true;
}

// Intended to be used by the controller
bool RBUserIOData::SetLabelValue(int nIndex, string strValue)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfLabels)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
   // Check to see if this is different than what is currently being displayed
   if (strValue != m_pstrtLabelSetup[nIndex].strValue)
   {
      // New data
      m_pstrtLabelSetup[nIndex].strValue = strValue;
      m_pstrtLabelSetup[nIndex].bNewData = true;
   }
   
   return true;
}

// Intended to be used by RB
bool RBUserIOData::GetLabelValue(int nIndex, string &rstrValue)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfLabels)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   if (!m_pstrtLabelSetup[nIndex].bNewData)
   {
      m_nLastError = ERROR_NO_NEW_DATA;
      return false;
   }
   
   rstrValue = m_pstrtLabelSetup[nIndex].strValue;
   m_pstrtLabelSetup[nIndex].bNewData = false;

   return true;
}

bool RBUserIOData::IsThereNewLabelData (int nIndex, bool &rbNewData)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfLabels)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   rbNewData = m_pstrtLabelSetup[nIndex].bNewData;

   return true;
}


///////////////// Output List ///////////////////

// Should only be called at initialization
bool RBUserIOData::SetNumberOfOutputLists (int nNumber)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   // If given an invalid number make it 0
   if (nNumber < 0 || nNumber > MAX_NUMBER_OF_CONTROLS)
   {
      m_nLastError = ERROR_INVALID_NUMBER_OF_CONTROLS;
      return false;
   }

   // Deallocate any check box setup elements
   if (m_pstrtOutputListSetup)
   {
      delete [] m_pstrtOutputListSetup;
   }

   // Allocate new setups
   m_pstrtOutputListSetup = new structOutputListSetup[nNumber];

   // Initialize the data in case the user forgets to
   int i;
   for (i = 0; i < nNumber; i++)
   {
      m_pstrtOutputListSetup[i].nPosX = 0;
      m_pstrtOutputListSetup[i].nPosY = 0;
      m_pstrtOutputListSetup[i].nWidth = 0;
		m_pstrtOutputListSetup[i].nHeight = 0;
      m_pstrtOutputListSetup[i].bNewData = false;
		m_pstrtOutputListSetup[i].strData = "";
      m_pstrtOutputListSetup[i].strLabels = "";
   }

   m_nNumberOfOutputLists = nNumber;

   return true;
}

// Should only be called at initialization after the number of controls are specified
bool RBUserIOData::SetupOutputList(int nIndex, int nPosX, int nPosY,
                               int nWidth, int nHeight, string strLabels)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   if (nIndex < 0 || nIndex >= m_nNumberOfOutputLists)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   if (nPosX < 0 || nPosX > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_POSX;
      return false;
   }

   if (nPosY < 0 || nPosY > MAX_SIZE_Y)
   {
      m_nLastError = ERROR_INVALID_POSY;
      return false;
   }
   
   if (nWidth < 0 || nWidth > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_WIDTH;
      return false;
   }

   if (nHeight < 0 || nHeight > MAX_SIZE_Y)
   {
      m_nLastError = ERROR_INVALID_HEIGHT;
      return false;
   }

   // Save the data
   m_pstrtOutputListSetup[nIndex].nPosX = nPosX;
   m_pstrtOutputListSetup[nIndex].nPosY = nPosY;
   m_pstrtOutputListSetup[nIndex].nWidth = nWidth;
   m_pstrtOutputListSetup[nIndex].nHeight = nHeight;
   m_pstrtOutputListSetup[nIndex].bNewData = false;
   m_pstrtOutputListSetup[nIndex].strData = "";
   m_pstrtOutputListSetup[nIndex].strLabels = strLabels;

   return true;
}

// Intended to be used by RB
int RBUserIOData::GetNumberOfOutputLists() const
{
   return m_nNumberOfOutputLists;
}

// Intended to be used by RB
bool RBUserIOData::GetOutputListSetup(int nIndex, structOutputListSetup *pstrtOutputListSetup)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfOutputLists)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   pstrtOutputListSetup->nPosX = m_pstrtOutputListSetup[nIndex].nPosX;
   pstrtOutputListSetup->nPosY = m_pstrtOutputListSetup[nIndex].nPosY;
   pstrtOutputListSetup->nWidth = m_pstrtOutputListSetup[nIndex].nWidth;
   pstrtOutputListSetup->nHeight = m_pstrtOutputListSetup[nIndex].nHeight;
   pstrtOutputListSetup->bNewData = m_pstrtOutputListSetup[nIndex].bNewData;
   pstrtOutputListSetup->strLabels = m_pstrtOutputListSetup[nIndex].strLabels;
   pstrtOutputListSetup->strData = m_pstrtOutputListSetup[nIndex].strData;

   return true;
}

// Intended to be used by the controller
// strData is tab separated per column
bool RBUserIOData::SetOutputListData(int nIndex, string strData)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfOutputLists)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
   // Check to see if this is different than what is currently being displayed
   if (strData != m_pstrtOutputListSetup[nIndex].strData)
   {
      // New data
      m_pstrtOutputListSetup[nIndex].strData = strData;
      m_pstrtOutputListSetup[nIndex].bNewData = true;
   }
   
   return true;
}

// Intended to be used by RB
bool RBUserIOData::GetOutputListData(int nIndex, string &rstrData)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfOutputLists)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   if (!m_pstrtOutputListSetup[nIndex].bNewData)
   {
      m_nLastError = ERROR_NO_NEW_DATA;
      return false;
   }
   
   rstrData = m_pstrtOutputListSetup[nIndex].strData;
   m_pstrtOutputListSetup[nIndex].bNewData = false;

   return true;
}

bool RBUserIOData::IsThereNewOutputListData (int nIndex, bool &rbNewData)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfOutputLists)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   rbNewData = m_pstrtOutputListSetup[nIndex].bNewData;

   return true;
}

/////////// Project Directory ///////////////////
string RBUserIOData::GetProjectDirectory () const
{
	return m_strProjectDirectory;
}

void RBUserIOData::SetProjectDirectory (string strDirectory)
{
	m_strProjectDirectory = strDirectory;
}



/*
///////////////// Chart ///////////////////

// Should only be called at initialization
bool RBUserIOData::SetNumberOfCharts (int nNumber)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   // If given an invalid number make it 0
   if (nNumber < 0 || nNumber > MAX_NUMBER_OF_CONTROLS)
   {
      m_nLastError = ERROR_INVALID_NUMBER_OF_CONTROLS;
      return false;
   }

   // Deallocate any check box setup elements
   if (m_pstrtChartSetup)
   {
      delete [] m_pstrtChartSetup;
   }

   // Allocate new setups
   m_pstrtChartSetup = new structChartSetup[nNumber];

   // Initialize the data in case the user forgets to
   int i;
   for (i = 0; i < nNumber; i++)
   {
      m_pstrtChartSetup[i].nPosX = 0;
      m_pstrtChartSetup[i].nPosY = 0;
      m_pstrtChartSetup[i].nSideLength = 0;
      m_pstrtChartSetup[i].strLabel = "";
		m_pstrtChartSetup[i].bNewData = false;
		m_pstrtChartSetup[i].dXValue = 0;
		m_pstrtChartSetup[i].dYValue = 0;
   }

   m_nNumberOfCharts = nNumber;

   return true;
}

// Should only be called at initialization after the number of controls are specified
bool RBUserIOData::SetupChart(int nIndex, int nPosX, int nPosY,
                               int nSideLength, string strLabel)
{
   // Can't be called during simulation
   if (m_bLockSettingsData)
   {
      m_nLastError = ERROR_SETUP_LOCKED;
      return false;
   }

   if (nIndex < 0 || nIndex >= m_nNumberOfCharts)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   if (nPosX < 0 || nPosX > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_POSX;
      return false;
   }

   if (nPosY < 0 || nPosY > MAX_SIZE_Y)
   {
      m_nLastError = ERROR_INVALID_POSY;
      return false;
   }
   
   if (nSideLength < 0 || nSideLength > MAX_SIZE_X)
   {
      m_nLastError = ERROR_INVALID_WIDTH;
      return false;
   }

   // Save the data
   m_pstrtChartSetup[nIndex].nPosX = nPosX;
   m_pstrtChartSetup[nIndex].nPosY = nPosY;
   m_pstrtChartSetup[nIndex].nSideLength = nSideLength; 
   m_pstrtChartSetup[nIndex].strLabel = strLabel;


   return true;
}

// Intended to be used by RB
int RBUserIOData::GetNumberOfCharts() const
{
   return m_nNumberOfCharts;
}

// Intended to be used by RB
bool RBUserIOData::GetChartSetup(int nIndex, structChartSetup *pstrtChartSetup)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfCharts)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

   pstrtChartSetup->nPosX = m_pstrtChartSetup[nIndex].nPosX;
   pstrtChartSetup->nPosY = m_pstrtChartSetup[nIndex].nPosY;
   pstrtChartSetup->nSideLength = m_pstrtChartSetup[nIndex].nSideLength;
   pstrtChartSetup->strLabel = m_pstrtChartSetup[nIndex].strLabel;


   return true;
}

// Intended to be used by control
// This will set a flag so that RB knows there is new data in here
// to add to the chart
bool RBUserIOData::SetNewChartData(int nIndex, double dX, double dY)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfCharts)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
   m_pstrtChartSetup[nIndex].bNewData = true;
	m_pstrtChartSetup[nIndex].dXValue = dX;
   m_pstrtChartSetup[nIndex].dYValue = dY;

   return true;
}

// Intended to be used by RB
// Checks if there is new data - to know if need to get it and add to chart
bool RBUserIOData::IsThereNewChartData (int nIndex, bool &rbNewData) 
{
   if (nIndex < 0 || nIndex >= m_nNumberOfCharts)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }

	rbNewData = m_pstrtChartSetup[nIndex].bNewData;

	return true;
}

// Intended to be used by RB
bool RBUserIOData::GetNewChartData(int nIndex, double &rdX, double &rdY)
{
   if (nIndex < 0 || nIndex >= m_nNumberOfCheckBoxes)
   {
      m_nLastError = ERROR_INVALID_CONTROL_INDEX;
      return false;
   }
   
   if (m_pstrtChartSetup[nIndex].bNewData != true)
   {
      m_nLastError = ERROR_NO_NEW_DATA;
      return false;
   }

	// Reset the new data flag, since picking it up
   m_pstrtChartSetup[nIndex].bNewData = false;
	rdX = m_pstrtChartSetup[nIndex].dXValue;
   rdY = m_pstrtChartSetup[nIndex].dYValue;

   return true;
}
*/

void RBUserIOData::CleanUp()
{
   if (m_pstrtSliderSetup)
   {
      delete [] m_pstrtSliderSetup;
		m_pstrtSliderSetup = NULL;
   }

   if (m_pstrtCheckBoxSetup)
   {
      delete [] m_pstrtCheckBoxSetup;
		m_pstrtCheckBoxSetup = NULL;
   }

   if (m_pstrtLabelSetup)
   {
      delete [] m_pstrtLabelSetup;
		m_pstrtLabelSetup = NULL;
   }

   if (m_pstrtOutputListSetup)
   {
      delete [] m_pstrtOutputListSetup;
		m_pstrtOutputListSetup = NULL;
   }

	if (m_pstrtEditSetup)
	{
		delete [] m_pstrtEditSetup;
		m_pstrtEditSetup = NULL;
	}

   if (m_pstrtButtonSetup)
   {
      delete [] m_pstrtButtonSetup;
		m_pstrtButtonSetup = NULL;
   }
}

int RBUserIOData::GetLastError() const
{
	return m_nLastError;
}
