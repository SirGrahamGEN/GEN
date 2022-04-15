/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xFlashMemory.cpp
*
* @class      XSAMD5XE5XFLASHMEMORY
* @brief      SAMD5xE5x Flash Memory class
* @ingroup    PLATFORM_SAMD5XE5X
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "XSAMD5xE5xFlashMemory.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XFLASHMEMORY::XSAMD5XE5XFLASHMEMORY()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XFLASHMEMORY::XSAMD5XE5XFLASHMEMORY()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XFLASHMEMORY::~XSAMD5XE5XFLASHMEMORY()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XFLASHMEMORY::~XSAMD5XE5XFLASHMEMORY()
{

}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XFLASHMEMORY::Ini()
* @brief      Ini
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XFLASHMEMORY::Ini()
{
  //--- ABRHAMD5XE5X ------------------
  /*
  __PWR_CLK_ENABLE();

  __BKPSRAM_CLK_ENABLE();

  HAL_PWR_EnableBkUpAccess();

  HAL_PWR_EnableBkUpReg();

  */

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XFLASHMEMORY::End()
* @brief      End
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XFLASHMEMORY::End()
{

  //--- ABRHAMD5XE5X ------------------
  /*
  //HAL_PWR_DisableBkUpReg();

  __BKPSRAM_CLK_DISABLE();

  __HAL_RCC_PWR_CLK_DISABLE();
  */

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XFLASHMEMORY::Read(XDWORD offset, XBYTE* data, XDWORD size)
* @brief      Read
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  offset :
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XFLASHMEMORY::Read(XDWORD offset, XBYTE* data, XDWORD size)
{
  //--- ABRHAMD5XE5X ------------------
  /*
  if((offset + size) > XSAMD5XE5XFLASHMEMORY_MAXSIZE) return false;

  for(int c=0; c<size; c++)
    {
      (*(data+c)) = (*(__IO uint8_t *)(XSAMD5XE5XFLASHMEMORY_BASE+offset+c));
    }
  */

  return true;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XFLASHMEMORY::Write(XDWORD offset, XBYTE* data, XDWORD size)
* @brief      Write
* @ingroup    PLATFORM_SAMD5XE5X
*
* @param[in]  offset :
* @param[in]  data :
* @param[in]  size :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XFLASHMEMORY::Write(XDWORD offset, XBYTE* data, XDWORD size)
{
  //--- ABRHAMD5XE5X ------------------
  /*
  if((offset + size) > XSAMD5XE5XFLASHMEMORY_MAXSIZE) return false;

  for(int c=0; c<size; c++)
    {
      (*(__IO uint8_t *)(XSAMD5XE5XFLASHMEMORY_BASE+offset+c)) = (*(data+c));
    }
  */

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XFLASHMEMORY::EraseAll()
* @brief      EraseAll
* @ingroup    PLATFORM_SAMD5XE5X
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XFLASHMEMORY::EraseAll()
{
  //--- ABRHAMD5XE5X ------------------
  /*
  for(int c=0; c<XSAMD5XE5XFLASHMEMORY_MAXSIZE; c++)
    {
      (*(__IO uint8_t *)(XSAMD5XE5XFLASHMEMORY_BASE+c))= 0;
    }
  */

  return true;
}






