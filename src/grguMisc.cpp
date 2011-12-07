//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#include "GlOgl.h"
#include "GLRender.h"


//*************************************************
//* Sets the External Error Function to call if
//* Glides Generates and Error
//*************************************************
FX_ENTRY void FX_CALL
grErrorSetCallback( void (*function)(const char *string, FxBool fatal) )
{
#ifdef OGL_DONE
    GlideMsg( "grErrorSetCallback( --- )\n" );
#endif

    ExternErrorFunction = function;
}

//*************************************************
//* Sets the Cull Mode
//*************************************************
FX_ENTRY void FX_CALL
grCullMode( GrCullMode_t mode )
{
#ifdef OGL_DONE
    GlideMsg( "grCullMode( %d )\n", mode );
#endif

    RenderDrawTriangles( );

    Glide.State.CullMode = mode;

    switch ( Glide.State.CullMode )
    {
    case GR_CULL_DISABLE:
        glDisable( GL_CULL_FACE );
        glCullFace( GL_BACK );  // This will be called in initialization
        break;

    case GR_CULL_NEGATIVE:
        glEnable( GL_CULL_FACE );
        if ( Glide.State.OriginInformation == GR_ORIGIN_LOWER_LEFT )
        {
            glFrontFace( GL_CCW );
        }
        else
        {
            glFrontFace( GL_CW );
        }
        break;

    case GR_CULL_POSITIVE:
        glEnable( GL_CULL_FACE );
        if ( Glide.State.OriginInformation == GR_ORIGIN_LOWER_LEFT )
        {
            glFrontFace( GL_CW );
        }
        else
        {
            glFrontFace( GL_CCW );
        }
        break;
    }

#ifdef OPENGL_DEBUG
    GLErro( "grCullMode" );
#endif
}

//*************************************************
//* Set the size and location of the hardware clipping window
//*************************************************
FX_ENTRY void FX_CALL 
grClipWindow( uint32_t minx, uint32_t miny, uint32_t maxx, uint32_t maxy )
{
#ifdef OGL_PARTDONE
    GlideMsg( "grClipWindow( %d, %d, %d, %d )\n", minx, miny, maxx, maxy );
#endif

    RenderDrawTriangles( );

    Glide.State.ClipMinX = minx;
    Glide.State.ClipMaxX = maxx;
    Glide.State.ClipMinY = miny;
    Glide.State.ClipMaxY = maxy;

    if ( ( Glide.State.ClipMinX != 0 ) || 
         ( Glide.State.ClipMinY != 0 ) ||
         ( Glide.State.ClipMaxX != (uint32_t) Glide.WindowWidth ) ||
         ( Glide.State.ClipMaxY != (uint32_t) Glide.WindowHeight ) )
    {
        OpenGL.Clipping = true;
    }
    else
    {
        OpenGL.Clipping = false;
    }

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    if ( Glide.State.OriginInformation == GR_ORIGIN_LOWER_LEFT )
    {
        glOrtho( Glide.State.ClipMinX, Glide.State.ClipMaxX, 
                 Glide.State.ClipMinY, Glide.State.ClipMaxY, 
                 OpenGL.ZNear, OpenGL.ZFar );
        glViewport( Glide.State.ClipMinX, Glide.State.ClipMinY, 
                    Glide.State.ClipMaxX - Glide.State.ClipMinX, 
                    Glide.State.ClipMaxY - Glide.State.ClipMinY ); 
        // Used for the buffer clearing
	    glScissor( Glide.State.ClipMinX, Glide.State.ClipMinY,
    			   Glide.State.ClipMaxX - Glide.State.ClipMinX,
    			   Glide.State.ClipMaxY - Glide.State.ClipMinY );
    }
    else
    {
        glOrtho( Glide.State.ClipMinX, Glide.State.ClipMaxX, 
                 Glide.State.ClipMaxY, Glide.State.ClipMinY, 
                 OpenGL.ZNear, OpenGL.ZFar );
        glViewport( Glide.State.ClipMinX, OpenGL.WindowHeight - Glide.State.ClipMaxY, 
                    Glide.State.ClipMaxX - Glide.State.ClipMinX, 
                    Glide.State.ClipMaxY - Glide.State.ClipMinY ); 
        // Used for the buffer clearing
	    glScissor( Glide.State.ClipMinX, OpenGL.WindowHeight - Glide.State.ClipMaxY, 
    			   Glide.State.ClipMaxX - Glide.State.ClipMinX,
    			   Glide.State.ClipMaxY - Glide.State.ClipMinY );
    }

    glMatrixMode( GL_MODELVIEW );
}

//*************************************************
FX_ENTRY void FX_CALL 
grDisableAllEffects( void )
{
#ifdef OGL_PARTDONE
    GlideMsg( "grDisableAllEffects( )\n" );
#endif

    grAlphaBlendFunction( GR_BLEND_ONE, GR_BLEND_ZERO, GR_BLEND_ONE, GR_BLEND_ZERO );
    grAlphaTestFunction( GR_CMP_ALWAYS );
    grChromakeyMode( GR_CHROMAKEY_DISABLE );
    grDepthBufferMode( GR_DEPTHBUFFER_DISABLE );
    grFogMode( GR_FOG_DISABLE );
}

//*************************************************
FX_ENTRY void FX_CALL
grResetTriStats( void )
{
#ifdef OGL_NOTDONE
    GlideMsg( "grResetTriStats( )\n" );
#endif
}

//*************************************************
FX_ENTRY void FX_CALL
grTriStats( uint32_t *trisProcessed, uint32_t *trisDrawn )
{
#ifdef OGL_NOTDONE
    GlideMsg( "grTriStats( )\n" );
#endif
}

//*************************************************
FX_ENTRY void FX_CALL
grHints( GrHint_t hintType, uint32_t hintMask )
{
#ifdef OGL_PARTDONE
    GlideMsg( "grHints( %d, %d )\n", hintType, hintMask );
#endif

    switch( hintType )
    {
    case GR_HINT_STWHINT:
        Glide.State.STWHint = hintMask;
        break;
    }
}


FX_ENTRY void FX_CALL 
ConvertAndDownloadRle( GrChipID_t        tmu,
                       uint32_t      startAddress,
                       GrLOD_t           thisLod,
                       GrLOD_t           largeLod,
                       GrAspectRatio_t   aspectRatio,
                       GrTextureFormat_t format,
                       uint32_t      evenOdd,
                       uint8_t     *bm_data,
                       long              bm_h,
                       uint32_t      u0,
                       uint32_t      v0,
                       uint32_t      width,
                       uint32_t      height,
                       uint32_t      dest_width,
                       uint32_t      dest_height,
                       uint16_t    *tlut )
{
#ifdef OGL_NOTDONE
    GlideMsg( "ConvertAndDownloadRle( %d, %lu, %d, %d, %d, %d, %d, ---, %l, %lu, %lu, %lu, %lu, %lu, %lu, --- )\n",
        tmu, startAddress, thisLod, largeLod, aspectRatio, format, evenOdd, bm_h, u0, v0, width, height,
        dest_width, dest_height );
#endif
}

//*************************************************
FX_ENTRY void FX_CALL 
grCheckForRoom( int n )
{
#ifdef OGL_NOTDONE
    GlideMsg( "grCheckForRoom( %l )\n", n );
#endif
}

//*************************************************
FX_ENTRY void FX_CALL
grParameterData( uint32_t param, uint32_t components, uint32_t type, int offset )
{
#ifdef OGL_NOTDONE
    GlideMsg( "grParameterData( %lu, %lu, %lu, %l )\n",
        param, components, type, offset );
#endif
}

//*************************************************
FX_ENTRY int FX_CALL
guEncodeRLE16( void *dst, void *src, uint32_t width, uint32_t height )
{
#ifdef OGL_NOTDONE
    GlideMsg( "guEncodeRLE16( ---, ---, %lu, %lu ) = 1\n", width, height ); 
#endif

    return 1; 
}

//*************************************************
FX_ENTRY uint32_t FX_CALL
guEndianSwapWords( uint32_t value )
{
#ifdef OGL_DONE
    GlideMsg( "guEndianSwapWords( %lu )\n", value );
#endif

    return ( value << 16 ) | ( value >> 16 );
}

//*************************************************
FX_ENTRY uint16_t FX_CALL
guEndianSwapBytes( uint16_t value )
{
#ifdef OGL_DONE
    GlideMsg( "guEndianSwapBytes( %u )\n", value );
#endif

    return ( value << 8 ) | ( value >> 8 );
}

FX_ENTRY void FX_CALL
guMovieStart( void )
{
#ifdef OGL_NOTDONE
    GlideMsg( "guMovieStart( ) - Not Supported\n" );
#endif
}

FX_ENTRY void FX_CALL
guMovieStop( void )
{
#ifdef OGL_NOTDONE
    GlideMsg( "guMovieStop( ) - Not Supported\n" );
#endif
}

FX_ENTRY void FX_CALL
guMovieSetName( const char *name )
{
#ifdef OGL_NOTDONE
    GlideMsg( "guMovieSetName( ) - Not Supported\n" );
#endif
}

