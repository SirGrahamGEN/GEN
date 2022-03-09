/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XThreadCollected.cpp
*
* @class      XTHREADCOLLECTED
* @brief      eXtended Thread Collected class
* @ingroup    UTILS
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


#ifdef XTHREADCOLLECTION_ACTIVE

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XThreadCollected.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XTHREADSCOLLECTEDMANAGER* XTHREADSCOLLECTEDMANAGER::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADCOLLECTED::XTHREADCOLLECTED()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADCOLLECTED::XTHREADCOLLECTED()
{
  Clean();

  xtimerout = GEN_XFACTORY.CreateTimer();
  
  XTIMER_MODULE(xtimerout)
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADCOLLECTED::XTHREADCOLLECTED(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
* @brief      XTHREADCOLLECTED
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
* @param[in]  ID :
* @param[in]  function :
* @param[in]  param :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADCOLLECTED::XTHREADCOLLECTED(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
{
  Clean();

  directxthread = GEN_XFACTORY.CreateThread(groupID, ID, function, param);
  if(directxthread)
    {
      this->ID       = ID;
      this->function = function;
      this->param    = param;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADCOLLECTED::~XTHREADCOLLECTED()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADCOLLECTED::~XTHREADCOLLECTED()
{
  if(xtimerout)     GEN_XFACTORY.DeleteTimer(xtimerout);
  if(directxthread) GEN_XFACTORY.DeleteThread(groupID, directxthread);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADCOLLECTED::Ini(bool run)
* @brief      Ini
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  run :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADCOLLECTED::Ini(bool run)
{
  if(directxthread) return directxthread->Ini(run);

  if(run)
    {
      if(!Run(true)) return false;
    }
   else
    {
      status = XTHREADSTATUS_STOP;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADCOLLECTED::Wait(int milliseconds)
* @brief      Wait
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  milliseconds :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADCOLLECTED::Wait(int milliseconds)
{
  if(directxthread)
    {
      directxthread->Wait(milliseconds);
      return;
    }

  GEN_XSLEEP.MilliSeconds(milliseconds);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADCOLLECTED::End()
* @brief      End
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADCOLLECTED::End()
{
  if(directxthread) return directxthread->End();

  if(status == XTHREADSTATUS_END) return false;
  status = XTHREADSTATUS_EXIT;

  WaitToEnd();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADCOLLECTED::IsRunning()
* @brief      IsRunning
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADCOLLECTED::IsRunning()
{
  if(directxthread) return directxthread->IsRunning();

  if(status == XTHREADSTATUS_RUN) return true;
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADCOLLECTED::Run(bool activate)
* @brief      Run
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  activate :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADCOLLECTED::Run(bool activate)
{
  if(directxthread) return directxthread->Run(activate);

  if(activate)
    {
      if(IsRunning()) return false;
      status = XTHREADSTATUS_RUN;
    }
    else
    {
      if(!IsRunning()) return false;
      status = XTHREADSTATUS_STOP;
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADCOLLECTED::Exit()
* @brief      Exit
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADCOLLECTED::Exit()
{
  if(directxthread) return directxthread->Exit();

  status = XTHREADSTATUS_EXIT;
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADGROUPID XTHREADCOLLECTED::GetGroupID()
* @brief      GetGroupID
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XTHREADGROUPID :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADGROUPID XTHREADCOLLECTED::GetGroupID()
{
  return groupID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADCOLLECTED::SetGroupID(XTHREADGROUPID groupID)
* @brief      SetGroupID
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADCOLLECTED::SetGroupID(XTHREADGROUPID groupID)
{
  this->groupID = groupID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* XTHREADCOLLECTED::GetID()
* @brief      GetID
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* XTHREADCOLLECTED::GetID()
{
  if(directxthread)
    {
      return directxthread->GetID();
    }
    else
    {
      return &ID;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADFUNCTION XTHREADCOLLECTED::GetFunction()
* @brief      GetFunction
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XTHREADFUNCTION :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADFUNCTION  XTHREADCOLLECTED::GetFunction()
{
  if(directxthread)
    {
      return directxthread->GetFunction();
    }
    else
    {
      return function;
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADCOLLECTED::SetFunction(XTHREADFUNCTION function)
* @brief      SetFunction
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  function :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADCOLLECTED::SetFunction(XTHREADFUNCTION function)
{
  this->function = function;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* XTHREADCOLLECTED::GetParam()
* @brief      GetParam
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void* :
*
*---------------------------------------------------------------------------------------------------------------------*/
void* XTHREADCOLLECTED::GetParam()
{
  if(directxthread) return directxthread->GetParam();
  return param;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADCOLLECTED::SetParam(void* param)
* @brief      SetParam
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  param :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADCOLLECTED::SetParam(void* param)
{
  this->param = param;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XTHREADCOLLECTED::GetWaitYield()
* @brief      GetWaitYield
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XTHREADCOLLECTED::GetWaitYield()
{
  if(directxthread) return directxthread->GetWaitYield();
  return waityield;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADCOLLECTED::SetWaitYield(XDWORD waityield)
* @brief      SetWaitYield
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  waityield :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADCOLLECTED::SetWaitYield(XDWORD waityield)
{
  if(directxthread) return directxthread->SetWaitYield(priority);
  this->waityield = waityield;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADPRIORITY XTHREADCOLLECTED::GetPriority()
* @brief      GetPriority
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XTHREADPRIORITY :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADPRIORITY XTHREADCOLLECTED::GetPriority()
{
  if(directxthread) return directxthread->GetPriority();
  return priority;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADCOLLECTED::SetPriority(XTHREADPRIORITY priority)
* @brief      SetPriority
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  priority :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADCOLLECTED::SetPriority(XTHREADPRIORITY priority)
{
  if(directxthread) return directxthread->SetPriority(priority);
  this->priority = priority;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XTHREADCOLLECTED::GetStackSize()
* @brief      GetStackSize
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD XTHREADCOLLECTED::GetStackSize()
{
  return stacksize;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADCOLLECTED::SetStackSize(XDWORD stacksize)
* @brief      SetStackSize
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  stacksize :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADCOLLECTED::SetStackSize(XDWORD stacksize)
{
  this->stacksize = stacksize;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADCOLLECTED::IsInFunction()
* @brief      IsInFunction
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADCOLLECTED::IsInFunction()
{
  if(directxthread) return directxthread->IsInFunction();
  return isinfunction;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADCOLLECTED::SetIsInFunction(bool isinfunction)
* @brief      SetIsInFunction
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  isinfunction :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADCOLLECTED::SetIsInFunction(bool isinfunction)
{
  this->isinfunction = isinfunction;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADSTATUS XTHREADCOLLECTED::GetStatus()
* @brief      GetStatus
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XTHREADSTATUS :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADSTATUS XTHREADCOLLECTED::GetStatus()
{
  if(directxthread) return directxthread->GetStatusFunc();
  //if(status == XTHREADSTATUS_EXIT) return XTHREADSTATUS_UNKNOWN; // #Imanol

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADCOLLECTED::SetStatus(XTHREADSTATUS status)
* @brief      SetStatus
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  status :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADCOLLECTED::SetStatus(XTHREADSTATUS status)
{
  this->status = status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADCOLLECTED::WaitToEnd()
* @brief      WaitToEnd
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADCOLLECTED::WaitToEnd()
{
  while(GetStatus() != XTHREADSTATUS_END)
    {
      Wait();
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADCOLLECTED::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADCOLLECTED::Clean()
{
  groupID         = XTHREADGROUPID_UNKNOWN;
  ID.Empty();
  function        = NULL;
  param           = NULL;

  waityield       = XTHREAD_DEFAULTWAITYIELD;

  priority        = XTHREADPRIORITY_UNKNOWN;
  stacksize       = 0;

  isinfunction    = false;
  status          = XTHREADSTATUS_NONE;

  xtimerout       = NULL;

  directxthread   = NULL;
}



/*---------------------------------------------------------------------------------------------------------------------*/
/* THREADSCOLLECTED                                                                                                    */
/*---------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADSCOLLECTED::XTHREADSCOLLECTED(XTHREADGROUPID groupID)
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  XTHREADGROUPID :
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADSCOLLECTED::XTHREADSCOLLECTED(XTHREADGROUPID groupID)
{
  Clean();

  this->groupID = groupID;

  xthreadsvectormutex = GEN_XFACTORY.Create_Mutex();

  XSTRING stringID;

  GetGroupThreadIDString(stringID);

  if(xthreadsvectormutex)
    {
      xthread = GEN_XFACTORY.CreateThread(groupID, stringID.Get(), ThreadRunFunction, (void*)this);
      if(xthread) xthread->Ini();
    }
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADSCOLLECTEDMANAGER::XTHREADSCOLLECTED::XTHREADSCOLLECTED()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADSCOLLECTED::XTHREADSCOLLECTED()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADSCOLLECTED::~XTHREADSCOLLECTED()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADSCOLLECTED::~XTHREADSCOLLECTED()
{
  ExitAll();

  if(xthread)
    {
      xthread->End();
      GEN_XFACTORY.DeleteThread(groupID, xthread);
    }

  DeleteAll();

  if(xthreadsvectormutex) GEN_XFACTORY.Delete_Mutex(xthreadsvectormutex);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADGROUPID XTHREADSCOLLECTED::GetGroupID()
* @brief      GetGroupID
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XTHREADGROUPID :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADGROUPID XTHREADSCOLLECTED::GetGroupID()
{
  return groupID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADSCOLLECTED::SetGroupID(XTHREADGROUPID groupID)
* @brief      SetGroupID
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADSCOLLECTED::SetGroupID(XTHREADGROUPID groupID)
{
  this->groupID = groupID;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADCOLLECTED* XTHREADSCOLLECTED::Create(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
* @brief      Create
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
* @param[in]  ID :
* @param[in]  function :
* @param[in]  param :
*
* @return     XTHREADCOLLECTED* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADCOLLECTED* XTHREADSCOLLECTED::Create(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
{
  XTHREADCOLLECTED* xthreadcollected = NULL;

  if(xthread)
    {
      if(!xthreadsvectormutex) return NULL;

      xthreadsvectormutex->Lock();

      xthreadcollected = new XTHREADCOLLECTED();
      if(xthreadcollected)
        {
          xthreadcollected->SetGroupID(groupID);
          xthreadcollected->GetID()->Set(ID);
          xthreadcollected->SetFunction(function);
          xthreadcollected->SetParam(param);

          xthreadsvector.Add(xthreadcollected);
        }

      /*
      #ifdef XTRACE_ACTIVE
      XSTRING groupID;
      GetGroupThreadIDString(groupID);
      XTRACE_PRINTCOLOR(XDEBUG_COLORINFO, __L("Create THREAD COLLECTED (%02d) grupo %s: %s"), xthreadsvector.GetSize(), groupID.Get(), ID);
      #endif
      */

      xthreadsvectormutex->UnLock();
    }
    else
    {
      xthreadcollected = new XTHREADCOLLECTED(groupID, ID, function, param);
      if(xthreadcollected)
        {

        }
    }

  return xthreadcollected;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADSCOLLECTED::Delete(XTHREADGROUPID groupID, XTHREADCOLLECTED* xthreadcollected)
* @brief      Delete
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
* @param[in]  xthreadcollected :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADSCOLLECTED::Delete(XTHREADGROUPID groupID, XTHREADCOLLECTED* xthreadcollected)
{
  bool status = false;

  if(xthread)
    {
      if(!xthreadsvectormutex) return false;

      xthreadsvectormutex->Lock();

      XDWORD index = 0;

      do{ XTHREADCOLLECTED* _xthreadcollected = xthreadsvector.Get(index);
          if(xthreadcollected == _xthreadcollected)
            {
              /*
              #ifdef XTRACE_ACTIVE
              XSTRING groupID;
              GetGroupThreadIDString(groupID);
              XTRACE_PRINTCOLOR(XDEBUG_COLORINFO, __L("Delete THREAD COLLECTED (%02d) grupo %s: %s"), xthreadsvector.GetSize(), groupID.Get(), xthreadcollected->GetID()->Get());
              #endif
              */

              xthreadcollected->Exit();
              xthreadsvector.Delete(xthreadcollected);
              delete xthreadcollected;

              status = true;

              break;
            }

          index++;

        } while(index < xthreadsvector.GetSize());

      xthreadsvectormutex->UnLock();
    }
    else
    {
      delete xthreadcollected;
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADSCOLLECTED::ExitAll()
* @brief      ExitAll
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADSCOLLECTED::ExitAll()
{
  if(!xthreadsvectormutex) return false;

  xthreadsvectormutex->Lock();

  for(XDWORD c=0; c<xthreadsvector.GetSize(); c++)
    {
      XTHREADCOLLECTED* xthreadcollected  = xthreadsvector.Get(c);
      if(xthreadcollected) xthreadcollected->Exit();
    }

  xthreadsvectormutex->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADSCOLLECTED::DeleteAll()
* @brief      DeleteAll
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADSCOLLECTED::DeleteAll()
{
  if(!xthreadsvectormutex) return false;

  xthreadsvectormutex->Lock();

  xthreadsvector.DeleteContents();
  xthreadsvector.DeleteAll();

  xthreadsvectormutex->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void XTHREADSCOLLECTED::ThreadRunFunction(void* param)
* @brief      ThreadRunFunction
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  param :
*
* @return     static :
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADSCOLLECTED::ThreadRunFunction(void* param)
{
  XTHREADSCOLLECTED* xthreadscollected = (XTHREADSCOLLECTED*)param;
  if(!xthreadscollected) return;

  if(!xthreadscollected->xthreadsvectormutex) return;

  xthreadscollected->xthreadsvectormutex->Lock();

  for(XDWORD c=0; c<xthreadscollected->xthreadsvector.GetSize(); c++)
    {
      XTHREADCOLLECTED* xthreadcollected  = xthreadscollected->xthreadsvector.Get(c);
      if(xthreadcollected)
        {
          switch(xthreadcollected->GetStatus())
            {
              case XTHREADSTATUS_RUN    : xthreadcollected->SetIsInFunction(true);
                                          xthreadcollected->GetFunction()(xthreadcollected->GetParam());
                                          xthreadcollected->SetIsInFunction(false);

                                          xthreadscollected->xthread->Wait();
                                          break;

              case XTHREADSTATUS_EXIT   : xthreadcollected->SetStatus(XTHREADSTATUS_END);
                                          break;
            }
        }
    }

  xthreadscollected->xthreadsvectormutex->UnLock();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADSCOLLECTED::GetGroupThreadIDString(XSTRING& stringID)
* @brief      GetGroupThreadIDString
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  stringID :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADSCOLLECTED::GetGroupThreadIDString(XSTRING& stringID)
{
  stringID = __L("TGRP_");

  switch(groupID)
    {
      case XTHREADGROUPID_UNKNOWN                       : stringID.Add(__L("UNKNOWN"));                         break;
      case XTHREADGROUPID_SCHEDULER                     : stringID.Add(__L("SCHEDULE"));                        break;
      case XTHREADGROUPID_SCRIPT                        : stringID.Add(__L("SCRIPT"));                          break;
      case XTHREADGROUPID_DIOSTREAM                     : stringID.Add(__L("DIOSTREAM"));                       break;
      case XTHREADGROUPID_DIOSTREAMUART                 : stringID.Add(__L("DIOSTREAMUART"));                   break;
      case XTHREADGROUPID_DIOSTREAMUDP                  : stringID.Add(__L("DIOSTREAMUDP"));                    break;
      case XTHREADGROUPID_DIOSTREAMTCPIP                : stringID.Add(__L("DIOSTREAMTCPIP"));                  break;
      case XTHREADGROUPID_DIOSTREAMWIFI                 : stringID.Add(__L("DIOSTREAMWIFI"));                   break;
      case XTHREADGROUPID_DIOSTREAMBLUETOOTH            : stringID.Add(__L("DIOSTREAMBLUETOOTH"));              break;
      case XTHREADGROUPID_DIOSTREAMUSB                  : stringID.Add(__L("DIOSTREAMUSB"));                    break;
      case XTHREADGROUPID_DIOSTREAMICMP                 : stringID.Add(__L("DIOSTREAMICMP"));                   break;
      case XTHREADGROUPID_DIOSTREAMSPI                  : stringID.Add(__L("DIOSTREAMSPI"));                    break;
      case XTHREADGROUPID_DIOSTREAMCIPHER               : stringID.Add(__L("DIOSTREAMCIPHER"));                 break;
      case XTHREADGROUPID_DIOPROTOCOL                   : stringID.Add(__L("DIOPROTOCOL"));                     break;
      case XTHREADGROUPID_DIOPROTOCOL_CONNECTIONMANAGER : stringID.Add(__L("DIOPROTOCOL_CONNECTIONMANAGER"));   break;
      case XTHREADGROUPID_DIOWEBSERVER                  : stringID.Add(__L("DIOWEBSERVER"));                    break;
      case XTHREADGROUPID_DIOATCMS                      : stringID.Add(__L("DIOATCMS"));                        break;
      case XTHREADGROUPID_DIOALERTS                     : stringID.Add(__L("DIOALERTS"));                       break;
      case XTHREADGROUPID_DIOPCAP                       : stringID.Add(__L("DIOPCAP"));                         break;
      case XTHREADGROUPID_VIDEO                         : stringID.Add(__L("VIDEO"));                           break;
      case XTHREADGROUPID_APPOWNER                      :
                              default                   : { XSTRING IDlocal;
                                                            IDlocal.Format(__L("APPOWNER[%d]"), groupID);

                                                            stringID.Add(IDlocal);
                                                          }
                                                          break;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADSCOLLECTED::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADSCOLLECTED::Clean()
{
  groupID             = XTHREADGROUPID_UNKNOWN;
  xthreadsvectormutex = NULL;
  xthread             = NULL;
}



/*---------------------------------------------------------------------------------------------------------------------*/
/* XTHREADSCOLLECTEDMANAGER                                                                                            */
/*---------------------------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADSCOLLECTEDMANAGER& XTHREADSCOLLECTEDMANAGER::GetInstance()
* @brief      GetInstance
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     XTHREADSCOLLECTEDMANAGER& :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADSCOLLECTEDMANAGER& XTHREADSCOLLECTEDMANAGER::GetInstance()
{
  if(!instance) instance = new XTHREADSCOLLECTEDMANAGER();

  return (*instance);
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADSCOLLECTEDMANAGER::DelInstance()
* @brief      DelInstance
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADSCOLLECTEDMANAGER::DelInstance()
{
  if(instance)
    {
      instance->DeleteAll();

      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADSCOLLECTEDMANAGER::ActivateGroup(XTHREADGROUPID groupID)
* @brief      ActivateGroup
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADSCOLLECTEDMANAGER::ActivateGroup(XTHREADGROUPID groupID)
{
  groupthreadsactivate.Add(groupID);
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADSCOLLECTEDMANAGER::DeactivateGroup(XTHREADGROUPID groupID)
* @brief      DeactivateGroup
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADSCOLLECTEDMANAGER::DeactivateGroup(XTHREADGROUPID groupID)
{
  groupthreadsactivate.Delete(groupID);
  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADSCOLLECTEDMANAGER::IsActivateGroup(XTHREADGROUPID groupID)
* @brief      IsActivateGroup
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADSCOLLECTEDMANAGER::IsActivateGroup(XTHREADGROUPID groupID)
{
  for(XDWORD c=0; c<groupthreadsactivate.GetSize(); c++)
    {
      XTHREADGROUPID _groupID = groupthreadsactivate.Get(c);
      if(groupID == _groupID) return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADSCOLLECTED* XTHREADSCOLLECTEDMANAGER::GetThreadsCollectedByGroupID(XTHREADGROUPID groupID)
* @brief      GetThreadsCollectedByGroupID
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
*
* @return     XTHREADSCOLLECTED* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADSCOLLECTED* XTHREADSCOLLECTEDMANAGER::GetThreadsCollectedByGroupID(XTHREADGROUPID groupID)
{
  XTHREADSCOLLECTED* xthreadscollected = NULL;

  for(XDWORD c=0; c<groupthreadsvector.GetSize(); c++)
    {
      XTHREADSCOLLECTED* _xthreadscollected = groupthreadsvector.Get(c);
      if(_xthreadscollected)
        {
          if(_xthreadscollected->GetGroupID() == groupID)
            {
              xthreadscollected = _xthreadscollected;
              break;
            }
        }
    }

  return xthreadscollected;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADCOLLECTED* XTHREADSCOLLECTEDMANAGER::CreateThread(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
* @brief      CreateThread
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
* @param[in]  ID :
* @param[in]  function :
* @param[in]  param :
*
* @return     XTHREADCOLLECTED* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADCOLLECTED* XTHREADSCOLLECTEDMANAGER::CreateThread(XTHREADGROUPID groupID, XCHAR* ID, XTHREADFUNCTION function, void* param)
{
  XTHREADCOLLECTED*  xthreadcollected = NULL;
  bool               isactivategroup  = IsActivateGroup(groupID);

  if(isactivategroup)
    {
      if(!groupthreadsmutex) return NULL;

      groupthreadsmutex->Lock();

      XTHREADSCOLLECTED* xthreadscollected = GetThreadsCollectedByGroupID(groupID);
      if(!xthreadscollected)
        {
          xthreadscollected = new XTHREADSCOLLECTED(groupID);
          if(xthreadscollected) groupthreadsvector.Add(xthreadscollected);
        }

      if(xthreadscollected) xthreadcollected = xthreadscollected->Create(groupID, ID, function, param);

      groupthreadsmutex->UnLock();
    }
    else
    {
      XTHREADSCOLLECTED* xthreadscollected = new XTHREADSCOLLECTED();
      if(xthreadscollected)
        {
          xthreadcollected = xthreadscollected->Create(groupID, ID, function, param);
          delete xthreadscollected;
        }
    }

  return xthreadcollected;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADSCOLLECTEDMANAGER::DeleteThread(XTHREADGROUPID groupID, XTHREADCOLLECTED* xthreadcollected)
* @brief      DeleteThread
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @param[in]  groupID :
* @param[in]  xthreadcollected :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADSCOLLECTEDMANAGER::DeleteThread(XTHREADGROUPID groupID, XTHREADCOLLECTED* xthreadcollected)
{
  bool isactivategroup = IsActivateGroup(groupID);
  bool status          = false;

  if(isactivategroup)
    {
      if(!groupthreadsmutex) return false;

      groupthreadsmutex->Lock();

      XTHREADSCOLLECTED* xthreadscollected = GetThreadsCollectedByGroupID(isactivategroup?groupID:XTHREADGROUPID_UNGROUP);
      if(xthreadscollected)
        {
          status = xthreadscollected->Delete(groupID, xthreadcollected);
        }

      groupthreadsmutex->UnLock();
    }
    else
    {
      XTHREADSCOLLECTED* xthreadscollected = new XTHREADSCOLLECTED();
      if(xthreadscollected)
        {
          status = xthreadscollected->Delete(groupID, xthreadcollected);
          delete xthreadscollected;
        }
    }

  return status;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XTHREADSCOLLECTEDMANAGER::DeleteAll()
* @brief      DeleteAll
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XTHREADSCOLLECTEDMANAGER::DeleteAll()
{
  if(!groupthreadsmutex) return false;

  groupthreadsmutex->Lock();

  groupthreadsvector.DeleteContents();
  groupthreadsvector.DeleteAll();

  groupthreadsmutex->UnLock();

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADSCOLLECTEDMANAGER::XTHREADSCOLLECTEDMANAGER()
* @brief      Constructor
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADSCOLLECTEDMANAGER::XTHREADSCOLLECTEDMANAGER()
{
  Clean();

  groupthreadsmutex = GEN_XFACTORY.Create_Mutex();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTHREADSCOLLECTEDMANAGER::~XTHREADSCOLLECTEDMANAGER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XTHREADSCOLLECTEDMANAGER::~XTHREADSCOLLECTEDMANAGER()
{
  DeleteAll();

  groupthreadsactivate.DeleteAll();

  if(groupthreadsmutex) GEN_XFACTORY.Delete_Mutex(groupthreadsmutex);

  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XTHREADSCOLLECTEDMANAGER::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    UTILS
*
* @author     Abraham J. Velez
* @date       01/03/2016 12:00
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XTHREADSCOLLECTEDMANAGER::Clean()
{
  nogroupthread     = NULL;
  groupthreadsmutex = NULL;
}


#endif



