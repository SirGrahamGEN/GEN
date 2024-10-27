/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWINDOWSStreamTCPIP.h
* 
* @class      DIOWINDOWSSTREAMTCPIP
* @brief      WINDOWS Data Input/Output Stream TCP/IP class
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

#ifndef _DIOWINDOWSSTREAMTCPIP_H_
#define _DIOWINDOWSSTREAMTCPIP_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include <windows.h>

#include "XFSMachine.h"
#include "XThreadCollected.h"

#include "DIOStreamTCPIP.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum DIOWINDOWSTCPIPFSMEVENTS
{
  DIOWINDOWSTCPIPFSMEVENT_NONE                = 0 ,

  DIOWINDOWSTCPIPFSMEVENT_GETTINGCONNECTION        ,
  DIOWINDOWSTCPIPFSMEVENT_CONNECTED             ,
  DIOWINDOWSTCPIPFSMEVENT_WAITINGTOREAD         ,
  DIOWINDOWSTCPIPFSMEVENT_SENDINGDATA           ,
  DIOWINDOWSTCPIPFSMEVENT_DISCONNECTING         ,

  DIOWINDOWSTCPIP_LASTEVENT
};


enum DIOWINDOWSTCPIPFSMSTATES
{
  DIOWINDOWSTCPIPFSMSTATE_NONE                = 0 ,

  DIOWINDOWSTCPIPFSMSTATE_GETTINGCONNECTION        ,
  DIOWINDOWSTCPIPFSMSTATE_CONNECTED             ,
  DIOWINDOWSTCPIPFSMSTATE_WAITINGTOREAD         ,
  DIOWINDOWSTCPIPFSMSTATE_SENDINGDATA           ,
  DIOWINDOWSTCPIPFSMSTATE_DISCONNECTING         ,

  DIOWINDOWSTCPIP_LASTSTATE
};


#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOWINDOWSSTREAMTCPIP : public DIOSTREAMTCPIP , public XFSMACHINE
{
  public:
                              DIOWINDOWSSTREAMTCPIP                   ();
    virtual                  ~DIOWINDOWSSTREAMTCPIP                   ();

    bool                      Open                                    ();
    bool                      Disconnect                              ();
    bool                      Close                                   ();

    SOCKET                    GetHandleSocket                         (); 
    void                      SetHandleSocket                         (SOCKET handlesocket); 

  protected:

    SOCKET                    Accept                                  (SOCKET handlesocket, void* addr, void* addrlen, XDWORD usec);
    int                       IsReadyConnect                          (SOCKET handlesocket);

  private:
    
    bool                      GetHandleServer                         ();
    bool                      GetHandleClient                         ();

    static void               ThreadConnection                        (void* data);

    void                      Clean                                   ();

    XTHREADCOLLECTED*         threadconnection;
    SOCKET                    handlesocket;    
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif

