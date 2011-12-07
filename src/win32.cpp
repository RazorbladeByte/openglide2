//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

#ifdef _MSC_VER
#pragma warning(disable: 4996)
#endif

#include "win32.h"
#include "GlOgl.h"

/* Functions for handling display window */

static HDC   hDC;
static HGLRC hRC;
static HWND  hWND;
static struct
{
    uint16_t red[ 256 ];
    uint16_t green[ 256 ];
    uint16_t blue[ 256 ];
} old_ramp;

static BOOL ramp_stored  = false;
static BOOL mode_changed = false;
#ifdef USE_SDL
static BOOL wasInit      = false;
#endif

bool InitialiseOpenGLWindow(uint32_t wnd, int x, int y, int width, int height)
{
    #ifdef USE_SDL
    bool FullScreen = UserConfig.InitFullScreen;
    wasInit = SDL_WasInit(SDL_INIT_VIDEO)!=0;
    if(!wasInit)
    {
        bool err = false;
        char *oldWindowId = 0;
        char windowId[40];

        if (wnd)
        {   // Set SDL window ID
            sprintf (windowId, "SDL_WINDOWID=%ld", (long)wnd);
            oldWindowId = getenv("SDL_WINDOWID");
            if (oldWindowId)
                oldWindowId = strdup(oldWindowId);
            putenv(windowId);
        }

        if (SDL_Init(SDL_INIT_VIDEO))
        {
            GlideMsg("Can't init SDL %s",SDL_GetError());
            err = true;
        }

        if (wnd)
        {   // Restore old value
            if (!oldWindowId)
                putenv("SDL_WINDOWID");
            else
            {
                sprintf (windowId, "SDL_WINDOWID=%s", oldWindowId);
                putenv(windowId);
                free (oldWindowId);
            }
        }

        if (err)
            return false;
    } else {
        SDL_Surface* tmpSurface = SDL_GetVideoSurface();
        if (tmpSurface)
        {
            // Preserve window/fullscreen mode in SDL apps and override config file entry
           (tmpSurface->flags&SDL_FULLSCREEN) ? (FullScreen = true) : (FullScreen = false);
        }
    } 

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if((SDL_SetVideoMode(width, height, 32, FullScreen ? SDL_OPENGL|SDL_FULLSCREEN : SDL_OPENGL)) == 0)
    {
        GlideMsg("Video mode set failed: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &height);
    if ( height > 16 ) {
        UserConfig.PrecisionFix = false;
    }

    if(SDL_GetGammaRamp(old_ramp.red, old_ramp.green, old_ramp.blue) != -1)
        ramp_stored = true;

    return true;
    #else
    PIXELFORMATDESCRIPTOR   pfd;
    int                     PixFormat;
    uint32_t            BitsPerPixel;
    HWND                    hwnd = (HWND) wnd;

    if( hwnd == NULL )
    {
        hwnd = GetActiveWindow();
    }

    if ( hwnd == NULL )
    {
        MessageBox( NULL, "NULL window specified", "Error", MB_OK );
        exit( 1 );
    }

    mode_changed = false;

    if ( UserConfig.InitFullScreen )
    {
        SetWindowLong( hwnd, 
                       GWL_STYLE, 
                       WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
        MoveWindow( hwnd, 0, 0, width, height, false );
        mode_changed = SetScreenMode( width, height );
    }
    else
    {
       RECT rect;
       rect.left = 0;
       rect.right = width;
       rect.top = 0;
       rect.bottom = height;

       AdjustWindowRectEx( &rect, 
                           GetWindowLong( hwnd, GWL_STYLE ),
                           GetMenu( hwnd ) != NULL,
                           GetWindowLong( hwnd, GWL_EXSTYLE ) );
       MoveWindow( hwnd, 
                   x, y, 
                   x + ( rect.right - rect.left ),
                   y + ( rect.bottom - rect.top ),
                   true );
    }

    hWND = hwnd;

    hDC = GetDC( hwnd );
    BitsPerPixel = GetDeviceCaps( hDC, BITSPIXEL );

    ZeroMemory( &pfd, sizeof( pfd ) );
    pfd.nSize        = sizeof( pfd );
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType   = PFD_TYPE_RGBA;
    pfd.cColorBits   = BitsPerPixel;
    pfd.cDepthBits   = BitsPerPixel;

    if ( !( PixFormat = ChoosePixelFormat( hDC, &pfd ) ) )
    {
        MessageBox( NULL, "ChoosePixelFormat() failed:  "
                    "Cannot find a suitable pixel format.", "Error", MB_OK );
        exit( 1 );
    } 

    // the window must have WS_CLIPCHILDREN and WS_CLIPSIBLINGS for this call to
    // work correctly, so we SHOULD set this attributes, not doing that yet
    if ( !SetPixelFormat( hDC, PixFormat, &pfd ) )
    {
        MessageBox( NULL, "SetPixelFormat() failed:  "
                    "Cannot set format specified.", "Error", MB_OK );
        exit( 1 );
    } 

    DescribePixelFormat( hDC, PixFormat, sizeof( PIXELFORMATDESCRIPTOR ), &pfd );
    GlideMsg( "ColorBits	= %d\n", pfd.cColorBits );
    GlideMsg( "DepthBits	= %d\n", pfd.cDepthBits );

    if ( pfd.cDepthBits > 16 )
    {
        UserConfig.PrecisionFix = false;
    }

    hRC = wglCreateContext( hDC );
    wglMakeCurrent( hDC, hRC );

    HDC pDC = GetDC( NULL );

    ramp_stored = GetDeviceGammaRamp( pDC, &old_ramp );

    ReleaseDC( NULL, pDC );
    return true;
    #endif
}

void FinaliseOpenGLWindow(void)
{
    #ifdef USE_SDL
	if ( ramp_stored )
        SDL_SetGammaRamp(old_ramp.red, old_ramp.green, old_ramp.blue);
    if (!wasInit)
        SDL_Quit();
    #else
    if ( ramp_stored )
    {
        HDC pDC = GetDC( NULL );

        BOOL res = SetDeviceGammaRamp( pDC, &old_ramp );

        ReleaseDC( NULL, pDC );
    }

    wglMakeCurrent( NULL, NULL );
    wglDeleteContext( hRC );
    ReleaseDC( hWND, hDC );

    if( mode_changed )
    {
        ResetScreenMode( );
    }
    #endif
}

void SetGamma(float value)
{
    struct
    {
        WORD red[256];
        WORD green[256];
        WORD blue[256];
    } ramp;
    int i;
    #ifndef USE_SDL
    HDC pDC = GetDC( NULL );
    #endif

    for ( i = 0; i < 256; i++ )
    {
        WORD v = (WORD)( 0xffff * pow( i / 255.0, 1.0 / value ) );

        ramp.red[ i ] = ramp.green[ i ] = ramp.blue[ i ] = ( v & 0xff00 );
    }

    #ifdef USE_SDL
	SDL_SetGammaRamp(ramp.red, ramp.green, ramp.blue);
    #else
    BOOL res = SetDeviceGammaRamp( pDC, &ramp );

    ReleaseDC( NULL, pDC );
    #endif
}

void RestoreGamma()
{
}

bool SetScreenMode(int &xsize, int &ysize)
{
    #ifdef USE_SDL
	return true;
    #else
    HDC          hdc;
    uint32_t bits_per_pixel;
    bool         found;
    DEVMODE      DevMode;

    hdc = GetDC( hWND );
    bits_per_pixel = GetDeviceCaps( hdc, BITSPIXEL );
    ReleaseDC( hWND, hdc );
    
    found = false;
    DevMode.dmSize = sizeof( DEVMODE );
    
    for ( int i = 0; 
          !found && EnumDisplaySettings( NULL, i, &DevMode ) != false; 
          i++ )
    {
        if ( ( DevMode.dmPelsWidth  == (uint32_t)xsize ) && 
             ( DevMode.dmPelsHeight == (uint32_t)ysize ) && 
             ( DevMode.dmBitsPerPel == bits_per_pixel ) )
        {
            found = true;
        }
    }
    
    return ( found && ChangeDisplaySettings( &DevMode, CDS_RESET|CDS_FULLSCREEN ) == DISP_CHANGE_SUCCESSFUL );
    #endif
}

void ResetScreenMode()
{
    #ifndef USE_SDL
    ChangeDisplaySettings( NULL, 0 );
    #endif
}

void SwapBuffers()
{
    #ifdef USE_SDL
	SDL_GL_SwapBuffers();
    #else
    SwapBuffers(hDC);
    #endif
}


/* Functions for reporting errors */

void ReportWarning(const char *message)
{
    MessageBox( NULL, message, "Warning", MB_OK );
}

void ReportError(const char *message)
{
    MessageBox( NULL, message, "Error", MB_OK );
}


/* Clock functions */

#pragma optimize( "", off )
float ClockFrequency( void )
{
    int64_t i64_perf_start, 
            i64_perf_freq, 
            i64_perf_end,
            i64_clock_start,
            i64_clock_end;
    double  d_loop_period, 
            d_clock_freq;

    QueryPerformanceFrequency( (LARGE_INTEGER*)&i64_perf_freq );

    QueryPerformanceCounter( (LARGE_INTEGER*)&i64_perf_start );
    i64_perf_end = 0;

    RDTSC( i64_clock_start );
    while( i64_perf_end < ( i64_perf_start + 350000 ) )
    {
        QueryPerformanceCounter( (LARGE_INTEGER*)&i64_perf_end );
    }
    RDTSC( i64_clock_end );

    i64_clock_end -= i64_clock_start;

    d_loop_period = ((double)i64_perf_freq) / 350000.0;
    d_clock_freq = ((double)( i64_clock_end & 0xffffffff )) * d_loop_period;

    return (float)d_clock_freq;
}
#pragma optimize( "", on )