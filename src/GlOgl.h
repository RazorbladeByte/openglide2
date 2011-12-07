//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

/* Main Header */

#ifndef __GLOGL_H__
#define __GLOGL_H__

//#define OGL_ALL
//#define OGL_PARTDONE
//#define OGL_NOTDONE
//#define OGL_DEBUG
//#define OGL_CRITICAL
//#define OPENGL_DEBUG
//#define OGL_PROFILING
//#define OGL_UTEX
//#define OGL_COMBINE

#ifdef OGL_ALL
 #define OGL_DONE
 #define OGL_PARTDONE
 #define OGL_NOTDONE
 #define OGL_DEBUG
 #define OGL_CRITICAL
 #define OPENGL_DEBUG
 #define OGL_PROFILING
 #define OGL_UTEX
 #define OGL_COMBINE
#endif

#include "win32.h"

#ifdef __GNUC__
 #define RDTSC(v) asm volatile ("rdtsc;" : "=A" (v) )
#else
 #define RDTSC(v)    __asm _emit 0x0f                \
                     __asm _emit 0x31                \
                     __asm mov dword ptr v, eax      \
                     __asm mov dword ptr v+4, edx
#endif

#define ERRORFILE               "openglide2.err"
#define GLIDEFILE               "openglide2.log"
#define INIFILE                 "openglide2.ini"

#define OGL_LOG_SEPARATE        "--------------------------------------------------------\n"

#define OGL_MIN_FRAME_BUFFER    2
#define OGL_MAX_FRAME_BUFFER    16
#define OGL_MIN_TEXTURE_BUFFER  2
#define OGL_MAX_TEXTURE_BUFFER  32

#define OGL_VER_1_1             101

#define OPENGLBUFFERMEMORY      OpenGL.WindowWidth * OpenGL.WindowHeight

#define OPENGLFOGTABLESIZE      64 * 1024

#define D1OVER255               0.003921568627451f      // 1 / 255
#define D1OVER65536             0.0000152587890625f     // 1 / 65536
#define D1OVER65535             0.000015259021896696421759365224689097f     // 1 / 65535
#define D1OVER256               0.00390625f             // 1 / 256
#define D2OVER256               0.0078125f              // 2 / 256
#define D4OVER256               0.015625f               // 4 / 256
#define D8OVER256               0.03125f                // 8 / 256

#define WBUFFERNEAR             -1.0f
#define WBUFFERFAR               0.0f
#define ZBUFFERNEAR              0.0f
#define ZBUFFERFAR              -1.0f

// Class declarations

typedef void (*GLIDEERRORFUNCTION)( const char *string, FxBool fatal );

struct BufferStruct
{
    bool                    Lock;
    GrLock_t                Type;
    GrLfbWriteMode_t        WriteMode;
    GrBuffer_t              Buffer;
    FxBool                  PixelPipeline;
    uint16_t          *Address;
};

struct TexSourceStruct
{
    uint32_t StartAddress;
    uint32_t EvenOdd;
    GrTexInfo    Info;
};

typedef uint32_t OGLByteColor;

struct GlideState
{
    GrBuffer_t              RenderBuffer;
    GrDepthBufferMode_t     DepthBufferMode;
    GrCmpFnc_t              DepthFunction;
    FxBool                  DepthBufferWritting;
    int16_t                 DepthBiasLevel;
    GrDitherMode_t          DitherMode;
    GrColor_t               ChromakeyValue;
    GrChromakeyMode_t       ChromaKeyMode;
    GrAlpha_t               AlphaReferenceValue;
    GrCmpFnc_t              AlphaTestFunction;
    FxBool                  AlphaMask;
    FxBool                  ColorMask;
    GrColor_t               ConstantColorValue;
    GrColor_t               FogColorValue;
    GrFogMode_t             FogMode;
    GrCullMode_t            CullMode;
    GrTextureClampMode_t    SClampMode;
    GrTextureClampMode_t    TClampMode;
    GrTextureFilterMode_t   MinFilterMode;
    GrTextureFilterMode_t   MagFilterMode;
    GrMipMapMode_t          MipMapMode;
    FxBool                  LodBlend;
    GrCombineFunction_t     ColorCombineFunction;
    GrCombineFactor_t       ColorCombineFactor;
    GrCombineLocal_t        ColorCombineLocal;
    GrCombineOther_t        ColorCombineOther;
    FxBool                  ColorCombineInvert;
    GrCombineFunction_t     AlphaFunction;
    GrCombineFactor_t       AlphaFactor;
    GrCombineLocal_t        AlphaLocal;
    GrCombineOther_t        AlphaOther;
    FxBool                  AlphaInvert;
    GrCombineFunction_t     TextureCombineCFunction;
    GrCombineFactor_t       TextureCombineCFactor;
    GrCombineFunction_t     TextureCombineAFunction;
    GrCombineFactor_t       TextureCombineAFactor;
    FxBool                  TextureCombineRGBInvert;
    FxBool                  TextureCombineAInvert;
    GrOriginLocation_t      OriginInformation;
    TexSourceStruct         TexSource;
    GrAlphaBlendFnc_t       AlphaBlendRgbSf;
    GrAlphaBlendFnc_t       AlphaBlendRgbDf;
    GrAlphaBlendFnc_t       AlphaBlendAlphaSf;
    GrAlphaBlendFnc_t       AlphaBlendAlphaDf;
    uint32_t                ClipMinX;
    uint32_t                ClipMaxX;
    uint32_t                ClipMinY;
    uint32_t                ClipMaxY;
    GrColorFormat_t         ColorFormat;
    uint32_t                STWHint;
    FxBool                  VRetrace;
};

struct GlideStruct
{
    int                     ActiveVoodoo;
    // Frame Buffer Stuff
    uint32_t            WindowWidth;
    uint32_t            WindowHeight;
    uint32_t            WindowTotalPixels; 
    int                     NumBuffers;
    int                     AuxBuffers;
    // States and Constants
    uint8_t           FogTable[ GR_FOG_TABLE_SIZE + 1 ];
    uint32_t            TexMemoryMaxPosition;
    bool                    CLocal;
    bool                    COther;
    bool                    ALocal;
    bool                    AOther;
    GlideState              State;
    BufferStruct            SrcBuffer;
    BufferStruct            DstBuffer;
    GLuint                  LFBTexture;
    uint32_t            LFBTextureSize;
    int                     TextureMemory;
};

struct OpenGLStruct
{
    bool                    GlideInit;
    bool                    WinOpen;
    GLsizei                 WindowWidth;
    GLsizei                 WindowHeight;
    GLfloat                 Gamma;
    GLfloat                 AlphaReferenceValue;
    GLenum                  AlphaTestFunction;
    GLboolean               DepthBufferWritting;
    GLfloat                 DepthBiasLevel;
    GLenum                  DepthFunction;
    GLenum                  RenderBuffer;
    GLenum                  SClampMode;
    GLenum                  TClampMode;
    GLenum                  MinFilterMode;
    GLenum                  MagFilterMode;
    GLenum                  TextureMode;
    GLenum                  SrcBlend;
    GLenum                  DstBlend;
    GLenum                  SrcAlphaBlend;
    GLenum                  DstAlphaBlend;
    GLuint                  Refresh;
    GLboolean               ColorMask;
    GLfloat                 ConstantColor[ 4 ];
    GLfloat                 AlphaColor[ 4 ];
    GLfloat                 ZNear;
    GLfloat                 ZFar;
    GLfloat                 FogColor[ 4 ];
    uint8_t           FogTable[ OPENGLFOGTABLESIZE ];
    OGLByteColor            ChromaColor;
    bool                    Fog;
    bool                    Texture;
    bool                    ColorTexture;
    bool                    AlphaTexture;
    bool                    Blend;
    bool                    AlphaBuffer;
    bool                    ChromaKey;
    bool                    Clipping;
    int                     MultiTextureTMUs;
    int                     DepthBufferType;
    int                     WaitSignal;
};

struct ConfigStruct
{
    int     OGLVersion;
    int     Priority;
    int     TextureMemorySize;
    int     FrameBufferMemorySize;

    bool    FogEnable;
    bool    InitFullScreen;
    bool    PrecisionFix;
    bool    EnableMipMaps;
    bool    BuildMipMaps;
    bool    IgnorePaletteChange;
    bool    Wrap565to5551;
    bool    TextureEnv;
    bool    MMXEnable;
    bool    CreateWindow;

    bool    EXT_secondary_color;
    bool    ARB_multitexture;
    bool    EXT_fog_coord;
    bool    EXT_texture_env_add;
    bool    EXT_texture_env_combine;
    bool    EXT_texture_lod_bias;
    bool    SGIS_generate_mipmap;
    bool    EXT_paletted_texture;
    bool    EXT_vertex_array;
    bool    EXT_blend_func_separate;
};

// Extern variables
extern const char *         openglide2Version;
extern double               ClockFreq;
extern GlideStruct          Glide;                  // Glide Internal
extern OpenGLStruct         OpenGL;                 // OpenGL equivalents
extern ConfigStruct         UserConfig;
extern ConfigStruct         InternalConfig;
extern GLIDEERRORFUNCTION   ExternErrorFunction;

#ifdef OGL_DEBUG
    // Profiling variables
    extern int64_t        InitialTick;
    extern int64_t        FinalTick;
    extern uint32_t     Frame;
    extern double           Fps;
    extern double           FpsAux;
#endif

// Genral Prototypes
void __cdecl GlideMsg( const char *szString, ... );
void __cdecl Error( const char *szString, ... );
void GLErro( const char *Funcao );
void ConvertColor4B( GrColor_t GlideColor, uint32_t &C );
void ConvertColorB( GrColor_t GlideColor, uint8_t &R, uint8_t &G, uint8_t &B, uint8_t &A );
void ConvertColorF( GrColor_t GlideColor, float &R, float &G, float &B, float &A );
GrColor_t ConvertConstantColor( float R, float G, float B, float A );
bool GenerateErrorFile( void );
bool ClearAndGenerateLogFile( void );
void CloseLogFile( void );
bool InitWindow( uint32_t hWnd );
void InitOpenGL( void );
void GetOptions( void );
void InitMainVariables( void );

void MMX_memcpy( void *Dst, void *Src, uint32_t NumberOfBytes );

int DetectMMX();

#endif
