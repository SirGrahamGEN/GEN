//------------------------------------------------------------------------------------------
//  COMPRESS_GZ.H
//
/**
// \class
//
//  Compression/Descompression LZW Class
//
//  @author  Diego Martinez
//  @version 22/06/2016
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _COMPRESS_GZ_H_
#define _COMPRESS_GZ_H_

//---- INCLUDES ----------------------------------------------------------------------------

#include "CompressBase.h"

//---- DEFINES & ENUMS  --------------------------------------------------------------------


#define COMPRESS_GZ_CHUNK          16384
#define COMPRESS_GZ_WINDOWBITS     15
#define COMPRESS_GZ_ENCODING       16

//---- CLASS -------------------------------------------------------------------------------

class XBUFFER;

class COMPRESS_GZ : public COMPRESSBASE
{
  public:
                            COMPRESS_GZ           ();
    virtual                ~COMPRESS_GZ           ();

    bool                    Compress              (XBYTE* source,XDWORD size,XBUFFER* buffer);
    bool                    Decompress            (XBYTE* source,XDWORD size,XBUFFER* buffer);

  private:

    void                    Clean                 ();

    int                     ZCompress             (XBYTE* target,XDWORD* targetsize,XBYTE* source,XDWORD sourcesize);
    int                     ZDecompress           (XBYTE* target,XDWORD* targetsize,XBYTE* source,XDWORD sourcesize);

};

//---- INLINE FUNCTIONS --------------------------------------------------------------------



#endif
