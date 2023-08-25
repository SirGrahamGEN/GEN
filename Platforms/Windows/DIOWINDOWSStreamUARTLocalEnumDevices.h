//------------------------------------------------------------------------------------------
//  DIOWINDOWSSTREAMUARTLOCALENUMDEVICES.H
//
/**
// \class
//
//  WINDOWS Data Input/Output Stream UART Local Enum Devices class
//
//  ""
//  @version 02/01/2002
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _DIOWINDOWSSTREAMUARTLOCALENUMDEVICES_H_
#define _DIOWINDOWSSTREAMUARTLOCALENUMDEVICES_H_

#if defined(DIO_ACTIVE) && defined(DIO_UART_ACTIVE)

//---- INCLUDES ----------------------------------------------------------------------------

#include "XString.h"

#include "DIOStreamUARTLocalEnumDevices.h"

//---- DEFINES & ENUMS  --------------------------------------------------------------------

//---- CLASS -------------------------------------------------------------------------------


class DIOWINDOWSSTREAMUARTLOCALENUMDEVICES :  public DIOSTREAMUARTLOCALENUMDEVICES
{
  public:
                          DIOWINDOWSSTREAMUARTLOCALENUMDEVICES          ();
    virtual              ~DIOWINDOWSSTREAMUARTLOCALENUMDEVICES          ();

    bool                  Search                                        ();
};


//---- INLINE FUNCTIONS --------------------------------------------------------------------

#endif

#endif



