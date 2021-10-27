/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xRand.cpp
*
* @class      XSAMD5XE5XRAND
* @brief      SAMD5xE5x rand class
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

#include <time.h>

#include "XSAMD5xE5xRand.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XRAND::XSAMD5XE5XRAND()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XRAND::XSAMD5XE5XRAND()
{
  Ini();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XRAND::~XSAMD5XE5XRAND()
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
XSAMD5XE5XRAND::~XSAMD5XE5XRAND()
{

}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XRAND::Ini()
* @brief      Ini
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XRAND::Ini()
{
  srand((unsigned)time(NULL));

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSAMD5XE5XRAND::MaxElements(int max)
* @brief      MaxElements
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  max :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int XSAMD5XE5XRAND::MaxElements(int max)
{
  return GETRANDOM(0,max-1);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSAMD5XE5XRAND::Max(int max)
* @brief      Max
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  max :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int XSAMD5XE5XRAND::Max(int max)
{
  return GETRANDOM(0,max);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSAMD5XE5XRAND::Between(int min,int max)
* @brief      Between
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  min :
* @param[in]  max :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int XSAMD5XE5XRAND::Between(int min,int max)
{
  return GETRANDOM(min,max);
}


