/*------------------------------------------------------------------------------------------
//  GRPWINDOWSCONTEXT.H
*/
/**
// \file
//
//  windows graphics context
//
//  @author  Imanol Celaya Ruiz de Alegria
//
//  Date Of Creation  : 04/04/2016 17:12:25
//  Last Modification :
*/
/*  GEN  Copyright (C).  All right reserved.
//----------------------------------------------------------------------------------------*/

#ifndef _GRPWINDOWSCONTEXT_H_
#define _GRPWINDOWSCONTEXT_H_


/*---- INCLUDES --------------------------------------------------------------------------*/

#include "windows.h"

#ifdef GRP_OPENGL_ACTIVE
#include "GRPOpenGL.h"
#endif

#include "GRPContext.h"

/*---- DEFINES & ENUMS  ------------------------------------------------------------------*/


/*---- CLASS -----------------------------------------------------------------------------*/

class GRPWINDOWSCONTEXT : public GRPCONTEXT
{
public:

                                    GRPWINDOWSCONTEXT                         ();
  virtual                          ~GRPWINDOWSCONTEXT                         ();

  virtual bool                      Create                                    (void* handle = NULL);
  virtual bool                      IsLost                                    ();
  virtual bool                      Destroy                                   ();

protected:

  #ifdef GRP_OPENGL_ACTIVE
  HGLRC                             hdlopenglrc;
  GRPOPENGLCTRL                     openglctrl;
  #endif

private:

  void                              Clean                                     ();
};


/*---- INLINE FUNCTIONS ------------------------------------------------------------------*/

#endif

