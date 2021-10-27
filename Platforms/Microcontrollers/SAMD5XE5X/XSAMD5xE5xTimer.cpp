/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xTimer.cpp
*
* @class      XSAMD5XE5XTIMER
* @brief      SAMD5xE5x timer class
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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

#include "XSAMD5xE5x_HAL.h"
#include "XSAMD5xE5xTimer.h"

#include "XSAMD5xE5xPlatformIni.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XTIMER::XSAMD5XE5XTIMER()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XTIMER::XSAMD5XE5XTIMER()
{
  Reset();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XTIMER::~XSAMD5XE5XTIMER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XTIMER::~XSAMD5XE5XTIMER()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XQWORD XSAMD5XE5XTIMER::GetMicroSecondsTickCounter()
* @brief      GetMicroSecondsTickCounter
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XQWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XQWORD XSAMD5XE5XTIMER::GetMicroSecondsTickCounter()
{
  XQWORD elapsedtime = 0;

  //--- ABRHAMD5XE5X ------------------

  elapsedtime = HAL_tick_count;

  elapsedtime *= 1000;  // Pass to MicroSeconds

  return elapsedtime;
}



