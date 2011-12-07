//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#ifndef __PGUTEXTURE_H__
#define __PGUTEXTURE_H__

#include "glide.h"

class PGUTexture  
{
public:
    uint32_t MemQueryAvail( GrChipID_t tmu );
    GrMipMapId_t GetCurrentMipMap( GrChipID_t tmu );
    FxBool ChangeAttributes( GrMipMapId_t mmid, int width, int height, 
                             GrTextureFormat_t fmt, GrMipMapMode_t mm_mode, 
                             GrLOD_t smallest_lod, GrLOD_t largest_lod, 
                             GrAspectRatio_t aspect, GrTextureClampMode_t s_clamp_mode, 
                             GrTextureClampMode_t t_clamp_mode, 
                             GrTextureFilterMode_t minFilterMode, 
                             GrTextureFilterMode_t magFilterMode );
    GrMipMapInfo * GetMipMapInfo( GrMipMapId_t mmid );
    void Source( GrMipMapId_t id );
    void MemReset( void );
    void DownloadMipMapLevel( GrMipMapId_t mmid, GrLOD_t lod, const void **src );
    void DownloadMipMap( GrMipMapId_t mmid, const void *src, const GuNccTable *table );
    GrMipMapId_t AllocateMemory( GrChipID_t tmu, uint8_t odd_even_mask, int width, int height, 
                                 GrTextureFormat_t fmt, GrMipMapMode_t mm_mode, 
                                 GrLOD_t smallest_lod, GrLOD_t largest_lod, 
                                 GrAspectRatio_t aspect, GrTextureClampMode_t s_clamp_mode, 
                                 GrTextureClampMode_t t_clamp_mode, 
                                 GrTextureFilterMode_t minfilter_mode, 
                                 GrTextureFilterMode_t magfilter_mode, 
                                 float lod_bias, FxBool trilinear );

    PGUTexture( void );
    virtual ~PGUTexture( void );


private:

    enum { MAX_MM = 1024 };

    GrMipMapInfo    mm_info[ MAX_MM ];
    uint32_t    mm_start[ MAX_MM ];
    uint32_t    m_free_mem;
    GrMipMapId_t    m_free_id;
    GrMipMapId_t    m_current_id;
};

extern PGUTexture UTextures;

#endif
