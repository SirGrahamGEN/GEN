/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPWINDOWSFactory.cpp
* 
* @class      GRPWINDOWSFACTORY
* @brief      WINDOWS Graphics factory class
* @ingroup    PLATFORM_WINDOWS
* 
* @copyright  GEN Group. All rights reserved.
* 
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
* 
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "GRPWINDOWSFactory.h"

#include "XFactoryMacros.h"

#include "GRPWINDOWSScreen.h"
#ifdef GRP_OPENGL_ACTIVE
#include "GRPWINDOWSContext.h"
#endif
#ifdef GRP_DESKTOPMANAGER_ACTIVE
#include "GRPWINDOWSDesktopManager.h"
#endif

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


CREATEFUNC(GRPWINDOWSFACTORY, GRPSCREEN             , GRPWINDOWSSCREEN            , CreateScreen)
DELETEFUNC(GRPWINDOWSFACTORY, GRPSCREEN             , GRPWINDOWSSCREEN            , DeleteScreen)


#ifdef GRP_OPENGL_ACTIVE
CREATEFUNC(GRPWINDOWSFACTORY, GRPCONTEXT            , GRPWINDOWSCONTEXT           , CreateContext)
DELETEFUNC(GRPWINDOWSFACTORY, GRPCONTEXT            , GRPWINDOWSCONTEXT           , DeleteContext)
#endif


#ifdef GRP_DESKTOPMANAGER_ACTIVE
CREATEFUNC(GRPWINDOWSFACTORY, GRPDESKTOPMANAGER     , GRPWINDOWSDESKTOPMANAGER    , CreateDesktopManager)
DELETEFUNC(GRPWINDOWSFACTORY, GRPDESKTOPMANAGER     , GRPWINDOWSDESKTOPMANAGER    , DeleteDesktopManager)
#endif


#pragma endregion

