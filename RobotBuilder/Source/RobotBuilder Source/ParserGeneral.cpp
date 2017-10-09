// ParserGeneral.cpp: implementation of the CParserGeneral class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ParserGeneral.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
Format Notes:

* Comments given by COMMENT_CHAR
* Data lines must end with a newline (ie NOT an EOF at end of file)
* Lines cannont exceed MODEL_FILE_MAX_LINE - 1
* It's OK to have comments after the useful data.
* Most of these restrictions can be eased with by putting more time into coding
	if desired.
*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserGeneral::CParserGeneral()
{

}

CParserGeneral::~CParserGeneral()
{

}


/*********************************************************************\
*  Function: CParserGeneral::GotoNextData
*
*  Description: Advances over blank lines and comment lines.  It will also
*		advance past comments on the current line if a comment is found before
*		another token.
*
*  Returns:  BOOL - FALSE if EOF is reached 
*  Argument: ifstream &istrmModelFile
*
*  Created:  4/27/2001  Steven Rodenbaugh
\*********************************************************************/
BOOL CParserGeneral::GotoNextData(ifstream &istrmModelFile, int & rnCurrentLineNumber)
{
	// Create a buffer to read the info to if needed
	char szBuffer[RB_FILE_MAX_LINE];

	BOOL bContinue = TRUE;
	// Read through blank and commented lines
   while (bContinue)
   {
	   EatWhite (istrmModelFile);
				
	   // Check if end of file has been reached and if so return that
	   if (istrmModelFile.peek () == EOF)
			return FALSE;

	   if (istrmModelFile.peek () != '\n' &&
		   istrmModelFile.peek () != RB_FILE_COMMENT_CHAR)
		   bContinue = FALSE;
	   else
	   {
		   	// Get the line to more the pointer to the next line
			istrmModelFile.getline (szBuffer, RB_FILE_MAX_LINE, '\n');
			rnCurrentLineNumber++;
	   }
	}

	// If get here, then have reached next non-new line and non-comment line
	// and haven't got EOF
	return TRUE;
}


/*********************************************************************\
*  Function: CParserGeneral::EatWhite
*
*  Description: Delete white space till next non- space/tab character.
*		istream has one, but apparently not ifstream.
*
*  Returns:  void 
*  Argument: ifstream &istrmModelFile - the file being parsed
*
*  Created:  4/27/2001  Steven Rodenbaugh
\*********************************************************************/
void CParserGeneral::EatWhite(ifstream &istrmModelFile)
{
	while (istrmModelFile.peek () == ' ' ||
		istrmModelFile.peek () == '\t')
	{
		// Throw the character away
		istrmModelFile.get ();
	}
}	

// Actually this returns the substring of all but the first and last characters
string CParserGeneral::StripQuotes(string strStringInQuotes)
{
	// First check that the first and last characters are quotes
	ASSERT (strStringInQuotes[0] == '"' && strStringInQuotes[strStringInQuotes.length () - 1]
		== '"');
	string strWithoutQuotes = strStringInQuotes.substr (1, 
		strStringInQuotes.length () - 2);
	return strWithoutQuotes;
}

BOOL CParserGeneral::ReadStringInDoubleQuotes(ifstream &istrmFile, string & strField)
{
	// Initalize the input string to empty
	strField = "";

	// Read the first character, which should be the first double quote
	// Note that >> is used, so any leading whitespace before the double quote
	// will not be saved.
	char c;
	istrmFile >> c;
	if (c != '"')
	{
		// Unexpected character read
		// Put it back an return
		istrmFile.putback (c);
		return FALSE;
	}

	// Loop through looking for the final quote or a newline which would indicate an error
	// Use get because >> doesn't save white-space
	c = istrmFile.get ();
	while (1)
	{
		if (c == '"')
		{
			// Then found of of quoted string so return without adding it to the string
			return TRUE;
		}
		else if (c == '\n' || istrmFile.eof ())
		{
			// Then unexpected end so return
			return FALSE;
		}
		else
		{
			// Make a string out of the character and append the string
			string strTemp = " ";
			strTemp[0] = c;
			// Character is OK so add the character to the string
			strField.append (strTemp);

			// Read the next character -- use get becase >> doesn't save whitespace
			c = istrmFile.get ();
		}
	}
}
