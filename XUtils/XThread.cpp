/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XThread.cpp
* 
* @class      XTHREAD
* @brief      eXtended Utils Thread class
* @ingroup    XUTILS
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

/*---- PRECOMPILATION INCLUDES ----------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_INCLUDES

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XThread.h"

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XTimer.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_XMUTEX


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XMUTEX::XMUTEX()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XMUTEX::XMUTEX()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XMUTEX::~XMUTEX()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XMUTEX::~XMUTEX()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMUTEX::IsLock()
* @brief      IsLock
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMUTEX::IsLock()
{
  return islock;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMUTEX::Lock()
* @brief      Lock
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMUTEX::Lock()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XMUTEX::UnLock()
* @brief      UnLock
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XMUTEX::UnLock()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XMUTEX::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XMUTEX::Clean()
{
  islock = false;
}


#pragma endregion


#pragma region CLASS_XTHREAD


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREAD::XTHREAD(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  XTHREADGROUPID :
* @param[in]  ID :
* @param[in]  function :
* @param[in]  param :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XTHREAD::XTHREAD(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
{
  Clean();

  statusfunc = XTHREADSTATUS_NONE;

  this->groupID     = groupID;
  this->ID          = ID;
  this->function    = function;
  this->param       = param;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREAD::~XTHREAD()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XTHREAD::~XTHREAD()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREAD::Ini(bool run)
* @brief      Ini
* @ingroup    XUTILS
*
* @param[in]  run :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREAD::Ini(bool run)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREAD::Wait(int miliseconds)
* @brief      Wait
* @ingroup    XUTILS
*
* @param[in]  miliseconds :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREAD::Wait(int miliseconds)
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREAD::End()
* @brief      End
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREAD::End()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREAD::IsRunning()
* @brief      IsRunning
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREAD::IsRunning()
{
  if(statusfunc == XTHREADSTATUS_RUN) return true;
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREAD::Run(bool activate)
* @brief      Run
* @ingroup    XUTILS
*
* @param[in]  activate :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREAD::Run(bool activate)
{
  if(activate)
    {
      if(IsRunning()) return false;
      statusfunc = XTHREADSTATUS_RUN;
    }
    else
    {
      if(!IsRunning()) return false;
      statusfunc = XTHREADSTATUS_STOP;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREAD::WaitToEnd(XDWORD timeout)
* @brief      WaitToEnd
* @ingroup    XUTILS
*
* @param[in]  timeout :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREAD::WaitToEnd(XDWORD timeout)
{
  if(!gotofunction)
    {
      statusfunc = XTHREADSTATUS_END;
      return true;
    }

  bool statustimeout = false;

  XTIMER* GEN_XFACTORY_CREATE(xtimerout, CreateTimer())
  if(!xtimerout) return false;
 
  while(statusfunc != XTHREADSTATUS_END)
    {
      Wait();

      if(xtimerout->GetMeasureSeconds() >= timeout)
        {
          statustimeout = true;
          break;
        }
    }

  GEN_XFACTORY.DeleteTimer(xtimerout);

  return (!statustimeout);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XTHREAD::GetWaitYield()
* @brief      GetWaitYield
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XTHREAD::GetWaitYield()
{
  return waityield;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREAD::SetWaitYield(XDWORD waityield = XTHREAD_DEFAULTWAITYIELD)
* @brief      SetWaitYield
* @ingroup    XUTILS
*
* @param[in]  waityield = XTHREAD_DEFAULTWAITYIELD :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XTHREAD::SetWaitYield(XDWORD waityield)
{
  this->waityield = waityield;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREAD::Exit()
* @brief      Exit
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREAD::Exit()
{
  statusfunc = XTHREADSTATUS_EXIT;
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADGROUPID XTHREAD::GetGroupID()
* @brief      GetGroupID
* @ingroup    XUTILS
*
* @return     XTHREADGROUPID :
*
* --------------------------------------------------------------------------------------------------------------------*/
XTHREADGROUPID XTHREAD::GetGroupID()
{
  return groupID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREAD::SetGroupID(XTHREADGROUPID groupID)
* @brief      SetGroupID
* @ingroup    XUTILS
*
* @param[in]  groupID : 
*
* @return     void : does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
void XTHREAD::SetGroupID(XTHREADGROUPID groupID)
{
  this->groupID = groupID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XTHREAD::GetID()
* @brief      GetID
* @ingroup    XUTILS
*
* @return     XSTRING* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSTRING* XTHREAD::GetID()
{
  return &ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADFUNCTION XTHREAD::GetFunction()
* @brief      GetFunction
* @ingroup    XUTILS
*
* @return     XTHREADFUNCTION :
*
* --------------------------------------------------------------------------------------------------------------------*/
XTHREADFUNCTION XTHREAD::GetFunction()
{
  return function;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* XTHREAD::GetParam()
* @brief      GetParam
* @ingroup    XUTILS
*
* @return     void* :
*
* --------------------------------------------------------------------------------------------------------------------*/
void* XTHREAD::GetParam()
{
  return param;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADPRIORITY XTHREAD::GetPriority()
* @brief      GetPriority
* @ingroup    XUTILS
*
* @return     XTHREADPRIORITY :
*
* --------------------------------------------------------------------------------------------------------------------*/
XTHREADPRIORITY XTHREAD::GetPriority()
{
  return priority;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREAD::SetPriority(XTHREADPRIORITY priority)
* @brief      SetPriority
* @ingroup    XUTILS
*
* @param[in]  priority :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XTHREAD::SetPriority(XTHREADPRIORITY priority)
{
  this->priority = priority;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XTHREAD::GetStackSize()
* @brief      GetStackSize
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XTHREAD::GetStackSize()
{
  return stacksize;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREAD::SetStackSize(XDWORD stacksize)
* @brief      SetStackSize
* @ingroup    XUTILS
*
* @param[in]  stacksize :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XTHREAD::SetStackSize(XDWORD stacksize)
{
  this->stacksize = stacksize;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREAD::IsInFunction()
* @brief      IsInFunction
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XTHREAD::IsInFunction()
{
  return isinfunction;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADSTATUS XTHREAD::GetStatusFunc()
* @brief      GetStatusFunc
* @ingroup    XUTILS
*
* @return     XTHREADSTATUS :
*
* --------------------------------------------------------------------------------------------------------------------*/
XTHREADSTATUS XTHREAD::GetStatusFunc()
{
  return statusfunc;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREAD::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XTHREAD::Clean()
{
  groupID         = XTHREADGROUPID_UNKNOWN;
  ID.Empty();
  function        = NULL;
  param           = NULL;

  waityield       = XTHREAD_DEFAULTWAITYIELD;

  priority        = XTHREADPRIORITY_UNKNOWN;
  stacksize       = 0;

  gotofunction    = false;
  isinfunction    = false;
  statusfunc      = XTHREADSTATUS_NONE;
}


#pragma endregion


#pragma endregion

