/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOANDROIDGPIO.cpp
*
* @class      DIOANDROIDGPIO
* @brief      Android DIO General Port Input/Ouput
* @ingroup    PLATFORM_ANDROID
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

#ifdef ANDROID


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include "DIOANDROIDGPIO.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOANDROIDGPIO::DIOANDROIDGPIO()
* @brief      Constructor
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOANDROIDGPIO::DIOANDROIDGPIO(): DIOGPIO()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DIOANDROIDGPIO::~DIOANDROIDGPIO()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DIOANDROIDGPIO::~DIOANDROIDGPIO()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOANDROIDGPIO::Ini()
* @brief      Ini
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOANDROIDGPIO::Ini()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOANDROIDGPIO::SetMode(XBYTE pin, bool isinput)
* @brief      SetMode
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  pin :
* @param[in]  isinput :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOANDROIDGPIO::SetMode(XBYTE pin, bool isinput)
{

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOANDROIDGPIO::Get(XBYTE pin)
* @brief      Get
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  pin :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOANDROIDGPIO::Get(XBYTE pin)
{

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOANDROIDGPIO::Set(XBYTE pin, bool active)
* @brief      Set
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  pin :
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOANDROIDGPIO::Set(XBYTE pin, bool active)
{

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DIOANDROIDGPIO::End()
* @brief      End
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DIOANDROIDGPIO::End()
{

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DIOANDROIDGPIO::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_ANDROID
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DIOANDROIDGPIO::Clean()
{

}


#endif
