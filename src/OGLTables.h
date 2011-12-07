//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#ifndef __OGL_TABLES_H__
#define __OGL_TABLES_H__

#include "GlOgl.h"
#include "GLRender.h"

typedef struct 
{
    float h;
    float w;
} OGLAspect;

typedef struct
{
    int width;
    int height;
    int numPixels;
} OGLTexInfo;

typedef struct
{
    bool                local;
    bool                other;
    ALPHAFACTORFUNCPROC func;
} OGLAlphaTable;

typedef struct
{
    bool                local;
    bool                other;
    bool                alocal;
    bool                aother;
    COLORFACTORFUNCPROC factorfunc;
    COLORFUNCTIONPROC   func;
} OGLColorTable;

// OGLTextureTables.cpp
extern OGLAspect    texAspects[ 7 ];
extern OGLTexInfo   texInfo[ 7 ][ 9 ];
extern uint32_t nSquareLod[ 2 ][ 7 ][ 9 ];
extern uint32_t nSquareTexLod[ 2 ][ 7 ][ 9 ][ 9 ];

// OGLColorAlphaTables.cpp
extern OGLAlphaTable alphaCombineTable[ 14 ][ 17 ];
extern OGLColorTable colorCombineTable[ 14 ][ 17 ];

// OGLFogTables.cpp
extern uint32_t intStartEnd[ GR_FOG_TABLE_SIZE + 1 ];
extern uint32_t intEndMinusStart[ GR_FOG_TABLE_SIZE ];
extern float        tableIndexToW[ GR_FOG_TABLE_SIZE ];

#endif
