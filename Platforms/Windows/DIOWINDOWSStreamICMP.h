//------------------------------------------------------------------------------------------
//  DIOWINDOWSSTREAMICMP.H
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

#ifndef _DIOWINDOWSSTREAMICMP_H_
#define _DIOWINDOWSSTREAMICMP_H_

#if defined(DIO_ACTIVE) && defined(DIO_STREAMICMP_ACTIVE)

//---- INCLUDES ----------------------------------------------------------------------------

#include "XFSMachine.h"
#include "DIOStreamICMP.h"

//---- DEFINES & ENUMS  --------------------------------------------------------------------

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


//---- CLASS -------------------------------------------------------------------------------

class XFACTORY;
class DIOFACTORY;
class XPUBLISHER;
class XTHREADCOLLECTED;


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
    XSTRING                   remoteaddress;

};


//---- INLINE FUNCTIONS --------------------------------------------------------------------

#endif

#endif