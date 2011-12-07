//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#ifndef __TEXTURE_CONVERSION_H__
#define __TEXTURE_CONVERSION_H__
 
void Convert565to8888( uint16_t *Buffer1, uint32_t *Buffer2, uint32_t Pixels );
void MMX565to8888( uint16_t *Src, uint32_t *Dst, uint32_t NumberOfPixels );
void Cpp565to8888( uint16_t *Buffer1, uint32_t *Buffer2, uint32_t Pixels );

void Convert565Kto8888( uint16_t *Buffer1, uint16_t key, uint32_t *Buffer2, uint32_t Pixels );

void Convert565to5551( uint32_t *Buffer1, uint32_t *Buffer2, int Pixels );
void MMX565to5551( uint32_t *Src, uint32_t *Dst, int NumberOfPixels );
void Cpp565to5551( uint32_t *Buffer1, uint32_t *Buffer2, int Pixels );

void Convert5551to565( uint32_t *Buffer1, uint32_t *Buffer2, int Pixels );
void MMX5551to565( uint32_t *Src, uint32_t *Dst, int NumberOfPixels );
void Cpp5551to565( uint32_t *Buffer1, uint32_t *Buffer2, int Pixels );

void Convert8888to565( uint32_t *Src, uint16_t *Dst, uint32_t Pixels );

void Convert4444to4444special( uint32_t *Buffer1, uint32_t *Buffer2, int Pixels );
void MMX4444to4444special( uint32_t *Src, uint32_t *Dst, int NumberOfPixels );
void Cpp4444to4444special( uint32_t *Buffer1, uint32_t *Buffer2, int Pixels );

void Convert1555to5551( uint32_t *Buffer1, uint32_t *Buffer2, int Pixels );
void MMX1555to5551( uint32_t *Src, uint32_t *Dst, int NumberOfPixels );
void Cpp1555to5551( uint32_t *Buffer1, uint32_t *Buffer2, int Pixels );

void ConvertA8toAP88( uint8_t *Buffer1, uint16_t *Buffer2, uint32_t Pixels );
void ConvertAI44toAP88( uint8_t *Buffer1, uint16_t *Buffer2, uint32_t Pixels );
void Convert8332to8888( uint16_t *Buffer1, uint32_t *Buffer2, uint32_t Pixels );
void ConvertP8to8888( uint8_t *Buffer1, uint32_t *Buffer2, uint32_t Pixels, uint32_t *palette );
void ConvertAP88to8888( uint16_t *Buffer1, uint32_t *Buffer2, uint32_t Pixels, uint32_t *palette );
void ConvertYIQto8888( uint8_t *in, uint32_t *out, uint32_t Pixels, GuNccTable *ncc );
void ConvertAYIQto8888( uint16_t *in, uint32_t *out, uint32_t Pixels, GuNccTable *ncc );
void SplitAP88( uint16_t *ap88, uint8_t *index, uint8_t *alpha, uint32_t pixels );

#endif
