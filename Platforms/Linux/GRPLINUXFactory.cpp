/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       GRPLINUXFactory.cpp
* 
* @class      GRPLINUXFACTORY
* @brief      LINUX Graphics factory class
* @ingroup    PLATFORM_LINUX
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

#include "GRPLINUXFactory.h"

#include "XFactoryMacros.h"
#include "XString.h"
#include "XTrace.h"

#ifdef LINUX_X11_ACTIVE
#include "GRPLINUXScreenX11.h"
#else
#include "GRPLINUXScreenFrameBuffer.h"
#endif

#ifdef GRP_OPENGL_ACTIVE
#include "GRP3DContext.h"
#endif

#ifdef GRP_DESKTOPMANAGER_ACTIVE
#include "GRPLINUXDesktopManager.h"
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


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPSCREEN* GRPLINUXFACTORY::CreateScreen()
* @brief      Create screen
* @ingroup    PLATFORM_LINUX
*
* @return     GRPSCREEN* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPSCREEN* GRPLINUXFACTORY::CreateScreen()
{
  GRPSCREEN* screen = NULL;

  #ifdef LINUX_X11_ACTIVE
  screen =  (GRPSCREEN*)new GRPLINUXSCREENX11;
  #else
  screen =  (GRPSCREEN*)new GRPLINUXSCREENFRAMEBUFFER;
  #endif

  return screen;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXFACTORY::DeleteScreen(GRPSCREEN* screen)
* @brief      Delete screen
* @ingroup    PLATFORM_LINUX
*
* @param[in]  screen :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXFACTORY::DeleteScreen(GRPSCREEN* screen)
{
  if(!screen) return false;

  delete screen;

  return true;
}


#ifdef GRP_OPENGL_ACTIVE


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPCONTEXT* GRPLINUXFACTORY::CreateContext()
* @brief      Create context
* @ingroup    PLATFORM_LINUX
*
* @return     GRPCONTEXT* :
*
* --------------------------------------------------------------------------------------------------------------------*/
GRPCONTEXT* GRPLINUXFACTORY::CreateContext()
{
  GRPCONTEXT* context = NULL;

  return context;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXFACTORY::DeleteContext(GRPCONTEXT* context)
* @brief      Delete context
* @ingroup    PLATFORM_LINUX
*
* @param[in]  context :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXFACTORY::DeleteContext(GRPCONTEXT* context)
{
  if(!context) return false;

  delete context;

  return true;
}

#endif


#ifdef GRP_DESKTOPMANAGER_ACTIVE
CREATEFUNC(GRPLINUXFACTORY, GRPDESKTOPMANAGER     , GRPLINUXDESKTOPMANAGER    , CreateDesktopManager)
DELETEFUNC(GRPLINUXFACTORY, GRPDESKTOPMANAGER     , GRPLINUXDESKTOPMANAGER    , DeleteDesktopManager)
#endif


#pragma endregion
