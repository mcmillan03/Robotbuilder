

#ifndef PARSER_TYPES_H
#define PARSER_TYPES_H

#define MODEL_COLOR_MIN	0.0f
#define MODEL_COLOR_MAX	1.0f
#define MODEL_SHININESS_MIN	0.0f
#define MODEL_SHININESS_MAX	128.0f
#define MODEL_FACES_MIN	3
#define MODEL_FACES_MAX	1e6
#define MODEL_VERTICES_MIN	3
#define MODEL_VERTICES_MAX	1e6
#define	MODEL_VERTICES_PER_FACE_MIN	3
#define	MODEL_VERTICES_PER_FACE_MAX	1e6
#define MODEL_CMB_FILE_COUNT_MIN	1
#define MODEL_CMB_FILE_COUNT_MAX	1e6	

typedef struct
{
	int nNumberOfVertices;
	int* pVertexArray;
} structFace;

typedef struct
{
	float x;
	float y;
	float z;
} structVertex;

typedef struct
{
	float afEmission[3];
	float afAmbient[3];
	float afDiffuse[3];
	float afSpecular[3];
	float fShininess;
	float fAlpha;
} structMaterial;


typedef struct
{
	float fXScale;
	float fYScale;
	float fZScale;
} structScaleVector;


#endif