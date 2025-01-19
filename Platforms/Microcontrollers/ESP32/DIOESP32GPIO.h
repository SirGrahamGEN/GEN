/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOESP32GPIO.h
*
* @class      DIOESP32GPIO
* @brief      Data Input/Output ESP32 General Port Input/Ouput (GPIO)
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

#ifndef _DIOESP32GPIO_H_
#define _DIOESP32GPIO_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DIOGPIO.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOESP32GPIO : public DIOGPIO
{

  public:
                              DIOESP32GPIO        ();
    virtual                  ~DIOESP32GPIO        ();

    bool                      Ini                 ();    
    
    bool                      SetMode             (DIOGPIO_ENTRY* entry, XWORD mode);  

    bool                      GetValue            (DIOGPIO_ENTRY* entry);
    bool                      SetValue            (DIOGPIO_ENTRY* entry, bool value);

    bool                      End                 ();

  private:

    void                      Clean               ();

};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif

