/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XLINUXFactory.cpp
* 
* @class      XLINUXFACTORY
* @brief      LINUX eXtended Utils factory class
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

#include "XLINUXFactory.h"

#include "XLINUXDateTime.h"
#include "XLINUXTimer.h"
#include "XLINUXRand.h"
#include "XLINUXFile.h"
#include "XLINUXDir.h"
#include "XLINUXConsole.h"
#include "XLINUXThread.h"

#include "XFactoryMacros.h"

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


CREATEFUNC(XLINUXFACTORY, XTIMER     , XLINUXTIMER      , CreateTimer)
DELETEFUNC(XLINUXFACTORY, XTIMER     , XLINUXTIMER      , DeleteTimer)

CREATEFUNC(XLINUXFACTORY, XDATETIME  , XLINUXDATETIME   , CreateDateTime)
DELETEFUNC(XLINUXFACTORY, XDATETIME  , XLINUXDATETIME   , DeleteDateTime)

CREATEFUNC(XLINUXFACTORY, XRAND      , XLINUXRAND       , CreateRand)
DELETEFUNC(XLINUXFACTORY, XRAND      , XLINUXRAND       , DeleteRand)

CREATEFUNC(XLINUXFACTORY, XFILE      , XLINUXFILE       , Create_File)
DELETEFUNC(XLINUXFACTORY, XFILE      , XLINUXFILE       , Delete_File)

CREATEFUNC(XLINUXFACTORY, XDIR       , XLINUXDIR        , Create_Dir)
DELETEFUNC(XLINUXFACTORY, XDIR       , XLINUXDIR        , Delete_Dir)

#ifdef XCONSOLE_ACTIVE
CREATEFUNC(XLINUXFACTORY, XCONSOLE   , XLINUXCONSOLE    , CreateConsole)
DELETEFUNC(XLINUXFACTORY, XCONSOLE   , XLINUXCONSOLE    , DeleteConsole)
#endif

CREATEFUNC(XLINUXFACTORY, XMUTEX     , XLINUXMUTEX      , Create_Mutex)
DELETEFUNC(XLINUXFACTORY, XMUTEX     , XLINUXMUTEX      , Delete_Mutex)


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREAD* XLINUXFACTORY::CreateThread(XTHREADGROUPID groupID, XCHAR* ID,XTHREADFUNCTION function,void* param)
* @brief      Create thread
* @ingroup    PLATFORM_LINUX
*
* @param[in]  groupID : group ID of threads
* @param[in]  ID : ID for thread
* @param[in]  function : callback to thread
* @param[in]  param : param to callback
*
* @return     XTHREAD* : thread created
*
* --------------------------------------------------------------------------------------------------------------------*/
XTHREAD* XLINUXFACTORY::CreateThread(XTHREADGROUPID groupID, XCHAR* ID,XTHREADFUNCTION function,void* param)
{
  XLINUXTHREAD* _class =  new XLINUXTHREAD(groupID, ID, function, param);
  return (XTHREAD*)_class;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XLINUXFACTORY::DeleteThread(XTHREADGROUPID groupID, XTHREAD* xthread)
* @brief      Delete thread
* @ingroup    PLATFORM_LINUX
*
* @param[in]  groupID : group ID of threads
* @param[in]  xthread : thread to delete
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XLINUXFACTORY::DeleteThread(XTHREADGROUPID groupID, XTHREAD* xthread)
{
  if(!xthread) return false;

  XLINUXTHREAD* _xthread = (XLINUXTHREAD*)xthread;
  delete _xthread;

  return true;
};


#pragma endregion

