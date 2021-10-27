

//------------------------------------------------------------------------------------------
//  XANDROIDRAND.H
//
/**
// \class
//
//  Windows 32 Random Functions
//
//  @author  Abraham J. Velez
//  @version 22/04/2002
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _XANDROIDRAND_H_
#define _XANDROIDRAND_H_


//---- INCLUDES ----------------------------------------------------------------------------

#include "XLINUXRand.h"

//---- DEFINES & ENUMS  --------------------------------------------------------------------

//---- CLASS -------------------------------------------------------------------------------

class XANDROIDRAND : public XLINUXRAND
{
  public:
                  XANDROIDRAND        ();
    virtual      ~XANDROIDRAND        ();
};

//---- INLINE FUNCTIONS --------------------------------------------------------------------


#endif

