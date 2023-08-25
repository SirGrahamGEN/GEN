//------------------------------------------------------------------------------------------
//  DIOWINDOWSSTREAMUSB.H
//
/**
// \class
//
//  WINDOWS Data IO Stream USB class
//
//  ""
//  @version 02/01/2002
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _DIOWINDOWSSTREAMUSB_H_
#define _DIOWINDOWSSTREAMUSB_H_

#if defined(DIO_ACTIVE) && defined(DIO_USB_ACTIVE)

//---- INCLUDES ----------------------------------------------------------------------------

#include <windows.h>

#include "XFSMachine.h"
#include "DIOStreamUSB.h"
#include "DIOStreamUSBConfig.h"


//---- DEFINES & ENUMS  --------------------------------------------------------------------


enum DIOWINDOWSUSBFSMEVENTS
{
  DIOWINDOWSUSBFSMEVENT_NONE                = 0 ,
  DIOWINDOWSUSBFSMEVENT_CONNECTED             ,
  DIOWINDOWSUSBFSMEVENT_WAITINGTOREAD         ,
  DIOWINDOWSUSBFSMEVENT_SENDINGDATA           ,
  DIOWINDOWSUSBFSMEVENT_DISCONNECTING         ,

  DIOWINDOWSUSB_LASTEVENT
};


enum DIOWINDOWSUSBFSMSTATES
{
  DIOWINDOWSUSBFSMSTATE_NONE                = 0 ,
  DIOWINDOWSUSBFSMSTATE_CONNECTED             ,
  DIOWINDOWSUSBFSMSTATE_WAITINGTOREAD         ,
  DIOWINDOWSUSBFSMSTATE_SENDINGDATA           ,
  DIOWINDOWSUSBFSMSTATE_DISCONNECTING         ,

  DIOWINDOWSUSB_LASTSTATE
};



//---- CLASS -------------------------------------------------------------------------------

class XTHREADCOLLECTED;

class DIOWINDOWSSTREAMUSB : public DIOSTREAMUSB , public XFSMACHINE
{
  public:
                          DIOWINDOWSSTREAMUSB                           ();
    virtual              ~DIOWINDOWSSTREAMUSB                           ();

    DIOSTREAMSTATUS       GetConnectStatus                              ();

    bool                  Open                                          ();

    bool                  Close                                         ();

    bool                  CleanBuffers                                  ();

  protected:



    static void           ThreadConnection                               (void* data);

    XDWORD                ReadBuffer                                    (XBYTE* buffer,XDWORD size);
    XDWORD                WriteBuffer                                   (XBYTE* buffer,XDWORD size);

    void                  Clean                                         ();

    XTHREADCOLLECTED*     threadconnection;

    HANDLE                handle;
    XDWORD                mask;
    HANDLE                hevent;
    OVERLAPPED            ovi;

    int                   readtimeout;
    int                   writetimeout;
};


//---- INLINE FUNCTIONS --------------------------------------------------------------------

#endif

#endif




