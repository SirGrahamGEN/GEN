/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOSTM32StreamUSB.h
*
* @class      DIOSTM32STREAMUSB
* @brief      Data Input/Output STM32 Stream USB class
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

#ifndef _DIOSTM32STREAMUSB_H_
#define _DIOSTM32STREAMUSB_H_


#if defined(DIO_ACTIVE) && defined(DIO_STREAMUSB_ACTIVE)


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XBuffer.h"
#include "XFSMachine.h"

#include "XSTM32_HAL.h"

#include "usb_device.h"

#include "DIOStreamUSB.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DIOSTM32USBFSMEVENTS
{
  DIOSTM32USBFSMEVENT_NONE               = 0  ,
  DIOSTM32USBFSMEVENT_CONNECTED             ,
  DIOSTM32USBFSMEVENT_WAITINGTOREAD         ,
  DIOSTM32USBFSMEVENT_DISCONNECTING         ,

  DIOSTM32USB_LASTEVENT

};


enum DIOSTM32USBFSMSTATES
{
  DIOSTM32USBFSMSTATE_NONE               = 0  ,

  DIOSTM32USBFSMSTATE_CONNECTED             ,
  DIOSTM32USBFSMSTATE_WAITINGTOREAD         ,
  DIOSTM32USBFSMSTATE_DISCONNECTING         ,

  DIOSTM32USB_LASTSTATE
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFACTORY;
class XPUBLISHER;
class DIOFACTORY;
class DIOSTREAMCONFIG;
class XTHREADCOLLECTED;


class DIOSTM32STREAMUSB : public DIOSTREAMUSB, public XFSMACHINE
{
  public:
                                DIOSTM32STREAMUSB         ();
    virtual                    ~DIOSTM32STREAMUSB         ();

    DIOSTREAMSTATUS             GetStatus              ();

    bool                        Open                          ();

    XDWORD                      WriteDirect                   (XBYTE* buffer, XDWORD size);

    XDWORD                      Write                         (XBYTE* buffer, XDWORD size);

    bool                        Disconnect                    ();
    bool                        Close                         ();

    bool                        CleanBuffers                  ();

    void                        HAL_USB_RxCpltCallback        (uint8_t* Buf, uint32_t *Len);

  protected:

    static void                 ThreadConnection              (void* param);
    void                        Clean                         ();

    XBUFFER                     readcache;
    XBYTE                       writebuffer[DIOSTREAM_MAXBUFFER];

    XTHREADCOLLECTED*           threadconnection;
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

extern DIOSTM32STREAMUSB*  diostreamusbptrhandle;


#endif

#endif






