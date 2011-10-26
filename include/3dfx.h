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

/* color types */

typedef unsigned long                FxColor_t;
typedef struct { float r, g, b, a; } FxColor4;

/* fundamental types */

#define FXTRUE    1
#define FXFALSE   0

/* helper macros */

#define FXUNUSED( a ) ((void)(a))
#define FXBIT( i )    ( 1L << (i) )
#ifdef __GNUC__
#define VARARGDECL(t) extern "C" t
#else
#define VARARGDECL(t) t __cdecl
#endif

/* export macros */
#define FX_ENTRY __declspec(dllexport)
#define FX_CALL __stdcall

/* customs  */

#define FASTCALL __fastcall
#define OG_memcpy MMXCopyMemory

typedef int (__stdcall *ExtFn)();

#endif /* !__3DFX_H__ */
