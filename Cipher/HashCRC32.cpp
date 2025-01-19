/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       HashCRC32.cpp
* 
* @class      HASHCRC32
* @brief      Hash CRC32 class
* @ingroup    CIPHER
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

#include "HashCRC32.h"

#include <string.h>

#include "XTrace.h"
#include "XFactory.h"
#include "XBuffer.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#define  HASHCRC32_INI      0xEDB88320

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         HASHCRC32::HASHCRC32()
* @brief      Constructor of class
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
HASHCRC32::HASHCRC32() : HASH()
{
  Clean();

  type = HASHTYPE_CRC32;

  resulttmp = new XBUFFER();

  XDWORD value = 0xffffffff;
  resulttmp->Add((XDWORD)value);

  Ini();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         HASHCRC32::~HASHCRC32()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
HASHCRC32::~HASHCRC32()
{
  if(resulttmp)
    {
      delete resulttmp;
      resulttmp = NULL;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool HASHCRC32::Do(XBYTE* input, XQWORD size)
* @brief      Do
* @ingroup    CIPHER
* 
* @param[in]  input : 
* @param[in]  size : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool HASHCRC32::Do(XBYTE* input, XQWORD size)
{
  if(!size) return false;

  XDWORD  value = 0;

  resulttmp->Extract(value);

  for(XDWORD c=0;c<size;c++)
    {
      value = Update(value, (*input));
      input++;
    }

  resulttmp->Add((XDWORD)value);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool HASHCRC32::ResetResult()
* @brief      Reset result
* @ingroup    CIPHER
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool HASHCRC32::ResetResult()
{
  HASH::ResetResult();

  resulttmp->Delete();
  XDWORD value = 0xffffffff;
  resulttmp->Add((XDWORD)value);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int HASHCRC32::GetDefaultSize()
* @brief      Get default size
* @ingroup    CIPHER
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int HASHCRC32::GetDefaultSize()
{
  return sizeof(XDWORD);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBUFFER* HASHCRC32::GetResult()
* @brief      Get result
* @ingroup    CIPHER
* 
* @return     XBUFFER* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBUFFER* HASHCRC32::GetResult()
{
  GetResultCRC32();

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XBYTE* HASHCRC32::GetResult(XDWORD& resultsize)
* @brief      Get result
* @ingroup    CIPHER
* 
* @param[in]  resultsize : 
* 
* @return     XBYTE* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE* HASHCRC32::GetResult(XDWORD& resultsize)
{
  GetResultCRC32();

  resultsize  = result->GetSize();

  return result->Get();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD HASHCRC32::GetResultCRC32()
* @brief      Get result CRC32
* @ingroup    CIPHER
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD HASHCRC32::GetResultCRC32()
{
  XDWORD value = 0;

  result->Delete();

  resulttmp->Extract(value);

  value ^= 0xffffffff;

  result->Add((XDWORD)value);

  return value;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void HASHCRC32::Ini()
* @brief      Ini
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
void HASHCRC32::Ini()
{
  XDWORD crc;
  int    i;
  int    j;

  for(i=0; i<256; i++)
    {
      crc = (XDWORD) i;

      for(j=0; j<8; j++)
        {
           if(crc & 0x00000001)
                  crc = ( crc >> 1 ) ^ HASHCRC32_INI;
            else  crc =   crc >> 1;
        }

      table[i] = crc;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDWORD HASHCRC32::Update(XDWORD CRC32, XBYTE data)
* @brief      Update
* @ingroup    CIPHER
* 
* @param[in]  CRC32 : 
* @param[in]  data : 
* 
* @return     XDWORD : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD HASHCRC32::Update(XDWORD CRC32, XBYTE data)
{
  XDWORD tmp;
  XDWORD long_c;

  long_c = 0x000000FF & (XDWORD) data;
  tmp    = CRC32 ^ long_c;

  CRC32 = (CRC32 >> 8) ^ table[ tmp & 0xff ];

  return CRC32;

}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void HASHCRC32::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    CIPHER
* 
* --------------------------------------------------------------------------------------------------------------------*/
void HASHCRC32::Clean()
{
  resulttmp = NULL;
}


#pragma endregion

