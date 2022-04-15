//------------------------------------------------------------------------------------------
//  DIOSTREAMXEVENT.H
//
/**
// \class
//
//  Data IO Stream Event class
//
//  ""
//  @version 23/05/2002
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _DIOSTREAMXEVENT_H_
#define _DIOSTREAMXEVENT_H_


//---- INCLUDES ----------------------------------------------------------------------------

#include "XEvent.h"

#include "DIOStreamDevice.h"

//---- DEFINES & ENUMS  --------------------------------------------------------------------


enum DIOSTREAMXEVENT_TYPE
{
  DIOSTREAMXEVENT_TYPE_UNKNOWN             = XEVENT_TYPE_DIOSTREAM  ,
  DIOSTREAMXEVENT_TYPE_GETTINGCONNECTION                            ,
  DIOSTREAMXEVENT_TYPE_CONNECTED                                   ,
  DIOSTREAMXEVENT_TYPE_DISCONNECTED                                ,
  DIOSTREAMXEVENT_TYPE_EXCEPTIONDEVICE                             ,
  DIOSTREAMXEVENT_TYPE_COOPERATIONDEVICE                           ,
};


//---- CLASS -------------------------------------------------------------------------------


class DIOSTREAM;


class DIOSTREAMXEVENT : public XEVENT
{
  public:
                                DIOSTREAMXEVENT                 (XSUBJECT* subject, XDWORD type = DIOSTREAMXEVENT_TYPE_UNKNOWN, XDWORD family = XEVENT_TYPE_DIOSTREAM) : XEVENT(subject, type, family)
                                {
                                  Clean();
                                }

    virtual                    ~DIOSTREAMXEVENT                 ()                                                                                          { Clean();                          }

    DIOSTREAM*                  GetDIOStream                    ()                                                                                          { return diostream;                 }
    void                        SetDIOStream                    (DIOSTREAM* diostream)                                                                      { this->diostream = diostream;      }

    DIOSTREAMDEVICE*            GetDevice                       ()                                                                                          { return &device;                   }
    void                        SetDevice                       (DIOSTREAMDEVICE& device)                                                                   {                                   }

  private:

    void                        Clean                           ()
                                {
                                  diostream = NULL;
                                }

    DIOSTREAM*                  diostream;
    DIOSTREAMDEVICE             device;
};



//---- INLINE FUNCTIONS --------------------------------------------------------------------


#endif
