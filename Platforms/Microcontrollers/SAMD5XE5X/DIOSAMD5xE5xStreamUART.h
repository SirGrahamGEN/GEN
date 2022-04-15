/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOSAMD5xE5xStreamUART.h
*
* @class      DIOSAMD5XE5XSTREAMUART
* @brief      SAMD5xE5x Data IO Stream UART class
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

#ifndef _DIOSAMD5XE5XSTREAMUART_H_
#define _DIOSAMD5XE5XSTREAMUART_H_

#if defined(DIO_ACTIVE) && defined(DIOUART_ACTIVE)

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"
#include "XFSMachine.h"

#include "XSAMD5xE5x_HAL.h"

#include "DIOStreamUART.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DIOSAMD5XE5XUARTFSMEVENTS
{
  DIOSAMD5XE5XUARTFSMEVENT_NONE              = 0  ,
  DIOSAMD5XE5XUARTFSMEVENT_CONNECTED              ,
  DIOSAMD5XE5XUARTFSMEVENT_WAITINGTOREAD          ,
  DIOSAMD5XE5XUARTFSMEVENT_DISCONNECTING          ,

  DIOSAMD5XE5XUART_LASTEVENT

};


enum DIOSAMD5XE5XUARTFSMSTATES
{
  DIOSAMD5XE5XUARTFSMSTATE_NONE              = 0  ,

  DIOSAMD5XE5XUARTFSMSTATE_CONNECTED              ,
  DIOSAMD5XE5XUARTFSMSTATE_WAITINGTOREAD          ,
  DIOSAMD5XE5XUARTFSMSTATE_DISCONNECTING          ,

  DIOSAMD5XE5XUART_LASTSTATE
};

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFACTORY;
class XPUBLISHER;
class DIOFACTORY;
class DIOSTREAMCONFIG;
class XTHREADCOLLECTED;


class DIOSAMD5XE5XSTREAMUART : public DIOSTREAMUART, public XFSMACHINE
{
  public:
                                DIOSAMD5XE5XSTREAMUART        ();
    virtual                    ~DIOSAMD5XE5XSTREAMUART        ();

    DIOSTREAMSTATUS             GetConnectStatus              ();

    bool                        Open                          ();

    bool                        Config                        (XWORD mask = DIOSTREAMUARTMASK_ALL);

    XDWORD                      ReadDirect                    (XBYTE* buffer, XDWORD size);
    XDWORD                      WriteDirect                   (XBYTE* buffer, XDWORD size);

    XDWORD                      Write                         (XBYTE* buffer, XDWORD size);

    bool                        Disconnect                    ();
    bool                        Close                         ();

    bool                        GetCTS                        ();
    bool                        GetDSR                        ();
    bool                        GetRing                       ();
    bool                        GetRLSD                       ();

    bool                        SetRTS                        (bool on = true);
    bool                        SetDTR                        (bool on = true);

    bool                        CleanBuffers                  ();

    //--- ABRHAMD5XE5X ------------------
    //UART_HandleTypeDef          huart;
    XBYTE                       receiveddata;
    XBUFFER                     readcache[3];

  protected:

    static void                 ThreadConnection              (void* param);

    void                        Clean                         ();

    XTHREADCOLLECTED*           threadconnection;
    int                         indexport;
    XBYTE                       writebuffer[DIOSTREAM_MAXBUFFER];
};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/


extern DIOSAMD5XE5XSTREAMUART*  diostreamuartptrhandle[3];


#endif

#endif





