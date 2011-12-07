//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#ifndef WRAPPER_CONFIG_H
#define WRAPPER_CONFIG_H

#include "win32.h"

#define WRAPPER_FLAG_WINDOWED               (0x1)
#define WRAPPER_FLAG_MIPMAPS                (0x2)
#define WRAPPER_FLAG_PALETTED_TEXTURE_CACHE (0x4)
#define WRAPPER_FLAG_MANAGED_TEXTURES       (0x8)

FX_ENTRY void FX_CALL setConfig(uint32_t flags);

#endif /* WRAPPER_CONFIG_H */
