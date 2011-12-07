//********************************************************
//            openglide2 - Glide to OpenGL Wrapper        
//                  Licensed under the LGPL               
//********************************************************

/* implementation of the TexDB class */

#include "GlOgl.h"
#include "TexDB.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TexDB::TexDB( uint32_t MemorySize )
{
    numberOfTexSections = MemorySize >> 15; // ( 32 * 1024 );

    m_first = new Record*[ numberOfTexSections ];

    for ( uint32_t i = 0; i < numberOfTexSections; i++ )
    {
        m_first[ i ] = NULL;
    }
}

TexDB::~TexDB( void )
{
    Record * r;

    for ( uint32_t i = 0; i < numberOfTexSections; i++ )
    {
        r = m_first[ i ];
        
        while ( r != NULL )
        {
            Record * tmp = r;
            r = r->next;
            delete tmp;
        }
    }
    delete[] m_first;
}

GrTexInfo * TexDB::Find( uint32_t startAddress, GrTexInfo *info, uint32_t hash, 
                         GLuint *pTexNum, GLuint *pTex2Num, bool *pal_change )
{
    Record         * r;
    uint32_t   sect = startAddress >> 15; // ( 32 * 1024 );

    for ( r = m_first[ sect ]; r != NULL; r = r->next )
    {
        if ( r->Match( startAddress, info, ( pal_change == NULL ) ? hash : 0 ) )
        {
            *pTexNum = r->texNum;

            if ( pTex2Num )
            {
                *pTex2Num = r->tex2Num;
            }

            if ( ( pal_change != NULL ) && ( r->hash != hash ) )
            {
                r->hash = hash;
                *pal_change = true;
            }

#ifdef OGL_UTEX
            GlideMsg( "Found tex %d\n", r->texNum );
#endif
            return &r->info;
        }
    }

#ifdef OGL_UTEX
    GlideMsg( "Tex not found\n" );
#endif

    return NULL;
}

void TexDB::WipeRange(uint32_t startAddress, uint32_t endAddress, uint32_t hash)
{
    Record         ** p;
    uint32_t   stt_sect;
    uint32_t   end_sect;

    stt_sect = startAddress >> 15; // ( 32 * 1024 );

   /*
    * Textures can be as large as 128K, so
    * one that starts 3 sections back can
    * extend into this one.
    */
    if ( stt_sect < 4 )
    {
        stt_sect = 0;
    }
    else
    {
        stt_sect -= 4;
    }
 
    end_sect = endAddress >> 15; // ( 32 * 1024 );

    if ( end_sect >= numberOfTexSections )
    {
        end_sect = numberOfTexSections - 1;
    }

    for ( uint32_t i = stt_sect; i <= end_sect; i++ )
    {
        p = &( m_first[ i ] );
        while ( *p != NULL )
        {
            Record * r = *p;
            
            if ( ( startAddress < r->endAddress ) && 
                 ( r->startAddress < endAddress ) && 
                 ( ( hash == 0 ) || ( r->hash == hash ) ) )
            {
                *p = r->next;
#ifdef OGL_UTEX
                GlideMsg( "Wipe tex %d\n", r->texNum );
#endif
                delete r;
            }
            else
            {
                p = &(r->next);
            }
        }
    }
}

void TexDB::Add( uint32_t startAddress, uint32_t endAddress, GrTexInfo *info, 
	             uint32_t hash, GLuint *pTexNum, GLuint *pTex2Num )
{
    Record     *r = new Record( pTex2Num != NULL );
    uint32_t   sect;

    sect = startAddress >> 15; // 32 * 1024

    r->startAddress = startAddress;
    r->endAddress = endAddress;
    r->info = *info;
    r->hash = hash;

    r->next = m_first[ sect ];
    m_first[ sect ] = r;

#ifdef OGL_UTEX
    GlideMsg( "Add tex %d\n", r->texNum );
#endif

    *pTexNum = r->texNum;

    if ( pTex2Num )
    {
        *pTex2Num = r->tex2Num;
    }
}


void TexDB::Clear( void )
{
    Record  * r;

    for ( uint32_t i = 0; i < numberOfTexSections; i++ )
    {
        r = m_first[ i ];
        
        while ( r != NULL )
        {
            Record *tmp = r;
            r = r->next;
            delete tmp;
        }

        m_first[ i ] = NULL;
    }
}

// TexDB::Record Class implementation

TexDB::Record::Record( bool two_tex )
{
   glGenTextures( 1, &texNum );

   if ( two_tex )
   {
         glGenTextures( 1, &tex2Num );
   }
   else
   {
         tex2Num = 0;
   }
}

TexDB::Record::~Record( void )
{
   glDeleteTextures( 1, &texNum );

   if ( tex2Num != 0 )
   {
         glDeleteTextures( 1, &tex2Num );
   }
}

bool TexDB::Record::Match( uint32_t stt, GrTexInfo *inf, uint32_t h )
{
   return ( ( startAddress == stt ) && 
            ( inf->largeLod == info.largeLod ) && 
            ( inf->aspectRatio == info.aspectRatio ) && 
            ( inf->format == info.format ) && 
            ( ( hash == h ) || ( h == 0 ) ) );
}
