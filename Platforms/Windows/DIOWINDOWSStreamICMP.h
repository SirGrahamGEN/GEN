/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DIOWINDOWSStreamICMP.h
* 
* @class      DIOWINDOWSSTREAMICMP
* @brief      WINDOWS Data Input/Output Stream ICMP class
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

#ifndef _DIOWINDOWSSTREAMICMP_H_
#define _DIOWINDOWSSTREAMICMP_H_


#if defined(DIO_ACTIVE) && defined(DIO_STREAMICMP_ACTIVE)

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES


#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#include "XFSMachine.h"
#include "XThreadCollected.h"

#include "DIOStreamICMP.h"


#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS

enum DIOWINDOWSICMPFSMEVENTS
{
  DIOWINDOWSICMPFSMEVENT_NONE                 = 0 ,

  DIOWINDOWSICMPFSMEVENT_GETTINGCONNECTION         ,
  DIOWINDOWSICMPFSMEVENT_CONNECTED                ,
  DIOWINDOWSICMPFSMEVENT_WAITINGTOREAD            ,
  DIOWINDOWSICMPFSMEVENT_SENDINGDATA              ,
  DIOWINDOWSICMPFSMEVENT_DISCONNECTING            ,

  DIOWINDOWSICMP_LASTEVENT
};


enum DIOWINDOWSICMPFSMSTATES
{
  DIOWINDOWSICMPFSMSTATE_NONE                 = 0 ,

  DIOWINDOWSICMPFSMSTATE_GETTINGCONNECTION         ,
  DIOWINDOWSICMPFSMSTATE_CONNECTED                ,
  DIOWINDOWSICMPFSMSTATE_WAITINGTOREAD            ,
  DIOWINDOWSICMPFSMSTATE_SENDINGDATA              ,
  DIOWINDOWSICMPFSMSTATE_DISCONNECTING            ,

  DIOWINDOWSICMP_LASTSTATE
};

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS


class DIOWINDOWSSTREAMICMP : public DIOSTREAMICMP , public XFSMACHINE
{
  public:
                              DIOWINDOWSSTREAMICMP                    ();
    virtual                  ~DIOWINDOWSSTREAMICMP                    ();

    bool                      Open                                    ();
    bool                      Disconnect                              ();
    bool                      Close                                   ();

  protected:

    int                       IsReadyConnect                          (SOCKET socket);

  private:

    void                      Clean                                   ();
    static void               ThreadConnection                        (void* data);

    XTHREADCOLLECTED*         threadconnection;
    SOCKET                    handle;    
};


#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif


#endif

