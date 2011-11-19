//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

/* Linear Frame Buffer Functions */


#include "GlOgl.h"
#include "Glextensions.h"
#include "GLRender.h"
#include "FormatConversion.h"


#define BLUE_SCREEN     (0x07FF)

// Will need to change this later
static unsigned int tempBuf[ 2048 * 2048 ];


//*************************************************
FX_ENTRY FxBool FX_CALL
grLfbLock( GrLock_t dwType, 
           GrBuffer_t dwBuffer, 
           GrLfbWriteMode_t dwWriteMode,
           GrOriginLocation_t dwOrigin, 
           FxBool bPixelPipeline, 
           GrLfbInfo_t *lfbInfo )
{ 
#ifdef OGL_CRITICAL
    GlideMsg( "grLfbLock( %d, %d, %d, %d, %d, --- )\n", dwType, dwBuffer, dwWriteMode, dwOrigin, bPixelPipeline ); 
#endif

    RenderDrawTriangles( );

    if ( dwType & 1 )
    {
        Glide.DstBuffer.Lock            = true;
        Glide.DstBuffer.Type            = dwType;
        Glide.DstBuffer.Buffer          = dwBuffer;
        Glide.DstBuffer.WriteMode       = dwWriteMode;
        Glide.DstBuffer.PixelPipeline   = bPixelPipeline;

        lfbInfo->lfbPtr = Glide.DstBuffer.Address;
    }
    else
    {
        unsigned int j;

        glReadBuffer( dwBuffer == GR_BUFFER_BACKBUFFER
                      ? GL_BACK : GL_FRONT );

        glReadPixels( 0, 0,
                      Glide.WindowWidth, Glide.WindowHeight,
                      GL_BGRA, GL_UNSIGNED_BYTE,
                      (void *)tempBuf );

        if ( dwOrigin == GR_ORIGIN_UPPER_LEFT )
        {
            for ( j = 0; j < Glide.WindowHeight; j++ )
            {
                Convert8888to565( tempBuf + ( ( ( Glide.WindowHeight ) - 1 - j ) * Glide.WindowWidth ),
                        Glide.SrcBuffer.Address + ( j * Glide.WindowWidth ),
                        Glide.WindowWidth );
            }
        }
        else
        {
            Convert8888to565( tempBuf, Glide.SrcBuffer.Address, Glide.WindowTotalPixels );
        }    
        Glide.SrcBuffer.Lock            = true;
        Glide.SrcBuffer.Type            = dwType;
        Glide.SrcBuffer.Buffer          = dwBuffer;
        Glide.SrcBuffer.WriteMode       = dwWriteMode;
        Glide.SrcBuffer.PixelPipeline   = bPixelPipeline;

        lfbInfo->lfbPtr = Glide.SrcBuffer.Address;
    }

    lfbInfo->writeMode = GR_LFBWRITEMODE_565;
    lfbInfo->strideInBytes = Glide.WindowWidth * 2;

    return FXTRUE;
}

//*************************************************
FX_ENTRY FxBool FX_CALL
grLfbUnlock( GrLock_t dwType, GrBuffer_t dwBuffer )
{ 
#ifdef OGL_CRITICAL
    GlideMsg("grLfbUnlock( %d, %d )\n", dwType, dwBuffer ); 
#endif
    
    if ( dwType & 1 )
    {
        if ( ! Glide.DstBuffer.Lock )
        {
            return FXFALSE;
        }

        unsigned int ii,
            x,
            y,
            maxx = 0,
            maxy = 0,
            minx = 2048, 
            miny = 2048;

        for ( ii = 0, x = 0, y = 0; ii < Glide.WindowTotalPixels; ii++ )
        {
            if ( Glide.DstBuffer.Address[ ii ] != BLUE_SCREEN )
            {
                if ( x > maxx ) maxx = x;
                if ( y > maxy ) maxy = y;
                if ( x < minx ) minx = x;
                if ( y < miny ) miny = y;

                tempBuf[ ii ] = 0x0    |    // A
                ( Glide.DstBuffer.Address[ ii ] & 0x001F ) << 19 |  // B
                ( Glide.DstBuffer.Address[ ii ] & 0x07E0 ) << 5  |  // G
                ( Glide.DstBuffer.Address[ ii ] >> 8 );             // R
                Glide.DstBuffer.Address[ ii ] = BLUE_SCREEN;
            } else
                tempBuf[ ii ] = 0xFFFFFFFF;

            x++;
            if ( x == Glide.WindowWidth )
            {
                x = 0;
                y++;
            }
        }

        if ( maxx >= minx )
        {
            maxx++; maxy++;
            unsigned int xsize = maxx - minx;
            unsigned int ysize = maxy - miny;

            // Draw a textured quad
            glPushAttrib( GL_COLOR_BUFFER_BIT|GL_TEXTURE_BIT|GL_DEPTH_BUFFER_BIT );

            glDisable( GL_BLEND );
            glEnable( GL_TEXTURE_2D );

            if ( Glide.DstBuffer.PixelPipeline )
                glEnable( GL_SCISSOR_TEST );

            glAlphaFunc( GL_EQUAL, 0.0f );
            glEnable( GL_ALPHA_TEST );

            glDepthMask( GL_FALSE );
            glDisable( GL_DEPTH_TEST );

            glBindTexture( GL_TEXTURE_2D, Glide.LFBTexture );
            glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, Glide.WindowWidth, ysize, GL_RGBA,
                GL_UNSIGNED_BYTE, tempBuf + ( miny * Glide.WindowWidth ) );

            glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
            glDrawBuffer( Glide.DstBuffer.Buffer == GR_BUFFER_BACKBUFFER
                        ? GL_BACK : GL_FRONT );

            glBegin( GL_QUADS );
                glColor3f( 1.0f, 1.0f, 1.0f );

                glTexCoord2f( (float)minx/Glide.LFBTextureSize, 0.0f );
                glVertex2f( (float)minx, (float)miny );

                glTexCoord2f((float)maxx/Glide.LFBTextureSize, 0.0f );
                glVertex2f( (float)maxx, (float)miny );

                glTexCoord2f( (float)maxx/Glide.LFBTextureSize, (float)ysize/Glide.LFBTextureSize );
                glVertex2f( (float)maxx, (float)maxy );

                glTexCoord2f( (float)minx/Glide.LFBTextureSize, (float)ysize/Glide.LFBTextureSize );
                glVertex2f( (float)minx, (float)maxy );
            glEnd( );

            glPopAttrib( );
            glDrawBuffer( OpenGL.RenderBuffer );

            if ( Glide.DstBuffer.Buffer != GR_BUFFER_BACKBUFFER )
            {
                glFlush( );
            }
        }

        Glide.DstBuffer.Lock = false;

        return FXTRUE;
    }
    else
    {
        if ( Glide.SrcBuffer.Lock )
        {
            Glide.SrcBuffer.Lock = false;
            
            return FXTRUE; 
        }
        else
        {
            return FXFALSE; 
        }
    }
}

//*************************************************
FX_ENTRY FxBool FX_CALL
grLfbReadRegion( GrBuffer_t src_buffer, unsigned int src_x, unsigned int src_y, unsigned int src_width,
                 unsigned int src_height, unsigned int dst_stride, void *dst_data )
{
#ifdef OGL_NOTDONE
    GlideMsg("grLfbReadRegion( %d, %d, %d, %d, %d, %d, --- )\n",
        src_buffer, src_x, src_y, src_width, src_height, dst_stride );
#endif

    // Taken from the linux sst1 driver
    FxBool rv = FXTRUE;
    GrLfbInfo_t info;

    info.size = sizeof( info );
    if ( grLfbLock( GR_LFB_READ_ONLY,
                src_buffer,
                GR_LFBWRITEMODE_ANY,
                GR_ORIGIN_UPPER_LEFT,
                FXFALSE,
                &info ) )
    {
        unsigned int *srcData;         /* Tracking Source Pointer */
        unsigned int *dstData;         /* Tracking Destination Pointer */
        unsigned int *end;             /* Demarks End of each Scanline */
        unsigned int srcJump;          /* bytes to next scanline */
        unsigned int dstJump;          /* bytes to next scanline */
        unsigned int length;           /* bytes to copy in scanline */
        unsigned int scanline;         /* scanline number */
        int          aligned;          /* word aligned? */

        dstData = ( unsigned int * ) dst_data;
        srcData = ( unsigned int * ) ( ((char*)info.lfbPtr)+
                                (src_y*info.strideInBytes) +
                                (src_x<<1) );
        scanline = src_height;
        length   = src_width * 2;
        dstJump  = dst_stride - length;
        srcJump  = info.strideInBytes - length;
        aligned  = !((unsigned int)srcData&0x2);

        if ( aligned ) {
            while( scanline-- ) {
                end = (unsigned int*)((char*)srcData + length - 2);

                while( srcData < end ) 
                    *dstData++ = *srcData++;

                if ( ((int)length) & 0x2 ) {
                    (*(unsigned short*)dstData) = (*(unsigned short*)srcData);
                    dstData = (unsigned int*)(((unsigned short*)dstData) + 1 );
                    srcData = (unsigned int*)(((unsigned short*)srcData) + 1 );
                }

                dstData = (unsigned int*)(((char*)dstData)+dstJump);
                srcData = (unsigned int*)(((char*)srcData)+srcJump);
            }
        } else {
            while( scanline-- ) {
                end = (unsigned int*)((char*)srcData + length - 2);

                (*(unsigned short*)dstData) = (*(unsigned short*)srcData);
                dstData = (unsigned int*)(((unsigned short*)dstData) + 1 );
                srcData = (unsigned int*)(((unsigned short*)srcData) + 1 );

                while( srcData < end )
                    *dstData++ = *srcData++;

                if ( !(((int)length) & 0x2) ) {
                    (*(unsigned short*)dstData) = (*(unsigned short*)srcData);
                    dstData = (unsigned int*)(((unsigned short*)dstData) + 1 );
                    srcData = (unsigned int*)(((unsigned short*)srcData) + 1 );
                }

                dstData = (unsigned int*)(((char*)dstData)+dstJump);
                srcData = (unsigned int*)(((char*)srcData)+srcJump);
            }
        }
        grLfbUnlock( GR_LFB_READ_ONLY, src_buffer );
    } else {
        rv = FXFALSE;
    }

    return rv; 
}

//*************************************************
FX_ENTRY FxBool FX_CALL
grLfbWriteRegion( GrBuffer_t dst_buffer, unsigned int dst_x, unsigned int dst_y, 
                  GrLfbSrcFmt_t src_format, unsigned int src_width, unsigned int src_height,
                  int src_stride, void *src_data )
{
#ifdef OGL_NOTDONE
    GlideMsg("grLfbWriteRegion( %d, %d, %d, %d, %d, %d, %d, --- )\n",
        dst_buffer, dst_x, dst_y, src_format, src_width, src_height, src_stride );
#endif

    RenderDrawTriangles( );

    // Taken from the linux sst1 driver
    FxBool           rv = FXTRUE;
    GrLfbInfo_t      info;
    GrLfbWriteMode_t writeMode;

    if ( src_format == GR_LFB_SRC_FMT_RLE16 )
        writeMode = GR_LFBWRITEMODE_565;
    else
        writeMode = (GrLfbWriteMode_t)src_format;

    info.size = sizeof( info );

    if ( grLfbLock((GrLock_t)( GR_LFB_WRITE_ONLY | GR_LFB_NOIDLE),
		dst_buffer, writeMode, GR_ORIGIN_UPPER_LEFT, FXFALSE, &info ) )
    {
        unsigned int *srcData;         /* Tracking Source Pointer */
        unsigned int *dstData;         /* Tracking Destination Pointer */
        unsigned int *end;             /* Demarks End of each Scanline */
        int srcJump;          /* bytes to next scanline */
        unsigned int dstJump;          /* bytes to next scanline */
        unsigned int length;           /* bytes to copy in scanline */
        unsigned int scanline;         /* scanline number */
        int   aligned;          /* word aligned? */

        srcData = ( unsigned int * ) src_data;
        dstData = ( unsigned int * ) ( ((char*)info.lfbPtr)+
                                (dst_y*info.strideInBytes) );
        scanline = src_height;

        switch( src_format ) {
            /* 16-bit aligned */
            case GR_LFB_SRC_FMT_565:
            case GR_LFB_SRC_FMT_555:
            case GR_LFB_SRC_FMT_1555:
            case GR_LFB_SRC_FMT_ZA16:
                dstData = (unsigned int*)(((unsigned short*)dstData) + dst_x);
                length  = src_width * 2;
                aligned = !((unsigned int)dstData&0x2);
                srcJump = src_stride - length;
                dstJump = info.strideInBytes - length;
                if ( aligned )
                {
                    while( scanline-- )
                    {
                        end = (unsigned int*)((char*)srcData + length - 2);
                        while( srcData < end )
                        {
                            // TODO: swap on bigendian?
                            *dstData = *srcData;
                            dstData++;
                            srcData++;
                        }

                        if ( ((int)length) & 0x2 )
                        {
                            (*(unsigned short*)&(dstData[0])) = (*(unsigned short*)&(srcData[0]));

                            dstData = (unsigned int*)(((unsigned short*)dstData) + 1 );
                            srcData = (unsigned int*)(((unsigned short*)srcData) + 1 );
                        }

                        dstData = (unsigned int*)(((char*)dstData)+dstJump);
                        srcData = (unsigned int*)(((char*)srcData)+srcJump);
                    }
                }
                else
                {
                    while( scanline-- ) {
                        end = (unsigned int*)((char*)srcData + length - 2);

                        // TODO: swap on bigendian?
                        (*(unsigned short*)&(dstData[0])) = (*(unsigned short*)&(srcData[0]));
                        dstData = (unsigned int*)(((unsigned short*)dstData) + 1 );
                        srcData = (unsigned int*)(((unsigned short*)srcData) + 1 );

                        while( srcData < end ) {
                            // TODO: swap on bigendian?
                            *dstData = *srcData;
                            dstData++;
                            srcData++;
                        }

                        if ( !(length & 0x2) )
                        {
                            // TODO: swap on bigendian?
                            (*(unsigned short*)&(dstData[0])) = (*(unsigned short*)&(srcData[0]));
                            dstData = (unsigned int*)(((unsigned short*)dstData) + 1 );
                            srcData = (unsigned int*)(((unsigned short*)srcData) + 1 );
                        }

                        dstData = (unsigned int*)(((char*)dstData)+dstJump);
                        srcData = (unsigned int*)(((char*)srcData)+srcJump);
                    }
                }
                break;
                /* 32-bit aligned */
                case GR_LFB_SRC_FMT_888:
                case GR_LFB_SRC_FMT_8888:
                case GR_LFB_SRC_FMT_565_DEPTH:
                case GR_LFB_SRC_FMT_555_DEPTH:
                case GR_LFB_SRC_FMT_1555_DEPTH:
                    dstData = ((unsigned int*)dstData) + dst_x;
                    length  = src_width * 4;
                    srcJump = src_stride - length;
                    dstJump = info.strideInBytes - length;

                    while( scanline-- ) {
                        end = (unsigned int*)((char*)srcData + length);
                        while( srcData < end ) {
                            // TODO: swap on bigendian?
                            *dstData = *srcData;
                            dstData++;
                            srcData++;
                        }
                        dstData = (unsigned int*)(((char*)dstData)+dstJump);
                        srcData = (unsigned int*)(((char*)srcData)+srcJump);
                    }
                break;
                case GR_LFB_SRC_FMT_RLE16:
	            // TODO: needs to be implemented
	            rv = FXFALSE;
	        break;
                default:
	            rv = FXFALSE;
	            break;
            }
            grLfbUnlock( GR_LFB_WRITE_ONLY, dst_buffer );
        } else {
            rv = FXFALSE;
        }

    return rv; 
}

FX_ENTRY void FX_CALL 
grLfbConstantAlpha( GrAlpha_t alpha )
{
#ifdef OGL_CRITICAL
    GlideMsg("grLfbConstantAlpha( %lu )\n", alpha );
#endif
}

FX_ENTRY void FX_CALL 
grLfbConstantDepth( unsigned short depth )
{
#ifdef OGL_CRITICAL
    GlideMsg("grLfbConstantDepth( %u )\n", depth );
#endif
}

FX_ENTRY void FX_CALL 
grLfbWriteColorSwizzle( FxBool swizzleBytes, FxBool swapWords )
{
#ifdef OGL_CRITICAL
    GlideMsg("grLfbWriteColorSwizzle( %d, %d )\n",
        swizzleBytes, swapWords );
#endif
}

FX_ENTRY void FX_CALL
grLfbWriteColorFormat( GrColorFormat_t colorFormat )
{
#ifdef OGL_CRITICAL
    GlideMsg("grLfbWriteColorFormat( %u )\n", colorFormat );
#endif
}

