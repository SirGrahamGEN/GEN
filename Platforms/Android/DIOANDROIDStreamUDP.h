/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOANDROIDStreamUDP.h
* 
* @class      DIOANDROIDSTREAMUDP
* @brief      ANDROID Data Input/Output Stream UDP class
* @ingroup    PLATFORM_ANDROID
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

#ifndef _DIOANDROIDSTREAMUDP_H_
#define _DIOANDROIDSTREAMUDP_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <stdio.h>

#include "XFSMachine.h"
#include "XANDROIDThread.h"

#include "DIOStreamUDP.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum DIOANDROIDUDPFSMEVENTS
{
  DIOANDROIDUDPFSMEVENT_NONE              = 0 ,

  DIOANDROIDUDPFSMEVENT_GETTINGCONNECTION      ,
  DIOANDROIDUDPFSMEVENT_CONNECTED             ,
  DIOANDROIDUDPFSMEVENT_WAITINGTOREAD         ,
  DIOANDROIDUDPFSMEVENT_SENDINGDATA           ,
  DIOANDROIDUDPFSMEVENT_DISCONNECTING         ,

  DIOANDROIDUDP_LASTEVENT
};


enum DIOANDROIDUDPFSMSTATES
{
  DIOANDROIDUDPFSMSTATE_NONE              = 0 ,

  DIOANDROIDUDPFSMSTATE_GETTINGCONNECTION      ,
  DIOANDROIDUDPFSMSTATE_CONNECTED             ,
  DIOANDROIDUDPFSMSTATE_WAITINGTOREAD         ,
  DIOANDROIDUDPFSMSTATE_SENDINGDATA           ,
  DIOANDROIDUDPFSMSTATE_DISCONNECTING         ,

  DIOANDROIDUDP_LASTSTATE
};


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS



#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


class THREAD;


class DIOANDROIDSTREAMUDP : public DIOSTREAMUDP , public XFSMACHINE
{
  public:
                              DIOANDROIDSTREAMUDP                   ();
    virtual                  ~DIOANDROIDSTREAMUDP                   ();

    bool                      Open                                  ();
    bool                      Disconnect                            ();
    bool                      Close                                 ();

  protected:

    int                       IsReadyConnect                        (int sock);

  private:
   
    static void               ThreadRunFunction                     (void* thread);

    void                      Clean                                 ();

    XTHREAD*                  threadconnection;
    int                       handle;
    XSTRING                   remoteaddress;
};


#pragma endregion


#endif

