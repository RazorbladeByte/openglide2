//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

/* Obsolete sst-1 interfacec */

#pragma once

#include "win32.h"


FX_ENTRY unsigned int* FX_CALL sst1InitMapBoard(unsigned int BoardNumber);
FX_ENTRY FxBool FX_CALL sst1InitGamma(unsigned int *sstbase, double gamma);
