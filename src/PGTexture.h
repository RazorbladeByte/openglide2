//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#ifndef __PGTEXTURE_H__
#define __PGTEXTURE_H__

#include "win32.h"
#include "TexDB.h"

class PGTexture  
{
    struct TexValues
    {
        GrLOD_t      lod;
        unsigned int width;
        unsigned int height;
        unsigned int nPixels;
    };

public:
	void NCCTable( GrNCCTable_t tab );

    static unsigned int LodOffset( unsigned int evenOdd, GrTexInfo *info );
    static unsigned int MipMapMemRequired( GrLOD_t lod, GrAspectRatio_t aspectRatio, 
                                           GrTextureFormat_t format );
    void ChromakeyMode( GrChromakeyMode_t mode );
    void ChromakeyValue( GrColor_t value );
    void GetAspect( float *hAspect, float *wAspect );
    void Clear( void );
    static unsigned int TextureMemRequired( unsigned int evenOdd, GrTexInfo *info );
    bool MakeReady( void );
    void DownloadTable( GrTexTable_t type, unsigned int *data, int first, int count );
    void Source( unsigned int startAddress, unsigned int evenOdd, GrTexInfo *info );
    void DownloadMipMap( unsigned int startAddress, unsigned int evenOdd, GrTexInfo *info );
    unsigned int GetMemorySize( void );

    PGTexture( int mem_size );
    virtual ~PGTexture();

#ifdef OGL_DEBUG
    int Num_565_Tex;
    int Num_1555_Tex;
    int Num_4444_Tex;
    int Num_332_Tex;
    int Num_8332_Tex;
    int Num_Alpha_Tex;
    int Num_AlphaIntensity88_Tex;
    int Num_AlphaIntensity44_Tex;
    int Num_AlphaPalette_Tex;
    int Num_Palette_Tex;
    int Num_Intensity_Tex;
    int Num_YIQ_Tex;
    int Num_AYIQ_Tex;
    int Num_Other_Tex;
#endif

private:
    void ApplyKeyToPalette( void );
    void GetTexValues( TexValues *tval );

    unsigned int    m_tex_memory_size;
    bool            m_palette_dirty;
    unsigned int    m_palette_hash;
    TexDB *         m_db;
    GrChromakeyMode_t m_chromakey_mode;
    unsigned int    m_chromakey_value_8888;
    unsigned short  m_chromakey_value_565;
    float           m_wAspect;
    float           m_hAspect;

    unsigned int    m_tex_temp[ 256 * 256 ];
    bool            m_valid;
    unsigned char * m_memory;
    unsigned int    m_startAddress;
    unsigned int    m_evenOdd;
    GrTexInfo       m_info;
    unsigned int    m_palette[ 256 ];
    GrNCCTable_t    m_ncc_select;
    GuNccTable      m_ncc[2];
};

extern PGTexture *Textures;

#endif
