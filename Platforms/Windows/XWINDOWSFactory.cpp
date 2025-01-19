/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XWINDOWSFactory.cpp
* 
* @class      XWINDOWSFACTORY
* @brief      WINDOWS eXtended Utils factory class 
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

#include "XWINDOWSFactory.h"

#include "XFactoryMacros.h"

#include "XWINDOWSTimer.h"
#include "XWINDOWSDateTime.h"
#include "XWINDOWSRand.h"

#ifdef BUILDER
#include "XWINDOWSFileBorland.h"
#else
#include "XWINDOWSFile.h"
#endif

#include "XWINDOWSDir.h"
#include "XWINDOWSSystem.h"
#ifdef XCONSOLE_ACTIVE
#include "XWINDOWSConsole.h"
#endif
#include "XWINDOWSThread.h"

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


CREATEFUNC(XWINDOWSFACTORY, XTIMER    , XWINDOWSTIMER             , CreateTimer)
DELETEFUNC(XWINDOWSFACTORY, XTIMER    , XWINDOWSTIMER             , DeleteTimer)


CREATEFUNC(XWINDOWSFACTORY, XDATETIME , XWINDOWSDATETIME          , CreateDateTime)
DELETEFUNC(XWINDOWSFACTORY, XDATETIME , XWINDOWSDATETIME          , DeleteDateTime)


CREATEFUNC(XWINDOWSFACTORY, XRAND     , XWINDOWSRAND              , CreateRand)
DELETEFUNC(XWINDOWSFACTORY, XRAND     , XWINDOWSRAND              , DeleteRand)

#ifdef BUILDER
CREATEFUNC(XWINDOWSFACTORY, XFILE     , XWINDOWSFILEBORLAND       , Create_File)
DELETEFUNC(XWINDOWSFACTORY, XFILE     , XWINDOWSFILEBORLAND       , Delete_File)
#else
CREATEFUNC(XWINDOWSFACTORY, XFILE     , XWINDOWSFILE              , Create_File)
DELETEFUNC(XWINDOWSFACTORY, XFILE     , XWINDOWSFILE              , Delete_File)
#endif


CREATEFUNC(XWINDOWSFACTORY, XDIR      , XWINDOWSDIR               , Create_Dir)
DELETEFUNC(XWINDOWSFACTORY, XDIR      , XWINDOWSDIR               , Delete_Dir)


#ifdef XCONSOLE_ACTIVE
CREATEFUNC(XWINDOWSFACTORY, XCONSOLE  , XWINDOWSCONSOLE           , CreateConsole)
DELETEFUNC(XWINDOWSFACTORY, XCONSOLE  , XWINDOWSCONSOLE           , DeleteConsole)
#endif


CREATEFUNC(XWINDOWSFACTORY, XMUTEX    , XWINDOWSMUTEX             , Create_Mutex)
DELETEFUNC(XWINDOWSFACTORY, XMUTEX    , XWINDOWSMUTEX             , Delete_Mutex)


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREAD* XWINDOWSFACTORY::CreateThread(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
* @brief      Create thread
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  groupID : group ID of threads
* @param[in]  ID : ID for thread
* @param[in]  function : callback to thread
* @param[in]  param : param to callback
*
* @return     XTHREAD* : thread created
*
* --------------------------------------------------------------------------------------------------------------------*/
XTHREAD* XWINDOWSFACTORY::CreateThread(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
{
  XWINDOWSTHREAD* _class =  new XWINDOWSTHREAD(groupID, ID, function, param);
  return (XTHREAD*)_class;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XWINDOWSFACTORY::DeleteThread(XTHREADGROUPID groupID, XTHREAD* xthread)
* @brief      Delete thread
* @ingroup    PLATFORM_WINDOWS
*
* @param[in]  groupID : group ID of threads
* @param[in]  xthread : thread to delete.
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XWINDOWSFACTORY::DeleteThread(XTHREADGROUPID groupID, XTHREAD* xthread)
{
  if(xthread)
    {
      delete xthread;      
    }

  return true;
}


#pragma endregion


