//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

/* Utility File */

#include "wrapper_config.h"
#include "GlOgl.h"
#include "Glextensions.h"
#include "OGLTables.h"

// Configuration Variables
ConfigStruct    UserConfig;
ConfigStruct    InternalConfig;

// Extern prototypes
extern unsigned long    NumberOfErrors;

// Functions

void __cdecl GlideMsg( const char *szString, ... )
{
    va_list( Arg );
    va_start( Arg, szString );

    FILE *fHandle = fopen(GLIDEFILE, "at" );
    if ( !fHandle )
    {
        return;
    }
    vfprintf( fHandle, szString, Arg );
    fflush( fHandle );
    fclose( fHandle );

    va_end( Arg );
}

void __cdecl Error( const char *szString, ... )
{
    va_list( Arg );
    va_start( Arg, szString );

    if ( NumberOfErrors == 0 )
    {
        GenerateErrorFile( );
    }

    FILE *fHandle = fopen( ERRORFILE, "at" );
    if ( ! fHandle )
    {
        return;
    }
    vfprintf( fHandle, szString, Arg );
    fflush( fHandle );
    fclose( fHandle );

    va_end( Arg );
    NumberOfErrors++;
}

void GLErro( const char *Funcao )
{
    GLenum Erro = glGetError( );

    if ( Erro != GL_NO_ERROR )
    {
        Error( "%s: OpenGLError = %s\n", Funcao, gluErrorString( Erro ) );
    }
}

void ConvertColorB( GrColor_t GlideColor, unsigned char &R, unsigned char &G, unsigned char &B, unsigned char &A )
{
    switch ( Glide.State.ColorFormat )
    {
    case GR_COLORFORMAT_ARGB:   //0xAARRGGBB
        A = (unsigned char)( ( GlideColor & 0xFF000000 ) >> 24 );
        R = (unsigned char)( ( GlideColor & 0x00FF0000 ) >> 16 );
        G = (unsigned char)( ( GlideColor & 0x0000FF00 ) >>  8 );
        B = (unsigned char)( ( GlideColor & 0x000000FF )       );
        break;

    case GR_COLORFORMAT_ABGR:   //0xAABBGGRR
        A = (unsigned char)( ( GlideColor & 0xFF000000 ) >> 24 );
        B = (unsigned char)( ( GlideColor & 0x00FF0000 ) >> 16 );
        G = (unsigned char)( ( GlideColor & 0x0000FF00 ) >>  8 );
        R = (unsigned char)( ( GlideColor & 0x000000FF )       );
        break;

    case GR_COLORFORMAT_RGBA:   //0xRRGGBBAA
        R = (unsigned char)( ( GlideColor & 0xFF000000 ) >> 24 );
        G = (unsigned char)( ( GlideColor & 0x00FF0000 ) >> 16 );
        B = (unsigned char)( ( GlideColor & 0x0000FF00 ) >>  8 );
        A = (unsigned char)( ( GlideColor & 0x000000FF )       );
        break;

    case GR_COLORFORMAT_BGRA:   //0xBBGGRRAA
        B = (unsigned char)( ( GlideColor & 0xFF000000 ) >> 24 );
        G = (unsigned char)( ( GlideColor & 0x00FF0000 ) >> 16 );
        R = (unsigned char)( ( GlideColor & 0x0000FF00 ) >>  8 );
        A = (unsigned char)( ( GlideColor & 0x000000FF )       );
        break;
    }
}

void ConvertColor4B( GrColor_t GlideColor, unsigned int &C )
{
    switch ( Glide.State.ColorFormat )
    {
    case GR_COLORFORMAT_ARGB:   //0xAARRGGBB
        C = GlideColor;
        break;

    case GR_COLORFORMAT_ABGR:   //0xAABBGGRR
        C = ( ( GlideColor & 0xFF00FF00 ) ||
              ( ( GlideColor & 0x00FF0000 ) >> 16 ) ||
              ( ( GlideColor & 0x000000FF ) <<  16 ) );
        break;

    case GR_COLORFORMAT_RGBA:   //0xRRGGBBAA
        C = ( ( ( GlideColor & 0x00FFFFFF ) << 8 ) ||
              ( ( GlideColor & 0xFF000000 ) >> 24 ) );
        break;

    case GR_COLORFORMAT_BGRA:   //0xBBGGRRAA
        C = ( ( ( GlideColor & 0xFF000000 ) >> 24 ) ||
              ( ( GlideColor & 0x00FF0000 ) >>  8 ) ||
              ( ( GlideColor & 0x0000FF00 ) <<  8 ) ||
              ( ( GlideColor & 0x000000FF ) << 24 ) );
        break;
    }
}

GrColor_t ConvertConstantColor( float R, float G, float B, float A )
{
    GrColor_t r = (GrColor_t) R;
    GrColor_t g = (GrColor_t) G;
    GrColor_t b = (GrColor_t) B;
    GrColor_t a = (GrColor_t) A;

    switch ( Glide.State.ColorFormat )
    {
    case GR_COLORFORMAT_ARGB:   //0xAARRGGBB
        return ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | b;

    case GR_COLORFORMAT_ABGR:   //0xAABBGGRR
        return ( a << 24 ) | ( b << 16 ) | ( g << 8 ) | r;

    case GR_COLORFORMAT_RGBA:   //0xRRGGBBAA
        return ( r << 24 ) | ( g << 16 ) | ( b << 8 ) | a;

    case GR_COLORFORMAT_BGRA:   //0xBBGGRRAA
        return ( b << 24 ) | ( g << 16 ) | ( r << 8 ) | a;
    }

    return 0;
}

void ConvertColorF( GrColor_t GlideColor, float &R, float &G, float &B, float &A )
{
    switch ( Glide.State.ColorFormat )
    {
    case GR_COLORFORMAT_ARGB:   //0xAARRGGBB
        A = (float)( ( GlideColor & 0xFF000000 ) >> 24 ) * D1OVER255;
        R = (float)( ( GlideColor & 0x00FF0000 ) >> 16 ) * D1OVER255;
        G = (float)( ( GlideColor & 0x0000FF00 ) >>  8 ) * D1OVER255;
        B = (float)( ( GlideColor & 0x000000FF )       ) * D1OVER255;
        break;

    case GR_COLORFORMAT_ABGR:   //0xAABBGGRR
        A = (float)( ( GlideColor & 0xFF000000 ) >> 24 ) * D1OVER255;
        B = (float)( ( GlideColor & 0x00FF0000 ) >> 16 ) * D1OVER255;
        G = (float)( ( GlideColor & 0x0000FF00 ) >>  8 ) * D1OVER255;
        R = (float)( ( GlideColor & 0x000000FF )       ) * D1OVER255;
        break;

    case GR_COLORFORMAT_RGBA:   //0xRRGGBBAA
        R = (float)( ( GlideColor & 0xFF000000 ) >> 24 ) * D1OVER255;
        G = (float)( ( GlideColor & 0x00FF0000 ) >> 16 ) * D1OVER255;
        B = (float)( ( GlideColor & 0x0000FF00 ) >>  8 ) * D1OVER255;
        A = (float)( ( GlideColor & 0x000000FF )       ) * D1OVER255;
        break;

    case GR_COLORFORMAT_BGRA:   //0xBBGGRRAA
        B = (float)( ( GlideColor & 0xFF000000 ) >> 24 ) * D1OVER255;
        G = (float)( ( GlideColor & 0x00FF0000 ) >> 16 ) * D1OVER255;
        R = (float)( ( GlideColor & 0x0000FF00 ) >>  8 ) * D1OVER255;
        A = (float)( ( GlideColor & 0x000000FF )       ) * D1OVER255;
        break;
    }
}

//*************************************************
unsigned int GetTexSize( const int Lod, const int aspectRatio, const int format )
{
    /*
    ** If the format is one of these:
    ** GR_TEXFMT_RGB_332
    ** GR_TEXFMT_YIQ_422
    ** GR_TEXFMT_ALPHA_8
    ** GR_TEXFMT_INTENSITY_8
    ** GR_TEXFMT_ALPHA_INTENSITY_44
    ** GR_TEXFMT_P_8
    ** Reduces the size by 2
    */
    return nSquareLod[ format > GR_TEXFMT_RSVD1 ][ aspectRatio ][ Lod ];
}

static char * FindConfig( const char *IniFile, const char *IniConfig )
{
    // Cannot return pointer to local buffer, unless
    // static.
    static char Buffer1[ 256 ];
    char    * EqLocation, 
            * Find;
    FILE    * file;

    Find = NULL;
    file = fopen( IniFile, "r" );

    while ( fgets( Buffer1, 255, file ) != NULL )
    {
        if ( ( EqLocation = strchr( Buffer1, '=' ) ) != NULL )
        {       
            if ( !strncmp( Buffer1, IniConfig, EqLocation - Buffer1 ) )
            {
                Find = EqLocation + 1;
                if ( Find[ strlen( Find ) - 1 ] == '\n' )
                {
                    Find[ strlen( Find ) - 1 ] = '\0';
                }
                break;
            }
        }
    }

    fclose( file );

    return Find;
}

void GetOptions( void )
{
    FILE        * IniFile;
    char        * Pointer;
    char        Path[ 256 ];

    UserConfig.FogEnable                    = true;
    UserConfig.InitFullScreen               = false;
    UserConfig.PrecisionFix                 = true;
    UserConfig.CreateWindow                 = false;
    UserConfig.EnableMipMaps                = false;
    UserConfig.BuildMipMaps                 = false;
    UserConfig.IgnorePaletteChange          = false;
    UserConfig.ARB_multitexture             = true;
    UserConfig.EXT_paletted_texture         = true;
    UserConfig.EXT_texture_env_add          = false;
    UserConfig.EXT_texture_env_combine      = false;
    UserConfig.EXT_vertex_array             = false;
    UserConfig.EXT_fog_coord                = true;
    UserConfig.EXT_blend_func_separate      = false;
    UserConfig.Wrap565to5551                = true;

    UserConfig.TextureMemorySize            = 16;
    UserConfig.FrameBufferMemorySize        = 8;

    UserConfig.Priority                     = 2;

    strcpy( Path, INIFILE );

    GlideMsg( "Configuration file is %s\n", Path );
    
    if ( _access( Path, 0 ) == -1 )
    {
        IniFile = fopen( Path, "w" );
        fprintf( IniFile, "openglide2 Configuration File\n\n" );
        fprintf( IniFile, "Info:\n" );
        fprintf( IniFile, "Priority goes from 0(HIGH) to 5(IDLE)\n" );
        fprintf( IniFile, "Texture Memory goes from %d to %d\n", OGL_MIN_TEXTURE_BUFFER, OGL_MAX_TEXTURE_BUFFER );
        fprintf( IniFile, "Frame Buffer Memory goes from %d to %d\n", OGL_MIN_FRAME_BUFFER, OGL_MAX_FRAME_BUFFER );
        fprintf( IniFile, "All other fields are boolean with 1(TRUE) and 0(FALSE)\n\n" );
        fprintf( IniFile, "Version=%s\n\n", openglide2Version );
        fprintf( IniFile, "[Options]\n" );
        fprintf( IniFile, "WrapperPriority=%d\n", UserConfig.Priority );
        fprintf( IniFile, "CreateWindow=%d\n", UserConfig.CreateWindow );
        fprintf( IniFile, "InitFullScreen=%d\n", UserConfig.InitFullScreen );
        fprintf( IniFile, "EnableMipMaps=%d\n", UserConfig.EnableMipMaps );
        fprintf( IniFile, "IgnorePaletteChange=%d\n", UserConfig.IgnorePaletteChange );
        fprintf( IniFile, "Wrap565to5551=%d\n", UserConfig.Wrap565to5551 );
        fprintf( IniFile, "EnablePrecisionFix=%d\n", UserConfig.PrecisionFix );
        fprintf( IniFile, "EnableMultiTextureEXT=%d\n", UserConfig.ARB_multitexture );
        fprintf( IniFile, "EnablePaletteEXT=%d\n", UserConfig.EXT_paletted_texture );
        fprintf( IniFile, "EnableVertexArrayEXT=%d\n", UserConfig.EXT_vertex_array );
        fprintf( IniFile, "TextureMemorySize=%d\n", UserConfig.TextureMemorySize );
        fprintf( IniFile, "FrameBufferMemorySize=%d\n", UserConfig.FrameBufferMemorySize );
        fclose( IniFile );
    }
    else
    {
        Pointer = FindConfig( Path, "Version" );
        if ( Pointer && !strcmp( Pointer, openglide2Version ) )
        {
            if ( (Pointer = FindConfig(Path, "CreateWindow")) )
                UserConfig.CreateWindow = atoi( Pointer ) ? true : false;
            if ( (Pointer = FindConfig(Path, "InitFullScreen")) )
                UserConfig.InitFullScreen = atoi( Pointer ) ? true : false;
            if ( (Pointer = FindConfig(Path, "EnableMipMaps")) )
                UserConfig.EnableMipMaps = atoi( Pointer ) ? true : false;
            if ( (Pointer = FindConfig(Path, "IgnorePaletteChange")) )
                UserConfig.IgnorePaletteChange = atoi( Pointer ) ? true : false;
            if ( (Pointer = FindConfig(Path, "EnablePrecisionFix")) )
                UserConfig.PrecisionFix = atoi( Pointer ) ? true : false;
            if ( (Pointer = FindConfig(Path, "EnableMultiTextureEXT")) )
                UserConfig.ARB_multitexture = atoi( Pointer ) ? true : false;
            if ( (Pointer = FindConfig(Path, "EnablePaletteEXT")) )
                UserConfig.EXT_paletted_texture = atoi( Pointer ) ? true : false;
            if ( (Pointer = FindConfig(Path, "EnableVertexArrayEXT")) )
                UserConfig.EXT_vertex_array = atoi( Pointer ) ? true : false;
            if ( (Pointer = FindConfig(Path, "TextureMemorySize")) )
                UserConfig.TextureMemorySize = atoi( Pointer );
            if ( (Pointer = FindConfig(Path, "WrapperPriority")) )
                UserConfig.Priority = atoi( Pointer );
            if ( (Pointer = FindConfig(Path, "Wrap565to5551")) )
                UserConfig.Wrap565to5551 = atoi( Pointer ) ? true : false;
            if ( (Pointer = FindConfig(Path, "FrameBufferMemorySize")) )
                UserConfig.FrameBufferMemorySize = atoi( Pointer );
        }
        else
        {
            remove( Path );
            GetOptions( );
        }
    }
}


FX_ENTRY void FX_CALL setConfig(unsigned int flags)
{
    UserConfig.EnableMipMaps = ((flags & WRAPPER_FLAG_MIPMAPS) != 0);
}


bool ClearAndGenerateLogFile( void )
{
    FILE    * GlideFile;
    char    tmpbuf[ 128 ];

    remove( ERRORFILE );
    GlideFile = fopen( GLIDEFILE, "w" );
    if ( ! GlideFile )
    {
        return false;
    }
    fclose( GlideFile );

    GlideMsg( OGL_LOG_SEPARATE );
    GlideMsg( "openglide2 Log File\n" );
    GlideMsg( OGL_LOG_SEPARATE );
    GlideMsg( "***** openglide2 %s *****\n", openglide2Version );
    GlideMsg( OGL_LOG_SEPARATE );
    _strdate( tmpbuf );
    GlideMsg( "Date: %s\n", tmpbuf );
    _strtime( tmpbuf );
    GlideMsg( "Time: %s\n", tmpbuf );
    GlideMsg( OGL_LOG_SEPARATE );
    GlideMsg( OGL_LOG_SEPARATE );
    ClockFreq = ClockFrequency( );
    GlideMsg( "Clock Frequency: %-4.2f Mhz\n", ClockFreq / 1000000.0f );
    GlideMsg( OGL_LOG_SEPARATE );
    GlideMsg( OGL_LOG_SEPARATE );

    return true;
}

void CloseLogFile( void )
{
    char tmpbuf[ 128 ];
    GlideMsg( OGL_LOG_SEPARATE );
    _strtime( tmpbuf );
    GlideMsg( "Time: %s\n", tmpbuf );
    GlideMsg( OGL_LOG_SEPARATE );

#ifdef OGL_DEBUG
    Fps = (float) Frame * ClockFreq / FpsAux;
    GlideMsg( "FPS = %f\n", Fps );
    GlideMsg( OGL_LOG_SEPARATE );
#endif
}

bool GenerateErrorFile( void )
{
    char    tmpbuf[ 128 ];
    FILE    * ErrorFile;

    ErrorFile = fopen( ERRORFILE, "w");
    if( !ErrorFile )
    {
        return false;
    }
    fclose( ErrorFile );

    NumberOfErrors++;
    Error(  OGL_LOG_SEPARATE );
    Error(  "openglide2 Error File\n");
    Error(  OGL_LOG_SEPARATE );
    _strdate( tmpbuf );
    Error(  "Date: %s\n", tmpbuf );
    _strtime( tmpbuf );
    Error(  "Time: %s\n", tmpbuf );
    Error(  OGL_LOG_SEPARATE );
    Error(  OGL_LOG_SEPARATE );

    return true;
}

// Detect if Processor has MMX Instructions
int DetectMMX( void )
{
    unsigned int Result;

    #ifdef __GNUC__
        asm ("push %%ebx;"
             "mov  $1, %%eax;"
             "CPUID;"
             "pop  %%ebx;"
             : "=d" (Result) /* Outputs */
             : /* No inputs */
             : "%eax", "%ecx", "cc" /* Clobbers */
            );
    #else
    __asm
    {
        push EAX
        push EDX
        mov EAX, 1
        CPUID
        mov Result, EDX
        pop EDX
        pop EAX
    }
    #endif

    #ifdef NOMMX
	    return 0
    #else
        return Result & 0x00800000;
    #endif
}

// Copy Blocks of Memory Using MMX

void MMX_memcpy( void *Dst, void *Src, unsigned int NumberOfBytes )
{
  if(DetectMMX != 0)
  {
    #ifdef __GNUC__
    asm ("jmp   MMXCopyMemory_start;"
         "MMXCopyMemory_copying:"
         "movq  (%1,%0), %%mm0;"
         "movq  %%mm0, (%2,%0);"
         "MMXCopyMemory_start:"
         "subl  $8, %0;"
         "jae   MMXCopyMemory_copying;"
         : /* No outputs */
         : "r" ((unsigned int)NumberOfBytes), "r" (Src), "r" (Dst) /* Inputs */
         : "%mm0", "memory" /* Clobbers */
        );
    #else
    __asm
    {
        mov ECX, NumberOfBytes
        mov EAX, Src
        mov EDX, Dst
        jmp start
copying:
        MOVQ MM0, [EAX+ECX]
        MOVQ [EDX+ECX], MM0
start:  sub ECX, 8
        jae copying
        EMMS
    }
    #endif
  }
  else
  {
	memcpy( Dst, Src, NumberOfBytes );
  }
}
