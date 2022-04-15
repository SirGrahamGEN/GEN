//------------------------------------------------------------------------------------------
//  DIOWINDOWSSTREAMIPLOCALENUMDEVICES.H
//
/**
// \class
//
//  WINDOWS Data Input/Output Stream IP Local Enum Devices class
//
//  ""
//  @version 02/01/2002
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _DIOWINDOWSSTREAMIPLOCALENUMDEVICES_H_
#define _DIOWINDOWSSTREAMIPLOCALENUMDEVICES_H_


//---- INCLUDES ----------------------------------------------------------------------------

#include "DIOStreamIPLocalEnumDevices.h"

//---- DEFINES & ENUMS  --------------------------------------------------------------------

//---- CLASS -------------------------------------------------------------------------------


class DIOWINDOWSSTREAMIPLOCALENUMDEVICES :  public DIOSTREAMIPLOCALENUMDEVICES
{
  public:
                              DIOWINDOWSSTREAMIPLOCALENUMDEVICES      ();
    virtual                  ~DIOWINDOWSSTREAMIPLOCALENUMDEVICES      ();

    bool                      Search                                  ();
};




//---- INLINE FUNCTIONS --------------------------------------------------------------------

#endif

