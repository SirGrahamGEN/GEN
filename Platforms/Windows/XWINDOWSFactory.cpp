/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XWINDOWSFactory.cpp
*
* @class      XWINDOWSFACTORY
* @brief      eXtended WINDOWS platform Factory
* @ingroup    PLATFORM_WINDOWS
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

#include "XWINDOWSTimer.h"
#include "XWINDOWSDateTime.h"
#include "XWINDOWSRand.h"
#include "XWINDOWSFile.h"
#include "XWINDOWSDir.h"
#include "XWINDOWSSystem.h"
#include "XWINDOWSConsole.h"
#include "XWINDOWSThread.h"

#include "XWINDOWSFactory.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


CREATEFUNC(XWINDOWSFACTORY, XTIMER    , XWINDOWSTIMER     , CreateTimer)
DELETEFUNC(XWINDOWSFACTORY, XTIMER    , XWINDOWSTIMER     , DeleteTimer)

CREATEFUNC(XWINDOWSFACTORY, XDATETIME , XWINDOWSDATETIME  , CreateDateTime)
DELETEFUNC(XWINDOWSFACTORY, XDATETIME , XWINDOWSDATETIME  , DeleteDateTime)

CREATEFUNC(XWINDOWSFACTORY, XRAND     , XWINDOWSRAND      , CreateRand)
DELETEFUNC(XWINDOWSFACTORY, XRAND     , XWINDOWSRAND      , DeleteRand)

CREATEFUNC(XWINDOWSFACTORY, XFILE     , XWINDOWSFILE      , Create_File)
DELETEFUNC(XWINDOWSFACTORY, XFILE     , XWINDOWSFILE      , Delete_File)

CREATEFUNC(XWINDOWSFACTORY, XDIR      , XWINDOWSDIR       , Create_Dir)
DELETEFUNC(XWINDOWSFACTORY, XDIR      , XWINDOWSDIR       , Delete_Dir)

CREATEFUNC(XWINDOWSFACTORY, XCONSOLE  , XWINDOWSCONSOLE   , CreateConsole)
DELETEFUNC(XWINDOWSFACTORY, XCONSOLE  , XWINDOWSCONSOLE   , DeleteConsole)

CREATEFUNC(XWINDOWSFACTORY, XMUTEX    , XWINDOWSMUTEX     , Create_Mutex)
DELETEFUNC(XWINDOWSFACTORY, XMUTEX    , XWINDOWSMUTEX     , Delete_Mutex)



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREAD* XWINDOWSFACTORY::CreateThread(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
* @brief      CreateThread
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID : group ID of threads
* @param[in]  ID : ID for thread
* @param[in]  function : callback to thread
* @param[in]  param : param to callback
*
* @return     XTHREAD* : thread created
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREAD* XWINDOWSFACTORY::CreateThread(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
{
  XWINDOWSTHREAD* _class =  new XWINDOWSTHREAD(groupID, ID, function, param);
  return (XTHREAD*)_class;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSFACTORY::DeleteThread(XTHREADGROUPID groupID, XTHREAD* xthread)
* @brief      DeleteThread
* @ingroup    PLATFORM_WINDOWS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID : group ID of threads
* @param[in]  xthread : thread to delete.
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFACTORY::DeleteThread(XTHREADGROUPID groupID, XTHREAD* xthread)
{
  if(xthread)
    {
      delete xthread;
      //xthread = NULL;
    }

  return true;
};

