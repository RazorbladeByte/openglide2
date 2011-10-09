//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#ifndef __TEXTURE_CONVERSION_H__
#define __TEXTURE_CONVERSION_H__

void Convert565to8888( FxU16 *Buffer1, FxU32 *Buffer2, FxU32 Pixels );
void MMX565to8888( FxU16 *Src, FxU32 *Dst, FxU32 NumberOfPixels );
void Cpp565to8888( FxU16 *Buffer1, FxU32 *Buffer2, FxU32 Pixels );

void Convert565Kto8888( FxU16 *Buffer1, FxU16 key, FxU32 *Buffer2, FxU32 Pixels );

void Convert565to5551( FxU32 *Buffer1, FxU32 *Buffer2, int Pixels );
void MMX565to5551( FxU32 *Src, FxU32 *Dst, int NumberOfPixels );
void Cpp565to5551( FxU32 *Buffer1, FxU32 *Buffer2, int Pixels );

void Convert5551to565( FxU32 *Buffer1, FxU32 *Buffer2, int Pixels );
void MMX5551to565( FxU32 *Src, FxU32 *Dst, int NumberOfPixels );
void Cpp5551to565( FxU32 *Buffer1, FxU32 *Buffer2, int Pixels );

void Convert8888to565( FxU32 *Src, FxU16 *Dst, FxU32 Pixels );

void Convert4444to4444special( FxU32 *Buffer1, FxU32 *Buffer2, int Pixels );
void MMX4444to4444special( FxU32 *Src, FxU32 *Dst, int NumberOfPixels );
void Cpp4444to4444special( FxU32 *Buffer1, FxU32 *Buffer2, int Pixels );

void Convert1555to5551( FxU32 *Buffer1, FxU32 *Buffer2, int Pixels );
void MMX1555to5551( FxU32 *Src, FxU32 *Dst, int NumberOfPixels );
void Cpp1555to5551( FxU32 *Buffer1, FxU32 *Buffer2, int Pixels );

void ConvertA8toAP88( FxU8 *Buffer1, FxU16 *Buffer2, FxU32 Pixels );
void ConvertAI44toAP88( FxU8 *Buffer1, FxU16 *Buffer2, FxU32 Pixels );
void Convert8332to8888( FxU16 *Buffer1, FxU32 *Buffer2, FxU32 Pixels );
void ConvertP8to8888( FxU8 *Buffer1, FxU32 *Buffer2, FxU32 Pixels, FxU32 *palette );
void ConvertAP88to8888( FxU16 *Buffer1, FxU32 *Buffer2, FxU32 Pixels, FxU32 *palette );
void ConvertYIQto8888( FxU8 *in, FxU32 *out, FxU32 Pixels, GuNccTable *ncc );
void ConvertAYIQto8888( FxU16 *in, FxU32 *out, FxU32 Pixels, GuNccTable *ncc );
void SplitAP88( FxU16 *ap88, FxU8 *index, FxU8 *alpha, FxU32 pixels );

#endif
