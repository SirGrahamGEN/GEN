/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XESP32Trace.cpp
* 
* @class      XESP32TRACE
* @brief      eXtended utils ESP32 timer class
* @ingroup    PLATFORM_ESP32
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

#ifdef XTRACE_ACTIVE

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XESP32Trace.h"

#include "XBase.h"
#include "XBuffer.h"
#include "XSleep.h"
#include "XTrace.h"

#include "XESP32DateTime.h"

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
* @fn         XESP32TRACE::XESP32TRACE()
* @brief      Constructor of class
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
XESP32TRACE::XESP32TRACE()
{
  Clean();

  XTRACE::instance = this;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XESP32TRACE::~XESP32TRACE()
* @brief      Destructor of class
* @note       VIRTUAL
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
XESP32TRACE::~XESP32TRACE()
{
  Clean();

  XTRACE::instance = NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XESP32TRACE::PrintSpecial(XTRACE_TARGET* target, XBYTE level, XCHAR* string)
* @brief      Print special
* @ingroup    PLATFORM_ESP32
*
* @param[in]  target : target to print the debug
* @param[in]  level : level of debug
* @param[in]  string : string with the line
*
* --------------------------------------------------------------------------------------------------------------------*/
void XESP32TRACE::PrintSpecial(XTRACE_TARGET* target, XBYTE level, XCHAR* string)
{
  XESP32DATETIME   xdatetime;
  static bool      reenter = false;

  if(reenter)
    {
      XBUFFER         xbufferpackettmp;
      static XBUFFER   xbuffercache;
      XESP32DATETIME   xdatetime;

      SetTraceTextToXBuffer(0xFFFFFFFF, 0xFFFFFFFF, level, sequence, &xdatetime, string, xbufferpackettmp);      
      
      xbuffercache.Add(xbufferpackettmp);
    }
   else
    {
      reenter = true;

      if(xbuffercache.GetSize())
        {
          //HAL_UART_Transmit(huart, (uint8_t*)xbuffercache.Get(), (uint16_t)xbuffercache.GetSize(), 1000);
          xbuffercache.Delete();
        }

      XBUFFER          xbufferpacket;
      XESP32DATETIME   xdatetime;

      SetTraceTextToXBuffer(0xFFFFFFFF, 0xFFFFFFFF, level, sequence, &xdatetime, string, xbufferpacket);
      //HAL_UART_Transmit(huart, (uint8_t*)xbufferpacket.Get(), (uint16_t)xbufferpacket.GetSize(), 1000);

      reenter = false;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XESP32TRACE::Clean()
* @brief      Clean the attributes of the class: Default initialize
* @note       INTERNAL
* @ingroup    PLATFORM_ESP32
*
* --------------------------------------------------------------------------------------------------------------------*/
void XESP32TRACE::Clean()
{

}


#pragma endregion


#endif

