/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWINDOWSStreamTCPIPServer.h
* 
* @class      DIOWINDOWSSTREAMTCPIPSERVER
* @brief      WINDOWS Data Input/Output Stream TCP/IP Server class
* @ingroup    PLATFORM_WINDOWS
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

#ifndef _DIOWINDOWSSTREAMTCPIPSERVER_H_
#define _DIOWINDOWSSTREAMTCPIPSERVER_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <windows.h>

#include "XFSMachine.h"
#include "XThreadCollected.h"

#include "DIOStreamTCPIPServer.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum DIOWINDOWSTCPIPSERVERFSMEVENTS
{
  DIOWINDOWSTCPIPSERVERFSMEVENT_NONE                = 0 ,

  DIOWINDOWSTCPIPSERVERFSMEVENT_GETTINGCONNECTION       ,
  DIOWINDOWSTCPIPSERVERFSMEVENT_CONNECTED               ,
  DIOWINDOWSTCPIPSERVERFSMEVENT_WAITINGTOREAD           ,
  DIOWINDOWSTCPIPSERVERFSMEVENT_SENDINGDATA             ,
  DIOWINDOWSTCPIPSERVERFSMEVENT_DISCONNECTING           ,

  DIOWINDOWSTCPIPSERVER_LASTEVENT
};


enum DIOWINDOWSTCPIPSERVERFSMSTATES
{
  DIOWINDOWSTCPIPSERVERFSMSTATE_NONE                = 0 ,

  DIOWINDOWSTCPIPSERVERFSMSTATE_GETTINGCONNECTION       ,
  DIOWINDOWSTCPIPSERVERFSMSTATE_CONNECTED               ,
  DIOWINDOWSTCPIPSERVERFSMSTATE_WAITINGTOREAD           ,
  DIOWINDOWSTCPIPSERVERFSMSTATE_SENDINGDATA             ,
  DIOWINDOWSTCPIPSERVERFSMSTATE_DISCONNECTING           ,

  DIOWINDOWSTCPIPSERVER_LASTSTATE
};


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOWINDOWSSTREAMTCPIPSERVER: public DIOSTREAMTCPIPSERVER, public XFSMACHINE
{
  public:
                                        DIOWINDOWSSTREAMTCPIPSERVER             ();
    virtual                            ~DIOWINDOWSSTREAMTCPIPSERVER             ();

    bool                                Open                                    ();
    bool                                Disconnect                              ();
    bool                                Close                                   ();

  protected:

    SOCKET                              Accept                                  (SOCKET socket, void* addr, void* addrlen, XDWORD usec);
    int                                 IsReadyConnect                          (SOCKET socket);

  private:

    DIOSTREAM*                          CreateStream                            ();    
    bool                                DeleteAllStreamDisconnected             ();
    bool                                DeleteAllStream                         ();

    bool                                GetHandleServer                         (DIOSTREAMTCPIP* diostream);
    
    static void                         ThreadConnection                        (void* data);

    void                                Clean                                   ();

    XTHREADCOLLECTED*                   threadconnection;
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

