//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#ifndef __WIN32_H__
#define __WIN32_H__

#include "3dfx.h"
#include "glide.h"

#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Functions for handling display window */

bool InitialiseOpenGLWindow(unsigned int wnd, int x, int y, int width, int height);
void FinaliseOpenGLWindow( void);

void SetGamma(float value);
void RestoreGamma();

bool SetScreenMode(int &xsize, int &ysize);
void ResetScreenMode();

void SwapBuffers();

/* Functions for handling OpenGL extensions */

ExtFn OGLGetProcAddress(const char *x);

/* Functions for reporting errors */

void ReportWarning(const char *);
void ReportError(const char *);

/* Clock functions */

float ClockFrequency( void );

#endif