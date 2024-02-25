/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOLightSensorLDRAnalog.h
* 
* @class      DIOLIGHTSENSORLDRANALOG
* @brief      Data Input/Output IO Sensor Light LDR (Light Dependent Resistor) Analog in port digital class
*             http://www.raspberrypi-spy.co.uk/2012/08/reading-analogue-sensors-with-one-gpio-pin/
* @ingroup    DATAIO
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

#ifndef _DIOLIGHTSENSORLDRANALOG_H_
#define _DIOLIGHTSENSORLDRANALOG_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XBase.h"
#include "XTreadCollected.h"

#include "DIODevice.h"
#include "DIOGPIO.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class XTIMER;
class XMUTEX;
class DIOGPIO;

class DIOLIGHTSENSORLDRANALOG :  public DIODEVICE
{
  public:
                          DIOLIGHTSENSORLDRANALOG       (DIOGPIO* diogpio, int pindata, bool activatecache);
    virtual              ~DIOLIGHTSENSORLDRANALOG       ();

    bool                  Ini                           ();

    int                   GetPinData                    ();

    bool                  ReadFromCache                 (XDWORD& level);
    bool                  ReadDirect                    (XDWORD& level);

    bool                  End                           ();

  private:
 
    static void           ThreadRunFunction             (void* param);
    
    void                  Clean                         ();

    DIOGPIO*              diogpio;
    int                   pindata;

    XTIMER*               xtimer;
    XTHREADCOLLECTED*     threadcache;
    XMUTEX*               xmutexread;

    XDWORD                nreads;
    XDWORD                levelcache;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

