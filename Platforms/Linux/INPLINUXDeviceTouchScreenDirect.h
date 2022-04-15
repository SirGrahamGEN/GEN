/**-------------------------------------------------------------------------------------------------------------------
*
* @file       INPLINUXDeviceTouchScreenDirect.h
*
* @class      INPLINUXDEVICETOUCHSCREENDIRECT
* @brief      LINUX direct input device mouse class
* @ingroup    PLATFORM_LINUX
*
* @copyright  GEN Group. All right reserved.
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

#ifndef _INPLINUXDEVICETOUCHSCREENDIRECT_H_
#define _INPLINUXDEVICETOUCHSCREENDIRECT_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XVector.h"

#include "INPLINUXDeviceID.h"

#include "INPDevice.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class INPLINUXDEVICETOUCHSCREENDIRECT : public INPDEVICE
{
  public:

                                  INPLINUXDEVICETOUCHSCREENDIRECT   ();
  virtual                        ~INPLINUXDEVICETOUCHSCREENDIRECT   ();


   bool                           Update                            ();

  private:

    void                          Clean                             ();

    bool                          CreateAllButtons                  ();
    bool                          CreateAllCursors                  ();

    bool                          OpenAllDevicesID                  ();
    bool                          CloseAllDevicesID                 ();

    bool                          UpdateTouchScreenData             ();

    XVECTOR<INPLINUXDEVICEID*>    touchscr;

    int                           touchscr_x;
    int                           touchscr_y;

};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif


