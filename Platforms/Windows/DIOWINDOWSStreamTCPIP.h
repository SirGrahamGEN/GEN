//------------------------------------------------------------------------------------------
//  DIOWINDOWSSTREAMTCPIP.H
//
/**
// \class
//
//  WINDOWS Data Input/Output Stream TCP/IP class
//
//  ""
//  @version 02/01/2002
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _DIOWINDOWSSTREAMTCPIP_H_
#define _DIOWINDOWSSTREAMTCPIP_H_


//---- INCLUDES ----------------------------------------------------------------------------


#include <windows.h>

#include "XFSMachine.h"
#include "XThreadCollected.h"

#include "DIOStreamTCPIP.h"

//---- DEFINES & ENUMS  --------------------------------------------------------------------


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


//---- CLASS -------------------------------------------------------------------------------

class XFACTORY;
class XPUBLISHER;
class DIOFACTORY;


class DIOWINDOWSSTREAMTCPIP : public DIOSTREAMTCPIP , public XFSMACHINE
{
  public:
                              DIOWINDOWSSTREAMTCPIP                   ();
    virtual                  ~DIOWINDOWSSTREAMTCPIP                   ();

    bool                      Open                                    ();
    bool                      Disconnect                              ();
    bool                      Close                                   ();

  protected:

    SOCKET                    Accept                                  (SOCKET socket, void* addr, void* addrlen, XDWORD usec);
    int                       IsReadyConnect                          (SOCKET socket);

  private:

    void                      Clean                                   ()
                              {
                                threadconnection   = NULL;
                                handlesocket      = INVALID_SOCKET;
                              }

    bool                      GetHandleServer                         ();
    bool                      GetHandleClient                         ();


    static void               ThreadConnection                         (void* data);

    XTHREADCOLLECTED*         threadconnection;
    SOCKET                    handlesocket;
};



//---- INLINE FUNCTIONS --------------------------------------------------------------------

#endif

