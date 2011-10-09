/*
   Copyright (c) 1995, 3Dfx Interactive, Inc.
   All Rights Reserved.
*/

#include <windows.h>
#include <io.h>

#ifndef __3DFX_H__
#define __3DFX_H__

/* basic data types */

typedef unsigned int       FxU;
typedef int                FxI;
typedef unsigned char      FxU8;
typedef signed   char      FxI8;
typedef unsigned short     FxU16;
typedef signed   short     FxI16;
typedef signed   int       FxI32;
typedef unsigned int       FxU32;
typedef long long          FxI64;
typedef unsigned long long FxU64;
typedef int                FxBool;
typedef float              FxFloat;
typedef double             FxDouble;
typedef FxU32              FxU;
typedef FxI32              FxI;



/* color types */

typedef unsigned long                FxColor_t;
typedef struct { float r, g, b, a; } FxColor4;

/* fundamental types */

#define FXTRUE    1
#define FXFALSE   0

/* helper macros */

#define FXUNUSED( a ) ((void)(a))
#define FXBIT( i )    ( 1L << (i) )
#define VARARGDECL(t) t __cdecl

/* export macros */
#ifdef __GNUC__
  #define DLL_PUBLIC __declspec(dllexport)
#else
  #define DLLEXPORT __declspec(dllexport)
#endif
#define FX_ENTRY DLLEXPORT
#define FX_CALL __stdcall

/* customs  */

#define FASTCALL __fastcall
#define OG_memcpy MMXCopyMemory

typedef int (__stdcall *ExtFn)();

#endif /* !__3DFX_H__ */
