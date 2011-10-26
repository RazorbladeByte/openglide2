/*
** Copyright (c) 1995, 3Dfx Interactive, Inc.
** All Rights Reserved.
**
** This is UNPUBLISHED PROPRIETARY SOURCE CODE of 3Dfx Interactive, Inc.;
** the contents of this file may not be disclosed to third parties, copied or
** duplicated in any form, in whole or in part, without the prior written
** permission of 3Dfx Interactive, Inc.
**
** RESTRICTED RIGHTS LEGEND:
** Use, duplication or disclosure by the Government is subject to restrictions
** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
** and Computer Software clause at DFARS 252.227-7013, and/or in similar or
** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
** rights reserved under the Copyright Laws of the United States.
**
** $Header: /cvsroot-fuse/openglide/openglide/sdk2_glideutl.h,v 1.1 2002/12/05 13:50:21 fbarros Exp $
** $Log: sdk2_glideutl.h,v $
** Revision 1.1  2002/12/05 13:50:21  fbarros
** 3dfx sdk 2 header file
**
** Revision 1.1.1.1  2001/06/25 18:00:50  paul
** v006 from sourceforge
**
** Revision 1.1.1.1  2001/02/01 16:24:51  fbarros
** Version 0.06
**
*/

/* Glide Utility routines */

#ifndef __GLIDEUTL_H__
#define __GLIDEUTL_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FX_GLIDE_NO_FUNC_PROTO
/*
** rendering functions
*/

FX_ENTRY void FX_CALL
guAADrawTriangleWithClip( const GrVertex *a, const GrVertex
                         *b, const GrVertex *c);

FX_ENTRY void FX_CALL
guDrawTriangleWithClip(
                       const GrVertex *a,
                       const GrVertex *b,
                       const GrVertex *c
                       );

FX_ENTRY void FX_CALL
guDrawPolygonVertexListWithClip( int nverts, const GrVertex vlist[] );

/*
** hi-level rendering utility functions
*/
FX_ENTRY void FX_CALL
guAlphaSource( GrAlphaSource_t mode );

FX_ENTRY void FX_CALL
guColorCombineFunction( GrColorCombineFnc_t fnc );

FX_ENTRY int FX_CALL
guEncodeRLE16( void *dst, void *src, unsigned int width, unsigned int height );

FX_ENTRY unsigned short * FX_CALL
guTexCreateColorMipMap( void );

/*
** fog stuff
*/
FX_ENTRY float FX_CALL
guFogTableIndexToW( int i );

FX_ENTRY void FX_CALL
guFogGenerateExp( GrFog_t fogtable[], float density );

FX_ENTRY void FX_CALL
guFogGenerateExp2( GrFog_t fogtable[], float density );

FX_ENTRY void FX_CALL
guFogGenerateLinear(GrFog_t fogtable[],
                    float nearZ, float farZ );

/*
** endian stuff
*/

FX_ENTRY unsigned int FX_CALL
guEndianSwapWords( unsigned int value );

FX_ENTRY unsigned short FX_CALL
guEndianSwapBytes( unsigned short value );


/*
** hi-level texture manipulation tools.
*/
FX_ENTRY FxBool FX_CALL
gu3dfGetInfo( const char *filename, Gu3dfInfo *info );

FX_ENTRY FxBool FX_CALL
gu3dfLoad( const char *filename, Gu3dfInfo *data );

#endif /* FX_GLIDE_NO_FUNC_PROTO */

#ifdef __cplusplus
}
#endif

#endif /* __GLIDEUTL_H__ */
