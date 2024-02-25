/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOI2CPWMControlerPCA9685.h
* 
* @class      DIOI2CPWMCONTROLERPCA9685
* @brief      Data Input/Output I2C PCA9685 (16-channel, 12-bit PWM controller) class
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

#ifndef _DIOI2CPWMCONTROLERPCA9685_H_
#define _DIOI2CPWMCONTROLERPCA9685_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <stdio.h>

#include "XBase.h"
#include "XString.h"

#include "DIODeviceI2C.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


#define DIOI2CPWMCONTROLERPCA9685_ADDR          0x40

#define DIOI2CPWMCONTROLERPCA9685_MODE1         0x00
#define DIOI2CPWMCONTROLERPCA9685_PRESCALE      0xFE

#define DIOI2CPWMCONTROLERPCA9685_LED0_ON_L     0x06
#define DIOI2CPWMCONTROLERPCA9685_LED0_ON_H     0x07
#define DIOI2CPWMCONTROLERPCA9685_LED0_OFF_L    0x08
#define DIOI2CPWMCONTROLERPCA9685_LED0_OFF_H    0x09

#define DIOI2CPWMCONTROLERPCA9685_ALLLED_ON_L   0xFA
#define DIOI2CPWMCONTROLERPCA9685_ALLLED_ON_H   0xFB
#define DIOI2CPWMCONTROLERPCA9685_ALLLED_OFF_L  0xFC
#define DIOI2CPWMCONTROLERPCA9685_ALLLED_OFF_H  0xFD


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOI2CPWMCONTROLERPCA9685 : public DIODEVICEI2C
{
  public:

                              DIOI2CPWMCONTROLERPCA9685   ();
    virtual                  ~DIOI2CPWMCONTROLERPCA9685   ();

    bool                      Reset                       ();
    bool                      SetPWMFrequency             (float frequency);
    bool                      SetPWM                      (XBYTE channel, XWORD on, XWORD off, bool wait = true);

    bool                      End                         ();

    bool                      ReadCommand                 (XBYTE cmd, XBYTE& value);
    bool                      SendCommand                 (XBYTE cmd, XBYTE value, bool wait = true);

  
  private:

    bool                      IniDevice                   ();

    void                      Clean                       ();
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

