/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XSAMD5xE5xFactory.cpp
*
* @class      XSAMD5XE5XFACTORY
* @brief       SAMD5xE5x platform factory class
* @ingroup    PLATFORM_SAMD5XE5X
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

#include "XThreadCollected.h"

#include "XSAMD5xE5xDateTime.h"
#include "XSAMD5xE5xTimer.h"
#include "XSAMD5xE5xRand.h"
#include "XSAMD5xE5xSystem.h"
#include "XSAMD5xE5xThread.h"
#include "XSAMD5xE5xFlashMemory.h"

#include "XFactoryMacros.h"

#include "XSAMD5xE5xFactory.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


CREATEFUNC(XSAMD5XE5XFACTORY  , XTIMER     , XSAMD5XE5XTIMER      , CreateTimer)
DELETEFUNC(XSAMD5XE5XFACTORY  , XTIMER     , XSAMD5XE5XTIMER      , DeleteTimer)

CREATEFUNC(XSAMD5XE5XFACTORY  , XDATETIME  , XSAMD5XE5XDATETIME   , CreateDateTime)
DELETEFUNC(XSAMD5XE5XFACTORY  , XDATETIME  , XSAMD5XE5XDATETIME   , DeleteDateTime)

CREATEFUNC(XSAMD5XE5XFACTORY  , XRAND      , XSAMD5XE5XRAND       , CreateRand)
DELETEFUNC(XSAMD5XE5XFACTORY  , XRAND      , XSAMD5XE5XRAND       , DeleteRand)

CREATEFUNC(XSAMD5XE5XFACTORY  , XSYSTEM    , XSAMD5XE5XSYSTEM     , CreateSystem)
DELETEFUNC(XSAMD5XE5XFACTORY  , XSYSTEM    , XSAMD5XE5XSYSTEM     , DeleteSystem)

CREATEFUNC(XSAMD5XE5XFACTORY  , XMUTEX     , XSAMD5XE5XMUTEX      , Create_Mutex)
DELETEFUNC(XSAMD5XE5XFACTORY  , XMUTEX     , XSAMD5XE5XMUTEX      , Delete_Mutex)



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREAD* XSAMD5XE5XFACTORY::CreateThread(XTHREADGROUPID groupID, XCHAR* ID,XTHREADFUNCTION function,void* data)
* @brief      CreateThread
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
* @param[in]  ID :
* @param[in]  function :
* @param[in]  data :
*
* @return     XTHREAD* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREAD* XSAMD5XE5XFACTORY::CreateThread(XTHREADGROUPID groupID, XCHAR* ID,XTHREADFUNCTION function,void* data)
{
  XSAMD5XE5XTHREAD* _class =  new XSAMD5XE5XTHREAD(groupID, ID,function,data);
  return (XTHREAD*)_class;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSAMD5XE5XFACTORY::DeleteThread(XTHREADGROUPID groupID, XTHREAD* xthread)
* @brief      DeleteThread
* @ingroup    PLATFORM_SAMD5XE5X
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
* @param[in]  xthread :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XSAMD5XE5XFACTORY::DeleteThread(XTHREADGROUPID groupID, XTHREAD* xthread)
{
  if(!xthread) return false;

  XSAMD5XE5XTHREAD* _xthread = (XSAMD5XE5XTHREAD*)xthread;
  delete _xthread;

  return true;
};



CREATEFUNC(XSAMD5XE5XFACTORY    , XFLASHMEMORY    , XSAMD5XE5XFLASHMEMORY      , Create_FlashMemory)
DELETEFUNC(XSAMD5XE5XFACTORY    , XFLASHMEMORY    , XSAMD5XE5XFLASHMEMORY      , Delete_FlashMemory)
