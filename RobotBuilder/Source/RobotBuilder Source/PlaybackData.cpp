// PlaybackData.cpp: implementation of the CPlaybackData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "PlaybackData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlaybackData::CPlaybackData()
{
	m_nNumberOfItemsPerSnapShot = 0;
}

CPlaybackData::~CPlaybackData()
{
	CleanUp ();
}

void CPlaybackData::AddSnapShot(double dTime)
{
	// Make sure the class has been initialized
	ASSERT (m_nNumberOfItemsPerSnapShot > 0);

	// Make sure that the time for this snapshot is later than the previous one
	if (m_SnapShotArray.GetSize () > 0)
		ASSERT (m_SnapShotArray.GetAt (m_SnapShotArray.GetSize () - 1).dTime < dTime);

	// Make sure the previous snapshot has all of its items allocated
	ASSERT (m_nCurrentSnapShotItemIndex == m_nNumberOfItemsPerSnapShot);
	
	// Allocate an new snapshot for the array
	structSnapShot strtSnapShot;
	strtSnapShot.dTime = dTime;
	try
	{
		strtSnapShot.arraySnapShotItems = new structSnapShotItem[m_nNumberOfItemsPerSnapShot];
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}

	// Add the new snap shot to the snap shot array
	m_SnapShotArray.Add (strtSnapShot);

	// Increment the index to the current snap shot
	m_nCurrentSnapShotIndex ++;

	// Reset the snap shot item index
	m_nCurrentSnapShotItemIndex = 0;

	// Make sure the index lines up
	ASSERT (m_SnapShotArray.GetSize () - 1 == m_nCurrentSnapShotIndex);
}

void CPlaybackData::Initialize(int nNumberOfItems, CString strArticulationPath, 
										 CString strArticulationFile, CString strEnvironmentPath,
										 CString strEnvironmentFile)
{
	ASSERT (nNumberOfItems > 0);

	// Clear any previous data
	CleanUp ();

	// Save the data
	m_nNumberOfItemsPerSnapShot = nNumberOfItems;
	m_strArticulationPath = strArticulationPath;
	m_strArticulationFile = strArticulationFile;
	m_strEnvironmentPath = strEnvironmentPath;
	m_strEnvironmentFile = strEnvironmentFile;

	// Reset the indices pointer
	ResetPlayback ();
	
	// Build temporary copies of the full path and file names
	CString strArticulationPathAndFile = strArticulationPath + strArticulationFile;
	CString strEnvironmentPathAndFile = strEnvironmentPath + strEnvironmentFile;


	// Check the time stamp of the dm file
	// Check if there is a dm first
	if (strArticulationPathAndFile.GetLength () > 0)
	{
		// Get the attributes of the file
		WIN32_FILE_ATTRIBUTE_DATA fileAttributes;
		if(GetFileAttributesEx (strArticulationPathAndFile, GetFileExInfoStandard, &fileAttributes))
		{
			m_filetimeArticulation = fileAttributes.ftLastWriteTime;
		}
		else
		{
			// Couldn't find the file
			m_filetimeArticulation.dwHighDateTime = 0;
			m_filetimeArticulation.dwLowDateTime = 0;
		}
	}
	// Check the time stamp of the environment file
	// Check if there is a environment first
	if (strEnvironmentPathAndFile.GetLength () > 0)
	{
		// Get the attributes of the file
		WIN32_FILE_ATTRIBUTE_DATA fileAttributes;
		if(GetFileAttributesEx (strEnvironmentPathAndFile, GetFileExInfoStandard, &fileAttributes))
		{
			m_filetimeEnvironment = fileAttributes.ftLastWriteTime;
		}
		else
		{
			// Couldn't find the file
			m_filetimeEnvironment.dwHighDateTime = 0;
			m_filetimeEnvironment.dwLowDateTime = 0;
		}
	}

}

void CPlaybackData::CleanUp()
{
	int i;
	for (i = 0; i < m_SnapShotArray.GetSize (); i++)
	{
		delete [] m_SnapShotArray.GetAt (i).arraySnapShotItems;
	}
	m_SnapShotArray.RemoveAll ();

	// Nothing left, so clear the other data
	m_nNumberOfItemsPerSnapShot = 0;
	m_strArticulationFile.Empty ();
	m_strArticulationPath.Empty ();
	m_strEnvironmentFile.Empty ();
	m_strEnvironmentPath.Empty ();
	m_filetimeArticulation.dwHighDateTime = 0;
	m_filetimeArticulation.dwLowDateTime = 0;
	m_filetimeEnvironment.dwHighDateTime = 0;
	m_filetimeEnvironment.dwLowDateTime = 0;
	ResetPlayback ();
}

// This is playback data, so the order the data is pushed in, will be the order
// it is played back
void CPlaybackData::AddItemData(const WTp3 wtp3Position, const WTm3 wtm3Orientation)
{
	// Add to the current snapshot
	int nSnapShotIndex = m_SnapShotArray.GetSize () - 1;

	// Populate the snap shot item data
	WTp3_copy (wtp3Position, 
		m_SnapShotArray.GetAt (nSnapShotIndex).arraySnapShotItems[m_nCurrentSnapShotItemIndex].wtp3Position);
	WTm3_copy (wtm3Orientation, 
		m_SnapShotArray.GetAt (nSnapShotIndex).arraySnapShotItems[m_nCurrentSnapShotItemIndex].wtm3Orientation);
	
	// Point to the next one
	m_nCurrentSnapShotItemIndex ++;
}

// Call to reset the dequeing pointers
void CPlaybackData::ResetPlayback()
{
	m_nCurrentSnapShotIndex = -1; // Start at -1 because it will be incremented before
		// it is used.
	m_nCurrentSnapShotItemIndex = m_nNumberOfItemsPerSnapShot; // This makes it look like
		// it completely finished the previous snap shot for checking on the first
		// call to GetNextSnapShot.
}


BOOL CPlaybackData::GetNextSnapShot(double &rdTime)
{
	// Check if already at end.  If so return false
	if (m_SnapShotArray.GetSize () <= m_nCurrentSnapShotIndex  + 1)
	{
		// Then have passed the end of the index
		return FALSE;
	}

	// Make sure that the previous snapshot was completely retrieved
	ASSERT (m_nCurrentSnapShotItemIndex == m_nNumberOfItemsPerSnapShot);

	// Increment the index
	m_nCurrentSnapShotIndex ++;

	// Reset the item index
	m_nCurrentSnapShotItemIndex = 0;

	// Get the next time
	rdTime = m_SnapShotArray.GetAt (m_nCurrentSnapShotIndex).dTime;

	// Return true to indicate that there is still data left
	return TRUE;
}

void CPlaybackData::GetNextSnapShotItem(WTp3 wtp3Position, WTm3 wtm3Orientation)
{
	// Make sure the index is valid
	ASSERT (m_nCurrentSnapShotItemIndex < m_nNumberOfItemsPerSnapShot);

	// Return the data
	WTp3_copy (m_SnapShotArray.GetAt (m_nCurrentSnapShotIndex).arraySnapShotItems[m_nCurrentSnapShotItemIndex].wtp3Position,
		wtp3Position);
	WTm3_copy (m_SnapShotArray.GetAt (m_nCurrentSnapShotIndex).arraySnapShotItems[m_nCurrentSnapShotItemIndex].wtm3Orientation,
		wtm3Orientation);

	// Increment the pointer to point to the next item
	m_nCurrentSnapShotItemIndex ++;
}

BOOL CPlaybackData::CheckFiles(CString strArticulationPath, CString strArticulationFile, 
										 CString strEnvironmentPath, CString strEnvironmentFile,
										 BOOL bCompareTimes)
{
	// Check if the dm is the same
	if (strArticulationFile != m_strArticulationFile)
		return FALSE;
	// Check if the environment is the same
	if (strEnvironmentFile != m_strEnvironmentFile)
		return FALSE;

	if (bCompareTimes)
	{
		// Build temporary copies of the full path and file names
		CString strArticulationPathAndFile = strArticulationPath + strArticulationFile;
		CString strEnvironmentPathAndFile = strEnvironmentPath + strEnvironmentFile;

		// Check the time stamp of the dm file
		// Check if there is a dm first
		if (strArticulationPathAndFile.GetLength () > 0)
		{
			// Get the attributes of the file
			WIN32_FILE_ATTRIBUTE_DATA fileAttributes;
			if(GetFileAttributesEx (strArticulationPathAndFile, GetFileExInfoStandard, &fileAttributes))
			{
				if (fileAttributes.ftLastWriteTime.dwHighDateTime != m_filetimeArticulation.dwHighDateTime ||
					fileAttributes.ftLastWriteTime.dwLowDateTime != m_filetimeArticulation.dwLowDateTime)
					return FALSE;
			}
			else
			{
				// Couldn't find the file.  This would be an indication of an error
				return FALSE;
			}
		}
		// Check the time stamp of the environment file
		// Check if there is a environment first
		if (strEnvironmentPathAndFile.GetLength () > 0)
		{
			// Get the attributes of the file
			WIN32_FILE_ATTRIBUTE_DATA fileAttributes;
			if(GetFileAttributesEx (strEnvironmentPathAndFile, GetFileExInfoStandard, &fileAttributes))
			{
				if (fileAttributes.ftLastWriteTime.dwHighDateTime != m_filetimeEnvironment.dwHighDateTime ||
					fileAttributes.ftLastWriteTime.dwLowDateTime != m_filetimeEnvironment.dwLowDateTime)
					return FALSE;
			}
			else
			{
				// Couldn't find the file.  This would be an indication of an error
				return FALSE;
			}
		}
	}

	// Otherwise, if get here, everything matched.
	return TRUE;
}

// This should be used if DynaMechs is crashing during record mode.  This will
// delete the current snapshot, which needs to be done, because it can't be
// completed (because DynaMechs is crashing and RB stops the simulation).
void CPlaybackData::DeleteCurrentSnapShot()
{
	// Deallocate the current snapshot
	delete [] m_SnapShotArray.GetAt (m_nCurrentSnapShotIndex).arraySnapShotItems;

	// Remove it from the array
	m_SnapShotArray.RemoveAt (m_nCurrentSnapShotIndex);

	// Decrement the index
	m_nCurrentSnapShotIndex --;
}

void CPlaybackData::GetPlaybackTimes(double &rdStartTime, double &rdEndTime)
{
	// It is assumed that this will be called only if there is valid playback
	// data
	ASSERT (m_SnapShotArray.GetSize () > 0);

	// Note that checks are made when new snap shots are added, that the new 
	// snap shots are later it time than the previous snap shot.

	// The start time will be the time of the first snap shot
	rdStartTime = m_SnapShotArray.GetAt (0).dTime;

	// The end time will be at the time of the last snap shot
	rdEndTime = m_SnapShotArray.GetAt (m_SnapShotArray.GetSize () - 1).dTime;
}

double CPlaybackData::PeekNextSnapShotTime() const
{
	// Assumed that there is valid playback data when called
	ASSERT (m_SnapShotArray.GetSize () > 0);

	// Check to see if at the end of the array (the pointer is greater
	// than the extent
	if (m_nCurrentSnapShotIndex + 1 >= m_SnapShotArray.GetSize () -  1)
	{
		// At end of array - no next time
		return PLAYBACK_END;
	}
	else
	{
		// Pick up the time and return it
		return m_SnapShotArray.GetAt (m_nCurrentSnapShotIndex + 1).dTime;
	}
}

int CPlaybackData::GetNumberOfItems() const
{
	return m_nNumberOfItemsPerSnapShot;
}

// call to determine if there is playback data currently stored
BOOL CPlaybackData::ContainsData() const
{
	if (m_SnapShotArray.GetSize () > 0)
		return TRUE;
	else
		return FALSE;
}

void CPlaybackData::GetPlaybackInfo(int &rnNumberOfItems, CString &rstrArticulationFile, 
												CString &rstrEnvironmentFile, FILETIME &rfiletimeArticulation, 
												FILETIME &rfiletimeEnvironment) const
{
	// Make sure there is data in the class
	ASSERT (ContainsData ());

	// Get number of items in each snap shot
	rnNumberOfItems = m_nNumberOfItemsPerSnapShot;

	// Get the files
	rstrArticulationFile = m_strArticulationFile;
	rstrEnvironmentFile = m_strEnvironmentFile;

	// Save the filetimes
	rfiletimeArticulation = m_filetimeArticulation;
	rfiletimeEnvironment = m_filetimeEnvironment;


}

void CPlaybackData::InitializeFromFile(int nNumberOfItems, CString strArticulationFile, 
													CString strEnvironmentFile, 
													FILETIME filetimeArticulation, 
													FILETIME filetimeEnvironment)
{
	ASSERT (nNumberOfItems > 0);

	// Clear any previous data
	CleanUp ();

	// Save the data
	m_nNumberOfItemsPerSnapShot = nNumberOfItems;
	m_strArticulationFile = strArticulationFile;
	m_strEnvironmentFile = strEnvironmentFile;
	m_filetimeArticulation = filetimeArticulation;
	m_filetimeEnvironment = filetimeEnvironment;

	// Reset the indices to reflect the new count of items
	ResetPlayback ();
}
