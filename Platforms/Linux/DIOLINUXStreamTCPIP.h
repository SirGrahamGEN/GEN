//------------------------------------------------------------------------------------------
//  DIOLINUXSTREAMTCPIP.H
//
/**
// \class
//
//  LINUX Data Input/Output Stream TCP/IP class
//
//  ""
//  @version 02/01/2002
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _DIOLINUXSTREAMTCPIP_H_
#define _DIOLINUXSTREAMTCPIP_H_


//---- INCLUDES ----------------------------------------------------------------------------



#include "XFSMachine.h"
#include "XThreadCollected.h"

#include "DIOStreamTCPIP.h"

//---- DEFINES & ENUMS  --------------------------------------------------------------------


enum DIOLINUXTCPIPFSMEVENTS
{
  DIOLINUXTCPIPFSMEVENT_NONE                = 0 ,

  DIOLINUXTCPIPFSMEVENT_GETTINGCONNECTION        ,
  DIOLINUXTCPIPFSMEVENT_CONNECTED               ,
  DIOLINUXTCPIPFSMEVENT_WAITINGTOREAD           ,
  DIOLINUXTCPIPFSMEVENT_SENDINGDATA             ,
  DIOLINUXTCPIPFSMEVENT_DISCONNECTING           ,

  DIOLINUXTCPIP_LASTEVENT
};


enum DIOLINUXTCPIPFSMSTATES
{
  DIOLINUXTCPIPFSMSTATE_NONE                = 0 ,

  DIOLINUXTCPIPFSMSTATE_GETTINGCONNECTION        ,
  DIOLINUXTCPIPFSMSTATE_CONNECTED               ,
  DIOLINUXTCPIPFSMSTATE_WAITINGTOREAD           ,
  DIOLINUXTCPIPFSMSTATE_SENDINGDATA             ,
  DIOLINUXTCPIPFSMSTATE_DISCONNECTING           ,

  DIOLINUXTCPIP_LASTSTATE
};


//---- CLASS -------------------------------------------------------------------------------

class XFACTORY;
class XPUBLISHER;
class DIOFACTORY;


class DIOLINUXSTREAMTCPIP : public DIOSTREAMTCPIP , public XFSMACHINE
{
  public:
                              DIOLINUXSTREAMTCPIP                     ();
    virtual                  ~DIOLINUXSTREAMTCPIP                     ();

    bool                      Open                                    ();
    bool                      Disconnect                              ();
    bool                      Close                                   ();

  protected:

    int                       Accept                                  (int socket, void* addr, void* addrlen, XDWORD usec);
    int                       IsReadyConnect                          (int socket);

  private:

    void                      Clean                                   ()
                              {
                                threadconnection   = NULL;
                                handlesocket      = -1;
                              }

    bool                      GetHandleServer                         ();
    bool                      GetHandleClient                         ();


    static void               ThreadConnection                         (void* data);

    XTHREADCOLLECTED*         threadconnection;

    int                       handlesocket;
};



//---- INLINE FUNCTIONS --------------------------------------------------------------------

#endif

