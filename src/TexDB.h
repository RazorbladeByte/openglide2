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
        unsigned int startAddress;
        unsigned int endAddress;
        GrTexInfo    info;
        unsigned int hash;
        GLuint       texNum;
        GLuint       tex2Num;
        Record       *next;

        Record( bool two_tex );
        ~Record( void );
        bool Match( unsigned int stt, GrTexInfo *inf, unsigned int h );
    };

    void Add( unsigned int startAddress, unsigned int endAddress, GrTexInfo *info, 
		      unsigned int hash, GLuint *pTexNum, GLuint *pTex2Num );
    void WipeRange( unsigned int startAddress, unsigned int endAddress, unsigned int hash );
    GrTexInfo * Find( unsigned int startAddress, GrTexInfo *info, unsigned int hash, 
                      GLuint *pTexNum, GLuint *pTex2Num, bool *pal_change );
    TexDB( unsigned int MemorySize );
    virtual ~TexDB( void );

private:
    unsigned int numberOfTexSections;
    Record ** m_first;
};

#endif
