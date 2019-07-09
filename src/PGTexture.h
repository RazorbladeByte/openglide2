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
        uint32_t width;
        uint32_t height;
        uint32_t nPixels;
    };

public:
	void NCCTable( GrNCCTable_t tab );

    static uint32_t LodOffset( uint32_t evenOdd, GrTexInfo *info );
    static uint32_t MipMapMemRequired( GrLOD_t lod, GrAspectRatio_t aspectRatio, 
                                           GrTextureFormat_t format );
    void ChromakeyMode( GrChromakeyMode_t mode );
    void ChromakeyValue( GrColor_t value );
    void GetAspect( float *hAspect, float *wAspect );
    void Clear( void );
    static uint32_t TextureMemRequired( uint32_t evenOdd, GrTexInfo *info );
    bool MakeReady( void );
    void DownloadTable( GrTexTable_t type, uint32_t *data, int first, int count );
    void Source( uint32_t startAddress, uint32_t evenOdd, GrTexInfo *info );
    void DownloadMipMap( uint32_t startAddress, uint32_t evenOdd, GrTexInfo *info );
	//Glidos approach to above func
	void DownloadMipMapPartial( uint32_t startAddress, uint32_t evenOdd, GrTexInfo *info, int start, int end );
    uint32_t GetMemorySize( void );

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

    uint32_t    m_tex_memory_size;
    bool            m_palette_dirty;
    uint32_t    m_palette_hash;
    TexDB *         m_db;
    GrChromakeyMode_t m_chromakey_mode;
    uint32_t    m_chromakey_value_8888;
    uint16_t  m_chromakey_value_565;
    float           m_wAspect;
    float           m_hAspect;

    uint32_t    m_tex_temp[ 256 * 256 ];
    bool            m_valid;
    uint8_t * m_memory;
    uint32_t    m_startAddress;
    uint32_t    m_evenOdd;
    GrTexInfo       m_info;
    uint32_t    m_palette[ 256 ];
    GrNCCTable_t    m_ncc_select;
    GuNccTable      m_ncc[2];
};

extern PGTexture *Textures;

#endif
