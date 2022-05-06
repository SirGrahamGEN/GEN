/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOSAMD5xE5xGPIO.h
*
* @class      DIOSAMD5XE5XGPIO
* @brief      SAMD5XE5X DIO General Port Input/Ouput
* @ingroup    PLATFORM_SAMD5XE5X
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

#ifndef _DIOSAMD5XE5XGPIO_H_
#define _DIOSAMD5XE5XGPIO_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOGPIO.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOSAMD5XE5XGPIO : public DIOGPIO
{
  public:
                          DIOSAMD5XE5XGPIO            ();
    virtual              ~DIOSAMD5XE5XGPIO            ();

    bool                  Ini                         ();

    bool                  SetMode                     (XBYTE pin, bool isinput, DIOGPIO_PINSGROUP block = DIOGPIO_PINSGROUP_A, DIOGPIO_PULLMODE pullmode = DIOGPIO_PULLMODE_OFF);

    bool                  Get                         (XBYTE pin, DIOGPIO_PINSGROUP block = DIOGPIO_PINSGROUP_A);
    bool                  Set                         (XBYTE pin, bool active, DIOGPIO_PINSGROUP block = DIOGPIO_PINSGROUP_A);

    bool                  End                         ();

  private:

    void                  Clean                       ();

};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

