//------------------------------------------------------------------------------------------
//  GRPANDROIDFACTORY.CPP
//
//  ANDROID Graphics Factory Class
//
//  Author            : Abraham J. Velez
//  Date Of Creation  : 08/08/2002
//  Last Mofificacion :
//
//  GEN  Copyright (C).  All right reserved.
//------------------------------------------------------------------------------------------


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


//---- INCLUDES ----------------------------------------------------------------------------

#include <stdio.h>

#include "XFactoryMacros.h"
#include "XTrace.h"

#include "GRPANDROIDScreen.h"
#ifdef GRP_OPENGL_ACTIVE
#include "GRPANDROIDContext.h"
#endif

#include "GRPANDROIDFactory.h"

#include "XMemory_Control.h"

//---- GENERAL VARIABLE --------------------------------------------------------------------


//---- CLASS MEMBERS -----------------------------------------------------------------------


CREATEFUNC(GRPANDROIDFACTORY, GRPSCREEN     , GRPANDROIDSCREEN    , CreateScreen)
DELETEFUNC(GRPANDROIDFACTORY, GRPSCREEN     , GRPANDROIDSCREEN    , DeleteScreen)


#ifdef GRP_OPENGL_ACTIVE
CREATEFUNC(GRPANDROIDFACTORY, GRPCONTEXT    , GRPANDROIDCONTEXT   , CreateContext)
DELETEFUNC(GRPANDROIDFACTORY, GRPCONTEXT    , GRPANDROIDCONTEXT   , DeleteContext)
#endif


