/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIONodeItemHandler_Actuator_GPIO.h
* 
* @class      DIONODEITEMHANDLER_ACTUATOR_GPIO
* @brief      Data Input/Output Node Item Handler actuator GPIO
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

#ifndef _DIONODEITEMHANDLER_ACTUATOR_GPIO_H_
#define _DIONODEITEMHANDLER_ACTUATOR_GPIO_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIONodeItemHandler_GPIO.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIONODEITEMHANDLER_ACTUATOR_GPIO : public DIONODEITEMHANDLER_GPIO
{
  public:
                                  DIONODEITEMHANDLER_ACTUATOR_GPIO      (XDWORD entryID, int GPIO = DIONODEITEMHANDLER_INVALIDPARAM, int pin = DIONODEITEMHANDLER_INVALIDPARAM);
    virtual                      ~DIONODEITEMHANDLER_ACTUATOR_GPIO      ();

    virtual bool                  Open                                  ();
    virtual bool                  Update                                ();
    
  private:

    void                          Clean                                 ();      
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif
