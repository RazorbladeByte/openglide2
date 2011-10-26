//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#ifndef __TEXTURE_CONVERSION_H__
#define __TEXTURE_CONVERSION_H__

void Convert565to8888( unsigned short *Buffer1, unsigned int *Buffer2, unsigned int Pixels );
void MMX565to8888( unsigned short *Src, unsigned int *Dst, unsigned int NumberOfPixels );
void Cpp565to8888( unsigned short *Buffer1, unsigned int *Buffer2, unsigned int Pixels );

void Convert565Kto8888( unsigned short *Buffer1, unsigned short key, unsigned int *Buffer2, unsigned int Pixels );

void Convert565to5551( unsigned int *Buffer1, unsigned int *Buffer2, int Pixels );
void MMX565to5551( unsigned int *Src, unsigned int *Dst, int NumberOfPixels );
void Cpp565to5551( unsigned int *Buffer1, unsigned int *Buffer2, int Pixels );

void Convert5551to565( unsigned int *Buffer1, unsigned int *Buffer2, int Pixels );
void MMX5551to565( unsigned int *Src, unsigned int *Dst, int NumberOfPixels );
void Cpp5551to565( unsigned int *Buffer1, unsigned int *Buffer2, int Pixels );

void Convert8888to565( unsigned int *Src, unsigned short *Dst, unsigned int Pixels );

void Convert4444to4444special( unsigned int *Buffer1, unsigned int *Buffer2, int Pixels );
void MMX4444to4444special( unsigned int *Src, unsigned int *Dst, int NumberOfPixels );
void Cpp4444to4444special( unsigned int *Buffer1, unsigned int *Buffer2, int Pixels );

void Convert1555to5551( unsigned int *Buffer1, unsigned int *Buffer2, int Pixels );
void MMX1555to5551( unsigned int *Src, unsigned int *Dst, int NumberOfPixels );
void Cpp1555to5551( unsigned int *Buffer1, unsigned int *Buffer2, int Pixels );

void ConvertA8toAP88( unsigned char *Buffer1, unsigned short *Buffer2, unsigned int Pixels );
void ConvertAI44toAP88( unsigned char *Buffer1, unsigned short *Buffer2, unsigned int Pixels );
void Convert8332to8888( unsigned short *Buffer1, unsigned int *Buffer2, unsigned int Pixels );
void ConvertP8to8888( unsigned char *Buffer1, unsigned int *Buffer2, unsigned int Pixels, unsigned int *palette );
void ConvertAP88to8888( unsigned short *Buffer1, unsigned int *Buffer2, unsigned int Pixels, unsigned int *palette );
void ConvertYIQto8888( unsigned char *in, unsigned int *out, unsigned int Pixels, GuNccTable *ncc );
void ConvertAYIQto8888( unsigned short *in, unsigned int *out, unsigned int Pixels, GuNccTable *ncc );
void SplitAP88( unsigned short *ap88, unsigned char *index, unsigned char *alpha, unsigned int pixels );

#endif
