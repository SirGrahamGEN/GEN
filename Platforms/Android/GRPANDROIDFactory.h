//------------------------------------------------------------------------------------------
//  GRPANDROIDFACTORY.H
//
/**
// \class
//
//  Android Graphics Factory
//
//  ""
//  @version 15/07/2002
*/
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------

#ifndef _GRPANDROIDFACTORY_H_
#define _GRPANDROIDFACTORY_H_


//---- INCLUDES ----------------------------------------------------------------------------

#include "GRPProperties.h"
#include "GRPFactory.h"

//---- DEFINES & ENUMS  --------------------------------------------------------------------

//---- CLASS -------------------------------------------------------------------------------


class GRPSCREEN;
class GRPCONTEXT;


class GRPANDROIDFACTORY : public GRPFACTORY
{
  public:

    GRPSCREEN*              CreateScreen            ();
    bool                    DeleteScreen            (GRPSCREEN* screen);

    #ifdef GRP_OPENGL_ACTIVE
    GRPCONTEXT*             CreateContext           ();
    bool                    DeleteContext           (GRPCONTEXT* context);
    #endif

};

//---- INLINE FUNCTIONS --------------------------------------------------------------------

#endif

