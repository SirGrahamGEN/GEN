/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XScheduler.cpp
* 
* @class      XSCHEDULER
* @brief      eXtended Utils Scheduler class
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

#include "XScheduler.h"

#include "XFactory.h"
#include "XSleep.h"
#include "XThread.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XTrace.h"

#include "XScheduler_XEvent.h"

#include "XMemory_Control.h"

#pragma endregion


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#pragma region CLASS_XSCHEDULERTASK                                                                                                     


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSCHEDULERTASK::XSCHEDULERTASK(XSCHEDULER* xscheduler)
* @brief      Constructor
* @ingroup    XUTILS
*
* @param[in]  XSCHEDULER* :
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSCHEDULERTASK::XSCHEDULERTASK(XSCHEDULER* xscheduler)
{
  Clean();

  this->xscheduler  = xscheduler;

  GEN_XFACTORY_CREATE(xtimer, CreateTimer())
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSCHEDULERTASK::~XSCHEDULERTASK()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSCHEDULERTASK::~XSCHEDULERTASK()
{
  if(xtimer)
    {
      GEN_XFACTORY.DeleteTimer(xtimer);
      xtimer = NULL;
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULERTASK::IsActive()
* @brief      IsActive
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::IsActive()
{
  return active;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULERTASK::SetIsActive(bool active)
* @brief      SetIsActive
* @ingroup    XUTILS
*
* @param[in]  active :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::SetIsActive(bool active)
{
  this->active  = active;
  if(xtimer) xtimer->Reset();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD XSCHEDULERTASK::GetID()
* @brief      GetID
* @ingroup    XUTILS
*
* @return     XDWORD :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDWORD XSCHEDULERTASK::GetID()
{
  return ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSCHEDULERTASK::SetID(XDWORD ID)
* @brief      SetID
* @ingroup    XUTILS
*
* @param[in]  ID :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSCHEDULERTASK::SetID(XDWORD ID)
{
  this->ID = ID;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XTIMER* XSCHEDULERTASK::GetXTimer()
* @brief      GetXTimer
* @ingroup    XUTILS
*
* @return     XTIMER* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XTIMER* XSCHEDULERTASK::GetXTimer()
{
  return xtimer;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULERTASK::IsInValidTimeLimit()
* @brief      IsInValidTimeLimit
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::IsInValidTimeLimit()
{
  return isinvalidtimelimit;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDATETIME* XSCHEDULERTASK::GetTimeLimitStart()
* @brief      GetTimeLimitStart
* @ingroup    XUTILS
*
* @return     XDATETIME* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* XSCHEDULERTASK::GetTimeLimitStart()
{
  return &xdatetimelimitstart;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDATETIME* XSCHEDULERTASK::GetTimeLimitEnd()
* @brief      GetTimeLimitEnd
* @ingroup    XUTILS
*
* @return     XDATETIME* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* XSCHEDULERTASK::GetTimeLimitEnd()
{
  return &xdatetimelimitend;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULERTASK::IsCyclic()
* @brief      XSCHEDULERTASK::IsCyclic
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::IsCyclic()
{
  return (!ncyclestodo)?false:true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int XSCHEDULERTASK::GetNCyclesTodo()
* @brief      XSCHEDULERTASK::GetNCyclesTodo
* @ingroup    XUTILS
*
* @return     int :
*
* --------------------------------------------------------------------------------------------------------------------*/
int XSCHEDULERTASK::GetNCyclesTodo()
{
  return ncyclestodo;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULERTASK::SetNCycles(int ncyclestodo, XDATETIME* xdatetimecadence)
* @brief      SetNCycles
* @ingroup    XUTILS
*
* @param[in]  ncyclestodo :
* @param[in]  xdatetimecadence :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::SetNCycles(int ncyclestodo, XDATETIME* xdatetimecadence)
{
  this->ncyclestodo = ncyclestodo;
  if(this->ncyclestodo<0) this->ncyclestodo = XSCHEDULER_CYCLEFOREVER;

  this->ncyclesactual = this->ncyclestodo;

  if(xdatetimecadence) this->xdatetimecadence.CopyFrom(xdatetimecadence);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULERTASK::SetNCycles(int ncyclestodo, XQWORD cadenceinseconds)
* @brief      SetNCycles
* @ingroup    XUTILS
*
* @param[in]  ncyclestodo :
* @param[in]  cadenceinseconds :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::SetNCycles(int ncyclestodo, XQWORD cadenceinseconds)
{
  XDATETIME xdatetimecadence;
  XTIMER    xtimercadence;

  xdatetimecadence.SetToZero();

  xtimercadence.Reset();
  xtimercadence.AddSeconds(cadenceinseconds);

  xtimercadence.GetMeasureToDate(&xdatetimecadence);

  return SetNCycles(ncyclestodo, &xdatetimecadence);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULERTASK::SetNCycles(int ncyclestodo, int cadenceinseconds)
* @brief      SetNCycles
* @ingroup    XUTILS
*
* @param[in]  ncyclestodo :
* @param[in]  cadenceinseconds :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::SetNCycles(int ncyclestodo, int cadenceinseconds)
{
  return SetNCycles(ncyclestodo, (XQWORD)cadenceinseconds);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULERTASK::IsStartImmediatelyCycles()
* @brief      IsStartImmediatelyCycles
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::IsStartImmediatelyCycles()
{
  return isstartimmediatelycycles;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSCHEDULERTASK::SetIsStartImmediatelyCycles(bool isstartimmediatelycycles)
* @brief      SetIsStartImmediatelyCycles
* @ingroup    XUTILS
*
* @param[in]  isstartimmediatelycycles :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSCHEDULERTASK::SetIsStartImmediatelyCycles(bool isstartimmediatelycycles)
{
  this->isstartimmediatelycycles = isstartimmediatelycycles;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULERTASK::SetTimeLimits(XDATETIME* xdatetimelimitstart, XDATETIME* xdatetimelimitend)
* @brief      SetTimeLimits
* @ingroup    XUTILS
*
* @param[in]  xdatetimelimitstart :
* @param[in]  xdatetimelimitend :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::SetTimeLimits(XDATETIME* xdatetimelimitstart, XDATETIME* xdatetimelimitend)
{
  if(xdatetimelimitstart) this->xdatetimelimitstart.CopyFrom(xdatetimelimitstart);
  if(xdatetimelimitend)   this->xdatetimelimitend.CopyFrom(xdatetimelimitend);

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSCHEDULERTASK::SetConditionDayWeek(XBYTE mask)
* @brief      SetConditionDayWeek
* @ingroup    XUTILS
*
* @param[in]  mask :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSCHEDULERTASK::SetConditionDayWeek(XBYTE mask)
{
  conditiondayweekmask =  mask;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSCHEDULERTASK::ResetCondition()
* @brief      ResetCondition
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::ResetCondition()
{
  if(!xtimer)
    {
      return false;      
    }

  xtimer->Reset();

  ncyclesmade = 0;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XSCHEDULERTASK::StartConditionImmediately()
* @brief      StartConditionImmediately
* @ingroup    XUTILS
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::StartConditionImmediately()
{
  if(!xtimer)
    {
      return false;      
    }

  xtimer->AddSeconds(xdatetimecadence.GetSeconsFromDate() + 1);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULERTASK::CheckCondition(XDATETIME* xdatetimeactual, XTIMER* xtimeractual)
* @brief      CheckCondition
* @ingroup    XUTILS
*
* @param[in]  xdatetimeactual :
* @param[in]  xtimeractual :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULERTASK::CheckCondition(XDATETIME* xdatetimeactual, XTIMER* xtimeractual)
{
  if(!xdatetimeactual) return false;

  XQWORD timeactualsec   = xdatetimeactual->GetSeconsFromDate();

  if(xdatetimelimitstart.IsValidDate())
    {
      if(timeactualsec <  xdatetimelimitstart.GetSeconsFromDate())
        {
          isinvalidtimelimit = false;

          xtimeractual->Reset();
          return false;
        }
       else isinvalidtimelimit = true;
    }

  if(xdatetimelimitend.IsValidDate())
    {
      if(timeactualsec >  xdatetimelimitend.GetSeconsFromDate())
        {
          isinvalidtimelimit = false;
          return false;

        } else isinvalidtimelimit = true;
    }

  if(conditiondayweekmask != XSCHEDULER_DAYWEEK_NONE)
    {
      if(!(GetDayOfWeekMask(xdatetimeactual) & conditiondayweekmask))
        {
          xtimeractual->Reset();
          return false;
        }
    }

  if(!ncyclesactual)  return false;

  bool checkcadence = true;
  if(isstartimmediatelycycles)
    {
      if(!ncyclesmade)  checkcadence = false;
    }

  if(checkcadence)
    {
      if(xdatetimecadence.IsValidDate())
        {
          if(xtimeractual->GetMeasureSeconds() < xdatetimecadence.GetSeconsFromDate()) return false;
        }
    }

  if(ncyclesactual>0)  ncyclesactual--;

  xtimeractual->Reset();

  ncyclesmade++;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XBYTE XSCHEDULERTASK::GetDayOfWeekMask(XDATETIME* xtimeactual)
* @brief      GetDayOfWeekMask
* @ingroup    XUTILS
*
* @param[in]  xtimeactual :
*
* @return     XBYTE :
*
* --------------------------------------------------------------------------------------------------------------------*/
XBYTE XSCHEDULERTASK::GetDayOfWeekMask(XDATETIME* xtimeactual)
{
  if(!xtimeactual) return XSCHEDULER_DAYWEEK_NONE;

  XBYTE mask = XSCHEDULER_DAYWEEK_NONE;

  switch(xtimeactual->GetDayOfWeek())
    {
      case XDATETIME_DAYWEEK_SUNDAY     : mask = XSCHEDULER_DAYWEEK_ISSUNDAY;     break;
      case XDATETIME_DAYWEEK_MONDAY     : mask = XSCHEDULER_DAYWEEK_ISMONDAY;     break;
      case XDATETIME_DAYWEEK_TUESDAY    : mask = XSCHEDULER_DAYWEEK_ISTUESDAY;    break;
      case XDATETIME_DAYWEEK_WEDNESDAY  : mask = XSCHEDULER_DAYWEEK_ISWEDNESDAY;  break;
      case XDATETIME_DAYWEEK_THURSDAY   : mask = XSCHEDULER_DAYWEEK_ISTHURSDAY;   break;
      case XDATETIME_DAYWEEK_FRIDAY     : mask = XSCHEDULER_DAYWEEK_ISFRIDAY;     break;
      case XDATETIME_DAYWEEK_SATURDAY   : mask = XSCHEDULER_DAYWEEK_ISSATURDAY;   break;
    }

  return mask;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSCHEDULERTASK::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSCHEDULERTASK::Clean()
{
  xscheduler                = NULL;
  xtimer                    = NULL;

  ID                        = 0;

  active                    = false;

  isstartimmediatelycycles  = false;
  ncyclesmade               = 0;
  ncyclestodo               = 0;
  ncyclesactual             = 0;

  isinvalidtimelimit        = false;

  conditiondayweekmask      = XSCHEDULER_DAYWEEK_NONE;
}


#pragma endregion


#pragma region CLASS_XSCHEDULER


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSCHEDULER::XSCHEDULER()
* @brief      Constructor
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSCHEDULER::XSCHEDULER()
{
  Clean();

  RegisterEvent(XEVENT_TYPE_SCHEDULER);

  GEN_XFACTORY_CREATE(xtimerwait, CreateTimer())
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSCHEDULER::~XSCHEDULER()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    XUTILS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
XSCHEDULER::~XSCHEDULER()
{
  DeRegisterEvent(XEVENT_TYPE_SCHEDULER);

  End();

  if(xtimerwait) 
    {
      GEN_XFACTORY.DeleteTimer(xtimerwait);
    }

  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULER::Ini()
* @brief      Ini
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULER::Ini()
{
  GEN_XFACTORY_CREATE(xmutexscheduler, Create_Mutex())
  if(!xmutexscheduler) return false;

  GEN_XFACTORY_CREATE(xdatetimeactual, CreateDateTime())
  if(!xdatetimeactual) return false;

  xthreadscheduler = CREATEXTHREAD(XTHREADGROUPID_SCHEDULER, __L("XSCHEDULER::Ini"),ThreadScheduler,(void*)this);
  if(!xthreadscheduler) return false;

  if(!xthreadscheduler->Ini()) return false;

  isactive = true;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULER::IsActive()
* @brief      IsActive
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULER::IsActive()
{
  return isactive;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSCHEDULER::Activate(bool on)
* @brief      Activate
* @ingroup    XUTILS
*
* @param[in]  on :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSCHEDULER::Activate(bool on)
{
  this->isactive = on;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XMUTEX* XSCHEDULER::GetMutexScheduler()
* @brief      GetMutexScheduler
* @ingroup    XUTILS
* 
* @return     XMUTEX* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XMUTEX* XSCHEDULER::GetMutexScheduler()
{
  return xmutexscheduler;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         XDATETIME* XSCHEDULER::GetDateTimeActual()
* @brief      GetDateTimeActual
* @ingroup    XUTILS
* 
* @return     XDATETIME* : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
XDATETIME* XSCHEDULER::GetDateTimeActual()
{
  return xdatetimeactual;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULER::Task_Add(XSCHEDULERTASK* task)
* @brief      Task_Add
* @ingroup    XUTILS
*
* @param[in]  task :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULER::Task_Add(XSCHEDULERTASK* task)
{
  if(!task) return false;

  if(xmutexscheduler) xmutexscheduler->Lock();

  if(task->GetXTimer()) task->GetXTimer()->Reset();

  tasks.Add(task);

  if(xmutexscheduler) xmutexscheduler->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSCHEDULERTASK* XSCHEDULER::Task_Get(int index)
* @brief      Task_Get
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     XSCHEDULERTASK* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSCHEDULERTASK* XSCHEDULER::Task_Get(int index)
{
  if(tasks.IsEmpty()) return NULL;

  return (XSCHEDULERTASK*)tasks.Get(index);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSCHEDULERTASK* XSCHEDULER::Task_GetForID(XDWORD ID)
* @brief      Task_GetForID
* @ingroup    XUTILS
*
* @param[in]  ID :
*
* @return     XSCHEDULERTASK* :
*
* --------------------------------------------------------------------------------------------------------------------*/
XSCHEDULERTASK* XSCHEDULER::Task_GetForID(XDWORD ID)
{
  if(!xmutexscheduler) return NULL;
  if(tasks.IsEmpty())  return NULL;

  xmutexscheduler->Lock();

  for(XDWORD c=0;c<tasks.GetSize();c++)
    {
      XSCHEDULERTASK* task = tasks.Get(c);
      if(task)
        {
          if(task->GetID()==ID)
            {
              xmutexscheduler->UnLock();
              return task;
            }
        }
    }

  xmutexscheduler->UnLock();

  return NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULER::Task_Del(int index)
* @brief      Task_Del
* @ingroup    XUTILS
*
* @param[in]  index :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULER::Task_Del(int index)
{
  if(!xmutexscheduler) return false;
  if(tasks.IsEmpty())  return false;

  bool status = false;

  xmutexscheduler->Lock();

  XSCHEDULERTASK* task = Task_Get(index);
  if(task)
    {
      status = tasks.Delete(task);
      delete task;
    }

  xmutexscheduler->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULER::Task_DelForID(XDWORD ID)
* @brief      Task_DelForID
* @ingroup    XUTILS
*
* @param[in]  ID :
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULER::Task_DelForID(XDWORD ID)
{
  if(!xmutexscheduler) return false;
  if(tasks.IsEmpty())  return false;

  xmutexscheduler->Lock();

  bool status = false;

  for(XDWORD c=0;c<tasks.GetSize();c++)
    {
      XSCHEDULERTASK* task = tasks.Get(c);
      if(task)
        {
          if(task->GetID()==ID)
            {
              status = tasks.Delete(task);
              delete task;
              break;
            }
        }
    }

  xmutexscheduler->UnLock();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULER::Task_DelAll()
* @brief      Task_DelAll
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULER::Task_DelAll()
{
  if(tasks.IsEmpty())  return false;

  if(xmutexscheduler) xmutexscheduler->Lock();

  tasks.DeleteContents();
  tasks.DeleteAll();

  if(xmutexscheduler) xmutexscheduler->UnLock();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XSCHEDULER::End()
* @brief      End
* @ingroup    XUTILS
*
* @return     bool : true if is succesful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool XSCHEDULER::End()
{
  isactive = false;

  if(xthreadscheduler)
    {
      xthreadscheduler->End();
      DELETEXTHREAD(XTHREADGROUPID_SCHEDULER, xthreadscheduler);

      xthreadscheduler = NULL;
    }

  Task_DelAll();

  if(xmutexscheduler)
    {
      GEN_XFACTORY.Delete_Mutex(xmutexscheduler);
      xmutexscheduler = NULL;
    }

  if(xdatetimeactual)
    {
      GEN_XFACTORY.DeleteDateTime(xdatetimeactual);
      xdatetimeactual = NULL;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSCHEDULER::ThreadScheduler(void* data)
* @brief      ThreadScheduler
* @ingroup    XUTILS
*
* @param[in]  data :
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSCHEDULER::ThreadScheduler(void* data)
{
  XSCHEDULER* xscheduler = (XSCHEDULER*)data;
  if(!xscheduler)                      
    {
      return;
    }

  if(!xscheduler->xmutexscheduler)     
    {
      return;
    }

  if(!xscheduler->xdatetimeactual)     
    {
      return;
    }

  if(!xscheduler->isactive) 
    {
      return;
    }

  GEN_XSLEEP.MilliSeconds(10);

  xscheduler->xmutexscheduler->Lock();

  XSCHEDULERTASK* task;

  task = xscheduler->Task_Get(xscheduler->indextask);
  if(!task)
    {
      xscheduler->xmutexscheduler->UnLock();
      xscheduler->indextask = 0;
      return;
    }

  if(xscheduler->xdatetimeactual) 
    {
      xscheduler->xdatetimeactual->Read();
    }

  if(task->IsActive())
    {
      if(task->CheckCondition(xscheduler->xdatetimeactual, task->GetXTimer()))
        {
          xscheduler->indextask++;
          xscheduler->xmutexscheduler->UnLock();

          XSCHEDULER_XEVENT xevent(xscheduler, XEVENT_TYPE_SCHEDULER);

          xevent.SetScheduler(xscheduler);
          xevent.SetTask(task);
          xevent.SetDateTime(xscheduler->xdatetimeactual);

          xscheduler->PostEvent(&xevent);
                 
          return;
        }
    }
   
  xscheduler->indextask++;
  xscheduler->xmutexscheduler->UnLock();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XSCHEDULER::Clean ()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    XUTILS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void XSCHEDULER::Clean ()
{
  xmutexscheduler     = NULL;
  xthreadscheduler    = NULL;
  xtimerwait          = NULL;

  isactive            = false;

  xdatetimeactual     = NULL;
  indextask           = 0;
}


#pragma endregion


#pragma endregion

