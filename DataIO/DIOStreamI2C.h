/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOStreamI2C.h
* 
* @class      DIOSTREAMI2C
* @brief      Data Input/Output Stream I2C class
* @ingroup    DATAIO
* 
* @author     Abraham J. Velez 
* @date       01/03/2016 12:00
* 
* @copyright  Copyright(c) 2005 - 2021 GEN Group.
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
* *---------------------------------------------------------------------------------------------------------------------*/

#ifndef _DIOSTREAMI2C_H_
#define _DIOSTREAMI2C_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFSMachine.h"

#include "DIOStream.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum  DIOSTREAMI2C_FSMEVENTS
{
  DIOSTREAMI2C_FSMEVENT_NONE                 = 0  ,
  DIOSTREAMI2C_FSMEVENT_CONNECTED                 ,
  DIOSTREAMI2C_FSMEVENT_WAITINGTOREAD             ,
  DIOSTREAMI2C_FSMEVENT_SENDINGDATA               ,
  DIOSTREAMI2C_FSMEVENT_DISCONNECTING             ,

  DIOSTREAMI2C_LASTEVENT
};

enum  DIOSTREAMI2C_FSMSTATES
{
  DIOSTREAMI2C_FSMSTATE_NONE                = 0  ,

  DIOSTREAMI2C_FSMSTATE_CONNECTED                ,
  DIOSTREAMI2C_FSMSTATE_WAITINGTOREAD            ,
  DIOSTREAMI2C_FSMSTATE_SENDINGDATA              ,
  DIOSTREAMI2C_FSMSTATE_DISCONNECTING            ,

  DIOSTREAMI2C_LASTSTATE
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XBUFFER;
class XFACTORY;
class XTHREADCOLLECTED;
class DIOGPIO;
class DIOSTREAMI2CCONFIG;


class DIOSTREAMI2C : public DIOSTREAM , public XFSMACHINE
{
  public:
                                  DIOSTREAMI2C                              ();
    virtual                      ~DIOSTREAMI2C                              ();

    DIOSTREAMCONFIG*              GetConfig                                 ();
    bool                          SetConfig                                 (DIOSTREAMCONFIG* config);

    virtual bool                  Open                                      ();

    virtual XDWORD                ReadDirect                                (XBYTE* buffer, XDWORD size);
    virtual XDWORD                WriteDirect                               (XBYTE* buffer, XDWORD size);

    virtual bool                  Close                                     ();

 protected:

    DIOSTREAMI2CCONFIG*           config;
    XTHREADCOLLECTED*             threadconnection;

  private:

    void                          Clean                                     ();
};

/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif



