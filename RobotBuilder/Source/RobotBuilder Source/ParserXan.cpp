// ParserXan.cpp: implementation of the CParserXan class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dmviewer.h"
#include "ParserXan.h"

#include <wt.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParserXan::CParserXan()
{

}

CParserXan::~CParserXan()
{

}

BOOL CParserXan::ParseXanFileAndBuildGeometry (CString strFile, WTgeometry **pwtGeometry)
{
	// Line Number
	int nCurrentLineNumber = 1;

	// Open the file
	ifstream istrmXanFile (strFile);
	if (!istrmXanFile) 
	{
		CString strError;
		strError.Format ("Failed to open %s.", strFile);
		AfxMessageBox (strError);
		return FALSE;
	}

	// Advance to the first token in case it starts as blanks.
	if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
	{
		FormatError(istrmXanFile, nCurrentLineNumber, strFile,
			"Error before first field.");
		return FALSE;
	}

	structMaterial strtMaterial;
	// Parse emission
	istrmXanFile >> strtMaterial.afEmission[0] >> strtMaterial.afEmission[1] >>
		strtMaterial.afEmission[2];
	if (!istrmXanFile.good ())
	{
		ParseError (istrmXanFile, nCurrentLineNumber, strFile,
			"Expected: <float - emission red> <float - emission green> <float - emission blue>");
		return FALSE;
	}
	// Validate the data
	if (strtMaterial.afEmission[0] < MODEL_COLOR_MIN || strtMaterial.afEmission[0] > MODEL_COLOR_MAX ||
		strtMaterial.afEmission[1] < MODEL_COLOR_MIN || strtMaterial.afEmission[1] > MODEL_COLOR_MAX ||
		strtMaterial.afEmission[2] < MODEL_COLOR_MIN || strtMaterial.afEmission[2] > MODEL_COLOR_MAX)
	{
		CString strError;
		strError.Format ("%f <= Emission Color <= %.1f", MODEL_COLOR_MIN, MODEL_COLOR_MAX);
		ValidationError (istrmXanFile, nCurrentLineNumber, strFile, strError);
		return FALSE;		
	}
	if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
	{
		FormatError (istrmXanFile, nCurrentLineNumber, strFile,
			"Error after Emission Color field.");
		return FALSE;			
	}

	// Parse ambient
	istrmXanFile >> strtMaterial.afAmbient[0] >> strtMaterial.afAmbient[1] >>
		strtMaterial.afAmbient[2];
	if (!istrmXanFile.good ())
	{
		ParseError (istrmXanFile, nCurrentLineNumber, strFile,
			"Expected: <float - ambient red> <float - ambient green> <float - ambient blue>");
		return FALSE;
	}
	// Validate the data
	if (strtMaterial.afAmbient[0] < MODEL_COLOR_MIN || strtMaterial.afAmbient[0] > MODEL_COLOR_MAX ||
		strtMaterial.afAmbient[1] < MODEL_COLOR_MIN || strtMaterial.afAmbient[1] > MODEL_COLOR_MAX ||
		strtMaterial.afAmbient[2] < MODEL_COLOR_MIN || strtMaterial.afAmbient[2] > MODEL_COLOR_MAX)
	{
		CString strError;
		strError.Format ("%f <= Ambient Color <= %.1f", MODEL_COLOR_MIN, MODEL_COLOR_MAX);
		ValidationError (istrmXanFile, nCurrentLineNumber, strFile, strError);
		return FALSE;		
	}
	if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
	{
		FormatError (istrmXanFile, nCurrentLineNumber, strFile,
			"Error after Ambient Color field.");
		return FALSE;			
	}

	// Parse diffuse
	istrmXanFile >> strtMaterial.afDiffuse[0] >> strtMaterial.afDiffuse[1] >>
		strtMaterial.afDiffuse[2];
	if (!istrmXanFile.good ())
	{
		ParseError (istrmXanFile, nCurrentLineNumber, strFile,
			"Expected: <float - diffuse red> <float - diffuse green> <float - diffuse blue>");
		return FALSE;
	}
	// Validate the data
	if (strtMaterial.afDiffuse[0] < MODEL_COLOR_MIN || strtMaterial.afDiffuse[0] > MODEL_COLOR_MAX ||
		strtMaterial.afDiffuse[1] < MODEL_COLOR_MIN || strtMaterial.afDiffuse[1] > MODEL_COLOR_MAX ||
		strtMaterial.afDiffuse[2] < MODEL_COLOR_MIN || strtMaterial.afDiffuse[2] > MODEL_COLOR_MAX)
	{
		CString strError;
		strError.Format ("%f <= Diffuse Color <= %.1f", MODEL_COLOR_MIN, MODEL_COLOR_MAX);
		ValidationError (istrmXanFile, nCurrentLineNumber, strFile, strError);
		return FALSE;		
	}
	if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
	{
		FormatError (istrmXanFile, nCurrentLineNumber, strFile,
			"Error after Diffuse Color field.");
		return FALSE;			
	}

	// Parse specular
	istrmXanFile >> strtMaterial.afSpecular[0] >> strtMaterial.afSpecular[1] >>
		strtMaterial.afSpecular[2];
	if (!istrmXanFile.good ())
	{
		ParseError (istrmXanFile, nCurrentLineNumber, strFile,
			"Expected: <float - specular red> <float - specular green> <float - specular blue>");
		return FALSE;
	}
	// Validate the data
	if (strtMaterial.afSpecular[0] < MODEL_COLOR_MIN || strtMaterial.afSpecular[0] > MODEL_COLOR_MAX ||
		strtMaterial.afSpecular[1] < MODEL_COLOR_MIN || strtMaterial.afSpecular[1] > MODEL_COLOR_MAX ||
		strtMaterial.afSpecular[2] < MODEL_COLOR_MIN || strtMaterial.afSpecular[2] > MODEL_COLOR_MAX)
	{
		CString strError;
		strError.Format ("%f <= Specular Color <= %.1f", MODEL_COLOR_MIN, MODEL_COLOR_MAX);
		ValidationError (istrmXanFile, nCurrentLineNumber, strFile, strError);
		return FALSE;		
	}
	if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
	{
		FormatError (istrmXanFile, nCurrentLineNumber, strFile,
			"Error after Specular Color field.");
		return FALSE;			
	}

	// Parse shininess
	istrmXanFile >> strtMaterial.fShininess;
	if (!istrmXanFile.good ())
	{
		ParseError (istrmXanFile, nCurrentLineNumber, strFile,
			"Expected: <float - shininess>");
		return FALSE;
	}
	// Validate the data
	if (strtMaterial.fShininess < MODEL_SHININESS_MIN || strtMaterial.fShininess > MODEL_SHININESS_MAX)
	{
		CString strError;
		strError.Format ("%f <= Shininess <= %.1f", MODEL_SHININESS_MIN, MODEL_SHININESS_MAX);
		ValidationError (istrmXanFile, nCurrentLineNumber, strFile, strError);
		return FALSE;		
	}
	if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
	{
		FormatError (istrmXanFile, nCurrentLineNumber, strFile,
			"Error after Shininess field.");
		return FALSE;			
	}

	// Parse alpha
	istrmXanFile >> strtMaterial.fAlpha;
	if (!istrmXanFile.good ())
	{
		ParseError (istrmXanFile, nCurrentLineNumber, strFile,
			"Expected: <float - alpha>");
		return FALSE;
	}
	// Validate the data
	if (strtMaterial.fAlpha < MODEL_COLOR_MIN || strtMaterial.fAlpha > MODEL_COLOR_MAX)
	{
		CString strError;
		strError.Format ("%f <= Shininess <= %.1f", MODEL_COLOR_MIN, MODEL_COLOR_MAX);
		ValidationError (istrmXanFile, nCurrentLineNumber, strFile, strError);
		return FALSE;		
	}
	if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
	{
		FormatError (istrmXanFile, nCurrentLineNumber, strFile,
			"Error after Alpha field.");
		return FALSE;			
	}

	// Parse scale
	structScaleVector strtScaleVector;
	istrmXanFile >> strtScaleVector.fXScale >> strtScaleVector.fYScale >>
		strtScaleVector.fZScale;
	if (!istrmXanFile.good ())
	{
		ParseError (istrmXanFile, nCurrentLineNumber, strFile,
			"Expected: <float - scale> <float - scale> <float - scale>");
		return FALSE;
	}
	if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
	{
		FormatError (istrmXanFile, nCurrentLineNumber, strFile,
			"Error after Scale field.");
		return FALSE;			
	}

	// Parse vertices and face numbers
	int nNumberOfVertices;
	int nNumberOfFaces;
	istrmXanFile >> nNumberOfVertices >> nNumberOfFaces;
	if (!istrmXanFile.good ())
	{
		ParseError (istrmXanFile, nCurrentLineNumber, strFile,
			"Expected: <int - vertices> <int - faces>");
		return FALSE;
	}
	// Validate the data
	if (nNumberOfVertices < MODEL_VERTICES_MIN || nNumberOfVertices > MODEL_VERTICES_MAX)
	{
		CString strError;
		strError.Format ("%d <= Vertices <= %d", MODEL_VERTICES_MIN, MODEL_VERTICES_MAX);
		ValidationError (istrmXanFile, nCurrentLineNumber, strFile, strError);
		return FALSE;		
	}
	if (nNumberOfFaces < MODEL_FACES_MIN || nNumberOfFaces > MODEL_FACES_MAX)
	{
		CString strError;
		strError.Format ("%d <= Faces <= %d", MODEL_FACES_MIN, MODEL_FACES_MAX);
		ValidationError (istrmXanFile, nCurrentLineNumber, strFile, strError);
		return FALSE;		
	}
	if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
	{
		FormatError (istrmXanFile, nCurrentLineNumber, strFile,
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
	}	catch (CMemoryException*)
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
		istrmXanFile >> (pstrtVertices + i)->x >> (pstrtVertices + i)->y >>
			(pstrtVertices + i)->z;
		if (!istrmXanFile.good ())
		{
			ParseError (istrmXanFile, nCurrentLineNumber, strFile,
				"Expected: <float - vertex x> <float - vertex y> <float - vertex z>");
			FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);
			return FALSE;
		}

		// Note that the vertices are scaled here before saving
		(pstrtVertices + i)->x *= strtScaleVector.fXScale;
		(pstrtVertices + i)->y *= strtScaleVector.fYScale;
		(pstrtVertices + i)->z *= strtScaleVector.fZScale;

		if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
		{
			FormatError (istrmXanFile, nCurrentLineNumber, strFile,
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
		istrmXanFile >> (pstrtFaces + i)->nNumberOfVertices;
		if (!istrmXanFile.good ())
		{
			ParseError (istrmXanFile, nCurrentLineNumber, strFile,
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
			ValidationError (istrmXanFile, nCurrentLineNumber, strFile, strError);
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
		EatWhite (istrmXanFile);
		// Look at the next character.  If it's a comment char or new line, go to the 
		// next data, otherwise, read the field as data
		if (istrmXanFile.peek () == '#' || istrmXanFile.peek () == '\n')
		{
			if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
			{
				FormatError (istrmXanFile, nCurrentLineNumber, strFile,
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
			istrmXanFile >> *(((pstrtFaces + i)->pVertexArray) + j);
			if (!istrmXanFile.good ())
			{
				ParseError (istrmXanFile, nCurrentLineNumber, strFile,
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
				ValidationError (istrmXanFile, nCurrentLineNumber, strFile, strError);
				FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);
				return FALSE;		
			}
		}
		// Don't call this on the last line, in case the file doens't end with a \n
		if (i < (nNumberOfFaces - 1))
		{
			if (!GotoNextData (istrmXanFile, nCurrentLineNumber))
			{
				FormatError (istrmXanFile, nCurrentLineNumber, strFile,
					"Error after Vertex Index field.");
				FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);
				return FALSE;			
			}
		}
	}

	// Close the file
	istrmXanFile.close ();

	// Build it
	BuildGeometry (&strtMaterial, nNumberOfVertices, pstrtVertices, nNumberOfFaces,
		pstrtFaces, pwtGeometry);
		
	// Free the memory
	FreeAllocatedMemory (pstrtVertices, nNumberOfFaces, pstrtFaces);

	return TRUE;
}

void CParserXan::ValidationError(ifstream &istrmXanFile, int nCurrentLineNumber, 
									   CString strFilename, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Validation error in %s on line %d.\n%s",
			strFilename, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmXanFile.close ();
}

void CParserXan::ParseError(ifstream &istrmXanFile, int nCurrentLineNumber, 
									   CString strFilename, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Parse error in %s on line %d.\n%s",
			strFilename, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmXanFile.close ();
}

void CParserXan::FormatError(ifstream &istrmXanFile, int nCurrentLineNumber, 
									   CString strFilename, CString strMessage)
{
	CString strErrorMessage;
	strErrorMessage.Format ("Format error in %s on line %d.\n%s",
			strFilename, nCurrentLineNumber, strMessage);
	AfxMessageBox (strErrorMessage);
	istrmXanFile.close ();
}

void CParserXan::FreeAllocatedMemory(structVertex *pstrtVertices, 
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

void CParserXan::BuildGeometry(structMaterial *pstrtMaterial, 
							   int nNumberOfVertices, const structVertex *pstrtVertices, 
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
		WTpoly_setbothsides (wtpolyFace, FALSE);
		ASSERT (flagStatus);
	}

	// now close the geometry
	FLAG flagStatus = WTgeometry_close (*pwtgeometry);
	ASSERT (flagStatus);

	// now compute the normals for shading purposes
//	WTvertex* wtvertex;
//	flagStatus = WTgeometry_beginedit (*pwtgeometry);
//	ASSERT (flagStatus);
//	wtvertex = WTgeometry_getvertices (*pwtgeometry);
//	ASSERT (wtvertex); // There should be more than zero vertices
//	while (wtvertex)
//	{
//		WTgeometry_computevertexnormal (*pwtgeometry, wtvertex);
//		wtvertex = WTvertex_next (wtvertex);
//	}
//	flagStatus = WTgeometry_endedit (*pwtgeometry);
//	ASSERT (flagStatus);

	// Now at the color information
	WTmtable* wtmtable;
	wtmtable = WTmtable_new (
		WTMAT_AMBIENT | WTMAT_DIFFUSE | WTMAT_EMISSION | WTMAT_SPECULAR |
		WTMAT_OPACITY | WTMAT_SHININESS,
		1, /* estimated entries */
		NULL /* unique name - if NULL WTK makes up one*/);
	ASSERT (wtmtable);

	int nMTableIndex = 0; // index in to material table
	nMTableIndex = WTmtable_newentry (wtmtable);
	// Verify that this is the only entry in the table
	ASSERT (nMTableIndex == 0);

	FLAG flagReturn;
	flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
		pstrtMaterial->afAmbient, WTMAT_AMBIENT);
	ASSERT (flagReturn);

	flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
		pstrtMaterial->afDiffuse, WTMAT_DIFFUSE);
	ASSERT (flagReturn);

	flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
		pstrtMaterial->afEmission, WTMAT_EMISSION);
	ASSERT (flagReturn);

	flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
		pstrtMaterial->afSpecular, WTMAT_SPECULAR);
	ASSERT (flagReturn);

	flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
		&(pstrtMaterial->fShininess), WTMAT_SHININESS);
	ASSERT (flagReturn);

	flagReturn = WTmtable_setvalue (wtmtable, nMTableIndex,
		&(pstrtMaterial->fAlpha), WTMAT_OPACITY);
	ASSERT (flagReturn);

	WTgeometry_setmtable (*pwtgeometry, wtmtable);
	flagReturn = WTgeometry_setmatid (*pwtgeometry, nMTableIndex);
	ASSERT (flagReturn);
}
