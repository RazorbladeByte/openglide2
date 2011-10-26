//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#include "sst1init.h"

FX_ENTRY unsigned int* FX_CALL sst1InitMapBoard(unsigned int BoardNumber)
{
#ifdef OGL_NOTDONE
    GlideMsg("sst1InitMapBoard(%d)\n", param1);
#endif

	return NULL;
}


FX_ENTRY int FX_CALL sst1InitGamma(unsigned int *sstbase, double gamma)
{
#ifdef OGL_NOTDONE
    GlideMsg("sst1InitGamma(%d, %g)\n", sstbase, gamma);
#endif

	return FXTRUE;
}
