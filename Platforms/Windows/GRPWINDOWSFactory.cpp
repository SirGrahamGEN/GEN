/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPWINDOWSFactory.cpp
*
* @class      GRPWINDOWSFACTORY
* @brief      Windows Graphics factory class
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

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactoryMacros.h"

#include "GRPWINDOWSScreen.h"
#ifdef GRP_OPENGL_ACTIVE
#include "GRPWINDOWSContext.h"
#endif

#include "GRPWINDOWSFactory.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


CREATEFUNC(GRPWINDOWSFACTORY, GRPSCREEN     , GRPWINDOWSSCREEN    , CreateScreen)
DELETEFUNC(GRPWINDOWSFACTORY, GRPSCREEN     , GRPWINDOWSSCREEN    , DeleteScreen)

#ifdef GRP_OPENGL_ACTIVE
CREATEFUNC(GRPWINDOWSFACTORY, GRPCONTEXT    , GRPWINDOWSCONTEXT   , CreateContext)
DELETEFUNC(GRPWINDOWSFACTORY, GRPCONTEXT    , GRPWINDOWSCONTEXT   , DeleteContext)
#endif




