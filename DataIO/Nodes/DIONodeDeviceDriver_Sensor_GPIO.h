/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeDeviceDriver_Sensor_GPIO.h
* 
* @class      DIONODEDEVICEDRIVER_SENSOR_GPIO
* @brief      Data Input/Output Node Device Driver sensor GPIO
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

#ifndef _DIONODEDEVICEDRIVER_SENSOR_GPIO_H_
#define _DIONODEDEVICEDRIVER_SENSOR_GPIO_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIONodeDeviceDriver_GPIO.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIONODEDEVICEDRIVER_SENSOR_GPIO : public DIONODEDEVICEDRIVER_GPIO
{
  public:
                                  DIONODEDEVICEDRIVER_SENSOR_GPIO       (XDWORD entryID, int GPIO = DIONODEDEVICEDRIVER_GPIO_INVALIDPARAM, int pin = DIONODEDEVICEDRIVER_GPIO_INVALIDPARAM);
    virtual                      ~DIONODEDEVICEDRIVER_SENSOR_GPIO       ();

    virtual bool                  Open                                  ();
    virtual bool                  Update                                ();
    
  private:

    void                          Clean                                 ();      
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
