/**-------------------------------------------------------------------------------------------------------------------
*
* @file       GRPLINUXFactory.cpp
*
* @class      GRPLINUXFACTORY
* @brief      Linux Graphics factory class
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @copyright  Copyright(c) 2008 - 2016 GEN Group.
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
*---------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XFactoryMacros.h"
#include "XString.h"
#include "XTrace.h"

#ifdef LINUX_X11_ACTIVE
#include "GRPLINUXScreenX11.h"
#else
#include "GRPLINUXScreenFrameBuffer.h"
#endif

#ifdef GRP_OPENGL_ACTIVE
#include "GRPContext.h"
#endif

#include "GRPLINUXFactory.h"

#include "XMemory_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         GRPSCREEN* GRPLINUXFACTORY::CreateScreen()
* @brief      CreateScreen
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     GRPSCREEN* :
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @brief      DeleteScreen
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  screen :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
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
* @brief      CreateContext
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     GRPCONTEXT* :
*
*---------------------------------------------------------------------------------------------------------------------*/
GRPCONTEXT* GRPLINUXFACTORY::CreateContext()
{
  GRPCONTEXT* context = NULL;

  return context;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool GRPLINUXFACTORY::DeleteContext(GRPCONTEXT* context)
* @brief      Delete Context
* @ingroup    PLATFORM_LINUX
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  context :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool GRPLINUXFACTORY::DeleteContext(GRPCONTEXT* context)
{
  if(!context) return false;

  delete context;

  return true;
}


#endif

