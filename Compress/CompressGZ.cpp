/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CompressGZ.cpp
* 
* @class      COMPRESSGZ
* @brief      Compress GZ class
* @ingroup    COMPRESS
* 
* @copyright  GEN Group. All rights reserved.
* 
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
* 
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "CompressGZ.h"

#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#include "XBuffer.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         COMPRESS_GZ::COMPRESS_GZ()
* @brief      Constructor of class
* @ingroup    COMPRESS
* 
* --------------------------------------------------------------------------------------------------------------------*/
COMPRESS_GZ::COMPRESS_GZ() : COMPRESSBASE()
{
  Clean();

  SetType(COMPRESSBASE_TYPE_GZ);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         COMPRESS_GZ::~COMPRESS_GZ()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    COMPRESS
* 
* --------------------------------------------------------------------------------------------------------------------*/
COMPRESS_GZ::~COMPRESS_GZ()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool COMPRESS_GZ::Compress(XBYTE* source, XDWORD size, XBUFFER* xbuffer)
* @brief      Compress
* @ingroup    COMPRESS
* 
* @param[in]  source : 
* @param[in]  size : 
* @param[in]  xbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool COMPRESS_GZ::Compress(XBYTE* source, XDWORD size, XBUFFER* xbuffer)
{
  if(!source)  return false;
  if(!size)    return false;
  if(!xbuffer) return false;

  xbuffer->Delete();
  xbuffer->Resize(size);

  XDWORD csize = size;

  ZCompress(xbuffer->Get(), &csize, source, size);

  xbuffer->Resize(csize);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool COMPRESS_GZ::Decompress(XBYTE* source, XDWORD size, XBUFFER* xbuffer)
* @brief      Decompress
* @ingroup    COMPRESS
* 
* @param[in]  source : 
* @param[in]  size : 
* @param[in]  xbuffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool COMPRESS_GZ::Decompress(XBYTE* source, XDWORD size, XBUFFER* xbuffer)
{
  if(!source)  return false;
  if(!size)    return false;
  if(!xbuffer) return false;

  XDWORD csize = xbuffer->GetSize();

  ZDecompress(xbuffer->Get(), &csize, source, size);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int COMPRESS_GZ::ZCompress(XBYTE* target, XDWORD* targetsize, XBYTE* source, XDWORD sourcesize)
* @brief      Z compress
* @ingroup    COMPRESS
* 
* @param[in]  target : 
* @param[in]  targetsize : 
* @param[in]  source : 
* @param[in]  sourcesize : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int COMPRESS_GZ::ZCompress(XBYTE* target, XDWORD* targetsize, XBYTE* source, XDWORD sourcesize)
{
  int       level = -1;
  z_stream  stream;

  stream.zalloc   = Z_NULL;
  stream.zfree    = Z_NULL;
  stream.opaque   = Z_NULL;

  if(deflateInit2(&stream, level, Z_DEFLATED, COMPRESS_GZ_WINDOWBITS | COMPRESS_GZ_ENCODING, 8, Z_DEFAULT_STRATEGY) != Z_OK)  return Z_BUF_ERROR;

  stream.next_in  = (Bytef*)source;
  stream.avail_in = (uInt)sourcesize;

  int destlen     = (uInt)*targetsize;

  do{ //int have;

      stream.avail_out = destlen;
      stream.next_out  = target;

      if(deflate(&stream, Z_FINISH) == Z_STREAM_ERROR)  return Z_STREAM_ERROR;

      //have = destlen - stream.avail_out;

    } while (stream.avail_out == 0);

 (*targetsize) = stream.total_out;

  if(deflateEnd(&stream) != Z_OK) return Z_BUF_ERROR;

  return  Z_OK;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int COMPRESS_GZ::ZDecompress(XBYTE* target,XDWORD* targetsize,XBYTE* source,XDWORD sourcesize)
* @brief      Z decompress
* @ingroup    COMPRESS
* 
* @param[in]  target : 
* @param[in]  targetsize : 
* @param[in]  source : 
* @param[in]  sourcesize : 
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int COMPRESS_GZ::ZDecompress(XBYTE* target,XDWORD* targetsize,XBYTE* source,XDWORD sourcesize)
{
  z_stream  stream;
  int       err;
  int       ret;
//unsigned  have;

  stream.zalloc   = Z_NULL;
  stream.zfree    = Z_NULL;
  stream.opaque   = Z_NULL;
  stream.avail_in = 0;
  stream.next_in  = Z_NULL;

  if(inflateInit2(&stream, 16 + MAX_WBITS) != Z_OK)  return Z_DATA_ERROR;

  stream.avail_in = sourcesize;

  if((uLong)stream.avail_in != (uLong)sourcesize) return Z_BUF_ERROR;

  stream.next_in =  (unsigned char*)source;

  do{ stream.avail_out  = *targetsize;
      stream.next_out   = (XBYTE*)target;
      ret               = inflate(&stream, Z_NO_FLUSH);

      switch(ret)
        {
          case Z_ERRNO          :
          case Z_STREAM_ERROR   :
          case Z_BUF_ERROR      :
          case Z_VERSION_ERROR  :
          case Z_NEED_DICT      :
          case Z_DATA_ERROR     :
          case Z_MEM_ERROR      : inflateEnd(&stream);
                                  return false;
        }

      //have = COMPRESS_GZ_CHUNK - stream.avail_out;

    } while(stream.avail_out == 0);

  if(inflateEnd(&stream) != Z_OK)
    {
      return Z_BUF_ERROR;
    }

  *targetsize = stream.total_out;

  err = inflateEnd(&stream);
  if(err!=Z_OK) return err;

  return Z_OK;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void COMPRESS_GZ::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    COMPRESS
* 
* --------------------------------------------------------------------------------------------------------------------*/
void COMPRESS_GZ::Clean()
{
  param1 = NULL;
}


#pragma endregion

