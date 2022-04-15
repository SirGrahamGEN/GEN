/*------------------------------------------------------------------------------------------
// DIOWINDOWSSTREAMI2C.H
*/
/**
// \class
//
//  WINDOWS Data IO Stream I2C class
//
//  ""
//  @version 20/09/2012 14:31:53
*/
/*  GEN  Copyright (C).  All right reserved.
//----------------------------------------------------------------------------------------*/

#ifndef _DIOWINDOWSSTREAMI2C_H_
#define _DIOWINDOWSSTREAMI2C_H_


/*---- INCLUDES --------------------------------------------------------------------------*/

#include "XFSMachine.h"

#include "DIOStreamI2C.h"

/*---- DEFINES & ENUMS  ------------------------------------------------------------------*/



/*---- CLASS -----------------------------------------------------------------------------*/

class XFACTORY;
class DIOFACTORY;
class XPUBLISHER;

class DIOWINDOWSSTREAMI2C : public DIOSTREAMI2C
{
  public:
                                  DIOWINDOWSSTREAMI2C                       ();
    virtual                      ~DIOWINDOWSSTREAMI2C                       ();

    bool                          Open                                      ();
    bool                          Close                                     ();

  private:

    void                          Clean                                     ();

    static void                   ThreadConnection                           (void* data);
};


//---- INLINE FUNCTIONS --------------------------------------------------------------------

#endif

