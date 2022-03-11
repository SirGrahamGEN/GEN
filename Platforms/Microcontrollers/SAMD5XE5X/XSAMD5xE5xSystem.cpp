/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xSystem.cpp
*
* @class      XSAMD5XE5XSYSTEM
* @brief      SAMD5xE5x system class
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

#include <stdio.h>

#include "XString.h"

#include "XSAMD5xE5x_HAL.h"
#include "XSAMD5xE5xSystem.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XSYSTEM::XSAMD5XE5XSYSTEM()
* @brief      Constructor
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSAMD5XE5XSYSTEM::XSAMD5XE5XSYSTEM() : XSYSTEM()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSAMD5XE5XSYSTEM::~XSAMD5XE5XSYSTEM()
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
XSAMD5XE5XSYSTEM::~XSAMD5XE5XSYSTEM()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEM_HARDWARETYPE XSAMD5XE5XSYSTEM::GetTypeHardware(int* revision)
* @brief      GetTypeHardware
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  revision :
*
* @return     XSYSTEM_HARDWARETYPE :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_HARDWARETYPE XSAMD5XE5XSYSTEM::GetTypeHardware(int* revision)
{
  return XSYSTEM_HARDWARETYPE_MICRO_SAMD5XE5X;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSYSTEM_SO XSAMD5XE5XSYSTEM::GetTypeSO()
* @brief      GetTypeSO
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSYSTEM_SO :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_SO XSAMD5XE5XSYSTEM::GetTypeSO()
{
  return XSYSTEM_SO_UNKNOWN;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XSYSTEM_PLATFORM XSAMD5XE5XSYSTEM::GetPlatform(XSTRING* namestring)
* @brief      GetPlatform
* @ingroup    
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @param[in]  namestring : 
* 
* @return     XSYSTEM_PLATFORM : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
XSYSTEM_PLATFORM XSAMD5XE5XSYSTEM::GetPlatform(XSTRING* namestring)
{
  if(namestring)  namestring->Set(__L("SAMD5xE5x"));

  return XSYSTEM_PLATFORM_UNKNONW;  
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XSAMD5XE5XSYSTEM::GetLanguageSO()
* @brief      GetLanguageSO
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XSAMD5XE5XSYSTEM::GetLanguageSO()
{
  return 0;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XSAMD5XE5XSYSTEM::GetSerialNumber()
* @brief      GetSerialNumber
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XSAMD5XE5XSYSTEM::GetSerialNumber()
{
  return NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XSYSTEM::GetMemoryInfo(XDWORD& total,XDWORD& free)
* @brief      GetMemoryInfo
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  total :
* @param[in]  free :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XSYSTEM::GetMemoryInfo(XDWORD& total,XDWORD& free)
{
  total = 0;
  free  = 0;

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XSYSTEM::ShutDown(XSYSTEM_CHANGESTATUSTYPE type)
* @brief      ShutDown
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  type :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XSYSTEM::ShutDown(XSYSTEM_CHANGESTATUSTYPE type)
{
  switch(type)
    {
      case XSYSTEM_CHANGESTATUSTYPE_REBOOT            : //--- ABRHAMD5XE5X ------------------
                                                        /*
                                                        #if defined(STM32F407xx) || defined(STM32F411xE) || defined(STM32F446x)
                                                          {
                                                            __DSB();                                                                                                                     // Ensure all outstanding memory accesses included buffered write are completed before reset
                                                             SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos) | (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) | SCB_AIRCR_SYSRESETREQ_Msk);        // Keep priority group unchanged
                                                            __DSB();                                                                                                                     // Ensure completion of memory access
                                                            while(1);                                                                                                                    // Wait until reset
                                                          }
                                                        #endif
                                                        */
                                                        break;

      case XSYSTEM_CHANGESTATUSTYPE_SESSION_LOGOFF    : break;

      case XSYSTEM_CHANGESTATUSTYPE_POWEROFF          : break;

                                        default       : break;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSAMD5XE5XSYSTEM::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSAMD5XE5XSYSTEM::Clean()
{

}

