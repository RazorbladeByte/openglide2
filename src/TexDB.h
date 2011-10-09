//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#ifndef __TEXDB_H__
#define __TEXDB_H__

#include "glide.h"

class TexDB  
{
public:
    void Clear( void );

    struct Record
    {
        FxU32 startAddress;
        FxU32 endAddress;
        GrTexInfo info;
        FxU32 hash;
        GLuint texNum;
        GLuint tex2Num;
        Record *next;

        Record( bool two_tex );
        ~Record( void );
        bool Match( FxU32 stt, GrTexInfo *inf, FxU32 h );
    };

    void Add( FxU32 startAddress, FxU32 endAddress, GrTexInfo *info, FxU32 hash, GLuint *pTexNum, GLuint *pTex2Num );
    void WipeRange( FxU32 startAddress, FxU32 endAddress, FxU32 hash );
    GrTexInfo * Find( FxU32 startAddress, GrTexInfo *info, FxU32 hash, 
               GLuint *pTexNum, GLuint *pTex2Num, bool *pal_change );
    TexDB( unsigned int MemorySize );
    virtual ~TexDB( void );

private:
    unsigned int numberOfTexSections;
    Record ** m_first;
};

#endif
