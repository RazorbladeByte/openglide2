/*
   Copyright (c) 1995, 3Dfx Interactive, Inc.
   All Rights Reserved.
*/

#include <windows.h>
#include <io.h>

#ifndef __3DFX_H__
#define __3DFX_H__

/* basic data types */

typedef int FxBool;

/* fundamental types */

#define FXTRUE    1
#define FXFALSE   0

/* helper macros */

#define FXBIT( i )    ( 1L << (i) )
#define VARARGDECL(t) t __cdecl

/* export macros */
#define FX_ENTRY __declspec(dllexport)
#define FX_CALL __stdcall

/* customs  */

#define FASTCALL __fastcall
#define OG_memcpy MMXCopyMemory

typedef int (__stdcall *ExtFn)();

#endif /* !__3DFX_H__ */
