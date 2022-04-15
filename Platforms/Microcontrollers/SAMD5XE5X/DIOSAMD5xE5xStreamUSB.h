/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOSAMD5xE5xStreamUSB.h
*
* @class      DIOSAMD5XE5XSTREAMUSB
* @brief      SAMD5xE5x Data IO Stream USB class
* @ingroup    PLATFORM_SAMD5XE5X
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

#ifndef _DIOSAMD5XE5XSTREAMUSB_H_
#define _DIOSAMD5XE5XSTREAMUSB_H_


#if defined(DIO_ACTIVE) && defined(DIOUSB_ACTIVE)

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "XBuffer.h"
#include "XFSMachine.h"

#include "XSAMD5xE5x_HAL.h"

//--- ABRHAMD5XE5X ------------------
//#include "usb_device.h"

#include "DIOStreamUSB.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DIOSAMD5XE5XUSBFSMEVENTS
{
  DIOSAMD5XE5XUSBFSMEVENT_NONE               = 0  ,
  DIOSAMD5XE5XUSBFSMEVENT_CONNECTED             ,
  DIOSAMD5XE5XUSBFSMEVENT_WAITINGTOREAD         ,
  DIOSAMD5XE5XUSBFSMEVENT_DISCONNECTING         ,

  DIOSAMD5XE5XUSB_LASTEVENT

};


enum DIOSAMD5XE5XUSBFSMSTATES
{
  DIOSAMD5XE5XUSBFSMSTATE_NONE               = 0  ,

  DIOSAMD5XE5XUSBFSMSTATE_CONNECTED             ,
  DIOSAMD5XE5XUSBFSMSTATE_WAITINGTOREAD         ,
  DIOSAMD5XE5XUSBFSMSTATE_DISCONNECTING         ,

  DIOSAMD5XE5XUSB_LASTSTATE
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFACTORY;
class XPUBLISHER;
class DIOFACTORY;
class DIOSTREAMCONFIG;
class XTHREADCOLLECTED;


class DIOSAMD5XE5XSTREAMUSB : public DIOSTREAMUSB, public XFSMACHINE
{
  public:
                                DIOSAMD5XE5XSTREAMUSB         ();
    virtual                    ~DIOSAMD5XE5XSTREAMUSB         ();

    DIOSTREAMSTATUS             GetConnectStatus              ();

    bool                        Open                          ();

    XDWORD                      WriteDirect                   (XBYTE* buffer, XDWORD size);

    XDWORD                      Write                         (XBYTE* buffer, XDWORD size);

    bool                        Disconnect                    ()                                { return false;                         }
    bool                        Close                         ();

    bool                        CleanBuffers                  ();

    //--- ABRHAMD5XE5X ------------------
    //void                      HAL_USB_RxCpltCallback        (uint8_t* Buf, uint32_t *Len);

  protected:


    static void                 ThreadConnection               (void* param);

    void                        Clean                         ()
                                {
                                  threadconnection   = NULL;
                                }


    XBUFFER                     readcache;
    XBYTE                       writebuffer[DIOSTREAM_MAXBUFFER];

    XTHREADCOLLECTED*           threadconnection;
};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

extern DIOSAMD5XE5XSTREAMUSB*  diostreamusbptrhandle;


#endif

#endif






