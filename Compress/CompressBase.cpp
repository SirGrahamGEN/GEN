/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       CompressBase.cpp
* 
* @class      COMPRESSBASE
* @brief      Compress Base class
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

#include "CompressBase.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
* @fn         COMPRESSBASE::COMPRESSBASE()
* @brief      Constructor of class
* @ingroup    COMPRESS
* 
* --------------------------------------------------------------------------------------------------------------------*/
COMPRESSBASE::COMPRESSBASE()
{
  SetType();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         COMPRESSBASE::COMPRESSBASE(COMPRESSBASE_TYPE type)
* @brief      Constructor of class
* @ingroup    COMPRESS
* 
* @param[in]  type : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
COMPRESSBASE::COMPRESSBASE(COMPRESSBASE_TYPE type)
{
  SetType(type);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         COMPRESSBASE::~COMPRESSBASE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    COMPRESS
* 
* --------------------------------------------------------------------------------------------------------------------*/
COMPRESSBASE::~COMPRESSBASE()
{
  SetType();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         COMPRESSBASE_TYPE COMPRESSBASE::GetType()
* @brief      Get type
* @ingroup    COMPRESS
* 
* @return     COMPRESSBASE_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
COMPRESSBASE_TYPE COMPRESSBASE::GetType()
{
  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         COMPRESSBASE_TYPE COMPRESSBASE::SetType(COMPRESSBASE_TYPE type)
* @brief      Set type
* @ingroup    COMPRESS
* 
* @param[in]  type : 
* 
* @return     COMPRESSBASE_TYPE : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
COMPRESSBASE_TYPE COMPRESSBASE::SetType(COMPRESSBASE_TYPE type)
{
  this->type = type;

  return type;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool COMPRESSBASE::Compress(XBYTE* origin,XDWORD size,XBUFFER* buffer)
* @brief      Compress
* @ingroup    COMPRESS
* 
* @param[in]  origin : 
* @param[in]  size : 
* @param[in]  buffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool COMPRESSBASE::Compress(XBYTE* origin,XDWORD size,XBUFFER* buffer)
{
  if(!origin)   return false;
  if(!size)     return false;
  if(!buffer)   return false;

  memcpy(buffer->Get(),origin,size);
  buffer->SetSize(size);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool COMPRESSBASE::Decompress(XBYTE* origin,XDWORD size,XBUFFER* buffer)
* @brief      Decompress
* @ingroup    COMPRESS
* 
* @param[in]  origin : 
* @param[in]  size : 
* @param[in]  buffer : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool COMPRESSBASE::Decompress(XBYTE* origin,XDWORD size,XBUFFER* buffer)
{
  if(!origin)   return false;
  if(!size)     return false;
  if(!buffer)   return false;

  memcpy(buffer->Get(),origin,size);
  buffer->SetSize(size);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool COMPRESSBASE::Compress(XBYTE* origin,XDWORD size,void* param1)
* @brief      Compress
* @ingroup    COMPRESS
* 
* @param[in]  origin : 
* @param[in]  size : 
* @param[in]  param1 : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool COMPRESSBASE::Compress(XBYTE* origin,XDWORD size,void* param1)
{
  if(!origin) return false;
  if(!size)   return false;

  for(XDWORD c=0; c<size; c++)
    {
      CompressResult(true,origin[c],param1);
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool COMPRESSBASE::Decompress(XBYTE* origin,XDWORD size,void* param1)
* @brief      Decompress
* @ingroup    COMPRESS
* 
* @param[in]  origin : 
* @param[in]  size : 
* @param[in]  param1 : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool COMPRESSBASE::Decompress(XBYTE* origin,XDWORD size,void* param1)
{
  if(!origin) return false;
  if(!size)   return false;

  for(XDWORD c=0; c<size; c++)
    {
      CompressResult(false,origin[c],param1);
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool COMPRESSBASE::CompressResult(bool compress,XBYTE data,void* param1)
* @brief      Compress result
* @ingroup    COMPRESS
* 
* @param[in]  compress : 
* @param[in]  data : 
* @param[in]  param1 : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool COMPRESSBASE::CompressResult(bool compress,XBYTE data,void* param1)
{
  if(compress)
    {

    }
   else
    {

    }

  return false;
}


#pragma endregion

