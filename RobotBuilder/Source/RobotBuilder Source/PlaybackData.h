// PlaybackData.h: interface for the CPlaybackData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYBACKDATA_H__5F8F1520_812E_474B_9CFC_A5A0A2A6C830__INCLUDED_)
#define AFX_PLAYBACKDATA_H__5F8F1520_812E_474B_9CFC_A5A0A2A6C830__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wt.h>

typedef struct
{
	WTp3 wtp3Position;
	WTm3 wtm3Orientation;
} structSnapShotItem;

typedef struct
{
	double dTime;
	structSnapShotItem* arraySnapShotItems;
} structSnapShot;


#define PLAYBACK_END -1.0  // Indicates the request for the next time 
									// can't be returned because at the end of the playback
									// data

class CPlaybackData  
{
public:
	void InitializeFromFile (int nNumberOfItems, CString strArticulationFile, CString strEnvironmentFile, FILETIME filetimeArticulation, FILETIME filetimeEnvironment);
	void GetPlaybackInfo (int &rnNumberOfItems, CString &rstrArticulationFile, CString &rstrEnvironmentFile, FILETIME &rfiletimeArticulation, FILETIME &rfiletimeEnvironment) const;
	BOOL ContainsData () const;
	int GetNumberOfItems () const;
	double PeekNextSnapShotTime () const;
	void GetPlaybackTimes (double &rdStartTime, double &rdEndTime);
	void DeleteCurrentSnapShot ();
	BOOL CheckFiles (CString strArticulationPath, CString strArticulationFile, 
		CString strEnvironmentPath, CString strEnvironmentFile, BOOL bCompareTimes);
	void GetNextSnapShotItem (WTp3 wtp3Position, WTm3 wtm3Orientation);
	BOOL GetNextSnapShot (double &rdTime);
	void ResetPlayback ();
	void AddItemData (const WTp3 wtp3Position, const WTm3 wtm3Orientation);
	void Initialize (int nNumberOfItems, CString strArticulationPath, CString strArticulationFile,
		CString strEnvironmentPath, CString strEnvironmentFile);
	void AddSnapShot (double dTime);
	CPlaybackData();
	virtual ~CPlaybackData();
	void CleanUp ();
protected:
	CArray<structSnapShot, structSnapShot> m_SnapShotArray;
	int m_nNumberOfItemsPerSnapShot;

	CString m_strArticulationPath;
	CString m_strArticulationFile;
	CString m_strEnvironmentPath;
	CString m_strEnvironmentFile;
	FILETIME m_filetimeArticulation, m_filetimeEnvironment;


private:
	int m_nCurrentSnapShotItemIndex;
	int m_nCurrentSnapShotIndex;

};

#endif // !defined(AFX_PLAYBACKDATA_H__5F8F1520_812E_474B_9CFC_A5A0A2A6C830__INCLUDED_)
