/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOSAMD5xE5xStreamSPI.h
*
* @class      DIOSAMD5XE5XSTREAMSPI
* @brief      SAMD5xE5x Data IO Stream SPI class
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

#ifndef _DIOSAMD5XE5XSTREAMSPI_H_
#define _DIOSAMD5XE5XSTREAMSPI_H_

#if defined(DIO_ACTIVE) && defined(DIOSPI_ACTIVE)

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"
#include "XFSMachine.h"

#include "XSAMD5xE5x_HAL.h"

#include "DIOStreamSPI.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define DIOSAMD5XE5XSTREAMSPI_MAXHANDLES   2
#define DIOSAMD5XE5XSTREAMSPI_MAXPORTS     2

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XFACTORY;
class XPUBLISHER;
class DIOFACTORY;
class DIOSTREAMCONFIG;
class XTHREADCOLLECTED;


class DIOSAMD5XE5XSTREAMSPIPORT : public DIOSTREAMSPI
{
  public:
                                            DIOSAMD5XE5XSTREAMSPIPORT           ();
    virtual                                ~DIOSAMD5XE5XSTREAMSPIPORT           ();


    XDWORD                                  GetCounterRef                       ();
    void                                    SetCounterRef                       (XDWORD counterref);

    //--- ABRHAMD5XE5X ------------------
    //SPI_HandleTypeDef*                      GetHandleSPI                        ();
    //void                                    SetHandleSPI                        (SPI_HandleTypeDef* hspi);

  private:

    void                                    Clean                               ();

    XDWORD                                  counterref;
    //--- ABRHAMD5XE5X ------------------
    //SPI_HandleTypeDef*                      hspi;
};




class DIOSAMD5XE5XSTREAMSPI : public DIOSTREAMSPI
{
  public:
                                            DIOSAMD5XE5XSTREAMSPI               ();
    virtual                                ~DIOSAMD5XE5XSTREAMSPI               ();

    DIOSTREAMSTATUS                         GetConnectStatus                    ();

    bool                                    Open                                ();

    bool                                    WaitToFilledReadingBuffer           (int filledto = DIOSTREAM_SOMETHINGTOREAD, int timeout = XTIMER_INFINITE);

    XDWORD                                  ReadDirect                          (XBYTE* buffer, XDWORD size);
    XDWORD                                  WriteDirect                         (XBYTE* buffer, XDWORD size);

    XDWORD                                  Write                               (XBYTE* buffer, XDWORD size);

    bool                                    Disconnect                          ();
    bool                                    Close                               ();

    bool                                    CleanBuffers                        ();

    //--- ABRHAMD5XE5X ------------------
  //SPI_HandleTypeDef*                      hspi;
    XWORD                                   localaddress;
    XWORD                                   remoteaddress;
    XBYTE                                   bufferdata[DIOSTREAM_MAXBUFFER];
    XWORD                                   sizebufferdata;
    XBUFFER                                 readcache[DIOSAMD5XE5XSTREAMSPI_MAXPORTS];

    static DIOSAMD5XE5XSTREAMSPIPORT*       ports[DIOSAMD5XE5XSTREAMSPI_MAXPORTS];
    static DIOSAMD5XE5XSTREAMSPI*           handles[DIOSAMD5XE5XSTREAMSPI_MAXHANDLES];

    int                                     indexhandle;
    int                                     indexport;

  protected:

    static void                             ThreadConnection                    (void* param);

    void                                    Clean                               ();



    XTHREADCOLLECTED*                       threadconnection;
    XBYTE                                   writebuffer[DIOSTREAM_MAXBUFFER];

};



/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

#endif

