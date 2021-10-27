/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSTM32DebugTrace.cpp
*
* @class      XSTM32TRACE
* @brief      eXtended utils STM32 timer class
* @ingroup    PLATFORM_STM32    PLATFORM_STM32
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


#ifdef XTRACE_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"
#include "XBuffer.h"
#include "XSleep.h"
#include "XTrace.h"

#include "XSTM32DateTime.h"

#include "XSTM32Trace.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTM32TRACE::XSTM32TRACE()
* @brief      Constructor
* @ingroup    PLATFORM_STM32    PLATFORM_STM32
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTM32TRACE::XSTM32TRACE()
{
  Clean();

  XTRACE::instance = this;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTM32TRACE::~XSTM32TRACE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    PLATFORM_STM32    PLATFORM_STM32
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTM32TRACE::~XSTM32TRACE()
{
  Clean();

  XTRACE::instance = NULL;
}




/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTM32TRACE::PrintSpecial(XTRACE_TARGET* target, XBYTE level, XCHAR* string)
* @brief      Print Special aim
* @ingroup    PLATFORM_STM32    PLATFORM_STM32
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  target : target to print the debug
* @param[in]  level : level of debug
* @param[in]  string : string with the line
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSTM32TRACE::PrintSpecial(XTRACE_TARGET* target, XBYTE level, XCHAR* string)
{
  XSTM32DATETIME   xdatetime;
  static bool      reenter = false;

  if(!huart) return;

  if(reenter)
    {
      XBUFFER         xbufferpackettmp;
      static XBUFFER   xbuffercache;
      XSTM32DATETIME   xdatetime;

      SetTraceTextToXBuffer(0xFFFFFFFF, 0xFFFFFFFF, level, sequence, &xdatetime, string, xbufferpackettmp);      
      
      xbuffercache.Add(xbufferpackettmp);
    }
   else
    {
      reenter = true;

      if(xbuffercache.GetSize())
        {
          HAL_UART_Transmit(huart, (uint8_t*)xbuffercache.Get(), (uint16_t)xbuffercache.GetSize(), 1000);
          xbuffercache.Delete();
        }

      XBUFFER          xbufferpacket;
      XSTM32DATETIME   xdatetime;

      SetTraceTextToXBuffer(0xFFFFFFFF, 0xFFFFFFFF, level, sequence, &xdatetime, string, xbufferpacket);
      HAL_UART_Transmit(huart, (uint8_t*)xbufferpacket.Get(), (uint16_t)xbufferpacket.GetSize(), 1000);

      reenter = false;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UART_HandleTypeDef* XSTM32TRACE::GetHuart()
* @brief      GetHuart
* @ingroup    PLATFORM_STM32
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     UART_HandleTypeDef* :
*
*---------------------------------------------------------------------------------------------------------------------*/
UART_HandleTypeDef* XSTM32TRACE::GetHuart()
{
  return huart;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTM32TRACE::SetHuart(UART_HandleTypeDef* huart)
* @brief      SetHuart
* @ingroup    PLATFORM_STM32
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  huart :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSTM32TRACE::SetHuart(UART_HandleTypeDef* huart)
{
  this->huart = huart;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSTM32TRACE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    PLATFORM_STM32    PLATFORM_STM32
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XSTM32TRACE::Clean()
{
  huart = NULL;
}


#endif
