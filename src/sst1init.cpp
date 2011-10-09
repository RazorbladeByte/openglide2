//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#include "sst1init.h"

FX_ENTRY FxU32* FX_CALL sst1InitMapBoard(FxU32 BoardNumber)
{
#ifdef OGL_NOTDONE
    GlideMsg("sst1InitMapBoard(%d)\n", param1);
#endif

	return NULL;
}


FX_ENTRY FxBool FX_CALL sst1InitGamma(FxU32 *sstbase, FxDouble gamma)
{
#ifdef OGL_NOTDONE
    GlideMsg("sst1InitGamma(%d, %g)\n", sstbase, gamma);
#endif

	return FXTRUE;
}
