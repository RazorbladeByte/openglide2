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
        uint32_t     startAddress;
        uint32_t     endAddress;
        GrTexInfo    info;
        uint32_t     hash;
        GLuint       texNum;
        GLuint       tex2Num;
        Record       *next;

        Record( bool two_tex );
        ~Record( void );
        bool Match( uint32_t stt, GrTexInfo *inf, uint32_t h );
    };

    void Add( uint32_t startAddress, uint32_t endAddress, GrTexInfo *info, 
		      uint32_t hash, GLuint *pTexNum, GLuint *pTex2Num );
    void WipeRange( uint32_t startAddress, uint32_t endAddress, uint32_t hash );
    GrTexInfo * Find( uint32_t startAddress, GrTexInfo *info, uint32_t hash, 
                      GLuint *pTexNum, GLuint *pTex2Num, bool *pal_change );
    TexDB( uint32_t MemorySize );
    virtual ~TexDB( void );

private:
    uint32_t numberOfTexSections;
    Record ** m_first;
};

#endif
