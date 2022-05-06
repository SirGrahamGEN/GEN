/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSTM32Sleep.h
*
* @class      XSTM32SLEEP
* @brief      eXtended utils STM32 sleep class
* @ingroup    PLATFORM_STM32
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

#ifndef _XSTM32SLEEP_H_
#define _XSTM32SLEEP_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XSleep.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XSTM32SLEEP : public XSLEEP
{
  public:

                       XSTM32SLEEP                 ();
    virtual           ~XSTM32SLEEP                 ();

    virtual void       Seconds                      (int seconds);
    virtual void       MilliSeconds                 (int milliseconds);
    virtual void       MicroSeconds                 (int microseconds);
    virtual void       NanoSeconds                  (int nanoseconds);
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif



