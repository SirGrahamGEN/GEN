/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSTM32DebugTrace.h
*
* @class      XSTM32TRACE
* @brief      eXtended utils STM32 trace class
* @ingroup    PLATFORM_STM32    PLATFORM_STM32
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

#ifndef _XSTM32TRACE_H_
#define _XSTM32TRACE_H_

#ifdef XTRACE_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBase.h"
#include "XString.h"
#include "XTrace.h"

#include "DIOURL.h"

#include "XSTM32_HAL.h"
#include "XSTM32Factory.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XSTM32TRACE : public XTRACE
{
  public:
                          XSTM32TRACE           ();
    virtual              ~XSTM32TRACE           ();

    virtual void          PrintSpecial          (XTRACE_TARGET* target, XBYTE level, XCHAR* string);

    UART_HandleTypeDef*   GetHuart              ();
    void                  SetHuart              (UART_HandleTypeDef* huart);

  private:

    void                  Clean                 ();

    UART_HandleTypeDef*   huart;
    XBUFFER               xbuffercache;
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

#endif


