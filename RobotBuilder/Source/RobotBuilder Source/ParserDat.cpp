// ParserDat.cpp: implementation of the CParserDat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "ParserDat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserDat::CParserDat()
{

}

CParserDat::~CParserDat()
{

}

BOOL CParserDat::ParseDatFileAndBuildGeometry (CString strFile, WTgeometry **pwtGeometry)
{
	// Line Number
	int nCurrentLineNumber = 1;

	// Open the file
	ifstream istrmDatFile (strFile);
	if (!istrmDatFile) 
	{
		CString strError;
		strError.Format ("Failed to open %s.", strFile);
		AfxMessageBox (strError);
		return FALSE;
	}

	// Advance to the first token in case it starts as blanks.
	if (!GotoNextData (istrmDatFile, nCurrentLineNumber))
	{
		FormatError(istrmDatFile, nCurrentLineNumber, strFile,
			"Error before first field.");
		return FALSE;
	}

	// Parse vertices and face numbers
	int nNumberOfVertices;
	int nNumberOfFaces;
	istrmDatFile >> nNumberOfVertices >> nNumberOfFaces;
	if (!istrmDatFile.good ())
	{
		ParseError (istrmDatFile, nCurrentLineNumber, strFile,
			"Expected: <int - vertices> <int - faces>");
		return FALSE;
	}
	// Validate the data
	if (nNumberOfVertices < MODEL_VERTICES_MIN || nNumberOfVertices > MODEL_VERTICES_MAX)
	{
		CString strError;
		strError.Format ("%d <= Vertices <= %d", MODEL_VERTICES_MIN, MODEL_VERTICES_MAX);
		ValidationError (istrmDatFile, nCurrentLineNumber, strFile, strError);
		return FALSE;		
	}
	if (nNumberOfFaces < MODEL_FACES_MIN || nNumberOfFaces > MODEL_FACES_MAX)
	{
		CString strError;
		strError.Format ("%d <= Faces <= %d", MODEL_FACES_MIN, MODEL_FACES_MAX);
		ValidationError (istrmDatFile, nCurrentLineNumber, strFile, strError);
		return FALSE;		
	}
	if (!GotoNextData (istrmDatFile, nCurrentLineNumber))
	{
		FormatError (istrmDatFile, nCurrentLineNumber, strFile,
			"Error after Vertices and Faces field.");
		return FALSE;			
	}
	// Allocate memory for the vertices and faces
	structVertex *pstrtVertices;
	structFace *pstrtFaces;
	try
	{
		pstrtVertices = new structVertex[nNumberOfVertices];
		pstrtFaces = new structFace[nNumberOfFaces];
	}
	catch (CMemoryException*)
	{
		AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
		AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
		// Throw exception to next handler to break out of this function
		throw;
	}
	// initialize the points to for the faces NULL, that way we know if need to 
	// free what they point to later, if the program ends unexpectedly
	int i;
	for (i = 0; i < nNumberOfFaces; i++)
	{
		(pstrtFaces + i)->pVertexArray = NULL;
	}
	
	// Read in the vertices
	for (i = 0; i < nNumberOfVertices; i++)
	{
		// Parse vertex
		istrmDatFile >> (pstrtVertices + i)->x >> (pstrtVertices + i)->y >>
			(pstrtVertices + i)->z;
		if (!istrmDatFile.good ())
		{
			ParseError (istrmDatFile, nCurrentLineNumber, strFile,
				"Expected: <float - vertex x> <float - vertex y> <float - vertex z>");
			FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);
			return FALSE;
		}

		if (!GotoNextData (istrmDatFile, nCurrentLineNumber))
		{
			FormatError (istrmDatFile, nCurrentLineNumber, strFile,
				"Error after Vertex field.");
			FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);
			return FALSE;			
		}
	}

	// Read in the vertices per face
	// This may extend for multiple lines, so I need to peek and see if it's
	// data before I read it
	for (i = 0; i < nNumberOfFaces; i++)
	{
		// Read in the vertex count for the face
		istrmDatFile >> (pstrtFaces + i)->nNumberOfVertices;
		if (!istrmDatFile.good ())
		{
			ParseError (istrmDatFile, nCurrentLineNumber, strFile,
				"Expected: ... <int - vertex count> ...");
			FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);
			return FALSE;
		}
		// Validate the data
		if ((pstrtFaces + i)->nNumberOfVertices < MODEL_VERTICES_PER_FACE_MIN || 
			(pstrtFaces + i)->nNumberOfVertices > MODEL_VERTICES_PER_FACE_MAX)
		{
			CString strError;
			strError.Format ("%d <= Vertices Per Face <= %d", MODEL_VERTICES_PER_FACE_MIN,
				MODEL_VERTICES_PER_FACE_MAX);
			ValidationError (istrmDatFile, nCurrentLineNumber, strFile, strError);
			FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);
			return FALSE;		
		}
		// Allocate space to hold the vertices
		try
		{
			(pstrtFaces + i)->pVertexArray = new int [(pstrtFaces + i)->nNumberOfVertices];
		}
		catch (CMemoryException*)
		{
			AfxMessageBox (IDS_STRING_OUT_OF_MEM_MSG, MB_OK);
			AfxGetMainWnd ()->PostMessage (WM_CLOSE); 
			// Throw exception to next handler to break out of this function
			throw;
		}

		// Remove the next whitespace
		EatWhite (istrmDatFile);
		// Look at the next character.  If it's a comment char or new line, go to the 
		// next data, otherwise, read the field as data
		if (istrmDatFile.peek () == '#' || istrmDatFile.peek () == '\n')
		{
			if (!GotoNextData (istrmDatFile, nCurrentLineNumber))
			{
				FormatError (istrmDatFile, nCurrentLineNumber, strFile,
					"Error after Vertices per face field.");
				FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);
				return FALSE;			
			}
		}
	}

	// Define the polygon faces by the vertex indices
	for (i = 0; i < nNumberOfFaces; i++)
	{
		// Get a copy of the number of vertices for this face
		int nVertexCount = (pstrtFaces + i)->nNumberOfVertices;
		// Read each vertex
		int j;
		for (j = 0; j < nVertexCount; j++)
		{
			istrmDatFile >> *(((pstrtFaces + i)->pVertexArray) + j);
			if (!istrmDatFile.good ())
			{
				ParseError (istrmDatFile, nCurrentLineNumber, strFile,
					"Expected: ... <int - vertex index> ...");
				FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);
				return FALSE;
			}
			// Validate the data
			if (*(((pstrtFaces + i)->pVertexArray) + j) < 0 || 
				*(((pstrtFaces + i)->pVertexArray) + j) > nNumberOfVertices - 1)
			{
				CString strError;
				strError.Format ("%d <= Vertex Index <= %d", 0,
					nNumberOfVertices - 1);
				ValidationError (istrmDatFile, nCurrentLineNumber, strFile, strError);
				FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);
				return FALSE;		
			}
		}
		// Don't call this on the last line, in case the file doens't end with a \n
		if (i < (nNumberOfFaces - 1))
		{
			if (!GotoNextData (istrmDatFile, nCurrentLineNumber))
			{
				FormatError (istrmDatFile, nCurrentLineNumber, strFile,
					"Error after Vertex Index field.");
				FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);
				return FALSE;			
			}
		}
	}

	// Close the file
	istrmDatFile.close ();

	// Build it
	BuildGeometry (nNumberOfVertices, pstrtVertices, nNumberOfFaces,
		pstrtFaces, pwtGeometry);
		
	// Free the memory
	FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);

	return TRUE;
}

void CParserDat::ValidationError(ifstream &istrmDatFile, int nCurrentLineNumber, 
									   CString strFilename, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Validation error in %s on line %d.\n%s",
			strFilename, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmDatFile.close ();
}

void CParserDat::ParseError(ifstream &istrmDatFile, int nCurrentLineNumber, 
									   CString strFilename, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Parse error in %s on line %d.\n%s",
			strFilename, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmDatFile.close ();
}

void CParserDat::FormatError(ifstream &istrmDatFile, int nCurrentLineNumber, 
									   CString strFilename, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Format error in %s on line %d.\n%s",
			strFilename, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmDatFile.close ();
}

void CParserDat::FreeAllocatedMemory(structVertex *pstrtVertices, 
									 int nNumberOfFaces, structFace *pstrtFaces)
{
	if (pstrtVertices)
	{
		delete[] pstrtVertices;
	}

	if (pstrtFaces)
	{
		// first free each vertex buffer
		int nCounter;
		for (nCounter = 0; nCounter < nNumberOfFaces; nCounter++)
		{
			if ((pstrtFaces + nCounter)->pVertexArray)
				delete[] ((pstrtFaces + nCounter)->pVertexArray) ;
		}

		delete[] pstrtFaces ;
	}
}

void CParserDat::BuildGeometry(int nNumberOfVertices, const structVertex *pstrtVertices, 
							   int nNumberOfFaces, const structFace *pstrtFaces,
							   WTgeometry **pwtgeometry)
{
	// based on info on page 6-21
	// initialize the geometry
	*pwtgeometry = WTgeometry_begin ();
	ASSERT (*pwtgeometry);


	// add the vertices
	int nCounter;
	for (nCounter = 0; nCounter < nNumberOfVertices; nCounter++)
	{
		WTp3 wtp3; // put the vertex points in here
		wtp3[X] = (pstrtVertices + nCounter)->x;
		wtp3[Y] = (pstrtVertices + nCounter)->y;
		wtp3[Z] = (pstrtVertices + nCounter)->z;

		WTvertex* wtVertex = WTgeometry_newvertex (*pwtgeometry, wtp3);
		ASSERT (wtVertex);
	}

	// Now add the polys
	for (nCounter = 0; nCounter < nNumberOfFaces; nCounter++)
	{
		WTpoly* wtpolyFace;

		// create the new poly
		wtpolyFace = WTgeometry_beginpoly (*pwtgeometry);
		ASSERT (wtpolyFace);

		int nNumberOfVerticesForFace = (pstrtFaces + nCounter)->nNumberOfVertices;

		int nInnerCounter;
		// front face defined by CCW vertices
		for (nInnerCounter = nNumberOfVerticesForFace - 1; nInnerCounter >= 0; nInnerCounter--)
		{
			// add the vertices to the poly
			FLAG flagStatus = WTpoly_addvertex (wtpolyFace, 
				*(((pstrtFaces + nCounter)->pVertexArray) + nInnerCounter));
			ASSERT (flagStatus);
			
		}

		// close the poly
		FLAG flagStatus = WTpoly_close (wtpolyFace);
		ASSERT (flagStatus);
	}

	// now close the geometry
	FLAG flagStatus = WTgeometry_close (*pwtgeometry);
	ASSERT (flagStatus);

	// now compute the normals for shading purposes
	WTvertex* wtvertex;
	flagStatus = WTgeometry_beginedit (*pwtgeometry);
	ASSERT (flagStatus);
	wtvertex = WTgeometry_getvertices (*pwtgeometry);
	ASSERT (wtvertex); // There should be more than zero vertices
	while (wtvertex)
	{
		WTgeometry_computevertexnormal (*pwtgeometry, wtvertex);
		wtvertex = WTvertex_next (wtvertex);
	}
	flagStatus = WTgeometry_endedit (*pwtgeometry);
	ASSERT (flagStatus);

	// The format doesn't define a color, so making the geometry white
	WTgeometry_setrgb (*pwtgeometry, 255, 255, 255);
}
