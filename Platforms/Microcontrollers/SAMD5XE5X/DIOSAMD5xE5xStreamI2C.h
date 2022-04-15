/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DIOSAMD5xE5xStreamI2C.h
*
* @class      DIOSAMD5XE5XSTREAMI2C
* @brief      SAMD5xE5x Data IO Stream I2C class
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

#ifndef _DIOSAMD5XE5XSTREAMI2C_H_
#define _DIOSAMD5XE5XSTREAMI2C_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"
#include "XFSMachine.h"

#include "XSAMD5xE5x_HAL.h"

#include "DIOStreamI2C.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define DIOSAMD5XE5XSTREAMI2C_MAXHANDLES   8
#define DIOSAMD5XE5XSTREAMI2C_MAXPORTS     2

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class XFACTORY;
class XPUBLISHER;
class DIOFACTORY;
class DIOSTREAMCONFIG;
class XTHREADCOLLECTED;


class DIOSAMD5XE5XSTREAMI2CPORT
{
  public:
                                            DIOSAMD5XE5XSTREAMI2CPORT           ();
    virtual                                ~DIOSAMD5XE5XSTREAMI2CPORT           ();


    XDWORD                                  GetCounterRef                       ();
    void                                    SetCounterRef                       (XDWORD counterref);

    //--- ABRHAMD5XE5X ------------------
    //I2C_HandleTypeDef*                      GetHandleI2C                        ();
    //void                                    SetHandleI2C                        (I2C_HandleTypeDef* hi2c);

  private:

    void                                    Clean                               ();


    XDWORD                                  counterref;
    //--- ABRHAMD5XE5X ------------------
    //I2C_HandleTypeDef*                      hi2c;
};





class DIOSAMD5XE5XSTREAMI2C : public DIOSTREAMI2C
{
  public:
                                            DIOSAMD5XE5XSTREAMI2C               ();
    virtual                                ~DIOSAMD5XE5XSTREAMI2C               ();

    DIOSTREAMSTATUS                         GetConnectStatus                    ();

    virtual bool                            Open                                ();

    bool                                    WaitToFilledReadingBuffer           (int filledto = DIOSTREAM_SOMETHINGTOREAD, int timeout = XTIMER_INFINITE);

    XDWORD                                  ReadDirect                          (XBYTE* buffer, XDWORD size);
    XDWORD                                  WriteDirect                         (XBYTE* buffer, XDWORD size);

    XDWORD                                  Write                               (XBYTE* buffer, XDWORD size);

    bool                                    Disconnect                          ();
    bool                                    Close                               ();

    bool                                    CleanBuffers                        ();

    //--- ABRHAMD5XE5X ------------------
    //I2C_HandleTypeDef*                      hi2c;
    XWORD                                   localaddress;
    XWORD                                   remoteaddress;
    XBYTE                                   bufferdata[DIOSTREAM_MAXBUFFER];
    XWORD                                   sizebufferdata;
    XBUFFER                                 readcache[DIOSAMD5XE5XSTREAMI2C_MAXPORTS];

    static DIOSAMD5XE5XSTREAMI2CPORT*       ports[DIOSAMD5XE5XSTREAMI2C_MAXPORTS];
    static DIOSAMD5XE5XSTREAMI2C*           handles[DIOSAMD5XE5XSTREAMI2C_MAXHANDLES];

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








